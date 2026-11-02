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

extern NpcGroupList flo_14_DefaultNPCs;
extern EvtScript flo_14_EVS_ExitWalk_flo_00_1;
extern EvtScript flo_14_EVS_ExitWalk_flo_13_0;
extern EvtScript flo_14_EVS_Main;
extern EvtScript flo_14_EVS_MakeEntities;
extern EvtScript flo_14_EVS_SetupBubbles;
extern EvtScript flo_14_EVS_SetupLogBridges;
extern EvtScript flo_14_EVS_SetupMusic;
extern EvtScript flo_14_EVS_UpdateTexturePan;
extern MapSettings flo_14_settings;

API_CALLABLE(EnableTexPanning);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(ResetFromLava);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(UseExitHeading);
API_CALLABLE(flo_14_SpawnSunEffect);

extern LavaReset TTYD64_flo_14_LavaResetList_802425FC[];
extern EntryList TTYD64_flo_14_EntryList;
extern EvtScript TTYD64_flo_14_Script_Main_EnterWalk;
extern EvtScript TTYD64_flo_14_Script_MakeExits;
extern EvtScript TTYD64_flo_14_Script_Exit2;

// clang-format off
LavaReset TTYD64_flo_14_LavaResetList_802425FC[] = {
    { .colliderID = 31, .pos = { -500.0f, 0.0f, -90.0f } },
    { .colliderID = 25, .pos = { -510.0f, 0.0f, 0.0f } },
    { .colliderID = 32, .pos = { -500.0f, 0.0f, 110.0f } },
    { .colliderID = 33, .pos = { -250.0f, 0.0f, -90.0f } },
    { .colliderID = 26, .pos = { -240.0f, 0.0f, 0.0f } },
    { .colliderID = 34, .pos = { -250.0f, 0.0f, 110.0f } },
    { .colliderID = 27, .pos = { -50.0f, 0.0f, 25.0f } },
    { .colliderID = 28, .pos = { 70.0f, 60.0f, -95.0f } },
    { .colliderID = 29, .pos = { 410.0f, 60.0f, -95.0f } },
    { .colliderID = 30, .pos = { 550.0f, 0.0f, 50.0f } },
    { .colliderID = 35, .pos = { -50.0f, 0.0f, 110.0f } },
    { .colliderID = 45, .pos = { 227.0f, 4.0f, -160.0f } },
    { .colliderID = -1, .pos = { 0.0f, 0.0f, 0.0f } },
};

EntryList TTYD64_flo_14_EntryList = {
    { 720.0f, 0.0f, 0.0f, 270.0f },
    { -720.0f, 0.0f, 0.0f, 90.0f },
    { 227.0f, 4.0f, -160.0f, -180.0f },
};

EvtScript TTYD64_flo_14_Script_Main_EnterWalk = {
    Set(GameByte(425), 38)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 0, Ref(flo_14_DefaultNPCs))
    Exec(flo_14_EVS_MakeEntities)
    Call(ModifyColliderFlags, 3, 9, 2)
    Thread
        Call(ResetFromLava, (Bytecode) TTYD64_flo_14_LavaResetList_802425FC)
    EndThread
    Call(EnableTexPanning, 29, 1)
    Call(EnableTexPanning, 31, 1)
    Call(EnableTexPanning, 32, 1)
    Call(EnableTexPanning, 35, 1)
    Call(EnableTexPanning, 36, 1)
    Call(EnableTexPanning, 39, 1)
    Call(EnableTexPanning, 41, 1)
    Call(EnableTexPanning, 43, 1)
    Call(EnableTexPanning, 45, 1)
    Call(EnableTexPanning, 47, 1)
    Call(EnableTexPanning, 49, 1)
    Call(EnableTexPanning, 51, 1)
    Call(EnableTexPanning, 53, 1)
    Call(EnableTexPanning, 30, 1)
    Call(EnableTexPanning, 33, 1)
    Call(EnableTexPanning, 34, 1)
    Call(EnableTexPanning, 37, 1)
    Call(EnableTexPanning, 38, 1)
    Call(EnableTexPanning, 42, 1)
    Call(EnableTexPanning, 44, 1)
    Call(EnableTexPanning, 46, 1)
    Call(EnableTexPanning, 48, 1)
    Call(EnableTexPanning, 50, 1)
    Call(EnableTexPanning, 52, 1)
    Call(EnableTexPanning, 54, 1)
    Thread
        Set(LVar0, 1)
        Set(LVar1, 140)
        Set(LVar2, 0)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 1)
        Set(LVar6, 0)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(flo_14_EVS_UpdateTexturePan)
    EndThread
    Thread
        Set(LVar0, 2)
        Set(LVar1, -200)
        Set(LVar2, 0)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 1)
        Set(LVar6, 0)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(flo_14_EVS_UpdateTexturePan)
    EndThread
    Exec(flo_14_EVS_SetupBubbles)
    Exec(flo_14_EVS_SetupLogBridges)
    Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 5, 0x7FFFFE00)
    Set(LVar0, Ref(TTYD64_flo_14_Script_MakeExits))
    Exec(EnterWalk)
    ExecWait(flo_14_EVS_SetupMusic)
    IfGe(GameByte(0), 53)
        Call(flo_14_SpawnSunEffect)
    EndIf
    Return
    End
};

EvtScript TTYD64_flo_14_Script_MakeExits = {
    BindTrigger(flo_14_EVS_ExitWalk_flo_13_0, 0x80000, 0, 1, 0)
    BindTrigger(flo_14_EVS_ExitWalk_flo_00_1, 0x80000, 4, 1, 0)
    BindTrigger(TTYD64_flo_14_Script_Exit2, 0x80000, 44, 1, 0)
    Return
    End
};

EvtScript TTYD64_flo_14_Script_Exit2 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 2)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "flo_26", 0)
    Wait(100)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_flo_14(void) {
    flo_14_settings.entryList = &TTYD64_flo_14_EntryList;
    flo_14_settings.entryCount = 3;
    Mod_ReplaceScript("TTYD64", &flo_14_EVS_Main, &TTYD64_flo_14_Script_Main_EnterWalk);
}
