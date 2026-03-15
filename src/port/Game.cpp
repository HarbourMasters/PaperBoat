#include <fast/Fast3dWindow.h>
#include <fast/interpreter.h>
#include <libultraship.h>

#include "Engine.h"
#include "port/interpolation/FrameInterpolation.h"

MtxF sInterpolationMatrixStack[0x1000];
MtxF* gInterpolationMatrix = &sInterpolationMatrixStack[0];

// Forward declarations for game C functions
extern "C" {
void load_engine_data(void);
void create_audio_system(void);
void init_game_globals(void);
void Graphics_ThreadUpdate(void); // New unified frame function from gfx_frame.c
}

// Bridge function: C code calls this, forwards to C++ engine
extern "C" void Graphics_PushFrame(Gfx *displayList) {
  GameEngine::ProcessGfxCommands(displayList);
}

#ifdef _WIN32
int SDL_main(int argc, char **argv) {
#else
#if defined(__cplusplus) && defined(PLATFORM_IOS)
extern "C"
#endif
    int
    main(int argc, char *argv[]) {
#endif
  GameEngine::Create();

  auto wnd = std::dynamic_pointer_cast<Fast::Fast3dWindow>(
      Ship::Context::GetInstance()->GetWindow());

  // Initialize game systems
  init_game_globals(); // Zero-initialize BSS globals FIRST (not automatic on
                       // PC)
  // Note: create_audio_system() is called by GameEngine::Create() ->
  // AudioInit()
  load_engine_data(); // Then configure them (calls clear_script_list(), etc.)

  // Main loop - single frame function handles everything
  while (wnd->IsRunning()) {
    GameEngine::Instance->StartFrame(); // Handle input/hotkeys
    FrameInterpolation_StartRecord();
    Graphics_ThreadUpdate();            // Game logic + build DL + submit
    FrameInterpolation_StopRecord();
  }

  GameEngine::Instance->Destroy();
  return 0;
}
