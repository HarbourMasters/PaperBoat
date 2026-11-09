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
API_CALLABLE(AfflictActor);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(CreateHomeTargetList);
API_CALLABLE(DispatchDamageEvent);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FallToGoal);
API_CALLABLE(FlyPartTo);
API_CALLABLE(FlyToGoal);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetDamageSource);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetIdleGoal);
API_CALLABLE(GetIndexFromHome);
API_CALLABLE(GetIndexFromPos);
API_CALLABLE(GetLastDamage);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOriginalActorType);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToCurrent);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HideHealthBar);
API_CALLABLE(IdleJumpToGoal);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(InterruptLeechActionCommand);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActor);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(ResetAllActorSounds);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorIdleJumpGravity);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSize);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetAnimationRate);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetDefenseTable);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetIdleGoal);
API_CALLABLE(SetIdleGoalToHome);
API_CALLABLE(SetPartEventBits);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSize);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetPartYaw);
API_CALLABLE(SetProjectileTargetOffset);
API_CALLABLE(SetTargetActor);
API_CALLABLE(SetTargetOffset);
API_CALLABLE(ShakeCam);
API_CALLABLE(StartRumble);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
API_CALLABLE(b_area_isk_part_1_buzzy_beetle_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_isk_part_1_pokey_mummy_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_isk_part_1_stone_chomp_ChompChainInit);
API_CALLABLE(b_area_isk_part_1_swooper_SetAbsoluteStatusOffsets);
extern EvtScript b_area_isk_part_1_buzzy_beetle_EVS_CheckToppleAnim;
extern EvtScript b_area_isk_part_1_buzzy_beetle_EVS_Idle;
extern u8 b_area_isk_part_1_buzzy_beetle_FlipPosOffsets[];
extern s32 b_area_isk_part_1_buzzy_beetle_ToppledDefense[];
extern s32 b_area_isk_part_1_buzzy_beetle_UprightDefense[];
extern Stage b_area_isk_part_1_isk_02b;
extern Stage b_area_isk_part_1_isk_04;
extern Stage b_area_isk_part_1_isk_05;
extern EvtScript b_area_isk_part_1_pokey_mummy_EVS_HitReactionBounce;
extern s32 b_area_isk_part_1_pokey_mummy_ThrownPartAnims[];
extern s32 b_area_isk_part_1_stone_chomp_ChainAnims[];
extern s32 b_area_isk_part_1_stone_chomp_DefenseTable[];
extern EvtScript b_area_isk_part_1_stone_chomp_EVS_Chomp_HopHome;
extern EvtScript b_area_isk_part_1_stone_chomp_EVS_Chomp_HopToPos;
extern EvtScript b_area_isk_part_1_stone_chomp_EVS_UpdateChain;
extern EvtScript b_area_isk_part_1_stone_chomp_EVS_UpdateTargetPartPos;
extern s32 b_area_isk_part_1_stone_chomp_StatusTable[];
extern s32 b_area_isk_part_1_swooper_DefenseTable[];
extern EvtScript b_area_isk_part_1_swooper_EVS_Idle;
extern s32 b_area_isk_part_1_swooper_StatusTable[];
extern Vec3i b_area_isk_part_1_vector3D_80224070;
extern Vec3i b_area_isk_part_1_vector3D_8022407C;
extern Vec3i b_area_isk_part_1_vector3D_80224088;
extern Vec3i b_area_isk_part_1_vector3D_802240A0;
extern Vec3i b_area_isk_part_1_vector3D_802240AC;
extern Vec3i b_area_isk_part_1_vector3D_802240B8;
extern Vec3i b_area_isk_part_1_vector3D_802241E8;
extern Vec3i b_area_isk_part_1_vector3D_802241F4;
extern Vec3i b_area_isk_part_1_vector3D_8022460C;
extern Vec3i b_area_isk_part_1_vector3D_80224618;
extern Vec3i b_area_isk_part_1_vector3D_80224624;
extern Vec3i b_area_isk_part_1_vector3D_80224630;
extern EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_HandleEvent_Ground;
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_HandleEvent;
extern EvtScript TTYD64_isk_part_1_stone_chomp_EVS_HandleEvent;
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_TakeTurn;
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_Attack_SinglePartLeap;
extern EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_TakeTurn_Ceiling;
extern EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_TakeTurn_Ground;
extern EvtScript TTYD64_isk_part_1_EVS_8021D150;
extern EvtScript TTYD64_isk_part_1_stone_chomp_EVS_TakeTurn;
extern EvtScript TTYD64_isk_part_1_swooper_EVS_HandleEvent;
extern EvtScript TTYD64_isk_part_1_EVS_8021ECAC;
extern EvtScript TTYD64_isk_part_1_swooper_EVS_Flying_TakeTurn;
extern EvtScript TTYD64_isk_part_1_swooper_EVS_TakeTurn;
extern EvtScript TTYD64_isk_part_1_stone_chomp_EVS_Idle;
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_DecrementSize;
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_Hit;
extern EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_HandleEvent_Ceiling;
extern EvtScript TTYD64_isk_part_1_swooper_EVS_Flying_HandleEvent;
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_KnockPartAway;
extern EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_FallFromCeiling;
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_ScareAway;
extern EvtScript TTYD64_isk_part_1_swooper_EVS_FallFromCeiling;
extern EvtScript TTYD64_isk_part_1_EVS_802230D4;
extern EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_Init;
extern EvtScript TTYD64_isk_part_1_swooper_EVS_ReturnHome;
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_Init;
extern EvtScript TTYD64_isk_part_1_EVS_80223E64;
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_SpinSmashHit;
extern EvtScript TTYD64_isk_part_1_stone_chomp_EVS_Init;
extern EvtScript TTYD64_isk_part_1_swooper_EVS_Init;
extern ActorBlueprint TTYD64_isk_part_1_pokey_mummy;
extern ActorBlueprint TTYD64_isk_part_1_stone_chomp;
extern ActorBlueprint TTYD64_isk_part_1_swooper;
extern ActorBlueprint TTYD64_isk_part_1_pokey_mummy_80225FE0;
extern ActorBlueprint TTYD64_isk_part_1_buzzy_beetle;
extern Vec3i TTYD64_isk_part_1_Pos_802265EC;
extern Battle TTYD64_isk_part_1_Formations[];
extern ActorPartBlueprint TTYD64_isk_part_1_stone_chomp_ActorParts[];
extern ActorPartBlueprint TTYD64_isk_part_1_pokey_mummy_ActorParts[];
extern s32 TTYD64_isk_part_1_buzzy_beetle_StatusTable[];
extern s32 TTYD64_isk_part_1_pokey_mummy_StatusTable[];
extern FormationRow TTYD64_isk_part_1_Formation_0A[];
extern FormationRow TTYD64_isk_part_1_Formation_12[];
extern FormationRow TTYD64_isk_part_1_Formation_04[];
extern FormationRow TTYD64_isk_part_1_Formation_0B[];
extern FormationRow TTYD64_isk_part_1_Formation_11[];
extern FormationRow TTYD64_isk_part_1_Formation_10[];
extern FormationRow TTYD64_isk_part_1_Formation_13[];
extern FormationRow TTYD64_isk_part_1_Formation_01[];
extern FormationRow TTYD64_isk_part_1_Formation_03[];
extern FormationRow TTYD64_isk_part_1_Formation_08[];
extern FormationRow TTYD64_isk_part_1_Formation_06[];
extern s32 TTYD64_isk_part_1_buzzy_beetle_GroundAnims[];
extern s32 TTYD64_isk_part_1_swooper_FlyingAnims[];
extern s32 TTYD64_isk_part_1_swooper_CeilingAnims[];
extern s32 TTYD64_isk_part_1_buzzy_beetle_CeilingAnims[];
extern s32 TTYD64_isk_part_1_buzzy_beetle_ToppledAnims[];
extern s32 TTYD64_isk_part_1_pokey_mummy_ThreePartAnims[];
extern s32 TTYD64_isk_part_1_stone_chomp_BasicAnims[];
extern s32 TTYD64_isk_part_1_pokey_mummy_OnePartAnims[];
extern s32 TTYD64_isk_part_1_pokey_mummy_FourPartAnims[];
extern s32 TTYD64_isk_part_1_pokey_mummy_TwoPartAnims[];
extern s32 TTYD64_isk_part_1_stone_chomp_QuickBiteAnims[];
extern s32 TTYD64_isk_part_1_stone_chomp_BiteAnims[];
extern s32 TTYD64_isk_part_1_stone_chomp_SlowBiteAnims[];
extern FormationRow TTYD64_isk_part_1_Formation_0D[];
extern FormationRow TTYD64_isk_part_1_Formation_0E[];
extern FormationRow TTYD64_isk_part_1_Formation_0C[];
extern FormationRow TTYD64_isk_part_1_Formation_0F[];
extern FormationRow TTYD64_isk_part_1_Formation_00[];
extern FormationRow TTYD64_isk_part_1_Formation_05[];
extern FormationRow TTYD64_isk_part_1_Formation_02[];
extern FormationRow TTYD64_isk_part_1_Formation_09[];
extern FormationRow TTYD64_isk_part_1_Formation_07[];
extern ActorPartBlueprint TTYD64_isk_part_1_swooper_ActorParts[];
extern ActorPartBlueprint TTYD64_isk_part_1_buzzy_beetle_ActorParts[];
extern FormationRow TTYD64_isk_part_1_Formation_802261A0[];

