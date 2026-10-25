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

extern EvtScript battle_move_power_bounce_EVS_UseMove;
extern EvtScript battle_move_power_bounce_EVS_UseMove_Ultra;
extern EvtScript battle_move_power_bounce_EVS_UseMove_Super;
extern EvtScript battle_move_power_bounce_EVS_UseMove_Basic;
extern EvtScript battle_move_power_bounce_EVS_JumpSupport_NoFollowUp;
extern EvtScript battle_move_power_bounce_EVS_JumpSupport_Rebound;
extern EvtScript battle_move_power_bounce_EVS_JumpSupport_Approach;
extern EvtScript battle_move_power_bounce_EVS_JumpSupport_CalcJumpTime;
extern EvtScript battle_move_power_bounce_EVS_JumpSupport_Miss;
extern s32 battle_move_power_bounce_DifficultyTable[];
API_CALLABLE(AddGoalPos);
API_CALLABLE(EnablePlayerBlur);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetCommandAutoSuccess);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetJumpActionQuality);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetPlayerActionQuality);
API_CALLABLE(InterruptActionCommand);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerBasicJumpToGoal);
API_CALLABLE(PlayerDamageEnemy);
API_CALLABLE(PlayerHopToGoal);
API_CALLABLE(PlayerPowerBounceEnemy);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(PlayerSuperJumpToGoal);
API_CALLABLE(PlayerTestEnemy);
API_CALLABLE(PlayerUltraJumpToGoal);
API_CALLABLE(PlayerYieldTurn);
API_CALLABLE(SetActionDifficultyTable);
API_CALLABLE(SetActionResult);
API_CALLABLE(SetActorJumpGravity);
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
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(action_command_jump_init);
API_CALLABLE(action_command_jump_start);
API_CALLABLE(battle_move_jump_attack_CalcJumpReboundTime);
API_CALLABLE(battle_move_power_bounce_GetHitChance);
API_CALLABLE(battle_move_power_bounce_IncrementHitCounter);
API_CALLABLE(battle_move_power_bounce_InitializeHitCounter);
API_CALLABLE(battle_move_power_bounce_StoreHitCountRecord);
API_CALLABLE(func_802693F0);
EvtScript TTYD64_battle_move_power_bounce_EVS_JumpSupport_Rebound;
EvtScript TTYD64_battle_move_power_bounce_EVS_JumpSupport_NoFollowUp;
EvtScript TTYD64_battle_move_power_bounce_EVS_802A2734;
EvtScript TTYD64_battle_move_power_bounce_EVS_UseMove_Basic;
EvtScript TTYD64_battle_move_power_bounce_EVS_UseMove_Super;
EvtScript TTYD64_battle_move_power_bounce_EVS_UseMove_Ultra;
EvtScript TTYD64_battle_move_power_bounce_EVS_802A4014;
EvtScript TTYD64_battle_move_power_bounce_EVS_UseMove;

// clang-format off
EvtScript TTYD64_battle_move_power_bounce_EVS_JumpSupport_Rebound = {
    Call(PlayerYieldTurn)
    Call(SetBattleFlagBits, BS_FLAGS1_EXECUTING_MOVE, 0)
    Call(UseBattleCamPreset, 3)
    Call(func_802693F0)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(GetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 40)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 65545)
    Call(SetActorJumpGravity, ACTOR_PLAYER, Float(1.2998))
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
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

