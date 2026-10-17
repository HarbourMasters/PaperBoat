#include "common.h"
#include "effects.h"
#include "entity.h"
#include "map.h"
#include "npc.h"
#include "script_api/map.h"
#include <stdio.h>
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/newmaps/nm.h"

API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(GetColliderCenter);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GetPartnerInUse);
API_CALLABLE(GetPlayerActionState);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlaySound);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetTexPanner);
API_CALLABLE(ShowGotItem);
API_CALLABLE(TeleportPartnerToPlayer);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_isk_21_Script_MarioDrowned;
extern EvtScript TTYD64_isk_21_Script_HandleSinkPlayer;
extern EvtScript TTYD64_isk_21_Script_SetupTexturePan;
extern EvtScript TTYD64_isk_21_Script_InitStuff;
extern EvtScript TTYD64_isk_21_Script_Main;
extern EvtScript TTYD64_isk_21_Script_TexturePan_Update;
extern EvtScript TTYD64_isk_21_Script_GetItem;
extern EvtScript TTYD64_isk_21_Script_SinkPlayer_Sand1;
extern EvtScript TTYD64_isk_21_Script_SinkPlayer_Sand2;
extern u8 TTYD64_isk_21_String_Tattle[];
extern EvtScript TTYD64_isk_21_Script_DrownMario;
extern EvtScript TTYD64_isk_21_Script_Exit0;
extern MapSettings TTYD64_isk_21_Header;
extern EvtScript TTYD64_isk_21_Script_SetupMusic;
extern EvtScript TTYD64_isk_21_Script_CreateExitTriggers;
extern EvtScript TTYD64_isk_21_Script_UpdateRespawnPoint_6;
extern EvtScript TTYD64_isk_21_Script_UpdateRespawnPoint_1;
extern EvtScript TTYD64_isk_21_Script_UpdateRespawnPoint_5;
extern EvtScript TTYD64_isk_21_Script_UpdateRespawnPoint_4;
extern EvtScript TTYD64_isk_21_Script_UpdateRespawnPoint_3;
extern EvtScript TTYD64_isk_21_Script_UpdateRespawnPoint_2;
extern EntryList TTYD64_isk_21_EntryList;

// clang-format off
static s32 TTYD64_isk_21_GetTattleMsg;

static s32 TTYD64_isk_21_GetTattle(void) {
    return TTYD64_isk_21_GetTattleMsg;
}

EvtScript TTYD64_isk_21_Script_MarioDrowned = {
    Call(PlaySound, 8419)
    IfEq(LVarA, 8)
        Call(TTYD64_SetPartnerAbilityState, PARTNER_LAKILESTER, 3)
    Else
        Call(DisablePlayerInput, 1)
        Loop(0)
            Call(GetPlayerActionState, LVar0)
            IfEq(LVar0, 0)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Call(DisablePlayerPhysics, 1)
        Thread
            Loop(5)
                Call(GetPlayerPos, LVar0, LVar1, LVar2)
                Sub(LVar1, 1)
                Call(SetPlayerPos, LVar0, LVar1, LVar2)
                Wait(1)
            EndLoop
        EndThread
        Call(SetPlayerAnimation, 0x10002)
        Call(SetPlayerAnimation, 0x1001B)
    EndIf
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(255.0))
    ExecWait(TTYD64_Script_FadeScreenOut)
    IfNe(LVarA, 8)
        Call(DisablePlayerPhysics, 0)
    EndIf
    Switch(MapVar(0))
    CaseEq(0)
        Call(SetPlayerPos, -764, 0, -3)
    CaseEq(1)
        Call(SetPlayerPos, -598, 0, -14)
    CaseEq(2)
        Call(SetPlayerPos, -459, 0, -14)
    CaseEq(3)
        Call(SetPlayerPos, -319, 0, 31)
    CaseEq(4)
        Call(SetPlayerPos, -279, 0, -75)
    CaseEq(5)
        Call(SetPlayerPos, 116, 0, 43)
    EndSwitch
    Switch(LVarA)
    CaseOrEq(9)
    CaseOrEq(6)
        Call(TTYD64_SetPlayerAnimFlagBits, PA_FLAG_INTERRUPT_USE_PARTNER, 1)
        EndCaseGroup
    EndSwitch
    Call(TeleportPartnerToPlayer)
    Call(InterpPlayerYaw, 90, 0)
    Wait(5)
    IfNe(LVarA, 8)
        Call(SetPlayerAnimation, 0x10002)
        Call(SetPlayerAnimation, 0x1000F)
    EndIf
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(5.0))
    Exec(TTYD64_Script_FadeScreenIn)
    Wait(10)
    IfEq(LVarA, 8)
        Return
    Else
        Call(SetPlayerAnimation, 0x10030)
        Wait(15)
        Call(SetPlayerAnimation, 0x10031)
        Thread
            Call(PlaySound, 370)
            Wait(12)
            Call(PlaySound, 370)
        EndThread
        Wait(25)
        Call(SetPlayerAnimation, 0x10002)
        Call(DisablePlayerInput, 0)
    EndIf
    Return
    End
};

