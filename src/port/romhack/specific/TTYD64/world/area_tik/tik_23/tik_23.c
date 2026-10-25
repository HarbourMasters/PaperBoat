#include "common.h"
#include "effects.h"
#include "entity.h"
#include "foliage.h"
#include "map.h"
#include "npc.h"
#include "script_api/map.h"
#include <string.h>
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/world/maps.h"

extern EvtScript tik_23_EVS_BindExitTriggers;
extern EvtScript tik_23_EVS_ExitPipe_tik_20_2;
extern EvtScript tik_23_EVS_ExitWalk_tik_24_1;
extern EvtScript tik_23_EVS_SetupMusic;
extern MapSettings tik_23_settings;

API_CALLABLE(EnableGroup);
API_CALLABLE(GotoMap);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(SetMusic);
API_CALLABLE(StopSound);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_tik_23_InitNewStuff;
extern EntryList TTYD64_tik_23_EntryList;
extern EvtScript TTYD64_tik_23_Script_802411A0;
extern EvtScript TTYD64_tik_23_Script_BlastDoor;
extern EvtScript TTYD64_tik_23_Script_UpdateDoor;
extern EvtScript TTYD64_tik_23_Script_80242080;
extern EvtScript TTYD64_tik_23_Script_Exit2;
extern BombTrigger TTYD64_tik_23_TriggerCoord_Door;

// clang-format off
EvtScript TTYD64_tik_23_InitNewStuff = {
    Exec(TTYD64_tik_23_Script_UpdateDoor)
    Return
    End
};

EntryList TTYD64_tik_23_EntryList = {
    { -270.0f, -20.0f, -20.0f, 90.0f },
    { 107.0f, -20.0f, -115.0f, 270.0f },
    { 274.0f, -20.0f, 3.0f, -90.0f },
};

EvtScript TTYD64_tik_23_Script_802411A0 = {
    Call(SetMusic, 0, 75, 0, 8)
    Exec(TTYD64_tik_23_InitNewStuff)
    Return
    End
};

EvtScript TTYD64_tik_23_Script_BlastDoor = {
    Call(PlayEffect_impl, 66, 0, 37, 37, 1, 10, 30, 0, 0, 0, 0, 0, 0)
    Call(EnableGroup, 39, 0)
    Call(ModifyColliderFlags, 0, 15, 0x7FFFFE00)
    Set(GameFlag(4547), 1)
    Unbind
    Return
    End
};

EvtScript TTYD64_tik_23_Script_UpdateDoor = {
    IfEq(GameFlag(4547), 0)
        BindTrigger(TTYD64_tik_23_Script_BlastDoor, 0x100000, Ref(TTYD64_tik_23_TriggerCoord_Door), 1, 0)
    Else
        Call(EnableGroup, 39, 0)
        Call(ModifyColliderFlags, 0, 15, 0x7FFFFE00)
    EndIf
    Call(StopSound, 33)
    Return
    End
};

EvtScript TTYD64_tik_23_Script_80242080 = {
    BindTrigger(tik_23_EVS_ExitWalk_tik_24_1, 0x80000, 6, 1, 0)
    BindTrigger(tik_23_EVS_ExitPipe_tik_20_2, 64, 12, 1, 0)
    BindTrigger(TTYD64_tik_23_Script_Exit2, 0x80000, 18, 1, 0)
    Return
    End
};

EvtScript TTYD64_tik_23_Script_Exit2 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 2)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "tik_28", 0)
    Wait(100)
    Return
    End
};

BombTrigger TTYD64_tik_23_TriggerCoord_Door = {
    .pos = { 310.0f, -20.0f, 3.0f },
    .diameter = 0.0f
};
// clang-format on

void TTYD64_InstallMap_tik_23(void) {
    tik_23_settings.entryList = &TTYD64_tik_23_EntryList;
    tik_23_settings.entryCount = 3;
    Mod_ReplaceScript("TTYD64", &tik_23_EVS_SetupMusic, &TTYD64_tik_23_Script_802411A0);
    Mod_ReplaceScript("TTYD64", &tik_23_EVS_BindExitTriggers, &TTYD64_tik_23_Script_80242080);
}