EvtScript TTYD64_battle_move_power_bounce_EVS_JumpSupport_NoFollowUp = {
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

EvtScript TTYD64_battle_move_power_bounce_EVS_802A2734 = {
    Call(TTYD64_Player_AC_802A9000)
    Exec(TTYD64_Script_NukeTracker)
    Return
    End
};

EvtScript TTYD64_battle_move_power_bounce_EVS_UseMove_Basic = {
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Exec(TTYD64_battle_move_power_bounce_EVS_802A2734)
    Call(SetActionDifficultyTable, Ref(battle_move_power_bounce_DifficultyTable))
    ExecWait(battle_move_power_bounce_EVS_JumpSupport_Approach)
    ExecWait(battle_move_power_bounce_EVS_JumpSupport_CalcJumpTime)
    Call(action_command_jump_start, LVarA, 1)
    Call(UseBattleCamPreset, 34)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 196608)
    Call(PlayerBasicJumpToGoal, LVarA, 0)
    Call(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    IfEq(LVar0, 6)
        ExecWait(battle_move_power_bounce_EVS_JumpSupport_Miss)
        Return
    EndIf
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
            Call(PlayerDamageEnemy, LVar0, 1048704, 0, 0, LVarC, 80)
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
            Call(PlayerDamageEnemy, LVar0, 1048704, 0, 0, LVarC, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_move_power_bounce_EVS_JumpSupport_NoFollowUp)
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
    Call(GetJumpActionQuality, LVarE)
    Call(battle_move_power_bounce_IncrementHitCounter)
    Set(LVarD, 0)
    Set(LVarF, 0)
    Set(LFlag0, 0)
    Label(10)
    ChildThread
        Call(UseBattleCamPreset, 27)
        Wait(5)
        Call(SetGoalToTarget, ACTOR_PLAYER)
        Call(UseBattleCamPreset, 35)
    EndChildThread
    Call(InterruptActionCommand)
    Call(SetActionDifficultyTable, Ref(battle_move_power_bounce_DifficultyTable))
    ExecGetTID(TTYD64_battle_move_power_bounce_EVS_802A4014, 0)
    Call(action_command_jump_init)
    Set(LVarA, 24)
    Switch(LVarF)
        CaseEq(0)
            Call(action_command_jump_start, LVarA, 1)
        CaseEq(1)
            Call(action_command_jump_start, LVarA, 2)
        CaseEq(2)
            Call(action_command_jump_start, LVarA, 3)
        CaseEq(3)
            Call(action_command_jump_start, LVarA, 4)
        CaseDefault
            Call(action_command_jump_start, LVarA, 5)
    EndSwitch
    Sub(LVarD, 1)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 65548)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    IfEq(LVarF, 0)
        Call(PlayerBasicJumpToGoal, 24, 3)
    Else
        Call(PlayerBasicJumpToGoal, 24, 4)
    EndIf
    Call(GetCommandAutoSuccess, LVar1)
    IfEq(LVar1, 1)
        IfGe(LVarF, 3)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(battle_move_power_bounce_GetHitChance)
    IfGe(LVarF, LVar0)
        Set(LFlag0, 1)
    EndIf
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            IfEq(LFlag0, 0)
                Call(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
                Call(PlayerPowerBounceEnemy, LVar0, 1048704, 0, 0, LVarC, LVarD, 64)
            Else
                Call(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
                Call(PlayerPowerBounceEnemy, LVar0, 1048704, 0, 0, LVarC, LVarD, 224)
            EndIf
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
            Call(PlayerPowerBounceEnemy, LVar0, 1048704, 0, 0, LVarC, LVarD, 32)
    EndSwitch
    Switch(LVarF)
        CaseEq(0)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_1)
        CaseEq(1)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_2)
        CaseEq(2)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_3)
        CaseEq(3)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_4)
        CaseDefault
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_4)
    EndSwitch
    Call(SetActionResult, LVarE)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            IfEq(LFlag0, 1)
                ExecWait(TTYD64_battle_move_power_bounce_EVS_JumpSupport_Rebound)
                Return
            EndIf
            ExecWait(TTYD64_battle_move_power_bounce_EVS_JumpSupport_NoFollowUp)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
            IfEq(LFlag0, 1)
                ExecWait(TTYD64_battle_move_power_bounce_EVS_JumpSupport_Rebound)
                Return
            EndIf
        EndCaseGroup
    EndSwitch
    Add(LVarF, 1)
    Call(battle_move_power_bounce_IncrementHitCounter)
    Goto(10)
    Return
    End
};

