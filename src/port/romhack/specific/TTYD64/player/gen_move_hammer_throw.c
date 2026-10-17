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

extern EvtScript battle_move_hammer_throw_EVS_UseMove_Impl;
extern EvtScript battle_move_hammer_throw_EVS_UseMove;
extern EvtScript battle_move_hammer_throw_EVS_HammerSupport_ReturnHome_SmashSuccess;
extern EvtScript battle_move_hammer_throw_EVS_802A3E5C;
extern EvtScript battle_move_hammer_throw_EVS_802A3FE0;
extern EvtScript battle_move_hammer_throw_EVS_802A4164;
extern EvtScript battle_move_hammer_throw_EVS_HammerSupport_ReturnHome_SmashMiss;
extern s32 battle_move_hammer_throw_EMS_BasicHammer[];
extern s32 battle_move_hammer_throw_EMS_SuperHammer[];
extern s32 battle_move_hammer_throw_EMS_UltraHammer[];
API_CALLABLE(AddBattleCamDist);
API_CALLABLE(AddGoalPos);
API_CALLABLE(CheckButtonDown);
API_CALLABLE(CreateVirtualEntity);
API_CALLABLE(DeleteVirtualEntity);
API_CALLABLE(EnablePlayerBlur);
API_CALLABLE(GetActionCommandMode);
API_CALLABLE(GetActionProgress);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetPlayerActionQuality);
API_CALLABLE(GetSmashActionQuality);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerDamageEnemy);
API_CALLABLE(PlayerHopToGoal);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(PlayerTestEnemy);
API_CALLABLE(PlayerYieldTurn);
API_CALLABLE(SetActionProgress);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(SetVirtualEntityJumpGravity);
API_CALLABLE(SetVirtualEntityPosition);
API_CALLABLE(SetVirtualEntityRotation);
API_CALLABLE(SetVirtualEntityScale);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowActionHud);
API_CALLABLE(StartRumble);
API_CALLABLE(TTYD64_Player_AC_802A9000);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(VirtualEntityJumpTo);
API_CALLABLE(VirtualEntityLandJump);
API_CALLABLE(action_command_hammer_start);
API_CALLABLE(battle_move_hammer_throw_ShouldMovesAutoSucceed);
API_CALLABLE(func_802693F0);
EvtScript TTYD64_battle_move_hammer_throw_EVS_802A1000;
EvtScript TTYD64_battle_move_hammer_throw_EVS_802A10A4;
EvtScript TTYD64_battle_move_hammer_throw_EVS_HammerSupport_ReturnHome_SmashSuccess;
EvtScript TTYD64_battle_move_hammer_throw_EVS_802A1998;
EvtScript TTYD64_battle_move_hammer_throw_EVS_UseMove;
EvtScript TTYD64_battle_move_hammer_throw_EVS_UseMove_Impl;

// clang-format off
EvtScript TTYD64_battle_move_hammer_throw_EVS_802A1000 = {
    Call(TTYD64_Player_AC_802A9000)
    Exec(TTYD64_Script_NukeTracker)
    Return
    End
};

