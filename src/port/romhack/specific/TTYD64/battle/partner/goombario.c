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

extern ActorBlueprint battle_partner_goombario;
extern s32 battle_partner_goombario_actionCommandTable[];
API_CALLABLE(ActorSpeak);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(EnableActorBlur);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetDistanceToGoal);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetJumpActionQuality);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartnerActionQuality);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(InterruptActionCommand);
API_CALLABLE(JumpToGoal);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(LoadItemScript);
API_CALLABLE(LoadStarPowerScript);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PartnerDamageEnemy);
API_CALLABLE(PartnerPowerBounceEnemy);
API_CALLABLE(PartnerTestEnemy);
API_CALLABLE(PartnerYieldTurn);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActionDifficultyTable);
API_CALLABLE(SetActionResult);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLookTarget);
API_CALLABLE(SetCamNoDraw);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamViewport);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToFirstTarget);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(SetNoInterpCamParams);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowActionHud);
API_CALLABLE(TTYD64_Player_partner1_Charge_GetBoosts);
API_CALLABLE(TTYD64_Player_partner1_Goombario_80238E48);
API_CALLABLE(TTYD64_Player_partner1_Goombario_8023903C);
API_CALLABLE(TTYD64_Player_partner1_Goombario_TattleCam_Start);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(action_command_jump_init);
API_CALLABLE(action_command_jump_start);
API_CALLABLE(battle_partner_goombario_AdjustMultibonkChance);
API_CALLABLE(battle_partner_goombario_GetReturnMoveTime);
API_CALLABLE(battle_partner_goombario_GetTattleCamPos);
API_CALLABLE(battle_partner_goombario_GetTattleMessage);
API_CALLABLE(battle_partner_goombario_JumpOnTarget);
API_CALLABLE(battle_partner_goombario_OnMissHeadbonk);
EvtScript TTYD64_battle_partner_goombario_EVS_80238000;
EvtScript TTYD64_battle_partner_goombario_EVS_80238710;
EvtScript TTYD64_battle_partner_goombario_EVS_80238B38;
EvtScript TTYD64_battle_partner_goombario_EVS_80238E94;
EvtScript TTYD64_battle_partner_goombario_EVS_80239100;
extern ActorBlueprint TTYD64_battle_partner_goombario;
EvtScript TTYD64_battle_partner_goombario_EVS_802392F0;
EvtScript TTYD64_battle_partner_goombario_EVS_8023997C;
EvtScript TTYD64_battle_partner_goombario_EVS_80239D98;
EvtScript TTYD64_battle_partner_goombario_EVS_8023A634;
EvtScript TTYD64_battle_partner_goombario_EVS_8023A71C;
extern s32 TTYD64_battle_partner_goombario_StatusTable_Goombario_802391F8[];
EvtScript TTYD64_battle_partner_goombario_EVS_8023AA58;
EvtScript TTYD64_battle_partner_goombario_EVS_8023AC78;
EvtScript TTYD64_battle_partner_goombario_EVS_8023ACD8;
extern s32 TTYD64_battle_partner_goombario_IdleAnimations_Goombario_802391B0[];
EvtScript TTYD64_battle_partner_goombario_EVS_8023AE84;
extern ActorPartBlueprint TTYD64_battle_partner_goombario_PartsTable_Goombario_802392A4[];
EvtScript TTYD64_battle_partner_goombario_EVS_8023AF3C;
EvtScript TTYD64_battle_partner_goombario_EVS_8023AF4C;
extern s32 TTYD64_battle_partner_goombario_DefenseTable_Goombario_802391EC[];
EvtScript TTYD64_battle_partner_goombario_EVS_8023BB9C;
EvtScript TTYD64_battle_partner_goombario_EVS_8023C57C;
EvtScript TTYD64_battle_partner_goombario_EVS_8023D63C;
EvtScript TTYD64_battle_partner_goombario_EVS_8023DB14;
EvtScript TTYD64_battle_partner_goombario_EVS_8023DE74;