EvtScript TTYD64_isk_21_Script_HandleSinkPlayer = {
    SetGroup(2)
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Set(LVarC, LVar2)
    Set(LVarD, LVar3)
    Set(LVarE, LVar4)
    Set(LVarF, LVar5)
    Set(LVar8, 5)
    Loop(0)
        Call(TTYD64_ReadField, TTYD64_F_GCOLLISIONSTATUS_2_2U, LVar0)
        IfEq(LVar0, LVarD)
            Call(GetPartnerInUse, LVar0)
            IfNe(LVar0, 8)
                Call(TTYD64_TestPlayerFlags, PS_FLAG_INPUT_DISABLED, LVar0)
                IfNe(LVar0, 1)
                    IfEq(LVar8, 0)
                        Set(LVar8, 5)
                        Call(GetColliderCenter, LVarE)
                        Set(LVar3, LVar1)
                        Call(GetModelCenter, LVarA)
                        IfLe(LVar1, LVar3)
                            ExecWait(TTYD64_isk_21_Script_MarioDrowned)
                            Call(TranslateModel, LVarA, 0, LVarB, 0)
                        Else
                            Set(LVar4, LVarB)
                            Sub(LVar1, LVar4)
                            Sub(LVar1, 1)
                            Call(TranslateModel, LVarA, 0, LVar1, 0)
                        EndIf
                        Call(UpdateColliderTransform, LVarC)
                        Call(UpdateColliderTransform, LVarD)
                        IfNe(LVarF, 0)
                            Call(UpdateColliderTransform, LVarF)
                        EndIf
                    EndIf
                    Sub(LVar8, 1)
                    IfEq(LVarF, 0)
                        Call(GetPlayerPos, LVar0, LVar1, LVar2)
                        Add(LVar0, 1)
                        Call(SetPlayerPos, LVar0, LVar1, LVar2)
                    EndIf
                EndIf
            EndIf
        Else
            Call(TTYD64_TestPlayerFlags, PS_FLAG_INPUT_DISABLED, LVar0)
            IfNe(LVar0, 1)
                Call(GetModelCenter, LVarA)
                IfLt(LVar1, LVarB)
                    Set(LVar3, LVarB)
                    Sub(LVar1, LVar3)
                    Set(LVar3, LVar1)
                    Add(LVar3, 2)
                    Call(GetModelCenter, LVarA)
                    IfGt(LVar1, LVarB)
                        Set(LVar3, 0)
                    EndIf
                    Call(TranslateModel, LVarA, 0, LVar3, 0)
                    Call(UpdateColliderTransform, LVarC)
                    Call(UpdateColliderTransform, LVarD)
                    IfNe(LVarF, 0)
                        Call(UpdateColliderTransform, LVarF)
                    EndIf
                EndIf
            EndIf
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_isk_21_Script_SetupTexturePan = {
    Call(SetTexPanner, 3, 0)
    Call(SetTexPanner, 5, 1)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 344)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 0)
        Set(LVar6, 0)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_isk_21_Script_TexturePan_Update)
    EndThread
    Thread
        Set(LVar0, 1)
        Set(LVar1, 0)
        Set(LVar2, -495)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 0)
        Set(LVar6, 0)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_isk_21_Script_TexturePan_Update)
    EndThread
    Return
    End
};