EvtScript TTYD64_battle_move_hammer_throw_EVS_802A10A4 = {
    Call(PlayerYieldTurn)
    Call(UseBattleCamPreset, 4)
    Call(MoveBattleCamOver, 5)
    Call(func_802693F0)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Wait(1)
        Goto(0)
    EndIf
    Loop(3)
        ExecWait(TTYD64_Script_TimingTutor)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Call(TTYD64_StylishAddCount, LVar0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
            Call(SetActorRotationOffset, ACTOR_PLAYER, 0, 16, 0)
            Thread
                Call(MakeLerp, 0, -180, 6, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, ACTOR_PLAYER, 0, 0, LVar0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
                Call(MakeLerp, 180, 0, 6, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, ACTOR_PLAYER, 0, 0, LVar0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
                Call(SetActorRotation, ACTOR_PLAYER, 0, 0, 0)
            EndThread
            Call(SetActorJumpGravity, ACTOR_PLAYER, Float(0.7998))
            Thread
                Exec(TTYD64_Script_InitTracker)
                Loop(8)
                    Call(TTYD64_StylishPressed, LVar0)
                    IfEq(LVar0, 1)
                        Call(TTYD64_StylishDisarm)
                        Call(TTYD64_StylishConsume)
                        Goto(1)
                    EndIf
                    Wait(1)
                EndLoop
                Loop(3)
                    ExecWait(TTYD64_Script_TimingTutor)
                    Call(TTYD64_StylishPressed, LVar0)
                    Wait(1)
                EndLoop
                Label(1)
            EndThread
            SetTimescale(Float(1.0996))
            Call(SetJumpAnimations, ACTOR_SELF, 0, 65538, 65538, 65538)
            Call(EnablePlayerBlur, 1)
            Call(PlayerHopToGoal, 15, 0, 2)
            Call(EnablePlayerBlur, 0)
            Call(SetActorRotationOffset, ACTOR_PLAYER, 0, 0, 0)
            SetTimescale(Float(1.0))
            Label(2)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 0)
                Wait(1)
                Goto(0)
            EndIf
            IfEq(LVar0, 1)
                Call(TTYD64_StylishAddCount, LVar0)
                Set(LVarA, 0)
                ExecWait(TTYD64_Script_DoStylishFX)
                Call(SetAnimation, ACTOR_PLAYER, 0, 196617)
                Wait(15)
                BreakLoop
            EndIf
        EndIf
        Wait(1)
    EndLoop
    Label(0)
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Wait(20)
    Call(EnablePlayerBlur, -1)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Wait(5)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Return
    End
};

EvtScript TTYD64_battle_move_hammer_throw_EVS_HammerSupport_ReturnHome_SmashSuccess = {
    Jump(TTYD64_battle_move_hammer_throw_EVS_802A10A4)
    Call(UseBattleCamPreset, 4)
    Call(MoveBattleCamOver, 5)
    Call(func_802693F0)
    Wait(20)
    Call(EnablePlayerBlur, -1)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Wait(5)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Return
    End
};

EvtScript TTYD64_battle_move_hammer_throw_EVS_802A1998 = {
    Add(LVarD, 6)
    Thread
        Wait(30)
        Call(TTYD64_StylishSetCount, 0)
        Exec(TTYD64_Script_InitTracker)
    EndThread
    Return
    End
};

EvtScript TTYD64_battle_move_hammer_throw_EVS_UseMove = {
    Call(ShowActionHud, 1)
    Call(TTYD64_GetStackBoost, 263, 1, LVarE, LVarF)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            Set(LVarD, 50)
            Add(LVarE, 1)
            Add(LVarF, 2)
            ExecWait(TTYD64_battle_move_hammer_throw_EVS_UseMove_Impl)
        CaseEq(1)
            Set(LVarD, 50)
            Add(LVarE, 2)
            Add(LVarF, 4)
            ExecWait(TTYD64_battle_move_hammer_throw_EVS_UseMove_Impl)
        CaseEq(2)
            Set(LVarD, 50)
            Add(LVarE, 3)
            Add(LVarF, 6)
            ExecWait(TTYD64_battle_move_hammer_throw_EVS_UseMove_Impl)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_move_hammer_throw_EVS_UseMove_Impl = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Exec(TTYD64_battle_move_hammer_throw_EVS_802A1000)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 16)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(4.0))
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(PlayerRunToGoal, 0)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            ExecWait(battle_move_hammer_throw_EVS_802A3E5C)
        CaseEq(1)
            ExecWait(battle_move_hammer_throw_EVS_802A3FE0)
        CaseEq(2)
            ExecWait(battle_move_hammer_throw_EVS_802A4164)
    EndSwitch
    Call(InitTargetIterator)
    Call(UseBattleCamPreset, 26)
    Call(AddBattleCamDist, 50)
    Call(MoveBattleCamOver, 20)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262167)
            Wait(4)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262168)
        CaseEq(1)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262173)
            Wait(4)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262174)
        CaseEq(2)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262179)
            Wait(4)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262180)
    EndSwitch
    Call(GetActionCommandMode, LVar0)
    IfGt(LVar0, 0)
        Call(battle_move_hammer_throw_ShouldMovesAutoSucceed)
        IfEq(LVar0, 0)
            Loop(45)
                Wait(1)
                Call(CheckButtonDown, 262144, LVar0)
                IfNe(LVar0, 0)
                    BreakLoop
                EndIf
            EndLoop
        EndIf
        ExecGetTID(TTYD64_battle_move_hammer_throw_EVS_802A1998, 0)
        Call(action_command_hammer_start, 0, LVarD, 3)
        Call(SetActionProgress, 0)
        Set(LVar1, 0)
        Loop(30)
            Wait(1)
            Call(GetActionProgress, LVar0)
            IfNe(LVar0, 0)
                IfNe(LVar1, 1)
                    Call(GetMenuSelection, LVar3, LVar4, LVar5)
                    Switch(LVar4)
                        CaseEq(0)
                            Call(SetAnimation, ACTOR_PLAYER, 0, 262169)
                        CaseEq(1)
                            Call(SetAnimation, ACTOR_PLAYER, 0, 262175)
                        CaseEq(2)
                            Call(SetAnimation, ACTOR_PLAYER, 0, 262181)
                    EndSwitch
                    Set(LVar1, 1)
                EndIf
            EndIf
            Call(CheckButtonDown, 262144, LVar0)
            IfEq(LVar0, 0)
                BreakLoop
            EndIf
        EndLoop
    Else
        Wait(10)
        Call(GetMenuSelection, LVar3, LVar4, LVar5)
        Switch(LVar4)
            CaseEq(0)
                Call(SetAnimation, ACTOR_PLAYER, 0, 262169)
            CaseEq(1)
                Call(SetAnimation, ACTOR_PLAYER, 0, 262175)
            CaseEq(2)
                Call(SetAnimation, ACTOR_PLAYER, 0, 262181)
        EndSwitch
        Wait(30)
    EndIf
    Call(GetActionCommandMode, LVar0)
    IfGt(LVar0, 0)
        Loop(0)
            Wait(1)
            Call(GetSmashActionQuality, LVar0)
            IfNe(LVar0, 0)
                BreakLoop
            EndIf
        EndLoop
    EndIf
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262171)
            Call(PlaySoundAtActor, ACTOR_PLAYER, 8469)
        CaseEq(1)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262177)
            Call(PlaySoundAtActor, ACTOR_PLAYER, 8470)
        CaseEq(2)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262183)
            Call(PlaySoundAtActor, ACTOR_PLAYER, 8471)
    EndSwitch
    Wait(3)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            Call(CreateVirtualEntity, LVarA, Ref(battle_move_hammer_throw_EMS_BasicHammer))
        CaseEq(1)
            Call(CreateVirtualEntity, LVarA, Ref(battle_move_hammer_throw_EMS_SuperHammer))
        CaseEq(2)
            Call(CreateVirtualEntity, LVarA, Ref(battle_move_hammer_throw_EMS_UltraHammer))
    EndSwitch
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Add(LVar1, 42)
    Add(LVar2, 5)
    Call(SetVirtualEntityPosition, LVarA, LVar0, LVar1, LVar2)
    Call(SetVirtualEntityScale, LVarA, Float(0.5996), Float(0.5996), Float(0.5996))
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetPlayerActionQuality, LVar3)
    Switch(LVar3)
        CaseGt(0)
            Thread
                Set(LVar0, 0)
                Loop(9)
                    Add(LVar0, 60)
                    Call(SetVirtualEntityRotation, LVarA, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetVirtualEntityJumpGravity, LVarA, Float(1.2998))
            Add(LVar2, 5)
            Call(VirtualEntityJumpTo, LVarA, LVar0, LVar1, LVar2, 11)
        CaseDefault
            Thread
                Set(LVar0, 0)
                Loop(18)
                    Add(LVar0, 60)
                    Call(SetVirtualEntityRotation, LVarA, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetVirtualEntityJumpGravity, LVarA, Float(0.7))
            Add(LVar2, 5)
            Call(VirtualEntityJumpTo, LVarA, LVar0, LVar1, LVar2, 20)
    EndSwitch
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Call(PlayerTestEnemy, LVar3, 268435520, 25, 0, 0, 16)
    IfEq(LVar3, 6)
        Call(VirtualEntityLandJump, LVarA)
        Call(DeleteVirtualEntity, LVarA)
        ExecWait(battle_move_hammer_throw_EVS_HammerSupport_ReturnHome_SmashMiss)
        Return
    EndIf
    Thread
        Call(GetPlayerActionQuality, LVar3)
        Switch(LVar3)
            CaseGt(0)
                Call(SetVirtualEntityJumpGravity, LVarA, Float(1.4))
                Add(LVar0, 60)
                Add(LVar1, 0)
                Call(VirtualEntityJumpTo, LVarA, LVar0, LVar1, LVar2, 10)
                Call(DeleteVirtualEntity, LVarA)
            CaseDefault
                Call(SetVirtualEntityJumpGravity, LVarA, Float(0.7998))
                Add(LVar0, 40)
                Add(LVar1, 0)
                Call(VirtualEntityJumpTo, LVarA, LVar0, LVar1, LVar2, 15)
                Call(DeleteVirtualEntity, LVarA)
        EndSwitch
    EndThread
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar1)
                CaseEq(0)
                    Call(StartRumble, 7)
                    Thread
                        Call(ShakeCam, 1, 0, 10, Float(1.2998))
                    EndThread
                CaseEq(1)
                    Call(StartRumble, 8)
                    Thread
                        Call(ShakeCam, 1, 0, 10, Float(1.5996))
                    EndThread
                CaseEq(2)
                    Call(StartRumble, 9)
                    Thread
                        Call(ShakeCam, 1, 0, 10, Float(1.9))
                    EndThread
            EndSwitch
        CaseDefault
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar1)
                CaseEq(0)
                    Call(StartRumble, 7)
                    Thread
                        Call(ShakeCam, 1, 0, 2, Float(1.2998))
                    EndThread
                CaseEq(1)
                    Call(StartRumble, 8)
                    Thread
                        Call(ShakeCam, 1, 0, 2, Float(1.5996))
                    EndThread
                CaseEq(2)
                    Call(StartRumble, 9)
                    Thread
                        Call(ShakeCam, 1, 0, 2, Float(1.9))
                    EndThread
            EndSwitch
    EndSwitch
    Call(UseBattleCamPreset, 44)
    Call(MoveBattleCamOver, 10)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            Call(PlaySoundAtActor, ACTOR_PLAYER, 8458)
        CaseEq(1)
            Call(PlaySoundAtActor, ACTOR_PLAYER, 8459)
        CaseEq(2)
            Call(PlaySoundAtActor, ACTOR_PLAYER, 8460)
    EndSwitch
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar1)
                CaseEq(0)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_NORMAL)
                CaseEq(1)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_SILENT)
                CaseEq(2)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_SILENT)
            EndSwitch
            Call(PlayerDamageEnemy, LVar0, 268697600, 25, 0, LVarF, 112)
        CaseDefault
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar1)
                CaseEq(0)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_NORMAL)
                CaseEq(1)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_SILENT)
                CaseEq(2)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_SILENT)
            EndSwitch
            Call(PlayerDamageEnemy, LVar0, 268697600, 25, 0, LVarE, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(1)
        CaseOrEq(3)
            ExecWait(TTYD64_battle_move_hammer_throw_EVS_HammerSupport_ReturnHome_SmashSuccess)
        EndCaseGroup
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(battle_move_hammer_throw_EVS_HammerSupport_ReturnHome_SmashMiss)
        EndCaseGroup
    EndSwitch
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_hammer_throw(void) {
    Mod_ReplaceScript(
        "TTYD64", &battle_move_hammer_throw_EVS_HammerSupport_ReturnHome_SmashSuccess,
        &TTYD64_battle_move_hammer_throw_EVS_HammerSupport_ReturnHome_SmashSuccess
    );
    Mod_ReplaceScript("TTYD64", &battle_move_hammer_throw_EVS_UseMove, &TTYD64_battle_move_hammer_throw_EVS_UseMove);
    Mod_ReplaceScript(
        "TTYD64", &battle_move_hammer_throw_EVS_UseMove_Impl, &TTYD64_battle_move_hammer_throw_EVS_UseMove_Impl
    );
}
