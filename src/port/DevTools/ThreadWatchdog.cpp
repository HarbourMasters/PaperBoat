#include "ThreadWatchdog.h"

#include <atomic>
#include <chrono>
#include <mutex>
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>
#include <cstring>
#include <string>
#include <thread>

#include <SDL2/SDL_thread.h>

#include "port/os/OS.h"

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
#define LH_WATCHDOG_STACKS 1
#endif

extern "C" {
#include "libultraship/libultra/types.h"
#include "libultraship/libultra/message.h"
int32_t AudioPlayerBuffered(void);
int32_t AudioPlayerGetDesiredBuffered(void);
void* osViGetCurrentFramebuffer(void);
void* osViGetNextFramebuffer(void);
}

namespace {

using Clock = std::chrono::steady_clock;

constexpr const char* kThreadNames[WATCHDOG_NUM_THREADS] = {
    "main-loop", "audio-mgr", "vi-ticker", "game-tick", "si-mgr",
};

// Blocking points in each loop that are not message-queue waits. A stall with
// no queue park is in one of these; naming them gives the reader somewhere to
// look when no symbols were available to resolve a stack.
constexpr const char* kThreadNonQueueWaits[WATCHDOG_NUM_THREADS] = {
    "HandleEvents (SDL/window), ProcessGfxCommands (renderer present), DrainRenderService callback",
    "AudioPlayerPlayFrame -> SDL_QueueAudio; port_auBgmLock (sBgmMutex) around alAudioFrame",
    "sleep_until; OS_SendEventMesg -> sMesgMutex",
    "port_runOnRenderThread sSvcCv handoff; osSetIntMask (sIntLock); port_auBgmLock (sBgmMutex) in "
    "snd_song_request_*; step_game_loop map-load I/O",
    "__osMotorAccess -> ControlDeck rumble; osSendMesg to a nuSiSendMesg reply queue",
};

// Entry point each heartbeat belongs to.
constexpr const char* kThreadLoops[WATCHDOG_NUM_THREADS] = {
    "SDL_main service loop (port/Game.cpp)",
    "nuAuMgr (audio/core/system.c)",
    "osCreateViManager ticker (port/os/VI.cpp)",
    "gfxThread (nugfxthread.c) -> Graphics_Retrace (port/gfx_frame.c) -> gfxRetrace_Callback (main.c)",
    "nuSiMgrThread (nusimgr.c) -> contRmbRetrace (nucontrmbmgr.c)",
};

// nuAuMgr skips retraces while the backend's FIFO is full, so it gets a longer
// leash than the frame-paced threads.
constexpr auto kStallAfter = std::chrono::seconds(5);
constexpr auto kRelaxedStallAfter = std::chrono::seconds(10);
constexpr auto kSampleEvery = std::chrono::milliseconds(500);
constexpr auto kRedumpEvery = std::chrono::seconds(10);

struct Heartbeat {
    std::atomic<uint64_t> count { 0 };
    std::atomic<unsigned long> tid { 0 }; // SDL thread id, recorded on first beat
    // Real (non-pseudo) thread handle, so the watcher can walk this thread's
    // stack when it stalls. Recorded on first beat alongside the tid.
    std::atomic<void*> handle { nullptr };
    // Watcher-thread state
    uint64_t lastCount = 0;
    Clock::time_point lastBeat {};
    bool started = false;
};

Heartbeat sBeats[WATCHDOG_NUM_THREADS];
std::atomic<bool> sStalledFlags[WATCHDOG_NUM_THREADS] = {};
std::thread sWatcher;
std::atomic<bool> sWatcherRun { false };

// Non-zero while a serviced thread is blocked on purpose.
std::atomic<int> sExpectedStallDepth { 0 };
std::atomic<const char*> sExpectedStallReason { nullptr };

std::string HumanDuration(std::chrono::milliseconds ms) {
    if (ms.count() < 1000) {
        return fmt::format("{}ms", ms.count());
    }
    return fmt::format("{:.1f}s", ms.count() / 1000.0);
}

// Repo source root, derived from this file's own build-time path so the check
// holds wherever the repo was cloned. The PDB records paths from the same
// compiler invocation, so our translation units share this prefix while the
// CRT/STL ones (which also contain "\src\") do not.
const std::string& ProjectSourceRoot() {
    static const std::string root = [] {
        const std::string self = __FILE__;
        const size_t pos = self.rfind("src");
        // Only usable if __FILE__ came through absolute; otherwise mark nothing
        // rather than risk the false positives a looser match produces.
        if (pos == std::string::npos || self.find(':') == std::string::npos) {
            return std::string();
        }
        return self.substr(0, pos);
    }();
    return root;
}

// Stack of the stalled thread, symbolized against the shipped PDB. Nothing else
// in the report can be reconstructed after the fact: by the time a maintainer
// reads the log the process is gone, so capture it here rather than asking for
// a debugger they cannot attach.
//
// Addresses are collected while the target is suspended and symbolized only
// after it resumes, to keep the window in which it is held as narrow as
// possible. See the caller for the hang risk this still carries.
std::string CaptureStalledStack(int threadIdx) {
#if defined(LH_WATCHDOG_STACKS)
    HANDLE thread = (HANDLE) sBeats[threadIdx].handle.load(std::memory_order_relaxed);
    if (thread == nullptr) {
        return {};
    }

    HANDLE proc = GetCurrentProcess();
    static std::once_flag symOnce;
    std::call_once(symOnce, [proc] {
        SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
        SymInitialize(proc, nullptr, TRUE);
    });

    if (SuspendThread(thread) == (DWORD) -1) {
        return {};
    }

    CONTEXT ctx = {};
    ctx.ContextFlags = CONTEXT_FULL;
    DWORD64 frames[32];
    int numFrames = 0;
    if (GetThreadContext(thread, &ctx)) {
        STACKFRAME64 sf = {};
#if defined(_M_X64)
        const DWORD machine = IMAGE_FILE_MACHINE_AMD64;
        sf.AddrPC.Offset = ctx.Rip;
        sf.AddrFrame.Offset = ctx.Rbp;
        sf.AddrStack.Offset = ctx.Rsp;
#elif defined(_M_ARM64)
        const DWORD machine = IMAGE_FILE_MACHINE_ARM64;
        sf.AddrPC.Offset = ctx.Pc;
        sf.AddrFrame.Offset = ctx.Fp;
        sf.AddrStack.Offset = ctx.Sp;
#else
        const DWORD machine = IMAGE_FILE_MACHINE_I386;
        sf.AddrPC.Offset = ctx.Eip;
        sf.AddrFrame.Offset = ctx.Ebp;
        sf.AddrStack.Offset = ctx.Esp;
#endif
        sf.AddrPC.Mode = sf.AddrFrame.Mode = sf.AddrStack.Mode = AddrModeFlat;
        // Addresses only while suspended; symbol lookup happens after resume.
        while (numFrames < 32
               && StackWalk64(
                   machine, proc, thread, &sf, &ctx, nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr
               )
               && sf.AddrPC.Offset != 0)
        {
            frames[numFrames++] = sf.AddrPC.Offset;
        }
    }
    ResumeThread(thread);

    if (numFrames == 0) {
        return {};
    }

    const std::string& srcRoot = ProjectSourceRoot();
    std::string out = "Stack:\n";
    alignas(SYMBOL_INFO) char symBuf[sizeof(SYMBOL_INFO) + 256] = {};
    auto* sym = reinterpret_cast<SYMBOL_INFO*>(symBuf);
    sym->SizeOfStruct = sizeof(SYMBOL_INFO);
    sym->MaxNameLen = 255;
    for (int i = 0; i < numFrames; i++) {
        DWORD64 symDisp = 0;
        DWORD lineDisp = 0;
        IMAGEHLP_LINE64 line = {};
        line.SizeOfStruct = sizeof(line);
        if (SymFromAddr(proc, frames[i], &symDisp, sym)) {
            if (SymGetLineFromAddr64(proc, frames[i], &lineDisp, &line)) {
                // Only frames under this repo's source root are ours; CRT and
                // STL paths contain "\src\" as well and must not match.
                const bool ours = !srcRoot.empty() && _strnicmp(line.FileName, srcRoot.c_str(), srcRoot.size()) == 0;
                out += fmt::format(
                    "{} #{:02} {}+0x{:x} ({}:{})\n", ours ? ">" : " ", i, sym->Name, symDisp, line.FileName,
                    line.LineNumber
                );
            } else {
                out += fmt::format("  #{:02} {}+0x{:x}\n", i, sym->Name, symDisp);
            }
        } else {
            // No symbols (plain Release with no PDB alongside): emit
            // module+offset, which stays resolvable later against a matching
            // build. A raw address is meaningless once ASLR is factored in.
            DWORD64 base = SymGetModuleBase64(proc, frames[i]);
            char modPath[MAX_PATH] = {};
            const char* modName = "?";
            if (base != 0 && GetModuleFileNameA((HMODULE) (uintptr_t) base, modPath, MAX_PATH) != 0) {
                const char* slash = strrchr(modPath, '\\');
                modName = slash != nullptr ? slash + 1 : modPath;
            }
            if (base != 0) {
                out += fmt::format("  #{:02} {}+0x{:x}\n", i, modName, frames[i] - base);
            } else {
                out += fmt::format("  #{:02} 0x{:x}\n", i, frames[i]);
            }
        }
    }
    return out;
#else
    (void) threadIdx;
    return {};
#endif
}

std::string BuildDump(const bool* stalled, Clock::time_point now, const std::string& stack) {
    OS_BlockedWait waits[16];
    const int numWaits = OS_MesgSnapshotBlockedWaits(waits, 16);
    auto waitFor = [&](int threadIdx) -> const OS_BlockedWait* {
        unsigned long tid = sBeats[threadIdx].tid.load(std::memory_order_relaxed);
        for (int i = 0; i < numWaits; i++) {
            if (waits[i].tid == tid) {
                return &waits[i];
            }
        }
        return nullptr;
    };
    auto ageOf = [&](int threadIdx) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(now - sBeats[threadIdx].lastBeat);
    };
    auto queueName = [](OSMesgQueue* mq) {
        const char* name = Graphics_QueueName(mq);
        return name != nullptr ? name : "unmapped queue";
    };
    auto queueFedBy = [](OSMesgQueue* mq) {
        const char* fedBy = Graphics_QueueFedBy(mq);
        return fedBy != nullptr ? fedBy : "unknown";
    };

