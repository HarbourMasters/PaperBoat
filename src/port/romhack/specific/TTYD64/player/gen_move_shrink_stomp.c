#include "common.h"
#include "script_api/battle.h"
#include "effects.h"
#include "entity.h"
#include "battle/battle.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/player/player_internal.h"

extern EvtScript battle_move_shrink_stomp_EVS_UseMove_Basic;
extern EvtScript battle_move_shrink_stomp_EVS_UseMove_Ultra;
extern EvtScript battle_move_shrink_stomp_EVS_UseMove_Super;
extern EvtScript battle_move_shrink_stomp_EVS_JumpSupport_ApproachAndJump;
extern EvtScript battle_move_shrink_stomp_EVS_JumpSupport_Rebound;
extern EvtScript battle_move_shrink_stomp_EVS_JumpSupport_Approach;
extern EvtScript battle_move_shrink_stomp_EVS_JumpSupport_CalcJumpTime;
extern EvtScript battle_move_shrink_stomp_EVS_JumpSupport_Miss;
API_CALLABLE(AddGoalPos);
API_CALLABLE(EnablePlayerBlur);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetJumpActionQuality);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPlayerActionQuality);
API_CALLABLE(InterruptActionCommand);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(MakeLerp);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlayParalyzeHitFX);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerBasicJumpToGoal);
API_CALLABLE(PlayerDamageEnemy);
API_CALLABLE(PlayerHopToGoal);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(PlayerSuperJumpToGoal);
API_CALLABLE(PlayerTestEnemy);
API_CALLABLE(PlayerUltraJumpToGoal);
API_CALLABLE(PlayerYieldTurn);
API_CALLABLE(SetActionResult);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(ShowActionHud);
API_CALLABLE(ShowMessageBox);
API_CALLABLE(TTYD64_Player_AC_802A9000);
API_CALLABLE(TTYD64_Player_AC_802A9120);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(WaitForMessageBoxDone);
API_CALLABLE(action_command_jump_start);
API_CALLABLE(battle_move_jump_attack_CalcJumpReboundTime);
API_CALLABLE(func_802693F0);
EvtScript TTYD64_battle_move_shrink_stomp_EVS_JumpSupport_Rebound;
EvtScript TTYD64_battle_move_shrink_stomp_EVS_802A19B0;
EvtScript TTYD64_battle_move_shrink_stomp_EVS_JumpSupport_ApproachAndJump;
EvtScript TTYD64_battle_move_shrink_stomp_EVS_UseMove_Super;
EvtScript TTYD64_battle_move_shrink_stomp_EVS_802A29C0;
EvtScript TTYD64_battle_move_shrink_stomp_EVS_UseMove_Ultra;
EvtScript TTYD64_battle_move_shrink_stomp_EVS_UseMove_Basic;
EvtScript TTYD64_battle_move_shrink_stomp_EVS_802A32F0;
EvtScript TTYD64_battle_move_shrink_stomp_EVS_802A35EC;
EvtScript TTYD64_battle_move_shrink_stomp_EVS_802A388C;
EvtScript TTYD64_battle_move_shrink_stomp_EVS_802A3A98;
EvtScript TTYD64_battle_move_shrink_stomp_EVS_802A3C88;

// clang-format off
EvtScript TTYD64_battle_move_shrink_stomp_EVS_JumpSupport_Rebound = {
    Call(PlayerYieldTurn)
    Call(SetBattleFlagBits, BS_FLAGS1_EXECUTING_MOVE, 0)
    Call(UseBattleCamPreset, 3)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(GetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 40)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 65545)
    Call(SetActorJumpGravity, ACTOR_PLAYER, Float(1.2998))
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Exec(TTYD64_battle_move_shrink_stomp_EVS_802A32F0)
    Call(battle_move_jump_attack_CalcJumpReboundTime)
    Call(PlayerHopToGoal, LVar0, 0, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65545)
    Wait(1)
    Call(AddGoalPos, ACTOR_PLAYER, -20, 0, 0)
    Call(PlayerHopToGoal, 6, 0, 2)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65545)
    Jump(TTYD64_battle_move_shrink_stomp_EVS_802A29C0)
    Call(EnablePlayerBlur, -1)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Return
    End
};

