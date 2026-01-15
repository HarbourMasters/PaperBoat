#include <libultraship.h>
#include <fast/interpreter.h>

#include "Engine.h"

#ifdef _WIN32
int SDL_main(int argc, char **argv) {
#else
#if defined(__cplusplus) && defined(PLATFORM_IOS)
extern "C"
#endif
int main(int argc, char *argv[]) {
#endif
    GameEngine::Create();
    



    GameEngine::Instance->Destroy();
    return 0;
}