    std::string out;

    // Downstream threads stall behind the one that actually broke, so the
    // longest-stalled thread is the best root-cause guess.
    int firstStalled = -1;
    int numStalled = 0;
    if (stalled != nullptr) {
        for (int i = 0; i < WATCHDOG_NUM_THREADS; i++) {
            if (!stalled[i]) {
                continue;
            }
            numStalled++;
            if (firstStalled < 0 || sBeats[i].lastBeat < sBeats[firstStalled].lastBeat) {
                firstStalled = i;
            }
        }
    }

    if (firstStalled < 0) {
        out += "===== Thread Watchdog: snapshot, no stall =====\n";
    } else {
        out += fmt::format(
            "===== Thread Watchdog: STALL DETECTED =====\n"
            "{} has not reported for {} (tid {}){}\n"
            "In loop: {}\n",
            kThreadNames[firstStalled], HumanDuration(ageOf(firstStalled)),
            sBeats[firstStalled].tid.load(std::memory_order_relaxed),
            numStalled > 1 ? fmt::format(", {} stalled total, this one first", numStalled) : "",
            kThreadLoops[firstStalled]
        );
        if (const OS_BlockedWait* w = waitFor(firstStalled)) {
            out += fmt::format(
                "Parked at: {} on {} {}/{}\n", w->isSend ? "osSendMesg (full)" : "osRecvMesg (empty)", queueName(w->mq),
                w->mq->validCount, w->mq->msgCount
            );
            out += fmt::format("Producers: {}\n", queueFedBy(w->mq));
        } else if (!stack.empty()) {
            out += "Parked at: no queue wait; see Stack below\n";
        } else {
            out += fmt::format(
                "Parked at: no queue wait, so loop/mutex/condvar. Candidates: {}\n", kThreadNonQueueWaits[firstStalled]
            );
        }
    }

