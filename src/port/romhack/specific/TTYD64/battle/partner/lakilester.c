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

extern ActorBlueprint battle_partner_lakilester;
extern EvtScript battle_partner_lakilester_EVS_HandlePhase;
extern EvtScript battle_partner_lakilester_EVS_Idle;
API_CALLABLE(AddBattleCamDist);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(DisableBattleCamClampX);
API_CALLABLE(FallToGoal);
API_CALLABLE(FlyToGoal);
API_CALLABLE(GetActionProgress);
API_CALLABLE(GetActorLevel);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetMashActionQuality);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetPartnerActionQuality);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(InterruptActionCommand);
API_CALLABLE(JumpPartTo);
API_CALLABLE(LandJumpPart);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(LoadItemScript);
API_CALLABLE(LoadStarPowerScript);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PartnerDamageEnemy);
API_CALLABLE(PartnerTestEnemy);
API_CALLABLE(PartnerYieldTurn);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerFallToGoal);
API_CALLABLE(PlayerHopToGoal);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActor);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActionHudPrepareTime);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetDamageSource);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(SetPartDispOffset);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartRotation);
API_CALLABLE(SetupMashMeter);
API_CALLABLE(ShowActionHud);
API_CALLABLE(ShowMessageBox);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(WaitForMessageBoxDone);
API_CALLABLE(action_command_hurricane_init);
API_CALLABLE(action_command_hurricane_start);
API_CALLABLE(action_command_spiny_surge_init);
API_CALLABLE(action_command_spiny_surge_start);
API_CALLABLE(action_command_three_chances_init);
API_CALLABLE(action_command_three_chances_start);
API_CALLABLE(battle_partner_lakilester_AllEnemiesBlownAway);
API_CALLABLE(battle_partner_lakilester_ApplyCloudNine);
API_CALLABLE(battle_partner_lakilester_BlowTargetAway);
API_CALLABLE(battle_partner_lakilester_CanTargetBeBlown);
API_CALLABLE(battle_partner_lakilester_GetSpinySurgeDamage);
API_CALLABLE(battle_partner_lakilester_InitHurricane);
API_CALLABLE(battle_partner_lakilester_IsHurricaneActive);
API_CALLABLE(battle_partner_lakilester_ProcessHurricane);
API_CALLABLE(battle_partner_lakilester_RemoveCloudNineFX);
API_CALLABLE(battle_partner_lakilester_SpawnCloudNineFX);
API_CALLABLE(battle_partner_lakilester_SpinyFlipActionCommand);
API_CALLABLE(battle_partner_lakilester_SpinyFlipUpdatePopup);
API_CALLABLE(battle_partner_lakilester_ThrowSpinyFX);
EvtScript TTYD64_battle_partner_lakilester_EVS_80239874;
EvtScript TTYD64_battle_partner_lakilester_EVS_8023A0EC;
extern s32 TTYD64_battle_partner_lakilester_DefenseTable_Lakilester_8023A1F8[];
extern ActorBlueprint TTYD64_battle_partner_lakilester;
EvtScript TTYD64_battle_partner_lakilester_EVS_8023A320;
EvtScript TTYD64_battle_partner_lakilester_EVS_8023A390;
EvtScript TTYD64_battle_partner_lakilester_EVS_8023A754;
EvtScript TTYD64_battle_partner_lakilester_EVS_8023A8EC;
EvtScript TTYD64_battle_partner_lakilester_EVS_8023B618;
EvtScript TTYD64_battle_partner_lakilester_EVS_8023BF50;
EvtScript TTYD64_battle_partner_lakilester_EVS_8023C6A4;
EvtScript TTYD64_battle_partner_lakilester_EVS_8023D044;
EvtScript TTYD64_battle_partner_lakilester_EVS_8023D4A8;
EvtScript TTYD64_battle_partner_lakilester_EVS_8023D82C;
extern s32 TTYD64_battle_partner_lakilester_StatusTable_Lakilester_8023A204[];
EvtScript TTYD64_battle_partner_lakilester_EVS_8023DB54;
EvtScript TTYD64_battle_partner_lakilester_EVS_8023DBE8;
EvtScript TTYD64_battle_partner_lakilester_EVS_8023DC70;
extern s32 TTYD64_battle_partner_lakilester_IdleAnimations_Lakilester_8023A1D0[];
EvtScript TTYD64_battle_partner_lakilester_EVS_8023DD34;
extern ActorPartBlueprint TTYD64_battle_partner_lakilester_PartsTable_Lakilester_8023A2B0[];
EvtScript TTYD64_battle_partner_lakilester_EVS_8023DE60;
extern s32 TTYD64_battle_partner_lakilester_IdleAnimations_Lakilester_8023A1EC[];

