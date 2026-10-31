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
#include "port/romhack/specific/TTYD64/battle/player_internal.h"

extern EvtScript battle_move_jump_attack_EVS_JumpSupport_Approach;
extern EvtScript battle_move_jump_attack_EVS_UseBerserker_Ultra;
extern EvtScript battle_move_jump_attack_EVS_FirstStrike;
extern EvtScript battle_move_jump_attack_EVS_UseMove_Ultra;
extern EvtScript battle_move_jump_attack_EVS_UseMove_Super;
extern EvtScript battle_move_jump_attack_EVS_UseMove_Basic;
extern EvtScript battle_move_jump_attack_EVS_JumpSupport_ApproachAndJump;
extern EvtScript battle_move_jump_attack_EVS_JumpSupport_NoFollowUp;
extern EvtScript battle_move_jump_attack_EVS_JumpSupport_Rebound;
extern EvtScript battle_move_jump_attack_EVS_CheckForAPress;
extern EvtScript battle_move_jump_attack_EVS_JumpSupport_CalcJumpTime;
extern EvtScript battle_move_jump_attack_EVS_JumpSupport_Miss;
extern EvtScript battle_move_jump_attack_EVS_UseMove;
API_CALLABLE(AddGoalPos);
API_CALLABLE(CancelablePlayerRunToGoal);
API_CALLABLE(EnablePlayerBlur);
API_CALLABLE(GetActionCommandMode);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetJumpActionQuality);
API_CALLABLE(GetPlayerActionQuality);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(InterruptActionCommand);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(PlayerBasicJumpToGoal);
API_CALLABLE(PlayerDamageEnemy);
API_CALLABLE(PlayerHopToGoal);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(PlayerSuperJumpToGoal);
API_CALLABLE(PlayerTestEnemy);
API_CALLABLE(PlayerUltraJumpToGoal);
API_CALLABLE(PlayerYieldTurn);
API_CALLABLE(SetActionCommandMode);
API_CALLABLE(SetActionResult);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToFirstTarget);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(ShowActionHud);
API_CALLABLE(TTYD64_Player_AC_802A9000);
API_CALLABLE(TTYD64_Player_AC_802A9120);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(action_command_jump_init);
API_CALLABLE(action_command_jump_start);
API_CALLABLE(battle_move_jump_attack_CalcJumpReboundTime);
API_CALLABLE(func_802693F0);
EvtScript TTYD64_battle_move_jump_attack_EVS_JumpSupport_Rebound;
EvtScript TTYD64_battle_move_jump_attack_EVS_JumpSupport_NoFollowUp;
EvtScript TTYD64_battle_move_jump_attack_EVS_JumpSupport_ApproachAndJump;
EvtScript TTYD64_battle_move_jump_attack_EVS_UseMove_Basic;
EvtScript TTYD64_battle_move_jump_attack_EVS_UseMove_Super;
EvtScript TTYD64_battle_move_jump_attack_EVS_UseMove_Ultra;
EvtScript TTYD64_battle_move_jump_attack_EVS_FirstStrike;
EvtScript TTYD64_battle_move_jump_attack_EVS_802A3110;
EvtScript TTYD64_battle_move_jump_attack_EVS_802A3CF0;
EvtScript TTYD64_battle_move_jump_attack_EVS_UseBerserker_Ultra;
EvtScript TTYD64_battle_move_jump_attack_EVS_802A47B0;
EvtScript TTYD64_battle_move_jump_attack_EVS_JumpSupport_Approach;

// clang-format off
EvtScript TTYD64_battle_move_jump_attack_EVS_JumpSupport_Rebound = {
    Call(PlayerYieldTurn)
    Call(SetBattleFlagBits, BS_FLAGS1_EXECUTING_MOVE, 0)
    Call(UseBattleCamPreset, 3)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(GetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 40)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 65545)
    Call(SetActorJumpGravity, ACTOR_PLAYER, Float(1.2998))
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(func_802693F0)
    Call(battle_move_jump_attack_CalcJumpReboundTime)
    Call(PlayerHopToGoal, LVar0, 0, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65545)
    Wait(1)
    Call(AddGoalPos, ACTOR_PLAYER, -20, 0, 0)
    Call(PlayerHopToGoal, 6, 0, 2)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65545)
    Wait(5)
    Call(EnablePlayerBlur, -1)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Return
    End
};

