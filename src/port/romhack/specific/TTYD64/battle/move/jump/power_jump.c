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

extern EvtScript battle_move_power_jump_EVS_UseMove;
extern EvtScript battle_move_power_jump_EVS_UseMove_Ultra;
extern EvtScript battle_move_power_jump_EVS_UseMove_Super;
extern EvtScript battle_move_power_jump_EVS_UseMove_Basic;
extern EvtScript battle_move_power_jump_EVS_JumpSupport_ApproachAndJump;
extern EvtScript battle_move_power_jump_EVS_JumpSupport_WeakRebound;
extern EvtScript battle_move_power_jump_EVS_JumpSupport_Rebound;
extern EvtScript battle_move_power_jump_EVS_802A26B4;
extern EvtScript battle_move_power_jump_EVS_JumpSupport_Approach;
extern EvtScript battle_move_power_jump_EVS_JumpSupport_CalcJumpTime;
extern EvtScript battle_move_power_jump_EVS_JumpSupport_Miss;
API_CALLABLE(AddGoalPos);
API_CALLABLE(EnablePlayerBlur);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetPlayerActionQuality);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(MakeLerp);
API_CALLABLE(PlayerBasicJumpToGoal);
API_CALLABLE(PlayerDamageEnemy);
API_CALLABLE(PlayerHopToGoal);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(PlayerTestEnemy);
API_CALLABLE(PlayerYieldTurn);
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
API_CALLABLE(TTYD64_Player_AC_802A9000);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(action_command_jump_start);
API_CALLABLE(battle_move_jump_attack_CalcJumpReboundTime);
API_CALLABLE(func_802693F0);
EvtScript TTYD64_battle_move_power_jump_EVS_JumpSupport_Rebound;
EvtScript TTYD64_battle_move_power_jump_EVS_JumpSupport_WeakRebound;
EvtScript TTYD64_battle_move_power_jump_EVS_JumpSupport_ApproachAndJump;
EvtScript TTYD64_battle_move_power_jump_EVS_802A2600;
EvtScript TTYD64_battle_move_power_jump_EVS_UseMove_Basic;
EvtScript TTYD64_battle_move_power_jump_EVS_UseMove_Super;
EvtScript TTYD64_battle_move_power_jump_EVS_UseMove_Ultra;
EvtScript TTYD64_battle_move_power_jump_EVS_802A2BC8;
EvtScript TTYD64_battle_move_power_jump_EVS_802A2EC4;
EvtScript TTYD64_battle_move_power_jump_EVS_UseMove;

// clang-format off
EvtScript TTYD64_battle_move_power_jump_EVS_JumpSupport_Rebound = {
    Call(PlayerYieldTurn)
    Call(SetBattleFlagBits, BS_FLAGS1_EXECUTING_MOVE, 0)
    Call(UseBattleCamPreset, 3)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(GetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 40)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 65545)
    Call(SetActorJumpGravity, ACTOR_PLAYER, Float(1.2998))
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Exec(TTYD64_battle_move_power_jump_EVS_802A2BC8)
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

EvtScript TTYD64_battle_move_power_jump_EVS_JumpSupport_WeakRebound = {
    Call(PlayerYieldTurn)
    Call(SetBattleFlagBits, BS_FLAGS1_EXECUTING_MOVE, 0)
    Call(UseBattleCamPreset, 3)
    Call(func_802693F0)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Sub(LVar0, 50)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 65545)
    Call(SetActorJumpGravity, ACTOR_PLAYER, Float(0.7998))
    Call(battle_move_jump_attack_CalcJumpReboundTime)
    Call(PlayerHopToGoal, LVar0, 0, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65545)
    Wait(1)
    Call(AddGoalPos, ACTOR_PLAYER, -30, 0, 0)
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

EvtScript TTYD64_battle_move_power_jump_EVS_JumpSupport_ApproachAndJump = {
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Exec(TTYD64_battle_move_power_jump_EVS_802A2600)
    ExecWait(battle_move_power_jump_EVS_JumpSupport_Approach)
    ExecWait(battle_move_power_jump_EVS_JumpSupport_CalcJumpTime)
    Call(action_command_jump_start, LVarA, 3)
    ExecGetTID(TTYD64_battle_move_power_jump_EVS_802A2EC4, 0)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 196608)
    Call(PlayerBasicJumpToGoal, LVarA, 0)
    Return
    End
};

EvtScript TTYD64_battle_move_power_jump_EVS_802A2600 = {
    Call(TTYD64_Player_AC_802A9000)
    Exec(TTYD64_Script_NukeTracker)
    Return
    End
};

