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

extern NpcGroupList kzn_03_DefaultNPCs;
extern EvtScript kzn_03_EVS_BindTriggers;
extern EvtScript kzn_03_EVS_ExitWalk_kzn_02_1;
extern EvtScript kzn_03_EVS_ExitWalk_kzn_04_0;
extern EvtScript kzn_03_EVS_ExitWalk_kzn_05_1;
extern EvtScript kzn_03_EVS_ExitWalk_kzn_09_0;
extern EvtScript kzn_03_EVS_ExitWalk_kzn_09_2;
extern EvtScript kzn_03_EVS_Main;
extern EvtScript kzn_03_EVS_MakeEntities;
extern EvtScript kzn_03_EVS_OnBreakBlock;
extern EvtScript kzn_03_EVS_SetupZiplines;
extern EvtScript kzn_03_EVS_UpdateTexturePan;
extern EvtScript kzn_03_EVS_UseSpringA;
extern EvtScript kzn_03_EVS_UseSpringB;
extern EvtScript kzn_03_EVS_UseSpringC;
extern MapSettings kzn_03_settings;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(EnableTexPanning);
API_CALLABLE(GetCurrentPartnerID);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetLoadType);
API_CALLABLE(GetPartnerInUse);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(HidePlayerShadow);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(InterruptUsePartner);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlayAmbientSounds);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerFlagBits);
API_CALLABLE(SetPlayerImgFXFlags);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanOffset);
API_CALLABLE(SetTexPanner);
API_CALLABLE(UpdatePlayerImgFX);
API_CALLABLE(kzn_03_IsPlayerOnFirstCliff);

extern EvtScript TTYD64_kzn_03_Script_InitNewStuff;
extern EvtScript TTYD64_kzn_03_Script_802431BC;
extern EvtScript TTYD64_kzn_03_Script_802432D8;
extern EvtScript TTYD64_kzn_03_Script_EnterMap;
extern EvtScript TTYD64_kzn_03_Script_8024365C;
extern EvtScript TTYD64_kzn_03_Script_Main_EnterWalk;
extern EvtScript TTYD64_kzn_03_Script_MakeEntities;
extern EvtScript TTYD64_kzn_03_Script_EnterVerticalPipe;
extern EvtScript TTYD64_kzn_03_Script_ExitVerticalPipe;
extern EvtScript TTYD64_kzn_03_Script_802435C0;
extern EntryList TTYD64_kzn_03_EntryList;
extern EvtScript TTYD64_kzn_03_Script_Exit5;
extern EvtScript TTYD64_kzn_03_Script_GotoMap_Exit5;
extern EvtScript TTYD64_kzn_03_Script_SetCameraSpeed_Normal;
extern EvtScript TTYD64_kzn_03_Script_SetCameraSpeed_Faster;

// clang-format off
EvtScript TTYD64_kzn_03_Script_InitNewStuff = {
    BindTrigger(TTYD64_kzn_03_Script_SetCameraSpeed_Normal, 0x80000, 16, 1, 0)
    BindTrigger(TTYD64_kzn_03_Script_SetCameraSpeed_Faster, 0x80000, 53, 1, 0)
    Exec(TTYD64_kzn_03_Script_8024365C)
    Return
    End
};

