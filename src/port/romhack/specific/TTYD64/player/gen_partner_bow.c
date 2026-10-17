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

extern ActorBlueprint battle_partner_bow;
API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddBattleCamDist);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(DisableBattleCamClampX);
API_CALLABLE(FlyToGoal);
API_CALLABLE(GetActionProgress);
API_CALLABLE(GetActionResultTier);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetBattleFlags2);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetPartnerActionQuality);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(InterruptActionCommand);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(LoadItemScript);
API_CALLABLE(LoadStarPowerScript);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PartnerAfflictEnemy);
API_CALLABLE(PartnerDamageEnemy);
API_CALLABLE(PartnerTestEnemy);
API_CALLABLE(PartnerYieldTurn);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActionHudPrepareTime);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamParam);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetBattleFlagBits2);
API_CALLABLE(SetDamageSource);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetPartAlpha);
API_CALLABLE(SetupMashMeter);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowActionHud);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseBattleCamPresetImmediately);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(action_command_smack_init);
API_CALLABLE(action_command_smack_start);
API_CALLABLE(action_command_spook_init);
API_CALLABLE(action_command_spook_start);
API_CALLABLE(battle_partner_bow_ApplyOuttaSight);
API_CALLABLE(battle_partner_bow_AverageSpookChance);
API_CALLABLE(battle_partner_bow_GetBowSize);
API_CALLABLE(battle_partner_bow_IsOuttaSightActive);
API_CALLABLE(battle_partner_bow_IsPlayerImmobile);
API_CALLABLE(battle_partner_bow_ModifyBowPos);
API_CALLABLE(battle_partner_bow_RestorePlayerIdleAnimations);
EvtScript TTYD64_battle_partner_bow_EVS_802382FC;
extern ActorPartBlueprint TTYD64_battle_partner_bow_PartsTable_Bow_802383F4[];
extern s32 TTYD64_battle_partner_bow_DefenseTable_Bow_8023833C[];
extern ActorBlueprint TTYD64_battle_partner_bow;
EvtScript TTYD64_battle_partner_bow_EVS_80238440;
EvtScript TTYD64_battle_partner_bow_EVS_8023967C;
EvtScript TTYD64_battle_partner_bow_EVS_8023A4E4;
EvtScript TTYD64_battle_partner_bow_EVS_8023B338;
EvtScript TTYD64_battle_partner_bow_EVS_8023BDCC;
EvtScript TTYD64_battle_partner_bow_EVS_8023C464;
EvtScript TTYD64_battle_partner_bow_EVS_8023C8C8;
EvtScript TTYD64_battle_partner_bow_EVS_8023CC94;
EvtScript TTYD64_battle_partner_bow_EVS_8023D05C;
EvtScript TTYD64_battle_partner_bow_EVS_8023D420;
EvtScript TTYD64_battle_partner_bow_EVS_8023D5B4;
EvtScript TTYD64_battle_partner_bow_EVS_8023D73C;
extern s32 TTYD64_battle_partner_bow_StatusTable_Bow_80238348[];
EvtScript TTYD64_battle_partner_bow_EVS_8023D894;
EvtScript TTYD64_battle_partner_bow_EVS_8023D904;
extern s32 TTYD64_battle_partner_bow_IdleAnimations_Bow_80238300[];
EvtScript TTYD64_battle_partner_bow_EVS_8023D9C0;
EvtScript TTYD64_battle_partner_bow_EVS_8023DA0C;
EvtScript TTYD64_battle_partner_bow_EVS_8023DA48;

// clang-format off
ActorPartBlueprint TTYD64_battle_partner_bow_PartsTable_Bow_802383F4[] = {
    {
        .flags = 0,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 9, 19 },
        .opacity = 255,
        .idleAnimations = TTYD64_battle_partner_bow_IdleAnimations_Bow_80238300,
        .defenseTable = TTYD64_battle_partner_bow_DefenseTable_Bow_8023833C,
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
        .unk_1E = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_battle_partner_bow_DefenseTable_Bow_8023833C[] = {
    1, 0, 0,
};

ActorBlueprint TTYD64_battle_partner_bow = {
    .flags = 512,
    .type = 115,
    .level = 0,
    .maxHP = 99,
    .partCount = 1,
    .unk_0A = { 0, 0 },
    .partsData = TTYD64_battle_partner_bow_PartsTable_Bow_802383F4,
    .initScript = &TTYD64_battle_partner_bow_EVS_8023D904,
    .statusTable = TTYD64_battle_partner_bow_StatusTable_Bow_80238348,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 36, 29 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 22 },
    .statusTextOffset = { 10, 22 },
};

s32 TTYD64_battle_partner_bow_StatusTable_Bow_80238348[] = {
    1, 100, 2, 100, 6, 100, 9, 100,
    7, 100, 4, 100, 3, 100, 11, 100,
    5, 100, 10, 100, 8, 100, 31, 0,
    32, 0, 37, 0, 34, 0, 36, 0,
    35, 0, 33, 0, 38, 0, 39, 0,
    41, 0, 0,
};

s32 TTYD64_battle_partner_bow_IdleAnimations_Bow_80238300[] = {
    1, 851970, 12, 851968, 6, 851996, 9, 851997,
    8, 851968, 4, 851994, 13, 851994, 18, 851968,
    26, 851997, 7, 851968, 48, 851995, 0,
};