// clang-format off
EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_HandleEvent_Ground = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330007)
            SetConst(LVar2, 0x330019)
            ExecWait(b_area_isk_part_1_buzzy_beetle_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfNe(LVar0, 2)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x33000B)
                SetConst(LVar2, 0x33000B)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x33001D)
                SetConst(LVar2, 0x33001D)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            EndIf
        CaseEq(36)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfNe(LVar0, 2)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x33000B)
                SetConst(LVar2, 0x33000B)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x33000B)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x33001D)
                SetConst(LVar2, 0x33001D)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x33001D)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330007)
            SetConst(LVar2, 0x330019)
            ExecWait(b_area_isk_part_1_buzzy_beetle_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 8, 2)
            Call(SetTargetOffset, ACTOR_SELF, 1, 0, 16)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
            Call(SetActorVar, ACTOR_SELF, 9, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_isk_part_1_buzzy_beetle_ToppledDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_isk_part_1_buzzy_beetle_ToppledAnims))
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x330007)
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
            UseBuf(Ref(b_area_isk_part_1_buzzy_beetle_FlipPosOffsets))
            Loop(19)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x330019)
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330007)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330007)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330007)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330007)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x33000C)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(SetAnimation, ACTOR_SELF, 1, 0x330017)
                Wait(8)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x330002)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(25)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x33000C)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(SetAnimation, ACTOR_SELF, 1, 0x33000D)
                Wait(8)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x330002)
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
            SetConst(LVar1, 0x330007)
            SetConst(LVar2, 0x330019)
            ExecWait(b_area_isk_part_1_buzzy_beetle_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330007)
            SetConst(LVar2, 0x330019)
            ExecWait(b_area_isk_part_1_buzzy_beetle_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330007)
            SetConst(LVar2, 0x330019)
            ExecWait(b_area_isk_part_1_buzzy_beetle_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330007)
            SetConst(LVar2, 0x330019)
            ExecWait(b_area_isk_part_1_buzzy_beetle_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x330001)
                ExecWait(Ref(EVS_Enemy_Recover))
            EndIf
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x330004)
                SetConst(LVar2, 0x330007)
                ExecWait(Ref(EVS_Enemy_ScareAway))
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x330002)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x330004)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x330002)
            EndIf
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x330007)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x330008)
            EndIf
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x33000C)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(SetAnimation, ACTOR_SELF, 1, 0x33000D)
                Wait(8)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x330002)
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
EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x80000)
                SetConst(LVar0, 1)
                Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 3)
                    SetConst(LVar0, 1)
                    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                    ExecWait(Ref(EVS_Enemy_Hit))
                Else
                    Call(GetDamageSource, LVar0)
                    Switch(LVar0)
                        CaseOrEq(6)
                        CaseOrEq(7)
                        CaseOrEq(9)
                            ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_Hit)
                        EndCaseGroup
                        CaseDefault
                            SetConst(LVar0, 1)
                            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                            ExecWait(Ref(EVS_Enemy_Hit))
                    EndSwitch
                EndIf
            EndIf
        CaseEq(32)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x80000)
                SetConst(LVar0, 1)
                Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
            Else
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 3)
                    SetConst(LVar0, 1)
                    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Wait(10)
                Else
                    Call(GetDamageSource, LVar0)
                    Switch(LVar0)
                        CaseOrEq(6)
                        CaseOrEq(7)
                        CaseOrEq(9)
                            ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_Hit)
                        EndCaseGroup
                        CaseDefault
                            SetConst(LVar0, 1)
                            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                            ExecWait(Ref(EVS_Enemy_Hit))
                            Wait(10)
                    EndSwitch
                EndIf
            EndIf
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(14)
            Call(GetActorVar, ACTOR_SELF, 6, LVar1)
            Call(GetActorVar, ACTOR_SELF, 7, LVar2)
            SetConst(LVar0, 1)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 3)
                    ExecWait(Ref(EVS_Enemy_BurnHit))
                Else
                    Call(GetDamageSource, LVarA)
                    Switch(LVarA)
                        CaseOrEq(6)
                        CaseOrEq(7)
                        CaseOrEq(9)
                            ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_Hit)
                        EndCaseGroup
                        CaseDefault
                            ExecWait(Ref(EVS_Enemy_BurnHit))
                    EndSwitch
                EndIf
            EndIf
        CaseOrEq(36)
            Call(GetActorVar, ACTOR_SELF, 6, LVar1)
            Call(GetActorVar, ACTOR_SELF, 7, LVar2)
            SetConst(LVar0, 1)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 3)
                    ExecWait(Ref(EVS_Enemy_BurnHit))
                Else
                    Call(GetDamageSource, LVarA)
                    Switch(LVarA)
                        CaseOrEq(6)
                        CaseOrEq(7)
                        CaseOrEq(9)
                            ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_Hit)
                        EndCaseGroup
                        CaseDefault
                            ExecWait(Ref(EVS_Enemy_BurnHit))
                    EndSwitch
                EndIf
            EndIf
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 7, LVar1)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_SpinSmashHit)
        CaseEq(33)
            ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_SpinSmashHit)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(17)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                SetConst(LVar0, 1)
                Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_Hit)
            EndIf
        CaseEq(37)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                SetConst(LVar0, 1)
                Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_Hit)
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, -1)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Call(GetActorVar, ACTOR_SELF, 2, LVar1)
            Call(SetAnimation, ACTOR_SELF, 1, LVar1)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            ExecWait(Ref(EVS_Enemy_HopToPos))
        CaseEq(38)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 1, LVar1)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(27)
            Call(GetBattleFlags, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Call(AfflictActor, 0, 9, 3)
            Else
                Call(AfflictActor, 256, 9, 3)
            EndIf
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Set(LVar0, 0)
                    Set(LVar1, 77)
                    SetConst(LVar2, 0x310121)
                CaseEq(1)
                    Set(LVar0, 0)
                    Set(LVar1, 59)
                    SetConst(LVar2, 0x310122)
                CaseEq(2)
                    Set(LVar0, 0)
                    Set(LVar1, 41)
                    SetConst(LVar2, 0x310123)
                CaseEq(3)
                    Set(LVar0, 0)
                    Set(LVar1, 23)
                    SetConst(LVar2, 0x310124)
            EndSwitch
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfNotFlag(LVar3, 4096)
                Call(SetAnimation, ACTOR_SELF, 1, LVar2)
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Call(GetStatusFlags, ACTOR_SELF, LVar6)
            IfFlag(LVar6, 0x80000)
                MulF(LVar0, Float(0.400390625))
                MulF(LVar1, Float(0.400390625))
            EndIf
            AddF(LVar3, LVar0)
            AddF(LVar4, LVar1)
            Call(PlayEffect_impl, 26, 0, LVar3, LVar4, LVar5, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(30)
        CaseEq(49)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 1, LVar1)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_ScareAway)
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
EvtScript TTYD64_isk_part_1_stone_chomp_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350006)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            Call(SetAnimation, ACTOR_SELF, 3, 0x350009)
            Call(SetAnimation, ACTOR_SELF, 4, 0x350009)
            Call(SetAnimation, ACTOR_SELF, 5, 0x350009)
            Call(SetAnimation, ACTOR_SELF, 6, 0x350009)
            Call(SetAnimation, ACTOR_SELF, 7, 0x350009)
            Call(SetAnimation, ACTOR_SELF, 8, 0x350009)
            Call(SetAnimation, ACTOR_SELF, 9, 0x350009)
            Call(SetAnimation, ACTOR_SELF, 10, 0x350009)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350007)
            SetConst(LVar2, 0x350008)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            Call(SetAnimation, ACTOR_SELF, 3, 0x350009)
            Call(SetAnimation, ACTOR_SELF, 4, 0x350009)
            Call(SetAnimation, ACTOR_SELF, 5, 0x350009)
            Call(SetAnimation, ACTOR_SELF, 6, 0x350009)
            Call(SetAnimation, ACTOR_SELF, 7, 0x350009)
            Call(SetAnimation, ACTOR_SELF, 8, 0x350009)
            Call(SetAnimation, ACTOR_SELF, 9, 0x350009)
            Call(SetAnimation, ACTOR_SELF, 10, 0x350009)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350007)
            SetConst(LVar2, 0x350008)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350008)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350006)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350006)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350006)
            Call(UseBattleCamPreset, 2)
            Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
            Call(AddGoalPos, ACTOR_SELF, 30, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 1017)
            Call(AddGoalPos, ACTOR_SELF, 15, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 1017)
            Call(AddGoalPos, ACTOR_SELF, 5, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 1017)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 1017)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350005)
            ExecWait(b_area_isk_part_1_stone_chomp_EVS_Chomp_HopHome)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 1017)
            Thread
                Call(ShakeCam, 1, 0, 1, Float(0.5))
            EndThread
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
            Call(SetActorVar, ACTOR_SELF, 8, 0)
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350006)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Call(SetActorVar, ACTOR_SELF, 8, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350006)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350006)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350001)
            SetConst(LVar2, 0x350006)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Call(SetGoalToHome, ACTOR_SELF)
                Call(GetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
                IfFlag(LVar0, 0x80000)
                    Sub(LVar1, 10)
                    Add(LVar2, 4)
                Else
                    Sub(LVar1, 5)
                    Add(LVar2, 11)
                EndIf
                Call(SetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350006)
            ExecWait(Ref(EVS_Enemy_AirLift))
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350006)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x350001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
        CaseEq(61)
            Wait(1000)
        CaseDefault
    EndSwitch
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x151000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        IfNe(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
            Call(FallToGoal, ACTOR_SELF, 11)
        EndIf
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_TakeTurn = {
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfEq(LVarA, 3)
        ExecWait(TTYD64_isk_part_1_EVS_8021D150)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 9, LVar0)
    IfEq(LVar0, 0)
        Call(GetActorVar, ACTOR_SELF, 10, LVar0)
        IfEq(LVar0, 2)
            Goto(123)
        EndIf
        ExecWait(TTYD64_isk_part_1_EVS_802230D4)
        IfEq(LVarE, -1)
            Goto(123)
        EndIf
        ExecWait(TTYD64_isk_part_1_EVS_80223E64)
        Switch(LVar9)
            CaseEq(1)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 400)
                    ExecWait(TTYD64_isk_part_1_EVS_8021ECAC)
                    Return
                EndIf
            CaseEq(2)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 200)
                    ExecWait(TTYD64_isk_part_1_EVS_8021ECAC)
                    Return
                EndIf
            CaseEq(3)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 100)
                    ExecWait(TTYD64_isk_part_1_EVS_8021ECAC)
                    Return
                EndIf
        EndSwitch
    EndIf
    Label(123)
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 500)
        ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_Attack_SinglePartLeap)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    EndIf
    Call(SetPartSounds, ACTOR_SELF, 6, 2, 0, 0)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 6, Float(1.0), Float(1.0), Float(1.0))
    Else
        Call(SetPartScale, ACTOR_SELF, 6, Float(0.400390625), Float(0.400390625), Float(1.0))
    EndIf
    ChildThread
        Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
        Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(2.2001953125))
        Call(SetAnimation, ACTOR_SELF, 6, 0x310116)
        Call(GetStatusFlags, ACTOR_SELF, LVar5)
        Call(GetActorVar, ACTOR_SELF, 0, LVarA)
        Switch(LVarA)
            CaseEq(0)
                IfNotFlag(LVar5, 0x80000)
                    Add(LVar1, 38)
                Else
                    Add(LVar1, 15)
                    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(1.2001953125))
                EndIf
                Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 15, 1)
            CaseEq(1)
                IfNotFlag(LVar5, 0x80000)
                    Add(LVar1, 20)
                Else
                    Add(LVar1, 8)
                    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(1.2001953125))
                EndIf
                Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 15, 1)
            CaseEq(2)
                IfNotFlag(LVar5, 0x80000)
                    Add(LVar1, 8)
                Else
                    Add(LVar1, 3)
                    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(1.2001953125))
                EndIf
                Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 15, 1)
            CaseEq(3)
        EndSwitch
    EndChildThread
    Call(PlaySoundAtActor, ACTOR_SELF, 834)
    Call(GetActorVar, ACTOR_SELF, 4, LVar1)
    Call(SetAnimation, ACTOR_SELF, 1, LVar1)
    Wait(12)
    Call(GetActorVar, ACTOR_SELF, 5, LVar1)
    Call(SetAnimation, ACTOR_SELF, 1, LVar1)
    Wait(1)
    Call(PlaySoundAtActor, ACTOR_SELF, 718)
    Wait(3)
    ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_DecrementSize)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVar0, 5)
                ChildThread
                    Wait(5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndChildThread
            EndIf
            Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 80)
            Sub(LVar1, 5)
            Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(20.0))
            Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
            Call(SetAnimation, ACTOR_SELF, 6, 0x310116)
            Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
            Call(GetActorVar, ACTOR_SELF, 2, LVar1)
            Call(SetAnimation, ACTOR_SELF, 1, LVar1)
            Return
        EndCaseGroup
    EndSwitch
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(20.0))
    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
    Call(SetAnimation, ACTOR_SELF, 6, 0x310116)
    Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 1)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, -0x7FFDFCD8, 3, 32)
    Call(GetActorVar, ACTOR_SELF, 2, LVar1)
    Call(SetAnimation, ACTOR_SELF, 1, LVar1)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(GetOwnerTarget, LVar3, 0)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Sub(LVar0, 55)
            Set(LVar1, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(6.0))
            Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
            Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 25, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(4.0))
            Sub(LVar0, 24)
            Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 21, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(3.0))
            Sub(LVar0, 20)
            Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 20, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_Attack_SinglePartLeap = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Call(AddGoalPos, ACTOR_SELF, 60, 0, 0)
            Else
                Call(AddGoalPos, ACTOR_SELF, 24, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x310108)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310104)
        CaseEq(1)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Call(AddGoalPos, ACTOR_SELF, 40, 0, 0)
            Else
                Call(AddGoalPos, ACTOR_SELF, 16, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x310109)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310105)
        CaseEq(2)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Call(AddGoalPos, ACTOR_SELF, 20, 0, 0)
            Else
                Call(AddGoalPos, ACTOR_SELF, 8, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x31010A)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310106)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 834)
    Call(MakeLerp, 0, -40, 20, 10)
    Label(0)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    ChildThread
        Wait(3)
        Call(PlaySoundAtActor, ACTOR_SELF, 749)
    EndChildThread
    Call(MakeLerp, -40, 90, 5, 1)
    Label(3)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(3)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 32)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(MakeLerp, 90, 0, 5, 0)
            Label(4)
            Call(UpdateLerp)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(4)
            EndIf
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310108)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310104)
                CaseEq(1)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310109)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310105)
                CaseEq(2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x31010A)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310106)
            EndSwitch
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Set(LVar1, 2)
        CaseEq(1)
            Set(LVar1, 2)
        CaseDefault
            Set(LVar1, 2)
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, -0x7FFDFD00, LVar1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(MakeLerp, 90, 0, 10, 0)
            Label(5)
            Call(UpdateLerp)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(5)
            EndIf
            Call(YieldTurn)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310108)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310104)
                CaseEq(1)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310109)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310105)
                CaseEq(2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x31010A)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310106)
            EndSwitch
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_TakeTurn_Ceiling = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 16)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
    Call(b_area_isk_part_1_buzzy_beetle_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_isk_part_1_buzzy_beetle_EVS_TakeTurn_Ground))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_isk_part_1_buzzy_beetle_EVS_HandleEvent_Ground))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_isk_part_1_buzzy_beetle_GroundAnims))
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x33000E)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x330011)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar4, LVar2)
        Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x33000E)
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
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 3, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(SetPartYaw, ACTOR_SELF, 1, 180)
            Call(SetAnimation, ACTOR_SELF, 1, 0x330008)
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
                Call(SetAnimation, ACTOR_SELF, 1, 0x330000)
            EndThread
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(8)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x330004)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x330001)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(SetAnimation, ACTOR_SELF, 1, 0x330008)
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
                Call(SetAnimation, ACTOR_SELF, 1, 0x330000)
            EndThread
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(8)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x330001)
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
EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_TakeTurn_Ground = {
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
            SetConst(LVar1, 0x330002)
            SetConst(LVar2, 0x330001)
            ExecWait(Ref(EVS_Enemy_FlipBackUp))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetActorVar, ACTOR_SELF, 8, 1)
            Call(SetTargetOffset, ACTOR_SELF, 1, 0, 16)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_isk_part_1_buzzy_beetle_UprightDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_isk_part_1_buzzy_beetle_GroundAnims))
            Call(BindIdle, ACTOR_SELF, Ref(b_area_isk_part_1_buzzy_beetle_EVS_Idle))
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x33000C)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x330006)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(10)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(5)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 8225)
    Call(SetAnimation, ACTOR_SELF, 1, 0x330005)
    Wait(20)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 2, 16)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x33000D)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x330001)
            Wait(8)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x330001)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_EVS_8021D150 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorSounds, ACTOR_SELF, 0, 748, 748)
    Call(SetActorSounds, ACTOR_SELF, 2, 748, 0)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0x31010B)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetAnimation, ACTOR_SELF, 1, 0x310107)
    Wait(4)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(4)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x31010B)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 2, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 5)
            Set(LVar1, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.099609375))
            ChildThread
                Wait(2)
                Set(LVar0, 0)
                Loop(5)
                    Add(LVar0, 30)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndChildThread
            Call(JumpToGoal, ACTOR_SELF, 22, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
            ChildThread
                Wait(2)
                Set(LVar0, 180)
                Loop(6)
                    Add(LVar0, 30)
                    IfEq(LVar0, 360)
                        Set(LVar0, 0)
                    EndIf
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            EndChildThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x31010B)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            ExecWait(Ref(EVS_Enemy_HopToPos))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310107)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.099609375))
    ChildThread
        Wait(2)
        Set(LVar0, 0)
        Loop(5)
            Add(LVar0, 30)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndChildThread
    Call(JumpToGoal, ACTOR_SELF, 18, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, -0x7FFDFC9C, 4, 32)
    Call(SetAnimation, ACTOR_SELF, 1, 0x310107)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
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
            Sub(LVar0, 10)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310107)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x31010B)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            ExecWait(Ref(EVS_Enemy_HopToPos))
            Call(SetAnimation, ACTOR_SELF, 1, 0x310107)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_stone_chomp_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Add(LVar0, 45)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 1017)
    Call(SetAnimation, ACTOR_SELF, 1, 0x350005)
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_SELF, 271)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x350001)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 1017)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 25)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 1017)
            Sub(LVar0, 15)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 1017)
            Call(SetAnimation, ACTOR_SELF, 1, 0x350004)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x350004)
            ExecWait(b_area_isk_part_1_stone_chomp_EVS_Chomp_HopToPos)
            Call(SetAnimation, ACTOR_SELF, 1, 0x350001)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(HPBarToHome, ACTOR_SELF)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorVar, ACTOR_SELF, 8, 0)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x350001)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 4)
    Else
        Add(LVar0, 10)
    EndIf
    Set(LVar1, 27)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2001953125))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x350004)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 1017)
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 1017)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 1017)
            Sub(LVar0, 10)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 1017)
            Call(SetAnimation, ACTOR_SELF, 1, 0x350001)
            Wait(8)
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x350004)
            ExecWait(b_area_isk_part_1_stone_chomp_EVS_Chomp_HopToPos)
            Call(SetAnimation, ACTOR_SELF, 1, 0x350001)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
            Call(SetActorYaw, ACTOR_SELF, 0)
        EndCaseGroup
    EndSwitch
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(HPBarToHome, ACTOR_SELF)
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_swooper_EVS_HandleEvent = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_isk_part_1_swooper_EVS_Flying_HandleEvent)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340015)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34000E)
                ExecWait(Ref(EVS_Enemy_Hit))
            EndIf
        CaseEq(10)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340015)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34000E)
                ExecWait(Ref(EVS_Enemy_Hit))
                ExecWait(TTYD64_isk_part_1_swooper_EVS_FallFromCeiling)
            EndIf
        CaseEq(14)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340017)
                SetConst(LVar2, 0x340018)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340011)
                SetConst(LVar2, 0x340012)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                ExecWait(TTYD64_isk_part_1_swooper_EVS_FallFromCeiling)
            EndIf
        CaseEq(36)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340017)
                SetConst(LVar2, 0x340018)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340018)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340011)
                SetConst(LVar2, 0x340012)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340012)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(47)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340015)
            ExecWait(Ref(EVS_Enemy_ShockHit_Impl))
            Call(UseBattleCamPreset, 2)
            ExecWait(TTYD64_isk_part_1_swooper_EVS_ReturnHome)
        CaseEq(38)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340015)
            ExecWait(Ref(EVS_Enemy_ShockHit_Impl))
            Thread
                Wait(30)
                Call(UseBattleCamPreset, 2)
            EndThread
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340015)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x34000C)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340015)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340015)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34000E)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34000E)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(56)
            Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_isk_part_1_swooper_FlyingAnims))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340002)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(TTYD64_isk_part_1_swooper_EVS_ReturnHome)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 1)
            Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, -24, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340002)
            SetConst(LVar2, 0x340015)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_EVS_8021ECAC = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x310104)
    Call(MakeLerp, 0, -20, 20, 10)
    Label(0)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    ChildThread
        Wait(8)
        Call(PlaySoundAtActor, ACTOR_SELF, 836)
    EndChildThread
    Call(MakeLerp, -20, 30, 20, 10)
    Label(1)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(1)
    EndIf
    ChildThread
        Wait(6)
        Call(PlaySoundAtActor, ACTOR_SELF, 837)
    EndChildThread
    Call(MakeLerp, 30, -40, 20, 10)
    Label(2)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(2)
    EndIf
    ChildThread
        Wait(4)
        Call(PlaySoundAtActor, ACTOR_SELF, 750)
    EndChildThread
    Call(MakeLerp, -40, 90, 10, 10)
    Label(3)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(3)
    EndIf
    Wait(20)
    Call(PlaySoundAtActor, ACTOR_SELF, 838)
    Call(StartRumble, 9)
    Thread
        Call(ShakeCam, 1, 0, 10, Float(1.0))
    EndThread
    Call(SummonEnemy, Ref(TTYD64_isk_part_1_Formation_802261A0), 0)
    Set(LVarB, LVar0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Sub(LVar1, 80)
    Call(SetActorPos, LVarB, LVar0, LVar1, LVar2)
    ChildThread
        Call(PlayEffect_impl, 37, 2, LVar0, 0, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(UseIdleAnimation, LVarB, 0)
        Call(SetAnimation, LVarB, 1, 0x31010C)
        Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
        Call(SetActorJumpGravity, LVarB, Float(1.2001953125))
        Call(SetGoalPos, LVarB, LVar0, 0, LVar2)
        Call(JumpToGoal, LVarB, 20, 0, 1, 0)
        Wait(20)
        Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
        Call(SetAnimation, LVarB, 1, 0x310104)
        Call(SetHomePos, LVarB, LVar0, LVar1, LVar2)
        Call(HPBarToHome, LVarB)
        Call(UseIdleAnimation, LVarB, 1)
    EndChildThread
    Call(GetActorVar, ACTOR_SELF, 10, LVar1)
    Switch(LVar1)
        CaseEq(0)
            Call(SetActorVar, LVarB, 10, 1)
        CaseEq(1)
            Call(SetActorVar, LVarB, 10, 2)
    EndSwitch
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Set(LVarA, LVar0)
    Call(MakeLerp, 90, -30, 7, 4)
    Label(4)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(4)
    EndIf
    Wait(20)
    Call(MakeLerp, -30, 0, 10, 10)
    Label(5)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(5)
    EndIf
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x310104)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_swooper_EVS_Flying_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x340002)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
        Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Else
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x340002)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
        Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
        Call(FlyToGoal, ACTOR_SELF, 0, -4, 0)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 2, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340006)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340006)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(10.0))
            Wait(15)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(TTYD64_isk_part_1_swooper_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseEq(7)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 8192)
                Set(LFlag0, 0)
            Else
                Set(LFlag0, 1)
            EndIf
    EndSwitch
    Wait(10)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340006)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340006)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Call(UseBattleCamPreset, 2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340002)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    Wait(10)
    Call(YieldTurn)
    ExecWait(TTYD64_isk_part_1_swooper_EVS_ReturnHome)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_swooper_EVS_TakeTurn = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_isk_part_1_swooper_EVS_Flying_TakeTurn)
        Return
    EndIf
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x340002)
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 24)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 2, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340006)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(AddGoalPos, ACTOR_SELF, -50, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340006)
            Call(FlyToGoal, ACTOR_SELF, 0, -40, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(10.0))
            Wait(15)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(TTYD64_isk_part_1_swooper_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseEq(7)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 8192)
                Set(LFlag0, 0)
            Else
                Set(LFlag0, 1)
            EndIf
    EndSwitch
    Wait(10)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340006)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340006)
    Call(FlyToGoal, ACTOR_SELF, 0, -40, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Call(UseBattleCamPreset, 2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340002)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    Wait(10)
    Call(YieldTurn)
    ExecWait(TTYD64_isk_part_1_swooper_EVS_ReturnHome)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_stone_chomp_EVS_Idle = {
    Label(0)
    Loop(0)
        ExecWait(b_area_isk_part_1_stone_chomp_EVS_UpdateTargetPartPos)
        Call(GetStatusFlags, ACTOR_SELF, LVar0)
        IfNotFlag(LVar0, 0x35D000)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_isk_part_1_stone_chomp_SlowBiteAnims))
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetIdleGoalToHome, ACTOR_SELF)
    Call(GetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleJumpToGoal, ACTOR_SELF, 11, 1)
    Loop(0)
        ExecWait(b_area_isk_part_1_stone_chomp_EVS_UpdateTargetPartPos)
        Call(GetStatusFlags, ACTOR_SELF, LVar0)
        IfNotFlag(LVar0, 0x35D000)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetIdleGoalToHome, ACTOR_SELF)
    Call(GetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleJumpToGoal, ACTOR_SELF, 6, 1)
    Call(RandInt, 10, LVar0)
    Add(LVar0, 1)
    Wait(LVar0)
    Loop(0)
        ExecWait(b_area_isk_part_1_stone_chomp_EVS_UpdateTargetPartPos)
        Call(GetStatusFlags, ACTOR_SELF, LVar0)
        IfNotFlag(LVar0, 0x35D000)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_isk_part_1_stone_chomp_BiteAnims))
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetIdleGoalToHome, ACTOR_SELF)
    Call(GetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleJumpToGoal, ACTOR_SELF, 15, 1)
    Loop(0)
        ExecWait(b_area_isk_part_1_stone_chomp_EVS_UpdateTargetPartPos)
        Call(GetStatusFlags, ACTOR_SELF, LVar0)
        IfNotFlag(LVar0, 0x35D000)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_isk_part_1_stone_chomp_SlowBiteAnims))
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetIdleGoalToHome, ACTOR_SELF)
    Call(GetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 20)
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleJumpToGoal, ACTOR_SELF, 12, 1)
    Loop(0)
        ExecWait(b_area_isk_part_1_stone_chomp_EVS_UpdateTargetPartPos)
        Call(GetStatusFlags, ACTOR_SELF, LVar0)
        IfNotFlag(LVar0, 0x35D000)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetIdleGoalToHome, ACTOR_SELF)
    Call(GetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 10)
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleJumpToGoal, ACTOR_SELF, 9, 1)
    Loop(0)
        ExecWait(b_area_isk_part_1_stone_chomp_EVS_UpdateTargetPartPos)
        Call(GetStatusFlags, ACTOR_SELF, LVar0)
        IfNotFlag(LVar0, 0x35D000)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_isk_part_1_stone_chomp_QuickBiteAnims))
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetIdleGoalToHome, ACTOR_SELF)
    Call(GetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleJumpToGoal, ACTOR_SELF, 6, 1)
    Call(RandInt, 10, LVar0)
    Add(LVar0, 10)
    Wait(LVar0)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_DecrementSize = {
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    Switch(LVarA)
        CaseEq(0)
            Call(SetActorVar, ACTOR_SELF, 1, 0x310105)
            Call(SetActorVar, ACTOR_SELF, 2, 0x310109)
            Call(SetActorVar, ACTOR_SELF, 3, 0x31010D)
            Call(SetActorVar, ACTOR_SELF, 4, 0x310112)
            Call(SetActorVar, ACTOR_SELF, 5, 0x310113)
            Call(SetActorVar, ACTOR_SELF, 6, 0x31011A)
            Call(SetActorVar, ACTOR_SELF, 7, 0x31011B)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_isk_part_1_pokey_mummy_ThreePartAnims))
            Call(SetPartFlagBits, ACTOR_SELF, 2, 0x800000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20000, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x20000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x800000, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(SetActorSize, ACTOR_SELF, 62, -0xEE6B280)
            Call(SetPartSize, ACTOR_SELF, 1, 62, -0xEE6B280)
            Call(b_area_isk_part_1_pokey_mummy_SetAbsoluteStatusOffsets, -15, 55, 10, 45)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 1, 0x310106)
            Call(SetActorVar, ACTOR_SELF, 2, 0x31010A)
            Call(SetActorVar, ACTOR_SELF, 3, 0x31010E)
            Call(SetActorVar, ACTOR_SELF, 4, 0x310114)
            Call(SetActorVar, ACTOR_SELF, 5, 0x310115)
            Call(SetActorVar, ACTOR_SELF, 6, 0x31011C)
            Call(SetActorVar, ACTOR_SELF, 7, 0x31011D)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_isk_part_1_pokey_mummy_TwoPartAnims))
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x800000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x20000, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x20000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x800000, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 2)
            Call(SetActorSize, ACTOR_SELF, 44, -0xEE6B280)
            Call(SetPartSize, ACTOR_SELF, 1, 44, -0xEE6B280)
            Call(b_area_isk_part_1_pokey_mummy_SetAbsoluteStatusOffsets, -15, 35, 10, 25)
        CaseEq(2)
            Call(SetActorVar, ACTOR_SELF, 1, 0x310107)
            Call(SetActorVar, ACTOR_SELF, 2, 0x31010B)
            Call(SetActorVar, ACTOR_SELF, 3, 0x31010F)
            Call(SetActorVar, ACTOR_SELF, 6, 0x31011E)
            Call(SetActorVar, ACTOR_SELF, 7, 0x31011F)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_isk_part_1_pokey_mummy_OnePartAnims))
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x800000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x20000, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 5, 0x20000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 5, 0x800000, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 3)
            Call(SetActorSize, ACTOR_SELF, 26, -0xEE6B280)
            Call(SetPartSize, ACTOR_SELF, 1, 26, -0xEE6B280)
            Call(b_area_isk_part_1_pokey_mummy_SetAbsoluteStatusOffsets, -15, 15, 10, 5)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_Hit = {
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 6, Float(1.0), Float(1.0), Float(1.0))
    Else
        Call(SetPartScale, ACTOR_SELF, 6, Float(0.400390625), Float(0.400390625), Float(1.0))
    EndIf
    ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_DecrementSize)
    SetConst(LVar0, 1)
    Call(GetLastEvent, ACTOR_SELF, LVar1)
    Switch(LVar1)
        CaseOrEq(14)
        CaseOrEq(36)
            Call(SetAnimation, ACTOR_SELF, 6, 0x310120)
            Call(GetActorVar, ACTOR_SELF, 6, LVar1)
        EndCaseGroup
        CaseDefault
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    ChildThread
        Wait(4)
        ExecWait(b_area_isk_part_1_pokey_mummy_EVS_HitReactionBounce)
    EndChildThread
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfNe(LVarA, 3)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
        Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
        Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(6.0))
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 30)
        Set(LVar1, 0)
        Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 10, 18, 0)
        Add(LVar0, 20)
        Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 8, 10, 0)
        Loop(20)
            Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
            Wait(1)
            Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
            Wait(1)
        EndLoop
        Call(SetPartFlagBits, ACTOR_SELF, 6, 0x20000, 1)
        Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
    Else
        Wait(30)
    EndIf
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(14)
            Call(GetActorVar, ACTOR_SELF, 7, LVar1)
            Call(SetAnimation, ACTOR_SELF, 1, LVar1)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetActorSize, ACTOR_SELF, LVar3, LVar4)
            Div(LVar3, 2)
            Add(LVar1, LVar3)
            Add(LVar2, 5)
            DivF(LVar3, Float(10.0))
            Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
        CaseEq(36)
            Call(GetActorVar, ACTOR_SELF, 7, LVar1)
            Call(SetAnimation, ACTOR_SELF, 1, LVar1)
            Wait(10)
        CaseDefault
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_HandleEvent_Ceiling = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330013)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330013)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_isk_part_1_buzzy_beetle_EVS_FallFromCeiling)
        CaseEq(13)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330013)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_isk_part_1_buzzy_beetle_EVS_FallFromCeiling)
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330018)
            SetConst(LVar2, 0x330018)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_isk_part_1_buzzy_beetle_EVS_FallFromCeiling)
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330018)
            SetConst(LVar2, 0x330018)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330018)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330013)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330007)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330013)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330007)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330016)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330016)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Wait(2)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x200000)
                ExecWait(TTYD64_isk_part_1_buzzy_beetle_EVS_FallFromCeiling)
            EndIf
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330013)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330013)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 1)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330011)
            SetConst(LVar2, 0x330013)
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
EvtScript TTYD64_isk_part_1_swooper_EVS_Flying_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340015)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340017)
            SetConst(LVar2, 0x340018)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340017)
            SetConst(LVar2, 0x340018)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340018)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340015)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Call(UseBattleCamPreset, 2)
            ExecWait(TTYD64_isk_part_1_swooper_EVS_ReturnHome)
        CaseEq(38)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340015)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Thread
                Wait(30)
                Call(UseBattleCamPreset, 2)
            EndThread
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340015)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340002)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340015)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340015)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340002)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340002)
            SetConst(LVar2, 0x340015)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340002)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340015)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_KnockPartAway = {
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 6, Float(1.0), Float(1.0), Float(1.0))
    Else
        Call(SetPartScale, ACTOR_SELF, 6, Float(0.400390625), Float(0.400390625), Float(1.0))
    EndIf
    ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_DecrementSize)
    SetConst(LVar0, 1)
    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    ChildThread
        Wait(4)
        ExecWait(b_area_isk_part_1_pokey_mummy_EVS_HitReactionBounce)
    EndChildThread
    Call(CreateHomeTargetList, 0x18004)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerID, LVar1)
    Call(GetOwnerTarget, LVar0, LVar9)
    IfNe(LVar1, LVar0)
        Call(ChooseNextTarget, 0, LVar0)
        Goto(0)
    EndIf
    Label(1)
    Add(LVarF, 1)
    Call(ChooseNextTarget, 0, LVar0)
    IfEq(LVar0, -1)
        Goto(10)
    EndIf
    Call(GetOwnerTarget, LVar0, LVar9)
    Call(GetActorFlags, LVar0, LVar1)
    IfFlag(LVar1, 0x4000)
        Goto(1)
    EndIf
    Call(GetOwnerID, LVar0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
    Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(7.0))
    Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 1)
    ChildThread
        Call(ShakeCam, 1, 0, 2, Float(1.0))
    EndChildThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(DispatchDamageEvent, LVar0, 1, 17)
    Goto(1)
    Label(10)
    Call(UseBattleCamPreset, 3)
    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
    Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(6.0))
    Call(JumpPartTo, ACTOR_SELF, 6, 296, 0, 0, 0, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 6, 0x20000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_FallFromCeiling = {
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 2)
    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 16)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
    Call(b_area_isk_part_1_buzzy_beetle_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_isk_part_1_buzzy_beetle_EVS_TakeTurn_Ground))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_isk_part_1_buzzy_beetle_EVS_HandleEvent_Ground))
    Call(SetActorVar, ACTOR_SELF, 9, 1)
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_isk_part_1_buzzy_beetle_ToppledDefense))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_isk_part_1_buzzy_beetle_ToppledAnims))
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(SetPartEventBits, ACTOR_SELF, 1, 16, 0)
    Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
    Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x330008)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x330002)
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
EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_ScareAway = {
    SetConst(LVar0, 1)
    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
    Call(UseBattleCamPreset, 2)
    Call(GetActorFlags, ACTOR_SELF, LVar9)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.0498046875))
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Set(LVarD, LVarB)
    Add(LVarD, 40)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarD, LVarC)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    Wait(20)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(FallToGoal, ACTOR_SELF, 10)
    Wait(20)
    Call(SetActorYaw, ACTOR_SELF, 180)
    Wait(5)
    Call(SetActorVar, ACTOR_SELF, 0, LVar2)
    Switch(LVar2)
        CaseEq(0)
            Set(LVar2, 96)
            Set(LVar6, 4)
        CaseEq(1)
            Set(LVar2, 72)
            Set(LVar6, 3)
        CaseEq(2)
            Set(LVar2, 48)
            Set(LVar6, 2)
        CaseDefault
            Set(LVar2, 24)
            Set(LVar6, 1)
    EndSwitch
    ChildThread
        Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
        Loop(LVar6)
            Call(PlayEffect_impl, 37, 2, LVarA, 0, LVarC, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(10)
        EndLoop
    EndChildThread
    Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar4, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
    Wait(8)
    Call(HideHealthBar, ACTOR_SELF)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(RemoveActor, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_swooper_EVS_FallFromCeiling = {
    Call(HideHealthBar, ACTOR_SELF)
    Call(GetLastDamage, ACTOR_SELF, LVar0)
    IfLe(LVar0, 0)
        Return
    EndIf
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x340002)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 24)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfEq(LVarA, -1)
        Call(SetHomePos, ACTOR_SELF, LVar0, 45, LVar2)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalToHome, ACTOR_SELF)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 0, 0)
        Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
    Else
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalPos, ACTOR_SELF, LVar0, 45, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 0, 0)
        Call(GetIndexFromPos, ACTOR_SELF, LVarA)
        Mod(LVarA, 4)
        Add(LVarA, 4)
        Call(SetGoalToIndex, ACTOR_SELF, LVarA)
        Call(GetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
        Call(SetHomePos, ACTOR_SELF, LVarA, LVarB, LVarC)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalToHome, ACTOR_SELF)
        Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
    EndIf
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, -10)
    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 22)
    Call(b_area_isk_part_1_swooper_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_isk_part_1_swooper_FlyingAnims))
    Call(SetActorFlagBits, ACTOR_SELF, 512, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_EVS_802230D4 = {
    Set(LVarE, -1)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfNe(LVar0, 0)
        Return
    EndIf
    Set(LFlag1, 0)
    Set(LFlag2, 0)
    Set(LFlag3, 0)
    Set(LFlag4, 0)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar5)
    Call(GetIndexFromHome, LVar0, LVar5)
    Mod(LVar5, 4)
    Switch(LVar5)
        CaseEq(0)
            Set(LFlag1, 1)
        CaseEq(1)
            Set(LFlag2, 1)
        CaseEq(2)
            Set(LFlag3, 1)
        CaseEq(3)
            Set(LFlag4, 1)
    EndSwitch
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Call(GetIndexFromHome, ACTOR_SELF, LVar1)
    Switch(LVar1)
        CaseEq(0)
            Return
        CaseEq(1)
            IfEq(LFlag1, 0)
                Set(LVarE, 0)
            EndIf
        CaseEq(2)
            IfEq(LFlag2, 0)
                Set(LVarE, 1)
            EndIf
        CaseEq(3)
            IfEq(LFlag3, 0)
                Set(LVarE, 2)
            EndIf
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_Init = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_isk_part_1_buzzy_beetle_EVS_Idle))
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 8, 0)
        Call(b_area_isk_part_1_buzzy_beetle_SetAbsoluteStatusOffsets, -10, 0, 10, 0)
        Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_isk_part_1_buzzy_beetle_EVS_TakeTurn_Ceiling))
        Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_isk_part_1_buzzy_beetle_EVS_HandleEvent_Ceiling))
        Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 0)
    Else
        Call(SetActorVar, ACTOR_SELF, 8, 1)
        Call(SetTargetOffset, ACTOR_SELF, 1, 0, 16)
        Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
        Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_isk_part_1_buzzy_beetle_EVS_TakeTurn_Ground))
        Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_isk_part_1_buzzy_beetle_EVS_HandleEvent_Ground))
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_isk_part_1_buzzy_beetle_GroundAnims))
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
EvtScript TTYD64_isk_part_1_swooper_EVS_ReturnHome = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340002)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 0, -24, 0)
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 11)
            Call(SetActorFlagBits, ACTOR_SELF, 2048, 1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_isk_part_1_swooper_CeilingAnims))
            Call(SetAnimation, ACTOR_SELF, 1, 0x34000C)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 24)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340002)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 11)
    EndSwitch
    Return
    End
};
// clang-format on