EvtScript TTYD64_kzn_03_Script_802431BC = {
    SetGroup(0)
    Call(SetTexPanner, LVar0, 3)
    Thread
        Set(LVar0, 3)
        Set(LVar1, -200)
        Set(LVar2, 0)
        Set(LVar3, 600)
        Set(LVar4, -400)
        Set(LVar5, 1)
        Set(LVar6, 0)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(kzn_03_EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

EvtScript TTYD64_kzn_03_Script_802432D8 = {
    SetGroup(0)
    Call(SetTexPanner, LVar0, 4)
    Thread
        Set(LVar0, 4)
        Set(LVar1, 500)
        Set(LVar2, 0)
        Set(LVar3, 0)
        Set(LVar4, -400)
        Set(LVar5, 1)
        Set(LVar6, 0)
        Set(LVar7, 0)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(kzn_03_EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

EvtScript TTYD64_kzn_03_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(5)
        Set(LVarA, Ref(kzn_03_EVS_BindTriggers))
        Exec(TTYD64_kzn_03_Script_EnterVerticalPipe)
    CaseDefault
        Set(LVar0, Ref(kzn_03_EVS_BindTriggers))
        Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_kzn_03_Script_8024365C = {
    SetGroup(0)
    Call(EnableTexPanning, 27, 1)
    Call(EnableTexPanning, 26, 1)
    Call(EnableTexPanning, 71, 1)
    Call(EnableTexPanning, 70, 1)
    Thread
        Set(LVar0, 1)
        Set(LVar1, 400)
        Set(LVar2, 0)
        Set(LVar3, 800)
        Set(LVar4, 0)
        Set(LVar5, 1)
        Set(LVar6, 0)
        Set(LVar7, 1)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(kzn_03_EVS_UpdateTexturePan)
    EndThread
    Thread
        Set(LVar0, 5)
        Set(LVar1, 300)
        Set(LVar2, -500)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(kzn_03_EVS_UpdateTexturePan)
    EndThread
    Thread
        Set(LVar0, 0)
        Loop(0)
            Call(SetTexPanOffset, 13, 0, LVar0, 0)
            Add(LVar0, 32768)
            Wait(6)
        EndLoop
    EndThread
    Return
    End
};

EvtScript TTYD64_kzn_03_Script_Main_EnterWalk = {
    Set(GameByte(425), 18)
    Call(SetSpriteShading, 0xA0002)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 1, Ref(kzn_03_DefaultNPCs))
    ExecWait(kzn_03_EVS_MakeEntities)
    Call(GetLoadType, LVar1)
    IfEq(LVar1, 1)
        Exec(EnterSavePoint)
        Exec(kzn_03_EVS_BindTriggers)
    Else
        Exec(TTYD64_kzn_03_Script_EnterMap)
    EndIf
    Wait(1)
    Call(SetMusic, 0, 41, 0, 8)
    Call(PlayAmbientSounds, 4)
    Exec(TTYD64_kzn_03_Script_InitNewStuff)
    Set(LVar0, 67)
    Exec(TTYD64_kzn_03_Script_802431BC)
    Set(LVar0, 68)
    Exec(TTYD64_kzn_03_Script_802432D8)
    ExecWait(kzn_03_EVS_SetupZiplines)
    Return
    End
};

EvtScript TTYD64_kzn_03_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SavePoint), 365, 530, 135, 0, 0x80000000)
    Call(MakeItemEntity, 375, 75, 290, 235, 17, GameFlag(1330))
    Call(MakeEntity, Ref(Entity_BrickBlock), 215, 745, -105, 0, 0x80000000)
    Call(MakeEntity, Ref(Entity_BrickBlock), 85, 770, -105, 0, 0x80000000)
    Call(MakeItemEntity, 144, 85, 795, -105, 13, GameFlag(1331))
    Call(MakeEntity, Ref(Entity_YellowBlock), 35, 730, -105, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1332))
    Call(MakeEntity, Ref(Entity_YellowBlock), -15, 730, -105, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1333))
    Call(MakeEntity, Ref(Entity_YellowBlock), -65, 730, -105, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1334))
    Call(MakeEntity, Ref(Entity_YellowBlock), -115, 730, -105, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1335))
    IfLt(GameByte(0), 29)
        Call(MakeEntity, Ref(Entity_Hammer3Block), 490, 470, 210, 0, 0x80000000)
        Call(AssignScript, Ref(kzn_03_EVS_OnBreakBlock))
        Thread
            Loop(0)
                IfGe(GameByte(0), 29)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            Call(ModifyColliderFlags, 0, 50, 0x7FFFFE00)
        EndThread
    Else
        Call(ModifyColliderFlags, 0, 50, 0x7FFFFE00)
    EndIf
    Call(MakeEntity, Ref(Entity_ScriptSpring), 160, 30, 350, 0, 0x80000000)
    Call(AssignScript, Ref(kzn_03_EVS_UseSpringA))
    Call(MakeEntity, Ref(Entity_ScriptSpring), 335, 265, 360, 0, 0x80000000)
    Call(AssignScript, Ref(kzn_03_EVS_UseSpringB))
    Thread
        Call(kzn_03_IsPlayerOnFirstCliff)
    EndThread
    Call(MakeEntity, Ref(Entity_ScriptSpring), -410, 645, 120, 0, 0x80000000)
    Call(AssignScript, Ref(kzn_03_EVS_UseSpringC))
    Return
    End
};

EvtScript TTYD64_kzn_03_Script_EnterVerticalPipe = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(DisablePartnerAI, 0)
    Call(HidePlayerShadow, 1)
    Call(SetPlayerAnimation, 0x10000)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Call(EnableNpcShadow, -4, 0)
        Call(SetNpcPos, -4, 0, -1000, 0)
    EndIf
    Call(GetEntryID, LVar0)
    Call(TTYD64_Pipe_GetEntryCoords)
    Sub(LVar2, 40)
    Call(SetPlayerPos, LVar1, LVar2, LVar3)
    Call(InterpPlayerYaw, LVar4, 0)
    Call(PlaySound, 355)
    Call(SetPlayerImgFXFlags, 256)
    Call(UpdatePlayerImgFX, 0x10000, 5, 2, 1, 1, 0)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Loop(40)
        Add(LVar1, 1)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Wait(3)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Thread
            Call(DisablePartnerAI, 0)
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Sub(LVar2, 3)
            Call(SetNpcPos, -4, LVar0, LVar1, LVar2)
            Call(SetNpcFlagBits, -4, 2, 0)
            Call(EnablePartnerAI)
            Call(EnableNpcShadow, -4, 1)
        EndThread
    EndIf
    Wait(2)
    Call(UpdatePlayerImgFX, 0x10000, 0, 0, 0, 0, 0)
    Wait(1)
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Call(HidePlayerShadow, 0)
    Label(0)
    Call(TTYD64_Pipe_GetCurrentFloor)
    Wait(1)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Exec(LVarA)
    Return
    End
};