EvtScript TTYD64_isk_21_Script_InitStuff = {
    Call(ParentColliderToModel, 15, 38)
    Call(ParentColliderToModel, 14, 38)
    Call(ParentColliderToModel, 19, 39)
    Call(ParentColliderToModel, 18, 39)
    Call(ParentColliderToModel, 21, 39)
    Exec(TTYD64_isk_21_Script_SinkPlayer_Sand1)
    Exec(TTYD64_isk_21_Script_SinkPlayer_Sand2)
    BindTrigger(TTYD64_isk_21_Script_UpdateRespawnPoint_1, 128, 24, 1, 0)
    BindTrigger(TTYD64_isk_21_Script_UpdateRespawnPoint_2, 128, 25, 1, 0)
    BindTrigger(TTYD64_isk_21_Script_UpdateRespawnPoint_3, 128, 26, 1, 0)
    BindTrigger(TTYD64_isk_21_Script_UpdateRespawnPoint_4, 128, 27, 1, 0)
    BindTrigger(TTYD64_isk_21_Script_UpdateRespawnPoint_5, 128, 28, 1, 0)
    BindTrigger(TTYD64_isk_21_Script_UpdateRespawnPoint_6, 128, 29, 1, 0)
    BindTrigger(TTYD64_isk_21_Script_DrownMario, 128, 20, 1, 0)
    BindTrigger(TTYD64_isk_21_Script_DrownMario, 128, 21, 1, 0)
    IfEq(GameFlag(5005), 0)
        BindTrigger(TTYD64_isk_21_Script_GetItem, 256, 7, 1, 0)
    EndIf
    Return
    End
};

