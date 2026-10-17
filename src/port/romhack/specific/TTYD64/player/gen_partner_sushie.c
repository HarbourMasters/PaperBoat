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

extern ActorBlueprint battle_partner_sushie;
extern EvtScript battle_partner_sushie_EVS_HandlePhase;
API_CALLABLE(AddBattleCamDist);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(CheckButtonDown);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(EnableActorBlur);
API_CALLABLE(FlyToGoal);
API_CALLABLE(GetActionProgress);
API_CALLABLE(GetActorLevel);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorScale);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetDistanceToGoal);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetMashActionQuality);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetPartnerActionQuality);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(InterruptActionCommand);
API_CALLABLE(JumpToGoal);
API_CALLABLE(LandJump);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(LoadItemScript);
API_CALLABLE(LoadStarPowerScript);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PartnerDamageEnemy);
API_CALLABLE(PartnerTestEnemy);
API_CALLABLE(PartnerYieldTurn);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActionHudPrepareTime);
API_CALLABLE(SetActionProgress);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetupMashMeter);
API_CALLABLE(ShowActionHud);
API_CALLABLE(ShowVariableMessageBox);
API_CALLABLE(TTYD64_Player_partner7_WaterBlock_PlayFX_59);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(WaitForMessageBoxDone);
API_CALLABLE(action_command_hammer_init);
API_CALLABLE(action_command_hammer_start);
API_CALLABLE(action_command_squirt_init);
API_CALLABLE(action_command_squirt_start);
API_CALLABLE(action_command_three_chances_init);
API_CALLABLE(action_command_three_chances_start);
API_CALLABLE(action_command_tidal_wave_init);
API_CALLABLE(action_command_tidal_wave_start);
API_CALLABLE(battle_partner_sushie_GetSquirtDamage);
API_CALLABLE(battle_partner_sushie_GetSquirtTargetPos);
API_CALLABLE(battle_partner_sushie_InflateSushie);
API_CALLABLE(battle_partner_sushie_ProcessTidalWave);
API_CALLABLE(battle_partner_sushie_SetScaleTidalWaveCharge);
API_CALLABLE(battle_partner_sushie_SetSquirtAngle);
EvtScript TTYD64_battle_partner_sushie_EVS_80238388;
EvtScript TTYD64_battle_partner_sushie_EVS_80238470;
extern ActorBlueprint TTYD64_battle_partner_sushie;
EvtScript TTYD64_battle_partner_sushie_EVS_80239010;
EvtScript TTYD64_battle_partner_sushie_EVS_802393D4;
extern s32 TTYD64_battle_partner_sushie_IdleAnimations_Sushie_80238ED0[];
extern s32 TTYD64_battle_partner_sushie_DefenseTable_Sushie_80238F0C[];
EvtScript TTYD64_battle_partner_sushie_EVS_802395CC;
EvtScript TTYD64_battle_partner_sushie_EVS_8023A540;
EvtScript TTYD64_battle_partner_sushie_EVS_8023AF68;
EvtScript TTYD64_battle_partner_sushie_EVS_8023B110;
extern ActorPartBlueprint TTYD64_battle_partner_sushie_PartsTable_Sushie_80238FC4[];
EvtScript TTYD64_battle_partner_sushie_EVS_8023C070;
EvtScript TTYD64_battle_partner_sushie_EVS_8023CB68;
EvtScript TTYD64_battle_partner_sushie_EVS_8023D234;
EvtScript TTYD64_battle_partner_sushie_EVS_8023D4E0;
EvtScript TTYD64_battle_partner_sushie_EVS_8023D654;
EvtScript TTYD64_battle_partner_sushie_EVS_8023D738;
extern s32 TTYD64_battle_partner_sushie_StatusTable_Sushie_80238F18[];
EvtScript TTYD64_battle_partner_sushie_EVS_8023D8B0;
EvtScript TTYD64_battle_partner_sushie_EVS_8023D944;
EvtScript TTYD64_battle_partner_sushie_EVS_8023D9CC;
EvtScript TTYD64_battle_partner_sushie_EVS_8023DA54;
EvtScript TTYD64_battle_partner_sushie_EVS_8023DAA0;

