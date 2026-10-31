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
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(ClampAngleFloat);
API_CALLABLE(CreateHomeTargetList);
API_CALLABLE(DispatchDamageEvent);
API_CALLABLE(EnableActorGlow);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FallToGoal);
API_CALLABLE(FlyPartTo);
API_CALLABLE(FlyToGoal);
API_CALLABLE(ForceHomePos);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetBattleVar);
API_CALLABLE(GetDamageSource);
API_CALLABLE(GetEnemyMaxHP);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetIndexFromHome);
API_CALLABLE(GetLastDamage);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartOffset);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HideHealthBar);
API_CALLABLE(IdleRunToGoal);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlaySoundAtPart);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActor);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(RemoveEffect);
API_CALLABLE(ResetActorSounds);
API_CALLABLE(ResetAllActorSounds);
API_CALLABLE(RotateModel);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorIdleSpeed);
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
API_CALLABLE(SetBattleVar);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetDefenseTable);
API_CALLABLE(SetEnemyHP);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetIdleGoal);
API_CALLABLE(SetPartEventBits);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartRotation);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSize);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetPartYaw);
API_CALLABLE(SetProjectileTargetOffset);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetStatusTable);
API_CALLABLE(SetTargetActor);
API_CALLABLE(SetTargetOffset);
API_CALLABLE(ShakeCam);
API_CALLABLE(StartRumble);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
API_CALLABLE(b_area_omo3_big_lantern_ghost_init_overlay);
API_CALLABLE(b_area_omo3_fuzzy_SpawnDrainHealthContinueFX);
API_CALLABLE(b_area_omo3_fuzzy_SpawnDrainHealthStartFX);
API_CALLABLE(b_area_omo3_goomba_CalculateArcsinDeg);
API_CALLABLE(b_area_omo3_koopatrol_StartRumbleWithParams);
API_CALLABLE(b_area_omo3_pokey_SetAbsoluteStatusOffsets);
extern s32 b_area_omo3_big_lantern_ghost_DefenseTable[];
extern EvtScript b_area_omo3_big_lantern_ghost_EVS_HandleEvent;
extern EvtScript b_area_omo3_big_lantern_ghost_EVS_HandlePhase;
extern EvtScript b_area_omo3_big_lantern_ghost_EVS_Idle;
extern EvtScript b_area_omo3_big_lantern_ghost_EVS_ReturnHome;
extern s32 b_area_omo3_big_lantern_ghost_StatusTable[];
extern EvtScript b_area_omo3_big_lantern_ghost_checkExtinguish;
extern s32 b_area_omo3_big_lantern_ghost_defenseTable2[];
extern EvtScript b_area_omo3_big_lantern_ghost_extinguish;
extern Vec3i b_area_omo3_big_lantern_ghost_pos;
extern EvtScript b_area_omo3_big_lantern_ghost_setGhostNoTarget;
extern EvtScript b_area_omo3_big_lantern_ghost_updateEffectThread;
extern s32 b_area_omo3_clubba_DefenseTable[];
extern EvtScript b_area_omo3_clubba_EVS_HandleEvent;
extern EvtScript b_area_omo3_clubba_EVS_Idle;
extern s32 b_area_omo3_fuzzy_DefenseTable[];
extern EvtScript b_area_omo3_fuzzy_EVS_Idle;
extern s32 b_area_omo3_fuzzy_StatusTable[];
extern s32 b_area_omo3_goomba_DefenseTable[];
extern s32 b_area_omo3_goomba_StatusTable[];
extern s32 b_area_omo3_hammer_bro_DefenseTable[];
extern EvtScript b_area_omo3_hammer_bro_EVS_HandleEvent;
extern EvtScript b_area_omo3_hammer_bro_EVS_Idle;
extern s32 b_area_omo3_hammer_bro_HammerAnims[];
extern s32 b_area_omo3_koopatrol_ChargedDefense[];
extern s32 b_area_omo3_koopatrol_ChargedStatusTable[];
extern s32 b_area_omo3_koopatrol_DefenseTable[];
extern EvtScript b_area_omo3_koopatrol_EVS_CountActiveSummoners;
extern EvtScript b_area_omo3_koopatrol_EVS_GetAvailableColumn;
extern EvtScript b_area_omo3_koopatrol_EVS_HandlePhase;
extern EvtScript b_area_omo3_koopatrol_EVS_UpdateOffsets;
extern u8 b_area_omo3_koopatrol_FlipPosOffsets[];
extern Vec3i b_area_omo3_koopatrol_SummonPos;
extern s32 b_area_omo3_koopatrol_ToppledDefense[];
extern EvtScript b_area_omo3_omo_01_EVS_PostBattle;
extern EvtScript b_area_omo3_omo_01_EVS_UpdateRockingHorse;
extern Stage b_area_omo3_omo_02;
extern Stage b_area_omo3_omo_03;
extern Stage b_area_omo3_omo_03b;
extern Stage b_area_omo3_omo_04;
extern Stage b_area_omo3_omo_05;
extern Stage b_area_omo3_omo_05b;
extern Stage b_area_omo3_omo_06;
extern Stage b_area_omo3_omo_07;
extern s32 b_area_omo3_pokey_DefenseTable[];
extern EvtScript b_area_omo3_pokey_EVS_CountSummonerPokeys;
extern EvtScript b_area_omo3_pokey_EVS_FindValidSummonPosition;
extern EvtScript b_area_omo3_pokey_EVS_HitReactionBounce;
extern EvtScript b_area_omo3_pokey_EVS_Idle;
extern Vec3i b_area_omo3_pokey_SummonPos;
extern s32 b_area_omo3_pokey_ThrownPartAnims[];
extern s32 b_area_omo3_red_shy_guy_DefenseTable[];
extern EvtScript b_area_omo3_red_shy_guy_EVS_HandleEvent;
extern EvtScript b_area_omo3_red_shy_guy_EVS_Idle;
extern EvtScript b_area_omo3_red_shy_guy_EVS_ReturnHome;
extern EvtScript TTYD64_omo3_koopatrol_EVS_HandleEvent;
extern EvtScript TTYD64_omo3_fuzzy_EVS_TakeTurn;
extern EvtScript TTYD64_omo3_koopatrol_EVS_Attack_ChargedToss;
extern EvtScript TTYD64_omo3_koopatrol_EVS_Attack_ShellToss;
extern EvtScript TTYD64_omo3_goomba_EVS_TakeTurn;
extern EvtScript TTYD64_omo3_pokey_EVS_HandleEvent;
extern EvtScript TTYD64_omo3_red_shy_guy_EVS_Attack_Vault;
extern EvtScript TTYD64_omo3_pokey_EVS_TakeTurn;
extern EvtScript TTYD64_omo3_pokey_EVS_Attack_GroundSmash;
extern EvtScript TTYD64_omo3_pokey_EVS_Attack_SinglePartLeap;
extern EvtScript TTYD64_omo3_hammer_bro_EVS_Attack_HammerThrow;
extern EvtScript TTYD64_omo3_hammer_bro_EVS_Attack_HammerSurge;
extern EvtScript TTYD64_omo3_koopatrol_EVS_TakeTurn;
extern EvtScript TTYD64_omo3_big_lantern_ghost_attackHeavyJump;
extern EvtScript TTYD64_omo3_pokey_EVS_SummonBackup;
extern EvtScript TTYD64_omo3_big_lantern_ghost_attackLightBeam;
extern EvtScript TTYD64_omo3_EVS_802250AC;
extern EvtScript TTYD64_omo3_red_shy_guy_EVS_Attack_Tackle;
extern EvtScript TTYD64_omo3_goomba_EVS_HandleEvent;
extern EvtScript TTYD64_omo3_fuzzy_EVS_HandleEvent;
extern EvtScript TTYD64_omo3_koopatrol_EVS_Move_SummonBackup;
extern EvtScript TTYD64_omo3_koopatrol_EVS_Idle;
extern EvtScript TTYD64_omo3_clubba_EVS_TakeTurn;
extern EvtScript TTYD64_omo3_pokey_EVS_DecrementSize;
extern EvtScript TTYD64_omo3_pokey_EVS_Pokey_Hit;
extern EvtScript TTYD64_omo3_pokey_EVS_KnockPartAway;
extern EvtScript TTYD64_omo3_pokey_EVS_Pokey_ScareAway;
extern EvtScript TTYD64_omo3_goomba_EVS_Idle;
extern EvtScript TTYD64_omo3_hammer_bro_EVS_HammerSurge_Miss;
extern EvtScript TTYD64_omo3_hammer_bro_EVS_HammerSurge_Hit;
extern EvtScript TTYD64_omo3_big_lantern_ghost_EVS_Init;
extern EvtScript TTYD64_omo3_big_lantern_ghost_EVS_TakeTurn;
extern EvtScript TTYD64_omo3_EVS_8022BF5C;
extern EvtScript TTYD64_omo3_pokey_EVS_Init;
extern EvtScript TTYD64_omo3_koopatrol_EVS_Init;
extern EvtScript TTYD64_omo3_pokey_EVS_Pokey_SpinSmashHit;
extern EvtScript TTYD64_omo3_EVS_8022CDB0;
extern EvtScript TTYD64_omo3_omo_01_EVS_PreBattle;
extern EvtScript TTYD64_omo3_hammer_bro_EVS_TakeTurn;
extern EvtScript TTYD64_omo3_hammer_bro_EVS_Init;
extern EvtScript TTYD64_omo3_red_shy_guy_EVS_TakeTurn;
extern EvtScript TTYD64_omo3_red_shy_guy_EVS_Init;
extern EvtScript TTYD64_omo3_fuzzy_EVS_Init;
extern EvtScript TTYD64_omo3_clubba_EVS_Init;
extern EvtScript TTYD64_omo3_goomba_EVS_Init;
extern ActorBlueprint TTYD64_omo3_red_shy_guy;
extern Stage TTYD64_omo3_omo_01;
extern ActorBlueprint TTYD64_omo3_koopatrol;
extern ActorBlueprint TTYD64_omo3_clubba;
extern ActorBlueprint TTYD64_omo3_fuzzy;
extern ActorBlueprint TTYD64_omo3_pokey;
extern ActorBlueprint TTYD64_omo3_pokey_8022F4A4;
extern ActorBlueprint TTYD64_omo3_big_lantern_ghost;
extern ActorBlueprint TTYD64_omo3_hammer_bro;
extern ActorBlueprint TTYD64_omo3_goomba;
extern ActorBlueprint TTYD64_omo3_koopatrol_8022F5E4;
extern Battle TTYD64_omo3_Formations[];
extern ActorPartBlueprint TTYD64_omo3_hammer_bro_ActorParts[];
extern ActorPartBlueprint TTYD64_omo3_pokey_ActorParts[];
extern s32 TTYD64_omo3_red_shy_guy_StatusTable[];
extern s32 TTYD64_omo3_clubba_StatusTable[];
extern s32 TTYD64_omo3_pokey_StatusTable[];
extern s32 TTYD64_omo3_hammer_bro_StatusTable[];
extern s32 TTYD64_omo3_koopatrol_StatusTable[];
extern FormationRow TTYD64_omo3_Formation_05[];
extern s32 TTYD64_omo3_big_lantern_ghost_DefaultAnims[];
extern StageListRow TTYD64_omo3_Stages[];
extern s32 TTYD64_omo3_koopatrol_ShuffleAnims[];
extern s32 TTYD64_omo3_hammer_bro_DefaultAnims[];
extern s32 TTYD64_omo3_koopatrol_DefaultAnims[];
extern s32 TTYD64_omo3_fuzzy_DefaultAnims[];
extern s32 TTYD64_omo3_clubba_DefaultAnims[];
extern s32 TTYD64_omo3_goomba_ShuffleAnims[];
extern s32 TTYD64_omo3_koopatrol_ToppledAnims[];
extern s32 TTYD64_omo3_koopatrol_ChargedAnims[];
extern s32 TTYD64_omo3_goomba_DefaultAnims[];
extern s32 TTYD64_omo3_red_shy_guy_DefaultAnims[];
extern ActorPartBlueprint TTYD64_omo3_big_lantern_ghost_ActorParts[];
extern s32 TTYD64_omo3_pokey_ThreePartAnims[];
extern s32 TTYD64_omo3_pokey_OnePartAnims[];
extern s32 TTYD64_omo3_pokey_FourPartAnims[];
extern s32 TTYD64_omo3_pokey_TwoPartAnims[];
extern FormationRow TTYD64_omo3_Formation_04[];
extern FormationRow TTYD64_omo3_Formation_02[];
extern FormationRow TTYD64_omo3_Formation_03[];
extern FormationRow TTYD64_omo3_Formation_08[];
extern FormationRow TTYD64_omo3_Formation_09[];
extern FormationRow TTYD64_omo3_Formation_06[];
extern ActorPartBlueprint TTYD64_omo3_clubba_ActorParts[];
extern ActorPartBlueprint TTYD64_omo3_fuzzy_ActorParts[];
extern ActorPartBlueprint TTYD64_omo3_goomba_ActorParts[];
extern ActorPartBlueprint TTYD64_omo3_koopatrol_ActorParts[];
extern ActorPartBlueprint TTYD64_omo3_red_shy_guy_ActorParts[];
extern FormationRow TTYD64_omo3_Formation_0A[];
extern FormationRow TTYD64_omo3_Formation_00[];
extern FormationRow TTYD64_omo3_Formation_01[];
extern FormationRow TTYD64_omo3_Formation_07[];
extern FormationRow TTYD64_omo3_pokey_SummonFormation[];
extern FormationRow TTYD64_omo3_koopatrol_BackupFormation[];
extern s32 TTYD64_omo3_Anims_8022FB58[];
extern s32 TTYD64_omo3_Defense_8022FC0C[];