    for (int i = 0; i < WATCHDOG_NUM_THREADS; i++) {
        const Heartbeat& hb = sBeats[i];
        uint64_t count = hb.count.load(std::memory_order_relaxed);
        if (count == 0) {
            out += fmt::format("  {:<11} never started\n", kThreadNames[i]);
            continue;
        }
        std::string age = (hb.lastBeat == Clock::time_point {}) ? std::string("?") : HumanDuration(ageOf(i));
        std::string park;
        if (const OS_BlockedWait* w = waitFor(i)) {
            park = fmt::format(
                "  {} {} {}/{}", w->isSend ? "send" : "recv", queueName(w->mq), w->mq->validCount, w->mq->msgCount
            );
        }
        out += fmt::format(
            "  {:<11} {:<7} {:>6} tid {:<6} {} beats{}\n", kThreadNames[i],
            (stalled != nullptr && stalled[i]) ? "STALLED" : "ok", age, hb.tid.load(std::memory_order_relaxed), count,
            park
        );
    }

    for (int i = 0; i < numWaits; i++) {
        bool known = false;
        for (int t = 0; t < WATCHDOG_NUM_THREADS; t++) {
            if (sBeats[t].tid.load(std::memory_order_relaxed) == waits[i].tid) {
                known = true;
                break;
            }
        }
        if (!known) {
            out += fmt::format(
                "  tid {:<6} parked {} {} {}/{}\n", waits[i].tid, waits[i].isSend ? "send" : "recv",
                queueName(waits[i].mq), waits[i].mq->validCount, waits[i].mq->msgCount
            );
        }
    }