// clang-format off
ActorBlueprint TTYD64_battle_partner_sushie = {
    .flags = 0,
    .type = 117,
    .level = 0,
    .maxHP = 99,
    .partCount = 1,
    .unk_0A = { 0, 0 },
    .partsData = TTYD64_battle_partner_sushie_PartsTable_Sushie_80238FC4,
    .initScript = &TTYD64_battle_partner_sushie_EVS_8023B110,
    .statusTable = TTYD64_battle_partner_sushie_StatusTable_Sushie_80238F18,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 37, 26 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

s32 TTYD64_battle_partner_sushie_IdleAnimations_Sushie_80238ED0[] = {
    1, 983042, 12, 983040, 6, 983061, 9, 983062,
    8, 983040, 4, 983056, 13, 983056, 18, 983040,
    26, 983062, 7, 983040, 48, 983060, 0,
};

s32 TTYD64_battle_partner_sushie_DefenseTable_Sushie_80238F0C[] = {
    1, 0, 0,
};

ActorPartBlueprint TTYD64_battle_partner_sushie_PartsTable_Sushie_80238FC4[] = {
    {
        .flags = 0,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 12, 17 },
        .opacity = 255,
        .idleAnimations = TTYD64_battle_partner_sushie_IdleAnimations_Sushie_80238ED0,
        .defenseTable = TTYD64_battle_partner_sushie_DefenseTable_Sushie_80238F0C,
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
        .unk_1E = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_battle_partner_sushie_StatusTable_Sushie_80238F18[] = {
    1, 100, 2, 100, 6, 100, 9, 100,
    7, 100, 4, 100, 3, 100, 11, 100,
    5, 100, 10, 100, 8, 100, 31, 0,
    32, 0, 37, 0, 34, 0, 36, 0,
    35, 0, 33, 0, 38, 0, 39, 0,
    41, 0, 0,
};

EvtScript TTYD64_battle_partner_sushie_EVS_80238388 = {
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(GetGoalPos, ACTOR_PARTNER, LVarB, LVarC, LVarD)
    Call(GetActorPos, ACTOR_PARTNER, LVarC, LVarD, LVarE)
    IfGt(LVarB, LVarC)
        Sub(LVarB, LVarC)
    Else
        Sub(LVarC, LVarB)
        Set(LVarB, LVarC)
    EndIf
    Sub(LVarB, 20)
    DivF(LVarB, Float(10.5889))
    AddF(LVarB, 15)
    Set(LVarA, LVarB)
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_80238470 = {
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_80239010 = {
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(InterruptActionCommand)
    Call(GetLastEvent, ACTOR_PARTNER, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, -1)
            Set(LVar1, 983056)
            ExecWait(EVS_Enemy_Hit)
            Call(SetAnimation, ACTOR_PARTNER, -1, 983041)
        EndCaseGroup
        CaseOrEq(23)
        CaseOrEq(25)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8332)
            Call(TTYD64_GetPartnerExtraBattleData_API, 14, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 983040)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 983060)
            EndIf
            ExecWait(EVS_Enemy_NoDamageHit)
        EndCaseGroup
        CaseEq(42)
            SetConst(LVar1, 983053)
            Set(LVar2, 20)
            ExecWait(EVS_Partner_SpikeContact)
        CaseEq(44)
            SetConst(LVar1, 983054)
            Set(LVar2, 20)
            SetConst(LVar3, 983055)
            ExecWait(EVS_Partner_BurnContact)
        CaseEq(14)
            SetConst(LVar1, 983054)
            SetConst(LVar2, 983055)
            ExecWait(EVS_Partner_BurnHit)
        CaseEq(47)
            SetConst(LVar1, 983053)
            Set(LVar2, 20)
            ExecWait(EVS_Partner_ShockHit)
        CaseEq(51)
        CaseEq(52)
            SetConst(LVar0, 1)
            SetConst(LVar1, 983041)
            SetConst(LVar2, 983043)
            Set(LVar3, 0)
            ExecWait(EVS_Partner_Recover)
        CaseOrEq(24)
        CaseOrEq(26)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8332)
            SetConst(LVar0, 1)
            SetConst(LVar1, 983060)
            ExecWait(EVS_Enemy_NoDamageHit)
            Wait(10)
        EndCaseGroup
        CaseEq(32)
            Set(LVar0, -1)
            Set(LVar1, 983056)
            ExecWait(TTYD64_PartnerDies)
            Return
        CaseEq(TTYD64_EVENT_SUPERGUARD)
            Set(LVar0, -1)
            Set(LVar1, 983046)
            ExecWait(TTYD64_DoSuperguard)
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_802393D4 = {
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
        CaseEq(167)
            ExecWait(TTYD64_battle_partner_sushie_EVS_802395CC)
        CaseEq(168)
            ExecWait(TTYD64_battle_partner_sushie_EVS_802395CC)
        CaseEq(169)
            ExecWait(TTYD64_battle_partner_sushie_EVS_802395CC)
        CaseEq(170)
            ExecWait(TTYD64_battle_partner_sushie_EVS_8023C070)
        CaseEq(171)
            ExecWait(TTYD64_battle_partner_sushie_EVS_8023A540)
        CaseEq(172)
            ExecWait(TTYD64_battle_partner_sushie_EVS_8023CB68)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_802395CC = {
    Exec(TTYD64_Script_NukeTracker)
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Call(action_command_hammer_init)
    ExecWait(TTYD64_battle_partner_sushie_EVS_8023D738)
    ExecWait(TTYD64_battle_partner_sushie_EVS_80238388)
    Loop(30)
        Wait(1)
        Call(CheckButtonDown, 262144, LVar0)
        IfNe(LVar0, 0)
            BreakLoop
        EndIf
    EndLoop
    Exec(TTYD64_Script_InitTracker)
    Call(action_command_hammer_start, 0, 57, 3)
    Call(SetActionProgress, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983044)
    Call(UseBattleCamPreset, 59)
    Set(LVar0, 30)
    Loop(60)
        Wait(1)
        Sub(LVar0, 1)
        IfEq(LVar0, 0)
            Call(SetAnimation, ACTOR_PARTNER, -1, 983048)
        EndIf
        Call(CheckButtonDown, 262144, LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
    EndLoop
    Thread
        Call(GetPartnerActionQuality, LVar0)
        Call(UseBattleCamPreset, 52)
        Call(MoveBattleCamOver, 20)
    EndThread
    Call(SetAnimation, ACTOR_PARTNER, -1, 983045)
    Thread
        Call(SetActorRotationOffset, ACTOR_PARTNER, 0, 12, 0)
        Set(LVar0, 0)
        Loop(10)
            Add(LVar0, 36)
            Call(SetActorRotation, ACTOR_PARTNER, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorRotation, ACTOR_PARTNER, 0, 0, 20)
    EndThread
    Thread
        Call(GetPartnerActionQuality, LVar0)
        IfGt(LVar0, 0)
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar2)
                CaseEq(167)
                    Wait(13)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.0996), Float(1.0996), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.0996), Float(1.0996), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.2), Float(1.2), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.2), Float(1.2), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.2998), Float(1.2998), Float(1.0))
                CaseEq(168)
                    Wait(13)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.15), Float(1.15), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.2), Float(1.2), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.3496), Float(1.3496), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.4), Float(1.4), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.5498), Float(1.5498), Float(1.0))
                CaseEq(169)
                    Wait(13)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.2), Float(1.2), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.2998), Float(1.2998), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.5), Float(1.5), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.5996), Float(1.5996), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.7998), Float(1.7998), Float(1.0))
            EndSwitch
        Else
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar2)
                CaseEq(167)
                    Wait(13)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
                CaseEq(168)
                    Wait(13)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.0498), Float(1.0498), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.0996), Float(1.0996), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.15), Float(1.15), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.2), Float(1.2), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.25), Float(1.25), Float(1.0))
                CaseEq(169)
                    Wait(13)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.0996), Float(1.0996), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.2), Float(1.2), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.2998), Float(1.2998), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.4), Float(1.4), Float(1.0))
                    Wait(1)
                    Call(SetActorScale, ACTOR_PARTNER, Float(1.5), Float(1.5), Float(1.0))
            EndSwitch
        EndIf
    EndThread
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8244)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(GetPartnerActionQuality, LVar0)
    IfGt(LVar0, 0)
        Thread
            Call(SetAnimation, ACTOR_PARTNER, -1, 983045)
            Wait(10)
            Call(SetAnimation, ACTOR_PARTNER, -1, 983046)
        EndThread
        Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.5996))
        Thread
            Loop(0)
                Call(TTYD64_StylishPressed, LVar0)
                IfEq(LVar0, 0)
                    Call(GetDistanceToGoal, ACTOR_SELF, LVar0)
                    IfLt(LVar0, 25)
                        Loop(2)
                            ExecWait(TTYD64_Script_TimingTutor)
                            Call(TTYD64_StylishPressed, LVar0)
                            IfEq(LVar0, 1)
                                Call(TTYD64_StylishDisarm)
                                Call(TTYD64_StylishAddCount, LVar0)
                                Set(LVarA, 0)
                                ExecWait(TTYD64_Script_DoStylishFX)
                                Wait(1)
                                Goto(0)
                            EndIf
                            Wait(1)
                        EndLoop
                        Wait(1)
                        Goto(0)
                    EndIf
                Else
                    Call(TTYD64_StylishDisarm)
                    Call(TTYD64_StylishConsume)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            Label(0)
        EndThread
        Call(JumpToGoal, ACTOR_PARTNER, 20, false, true, false)
    Else
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Thread
            Call(SetAnimation, ACTOR_PARTNER, -1, 983045)
            Wait(10)
            Call(SetAnimation, ACTOR_PARTNER, -1, 983046)
        EndThread
        Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.0))
        Call(JumpToGoal, ACTOR_PARTNER, 20, false, true, false)
    EndIf
    Call(SetAnimation, ACTOR_PARTNER, -1, 983047)
    Call(SetActorRotation, ACTOR_PARTNER, 0, 0, 0)
    Call(SetActorRotationOffset, ACTOR_PARTNER, 0, 0, 0)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(167)
            Set(LVarE, 1)
            Set(LVarF, 3)
        CaseEq(168)
            Set(LVarE, 2)
            Set(LVarF, 4)
        CaseEq(169)
            Set(LVarE, 3)
            Set(LVarF, 5)
    EndSwitch
    Call(PartnerTestEnemy, LVar0, 0, 20, 0, 1, 16)
    IfEq(LVar0, 6)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
        Call(LandJump, ACTOR_PARTNER)
        Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Call(AddGoalPos, ACTOR_PARTNER, 15, 0, 0)
        Call(JumpToGoal, ACTOR_PARTNER, 20, false, true, false)
        Call(AddGoalPos, ACTOR_PARTNER, 10, 0, 0)
        Call(JumpToGoal, ACTOR_PARTNER, 10, false, true, false)
        Wait(10)
        Call(SetGoalToHome, ACTOR_PARTNER)
        Call(SetActorSpeed, ACTOR_PARTNER, Float(6.0))
        Call(SetAnimation, ACTOR_PARTNER, -1, 983043)
        Call(RunToGoal, ACTOR_PARTNER, 0)
        Return
    EndIf
    Thread
        Wait(3)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    EndThread
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(PartnerDamageEnemy, LVar0, 128, 4, 0, LVarF, 112)
        CaseDefault
            Call(PartnerDamageEnemy, LVar0, 128, 4, 0, LVarE, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 51)
            ExecWait(TTYD64_battle_partner_sushie_EVS_8023AF68)
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
            Call(UseBattleCamPreset, 3)
            Call(MoveBattleCamOver, 8)
            ExecWait(TTYD64_Script_BellyFlop_GoBackToHome_Succeed)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_8023A540 = {
    Exec(TTYD64_Script_NukeTracker)
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(InitTargetIterator)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, -95, 26, 10)
    Call(SetBattleCamOffsetY, 11)
    Call(SetBattleCamDist, 238)
    Call(MoveBattleCamOver, 30)
    Wait(10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983049)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.0))
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(TTYD64_GetMarioPos, LVar3)
    IfEq(LVar3, 0)
        Add(LVar0, 30)
    EndIf
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 10, false, true, false)
    Call(LoadActionCommand, ACTION_COMMAND_THREE_CHANCES)
    Call(action_command_three_chances_init, 0)
    Call(SetActionHudPrepareTime, 0)
    Set(LVar0, 0)
    Call(TTYD64_GetMarioPos, LVar3)
    IfEq(LVar3, 0)
        Loop(4)
            Add(LVar0, 45)
            Call(SetActorYaw, ACTOR_PARTNER, LVar0)
            Wait(1)
        EndLoop
    Else
        Wait(4)
    EndIf
    Wait(4)
    Call(action_command_three_chances_start, 0, 100, 3)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983051)
    Wait(110)
    Call(GetPartnerActionQuality, LVar0)
    IfEq(LVar0, 0)
        Set(LVarA, LVar0)
        Goto(10)
    EndIf
    Call(SetAnimation, ACTOR_PARTNER, -1, 983052)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, -95, 27, 10)
    Call(SetBattleCamOffsetY, 11)
    Call(SetBattleCamDist, 277)
    Call(MoveBattleCamOver, 10)
    Thread
        Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_SUSHIE_FOUNTAIN)
        Call(TTYD64_Player_partner7_WaterBlock_PlayFX_59)
        Wait(65)
        Exec(TTYD64_Script_InitTracker)
        Call(SetAnimation, ACTOR_PARTNER, -1, 983057)
    EndThread
    Wait(45)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar1, 83)
    Call(PlayEffect_impl, 91, 0, LVar0, LVar1, LVar2, Float(1.0), 50, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8245)
    Thread
        Wait(20)
        Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Add(LVar1, 100)
        Call(PlayEffect_impl, 17, 4, LVar0, LVar1, LVar2, 50, 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(5)
        Sub(LVar1, 20)
        Call(PlayEffect_impl, 17, 4, LVar0, LVar1, LVar2, 50, 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(5)
        Sub(LVar1, 20)
        Call(PlayEffect_impl, 17, 4, LVar0, LVar1, LVar2, 50, 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(5)
        Sub(LVar1, 20)
        Call(PlayEffect_impl, 17, 4, LVar0, LVar1, LVar2, 50, 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(5)
        Sub(LVar1, 20)
        Call(PlayEffect_impl, 17, 4, LVar0, LVar1, LVar2, 50, 0, 0, 0, 0, 0, 0, 0, 0)
    EndThread
    Wait(40)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(PlayEffect_impl, 90, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Wait(30)
    Call(TTYD64_GetEffect, LVarF, LVar0)
    Call(TTYD64_ReadPtrField, LVar0, TTYD64_F_EFFECTINSTANCE_C_4U, LVar0)
    Call(TTYD64_WritePtrField, LVar0, TTYD64_F_WATERBLOCKFXDATA_10_4U, 20)
    Call(GetPartnerActionQuality, LVar0)
    Call(TTYD64_AddDefenseBoost, 0, 1, LVar0)
    Set(LVarA, LVar0)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 15)
    Add(LVar1, 35)
    Set(LVarF, 6)
    Call(PlayEffect_impl, 86, LVarF, LVar0, LVar1, LVar2, Float(1.5), 60, 0, 0, 0, 0, 0, 0, 0)
    Wait(4)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(PartnerYieldTurn)
    Label(10)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 0)
        ExecGetTID(TTYD64_battle_partner_sushie_EVS_8023D234, LVar9)
        Loop(0)
            IsThreadRunning(LVar9, LVar0)
            IfEq(LVar0, 0)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndIf
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.0))
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983043)
    Call(TTYD64_StylishGetCount, LVar0)
    IfGt(LVar0, 0)
        Call(JumpToGoal, ACTOR_PARTNER, 12, false, true, false)
        Wait(10)
    Else
        Call(JumpToGoal, ACTOR_PARTNER, 10, false, true, false)
    EndIf
    Set(LVar1, 180)
    Loop(4)
        Sub(LVar1, 45)
        Call(SetActorYaw, ACTOR_PARTNER, LVar1)
    EndLoop
    Call(SetActorYaw, ACTOR_PARTNER, 0)
    IfEq(LVarA, 0)
    Else
        Call(ShowVariableMessageBox, 38, 60, LVarA)
    EndIf
    Call(WaitForMessageBoxDone)
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_8023AF68 = {
    Call(PartnerYieldTurn)
    Call(UseBattleCamPreset, 51)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983046)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Sub(LVar0, 15)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(0.4))
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 8, false, true, false)
    Sub(LVar0, 5)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 4, false, true, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983041)
    Wait(15)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(6.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 983043)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983041)
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_8023B110 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_battle_partner_sushie_EVS_8023D8B0))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_battle_partner_sushie_EVS_80238470))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_battle_partner_sushie_EVS_80239010))
    Call(BindHandlePhase, ACTOR_SELF, Ref(battle_partner_sushie_EVS_HandlePhase))
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_8023C070 = {
    Exec(TTYD64_Script_NukeTracker)
    Call(LoadActionCommand, ACTION_COMMAND_SQUIRT)
    Call(action_command_squirt_init)
    Call(GetActorLevel, 256, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetupMashMeter, 3, 40, 75, 100, 0, 0)
        CaseEq(1)
            Call(SetupMashMeter, 4, 35, 60, 80, 100, 0)
        CaseEq(2)
            Call(SetupMashMeter, 5, 20, 40, 60, 80, 100)
    EndSwitch
    Call(UseBattleCamPreset, 13)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 40)
    Call(InitTargetIterator)
    Thread
        Call(SetAnimation, ACTOR_PARTNER, -1, 983045)
        Wait(5)
        Call(SetAnimation, ACTOR_PARTNER, -1, 983046)
    EndThread
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.0))
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Exec(TTYD64_Script_InitTracker)
    Thread
        Loop(3)
            ExecWait(TTYD64_Script_TimingTutor)
            Wait(1)
        EndLoop
    EndThread
    Call(JumpToGoal, ACTOR_PARTNER, 10, false, true, false)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Call(TTYD64_StylishAddCount, LVar0)
        Set(LVarA, 0)
        ExecWait(TTYD64_Script_DoStylishFX)
        Call(PlaySoundAtActor, ACTOR_SELF, 8244)
        Thread
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            SetTimescale(Float(3.0))
            Call(MakeLerp, 0, -180, 8, 0)
            Loop(0)
                Call(UpdateLerp)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
            Call(MakeLerp, -180, 0, 8, 0)
            Loop(0)
                Call(UpdateLerp)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
            SetTimescale(Float(1.0))
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 9, 0)
        EndThread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.4))
        Call(JumpToGoal, ACTOR_SELF, 20, false, false, false)
    EndIf
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Call(battle_partner_sushie_SetSquirtAngle)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983049)
    Call(AddBattleCamDist, -80)
    Call(MoveBattleCamOver, 90)
    Call(action_command_squirt_start, 0, 87, 3)
    Loop(90)
        Call(GetActionProgress, LVar0)
        IfEq(LVar0, 0)
            Call(GetActorScale, -127, LVar0, LVar1, LVar2)
            SetF(LVar1, LVar0)
            SubF(LVar1, Float(1.0))
            DivF(LVar1, 4)
            SubF(LVar0, LVar1)
        Else
            SetF(LVar0, LVar0)
            DivF(LVar0, 100)
            SetF(LVar1, Float(1.0))
            AddF(LVar0, LVar1)
        EndIf
        Call(SetActorScale, ACTOR_SELF, LVar0, LVar0, Float(1.0))
        SetF(LVarE, LVar0)
        Wait(1)
    EndLoop
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_SUSHIE_SQUIRT)
    Call(UseBattleCamPreset, 3)
    Call(MoveBattleCamOver, 10)
    Call(PartnerTestEnemy, LVar0, 268435460, 20, 0, 1, 16)
    IfEq(LVar0, 6)
        Call(SetAnimation, ACTOR_PARTNER, -1, 983050)
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
        Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Add(LVar0, 10)
        Add(LVar1, 11)
        Call(GetGoalPos, ACTOR_PARTNER, LVar3, LVar4, LVar5)
        Call(battle_partner_sushie_GetSquirtTargetPos)
        Call(PlayEffect_impl, 89, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, LVarE, 10, 0, 0, 0, 0)
        Wait(20)
        ExecWait(TTYD64_battle_partner_sushie_EVS_8023D9CC)
        Return
    EndIf
    Call(SetAnimation, ACTOR_PARTNER, -1, 983050)
    Thread
        Call(battle_partner_sushie_InflateSushie)
    EndThread
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Add(LVar1, 11)
    Call(GetGoalPos, ACTOR_PARTNER, LVar3, LVar4, LVar5)
    Call(PlayEffect_impl, 89, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, LVarE, 10, 0, 0, 0, 0)
    Exec(TTYD64_Script_InitTracker)
    Wait(10)
    Call(GetActionProgress, LVar0)
    Call(battle_partner_sushie_GetSquirtDamage)
    Switch(LVar0)
        CaseGt(0)
            Call(PartnerDamageEnemy, LVar0, 268435460, 530, 0, LVarF, 112)
            Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_HIT_RATTLE)
        CaseDefault
            Call(PartnerDamageEnemy, LVar0, 268435460, 530, 0, LVarF, 48)
            Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_HIT_RATTLE)
    EndSwitch
    Call(GetActionProgress, LVar0)
    IfGt(LVar0, 80)
        ExecGetTID(TTYD64_battle_partner_sushie_EVS_8023D4E0, LVar9)
        Loop(0)
            IsThreadRunning(LVar9, LVar0)
            IfEq(LVar0, 0)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndIf
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_partner_sushie_EVS_8023D9CC)
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
            ExecWait(TTYD64_battle_partner_sushie_EVS_8023D944)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_8023CB68 = {
    Exec(TTYD64_Script_NukeTracker)
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(LoadActionCommand, ACTION_COMMAND_TIDAL_WAVE)
    Call(action_command_tidal_wave_init)
    Call(SetupMashMeter, 5, 20, 30, 60, 80, 100)
    Call(InitTargetIterator)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, -65, 53, 10)
    Call(SetBattleCamOffsetY, 16)
    Call(SetBattleCamDist, 214)
    Call(MoveBattleCamOver, 20)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983043)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(0.5))
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 5, false, true, false)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.0))
    Call(AddGoalPos, ACTOR_PARTNER, 30, 40, 0)
    Call(JumpToGoal, ACTOR_PARTNER, 15, false, true, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983041)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983051)
    Call(action_command_tidal_wave_start, 0, 100, 3)
    Call(SetActorRotationOffset, ACTOR_PARTNER, 0, 12, 0)
    Thread
        Wait(54)
        Loop(8)
            Call(SetActorDispOffset, ACTOR_PARTNER, 0, 0, 0)
            Wait(1)
            Call(SetActorDispOffset, ACTOR_PARTNER, -1, 0, 0)
            Wait(1)
        EndLoop
        Loop(7)
            Call(SetActorDispOffset, ACTOR_PARTNER, 1, 0, 0)
            Wait(1)
            Call(SetActorDispOffset, ACTOR_PARTNER, -1, 0, 0)
            Wait(1)
        EndLoop
        Loop(8)
            Call(SetActorDispOffset, ACTOR_PARTNER, 1, 0, 0)
            Wait(1)
            Call(SetActorDispOffset, ACTOR_PARTNER, -2, 0, 0)
            Wait(1)
        EndLoop
        Call(SetActorDispOffset, ACTOR_PARTNER, 0, 0, 0)
    EndThread
    Loop(100)
        Call(GetActionProgress, LVar0)
        Call(battle_partner_sushie_SetScaleTidalWaveCharge)
        Wait(1)
    EndLoop
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 5)
    Wait(10)
    Call(EnableActorBlur, ACTOR_PARTNER, 1)
    Call(battle_partner_sushie_ProcessTidalWave)
    Call(SetActorPos, ACTOR_PARTNER, -220, 0, 0)
    Call(EnableActorBlur, ACTOR_PARTNER, 0)
    Wait(15)
    Call(UseBattleCamPreset, 3)
    Call(MoveBattleCamOver, 20)
    Call(GetMashActionQuality, LVar0)
    Set(LVarE, LVar0)
    Set(LVarF, LVar0)
    Call(InitTargetIterator)
    Loop(0)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(PartnerTestEnemy, LVar0, 0, 20, 0, 2, 16)
        IfEq(LVar0, 6)
            Goto(10)
        EndIf
        Switch(LVarE)
            CaseGe(6)
                Call(PartnerDamageEnemy, LVar0, 805306372, 0, 0, LVarF, 112)
            CaseDefault
                Call(PartnerDamageEnemy, LVar0, 805306372, 0, 0, LVarF, 48)
        EndSwitch
        Wait(5)
        Label(10)
        Call(ChooseNextTarget, 0, LVar0)
        IfEq(LVar0, -1)
            BreakLoop
        EndIf
    EndLoop
    Call(PartnerYieldTurn)
    Exec(TTYD64_Script_InitTracker)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(AddGoalPos, ACTOR_PARTNER, 0, 150, 0)
    Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(SetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(SetActorRotationOffset, ACTOR_PARTNER, 0, 0, 0)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.0))
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983041)
    Call(JumpToGoal, ACTOR_PARTNER, 40, false, true, false)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(0.7))
    ExecWait(TTYD64_Script_TydalWave_GoBackToHome)
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_8023D234 = {
    Loop(5)
        ExecWait(TTYD64_Script_TimingTutor)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Call(TTYD64_StylishAddCount, LVar0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            Thread
                SetTimescale(Float(3.0))
                Call(PlaySound, 8244)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 15, 0)
                Call(MakeLerp, 0, 180, 15, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
                Call(MakeLerp, -180, 0, 10, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
                SetTimescale(Float(1.0))
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            EndThread
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_8023D4E0 = {
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
                Call(SetAnimation, ACTOR_PARTNER, -1, 983057)
                Wait(25)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndIf
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_8023D654 = {
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(6.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 983043)
    Call(SetActorYaw, ACTOR_PARTNER, 0)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983041)
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_8023D738 = {
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar0, 40)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(4.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 983043)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983041)
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_8023D8B0 = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_battle_partner_sushie_EVS_802393D4)
        CaseEq(5)
            ExecWait(TTYD64_battle_partner_sushie_EVS_8023DA54)
        CaseEq(3)
            ExecWait(TTYD64_battle_partner_sushie_EVS_8023DAA0)
        CaseEq(7)
            ExecWait(TTYD64_battle_partner_sushie_EVS_8023D654)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_8023D944 = {
    Call(PartnerYieldTurn)
    Call(UseBattleCamPreset, 4)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983043)
    Call(FlyToGoal, ACTOR_PARTNER, 30, 0, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983041)
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_8023D9CC = {
    Call(PartnerYieldTurn)
    Call(UseBattleCamPreset, 51)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983043)
    Call(FlyToGoal, ACTOR_PARTNER, 30, 0, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983041)
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_8023DA54 = {
    Call(SetAnimation, ACTOR_PARTNER, -1, 983057)
    Wait(36)
    Call(SetAnimation, ACTOR_PARTNER, -1, 983041)
    Return
    End
};

EvtScript TTYD64_battle_partner_sushie_EVS_8023DAA0 = {
    SetConst(LVar0, 1)
    SetConst(LVar1, 983043)
    ExecWait(EVS_Partner_RunAway)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_partner_sushie(void) {
    Mod_ReplaceActorBlueprint("TTYD64", &battle_partner_sushie, &TTYD64_battle_partner_sushie);
}
