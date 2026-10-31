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

extern s32 flo_22_BerryList[];
extern NpcGroupList flo_22_DefaultNPCs;
extern EvtScript flo_22_EVS_BindExitTriggers;
extern EvtScript flo_22_EVS_SetupFoliage;
extern EvtScript flo_22_EVS_SetupMusic;
extern EvtScript flo_22_EVS_SniffleHint;
extern EvtScript flo_22_EVS_TossItemIntoWell;
extern MapSettings flo_22_settings;

API_CALLABLE(AssignScript);
API_CALLABLE(CloseChoicePopup);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetNextPathPos);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(LoadPath);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(NpcFacePlayer);
API_CALLABLE(NpcJump0);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerJump);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveItemAt);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetItemPos);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcJumpscale);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerJumpscale);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(ShowConsumableChoicePopup);
API_CALLABLE(ShowMessageAtScreenPos);
API_CALLABLE(ShowMessageAtWorldPos);
API_CALLABLE(flo_22_SpawnSunEffect);
API_CALLABLE(kmr_10_PlaySpringReboundAnimation);

extern EvtScript TTYD64_flo_22_Script_MakeEntities;
extern EvtScript TTYD64_flo_22_Script_Well;
extern Vec3f TTYD64_flo_22_VectorList_Spring[];
extern EvtScript TTYD64_flo_22_Script_SpawnSpring;
extern EvtScript TTYD64_flo_22_Script_Main;
extern EvtScript TTYD64_flo_22_Script_Exit1;
extern EvtScript TTYD64_flo_22_Script_EnterSpring;
extern EvtScript TTYD64_flo_22_Script_BindWell;
extern EntryList TTYD64_flo_22_EntryList;

// clang-format off
EvtScript TTYD64_flo_22_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_ScriptSpring), 35, 0, 86, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignScript, Ref(TTYD64_flo_22_Script_Exit1))
    IfEq(GameFlag(1395), 0)
        Call(TTYD64_GetEntityPointer, MapVar(0), LVar1)
        Call(TTYD64_WritePtrField, LVar1, TTYD64_F_ENTITY_48_4U, 0)
        Call(TTYD64_WritePtrField, LVar1, TTYD64_F_ENTITY_4C_4U, 0xC47A0000)
        Call(TTYD64_WritePtrField, LVar1, TTYD64_F_ENTITY_50_4U, 0)
    EndIf
    Return
    End
};

EvtScript TTYD64_flo_22_Script_Well = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerInput, 0)
    Call(ShowConsumableChoicePopup)
    Call(CloseChoicePopup)
    Call(DisablePlayerInput, 1)
    Set(LVar8, LVar0)
    Switch(LVar8)
    CaseLe(-1)
    CaseLe(0)
        Call(ShowMessageAtScreenPos, 0x1D015C, 160, 40)
    CaseEq(158)
        ExecWait(flo_22_EVS_TossItemIntoWell)
        Call(RemoveItemAt, LVar1)
        IfEq(GameFlag(1395), 0)
            Call(ShowMessageAtWorldPos, 0x1100DD, 35, 35, 0)
            Set(GameFlag(1395), 1)
            Call(MakeItemEntity, 312, -35, 0, 0, 0, GameFlag(1392))
            Set(LVar7, LVar0)
            Call(SetNpcFlagBits, 0, 2, 1)
            Call(SetNpcFlagBits, 0, 16, 0)
            Call(SetNpcPos, 0, 35, 0, 0)
            Call(SetNpcJumpscale, 0, Float(1.0))
            Thread
                Call(NpcJump0, 0, -53, 0, 0, 25)
                Call(NpcJump0, 0, -73, 0, 0, 15)
                Call(NpcJump0, 0, -83, 0, 0, 8)
            EndThread
            Loop(53)
                Call(GetNpcPos, 0, LVar1, LVar2, LVar3)
                Call(SetItemPos, LVar7, LVar1, LVar2, LVar3)
                Wait(1)
            EndLoop
            Call(SetNpcPos, 0, 0, -1000, 0)
            Call(SetNpcFlagBits, 0, 2, 0)
            Call(SetNpcFlagBits, 0, 16, 1)
            ExecWait(TTYD64_flo_22_Script_SpawnSpring)
            Unbind
        Else
            Call(ShowMessageAtWorldPos, 0x1100DE, 35, 35, 0)
        EndIf
    CaseDefault
        ExecWait(flo_22_EVS_TossItemIntoWell)
        Call(RemoveItemAt, LVar1)
        Call(ShowMessageAtWorldPos, 0x1100DC, 35, 35, 0)
        Call(RandInt, 1, LVar1)
        IfEq(LVar1, 0)
            Call(SetNpcJumpscale, 0, Float(0.0))
            Call(NpcFacePlayer, 0, 0)
            Wait(1)
            Call(SetNpcPos, 0, 30, 0, 0)
            Call(SetNpcAnimation, 0, 0x4B0001)
            Call(NpcJump0, 0, 30, 60, 0, 20)
            Wait(10)
            Call(SetNpcAnimation, 0, 0x4B0004)
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(NpcJump0, 0, LVar0, LVar1, LVar2, 5)
            Set(MapVar(10), 1)
        Else
            Call(SetNpcPos, 1, 30, 0, 0)
            Call(SetNpcAnimation, 1, 0x48000E)
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(SetNpcJumpscale, 1, Float(2.0))
            Call(NpcJump0, 1, LVar0, LVar1, LVar2, 20)
            Set(MapVar(11), 1)
        EndIf
    EndSwitch
    Call(DisablePlayerInput, 0)
    Return
    End
};

