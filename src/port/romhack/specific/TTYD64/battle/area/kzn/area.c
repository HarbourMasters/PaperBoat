#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_drop_tables.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/battle/area/battles_a.h"

API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(CountTargets);
API_CALLABLE(CreateHomeTargetList);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyPartTo);
API_CALLABLE(FlyToGoal);
API_CALLABLE(ForceHomePos);
API_CALLABLE(FreezeBattleState);
API_CALLABLE(GetActorAttackBoost);
API_CALLABLE(GetActorDefenseBoost);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetBattleVar);
API_CALLABLE(GetDist2D);
API_CALLABLE(GetDistanceToGoal);
API_CALLABLE(GetEnemyMaxHP);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetIndexFromHome);
API_CALLABLE(GetIndexFromPos);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOriginalActorType);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartPos);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToCurrent);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HealActor);
API_CALLABLE(HideHealthBar);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(JumpWithBounce);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(ResetAllActorSounds);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorType);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetAnimationRate);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetBattleVar);
API_CALLABLE(SetDefenseTable);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetPartAlpha);
API_CALLABLE(SetPartDispOffset);
API_CALLABLE(SetPartEventBits);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartRotation);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetPartYaw);
API_CALLABLE(SetProjectileTargetOffset);
API_CALLABLE(SetStatusTable);
API_CALLABLE(SetTargetActor);
API_CALLABLE(SetTargetOffset);
API_CALLABLE(ShakeCam);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(WaitForBuffDone);
API_CALLABLE(YieldTurn);
API_CALLABLE(b_area_kzn_lava_bubble_PlayLavaBubbleFlightSound);
API_CALLABLE(b_area_kzn_medi_guy_MediGuySpriteRotationFunc);
API_CALLABLE(b_area_kzn_putrid_piranha_UnkEffect6FFunc);
API_CALLABLE(b_area_kzn_red_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_kzn_spike_top_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_kzn_white_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_kzn_white_magikoopa_GetActorDefense);
API_CALLABLE(b_area_kzn_white_magikoopa_GetBootsHammerLevel);
API_CALLABLE(b_area_kzn_white_magikoopa_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_kzn_white_magikoopa_ShrinkActor);
API_CALLABLE(b_area_kzn_white_magikoopa_StartRumbleWithParams);
extern Stage b_area_kzn_kzn_01;
extern s32 b_area_kzn_lava_bubble_DefenseTable[];
extern EvtScript b_area_kzn_lava_bubble_EVS_Ember_FlyHome;
extern EvtScript b_area_kzn_lava_bubble_EVS_HandleEvent;
extern EvtScript b_area_kzn_lava_bubble_EVS_Idle;
extern s32 b_area_kzn_lava_bubble_ProjectileAnims[];
extern s32 b_area_kzn_lava_bubble_StatusTable[];
extern s32 b_area_kzn_medi_guy_DefenseTable[];
extern EvtScript b_area_kzn_medi_guy_EVS_FindInjuredActor;
extern EvtScript b_area_kzn_medi_guy_EVS_HandleEvent;
extern EvtScript b_area_kzn_medi_guy_EVS_Idle;
extern EvtScript b_area_kzn_medi_guy_EVS_Move_HealOne;
extern EvtScript b_area_kzn_medi_guy_EVS_ReturnHome;
extern s32 b_area_kzn_medi_guy_StatusTable[];
extern s32 b_area_kzn_putrid_piranha_DefenseTable[];
extern EvtScript b_area_kzn_putrid_piranha_EVS_HandleEvent;
extern EvtScript b_area_kzn_putrid_piranha_EVS_Idle;
extern EvtScript b_area_kzn_putrid_piranha_EVS_ReturnHome;
extern s32 b_area_kzn_putrid_piranha_StatusTable[];
extern s32 b_area_kzn_red_magikoopa_BroomAnims[];
extern EvtScript b_area_kzn_red_magikoopa_EVS_HandleEvent;
extern EvtScript b_area_kzn_spike_top_EVS_CheckToppleAnim;
extern EvtScript b_area_kzn_spike_top_EVS_Idle;
extern u8 b_area_kzn_spike_top_FlipPosOffsets[];
extern s32 b_area_kzn_spike_top_StatusTable[];
extern s32 b_area_kzn_spike_top_ToppledDefense[];
extern s32 b_area_kzn_spike_top_UprightDefense[];
extern s32 b_area_kzn_white_magikoopa_DefenseTable_80223B2C[];
extern EvtScript b_area_kzn_white_magikoopa_EVS_Flee;
extern EvtScript b_area_kzn_white_magikoopa_EVS_HandleEvent_Ground;
extern EvtScript b_area_kzn_white_magikoopa_EVS_Idle;
extern EvtScript b_area_kzn_white_magikoopa_EVS_KnockDownCheck;
extern s32 b_area_kzn_white_magikoopa_IdleAnimations_80223E08[];
extern EvtScript TTYD64_kzn_white_magikoopa_EVS_Move_HealOne;
extern EvtScript TTYD64_kzn_spike_top_EVS_HandleEvent;
extern EvtScript TTYD64_kzn_spike_top_EVS_Ceiling_TakeTurn;
extern EvtScript TTYD64_kzn_spike_top_EVS_TakeTurn;
extern EvtScript TTYD64_kzn_putrid_piranha_EVS_Attack_Bite;
extern EvtScript TTYD64_kzn_medi_guy_EVS_Attack_Swoop;
extern EvtScript TTYD64_kzn_red_magikoopa_EVS_TakeTurn;
extern EvtScript TTYD64_kzn_white_magikoopa_EVS_Move_HealAll;
extern EvtScript TTYD64_kzn_white_magikoopa_EVS_Attack_WandStrike;
extern EvtScript TTYD64_kzn_white_magikoopa_EVS_Attack_WandStrike_8021DDDC;
extern EvtScript TTYD64_kzn_white_magikoopa_EVS_HandleEvent_Flying;
extern EvtScript TTYD64_kzn_white_magikoopa_EVS_HandleEvent_Flying_8021EAAC;
extern EvtScript TTYD64_kzn_white_magikoopa_EVS_Attack_MagicBlast;
extern EvtScript TTYD64_kzn_white_magikoopa_EVS_Attack_MagicBlast_8021F76C;
extern EvtScript TTYD64_kzn_EVS_8021FDC8;
extern EvtScript TTYD64_kzn_putrid_piranha_EVS_Attack_Bite_80220414;
extern EvtScript TTYD64_kzn_white_magikoopa_EVS_KnockDown;
extern EvtScript TTYD64_kzn_white_magikoopa_EVS_KnockDown_80221040;
extern EvtScript TTYD64_kzn_putrid_piranha_EVS_Attack_BadBreath;
extern EvtScript TTYD64_kzn_spike_top_EVS_Ceiling_HandleEvent;
extern EvtScript TTYD64_kzn_spike_top_EVS_FallFromCeiling;
extern EvtScript TTYD64_kzn_lava_bubble_EVS_Attack_ShootPartner;
extern EvtScript TTYD64_kzn_EVS_80224BAC;
extern EvtScript TTYD64_kzn_lava_bubble_EVS_TakeTurn;
extern EvtScript TTYD64_kzn_white_magikoopa_EVS_TakeTurn;
extern EvtScript TTYD64_kzn_lava_bubble_EVS_ShootFire_Impl;
extern EvtScript TTYD64_kzn_spike_top_EVS_Init;
extern EvtScript TTYD64_kzn_lava_bubble_EVS_Init;
extern EvtScript TTYD64_kzn_red_magikoopa_EVS_Init_Flying;
extern EvtScript TTYD64_kzn_medi_guy_EVS_Init;
extern EvtScript TTYD64_kzn_putrid_piranha_EVS_TakeTurn;
extern EvtScript TTYD64_kzn_medi_guy_EVS_TakeTurn;
extern EvtScript TTYD64_kzn_white_magikoopa_EVS_Init_Flying;
extern EvtScript TTYD64_kzn_lava_bubble_EVS_ShootFire;
extern EvtScript TTYD64_kzn_putrid_piranha_EVS_Init;
extern ActorBlueprint TTYD64_kzn_red_magikoopa_flying;
extern ActorBlueprint TTYD64_kzn_spike_top;
extern ActorBlueprint TTYD64_kzn_medi_guy;
extern ActorBlueprint TTYD64_kzn_white_magikoopa_flying;
extern ActorBlueprint TTYD64_kzn_lava_bubble;
extern ActorBlueprint TTYD64_kzn_putrid_piranha;
extern Battle TTYD64_kzn_Formations[];
extern ActorPartBlueprint TTYD64_kzn_lava_bubble_ActorParts[];
extern s32 TTYD64_kzn_white_magikoopa_StatusTable_Ground[];
extern s32 TTYD64_kzn_white_magikoopa_StatusTable_Flying[];
extern s32 TTYD64_kzn_white_magikoopa_StatusTable_Ground_80228E78[];
extern s32 TTYD64_kzn_white_magikoopa_StatusTable_Flying_80228FD0[];
extern FormationRow TTYD64_kzn_Formation_0D[];
extern FormationRow TTYD64_kzn_Formation_0E[];
extern FormationRow TTYD64_kzn_Formation_14[];
extern FormationRow TTYD64_kzn_Formation_02[];
extern FormationRow TTYD64_kzn_Formation_03[];
extern ActorPartBlueprint TTYD64_kzn_white_magikoopa_FlyingParts[];
extern ActorPartBlueprint TTYD64_kzn_red_magikoopa_FlyingParts[];
extern FormationRow TTYD64_kzn_Formation_0A[];
extern FormationRow TTYD64_kzn_Formation_0C[];
extern FormationRow TTYD64_kzn_Formation_11[];
extern FormationRow TTYD64_kzn_Formation_12[];
extern FormationRow TTYD64_kzn_Formation_10[];
extern FormationRow TTYD64_kzn_Formation_13[];
extern FormationRow TTYD64_kzn_Formation_01[];
extern FormationRow TTYD64_kzn_Formation_04[];
extern FormationRow TTYD64_kzn_Formation_05[];
extern FormationRow TTYD64_kzn_Formation_06[];
extern FormationRow TTYD64_kzn_Formation_07[];
extern s32 TTYD64_kzn_white_magikoopa_IdleAnimations_80223D70[];
extern s32 TTYD64_kzn_red_magikoopa_FlyingAnims[];
extern s32 TTYD64_kzn_spike_top_GroundAnims[];
extern s32 TTYD64_kzn_medi_guy_DefaultAnims[];
extern s32 TTYD64_kzn_white_magikoopa_IdleAnimations_80223DBC[];
extern s32 TTYD64_kzn_red_magikoopa_GroundAnims[];
extern s32 TTYD64_kzn_spike_top_CeilingAnims[];
extern s32 TTYD64_kzn_putrid_piranha_DefaultAnims[];
extern s32 TTYD64_kzn_lava_bubble_DefaultAnims[];
extern s32 TTYD64_kzn_spike_top_ToppledAnims[];
extern FormationRow TTYD64_kzn_Formation_0B[];
extern FormationRow TTYD64_kzn_Formation_0F[];
extern FormationRow TTYD64_kzn_Formation_00[];
extern FormationRow TTYD64_kzn_Formation_08[];
extern FormationRow TTYD64_kzn_Formation_09[];
extern ActorPartBlueprint TTYD64_kzn_spike_top_ActorParts[];
extern ActorPartBlueprint TTYD64_kzn_medi_guy_ActorParts[];
extern ActorPartBlueprint TTYD64_kzn_putrid_piranha_ActorParts[];
extern s32 TTYD64_kzn_Anims_8022ACD8[];

