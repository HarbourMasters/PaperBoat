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

extern EvtScript jan_22_D_8024202C_B861AC;
extern NpcGroupList jan_22_DefaultNPCs;
extern EvtScript jan_22_EVS_Main;
extern EvtScript jan_22_EVS_MakeEntities;
extern EvtScript jan_22_EVS_SetupBasketElevator;
extern EvtScript jan_22_EVS_SetupBushes;
extern EvtScript jan_22_EVS_SetupMusic;
extern EvtScript jan_22_EVS_SetupTrees;
extern EvtScript jan_22_EVS_SetupZiplines;
extern NpcGroupList jan_22_RavenNPCs;
extern LavaReset jan_22_SafeFloorColliders[];

API_CALLABLE(EnableModel);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(ResetFromLava);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanOffset);
API_CALLABLE(SetTexPanner);

extern EvtScript TTYD64_jan_22_Script_80241D38;
extern EvtScript TTYD64_jan_22_Script_80241DF0;
extern EvtScript TTYD64_jan_22_Script_80241E94;
extern EvtScript TTYD64_jan_22_Script_80241F38;
extern EvtScript TTYD64_jan_22_Script_Main;
extern EvtScript TTYD64_jan_22_Script_InitNewStuff;
extern EvtScript TTYD64_jan_22_Script_BlastRock;
extern BombTrigger TTYD64_jan_22_TriggerCoord_Rock;

// clang-format off
EvtScript TTYD64_jan_22_Script_80241D38 = {
    SetGroup(0)
    Call(SetTexPanner, 123, 1)
    Call(SetTexPanner, 148, 1)
    Call(SetTexPanner, 156, 1)
    Set(LVar0, 0)
    Label(10)
    Call(SetTexPanOffset, 1, 0, 0, LVar0)
    Sub(LVar0, 300)
    Wait(1)
    Goto(10)
    Return
    End
};

EvtScript TTYD64_jan_22_Script_80241DF0 = {
    SetGroup(0)
    Call(SetTexPanner, 150, 2)
    Call(SetTexPanner, 152, 2)
    Set(LVar0, 0)
    Label(10)
    Call(SetTexPanOffset, 2, 0, 0, LVar0)
    Sub(LVar0, 300)
    Wait(1)
    Goto(10)
    Return
    End
};

EvtScript TTYD64_jan_22_Script_80241E94 = {
    SetGroup(0)
    Call(SetTexPanner, 145, 3)
    Call(SetTexPanner, 146, 3)
    Set(LVar0, 0)
    Label(10)
    Call(SetTexPanOffset, 3, 0, 0, LVar0)
    Sub(LVar0, 170)
    Wait(1)
    Goto(10)
    Return
    End
};

EvtScript TTYD64_jan_22_Script_80241F38 = {
    SetGroup(0)
    Call(SetTexPanner, 151, 4)
    Call(SetTexPanner, 153, 4)
    Set(LVar0, 0)
    Label(10)
    Call(SetTexPanOffset, 4, 0, 0, LVar0)
    Add(LVar0, 300)
    Wait(1)
    Goto(10)
    Return
    End
};

EvtScript TTYD64_jan_22_Script_Main = {
    Set(GameByte(425), 36)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(ModifyColliderFlags, 0, 22, 0x7FFFFE00)
    Switch(GameByte(0))
    CaseLt(22)
        Call(MakeNpcs, 0, Ref(jan_22_DefaultNPCs))
    CaseEq(38)
        Call(MakeNpcs, 0, Ref(jan_22_DefaultNPCs))
    CaseDefault
        Call(MakeNpcs, 0, Ref(jan_22_RavenNPCs))
    EndSwitch
    ExecWait(jan_22_EVS_MakeEntities)
    Exec(jan_22_EVS_SetupZiplines)
    Exec(jan_22_EVS_SetupBasketElevator)
    Exec(jan_22_EVS_SetupTrees)
    Exec(jan_22_EVS_SetupBushes)
    Call(ModifyColliderFlags, 3, 53, 3)
    Thread
        Call(ResetFromLava, (Bytecode) jan_22_SafeFloorColliders)
    EndThread
    Exec(TTYD64_jan_22_Script_InitNewStuff)
    Exec(TTYD64_jan_22_Script_80241DF0)
    Exec(TTYD64_jan_22_Script_80241E94)
    Exec(TTYD64_jan_22_Script_80241F38)
    Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 9, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 5, 0x7FFFFE00)
    Exec(jan_22_D_8024202C_B861AC)
    IfEq(GameByte(0), 38)
        Wait(65)
    EndIf
    ExecWait(jan_22_EVS_SetupMusic)
    Return
    End
};

EvtScript TTYD64_jan_22_Script_InitNewStuff = {
    IfEq(GameFlag(5383), 1)
        Call(EnableModel, 142, 0)
        Call(EnableModel, 161, 0)
        Call(ModifyColliderFlags, 0, 67, 0x7FFFFE00)
    Else
        BindTrigger(TTYD64_jan_22_Script_BlastRock, 0x100000, Ref(TTYD64_jan_22_TriggerCoord_Rock), 1, 0)
    EndIf
    Call(MakeItemEntity, 348, 1074, 90, -170, 17, GameFlag(5384))
    Exec(TTYD64_jan_22_Script_80241D38)
    Return
    End
};

EvtScript TTYD64_jan_22_Script_BlastRock = {
    Call(PlayEffect_impl, 66, 0, 142, 142, 1, 10, 30, 0, 0, 0, 0, 0, 0)
    Call(EnableModel, 142, 0)
    Call(EnableModel, 161, 0)
    Call(ModifyColliderFlags, 0, 67, 0x7FFFFE00)
    Set(GameFlag(5383), 1)
    Unbind
    Return
    End
};

BombTrigger TTYD64_jan_22_TriggerCoord_Rock = {
    .pos = { 1074.0f, 90.0f, -170.0f },
    .diameter = 2.0f
};
// clang-format on

void TTYD64_InstallMap_jan_22(void) {
    Mod_ReplaceScript("TTYD64", &jan_22_EVS_Main, &TTYD64_jan_22_Script_Main);
}