// clang-format off
EvtScript TTYD64_omo3_koopatrol_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_Hit))
                EndCaseGroup
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590006)
                    ExecWait(Ref(EVS_Enemy_Hit))
            EndSwitch
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x59000C)
            SetConst(LVar2, 0x59000D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x59000C)
            SetConst(LVar2, 0x59000D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x59000D)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_SpinSmashHit))
                EndCaseGroup
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590006)
                    ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            EndSwitch
        CaseEq(33)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_SpinSmashHit))
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_Death))
                EndCaseGroup
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590006)
                    ExecWait(Ref(EVS_Enemy_SpinSmashHit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
                    Wait(5)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_Death))
            EndSwitch
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(SetActorVar, ACTOR_SELF, 3, 0)
            Call(SetActorVar, ACTOR_SELF, 9, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_omo3_koopatrol_ToppledDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_koopatrol_ToppledAnims))
            Call(SetTargetOffset, ACTOR_SELF, 1, -5, 15)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 16, 0)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x59000B)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            Thread
                Wait(4)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -60)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -75)
                Wait(1)
            EndThread
            UseBuf(Ref(b_area_omo3_koopatrol_FlipPosOffsets))
            Loop(22)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x59000F)
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x59000B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x59000B)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x590004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x59000B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x59000B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 2)
                Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_omo3_koopatrol_StatusTable))
                Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_omo3_koopatrol_DefenseTable))
                Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
                Call(SetActorVar, ACTOR_SELF, 0, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_koopatrol_DefaultAnims))
                Call(GetStatusFlags, ACTOR_SELF, LVarA)
                IfNotFlag(LVarA, 0x18000000)
                    Call(EnableActorGlow, ACTOR_SELF, 0)
                EndIf
                Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x590008)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseOrEq(23)
        CaseOrEq(25)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590007)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(GetStatusFlags, ACTOR_SELF, LVar0)
                    IfNotFlag(LVar0, 0x35D000)
                        Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
                        Wait(10)
                    EndIf
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                CaseEq(2)
                    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
                    IfEq(LVar0, 1)
                        SetConst(LVar0, 1)
                        SetConst(LVar1, 0x590005)
                    Else
                        SetConst(LVar0, 1)
                        SetConst(LVar1, 0x590006)
                    EndIf
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndSwitch
        EndCaseGroup
        CaseEq(27)
            Wait(10)
            Set(LFlag0, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                Add(LVar1, 16)
                Set(LFlag0, 1)
            EndIf
            IfFlag(LVar3, 0x40000)
                Add(LVar0, -14)
                Add(LVar1, 20)
                Set(LFlag0, 1)
            EndIf
            IfFlag(LVar3, 4096)
                Add(LVar0, -14)
                Add(LVar1, 20)
                Set(LFlag0, 1)
            EndIf
            Call(GetActorVar, ACTOR_SELF, 0, LVarA)
            IfEq(LVarA, 2)
                Add(LVar1, 23)
                Set(LFlag0, 1)
            EndIf
            IfEq(LFlag0, 0)
                Add(LVar1, 42)
            EndIf
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(20)
        CaseEq(32)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Wait(10)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_Death))
                    Return
                EndCaseGroup
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590006)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
                    Wait(5)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_Death))
                    Return
            EndSwitch
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590001)
                    ExecWait(Ref(EVS_Enemy_Recover))
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590006)
                    ExecWait(Ref(EVS_Enemy_Recover))
            EndSwitch
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590004)
                    SetConst(LVar2, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_ScareAway))
                    Return
                EndCaseGroup
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndSwitch
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590016)
                    ExecWait(Ref(EVS_Enemy_AirLift))
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
                    ExecWait(Ref(EVS_Enemy_AirLift))
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
                    ExecWait(Ref(EVS_Enemy_AirLift))
            EndSwitch
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590016)
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590001)
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_fuzzy_EVS_TakeTurn = {
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
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 50)
        Set(LVar1, 0)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Goto(100)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0001)
    Label(100)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0004)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 9, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 8, 0)
    Wait(5)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 5)
            Set(LVar1, 0)
            Sub(LVar2, 5)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0005)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 11, 0, 1, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0009)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 15)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Wait(4)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            ExecWait(Ref(EVS_Enemy_HopToPos))
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
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -3, -12, -15)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0005)
    Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
    IfEq(LFlag0, 1)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 0, 32)
        Return
    EndIf
    Wait(10)
    Call(GetOwnerTarget, LVar0, 0)
    Switch(LVar0)
        CaseEq(0)
            Call(UseIdleAnimation, 0, 0)
            Call(SetAnimation, 0, 0, 0x3000C)
        CaseEq(256)
            Call(UseIdleAnimation, 256, 0)
            Set(LVar0, 4)
            Exec(TTYD64_SetPartnerAnimation_Battle)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 992)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0007)
    Wait(21)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0000)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 330)
    Call(PlaySoundAtActor, ACTOR_SELF, 992)
    Call(SetActorDispOffset, ACTOR_SELF, -3, -2, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
    Wait(2)
    Call(SetActorScale, ACTOR_SELF, Float(0.599609375), Float(1.599609375), Float(1.0))
    Wait(10)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 1, 32)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0001)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(GetOwnerTarget, LVar0, 0)
            Call(GetLastDamage, LVar0, LVar3)
            IfNe(LVar3, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8301)
                Call(PlaySoundAtActor, ACTOR_SELF, 532)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 10)
                Call(b_area_omo3_fuzzy_SpawnDrainHealthStartFX, LVar0, LVar1, LVar2, LVar3)
                Thread
                    Wait(15)
                    Call(PlaySoundAtActor, ACTOR_SELF, 604)
                    Call(b_area_omo3_fuzzy_SpawnDrainHealthContinueFX, LVar0, LVar1, LVar2, LVar3)
                EndThread
                Add(LVar0, 20)
                Add(LVar1, 20)
                Call(PlayEffect_impl, 64, 0, LVar0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0)
                Call(GetActorHP, ACTOR_SELF, LVar0)
                Add(LVar0, LVar3)
                Call(SetEnemyHP, ACTOR_SELF, LVar0)
            EndIf
            Thread
                Call(SetActorScale, ACTOR_SELF, Float(1.599609375), Float(0.599609375), Float(1.0))
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 330)
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 300)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 270)
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(0.7001953125), Float(1.0))
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 240)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 210)
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 180)
                Wait(2)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(0.7001953125), Float(1.0))
                Wait(2)
                Call(SetActorScale, ACTOR_SELF, Float(1.2001953125), Float(0.5), Float(1.0))
            EndThread
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetActorScale, ACTOR_SELF, Float(1.400390625), Float(0.2001953125), Float(1.0))
            Wait(1)
            Thread
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(1.2001953125), Float(0.5), Float(1.0))
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 150)
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 120)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 90)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 60)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(5)
            Call(YieldTurn)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            ExecWait(Ref(EVS_Enemy_HopToPos))
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0001)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_koopatrol_EVS_Attack_ChargedToss = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_omo3_EVS_8022CDB0)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Call(RandInt, 100, LVar0)
        IfLt(LVar0, 50)
            ExecWait(TTYD64_omo3_EVS_8022BF5C)
            Return
        EndIf
        Call(UseBattleCamPreset, 14)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 20)
        Call(PlaySoundAtActor, ACTOR_SELF, 728)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 10)
        Call(PlayEffect_impl, 107, 6, LVar0, LVar1, LVar2, Float(1.0), 45, 0, 0, 0, 0, 0, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590015)
        Wait(30)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 20)
        Thread
            Wait(8)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590007)
        EndThread
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 8378)
        Call(b_area_omo3_koopatrol_StartRumbleWithParams, 128, 10)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(0.5))
        EndThread
        Call(SetAnimation, ACTOR_SELF, 1, 0x590006)
        Call(SetStatusTable, ACTOR_SELF, Ref(b_area_omo3_koopatrol_ChargedStatusTable))
        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_omo3_koopatrol_ChargedDefense))
        Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 0)
        Call(SetActorVar, ACTOR_SELF, 0, 2)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_koopatrol_ChargedAnims))
        Call(TTYD64_AddCharge, ACTOR_SELF, 6)
        Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 1)
        Wait(10)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Return
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Loop(20)
        Call(SetActorDispOffset, ACTOR_SELF, 1, 0, 0)
        Wait(1)
        Call(SetActorDispOffset, ACTOR_SELF, -1, 0, 0)
        Wait(1)
    EndLoop
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 892)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 4, 16)
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
            Thread
                Loop(30)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(PlayEffect_impl, 7, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -200, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Wait(15)
            Call(GetStatusFlags, ACTOR_SELF, LVarA)
            IfNotFlag(LVarA, 0x18000000)
                Call(EnableActorGlow, ACTOR_SELF, 0)
            EndIf
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorPos, ACTOR_SELF, 300, 0, 0)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_omo3_koopatrol_StatusTable))
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_omo3_koopatrol_DefenseTable))
            Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_koopatrol_DefaultAnims))
            Wait(10)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 15, 0)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Loop(30)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 7, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(1)
        EndLoop
    EndThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarA, 0, 0xFFFF, 0, 4, 32)
    Switch(LVarA)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                Set(LVar0, 0)
                Loop(60)
                    Add(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 30, 0, 1, 0)
            Sub(LVar0, 40)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Wait(20)
            Call(YieldTurn)
            Call(GetStatusFlags, ACTOR_SELF, LVarA)
            IfNotFlag(LVarA, 0x18000000)
                Call(EnableActorGlow, ACTOR_SELF, 0)
            EndIf
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorPos, ACTOR_SELF, 300, 0, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x590004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x590001)
            Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_omo3_koopatrol_StatusTable))
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_omo3_koopatrol_DefenseTable))
            Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_koopatrol_DefaultAnims))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_koopatrol_EVS_Attack_ShellToss = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590006)
    Else
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        IfEq(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 9, LVar0)
            Sub(LVar0, 1)
            IfGt(LVar0, 0)
                Call(SetActorVar, ACTOR_SELF, 9, LVar0)
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
                Wait(15)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Else
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
                Wait(10)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8321)
                Call(SetAnimation, ACTOR_SELF, 1, 0x59000F)
                Set(LVar0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
                Thread
                    Loop(5)
                        Add(LVar0, 15)
                        Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                        Wait(1)
                    EndLoop
                EndThread
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
                Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8378)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x590001)
                Call(SetActorVar, ACTOR_SELF, 0, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_koopatrol_DefaultAnims))
                Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_omo3_koopatrol_DefenseTable))
                Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
                Call(SetTargetOffset, ACTOR_SELF, 1, -4, 32)
                Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -4)
                Call(SetPartEventBits, ACTOR_SELF, 1, 16, 1)
                Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndIf
        Call(RandInt, 100, LVar0)
        IfLt(LVar0, 40)
            ExecWait(TTYD64_omo3_EVS_802250AC)
            Return
        EndIf
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590007)
        Wait(10)
        Thread
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 4)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            Wait(3)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            Wait(2)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        EndThread
        Call(PlaySoundAtActor, ACTOR_SELF, 8225)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590006)
        Wait(10)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 4, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -40, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(UseBattleCamPreset, 5)
                Call(SetBattleCamDist, 300)
                Call(SetBattleCamOffsetY, 20)
                Call(MoveBattleCamOver, 10)
                Call(SetBattleCamTargetingModes, -1, 1, 0)
            EndIf
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
            Wait(8)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Wait(4)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590016)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590016)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590016)
            Wait(6)
            Sub(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590016)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590001)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetPartYaw, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 4, 32)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
            Wait(8)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x590004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x590001)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_goomba_EVS_TakeTurn = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x260003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 10)
            Set(LVar1, 10)
            Add(LVar2, 3)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_omo3_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260008)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 5, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 7, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260005)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Thread
                Wait(4)
                Set(LVar0, 180)
                Loop(4)
                    Sub(LVar0, 45)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260007)
            Wait(5)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_omo3_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x26000B)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Wait(1)
    EndSwitch
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(1)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
            Wait(3)
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_pokey_EVS_HandleEvent = {
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
                            ExecWait(TTYD64_omo3_pokey_EVS_Pokey_Hit)
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
                            ExecWait(TTYD64_omo3_pokey_EVS_Pokey_Hit)
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
                            ExecWait(TTYD64_omo3_pokey_EVS_Pokey_Hit)
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
                            ExecWait(TTYD64_omo3_pokey_EVS_Pokey_Hit)
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
            ExecWait(TTYD64_omo3_pokey_EVS_Pokey_SpinSmashHit)
        CaseEq(33)
            ExecWait(TTYD64_omo3_pokey_EVS_Pokey_SpinSmashHit)
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
                ExecWait(TTYD64_omo3_pokey_EVS_Pokey_Hit)
            EndIf
        CaseEq(37)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                SetConst(LVar0, 1)
                Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                ExecWait(TTYD64_omo3_pokey_EVS_Pokey_Hit)
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
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Set(LVar0, 0)
                    Set(LVar1, 77)
                    SetConst(LVar2, 0x310021)
                CaseEq(1)
                    Set(LVar0, 0)
                    Set(LVar1, 59)
                    SetConst(LVar2, 0x310022)
                CaseEq(2)
                    Set(LVar0, 0)
                    Set(LVar1, 41)
                    SetConst(LVar2, 0x310023)
                CaseEq(3)
                    Set(LVar0, 0)
                    Set(LVar1, 23)
                    SetConst(LVar2, 0x310024)
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
            ExecWait(TTYD64_omo3_pokey_EVS_Pokey_ScareAway)
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
EvtScript TTYD64_omo3_red_shy_guy_EVS_Attack_Vault = {
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
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 564)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0009)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0003)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 80)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
    Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0004)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Sub(LVar0, 40)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0009)
            Thread
                Wait(12)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B000A)
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 10)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 24, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0005)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Sub(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 15)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3B0004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0001)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0009)
    Thread
        Wait(9)
        Call(SetAnimation, ACTOR_SELF, 1, 0x3B000A)
    EndThread
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(JumpToGoal, ACTOR_SELF, 18, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 15)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 14, 0)
                Set(LVar3, 0)
                Loop(20)
                    Sub(LVar3, 30)
                    IfLt(LVar3, 0)
                        Add(LVar3, 360)
                    EndIf
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar3)
                    Wait(1)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(GetBattleFlags, LVar0)
            IfFlag(LVar0, (-0x7FFFFFFF - 1))
                Goto(1)
            EndIf
            Call(GetOwnerTarget, LVar2, 0)
            Call(GetLastDamage, LVar2, LVar0)
            IfEq(LVar0, 0)
                Goto(1)
            EndIf
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 841)
            Call(PlaySoundAtActor, ACTOR_SELF, 1865)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0009)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0007)
            Wait(15)
            Goto(2)
            Label(1)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8420)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0010)
            Wait(10)
            Call(PlaySoundAtActor, ACTOR_SELF, 8387)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 50)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0011)
            Else
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0013)
            EndIf
            Wait(25)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Label(2)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3B0004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0001)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_pokey_EVS_TakeTurn = {
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfEq(LVarA, 3)
        ExecWait(TTYD64_omo3_pokey_EVS_Attack_SinglePartLeap)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 9, LVar0)
    IfEq(LVar0, 0)
        Call(GetActorVar, ACTOR_SELF, 10, LVar0)
        IfEq(LVar0, 2)
            Goto(123)
        EndIf
        ExecWait(b_area_omo3_pokey_EVS_FindValidSummonPosition)
        IfEq(LVarE, -1)
            Goto(123)
        EndIf
        ExecWait(b_area_omo3_pokey_EVS_CountSummonerPokeys)
        Switch(LVar9)
            CaseEq(1)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 400)
                    ExecWait(TTYD64_omo3_pokey_EVS_SummonBackup)
                    Return
                EndIf
            CaseEq(2)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 200)
                    ExecWait(TTYD64_omo3_pokey_EVS_SummonBackup)
                    Return
                EndIf
            CaseEq(3)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 100)
                    ExecWait(TTYD64_omo3_pokey_EVS_SummonBackup)
                    Return
                EndIf
        EndSwitch
    EndIf
    Label(123)
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 500)
        ExecWait(TTYD64_omo3_pokey_EVS_Attack_GroundSmash)
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
        Call(SetAnimation, ACTOR_SELF, 6, 0x310016)
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
    ExecWait(TTYD64_omo3_pokey_EVS_DecrementSize)
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
            Call(SetAnimation, ACTOR_SELF, 6, 0x310016)
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
    Call(SetAnimation, ACTOR_SELF, 6, 0x310016)
    Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 1)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, -0x7FFDFD00, 3, 32)
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
EvtScript TTYD64_omo3_pokey_EVS_Attack_GroundSmash = {
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x310008)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310004)
        CaseEq(1)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Call(AddGoalPos, ACTOR_SELF, 40, 0, 0)
            Else
                Call(AddGoalPos, ACTOR_SELF, 16, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x310009)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310005)
        CaseEq(2)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Call(AddGoalPos, ACTOR_SELF, 20, 0, 0)
            Else
                Call(AddGoalPos, ACTOR_SELF, 8, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x31000A)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310006)
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
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310008)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310004)
                CaseEq(1)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310009)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310005)
                CaseEq(2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x31000A)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310006)
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
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310008)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310004)
                CaseEq(1)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310009)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310005)
                CaseEq(2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x31000A)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310006)
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
EvtScript TTYD64_omo3_pokey_EVS_Attack_SinglePartLeap = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x31000B)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetAnimation, ACTOR_SELF, 1, 0x310007)
    Wait(4)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(4)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x31000B)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x31000B)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            ExecWait(Ref(EVS_Enemy_HopToPos))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310007)
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
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, -0x7FFDFD00, 4, 32)
    Call(SetAnimation, ACTOR_SELF, 1, 0x310007)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x310007)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x31000B)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            ExecWait(Ref(EVS_Enemy_HopToPos))
            Call(SetAnimation, ACTOR_SELF, 1, 0x310007)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_hammer_bro_EVS_Attack_HammerThrow = {
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
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    EndIf
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ChildThread
            Set(LVar0, 0)
            Label(0)
            Add(LVar0, 20)
            Mod(LVar0, 360)
            Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, LVar0)
            Wait(1)
            Goto(0)
        EndChildThread
        Call(SetPartPos, ACTOR_SELF, 2, 0, 50, 0)
        Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x5A000C)
        Goto(100)
    EndIf
    ChildThread
        Set(LVar0, 0)
        Label(0)
        Add(LVar0, 20)
        Mod(LVar0, 360)
        Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, LVar0)
        Wait(1)
        Goto(0)
    EndChildThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 23)
    Add(LVar1, 23)
    Sub(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A000C)
    Wait(8)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Label(100)
    Thread
        Wait(15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x5A0002)
    EndThread
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 2, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Else
        Call(SetPartScale, ACTOR_SELF, 2, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetPartSounds, ACTOR_SELF, 2, 2, 0, 0)
            Call(PlaySoundAtPart, ACTOR_SELF, 2, 745)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 10)
            Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(1.2998046875))
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 15, 1)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Sub(LVar0, 40)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 15, 1)
            Sub(LVar0, 30)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 10, 1)
            Sub(LVar0, 20)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 5, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Wait(15)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(20)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetPartSounds, ACTOR_SELF, 2, 2, 0, 0)
    Call(PlaySoundAtPart, ACTOR_SELF, 2, 745)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(1.2998046875))
    Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 15, 1)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 5, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Exec(TTYD64_Script_TryToShrinkTarget)
            Call(GetPartOffset, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Set(LVar1, 10)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 20, 1)
            Sub(LVar0, 30)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 10, 1)
            Sub(LVar0, 20)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 5, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Wait(20)
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
EvtScript TTYD64_omo3_hammer_bro_EVS_Attack_HammerSurge = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Thread
        Set(LVar0, 0)
        Loop(100)
            Add(LVar0, 20)
            Mod(LVar0, 360)
            Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, LVar0)
            Call(SetPartRotation, ACTOR_SELF, 3, 0, 0, LVar0)
            Call(SetPartRotation, ACTOR_SELF, 4, 0, 0, LVar0)
            Call(SetPartRotation, ACTOR_SELF, 5, 0, 0, LVar0)
            Call(SetPartRotation, ACTOR_SELF, 6, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 23)
    Add(LVar1, 23)
    Sub(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 2, Float(0.400390625), Float(0.400390625), Float(0.400390625))
        Call(SetPartScale, ACTOR_SELF, 3, Float(0.400390625), Float(0.400390625), Float(0.400390625))
        Call(SetPartScale, ACTOR_SELF, 4, Float(0.400390625), Float(0.400390625), Float(0.400390625))
        Call(SetPartScale, ACTOR_SELF, 5, Float(0.400390625), Float(0.400390625), Float(0.400390625))
        Call(SetPartScale, ACTOR_SELF, 6, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Else
        Call(SetPartScale, ACTOR_SELF, 2, Float(1.0), Float(1.0), Float(1.0))
        Call(SetPartScale, ACTOR_SELF, 3, Float(1.0), Float(1.0), Float(1.0))
        Call(SetPartScale, ACTOR_SELF, 4, Float(1.0), Float(1.0), Float(1.0))
        Call(SetPartScale, ACTOR_SELF, 5, Float(1.0), Float(1.0), Float(1.0))
        Call(SetPartScale, ACTOR_SELF, 6, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Set(LVar0, 2)
            Exec(TTYD64_omo3_hammer_bro_EVS_HammerSurge_Miss)
            Wait(5)
            Set(LVar0, 3)
            Exec(TTYD64_omo3_hammer_bro_EVS_HammerSurge_Miss)
            Wait(5)
            Set(LVar0, 4)
            Exec(TTYD64_omo3_hammer_bro_EVS_HammerSurge_Miss)
            Wait(5)
            Set(LVar0, 5)
            Exec(TTYD64_omo3_hammer_bro_EVS_HammerSurge_Miss)
            Wait(5)
            Set(LVar0, 6)
            Exec(TTYD64_omo3_hammer_bro_EVS_HammerSurge_Miss)
            Wait(5)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x5A0002)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(20)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Set(LVar0, 2)
        Exec(TTYD64_omo3_hammer_bro_EVS_HammerSurge_Hit)
        Wait(5)
        Set(LVar0, 3)
        Exec(TTYD64_omo3_hammer_bro_EVS_HammerSurge_Hit)
        Wait(5)
        Set(LVar0, 4)
        Exec(TTYD64_omo3_hammer_bro_EVS_HammerSurge_Hit)
        Wait(5)
        Set(LVar0, 5)
        Exec(TTYD64_omo3_hammer_bro_EVS_HammerSurge_Hit)
        Wait(5)
        Set(LVar0, 6)
        Exec(TTYD64_omo3_hammer_bro_EVS_HammerSurge_Hit)
    EndThread
    Wait(21)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 2, 16)
    Wait(5)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 2, 64)
    Wait(5)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 2, 64)
    Wait(5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A0002)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 2, 64)
    Wait(5)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Exec(TTYD64_Script_TryToShrinkTarget)
            Wait(20)
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
EvtScript TTYD64_omo3_koopatrol_EVS_TakeTurn = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetBattleVar, 1, 1)
        ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ShellToss)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(GetBattleVar, 1, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseOrEq(0)
                        CaseOrEq(1)
                            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
                            Switch(LVar0)
                                CaseEq(0)
                                    Call(GetBattleVar, 4, LVar1)
                                CaseEq(1)
                                    Call(GetBattleVar, 5, LVar1)
                                CaseEq(2)
                                    Call(GetBattleVar, 6, LVar1)
                                CaseEq(3)
                                    Call(GetBattleVar, 7, LVar1)
                            EndSwitch
                            IfGe(LVar1, 2)
                                Call(RandInt, 1000, LVar0)
                                IfLt(LVar0, 300)
                                    Call(SetBattleVar, 1, 2)
                                    ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ChargedToss)
                                Else
                                    Call(SetBattleVar, 1, 1)
                                    ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ShellToss)
                                EndIf
                                Return
                            EndIf
                        EndCaseGroup
                        CaseEq(2)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 300)
                                Call(SetBattleVar, 1, 2)
                                ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ChargedToss)
                            Else
                                Call(SetBattleVar, 1, 1)
                                ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ShellToss)
                            EndIf
                            Return
                    EndSwitch
                    ExecWait(b_area_omo3_koopatrol_EVS_GetAvailableColumn)
                    IfEq(LVarA, -1)
                        Call(RandInt, 1000, LVar0)
                        IfLt(LVar0, 300)
                            Call(SetBattleVar, 1, 2)
                            ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ChargedToss)
                        Else
                            Call(SetBattleVar, 1, 1)
                            ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ShellToss)
                        EndIf
                        Return
                    EndIf
                    ExecWait(b_area_omo3_koopatrol_EVS_CountActiveSummoners)
                    Switch(LVar9)
                        CaseEq(1)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 400)
                                Call(SetBattleVar, 1, 1)
                                ExecWait(TTYD64_omo3_koopatrol_EVS_Move_SummonBackup)
                                Return
                            EndIf
                        CaseEq(2)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 200)
                                Call(SetBattleVar, 1, 1)
                                ExecWait(TTYD64_omo3_koopatrol_EVS_Move_SummonBackup)
                                Return
                            EndIf
                        CaseEq(3)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 100)
                                Call(SetBattleVar, 1, 1)
                                ExecWait(TTYD64_omo3_koopatrol_EVS_Move_SummonBackup)
                                Return
                            EndIf
                    EndSwitch
                    Call(RandInt, 1000, LVar0)
                    IfLt(LVar0, 300)
                        Call(SetBattleVar, 1, 2)
                        ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ChargedToss)
                    Else
                        Call(SetBattleVar, 1, 1)
                        ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ShellToss)
                    EndIf
                CaseEq(1)
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseOrEq(0)
                        CaseOrEq(1)
                            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
                            Switch(LVar0)
                                CaseEq(0)
                                    Call(GetBattleVar, 4, LVar1)
                                CaseEq(1)
                                    Call(GetBattleVar, 5, LVar1)
                                CaseEq(2)
                                    Call(GetBattleVar, 6, LVar1)
                                CaseEq(3)
                                    Call(GetBattleVar, 7, LVar1)
                            EndSwitch
                            IfGe(LVar1, 2)
                                Call(RandInt, 1000, LVar0)
                                IfLt(LVar0, 300)
                                    Call(SetBattleVar, 1, 2)
                                    ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ChargedToss)
                                Else
                                    Call(SetBattleVar, 1, 1)
                                    ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ShellToss)
                                EndIf
                                Return
                            EndIf
                        EndCaseGroup
                        CaseEq(2)
                            ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ShellToss)
                            Return
                    EndSwitch
                    ExecWait(b_area_omo3_koopatrol_EVS_GetAvailableColumn)
                    IfEq(LVarA, -1)
                        ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ShellToss)
                        Return
                    EndIf
                    ExecWait(b_area_omo3_koopatrol_EVS_CountActiveSummoners)
                    Switch(LVar9)
                        CaseEq(1)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 400)
                                ExecWait(TTYD64_omo3_koopatrol_EVS_Move_SummonBackup)
                                Return
                            EndIf
                        CaseEq(2)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 200)
                                ExecWait(TTYD64_omo3_koopatrol_EVS_Move_SummonBackup)
                                Return
                            EndIf
                        CaseEq(3)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 100)
                                ExecWait(TTYD64_omo3_koopatrol_EVS_Move_SummonBackup)
                                Return
                            EndIf
                    EndSwitch
                    ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ShellToss)
                CaseEq(2)
                    ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ChargedToss)
            EndSwitch
        CaseEq(1)
            Call(SetBattleVar, 1, 1)
            ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ShellToss)
        CaseEq(2)
            ExecWait(TTYD64_omo3_koopatrol_EVS_Attack_ChargedToss)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_big_lantern_ghost_attackHeavyJump = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfGe(LVar0, 6)
        ExecWait(b_area_omo3_big_lantern_ghost_checkExtinguish)
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
    Call(SetBattleCamDist, 260)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x6D0006)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6D0001)
    Wait(8)
    Call(SetActorSounds, ACTOR_SELF, 2, 999, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6D0010)
            Thread
                Wait(10)
                Call(SetAnimation, ACTOR_SELF, 1, 0x6D0011)
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 893)
            Call(ResetActorSounds, ACTOR_SELF, 2)
            Sub(LVar0, 15)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6D0001)
            Sub(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 893)
            Wait(8)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(UseBattleCamPreset, 2)
            ExecWait(b_area_omo3_big_lantern_ghost_EVS_ReturnHome)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x6D0010)
    Thread
        Wait(7)
        Call(SetAnimation, ACTOR_SELF, 1, 0x6D0011)
    EndThread
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 5, 32)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(PlaySoundAtActor, ACTOR_SELF, 893)
            Call(ResetActorSounds, ACTOR_SELF, 2)
            Call(UseBattleCamPreset, 63)
            Call(SetBattleCamDist, 320)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(MoveBattleCamOver, 20)
            Call(SetBattleCamTargetingModes, -1, 1, 0)
            Thread
                Wait(5)
                Call(SetAnimation, ACTOR_SELF, 1, 0x6D0010)
            EndThread
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 893)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6D0001)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 893)
            Wait(8)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            ExecWait(b_area_omo3_big_lantern_ghost_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_pokey_EVS_SummonBackup = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x310004)
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
    Call(SummonEnemy, Ref(TTYD64_omo3_pokey_SummonFormation), 0)
    Set(LVarB, LVar0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Sub(LVar1, 80)
    Call(SetActorPos, LVarB, LVar0, LVar1, LVar2)
    ChildThread
        Call(PlayEffect_impl, 37, 2, LVar0, 0, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(UseIdleAnimation, LVarB, 0)
        Call(SetAnimation, LVarB, 1, 0x31000C)
        Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
        Call(SetActorJumpGravity, LVarB, Float(1.2001953125))
        Call(SetGoalPos, LVarB, LVar0, 0, LVar2)
        Call(JumpToGoal, LVarB, 20, 0, 1, 0)
        Wait(20)
        Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
        Call(SetAnimation, LVarB, 1, 0x310004)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x310004)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_big_lantern_ghost_attackLightBeam = {
    Call(SetActorVar, ACTOR_SELF, 11, 0)
    Call(SetActorVar, ACTOR_SELF, 12, 3)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 13)
    Call(SetBattleCamDist, 240)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 80)
    Set(LVar1, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x6D0006)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6D0001)
    Wait(20)
    Call(UseBattleCamPreset, 5)
    Call(SetBattleCamDist, 350)
    Call(SetBattleCamOffsetY, 35)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 8)
    Call(PlaySoundAtActor, ACTOR_SELF, 747)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6D000F)
    Call(GetActorVar, ACTOR_SELF, 0, LVar5)
    Call(SetActorVar, ACTOR_SELF, 0, 11)
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
    Call(GetActorVar, ACTOR_SELF, 4, LVar2)
    Add(LVar1, 10)
    Add(LVar2, 2)
    Thread
        Wait(1)
        Call(PlayEffect_impl, 53, 2, LVar0, LVar1, LVar2, Float(1.0), LVarB, 0, 0, 0, 0, 0, 0, 0)
        Wait(30)
        Call(RemoveEffect, LVarB)
    EndThread
    Thread
        Wait(1)
        Call(PlayEffect_impl, 79, 1, LVar0, LVar1, LVar2, Float(1.5), 30, 0, 0, 0, 0, 0, 0, 0)
    EndThread
    Wait(5)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
            Switch(LVarA)
                CaseEq(6)
                CaseDefault
                    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarD, 0, 0xFFFF, 0, 3, 32)
            EndSwitch
        EndCaseGroup
        CaseDefault
            Wait(2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyDamageTarget, ACTOR_SELF, LVarE, 0x2000000, 0xFFFF, 0, 3, 32)
            Wait(2)
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
            Switch(LVarA)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarA, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                CaseDefault
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarD, 0x2000000, 0xFFFF, 0, 3, 32)
            EndSwitch
    EndSwitch
    Wait(40)
    Call(SetActorVar, ACTOR_SELF, 0, LVar5)
    Thread
        Call(GetActorVar, ACTOR_SELF, 13, LVar0)
        Wait(10)
        Switch(LVar0)
            CaseEq(0)
                Call(PlaySoundAtActor, ACTOR_SELF, 938)
            CaseEq(1)
                Call(PlaySoundAtActor, ACTOR_SELF, 937)
            CaseEq(2)
                Call(PlaySoundAtActor, ACTOR_SELF, 936)
            CaseEq(3)
                Call(PlaySoundAtActor, ACTOR_SELF, 935)
        EndSwitch
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x6D0014)
    Wait(60)
    Call(UseBattleCamPreset, 2)
    ExecWait(b_area_omo3_big_lantern_ghost_EVS_ReturnHome)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_EVS_802250AC = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590007)
    Wait(10)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 4)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(3)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(2)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 8225)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590006)
    Wait(10)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 4, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(UseBattleCamPreset, 2)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, -300)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Thread
                Wait(15)
                Call(PlaySound, 8225)
            EndThread
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 500)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
            Wait(15)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(UseBattleCamPreset, 2)
    Thread
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyTestTarget, ACTOR_SELF, LVarB, 0, 0, 4, 16)
        Switch(LVarB)
            CaseOrEq(6)
            CaseOrEq(5)
                IfEq(LVarB, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
            EndCaseGroup
            CaseDefault
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 4, 32)
        EndSwitch
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
    EndThread
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 4, 32)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, -300)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Thread
        Wait(15)
        Call(PlaySound, 8225)
    EndThread
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 500)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
    Wait(15)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_red_shy_guy_EVS_Attack_Tackle = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0003)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetActorSounds, ACTOR_SELF, 2, 751, 0)
            Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
            Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0004)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0005)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(ResetAllActorSounds, ACTOR_SELF)
            Sub(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3B0004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0001)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Wait(3)
        Call(PlaySoundAtActor, ACTOR_SELF, 751)
    EndThread
    Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
    Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0004)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0005)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 15)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0001)
    Wait(8)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    ExecWait(b_area_omo3_red_shy_guy_EVS_ReturnHome)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_goomba_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260009)
            SetConst(LVar2, 0x26000A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260009)
            SetConst(LVar2, 0x26000A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26000A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26000E)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260007)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26000E)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260003)
            SetConst(LVar2, 0x260005)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_fuzzy_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Call(GetLastElement, LVar0)
            IfFlag(LVar0, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0013)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0008)
            EndIf
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0010)
            SetConst(LVar2, 0x2B0012)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0010)
            SetConst(LVar2, 0x2B0012)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0012)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0008)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0008)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0008)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0013)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0013)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0003)
            ExecWait(Ref(EVS_Enemy_HopHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0013)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0008)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            Call(GetLastElement, LVar0)
            IfFlag(LVar0, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0013)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0013)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0008)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0008)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0003)
            SetConst(LVar2, 0x2B0009)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0003)
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
EvtScript TTYD64_omo3_koopatrol_EVS_Move_SummonBackup = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(PlaySoundAtActor, ACTOR_SELF, 741)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590002)
    Wait(20)
    Loop(2)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590002)
        Wait(8)
        Call(PlaySoundAtActor, ACTOR_SELF, 741)
        Call(SetActorYaw, ACTOR_SELF, 180)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590009)
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590002)
        Wait(8)
        Call(PlaySoundAtActor, ACTOR_SELF, 741)
        Call(SetActorYaw, ACTOR_SELF, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590009)
        Wait(8)
    EndLoop
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 15)
    Thread
        Wait(8)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 8301)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x590016)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
    Call(SummonEnemy, Ref(TTYD64_omo3_koopatrol_BackupFormation), 0)
    Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Add(LVar1, 200)
    Call(SetActorPos, LVar0, LVar1, LVar2, LVar3)
    Call(SetGoalToIndex, LVar0, LVarA)
    Call(PlaySoundAtActor, LVar0, 8403)
    Call(SetActorSounds, LVar0, 0, 0, 0)
    Call(SetAnimation, LVar0, 1, 0x590006)
    Call(SetActorSpeed, LVar0, Float(6.0))
    Call(RunToGoal, LVar0, 0, 0)
    Call(SetAnimation, LVar0, 1, 0x590008)
    Wait(10)
    Call(SetAnimation, LVar0, 1, 0x590001)
    Call(GetActorPos, LVar0, LVar1, LVar2, LVar3)
    Call(ForceHomePos, LVar0, LVar1, LVar2, LVar3)
    Call(HPBarToHome, LVar0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar1)
    Switch(LVar1)
        CaseEq(0)
            Call(SetActorVar, LVar0, 1, 1)
        CaseEq(1)
            Call(SetActorVar, LVar0, 1, 2)
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 2, LVar1)
    Call(SetActorVar, LVar0, 2, LVar1)
    Switch(LVar1)
        CaseEq(0)
            Call(GetBattleVar, 4, LVar0)
            Add(LVar0, 1)
            Call(SetBattleVar, 4, LVar0)
        CaseEq(1)
            Call(GetBattleVar, 5, LVar0)
            Add(LVar0, 1)
            Call(SetBattleVar, 5, LVar0)
        CaseEq(2)
            Call(GetBattleVar, 6, LVar0)
            Add(LVar0, 1)
            Call(SetBattleVar, 6, LVar0)
        CaseEq(3)
            Call(GetBattleVar, 7, LVar0)
            Add(LVar0, 1)
            Call(SetBattleVar, 7, LVar0)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_koopatrol_EVS_Idle = {
    Label(0)
    Call(RandInt, 80, LVarA)
    Add(LVarA, 80)
    Loop(LVarA)
        Label(1)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        Call(GetActorVar, ACTOR_SELF, 3, LVar2)
        ExecWait(b_area_omo3_koopatrol_EVS_UpdateOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(1)
        EndIf
        IfFlag(LVar1, 0x235D000)
            Wait(1)
            Goto(1)
        EndIf
        IfEq(LVar2, 1)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_koopatrol_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_koopatrol_DefaultAnims))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_koopatrol_ToppledAnims))
    EndSwitch
    Loop(20)
        Label(2)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        Call(GetActorVar, ACTOR_SELF, 3, LVar2)
        ExecWait(b_area_omo3_koopatrol_EVS_UpdateOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(2)
        EndIf
        IfFlag(LVar1, 0x235D000)
            Wait(1)
            Goto(2)
        EndIf
        IfEq(LVar2, 1)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_koopatrol_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_koopatrol_DefaultAnims))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_koopatrol_ToppledAnims))
    EndSwitch
    Loop(80)
        Label(3)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        Call(GetActorVar, ACTOR_SELF, 3, LVar2)
        ExecWait(b_area_omo3_koopatrol_EVS_UpdateOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(3)
        EndIf
        IfFlag(LVar1, 0x235D000)
            Wait(1)
            Goto(3)
        EndIf
        IfEq(LVar2, 1)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_clubba_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 27)
        Set(LVar1, 0)
        Sub(LVar2, 6)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Wait(15)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x3A0002)
        Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetStatusFlags, ACTOR_SELF, LVar0)
        IfNotFlag(LVar0, 0x80000)
            Call(AddGoalPos, ACTOR_SELF, 27, 0, -6)
        Else
            Call(AddGoalPos, ACTOR_SELF, 10, 0, -6)
        EndIf
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x3A0001)
        Wait(10)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8389)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3A0008)
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                Wait(20)
            EndIf
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3A0002)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x3A0009)
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_SELF, 8389)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3A000A)
    Wait(2)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Thread
                Call(ShakeCam, 1, 0, 10, Float(1.5))
            EndThread
            Call(UseBattleCamPreset, 2)
            Wait(19)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3A0002)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_pokey_EVS_DecrementSize = {
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    Switch(LVarA)
        CaseEq(0)
            Call(SetActorVar, ACTOR_SELF, 1, 0x310005)
            Call(SetActorVar, ACTOR_SELF, 2, 0x310009)
            Call(SetActorVar, ACTOR_SELF, 3, 0x31000D)
            Call(SetActorVar, ACTOR_SELF, 4, 0x310012)
            Call(SetActorVar, ACTOR_SELF, 5, 0x310013)
            Call(SetActorVar, ACTOR_SELF, 6, 0x31001A)
            Call(SetActorVar, ACTOR_SELF, 7, 0x31001B)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_pokey_ThreePartAnims))
            Call(SetPartFlagBits, ACTOR_SELF, 2, 0x800000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20000, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x20000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x800000, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(SetActorSize, ACTOR_SELF, 62, -0xEE6B280)
            Call(SetPartSize, ACTOR_SELF, 1, 62, -0xEE6B280)
            Call(b_area_omo3_pokey_SetAbsoluteStatusOffsets, -15, 55, 10, 45)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 1, 0x310006)
            Call(SetActorVar, ACTOR_SELF, 2, 0x31000A)
            Call(SetActorVar, ACTOR_SELF, 3, 0x31000E)
            Call(SetActorVar, ACTOR_SELF, 4, 0x310014)
            Call(SetActorVar, ACTOR_SELF, 5, 0x310015)
            Call(SetActorVar, ACTOR_SELF, 6, 0x31001C)
            Call(SetActorVar, ACTOR_SELF, 7, 0x31001D)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_pokey_TwoPartAnims))
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x800000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x20000, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x20000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x800000, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 2)
            Call(SetActorSize, ACTOR_SELF, 44, -0xEE6B280)
            Call(SetPartSize, ACTOR_SELF, 1, 44, -0xEE6B280)
            Call(b_area_omo3_pokey_SetAbsoluteStatusOffsets, -15, 35, 10, 25)
        CaseEq(2)
            Call(SetActorVar, ACTOR_SELF, 1, 0x310007)
            Call(SetActorVar, ACTOR_SELF, 2, 0x31000B)
            Call(SetActorVar, ACTOR_SELF, 3, 0x31000F)
            Call(SetActorVar, ACTOR_SELF, 6, 0x31001E)
            Call(SetActorVar, ACTOR_SELF, 7, 0x31001F)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_pokey_OnePartAnims))
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x800000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x20000, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 5, 0x20000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 5, 0x800000, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 3)
            Call(SetActorSize, ACTOR_SELF, 26, -0xEE6B280)
            Call(SetPartSize, ACTOR_SELF, 1, 26, -0xEE6B280)
            Call(b_area_omo3_pokey_SetAbsoluteStatusOffsets, -15, 15, 10, 5)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_pokey_EVS_Pokey_Hit = {
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 6, Float(1.0), Float(1.0), Float(1.0))
    Else
        Call(SetPartScale, ACTOR_SELF, 6, Float(0.400390625), Float(0.400390625), Float(1.0))
    EndIf
    ExecWait(TTYD64_omo3_pokey_EVS_DecrementSize)
    SetConst(LVar0, 1)
    Call(GetLastEvent, ACTOR_SELF, LVar1)
    Switch(LVar1)
        CaseOrEq(14)
        CaseOrEq(36)
            Call(SetAnimation, ACTOR_SELF, 6, 0x310020)
            Call(GetActorVar, ACTOR_SELF, 6, LVar1)
        EndCaseGroup
        CaseDefault
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    ChildThread
        Wait(4)
        ExecWait(b_area_omo3_pokey_EVS_HitReactionBounce)
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
EvtScript TTYD64_omo3_pokey_EVS_KnockPartAway = {
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 6, Float(1.0), Float(1.0), Float(1.0))
    Else
        Call(SetPartScale, ACTOR_SELF, 6, Float(0.400390625), Float(0.400390625), Float(1.0))
    EndIf
    ExecWait(TTYD64_omo3_pokey_EVS_DecrementSize)
    SetConst(LVar0, 1)
    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    ChildThread
        Wait(4)
        ExecWait(b_area_omo3_pokey_EVS_HitReactionBounce)
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
EvtScript TTYD64_omo3_pokey_EVS_Pokey_ScareAway = {
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
EvtScript TTYD64_omo3_goomba_EVS_Idle = {
    Label(10)
    Call(RandInt, 80, LVar0)
    Add(LVar0, 80)
    Loop(LVar0)
        Label(0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(0)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_goomba_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_goomba_DefaultAnims))
    Loop(20)
        Label(1)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_goomba_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_goomba_DefaultAnims))
    Loop(80)
        Label(2)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(2)
        EndIf
        Wait(1)
    EndLoop
    Goto(10)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_hammer_bro_EVS_HammerSurge_Miss = {
    Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A0002)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A000C)
    Wait(4)
    Call(SetPartFlagBits, ACTOR_SELF, LVar0, 1, 0)
    Call(SetPartSounds, ACTOR_SELF, LVar0, 2, 0, 0)
    Call(PlaySoundAtPart, ACTOR_SELF, LVar0, 745)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Set(LVar2, 10)
    Call(RandInt, 60, LVar4)
    Set(LVar5, 30)
    Sub(LVar5, LVar4)
    Add(LVar1, LVar5)
    Call(SetPartJumpGravity, ACTOR_SELF, LVar0, Float(1.2998046875))
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 15, 1)
    Sub(LVar1, 50)
    Set(LVar2, 10)
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 20, 1)
    Sub(LVar1, 30)
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 10, 1)
    Sub(LVar1, 20)
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 5, 1)
    Call(SetPartFlagBits, ACTOR_SELF, LVar0, 1, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_hammer_bro_EVS_HammerSurge_Hit = {
    Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A0002)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A000C)
    Wait(4)
    Call(SetPartFlagBits, ACTOR_SELF, LVar0, 1, 0)
    Call(SetPartSounds, ACTOR_SELF, LVar0, 2, 0, 0)
    Call(PlaySoundAtPart, ACTOR_SELF, LVar0, 745)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Call(SetPartJumpGravity, ACTOR_SELF, LVar0, Float(1.2998046875))
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 15, 1)
    Sub(LVar1, 50)
    Set(LVar2, 10)
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 20, 1)
    Sub(LVar1, 30)
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 10, 1)
    Sub(LVar1, 20)
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 5, 1)
    Call(SetPartFlagBits, ACTOR_SELF, LVar0, 1, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_big_lantern_ghost_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo3_big_lantern_ghost_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo3_big_lantern_ghost_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo3_big_lantern_ghost_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_omo3_big_lantern_ghost_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 10)
    Call(SetActorVar, ACTOR_SELF, 0, 2)
    Call(SetActorVar, ACTOR_SELF, 1, 240)
    Call(SetActorVar, ACTOR_SELF, 7, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 0)
    Call(SetActorVar, ACTOR_SELF, 12, 0)
    Call(PlayEffect_impl, 60, 1, LVar0, LVar1, LVar2, Float(1.0), LVar0, 0, 0, 0, 0, 0, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 10, LVar0)
    Call(b_area_omo3_big_lantern_ghost_init_overlay)
    Exec(b_area_omo3_big_lantern_ghost_updateEffectThread)
    ExecWait(b_area_omo3_big_lantern_ghost_setGhostNoTarget)
    Wait(2)
    Call(SetActorVar, ACTOR_SELF, 13, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_big_lantern_ghost_EVS_TakeTurn = {
    Call(GetActorVar, ACTOR_SELF, 12, LVar0)
    IfGt(LVar0, 0)
        Sub(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 12, LVar0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 11, LVar0)
    Switch(LVar0)
        CaseEq(2)
            Call(GetActorVar, ACTOR_SELF, 12, LVar0)
            IfGt(LVar0, 0)
                Call(SetActorVar, ACTOR_SELF, 11, 0)
            EndIf
        CaseEq(1)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfLt(LVar0, 6)
                Call(SetActorVar, ACTOR_SELF, 11, 0)
            EndIf
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 11, LVar0)
    Switch(LVar0)
        CaseEq(2)
            ExecWait(TTYD64_omo3_big_lantern_ghost_attackLightBeam)
        CaseEq(1)
            ExecWait(b_area_omo3_big_lantern_ghost_extinguish)
        CaseDefault
            ExecWait(TTYD64_omo3_big_lantern_ghost_attackHeavyJump)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_EVS_8022BF5C = {
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Thread
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590007)
    EndThread
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_omo3_koopatrol_ChargedStatusTable))
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(TTYD64_omo3_Defense_8022FC0C))
    Call(SetActorVar, ACTOR_SELF, 0, 2)
    Call(SetActorVar, ACTOR_SELF, 3, 1)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_Anims_8022FB58))
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 1)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590005)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_pokey_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo3_pokey_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo3_pokey_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_omo3_pokey_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Call(SetActorVar, ACTOR_SELF, 9, LVar0)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0x310004)
    Call(SetActorVar, ACTOR_SELF, 2, 0x310008)
    Call(SetActorVar, ACTOR_SELF, 3, 0x31000C)
    Call(SetActorVar, ACTOR_SELF, 4, 0x310010)
    Call(SetActorVar, ACTOR_SELF, 5, 0x310011)
    Call(SetActorVar, ACTOR_SELF, 6, 0x310018)
    Call(SetActorVar, ACTOR_SELF, 7, 0x310019)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_koopatrol_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo3_koopatrol_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_omo3_koopatrol_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_omo3_koopatrol_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_omo3_koopatrol_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(GetIndexFromHome, ACTOR_SELF, LVar0)
    Call(SetActorVar, ACTOR_SELF, 2, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetBattleVar, 4, 0)
        CaseEq(1)
            Call(SetBattleVar, 5, 0)
        CaseEq(2)
            Call(SetBattleVar, 6, 0)
        CaseEq(3)
            Call(SetBattleVar, 7, 0)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_pokey_EVS_Pokey_SpinSmashHit = {
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
            ExecWait(TTYD64_omo3_pokey_EVS_KnockPartAway)
        CaseEq(1)
            ExecWait(TTYD64_omo3_pokey_EVS_KnockPartAway)
        CaseEq(2)
            ExecWait(TTYD64_omo3_pokey_EVS_KnockPartAway)
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
EvtScript TTYD64_omo3_EVS_8022CDB0 = {
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590001)
    Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_omo3_koopatrol_StatusTable))
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_omo3_koopatrol_DefenseTable))
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo3_koopatrol_DefaultAnims))
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_omo_01_EVS_PreBattle = {
    Call(SetSpriteShading, -1)
    Call(SetCamBGColor, 1, 0, 0, 0)
    Thread
        SetF(LVar0, Float(0.0))
        SetF(LVar1, Float(0.0))
        Loop(0)
            Call(RotateModel, 23, LVar1, 0, 0, 1)
            Call(RotateModel, 21, LVar0, 0, 0, 1)
            SubF(LVar0, Float(0.599609375))
            SubF(LVar1, Float(7.2001953125))
            Call(ClampAngleFloat, LVar0)
            Call(ClampAngleFloat, LVar1)
            Wait(1)
        EndLoop
    EndThread
    Exec(b_area_omo3_omo_01_EVS_UpdateRockingHorse)
    Return
    End
};
// clang-format on