// clang-format off
s32 TTYD64_battle_partner_lakilester_DefenseTable_Lakilester_8023A1F8[] = {
    1, 0, 0,
};

ActorBlueprint TTYD64_battle_partner_lakilester = {
    .flags = 512,
    .type = 118,
    .level = 0,
    .maxHP = 99,
    .partCount = 2,
    .unk_0A = { 0, 0 },
    .partsData = TTYD64_battle_partner_lakilester_PartsTable_Lakilester_8023A2B0,
    .initScript = &TTYD64_battle_partner_lakilester_EVS_8023A320,
    .statusTable = TTYD64_battle_partner_lakilester_StatusTable_Lakilester_8023A204,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 44, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 30 },
    .statusTextOffset = { 13, 31 },
};

s32 TTYD64_battle_partner_lakilester_StatusTable_Lakilester_8023A204[] = {
    1, 100, 2, 100, 6, 100, 9, 100,
    7, 100, 4, 100, 3, 100, 11, 100,
    5, 100, 10, 100, 8, 100, 31, 0,
    32, 0, 37, 0, 34, 0, 36, 0,
    35, 0, 33, 0, 38, 0, 39, 0,
    41, 0, 0,
};

s32 TTYD64_battle_partner_lakilester_IdleAnimations_Lakilester_8023A1D0[] = {
    1, 1048578, 12, 1048576, 6, 1048603, 9, 1048604,
    8, 1048576, 4, 1048584, 13, 1048584, 18, 1048576,
    26, 1048604, 7, 1048576, 48, 1048602, 0,
};

