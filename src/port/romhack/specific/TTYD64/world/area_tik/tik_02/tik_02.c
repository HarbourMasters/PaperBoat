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

extern u8 tik_02_DripVolumes[];
extern EvtScript tik_02_EVS_BindExitTriggers;
extern EvtScript tik_02_EVS_CreateDripVolumes;
extern EvtScript tik_02_EVS_ExitWalk_tik_18_1;
extern EvtScript tik_02_EVS_SetupDrips;
extern MapSettings tik_02_settings;

API_CALLABLE(EnableGroup);
API_CALLABLE(GotoMap);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(UseExitHeading);

extern BombTrigger TTYD64_tik_02_TriggerCoord_Wall;
extern EntryList TTYD64_tik_02_EntryList;
extern EvtScript TTYD64_tik_02_Script_80241B48;
extern EvtScript TTYD64_tik_02_Script_BlastWall;
extern EvtScript TTYD64_tik_02_Script_InitNewStuff;
extern EvtScript TTYD64_tik_02_Script_Exit1;
extern EvtScript TTYD64_tik_02_Script_80240B48;
extern EvtScript TTYD64_tik_02_Script_HideCrack;

// clang-format off
BombTrigger TTYD64_tik_02_TriggerCoord_Wall = {
    .pos = { 644.0f, -10.0f, 18.0f },
    .diameter = 0.0f
};

EntryList TTYD64_tik_02_EntryList = {
    { -360.0f, -10.0f, 0.0f, 90.0f },
    { 606.0f, -10.0f, 18.0f, -90.0f },
};

EvtScript TTYD64_tik_02_Script_80241B48 = {
    Set(LVar0, Ref(tik_02_DripVolumes))
    Exec(tik_02_EVS_CreateDripVolumes)
    Exec(TTYD64_tik_02_Script_InitNewStuff)
    Return
    End
};

EvtScript TTYD64_tik_02_Script_BlastWall = {
    Call(PlayEffect_impl, 66, 0, 39, 39, 1, 10, 30, 0, 0, 0, 0, 0, 0)
    Exec(TTYD64_tik_02_Script_HideCrack)
    Set(GameFlag(4535), 1)
    Unbind
    Return
    End
};

EvtScript TTYD64_tik_02_Script_InitNewStuff = {
    IfEq(GameFlag(4535), 1)
        Exec(TTYD64_tik_02_Script_HideCrack)
    Else
        BindTrigger(TTYD64_tik_02_Script_BlastWall, 0x100000, Ref(TTYD64_tik_02_TriggerCoord_Wall), 1, 0)
    EndIf
    Call(SetCamSpeed, 0, 3)
    Return
    End
};

EvtScript TTYD64_tik_02_Script_Exit1 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 1)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "pit_00", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_tik_02_Script_80240B48 = {
    BindTrigger(tik_02_EVS_ExitWalk_tik_18_1, 0x80000, 8, 1, 0)
    BindTrigger(TTYD64_tik_02_Script_Exit1, 0x80000, 20, 1, 0)
    Return
    End
};

EvtScript TTYD64_tik_02_Script_HideCrack = {
    Call(EnableGroup, 41, 0)
    Call(ModifyColliderFlags, 0, 18, 0x7FFFFE00)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_tik_02(void) {
    tik_02_settings.entryList = &TTYD64_tik_02_EntryList;
    tik_02_settings.entryCount = 2;
    Mod_ReplaceScript("TTYD64", &tik_02_EVS_SetupDrips, &TTYD64_tik_02_Script_80241B48);
    Mod_ReplaceScript("TTYD64", &tik_02_EVS_BindExitTriggers, &TTYD64_tik_02_Script_80240B48);
}
