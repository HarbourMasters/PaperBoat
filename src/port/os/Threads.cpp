#include "OS.h"

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <thread>

#include <SDL2/SDL_thread.h>

namespace {

struct OsThreadState {
    void (*entry)(void*) = nullptr;
    void* arg = nullptr;
    int32_t id = 0;
    int32_t pri = 0;
    std::thread worker;
    bool started = false;
};

std::mutex sTableMutex;
std::map<void*, OsThreadState> sThreads;
std::set<void*> sEnabledEntries;

std::atomic<bool> sExitRequested { false };

std::mutex& ExitMutex() {
    static std::mutex* m = new std::mutex();
    return *m;
}

std::condition_variable& ExitCv() {
    static std::condition_variable* cv = new std::condition_variable();
    return *cv;
}

std::atomic<int> sLiveThreads { 0 };

bool ThreadEnabled(void* entry) {
    return sEnabledEntries.count(entry) != 0;
}

} // namespace

extern "C" void OS_EnableThreadEntry(void* entry) {
    std::lock_guard<std::mutex> lock(sTableMutex);
    sEnabledEntries.insert(entry);
}

extern "C" void OS_RequestThreadExit(void) {
    sExitRequested.store(true, std::memory_order_release);
}

extern "C" int OS_ThreadShouldExit(void) {
    return sExitRequested.load(std::memory_order_acquire) ? 1 : 0;
}

extern "C" void OS_JoinDecompThreads(void) {
    bool allReturned;
    {
        std::unique_lock<std::mutex> lock(ExitMutex());
        allReturned = ExitCv().wait_for(lock, std::chrono::seconds(2), [] { return sLiveThreads == 0; });
    }

    std::lock_guard<std::mutex> lock(sTableMutex);
    for (auto& entry : sThreads) {
        OsThreadState& st = entry.second;
        if (st.worker.joinable()) {
            if (allReturned) {
                st.worker.join();
            } else {
                st.worker.detach();
            }
        }
        st.started = false;
    }
}

extern "C" void OS_CreateThread(void* thread, int32_t id, void (*entry)(void*), void* arg, void* sp, int32_t pri) {
    (void) sp;

    std::lock_guard<std::mutex> lock(sTableMutex);
    OsThreadState& st = sThreads[thread];
    st.entry = entry;
    st.arg = arg;
    st.id = id;
    st.pri = pri;
    st.started = false;
}

extern "C" void OS_StartThread(void* thread) {
    std::unique_lock<std::mutex> lock(sTableMutex);

    auto it = sThreads.find(thread);
    if (it == sThreads.end()) {
        return;
    }

    OsThreadState& st = it->second;
    if (st.started || st.entry == nullptr || !ThreadEnabled((void*) st.entry)) {
        return;
    }

    st.started = true;
    {
        std::lock_guard<std::mutex> exitLock(ExitMutex());
        sLiveThreads++;
    }

    void (*entry)(void*) = st.entry;
    void* arg = st.arg;
    auto tid = std::make_shared<std::atomic<unsigned long>>(0);
    st.worker = std::thread([entry, arg, tid]() {
        tid->store((unsigned long) SDL_ThreadID(), std::memory_order_release);
        entry(arg);
        {
            std::lock_guard<std::mutex> exitLock(ExitMutex());
            sLiveThreads--;
        }
        ExitCv().notify_all();
    });
    lock.unlock();
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(50);
    while (std::chrono::steady_clock::now() < deadline) {
        const unsigned long id = tid->load(std::memory_order_acquire);
        OS_BlockedWait waits[16];
        const int n = OS_MesgSnapshotBlockedWaits(waits, 16);
        bool parked = false;
        for (int i = 0; i < n && id != 0; i++) {
            if (waits[i].tid == id) {
                parked = true;
            }
        }
        if (parked) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(200));
    }
}

extern "C" void OS_StopThread(void* thread) {
    (void) thread;
}

extern "C" void OS_SetThreadPri(void* thread, int32_t pri) {
    (void) thread;
    (void) pri;
}
