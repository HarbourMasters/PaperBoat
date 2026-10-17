#include "common.h"
#include "effects.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_flags.h"
#include "../include/ttyd64_rawmem.h"
#include "../include/ttyd64_symbols.h"
#include "world_lib.h"
#include "world_lib_gen.h"

// clang-format off
EvtScript TTYD64_Script_TexturePanning = {
    SetGroup(0)
    IfEq(LVar5, 1)
        IfEq(LVar6, 1)
            IfEq(LVar7, 1)
                IfEq(LVar8, 1)
                    Call(TTYD64_Func_AnimateTexture_DelayAll)
                    Return
                EndIf
            EndIf
        EndIf
    EndIf
    Call(TTYD64_Function_AnimateTexture)
    Return
    End
};

EvtScript TTYD64_Script_AdvancedUpdateModelAlpha = {
    Set(LVar6, LVar0)
    Set(LVar7, LVar1)
    Set(LVar8, LVar2)
    Set(LVar9, LVar3)
    Call(SetModelCustomGfx, LVar6, 1, -1)
    Call(SetCustomGfxBuilders, 1, Ref(TTYD64_Function_InitDisplayListCode), 0)
    Call(MakeLerp, LVar8, LVar9, LVar7, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(TTYD64_SetFadeModelAlpha, LVar0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript TTYD64_RestoreInputs = {
    Call(TTYD64_WriteField, TTYD64_F_GMESSAGEPRINTERS_4F8_1U, 3)
    Call(TTYD64_TestPlayerFlags, PS_FLAG_NO_STATIC_COLLISION, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_WriteField, TTYD64_F_GPLAYERSTATUS_14_1U, 1)
        Call(DisablePlayerPhysics, 0)
    EndIf
    Call(TTYD64_TestPlayerFlags, PS_FLAG_INPUT_DISABLED, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_WriteField, TTYD64_F_GPLAYERSTATUS_15_1U, 1)
        Call(DisablePlayerInput, 0)
    EndIf
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Call(EnablePartnerAI)
    EndIf
    Return
    End
};

EvtScript TTYD64_SetPlayerAnimation = {
    Call(SetPlayerAnimation, 65536)
    Call(SetPlayerAnimation, LVar0)
    Switch(LVar1)
        CaseEq(1)
            Call(PlaySoundAtPlayer, 610, 0)
            Call(ShowEmote, 0, 0, -45, 20, 0, 0, 0, 0, 0)
        CaseGe(2)
            Call(PlaySoundAtPlayer, 611, 0)
            Call(ShowEmote, 0, 2, -45, 20, 0, 0, 0, 0, 0)
    EndSwitch
    Loop(LVar2)
        Wait(1)
    EndLoop
    Call(SetPlayerAnimation, 65536)
    Return
    End
};

EvtScript TTYD64_PlayerStopUsingPartner = {
    Call(TTYD64_TestPlayerAnimFlags, PA_FLAG_USING_WATT, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_SetPlayerAnimFlagBits, PA_FLAG_INTERRUPT_USE_PARTNER, 1)
    EndIf
    Call(TTYD64_GetPartnerAbilityState, PARTNER_LAKILESTER, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_SetPlayerAnimFlagBits, PA_FLAG_INTERRUPT_USE_PARTNER, 1)
        Wait(20)
    EndIf
    Return
    End
};

EvtScript TTYD64_Script_UpdateModelAlpha = {
    Set(LVar6, LVar0)
    Set(LVar7, LVar1)
    Set(LVar8, LVar2)
    Call(SetModelCustomGfx, LVar6, 1, -1)
    Call(SetCustomGfxBuilders, 1, Ref(TTYD64_Function_InitDisplayListCode), 0)
    IfEq(LVar7, 0)
        Set(LVar0, 255)
        Set(LVar1, 0)
    Else
        Set(LVar0, 0)
        Set(LVar1, 255)
    EndIf
    Call(MakeLerp, LVar0, LVar1, LVar8, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(TTYD64_SetFadeModelAlpha, LVar0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript TTYD64_IsBadgeEquipped_Script = {
    Set(LVar1, 0x8010F498)
    Loop(0)
        Call(TTYD64_WorldLib_ReadEquippedBadgeAt, LVar1, LVar2)
        IfEq(LVar0, LVar2)
            Set(LVar0, 1)
            BreakLoop
        EndIf
        Add(LVar1, 2)
        IfGe(LVar1, 0x8010F510)
            Set(LVar0, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript TTYD64_InterpNpcYaw = {
    Call(MakeLerp, 0, LVar3, LVar4, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(InterpNpcYaw, LVar2, LVar0, 1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_SetPartnerAnimation = {
    Call(GetCurrentPartnerID, LVar2)
    Switch(LVar2)
        CaseEq(1)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetNpcAnimation, -4, 65537)
                CaseEq(1)
                    Call(SetNpcAnimation, -4, 65538)
                CaseEq(2)
                    Call(SetNpcAnimation, -4, 65539)
                CaseEq(3)
                    Call(SetNpcAnimation, -4, 65544)
                CaseEq(4)
                    Call(SetNpcAnimation, -4, 65543)
                CaseEq(5)
                    Call(SetNpcAnimation, -4, 65545)
            EndSwitch
        CaseEq(2)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetNpcAnimation, -4, 131075)
                CaseEq(1)
                    Call(SetNpcAnimation, -4, 131076)
                CaseEq(2)
                    Call(SetNpcAnimation, -4, 131077)
                CaseEq(3)
                    Call(SetNpcAnimation, -4, 131085)
                CaseEq(4)
                    Call(SetNpcAnimation, -4, 131084)
                CaseEq(5)
                    Call(SetNpcAnimation, -4, 131089)
            EndSwitch
        CaseEq(3)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetNpcAnimation, -4, 196611)
                CaseEq(1)
                    Call(SetNpcAnimation, -4, 196613)
                CaseEq(2)
                    Call(SetNpcAnimation, -4, 196615)
                CaseEq(3)
                    Call(SetNpcAnimation, -4, 196622)
                CaseEq(4)
                    Call(SetNpcAnimation, -4, 196621)
                CaseEq(5)
                    Call(SetNpcAnimation, -4, 196623)
            EndSwitch
        CaseEq(4)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetNpcAnimation, -4, 262145)
                CaseEq(1)
                    Call(SetNpcAnimation, -4, 262146)
                CaseEq(2)
                    Call(SetNpcAnimation, -4, 262147)
                CaseEq(3)
                    Call(SetNpcAnimation, -4, 262150)
                CaseEq(4)
                    Call(SetNpcAnimation, -4, 262149)
                CaseEq(5)
                    Call(SetNpcAnimation, -4, 262151)
            EndSwitch
        CaseEq(9)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetNpcAnimation, -4, 327681)
                CaseEq(1)
                    Call(SetNpcAnimation, -4, 327682)
                CaseEq(2)
                    Call(SetNpcAnimation, -4, 327683)
                CaseEq(3)
                    Call(SetNpcAnimation, -4, 327684)
                CaseEq(4)
                    Call(SetNpcAnimation, -4, 327692)
                CaseEq(5)
                    Call(SetNpcAnimation, -4, 327690)
            EndSwitch
        CaseEq(6)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetNpcAnimation, -4, 393217)
                CaseEq(1)
                    Call(SetNpcAnimation, -4, 393218)
                CaseEq(2)
                    Call(SetNpcAnimation, -4, 393219)
                CaseEq(3)
                    Call(SetNpcAnimation, -4, 393220)
                CaseEq(4)
                    Call(SetNpcAnimation, -4, 393223)
                CaseEq(5)
                    Call(SetNpcAnimation, -4, 393222)
            EndSwitch
        CaseEq(7)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetNpcAnimation, -4, 458753)
                CaseEq(1)
                    Call(SetNpcAnimation, -4, 458754)
                CaseEq(2)
                    Call(SetNpcAnimation, -4, 458755)
                CaseEq(3)
                    Call(SetNpcAnimation, -4, 458756)
                CaseEq(4)
                    Call(SetNpcAnimation, -4, 458759)
                CaseEq(5)
                    Call(SetNpcAnimation, -4, 458758)
            EndSwitch
        CaseEq(8)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetNpcAnimation, -4, 524289)
                CaseEq(1)
                    Call(SetNpcAnimation, -4, 524293)
                CaseEq(2)
                    Call(SetNpcAnimation, -4, 524295)
                CaseEq(3)
                    Call(SetNpcAnimation, -4, 524297)
                CaseEq(4)
                    Call(SetNpcAnimation, -4, 524292)
                CaseEq(5)
                    Call(SetNpcAnimation, -4, 524301)
            EndSwitch
    EndSwitch
    IfNe(LVar2, 0)
        Switch(LVar1)
            CaseEq(1)
                Call(PlaySoundAtNpc, -4, 610, 0)
                Call(ShowEmote, -4, 0, -45, 20, 1, 0, 0, 0, 0)
            CaseGe(2)
                Call(PlaySoundAtNpc, -4, 611, 0)
                Call(ShowEmote, -4, 2, -45, 20, 1, 0, 0, 0, 0)
        EndSwitch
    EndIf
    Return
    End
};

EvtScript TTYD64_SpeakPartnerToPlayer = {
    Call(GetCurrentPartnerID, LVar2)
    Switch(LVar2)
        CaseEq(1)
            Call(SpeakToPlayer, -4, 65544, 65537, LVar1, LVar0)
        CaseEq(2)
            Call(SpeakToPlayer, -4, 131085, 131075, LVar1, LVar0)
        CaseEq(3)
            Call(SpeakToPlayer, -4, 196622, 196611, LVar1, LVar0)
        CaseEq(4)
            Call(SpeakToPlayer, -4, 262150, 262145, LVar1, LVar0)
        CaseEq(9)
            Call(SpeakToPlayer, -4, 327684, 327681, LVar1, LVar0)
        CaseEq(6)
            Call(SpeakToPlayer, -4, 393220, 393217, LVar1, LVar0)
        CaseEq(7)
            Call(SpeakToPlayer, -4, 458756, 458753, LVar1, LVar0)
        CaseEq(8)
            Call(SpeakToPlayer, -4, 524297, 524289, LVar1, LVar0)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_Script_FadeScreenIn = {
    Loop(0)
        Call(TTYD64_GetScreenOverlayFrontProgress, LVar2)
        SubF(LVar2, LVar0)
        IfLe(LVar2, LVar1)
            SetF(LVar2, LVar1)
            Call(TTYD64_SetScreenOverlayFront, 1, LVar2)
            BreakLoop
        EndIf
        Call(TTYD64_SetScreenOverlayFront, 0, LVar2)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_MovePartnerInFrontOfMario = {
    Call(GetCurrentPartnerID, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(DisablePartnerAI, 0)
    Set(LVar0, 1)
    Set(LVar1, 0)
    ExecWait(TTYD64_SetPartnerAnimation)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(TTYD64_ReadField, TTYD64_F_GPLAYERSTATUS_A8_4U, LVar7)
    IfEq(LVar7, 0)
        Add(LVar0, -35)
    Else
        Add(LVar0, 35)
    EndIf
    Add(LVar1, 10)
    Call(PartnerIsFlying, LVar3)
    IfEq(LVar3, 0)
        Call(NpcFlyTo, -4, LVar0, LVar1, LVar2, 15, 0, 0)
    Else
        Call(NpcMoveTo, -4, LVar0, LVar2, 15)
    EndIf
    Set(LVar0, 0)
    Set(LVar1, 0)
    ExecWait(TTYD64_SetPartnerAnimation)
    IfEq(LVar7, 0)
        Call(InterpNpcYaw, -4, 90, 0)
    Else
        Call(InterpNpcYaw, -4, -90, 0)
    EndIf
    Wait(10)
    Call(EnablePartnerAI)
    Return
    End
};

EvtScript TTYD64_DoNpcDefeat = {
    Call(SetNpcAnimation, LVar0, LVar1)
    Wait(20)
    Thread
        Loop(5)
            Call(SetNpcFlagBits, LVar0, 16777216, 1)
            Wait(1)
            Call(SetNpcFlagBits, LVar0, 16777216, 0)
            Wait(1)
        EndLoop
        Call(SetNpcFlagBits, LVar0, 16777216, 1)
        Call(EnableNpcShadow, LVar0, 0)
    EndThread
    Wait(3)
    Call(PlaySoundAtNpc, LVar0, 997, 0)
    Call(GetNpcPos, LVar0, LVar2, LVar3, LVar4)
    Call(PlayEffect_impl, 1, LVar2, LVar3, LVar4, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(PlayEffect_impl, 24, 1, LVar2, LVar3, LVar4, 0, -100, 10, 8, 0, 0, 0, 0, 0)
    Return
    End
};

EvtScript TTYD64_MovePartnerBehindMario = {
    Call(GetCurrentPartnerID, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(DisablePartnerAI, 0)
    Set(LVar0, 1)
    Set(LVar1, 0)
    ExecWait(TTYD64_SetPartnerAnimation)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(TTYD64_ReadField, TTYD64_F_GPLAYERSTATUS_A8_4U, LVar7)
    IfEq(LVar7, 0)
        Add(LVar0, 35)
    Else
        Add(LVar0, -35)
    EndIf
    Add(LVar1, 10)
    Call(PartnerIsFlying, LVar3)
    IfEq(LVar3, 0)
        Call(NpcFlyTo, -4, LVar0, LVar1, LVar2, 15, 0, 0)
    Else
        Call(NpcMoveTo, -4, LVar0, LVar2, 15)
    EndIf
    Set(LVar0, 0)
    Set(LVar1, 0)
    ExecWait(TTYD64_SetPartnerAnimation)
    IfEq(LVar7, 0)
        Call(InterpNpcYaw, -4, -90, 0)
    Else
        Call(InterpNpcYaw, -4, 90, 0)
    EndIf
    Wait(10)
    Call(EnablePartnerAI)
    Return
    End
};

EvtScript TTYD64_Script_FadeScreenOut = {
    Loop(0)
        Call(TTYD64_GetScreenOverlayFrontProgress, LVar2)
        AddF(LVar2, LVar0)
        IfGe(LVar2, LVar1)
            SetF(LVar2, LVar1)
            Call(TTYD64_SetScreenOverlayFront, 1, LVar2)
            BreakLoop
        EndIf
        Call(TTYD64_SetScreenOverlayFront, 0, LVar2)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_Script_ShakeActor = {
    Set(LFlag0, 0)
    Set(LVarA, 0)
    Set(LVarB, 0)
    Label(0)
    IfEq(LFlag0, 0)
        Call(RandInt, LVar1, LVarA)
        Call(RandInt, LVar1, LVarB)
        Set(LFlag0, 1)
    Else
        Mul(LVarA, -1)
        Mul(LVarB, -1)
        Set(LFlag0, 0)
    EndIf
    Call(SetActorDispOffset, LVar0, LVarA, LVarB, 0)
    Wait(LVar2)
    Goto(0)
    Return
    End
};

EvtScript TTYD64_Script_Interact_NPC_Settings = {
    Call(SpeakToPlayer, -1, 9176068, 9176065, 0, Ref(TTYD64_String_Settings_Start))
    Call(ShowChoice, Ref(TTYD64_String_Choice_Settings_Start))
    Set(LVar1, LVar0)
    Call(CloseMessage)
    Switch(LVar1)
        CaseEq(0)
            Switch(GameByte(4105))
                CaseEq(0)
                    Set(LVar0, Ref(TTYD64_String_Easy))
                CaseEq(1)
                    Set(LVar0, Ref(TTYD64_String_Normal))
                CaseEq(2)
                    Set(LVar0, Ref(TTYD64_String_Hard))
                CaseEq(3)
                    Set(LVar0, Ref(TTYD64_String_VeryHard))
            EndSwitch
            Call(SetMessageText, LVar0, 0)
            Call(SpeakToPlayer, -1, 9176068, 9176065, 0, Ref(TTYD64_String_Settings_Difficulty))
            Call(ShowChoice, Ref(TTYD64_String_Choice_Settings_Difficulty))
            IfNe(LVar0, 4)
                Set(GameByte(4105), LVar0)
            EndIf
            Call(CloseMessage)
            Jump(TTYD64_Script_Interact_NPC_Settings)
            Return
        CaseEq(1)
            Switch(GameByte(4104))
                CaseEq(0)
                    Set(LVar0, Ref(TTYD64_String_TTYD64))
                CaseEq(1)
                    Set(LVar0, Ref(TTYD64_String_Original))
            EndSwitch
            Call(SetMessageText, LVar0, 0)
            Call(SpeakToPlayer, -1, 9176068, 9176065, 0, Ref(TTYD64_String_Settings_Music))
            Call(ShowChoice, Ref(TTYD64_String_Choice_Settings_YesNo))
            IfNe(LVar0, 2)
                IfEq(LVar0, 1)
                    Set(LVar0, 0)
                Else
                    Set(LVar0, 1)
                EndIf
                Set(GameByte(4104), LVar0)
            EndIf
            Call(CloseMessage)
            Jump(TTYD64_Script_Interact_NPC_Settings)
            Return
        CaseEq(2)
            Call(SpeakToPlayer, -1, 9176068, 9176065, 0, Ref(TTYD64_String_Settings_FFWD))
            Call(ShowChoice, Ref(TTYD64_String_Choice_Settings_YesNo))
            IfNe(LVar0, 2)
                IfEq(LVar0, 1)
                    Set(LVar0, 0)
                Else
                    Set(LVar0, 1)
                EndIf
                Set(GameFlag(4105), LVar0)
            EndIf
            Call(CloseMessage)
            Jump(TTYD64_Script_Interact_NPC_Settings)
            Return
    EndSwitch
    Return
    End
};

EvtScript TTYD64_Script_UpgradeAnimation_Sparkles = {
    Wait(10)
    Call(PlaySound, 8493)
    Wait(40)
    Call(PlaySound, 8494)
    Wait(10)
    Thread
        Wait(10)
        Call(TTYD64_Function_ChangeScreenColorOverlay, 70, 70)
        Wait(30)
        Call(PlaySound, 8334)
        Call(TTYD64_Function_ChangeScreenColorOverlay, 50, 50)
    EndThread
    Thread
        Wait(3)
    EndThread
    Thread
        Wait(57)
        Call(TTYD64_Function_PlayFX_33_RadialFlowOut)
        Call(TTYD64_Function_PlayFX_11_Sparkles_Random)
        Wait(5)
        Call(TTYD64_Function_PlayFX_11_Sparkles_Type4)
        Wait(5)
        Call(TTYD64_Function_PlayFX_11_Sparkles_Random)
    EndThread
    Wait(3)
    Wait(30)
    Return
    End
};

EvtScript TTYD64_Script_Eldstar_UpgradeAnimation = {
    Call(SetNpcAnimation, -1, 1179651)
    Wait(20)
    Call(PlaySoundAtPlayer, 313, 0)
    Call(SetPlayerAnimation, 65567)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Set(LVar3, LVar1)
    Add(LVar0, 5)
    Add(LVar1, 50)
    Add(LVar2, 10)
    Add(LVar3, 30)
    Loop(6)
        Call(PlayEffect_impl, 17, 3, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(6)
        Call(PlayEffect_impl, 17, 1, LVar0, LVar3, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(6)
    EndLoop
    Wait(20)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(PlaySoundAtPlayer, 392, 0)
    Call(PlayEffect_impl, 82, 4, LVar0, LVar1, LVar2, 1, 30, 0, 0, 0, 0, 0, 0, 0)
    Wait(40)
    Call(SetPlayerAnimation, 65538)
    Call(SetNpcAnimation, -1, 1179649)
    Return
    End
};

EvtScript TTYD64_Script_Init_NPC_Settings = {
    Call(BindNpcInteract, -1, Ref(TTYD64_Script_Interact_NPC_Settings))
    Return
    End
};

EvtScript TTYD64_Script_Interact_NPC_NGPlus = {
    Call(SpeakToPlayer, -1, 1179656, 1179649, 0, Ref(TTYD64_String_NGPlus_Hi))
    Call(ShowChoice, 1966093)
    IfNe(LVar0, 0)
        Call(CloseMessage)
        Call(SpeakToPlayer, -1, 1179656, 1179649, 0, Ref(TTYD64_String_NGPlus_Cancel))
        Return
    EndIf
    Call(CloseMessage)
    Call(SpeakToPlayer, -1, 1179656, 1179649, 0, Ref(TTYD64_String_NGPlus_AskConfirm))
    Call(ShowChoice, 1966093)
    IfNe(LVar0, 0)
        Call(CloseMessage)
        Call(SpeakToPlayer, -1, 1179656, 1179649, 0, Ref(TTYD64_String_NGPlus_Cancel))
        Return
    EndIf
    Call(CloseMessage)
    Call(SpeakToPlayer, -1, 1179656, 1179649, 0, Ref(TTYD64_String_NGPlus_Alright))
    ExecWait(TTYD64_Script_Eldstar_UpgradeAnimation)
    Set(GameFlag(4107), 1)
    IfLt(GameByte(4106), 255)
        Add(GameByte(4106), 1)
    EndIf
    Call(TTYD64_Function_InitNewGamePlusData)
    Call(GotoMapSpecial, (Bytecode) "kmr_31", 0, 11)
    Wait(2000)
    Return
    End
};

EvtScript TTYD64_Script_UpgradePartners_Main = {
    Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_18_1U, LVar1)
    IfLt(LVar1, 3)
        Call(ContinueSpeech, 0, 10813444, 10813441, 0, Ref(TTYD64_String_Merlon_NotEnoughShines))
        Call(DisablePlayerInput, 0)
        Return
    EndIf
    Call(CloseMessage)
    Call(ModifyGlobalOverrideFlags, 1, 2097152)
    Call(DisablePartnerAI, 0)
    Call(SetNpcFlagBits, -4, 256, 1)
    Call(TTYD64_WorldLib_FindKeyItem, 15, LVarC)
    Call(TTYD64_Function_GetPartnersAbleToUpgrade)
    IfEq(LVar0, -1)
        Call(SpeakToPlayer, 0, 10813444, 10813441, 0, Ref(TTYD64_String_Merlon_NoAvailablePartners))
        Wait(10)
        Call(DisablePlayerInput, 0)
        Call(EnablePartnerAI)
        Call(ModifyGlobalOverrideFlags, 0, 2097152)
        Return
    EndIf
    Call(TTYD64_SetShineCounterVisible, 1)
    Call(TTYD64_Function_OpenSuperBlockMenu)
    IfEq(LVar0, -1)
        Call(DisablePlayerInput, 0)
        Call(EnablePartnerAI)
        Call(ModifyGlobalOverrideFlags, 0, 2097152)
        Return
    EndIf
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Call(EnablePartnerAI)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, LVarB)
        Call(TTYD64_Function_SwitchToPartner, LVarB)
    Else
        Call(func_802CF56C, 2)
    EndIf
    Wait(10)
    Call(SpeakToPlayer, 0, 10813444, 10813441, 0, Ref(TTYD64_String_Merlon_AskConfirmation))
    Call(ShowChoice, 1966093)
    Call(CloseMessage)
    IfNe(LVar0, 0)
        Call(DisablePlayerInput, 0)
        Call(EnablePartnerAI)
        Call(ModifyGlobalOverrideFlags, 0, 2097152)
        Return
    EndIf
    Thread
        Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_18_1U, LVar1)
        Loop(3)
            Sub(LVar1, 1)
            Call(TTYD64_WriteField, TTYD64_F_GPLAYERDATA_18_1U, LVar1)
            Wait(8)
        EndLoop
    EndThread
    ExecWait(TTYD64_Script_UpgradeAnimation)
    Call(TTYD64_Function_UpgradePartner, LVarB, LVarD)
    Call(TTYD64_Function_SetMessageString_CurrentPartner)
    IfEq(LVarD, 1)
        Call(SpeakToPlayer, 0, 10813444, 10813441, 0, Ref(TTYD64_String_Merlon_PartnerIsNow_SuperRank))
    Else
        Call(SpeakToPlayer, 0, 10813444, 10813441, 0, Ref(TTYD64_String_Merlon_PartnerIsNow_UltraRank))
    EndIf
    Call(TTYD64_RaisePartnerMaxHP, LVarB)
    Call(DisablePlayerInput, 0)
    Call(EnablePartnerAI)
    Call(ModifyGlobalOverrideFlags, 0, 2097152)
    Return
    End
};

EvtScript TTYD64_Script_Init_NPC_NGPlus = {
    IfNe(GameByte(0), 95)
        Call(SetNpcPos, -1, 0, -1000, 0)
    EndIf
    Call(BindNpcInteract, -1, Ref(TTYD64_Script_Interact_NPC_NGPlus))
    Return
    End
};

EvtScript TTYD64_Script_UpgradeAnimation = {
    Exec(TTYD64_Script_UpgradeAnimation_Sparkles)
    Call(GetNpcPos, 0, LVar0, LVar1, LVar2)
    Add(LVar1, 15)
    Call(SetNpcAnimation, 0, 10813448)
    Call(PlayEffect_impl, 107, 1, LVar0, LVar1, LVar2, Float(1.0), 50, 0, 0, 0, 0, 0, 0)
    Wait(50)
    Call(SetNpcAnimation, 0, 10813449)
    Call(PlayEffect_impl, 82, 7, LVar0, LVar1, LVar2, Float(2.0), 30, 0, 0, 0, 0, 0, 0)
    Wait(70)
    Call(SetNpcAnimation, 0, 10813450)
    Call(PlayEffect_impl, 82, 3, LVar0, LVar1, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0)
    Wait(10)
    Call(SetNpcAnimation, 0, 10813440)
    Call(SetNpcAnimation, 0, 10813450)
    Call(PlayEffect_impl, 82, 3, LVar0, LVar1, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0)
    Wait(30)
    Call(SetNpcAnimation, 0, 10813441)
    Return
    End
};

EvtScript TTYD64_Script_ExitMinigame_Mole = {
    Call(DisablePlayerInput, 1)
    Call(GotoMap, (Bytecode) "kmr_32", 1)
    Return
    End
};

// clang-format on