// clang-format off
EvtScript TTYD64_kzn_white_magikoopa_EVS_Move_HealOne = {
    Set(LVar8, 0)
    Set(LVar9, 9999)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetActorHP, LVar0, LVar2)
    Call(b_area_kzn_white_magikoopa_GetBootsHammerLevel, LVar3, LVar4)
    IfGt(LVar3, LVar4)
        Set(LVar3, LVar4)
    EndIf
    Call(b_area_kzn_white_magikoopa_GetActorDefense, LVar0, LVar1, LVar5)
    Call(GetActorDefenseBoost, LVar0, LVar6)
    Add(LVar5, LVar6)
    Sub(LVar3, LVar5)
    Sub(LVar2, LVar3)
    Call(b_area_kzn_white_magikoopa_CheckMagikoopaCastTarget, LVar0, LVarA)
    IfEq(LVarA, 0)
        Call(GetEnemyMaxHP, LVar0, LVarA)
        Call(GetActorHP, LVar0, LVarB)
        IfNe(LVarA, LVarB)
            IfLt(LVar2, LVar9)
                Set(LVar8, LVar0)
                Set(LVar9, LVar2)
            Else
                IfEq(LVar2, LVar9)
                    IfLt(LVar0, LVar8)
                        Set(LVar8, LVar0)
                        Set(LVar9, LVar2)
                    EndIf
                EndIf
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfNe(LVar8, 0)
        Goto(100)
    EndIf
    Set(LVar8, 0)
    Set(LVar9, 9999)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(1)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetActorHP, LVar0, LVar2)
    Call(b_area_kzn_white_magikoopa_GetBootsHammerLevel, LVar3, LVar4)
    IfGt(LVar3, LVar4)
        Set(LVar3, LVar4)
    EndIf
    Call(b_area_kzn_white_magikoopa_GetActorDefense, LVar0, LVar1, LVar5)
    Call(GetActorDefenseBoost, LVar0, LVar6)
    Add(LVar5, LVar6)
    Sub(LVar3, LVar5)
    Sub(LVar2, LVar4)
    Set(LFlag0, 0)
    Call(GetOriginalActorType, LVar0, LVarA)
    IfEq(LVarA, 71)
        Call(GetActorVar, LVar0, 8, LVarA)
        IfEq(LVarA, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetOwnerID, LVarA)
    IfNe(LVarA, LVar0)
        IfEq(LFlag0, 0)
            Call(GetEnemyMaxHP, LVar0, LVarA)
            Call(GetActorHP, LVar0, LVarB)
            IfNe(LVarA, LVarB)
                IfLt(LVar2, LVar9)
                    Set(LVar8, LVar0)
                    Set(LVar9, LVar2)
                Else
                    IfEq(LVar2, LVar9)
                        IfLt(LVar0, LVar8)
                            Set(LVar8, LVar0)
                            Set(LVar9, LVar2)
                        EndIf
                    EndIf
                EndIf
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(1)
    EndIf
    IfNe(LVar8, 0)
        Goto(100)
    EndIf
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(2)
    Call(GetOwnerTarget, LVar0, LVar1)
    Set(LFlag0, 0)
    Call(GetOriginalActorType, LVar0, LVarA)
    IfEq(LVarA, 71)
        Call(GetActorVar, LVar0, 8, LVarA)
        IfEq(LVarA, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetOwnerID, LVarA)
    IfNe(LVarA, LVar0)
        IfEq(LFlag0, 0)
            Call(GetEnemyMaxHP, LVar0, LVarA)
            Call(GetActorHP, LVar0, LVarB)
            IfNe(LVarA, LVarB)
                Set(LVar8, LVar0)
                Goto(100)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(2)
    EndIf
    Call(GetEnemyMaxHP, ACTOR_SELF, LVarA)
    Call(GetActorHP, ACTOR_SELF, LVarB)
    IfNe(LVarA, LVarB)
        Set(LVar8, -127)
        Goto(100)
    EndIf
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(3)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOwnerID, LVarA)
    IfNe(LVarA, LVar0)
        Call(GetActorFlags, ACTOR_SELF, LVar0)
        IfFlag(LVar0, 512)
            ExecWait(TTYD64_kzn_white_magikoopa_EVS_Attack_MagicBlast_8021F76C)
        Else
            ExecWait(TTYD64_kzn_white_magikoopa_EVS_Attack_WandStrike)
        EndIf
        Return
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(3)
    EndIf
    ExecWait(b_area_kzn_white_magikoopa_EVS_Flee)
    Return
    Label(100)
    Call(RandInt, 1000, LVar0)
    IfGt(LVar0, 750)
        Call(GetActorFlags, ACTOR_SELF, LVar0)
        IfFlag(LVar0, 512)
            ExecWait(TTYD64_kzn_white_magikoopa_EVS_Attack_MagicBlast_8021F76C)
        Else
            ExecWait(TTYD64_kzn_white_magikoopa_EVS_Attack_WandStrike)
        EndIf
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560302)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570302)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560301)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570301)
    EndIf
    Wait(5)
    Thread
        Wait(5)
        Call(PlaySoundAtActor, LVar8, 8301)
        Call(PlaySoundAtActor, LVar8, 532)
        Wait(30)
        Call(PlaySoundAtActor, LVar8, 604)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(HealActor, LVar8, 8, 0)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_spike_top_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_kzn_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfNe(LVar0, 2)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0016)
                SetConst(LVar2, 0x4D0017)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0018)
                SetConst(LVar2, 0x4D0018)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            EndIf
        CaseEq(36)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfNe(LVar0, 2)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0016)
                SetConst(LVar2, 0x4D0017)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0017)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0018)
                SetConst(LVar2, 0x4D0018)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0018)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_kzn_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 8, 2)
            Call(SetTargetOffset, ACTOR_SELF, 1, 1, 20)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -3, -8)
            Call(SetActorVar, ACTOR_SELF, 9, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kzn_spike_top_ToppledDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kzn_spike_top_ToppledAnims))
            Call(SetPartEventBits, ACTOR_SELF, 1, 16, 0)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0013)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            Thread
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -45)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -90)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -135)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -180)
                Wait(1)
            EndThread
            UseBuf(Ref(b_area_kzn_spike_top_FlipPosOffsets))
            Loop(19)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0015)
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0008)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D000B)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(SetAnimation, ACTOR_SELF, 1, 0x4D000E)
                Wait(8)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0005)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(25)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D000B)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(SetAnimation, ACTOR_SELF, 1, 0x4D000C)
                Wait(8)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0005)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(27)
            Wait(10)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                Add(LVar1, 9)
            Else
                Add(LVar1, 24)
            EndIf
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(20)
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_kzn_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_kzn_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_kzn_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_kzn_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0003)
                ExecWait(Ref(EVS_Enemy_Recover))
            EndIf
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0008)
                SetConst(LVar2, 0x4D0013)
                ExecWait(Ref(EVS_Enemy_ScareAway))
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0005)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0008)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0005)
            EndIf
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(SetActorDispOffset, ACTOR_SELF, 7, 0, 0)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0013)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0015)
            EndIf
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D000B)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(SetAnimation, ACTOR_SELF, 1, 0x4D000C)
                Wait(8)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0005)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_spike_top_EVS_Ceiling_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 24)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
    Call(b_area_kzn_spike_top_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kzn_spike_top_EVS_TakeTurn))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kzn_spike_top_EVS_HandleEvent))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kzn_spike_top_GroundAnims))
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
    Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
    Call(GetIndexFromPos, ACTOR_SELF, LVar0)
    Mod(LVar0, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVar0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar4, LVar2)
        Call(SetAnimation, ACTOR_SELF, 1, 0x4D0001)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x4D0009)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar4, LVar2)
        Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x4D0001)
        Wait(8)
    EndIf
    Call(SetActorSounds, ACTOR_SELF, 2, 769, 0)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 5)
        Call(SetBattleCamDist, 430)
        Call(SetBattleCamOffsetY, 20)
        Call(MoveBattleCamOver, 10)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 4, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(SetPartYaw, ACTOR_SELF, 1, 180)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0015)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar1, 24)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(ResetAllActorSounds, ACTOR_SELF)
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Thread
                Wait(5)
                Call(SetAnimation, ACTOR_SELF, 1, 0x4D0000)
            EndThread
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(8)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0008)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0003)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4D0015)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 24)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, LVar4)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 4, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Thread
                Wait(5)
                Call(SetAnimation, ACTOR_SELF, 1, 0x4D0000)
            EndThread
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(8)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0008)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0003)
        EndCaseGroup
    EndSwitch
    Label(10)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_spike_top_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 2)
        Call(GetActorVar, ACTOR_SELF, 9, LVar0)
        Sub(LVar0, 1)
        IfGt(LVar0, 0)
            Call(SetActorVar, ACTOR_SELF, 9, LVar0)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(UseBattleCamPreset, 2)
        Else
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(20)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0005)
            SetConst(LVar2, 0x4D0003)
            ExecWait(Ref(EVS_Enemy_FlipBackUp))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetActorVar, ACTOR_SELF, 8, 1)
            Call(SetTargetOffset, ACTOR_SELF, 1, 0, 24)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kzn_spike_top_UprightDefense))
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kzn_spike_top_GroundAnims))
            Call(BindIdle, ACTOR_SELF, Ref(b_area_kzn_spike_top_EVS_Idle))
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 16, 1)
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
        EndIf
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Return
    EndIf
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4D000B)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4D000F)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(10)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(5)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 8225)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4D000A)
    Wait(20)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 3, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Loop(0)
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Add(LVar0, 30)
                    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
                    IfGt(LVar0, LVar3)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                Call(UseBattleCamPreset, 1)
                IfEq(LVarA, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
                Wait(15)
                Call(UseBattleCamPreset, 2)
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -150, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Wait(15)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 200)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D000C)
            Wait(10)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0003)
            Wait(8)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0008)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0003)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_putrid_piranha_EVS_Attack_Bite = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x360018)
        Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
        Wait(8)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 27)
        Set(LVar1, 0)
        Set(LVar3, LVar0)
        Set(LVar4, LVar1)
        Set(LVar5, LVar2)
        Call(GetOwnerTarget, LVar9, 0)
        Call(GetActorPos, LVar9, LVar6, LVar7, LVar8)
        Add(LVar3, LVar6)
        Add(LVar4, LVar7)
        Add(LVar5, LVar8)
        Div(LVar3, 2)
        Div(LVar4, 2)
        Div(LVar5, 2)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, LVar3, LVar4, LVar5)
        Call(SetBattleCamDist, 300)
        Call(SetBattleCamOffsetY, 40)
        Wait(20)
        Call(PlaySoundAtActor, ACTOR_SELF, 801)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorFlagBits, ACTOR_SELF, 4, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x360017)
        Wait(8)
    Else
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x360003)
        Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
        Call(SetAnimation, ACTOR_SELF, 1, 0x360003)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Add(LVar0, 10)
        Else
            Add(LVar0, 27)
        EndIf
        Set(LVar1, 0)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x360001)
    EndIf
    Thread
        Wait(8)
        Call(PlaySoundAtActor, ACTOR_SELF, 8414)
    EndThread
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x360005)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x360006)
            Wait(6)
            Call(SetAnimation, ACTOR_SELF, 1, 0x360007)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(14)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(YieldTurn)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
                Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
                Call(PlaySoundAtActor, ACTOR_SELF, 802)
                Call(SetAnimation, ACTOR_SELF, 1, 0x360018)
                Wait(10)
                Call(SetGoalToHome, ACTOR_SELF)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(PlaySoundAtActor, ACTOR_SELF, 801)
                Call(SetAnimation, ACTOR_SELF, 1, 0x360017)
                Wait(10)
                Call(SetActorFlagBits, ACTOR_SELF, 4, 0)
            Else
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
                Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
                Call(SetActorYaw, ACTOR_SELF, 180)
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                ExecWait(b_area_kzn_putrid_piranha_EVS_ReturnHome)
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x360005)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x360006)
    Wait(1)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 3, 32)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x360007)
            Wait(20)
            Call(YieldTurn)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
                Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
                Call(PlaySoundAtActor, ACTOR_SELF, 802)
                Call(SetAnimation, ACTOR_SELF, 1, 0x360018)
                Wait(10)
                Call(SetGoalToHome, ACTOR_SELF)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(PlaySoundAtActor, ACTOR_SELF, 801)
                Call(SetAnimation, ACTOR_SELF, 1, 0x360017)
                Wait(10)
                Call(SetActorFlagBits, ACTOR_SELF, 4, 0)
            Else
                Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
                ExecWait(b_area_kzn_putrid_piranha_EVS_ReturnHome)
            EndIf
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_medi_guy_EVS_Attack_Swoop = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Thread
        SetF(LVar0, Float(0.0))
        Loop(15)
            AddF(LVar0, Float(2.0))
            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x400003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 12)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(10)
            Call(PlaySoundAtActor, ACTOR_SELF, 760)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x400005)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 761)
            Thread
                Wait(5)
                Set(LVar0, 0)
                Loop(60)
                    Call(b_area_kzn_medi_guy_MediGuySpriteRotationFunc, LVar0, LVar1, 15, 60, Float(30.0))
                    Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar1)
                    Add(LVar0, 1)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Add(LVar2, 1)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x400005)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(30)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
            ExecWait(b_area_kzn_medi_guy_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 760)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0x400005)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Set(LVarC, LVar2)
    Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 761)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, 1)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x400005)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(UseBattleCamPreset, 2)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpWithBounce, ACTOR_SELF, 10, Float(2.0))
            Wait(20)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_kzn_medi_guy_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_red_magikoopa_EVS_TakeTurn = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_kzn_red_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
        IfEq(LVar3, 0)
            Call(GetActorAttackBoost, LVar0, LVar4)
            IfLt(LVar4, 3)
                Set(LVar8, LVar0)
                Call(SetBattleVar, 2, LVar1)
                Goto(100)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfEq(LFlag0, 0)
        Set(LFlag0, 1)
        Call(SetBattleVar, 2, -1)
        Goto(10)
    EndIf
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_kzn_white_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        ExecWait(TTYD64_kzn_white_magikoopa_EVS_Attack_MagicBlast)
    Else
        ExecWait(TTYD64_kzn_white_magikoopa_EVS_Attack_WandStrike_8021DDDC)
    EndIf
    Return
    Label(100)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560102)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570102)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560101)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570101)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Call(PlaySoundAtActor, LVar8, 733)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(TTYD64_BoostAttack, LVar8, 1, 3)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_white_magikoopa_EVS_Move_HealAll = {
    Call(RandInt, 1000, LVar0)
    IfGt(LVar0, 750)
        Call(GetActorFlags, ACTOR_SELF, LVar0)
        IfFlag(LVar0, 512)
            ExecWait(TTYD64_kzn_white_magikoopa_EVS_Attack_MagicBlast_8021F76C)
        Else
            ExecWait(TTYD64_kzn_white_magikoopa_EVS_Attack_WandStrike)
        EndIf
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560302)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570302)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560301)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570301)
    EndIf
    Wait(5)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Set(LFlag0, 0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar1)
    IfEq(LVar1, 71)
        Call(GetActorVar, LVar0, 8, LVar1)
        IfEq(LVar1, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    IfEq(LFlag0, 0)
        Thread
            Wait(5)
            Call(PlaySoundAtActor, LVar0, 8301)
            Call(PlaySoundAtActor, LVar0, 532)
            Wait(30)
            Call(PlaySoundAtActor, LVar0, 604)
        EndThread
        Thread
            Call(FreezeBattleState, 1)
            Call(HealActor, LVar0, 4, 1)
            Call(FreezeBattleState, 0)
        EndThread
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Call(WaitForBuffDone)
    Wait(1)
    Call(UseBattleCamPreset, 2)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_white_magikoopa_EVS_Attack_WandStrike = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 731)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x560302)
        Set(LVar0, 200)
        Loop(20)
            Sub(LVar0, 10)
            Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 5)
    Else
        Add(LVar0, 25)
    EndIf
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
    Set(LVar0, 55)
    Loop(20)
        Add(LVar0, 10)
        Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_SELF, 1, 255)
    Call(SetAnimation, ACTOR_SELF, 1, 0x560303)
    Wait(11)
    Call(PlaySoundAtActor, ACTOR_SELF, 732)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(UseBattleCamPreset, 2)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560301)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560301)
            Call(FlyToGoal, ACTOR_SELF, 20, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_white_magikoopa_EVS_Attack_WandStrike_8021DDDC = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 731)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x560102)
        Set(LVar0, 200)
        Loop(20)
            Sub(LVar0, 10)
            Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 5)
    Else
        Add(LVar0, 25)
    EndIf
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
    Set(LVar0, 55)
    Loop(20)
        Add(LVar0, 10)
        Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_SELF, 1, 255)
    Call(SetAnimation, ACTOR_SELF, 1, 0x560103)
    Wait(11)
    Call(PlaySoundAtActor, ACTOR_SELF, 732)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(UseBattleCamPreset, 2)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560101)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560101)
            Call(FlyToGoal, ACTOR_SELF, 20, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_white_magikoopa_EVS_HandleEvent_Flying = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            ExecWait(b_area_kzn_white_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570104)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseOrEq(10)
        CaseOrEq(12)
            ExecWait(b_area_kzn_white_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570104)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_kzn_white_magikoopa_EVS_KnockDown)
        EndCaseGroup
        CaseOrEq(14)
        CaseOrEq(15)
            ExecWait(b_area_kzn_white_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570105)
            SetConst(LVar2, 0x570106)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_kzn_white_magikoopa_EVS_KnockDown)
        EndCaseGroup
        CaseEq(36)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570105)
            SetConst(LVar2, 0x570106)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570106)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570104)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570104)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570104)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570101)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570104)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570104)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570101)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570101)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570101)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570104)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570102)
            ExecWait(b_area_kzn_white_magikoopa_EVS_Flee)
            Return
        CaseEq(58)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570102)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                IfFlag(LVar0, 0x80000)
                    Call(SetPartDispOffset, ACTOR_SELF, 2, -3, 0, 0)
                Else
                    Call(SetPartDispOffset, ACTOR_SELF, 2, -15, 0, 0)
                EndIf
            EndIf
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570104)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_white_magikoopa_EVS_HandleEvent_Flying_8021EAAC = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            ExecWait(b_area_kzn_white_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseOrEq(10)
        CaseOrEq(12)
            ExecWait(b_area_kzn_white_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_kzn_white_magikoopa_EVS_KnockDown_80221040)
        EndCaseGroup
        CaseOrEq(14)
        CaseOrEq(15)
            ExecWait(b_area_kzn_white_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570305)
            SetConst(LVar2, 0x570306)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_kzn_white_magikoopa_EVS_KnockDown_80221040)
        EndCaseGroup
        CaseEq(36)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570305)
            SetConst(LVar2, 0x570306)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570306)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570301)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570301)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570301)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570301)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570304)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570302)
            ExecWait(b_area_kzn_white_magikoopa_EVS_Flee)
            Return
        CaseEq(58)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570302)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                IfFlag(LVar0, 0x80000)
                    Call(SetPartDispOffset, ACTOR_SELF, 2, -3, 0, 0)
                Else
                    Call(SetPartDispOffset, ACTOR_SELF, 2, -15, 0, 0)
                EndIf
            EndIf
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_white_magikoopa_EVS_Attack_MagicBlast = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    Else
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 10)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 12)
        Add(LVar1, 14)
    Else
        Sub(LVar0, 30)
        Add(LVar1, 36)
    EndIf
    Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570102)
    Wait(30)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8405)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570103)
            Wait(5)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar9)
            IfFlag(LVar9, 0x80000)
                Sub(LVar0, 8)
                Add(LVar1, 8)
            Else
                Sub(LVar0, 20)
                Add(LVar1, 20)
            EndIf
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Sub(LVar3, 50)
            Set(LVar4, 0)
            Call(b_area_kzn_white_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
            Wait(50)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(14)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 8405)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570103)
    Wait(5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 8)
        Add(LVar1, 8)
    Else
        Sub(LVar0, 20)
        Add(LVar1, 20)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 10)
    Call(b_area_kzn_white_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
    Wait(18)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(19)
            Call(YieldTurn)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_white_magikoopa_EVS_Attack_MagicBlast_8021F76C = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    Else
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 10)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 12)
        Add(LVar1, 14)
    Else
        Sub(LVar0, 30)
        Add(LVar1, 36)
    EndIf
    Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570302)
    Wait(30)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8405)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570303)
            Wait(5)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar9)
            IfFlag(LVar9, 0x80000)
                Sub(LVar0, 8)
                Add(LVar1, 8)
            Else
                Sub(LVar0, 20)
                Add(LVar1, 20)
            EndIf
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Sub(LVar3, 50)
            Set(LVar4, 0)
            Call(b_area_kzn_white_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
            Wait(50)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(14)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 8405)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570303)
    Wait(5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 8)
        Add(LVar1, 8)
    Else
        Sub(LVar0, 20)
        Add(LVar1, 20)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 10)
    Call(b_area_kzn_white_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
    Wait(18)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(19)
            Call(YieldTurn)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_EVS_8021FDC8 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(GetOwnerTarget, LVarA, 0)
    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460001)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460005)
    Wait(30)
    Call(PlaySoundAtActor, ACTOR_SELF, 720)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460006)
    Thread
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 1, 0x460001)
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Add(LVar1, 4)
    Add(LVar2, 2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(TTYD64_GetMarioPos, LVar0)
    IfEq(LVar0, 0)
        Set(LVarB, 256)
    Else
        Set(LVarB, 0)
    EndIf
    Call(GetGoalPos, LVarB, LVar3, LVar4, LVar5)
    Add(LVar3, 55)
    Sub(LVar4, 6)
    Add(LVar5, 2)
    Set(LVar6, 6)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.5), Float(0.5), Float(0.5))
    Else
        Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.7998046875), Float(0.7998046875), Float(0.7998046875))
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Add(LVar1, 4)
    Add(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, LVar6, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 0)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(6.0))
    Call(SetPartJumpGravity, ACTOR_SELF, LVar6, Float(0.009765625))
    Call(SetPartSounds, ACTOR_SELF, LVar6, 2, 720, 0)
    Call(FlyPartTo, ACTOR_SELF, LVar6, LVar3, LVar1, LVar5, 0, 0, 4)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(4.0))
    Call(GetPartPos, ACTOR_SELF, LVar6, LVar3, LVar4, LVar5)
    Add(LVar3, 40)
    Call(FlyPartTo, ACTOR_SELF, LVar6, LVar3, LVar1, LVar5, 0, 0, 4)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(5.0))
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(FlyPartTo, ACTOR_SELF, LVar6, LVar3, LVar1, LVar5, 0, 0, 3)
    Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 1)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000002, 0, 0, 3, 32)
    EndSwitch
    Wait(20)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            ExecWait(b_area_kzn_lava_bubble_EVS_Ember_FlyHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_putrid_piranha_EVS_Attack_Bite_80220414 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Set(LVar1, 5)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Thread
        Call(b_area_kzn_lava_bubble_PlayLavaBubbleFlightSound)
    EndThread
    Call(FlyToGoal, ACTOR_SELF, 0, 0, 11)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460001)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x460004)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 0)
            Add(LVar2, 1)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Sub(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Sub(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 3, 0, 1, 0)
            Wait(14)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(b_area_kzn_lava_bubble_EVS_Ember_FlyHome)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x460004)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, 1)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 130, 0, 0, 4, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Set(LVar0, 1)
            Set(LVar1, 0x460004)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Wait(5)
            ExecWait(b_area_kzn_lava_bubble_EVS_Ember_FlyHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_white_magikoopa_EVS_KnockDown = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560104)
        Goto(0)
    EndIf
    Call(GetLastElement, LVar0)
    IfFlag(LVar0, 1024)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560104)
        Goto(0)
    EndIf
    Return
    Label(0)
    Call(HideHealthBar, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 3, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    EndIf
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x800000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20001, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20001, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x800000, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 0x100000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar2, 1)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(PlaySoundAtActor, ACTOR_SELF, 769)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(b_area_kzn_white_magikoopa_StartRumbleWithParams, 150, 10)
    Thread
        Call(ShakeCam, 1, 0, 5, Float(0.7001953125))
    EndThread
    Call(GetLastEvent, ACTOR_SELF, LVar3)
    IfEq(LVar3, 15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560104)
        Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Add(LVar4, 10)
        Add(LVar5, 5)
        Call(PlayEffect_impl, 39, 0, LVar3, LVar4, LVar5, Float(1.0), 10, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Loop(20)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
        Wait(1)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
        Wait(1)
    EndLoop
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x560101)
    Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kzn_red_magikoopa_EVS_HandleEvent))
    Call(SetActorType, ACTOR_SELF, 81)
    Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_kzn_white_magikoopa_StatusTable_Ground_80228E78))
    Call(b_area_kzn_white_magikoopa_SetAbsoluteStatusOffsets, -10, 20, 10, 32)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(GetIndexFromPos, ACTOR_SELF, LVar0)
    Mod(LVar0, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVar0)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_white_magikoopa_EVS_KnockDown_80221040 = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560304)
        Goto(0)
    EndIf
    Call(GetLastElement, LVar0)
    IfFlag(LVar0, 1024)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560304)
        Goto(0)
    EndIf
    Return
    Label(0)
    Call(HideHealthBar, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 3, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    EndIf
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x800000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20001, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20001, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x800000, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 0x100000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar2, 1)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(PlaySoundAtActor, ACTOR_SELF, 769)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(b_area_kzn_white_magikoopa_StartRumbleWithParams, 150, 10)
    Thread
        Call(ShakeCam, 1, 0, 5, Float(0.7001953125))
    EndThread
    Call(GetLastEvent, ACTOR_SELF, LVar3)
    IfEq(LVar3, 15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560304)
        Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Add(LVar4, 10)
        Add(LVar5, 5)
        Call(PlayEffect_impl, 39, 0, LVar3, LVar4, LVar5, Float(1.0), 10, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Loop(20)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
        Wait(1)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
        Wait(1)
    EndLoop
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x560301)
    Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kzn_white_magikoopa_EVS_HandleEvent_Ground))
    Call(SetActorType, ACTOR_SELF, 89)
    Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_kzn_white_magikoopa_StatusTable_Ground))
    Call(b_area_kzn_white_magikoopa_SetAbsoluteStatusOffsets, -10, 20, 10, 32)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(GetIndexFromPos, ACTOR_SELF, LVar0)
    Mod(LVar0, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVar0)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_putrid_piranha_EVS_Attack_BadBreath = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x360003)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x360003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 16)
    Else
        Add(LVar0, 40)
    EndIf
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x360001)
    Call(SetAnimation, ACTOR_SELF, 1, 0x360008)
    Wait(11)
    Call(PlaySoundAtActor, ACTOR_SELF, 939)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 12)
        Set(LVar1, 5)
        SetF(LVar3, Float(0.400390625))
    Else
        Add(LVar0, 32)
        Set(LVar1, 13)
        SetF(LVar3, Float(1.0))
    EndIf
    Call(b_area_kzn_putrid_piranha_UnkEffect6FFunc, LVar2, LVar0, LVar1, LVar2, LVar3, 30, 120, 0, 120)
    Wait(1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x360009)
    Wait(5)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x36000A)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(14)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(b_area_kzn_putrid_piranha_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0xFFFF, -0x7FFDFC9C, 2, 32)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x36000A)
            Wait(20)
            Call(YieldTurn)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_kzn_putrid_piranha_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_spike_top_EVS_Ceiling_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_kzn_spike_top_EVS_FallFromCeiling)
        CaseEq(13)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_kzn_spike_top_EVS_FallFromCeiling)
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0019)
            SetConst(LVar2, 0x4D001A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_kzn_spike_top_EVS_FallFromCeiling)
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0019)
            SetConst(LVar2, 0x4D001A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D001A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0008)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D000D)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D000D)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Wait(2)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x200000)
                ExecWait(TTYD64_kzn_spike_top_EVS_FallFromCeiling)
            EndIf
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 1)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0009)
            SetConst(LVar2, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_spike_top_EVS_FallFromCeiling = {
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 2)
    Call(SetTargetOffset, ACTOR_SELF, 1, 1, 20)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -3, -8)
    Call(b_area_kzn_spike_top_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kzn_spike_top_EVS_TakeTurn))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kzn_spike_top_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 9, 1)
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kzn_spike_top_ToppledDefense))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kzn_spike_top_ToppledAnims))
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(SetPartEventBits, ACTOR_SELF, 1, 16, 0)
    Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
    Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4D0015)
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 24)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetActorSounds, ACTOR_SELF, 2, 769, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(GetIndexFromPos, ACTOR_SELF, LVarA)
    Mod(LVarA, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVarA)
    Call(GetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(SetHomePos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Set(LVarD, LVarA)
    Set(LVarE, LVarB)
    Set(LVarF, LVarC)
    Sub(LVarD, LVar0)
    Sub(LVarE, LVar1)
    Sub(LVarF, LVar2)
    Div(LVarD, 2)
    Div(LVarE, 2)
    Div(LVarF, 2)
    Add(LVar0, LVarD)
    Add(LVar1, LVarE)
    Add(LVar2, LVarF)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4D0005)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_lava_bubble_EVS_Attack_ShootPartner = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 256)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(TTYD64_GetMarioPos, LVar0)
    IfEq(LVar0, 0)
        Set(LVarA, 256)
    Else
        Set(LVarA, 0)
    EndIf
    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfEq(LVarA, 1)
        Add(LVar0, 100)
        Set(LVar1, 5)
    Else
        Add(LVar0, 30)
        Set(LVar1, 50)
    EndIf
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460003)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Thread
        Call(b_area_kzn_lava_bubble_PlayLavaBubbleFlightSound)
    EndThread
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 11)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460001)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460005)
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460006)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Add(LVar1, 4)
    Add(LVar2, 2)
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfLe(LVar0, 0)
        Call(SetTargetActor, ACTOR_SELF, 0)
    Else
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar4, 6)
    Add(LVar5, 2)
    ExecWait(TTYD64_kzn_lava_bubble_EVS_ShootFire)
    Wait(20)
    Switch(LVar9)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(b_area_kzn_lava_bubble_EVS_Ember_FlyHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_EVS_80224BAC = {
    Loop(0)
        Call(GetPartPos, ACTOR_SELF, LVar6, LVar1, 0, LVar2)
        Call(TTYD64_GetMarioPos, LVar0)
        IfEq(LVar0, 0)
            Set(LVar0, 256)
        Else
            Set(LVar0, 0)
        EndIf
        Call(GetActorPos, LVar0, LVar3, 0, LVar4)
        Call(GetDist2D, LVar0, LVar1, LVar2, LVar3, LVar4)
        IfLe(LVar0, 12)
            Call(GetOwnerTarget, LVar5, 0)
            Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVar9, 0, 0, 1, 16)
            Switch(LVar9)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarA, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar9, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    BreakLoop
            EndSwitch
            Call(EnemyDamageTarget, ACTOR_SELF, LVar9, 0x10000002, 0, 0, 3, 32)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVar9, 0, 0, 1, 16)
    Switch(LVar9)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar9, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVar9, 0x10000002, 0, 0, 3, 32)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_lava_bubble_EVS_TakeTurn = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Switch(LVar0)
            CaseEq(1)
                Call(RandInt, 99, LVar0)
                IfLt(LVar0, 49)
                    ExecWait(TTYD64_kzn_EVS_8021FDC8)
                Else
                    ExecWait(TTYD64_kzn_putrid_piranha_EVS_Attack_Bite_80220414)
                EndIf
            CaseEq(0)
                ExecWait(TTYD64_kzn_lava_bubble_EVS_Attack_ShootPartner)
        EndSwitch
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(1)
            Call(GetStatusFlags, 256, LVar0)
            IfFlag(LVar0, 0x1000000)
                Call(RandInt, 99, LVar0)
                IfLt(LVar0, 49)
                    ExecWait(TTYD64_kzn_EVS_8021FDC8)
                Else
                    ExecWait(TTYD64_kzn_putrid_piranha_EVS_Attack_Bite_80220414)
                EndIf
            Else
                Call(RandInt, 1000, LVar0)
                IfLe(LVar0, 300)
                    ExecWait(TTYD64_kzn_lava_bubble_EVS_Attack_ShootPartner)
                Else
                    Call(RandInt, 99, LVar0)
                    IfLt(LVar0, 49)
                        ExecWait(TTYD64_kzn_EVS_8021FDC8)
                    Else
                        ExecWait(TTYD64_kzn_putrid_piranha_EVS_Attack_Bite_80220414)
                    EndIf
                EndIf
            EndIf
        CaseEq(0)
            Call(GetStatusFlags, 256, LVar0)
            IfFlag(LVar0, 0x1000000)
                ExecWait(TTYD64_kzn_lava_bubble_EVS_Attack_ShootPartner)
            Else
                Call(RandInt, 1000, LVar0)
                IfLe(LVar0, 300)
                    ExecWait(TTYD64_kzn_lava_bubble_EVS_Attack_ShootPartner)
                Else
                    ExecWait(TTYD64_kzn_lava_bubble_EVS_Attack_ShootPartner)
                EndIf
            EndIf
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_white_magikoopa_EVS_TakeTurn = {
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_kzn_white_magikoopa_EVS_Flee)
        Return
    EndIf
    Set(LVarA, 0)
    Set(LVarB, 0)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Set(LFlag0, 0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar1)
    IfEq(LVar1, 71)
        Call(GetActorVar, LVar0, 8, LVar1)
        IfEq(LVar1, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    IfEq(LFlag0, 0)
        Call(GetActorHP, LVar0, LVar2)
        Call(GetEnemyMaxHP, LVar0, LVar3)
        IfNe(LVar2, LVar3)
            Add(LVarA, 1)
        EndIf
        Add(LVarB, 1)
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Mul(LVarA, 100)
    Div(LVarA, LVarB)
    Switch(LVarA)
        CaseGe(60)
            ExecWait(TTYD64_kzn_white_magikoopa_EVS_Move_HealAll)
        CaseEq(0)
            Call(GetActorFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 512)
                ExecWait(TTYD64_kzn_white_magikoopa_EVS_Attack_MagicBlast_8021F76C)
            Else
                ExecWait(TTYD64_kzn_white_magikoopa_EVS_Attack_WandStrike)
            EndIf
        CaseDefault
            ExecWait(TTYD64_kzn_white_magikoopa_EVS_Move_HealOne)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_lava_bubble_EVS_ShootFire_Impl = {
    Set(LVar6, 2)
    Set(LVar7, 4)
    Loop(LVar7)
        Thread
            Call(GetStatusFlags, ACTOR_SELF, LVarA)
            IfFlag(LVarA, 0x80000)
                Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.2001953125), Float(0.2001953125), Float(0.2001953125))
            Else
                Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.5), Float(0.5), Float(0.5))
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 5)
            Add(LVar1, 4)
            Add(LVar2, 2)
            Call(SetPartPos, ACTOR_SELF, LVar6, LVar0, LVar1, LVar2)
            Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(8.0))
            Call(SetPartJumpGravity, ACTOR_SELF, LVar6, Float(0.009765625))
            Call(SetPartSounds, ACTOR_SELF, LVar6, 2, 720, 0)
            IfEq(LVar7, 4)
                Call(TTYD64_GetPartnerHP_API, LVar8)
                IfGt(LVar8, 0)
                    Exec(TTYD64_kzn_EVS_80224BAC)
                EndIf
            EndIf
            Call(JumpPartTo, ACTOR_SELF, LVar6, LVar3, LVar4, LVar5, 0, 0)
            Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 1)
        EndThread
        Wait(3)
        Add(LVar6, 1)
    EndLoop
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_spike_top_EVS_Init = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kzn_spike_top_EVS_Idle))
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 8, 0)
        Call(b_area_kzn_spike_top_SetAbsoluteStatusOffsets, -10, 0, 10, 0)
        Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kzn_spike_top_EVS_Ceiling_TakeTurn))
        Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kzn_spike_top_EVS_Ceiling_HandleEvent))
        Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 0)
    Else
        Call(SetActorVar, ACTOR_SELF, 8, 1)
        Call(SetTargetOffset, ACTOR_SELF, 1, 0, 24)
        Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
        Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kzn_spike_top_EVS_TakeTurn))
        Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kzn_spike_top_EVS_HandleEvent))
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kzn_spike_top_GroundAnims))
        Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
        Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
        Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
    EndIf
    Call(HPBarToHome, ACTOR_SELF)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_lava_bubble_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kzn_lava_bubble_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kzn_lava_bubble_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kzn_lava_bubble_EVS_HandleEvent))
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
    EndSwitch
    Call(SetPartScale, ACTOR_SELF, 2, Float(0.5), Float(0.5), Float(0.5))
    Call(SetPartScale, ACTOR_SELF, 3, Float(0.5), Float(0.5), Float(0.5))
    Call(SetPartScale, ACTOR_SELF, 4, Float(0.5), Float(0.5), Float(0.5))
    Call(SetPartScale, ACTOR_SELF, 5, Float(0.5), Float(0.5), Float(0.5))
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 5)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

