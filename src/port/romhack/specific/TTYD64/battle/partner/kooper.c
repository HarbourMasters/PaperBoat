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

extern ActorBlueprint battle_partner_kooper;
API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(CheckButtonDown);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(EnableActorBlur);
API_CALLABLE(EnableActorPaletteEffects);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(FlyToGoal);
API_CALLABLE(GetActionProgress);
API_CALLABLE(GetActorLevel);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetAnimation);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetPartnerActionQuality);
API_CALLABLE(GetSmashActionQuality);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(InterruptActionCommand);
API_CALLABLE(JumpToGoal);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(LoadItemScript);
API_CALLABLE(LoadStarPowerScript);
API_CALLABLE(MakeLerp);
API_CALLABLE(ModifyActorDecoration);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PartnerAfflictEnemy);
API_CALLABLE(PartnerDamageEnemy);
API_CALLABLE(PartnerTestEnemy);
API_CALLABLE(PartnerYieldTurn);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(ResetActorSounds);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActionProgress);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPaletteEffect);
API_CALLABLE(SetActorPaletteSwapParams);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetAnimationRate);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetDamageSource);
API_CALLABLE(SetDefenseTable);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetProjectileTargetOffset);
API_CALLABLE(SetTargetOffset);
API_CALLABLE(SetupMashMeter);
API_CALLABLE(ShowActionHud);
API_CALLABLE(TTYD64_Player_AC_802A9000);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(action_command_dizzy_shell_start);
API_CALLABLE(action_command_fire_shell_start);
API_CALLABLE(action_command_hammer_start);
API_CALLABLE(battle_partner_kooper_AverageTargetDizzyChance);
API_CALLABLE(battle_partner_kooper_GetFireShellSpeedAndDamage);
API_CALLABLE(battle_partner_kooper_SetTargetsYaw);
API_CALLABLE(battle_partner_kooper_SlowDown);
EvtScript TTYD64_battle_partner_kooper_EVS_80238000;
EvtScript TTYD64_battle_partner_kooper_EVS_802382D0;
extern s32 TTYD64_battle_partner_kooper_IdleAnimations_Kooper_Flipped[];
extern ActorBlueprint TTYD64_battle_partner_kooper;
EvtScript TTYD64_battle_partner_kooper_EVS_80238570;
EvtScript TTYD64_battle_partner_kooper_EVS_80239664;
EvtScript TTYD64_battle_partner_kooper_EVS_8023A28C;
EvtScript TTYD64_battle_partner_kooper_EVS_8023AE48;
EvtScript TTYD64_battle_partner_kooper_EVS_8023B940;
EvtScript TTYD64_battle_partner_kooper_EVS_8023C0B0;
EvtScript TTYD64_battle_partner_kooper_EVS_8023C7E4;
EvtScript TTYD64_battle_partner_kooper_EVS_8023CD84;
EvtScript TTYD64_battle_partner_kooper_EVS_8023CFD0;
EvtScript TTYD64_battle_partner_kooper_EVS_8023D1F0;
EvtScript TTYD64_battle_partner_kooper_EVS_8023D380;
EvtScript TTYD64_battle_partner_kooper_EVS_8023D8C8;
EvtScript TTYD64_battle_partner_kooper_EVS_8023D9AC;
EvtScript TTYD64_battle_partner_kooper_EVS_8023DA8C;
extern s32 TTYD64_battle_partner_kooper_StatusTable_Kooper_80238478[];
EvtScript TTYD64_battle_partner_kooper_EVS_8023DBEC;
EvtScript TTYD64_battle_partner_kooper_EVS_8023DD04;
extern s32 TTYD64_battle_partner_kooper_IdleAnimations_Kooper_Normal[];
extern s32 TTYD64_battle_partner_kooper_IntTable_Kooper_Flip[];
EvtScript TTYD64_battle_partner_kooper_EVS_8023DE14;
EvtScript TTYD64_battle_partner_kooper_EVS_8023DE50;
extern ActorPartBlueprint TTYD64_battle_partner_kooper_PartsTable_Kooper_80238524[];
EvtScript TTYD64_battle_partner_kooper_EVS_8023DE9C;
extern s32 TTYD64_battle_partner_kooper_DefenseTable_Kooper_Normal[];
extern s32 TTYD64_battle_partner_kooper_DefenseTable_Kooper_Flipped[];

// clang-format off
s32 TTYD64_battle_partner_kooper_IdleAnimations_Kooper_Flipped[] = {
    1, 655385, 12, 655363, 6, 655363, 9, 655385,
    8, 655363, 13, 655388, 7, 655363, 18, 655385,
    0,
};

ActorBlueprint TTYD64_battle_partner_kooper = {
    .flags = 0,
    .type = 112,
    .level = 0,
    .maxHP = 99,
    .partCount = 1,
    .unk_0A = { 0, 0 },
    .partsData = TTYD64_battle_partner_kooper_PartsTable_Kooper_80238524,
    .initScript = &TTYD64_battle_partner_kooper_EVS_8023D1F0,
    .statusTable = TTYD64_battle_partner_kooper_StatusTable_Kooper_80238478,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 32, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 30 },
    .statusTextOffset = { 10, 30 },
};

s32 TTYD64_battle_partner_kooper_StatusTable_Kooper_80238478[] = {
    1, 100, 2, 100, 6, 100, 9, 100,
    7, 100, 4, 100, 3, 100, 11, 100,
    5, 100, 10, 100, 8, 100, 31, 0,
    32, 0, 37, 0, 34, 0, 36, 0,
    35, 0, 33, 0, 38, 0, 39, 0,
    41, 0, 0,
};

s32 TTYD64_battle_partner_kooper_IdleAnimations_Kooper_Normal[] = {
    1, 655365, 12, 655360, 6, 655390, 9, 655391,
    8, 655360, 4, 655388, 13, 655388, 18, 655360,
    26, 655391, 7, 655360, 48, 655369, 0,
};

s32 TTYD64_battle_partner_kooper_IntTable_Kooper_Flip[] = {
    9, 16, 22, 26, 30, 32, 33, 32,
    30, 26, 22, 16, 9, 0, 4, 6,
    7, 6, 4, 0, 2, 0,
};