EvtScript TTYD64_battle_move_shrink_stomp_EVS_802A19B0 = {
    Call(GetOwnerTarget, LVar4, 0)
    Call(TTYD64_GetStackBoost, 303, 2, LVarC, 0)
    Add(LVarC, 3)
    IfGt(LVarC, 9)
        Set(LVarC, 9)
    EndIf
    Call(TTYD64_AddAttackBoost, LVar4, -2, LVarC)
    Call(TTYD64_MakeActorTiny, LVar4)
    Call(PlaySoundAtActor, LVar4, 8454)
    Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
    Sub(LVar0, 15)
    Add(LVar1, 35)
    Set(LVar2, 6)
    Call(PlayEffect_impl, 86, 3, LVar0, LVar1, LVar2, Float(1.5), 60, 0, 0, 0, 0, 0, 0, 0)
    Call(TTYD64_GetEffectData, LVarF, LVar0)
    Call(TTYD64_WritePtrField, LVar0, TTYD64_F_STATCHANGEFXDATA_20_4U, -2)
    Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
    Add(LVar1, 15)
    Add(LVar2, 2)
    Call(PlayParalyzeHitFX)
    Return
    End
};

EvtScript TTYD64_battle_move_shrink_stomp_EVS_JumpSupport_ApproachAndJump = {
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Exec(TTYD64_battle_move_shrink_stomp_EVS_802A3C88)
    ExecWait(battle_move_shrink_stomp_EVS_JumpSupport_Approach)
    ExecWait(battle_move_shrink_stomp_EVS_JumpSupport_CalcJumpTime)
    Call(action_command_jump_start, LVarA, 3)
    ExecGetTID(TTYD64_battle_move_shrink_stomp_EVS_802A3A98, 0)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 196608)
    Call(PlayerBasicJumpToGoal, LVarA, 0)
    Return
    End
};

EvtScript TTYD64_battle_move_shrink_stomp_EVS_UseMove_Super = {
    ExecWait(TTYD64_battle_move_shrink_stomp_EVS_JumpSupport_ApproachAndJump)
    Call(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    IfEq(LVar0, 6)
        ExecWait(battle_move_shrink_stomp_EVS_JumpSupport_Miss)
        Return
    EndIf
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_ACTOR_JUMPED_2)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 2, 80)
        CaseDefault
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_ACTOR_JUMPED_2)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 2, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Exec(TTYD64_battle_move_shrink_stomp_EVS_802A19B0)
            ExecWait(TTYD64_battle_move_shrink_stomp_EVS_802A388C)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
        EndCaseGroup
    EndSwitch
    Call(GetJumpActionQuality, LVarF)
    ChildThread
        Call(UseBattleCamPreset, 27)
        Wait(5)
        Call(SetGoalToTarget, ACTOR_PLAYER)
        Call(UseBattleCamPreset, 35)
    EndChildThread
    Call(InterruptActionCommand)
    ExecGetTID(TTYD64_battle_move_shrink_stomp_EVS_802A35EC, 0)
    Call(TTYD64_Player_AC_802A9000)
    Call(ShowActionHud, 0)
    Call(TTYD64_Player_AC_802A9120, 37, 3)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(EnablePlayerBlur, 1)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65546, 65547)
    Call(PlayerSuperJumpToGoal, 20, 4)
    Wait(7)
    Call(PlayerSuperJumpToGoal, 3, 5)
    Call(EnablePlayerBlur, 0)
    Wait(1)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_ACTOR_JUMPED_2)
    Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 2, 224)
    Call(SetActionResult, LVarF)
    Exec(TTYD64_battle_move_shrink_stomp_EVS_802A19B0)
    ExecWait(TTYD64_battle_move_shrink_stomp_EVS_JumpSupport_Rebound)
    Return
    End
};

