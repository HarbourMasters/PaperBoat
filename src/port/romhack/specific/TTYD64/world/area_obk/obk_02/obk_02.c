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

extern NpcGroupList obk_02_DefaultNPCs;
extern EvtScript obk_02_EVS_BindExitTriggers;
extern EvtScript obk_02_EVS_ClockDoNothing;
extern EvtScript obk_02_EVS_Main;
extern EvtScript obk_02_EVS_MakeEntities;
extern EvtScript obk_02_EVS_ManageRegionVisibility;
extern EvtScript obk_02_EVS_OpenChest;
extern EvtScript obk_02_EVS_SetupBombableWall;
extern EvtScript obk_02_EVS_SetupMusic;
extern EvtScript obk_02_EVS_UpdateClock;
extern MapSettings obk_02_settings;

API_CALLABLE(AssignPanelFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAt);
API_CALLABLE(PlaySoundAtPlayer);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanOffset);
API_CALLABLE(SetTexPanner);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowEmote);
API_CALLABLE(TranslateGroup);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UpdateLerp);

extern EvtScript TTYD64_obk_02_Script_8024067C;
extern EvtScript TTYD64_obk_02_Script_Main;
extern EvtScript TTYD64_obk_02_Script_MakeEntities;
extern EvtScript TTYD64_obk_02_Script_ActivateChandelier;
extern EvtScript TTYD64_obk_02_Script_Exit3;
extern EvtScript TTYD64_obk_02_Script_TrackEntry;
extern EvtScript TTYD64_obk_02_Script_InitChest;
extern EvtScript TTYD64_obk_02_Script_DisableChandelierColliders;
extern EvtScript TTYD64_obk_02_Script_EnableChandelierColliders;
extern EntryList TTYD64_obk_02_EntryList;

// clang-format off
EvtScript TTYD64_obk_02_Script_8024067C = {
    Thread
        Call(SetTexPanner, 41, 1)
        Call(SetTexPanner, 42, 1)
        Call(SetTexPanner, 43, 1)
        Call(SetTexPanner, 44, 1)
        Call(SetTexPanner, 45, 1)
        Call(SetTexPanner, 46, 1)
        Loop(0)
            Call(SetTexPanOffset, 1, 0, 0, 0)
            Wait(2)
            Call(SetTexPanOffset, 1, 0, 32768, 0)
            Wait(2)
        EndLoop
    EndThread
    Call(SetTexPanner, 92, 0)
    Call(SetTexPanner, 93, 0)
    Set(LVar0, 0)
    Set(LVar1, 0)
    Loop(0)
        Add(LVar0, 300)
        Add(LVar1, 100)
        Call(SetTexPanOffset, 0, 0, LVar0, LVar1)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_obk_02_Script_Main = {
    Set(GameByte(425), 13)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeNpcs, 0, Ref(obk_02_DefaultNPCs))
    ExecWait(obk_02_EVS_MakeEntities)
    Exec(TTYD64_obk_02_Script_8024067C)
    Exec(obk_02_EVS_SetupBombableWall)
    Exec(obk_02_EVS_ClockDoNothing)
    Exec(obk_02_EVS_UpdateClock)
    Exec(obk_02_EVS_SetupMusic)
    Exec(TTYD64_obk_02_Script_TrackEntry)
    Exec(obk_02_EVS_ManageRegionVisibility)
    Exec(TTYD64_obk_02_Script_InitChest)
    Return
    End
};

EvtScript TTYD64_obk_02_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_Chest), 0, 0, 0, 0, 0, 0x80000000)
    Call(TTYD64_GetEntityPointer, LVar0, MapVar(2))
    Call(AssignScript, Ref(obk_02_EVS_OpenChest))
    Call(MakeEntity, Ref(Entity_HiddenPanel), 100, -210, 0, 0, 6, 0x80000000)
    Call(AssignPanelFlag, GameFlag(964))
    Return
    End
};