Battle TTYD64_kzn_Formations[] = {
    { .name = "\320\326\353x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kzn_Formation_00,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\320\326\353x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kzn_Formation_01,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\320\326\353x4",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kzn_Formation_02,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\320\326\353,\310\262\341\303\310x\023",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kzn_Formation_03,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\320\326\353x2,KDuO\330\244\333\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kzn_Formation_04,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\320\326\353x2,\354\303\311\253\341\303\257",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kzn_Formation_05,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\320\326\353x2,\333\357\244\310\253\341\303\257",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kzn_Formation_06,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\320\326\353x2,\310\262\341\303\310",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kzn_Formation_07,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\310\262\341\303\310x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kzn_Formation_08,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\310\262\341\303\310,\320\326\353",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kzn_Formation_09,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\310\262\341\303\310x\022,\320\326\353",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kzn_Formation_0A,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\310\262\341\303\310,\335\244\272\363\321\303\257\363",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kzn_Formation_0B,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\310\262\341\303\310x\022,\335\244\272\363\321\303\257\363",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kzn_Formation_0C,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\310\262\341\303\310x\022,\335\244\272\363\321\303\257\363x\022",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kzn_Formation_0D,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\310\262\341\303\310,\320\326\353x\023",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kzn_Formation_0E,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\335\244\272\363\321\303\257\363x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kzn_Formation_0F,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\335\244\272\363\321\303\257\363x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kzn_Formation_10,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\335\244\272\363\321\303\257\363,\320\326\353,\335\244\272\363\321\303\257\363",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kzn_Formation_11,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\335\244\272\363\321\303\257\363x\022,\310\262\341\303\310",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kzn_Formation_12,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name = "\335\244\272\363\321\303\257\363,\310\262\341\303\310,\335\244\272\363\321\303\257\363",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kzn_Formation_13,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    { .name =
          "\335\244\272\363\321\303\257\363,\310\262\341\303\310,\335\244\272\363\321\303\257\363,\310\262\341\303\310",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kzn_Formation_14,
      .stage = &b_area_kzn_kzn_01,
      .onBattleStart = NULL },
    {},
};

ActorPartBlueprint TTYD64_kzn_lava_bubble_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 25 },
        .opacity = 255,
        .idleAnimations = TTYD64_kzn_lava_bubble_DefaultAnims,
        .defenseTable = b_area_kzn_lava_bubble_DefenseTable,
        .eventFlags = 0x2,
        .elementImmunityFlags = 0x2,
        .projectileTargetOffset = { -3, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = b_area_kzn_lava_bubble_ProjectileAnims,
        .defenseTable = b_area_kzn_lava_bubble_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = b_area_kzn_lava_bubble_ProjectileAnims,
        .defenseTable = b_area_kzn_lava_bubble_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = b_area_kzn_lava_bubble_ProjectileAnims,
        .defenseTable = b_area_kzn_lava_bubble_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = b_area_kzn_lava_bubble_ProjectileAnims,
        .defenseTable = b_area_kzn_lava_bubble_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 6,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_kzn_Anims_8022ACD8,
        .defenseTable = b_area_kzn_lava_bubble_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_kzn_white_magikoopa_StatusTable_Ground[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  75, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_kzn_white_magikoopa_StatusTable_Flying[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  100, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,   33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_kzn_white_magikoopa_StatusTable_Ground_80228E78[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  75, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_kzn_white_magikoopa_StatusTable_Flying_80228FD0[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  100, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,   33, 0, 38, 0,  39, 0,  41, -1, 0,
};

// clang-format off
EvtScript TTYD64_kzn_red_magikoopa_EVS_Init_Flying = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kzn_white_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kzn_red_magikoopa_EVS_TakeTurn))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kzn_white_magikoopa_EVS_HandleEvent_Flying))
    Call(GetBattleVar, 2, LVar0)
    IfEq(LVar0, 0)
        Call(SetBattleVar, 2, -1)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_medi_guy_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kzn_medi_guy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kzn_medi_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kzn_medi_guy_EVS_HandleEvent))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 5)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_putrid_piranha_EVS_TakeTurn = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_kzn_putrid_piranha_EVS_Attack_Bite)
        Return
    EndIf
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 70)
        ExecWait(TTYD64_kzn_putrid_piranha_EVS_Attack_BadBreath)
    Else
        ExecWait(TTYD64_kzn_putrid_piranha_EVS_Attack_Bite)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_medi_guy_EVS_TakeTurn = {
    ExecWait(b_area_kzn_medi_guy_EVS_FindInjuredActor)
    IfEq(LVar0, -1)
        ExecWait(TTYD64_kzn_medi_guy_EVS_Attack_Swoop)
    Else
        Call(RandInt, 1000, LVarA)
        IfLt(LVarA, 600)
            ExecWait(b_area_kzn_medi_guy_EVS_Move_HealOne)
        Else
            ExecWait(TTYD64_kzn_medi_guy_EVS_Attack_Swoop)
        EndIf
    EndIf
    Return
    End
};
// clang-format on