EvtScript TTYD64_battle_move_shrink_stomp_EVS_802A29C0 = {
    Exec(TTYD64_Script_InitTracker)
    Wait(5)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Return
    EndIf
    Exec(TTYD64_Script_InitTracker)
    Loop(3)
        ExecWait(TTYD64_Script_TimingTutor)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishAddCount, LVar0)
            Call(TTYD64_WriteField, TTYD64_F_GACTIONCOMMANDSTATUS_60_1U, 0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Call(SetAnimation, ACTOR_PLAYER, 0, 196617)
            Wait(20)
            Call(EnablePlayerBlur, -1)
            Call(SetGoalToHome, ACTOR_PLAYER)
            Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
            Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
            Call(PlayerRunToGoal, 0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
            Return
        EndIf
        Wait(1)
    EndLoop
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Call(EnablePlayerBlur, -1)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Call(ShowMessageBox, 266, 60)
    Call(WaitForMessageBoxDone)
    Return
    End
};

EvtScript TTYD64_battle_move_shrink_stomp_EVS_UseMove_Ultra = {
    ExecWait(TTYD64_battle_move_shrink_stomp_EVS_JumpSupport_ApproachAndJump)
    Call(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    IfEq(LVar0, 6)
        ExecWait(battle_move_shrink_stomp_EVS_JumpSupport_Miss)
        Return
    EndIf
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_ACTOR_JUMPED_3)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 3, 80)
        CaseDefault
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_ACTOR_JUMPED_3)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 3, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Exec(TTYD64_battle_move_shrink_stomp_EVS_802A19B0)
            ExecWait(TTYD64_battle_move_shrink_stomp_EVS_802A388C)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
        EndCaseGroup
    EndSwitch
    Call(GetJumpActionQuality, LVarF)
    ChildThread
        Call(UseBattleCamPreset, 28)
        Wait(5)
        Call(SetGoalToTarget, ACTOR_PLAYER)
        Call(UseBattleCamPreset, 35)
    EndChildThread
    Call(InterruptActionCommand)
    ExecGetTID(TTYD64_battle_move_shrink_stomp_EVS_802A35EC, 0)
    Call(TTYD64_Player_AC_802A9000)
    Call(ShowActionHud, 0)
    Call(TTYD64_Player_AC_802A9120, 25, 3)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(EnablePlayerBlur, 1)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65543, 65548)
    Call(PlayerUltraJumpToGoal, 25, 4)
    Call(EnablePlayerBlur, 0)
    Wait(1)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_ACTOR_JUMPED_3)
    Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 3, 224)
    Call(SetActionResult, LVarF)
    Exec(TTYD64_battle_move_shrink_stomp_EVS_802A19B0)
    ExecWait(TTYD64_battle_move_shrink_stomp_EVS_JumpSupport_Rebound)
    Return
    End
};

EvtScript TTYD64_battle_move_shrink_stomp_EVS_UseMove_Basic = {
    ExecWait(TTYD64_battle_move_shrink_stomp_EVS_JumpSupport_ApproachAndJump)
    Call(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    IfEq(LVar0, 6)
        ExecWait(battle_move_shrink_stomp_EVS_JumpSupport_Miss)
        Return
    EndIf
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 1, 80)
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 1, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Exec(TTYD64_battle_move_shrink_stomp_EVS_802A19B0)
            ExecWait(TTYD64_battle_move_shrink_stomp_EVS_802A388C)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
        EndCaseGroup
    EndSwitch
    ChildThread
        Call(UseBattleCamPreset, 27)
        Wait(5)
        Call(SetGoalToTarget, ACTOR_PLAYER)
        Call(UseBattleCamPreset, 35)
    EndChildThread
    Call(GetJumpActionQuality, LVarF)
    Call(InterruptActionCommand)
    ExecGetTID(TTYD64_battle_move_shrink_stomp_EVS_802A35EC, 0)
    Call(TTYD64_Player_AC_802A9000)
    Call(ShowActionHud, 0)
    Call(TTYD64_Player_AC_802A9120, 24, 3)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 65548)
    Call(PlayerBasicJumpToGoal, 24, 3)
    Wait(1)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_ACTOR_JUMPED_1)
    Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 1, 224)
    Call(SetActionResult, LVarF)
    Exec(TTYD64_battle_move_shrink_stomp_EVS_802A19B0)
    ExecWait(TTYD64_battle_move_shrink_stomp_EVS_JumpSupport_Rebound)
    Return
    End
};