EvtScript TTYD64_obk_02_Script_ActivateChandelier = {
    Exec(TTYD64_obk_02_Script_EnableChandelierColliders)
    Call(ModifyColliderFlags, 0, 38, 0x7FFFFE00)
    Call(DisablePlayerInput, 1)
    Wait(15)
    Thread
        Call(PlaySoundAt, 8490, 0, 4, 26, -12)
        Call(MakeLerp, 0, -80, 10, 1)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, 50, 0, LVar0, 0)
            Call(UpdateColliderTransform, 27)
            Call(UpdateColliderTransform, 37)
            Call(UpdateColliderTransform, 40)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(PlaySoundAt, 8491, 0, 4, 26, -12)
        Call(ShakeCam, 0, 0, 10, Float(1.5))
        Wait(40)
        Set(MapFlag(0), 1)
        Call(ModifyColliderFlags, 0, 40, 0x7FFFFE00)
        Call(PlaySoundAt, 8492, 0, 4, 26, -12)
        Call(MakeLerp, -80, 0, 20, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, 50, 0, LVar0, 0)
            Call(UpdateColliderTransform, 27)
            Call(UpdateColliderTransform, 37)
            Call(UpdateColliderTransform, 40)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Set(MapFlag(0), 0)
        Call(ModifyColliderFlags, 1, 38, 0x7FFFFE00)
        Exec(TTYD64_obk_02_Script_DisableChandelierColliders)
    EndThread
    Wait(2)
    Call(SetPlayerAnimation, 0x8001F)
    Wait(20)
    Call(DisablePlayerInput, 0)
    Call(PlaySoundAtPlayer, 610, 0)
    Call(ShowEmote, 0, 0, -45, 20, 0, 0, 0, 0, 0)
    Call(SetPlayerAnimation, 0x10002)
    Set(GameFlag(962), 1)
    Wait(5)
    Return
    End
};

EvtScript TTYD64_obk_02_Script_Exit3 = {
    Unbind
    Call(PlaySound, 157)
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerActionState, 8)
    Loop(0)
        IfEq(MapFlag(0), 1)
            BreakLoop
        EndIf
        Call(SetPlayerAnimation, 0x10002)
        Call(SetPlayerAnimation, 0x80005)
        Wait(1)
    EndLoop
    Call(GotoMap, (Bytecode) "obk_11", 0)
    Loop(0)
        Call(GetModelCenter, 46)
        Sub(LVar1, 52)
        Call(GetPlayerPos, LVar0, 0, LVar2)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetPlayerAnimation, 0x10002)
        Call(SetPlayerAnimation, 0x80005)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_obk_02_Script_TrackEntry = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVar2, 75)
        Set(LVar3, 1)
        ExecWait(EnterSingleDoor)
        ExecWait(obk_02_EVS_BindExitTriggers)
    CaseEq(1)
        Set(LVar2, 77)
        Set(LVar3, 1)
        ExecWait(EnterSingleDoor)
        ExecWait(obk_02_EVS_BindExitTriggers)
    CaseEq(2)
        Set(LVar0, Ref(obk_02_EVS_BindExitTriggers))
        Exec(EnterWalk)
    CaseEq(3)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Add(LVar1, 70)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        ExecWait(obk_02_EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_obk_02_Script_InitChest = {
    Call(TTYD64_DisarmChestEntity, MapVar(2))
    Call(ParentColliderToModel, 27, 39)
    Call(ParentColliderToModel, 37, 39)
    Call(ParentColliderToModel, 40, 39)
    BindTrigger(TTYD64_obk_02_Script_ActivateChandelier, 2048, 38, 1, 0)
    BindTrigger(TTYD64_obk_02_Script_Exit3, 0x40000, 40, 1, 0)
    Exec(TTYD64_obk_02_Script_DisableChandelierColliders)
    Return
    End
};

EvtScript TTYD64_obk_02_Script_DisableChandelierColliders = {
    Call(ModifyColliderFlags, 0, 27, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 37, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 40, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 39, 0x7FFFFE00)
    Return
    End
};

EvtScript TTYD64_obk_02_Script_EnableChandelierColliders = {
    Call(ModifyColliderFlags, 1, 27, 0x7FFFFE00)
    Call(ModifyColliderFlags, 1, 37, 0x7FFFFE00)
    Call(ModifyColliderFlags, 1, 40, 0x7FFFFE00)
    Call(ModifyColliderFlags, 1, 39, 0x7FFFFE00)
    Return
    End
};

EntryList TTYD64_obk_02_EntryList = {
    { 67.0f, 0.0f, 235.0f, 0.0f },
    { 0.0f, -210.0f, 235.0f, 0.0f },
    { 220.0f, -210.0f, 65.0f, 270.0f },
    { -31.0f, 0.0f, 6.0f, -180.0f },
};
// clang-format on

void TTYD64_InstallMap_obk_02(void) {
    obk_02_settings.entryList = &TTYD64_obk_02_EntryList;
    obk_02_settings.entryCount = 4;
    Mod_ReplaceScript("TTYD64", &obk_02_EVS_Main, &TTYD64_obk_02_Script_Main);
    Mod_ReplaceScript("TTYD64", &obk_02_EVS_MakeEntities, &TTYD64_obk_02_Script_MakeEntities);
}
