#include <fast/Fast3dWindow.h>
#include <fast/interpreter.h>
#include <libultraship.h>

#include <chrono>
#include <mutex>
#include <unordered_map>

#include "Engine.h"
#include "port/DevTools/ThreadWatchdog.h"
#include "port/interpolation/FrameInterpolation.h"
#include "port/os/OS.h"

#ifdef __EMSCRIPTEN__
#include <SDL2/SDL.h>
#include "port/web/WebUtils.h"
#endif
#ifdef __ANDROID__
// Redefines main() to SDL_main(), which SDLActivity calls into. The game data
// is unpacked before this process starts, by GameAssets.kt.
#include <SDL2/SDL_main.h>
#endif

MtxF sInterpolationMatrixStack[0x1000];
MtxF* gInterpolationMatrix = &sInterpolationMatrixStack[0];

extern "C" {
void load_engine_data(void);
void init_game_globals(void);

void Graphics_EnableNusysThreads(void);
void Graphics_Start(void);
void* Graphics_TaskFromList(const void* osTask);
uint32_t Graphics_TaskFlags(const void* nuTask);
int32_t Graphics_ShouldCapturePrevFrame(void);
void Graphics_DrawFrame(Gfx* backgroundList, Gfx* mainList, int32_t capturePrevFrame);
}

#define NU_SC_SWAPBUFFER 0x0001 /* nusys.h */
#define NU_SC_NORDP      0x0002

namespace {

struct InterpPair {
    int prev = -1;
    int curr = -1;
    bool should = false;
    bool capturePrevFrame = true;
};
std::mutex sInterpMutex;
std::unordered_map<const void*, InterpPair> sTaskInterp;
Gfx* sPendingNoSwap = nullptr;
InterpPair sPendingNoSwapPair;

InterpPair TakePair(const void* nuTask) {
    std::lock_guard<std::mutex> lock(sInterpMutex);
    InterpPair pair;
    auto it = sTaskInterp.find(nuTask);
    if (it != sTaskInterp.end()) {
        pair = it->second;
        sTaskInterp.erase(it);
    }
    return pair;
}

int ServiceRcp() {
    OSTask* task = OS_SpTakePendingTask();
    if (task == nullptr) {
        return 0;
    }
    const void* nuTask = Graphics_TaskFromList(task);
    const uint32_t flags = Graphics_TaskFlags(nuTask);
    InterpPair pair = TakePair(nuTask);
    Gfx* list = (Gfx*) task->t.data_ptr;

    if (flags & NU_SC_SWAPBUFFER) {
        FrameInterpolation_BeginRenderPass(pair.prev, pair.curr, pair.should);
        Graphics_DrawFrame(sPendingNoSwap, list, pair.capturePrevFrame);
        FrameInterpolation_ReleasePair(pair.prev, pair.curr);
        if (sPendingNoSwap != nullptr) {
            FrameInterpolation_ReleasePair(sPendingNoSwapPair.prev, sPendingNoSwapPair.curr);
            sPendingNoSwap = nullptr;
        }
    } else {
        if (sPendingNoSwap != nullptr) {
            FrameInterpolation_ReleasePair(sPendingNoSwapPair.prev, sPendingNoSwapPair.curr);
        }
        sPendingNoSwap = list;
        sPendingNoSwapPair = pair;
    }

    if (!(flags & NU_SC_NORDP)) {
        OS_SendEventMesg(OS_EVENT_DP);
    }
    OS_SendEventMesg(OS_EVENT_SP);
    return 1;
}

} // namespace

extern "C" void port_nuGfxOnSubmit(void* nuTask) {
    InterpPair pair;
    FrameInterpolation_GetRecordingPair(&pair.prev, &pair.curr, &pair.should);
    FrameInterpolation_ClaimPair(pair.prev, pair.curr);
    pair.capturePrevFrame = Graphics_ShouldCapturePrevFrame() != 0;
    if (Graphics_TaskFlags(nuTask) & NU_SC_SWAPBUFFER) {
        FrameInterpolation_StopRecord();
    }
    std::lock_guard<std::mutex> lock(sInterpMutex);
    auto [it, inserted] = sTaskInterp.emplace(nuTask, pair);
    if (!inserted) {
        FrameInterpolation_ReleasePair(it->second.prev, it->second.curr);
        it->second = pair;
    }
}

#ifdef _WIN32
int SDL_main(int argc, char** argv) {
#else
#if defined(__cplusplus) && defined(PLATFORM_IOS)
extern "C"
#endif
    int main(int argc, char* argv[]) {
#endif
#ifdef __EMSCRIPTEN__
    // Everything the engine writes lives under /storage, an IndexedDB mount.
    // Both calls must precede anything that looks for a file there.
    WebCache_Mount("/storage");
    WebCache_Load();
#endif

    Graphics_EnableNusysThreads();
    GameEngine::Create(argc, argv);

    auto wnd = std::dynamic_pointer_cast<Fast::Fast3dWindow>(Ship::Context::GetRawInstance()->GetWindow());

    // Initialize game systems
    init_game_globals();
    load_engine_data();

    Graphics_Start();

    while (wnd->IsRunning()) {
        ThreadWatchdog_Beat(WATCHDOG_MAIN_LOOP);
        GameEngine::Instance->StartFrame();
        OS_SiService();
        GameEngine::DrainRenderService();
        if (!ServiceRcp()) {
            if (ThreadWatchdog_IsStalled(WATCHDOG_GAME_TICK)) {
                GameEngine::Instance->RenderGuiFrame();
                SDL_Delay(16);
                continue;
            }
            SDL_Delay(1);
        }
#ifdef __EMSCRIPTEN__
        // A tab can close without warning, so sync periodically, not just on exit.
        static uint32_t lastSync = 0;
        const uint32_t now = SDL_GetTicks();
        if (now - lastSync > 5000) {
            lastSync = now;
            WebCache_Save();
        }
#endif
    }

    OS_RequestThreadExit();
    GameEngine::ShutdownRenderService();
    OS_BeginShutdown();
    OS_StopViTicker();

    GameEngine::Instance->Destroy();
    GameEngine::RelaunchIfRequested(argc, argv);
#ifdef __EMSCRIPTEN__
    // Destroy() wrote the config after the last periodic sync. Not awaited: the
    // write finishes in the page after the runtime exits.
    WebCache_SaveNoWait();
#endif
    return 0;
}
