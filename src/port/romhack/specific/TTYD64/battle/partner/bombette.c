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

extern ActorBlueprint battle_partner_bombette;
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(CheckButtonDown);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(FlyToGoal);
API_CALLABLE(GetActorLevel);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetMashActionQuality);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetPartnerActionQuality);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(InterruptActionCommand);
API_CALLABLE(JumpToGoal);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(LoadItemScript);
API_CALLABLE(LoadStarPowerScript);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PartnerDamageEnemy);
API_CALLABLE(PartnerTestEnemy);
API_CALLABLE(PartnerYieldTurn);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(ResetActorSounds);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(SetupMashMeter);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowActionHud);
API_CALLABLE(ShowShockEffect);
API_CALLABLE(StartRumble);
API_CALLABLE(StopSound);
API_CALLABLE(TTYD64_Player_AC_802A9000);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseBattleCamPresetImmediately);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(action_command_body_slam_start);
API_CALLABLE(action_command_bomb_start);
API_CALLABLE(battle_partner_bombette_GetBombDamage);
API_CALLABLE(battle_partner_bombette_GetMegaBombDamage);
API_CALLABLE(battle_partner_bombette_GetPowerBombDamage);
API_CALLABLE(battle_partner_bombette_PlayExplosionFX);
API_CALLABLE(battle_partner_kooper_SlowDown);
EvtScript TTYD64_battle_partner_bombette_EVS_80238000;
EvtScript TTYD64_battle_partner_bombette_EVS_802386DC;
extern ActorBlueprint TTYD64_battle_partner_bombette;
EvtScript TTYD64_battle_partner_bombette_EVS_80238780;
EvtScript TTYD64_battle_partner_bombette_EVS_80239DF8;
EvtScript TTYD64_battle_partner_bombette_EVS_8023B0FC;
EvtScript TTYD64_battle_partner_bombette_EVS_8023BD2C;
EvtScript TTYD64_battle_partner_bombette_EVS_8023C058;
EvtScript TTYD64_battle_partner_bombette_EVS_8023C5AC;
EvtScript TTYD64_battle_partner_bombette_EVS_8023CA6C;
EvtScript TTYD64_battle_partner_bombette_EVS_8023CB50;
extern s32 TTYD64_battle_partner_bombette_StatusTable_Bombette_80238688[];
EvtScript TTYD64_battle_partner_bombette_EVS_8023CD50;
EvtScript TTYD64_battle_partner_bombette_EVS_8023CDDC;
EvtScript TTYD64_battle_partner_bombette_EVS_8023CE60;
EvtScript TTYD64_battle_partner_bombette_EVS_8023CEC0;
extern s32 TTYD64_battle_partner_bombette_IdleAnimations_Bombette_80238640[];
EvtScript TTYD64_battle_partner_bombette_EVS_8023CF78;
EvtScript TTYD64_battle_partner_bombette_EVS_8023CFB4;
EvtScript TTYD64_battle_partner_bombette_EVS_8023CFF0;
extern ActorPartBlueprint TTYD64_battle_partner_bombette_PartsTable_Bombette_80238734[];
EvtScript TTYD64_battle_partner_bombette_EVS_8023D03C;
EvtScript TTYD64_battle_partner_bombette_EVS_8023D04C;
extern s32 TTYD64_battle_partner_bombette_DefenseTable_Bombette_8023867C[];