EvtScript TTYD64_battle_move_shrink_stomp_EVS_802A32F0 = {
    Call(func_802693F0)
    Exec(TTYD64_Script_InitTracker)
    Wait(5)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Return
    EndIf
    Loop(3)
        ExecWait(TTYD64_Script_TimingTutor)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishAddCount, LVar0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            SetTimescale(Float(3.0))
            Loop(3)
                Call(MakeLerp, 0, -180, 3, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, ACTOR_PLAYER, 0, LVar0, 0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
                Call(MakeLerp, -180, 0, 3, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, ACTOR_PLAYER, 0, LVar0, 0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
            EndLoop
            SetTimescale(Float(1.0))
            Call(SetActorRotation, ACTOR_PLAYER, 0, 0, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Return
    End
};

EvtScript TTYD64_battle_move_shrink_stomp_EVS_802A35EC = {
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Exec(TTYD64_Script_InitTracker)
    Wait(5)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Return
    EndIf
    Loop(3)
        ExecWait(TTYD64_Script_TimingTutor)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishAddCount, LVar0)
            Call(TTYD64_WriteField, TTYD64_F_GACTIONCOMMANDSTATUS_60_1U, 0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_0_1U, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 327680, 327680, 65548)
                CaseEq(1)
                    Call(SetAnimation, ACTOR_PLAYER, 0, 327680)
                    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 327680, 327680, 65548)
                CaseEq(2)
                    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65567, 65567, 65548)
            EndSwitch
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Return
    End
};

EvtScript TTYD64_battle_move_shrink_stomp_EVS_802A388C = {
    Call(PlayerYieldTurn)
    Call(SetBattleFlagBits, BS_FLAGS1_EXECUTING_MOVE, 0)
    Call(UseBattleCamPreset, 29)
    Call(func_802693F0)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 65545)
    Call(SetActorJumpGravity, ACTOR_PLAYER, Float(1.0))
    Call(battle_move_jump_attack_CalcJumpReboundTime)
    Call(PlayerHopToGoal, LVar0, 0, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65545)
    Wait(1)
    Call(AddGoalPos, ACTOR_PLAYER, -20, 0, 0)
    Call(PlayerHopToGoal, 6, 0, 2)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65545)
    Wait(2)
    Call(EnablePlayerBlur, -1)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Call(ShowMessageBox, 266, 60)
    Call(WaitForMessageBoxDone)
    Return
    End
};

EvtScript TTYD64_battle_move_shrink_stomp_EVS_802A3A98 = {
    Call(UseBattleCamPreset, 34)
    Exec(TTYD64_Script_InitTracker)
    Wait(5)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Return
    EndIf
    Loop(3)
        ExecWait(TTYD64_Script_TimingTutor)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishAddCount, LVar0)
            Call(TTYD64_WriteField, TTYD64_F_GACTIONCOMMANDSTATUS_60_1U, 0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65555, 65555, 65548)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Return
    End
};

EvtScript TTYD64_battle_move_shrink_stomp_EVS_802A3C88 = {
    Call(TTYD64_Player_AC_802A9000)
    Exec(TTYD64_Script_NukeTracker)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_shrink_stomp(void) {
    Mod_ReplaceScript(
        "TTYD64", &battle_move_shrink_stomp_EVS_JumpSupport_Rebound,
        &TTYD64_battle_move_shrink_stomp_EVS_JumpSupport_Rebound
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_shrink_stomp_EVS_JumpSupport_ApproachAndJump,
        &TTYD64_battle_move_shrink_stomp_EVS_JumpSupport_ApproachAndJump
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_shrink_stomp_EVS_UseMove_Super, &TTYD64_battle_move_shrink_stomp_EVS_UseMove_Super
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_shrink_stomp_EVS_UseMove_Ultra, &TTYD64_battle_move_shrink_stomp_EVS_UseMove_Ultra
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_shrink_stomp_EVS_UseMove_Basic, &TTYD64_battle_move_shrink_stomp_EVS_UseMove_Basic
    );
}