EvtScript TTYD64_kzn_03_Script_ExitVerticalPipe = {
    Call(TTYD64_Pipe_CheckDownInput)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(GetPartnerInUse, LVar0)
    IfNe(LVar0, 0)
        Call(GetCurrentPartnerID, LVar1)
        IfNe(LVar1, 6)
            Return
        Else
            Call(InterruptUsePartner)
            Call(DisablePlayerInput, 1)
        EndIf
    Else
        Call(DisablePlayerInput, 1)
    EndIf
    SetGroup(27)
    Call(TTYD64_Pipe_SetAnimFlag)
    Call(DisablePlayerPhysics, 1)
    Call(HidePlayerShadow, 1)
    Set(LVar0, LVarA)
    Call(TTYD64_Pipe_GetEntryCoords)
    Call(PlayerMoveTo, LVar1, LVar3, 3)
    Set(LVar0, LVarA)
    Call(TTYD64_Pipe_GetEntryCoords)
    Call(SetPlayerPos, LVar1, LVar2, LVar3)
    Call(SetPlayerFlagBits, 0x200000, 1)
    Call(TTYD64_Pipe_GetCameraYaw)
    Call(InterpPlayerYaw, LVar0, 0)
    Wait(2)
    Call(SetPlayerFlagBits, 0x200000, 0)
    Call(PlaySound, 355)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Thread
        Wait(4)
        Loop(40)
            Sub(LVar1, 1)
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Call(SetPlayerImgFXFlags, 2048)
    Call(UpdatePlayerImgFX, 0x10002, 5, 2, 1, 1, 0)
    Wait(25)
    ExecWait(LVarC)
    Return
    End
};

EvtScript TTYD64_kzn_03_Script_802435C0 = {
    BindTrigger(kzn_03_EVS_ExitWalk_kzn_02_1, 0x80000, 31, 1, 0)
    BindTrigger(kzn_03_EVS_ExitWalk_kzn_04_0, 0x80000, 34, 1, 0)
    BindTrigger(kzn_03_EVS_ExitWalk_kzn_09_0, 0x80000, 38, 1, 0)
    BindTrigger(kzn_03_EVS_ExitWalk_kzn_05_1, 0x80000, 40, 1, 0)
    BindTrigger(kzn_03_EVS_ExitWalk_kzn_09_2, 0x80000, 43, 1, 0)
    BindTrigger(TTYD64_kzn_03_Script_Exit5, 128, 55, 1, 0)
    Return
    End
};

EntryList TTYD64_kzn_03_EntryList = {
    { -410.0f, 870.0f, -65.0f, 90.0f },
    { 435.0f, 670.0f, -10.0f, 270.0f },
    { 450.0f, 470.0f, 220.0f, 270.0f },
    { -425.0f, 60.0f, 325.0f, 90.0f },
    { 440.0f, 20.0f, 280.0f, 270.0f },
    { -663.0f, 92.0f, 209.0f, -270.0f },
};

EvtScript TTYD64_kzn_03_Script_Exit5 = {
    SetGroup(27)
    Set(LVarA, 5)
    Set(LVarB, 55)
    Set(LVarC, Ref(TTYD64_kzn_03_Script_GotoMap_Exit5))
    ExecWait(TTYD64_kzn_03_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_kzn_03_Script_GotoMap_Exit5 = {
    Call(GotoMap, (Bytecode) "tyd_05", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_kzn_03_Script_SetCameraSpeed_Normal = {
    Call(SetCamSpeed, 0, Float(1.0))
    Return
    End
};

EvtScript TTYD64_kzn_03_Script_SetCameraSpeed_Faster = {
    Call(SetCamSpeed, 0, Float(7.0))
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_kzn_03(void) {
    kzn_03_settings.entryList = &TTYD64_kzn_03_EntryList;
    kzn_03_settings.entryCount = 6;
    Mod_ReplaceScript("TTYD64", &kzn_03_EVS_Main, &TTYD64_kzn_03_Script_Main_EnterWalk);
    Mod_ReplaceScript("TTYD64", &kzn_03_EVS_MakeEntities, &TTYD64_kzn_03_Script_MakeEntities);
    Mod_ReplaceScript("TTYD64", &kzn_03_EVS_BindTriggers, &TTYD64_kzn_03_Script_802435C0);
}
