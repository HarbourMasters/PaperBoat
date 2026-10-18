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

extern NpcGroupList jan_10_DefaultNPCs;
extern EvtScript jan_10_EVS_ExitWalk_jan_09_2;
extern EvtScript jan_10_EVS_Main;
extern EvtScript jan_10_EVS_MakeEntities;
extern EvtScript jan_10_EVS_SetupBushes;
extern EvtScript jan_10_EVS_SetupLogs;
extern EvtScript jan_10_EVS_SetupMusic;
extern EvtScript jan_10_EVS_SetupTrees;
extern EvtScript jan_10_EVS_UpdateTexturePan;
extern MapSettings jan_10_settings;

API_CALLABLE(EnableTexPanning);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeNpcs);
API_CALLABLE(MakeTransformGroup);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_jan_10_Script_Main_EnterWalk;
extern EvtScript TTYD64_jan_10_Script_Exit1;
extern EvtScript TTYD64_jan_10_Script_MakeExits;
extern EntryList TTYD64_jan_10_EntryList;

// clang-format off
EvtScript TTYD64_jan_10_Script_Main_EnterWalk = {
    Set(GameByte(425), 36)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 0, Ref(jan_10_DefaultNPCs))
    ExecWait(jan_10_EVS_MakeEntities)
    Exec(jan_10_EVS_SetupLogs)
    Call(ModifyColliderFlags, 3, 14, 4)
    Call(ModifyColliderFlags, 0, 14, 0x80000)
    Call(ModifyColliderFlags, 3, 32, 1)
    Exec(jan_10_EVS_SetupTrees)
    Exec(jan_10_EVS_SetupBushes)
    Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
    Set(LVar0, Ref(TTYD64_jan_10_Script_MakeExits))
    Exec(EnterWalk)
    Exec(jan_10_EVS_SetupMusic)
    Call(MakeTransformGroup, 69)
    Call(EnableTexPanning, 68, 1)
    Thread
        Set(LVar0, 1)
        Set(LVar1, -80)
        Set(LVar2, 140)
        Set(LVar3, 80)
        Set(LVar4, -100)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(jan_10_EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

EvtScript TTYD64_jan_10_Script_Exit1 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 1)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "jan_26", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_jan_10_Script_MakeExits = {
    BindTrigger(jan_10_EVS_ExitWalk_jan_09_2, 0x80000, 3, 1, 0)
    BindTrigger(TTYD64_jan_10_Script_Exit1, 0x80000, 39, 1, 0)
    Return
    End
};

EntryList TTYD64_jan_10_EntryList = {
    { 380.0f, -20.0f, 0.0f, 270.0f },
    { -94.0f, -20.0f, -116.0f, -180.0f },
};
// clang-format on

void TTYD64_InstallMap_jan_10(void) {
    jan_10_settings.entryList = &TTYD64_jan_10_EntryList;
    jan_10_settings.entryCount = 2;
    Mod_ReplaceScript("TTYD64", &jan_10_EVS_Main, &TTYD64_jan_10_Script_Main_EnterWalk);
}