EvtScript TTYD64_battle_move_jump_attack_EVS_JumpSupport_NoFollowUp = {
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
    Return
    End
};

EvtScript TTYD64_battle_move_jump_attack_EVS_JumpSupport_ApproachAndJump = {
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Exec(TTYD64_battle_move_jump_attack_EVS_802A3110)
    ExecWait(TTYD64_battle_move_jump_attack_EVS_JumpSupport_Approach)
    ExecWait(battle_move_jump_attack_EVS_JumpSupport_CalcJumpTime)
    Call(action_command_jump_start, LVarA, 3)
    ExecGetTID(TTYD64_battle_move_jump_attack_EVS_802A47B0, 0)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 196608)
    Call(PlayerBasicJumpToGoal, LVarA, 0)
    Return
    End
};

EvtScript TTYD64_battle_move_jump_attack_EVS_UseMove_Basic = {
    ExecWait(TTYD64_battle_move_jump_attack_EVS_JumpSupport_ApproachAndJump)
    Call(GetActionCommandMode, LVar0)
    IfEq(LVar0, 2)
        Call(SetActionCommandMode, 3)
        Loop(0)
            Call(GetActionCommandMode, LVar0)
            IfLt(LVar0, 2)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndIf
    Call(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    IfEq(LVar0, 6)
        ExecWait(battle_move_jump_attack_EVS_JumpSupport_Miss)
        Return
    EndIf
    Call(GetActionCommandMode, LVar0)
    IfGt(LVar0, 0)
        Wait(1)
    EndIf
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 1, 80)
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 1, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_move_jump_attack_EVS_JumpSupport_NoFollowUp)
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
    ExecGetTID(TTYD64_battle_move_jump_attack_EVS_802A3CF0, 0)
    Call(TTYD64_Player_AC_802A9000)
    Call(ShowActionHud, 0)
    Call(TTYD64_Player_AC_802A9120, 24, 3)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 65548)
    Call(PlayerBasicJumpToGoal, 24, 3)
    Wait(1)
    Call(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
    Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 1, 224)
    Call(SetActionResult, LVarF)
    ExecWait(TTYD64_battle_move_jump_attack_EVS_JumpSupport_Rebound)
    Return
    End
};

EvtScript TTYD64_battle_move_jump_attack_EVS_UseMove_Super = {
    ExecWait(TTYD64_battle_move_jump_attack_EVS_JumpSupport_ApproachAndJump)
    Call(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    IfEq(LVar0, 6)
        ExecWait(battle_move_jump_attack_EVS_JumpSupport_Miss)
        Return
    EndIf
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 2, 80)
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 2, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_move_jump_attack_EVS_JumpSupport_NoFollowUp)
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
    ExecGetTID(TTYD64_battle_move_jump_attack_EVS_802A3CF0, 0)
    Call(TTYD64_Player_AC_802A9000)
    Call(ShowActionHud, 0)
    Call(TTYD64_Player_AC_802A9120, 37, 3)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(EnablePlayerBlur, 1)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65546, 65547)
    Call(PlayerSuperJumpToGoal, 20, 4)
    Wait(7)
    Call(PlayerSuperJumpToGoal, 3, 5)
    Call(EnablePlayerBlur, -1)
    Wait(1)
    Call(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
    Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 2, 224)
    Call(SetActionResult, LVarF)
    ExecWait(TTYD64_battle_move_jump_attack_EVS_JumpSupport_Rebound)
    Return
    End
};

EvtScript TTYD64_battle_move_jump_attack_EVS_UseMove_Ultra = {
    ExecWait(TTYD64_battle_move_jump_attack_EVS_JumpSupport_ApproachAndJump)
    Call(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    IfEq(LVar0, 6)
        ExecWait(battle_move_jump_attack_EVS_JumpSupport_Miss)
        Return
    EndIf
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 3, 80)
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 3, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_move_jump_attack_EVS_JumpSupport_NoFollowUp)
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
    ExecGetTID(TTYD64_battle_move_jump_attack_EVS_802A3CF0, 0)
    Call(TTYD64_Player_AC_802A9000)
    Call(ShowActionHud, 0)
    Call(TTYD64_Player_AC_802A9120, 25, 3)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(EnablePlayerBlur, 1)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65543, 65548)
    Call(PlayerUltraJumpToGoal, 25, 4)
    Call(EnablePlayerBlur, -1)
    Wait(1)
    Call(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
    Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 3, 224)
    Call(SetActionResult, LVarF)
    ExecWait(TTYD64_battle_move_jump_attack_EVS_JumpSupport_Rebound)
    Return
    End
};