EvtScript TTYD64_battle_move_power_bounce_EVS_UseMove_Super = {
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Exec(TTYD64_battle_move_power_bounce_EVS_802A2734)
    Call(SetActionDifficultyTable, Ref(battle_move_power_bounce_DifficultyTable))
    ExecWait(battle_move_power_bounce_EVS_JumpSupport_Approach)
    ExecWait(battle_move_power_bounce_EVS_JumpSupport_CalcJumpTime)
    Call(action_command_jump_start, LVarA, 1)
    Call(UseBattleCamPreset, 34)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 196608)
    Call(PlayerBasicJumpToGoal, LVarA, 0)
    Call(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    IfEq(LVar0, 6)
        ExecWait(battle_move_power_bounce_EVS_JumpSupport_Miss)
        Return
    EndIf
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
            Call(PlayerDamageEnemy, LVar0, 1048704, 0, 0, LVarC, 80)
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
            Call(PlayerDamageEnemy, LVar0, 1048704, 0, 0, LVarC, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_move_power_bounce_EVS_JumpSupport_NoFollowUp)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
        EndCaseGroup
    EndSwitch
    Call(GetJumpActionQuality, LVarE)
    Call(battle_move_power_bounce_IncrementHitCounter)
    Set(LVarD, 0)
    Set(LVarF, 0)
    Set(LFlag0, 0)
    Label(10)
    ChildThread
        Call(UseBattleCamPreset, 27)
        Wait(5)
        Call(SetGoalToTarget, ACTOR_PLAYER)
        Call(UseBattleCamPreset, 35)
    EndChildThread
    Call(InterruptActionCommand)
    Call(SetActionDifficultyTable, Ref(battle_move_power_bounce_DifficultyTable))
    ExecGetTID(TTYD64_battle_move_power_bounce_EVS_802A4014, 0)
    Call(action_command_jump_init)
    Set(LVarA, 37)
    Switch(LVarF)
        CaseEq(0)
            Call(action_command_jump_start, LVarA, 1)
        CaseEq(1)
            Call(action_command_jump_start, LVarA, 2)
        CaseEq(2)
            Call(action_command_jump_start, LVarA, 3)
        CaseEq(3)
            Call(action_command_jump_start, LVarA, 4)
        CaseDefault
            Call(action_command_jump_start, LVarA, 5)
    EndSwitch
    Sub(LVarD, 1)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65546, 65547)
    Call(EnablePlayerBlur, 1)
    IfEq(LVarF, 0)
        Call(PlayerSuperJumpToGoal, 20, 3)
        Wait(7)
        Call(PlayerSuperJumpToGoal, 3, 6)
    Else
        Call(PlayerSuperJumpToGoal, 20, 4)
        Wait(7)
        Call(PlayerSuperJumpToGoal, 3, 5)
    EndIf
    Call(EnablePlayerBlur, 0)
    Call(GetCommandAutoSuccess, LVar1)
    IfEq(LVar1, 1)
        IfGt(LVarF, 3)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(battle_move_power_bounce_GetHitChance)
    IfGt(LVarF, LVar0)
        Set(LFlag0, 1)
    EndIf
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            IfEq(LFlag0, 0)
                Call(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
                Call(PlayerPowerBounceEnemy, LVar0, 1048704, 0, 0, LVarC, LVarD, 64)
            Else
                Call(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
                Call(PlayerPowerBounceEnemy, LVar0, 1048704, 0, 0, LVarC, LVarD, 224)
            EndIf
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
            Call(PlayerPowerBounceEnemy, LVar0, 1048704, 0, 0, LVarC, LVarD, 32)
    EndSwitch
    Switch(LVarF)
        CaseEq(0)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_1)
        CaseEq(1)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_2)
        CaseEq(2)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_3)
        CaseEq(3)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_4)
        CaseDefault
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_4)
    EndSwitch
    Call(SetActionResult, LVarE)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            IfEq(LFlag0, 1)
                ExecWait(TTYD64_battle_move_power_bounce_EVS_JumpSupport_Rebound)
                Return
            EndIf
            ExecWait(TTYD64_battle_move_power_bounce_EVS_JumpSupport_NoFollowUp)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
            IfEq(LFlag0, 1)
                ExecWait(TTYD64_battle_move_power_bounce_EVS_JumpSupport_Rebound)
                Return
            EndIf
        EndCaseGroup
    EndSwitch
    Add(LVarF, 1)
    Call(battle_move_power_bounce_IncrementHitCounter)
    Goto(10)
    Return
    End
};