Battle TTYD64_isk_part_1_Formations[] = {
    { .name = "\265\363\334\336\337\374x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_00,
      .stage = &b_area_isk_part_1_isk_02b,
      .onBattleStart = NULL },
    { .name = "\265\363\334\336\337\374x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_01,
      .stage = &b_area_isk_part_1_isk_02b,
      .onBattleStart = NULL },
    { .name = "\265\363\334\336\337\374,\320\265\320\265",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_02,
      .stage = &b_area_isk_part_1_isk_04,
      .onBattleStart = NULL },
    { .name = "\265\363\334\336\337\374x\022,\320\265\320\265",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_03,
      .stage = &b_area_isk_part_1_isk_04,
      .onBattleStart = NULL },
    { .name = "\265\363\334\336\337\374x\022,\320\265\320\265x\022",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_04,
      .stage = &b_area_isk_part_1_isk_04,
      .onBattleStart = NULL },
    { .name = "\320\265\320\265x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_05,
      .stage = &b_area_isk_part_1_isk_04,
      .onBattleStart = NULL },
    { .name = "\320\265\320\265x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_06,
      .stage = &b_area_isk_part_1_isk_04,
      .onBattleStart = NULL },
    { .name = "\271\310\374\363\357\363\357\363x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_07,
      .stage = &b_area_isk_part_1_isk_02b,
      .onBattleStart = NULL },
    { .name = "\271\310\374\363\357\363\357\363x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_08,
      .stage = &b_area_isk_part_1_isk_02b,
      .onBattleStart = NULL },
    { .name = "\341\303\310x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_09,
      .stage = &b_area_isk_part_1_isk_02b,
      .onBattleStart = NULL },
    { .name = "\341\303\310x\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_0A,
      .stage = &b_area_isk_part_1_isk_02b,
      .onBattleStart = NULL },
    { .name = "\341\303\310,\341\303\310\010f\223X\207F\011,\320\265\320\265",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_0B,
      .stage = &b_area_isk_part_1_isk_05,
      .onBattleStart = NULL },
    { .name = "\341\303\310,\320\265\320\265",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_0C,
      .stage = &b_area_isk_part_1_isk_05,
      .onBattleStart = NULL },
    { .name = "\341\303\310\010f\223X\207F\011,\341\303\310",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_0D,
      .stage = &b_area_isk_part_1_isk_05,
      .onBattleStart = NULL },
    { .name = "\341\303\310,\341\303\310(f\223X\207F)",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_0E,
      .stage = &b_area_isk_part_1_isk_05,
      .onBattleStart = NULL },
    { .name = "\341\303\310(f\223X\207F)x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_0F,
      .stage = &b_area_isk_part_1_isk_05,
      .onBattleStart = NULL },
    { .name = "\341\303\310,\341\303\310(f\223X\207F)x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_10,
      .stage = &b_area_isk_part_1_isk_05,
      .onBattleStart = NULL },
    { .name = "\341\303\310(f\223X\207F)x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_11,
      .stage = &b_area_isk_part_1_isk_05,
      .onBattleStart = NULL },
    { .name = "\341\303\310(f\223X\207F)x\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_12,
      .stage = &b_area_isk_part_1_isk_05,
      .onBattleStart = NULL },
    { .name = "\341\303\310(f\223X\207F)x\022,\320\265\320\265",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_isk_part_1_Formation_13,
      .stage = &b_area_isk_part_1_isk_05,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_isk_part_1_pokey_mummy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_isk_part_1_swooper_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_isk_part_1_pokey_mummy_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Call(SetActorVar, ACTOR_SELF, 9, LVar0)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0x310104)
    Call(SetActorVar, ACTOR_SELF, 2, 0x310108)
    Call(SetActorVar, ACTOR_SELF, 3, 0x31010C)
    Call(SetActorVar, ACTOR_SELF, 4, 0x310110)
    Call(SetActorVar, ACTOR_SELF, 5, 0x310111)
    Call(SetActorVar, ACTOR_SELF, 6, 0x310118)
    Call(SetActorVar, ACTOR_SELF, 7, 0x310119)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_isk_part_1_stone_chomp_ActorParts[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_isk_part_1_stone_chomp_BasicAnims,
        .defenseTable = b_area_isk_part_1_stone_chomp_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x900001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -13, 40 },
        .opacity = 255,
        .idleAnimations = TTYD64_isk_part_1_stone_chomp_BasicAnims,
        .defenseTable = b_area_isk_part_1_stone_chomp_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -14 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x124002,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 12 },
        .opacity = 255,
        .idleAnimations = b_area_isk_part_1_stone_chomp_ChainAnims,
        .defenseTable = b_area_isk_part_1_stone_chomp_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x124002,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 12 },
        .opacity = 255,
        .idleAnimations = b_area_isk_part_1_stone_chomp_ChainAnims,
        .defenseTable = b_area_isk_part_1_stone_chomp_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x124002,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 12 },
        .opacity = 255,
        .idleAnimations = b_area_isk_part_1_stone_chomp_ChainAnims,
        .defenseTable = b_area_isk_part_1_stone_chomp_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x124002,
        .index = 6,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 12 },
        .opacity = 255,
        .idleAnimations = b_area_isk_part_1_stone_chomp_ChainAnims,
        .defenseTable = b_area_isk_part_1_stone_chomp_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x124002,
        .index = 7,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 12 },
        .opacity = 255,
        .idleAnimations = b_area_isk_part_1_stone_chomp_ChainAnims,
        .defenseTable = b_area_isk_part_1_stone_chomp_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x124002,
        .index = 8,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 12 },
        .opacity = 255,
        .idleAnimations = b_area_isk_part_1_stone_chomp_ChainAnims,
        .defenseTable = b_area_isk_part_1_stone_chomp_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x124002,
        .index = 9,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 12 },
        .opacity = 255,
        .idleAnimations = b_area_isk_part_1_stone_chomp_ChainAnims,
        .defenseTable = b_area_isk_part_1_stone_chomp_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x124002,
        .index = 10,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 12 },
        .opacity = 255,
        .idleAnimations = b_area_isk_part_1_stone_chomp_ChainAnims,
        .defenseTable = b_area_isk_part_1_stone_chomp_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_isk_part_1_EVS_80223E64 = {
    Set(LVar9, 0)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar2)
    Switch(LVar2)
        CaseEq(20)
            Call(GetStatusFlags, LVar0, LVar3)
            IfNotFlag(LVar3, 0x3DD000)
                Call(GetActorVar, ACTOR_SELF, 0, LVar3)
                IfEq(LVar3, 0)
                    Call(GetActorVar, LVar0, 10, LVar3)
                    IfNe(LVar3, 2)
                        Add(LVar9, 1)
                    EndIf
                EndIf
            EndIf
    EndSwitch
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_SpinSmashHit = {
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        SetConst(LVar0, 1)
        Call(GetActorVar, ACTOR_SELF, 3, LVar1)
        ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    Switch(LVarA)
        CaseEq(0)
            ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_KnockPartAway)
        CaseEq(1)
            ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_KnockPartAway)
        CaseEq(2)
            ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_KnockPartAway)
        CaseEq(3)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_1_stone_chomp_EVS_Init = {
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_isk_part_1_stone_chomp_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_isk_part_1_stone_chomp_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_isk_part_1_stone_chomp_EVS_HandleEvent))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Set(LVar0, 3)
    Loop(8)
        Call(SetPartSize, ACTOR_SELF, LVar0, 16, 16)
        Add(LVar0, 1)
    EndLoop
    Call(b_area_isk_part_1_stone_chomp_ChompChainInit)
    Exec(b_area_isk_part_1_stone_chomp_EVS_UpdateChain)
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_isk_part_1_pokey_mummy_ActorParts[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_isk_part_1_pokey_mummy_FourPartAnims,
        .defenseTable = b_area_isk_part_1_swooper_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 72 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_isk_part_1_swooper_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 54 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_isk_part_1_swooper_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 36 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_isk_part_1_swooper_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 16 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_isk_part_1_swooper_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 6,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_isk_part_1_pokey_mummy_ThrownPartAnims,
        .defenseTable = b_area_isk_part_1_swooper_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_isk_part_1_buzzy_beetle_StatusTable[] = {
    1,  0, 2,  0, 6,  90, 9,  50, 7,  80, 4,  75, 3,  0, 11, 50, 5,  75, 10, 90, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, 0,  0,
};

s32 TTYD64_isk_part_1_pokey_mummy_StatusTable[] = {
    1,  0, 2,  0, 6,  80, 9,  0, 7,  90, 4,  90, 3,  0, 11, 0, 5,  100, 10, 90, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0, 36, 0,  35, 0,  33, 0, 38, 0, 39, 0,   41, 0,  0,
};

FormationRow TTYD64_isk_part_1_Formation_0A[] = {
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
};

FormationRow TTYD64_isk_part_1_Formation_12[] = {
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_8022460C },
      .priority = 10,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_80224618 },
      .priority = 9,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_80224624 },
      .priority = 8,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_80224630 },
      .priority = 7,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
};