EvtScript TTYD64_battle_move_jump_attack_EVS_FirstStrike = {
    ExecWait(battle_move_jump_attack_EVS_UseMove)
    Return
    End
};

EvtScript TTYD64_battle_move_jump_attack_EVS_802A3110 = {
    Call(TTYD64_Player_AC_802A9000)
    Exec(TTYD64_Script_NukeTracker)
    Return
    End
};

EvtScript TTYD64_battle_move_jump_attack_EVS_802A3CF0 = {
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
                    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 327680, 65546, 65547)
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

EvtScript TTYD64_battle_move_jump_attack_EVS_UseBerserker_Ultra = {
    Call(GetBattlePhase, LVar0)
    IfNe(LVar0, 1)
        Call(InitTargetIterator)
    EndIf
    Call(SetGoalToTarget, ACTOR_PLAYER)
    ExecWait(TTYD64_battle_move_jump_attack_EVS_JumpSupport_ApproachAndJump)
    Call(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    IfEq(LVar0, 6)
        ExecWait(battle_move_jump_attack_EVS_JumpSupport_Miss)
        Return
    EndIf
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 3, 80)
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 3, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_move_jump_attack_EVS_JumpSupport_NoFollowUp)
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
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Call(action_command_jump_init)
    Call(ShowActionHud, 0)
    Call(action_command_jump_start, 25, 3)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(EnablePlayerBlur, 1)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65543, 65548)
    Call(PlayerUltraJumpToGoal, 25, 4)
    Call(EnablePlayerBlur, -1)
    Wait(1)
    Call(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
    Call(PlayerDamageEnemy, LVar0, 128, 0, 0, 3, 224)
    Call(SetActionResult, LVarF)
    ExecWait(TTYD64_battle_move_jump_attack_EVS_JumpSupport_Rebound)
    Return
    End
};

EvtScript TTYD64_battle_move_jump_attack_EVS_802A47B0 = {
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

EvtScript TTYD64_battle_move_jump_attack_EVS_JumpSupport_Approach = {
    Call(GetBattlePhase, LVar0)
    IfNe(LVar0, 1)
        Call(SetGoalToFirstTarget, ACTOR_SELF)
    EndIf
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Call(GetBattlePhase, LVar0)
    IfNe(LVar0, 1)
        Call(InitTargetIterator)
    EndIf
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(GetGoalPos, ACTOR_PLAYER, LVar3, LVar4, LVar5)
    Sub(LVar3, Float(70.0))
    IfLt(LVar0, LVar3)
        Set(LVar3, LVar0)
    EndIf
    Call(SetGoalPos, ACTOR_PLAYER, LVar3, LVar4, LVar5)
    Call(UseBattleCamPreset, 26)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(5.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(CancelablePlayerRunToGoal, 0, LVar0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    ExecWait(battle_move_jump_attack_EVS_CheckForAPress)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65542)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_jump_attack(void) {
    Mod_ReplaceScript(
        "TTYD64", &battle_move_jump_attack_EVS_JumpSupport_Rebound,
        &TTYD64_battle_move_jump_attack_EVS_JumpSupport_Rebound
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_jump_attack_EVS_JumpSupport_NoFollowUp,
        &TTYD64_battle_move_jump_attack_EVS_JumpSupport_NoFollowUp
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_jump_attack_EVS_JumpSupport_ApproachAndJump,
        &TTYD64_battle_move_jump_attack_EVS_JumpSupport_ApproachAndJump
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_jump_attack_EVS_UseMove_Basic, &TTYD64_battle_move_jump_attack_EVS_UseMove_Basic
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_jump_attack_EVS_UseMove_Super, &TTYD64_battle_move_jump_attack_EVS_UseMove_Super
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_jump_attack_EVS_UseMove_Ultra, &TTYD64_battle_move_jump_attack_EVS_UseMove_Ultra
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_jump_attack_EVS_FirstStrike, &TTYD64_battle_move_jump_attack_EVS_FirstStrike
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_jump_attack_EVS_UseBerserker_Ultra,
        &TTYD64_battle_move_jump_attack_EVS_UseBerserker_Ultra
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_jump_attack_EVS_JumpSupport_Approach,
        &TTYD64_battle_move_jump_attack_EVS_JumpSupport_Approach
    );
}