ActorPartBlueprint TTYD64_battle_partner_lakilester_PartsTable_Lakilester_8023A2B0[] = {
    {
        .flags = 0,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 12, 30 },
        .opacity = 255,
        .idleAnimations = TTYD64_battle_partner_lakilester_IdleAnimations_Lakilester_8023A1D0,
        .defenseTable = TTYD64_battle_partner_lakilester_DefenseTable_Lakilester_8023A1F8,
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
        .unk_1E = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 1048577,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = TTYD64_battle_partner_lakilester_IdleAnimations_Lakilester_8023A1EC,
        .defenseTable = TTYD64_battle_partner_lakilester_DefenseTable_Lakilester_8023A1F8,
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
        .unk_1E = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_battle_partner_lakilester_IdleAnimations_Lakilester_8023A1EC[] = {
    1, 1048596, 0,
};

EvtScript TTYD64_battle_partner_lakilester_EVS_80239874 = {
    Call(UseIdleAnimation, ACTOR_PLAYER, false)
    Call(SetBattleFlagBits, BS_FLAGS1_SHOW_PLAYER_DECORATIONS, 0)
    Call(SetActorFlagBits, ACTOR_PLAYER, ACTOR_FLAG_NO_INACTIVE_ANIM, 1)
    Call(LoadActionCommand, ACTION_COMMAND_THREE_CHANCES)
    Call(action_command_three_chances_init, 2)
    Call(SetActionHudPrepareTime, 50)
    Call(InitTargetIterator)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(UseBattleCamPreset, 10)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamOffsetY, 17)
    Call(SetBattleCamDist, 300)
    Call(MoveBattleCamOver, 30)
    Call(DisableBattleCamClampX)
    Wait(10)
    Thread
        Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Add(LVar1, 40)
        Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Call(FlyToGoal, ACTOR_PARTNER, 30, 0, 10)
    EndThread
    Wait(15)
    Set(LVar0, 0)
    Loop(10)
        Add(LVar0, 18)
        Call(SetActorYaw, ACTOR_PARTNER, LVar0)
        Wait(1)
    EndLoop
    Wait(10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048581)
    Wait(5)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048580)
    Wait(15)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar0, -12)
    Add(LVar1, 13)
    Add(LVar2, -5)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(4.0))
    Call(SetActorJumpGravity, ACTOR_PLAYER, Float(1.0))
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 65568)
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(PlayerHopToGoal, 18, 0, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65568)
    Wait(3)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Call(action_command_three_chances_start, 0, 97, 3)
    Call(AddBattleCamDist, -75)
    Call(MoveBattleCamOver, 100)
    Call(SetBattleCamTargetingModes, 0, 0, 1)
    Wait(100)
    Exec(TTYD64_Script_InitTracker)
    Wait(3)
    Call(AddBattleCamDist, 50)
    Call(MoveBattleCamOver, 5)
    Call(GetPartnerActionQuality, LVarA)
    IfGt(LVarA, 0)
        Call(battle_partner_lakilester_RemoveCloudNineFX)
        Call(PlaySoundAtActor, ACTOR_PARTNER, 8221)
        Call(battle_partner_lakilester_SpawnCloudNineFX)
        Call(battle_partner_lakilester_ApplyCloudNine)
        Call(SetActorFlagBits, ACTOR_PLAYER, ACTOR_FLAG_SHOW_STATUS_ICONS, 1)
    EndIf
    Call(UseIdleAnimation, ACTOR_PLAYER, true)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048582)
    Thread
        Call(GetActorPos, ACTOR_PLAYER, LVar3, LVar4, LVar5)
        Loop(10)
            Set(LVar0, LVar3)
            Set(LVar1, LVar4)
            Set(LVar2, LVar5)
            Call(RandInt, 40, LVar6)
            Sub(LVar6, 20)
            Add(LVar0, LVar6)
            Call(RandInt, 30, LVar6)
            Sub(LVar6, 15)
            Add(LVar1, LVar6)
            Call(PlayEffect_impl, 105, 0, LVar0, LVar1, LVar2, Float(1.0), 20, 0, 0, 0, 0, 0, 0, 0)
            Wait(1)
        EndLoop
    EndThread
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 65568)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(PlayerFallToGoal, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048578)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65568)
    ExecGetTID(TTYD64_battle_partner_lakilester_EVS_8023A754, LVar9)
    Loop(0)
        IsThreadRunning(LVar9, LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Wait(7)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Thread
        Call(SetGoalToHome, ACTOR_PLAYER)
        Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
        Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
        Call(PlayerRunToGoal, 0)
        Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
        Call(SetActorFlagBits, ACTOR_PLAYER, ACTOR_FLAG_NO_INACTIVE_ANIM, 0)
    EndThread
    Thread
        Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Sub(LVar1, 40)
        Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Call(FlyToGoal, ACTOR_PARTNER, 30, 0, 10)
    EndThread
    Wait(15)
    Set(LVar0, 180)
    Loop(10)
        Sub(LVar0, 18)
        Call(SetActorYaw, ACTOR_PARTNER, LVar0)
        Wait(1)
    EndLoop
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Wait(10)
    IfGt(LVarA, 0)
        Call(ShowMessageBox, 40, 60)
        Call(WaitForMessageBoxDone)
    EndIf
    Call(SetBattleFlagBits, BS_FLAGS1_SHOW_PLAYER_DECORATIONS, 1)
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023A0EC = {
    Call(PlaySoundAtActor, ACTOR_SELF, 8815)
    SetTimescale(Float(3.0))
    Loop(1)
        Call(MakeLerp, 0, -180, 12, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(SetActorRotation, ACTOR_SELF, 0, LVar0, 0)
            Call(SetPartRotation, ACTOR_SELF, 2, 0, LVar0, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(MakeLerp, -180, 0, 12, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(SetActorRotation, ACTOR_SELF, 0, LVar0, 0)
            Call(SetPartRotation, ACTOR_SELF, 2, 0, LVar0, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndLoop
    SetTimescale(Float(1.0))
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, 0)
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023A320 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_battle_partner_lakilester_EVS_8023DB54))
    Call(BindIdle, ACTOR_SELF, Ref(battle_partner_lakilester_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_battle_partner_lakilester_EVS_8023A390))
    Call(BindHandlePhase, ACTOR_SELF, Ref(battle_partner_lakilester_EVS_HandlePhase))
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023A390 = {
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(InterruptActionCommand)
    Call(GetLastEvent, ACTOR_PARTNER, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, -1)
            Set(LVar1, 1048586)
            ExecWait(EVS_Enemy_Hit)
            Call(SetAnimation, ACTOR_PARTNER, -1, 1048578)
        EndCaseGroup
        CaseOrEq(23)
        CaseOrEq(25)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8332)
            Call(TTYD64_GetPartnerExtraBattleData_API, 14, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 1048576)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 1048602)
            EndIf
            ExecWait(EVS_Enemy_NoDamageHit)
        EndCaseGroup
        CaseEq(42)
            SetConst(LVar1, 1048586)
            SetConst(LVar2, 20)
            ExecWait(EVS_Partner_SpikeContact)
        CaseEq(44)
            SetConst(LVar1, 1048588)
            Set(LVar2, 20)
            SetConst(LVar3, 1048589)
            ExecWait(EVS_Partner_BurnContact)
        CaseEq(14)
            SetConst(LVar1, 1048588)
            SetConst(LVar2, 1048589)
            ExecWait(EVS_Partner_BurnHit)
        CaseEq(47)
            SetConst(LVar1, 1048586)
            Set(LVar2, 20)
            ExecWait(EVS_Partner_ShockHit)
        CaseEq(51)
        CaseEq(52)
            SetConst(LVar0, 1)
            SetConst(LVar1, 1048578)
            SetConst(LVar2, 1048579)
            Set(LVar3, 4)
            ExecWait(EVS_Partner_Recover)
        CaseOrEq(24)
        CaseOrEq(26)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8332)
            SetConst(LVar0, 1)
            SetConst(LVar1, 1048602)
            ExecWait(EVS_Enemy_NoDamageHit)
            Wait(10)
        CaseEq(32)
            Set(LVar0, -1)
            Set(LVar1, 1048586)
            ExecWait(TTYD64_PartnerDies)
            Return
        CaseEq(TTYD64_EVENT_SUPERGUARD)
            Set(LVar0, -1)
            Set(LVar1, 1048598)
            ExecWait(TTYD64_DoSuperguard)
        EndCaseGroup
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023A754 = {
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
                Call(SetAnimation, ACTOR_PARTNER, -1, 1048583)
                Wait(25)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndIf
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023A8EC = {
    Exec(TTYD64_Script_NukeTracker)
    Thread
        Call(battle_partner_lakilester_SpinyFlipUpdatePopup)
    EndThread
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048579)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar0, 40)
    Add(LVar1, 20)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_PARTNER, 30, 0, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048577)
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, 47, 46, 12)
    Call(SetBattleCamOffsetY, 7)
    Call(SetBattleCamDist, 416)
    Call(MoveBattleCamOver, 30)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar0, 3)
    Add(LVar1, 10)
    Add(LVar2, 5)
    Call(SetPartPos, ACTOR_PARTNER, 2, LVar0, LVar1, LVar2)
    Wait(1)
    Call(SetPartFlagBits, ACTOR_PARTNER, 2, ACTOR_PART_FLAG_INVISIBLE, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 1048596)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048591)
    Loop(4)
        Add(LVar1, 6)
        Call(SetPartPos, ACTOR_PARTNER, 2, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar0, 8)
    Add(LVar1, 40)
    Add(LVar2, 5)
    Call(PlayEffect_impl, 107, 0, LVar0, LVar1, LVar2, Float(1.0), 80, 0, 0, 0, 0, 0, 0, 0)
    Call(SetActorVar, ACTOR_PARTNER, 0, 1)
    Thread
        Loop(40)
            Call(SetActorDispOffset, ACTOR_PARTNER, 1, 0, 0)
            Call(SetPartDispOffset, ACTOR_PARTNER, 2, 1, 0, 0)
            Wait(1)
            Call(SetActorDispOffset, ACTOR_PARTNER, -1, 0, 0)
            Call(SetPartDispOffset, ACTOR_PARTNER, 2, -1, 0, 0)
            Wait(1)
            Call(GetActorVar, ACTOR_PARTNER, 0, LVar0)
            IfEq(LVar0, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(SetActorDispOffset, ACTOR_PARTNER, 0, 0, 0)
        Call(SetPartDispOffset, ACTOR_PARTNER, 2, 0, 0, 0)
    EndThread
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Thread
        Wait(30)
        Exec(TTYD64_Script_InitTracker)
        Wait(40)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 0)
            Loop(8)
                Call(GetActorVar, ACTOR_SELF, 0, LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                ExecWait(TTYD64_Script_TimingTutor)
                Call(TTYD64_StylishPressed, LVar0)
                IfEq(LVar0, 1)
                    Call(TTYD64_StylishAddCount, LVar0)
                    Set(LVarA, 0)
                    ExecWait(TTYD64_Script_DoStylishFX)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        Else
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
        EndIf
    EndThread
    Call(battle_partner_lakilester_SpinyFlipActionCommand)
    Call(SetActorVar, ACTOR_PARTNER, 0, 0)
    Wait(5)
    Call(TTYD64_StylishGetCount, LVar0)
    IfGt(LVar0, 0)
        ExecGetTID(TTYD64_battle_partner_lakilester_EVS_8023A0EC, LVar1)
        Loop(0)
            IsThreadRunning(LVar1, LVar0)
            IfEq(LVar0, 0)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndIf
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048594)
    Wait(3)
    Call(PartnerTestEnemy, LVar0, 0, 20, 0, 2, 16)
    IfEq(LVar0, 6)
        Set(LVarF, -1)
    EndIf
    Exec(TTYD64_Script_InitTracker)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8219)
    Switch(LVarF)
        CaseEq(-1)
            Call(SetAnimation, ACTOR_SELF, 2, 1048597)
            Call(SetPartJumpGravity, ACTOR_PARTNER, 2, Float(1.5))
            Set(LVar0, LVar7)
            Set(LVar1, LVar8)
            Set(LVar2, LVar9)
            Call(JumpPartTo, ACTOR_PARTNER, 2, LVar7, LVar8, LVar9, 20)
            Call(LandJumpPart, 256, 2)
        CaseEq(0)
            Call(SetAnimation, ACTOR_SELF, 2, 1048597)
            Call(SetPartJumpGravity, ACTOR_PARTNER, 2, Float(1.5))
            Set(LVar0, LVar7)
            Set(LVar1, LVar8)
            Set(LVar2, LVar9)
            Call(JumpPartTo, ACTOR_PARTNER, 2, LVar7, LVar8, LVar9, 20)
            Call(LandJumpPart, 256, 2)
        CaseDefault
            Call(SetAnimation, ACTOR_SELF, 2, 1048597)
            Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(SetPartJumpGravity, ACTOR_PARTNER, 2, Float(1.5))
            Call(JumpPartTo, ACTOR_PARTNER, 2, LVar0, LVar1, LVar2, 20)
    EndSwitch
    Thread
        Add(LVar0, 50)
        Set(LVar1, 0)
        Call(SetPartJumpGravity, ACTOR_PARTNER, 2, Float(1.5))
        Call(JumpPartTo, ACTOR_PARTNER, 2, LVar0, LVar1, LVar2, 15)
        Call(SetPartFlagBits, ACTOR_PARTNER, 2, ACTOR_PART_FLAG_INVISIBLE, 1)
    EndThread
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(173)
            Set(LVarE, 3)
        CaseEq(174)
            Set(LVarE, 4)
        CaseEq(175)
            Set(LVarE, 5)
    EndSwitch
    Switch(LVarF)
        CaseGt(0)
            Call(PartnerDamageEnemy, LVar0, 268500992, 0, 0, LVarE, 112)
            Set(LVarB, LVar0)
            Call(TTYD64_StylishPressed, LVar1)
            IfEq(LVar1, 0)
                Loop(4)
                    ExecWait(TTYD64_Script_TimingTutor)
                    Call(TTYD64_StylishPressed, LVar1)
                    IfEq(LVar1, 1)
                        Call(TTYD64_StylishDisarm)
                        Call(TTYD64_StylishConsume)
                        Call(TTYD64_StylishAddCount, LVar1)
                        Set(LVarA, 0)
                        ExecWait(TTYD64_Script_DoStylishFX)
                        Call(SetAnimation, ACTOR_PARTNER, -1, 1048583)
                        Wait(25)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
            EndIf
            Set(LVar0, LVarB)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
        CaseDefault
            Set(LVar0, 2)
    EndSwitch
    Switch(LVarF)
        CaseEq(1)
            Call(UseBattleCamPreset, 4)
        CaseDefault
            Call(UseBattleCamPreset, 51)
    EndSwitch
    Wait(15)
    Switch(LVar0)
        CaseOrEq(1)
        CaseOrEq(3)
            ExecWait(TTYD64_battle_partner_lakilester_EVS_8023D044)
        EndCaseGroup
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_partner_lakilester_EVS_8023DBE8)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023B618 = {
    Exec(TTYD64_Script_NukeTracker)
    Call(LoadActionCommand, ACTION_COMMAND_SPINY_SURGE)
    Call(action_command_spiny_surge_init)
    Call(GetActorLevel, 256, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetupMashMeter, 2, 99, 100, 0, 0, 0)
        CaseEq(1)
            Call(SetupMashMeter, 3, 70, 99, 100, 0, 0)
        CaseEq(2)
            Call(SetupMashMeter, 4, 40, 70, 99, 100, 0)
    EndSwitch
    Call(SetActionHudPrepareTime, 10)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, 45, 60, 0)
    Call(SetBattleCamOffsetY, 0)
    Call(SetBattleCamDist, 400)
    Call(MoveBattleCamOver, 30)
    Call(InitTargetIterator)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048579)
    Call(AddGoalPos, ACTOR_PARTNER, 60, 20, 0)
    Call(FlyToGoal, ACTOR_PARTNER, 30, 0, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048577)
    Wait(10)
    Exec(TTYD64_Script_InitTracker)
    Call(GetActorLevel, 256, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Set(LVarA, 60)
        CaseEq(1)
            Set(LVarA, 60)
        CaseEq(2)
            Set(LVarA, 60)
    EndSwitch
    Set(LVarB, LVarA)
    Add(LVarB, -3)
    Call(action_command_spiny_surge_start, 0, LVarB, 3)
    Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
    Call(InitTargetIterator)
    Call(SetActorVar, ACTOR_PARTNER, 0, 0)
    Set(LVar9, 0)
    Set(LFlag2, 0)
    Set(LFlag3, 0)
    Loop(LVarA)
        Call(GetActionProgress, LVar0)
        IfEq(LVar9, 2)
            Set(LVar0, 3)
        EndIf
        Switch(LVar0)
            CaseEq(-1)
                Set(LVar9, 0)
                Call(SetPartFlagBits, ACTOR_PARTNER, 2, ACTOR_PART_FLAG_INVISIBLE, 1)
                Call(SetAnimation, ACTOR_PARTNER, -1, 1048577)
            CaseEq(1)
                IfEq(LVar9, 1)
                    BreakSwitch
                EndIf
                Call(SetPartFlagBits, ACTOR_PARTNER, 2, ACTOR_PART_FLAG_INVISIBLE, 0)
                Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
                Add(LVar0, 3)
                Add(LVar1, 34)
                Add(LVar2, 5)
                Call(SetPartPos, ACTOR_PARTNER, 2, LVar0, LVar1, LVar2)
                Call(SetAnimation, ACTOR_PARTNER, -1, 1048591)
                Set(LVar9, 1)
            CaseEq(2)
                IfEq(LVar9, 0)
                    BreakSwitch
                EndIf
                IfEq(LFlag2, 0)
                    Call(PlaySoundAtActor, ACTOR_PARTNER, 8219)
                    Set(LFlag2, 1)
                Else
                    Call(PlaySoundAtActor, ACTOR_PARTNER, 8220)
                    Set(LFlag2, 0)
                EndIf
                Call(battle_partner_lakilester_ThrowSpinyFX)
                Call(SetAnimation, ACTOR_PARTNER, -1, 1048595)
                Call(SetPartFlagBits, ACTOR_PARTNER, 2, ACTOR_PART_FLAG_INVISIBLE, 1)
                ChildThread
                    Call(GetActorVar, ACTOR_PARTNER, 0, LVar0)
                    Add(LVar0, 1)
                    Call(SetActorVar, ACTOR_PARTNER, 0, LVar0)
                    Wait(15)
                    Call(GetActorVar, ACTOR_PARTNER, 0, LVar0)
                    Sub(LVar0, 1)
                    Call(SetActorVar, ACTOR_PARTNER, 0, LVar0)
                EndChildThread
                Set(LFlag3, 1)
                Set(LVar9, 0)
        EndSwitch
        Wait(1)
    EndLoop
    Call(SetPartFlagBits, ACTOR_PARTNER, 2, ACTOR_PART_FLAG_INVISIBLE, 1)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048577)
    Loop(0)
        Call(GetActorVar, ACTOR_PARTNER, 0, LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Wait(10)
    IfEq(LFlag3, 0)
        Set(LVar0, 0)
        Set(LVarF, 0)
        Wait(15)
        Goto(13)
    EndIf
    Call(InitTargetIterator)
    Label(0)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(PartnerTestEnemy, LVar0, 0, 20, 0, 2, 16)
    IfEq(LVar0, 6)
        Goto(12)
    EndIf
    Call(GetPartnerActionQuality, LVarA)
    Call(battle_partner_lakilester_GetSpinySurgeDamage)
    Switch(LVar0)
        CaseGt(0)
            Call(PartnerDamageEnemy, LVar0, 805371904, 0, 0, LVarF, 112)
        CaseDefault
            Call(PartnerDamageEnemy, LVar0, 805371904, 0, 0, LVarF, 48)
    EndSwitch
    Switch(LVar0)
        CaseGt(0)
            Call(UseBattleCamPreset, 4)
        CaseDefault
            Call(UseBattleCamPreset, 51)
    EndSwitch
    Wait(6)
    Label(12)
    Call(ChooseNextTarget, 0, LVar1)
    IfNe(LVar1, -1)
        Goto(0)
    EndIf
    Wait(30)
    Label(13)
    Switch(LVar0)
        CaseOrEq(1)
        CaseOrEq(3)
            ExecWait(TTYD64_battle_partner_lakilester_EVS_8023D044)
        EndCaseGroup
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_partner_lakilester_EVS_8023DBE8)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023BF50 = {
    Call(UseIdleAnimation, ACTOR_PLAYER, false)
    Call(LoadActionCommand, ACTION_COMMAND_THREE_CHANCES)
    Call(action_command_three_chances_init, 2)
    Call(SetActionHudPrepareTime, 50)
    Call(battle_partner_lakilester_RemoveCloudNineFX)
    Call(InitTargetIterator)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(UseBattleCamPreset, 10)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamOffsetY, 0)
    Call(SetBattleCamDist, 300)
    Call(MoveBattleCamOver, 30)
    Call(DisableBattleCamClampX)
    Wait(10)
    Set(LVar0, 0)
    Loop(10)
        Add(LVar0, 18)
        Call(SetActorYaw, ACTOR_PARTNER, LVar0)
        Wait(1)
    EndLoop
    Wait(10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048581)
    Wait(20)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 12)
    Add(LVar1, -7)
    Add(LVar2, 5)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_PARTNER, 20, -10, 10)
    Thread
        Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Add(LVar1, 40)
        Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Call(FlyToGoal, ACTOR_PLAYER, 20, 0, 10)
    EndThread
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar1, 40)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_PARTNER, 20, 0, 10)
    Call(action_command_three_chances_start, 0, 97, 3)
    Call(AddBattleCamDist, -75)
    Call(MoveBattleCamOver, 100)
    Call(SetBattleCamTargetingModes, 0, 0, 1)
    Wait(100)
    Exec(TTYD64_Script_InitTracker)
    Wait(3)
    Call(AddBattleCamDist, 50)
    Call(MoveBattleCamOver, 5)
    Call(GetPartnerActionQuality, LVarA)
    IfGt(LVarA, 0)
        Call(PlaySoundAtActor, ACTOR_PARTNER, 8221)
        Call(battle_partner_lakilester_SpawnCloudNineFX)
        Call(battle_partner_lakilester_ApplyCloudNine)
    EndIf
    Call(UseIdleAnimation, ACTOR_PLAYER, true)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048582)
    Thread
        Call(GetActorPos, ACTOR_PLAYER, LVar3, LVar4, LVar5)
        Loop(10)
            Set(LVar0, LVar3)
            Set(LVar1, LVar4)
            Set(LVar2, LVar5)
            Call(RandInt, 40, LVar6)
            Sub(LVar6, 20)
            Add(LVar0, LVar6)
            Call(RandInt, 30, LVar6)
            Sub(LVar6, 15)
            Add(LVar1, LVar6)
            Call(PlayEffect_impl, 105, 0, LVar0, LVar1, LVar2, Float(1.0), 20, 0, 0, 0, 0, 0, 0, 0)
            Wait(1)
        EndLoop
    EndThread
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(FallToGoal, ACTOR_PLAYER, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048578)
    ExecGetTID(TTYD64_battle_partner_lakilester_EVS_8023A754, LVar9)
    Loop(0)
        IsThreadRunning(LVar9, LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Wait(7)
    Thread
        Call(SetGoalToHome, ACTOR_PLAYER)
        Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
        Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
        Call(PlayerRunToGoal, 0)
        Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    EndThread
    Thread
        Call(SetGoalToHome, ACTOR_PARTNER)
        Call(FlyToGoal, ACTOR_PARTNER, 20, 0, 10)
    EndThread
    Set(LVar0, 180)
    Loop(10)
        Sub(LVar0, 18)
        Call(SetActorYaw, ACTOR_PARTNER, LVar0)
        Wait(1)
    EndLoop
    Call(PartnerYieldTurn)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Wait(10)
    IfGt(LVarA, 0)
        Call(ShowMessageBox, 40, 60)
        Call(WaitForMessageBoxDone)
    EndIf
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023C6A4 = {
    Exec(TTYD64_Script_NukeTracker)
    Call(LoadActionCommand, ACTION_COMMAND_HURRICANE)
    Call(action_command_hurricane_init)
    Call(SetupMashMeter, 1, 100, 0, 0, 0, 0)
    Call(SetActionHudPrepareTime, 15)
    Call(SetDamageSource, 20)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, -45, 54, 0)
    Call(SetBattleCamOffsetY, 0)
    Call(SetBattleCamDist, 280)
    Call(MoveBattleCamOver, 40)
    Call(InitTargetIterator)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048579)
    Call(AddGoalPos, ACTOR_PARTNER, 40, 20, 0)
    Call(FlyToGoal, ACTOR_PARTNER, 30, 0, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048577)
    Wait(15)
    Call(battle_partner_lakilester_InitHurricane)
    Call(action_command_hurricane_start, 0, 147, 3, LVar0)
    Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
    Call(SetActorRotationOffset, ACTOR_PARTNER, 0, 20, 0)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, 35, 54, 0)
    Call(SetBattleCamOffsetY, 0)
    Call(SetBattleCamDist, 430)
    Call(MoveBattleCamOver, 150)
    Call(SetBattleCamTargetingModes, 0, 0, 1)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_LAKILESTER_HURRICANE_WIND)
    Thread
        Call(battle_partner_lakilester_ProcessHurricane)
    EndThread
    Wait(2)
    Loop(150)
        Call(battle_partner_lakilester_IsHurricaneActive)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
        Call(GetMashActionQuality, LVar0)
        IfEq(LVar0, 100)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Wait(15)
    Call(GetMashActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(99)
            Call(UseBattleCamPreset, 4)
        CaseDefault
            Call(UseBattleCamPreset, 51)
    EndSwitch
    Call(InitTargetIterator)
    Label(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(battle_partner_lakilester_CanTargetBeBlown)
    IfGt(LVar0, 0)
        Set(LVarA, LVar0)
        Thread
            Call(battle_partner_lakilester_BlowTargetAway)
            Call(SetBattleFlagBits, BS_FLAGS1_STAR_POINTS_DROPPED, 1)
            Call(RemoveActor, LVarA)
        EndThread
    Else
        IfEq(LVar0, 0)
            Call(PartnerDamageEnemy, LVar2, 268435456, 0, 0, 0, 2080)
        EndIf
    EndIf
    Label(11)
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(10)
    EndIf
    Exec(TTYD64_Script_InitTracker)
    Wait(5)
    Call(GetPartnerActionQuality, LVar0)
    IfGe(LVar0, 100)
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
                    Call(SetAnimation, ACTOR_PARTNER, -1, 1048583)
                    Wait(25)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        EndIf
    EndIf
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Wait(25)
    Call(SetActorRotation, ACTOR_PARTNER, 0, 0, 0)
    Call(SetActorRotationOffset, ACTOR_PARTNER, 0, 0, 0)
    ExecWait(TTYD64_battle_partner_lakilester_EVS_8023DBE8)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048578)
    Call(battle_partner_lakilester_AllEnemiesBlownAway)
    Call(PartnerYieldTurn)
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023D044 = {
    Call(GetMenuSelection, 0, 0, LVar0)
    IfEq(LVar0, 176)
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
                    Call(SetAnimation, ACTOR_PARTNER, -1, 1048583)
                    Wait(25)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        EndIf
    EndIf
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Call(PartnerYieldTurn)
    Call(UseBattleCamPreset, 4)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048579)
    Call(FlyToGoal, ACTOR_PARTNER, 15, 0, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048578)
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023D4A8 = {
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Call(ShowActionHud, 1)
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
        CaseEq(173)
            Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
            ExecWait(TTYD64_battle_partner_lakilester_EVS_8023A8EC)
        CaseEq(174)
            Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
            ExecWait(TTYD64_battle_partner_lakilester_EVS_8023A8EC)
        CaseEq(175)
            Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
            ExecWait(TTYD64_battle_partner_lakilester_EVS_8023A8EC)
        CaseEq(176)
            ExecWait(TTYD64_battle_partner_lakilester_EVS_8023B618)
        CaseEq(177)
            Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
            ExecWait(TTYD64_battle_partner_lakilester_EVS_8023DC70)
        CaseEq(178)
            ExecWait(TTYD64_battle_partner_lakilester_EVS_8023C6A4)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023D82C = {
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(6.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048579)
    Call(SetActorYaw, ACTOR_PARTNER, 0)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048578)
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023DB54 = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_battle_partner_lakilester_EVS_8023D4A8)
        CaseEq(5)
            ExecWait(TTYD64_battle_partner_lakilester_EVS_8023DD34)
        CaseEq(3)
            ExecWait(TTYD64_battle_partner_lakilester_EVS_8023DE60)
        CaseEq(7)
            ExecWait(TTYD64_battle_partner_lakilester_EVS_8023D82C)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023DBE8 = {
    Call(PartnerYieldTurn)
    Call(UseBattleCamPreset, 51)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048579)
    Call(FlyToGoal, ACTOR_PARTNER, 15, 0, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 1048578)
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023DC70 = {
    Exec(TTYD64_Script_NukeTracker)
    Call(GetStatusFlags, ACTOR_PLAYER, LVar0)
    IfFlag(LVar0, 3526656)
        ExecWait(TTYD64_battle_partner_lakilester_EVS_8023BF50)
    Else
        ExecWait(TTYD64_battle_partner_lakilester_EVS_80239874)
    EndIf
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023DD34 = {
    SetConst(LVar0, 1)
    SetConst(LVar1, 1048583)
    SetConst(LVar2, 1048578)
    SetConst(LVar3, 1048578)
    ExecWait(EVS_Partner_Celebrate)
    Return
    End
};

EvtScript TTYD64_battle_partner_lakilester_EVS_8023DE60 = {
    SetConst(LVar0, 1)
    SetConst(LVar1, 1048579)
    ExecWait(EVS_Partner_RunAway)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_partner_lakilester(void) {
    Mod_ReplaceActorBlueprint("TTYD64", &battle_partner_lakilester, &TTYD64_battle_partner_lakilester);
}