FormationRow TTYD64_isk_part_1_Formation_04[] = {
    { .actor = &TTYD64_isk_part_1_pokey_mummy_80225FE0,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_isk_part_1_pokey_mummy_80225FE0,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_isk_part_1_swooper,
      .home = { .vec = &b_area_isk_part_1_vector3D_802241E8 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
    { .actor = &TTYD64_isk_part_1_swooper,
      .home = { .vec = &b_area_isk_part_1_vector3D_802241F4 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
};

// clang-format off
EvtScript TTYD64_isk_part_1_swooper_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_isk_part_1_swooper_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_isk_part_1_swooper_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_isk_part_1_swooper_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_isk_part_1_Formation_0B[] = {
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_802240AC },
      .priority = 9,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_swooper,
      .home = { .vec = &b_area_isk_part_1_vector3D_802240B8 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
};

FormationRow TTYD64_isk_part_1_Formation_11[] = {
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_802240A0 },
      .priority = 10,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_802240AC },
      .priority = 9,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_802240B8 },
      .priority = 8,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
};

FormationRow TTYD64_isk_part_1_Formation_10[] = {
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_802240AC },
      .priority = 9,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_802240B8 },
      .priority = 8,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
};

FormationRow TTYD64_isk_part_1_Formation_13[] = {
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_802240A0 },
      .priority = 10,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_802240AC },
      .priority = 9,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_swooper,
      .home = { .vec = &b_area_isk_part_1_vector3D_802240B8 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
};