EvtScript TTYD64_isk_21_Script_Main = {
    Set(GameByte(425), 11)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_isk_21_Script_SetupMusic)
    Exec(TTYD64_isk_21_Script_SetupTexturePan)
    Call(MakeItemEntity, 395, 153, 32, -19, 17, GameFlag(5005))
    Set(MapVar(1), LVar0)
    Exec(TTYD64_isk_21_Script_InitStuff)
    Set(LVar0, (Bytecode) TTYD64_isk_21_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

EvtScript TTYD64_isk_21_Script_TexturePan_Update = {
    SetGroup(0)
    IfEq(LVar5, 1)
        IfEq(LVar6, 1)
            IfEq(LVar7, 1)
                IfEq(LVar8, 1)
                    Call(TTYD64_TexturePan_Simple)
                    Return
                EndIf
            EndIf
        EndIf
    EndIf
    Call(TTYD64_TexturePan_Complex)
    Return
    End
};

EvtScript TTYD64_isk_21_Script_GetItem = {
    Call(DisablePlayerInput, 1)
    Call(TTYD64_nm_AddBadge, 395, 0)
    Call(RemoveItemEntity, MapVar(1))
    Call(ShowGotItem, 395, 1, 0)
    Set(GameFlag(5005), 1)
    Unbind
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_isk_21_Script_SinkPlayer_Sand1 = {
    Set(LVar0, 38)
    Set(LVar1, -3)
    Set(LVar2, 15)
    Set(LVar3, 14)
    Set(LVar4, 16)
    Set(LVar5, 0)
    Exec(TTYD64_isk_21_Script_HandleSinkPlayer)
    Return
    End
};

EvtScript TTYD64_isk_21_Script_SinkPlayer_Sand2 = {
    Set(LVar0, 39)
    Set(LVar1, -4)
    Set(LVar2, 19)
    Set(LVar3, 18)
    Set(LVar4, 20)
    Set(LVar5, 21)
    Exec(TTYD64_isk_21_Script_HandleSinkPlayer)
    Return
    End
};

u8 TTYD64_isk_21_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x34, 0x48, 0x49, 0x53, 0xF7, 0x52, 0x4F, 0x4F,
    0x4D, 0xF7, 0x49, 0x53, 0xF7, 0x46, 0x55, 0x4C, 0x4C, 0xF7, 0x4F, 0x46,
    0xF7, 0x51, 0x55, 0x49, 0x43, 0x4B, 0x53, 0x41, 0x4E, 0x44, 0x53, 0x0C,
    0xF0, 0x52, 0x45, 0x4D, 0x45, 0x4D, 0x42, 0x45, 0x52, 0xF7, 0x54, 0x4F,
    0xF7, 0x41, 0x56, 0x4F, 0x49, 0x44, 0xF7, 0x53, 0x54, 0x41, 0x59, 0x49,
    0x4E, 0x47, 0xF7, 0x53, 0x54, 0x49, 0x4C, 0x4C, 0xF0, 0x49, 0x46, 0xF7,
    0x59, 0x4F, 0x55, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x57, 0x41,
    0x4E, 0x54, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0x54, 0x48, 0x49, 0x4E, 0x47,
    0xF7, 0x42, 0x41, 0x44, 0xF0, 0x54, 0x4F, 0xF7, 0x48, 0x41, 0x50, 0x50,
    0x45, 0x4E, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_isk_21_Script_DrownMario = {
    ExecWait(TTYD64_isk_21_Script_MarioDrowned)
    Call(TranslateModel, 39, 0, -4, 0)
    Call(UpdateColliderTransform, 19)
    Call(UpdateColliderTransform, 18)
    Call(UpdateColliderTransform, 21)
    Return
    End
};

EvtScript TTYD64_isk_21_Script_Exit0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "isk_07", 2)
    Wait(100)
    Return
    End
};

MapSettings TTYD64_isk_21_Header = {
    .main = &TTYD64_isk_21_Script_Main,
    .entryList = &TTYD64_isk_21_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_isk_21_GetTattle },
};

EvtScript TTYD64_isk_21_Script_SetupMusic = {
    Call(SetMusic, 0, 24, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_isk_21_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_isk_21_Script_Exit0, 0x80000, 13, 1, 0)
    Return
    End
};

EvtScript TTYD64_isk_21_Script_UpdateRespawnPoint_6 = {
    Set(MapVar(0), 5)
    Return
    End
};

EvtScript TTYD64_isk_21_Script_UpdateRespawnPoint_1 = {
    Set(MapVar(0), 0)
    Return
    End
};

EvtScript TTYD64_isk_21_Script_UpdateRespawnPoint_5 = {
    Set(MapVar(0), 4)
    Return
    End
};

EvtScript TTYD64_isk_21_Script_UpdateRespawnPoint_4 = {
    Set(MapVar(0), 3)
    Return
    End
};

EvtScript TTYD64_isk_21_Script_UpdateRespawnPoint_3 = {
    Set(MapVar(0), 2)
    Return
    End
};

EvtScript TTYD64_isk_21_Script_UpdateRespawnPoint_2 = {
    Set(MapVar(0), 1)
    Return
    End
};

EntryList TTYD64_isk_21_EntryList = {
    { -835.0f, 0.0f, 55.0f, 0.0f },
};

MapConfig TTYD64_mapcfg_isk_21 = {
    .id = "isk_21",
    .settings = &TTYD64_isk_21_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_isk_21(void) {
    TTYD64_isk_21_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_isk_21_String_Tattle);
}
