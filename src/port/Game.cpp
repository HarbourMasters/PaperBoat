#include <fast/Fast3dWindow.h>
#include <fast/interpreter.h>
#include <libultraship.h>

#include "Engine.h"
#include "port/interpolation/FrameInterpolation.h"

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
void create_audio_system(void);
void init_game_globals(void);
void Graphics_ThreadUpdate(void); // New unified frame function from gfx_frame.c
}

extern "C" void Graphics_PushFrame(Gfx* displayList) {
    GameEngine::ProcessGfxCommands(displayList);
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

    GameEngine::Create(argc, argv);

    auto wnd = std::dynamic_pointer_cast<Fast::Fast3dWindow>(Ship::Context::GetRawInstance()->GetWindow());

    // Initialize game systems
    init_game_globals();
    load_engine_data();

    // Main loop
    while (wnd->IsRunning()) {
        GameEngine::Instance->StartFrame();
        FrameInterpolation_StartRecord();
        Graphics_ThreadUpdate();
        FrameInterpolation_StopRecord();
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

    GameEngine::Instance->Destroy();
    GameEngine::RelaunchIfRequested(argc, argv);
#ifdef __EMSCRIPTEN__
    // Destroy() wrote the config after the last periodic sync. Not awaited: the
    // write finishes in the page after the runtime exits.
    WebCache_SaveNoWait();
#endif
    return 0;
}