EvtScript TTYD64_battle_partner_bow_EVS_802382FC = {
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(6.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 851971)
    Call(SetActorYaw, ACTOR_PARTNER, 0)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_80238440 = {
    Call(LoadActionCommand, ACTION_COMMAND_SMACK)
    Exec(TTYD64_Script_NukeTracker)
    Call(action_command_smack_init)
    Call(SetActionHudPrepareTime, 0)
    Call(SetupMashMeter, 4, 35, 69, 99, 100, 0)
    Set(LVarB, 90)
    Set(LVarC, 4)
    Wait(10)
    Thread
        Wait(10)
        Set(LVar0, LVarB)
        Add(LVar0, -3)
        Call(action_command_smack_start, 0, LVar0, 3, 1)
        Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
    EndThread
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_BOO_VANISH_A)
    Call(SetPartAlpha, ACTOR_PARTNER, -1, 55)
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Thread
        Call(SetAnimation, ACTOR_PARTNER, -1, 851971)
        Call(AddGoalPos, ACTOR_PARTNER, -25, -10, 0)
        Call(FlyToGoal, ACTOR_PARTNER, 15, 0, 10)
    EndThread
    Call(UseBattleCamPreset, 13)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamDist, 180)
    Call(MoveBattleCamOver, 30)
    Call(SetBattleCamOffsetY, 9)
    Call(DisableBattleCamClampX)
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_BOO_APPEAR_A)
    Set(LVar0, 55)
    Loop(5)
        Add(LVar0, 40)
        Call(SetPartAlpha, ACTOR_PARTNER, -1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_PARTNER, -1, 255)
    Call(UseBattleCamPresetImmediately, 19)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851985)
    Wait(20)
    Set(LVarF, 0)
    Set(LVarE, 0)
    Set(LVarD, 0)
    Set(LFlag0, 0)
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851986)
    Loop(30)
        Call(SetActorDispOffset, ACTOR_PARTNER, Float(0.5), 0, 0)
        Wait(1)
        Call(SetActorDispOffset, ACTOR_PARTNER, Float(-0.5), 0, 0)
        Wait(1)
    EndLoop
    Call(GetPartnerActionQuality, LVarB)
    Call(GetActionResultTier, LVarD)
    Switch(LVarD)
        CaseOrEq(3)
        CaseOrEq(4)
            Sub(LVarD, 1)
        EndCaseGroup
    EndSwitch
    Label(0)
    Call(PartnerTestEnemy, LVar0, 268435456, 149, 0, 1, 16)
    IfEq(LVar0, 6)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851978)
        Call(InterruptActionCommand)
        Set(LVar0, 0)
        Loop(15)
            Add(LVar0, -45)
            Call(SetActorYaw, ACTOR_PARTNER, LVar0)
            Wait(1)
        EndLoop
        Loop(15)
            Add(LVar0, -90)
            Call(SetActorYaw, ACTOR_PARTNER, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorYaw, ACTOR_PARTNER, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851994)
        Call(AddActorDecoration, ACTOR_SELF, 0, 0, 3)
        Wait(40)
        Call(RemoveActorDecoration, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
        Wait(10)
        ExecWait(TTYD64_battle_partner_bow_EVS_8023D420)
        Return
    EndIf
    Add(LVarE, 1)
    IfGt(LVarE, LVarD)
        Goto(2)
    EndIf
    Call(SetActorScale, ACTOR_PARTNER, Float(1.4), Float(1.4), Float(1.0))
    IfEq(LFlag0, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851978)
        Set(LFlag0, 1)
        Call(SetDamageSource, 14)
    Else
        Call(SetAnimation, ACTOR_PARTNER, -1, 851979)
        Set(LFlag0, 0)
        Call(SetDamageSource, 15)
    EndIf
    Wait(2)
    Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    Thread
        Call(ShakeCam, 1, 0, 2, Float(0.5))
        Call(ShakeCam, 1, 0, 2, Float(1.5))
        Call(ShakeCam, 1, 0, 1, Float(0.5))
        Call(ShakeCam, 1, 0, 1, Float(0.2))
    EndThread
    IfEq(LVarE, 1)
        Call(battle_partner_bow_GetBowSize)
        Call(AddBattleCamDist, LVar0)
        Call(MoveBattleCamOver, 5)
    Else
        Call(AddBattleCamDist, 25)
        Call(MoveBattleCamOver, 5)
    EndIf
    Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(PlayEffect_impl, 68, 5, LVar0, LVar1, LVar2, Float(1.0), 20, 0, 0, 0, 0, 0, 0, 0)
    Call(SetActorSounds, ACTOR_PARTNER, 3, 8218, 0)
    IfEq(LVarE, 1)
        IfGt(LVarB, 99)
            Call(PartnerDamageEnemy, LVar0, 268435456, 149, 0, LVarC, 80)
        Else
            Call(PartnerDamageEnemy, LVar0, 268435456, 149, 0, LVarC, 16)
        EndIf
        IfNe(GameByte(4107), 1)
            Call(TTYD64_ReadField, TTYD64_F_GBATTLESTATUS_180_2U, LVarC)
            IfLt(LVarC, -1)
                Set(LVarC, 0)
            EndIf
        EndIf
        Goto(1)
    Else
        IfNe(GameByte(4107), 1)
            IfGt(LVarC, 1)
                Sub(LVarC, 1)
            EndIf
            IfGt(LVarB, 99)
                Call(PartnerDamageEnemy, LVar0, 402653184, 149, 0, LVarC, 64)
            Else
                Call(PartnerDamageEnemy, LVar0, 402653184, 149, 0, LVarC, 0)
            EndIf
        Else
            IfGt(LVarB, 99)
                Call(PartnerDamageEnemy, LVar0, 268435456, 149, 0, LVarC, 64)
            Else
                Call(PartnerDamageEnemy, LVar0, 268435456, 149, 0, LVarC, 0)
            EndIf
        EndIf
        Goto(1)
    EndIf
    Label(1)
    IfEq(LVarE, 1)
        Set(LVar0, 0)
        Loop(8)
            Add(LVar0, 144)
            Call(SetActorYaw, ACTOR_PARTNER, LVar0)
            Wait(1)
        EndLoop
    Else
        Set(LVar0, 0)
        Loop(8)
            Sub(LVar0, 144)
            Call(SetActorYaw, ACTOR_PARTNER, LVar0)
            Wait(1)
        EndLoop
    EndIf
    Call(SetActorYaw, ACTOR_PARTNER, 0)
    Add(LVarF, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
    Goto(0)
    Label(2)
    Thread
        Call(ShakeCam, 1, 0, 2, Float(0.5))
        Call(ShakeCam, 1, 0, 2, Float(1.5))
        Call(ShakeCam, 1, 0, 1, Float(0.5))
        Call(ShakeCam, 1, 0, 1, Float(0.2))
    EndThread
    IfEq(LVarE, 1)
        Call(battle_partner_bow_GetBowSize)
        Call(AddBattleCamDist, LVar0)
        Call(MoveBattleCamOver, 5)
    Else
        Call(AddBattleCamDist, 25)
        Call(MoveBattleCamOver, 5)
    EndIf
    Call(SetActorScale, ACTOR_PARTNER, Float(1.4), Float(1.4), Float(1.0))
    IfEq(LFlag0, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851978)
        Set(LFlag0, 1)
        Call(SetDamageSource, 16)
    Else
        Call(SetAnimation, ACTOR_PARTNER, -1, 851979)
        Set(LFlag0, 0)
        Call(SetDamageSource, 17)
    EndIf
    Wait(2)
    Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    Call(SetActorSounds, ACTOR_PARTNER, 3, 8218, 0)
    IfNe(GameByte(4107), 1)
        IfGt(LVarC, 1)
            Sub(LVarC, 1)
        EndIf
        Call(GetPartnerActionQuality, LVar0)
        Switch(LVar0)
            CaseGt(99)
                IfEq(LVarD, 0)
                    Add(LVarC, 1)
                    Call(PartnerDamageEnemy, LVar0, 268435456, 149, 0, LVarC, 96)
                Else
                    Call(PartnerDamageEnemy, LVar0, 402653184, 149, 0, LVarC, 96)
                EndIf
            CaseDefault
                IfEq(LVarD, 0)
                    Add(LVarC, 1)
                    Call(PartnerDamageEnemy, LVar0, 268435456, 149, 0, LVarC, 32)
                Else
                    Call(PartnerDamageEnemy, LVar0, 402653184, 149, 0, LVarC, 32)
                EndIf
        EndSwitch
    Else
        Call(GetPartnerActionQuality, LVar0)
        Switch(LVar0)
            CaseGt(99)
                IfEq(LVarD, 0)
                    Add(LVarC, 1)
                    Call(PartnerDamageEnemy, LVar0, 268435456, 149, 0, LVarC, 96)
                Else
                    Call(PartnerDamageEnemy, LVar0, 268435456, 149, 0, LVarC, 96)
                EndIf
            CaseDefault
                IfEq(LVarD, 0)
                    Add(LVarC, 1)
                    Call(PartnerDamageEnemy, LVar0, 268435456, 149, 0, LVarC, 32)
                Else
                    Call(PartnerDamageEnemy, LVar0, 268435456, 149, 0, LVarC, 32)
                EndIf
        EndSwitch
    EndIf
    Thread
        IfEq(LVarE, 1)
            Set(LVar0, 0)
            Loop(8)
                Add(LVar0, 144)
                Call(SetActorYaw, ACTOR_PARTNER, LVar0)
                Wait(1)
            EndLoop
        Else
            Set(LVar0, 0)
            Loop(8)
                Sub(LVar0, 144)
                Call(SetActorYaw, ACTOR_PARTNER, LVar0)
                Wait(1)
            EndLoop
        EndIf
        IfEq(LVarE, 1)
            Set(LVar0, 0)
            Loop(8)
                Add(LVar0, 72)
                Call(SetActorYaw, ACTOR_PARTNER, LVar0)
                Wait(1)
            EndLoop
        Else
            Set(LVar0, 0)
            Loop(8)
                Sub(LVar0, 72)
                Call(SetActorYaw, ACTOR_PARTNER, LVar0)
                Wait(1)
            EndLoop
        EndIf
        Call(SetActorYaw, ACTOR_PARTNER, 0)
    EndThread
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(10)
            Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
            ExecWait(TTYD64_battle_partner_bow_EVS_8023D420)
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
            Wait(10)
            Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
            ExecWait(TTYD64_battle_partner_bow_EVS_8023BDCC)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023967C = {
    Call(LoadActionCommand, ACTION_COMMAND_SPOOK)
    Exec(TTYD64_Script_NukeTracker)
    Call(action_command_spook_init)
    Call(SetupMashMeter, 1, 100, 0, 0, 0, 0)
    Call(SetActionHudPrepareTime, 20)
    Wait(10)
    Thread
        Call(UseBattleCamPreset, 15)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamOffsetY, 4)
        Call(AddBattleCamDist, -150)
        Call(MoveBattleCamOver, 20)
        Call(DisableBattleCamClampX)
    EndThread
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar0, 40)
    Add(LVar1, 20)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_PARTNER, 20, 0, 10)
    Wait(15)
    Call(UseBattleCamPresetImmediately, 19)
    Thread
        Wait(74)
        Loop(8)
            Call(SetActorDispOffset, ACTOR_PARTNER, 1, 0, 0)
            Wait(1)
            Call(SetActorDispOffset, ACTOR_PARTNER, -1, 0, 0)
            Wait(1)
        EndLoop
        Loop(7)
            Call(SetActorDispOffset, ACTOR_PARTNER, 2, 0, 0)
            Wait(1)
            Call(SetActorDispOffset, ACTOR_PARTNER, -2, 0, 0)
            Wait(1)
        EndLoop
        Loop(8)
            Call(SetActorDispOffset, ACTOR_PARTNER, 3, 0, 0)
            Wait(1)
            Call(SetActorDispOffset, ACTOR_PARTNER, -3, 0, 0)
            Wait(1)
        EndLoop
        Call(SetActorDispOffset, ACTOR_PARTNER, 0, 0, 0)
    EndThread
    Call(battle_partner_bow_AverageSpookChance)
    Call(action_command_spook_start, 0, 87, 3, LVar0)
    Call(GetActionProgress, LVar1)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851980)
    Set(LVar1, 0)
    Set(LVar2, 0)
    Loop(90)
        Switch(LVar1)
            CaseGt(80)
                IfEq(LVar2, 7)
                    Call(AddBattleCamDist, -20)
                    Call(MoveBattleCamOver, 20)
                    Call(SetBattleCamTargetingModes, 0, 0, 1)
                    Set(LVar2, 8)
                EndIf
            CaseGt(70)
                IfEq(LVar2, 6)
                    Call(AddBattleCamDist, -20)
                    Call(MoveBattleCamOver, 20)
                    Call(SetBattleCamTargetingModes, 0, 0, 1)
                    Set(LVar2, 7)
                EndIf
            CaseGt(60)
                IfEq(LVar2, 5)
                    Call(AddBattleCamDist, -20)
                    Call(MoveBattleCamOver, 20)
                    Call(SetBattleCamTargetingModes, 0, 0, 1)
                    Set(LVar2, 6)
                EndIf
            CaseGt(50)
                IfEq(LVar2, 4)
                    Call(AddBattleCamDist, -20)
                    Call(MoveBattleCamOver, 20)
                    Call(SetBattleCamTargetingModes, 0, 0, 1)
                    Set(LVar2, 5)
                EndIf
            CaseGt(40)
                IfEq(LVar2, 3)
                    Call(AddBattleCamDist, -20)
                    Call(MoveBattleCamOver, 20)
                    Call(SetBattleCamTargetingModes, 0, 0, 1)
                    Set(LVar2, 4)
                EndIf
            CaseGt(30)
                IfEq(LVar2, 2)
                    Call(AddBattleCamDist, -20)
                    Call(MoveBattleCamOver, 20)
                    Call(SetBattleCamTargetingModes, 0, 0, 1)
                    Set(LVar2, 3)
                EndIf
            CaseGt(20)
                IfEq(LVar2, 1)
                    Call(AddBattleCamDist, -20)
                    Call(MoveBattleCamOver, 20)
                    Call(SetBattleCamTargetingModes, 0, 0, 1)
                    Set(LVar2, 2)
                EndIf
            CaseGt(10)
                IfEq(LVar2, 0)
                    Call(AddBattleCamDist, -20)
                    Call(MoveBattleCamOver, 20)
                    Call(SetBattleCamTargetingModes, 0, 0, 1)
                    Set(LVar2, 1)
                EndIf
        EndSwitch
        Add(LVar1, 1)
        Wait(1)
    EndLoop
    Call(SetActorDispOffset, ACTOR_PARTNER, 0, 0, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851982)
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
    Thread
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 5)
        Wait(5)
        Call(UseBattleCamPreset, 1)
        Loop(5)
            Call(SetBattleCamParam, 3, 110)
            Wait(2)
            Call(SetBattleCamParam, 3, 100)
            Wait(2)
        EndLoop
    EndThread
    Exec(TTYD64_Script_InitTracker)
    Thread
        Set(LVar0, 255)
        Loop(15)
            Sub(LVar0, 10)
            Call(SetPartAlpha, ACTOR_PARTNER, -1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_BOW_SPOOK)
    SetF(LVar0, Float(1.0))
    Call(GetActionProgress, LVar2)
    Switch(LVar2)
        CaseLe(20)
            SetF(LVar1, Float(0.2998))
        CaseLe(40)
            SetF(LVar1, Float(0.4))
        CaseLe(60)
            SetF(LVar1, Float(0.5))
        CaseLe(80)
            SetF(LVar1, Float(0.5996))
        CaseDefault
            SetF(LVar1, Float(0.7))
    EndSwitch
    Loop(5)
        AddF(LVar0, LVar1)
        Call(SetActorScale, ACTOR_PARTNER, LVar0, LVar0, LVar0)
        Wait(1)
    EndLoop
    SetF(LVarE, LVar0)
    Thread
        Loop(5)
            Loop(3)
                SubF(LVar0, Float(0.23))
                Call(SetActorScale, ACTOR_PARTNER, LVar0, LVar0, LVar0)
                Wait(1)
            EndLoop
            Loop(3)
                AddF(LVar0, Float(0.23))
                Call(SetActorScale, ACTOR_PARTNER, LVar0, LVar0, LVar0)
                Wait(1)
            EndLoop
        EndLoop
    EndThread
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar1, 32)
    Call(PlayEffect_impl, 107, 6, LVar0, LVar1, LVar2, Float(1.7998), 45, 0, 0, 0, 0, 0, 0, 0)
    Call(PlayEffect_impl, 107, 6, LVar0, LVar1, LVar2, Float(1.0), 45, 0, 0, 0, 0, 0, 0, 0)
    Wait(15)
    Call(InitTargetIterator)
    Call(GetActionProgress, LVarF)
    Loop(0)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(PartnerTestEnemy, LVar0, 0, 20, 0, 2, 16)
        IfEq(LVar0, 6)
            Goto(10)
        EndIf
        Call(SetDamageSource, 18)
        Switch(LVarF)
            CaseGt(99)
                Call(PartnerAfflictEnemy, LVar0, 1879048192, 0, 4194304, LVarF, 0, 112)
            CaseDefault
                Call(PartnerAfflictEnemy, LVar0, 1879048192, 0, 4194304, LVarF, 0, 176)
        EndSwitch
        Label(10)
        Wait(5)
        Call(ChooseNextTarget, 0, LVar0)
        IfEq(LVar0, -1)
            BreakLoop
        EndIf
    EndLoop
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(99)
            Call(UseBattleCamPreset, 4)
        CaseDefault
            Call(UseBattleCamPreset, 51)
    EndSwitch
    Wait(30)
    Thread
        Set(LVar0, 105)
        Loop(15)
            Add(LVar0, 10)
            Call(SetPartAlpha, ACTOR_PARTNER, -1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(GetActionProgress, LVar2)
    Switch(LVar2)
        CaseLe(20)
            SetF(LVar1, Float(0.2998))
        CaseLe(40)
            SetF(LVar1, Float(0.4))
        CaseLe(60)
            SetF(LVar1, Float(0.5))
        CaseLe(80)
            SetF(LVar1, Float(0.5996))
        CaseDefault
            SetF(LVar1, Float(0.7))
    EndSwitch
    SetF(LVar0, LVarE)
    Loop(5)
        SubF(LVar0, LVar1)
        Call(SetActorScale, ACTOR_PARTNER, LVar0, LVar0, LVar0)
        Wait(1)
    EndLoop
    Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
    ExecWait(TTYD64_battle_partner_bow_EVS_8023CC94)
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023A4E4 = {
    Call(LoadActionCommand, ACTION_COMMAND_SMACK)
    Exec(TTYD64_Script_NukeTracker)
    Call(action_command_smack_init)
    Call(SetActionHudPrepareTime, 0)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(179)
            Call(SetupMashMeter, 4, 40, 70, 99, 100, 0)
            Set(LVarB, 60)
            Set(LVarC, 1)
        CaseEq(180)
            Call(SetupMashMeter, 5, 35, 60, 80, 99, 100)
            Set(LVarB, 60)
            Set(LVarC, 1)
        CaseEq(181)
            Call(SetupMashMeter, 5, 35, 60, 80, 99, 100)
            Set(LVarB, 60)
            Set(LVarC, 1)
    EndSwitch
    Wait(10)
    Thread
        Wait(10)
        Set(LVar0, LVarB)
        Add(LVar0, -3)
        Call(action_command_smack_start, 0, LVar0, 3, 0)
        Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
    EndThread
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_BOO_VANISH_A)
    Call(SetPartAlpha, ACTOR_PARTNER, -1, 55)
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Thread
        Call(SetAnimation, ACTOR_PARTNER, -1, 851971)
        Call(AddGoalPos, ACTOR_PARTNER, -15, -10, 0)
        Call(FlyToGoal, ACTOR_PARTNER, 15, 0, 10)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
    EndThread
    Call(UseBattleCamPreset, 13)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamDist, 180)
    Call(MoveBattleCamOver, 30)
    Call(SetBattleCamOffsetY, 9)
    Call(DisableBattleCamClampX)
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_BOO_APPEAR_A)
    Set(LVar0, 55)
    Loop(5)
        Add(LVar0, 40)
        Call(SetPartAlpha, ACTOR_PARTNER, -1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_PARTNER, -1, 255)
    Call(UseBattleCamPresetImmediately, 19)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851973)
    Wait(20)
    Set(LVarF, 0)
    Set(LVarE, 0)
    Set(LVarD, 0)
    Set(LFlag0, 0)
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_SELF)
    Loop(15)
        Call(SetActorDispOffset, ACTOR_PARTNER, Float(0.5), 0, 0)
        Wait(1)
        Call(SetActorDispOffset, ACTOR_PARTNER, Float(-0.5), 0, 0)
        Wait(1)
    EndLoop
    Call(GetPartnerActionQuality, LVarB)
    Call(GetActionResultTier, LVarD)
    Label(0)
    Call(PartnerTestEnemy, LVar0, 0, 20, 0, 1, 16)
    IfEq(LVar0, 6)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851975)
        Call(InterruptActionCommand)
        Set(LVar0, 0)
        Loop(20)
            Add(LVar0, -45)
            Call(SetActorYaw, ACTOR_PARTNER, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorYaw, ACTOR_PARTNER, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851994)
        Call(AddActorDecoration, ACTOR_SELF, 0, 0, 3)
        Wait(30)
        Call(RemoveActorDecoration, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
        Wait(10)
        ExecWait(TTYD64_battle_partner_bow_EVS_8023D420)
        Return
    EndIf
    Add(LVarE, 1)
    IfGt(LVarE, LVarD)
        Goto(2)
    EndIf
    Call(SetActorScale, ACTOR_PARTNER, Float(1.4), Float(1.4), Float(1.0))
    IfEq(LFlag0, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851975)
        Set(LFlag0, 1)
        Call(SetDamageSource, 10)
    Else
        Call(SetAnimation, ACTOR_PARTNER, -1, 851976)
        Set(LFlag0, 0)
        Call(SetDamageSource, 11)
    EndIf
    Wait(2)
    Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    Thread
        Call(ShakeCam, 1, 0, 2, Float(0.5))
        Call(ShakeCam, 1, 0, 2, Float(1.5))
        Call(ShakeCam, 1, 0, 1, Float(0.5))
        Call(ShakeCam, 1, 0, 1, Float(0.2))
    EndThread
    IfEq(LVarE, 1)
        Call(battle_partner_bow_GetBowSize)
        Call(AddBattleCamDist, LVar0)
        Call(MoveBattleCamOver, 5)
    Else
        Call(AddBattleCamDist, 25)
        Call(MoveBattleCamOver, 5)
    EndIf
    Call(SetActorSounds, ACTOR_PARTNER, 3, 8217, 0)
    IfEq(LVarE, 1)
        IfGt(LVarB, 99)
            Call(PartnerDamageEnemy, LVar0, 0, 5, 0, LVarC, 80)
        Else
            Call(PartnerDamageEnemy, LVar0, 0, 5, 0, LVarC, 16)
        EndIf
        IfNe(GameByte(4107), 1)
            Call(TTYD64_ReadField, TTYD64_F_GBATTLESTATUS_180_2U, LVarC)
            IfLt(LVarC, -1)
                Set(LVarC, 0)
            EndIf
        EndIf
        Goto(1)
    Else
        IfNe(GameByte(4107), 1)
            IfGt(LVarC, 1)
                Sub(LVarC, 1)
            EndIf
            IfGt(LVarB, 99)
                Call(PartnerDamageEnemy, LVar0, 134217728, 5, 0, LVarC, 64)
            Else
                Call(PartnerDamageEnemy, LVar0, 134217728, 5, 0, LVarC, 0)
            EndIf
        Else
            IfGt(LVarB, 99)
                Call(PartnerDamageEnemy, LVar0, 0, 5, 0, LVarC, 64)
            Else
                Call(PartnerDamageEnemy, LVar0, 0, 5, 0, LVarC, 0)
            EndIf
        EndIf
        Goto(1)
    EndIf
    Label(1)
    Wait(8)
    Add(LVarF, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
    Goto(0)
    Label(2)
    IfEq(LVarE, 1)
        Call(battle_partner_bow_GetBowSize)
        Call(AddBattleCamDist, LVar0)
        Call(MoveBattleCamOver, 5)
    Else
        Call(AddBattleCamDist, 25)
        Call(MoveBattleCamOver, 5)
    EndIf
    Call(SetActorScale, ACTOR_PARTNER, Float(1.4), Float(1.4), Float(1.0))
    IfEq(LFlag0, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851975)
        Set(LFlag0, 1)
        Call(SetDamageSource, 12)
    Else
        Call(SetAnimation, ACTOR_PARTNER, -1, 851976)
        Set(LFlag0, 0)
        Call(SetDamageSource, 13)
    EndIf
    Wait(2)
    Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    Call(SetActorSounds, ACTOR_PARTNER, 3, 8217, 0)
    IfNe(GameByte(4107), 1)
        IfGt(LVarC, 1)
            Sub(LVarC, 1)
        EndIf
        Call(GetPartnerActionQuality, LVar0)
        Switch(LVar0)
            CaseGt(99)
                IfEq(LVarD, 0)
                    Call(PartnerDamageEnemy, LVar0, 0, 5, 0, LVarC, 96)
                Else
                    Call(PartnerDamageEnemy, LVar0, 134217728, 5, 0, LVarC, 96)
                EndIf
            CaseDefault
                IfEq(LVarD, 0)
                    Call(PartnerDamageEnemy, LVar0, 0, 5, 0, LVarC, 32)
                Else
                    Call(PartnerDamageEnemy, LVar0, 134217728, 5, 0, LVarC, 32)
                EndIf
        EndSwitch
    Else
        Call(GetPartnerActionQuality, LVar0)
        Switch(LVar0)
            CaseGt(99)
                Call(PartnerDamageEnemy, LVar0, 0, 5, 0, LVarC, 96)
            CaseDefault
                Call(PartnerDamageEnemy, LVar0, 0, 5, 0, LVarC, 32)
        EndSwitch
    EndIf
    Wait(8)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
            ExecWait(TTYD64_battle_partner_bow_EVS_8023D420)
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
            Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
            ExecWait(TTYD64_battle_partner_bow_EVS_8023BDCC)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023B338 = {
    Set(LVarB, 60)
    Set(LVarC, 1)
    Call(TTYD64_GetPartnerData_API, LVar0)
    Call(TTYD64_ReadPtrField, LVar0, TTYD64_F_PARTNERDATA_1_1U, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Set(LVarD, 4)
        CaseEq(1)
            Set(LVarD, 5)
        CaseEq(2)
            Set(LVarD, 6)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_BOO_VANISH_A)
    Call(SetPartAlpha, ACTOR_PARTNER, -1, 55)
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Thread
        Call(SetAnimation, ACTOR_PARTNER, -1, 851971)
        Call(AddGoalPos, ACTOR_PARTNER, -15, -10, 0)
        Call(FlyToGoal, ACTOR_PARTNER, 15, 0, 10)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
    EndThread
    Call(UseBattleCamPreset, 13)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamDist, 180)
    Call(MoveBattleCamOver, 30)
    Call(SetBattleCamOffsetY, 9)
    Call(DisableBattleCamClampX)
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_BOO_APPEAR_A)
    Set(LVar0, 55)
    Loop(5)
        Add(LVar0, 40)
        Call(SetPartAlpha, ACTOR_PARTNER, -1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_PARTNER, -1, 255)
    Call(UseBattleCamPresetImmediately, 19)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851973)
    Wait(10)
    Set(LVarF, 0)
    Set(LVarE, 0)
    Set(LFlag0, 0)
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_SELF)
    Label(0)
    Call(PartnerTestEnemy, LVar0, 0, 20, 0, 1, 16)
    IfEq(LVar0, 6)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851975)
        Set(LVar0, 0)
        Loop(20)
            Add(LVar0, -45)
            Call(SetActorYaw, ACTOR_PARTNER, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorYaw, ACTOR_PARTNER, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851994)
        Call(AddActorDecoration, ACTOR_SELF, 0, 0, 3)
        Wait(30)
        Call(RemoveActorDecoration, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
        Wait(10)
        ExecWait(TTYD64_battle_partner_bow_EVS_8023D420)
        Return
    EndIf
    Add(LVarE, 1)
    IfGt(LVarE, LVarD)
        Goto(2)
    EndIf
    Call(SetActorScale, ACTOR_PARTNER, Float(1.4), Float(1.4), Float(1.0))
    IfEq(LFlag0, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851975)
        Set(LFlag0, 1)
        Call(SetDamageSource, 10)
    Else
        Call(SetAnimation, ACTOR_PARTNER, -1, 851976)
        Set(LFlag0, 0)
        Call(SetDamageSource, 11)
    EndIf
    Wait(2)
    Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    Thread
        Call(ShakeCam, 1, 0, 2, Float(0.5))
        Call(ShakeCam, 1, 0, 2, Float(1.5))
        Call(ShakeCam, 1, 0, 1, Float(0.5))
        Call(ShakeCam, 1, 0, 1, Float(0.2))
    EndThread
    IfEq(LVarE, 1)
        Call(battle_partner_bow_GetBowSize)
        Call(AddBattleCamDist, LVar0)
        Call(MoveBattleCamOver, 5)
    Else
        Call(AddBattleCamDist, 25)
        Call(MoveBattleCamOver, 5)
    EndIf
    Call(SetActorSounds, ACTOR_PARTNER, 3, 8217, 0)
    IfEq(LVarE, 1)
        Call(PartnerDamageEnemy, LVar0, 0, 5, 0, LVarC, 16)
        IfNe(GameByte(4107), 1)
            Call(TTYD64_ReadField, TTYD64_F_GBATTLESTATUS_180_2U, LVarC)
            IfLt(LVarC, -1)
                Set(LVarC, 0)
            EndIf
        EndIf
        Goto(1)
    Else
        IfNe(GameByte(4107), 1)
            IfGt(LVarC, 1)
                Sub(LVarC, 1)
            EndIf
            Call(PartnerDamageEnemy, LVar0, 134217728, 5, 0, LVarC, 0)
        Else
            Call(PartnerDamageEnemy, LVar0, 0, 5, 0, LVarC, 0)
        EndIf
        Goto(1)
    EndIf
    Label(1)
    Wait(8)
    Add(LVarF, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
    Goto(0)
    Label(2)
    IfEq(LVarE, 1)
        Call(battle_partner_bow_GetBowSize)
        Call(AddBattleCamDist, LVar0)
        Call(MoveBattleCamOver, 5)
    Else
        Call(AddBattleCamDist, 25)
        Call(MoveBattleCamOver, 5)
    EndIf
    Call(SetActorScale, ACTOR_PARTNER, Float(1.4), Float(1.4), Float(1.0))
    IfEq(LFlag0, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 851975)
        Set(LFlag0, 1)
        Call(SetDamageSource, 12)
    Else
        Call(SetAnimation, ACTOR_PARTNER, -1, 851976)
        Set(LFlag0, 0)
        Call(SetDamageSource, 13)
    EndIf
    Wait(2)
    Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    Call(SetActorSounds, ACTOR_PARTNER, 3, 8217, 0)
    IfNe(GameByte(4107), 1)
        IfGt(LVarC, 1)
            Sub(LVarC, 1)
        EndIf
        Call(PartnerDamageEnemy, LVar0, 134217728, 5, 0, LVarC, 32)
    Else
        Call(PartnerDamageEnemy, LVar0, 0, 5, 0, LVarC, 32)
    EndIf
    Wait(8)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
            ExecWait(TTYD64_battle_partner_bow_EVS_8023D420)
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
            Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
            ExecWait(TTYD64_battle_partner_bow_EVS_8023BDCC)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023BDCC = {
    Exec(TTYD64_Script_InitTracker)
    Call(PartnerYieldTurn)
    Call(UseBattleCamPreset, 4)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_BOO_VANISH_A)
    Thread
        Set(LVar0, 200)
        Loop(20)
            Sub(LVar0, 10)
            Call(SetPartAlpha, ACTOR_PARTNER, -1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Wait(10)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851971)
    Call(FlyToGoal, ACTOR_PARTNER, 30, 0, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_BOO_APPEAR_A)
    Thread
        Set(LVar0, 55)
        Loop(20)
            Add(LVar0, 10)
            Call(SetPartAlpha, ACTOR_PARTNER, -1, LVar0)
            Wait(1)
        EndLoop
        Call(SetPartAlpha, ACTOR_PARTNER, -1, 255)
    EndThread
    Wait(1)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 0)
        Loop(4)
            ExecWait(TTYD64_Script_TimingTutor)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                Call(TTYD64_StylishDisarm)
                Call(TTYD64_StylishConsume)
                Call(TTYD64_StylishAddCount, LVar0)
                Set(LVarA, 0)
                ExecWait(TTYD64_Script_DoStylishFX)
                Call(GetMenuSelection, 0, 0, LVar0)
                IfNe(LVar0, 184)
                    Call(SetAnimation, ACTOR_PARTNER, -1, 851983)
                    Wait(5)
                Else
                    Exec(TTYD64_Script_InitTracker)
                    Call(SetAnimation, ACTOR_PARTNER, -1, 851984)
                    Wait(20)
                    Call(TTYD64_StylishPressed, LVar0)
                    IfEq(LVar0, 0)
                        Loop(5)
                            ExecWait(TTYD64_Script_TimingTutor)
                            Call(TTYD64_StylishPressed, LVar0)
                            IfEq(LVar0, 1)
                                Call(TTYD64_StylishDisarm)
                                Call(TTYD64_StylishConsume)
                                Call(TTYD64_StylishAddCount, LVar0)
                                Set(LVarA, 0)
                                ExecWait(TTYD64_Script_DoStylishFX)
                                Call(SetAnimation, ACTOR_PARTNER, -1, 851985)
                                Exec(TTYD64_Script_InitTracker)
                                Wait(20)
                                Call(TTYD64_StylishPressed, LVar0)
                                IfEq(LVar0, 0)
                                    Loop(5)
                                        ExecWait(TTYD64_Script_TimingTutor)
                                        Call(TTYD64_StylishPressed, LVar0)
                                        IfEq(LVar0, 1)
                                            Call(TTYD64_StylishDisarm)
                                            Call(TTYD64_StylishConsume)
                                            Call(TTYD64_StylishAddCount, LVar0)
                                            Set(LVarA, 0)
                                            ExecWait(TTYD64_Script_DoStylishFX)
                                            Call(SetAnimation, ACTOR_PARTNER, -1, 851986)
                                            Wait(10)
                                            BreakLoop
                                        EndIf
                                        Wait(1)
                                    EndLoop
                                EndIf
                                BreakLoop
                            EndIf
                            Wait(1)
                        EndLoop
                    EndIf
                EndIf
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndIf
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Wait(20)
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023C464 = {
    Call(SetActorFlagBits, ACTOR_PLAYER, ACTOR_FLAG_NO_INACTIVE_ANIM, 1)
    Call(SetActorFlagBits, ACTOR_PLAYER, ACTOR_FLAG_USING_IDLE_ANIM, 0)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, -129, 28, 0)
    Call(SetBattleCamOffsetY, 15)
    Call(SetBattleCamDist, 260)
    Call(MoveBattleCamOver, 40)
    Thread
        Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Add(LVar1, 5)
        Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Call(FlyToGoal, ACTOR_PARTNER, 10, 0, 10)
    EndThread
    Set(LVar0, 0)
    Loop(10)
        Add(LVar0, 18)
        Call(SetActorYaw, ACTOR_PARTNER, LVar0)
        Wait(1)
    EndLoop
    Wait(10)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, -30)
    Add(LVar1, 30)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_PARTNER, 20, 30, 10)
    Thread
        Set(LVar0, 180)
        Loop(10)
            Sub(LVar0, 18)
            Call(SetActorYaw, ACTOR_PARTNER, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Thread
        Set(LVar0, 255)
        Loop(30)
            Sub(LVar0, 5)
            Call(SetPartAlpha, ACTOR_PARTNER, -1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(battle_partner_bow_ModifyBowPos, -10, 20)
    Add(LVar2, 5)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_PARTNER, 20, 0, 0)
    Call(battle_partner_bow_IsPlayerImmobile)
    IfEq(LVar0, 0)
        Call(SetAnimation, ACTOR_PLAYER, 0, 65556)
    EndIf
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8206)
    Set(LVar0, 255)
    Loop(15)
        Sub(LVar0, 10)
        Call(SetPartAlpha, ACTOR_PLAYER, 1, LVar0)
        Wait(1)
    EndLoop
    Wait(15)
    Call(GetBattleFlags2, LVar0)
    IfFlag(LVar0, 2)
        Call(TTYD64_SetMoveScratch, TTYD64_MSI_BOW, TTYD64_MS_FLAG, 1)
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Call(battle_partner_bow_ApplyOuttaSight)
    Call(SetActorFlagBits, ACTOR_PLAYER, ACTOR_FLAG_NO_INACTIVE_ANIM, 0)
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023C8C8 = {
    Exec(TTYD64_Script_NukeTracker)
    Call(UseBattleCamPreset, 2)
    Wait(20)
    Exec(TTYD64_Script_InitTracker)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8207)
    Thread
        Wait(10)
        Set(LVar0, 105)
        Loop(30)
            Add(LVar0, 5)
            Call(SetPartAlpha, ACTOR_PLAYER, 1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Thread
        Set(LVar0, 105)
        Loop(30)
            Add(LVar0, 5)
            Call(SetPartAlpha, ACTOR_PARTNER, -1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(PartnerYieldTurn)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 40)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(FlyToGoal, ACTOR_PARTNER, 20, 0, 10)
    Call(TTYD64_GetMoveScratch, TTYD64_MSI_BOW, TTYD64_MS_FLAG, LVar0)
    IfEq(LVar0, 1)
        Call(SetBattleFlagBits2, BS_FLAGS2_PLAYER_TURN_USED, 1)
    EndIf
    Call(TTYD64_SetMoveScratch, TTYD64_MSI_BOW, TTYD64_MS_FLAG, 0)
    Call(battle_partner_bow_RestorePlayerIdleAnimations)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 0)
        Loop(4)
            ExecWait(TTYD64_Script_TimingTutor)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                Call(TTYD64_StylishDisarm)
                Call(TTYD64_StylishConsume)
                Call(TTYD64_StylishAddCount, LVar0)
                Set(LVarA, 0)
                ExecWait(TTYD64_Script_DoStylishFX)
                Call(UseIdleAnimation, ACTOR_PARTNER, false)
                Call(SetAnimation, ACTOR_PARTNER, -1, 851983)
                Wait(25)
                Call(UseIdleAnimation, ACTOR_PARTNER, true)
                Return
            EndIf
            Wait(1)
        EndLoop
    EndIf
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Wait(16)
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023CC94 = {
    Call(GetPartnerActionQuality, LVar0)
    IfGe(LVar0, 60)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 0)
            Loop(2)
                ExecWait(TTYD64_Script_TimingTutor)
                Call(TTYD64_StylishPressed, LVar0)
                IfEq(LVar0, 1)
                    Call(TTYD64_StylishDisarm)
                    Call(TTYD64_StylishConsume)
                    Call(TTYD64_StylishAddCount, LVar0)
                    Set(LVarA, 0)
                    ExecWait(TTYD64_Script_DoStylishFX)
                    Call(SetAnimation, ACTOR_PARTNER, -1, 851983)
                    Exec(TTYD64_Script_InitTracker)
                    Wait(20)
                    Call(TTYD64_StylishPressed, LVar0)
                    IfEq(LVar0, 0)
                        Loop(5)
                            ExecWait(TTYD64_Script_TimingTutor)
                            Call(TTYD64_StylishPressed, LVar0)
                            IfEq(LVar0, 1)
                                Call(TTYD64_StylishDisarm)
                                Call(TTYD64_StylishConsume)
                                Call(TTYD64_StylishAddCount, LVar0)
                                Set(LVarA, 0)
                                ExecWait(TTYD64_Script_DoStylishFX)
                                Call(SetAnimation, ACTOR_PARTNER, -1, 851982)
                                Wait(30)
                                Call(SetAnimation, ACTOR_PARTNER, -1, 851983)
                                Wait(15)
                                BreakLoop
                            EndIf
                            Wait(1)
                        EndLoop
                    EndIf
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        EndIf
    EndIf
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Call(PartnerYieldTurn)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851971)
    Call(FlyToGoal, ACTOR_PARTNER, 15, 0, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023D05C = {
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(InterruptActionCommand)
    Call(GetLastEvent, ACTOR_PARTNER, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, -1)
            Set(LVar1, 851989)
            ExecWait(EVS_Enemy_Hit)
            Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
        EndCaseGroup
        CaseOrEq(23)
        CaseOrEq(25)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8332)
            Call(TTYD64_GetPartnerExtraBattleData_API, 14, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 851968)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 851995)
            EndIf
            ExecWait(EVS_Enemy_NoDamageHit)
        EndCaseGroup
        CaseEq(42)
            SetConst(LVar1, 851989)
            Set(LVar2, 14)
            ExecWait(EVS_Partner_SpikeContact)
        CaseEq(44)
            SetConst(LVar1, 851990)
            Set(LVar2, 14)
            SetConst(LVar3, 851991)
            ExecWait(EVS_Partner_BurnContact)
        CaseEq(14)
            SetConst(LVar1, 851990)
            SetConst(LVar2, 851991)
            ExecWait(EVS_Partner_BurnHit)
        CaseEq(47)
            SetConst(LVar1, 851989)
            Set(LVar2, 14)
            ExecWait(EVS_Partner_ShockHit)
        CaseEq(51)
        CaseEq(52)
            SetConst(LVar0, 1)
            SetConst(LVar1, 851969)
            SetConst(LVar2, 851971)
            Set(LVar3, 9)
            ExecWait(EVS_Partner_Recover)
        CaseOrEq(24)
        CaseOrEq(26)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8332)
            SetConst(LVar0, 1)
            SetConst(LVar1, 851995)
            ExecWait(EVS_Enemy_NoDamageHit)
            Wait(10)
        EndCaseGroup
        CaseEq(32)
            Set(LVar0, -1)
            Set(LVar1, 851989)
            ExecWait(TTYD64_PartnerDies)
            Return
        CaseEq(TTYD64_EVENT_SUPERGUARD)
            Set(LVar0, -1)
            Set(LVar1, 851981)
            ExecWait(TTYD64_DoSuperguard)
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023D420 = {
    Call(PartnerYieldTurn)
    Call(UseBattleCamPreset, 51)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_BOO_VANISH_A)
    Thread
        Set(LVar0, 200)
        Loop(20)
            Sub(LVar0, 10)
            Call(SetPartAlpha, ACTOR_PARTNER, -1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Wait(10)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851971)
    Call(FlyToGoal, ACTOR_PARTNER, 30, 0, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_BOO_APPEAR_A)
    Set(LVar0, 55)
    Loop(20)
        Add(LVar0, 10)
        Call(SetPartAlpha, ACTOR_PARTNER, -1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_PARTNER, -1, 255)
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023D5B4 = {
    Call(ShowActionHud, 1)
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
        CaseEq(179)
            ExecWait(TTYD64_battle_partner_bow_EVS_8023A4E4)
        CaseEq(180)
            ExecWait(TTYD64_battle_partner_bow_EVS_8023A4E4)
        CaseEq(181)
            ExecWait(TTYD64_battle_partner_bow_EVS_8023A4E4)
        CaseEq(182)
            Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
            ExecWait(TTYD64_battle_partner_bow_EVS_8023C464)
        CaseEq(183)
            Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
            ExecWait(TTYD64_battle_partner_bow_EVS_8023967C)
        CaseEq(184)
            ExecWait(TTYD64_battle_partner_bow_EVS_80238440)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023D73C = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(1)
            ExecWait(TTYD64_battle_partner_bow_EVS_8023B338)
        CaseEq(0)
            ExecWait(TTYD64_battle_partner_bow_EVS_8023D5B4)
        CaseEq(5)
            ExecWait(TTYD64_battle_partner_bow_EVS_8023D9C0)
        CaseEq(3)
            ExecWait(TTYD64_battle_partner_bow_EVS_8023DA0C)
        CaseEq(7)
            ExecWait(TTYD64_battle_partner_bow_EVS_802382FC)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023D894 = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(12)
            Call(battle_partner_bow_IsOuttaSightActive)
            IfNe(LVar0, 0)
                ExecWait(TTYD64_battle_partner_bow_EVS_8023C8C8)
            EndIf
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023D904 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_battle_partner_bow_EVS_8023D73C))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_battle_partner_bow_EVS_8023DA48))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_battle_partner_bow_EVS_8023D05C))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_battle_partner_bow_EVS_8023D894))
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023D9C0 = {
    Call(SetAnimation, ACTOR_PARTNER, -1, 851985)
    Wait(36)
    Call(SetAnimation, ACTOR_PARTNER, -1, 851969)
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023DA0C = {
    SetConst(LVar0, 1)
    SetConst(LVar1, 851971)
    ExecWait(EVS_Partner_RunAway)
    Return
    End
};

EvtScript TTYD64_battle_partner_bow_EVS_8023DA48 = {
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_partner_bow(void) {
    Mod_ReplaceActorBlueprint("TTYD64", &battle_partner_bow, &TTYD64_battle_partner_bow);
}