    NusysWatchdogState nu;
    Graphics_GetWatchdogState(&nu);
    void* curFb = osViGetCurrentFramebuffer();
    void* nextFb = osViGetNextFramebuffer();
    out += fmt::format(
        "Pipeline: taskSpool={} pendingSpTask={} retraceQ={} gfxMesgQ={} gfxRequestQ={} rspQ={} rdpQ={} waitQ={} "
        "taskMgrQ={} fb cur{}next{} area={} map={}\n",
        nu.taskSpool, OS_SpPeekPendingTask() != nullptr ? "yes" : "no", nu.retraceQ, nu.gfxMesgQ, nu.gfxRequestQ,
        nu.rspQ, nu.rdpQ, nu.waitQ, nu.taskMgrQ, curFb == nextFb ? "==" : "!=", OS_ViBlackActive() ? " viBlack" : "",
        nu.areaID, nu.mapID
    );
    out += fmt::format("Audio queue: buffered={} desired={}", AudioPlayerBuffered(), AudioPlayerGetDesiredBuffered());

    if (!stack.empty()) {
        out += "\n" + stack;
    }
    return out;
}

void Watcher() {
    auto lastSample = Clock::now();
    auto lastReport = Clock::time_point {};
    bool wasStalled = false;
    bool wasExpected = false;

    while (sWatcherRun.load(std::memory_order_relaxed)) {
        std::this_thread::sleep_for(kSampleEvery);
        auto now = Clock::now();

        // A debugger pause (or system sleep) suspends every thread including
        // this one; a stale "last beat" then isn't a stall. Rebaseline.
        const bool suspended = (now - lastSample) > kSampleEvery * 4;
        lastSample = now;
        const bool expected = sExpectedStallDepth.load(std::memory_order_acquire) > 0;
        const bool rebaseline = suspended || expected || wasExpected;
        wasExpected = expected;

        bool stalled[WATCHDOG_NUM_THREADS] = {};
        bool anyStalled = false;
        for (int i = 0; i < WATCHDOG_NUM_THREADS; i++) {
            Heartbeat& hb = sBeats[i];
            uint64_t cur = hb.count.load(std::memory_order_relaxed);
            if (!hb.started) {
                if (cur == 0) {
                    continue; // thread not running yet; don't judge it
                }
                hb.started = true;
            }
            if (cur != hb.lastCount || rebaseline) {
                hb.lastCount = cur;
                hb.lastBeat = now;
                continue;
            }
            const auto limit = (i == WATCHDOG_AUDIO_MANAGER) ? kRelaxedStallAfter : kStallAfter;
            if (now - hb.lastBeat > limit) {
                stalled[i] = true;
                anyStalled = true;
            }
        }
        for (int i = 0; i < WATCHDOG_NUM_THREADS; i++) {
            sStalledFlags[i].store(stalled[i], std::memory_order_relaxed);
        }

        if (!anyStalled) {
            wasStalled = false;
            continue;
        }
        // One dump when a stall appears, then a refresher while it persists.
        if (wasStalled && (now - lastReport) < kRedumpEvery) {
            continue;
        }
        const bool firstReportOfEpisode = !wasStalled;
        wasStalled = true;
        lastReport = now;

        int root = -1;
        for (int i = 0; i < WATCHDOG_NUM_THREADS; i++) {
            if (stalled[i] && (root < 0 || sBeats[i].lastBeat < sBeats[root].lastBeat)) {
                root = i;
            }
        }

        // The stack is folded into the report below so the diagnosis is one
        // block, but walking a thread means suspending it, which can hang if it
        // holds a DbgHelp or loader lock and would take this watcher with it.
        // Leave a breadcrumb first so a hang still names the stalled thread.
        std::string stack;
        if (firstReportOfEpisode && root >= 0) {
            SPDLOG_ERROR("[Watchdog] {} stalled, collecting state", kThreadNames[root]);
            stack = CaptureStalledStack(root);
        }
        SPDLOG_ERROR("{}", BuildDump(stalled, now, stack));
    }
}

} // namespace