FormationRow TTYD64_isk_part_1_Formation_01[] = {
    { .actor = &TTYD64_isk_part_1_pokey_mummy_80225FE0,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_isk_part_1_pokey_mummy_80225FE0,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_isk_part_1_pokey_mummy_80225FE0,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
};

FormationRow TTYD64_isk_part_1_Formation_03[] = {
    { .actor = &TTYD64_isk_part_1_pokey_mummy_80225FE0,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_isk_part_1_pokey_mummy_80225FE0,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_isk_part_1_swooper,
      .home = { .vec = &b_area_isk_part_1_vector3D_80224088 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
};

FormationRow TTYD64_isk_part_1_Formation_08[] = {
    { .actor = &TTYD64_isk_part_1_stone_chomp,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_isk_part_1_stone_chomp,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_isk_part_1_stone_chomp,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_isk_part_1_Formation_06[] = {
    { .actor = &TTYD64_isk_part_1_swooper,
      .home = { .vec = &b_area_isk_part_1_vector3D_80224070 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
    { .actor = &TTYD64_isk_part_1_swooper,
      .home = { .vec = &b_area_isk_part_1_vector3D_8022407C },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
    { .actor = &TTYD64_isk_part_1_swooper,
      .home = { .vec = &b_area_isk_part_1_vector3D_80224088 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
};

s32 TTYD64_isk_part_1_buzzy_beetle_GroundAnims[] = {
    1,  0x330001, 7, 0x330000, 6, 0x330009, 9, 0x330001, 8, 0x330000,
    11, 0x330001, 5, 0x330000, 4, 0x33000A, 3, 0x33000A, 0,
};

s32 TTYD64_isk_part_1_swooper_FlyingAnims[] = {
    1,  0x340002, 7, 0x340001, 6, 0x340013, 9, 0x340002, 8, 0x340001,
    11, 0x340002, 5, 0x340001, 4, 0x340014, 3, 0x340014, 0,
};

s32 TTYD64_isk_part_1_swooper_CeilingAnims[] = {
    1,  0x34000C, 7, 0x34000B, 6, 0x34000F, 9, 0x34000C, 8, 0x34000B,
    11, 0x34000C, 5, 0x34000B, 4, 0x340010, 3, 0x340010, 0,
};

s32 TTYD64_isk_part_1_buzzy_beetle_CeilingAnims[] = {
    1,  0x33000F, 7, 0x33000E, 6, 0x330014, 9, 0x33000F, 8, 0x33000E,
    11, 0x33000F, 5, 0x33000E, 4, 0x330015, 3, 0x330015, 0,
};

s32 TTYD64_isk_part_1_buzzy_beetle_ToppledAnims[] = {
    1, 0x330002, 7, 0x33001A, 6, 0x33001B, 9, 0x330002, 8, 0x33001A, 11, 0x330002, 4, 0x33001C, 3, 0x33001C, 0,
};

s32 TTYD64_isk_part_1_pokey_mummy_ThreePartAnims[] = {
    1, 0x310105, 7, 0x310101, 6, 0x310126, 8, 0x310101, 5, 0x310101, 4, 0x310122, 3, 0x310122, 0,
};

s32 TTYD64_isk_part_1_stone_chomp_BasicAnims[] = {
    1, 0x350001, 7, 0x350000, 6, 0x35000A, 9, 0x350001, 8, 0x350000, 11, 0x350001, 4, 0x35000B, 0,
};

s32 TTYD64_isk_part_1_pokey_mummy_OnePartAnims[] = {
    1, 0x310107, 7, 0x310103, 6, 0x310128, 8, 0x310103, 5, 0x310103, 4, 0x310124, 3, 0x310124, 0,
};

s32 TTYD64_isk_part_1_pokey_mummy_FourPartAnims[] = {
    1, 0x310104, 7, 0x310100, 6, 0x310125, 8, 0x310100, 5, 0x310100, 4, 0x310121, 3, 0x310121, 0,
};

s32 TTYD64_isk_part_1_pokey_mummy_TwoPartAnims[] = {
    1, 0x310106, 7, 0x310102, 6, 0x310127, 8, 0x310102, 5, 0x310102, 4, 0x310123, 3, 0x310123, 0,
};

s32 TTYD64_isk_part_1_stone_chomp_QuickBiteAnims[] = {
    1, 0x350003, 9, 0x350003, 8, 0x350000, 7, 0x350000, 6, 0x35000A, 11, 0x350003, 4, 0x35000B, 0,
};

s32 TTYD64_isk_part_1_stone_chomp_BiteAnims[] = {
    1, 0x350004, 9, 0x350004, 8, 0x350000, 7, 0x350000, 6, 0x35000A, 11, 0x350004, 4, 0x35000B, 0,
};

s32 TTYD64_isk_part_1_stone_chomp_SlowBiteAnims[] = {
    1, 0x350005, 9, 0x350005, 8, 0x350000, 7, 0x350000, 6, 0x35000A, 11, 0x350005, 4, 0x35000B, 0,
};

FormationRow TTYD64_isk_part_1_Formation_0D[] = {
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_802240AC },
      .priority = 10,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
};

FormationRow TTYD64_isk_part_1_Formation_0E[] = {
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_802240B8 },
      .priority = 9,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
};

FormationRow TTYD64_isk_part_1_Formation_0C[] = {
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_swooper,
      .home = { .vec = &b_area_isk_part_1_vector3D_802240B8 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
};

FormationRow TTYD64_isk_part_1_Formation_0F[] = {
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_802240AC },
      .priority = 10,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .vec = &b_area_isk_part_1_vector3D_802240B8 },
      .priority = 9,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
};

FormationRow TTYD64_isk_part_1_Formation_00[] = {
    { .actor = &TTYD64_isk_part_1_pokey_mummy_80225FE0,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_isk_part_1_pokey_mummy_80225FE0,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
};

FormationRow TTYD64_isk_part_1_Formation_05[] = {
    { .actor = &TTYD64_isk_part_1_swooper,
      .home = { .vec = &b_area_isk_part_1_vector3D_8022407C },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
    { .actor = &TTYD64_isk_part_1_swooper,
      .home = { .vec = &b_area_isk_part_1_vector3D_80224088 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
};

FormationRow TTYD64_isk_part_1_Formation_02[] = {
    { .actor = &TTYD64_isk_part_1_pokey_mummy_80225FE0,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_isk_part_1_swooper,
      .home = { .vec = &b_area_isk_part_1_vector3D_80224088 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
};

FormationRow TTYD64_isk_part_1_Formation_09[] = {
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_isk_part_1_buzzy_beetle,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
};

FormationRow TTYD64_isk_part_1_Formation_07[] = {
    { .actor = &TTYD64_isk_part_1_stone_chomp,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_isk_part_1_stone_chomp,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

ActorBlueprint TTYD64_isk_part_1_pokey_mummy = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x15,
    .level = 10,
    .partCount = 6,
    .partsData = TTYD64_isk_part_1_pokey_mummy_ActorParts,
    .initScript = &TTYD64_isk_part_1_pokey_mummy_EVS_Init,
    .statusTable = TTYD64_isk_part_1_pokey_mummy_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 90,
    .hurricaneChance = 85,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 1,
    .size = { 24, 80 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 75 },
    .statusTextOffset = { 10, 65 },
};

ActorBlueprint TTYD64_isk_part_1_stone_chomp = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x18,
    .level = 14,
    .partCount = 10,
    .partsData = TTYD64_isk_part_1_stone_chomp_ActorParts,
    .initScript = &TTYD64_isk_part_1_stone_chomp_EVS_Init,
    .statusTable = b_area_isk_part_1_stone_chomp_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 25,
    .hurricaneChance = 25,
    .spookChance = 0,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 5,
    .size = { 56, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_isk_part_1_swooper = {
    .flags = 0x800,
    .maxHP = 4,
    .type = 0x16,
    .level = 10,
    .partCount = 1,
    .partsData = TTYD64_isk_part_1_swooper_ActorParts,
    .initScript = &TTYD64_isk_part_1_swooper_EVS_Init,
    .statusTable = b_area_isk_part_1_swooper_StatusTable,
    .escapeChance = 50,
    .airLiftChance = 100,
    .hurricaneChance = 95,
    .spookChance = 90,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 1,
    .size = { 31, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, -20 },
    .statusTextOffset = { 10, -20 },
};

ActorBlueprint TTYD64_isk_part_1_pokey_mummy_80225FE0 = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x15,
    .level = 10,
    .partCount = 6,
    .partsData = TTYD64_isk_part_1_pokey_mummy_ActorParts,
    .initScript = &TTYD64_isk_part_1_pokey_mummy_EVS_Init,
    .statusTable = TTYD64_isk_part_1_pokey_mummy_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 90,
    .hurricaneChance = 85,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 1,
    .size = { 24, 80 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 75 },
    .statusTextOffset = { 10, 65 },
};

ActorBlueprint TTYD64_isk_part_1_buzzy_beetle = {
    .flags = 0x800,
    .maxHP = 3,
    .type = 0x17,
    .level = 10,
    .partCount = 1,
    .partsData = TTYD64_isk_part_1_buzzy_beetle_ActorParts,
    .initScript = &TTYD64_isk_part_1_buzzy_beetle_EVS_Init,
    .statusTable = TTYD64_isk_part_1_buzzy_beetle_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 75,
    .hurricaneChance = 75,
    .spookChance = 75,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 22, 18 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -8, 16 },
    .statusTextOffset = { 8, 13 },
};

ActorPartBlueprint TTYD64_isk_part_1_swooper_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 29 },
        .opacity = 255,
        .idleAnimations = TTYD64_isk_part_1_swooper_CeilingAnims,
        .defenseTable = b_area_isk_part_1_swooper_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 1, 15 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_isk_part_1_buzzy_beetle_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 16 },
        .opacity = 255,
        .idleAnimations = TTYD64_isk_part_1_buzzy_beetle_CeilingAnims,
        .defenseTable = b_area_isk_part_1_buzzy_beetle_UprightDefense,
        .eventFlags = 0x1000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 1, 7 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_isk_part_1_Formation_802261A0[] = {
    { .actor = &TTYD64_isk_part_1_pokey_mummy,
      .home = { .vec = &TTYD64_isk_part_1_Pos_802265EC },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

Vec3i TTYD64_isk_part_1_Pos_802265EC = { 400, -100, 0 };

void TTYD64_InstallBattles_isk_part_1(void) {
    Mod_SetBattleList("TTYD64", 11, TTYD64_isk_part_1_Formations);
}
