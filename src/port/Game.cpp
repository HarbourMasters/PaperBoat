#include <libultraship.h>
#include <fast/interpreter.h>
#include <fast/Fast3dWindow.h>

#include "Engine.h"

// Forward declarations for game C functions
extern "C" {
    void load_engine_data(void);
    void step_game_loop(void);
    void gfx_task_background(void);
    void gfx_draw_frame(void);
    void create_audio_system(void);
}

#ifdef _WIN32
int SDL_main(int argc, char **argv) {
#else
#if defined(__cplusplus) && defined(PLATFORM_IOS)
extern "C"
#endif
int main(int argc, char *argv[]) {
#endif
    GameEngine::Create();

    auto wnd = std::dynamic_pointer_cast<Fast::Fast3dWindow>(
        Ship::Context::GetInstance()->GetWindow()
    );

    // Initialize game systems
    create_audio_system();
    load_engine_data();

    // Main loop - target 60fps (original N64 timing)
    while (wnd->IsRunning()) {
        GameEngine::Instance->StartFrame();

        // Game logic
        step_game_loop();

        // Graphics rendering
        gfx_task_background();
        gfx_draw_frame();

        // Graphics commands processed via nuGfxTaskStart override
    }

    GameEngine::Instance->Destroy();
    return 0;
}