ActorPartBlueprint TTYD64_battle_partner_kooper_PartsTable_Kooper_80238524[] = {
    {
        .flags = 0,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 8, 27 },
        .opacity = 255,
        .idleAnimations = TTYD64_battle_partner_kooper_IdleAnimations_Kooper_Normal,
        .defenseTable = TTYD64_battle_partner_kooper_DefenseTable_Kooper_Normal,
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
        .unk_1E = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_battle_partner_kooper_DefenseTable_Kooper_Normal[] = {
    1, 1, 0,
};

s32 TTYD64_battle_partner_kooper_DefenseTable_Kooper_Flipped[] = {
    1, 0, 0,
};

EvtScript TTYD64_battle_partner_kooper_EVS_80238000 = {
    Call(AddActorDecoration, ACTOR_SELF, 0, 0, 2)
    Call(SetAnimationRate, ACTOR_SELF, 0, Float(3.0))
    Wait(20)
    Call(SetAnimationRate, ACTOR_SELF, 0, Float(1.0))
    Call(RemoveActorDecoration, ACTOR_SELF, 0, 0)
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8321)
    Call(SetAnimation, ACTOR_SELF, -1, 655385)
    Set(LVar0, 0)
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
    ChildThread
        Loop(5)
            Add(LVar0, -15)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndChildThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
    Call(JumpToGoal, ACTOR_SELF, 8, false, true, false)
    Call(PlaySoundAtActor, ACTOR_SELF, 8378)
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, -1, 655364)
    Call(SetIdleAnimations, ACTOR_SELF, 0, Ref(TTYD64_battle_partner_kooper_IdleAnimations_Kooper_Normal))
    Call(SetDefenseTable, ACTOR_SELF, 0, Ref(TTYD64_battle_partner_kooper_DefenseTable_Kooper_Normal))
    Call(SetTargetOffset, ACTOR_SELF, 0, 8, 27)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 0, -1, -4)
    Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_FLIPPED, 0)
    Call(ResetActorSounds, ACTOR_SELF, 2)
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_802382D0 = {
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
        CaseEq(137)
            Call(SetDamageSource, 6)
            Set(LVarF, 2)
            Set(LVarE, 1)
            ExecWait(TTYD64_battle_partner_kooper_EVS_8023AE48)
        CaseEq(138)
            Call(SetDamageSource, 6)
            Set(LVarF, 3)
            Set(LVarE, 2)
            ExecWait(TTYD64_battle_partner_kooper_EVS_8023AE48)
        CaseEq(139)
            Call(SetDamageSource, 6)
            Set(LVarF, 5)
            Set(LVarE, 3)
            ExecWait(TTYD64_battle_partner_kooper_EVS_8023AE48)
        CaseEq(140)
            Call(SetDamageSource, 7)
            ExecWait(TTYD64_battle_partner_kooper_EVS_8023A28C)
        CaseEq(141)
            Call(SetDamageSource, 8)
            ExecWait(TTYD64_battle_partner_kooper_EVS_80239664)
        CaseEq(142)
            Call(SetDamageSource, 9)
            ExecWait(TTYD64_battle_partner_kooper_EVS_80238570)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_80238570 = {
    Call(LoadActionCommand, ACTION_COMMAND_FIRE_SHELL)
    Exec(TTYD64_battle_partner_kooper_EVS_8023DE50)
    Call(SetupMashMeter, 5, 35, 60, 80, 99, 100)
    Call(InitTargetIterator)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(4.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 655366)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_PARTNER, 0, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655364)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655374)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Wait(15)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
    Call(UseBattleCamPreset, 59)
    Call(MoveBattleCamOver, 75)
    Set(LVarD, 75)
    Set(LVarC, LVarD)
    Add(LVarC, -3)
    Call(action_command_fire_shell_start, 0, LVarC, 3)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Set(LVarA, Float(8.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8204)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_ROARING_FIRE)
    Call(AddActorDecoration, ACTOR_SELF, 0, 0, 4)
    Wait(1)
    Call(ModifyActorDecoration, 256, -1, 0, 10, 10, 255, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 1)
    Call(SetActorPaletteEffect, ACTOR_PARTNER, -1, 15)
    Call(SetActorPaletteSwapParams, ACTOR_PARTNER, -1, 0, 0, 1, 10, 1000, 10, 0, 0)
    Call(EnableActorPaletteEffects, ACTOR_PARTNER, 0, 1)
    Set(LVar6, 0)
    Set(LVar7, 0)
    Set(LVar8, 30)
    Set(LVar9, 30)
    Loop(LVarD)
        Wait(1)
        Call(GetActionProgress, LVar0)
        Switch(LVar0)
            CaseGe(80)
                Call(SetAnimation, ACTOR_PARTNER, -1, 655373)
                Set(LVar9, 80)
                Set(LVar7, 8)
                IfNe(LVar6, LVar7)
                    Call(SetActorPaletteEffect, ACTOR_PARTNER, -1, 15)
                    Call(SetActorPaletteSwapParams, ACTOR_PARTNER, -1, LVar6, LVar7, 1, 10, 1000, 10, 0, 0)
                    Set(LVar6, LVar7)
                EndIf
            CaseGe(60)
                Call(SetAnimation, ACTOR_PARTNER, -1, 655372)
                Set(LVar9, 60)
                Set(LVar7, 7)
                IfNe(LVar6, LVar7)
                    Call(SetActorPaletteEffect, ACTOR_PARTNER, -1, 15)
                    Call(SetActorPaletteSwapParams, ACTOR_PARTNER, -1, LVar6, LVar7, 1, 10, 1000, 10, 0, 0)
                    Set(LVar6, LVar7)
                EndIf
            CaseGe(40)
                Call(SetAnimation, ACTOR_PARTNER, -1, 655371)
                Set(LVar9, 40)
                Set(LVar7, 6)
                IfNe(LVar6, LVar7)
                    Call(SetActorPaletteEffect, ACTOR_PARTNER, -1, 15)
                    Call(SetActorPaletteSwapParams, ACTOR_PARTNER, -1, LVar6, LVar7, 1, 10, 1000, 10, 0, 0)
                    Set(LVar6, LVar7)
                EndIf
            CaseGe(20)
                Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
                Set(LVar9, 35)
                Set(LVar7, 5)
                IfNe(LVar6, LVar7)
                    Call(SetActorPaletteEffect, ACTOR_PARTNER, -1, 15)
                    Call(SetActorPaletteSwapParams, ACTOR_PARTNER, -1, LVar6, LVar7, 1, 10, 1000, 10, 0, 0)
                    Set(LVar6, LVar7)
                EndIf
            CaseDefault
                Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
                Set(LVar9, 30)
                Set(LVar7, 0)
                IfNe(LVar6, LVar7)
                    Call(SetActorPaletteEffect, ACTOR_PARTNER, -1, 15)
                    Call(SetActorPaletteSwapParams, ACTOR_PARTNER, -1, LVar6, LVar7, 1, 10, 1000, 10, 0, 0)
                    Set(LVar6, LVar7)
                EndIf
        EndSwitch
        IfLt(LVar8, LVar9)
            Add(LVar8, 1)
        EndIf
        IfGt(LVar8, LVar9)
            Sub(LVar8, 1)
        EndIf
        Call(ModifyActorDecoration, 256, -1, 0, LVar8, LVar8, 255, 0)
        Switch(LVarD)
            CaseEq(10)
                Call(GetActorPos, ACTOR_PARTNER, LVar3, LVar4, LVar5)
                Call(PlayEffect_impl, 29, 1, LVar3, LVar4, LVar5, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseEq(20)
                Call(GetActorPos, ACTOR_PARTNER, LVar3, LVar4, LVar5)
                Call(PlayEffect_impl, 29, 1, LVar3, LVar4, LVar5, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseEq(40)
                Call(GetActorPos, ACTOR_PARTNER, LVar3, LVar4, LVar5)
                Call(PlayEffect_impl, 29, 1, LVar3, LVar4, LVar5, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseEq(60)
                Call(GetActorPos, ACTOR_PARTNER, LVar3, LVar4, LVar5)
                Call(PlayEffect_impl, 29, 1, LVar3, LVar4, LVar5, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        EndSwitch
    EndLoop
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_FIRE_SHELL_LAUNCH)
    Call(battle_partner_kooper_GetFireShellSpeedAndDamage)
    Switch(LVarE)
        CaseOrEq(0)
        CaseOrEq(1)
            Call(UseBattleCamPreset, 3)
            Call(MoveBattleCamOver, 50)
            SetF(LVarA, Float(10.0))
        EndCaseGroup
        CaseOrEq(2)
        CaseOrEq(3)
            Call(UseBattleCamPreset, 3)
            Call(MoveBattleCamOver, 30)
            SetF(LVarA, Float(10.0))
        EndCaseGroup
        CaseEq(4)
            Call(UseBattleCamPreset, 3)
            Call(MoveBattleCamOver, 15)
            SetF(LVarA, Float(16.0))
    EndSwitch
    Set(LVarB, 350)
    DivF(LVarB, LVarA)
    Thread
        Call(AddActorDecoration, ACTOR_PARTNER, -1, 1, 6)
        Wait(1)
        Switch(LVarE)
            CaseOrEq(0)
            CaseOrEq(1)
                Call(ModifyActorDecoration, 256, -1, 1, 50, 0, 0, 0)
            EndCaseGroup
            CaseOrEq(2)
            CaseOrEq(3)
                Call(ModifyActorDecoration, 256, -1, 1, 100, 0, 0, 0)
            EndCaseGroup
            CaseEq(4)
                Call(ModifyActorDecoration, 256, -1, 1, 300, 0, 0, 0)
        EndSwitch
        Call(EnableActorBlur, ACTOR_PARTNER, 1)
        Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Add(LVar0, 350)
        Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Call(SetActorSpeed, ACTOR_PARTNER, LVarA)
        Call(SetActorSounds, ACTOR_PARTNER, 0, 0, 0)
        Call(RunToGoal, ACTOR_PARTNER, 0)
        Call(RemoveActorDecoration, ACTOR_SELF, 0, 1)
        Wait(20)
        Call(RemoveActorDecoration, ACTOR_SELF, 0, 0)
        Call(EnableActorPaletteEffects, ACTOR_PARTNER, 0, 0)
        Call(SetActorPos, ACTOR_PARTNER, -200, 0, 0)
        Call(SetGoalToHome, ACTOR_PARTNER)
        Call(AddGoalPos, ACTOR_PARTNER, 40, 0, 0)
        Call(SetActorSpeed, ACTOR_PARTNER, Float(12.0))
        Call(FlyToGoal, ACTOR_PARTNER, 0, 0, 6)
        Call(EnableActorBlur, ACTOR_PARTNER, 0)
        Call(SetActorVar, ACTOR_SELF, 0, 1)
    EndThread
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Set(LFlag0, 0)
    Label(10)
    Wait(1)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(GetActorPos, ACTOR_PARTNER, LVar3, LVar4, LVar5)
    IfGt(LVar0, LVar3)
        Goto(10)
    EndIf
    Call(PartnerTestEnemy, LVar0, 0, 20, 0, 2, 16)
    IfEq(LVar0, 6)
        Goto(12)
    EndIf
    IfEq(LFlag0, 0)
        Call(GetPartnerActionQuality, LVar0)
        Switch(LVar0)
            CaseGt(99)
                Call(UseBattleCamPreset, 4)
            CaseDefault
                Call(UseBattleCamPreset, 51)
        EndSwitch
    EndIf
    Set(LFlag0, 1)
    Call(GetActionProgress, LVar0)
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(99)
            Call(PartnerDamageEnemy, LVar0, 536870914, 159, 0, LVarF, 112)
        CaseDefault
            Call(PartnerDamageEnemy, LVar0, 536870914, 159, 0, LVarF, 48)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Label(12)
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(10)
    EndIf
    IfEq(LFlag0, 0)
        Call(GetPartnerActionQuality, LVar0)
        Switch(LVar0)
            CaseGt(99)
                Call(UseBattleCamPreset, 4)
            CaseDefault
                Call(UseBattleCamPreset, 51)
        EndSwitch
    EndIf
    Label(11)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Wait(1)
        Goto(11)
    EndIf
    Jump(TTYD64_Script_DoStylish_DizzyShell)
    Call(PartnerYieldTurn)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655375)
    Wait(15)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655364)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(7.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 655366)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655364)
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_80239664 = {
    Call(LoadActionCommand, ACTION_COMMAND_DIZZY_SHELL)
    Exec(TTYD64_battle_partner_kooper_EVS_8023DE50)
    Call(SetupMashMeter, 1, 100, 0, 0, 0, 0)
    Call(InitTargetIterator)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(4.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 655366)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_PARTNER, 0, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655364)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655374)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Wait(15)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
    Call(UseBattleCamPreset, 59)
    Call(MoveBattleCamOver, 75)
    Set(LVarD, 75)
    Set(LVarA, LVarD)
    Add(LVarA, -3)
    Call(battle_partner_kooper_AverageTargetDizzyChance)
    Call(action_command_dizzy_shell_start, 0, LVarA, 3, LVar0)
    Call(SetActionProgress, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8204)
    Set(LVar9, 0)
    Set(LVarA, Float(8.0))
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8230)
    Call(AddActorDecoration, ACTOR_SELF, 0, 1, 7)
    Call(SetActorVar, ACTOR_SELF, 1, 1)
    Set(LVar9, 1)
    Loop(LVarD)
        Wait(1)
        Call(GetActionProgress, LVar0)
        Switch(LVar0)
            CaseLt(20)
                Set(LVarA, Float(10.0))
                Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
            CaseLt(40)
                Set(LVarA, Float(12.0))
                Call(SetAnimation, ACTOR_PARTNER, -1, 655371)
            CaseLt(60)
                Set(LVarA, Float(14.0))
                Call(SetAnimation, ACTOR_PARTNER, -1, 655372)
            CaseDefault
                Set(LVarA, Float(16.0))
                Call(SetAnimation, ACTOR_PARTNER, -1, 655373)
        EndSwitch
        Switch(LVarD)
            CaseEq(10)
                Call(GetActorPos, ACTOR_PARTNER, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseEq(20)
                Call(GetActorPos, ACTOR_PARTNER, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseEq(40)
                Call(GetActorPos, ACTOR_PARTNER, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseEq(60)
                Call(GetActorPos, ACTOR_PARTNER, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        EndSwitch
    EndLoop
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_DIZZY_SHELL_LAUNCH)
    Call(UseBattleCamPreset, 3)
    Call(MoveBattleCamOver, 15)
    Set(LVarB, 300)
    DivF(LVarB, LVarA)
    Thread
        Call(AddActorDecoration, ACTOR_SELF, 0, 0, 5)
        Call(EnableActorBlur, ACTOR_PARTNER, 1)
        Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Add(LVar0, 350)
        Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Call(SetActorSpeed, ACTOR_PARTNER, LVarA)
        Call(SetActorSounds, ACTOR_PARTNER, 0, 0, 0)
        Call(RunToGoal, ACTOR_PARTNER, 0)
        Call(RemoveActorDecoration, ACTOR_SELF, 0, 0)
        Call(RemoveActorDecoration, ACTOR_SELF, 0, 1)
        Wait(20)
        Call(SetActorPos, ACTOR_PARTNER, -200, 0, 0)
        Call(SetGoalToHome, ACTOR_PARTNER)
        Call(AddGoalPos, ACTOR_PARTNER, 40, 0, 0)
        Call(SetActorSpeed, ACTOR_PARTNER, Float(12.0))
        Call(FlyToGoal, ACTOR_PARTNER, 0, 0, 6)
        Call(EnableActorBlur, ACTOR_PARTNER, 0)
        Call(SetActorVar, ACTOR_SELF, 0, 1)
    EndThread
    Thread
        Call(battle_partner_kooper_SetTargetsYaw)
    EndThread
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Set(LFlag0, 0)
    Label(10)
    Wait(1)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(GetActorPos, ACTOR_PARTNER, LVar3, LVar4, LVar5)
    IfGt(LVar0, LVar3)
        Goto(10)
    EndIf
    Call(PartnerTestEnemy, LVar0, 0, 20, 0, 2, 16)
    IfEq(LVar0, 6)
        Goto(12)
    EndIf
    IfEq(LFlag0, 0)
        Call(GetPartnerActionQuality, LVar0)
        Switch(LVar0)
            CaseGt(99)
                Call(UseBattleCamPreset, 4)
            CaseDefault
                Call(UseBattleCamPreset, 51)
        EndSwitch
    EndIf
    Set(LFlag0, 1)
    Call(GetActionProgress, LVarF)
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            IfEq(LVar9, 1)
                IfEq(LVarF, 100)
                    Call(PartnerAfflictEnemy, LVar0, 1610612736, 159, (Bytecode) (s32) 0xC0040300, 254, 0, 112)
                Else
                    Call(PartnerAfflictEnemy, LVar0, 1610612736, 159, (Bytecode) (s32) 0xC0040300, LVarF, 0, 112)
                EndIf
            Else
                Call(PartnerAfflictEnemy, LVar0, 1610612736, 159, (Bytecode) (s32) 0xC0040300, LVarF, 0, 112)
            EndIf
        CaseDefault
            IfEq(LVar9, 1)
                Call(PartnerAfflictEnemy, LVar0, 1610612736, 159, (Bytecode) (s32) 0xC0040300, 255, 0, 48)
            Else
                Call(PartnerAfflictEnemy, LVar0, 1610612736, 159, (Bytecode) (s32) 0xC0040300, 255, 0, 48)
            EndIf
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Label(12)
    Call(ChooseNextTarget, 0, LVar2)
    IfNe(LVar2, -1)
        Goto(10)
    EndIf
    IfEq(LFlag0, 0)
        Call(GetPartnerActionQuality, LVar0)
        Switch(LVar0)
            CaseGt(99)
                Call(UseBattleCamPreset, 4)
            CaseDefault
                Call(UseBattleCamPreset, 51)
        EndSwitch
    EndIf
    Label(11)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Wait(1)
        Goto(11)
    EndIf
    Jump(TTYD64_Script_DoStylish_DizzyShell)
    Call(PartnerYieldTurn)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655375)
    Wait(15)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655364)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(7.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 655366)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655364)
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023A28C = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Exec(TTYD64_battle_partner_kooper_EVS_8023C7E4)
    Call(GetActorLevel, 256, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Set(LVarE, 1)
            Set(LVarF, 2)
        CaseEq(1)
            Set(LVarE, 1)
            Set(LVarF, 3)
        CaseEq(2)
            Set(LVarE, 1)
            Set(LVarF, 4)
    EndSwitch
    Call(InitTargetIterator)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(4.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 655366)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_PARTNER, 0, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655364)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655374)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Wait(15)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
    Loop(30)
        Wait(1)
        Call(CheckButtonDown, 262144, LVar0)
        IfNe(LVar0, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(UseBattleCamPreset, 59)
    Call(action_command_hammer_start, 0, 47, 3)
    Call(SetActionProgress, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8204)
    Set(LVar9, 0)
    Set(LVar1, 0)
    Loop(50)
        Wait(1)
        Switch(LVar9)
            CaseLt(20)
                Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
            CaseEq(20)
                Call(GetActorPos, ACTOR_PARTNER, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseLt(30)
                Call(SetAnimation, ACTOR_PARTNER, -1, 655371)
            CaseEq(30)
                Call(GetActorPos, ACTOR_PARTNER, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseLt(40)
                Call(SetAnimation, ACTOR_PARTNER, -1, 655372)
            CaseEq(40)
                Call(GetActorPos, ACTOR_PARTNER, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseLt(50)
                Call(SetAnimation, ACTOR_PARTNER, -1, 655373)
            CaseEq(50)
                Call(GetActorPos, ACTOR_PARTNER, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        EndSwitch
        Add(LVar9, 1)
        Call(GetActionProgress, LVar0)
        IfNe(LVar0, 0)
            IfNe(LVar1, 1)
                Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
                Set(LVar1, 1)
            EndIf
        EndIf
        Call(CheckButtonDown, 262144, LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
    EndLoop
    Label(0)
    Wait(1)
    Set(LVarA, Float(8.0))
    Switch(LVar9)
        CaseLt(20)
            Set(LVarA, Float(10.0))
            Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
        CaseLt(30)
            Set(LVarA, Float(12.0))
            Call(SetAnimation, ACTOR_PARTNER, -1, 655371)
        CaseLt(40)
            Set(LVarA, Float(14.0))
            Call(SetAnimation, ACTOR_PARTNER, -1, 655372)
        CaseLt(50)
            Set(LVarA, Float(16.0))
            Call(SetAnimation, ACTOR_PARTNER, -1, 655373)
    EndSwitch
    Add(LVar9, 1)
    Call(GetSmashActionQuality, LVar0)
    IfEq(LVar0, 0)
        Goto(0)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8203)
    Call(UseBattleCamPreset, 3)
    Call(MoveBattleCamOver, 15)
    Set(LVarB, 260)
    DivF(LVarB, LVarA)
    Thread
        Call(AddActorDecoration, ACTOR_SELF, 0, 1, 5)
        Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Add(LVar0, 260)
        Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Call(SetActorSpeed, ACTOR_PARTNER, LVarA)
        Call(SetActorSounds, ACTOR_PARTNER, 0, 0, 0)
        Call(RunToGoal, ACTOR_PARTNER, 0)
        Call(SetActorVar, ACTOR_SELF, 0, 1)
        Call(RemoveActorDecoration, ACTOR_SELF, 0, 1)
    EndThread
    Set(LFlag0, 0)
    Label(10)
    Wait(1)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(GetActorPos, ACTOR_PARTNER, LVar3, LVar4, LVar5)
    IfGt(LVar0, LVar3)
        Goto(10)
    EndIf
    Call(PartnerTestEnemy, LVar0, 0, 20, 0, 2, 16)
    IfEq(LVar0, 6)
        Goto(12)
    EndIf
    IfEq(LFlag0, 0)
        Call(GetPartnerActionQuality, LVar0)
        Switch(LVar0)
            CaseGt(0)
                Call(UseBattleCamPreset, 4)
            CaseDefault
                Call(UseBattleCamPreset, 51)
        EndSwitch
    EndIf
    Set(LFlag0, 1)
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(PartnerDamageEnemy, LVar0, 536870912, 159, 0, LVarF, 112)
        CaseDefault
            Call(PartnerDamageEnemy, LVar0, 536870912, 159, 0, LVarE, 48)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Label(12)
    Call(ChooseNextTarget, 0, LVar2)
    IfNe(LVar2, -1)
        Goto(10)
    EndIf
    IfEq(LFlag0, 0)
        Call(GetPartnerActionQuality, LVar0)
        Switch(LVar0)
            CaseGt(0)
                Call(UseBattleCamPreset, 4)
            CaseDefault
                Call(UseBattleCamPreset, 51)
        EndSwitch
    EndIf
    Label(11)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Wait(1)
        Goto(11)
    EndIf
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            ExecWait(TTYD64_battle_partner_kooper_EVS_8023CFD0)
        CaseDefault
            ExecWait(TTYD64_battle_partner_kooper_EVS_8023CD84)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023AE48 = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Exec(TTYD64_battle_partner_kooper_EVS_8023DE50)
    Call(InitTargetIterator)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(4.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 655366)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_PARTNER, 0, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655364)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655374)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Wait(15)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
    Loop(30)
        Wait(1)
        Call(CheckButtonDown, 262144, LVar0)
        IfNe(LVar0, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(action_command_hammer_start, 0, 47, 3)
    Call(SetActionProgress, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8204)
    Call(UseBattleCamPreset, 59)
    Set(LVar9, 0)
    Set(LVar1, 0)
    Loop(50)
        Wait(1)
        Switch(LVar9)
            CaseLt(20)
                Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
            CaseEq(20)
                Call(GetActorPos, ACTOR_PARTNER, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseLt(30)
                Call(SetAnimation, ACTOR_PARTNER, -1, 655371)
            CaseEq(30)
                Call(GetActorPos, ACTOR_PARTNER, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseLt(40)
                Call(SetAnimation, ACTOR_PARTNER, -1, 655372)
            CaseEq(40)
                Call(GetActorPos, ACTOR_PARTNER, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseLt(50)
                Call(SetAnimation, ACTOR_PARTNER, -1, 655373)
            CaseEq(50)
                Call(GetActorPos, ACTOR_PARTNER, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        EndSwitch
        Add(LVar9, 1)
        Call(GetActionProgress, LVar0)
        IfNe(LVar0, 0)
            IfNe(LVar1, 1)
                Set(LVar1, 1)
            EndIf
        EndIf
        Call(CheckButtonDown, 262144, LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
    EndLoop
    Label(0)
    Wait(1)
    SetF(LVarA, Float(8.0))
    Switch(LVar9)
        CaseLt(20)
            SetF(LVarA, Float(10.0))
            Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
        CaseLt(30)
            SetF(LVarA, Float(12.0))
            Call(SetAnimation, ACTOR_PARTNER, -1, 655371)
        CaseLt(40)
            SetF(LVarA, Float(14.0))
            Call(SetAnimation, ACTOR_PARTNER, -1, 655372)
        CaseLt(50)
            SetF(LVarA, Float(16.0))
            Call(SetAnimation, ACTOR_PARTNER, -1, 655373)
    EndSwitch
    Add(LVar9, 1)
    Call(GetSmashActionQuality, LVar0)
    IfEq(LVar0, 0)
        Goto(0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8202)
    Call(UseBattleCamPreset, 3)
    Call(MoveBattleCamOver, 15)
    ExecWait(TTYD64_battle_partner_kooper_EVS_8023D9AC)
    Call(AddActorDecoration, ACTOR_SELF, 0, 0, 5)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, LVarA)
    Call(SetActorSounds, ACTOR_PARTNER, 0, 0, 0)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(PartnerTestEnemy, LVar0, 0, 20, 0, 2, 16)
    IfEq(LVar0, 6)
        Thread
            Call(battle_partner_kooper_SlowDown)
            Call(RemoveActorDecoration, ACTOR_SELF, 0, 0)
        EndThread
        Wait(4)
        Call(SetAnimation, ACTOR_PARTNER, -1, 655369)
        Call(SetActorRotationOffset, ACTOR_PARTNER, 8, 0, 0)
        Set(LVar0, 0)
        Loop(2)
            Add(LVar0, -30)
            Call(SetActorRotation, ACTOR_PARTNER, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Wait(5)
        Call(GetActorPos, ACTOR_PARTNER, LVar4, LVar5, LVar6)
        Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 16, 4, 0, 10, 0, 0, 0, 0, 0)
        Loop(5)
            Add(LVar0, 12)
            Call(SetActorRotation, ACTOR_PARTNER, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorRotationOffset, ACTOR_PARTNER, 0, 0, 0)
        Call(SetActorRotation, ACTOR_PARTNER, 0, 0, 2)
        Wait(2)
        Call(SetActorRotation, ACTOR_PARTNER, 0, 0, -2)
        Wait(2)
        Call(SetActorRotation, ACTOR_PARTNER, 0, 0, 0)
        Wait(10)
        Call(SetAnimation, ACTOR_PARTNER, -1, 655375)
        Wait(10)
        Call(SetGoalToHome, ACTOR_PARTNER)
        Call(SetActorSpeed, ACTOR_PARTNER, Float(7.0))
        Call(SetAnimation, ACTOR_PARTNER, -1, 655366)
        Call(RunToGoal, ACTOR_PARTNER, 0)
        Return
    EndIf
    Call(RemoveActorDecoration, ACTOR_SELF, 0, 0)
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(PartnerDamageEnemy, LVar0, 0, 159, 0, LVarF, 112)
        CaseDefault
            Call(PartnerDamageEnemy, LVar0, 0, 159, 0, LVarE, 48)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_partner_kooper_EVS_8023CD84)
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
            ExecWait(TTYD64_Script_ShellToss_GoBackToHome_Succeed)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023B940 = {
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(InterruptActionCommand)
    Call(GetLastEvent, ACTOR_PARTNER, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, -1)
            Set(LVar1, 655377)
            ExecWait(EVS_Enemy_Hit)
            Call(SetAnimation, ACTOR_PARTNER, -1, 655363)
        EndCaseGroup
        CaseOrEq(23)
        CaseOrEq(25)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8332)
            Call(TTYD64_GetPartnerExtraBattleData_API, 14, LVar0)
            IfEq(LVar0, 0)
                Call(GetAnimation, ACTOR_PARTNER, -1, LVar0)
                Switch(LVar0)
                    CaseOrEq(655363)
                    CaseOrEq(655388)
                        SetConst(LVar0, 1)
                        SetConst(LVar1, 655363)
                    EndCaseGroup
                    CaseDefault
                        SetConst(LVar0, 1)
                        SetConst(LVar1, 655360)
                EndSwitch
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 655369)
            EndIf
            ExecWait(EVS_Enemy_NoDamageHit)
        EndCaseGroup
        CaseEq(42)
            SetConst(LVar1, 655377)
            Set(LVar2, 16)
            ExecWait(EVS_Partner_SpikeContact)
        CaseEq(44)
            SetConst(LVar1, 655378)
            Set(LVar2, 16)
            SetConst(LVar3, 655379)
            ExecWait(EVS_Partner_BurnContact)
        CaseEq(14)
            SetConst(LVar1, 655378)
            SetConst(LVar2, 655379)
            ExecWait(EVS_Partner_BurnHit)
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 655377)
            Set(LVar2, 16)
            ExecWait(EVS_Partner_ShockHit)
        CaseEq(51)
        CaseEq(52)
            SetConst(LVar0, 1)
            SetConst(LVar1, 655364)
            SetConst(LVar2, 655366)
            Set(LVar3, 0)
            ExecWait(EVS_Partner_Recover)
        CaseOrEq(24)
        CaseOrEq(26)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8332)
            SetConst(LVar0, 1)
            SetConst(LVar1, 655376)
            ExecWait(EVS_Enemy_NoDamageHit)
            Wait(10)
            Call(SetAnimation, ACTOR_PARTNER, -1, 655375)
        EndCaseGroup
        CaseEq(13)
            Call(TTYD64_SetPartnerExtraBattleData_API, 12, 1)
            Call(TTYD64_SetPartnerExtraBattleData_API, 13, 2)
            Call(TTYD64_SetPartnerExtraBattleData_API, 14, 0)
            Call(SetDefenseTable, ACTOR_SELF, 0, Ref(TTYD64_battle_partner_kooper_DefenseTable_Kooper_Flipped))
            Call(SetIdleAnimations, ACTOR_SELF, 0, Ref(TTYD64_battle_partner_kooper_IdleAnimations_Kooper_Flipped))
            Call(SetTargetOffset, ACTOR_SELF, 0, -5, 15)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_FLIPPED, 1)
            Call(SetAnimation, ACTOR_SELF, -1, 655377)
            Call(GetStatusFlags, ACTOR_SELF, LVarA)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            ChildThread
                Wait(4)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 60)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 75)
                Wait(1)
            EndChildThread
            UseBuf(TTYD64_battle_partner_kooper_IntTable_Kooper_Flip)
            Loop(22)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, -1, 655385)
        CaseEq(32)
            Call(TTYD64_GetPartnerExtraBattleData_API, 12, LVar0)
            IfEq(LVar0, 1)
                Call(SetIdleAnimations, ACTOR_SELF, 0, Ref(TTYD64_battle_partner_kooper_IdleAnimations_Kooper_Normal))
                Call(SetDefenseTable, ACTOR_SELF, 0, Ref(TTYD64_battle_partner_kooper_DefenseTable_Kooper_Normal))
            EndIf
            Set(LVar0, -1)
            Set(LVar1, 655377)
            ExecWait(TTYD64_PartnerDies)
            Return
        CaseEq(TTYD64_EVENT_SUPERGUARD)
            Set(LVar0, -1)
            Set(LVar1, 655367)
            ExecWait(TTYD64_DoSuperguard)
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023C0B0 = {
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar0, 60)
    Call(SetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(InitTargetIterator)
    Call(UseBattleCamPreset, 3)
    Call(MoveBattleCamOver, 15)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655370)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(16.0))
    Call(SetActorSounds, ACTOR_PARTNER, 0, 0, 0)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(PartnerTestEnemy, LVar0, 0, 20, 0, 2, 16)
    IfEq(LVar0, 6)
        Thread
            Call(battle_partner_kooper_SlowDown)
            Call(RemoveActorDecoration, ACTOR_SELF, 0, 0)
        EndThread
        Wait(4)
        Call(SetAnimation, ACTOR_PARTNER, -1, 655369)
        Call(SetActorRotationOffset, ACTOR_PARTNER, 8, 0, 0)
        Set(LVar0, 0)
        Loop(2)
            Add(LVar0, -30)
            Call(SetActorRotation, ACTOR_PARTNER, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Wait(5)
        Call(GetActorPos, ACTOR_PARTNER, LVar4, LVar5, LVar6)
        Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 16, 4, 0, 10, 0, 0, 0, 0, 0)
        Loop(5)
            Add(LVar0, 12)
            Call(SetActorRotation, ACTOR_PARTNER, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorRotationOffset, ACTOR_PARTNER, 0, 0, 0)
        Call(SetActorRotation, ACTOR_PARTNER, 0, 0, 2)
        Wait(2)
        Call(SetActorRotation, ACTOR_PARTNER, 0, 0, -2)
        Wait(2)
        Call(SetActorRotation, ACTOR_PARTNER, 0, 0, 0)
        Wait(10)
        Call(SetAnimation, ACTOR_PARTNER, -1, 655375)
        Wait(10)
        Call(SetGoalToHome, ACTOR_PARTNER)
        Call(SetActorSpeed, ACTOR_PARTNER, Float(7.0))
        Call(SetAnimation, ACTOR_PARTNER, -1, 655366)
        Call(RunToGoal, ACTOR_PARTNER, 0)
        Return
    EndIf
    Set(LVarF, 1)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(137)
            Set(LVarF, 2)
        CaseEq(138)
            Set(LVarF, 3)
        CaseEq(139)
            Set(LVarF, 5)
    EndSwitch
    Call(PartnerDamageEnemy, LVar0, 0, 159, 0, LVarF, 48)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(137)
            Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
        CaseEq(138)
            Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
        CaseEq(139)
            Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    EndSwitch
    Call(UseBattleCamPreset, 3)
    Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.0996))
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 10, false, true, false)
    Sub(LVar0, 30)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 8, false, false, true)
    Sub(LVar0, 20)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 6, false, false, true)
    Sub(LVar0, 10)
    Call(JumpToGoal, ACTOR_PARTNER, 4, false, false, true)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655375)
    Wait(15)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655364)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(7.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 655366)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655364)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023C7E4 = {
    Call(TTYD64_Player_AC_802A9000)
    Exec(TTYD64_Script_NukeTracker)
    Wait(48)
    Call(CheckButtonDown, 262144, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Exec(TTYD64_Script_InitTracker)
    Loop(0)
        Call(CheckButtonDown, 262144, LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Return
    EndIf
    Call(GetPartnerActionQuality, LVar0)
    IfNe(LVar0, 0)
        Wait(1)
        Loop(2)
            ExecWait(TTYD64_Script_TimingTutor)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                Call(TTYD64_StylishDisarm)
                Call(TTYD64_StylishConsume)
                Call(TTYD64_StylishAddCount, LVar0)
                Call(TTYD64_WriteField, TTYD64_F_GACTIONCOMMANDSTATUS_60_1U, 0)
                Set(LVarA, 0)
                ExecWait(TTYD64_Script_DoStylishFX)
                Call(PlaySoundAtActor, ACTOR_SELF, 8205)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
                Thread
                    Wait(3)
                    SetTimescale(Float(3.0))
                    Loop(8)
                        Call(MakeLerp, 0, 180, 5, 0)
                        Loop(0)
                            Call(UpdateLerp)
                            Call(SetActorRotation, ACTOR_SELF, LVar0, 0, 0)
                            Wait(1)
                            IfEq(LVar1, 0)
                                BreakLoop
                            EndIf
                        EndLoop
                        Call(MakeLerp, -180, 0, 5, 0)
                        Loop(0)
                            Call(UpdateLerp)
                            Call(SetActorRotation, ACTOR_SELF, LVar0, 0, 0)
                            Wait(1)
                            IfEq(LVar1, 0)
                                BreakLoop
                            EndIf
                        EndLoop
                    EndLoop
                    SetTimescale(Float(1.0))
                    Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                EndThread
                Loop(6)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Add(LVar1, 5)
                    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Wait(1)
                EndLoop
                Loop(6)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Sub(LVar1, 5)
                    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Wait(1)
                EndLoop
                Call(GetActorPos, ACTOR_SELF, LVar0, 0, LVar2)
                Call(GetGoalPos, ACTOR_SELF, 0, LVar1, 0)
                Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndIf
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023CD84 = {
    Call(ResetActorSounds, ACTOR_PARTNER, 0)
    Thread
        Call(UseBattleCamPreset, 4)
        Wait(30)
        Call(UseBattleCamPreset, 2)
    EndThread
    Call(PartnerYieldTurn)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Sub(LVar0, 60)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.4))
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 20, false, true, false)
    Sub(LVar0, 30)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 8, false, false, true)
    Sub(LVar0, 20)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 6, false, false, true)
    Sub(LVar0, 10)
    Call(JumpToGoal, ACTOR_PARTNER, 4, false, false, true)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655375)
    Wait(4)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(7.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 655366)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655364)
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023CFD0 = {
    Call(ResetActorSounds, ACTOR_PARTNER, 0)
    Call(UseBattleCamPreset, 51)
    Call(PartnerYieldTurn)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Sub(LVar0, 30)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.0996))
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 10, false, true, false)
    Sub(LVar0, 20)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 8, false, false, true)
    Sub(LVar0, 10)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 6, false, false, true)
    Sub(LVar0, 10)
    Call(JumpToGoal, ACTOR_PARTNER, 4, false, false, true)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655375)
    Wait(4)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(7.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 655366)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655364)
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023D1F0 = {
    Call(BindTakeTurn, ACTOR_PARTNER, Ref(TTYD64_battle_partner_kooper_EVS_8023DBEC))
    Call(BindIdle, ACTOR_PARTNER, Ref(TTYD64_battle_partner_kooper_EVS_8023DE9C))
    Call(BindHandleEvent, ACTOR_PARTNER, Ref(TTYD64_battle_partner_kooper_EVS_8023B940))
    Call(BindHandlePhase, ACTOR_PARTNER, Ref(TTYD64_battle_partner_kooper_EVS_8023D380))
    Call(TTYD64_GetPartnerExtraBattleData_API, 12, LVar0)
    IfEq(LVar0, 1)
        Call(SetBattleFlagBits2, BS_FLAGS2_PARTNER_TURN_USED, 1)
        Call(SetTargetOffset, ACTOR_SELF, 0, -5, 15)
        Call(SetProjectileTargetOffset, ACTOR_SELF, 0, 0, 0)
        Call(SetDefenseTable, ACTOR_SELF, 0, Ref(TTYD64_battle_partner_kooper_DefenseTable_Kooper_Flipped))
        Call(SetIdleAnimations, ACTOR_SELF, 0, Ref(TTYD64_battle_partner_kooper_IdleAnimations_Kooper_Flipped))
        Call(TTYD64_GetPartnerExtraBattleData_API, 13, LVar0)
        IfEq(LVar0, 0)
            Call(TTYD64_SetPartnerExtraBattleData_API, 12, 0)
            Call(SetBattleFlagBits, BS_FLAGS1_PLAYER_IN_BACK, 0)
            Thread
                Wait(15)
                Exec(TTYD64_battle_partner_kooper_EVS_80238000)
            EndThread
        EndIf
    EndIf
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023D380 = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 11)
        Call(TTYD64_GetPartnerExtraBattleData_API, 12, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_GetPartnerExtraBattleData_API, 13, LVar0)
            Sub(LVar0, 1)
            Call(TTYD64_SetPartnerExtraBattleData_API, 13, LVar0)
            IfGt(LVar0, 0)
                Call(AddActorDecoration, ACTOR_SELF, 0, 0, 2)
                Call(SetAnimationRate, ACTOR_SELF, 0, Float(3.0))
                Wait(30)
                Call(SetAnimationRate, ACTOR_SELF, 0, Float(1.0))
                Call(RemoveActorDecoration, ACTOR_SELF, 0, 0)
                Call(SetBattleFlagBits2, BS_FLAGS2_PARTNER_TURN_USED, 1)
            Else
                ExecWait(TTYD64_battle_partner_kooper_EVS_80238000)
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, true)
            Return
        EndIf
    EndIf
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023D8C8 = {
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(6.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 655366)
    Call(SetActorYaw, ACTOR_PARTNER, 0)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 655364)
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023D9AC = {
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(GetGoalPos, ACTOR_PARTNER, LVarB, LVarC, LVarD)
    Call(GetActorPos, ACTOR_PARTNER, LVarC, LVarD, LVar0)
    IfGt(LVarB, LVarC)
        Sub(LVarB, LVarC)
    Else
        Sub(LVarC, LVarB)
        Set(LVarB, LVarC)
    EndIf
    DivF(LVarB, LVarA)
    IfLt(LVarB, 0)
        Set(LVarB, 0)
    EndIf
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023DA8C = {
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(137)
            Call(SetDamageSource, 6)
            ExecWait(TTYD64_battle_partner_kooper_EVS_8023C0B0)
        CaseEq(138)
            Call(SetDamageSource, 6)
            ExecWait(TTYD64_battle_partner_kooper_EVS_8023C0B0)
        CaseEq(139)
            Call(SetDamageSource, 6)
            ExecWait(TTYD64_battle_partner_kooper_EVS_8023C0B0)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023DBEC = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(1)
            ExecWait(TTYD64_battle_partner_kooper_EVS_8023DA8C)
        CaseEq(0)
            ExecWait(TTYD64_battle_partner_kooper_EVS_802382D0)
        CaseEq(5)
            ExecWait(TTYD64_battle_partner_kooper_EVS_8023DD04)
        CaseEq(3)
            ExecWait(TTYD64_battle_partner_kooper_EVS_8023DE14)
        CaseEq(7)
            ExecWait(TTYD64_battle_partner_kooper_EVS_8023D8C8)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023DD04 = {
    SetConst(LVar0, 1)
    SetConst(LVar1, 655382)
    SetConst(LVar2, 655365)
    SetConst(LVar3, 655364)
    ExecWait(EVS_Partner_Celebrate)
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023DE14 = {
    SetConst(LVar0, 1)
    SetConst(LVar1, 655366)
    ExecWait(EVS_Partner_RunAway)
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023DE50 = {
    Call(TTYD64_Player_AC_802A9000)
    Exec(TTYD64_Script_NukeTracker)
    Return
    End
};

EvtScript TTYD64_battle_partner_kooper_EVS_8023DE9C = {
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_partner_kooper(void) {
    Mod_ReplaceActorBlueprint("TTYD64", &battle_partner_kooper, &TTYD64_battle_partner_kooper);
}