Battle TTYD64_omo3_Formations[] = {
    { .name = "\323\303\260\253\363\306\351O\223",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_omo3_Formation_00,
      .stage = &b_area_omo3_omo_03,
      .onBattleStart = NULL },
    { .name = "\257\352\334\374\010\324\374\301x\223\011",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_omo3_Formation_01,
      .stage = &b_area_omo3_omo_04,
      .onBattleStart = NULL },
    { .name = "\257\352\334\374x\022\010\324\374\301x\223\011",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo3_Formation_02,
      .stage = &b_area_omo3_omo_04,
      .onBattleStart = NULL },
    { .name = "\254\334\363xDx\022\010\324\374\301x\223\011",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo3_Formation_03,
      .stage = &b_area_omo3_omo_04,
      .onBattleStart = NULL },
    { .name = "\301\347\355\334\363x\022\010\324\374\301x\223\011",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo3_Formation_04,
      .stage = &b_area_omo3_omo_04,
      .onBattleStart = NULL },
    { .name = "\301\347\355\334\363x\024\010\324\374\301x\223\011",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_omo3_Formation_05,
      .stage = &b_area_omo3_omo_04,
      .onBattleStart = NULL },
    { .name = "\317\363\336\374\326\355\271x\022\010\324\374\301x\223\011",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo3_Formation_06,
      .stage = &b_area_omo3_omo_04,
      .onBattleStart = NULL },
    { .name = "\317\363\336\374\326\355\271\010\324\374\301x\223\011",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_omo3_Formation_07,
      .stage = &b_area_omo3_omo_04,
      .onBattleStart = NULL },
    { .name = "\265\363\334x\022\010\324\374\301x\223\011",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo3_Formation_08,
      .stage = &b_area_omo3_omo_04,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263x\022\010\324\374\301x\223\011",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo3_Formation_09,
      .stage = &b_area_omo3_omo_04,
      .onBattleStart = NULL },
    { .name = "\330\244\333\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_omo3_Formation_0A,
      .stage = &TTYD64_omo3_omo_01,
      .onBattleStart = NULL },
    {},
};