Vec3f TTYD64_flo_22_VectorList_Spring[] = {
    { 35.0f, 0.0f, 0.0f },
    { 35.0f, 47.0f, 9.0f },
    { 35.0f, 69.0f, 26.0f },
    { 35.0f, 71.0f, 47.0f },
    { 35.0f, 57.0f, 68.0f },
    { 35.0f, 41.0f, 75.0f },
    { 34.0f, 1.0f, 84.0f },
};

EvtScript TTYD64_flo_22_Script_SpawnSpring = {
    Call(PlaySound, 8197)
    Call(LoadPath, 22, (Bytecode) TTYD64_flo_22_VectorList_Spring, 7, 0)
    Loop(0)
        Call(GetNextPathPos)
        Call(TTYD64_GetEntityPointer, MapVar(0), LVar9)
        Call(TTYD64_WritePtrField, LVar9, TTYD64_F_ENTITY_48_4F, LVar1)
        Call(TTYD64_WritePtrField, LVar9, TTYD64_F_ENTITY_4C_4F, LVar2)
        Call(TTYD64_WritePtrField, LVar9, TTYD64_F_ENTITY_50_4F, LVar3)
        Wait(1)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
    EndLoop
    Set(LVar0, 35)
    Set(LVar1, 0)
    Set(LVar2, 86)
    Add(LVar2, 30)
    Call(PlayEffect_impl, 6, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySound, 8326)
    Call(kmr_10_PlaySpringReboundAnimation, MapVar(0))
    Wait(45)
    Return
    End
};

EvtScript TTYD64_flo_22_Script_Main = {
    Set(GameByte(425), 38)
    Call(SetSpriteShading, -1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 0, Ref(flo_22_DefaultNPCs))
    ExecWait(TTYD64_flo_22_Script_MakeEntities)
    Exec(flo_22_EVS_SetupFoliage)
    Exec(TTYD64_flo_22_Script_BindWell)
    Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 0)
        Set(LVar0, Ref(flo_22_EVS_BindExitTriggers))
        Exec(EnterWalk)
    Else
        Exec(flo_22_EVS_BindExitTriggers)
        Exec(TTYD64_flo_22_Script_EnterSpring)
    EndIf
    IfEq(GameFlag(1395), 0)
        Exec(flo_22_EVS_SniffleHint)
    EndIf
    ExecWait(flo_22_EVS_SetupMusic)
    IfGe(GameByte(0), 53)
        Call(flo_22_SpawnSunEffect)
    EndIf
    Return
    End
};

EvtScript TTYD64_flo_22_Script_Exit1 = {
    IfEq(MapFlag(0), 1)
        Return
    EndIf
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerActionState, 6)
    Wait(1)
    Thread
        Wait(10)
        Call(GotoMap, (Bytecode) "flo_28", 0)
    EndThread
    Call(SetPlayerJumpscale, Float(0.7001953125))
    Call(PlayerJump, 35, 0, 0, 30)
    Return
    End
};

EvtScript TTYD64_flo_22_Script_EnterSpring = {
    Call(DisablePlayerInput, 1)
    Call(SetPlayerJumpscale, Float(1.5))
    Call(PlayerJump, 34, 25, 84, 16)
    Set(MapFlag(0), 1)
    Call(PlayerJump, -13, 0, 86, 16)
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerInput, 0)
    Set(MapFlag(0), 0)
    Return
    End
};

EvtScript TTYD64_flo_22_Script_BindWell = {
    IfEq(GameFlag(1395), 1)
        Call(MakeItemEntity, 312, -83, 0, 0, 0, GameFlag(1392))
    Else
        BindPadlock(TTYD64_flo_22_Script_Well, 256, 9, (Bytecode) flo_22_BerryList, 0, 1)
    EndIf
    Return
    End
};

EntryList TTYD64_flo_22_EntryList = {
    { -230.0f, 0.0f, 0.0f, 90.0f },
    { 35.0f, 0.0f, 0.0f, -180.0f },
};
// clang-format on

void TTYD64_InstallMap_flo_22(void) {
    flo_22_settings.main = &TTYD64_flo_22_Script_Main;
    flo_22_settings.entryList = &TTYD64_flo_22_EntryList;
    flo_22_settings.entryCount = 2;
}
