#include <fast/Fast3dWindow.h>
#include <fast/interpreter.h>
#include <libultraship.h>

#include "Engine.h"
#include "port/interpolation/FrameInterpolation.h"

MtxF sInterpolationMatrixStack[0x1000];
MtxF *gInterpolationMatrix = &sInterpolationMatrixStack[0];

extern "C" {
void load_engine_data(void);
void create_audio_system(void);
void init_game_globals(void);
void Graphics_ThreadUpdate(void); // New unified frame function from gfx_frame.c
}

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
  GameEngine::Create(argc, argv);

  auto wnd = std::dynamic_pointer_cast<Fast::Fast3dWindow>(
      WindowGetWindowComponent());

  // Initialize game systems
  init_game_globals();
  load_engine_data();

  // Main loop
  while (wnd->IsRunning()) {
    GameEngine::Instance->StartFrame();
    FrameInterpolation_StartRecord();
    Graphics_ThreadUpdate();
    FrameInterpolation_StopRecord();
  }

  GameEngine::Instance->Destroy();
  return 0;
}
