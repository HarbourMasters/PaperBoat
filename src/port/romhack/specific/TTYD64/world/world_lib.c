#include "common.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/TTYD64.h"
#include "port/romhack/specific/TTYD64/world/world_lib.h"
#include "port/romhack/specific/TTYD64/world/world_lib_gen.h"

s32 TTYD64_WorldLib_MsgID(const u8* msg) {
    return Mod_RegisterInlineMessage("TTYD64", msg);
}

static void bind_messages(Bytecode* script) {
    Bytecode* cmd = script;
    Bytecode argc;
    Bytecode i;
    s32 m;

    while (true) {
        argc = cmd[1];
        for (i = 0; i < argc; i++) {
            for (m = 0; m < TTYD64_WorldLib_MessageCount; m++) {
                if (cmd[2 + i] == (Bytecode) TTYD64_WorldLib_Messages[m]) {
                    cmd[2 + i] = TTYD64_WorldLib_MsgID(TTYD64_WorldLib_Messages[m]);
                    break;
                }
            }
        }
        if (cmd[0] == EVT_OP_END) {
            break;
        }
        cmd += 2 + argc;
    }
}

void TTYD64_InstallWorldLib(void) {
    s32 i;

    for (i = 0; i < TTYD64_WorldLib_MessageCount; i++) {
        TTYD64_WorldLib_MsgID(TTYD64_WorldLib_Messages[i]);
    }
    for (i = 0; i < TTYD64_WorldLib_MsgScriptCount; i++) {
        bind_messages(TTYD64_WorldLib_MsgScripts[i]);
    }
}