FormationRow TTYD64_kzn_Formation_0D[] = {
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
};

FormationRow TTYD64_kzn_Formation_0E[] = {
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
};

FormationRow TTYD64_kzn_Formation_14[] = {
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
};

FormationRow TTYD64_kzn_Formation_02[] = {
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
};

FormationRow TTYD64_kzn_Formation_03[] = {
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
};

ActorPartBlueprint TTYD64_kzn_white_magikoopa_FlyingParts[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_kzn_white_magikoopa_IdleAnimations_80223D70,
        .defenseTable = b_area_kzn_white_magikoopa_DefenseTable_80223B2C,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -10, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_kzn_white_magikoopa_IdleAnimations_80223DBC,
        .defenseTable = b_area_kzn_white_magikoopa_DefenseTable_80223B2C,
        .eventFlags = 0x800000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_kzn_white_magikoopa_IdleAnimations_80223E08,
        .defenseTable = b_area_kzn_white_magikoopa_DefenseTable_80223B2C,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_kzn_red_magikoopa_FlyingParts[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_kzn_red_magikoopa_GroundAnims,
        .defenseTable = b_area_kzn_white_magikoopa_DefenseTable_80223B2C,
        .eventFlags = 0x800000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -10, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_kzn_red_magikoopa_FlyingAnims,
        .defenseTable = b_area_kzn_white_magikoopa_DefenseTable_80223B2C,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_kzn_red_magikoopa_BroomAnims,
        .defenseTable = b_area_kzn_white_magikoopa_DefenseTable_80223B2C,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_kzn_white_magikoopa_EVS_Init_Flying = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kzn_white_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kzn_white_magikoopa_EVS_TakeTurn))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kzn_white_magikoopa_EVS_HandleEvent_Flying_8021EAAC))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn_lava_bubble_EVS_ShootFire = {
    Exec(TTYD64_kzn_lava_bubble_EVS_ShootFire_Impl)
    Call(GetDistanceToGoal, ACTOR_SELF, LVar0)
    DivF(LVar0, Float(8.0))
    Add(LVar0, 1)
    Wait(LVar0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_kzn_Formation_0A[] = {
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
};

FormationRow TTYD64_kzn_Formation_0C[] = {
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
};

FormationRow TTYD64_kzn_Formation_11[] = {
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
};

FormationRow TTYD64_kzn_Formation_12[] = {
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
};

FormationRow TTYD64_kzn_Formation_10[] = {
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
};

FormationRow TTYD64_kzn_Formation_13[] = {
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
};

FormationRow TTYD64_kzn_Formation_01[] = {
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
};

FormationRow TTYD64_kzn_Formation_04[] = {
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_kzn_Formation_05[] = {
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_red_magikoopa_flying,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kzn_Formation_06[] = {
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_white_magikoopa_flying,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kzn_Formation_07[] = {
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
};

// clang-format off
EvtScript TTYD64_kzn_putrid_piranha_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kzn_putrid_piranha_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kzn_putrid_piranha_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kzn_putrid_piranha_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_kzn_white_magikoopa_IdleAnimations_80223D70[] = {
    1,  0x560301, 7, 0x560300, 6, 0x560308, 9, 0x560301, 8, 0x560300,
    11, 0x560301, 5, 0x560300, 4, 0x560307, 3, 0x560307, 0,
};

s32 TTYD64_kzn_red_magikoopa_FlyingAnims[] = {
    1,  0x570101, 7, 0x570100, 6, 0x570108, 9, 0x570101, 8, 0x570100,
    11, 0x570101, 5, 0x570100, 4, 0x570107, 3, 0x570107, 0,
};

s32 TTYD64_kzn_spike_top_GroundAnims[] = {
    1,  0x4D0003, 7, 0x4D0000, 6, 0x4D001B, 9, 0x4D0003, 8, 0x4D0000,
    11, 0x4D0003, 5, 0x4D0000, 4, 0x4D001E, 3, 0x4D001E, 0,
};

s32 TTYD64_kzn_medi_guy_DefaultAnims[] = {
    1,  0x400001, 7, 0x400000, 6, 0x400004, 9, 0x400001, 8, 0x400000,
    11, 0x400001, 5, 0x400000, 4, 0x40000A, 3, 0x40000A, 0,
};

s32 TTYD64_kzn_white_magikoopa_IdleAnimations_80223DBC[] = {
    1,  0x570301, 7, 0x570300, 6, 0x570308, 9, 0x570301, 8, 0x570300,
    11, 0x570301, 5, 0x570300, 4, 0x570307, 3, 0x570307, 0,
};

s32 TTYD64_kzn_red_magikoopa_GroundAnims[] = {
    1,  0x560101, 7, 0x560100, 6, 0x560108, 9, 0x560101, 8, 0x560100,
    11, 0x560101, 5, 0x560100, 4, 0x560107, 3, 0x560107, 0,
};

s32 TTYD64_kzn_spike_top_CeilingAnims[] = {
    1,  0x4D0004, 7, 0x4D0001, 6, 0x4D001C, 9, 0x4D0004, 8, 0x4D0001,
    11, 0x4D0004, 5, 0x4D0001, 4, 0x4D001F, 3, 0x4D001F, 0,
};

s32 TTYD64_kzn_putrid_piranha_DefaultAnims[] = {
    1,  0x360001, 7, 0x360000, 6, 0x360000, 9, 0x360001, 8, 0x360000,
    11, 0x360000, 5, 0x360000, 5, 0x360000, 4, 0x36000F, 0,
};

s32 TTYD64_kzn_lava_bubble_DefaultAnims[] = {
    1,  0x460001, 7, 0x460000, 6, 0x460001, 9, 0x460001, 8, 0x460000,
    11, 0x460001, 5, 0x460000, 4, 0x46000A, 3, 0x46000A, 0,
};

s32 TTYD64_kzn_spike_top_ToppledAnims[] = {
    1, 0x4D0005, 7, 0x4D0002, 6, 0x4D001D, 9, 0x4D0005, 8, 0x4D0002, 11, 0x4D0005, 4, 0x4D0020, 3, 0x4D0020, 0,
};

FormationRow TTYD64_kzn_Formation_0B[] = {
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
};

FormationRow TTYD64_kzn_Formation_0F[] = {
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_kzn_putrid_piranha,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
};

FormationRow TTYD64_kzn_Formation_00[] = {
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
};

FormationRow TTYD64_kzn_Formation_08[] = {
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
};

FormationRow TTYD64_kzn_Formation_09[] = {
    { .actor = &TTYD64_kzn_spike_top,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_kzn_lava_bubble,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
};

ActorBlueprint TTYD64_kzn_red_magikoopa_flying = {
    .flags = 0x200,
    .maxHP = 11,
    .type = 0x52,
    .level = 21,
    .partCount = 3,
    .partsData = TTYD64_kzn_red_magikoopa_FlyingParts,
    .initScript = &TTYD64_kzn_red_magikoopa_EVS_Init_Flying,
    .statusTable = TTYD64_kzn_white_magikoopa_StatusTable_Flying,
    .escapeChance = 40,
    .airLiftChance = 95,
    .hurricaneChance = 75,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 48, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -25, 20 },
    .statusTextOffset = { 1, 34 },
};

ActorBlueprint TTYD64_kzn_spike_top = {
    .flags = 0x800,
    .maxHP = 5,
    .type = 0x2C,
    .level = 17,
    .partCount = 1,
    .partsData = TTYD64_kzn_spike_top_ActorParts,
    .initScript = &TTYD64_kzn_spike_top_EVS_Init,
    .statusTable = b_area_kzn_spike_top_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 70,
    .hurricaneChance = 65,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 24, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -8, 16 },
    .statusTextOffset = { 8, 13 },
};

ActorBlueprint TTYD64_kzn_medi_guy = {
    .flags = 0x200,
    .maxHP = 7,
    .type = 0x22,
    .level = 14,
    .partCount = 1,
    .partsData = TTYD64_kzn_medi_guy_ActorParts,
    .initScript = &TTYD64_kzn_medi_guy_EVS_Init,
    .statusTable = b_area_kzn_medi_guy_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 90,
    .hurricaneChance = 95,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 2,
    .size = { 24, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 12, 31 },
};

ActorBlueprint TTYD64_kzn_white_magikoopa_flying = {
    .flags = 0x200,
    .maxHP = 11,
    .type = 0x5A,
    .level = 21,
    .partCount = 3,
    .partsData = TTYD64_kzn_white_magikoopa_FlyingParts,
    .initScript = &TTYD64_kzn_white_magikoopa_EVS_Init_Flying,
    .statusTable = TTYD64_kzn_white_magikoopa_StatusTable_Flying_80228FD0,
    .escapeChance = 40,
    .airLiftChance = 95,
    .hurricaneChance = 75,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 48, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -25, 20 },
    .statusTextOffset = { 1, 34 },
};

ActorBlueprint TTYD64_kzn_lava_bubble = {
    .flags = 0x200,
    .maxHP = 9,
    .type = 0x2B,
    .level = 17,
    .partCount = 6,
    .partsData = TTYD64_kzn_lava_bubble_ActorParts,
    .initScript = &TTYD64_kzn_lava_bubble_EVS_Init,
    .statusTable = b_area_kzn_lava_bubble_StatusTable,
    .escapeChance = 50,
    .airLiftChance = 90,
    .hurricaneChance = 85,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 1,
    .size = { 33, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_kzn_putrid_piranha = {
    .flags = 0x0,
    .maxHP = 12,
    .type = 0x2D,
    .level = 17,
    .partCount = 1,
    .partsData = TTYD64_kzn_putrid_piranha_ActorParts,
    .initScript = &TTYD64_kzn_putrid_piranha_EVS_Init,
    .statusTable = b_area_kzn_putrid_piranha_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 20,
    .hurricaneChance = 20,
    .spookChance = 30,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 1,
    .size = { 60, 52 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -22, 32 },
    .statusTextOffset = { 1, 44 },
};

ActorPartBlueprint TTYD64_kzn_spike_top_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_kzn_spike_top_CeilingAnims,
        .defenseTable = b_area_kzn_spike_top_UprightDefense,
        .eventFlags = 0x1010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 14 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_kzn_medi_guy_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 38 },
        .opacity = 255,
        .idleAnimations = TTYD64_kzn_medi_guy_DefaultAnims,
        .defenseTable = b_area_kzn_medi_guy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -5 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_kzn_putrid_piranha_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -15, 50 },
        .opacity = 255,
        .idleAnimations = TTYD64_kzn_putrid_piranha_DefaultAnims,
        .defenseTable = b_area_kzn_putrid_piranha_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 3, -14 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_kzn_Anims_8022ACD8[] = {
    1,
    0x46000C,
    0,
};

void TTYD64_InstallBattles_kzn(void) {
    Mod_SetBattleList("TTYD64", 22, TTYD64_kzn_Formations);
}
