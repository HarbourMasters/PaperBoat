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
#include "port/romhack/specific/TTYD64/maps/maps.h"

extern NpcGroupList jan_07_DefaultNPCs;
extern EvtScript jan_07_EVS_ExitWalk_jan_06_1;
extern EvtScript jan_07_EVS_Main;
extern EvtScript jan_07_EVS_SetupBushes;
extern EvtScript jan_07_EVS_SetupMusic;
extern EvtScript jan_07_EVS_SetupTrees;
extern MapSettings jan_07_settings;

API_CALLABLE(EnableGroup);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(UseExitHeading);

extern BombTrigger TTYD64_jan_07_TriggerCoord_Wall;
extern EvtScript TTYD64_jan_07_Script_Main_EnterWalk;
extern EvtScript TTYD64_jan_07_Script_BlastWall;
extern EvtScript TTYD64_jan_07_Script_InitExit1;
extern EvtScript TTYD64_jan_07_Script_Exit1;
extern EvtScript TTYD64_jan_07_Script_MakeExits;
extern EvtScript TTYD64_jan_07_Script_HideWall;
extern EntryList TTYD64_jan_07_EntryList;

// clang-format off
BombTrigger TTYD64_jan_07_TriggerCoord_Wall = {
    .pos = { 90.0f, 0.0f, -35.0f },
    .diameter = 0.0f
};

EvtScript TTYD64_jan_07_Script_Main_EnterWalk = {
    Set(GameByte(425), 36)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 0, Ref(jan_07_DefaultNPCs))
    Exec(jan_07_EVS_SetupTrees)
    Exec(jan_07_EVS_SetupBushes)
    Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
    Set(LVar0, Ref(TTYD64_jan_07_Script_MakeExits))
    Exec(EnterWalk)
    Exec(TTYD64_jan_07_Script_InitExit1)
    Return
    End
};

EvtScript TTYD64_jan_07_Script_BlastWall = {
    Call(PlayEffect_impl, 66, 0, 41, 41, 1, 10, 30, 0, 0, 0, 0, 0, 0)
    Exec(TTYD64_jan_07_Script_HideWall)
    Set(GameFlag(5392), 1)
    Unbind
    Return
    End
};

EvtScript TTYD64_jan_07_Script_InitExit1 = {
    IfEq(GameFlag(5392), 0)
        BindTrigger(TTYD64_jan_07_Script_BlastWall, 0x100000, Ref(TTYD64_jan_07_TriggerCoord_Wall), 1, 0)
    Else
        Exec(TTYD64_jan_07_Script_HideWall)
    EndIf
    Exec(jan_07_EVS_SetupMusic)
    Return
    End
};

EvtScript TTYD64_jan_07_Script_Exit1 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 1)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "jan_25", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_jan_07_Script_MakeExits = {
    BindTrigger(jan_07_EVS_ExitWalk_jan_06_1, 0x80000, 0, 1, 0)
    BindTrigger(TTYD64_jan_07_Script_Exit1, 0x80000, 20, 1, 0)
    Return
    End
};

EvtScript TTYD64_jan_07_Script_HideWall = {
    Call(EnableGroup, 43, 0)
    Call(ModifyColliderFlags, 0, 19, 0x7FFFFE00)
    Return
    End
};

EntryList TTYD64_jan_07_EntryList = {
    { -220.0f, 0.0f, 0.0f, 90.0f },
    { 87.0f, 0.0f, -12.0f, -180.0f },
};
// clang-format on

void TTYD64_InstallMap_jan_07(void) {
    jan_07_settings.entryList = &TTYD64_jan_07_EntryList;
    jan_07_settings.entryCount = 2;
    Mod_ReplaceScript("TTYD64", &jan_07_EVS_Main, &TTYD64_jan_07_Script_Main_EnterWalk);
}