// clang-format off
ActorBlueprint TTYD64_battle_partner_goombario = {
    .flags = 0,
    .type = 111,
    .level = 0,
    .maxHP = 99,
    .partCount = 1,
    .unk_0A = { 0, 0 },
    .partsData = TTYD64_battle_partner_goombario_PartsTable_Goombario_802392A4,
    .initScript = &TTYD64_battle_partner_goombario_EVS_8023AC78,
    .statusTable = TTYD64_battle_partner_goombario_StatusTable_Goombario_802391F8,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 29, 26 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

s32 TTYD64_battle_partner_goombario_StatusTable_Goombario_802391F8[] = {
    1, 100, 2, 100, 6, 100, 9, 100,
    7, 100, 4, 100, 3, 100, 11, 100,
    5, 100, 10, 100, 8, 100, 31, 0,
    32, 0, 37, 0, 34, 0, 36, 0,
    35, 0, 33, 0, 38, 0, 39, 0,
    41, 0, 0,
};

s32 TTYD64_battle_partner_goombario_IdleAnimations_Goombario_802391B0[] = {
    1, 589826, 12, 589824, 6, 589845, 9, 589846,
    8, 589824, 4, 589844, 13, 589844, 18, 589824,
    26, 589846, 7, 589824, 48, 589838, 0,
};

ActorPartBlueprint TTYD64_battle_partner_goombario_PartsTable_Goombario_802392A4[] = {
    {
        .flags = 0,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 8, 22 },
        .opacity = 255,
        .idleAnimations = TTYD64_battle_partner_goombario_IdleAnimations_Goombario_802391B0,
        .defenseTable = TTYD64_battle_partner_goombario_DefenseTable_Goombario_802391EC,
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
        .unk_1E = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_battle_partner_goombario_DefenseTable_Goombario_802391EC[] = {
    1, 0, 0,
};

EvtScript TTYD64_battle_partner_goombario_EVS_80238000 = {
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Call(action_command_jump_init)
    Exec(TTYD64_Script_NukeTracker)
    ExecWait(TTYD64_battle_partner_goombario_EVS_8023997C)
    ExecWait(TTYD64_battle_partner_goombario_EVS_8023A634)
    Call(SetAnimation, ACTOR_SELF, 1, 589831)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 18, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 19, 0)
    Wait(1)
    Call(UseBattleCamPreset, 52)
    Call(action_command_jump_start, LVarA, 3)
    Call(UseBattleCamPreset, 52)
    Call(SetAnimation, ACTOR_SELF, 1, 589830)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 9, 0)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(SetJumpAnimations, ACTOR_PARTNER, 0, 589830, 589830, 589830)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8205)
    Call(battle_partner_goombario_JumpOnTarget, LVarA, 0)
    Call(PartnerTestEnemy, LVar0, 128, 20, 0, 1, 16)
    IfEq(LVar0, 6)
        Call(SetJumpAnimations, ACTOR_PARTNER, 0, 589830, 589830, 589830)
        Call(battle_partner_goombario_OnMissHeadbonk)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(1.0))
        EndThread
        Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_TRIP)
        Wait(20)
        ExecWait(TTYD64_battle_partner_goombario_EVS_80238B38)
        Return
    EndIf
    ChildThread
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0996), Float(0.7998), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.2998), Float(0.5), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    EndChildThread
    Wait(1)
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Set(LVar0, 3)
            Call(PartnerDamageEnemy, LVar0, 128, 0, 0, LVar0, 80)
        CaseDefault
            Set(LVar0, 3)
            Call(PartnerDamageEnemy, LVar0, 128, 0, 0, LVar0, 48)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_partner_goombario_EVS_80238B38)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
        EndCaseGroup
    EndSwitch
    Thread
        Call(UseBattleCamPreset, 50)
        Wait(5)
        Call(SetGoalToTarget, ACTOR_PARTNER)
        Call(UseBattleCamPreset, 53)
    EndThread
    Call(GetJumpActionQuality, LVarF)
    Call(InterruptActionCommand)
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Call(action_command_jump_init)
    Call(ShowActionHud, 0)
    Call(action_command_jump_start, 24, 3)
    Set(LVarA, 24)
    Thread
        Wait(4)
        Set(LVar0, 0)
        Loop(6)
            Add(LVar0, -30)
            Call(SetActorRotation, ACTOR_SELF, 0, -250000000, LVar0)
            Wait(1)
        EndLoop
        Call(SetAnimation, ACTOR_SELF, 1, 589830)
    EndThread
    Thread
        Set(LVar0, 0)
        Loop(LVarA)
            Add(LVar0, 133)
            Call(SetActorRotation, ACTOR_SELF, -250000000, LVar0, -250000000)
            Wait(1)
        EndLoop
    EndThread
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(EnableActorBlur, ACTOR_PARTNER, 1)
    Call(SetJumpAnimations, ACTOR_PARTNER, 0, 589830, 589830, 589830)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_GOOMBARIO_HEADBONK)
    Call(battle_partner_goombario_JumpOnTarget, LVarA, 3)
    Call(EnableActorBlur, ACTOR_PARTNER, -1)
    ChildThread
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0996), Float(0.7998), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.2998), Float(0.5), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    EndChildThread
    Wait(1)
    Call(TTYD64_Player_partner1_Charge_GetBoosts)
    Add(LVar0, 3)
    Call(PartnerDamageEnemy, LVar0, 128, 0, 0, LVar0, 32)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Call(SetActionResult, LVarF)
    ExecWait(TTYD64_battle_partner_goombario_EVS_8023D63C)
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_80238710 = {
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Wait(1)
        Goto(0)
    EndIf
    Exec(TTYD64_Script_InitTracker)
    Loop(3)
        ExecWait(TTYD64_Script_TimingTutor)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Call(TTYD64_StylishAddCount, LVar0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 25)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 22, 0)
            Thread
                Call(MakeLerp, 0, 180, 5, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
                Call(MakeLerp, -180, 0, 5, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -7, 0)
            Call(JumpToGoal, ACTOR_SELF, 12, false, false, true)
            Wait(5)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Label(0)
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_80238B38 = {
    Call(PartnerYieldTurn)
    Call(UseBattleCamPreset, 51)
    Call(SetAnimation, ACTOR_PARTNER, -1, 589825)
    Thread
        Wait(4)
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
        Set(LVar0, 180)
        Loop(3)
            Add(LVar0, 60)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
    EndThread
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Sub(LVar0, 30)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.2))
    Call(battle_partner_goombario_GetReturnMoveTime)
    Call(JumpToGoal, ACTOR_PARTNER, LVar0, false, true, false)
    Call(SetAnimation, ACTOR_SELF, 1, 589831)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 18, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 19, 0)
    Wait(1)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 589825)
    Call(AddGoalPos, ACTOR_PARTNER, -10, 0, 0)
    Call(JumpToGoal, ACTOR_PARTNER, 6, false, false, true)
    Call(SetAnimation, ACTOR_PARTNER, -1, 589825)
    Call(SetAnimation, ACTOR_SELF, 1, 589831)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 18, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 19, 0)
    Wait(1)
    Call(SetAnimation, ACTOR_SELF, 1, 589825)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Jump(TTYD64_Script_DoStylish_Multibonk)
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_80238E94 = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(10)
            IfEq(GameFlag(1817), 0)
                Call(UseIdleAnimation, ACTOR_PARTNER, false)
                Call(UseBattleCamPreset, 14)
                Call(BattleCamTargetActor, ACTOR_SELF)
                Call(MoveBattleCamOver, 20)
                Wait(10)
                Call(SetActorYaw, ACTOR_PLAYER, 30)
                Wait(1)
                Call(SetActorYaw, ACTOR_PLAYER, 60)
                Wait(1)
                Call(SetActorYaw, ACTOR_PLAYER, 90)
                Wait(1)
                Call(SetActorYaw, ACTOR_PLAYER, 120)
                Wait(1)
                Call(SetActorYaw, ACTOR_PLAYER, 150)
                Wait(1)
                Call(SetActorYaw, ACTOR_PLAYER, 180)
                Wait(5)
                Call(ActorSpeak, 721082, 256, 0, 589839, 589825)
                Call(SetActorYaw, ACTOR_PLAYER, 150)
                Wait(1)
                Call(SetActorYaw, ACTOR_PLAYER, 120)
                Wait(1)
                Call(SetActorYaw, ACTOR_PLAYER, 90)
                Wait(1)
                Call(SetActorYaw, ACTOR_PLAYER, 60)
                Wait(1)
                Call(SetActorYaw, ACTOR_PLAYER, 30)
                Wait(1)
                Call(SetActorYaw, ACTOR_PLAYER, 0)
                Wait(5)
                Set(GameFlag(1817), 1)
                Call(UseIdleAnimation, ACTOR_PARTNER, true)
            EndIf
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_80239100 = {
    Call(SetGoalToFirstTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(GetGoalPos, ACTOR_PARTNER, LVar3, LVar4, LVar5)
    Sub(LVar3, Float(70.0))
    IfLt(LVar0, LVar3)
        Set(LVar3, LVar0)
    EndIf
    Call(SetGoalPos, ACTOR_PARTNER, LVar3, LVar4, LVar5)
    Call(UseBattleCamPreset, 47)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(5.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 589827)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 589825)
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_802392F0 = {
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Call(action_command_jump_init)
    Exec(TTYD64_Script_NukeTracker)
    ExecWait(TTYD64_battle_partner_goombario_EVS_8023997C)
    ExecWait(TTYD64_battle_partner_goombario_EVS_8023A634)
    Call(SetAnimation, ACTOR_SELF, 1, 589831)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 18, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 19, 0)
    Wait(1)
    Call(UseBattleCamPreset, 52)
    Call(action_command_jump_start, LVarA, 3)
    Call(UseBattleCamPreset, 52)
    Call(SetAnimation, ACTOR_SELF, 1, 589830)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 9, 0)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(SetJumpAnimations, ACTOR_PARTNER, 0, 589830, 589830, 589830)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8205)
    Call(battle_partner_goombario_JumpOnTarget, LVarA, 0)
    Call(PartnerTestEnemy, LVar0, 128, 20, 0, 1, 16)
    IfEq(LVar0, 6)
        Call(SetJumpAnimations, ACTOR_PARTNER, 0, 589830, 589830, 589830)
        Call(battle_partner_goombario_OnMissHeadbonk)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(1.0))
        EndThread
        Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_TRIP)
        Wait(20)
        ExecWait(TTYD64_battle_partner_goombario_EVS_80238B38)
        Return
    EndIf
    ChildThread
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0996), Float(0.7998), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.2998), Float(0.5), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    EndChildThread
    Wait(1)
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Set(LVar0, 2)
            Call(PartnerDamageEnemy, LVar0, 128, 0, 0, LVar0, 80)
        CaseDefault
            Set(LVar0, 2)
            Call(PartnerDamageEnemy, LVar0, 128, 0, 0, LVar0, 48)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_partner_goombario_EVS_80238B38)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
        EndCaseGroup
    EndSwitch
    Thread
        Call(UseBattleCamPreset, 50)
        Wait(5)
        Call(SetGoalToTarget, ACTOR_PARTNER)
        Call(UseBattleCamPreset, 53)
    EndThread
    Call(GetJumpActionQuality, LVarF)
    Call(InterruptActionCommand)
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Call(action_command_jump_init)
    Call(ShowActionHud, 0)
    Call(action_command_jump_start, 24, 3)
    Set(LVarA, 24)
    Thread
        Wait(4)
        Set(LVar0, 0)
        Loop(6)
            Add(LVar0, -30)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(EnableActorBlur, ACTOR_PARTNER, 1)
    Call(SetJumpAnimations, ACTOR_PARTNER, 0, 589830, 589830, 589830)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_GOOMBARIO_HEADBONK)
    Call(battle_partner_goombario_JumpOnTarget, LVarA, 3)
    Call(EnableActorBlur, ACTOR_PARTNER, -1)
    ChildThread
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0996), Float(0.7998), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.2998), Float(0.5), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    EndChildThread
    Wait(1)
    Call(TTYD64_Player_partner1_Charge_GetBoosts)
    Add(LVar0, 2)
    Call(PartnerDamageEnemy, LVar0, 128, 0, 0, LVar0, 32)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Call(SetActionResult, LVarF)
    ExecWait(TTYD64_battle_partner_goombario_EVS_8023D63C)
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_8023997C = {
    Call(SetGoalToFirstTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(GetGoalPos, ACTOR_PARTNER, LVar3, LVar4, LVar5)
    Sub(LVar3, Float(70.0))
    IfLt(LVar0, LVar3)
        Set(LVar3, LVar0)
    EndIf
    Call(SetGoalPos, ACTOR_PARTNER, LVar3, LVar4, LVar5)
    Call(UseBattleCamPreset, 47)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(5.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 589827)
    Thread
        Wait(2)
        Call(TTYD64_StylishSetCount, 0)
        Exec(TTYD64_Script_InitTracker)
        Loop(0)
            Call(GetDistanceToGoal, ACTOR_SELF, LVarA)
            IfLt(LVarA, 20)
                Call(TTYD64_StylishPressed, LVar0)
                IfEq(LVar0, 1)
                    Wait(1)
                    Call(TTYD64_StylishDisarm)
                    Call(TTYD64_StylishConsume)
                    Goto(0)
                Else
                    BreakLoop
                EndIf
            EndIf
            Wait(1)
        EndLoop
        Loop(2)
            ExecWait(TTYD64_Script_TimingTutor)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Label(0)
    EndThread
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 589825)
    Label(1)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Call(TTYD64_StylishAddCount, LVar0)
        Set(LVarA, 0)
        ExecWait(TTYD64_Script_DoStylishFX)
        Call(SetAnimation, ACTOR_PARTNER, -1, 589840)
        Wait(20)
    EndIf
    Label(2)
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_80239D98 = {
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(InterruptActionCommand)
    Call(GetLastEvent, ACTOR_PARTNER, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, -1)
            Set(LVar1, 589834)
            ExecWait(EVS_Enemy_Hit)
            Call(SetAnimation, ACTOR_PARTNER, -1, 589825)
        EndCaseGroup
        CaseOrEq(23)
        CaseOrEq(25)
            ExecWait(TTYD64_Script_Goombario_HandleEvent_Immune)
        EndCaseGroup
        CaseEq(42)
            SetConst(LVar1, 589834)
            Set(LVar2, 12)
            ExecWait(EVS_Partner_SpikeContact)
        CaseEq(44)
            SetConst(LVar1, 589835)
            Set(LVar2, 12)
            SetConst(LVar3, 589836)
            ExecWait(EVS_Partner_BurnContact)
        CaseEq(14)
            SetConst(LVar1, 589835)
            SetConst(LVar2, 589836)
            ExecWait(EVS_Partner_BurnHit)
        CaseEq(47)
            SetConst(LVar1, 589834)
            Set(LVar2, 12)
            ExecWait(EVS_Partner_ShockHit)
        CaseEq(51)
            Call(TTYD64_Player_partner1_Goombario_8023903C)
        CaseEq(52)
            SetConst(LVar0, 1)
            SetConst(LVar1, 589825)
            SetConst(LVar2, 589827)
            Set(LVar3, 0)
            ExecWait(EVS_Partner_Recover)
        CaseOrEq(24)
        CaseOrEq(26)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8332)
            SetConst(LVar0, 1)
            SetConst(LVar1, 589838)
            ExecWait(EVS_Enemy_NoDamageHit)
            Wait(10)
        EndCaseGroup
        CaseEq(32)
            Set(LVar0, -1)
            Set(LVar1, 589834)
            ExecWait(TTYD64_PartnerDies)
            Return
        CaseEq(TTYD64_EVENT_SUPERGUARD)
            Set(LVar0, -1)
            Set(LVar1, 589828)
            ExecWait(TTYD64_DoSuperguard)
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_8023A634 = {
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(GetGoalPos, ACTOR_PARTNER, LVarB, LVar7, LVarD)
    Call(GetActorPos, ACTOR_PARTNER, LVar7, LVarD, LVarE)
    IfGt(LVarB, LVar7)
        Sub(LVarB, LVar7)
    Else
        Sub(LVar7, LVarB)
        Set(LVarB, LVar7)
    EndIf
    Sub(LVarB, 20)
    DivF(LVarB, Float(10.5889))
    AddF(LVarB, 15)
    Set(LVarA, LVarB)
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_8023A71C = {
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(6.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 589827)
    Call(SetActorYaw, ACTOR_PARTNER, 0)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 589825)
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_8023AA58 = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(1)
            ExecWait(TTYD64_battle_partner_goombario_EVS_8023AF3C)
        CaseEq(0)
            ExecWait(TTYD64_battle_partner_goombario_EVS_8023DE74)
        CaseEq(5)
            ExecWait(TTYD64_battle_partner_goombario_EVS_8023ACD8)
        CaseEq(3)
            ExecWait(TTYD64_battle_partner_goombario_EVS_8023AE84)
        CaseEq(7)
            ExecWait(TTYD64_battle_partner_goombario_EVS_8023A71C)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_8023AC78 = {
    Call(BindTakeTurn, ACTOR_PARTNER, Ref(TTYD64_battle_partner_goombario_EVS_8023AA58))
    Call(BindIdle, ACTOR_PARTNER, Ref(TTYD64_battle_partner_goombario_EVS_8023AF4C))
    Call(BindHandleEvent, ACTOR_PARTNER, Ref(TTYD64_battle_partner_goombario_EVS_80239D98))
    Call(BindHandlePhase, ACTOR_PARTNER, Ref(TTYD64_battle_partner_goombario_EVS_80238E94))
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_8023ACD8 = {
    SetConst(LVar0, 1)
    SetConst(LVar1, 589840)
    SetConst(LVar2, 589841)
    SetConst(LVar3, 589825)
    ExecWait(EVS_Partner_Celebrate)
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_8023AE84 = {
    SetConst(LVar0, 1)
    SetConst(LVar1, 589827)
    ExecWait(EVS_Partner_RunAway)
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_8023AF3C = {
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_8023AF4C = {
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_8023BB9C = {
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Call(action_command_jump_init)
    ExecWait(TTYD64_battle_partner_goombario_EVS_80239100)
    ExecWait(TTYD64_battle_partner_goombario_EVS_8023A634)
    Call(SetAnimation, ACTOR_SELF, 1, 589831)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 18, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 19, 0)
    Wait(1)
    Call(UseBattleCamPreset, 52)
    Call(action_command_jump_start, LVarA, 1)
    Call(UseBattleCamPreset, 52)
    Call(SetAnimation, ACTOR_SELF, 1, 589830)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 9, 0)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(SetJumpAnimations, ACTOR_PARTNER, 0, 589830, 589830, 589830)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8205)
    Call(battle_partner_goombario_JumpOnTarget, LVarA, 0)
    Call(PartnerTestEnemy, LVar0, 1048704, 20, 0, 1, 16)
    IfEq(LVar0, 6)
        Call(SetJumpAnimations, ACTOR_PARTNER, 0, 589830, 589830, 589830)
        Call(battle_partner_goombario_OnMissHeadbonk)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(1.0))
        EndThread
        Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_TRIP)
        Wait(20)
        ExecWait(TTYD64_battle_partner_goombario_EVS_80238B38)
        Return
    EndIf
    ChildThread
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0996), Float(0.7998), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.2998), Float(0.5), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    EndChildThread
    Wait(1)
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(TTYD64_Function_Multibonk_GetAmountToDeal, LVar0)
            Call(PartnerDamageEnemy, LVar0, 1048704, 0, 0, LVar0, 80)
        CaseDefault
            Call(TTYD64_Function_Multibonk_GetAmountToDeal, LVar0)
            Call(PartnerDamageEnemy, LVar0, 1048704, 0, 0, LVar0, 48)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_partner_goombario_EVS_80238B38)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
        EndCaseGroup
    EndSwitch
    Thread
        Call(UseBattleCamPreset, 50)
        Wait(5)
        Call(SetGoalToTarget, ACTOR_PARTNER)
        Call(UseBattleCamPreset, 53)
    EndThread
    Call(GetJumpActionQuality, LVarE)
    Set(LVarD, 0)
    Set(LVarF, 0)
    Set(LFlag0, 0)
    Label(10)
    Thread
        Call(UseBattleCamPreset, 50)
        Wait(5)
        Call(SetGoalToTarget, ACTOR_PARTNER)
        Call(UseBattleCamPreset, 53)
    EndThread
    Call(InterruptActionCommand)
    Call(SetActionDifficultyTable, Ref(battle_partner_goombario_actionCommandTable))
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
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
    Thread
        Wait(4)
        Set(LVar0, 0)
        Loop(6)
            Add(LVar0, -30)
            Call(SetActorRotation, ACTOR_SELF, 0, -250000000, LVar0)
            Wait(1)
        EndLoop
        Call(SetAnimation, ACTOR_SELF, 1, 589830)
    EndThread
    Thread
        Set(LVar0, 0)
        Loop(LVarA)
            Add(LVar0, 133)
            Call(SetActorRotation, ACTOR_SELF, -250000000, LVar0, -250000000)
            Wait(1)
        EndLoop
    EndThread
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(EnableActorBlur, ACTOR_PARTNER, 1)
    Call(SetJumpAnimations, ACTOR_PARTNER, 0, 589830, 589830, 589830)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_GOOMBARIO_HEADBONK)
    Call(battle_partner_goombario_JumpOnTarget, LVarA, 3)
    Call(EnableActorBlur, ACTOR_PARTNER, -1)
    Sub(LVarD, 1)
    Call(battle_partner_goombario_AdjustMultibonkChance)
    IfGe(LVarF, LVar0)
        Set(LFlag0, 1)
    EndIf
    ChildThread
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0996), Float(0.7998), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.2998), Float(0.5), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    EndChildThread
    Wait(1)
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            IfEq(LFlag0, 0)
                Call(TTYD64_Function_Multibonk_GetAmountToDeal, LVar0)
                Call(PartnerPowerBounceEnemy, LVar0, 1048704, 0, 0, LVar0, LVarD, 64)
            Else
                Call(TTYD64_Function_Multibonk_GetAmountToDeal, LVar0)
                Call(PartnerPowerBounceEnemy, LVar0, 1048704, 0, 0, LVar0, LVarD, 32)
            EndIf
        CaseDefault
            Call(TTYD64_Function_Multibonk_GetAmountToDeal, LVar0)
            Call(PartnerPowerBounceEnemy, LVar0, 1048704, 0, 0, LVar0, LVarD, 32)
            Set(LFlag0, 0)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Call(SetActionResult, LVarE)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_partner_goombario_EVS_80238B38)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
            IfEq(LFlag0, 1)
                ExecWait(TTYD64_battle_partner_goombario_EVS_8023D63C)
                Return
            EndIf
        EndCaseGroup
    EndSwitch
    Add(LVarF, 1)
    Goto(10)
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_8023C57C = {
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Call(action_command_jump_init)
    Exec(TTYD64_Script_NukeTracker)
    ExecWait(TTYD64_battle_partner_goombario_EVS_8023997C)
    ExecWait(TTYD64_battle_partner_goombario_EVS_8023A634)
    Call(SetAnimation, ACTOR_SELF, 1, 589831)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 18, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 19, 0)
    Wait(1)
    Call(UseBattleCamPreset, 52)
    Call(action_command_jump_start, LVarA, 3)
    Call(UseBattleCamPreset, 52)
    Call(SetAnimation, ACTOR_SELF, 1, 589830)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 9, 0)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(SetJumpAnimations, ACTOR_PARTNER, 0, 589830, 589830, 589830)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8205)
    Call(battle_partner_goombario_JumpOnTarget, LVarA, 0)
    Call(PartnerTestEnemy, LVar0, 128, 20, 0, 1, 16)
    IfEq(LVar0, 6)
        Call(SetJumpAnimations, ACTOR_PARTNER, 0, 589830, 589830, 589830)
        Call(battle_partner_goombario_OnMissHeadbonk)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(1.0))
        EndThread
        Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_TRIP)
        Wait(20)
        ExecWait(TTYD64_battle_partner_goombario_EVS_80238B38)
        Return
    EndIf
    ChildThread
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0996), Float(0.7998), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.2998), Float(0.5), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    EndChildThread
    Wait(1)
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Set(LVar0, 1)
            Call(PartnerDamageEnemy, LVar0, 128, 0, 0, LVar0, 80)
        CaseDefault
            Set(LVar0, 1)
            Call(PartnerDamageEnemy, LVar0, 128, 0, 0, LVar0, 48)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_partner_goombario_EVS_80238B38)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
        EndCaseGroup
    EndSwitch
    Thread
        Call(UseBattleCamPreset, 50)
        Wait(5)
        Call(SetGoalToTarget, ACTOR_PARTNER)
        Call(UseBattleCamPreset, 53)
    EndThread
    Call(GetJumpActionQuality, LVarF)
    Call(InterruptActionCommand)
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Call(action_command_jump_init)
    Call(ShowActionHud, 0)
    Call(action_command_jump_start, 24, 3)
    Set(LVarA, 24)
    Thread
        Wait(4)
        Set(LVar0, 0)
        Loop(6)
            Add(LVar0, -30)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(SetJumpAnimations, ACTOR_PARTNER, 0, 589830, 589830, 589830)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_GOOMBARIO_HEADBONK)
    Call(battle_partner_goombario_JumpOnTarget, LVarA, 3)
    ChildThread
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0996), Float(0.7998), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.2998), Float(0.5), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    EndChildThread
    Wait(1)
    Call(TTYD64_Player_partner1_Charge_GetBoosts)
    Add(LVar0, 1)
    Call(PartnerDamageEnemy, LVar0, 128, 0, 0, LVar0, 32)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Call(SetActionResult, LVarF)
    ExecWait(TTYD64_battle_partner_goombario_EVS_8023D63C)
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_8023D63C = {
    Call(PartnerYieldTurn)
    Call(UseBattleCamPreset, 3)
    Exec(TTYD64_Script_InitTracker)
    Call(SetAnimation, ACTOR_PARTNER, -1, 589825)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar0, 60)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.4))
    Call(battle_partner_goombario_GetReturnMoveTime)
    Thread
        Wait(4)
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
        Sub(LVar0, 4)
        Set(LVar1, LVar0)
        Div(LVar1, 3)
        IfLt(LVar1, 1)
            Set(LVar1, 1)
        EndIf
        Set(LVar2, LVar1)
        Mod(LVar2, 2)
        IfEq(LVar2, 0)
            Sub(LVar1, 1)
        EndIf
        Set(LVar0, 180)
        Loop(LVar1)
            Loop(3)
                Add(LVar0, 60)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                Wait(1)
            EndLoop
        EndLoop
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
    EndThread
    Call(JumpToGoal, ACTOR_PARTNER, LVar0, false, true, false)
    Call(SetAnimation, ACTOR_SELF, 1, 589831)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 18, 0)
    Wait(1)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 589825)
    Call(AddGoalPos, ACTOR_PARTNER, -20, 0, 0)
    Call(JumpToGoal, ACTOR_PARTNER, 6, false, false, true)
    Call(SetAnimation, ACTOR_SELF, 1, 589831)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 18, 0)
    Wait(1)
    Call(AddGoalPos, ACTOR_PARTNER, -10, 0, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 589825)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(JumpToGoal, ACTOR_PARTNER, 4, false, false, true)
    Call(SetAnimation, ACTOR_SELF, 1, 589831)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 18, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 589825)
    ExecWait(TTYD64_battle_partner_goombario_EVS_80238710)
    Wait(2)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(8.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 589827)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 589825)
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_8023DB14 = {
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(6.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 589827)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_PARTNER, 0, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 589825)
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(SetBattleFlagBits, BS_FLAGS1_TATTLE_OPEN, 1)
    Call(TTYD64_Player_partner1_Goombario_TattleCam_Start)
    ExecWait(TTYD64_Script_Tattle_DoStylish)
    Wait(12)
    Call(SetCamEnabled, 2, 1)
    Call(SetCamNoDraw, 2, 0)
    Call(SetCamPerspective, 2, 6, 25, 16, 1024)
    Call(SetCamViewport, 2, 137, 95, 138, 99)
    Call(GetOwnerTarget, LVarA, LVarB)
    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(battle_partner_goombario_GetTattleCamPos)
    Wait(1)
    Call(SetCamLookTarget, 2, LVar0, LVar1, LVar2)
    Call(SetNoInterpCamParams, 2, 0, LVar3, 100, 4)
    Wait(2)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_TATTLE_WINDOW_OPEN)
    Call(SetCamNoDraw, 2, 1)
    Wait(10)
    Call(battle_partner_goombario_GetTattleMessage)
    Call(ActorSpeak, LVar0, ACTOR_SELF, 1, 589839, 589825)
    Call(TTYD64_Player_partner1_Goombario_80238E48)
    Wait(12)
    Call(SetCamEnabled, 2, 0)
    Wait(32)
    Call(UseBattleCamPreset, 2)
    Call(SetBattleFlagBits, BS_FLAGS1_TATTLE_OPEN, 0)
    Call(PartnerYieldTurn)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(4.0))
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.7998))
    Call(SetAnimation, ACTOR_PARTNER, -1, 589827)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 589825)
    Return
    End
};

EvtScript TTYD64_battle_partner_goombario_EVS_8023DE74 = {
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Call(ShowActionHud, 1)
    Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
    Switch(LVar0)
        CaseEq(8)
            Call(LoadStarPowerScript)
            ExecWait(LVar0)
            Return
        CaseEq(2)
            Call(LoadItemScript)
            ExecWait(LVar0)
            Return
    EndSwitch
    Switch(LVar2)
        CaseEq(131)
            ExecWait(TTYD64_battle_partner_goombario_EVS_8023C57C)
        CaseEq(132)
            ExecWait(TTYD64_battle_partner_goombario_EVS_802392F0)
        CaseEq(133)
            ExecWait(TTYD64_battle_partner_goombario_EVS_80238000)
        CaseEq(134)
            ExecWait(TTYD64_battle_partner_goombario_EVS_8023DB14)
        CaseEq(135)
            ExecWait(TTYD64_battle_partner_goombario_EVS_8023BB9C)
        CaseEq(136)
            ExecWait(TTYD64_Script_Goombario_Init_Ponder)
    EndSwitch
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_partner_goombario(void) {
    Mod_ReplaceActorBlueprint("TTYD64", &battle_partner_goombario, &TTYD64_battle_partner_goombario);
}
