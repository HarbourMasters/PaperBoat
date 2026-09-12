#include "port/ShipInit.hpp"
#include <libultraship/bridge/windowbridge.h>
#include <libultraship/bridge/controllerbridge.h>
#include "port/Engine.h"

#include <ship/Context.h>
#include <ship/window/Window.h>

#include "game_modes.h"

#define CMD_REGISTER gShipContext->GetChildren().GetFirst<Ship::Console>()->AddCommand
// TODO: Commands should be using the output passed in.
#define ERROR_MESSAGE \
    std::reinterpret_pointer_cast<Ship::ConsoleWindow>(WindowGetWindowComponent()->GetGui()->GetGuiWindow("Console")) \
        ->SendErrorMessage
#define INFO_MESSAGE \
    std::reinterpret_pointer_cast<Ship::ConsoleWindow>(WindowGetWindowComponent()->GetGui()->GetGuiWindow("Console")) \
        ->SendInfoMessage

// Defined in state_startup.c.
extern "C" b32 gPortResetToTitleScreen;

static bool ResetHandler(std::shared_ptr<Ship::Console> Console, std::vector<std::string> args, std::string* output) {
    gPortResetToTitleScreen = true;
    gOverrideFlags |= GLOBAL_OVERRIDES_SOFT_RESET;
    return 1;
}

void DevConsole_Init(void) {
    CMD_REGISTER("reset", { ResetHandler, "Resets the game." });
}

static RegisterShipInitFunc initFunc(DevConsole_Init);