extern "C" void ThreadWatchdog_Beat(WatchdogThread id) {
    Heartbeat& hb = sBeats[id];
    hb.count.fetch_add(1, std::memory_order_relaxed);
    if (hb.tid.load(std::memory_order_relaxed) == 0) {
#if defined(LH_WATCHDOG_STACKS)
        // GetCurrentThread is a pseudo-handle only valid on this thread, so
        // duplicate it into one the watcher can use. Leaked by design: it must
        // outlive the thread's own loop for the whole session.
        HANDLE dup = nullptr;
        DuplicateHandle(
            GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &dup,
            THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION, FALSE, 0
        );
        hb.handle.store(dup, std::memory_order_relaxed);
#endif
        hb.tid.store((unsigned long) SDL_ThreadID(), std::memory_order_relaxed);
    }
}

extern "C" void ThreadWatchdog_Start(void) {
    if (sWatcherRun.exchange(true)) {
        return;
    }
    sWatcher = std::thread(Watcher);
}

extern "C" void ThreadWatchdog_Stop(void) {
    if (!sWatcherRun.exchange(false)) {
        return;
    }
    if (sWatcher.joinable()) {
        sWatcher.join();
    }
}

extern "C" void ThreadWatchdog_DumpNow(void) {
    SPDLOG_INFO("{}", BuildDump(nullptr, Clock::now(), std::string()));
}

extern "C" int ThreadWatchdog_IsStalled(WatchdogThread id) {
    return sStalledFlags[id].load(std::memory_order_relaxed) ? 1 : 0;
}

extern "C" void ThreadWatchdog_BeginExpectedStall(const char* reason) {
    if (sExpectedStallDepth.fetch_add(1, std::memory_order_acq_rel) == 0) {
        sExpectedStallReason.store(reason, std::memory_order_relaxed);
        SPDLOG_DEBUG("[Watchdog] stall reporting suppressed: {}", reason ? reason : "?");
    }
}

extern "C" void ThreadWatchdog_EndExpectedStall(void) {
    const int prev = sExpectedStallDepth.fetch_sub(1, std::memory_order_acq_rel);
    if (prev <= 0) {
        // Unbalanced release would leave the counter negative and suppress
        // every future stall, which is worse than the false positive.
        sExpectedStallDepth.store(0, std::memory_order_release);
        SPDLOG_WARN("[Watchdog] ThreadWatchdog_EndExpectedStall without a matching Begin");
        return;
    }
    if (prev == 1) {
        const char* reason = sExpectedStallReason.load(std::memory_order_relaxed);
        SPDLOG_DEBUG("[Watchdog] stall reporting resumed: {}", reason ? reason : "?");
        sExpectedStallReason.store(nullptr, std::memory_order_relaxed);
    }
}