EvtScript TTYD64_battle_move_power_bounce_EVS_UseMove_Ultra = {
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Exec(TTYD64_battle_move_power_bounce_EVS_802A2734)
    Call(SetActionDifficultyTable, Ref(battle_move_power_bounce_DifficultyTable))
    ExecWait(battle_move_power_bounce_EVS_JumpSupport_Approach)
    ExecWait(battle_move_power_bounce_EVS_JumpSupport_CalcJumpTime)
    Call(action_command_jump_start, LVarA, 1)
    Call(UseBattleCamPreset, 34)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 196608)
    Call(PlayerBasicJumpToGoal, LVarA, 0)
    Call(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    IfEq(LVar0, 6)
        ExecWait(battle_move_power_bounce_EVS_JumpSupport_Miss)
        Return
    EndIf
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
            Call(PlayerDamageEnemy, LVar0, 1048704, 0, 0, LVarC, 80)
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
            Call(PlayerDamageEnemy, LVar0, 1048704, 0, 0, LVarC, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_move_power_bounce_EVS_JumpSupport_NoFollowUp)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
        EndCaseGroup
    EndSwitch
    Call(GetJumpActionQuality, LVarE)
    Call(battle_move_power_bounce_IncrementHitCounter)
    Set(LVarD, 0)
    Set(LVarF, 0)
    Set(LFlag0, 0)
    Label(10)
    ChildThread
        Call(UseBattleCamPreset, 28)
        Wait(5)
        Call(SetGoalToTarget, ACTOR_PLAYER)
        Call(UseBattleCamPreset, 35)
    EndChildThread
    Call(InterruptActionCommand)
    Call(SetActionDifficultyTable, Ref(battle_move_power_bounce_DifficultyTable))
    ExecGetTID(TTYD64_battle_move_power_bounce_EVS_802A4014, 0)
    Call(action_command_jump_init)
    Set(LVarA, 25)
    Switch(LVarF)
        CaseEq(0)
            Call(action_command_jump_start, LVarA, 1)
        CaseEq(1)
            Call(action_command_jump_start, LVarA, 2)
        CaseEq(2)
            Call(action_command_jump_start, LVarA, 3)
        CaseEq(3)
            Call(action_command_jump_start, LVarA, 4)
        CaseDefault
            Call(action_command_jump_start, LVarA, 5)
    EndSwitch
    Sub(LVarD, 1)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(EnablePlayerBlur, 1)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65543, 65548)
    IfEq(LVarF, 0)
        Call(PlayerUltraJumpToGoal, 25, 2)
    Else
        Call(PlayerUltraJumpToGoal, 25, 4)
    EndIf
    Call(EnablePlayerBlur, 0)
    Call(GetCommandAutoSuccess, LVar1)
    IfEq(LVar1, 1)
        IfGt(LVarF, 3)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(battle_move_power_bounce_GetHitChance)
    IfGt(LVarF, LVar0)
        Set(LFlag0, 1)
    EndIf
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            IfEq(LFlag0, 0)
                Call(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
                Call(PlayerPowerBounceEnemy, LVar0, 1048704, 0, 0, LVarC, LVarD, 64)
            Else
                Call(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
                Call(PlayerPowerBounceEnemy, LVar0, 1048704, 0, 0, LVarC, LVarD, 224)
            EndIf
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
            Call(PlayerPowerBounceEnemy, LVar0, 1048704, 0, 0, LVarC, LVarD, 32)
    EndSwitch
    Switch(LVarF)
        CaseEq(0)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_1)
        CaseEq(1)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_2)
        CaseEq(2)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_3)
        CaseEq(3)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_4)
        CaseDefault
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_4)
    EndSwitch
    Call(SetActionResult, LVarE)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            IfEq(LFlag0, 1)
                ExecWait(TTYD64_battle_move_power_bounce_EVS_JumpSupport_Rebound)
                Return
            EndIf
            ExecWait(TTYD64_battle_move_power_bounce_EVS_JumpSupport_NoFollowUp)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
            IfEq(LFlag0, 1)
                ExecWait(TTYD64_battle_move_power_bounce_EVS_JumpSupport_Rebound)
                Return
            EndIf
        EndCaseGroup
    EndSwitch
    Add(LVarF, 1)
    Call(battle_move_power_bounce_IncrementHitCounter)
    Goto(10)
    Return
    End
};

EvtScript TTYD64_battle_move_power_bounce_EVS_802A4014 = {
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Exec(TTYD64_Script_InitTracker)
    Wait(5)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Return
    EndIf
    Loop(5)
        ExecWait(TTYD64_Script_TimingTutor)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishAddCount, LVar0)
            Call(TTYD64_WriteField, TTYD64_F_GACTIONCOMMANDSTATUS_60_1U, 0)
            Call(TTYD64_StylishGetCount, LVar0)
            IfGt(LVar0, 3)
                Set(LVarA, 1)
            EndIf
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

EvtScript TTYD64_battle_move_power_bounce_EVS_UseMove = {
    Set(LFlagA, 0)
    Call(ShowActionHud, 1)
    Call(battle_move_power_bounce_InitializeHitCounter)
    Call(TTYD64_GetStackBoost, 228, 1, LVarC, 0)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            Add(LVarC, 1)
            ExecWait(TTYD64_battle_move_power_bounce_EVS_UseMove_Basic)
        CaseEq(1)
            Add(LVarC, 2)
            ExecWait(TTYD64_battle_move_power_bounce_EVS_UseMove_Super)
        CaseEq(2)
            Add(LVarC, 3)
            ExecWait(TTYD64_battle_move_power_bounce_EVS_UseMove_Ultra)
    EndSwitch
    Call(battle_move_power_bounce_StoreHitCountRecord)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_power_bounce(void) {
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_bounce_EVS_JumpSupport_Rebound,
        &TTYD64_battle_move_power_bounce_EVS_JumpSupport_Rebound
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_bounce_EVS_JumpSupport_NoFollowUp,
        &TTYD64_battle_move_power_bounce_EVS_JumpSupport_NoFollowUp
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_bounce_EVS_UseMove_Basic, &TTYD64_battle_move_power_bounce_EVS_UseMove_Basic
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_bounce_EVS_UseMove_Super, &TTYD64_battle_move_power_bounce_EVS_UseMove_Super
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_bounce_EVS_UseMove_Ultra, &TTYD64_battle_move_power_bounce_EVS_UseMove_Ultra
    );
    Mod_ReplaceScript("TTYD64", &battle_move_power_bounce_EVS_UseMove, &TTYD64_battle_move_power_bounce_EVS_UseMove);
}