EvtScript TTYD64_battle_move_power_jump_EVS_UseMove_Basic = {
    ExecWait(TTYD64_battle_move_power_jump_EVS_JumpSupport_ApproachAndJump)
    Call(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    IfEq(LVar0, 6)
        ExecWait(battle_move_power_jump_EVS_JumpSupport_Miss)
        Return
    EndIf
    ExecWait(battle_move_power_jump_EVS_802A26B4)
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, LVarD, 112)
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, LVarC, 48)
    EndSwitch
    Switch(LVar0)
        CaseGt(0)
            ExecWait(TTYD64_battle_move_power_jump_EVS_JumpSupport_Rebound)
        CaseDefault
            ExecWait(TTYD64_battle_move_power_jump_EVS_JumpSupport_WeakRebound)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_move_power_jump_EVS_UseMove_Super = {
    ExecWait(TTYD64_battle_move_power_jump_EVS_JumpSupport_ApproachAndJump)
    Call(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    IfEq(LVar0, 6)
        ExecWait(battle_move_power_jump_EVS_JumpSupport_Miss)
        Return
    EndIf
    ExecWait(battle_move_power_jump_EVS_802A26B4)
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, LVarD, 112)
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, LVarC, 48)
    EndSwitch
    Switch(LVar0)
        CaseGt(0)
            ExecWait(TTYD64_battle_move_power_jump_EVS_JumpSupport_Rebound)
        CaseDefault
            ExecWait(TTYD64_battle_move_power_jump_EVS_JumpSupport_WeakRebound)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_move_power_jump_EVS_UseMove_Ultra = {
    ExecWait(TTYD64_battle_move_power_jump_EVS_JumpSupport_ApproachAndJump)
    Call(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    IfEq(LVar0, 6)
        ExecWait(battle_move_power_jump_EVS_JumpSupport_Miss)
        Return
    EndIf
    ExecWait(battle_move_power_jump_EVS_802A26B4)
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, LVarD, 112)
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, 0, LVarC, 48)
    EndSwitch
    Switch(LVar0)
        CaseGt(0)
            ExecWait(TTYD64_battle_move_power_jump_EVS_JumpSupport_Rebound)
        CaseDefault
            ExecWait(TTYD64_battle_move_power_jump_EVS_JumpSupport_WeakRebound)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_move_power_jump_EVS_802A2BC8 = {
    Call(func_802693F0)
    Exec(TTYD64_Script_InitTracker)
    Wait(4)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Return
    EndIf
    Loop(4)
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

EvtScript TTYD64_battle_move_power_jump_EVS_802A2EC4 = {
    Call(UseBattleCamPreset, 34)
    Exec(TTYD64_Script_InitTracker)
    Wait(4)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Return
    EndIf
    Loop(4)
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

EvtScript TTYD64_battle_move_power_jump_EVS_UseMove = {
    Call(EnablePlayerBlur, 1)
    Call(ShowActionHud, 1)
    Call(TTYD64_GetStackBoost, 289, 2, LVarC, LVarD)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            Add(LVarC, 3)
            Add(LVarD, 4)
            ExecWait(TTYD64_battle_move_power_jump_EVS_UseMove_Basic)
        CaseEq(1)
            Add(LVarC, 4)
            Add(LVarD, 6)
            ExecWait(TTYD64_battle_move_power_jump_EVS_UseMove_Super)
        CaseEq(2)
            Add(LVarC, 5)
            Add(LVarD, 8)
            ExecWait(TTYD64_battle_move_power_jump_EVS_UseMove_Ultra)
    EndSwitch
    Call(EnablePlayerBlur, 0)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_power_jump(void) {
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_jump_EVS_JumpSupport_Rebound,
        &TTYD64_battle_move_power_jump_EVS_JumpSupport_Rebound
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_jump_EVS_JumpSupport_WeakRebound,
        &TTYD64_battle_move_power_jump_EVS_JumpSupport_WeakRebound
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_jump_EVS_JumpSupport_ApproachAndJump,
        &TTYD64_battle_move_power_jump_EVS_JumpSupport_ApproachAndJump
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_jump_EVS_UseMove_Basic, &TTYD64_battle_move_power_jump_EVS_UseMove_Basic
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_jump_EVS_UseMove_Super, &TTYD64_battle_move_power_jump_EVS_UseMove_Super
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_jump_EVS_UseMove_Ultra, &TTYD64_battle_move_power_jump_EVS_UseMove_Ultra
    );
    Mod_ReplaceScript("TTYD64", &battle_move_power_jump_EVS_UseMove, &TTYD64_battle_move_power_jump_EVS_UseMove);
}