ActorPartBlueprint TTYD64_omo3_hammer_bro_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -3, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo3_hammer_bro_DefaultAnims,
        .defenseTable = b_area_omo3_hammer_bro_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -3, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_omo3_hammer_bro_HammerAnims,
        .defenseTable = b_area_omo3_hammer_bro_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_omo3_hammer_bro_HammerAnims,
        .defenseTable = b_area_omo3_hammer_bro_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_omo3_hammer_bro_HammerAnims,
        .defenseTable = b_area_omo3_hammer_bro_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_omo3_hammer_bro_HammerAnims,
        .defenseTable = b_area_omo3_hammer_bro_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 6,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_omo3_hammer_bro_HammerAnims,
        .defenseTable = b_area_omo3_hammer_bro_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_omo3_pokey_ActorParts[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo3_pokey_FourPartAnims,
        .defenseTable = b_area_omo3_pokey_DefenseTable,
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
        .defenseTable = b_area_omo3_pokey_DefenseTable,
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
        .defenseTable = b_area_omo3_pokey_DefenseTable,
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
        .defenseTable = b_area_omo3_pokey_DefenseTable,
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
        .defenseTable = b_area_omo3_pokey_DefenseTable,
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
        .idleAnimations = b_area_omo3_pokey_ThrownPartAnims,
        .defenseTable = b_area_omo3_pokey_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_omo3_red_shy_guy_StatusTable[] = {
    1,  0, 2,  0, 6,  70, 9,  50, 7,  70, 4,  90, 3,  100, 11, 50, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0,   38, 1,  39, 0,  41, 0,  0,
};

s32 TTYD64_omo3_clubba_StatusTable[] = {
    1,  0, 2,  0, 6,  90, 9,  50, 7,  70, 4,  75, 3,  100, 11, 50, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 1, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0,   38, 1,  39, 0,  41, -1, 0,
};

s32 TTYD64_omo3_pokey_StatusTable[] = {
    1,  0, 2,  0, 6,  90, 9,  0, 7,  90, 4,  90, 3,  0, 11, 0, 5,  100, 10, 90, 8, 100,
    31, 0, 32, 0, 37, 0,  34, 0, 36, 0,  35, 0,  33, 0, 38, 0, 39, 0,   41, 0,  0,
};

s32 TTYD64_omo3_hammer_bro_StatusTable[] = {
    1,  0, 2,  0,  6,  50, 9,  60, 7,  50, 4,  70, 3,  0, 11, 80, 5,  70, 10, 70, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0,  39, 0,  41, -2, 0,
};

s32 TTYD64_omo3_koopatrol_StatusTable[] = {
    1,  0, 2,  0,  6,  50, 9,  60, 7,  60, 4,  75, 3,  0, 11, 80, 5,  75, 10, 70, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

// clang-format off
EvtScript TTYD64_omo3_hammer_bro_EVS_TakeTurn = {
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
    MulF(LVar0, Float(100.0))
    DivF(LVar0, LVar1)
    IfGt(LVar0, 34)
        ExecWait(TTYD64_omo3_hammer_bro_EVS_Attack_HammerThrow)
    Else
        ExecWait(TTYD64_omo3_hammer_bro_EVS_Attack_HammerSurge)
    EndIf
    Return
    End
};
// clang-format on

FormationRow TTYD64_omo3_Formation_05[] = {
    { .actor = &TTYD64_omo3_fuzzy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
    { .actor = &TTYD64_omo3_fuzzy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
    { .actor = &TTYD64_omo3_fuzzy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
    { .actor = &TTYD64_omo3_fuzzy,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
};

// clang-format off
EvtScript TTYD64_omo3_hammer_bro_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo3_hammer_bro_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo3_hammer_bro_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo3_hammer_bro_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo3_red_shy_guy_EVS_TakeTurn = {
    Call(RandInt, 1, LVar0)
    IfEq(LVar0, 0)
        ExecWait(TTYD64_omo3_red_shy_guy_EVS_Attack_Tackle)
    Else
        ExecWait(TTYD64_omo3_red_shy_guy_EVS_Attack_Vault)
    EndIf
    Return
    End
};
// clang-format on

s32 TTYD64_omo3_big_lantern_ghost_DefaultAnims[] = {
    1,        0x6D0001, 7,        0x6D0000, 6,        0x6D000C, 9,        0x6D0001, 8,        0x6D0000, 11,
    0x6D0000, 5,        0x6D0000, 5,        0x6D0000, 4,        0x6D000D, 3,        0x6D000D, 0,
};

StageListRow TTYD64_omo3_Stages[] = {
    { .name = "omo_01", .stage = &TTYD64_omo3_omo_01 },   { .name = "omo_02", .stage = &b_area_omo3_omo_02 },
    { .name = "omo_03", .stage = &b_area_omo3_omo_03 },   { .name = "omo_03b", .stage = &b_area_omo3_omo_03b },
    { .name = "omo_04", .stage = &b_area_omo3_omo_04 },   { .name = "omo_05", .stage = &b_area_omo3_omo_05 },
    { .name = "omo_05b", .stage = &b_area_omo3_omo_05b }, { .name = "omo_06", .stage = &b_area_omo3_omo_06 },
    { .name = "omo_07", .stage = &b_area_omo3_omo_07 },   {},
};

s32 TTYD64_omo3_koopatrol_ShuffleAnims[] = {
    1,  0x590003, 7, 0x590000, 6, 0x590011, 9, 0x590003, 8, 0x590000,
    11, 0x590003, 5, 0x590000, 4, 0x590013, 3, 0x590013, 0,
};

s32 TTYD64_omo3_hammer_bro_DefaultAnims[] = {
    1,  0x5A0002, 7, 0x5A0000, 6, 0x5A0011, 9, 0x5A0002, 8, 0x5A0000,
    11, 0x5A0002, 5, 0x5A0000, 4, 0x5A0012, 3, 0x5A0012, 0,
};

// clang-format off
EvtScript TTYD64_omo3_red_shy_guy_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo3_red_shy_guy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo3_red_shy_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo3_red_shy_guy_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_omo3_koopatrol_DefaultAnims[] = {
    1,  0x590001, 7, 0x590000, 6, 0x590011, 9, 0x590001, 8, 0x590000,
    11, 0x590001, 5, 0x590000, 4, 0x590013, 3, 0x590013, 0,
};

s32 TTYD64_omo3_fuzzy_DefaultAnims[] = {
    1,  0x2B0001, 7, 0x2B0000, 6, 0x2B000E, 9, 0x2B0001, 8, 0x2B0000,
    11, 0x2B0001, 5, 0x2B0000, 4, 0x2B000F, 3, 0x2B000F, 0,
};

s32 TTYD64_omo3_clubba_DefaultAnims[] = {
    1,  0x3A0001, 7, 0x3A0000, 6, 0x3A0003, 9, 0x3A0001, 8, 0x3A0000,
    11, 0x3A0001, 5, 0x3A0000, 4, 0x3A0005, 3, 0x3A0005, 0,
};

s32 TTYD64_omo3_goomba_ShuffleAnims[] = {
    1,  0x260003, 7, 0x260000, 6, 0x260008, 9, 0x260001, 8, 0x260000,
    11, 0x260003, 5, 0x260000, 4, 0x260007, 3, 0x260007, 0,
};

s32 TTYD64_omo3_koopatrol_ToppledAnims[] = {
    1,  0x59000F, 7, 0x590010, 6, 0x590012, 9, 0x59000F, 8, 0x590010,
    11, 0x59000F, 5, 0x590010, 4, 0x590014, 3, 0x590014, 0,
};

// clang-format off
EvtScript TTYD64_omo3_fuzzy_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo3_fuzzy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo3_fuzzy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_omo3_fuzzy_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_omo3_koopatrol_ChargedAnims[] = {
    1,  0x590006, 7, 0x590006, 6, 0x590006, 9, 0x590006, 8, 0x590006,
    11, 0x590006, 5, 0x590006, 4, 0x590006, 3, 0x590006, 0,
};

// clang-format off
EvtScript TTYD64_omo3_clubba_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo3_clubba_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo3_clubba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo3_clubba_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_omo3_goomba_DefaultAnims[] = {
    1,  0x260001, 7, 0x260000, 6, 0x260008, 9, 0x260001, 8, 0x260000,
    11, 0x260001, 5, 0x260000, 4, 0x260007, 3, 0x260007, 0,
};

s32 TTYD64_omo3_red_shy_guy_DefaultAnims[] = {
    1,  0x3B0001, 7, 0x3B0000, 6, 0x3B0012, 9, 0x3B0001, 8, 0x3B0000,
    11, 0x3B0001, 5, 0x3B0000, 4, 0x3B0013, 3, 0x3B0013, 0,
};

// clang-format off
EvtScript TTYD64_omo3_goomba_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo3_goomba_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_omo3_goomba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_omo3_goomba_EVS_HandleEvent))
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_omo3_big_lantern_ghost_ActorParts[] = {
    {
        .flags = 0x820000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 54 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo3_big_lantern_ghost_DefaultAnims,
        .defenseTable = b_area_omo3_big_lantern_ghost_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x2001,
        .index = 2,
        .posOffset = { -40, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo3_big_lantern_ghost_DefaultAnims,
        .defenseTable = b_area_omo3_big_lantern_ghost_defenseTable2,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -9 },
        .overrideNameMsg = 0x29007F,
    },
};

s32 TTYD64_omo3_pokey_ThreePartAnims[] = {
    1, 0x310005, 7, 0x310001, 6, 0x310026, 8, 0x310001, 5, 0x310001, 4, 0x310022, 3, 0x310022, 0,
};

s32 TTYD64_omo3_pokey_OnePartAnims[] = {
    1, 0x310007, 7, 0x310003, 6, 0x310028, 8, 0x310003, 5, 0x310003, 4, 0x310024, 3, 0x310024, 0,
};

s32 TTYD64_omo3_pokey_FourPartAnims[] = {
    1, 0x310004, 7, 0x310000, 6, 0x310025, 8, 0x310000, 5, 0x310000, 4, 0x310021, 3, 0x310021, 0,
};

s32 TTYD64_omo3_pokey_TwoPartAnims[] = {
    1, 0x310006, 7, 0x310002, 6, 0x310027, 8, 0x310002, 5, 0x310002, 4, 0x310023, 3, 0x310023, 0,
};

FormationRow TTYD64_omo3_Formation_04[] = {
    { .actor = &TTYD64_omo3_fuzzy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
    { .actor = &TTYD64_omo3_fuzzy,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
};

FormationRow TTYD64_omo3_Formation_02[] = {
    { .actor = &TTYD64_omo3_goomba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GOOMBA },
    { .actor = &TTYD64_omo3_goomba,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GOOMBA },
};

FormationRow TTYD64_omo3_Formation_03[] = {
    { .actor = &TTYD64_omo3_clubba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
    { .actor = &TTYD64_omo3_clubba,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
};

FormationRow TTYD64_omo3_Formation_08[] = {
    { .actor = &TTYD64_omo3_pokey_8022F4A4,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 1,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_omo3_pokey_8022F4A4,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 1,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
};

FormationRow TTYD64_omo3_Formation_09[] = {
    { .actor = &TTYD64_omo3_koopatrol,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_omo3_koopatrol,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_omo3_Formation_06[] = {
    { .actor = &TTYD64_omo3_hammer_bro,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_omo3_hammer_bro,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
};

ActorBlueprint TTYD64_omo3_red_shy_guy = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x1F,
    .level = 14,
    .partCount = 1,
    .partsData = TTYD64_omo3_red_shy_guy_ActorParts,
    .initScript = &TTYD64_omo3_red_shy_guy_EVS_Init,
    .statusTable = TTYD64_omo3_red_shy_guy_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 85,
    .hurricaneChance = 80,
    .spookChance = 80,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 28, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

Stage TTYD64_omo3_omo_01 = {
    .texture = "omo_tex",
    .shape = "omo_bt01_shape",
    .hit = "omo_bt01_hit",
    .preBattle = &TTYD64_omo3_omo_01_EVS_PreBattle,
    .postBattle = &b_area_omo3_omo_01_EVS_PostBattle,
    .bg = "omo_bg",
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_omo3_koopatrol = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x4C,
    .level = 25,
    .partCount = 1,
    .partsData = TTYD64_omo3_koopatrol_ActorParts,
    .initScript = &TTYD64_omo3_koopatrol_EVS_Init,
    .statusTable = TTYD64_omo3_koopatrol_StatusTable,
    .escapeChance = 50,
    .airLiftChance = 75,
    .hurricaneChance = 65,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 2,
    .size = { 32, 42 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 32 },
    .statusTextOffset = { 5, 32 },
};

ActorBlueprint TTYD64_omo3_clubba = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x1E,
    .level = 13,
    .partCount = 1,
    .partsData = TTYD64_omo3_clubba_ActorParts,
    .initScript = &TTYD64_omo3_clubba_EVS_Init,
    .statusTable = TTYD64_omo3_clubba_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 60,
    .hurricaneChance = 70,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 1,
    .size = { 42, 42 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 35 },
};

ActorBlueprint TTYD64_omo3_fuzzy = {
    .flags = 0x0,
    .maxHP = 3,
    .type = 0x0A,
    .level = 6,
    .partCount = 1,
    .partsData = TTYD64_omo3_fuzzy_ActorParts,
    .initScript = &TTYD64_omo3_fuzzy_EVS_Init,
    .statusTable = b_area_omo3_fuzzy_StatusTable,
    .escapeChance = 50,
    .airLiftChance = 95,
    .hurricaneChance = 95,
    .spookChance = 95,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 33, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_omo3_pokey = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x14,
    .level = 9,
    .partCount = 6,
    .partsData = TTYD64_omo3_pokey_ActorParts,
    .initScript = &TTYD64_omo3_pokey_EVS_Init,
    .statusTable = TTYD64_omo3_pokey_StatusTable,
    .escapeChance = 70,
    .airLiftChance = 90,
    .hurricaneChance = 85,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 24, 80 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 75 },
    .statusTextOffset = { 10, 65 },
};

ActorBlueprint TTYD64_omo3_pokey_8022F4A4 = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x14,
    .level = 9,
    .partCount = 6,
    .partsData = TTYD64_omo3_pokey_ActorParts,
    .initScript = &TTYD64_omo3_pokey_EVS_Init,
    .statusTable = TTYD64_omo3_pokey_StatusTable,
    .escapeChance = 70,
    .airLiftChance = 90,
    .hurricaneChance = 85,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 24, 80 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 75 },
    .statusTextOffset = { 10, 65 },
};

ActorBlueprint TTYD64_omo3_big_lantern_ghost = {
    .flags = 0x0,
    .maxHP = 40,
    .type = 0xB1,
    .level = 42,
    .partCount = 2,
    .partsData = TTYD64_omo3_big_lantern_ghost_ActorParts,
    .initScript = &TTYD64_omo3_big_lantern_ghost_EVS_Init,
    .statusTable = b_area_omo3_big_lantern_ghost_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 86, 60 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -30, 55 },
    .statusTextOffset = { 20, 45 },
};

ActorBlueprint TTYD64_omo3_hammer_bro = {
    .flags = 0x0,
    .maxHP = 12,
    .type = 0x4B,
    .level = 27,
    .partCount = 6,
    .partsData = TTYD64_omo3_hammer_bro_ActorParts,
    .initScript = &TTYD64_omo3_hammer_bro_EVS_Init,
    .statusTable = TTYD64_omo3_hammer_bro_StatusTable,
    .escapeChance = 30,
    .airLiftChance = 75,
    .hurricaneChance = 60,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 28, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 35 },
};

ActorBlueprint TTYD64_omo3_goomba = {
    .flags = 0x0,
    .maxHP = 2,
    .type = 0x07,
    .level = 5,
    .partCount = 1,
    .partsData = TTYD64_omo3_goomba_ActorParts,
    .initScript = &TTYD64_omo3_goomba_EVS_Init,
    .statusTable = b_area_omo3_goomba_StatusTable,
    .escapeChance = 90,
    .airLiftChance = 100,
    .hurricaneChance = 90,
    .spookChance = 100,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 24, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_omo3_koopatrol_8022F5E4 = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x4C,
    .level = 25,
    .partCount = 1,
    .partsData = TTYD64_omo3_koopatrol_ActorParts,
    .initScript = &TTYD64_omo3_koopatrol_EVS_Init,
    .statusTable = TTYD64_omo3_koopatrol_StatusTable,
    .escapeChance = 50,
    .airLiftChance = 75,
    .hurricaneChance = 65,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 2,
    .size = { 32, 42 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 32 },
    .statusTextOffset = { 5, 32 },
};

ActorPartBlueprint TTYD64_omo3_clubba_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -12, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo3_clubba_DefaultAnims,
        .defenseTable = b_area_omo3_clubba_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 8, -3 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_omo3_fuzzy_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo3_fuzzy_DefaultAnims,
        .defenseTable = b_area_omo3_fuzzy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_omo3_goomba_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo3_goomba_DefaultAnims,
        .defenseTable = b_area_omo3_goomba_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_omo3_koopatrol_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo3_koopatrol_DefaultAnims,
        .defenseTable = b_area_omo3_koopatrol_DefenseTable,
        .eventFlags = 0x1010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_omo3_red_shy_guy_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo3_red_shy_guy_DefaultAnims,
        .defenseTable = b_area_omo3_red_shy_guy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_omo3_Formation_0A[] = {
    { .actor = &TTYD64_omo3_red_shy_guy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_omo3_Formation_00[] = {
    { .actor = &TTYD64_omo3_big_lantern_ghost,
      .home = { .vec = &b_area_omo3_big_lantern_ghost_pos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_omo3_Formation_01[] = {
    { .actor = &TTYD64_omo3_goomba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GOOMBA },
};

FormationRow TTYD64_omo3_Formation_07[] = {
    { .actor = &TTYD64_omo3_hammer_bro,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
};

FormationRow TTYD64_omo3_pokey_SummonFormation[] = {
    { .actor = &TTYD64_omo3_pokey,
      .home = { .vec = &b_area_omo3_pokey_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_omo3_koopatrol_BackupFormation[] = {
    { .actor = &TTYD64_omo3_koopatrol_8022F5E4,
      .home = { .vec = &b_area_omo3_koopatrol_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

s32 TTYD64_omo3_Anims_8022FB58[] = {
    1,
    0x590005,
    0,
};

s32 TTYD64_omo3_Defense_8022FC0C[] = {
    1,
    99,
    0,
};

void TTYD64_InstallBattles_omo3(void) {
    Mod_SetBattleList("TTYD64", 18, TTYD64_omo3_Formations);
    Mod_SetStageList("TTYD64", 18, TTYD64_omo3_Stages);
}
