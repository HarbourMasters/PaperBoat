#include "common.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/TTYD64.h"
#include "port/romhack/specific/TTYD64/battle/player_gen.h"
#include "port/romhack/specific/TTYD64/battle/player_internal.h"

void TTYD64_Player_BindMessage(Bytecode* script, u8* msg) {
    const Bytecode id = Mod_RegisterInlineMessage("TTYD64", msg);
    Bytecode* cmd = script;
    Bytecode i;

    while (true) {
        const Bytecode op = cmd[0];
        const Bytecode argc = cmd[1];

        for (i = 0; i < argc; i++) {
            if (cmd[2 + i] == (Bytecode) msg) {
                cmd[2 + i] = id;
            }
        }
        if (op == EVT_OP_END) {
            break;
        }
        cmd += 2 + argc;
    }
}

API_CALLABLE(TTYD64_Player_AddBadge) {
    Bytecode* args = script->ptrReadPos;
    s32 badgeID = evt_get_variable(script, *args++);
    Bytecode outVar = *args++;

    evt_set_variable(script, outVar, add_item(badgeID));
    return ApiStatus_DONE2;
}

void TTYD64_InstallPlayerOverlays(void) {
    TTYD64_Player_InstallActionCommands();
    TTYD64_Player_InstallGenerated();
    TTYD64_Player_InstallMoveScratch();
}