// clang-format off
ActorBlueprint TTYD64_battle_partner_bombette = {
    .flags = 0,
    .type = 113,
    .level = 0,
    .maxHP = 99,
    .partCount = 1,
    .unk_0A = { 0, 0 },
    .partsData = TTYD64_battle_partner_bombette_PartsTable_Bombette_80238734,
    .initScript = &TTYD64_battle_partner_bombette_EVS_8023CE60,
    .statusTable = TTYD64_battle_partner_bombette_StatusTable_Bombette_80238688,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 30, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

s32 TTYD64_battle_partner_bombette_StatusTable_Bombette_80238688[] = {
    1, 100, 2, 100, 6, 100, 9, 100,
    7, 100, 4, 100, 3, 100, 11, 100,
    5, 100, 10, 100, 8, 100, 31, 0,
    32, 0, 37, 0, 34, 0, 36, 0,
    35, 0, 33, 0, 38, 0, 39, 0,
    41, 0, 0,
};

s32 TTYD64_battle_partner_bombette_IdleAnimations_Bombette_80238640[] = {
    1, 720902, 12, 720896, 6, 720927, 9, 720928,
    8, 720896, 4, 720926, 13, 720926, 18, 720896,
    26, 720928, 7, 720896, 48, 720910, 0,
};

ActorPartBlueprint TTYD64_battle_partner_bombette_PartsTable_Bombette_80238734[] = {
    {
        .flags = 0,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 9, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_battle_partner_bombette_IdleAnimations_Bombette_80238640,
        .defenseTable = TTYD64_battle_partner_bombette_DefenseTable_Bombette_8023867C,
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
        .unk_1E = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_battle_partner_bombette_DefenseTable_Bombette_8023867C[] = {
    1, 0, 0,
};

EvtScript TTYD64_battle_partner_bombette_EVS_80238000 = {
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(AddGoalPos, ACTOR_PARTNER, -20, 0, 0)
    Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_LRAW_BOMBETTE_FUSE)
    Call(UseBattleCamPresetImmediately, 11)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 1)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720922)
    Wait(5)
    Call(PartnerTestEnemy, LVar0, 0, 16, 0, 1, 16)
    Wait(10)
    Call(StopSound, 647)
    Loop(7)
        Call(SetActorDispOffset, ACTOR_PARTNER, Float(0.5), 0, 0)
        Wait(1)
        Call(SetActorDispOffset, ACTOR_PARTNER, Float(-0.5), 0, 0)
        Wait(1)
    EndLoop
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 0, 0)
    Set(LVarA, 0)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(battle_partner_bombette_PlayExplosionFX, LVar0, LVar1, LVar2)
    Call(UseBattleCamPreset, 3)
    Call(MoveBattleCamOver, 8)
    Thread
        Call(StartRumble, 4)
        Call(ShakeCam, 1, 0, 2, Float(0.75))
        Call(ShakeCam, 1, 0, 5, Float(3.0))
        Call(ShakeCam, 1, 0, 10, Float(4.5))
        Call(ShakeCam, 1, 0, 5, Float(3.0))
        Call(ShakeCam, 1, 0, 10, Float(6.0))
        Call(ShakeCam, 1, 0, 5, Float(3.0))
        Call(ShakeCam, 1, 0, 3, Float(2.25))
        Call(ShakeCam, 1, 0, 4, Float(1.2))
        Call(ShakeCam, 1, 0, 6, Float(0.45))
        Call(ShakeCam, 1, 0, 8, Float(0.15))
    EndThread
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8214)
    Call(PartnerTestEnemy, LVar0, 0, 20, 0, 1, 16)
    IfEq(LVar0, 6)
        Goto(10)
    EndIf
    Set(LVarF, 1)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(143)
            Set(LVarF, 5)
        CaseEq(144)
            Set(LVarF, 6)
        CaseEq(145)
            Set(LVarF, 7)
    EndSwitch
    Call(PartnerDamageEnemy, LVar0, 268435968, 0, 0, LVarF, 48)
    Label(10)
    Set(LVar0, 0)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(1)
        CaseOrEq(3)
            Thread
                Set(LVar0, 0)
                Loop(80)
                    Wait(1)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Add(LVar0, 33)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(SetAnimation, ACTOR_PARTNER, -1, 720923)
            Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Add(LVar1, 200)
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(FlyToGoal, ACTOR_PARTNER, 10, 0, 0)
            Wait(50)
            Call(SetGoalToHome, ACTOR_PARTNER)
            Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Add(LVar0, 25)
            Add(LVar1, 200)
            Call(SetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(SetGoalToHome, ACTOR_PARTNER)
            Call(SetActorSpeed, ACTOR_PARTNER, Float(4.0))
            Call(SetActorJumpGravity, ACTOR_PARTNER, Float(0.5996))
            Call(SetAnimation, ACTOR_PARTNER, -1, 720923)
            Call(JumpToGoal, ACTOR_PARTNER, 20, false, true, false)
            Call(SetAnimation, ACTOR_PARTNER, -1, 720900)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_802386DC = {
    Loop(15)
        Call(SetActorDispOffset, ACTOR_PARTNER, Float(0.5), 0, 0)
        Wait(1)
        Call(SetActorDispOffset, ACTOR_PARTNER, Float(-0.5), 0, 0)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_80238780 = {
    Call(LoadActionCommand, ACTION_COMMAND_BOMB)
    Exec(TTYD64_battle_partner_bombette_EVS_8023CFF0)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(146)
            Call(GetActorLevel, 256, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetupMashMeter, 5, 35, 60, 80, 99, 100)
                CaseEq(1)
                    Call(SetupMashMeter, 5, 35, 60, 80, 99, 100)
                CaseEq(2)
                    Call(SetupMashMeter, 5, 35, 60, 80, 99, 100)
            EndSwitch
        CaseEq(147)
            Call(GetActorLevel, 256, LVar0)
            Switch(LVar0)
                CaseEq(1)
                    Call(SetupMashMeter, 5, 35, 60, 80, 99, 100)
                CaseEq(2)
                    Call(SetupMashMeter, 5, 35, 60, 80, 99, 100)
            EndSwitch
        CaseEq(148)
            Call(SetupMashMeter, 5, 35, 60, 80, 99, 100)
    EndSwitch
    Wait(10)
    Call(UseBattleCamPreset, 48)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(146)
            Call(InitTargetIterator)
            Call(SetGoalToTarget, ACTOR_PARTNER)
            Call(AddGoalPos, ACTOR_PARTNER, -20, 0, 0)
        CaseEq(147)
            Call(InitTargetIterator)
            Call(SetGoalToTarget, ACTOR_PARTNER)
            Call(AddGoalPos, ACTOR_PARTNER, -40, 0, 0)
        CaseEq(148)
            Call(InitTargetIterator)
            Call(SetGoalToTarget, ACTOR_PARTNER)
            Call(AddGoalPos, ACTOR_PARTNER, -40, 0, 0)
    EndSwitch
    Call(MoveBattleCamOver, 60)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(146)
            Call(action_command_bomb_start, 0, 57, 3, 0)
        CaseEq(147)
            Call(action_command_bomb_start, 0, 72, 3, 1)
        CaseEq(148)
            Call(action_command_bomb_start, 0, 87, 3, 2)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_LRAW_BOMBETTE_FUSE)
    ChildThread
        Call(SetActorVar, ACTOR_SELF, 0, 1)
        Call(SetAnimation, ACTOR_PARTNER, -1, 720905)
        Call(GetMenuSelection, LVar0, LVar1, LVar2)
        Switch(LVar2)
            CaseEq(146)
                Set(LVar0, 45)
            CaseEq(147)
                Set(LVar0, 50)
            CaseEq(148)
                Set(LVar0, 50)
        EndSwitch
        Call(RunToGoal, ACTOR_PARTNER, 45)
        Call(SetAnimation, ACTOR_PARTNER, -1, 720922)
        Call(SetActorVar, ACTOR_SELF, 0, 0)
    EndChildThread
    Switch(LVar2)
        CaseEq(146)
            Set(LVar0, 45)
        CaseEq(147)
            Set(LVar0, 50)
        CaseEq(148)
            Set(LVar0, 50)
    EndSwitch
    Wait(LVar0)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(146)
            Call(PartnerTestEnemy, LVar0, 0, 16, 0, 1, 16)
    EndSwitch
    Call(StopSound, 647)
    Switch(LVar2)
        CaseEq(146)
            Set(LVar0, 7)
        CaseEq(147)
            Set(LVar0, 12)
        CaseEq(148)
            Set(LVar0, 20)
    EndSwitch
    Loop(LVar0)
        Call(SetActorDispOffset, ACTOR_PARTNER, Float(0.5), 0, 0)
        Wait(1)
        Call(SetActorDispOffset, ACTOR_PARTNER, Float(-0.5), 0, 0)
        Wait(1)
    EndLoop
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 0, 0)
    Call(UseBattleCamPreset, 3)
    Call(MoveBattleCamOver, 8)
    Call(GetMashActionQuality, LVar0)
    Call(battle_partner_bombette_GetBombDamage, LVar0)
    Set(LVarA, LVar0)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(battle_partner_bombette_PlayExplosionFX, LVar0, LVar1, LVar2)
    Thread
        Call(GetMenuSelection, LVar0, LVar1, LVar2)
        Switch(LVar2)
            CaseEq(146)
                IfGt(LVarA, 0)
                    Call(StartRumble, 4)
                    Call(ShakeCam, 1, 0, 2, Float(0.75))
                    Call(ShakeCam, 1, 0, 5, Float(3.0))
                    Call(ShakeCam, 1, 0, 10, Float(4.5))
                    Call(ShakeCam, 1, 0, 5, Float(3.0))
                    Call(ShakeCam, 1, 0, 10, Float(6.0))
                    Call(ShakeCam, 1, 0, 5, Float(3.0))
                    Call(ShakeCam, 1, 0, 3, Float(2.25))
                    Call(ShakeCam, 1, 0, 4, Float(1.2))
                    Call(ShakeCam, 1, 0, 6, Float(0.45))
                    Call(ShakeCam, 1, 0, 8, Float(0.15))
                Else
                    Call(StartRumble, 4)
                    Call(ShakeCam, 1, 0, 1, Float(0.4))
                    Call(ShakeCam, 1, 0, 2, Float(1.5996))
                    Call(ShakeCam, 1, 0, 5, Float(2.4))
                    Call(ShakeCam, 1, 0, 2, Float(1.5996))
                    Call(ShakeCam, 1, 0, 5, Float(3.2))
                    Call(ShakeCam, 1, 0, 2, Float(1.5996))
                    Call(ShakeCam, 1, 0, 1, Float(1.2))
                    Call(ShakeCam, 1, 0, 2, Float(0.6396))
                    Call(ShakeCam, 1, 0, 3, Float(0.24))
                    Call(ShakeCam, 1, 0, 4, Float(0.08))
                EndIf
            CaseEq(147)
                IfGt(LVarA, 0)
                    Call(StartRumble, 5)
                    Call(ShakeCam, 1, 0, 2, Float(0.75))
                    Call(ShakeCam, 1, 0, 5, Float(3.0))
                    Call(ShakeCam, 1, 0, 10, Float(4.5))
                    Call(ShakeCam, 1, 0, 5, Float(3.0))
                    Call(ShakeCam, 1, 0, 10, Float(6.0))
                    Call(ShakeCam, 1, 0, 5, Float(3.0))
                    Call(ShakeCam, 1, 0, 3, Float(2.25))
                    Call(ShakeCam, 1, 0, 4, Float(1.2))
                    Call(ShakeCam, 1, 0, 6, Float(0.45))
                    Call(ShakeCam, 1, 0, 8, Float(0.15))
                Else
                    Call(StartRumble, 5)
                    Call(ShakeCam, 1, 0, 1, Float(0.4))
                    Call(ShakeCam, 1, 0, 2, Float(1.5996))
                    Call(ShakeCam, 1, 0, 5, Float(2.4))
                    Call(ShakeCam, 1, 0, 2, Float(1.5996))
                    Call(ShakeCam, 1, 0, 5, Float(3.2))
                    Call(ShakeCam, 1, 0, 2, Float(1.5996))
                    Call(ShakeCam, 1, 0, 1, Float(1.2))
                    Call(ShakeCam, 1, 0, 2, Float(0.6396))
                    Call(ShakeCam, 1, 0, 3, Float(0.24))
                    Call(ShakeCam, 1, 0, 4, Float(0.08))
                EndIf
            CaseEq(148)
                IfGt(LVarA, 0)
                    Call(StartRumble, 6)
                    Call(ShakeCam, 1, 0, 2, Float(1.0))
                    Call(ShakeCam, 1, 0, 5, Float(4.0))
                    Call(ShakeCam, 1, 0, 10, Float(6.0))
                    Call(ShakeCam, 1, 0, 5, Float(4.0))
                    Call(ShakeCam, 1, 0, 10, Float(8.0))
                    Call(ShakeCam, 1, 0, 5, Float(4.0))
                    Call(ShakeCam, 1, 0, 3, Float(3.0))
                    Call(ShakeCam, 1, 0, 4, Float(1.5996))
                    Call(ShakeCam, 1, 0, 6, Float(0.5996))
                    Call(ShakeCam, 1, 0, 8, Float(0.2))
                Else
                    Call(StartRumble, 6)
                    Call(ShakeCam, 1, 0, 1, Float(0.5))
                    Call(ShakeCam, 1, 0, 2, Float(2.0))
                    Call(ShakeCam, 1, 0, 5, Float(3.0))
                    Call(ShakeCam, 1, 0, 2, Float(2.0))
                    Call(ShakeCam, 1, 0, 5, Float(4.0))
                    Call(ShakeCam, 1, 0, 2, Float(2.0))
                    Call(ShakeCam, 1, 0, 1, Float(1.5))
                    Call(ShakeCam, 1, 0, 2, Float(0.7998))
                    Call(ShakeCam, 1, 0, 3, Float(0.2998))
                    Call(ShakeCam, 1, 0, 4, Float(0.0996))
                EndIf
        EndSwitch
    EndThread
    Thread
        Call(GetMenuSelection, LVar0, LVar1, LVar2)
        Switch(LVar2)
            CaseEq(146)
            CaseEq(147)
                Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
                Wait(8)
                IfGt(LVarA, 0)
                    Call(PlayEffect_impl, 104, 0, LVar0, 0, LVar2, 1, 0, 0, 0, 0, 0, 0, 0, 0)
                Else
                    Call(PlayEffect_impl, 104, 1, LVar0, 0, LVar2, 1, 0, 0, 0, 0, 0, 0, 0, 0)
                EndIf
            CaseEq(148)
                Set(LVarA, 0)
                Wait(10)
                Call(battle_partner_bombette_PlayExplosionFX, 88, 33, 5)
                Wait(10)
                Call(battle_partner_bombette_PlayExplosionFX, 18, 73, 5)
                Wait(10)
                Call(battle_partner_bombette_PlayExplosionFX, 120, 19, 5)
                Wait(10)
        EndSwitch
    EndThread
    Set(LFlag0, 0)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(146)
            Call(SetGoalToTarget, ACTOR_PARTNER)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8214)
            Call(PartnerTestEnemy, LVar0, 0, 20, 0, 1, 16)
            IfEq(LVar0, 6)
                BreakSwitch
            EndIf
            Call(GetMashActionQuality, LVar0)
            Call(battle_partner_bombette_GetBombDamage, LVar0)
            Switch(LVar0)
                CaseGt(0)
                    Call(PartnerDamageEnemy, LVar0, 268435968, 0, 0, LVarF, 112)
                    Set(LFlag0, 1)
                CaseDefault
                    Call(PartnerDamageEnemy, LVar0, 268435968, 0, 0, LVarF, 48)
            EndSwitch
        CaseEq(147)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8214)
            Label(5)
            Call(SetGoalToTarget, ACTOR_PARTNER)
            Call(PartnerTestEnemy, LVar0, 0, 20, 0, 1, 16)
            IfEq(LVar0, 6)
                Goto(6)
            EndIf
            Call(GetMashActionQuality, LVar0)
            Call(battle_partner_bombette_GetPowerBombDamage, LVar0)
            Switch(LVar0)
                CaseGt(0)
                    Call(PartnerDamageEnemy, LVar0, 805306880, 0, 0, LVarF, 112)
                    Set(LFlag0, 1)
                CaseDefault
                    Call(PartnerDamageEnemy, LVar0, 805306880, 0, 0, LVarF, 48)
            EndSwitch
            Label(6)
            Call(ChooseNextTarget, 0, LVar0)
            IfNe(LVar0, -1)
                Goto(5)
            EndIf
        CaseEq(148)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8216)
            Label(10)
            Call(SetGoalToTarget, ACTOR_PARTNER)
            Call(PartnerTestEnemy, LVar0, 0, 20, 0, 1, 16)
            IfEq(LVar0, 6)
                Goto(11)
            EndIf
            Call(GetMashActionQuality, LVar0)
            Call(battle_partner_bombette_GetMegaBombDamage, LVar0)
            Switch(LVar0)
                CaseGt(0)
                    Call(PartnerDamageEnemy, LVar0, 805306880, 0, 0, LVarF, 112)
                    Set(LFlag0, 1)
                CaseDefault
                    Call(PartnerDamageEnemy, LVar0, 805306880, 0, 0, LVarF, 48)
            EndSwitch
            Label(11)
            Wait(5)
            Call(ChooseNextTarget, 0, LVar0)
            IfNe(LVar0, -1)
                Goto(10)
            EndIf
    EndSwitch
    IfGt(LFlag0, 0)
        Call(UseBattleCamPreset, 4)
        Call(MoveBattleCamOver, 10)
    Else
        Call(UseBattleCamPreset, 51)
    EndIf
    Set(LVar0, 0)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(1)
        CaseOrEq(3)
            Thread
                Set(LVar0, 0)
                Loop(80)
                    Wait(1)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Add(LVar0, 33)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(SetAnimation, ACTOR_PARTNER, -1, 720923)
            Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Add(LVar1, 200)
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(FlyToGoal, ACTOR_PARTNER, 10, 0, 0)
            Wait(50)
            Jump(TTYD64_Script_Bomb_DoStylish)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_80239DF8 = {
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(InterruptActionCommand)
    Call(StopSound, 647)
    Call(GetLastEvent, ACTOR_PARTNER, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, -1)
            Set(LVar1, 720914)
            ExecWait(EVS_Enemy_Hit)
            Call(SetAnimation, ACTOR_PARTNER, -1, 720900)
        EndCaseGroup
        CaseOrEq(23)
        CaseOrEq(25)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8332)
            Call(TTYD64_GetPartnerExtraBattleData_API, 14, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 720896)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 720910)
            EndIf
            ExecWait(EVS_Enemy_NoDamageHit)
        EndCaseGroup
        CaseEq(42)
            SetConst(LVar1, 720914)
            Set(LVar2, 15)
            SetConst(LVar3, 720926)
            ExecWait(EVS_Partner_BombetteSpikeContact)
        CaseEq(14)
            SetConst(LVar1, 720915)
            SetConst(LVar2, 720916)
            ExecWait(EVS_Partner_BurnHit)
            Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Set(LVarA, 0)
            Call(battle_partner_bombette_PlayExplosionFX, LVar0, LVar1, LVar2)
            Thread
                Call(ShakeCam, 1, 0, 2, Float(0.5))
                Call(ShakeCam, 1, 0, 5, Float(2.0))
                Call(ShakeCam, 1, 0, 10, Float(3.0))
                Call(ShakeCam, 1, 0, 5, Float(2.0))
                Call(ShakeCam, 1, 0, 3, Float(1.5))
                Call(ShakeCam, 1, 0, 4, Float(0.7998))
                Call(ShakeCam, 1, 0, 6, Float(0.2998))
                Call(ShakeCam, 1, 0, 8, Float(0.0996))
            EndThread
            Thread
                Set(LVar0, 0)
                Loop(80)
                    Wait(1)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Add(LVar0, 33)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(SetAnimation, ACTOR_PARTNER, -1, 720923)
            Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Add(LVar1, 200)
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(FlyToGoal, ACTOR_PARTNER, 10, 0, 0)
            Wait(50)
            Call(SetGoalToHome, ACTOR_PARTNER)
            Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Add(LVar1, 200)
            Call(SetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(SetGoalToHome, ACTOR_PARTNER)
            Call(SetActorSpeed, ACTOR_PARTNER, Float(4.0))
            Call(SetActorJumpGravity, ACTOR_PARTNER, Float(0.5996))
            Call(SetAnimation, ACTOR_PARTNER, -1, 720923)
            Call(JumpToGoal, ACTOR_PARTNER, 20, false, true, false)
            Call(SetAnimation, ACTOR_PARTNER, -1, 720913)
            Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.0))
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_PARTNER, 10, false, true, false)
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_PARTNER, 8, false, true, false)
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_PARTNER, 5, false, true, false)
        CaseEq(44)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(UseBattleCamPreset, 61)
            Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Sub(LVar0, 60)
            Add(LVar1, 40)
            Call(SetActorJumpGravity, ACTOR_PARTNER, Float(0.0996))
            Call(SetJumpAnimations, ACTOR_PARTNER, 0, 720915, 720915, 720915)
            Call(SetAnimation, ACTOR_PARTNER, -1, 720915)
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_PARTNER, 5, false, true, false)
            SetConst(LVar1, 720915)
            SetConst(LVar2, 720916)
            ExecWait(EVS_Partner_BurnHit)
            Call(UseBattleCamPreset, 2)
            Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Set(LVarA, 0)
            Call(battle_partner_bombette_PlayExplosionFX, LVar0, LVar1, LVar2)
            Thread
                Call(ShakeCam, 1, 0, 2, Float(0.5))
                Call(ShakeCam, 1, 0, 5, Float(2.0))
                Call(ShakeCam, 1, 0, 10, Float(3.0))
                Call(ShakeCam, 1, 0, 5, Float(2.0))
                Call(ShakeCam, 1, 0, 3, Float(1.5))
                Call(ShakeCam, 1, 0, 4, Float(0.7998))
                Call(ShakeCam, 1, 0, 6, Float(0.2998))
                Call(ShakeCam, 1, 0, 8, Float(0.0996))
            EndThread
            Thread
                Set(LVar0, 0)
                Loop(80)
                    Wait(1)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Add(LVar0, 33)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(SetAnimation, ACTOR_PARTNER, -1, 720923)
            Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Add(LVar1, 200)
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(FlyToGoal, ACTOR_PARTNER, 10, 0, 0)
            Wait(50)
            Call(SetGoalToHome, ACTOR_PARTNER)
            Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Add(LVar1, 200)
            Call(SetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(SetGoalToHome, ACTOR_PARTNER)
            Call(SetActorSpeed, ACTOR_PARTNER, Float(4.0))
            Call(SetActorJumpGravity, ACTOR_PARTNER, Float(0.5996))
            Call(SetAnimation, ACTOR_PARTNER, -1, 720923)
            Call(JumpToGoal, ACTOR_PARTNER, 20, false, true, false)
            Call(SetAnimation, ACTOR_PARTNER, -1, 720913)
            Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.0))
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_PARTNER, 10, false, true, false)
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_PARTNER, 8, false, true, false)
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_PARTNER, 5, false, true, false)
        CaseEq(47)
            SetConst(LVar1, 720914)
            Set(LVar2, 15)
            SetConst(LVar3, 720926)
            Set(LVarA, LVar1)
            Set(LVarB, LVar2)
            Set(LVarC, LVar3)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(UseBattleCamPreset, 62)
            Call(SetAnimation, ACTOR_PARTNER, -1, LVarA)
            Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Sub(LVar0, 60)
            Add(LVar1, 40)
            Call(SetActorJumpGravity, ACTOR_PARTNER, Float(0.0996))
            Call(SetJumpAnimations, ACTOR_PARTNER, 0, LVarA, LVarA, LVarA)
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_PARTNER, 5, false, false, false)
            Call(ShowShockEffect, -127)
            Set(LVar1, LVarA)
            Set(LVar2, 0)
            ExecWait(EVS_Partner_Hit)
            Call(SetAnimation, ACTOR_PARTNER, -1, 720907)
            Wait(8)
            Call(UseBattleCamPreset, 2)
            Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Set(LVarA, 0)
            Call(battle_partner_bombette_PlayExplosionFX, LVar0, LVar1, LVar2)
            Thread
                Call(ShakeCam, 1, 0, 2, Float(0.5))
                Call(ShakeCam, 1, 0, 5, Float(2.0))
                Call(ShakeCam, 1, 0, 10, Float(3.0))
                Call(ShakeCam, 1, 0, 5, Float(2.0))
                Call(ShakeCam, 1, 0, 3, Float(1.5))
                Call(ShakeCam, 1, 0, 4, Float(0.7998))
                Call(ShakeCam, 1, 0, 6, Float(0.2998))
                Call(ShakeCam, 1, 0, 8, Float(0.0996))
            EndThread
            Thread
                Set(LVar0, 0)
                Loop(80)
                    Wait(1)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Add(LVar0, 33)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(SetAnimation, ACTOR_PARTNER, -1, 720923)
            Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Add(LVar1, 200)
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(FlyToGoal, ACTOR_PARTNER, 10, 0, 0)
            Wait(50)
            Call(SetGoalToHome, ACTOR_PARTNER)
            Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Add(LVar1, 200)
            Call(SetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(SetGoalToHome, ACTOR_PARTNER)
            Call(SetActorSpeed, ACTOR_PARTNER, Float(4.0))
            Call(SetActorJumpGravity, ACTOR_PARTNER, Float(0.5996))
            Call(SetAnimation, ACTOR_PARTNER, -1, 720923)
            Call(JumpToGoal, ACTOR_PARTNER, 20, false, true, false)
            Call(SetAnimation, ACTOR_PARTNER, -1, 720913)
            Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.0))
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_PARTNER, 10, false, true, false)
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_PARTNER, 8, false, true, false)
            Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_PARTNER, 5, false, true, false)
        CaseEq(51)
        CaseEq(52)
            SetConst(LVar0, 1)
            SetConst(LVar1, 720900)
            SetConst(LVar2, 720904)
            Set(LVar3, 0)
            ExecWait(EVS_Partner_Recover)
        CaseOrEq(24)
        CaseOrEq(26)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8332)
            SetConst(LVar0, 1)
            SetConst(LVar1, 720910)
            ExecWait(EVS_Enemy_NoDamageHit)
            Wait(10)
        EndCaseGroup
        CaseEq(32)
            Set(LVar0, -1)
            Set(LVar1, 720914)
            ExecWait(TTYD64_PartnerDies)
            Return
        CaseEq(TTYD64_EVENT_SUPERGUARD)
            Set(LVar0, -1)
            Set(LVar1, 720906)
            ExecWait(TTYD64_DoSuperguard)
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_8023B0FC = {
    Call(LoadActionCommand, ACTION_COMMAND_BODY_SLAM)
    Exec(TTYD64_battle_partner_bombette_EVS_8023CFF0)
    Call(SetupMashMeter, 1, 100, 0, 0, 0, 0)
    Wait(10)
    Call(UseBattleCamPreset, 48)
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(AddGoalPos, ACTOR_PARTNER, -40, 0, 0)
    Set(LFlag2, 0)
    Loop(60)
        Call(CheckButtonDown, 32768, LVar0)
        IfNe(LVar0, 0)
            Set(LFlag2, 1)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(MoveBattleCamOver, 65)
    IfEq(LFlag2, 1)
        Call(action_command_body_slam_start, 0, 92, 3, 0)
        Set(LFlag0, 0)
        ExecGetTID(TTYD64_battle_partner_bombette_EVS_8023CF78, LVarA)
        Loop(35)
            Call(CheckButtonDown, 32768, LVar0)
            IfEq(LVar0, 0)
                Set(LFlag0, 1)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        IfEq(LFlag0, 1)
            KillThread(LVarA)
            Goto(10)
        EndIf
        Set(LFlag0, 0)
        ExecGetTID(TTYD64_battle_partner_bombette_EVS_8023CD50, LVarA)
        Loop(30)
            Call(CheckButtonDown, 32768, LVar0)
            IfEq(LVar0, 0)
                Set(LFlag0, 1)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        IfEq(LFlag0, 1)
            KillThread(LVarA)
            Goto(10)
        EndIf
        IfEq(LFlag0, 0)
            ExecGetTID(TTYD64_battle_partner_bombette_EVS_802386DC, LVarA)
            Loop(30)
                Call(CheckButtonDown, 32768, LVar0)
                IfEq(LVar0, 0)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                KillThread(LVarA)
                Goto(10)
            EndIf
        EndIf
    Else
        Set(LFlag0, 0)
        ExecGetTID(TTYD64_battle_partner_bombette_EVS_8023CF78, LVarA)
        Loop(35)
            Call(CheckButtonDown, 32768, LVar0)
            IfNe(LVar0, 0)
                IfEq(LFlag2, 0)
                    Call(action_command_body_slam_start, 0, 92, 3, 0)
                    Set(LFlag2, 1)
                EndIf
            EndIf
            IfEq(LFlag2, 1)
                IfEq(LVar0, 0)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
            EndIf
            Wait(1)
        EndLoop
        IfEq(LFlag0, 1)
            KillThread(LVarA)
            Goto(10)
        EndIf
        Set(LFlag0, 0)
        ExecGetTID(TTYD64_battle_partner_bombette_EVS_8023CD50, LVarA)
        Loop(30)
            Call(CheckButtonDown, 32768, LVar0)
            IfNe(LVar0, 0)
                IfEq(LFlag2, 0)
                    Call(action_command_body_slam_start, 0, 92, 3, 0)
                    Set(LFlag2, 1)
                EndIf
            EndIf
            IfEq(LFlag2, 1)
                IfEq(LVar0, 0)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
            EndIf
            Wait(1)
        EndLoop
        IfEq(LFlag0, 1)
            KillThread(LVarA)
            Goto(10)
        EndIf
        IfEq(LFlag0, 0)
            ExecGetTID(TTYD64_battle_partner_bombette_EVS_802386DC, LVarA)
            Loop(30)
                Call(CheckButtonDown, 32768, LVar0)
                IfEq(LVar0, 0)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                KillThread(LVarA)
                Goto(10)
            EndIf
        EndIf
    EndIf
    Label(10)
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 0, 0)
    Wait(2)
    Call(InterruptActionCommand)
    Call(PartnerTestEnemy, LVar0, 0, 149, 0, 1, 16)
    IfEq(LVar0, 6)
        Call(PlaySoundAtActor, ACTOR_PARTNER, 8224)
        Call(SetGoalToTarget, ACTOR_PARTNER)
        Call(AddGoalPos, ACTOR_PARTNER, -10, 0, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 720912)
        Call(SetActorSpeed, ACTOR_PARTNER, Float(6.0))
        Call(SetActorSounds, ACTOR_PARTNER, 0, 0, 0)
        Call(RunToGoal, ACTOR_PARTNER, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 720900)
        Call(UseBattleCamPreset, 51)
        Thread
            Call(SetActorRotationOffset, ACTOR_PARTNER, 0, 15, 0)
            Set(LVar0, 0)
            Loop(10)
                Add(LVar0, -72)
                Call(SetActorRotation, ACTOR_PARTNER, 0, 0, LVar0)
                Wait(1)
            EndLoop
            Call(SetActorRotationOffset, ACTOR_PARTNER, 0, 0, 0)
        EndThread
        Call(AddGoalPos, ACTOR_PARTNER, 60, 0, 0)
        Call(RunToGoal, ACTOR_PARTNER, 10)
        Call(SetAnimation, ACTOR_PARTNER, -1, 720900)
        Thread
            Call(battle_partner_kooper_SlowDown)
        EndThread
        Wait(20)
        Call(SetGoalToHome, ACTOR_PARTNER)
        Call(SetActorSpeed, ACTOR_PARTNER, Float(5.0))
        Call(SetAnimation, ACTOR_PARTNER, -1, 720904)
        Call(ResetActorSounds, ACTOR_PARTNER, 0)
        Call(RunToGoal, ACTOR_PARTNER, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 720900)
        Return
    EndIf
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(143)
            Set(LVarE, 1)
            Set(LVarF, 2)
        CaseEq(144)
            Set(LVarE, 2)
            Set(LVarF, 3)
        CaseEq(145)
            Set(LVarE, 3)
            Set(LVarF, 5)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8224)
    Call(GetPartnerActionQuality, LVar0)
    IfGt(LVar0, 0)
        Call(SetGoalToTarget, ACTOR_PARTNER)
        Call(AddGoalPos, ACTOR_PARTNER, -10, 0, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 720912)
        Call(RunToGoal, ACTOR_PARTNER, 3)
        Call(SetAnimation, ACTOR_PARTNER, -1, 720900)
    Else
        Call(SetGoalToTarget, ACTOR_PARTNER)
        Call(AddGoalPos, ACTOR_PARTNER, -10, 0, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 720912)
        Call(SetActorSpeed, ACTOR_PARTNER, Float(6.0))
        Call(RunToGoal, ACTOR_PARTNER, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 720900)
    EndIf
    Switch(LVar0)
        CaseGt(0)
            Call(PartnerDamageEnemy, LVar0, 0, 1, 0, LVarF, 112)
        CaseDefault
            Call(PartnerDamageEnemy, LVar0, 0, 1, 0, LVarE, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_partner_bombette_EVS_8023C058)
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
            ExecWait(TTYD64_battle_partner_bombette_EVS_8023BD2C)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_8023BD2C = {
    Call(PartnerYieldTurn)
    Jump(TTYD64_Script_Slam_DoStylish)
    Call(UseBattleCamPreset, 4)
    Call(MoveBattleCamOver, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720913)
    Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Sub(LVar0, 60)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.4))
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 25, false, true, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720910)
    Wait(1)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720913)
    Sub(LVar0, 30)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 8, false, true, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720910)
    Wait(1)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720913)
    Sub(LVar0, 20)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 6, false, true, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720910)
    Wait(1)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720913)
    Sub(LVar0, 10)
    Call(JumpToGoal, ACTOR_PARTNER, 4, false, true, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720910)
    Wait(1)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720900)
    Wait(8)
    Call(ResetActorSounds, ACTOR_PARTNER, 0)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(5.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 720904)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720900)
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_8023C058 = {
    Call(PartnerYieldTurn)
    Call(UseBattleCamPreset, 51)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720913)
    Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.4))
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 15, false, true, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720910)
    Wait(1)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720913)
    Sub(LVar0, 30)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 8, false, true, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720910)
    Wait(1)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720913)
    Sub(LVar0, 20)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 6, false, true, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720910)
    Wait(1)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720913)
    Sub(LVar0, 10)
    Call(JumpToGoal, ACTOR_PARTNER, 4, false, true, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720910)
    Wait(1)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720900)
    Wait(8)
    Call(ResetActorSounds, ACTOR_PARTNER, 0)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(5.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 720904)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720900)
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_8023C5AC = {
    Call(ShowActionHud, 1)
    Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
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
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(143)
            ExecWait(TTYD64_battle_partner_bombette_EVS_8023B0FC)
        CaseEq(144)
            ExecWait(TTYD64_battle_partner_bombette_EVS_8023B0FC)
        CaseEq(145)
            ExecWait(TTYD64_battle_partner_bombette_EVS_8023B0FC)
        CaseEq(146)
            ExecWait(TTYD64_battle_partner_bombette_EVS_80238780)
        CaseEq(147)
            ExecWait(TTYD64_battle_partner_bombette_EVS_80238780)
        CaseEq(148)
            ExecWait(TTYD64_battle_partner_bombette_EVS_80238780)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_8023CA6C = {
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(6.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 720904)
    Call(SetActorYaw, ACTOR_PARTNER, 0)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 720900)
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_8023CB50 = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(1)
            ExecWait(TTYD64_battle_partner_bombette_EVS_8023CDDC)
        CaseEq(0)
            ExecWait(TTYD64_battle_partner_bombette_EVS_8023C5AC)
        CaseEq(5)
            ExecWait(TTYD64_battle_partner_bombette_EVS_8023CEC0)
        CaseEq(3)
            ExecWait(TTYD64_battle_partner_bombette_EVS_8023CFB4)
        CaseEq(7)
            ExecWait(TTYD64_battle_partner_bombette_EVS_8023CA6C)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_8023CD50 = {
    Call(SetAnimation, ACTOR_PARTNER, -1, 720911)
    Loop(15)
        Call(SetActorDispOffset, ACTOR_PARTNER, Float(0.5), 0, 0)
        Wait(1)
        Call(SetActorDispOffset, ACTOR_PARTNER, Float(-0.5), 0, 0)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_8023CDDC = {
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(143)
            ExecWait(TTYD64_battle_partner_bombette_EVS_80238000)
        CaseEq(144)
            ExecWait(TTYD64_battle_partner_bombette_EVS_80238000)
        CaseEq(145)
            ExecWait(TTYD64_battle_partner_bombette_EVS_80238000)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_8023CE60 = {
    Call(BindTakeTurn, ACTOR_PARTNER, Ref(TTYD64_battle_partner_bombette_EVS_8023CB50))
    Call(BindIdle, ACTOR_PARTNER, Ref(TTYD64_battle_partner_bombette_EVS_8023D04C))
    Call(BindHandleEvent, ACTOR_PARTNER, Ref(TTYD64_battle_partner_bombette_EVS_80239DF8))
    Call(BindHandlePhase, ACTOR_PARTNER, Ref(TTYD64_battle_partner_bombette_EVS_8023D03C))
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_8023CEC0 = {
    SetConst(LVar0, 1)
    SetConst(LVar1, 720920)
    SetConst(LVar2, 720921)
    SetConst(LVar3, 720900)
    ExecWait(EVS_Partner_Celebrate)
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_8023CF78 = {
    Call(SetAnimation, ACTOR_PARTNER, -1, 720904)
    Call(RunToGoal, ACTOR_PARTNER, 35)
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_8023CFB4 = {
    SetConst(LVar0, 1)
    SetConst(LVar1, 720904)
    ExecWait(EVS_Partner_RunAway)
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_8023CFF0 = {
    Call(TTYD64_Player_AC_802A9000)
    Exec(TTYD64_Script_NukeTracker)
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_8023D03C = {
    Return
    End
};

EvtScript TTYD64_battle_partner_bombette_EVS_8023D04C = {
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_partner_bombette(void) {
    Mod_ReplaceActorBlueprint("TTYD64", &battle_partner_bombette, &TTYD64_battle_partner_bombette);
}
