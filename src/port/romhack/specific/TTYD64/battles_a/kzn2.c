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
#include "port/romhack/specific/TTYD64/battles_a/battles_a.h"
#include "port/patches/Patches.h"

API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(CancelEnemyTurn);
API_CALLABLE(ClearStatusEffects);
API_CALLABLE(CreateNpc);
API_CALLABLE(DeleteAnimatedModel);
API_CALLABLE(DropStarPoints);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnableModel);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyToGoal);
API_CALLABLE(ForceHomePos);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetAnimatedModelRootPosition);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetEnemyMaxHP);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastDamage);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetPartOffset);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HideHealthBar);
API_CALLABLE(LoadAnimatedModel);
API_CALLABLE(LoadBattleDmaData);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(OverrideBattleDmaDest);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlayModelAnimation);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActor);
API_CALLABLE(RemoveEffect);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorType);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetAnimatedModelRootPosition);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetAnimatorFlags);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetDefenseTable);
API_CALLABLE(SetEnemyHP);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetNpcYaw);
API_CALLABLE(SetPartEventBits);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartImmunityBits);
API_CALLABLE(ShakeCam);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(b_area_kzn2_lava_bud_SetPetitFlameSize);
API_CALLABLE(b_area_kzn2_lava_piranha_CreateVineRenderer);
API_CALLABLE(b_area_kzn2_lava_piranha_GetSinkPosLavaBud);
API_CALLABLE(b_area_kzn2_lava_piranha_GetSinkPosLavaPiranha);
API_CALLABLE(b_area_kzn2_lava_piranha_ManageFakeoutMusic);
API_CALLABLE(b_area_kzn2_lava_piranha_StartRumbleWithParams);
API_CALLABLE(b_area_kzn2_petit_piranha_SetFlamePosX);
API_CALLABLE(b_area_kzn2_petit_piranha_SetFlameScaleH);
extern Stage b_area_kzn2_kzn_05;
extern ActorPartBlueprint b_area_kzn2_lava_bud_ActorParts[];
extern s32 b_area_kzn2_lava_bud_FieryAnims[];
extern s32 b_area_kzn2_lava_bud_FieryDefense[];
extern FormationRow b_area_kzn2_lava_bud_PetitBombFormation[];
extern s32 b_area_kzn2_lava_bud_StatusTable[];
extern s32 b_area_kzn2_lava_bud_StunnedAnims[];
extern s32 b_area_kzn2_lava_bud_StunnedDefense[];
extern Vec3i b_area_kzn2_lava_bud_SummonPos;
extern ActorPartBlueprint b_area_kzn2_lava_piranha_ActorParts[];
extern u8 b_area_kzn2_lava_piranha_AnimModel_ExtraVine[];
extern u8 b_area_kzn2_lava_piranha_AnimModel_MainHeadVine[];
extern u8 b_area_kzn2_lava_piranha_AnimModel_SideHeadVine[];
extern EvtScript b_area_kzn2_lava_piranha_EVS_HandlePhase;
extern EvtScript b_area_kzn2_lava_piranha_EVS_Ignite;
extern EvtScript b_area_kzn2_lava_piranha_EVS_InitVines;
extern EvtScript b_area_kzn2_lava_piranha_EVS_RemovePetitPiranha;
extern s32 b_area_kzn2_lava_piranha_FieryAnims[];
extern s32 b_area_kzn2_lava_piranha_FieryDefense[];
extern s32 b_area_kzn2_lava_piranha_StatusTable[];
extern s32 b_area_kzn2_lava_piranha_StunnedAnims[];
extern s32 b_area_kzn2_lava_piranha_StunnedDefense[];
extern Vec3i b_area_kzn2_lava_piranha_SummonPos;
extern u8 b_area_kzn2_lava_piranha_anim1[];
extern u8 b_area_kzn2_lava_piranha_anim1_8021A364[];
extern Vec3i b_area_kzn2_lava_piranha_pos;
extern ActorPartBlueprint b_area_kzn2_petit_piranha_ActorParts[];
extern EvtScript b_area_kzn2_petit_piranha_EVS_Death;
extern EvtScript b_area_kzn2_petit_piranha_EVS_HandleEvent;
extern EvtScript b_area_kzn2_petit_piranha_EVS_Idle;
extern s32 b_area_kzn2_petit_piranha_StatusTable[];
extern Vec3i b_area_kzn2_petit_piranha_pos1;
extern Vec3i b_area_kzn2_petit_piranha_pos2;
extern ActorBlueprint TTYD64_kzn2_lava_piranha;
extern EvtScript TTYD64_kzn2_lava_piranha_EVS_Init;
extern EvtScript TTYD64_kzn2_lava_piranha_EVS_Idle;
extern EvtScript TTYD64_kzn2_lava_piranha_EVS_HandleEvent;
extern EvtScript TTYD64_kzn2_lava_piranha_EVS_BurnHit;
extern EvtScript TTYD64_kzn2_lava_piranha_EVS_TakeTurn;
extern EvtScript TTYD64_kzn2_lava_piranha_EVS_Attack_SpitFire;
extern EvtScript TTYD64_kzn2_lava_piranha_EVS_Death;
extern EvtScript TTYD64_kzn2_lava_piranha_EVS_ComboHit;
extern EvtScript TTYD64_kzn2_lava_piranha_EVS_Hit;
extern EvtScript TTYD64_kzn2_lava_piranha_EVS_Hit_Inner;
extern EvtScript TTYD64_kzn2_lava_piranha_EVS_PlayIdleAnimation;
extern ActorBlueprint TTYD64_kzn2_petit_piranha;
extern EvtScript TTYD64_kzn2_petit_piranha_EVS_Init;
extern EvtScript TTYD64_kzn2_petit_piranha_EVS_TakeTurn;
extern ActorBlueprint TTYD64_kzn2_lava_bud;
extern EvtScript TTYD64_kzn2_lava_bud_EVS_Init;
extern EvtScript TTYD64_kzn2_lava_bud_EVS_Idle;
extern EvtScript TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine;
extern EvtScript TTYD64_kzn2_lava_bud_EVS_HandleEvent;
extern EvtScript TTYD64_kzn2_lava_bud_EVS_BurnHit;
extern EvtScript TTYD64_kzn2_lava_bud_EVS_TakeTurn;
extern EvtScript TTYD64_kzn2_lava_bud_EVS_PlayIdleAnimation;
extern EvtScript TTYD64_kzn2_lava_bud_EVS_Move_SummonPetit;
extern EvtScript TTYD64_kzn2_lava_bud_EVS_Death;
extern EvtScript TTYD64_kzn2_lava_bud_EVS_ComboHit;
extern EvtScript TTYD64_kzn2_lava_bud_EVS_Hit;
extern EvtScript TTYD64_kzn2_lava_bud_EVS_Attack_SpitPetit;
extern EvtScript TTYD64_kzn2_lava_piranha_EVS_Attack_FireBreath;
extern FormationRow TTYD64_kzn2_lava_piranha_LeftBudFormation[];
extern FormationRow TTYD64_kzn2_lava_piranha_RightBudFormation[];
extern FormationRow TTYD64_kzn2_lava_bud_LeftPetitFormation[];
extern FormationRow TTYD64_kzn2_lava_bud_RightPetitFormation[];
extern FormationRow TTYD64_kzn2_Formation_00[];
extern FormationRow TTYD64_kzn2_Formation_01[];
extern Battle TTYD64_kzn2_Formations[];

static Bytecode TTYD64_kzn2_lava_piranha_unusedArray[64];
static Bytecode TTYD64_kzn2_lava_bud_unusedArray[64];

ActorBlueprint TTYD64_kzn2_lava_piranha = {
    .flags = 0x0,
    .maxHP = 40,
    .type = 0xB3,
    .level = 45,
    .partCount = 2,
    .partsData = b_area_kzn2_lava_piranha_ActorParts,
    .initScript = &TTYD64_kzn2_lava_piranha_EVS_Init,
    .statusTable = b_area_kzn2_lava_piranha_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 70,
    .coinReward = 0,
    .size = { 50, 50 },
    .healthBarOffset = { 20, -10 },
    .statusIconOffset = { 5, 45 },
    .statusTextOffset = { 30, 47 },
};

// clang-format off
EvtScript TTYD64_kzn2_lava_piranha_EVS_Init = {
    UseArray(Ref(TTYD64_kzn2_lava_piranha_unusedArray))
    Call(EnableGroup, 23, 1)
    Call(EnableGroup, 28, 0)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 0)
    Call(SetActorVar, ACTOR_SELF, 13, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Set(LVar0, 30)
    Call(SetActorVar, ACTOR_SELF, 13, LVar0)
    Call(SetActorVar, ACTOR_SELF, 7, 0x790003)
    Call(SetActorVar, ACTOR_SELF, 8, 0x790009)
    Call(ForceHomePos, ACTOR_SELF, 61, 61, 0)
    Call(LoadAnimatedModel, 0, Ref(b_area_kzn2_lava_piranha_AnimModel_MainHeadVine))
    Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
    Call(LoadBattleDmaData, 0)
    Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
    Call(SetAnimatedModelRootPosition, 0, 0, 0, 0)
    Call(SetAnimatorFlags, 0, 128, 1)
    Call(LoadAnimatedModel, 1, Ref(b_area_kzn2_lava_piranha_AnimModel_SideHeadVine))
    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
    Call(LoadBattleDmaData, 31)
    Call(PlayModelAnimation, 1, (Bytecode) VINE_1_BASE)
    Call(SetAnimatedModelRootPosition, 1, 0, 0, 0)
    Call(SetAnimatorFlags, 1, 128, 1)
    Call(LoadAnimatedModel, 2, Ref(b_area_kzn2_lava_piranha_AnimModel_SideHeadVine))
    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
    Call(LoadBattleDmaData, 31)
    Call(PlayModelAnimation, 2, (Bytecode) VINE_2_BASE)
    Call(SetAnimatedModelRootPosition, 2, 50, 14, 20)
    Call(SetAnimatorFlags, 2, 128, 1)
    Call(LoadAnimatedModel, 3, Ref(b_area_kzn2_lava_piranha_AnimModel_ExtraVine))
    Call(OverrideBattleDmaDest, (Bytecode) VINE_3_BASE)
    Call(LoadBattleDmaData, 34)
    Call(PlayModelAnimation, 3, (Bytecode) VINE_3_BASE)
    Call(SetAnimatedModelRootPosition, 3, 0, 0, 3)
    Call(SetAnimatorFlags, 3, 128, 1)
    Call(SummonEnemy, Ref(TTYD64_kzn2_lava_piranha_LeftBudFormation), 0)
    Call(SummonEnemy, Ref(TTYD64_kzn2_lava_piranha_RightBudFormation), 0)
    Wait(2)
    Exec(b_area_kzn2_lava_piranha_EVS_InitVines)
    Call(CreateNpc, 0, 0xB70000)
    Call(SetNpcYaw, 0, 90)
    Call(SetNpcPos, 0, -300, 0, 0)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kzn2_lava_piranha_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_kzn2_lava_piranha_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kzn2_lava_piranha_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kzn2_lava_piranha_EVS_HandlePhase))
    Call(ForceHomePos, 513, 57, 57, 0)
    Call(ForceHomePos, 514, 107, 71, 20)
    Call(HPBarToHome, 513)
    Call(HPBarToHome, 514)
    Call(b_area_kzn2_lava_piranha_CreateVineRenderer)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_piranha_EVS_Idle = {
    Label(0)
    Call(GetActorHP, ACTOR_SELF, LVar0)
    IfEq(LVar0, 0)
        Goto(99)
    EndIf
    Call(GetActorVar, 512, 0, LVar0)
    IfEq(LVar0, 0)
        Goto(99)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    IfNe(LVar0, 0)
        Goto(99)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 13, LVar0)
    Sub(LVar0, 1)
    Call(SetActorVar, ACTOR_SELF, 13, LVar0)
    IfNe(LVar0, 0)
        Goto(99)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 12, LVar0)
    Add(LVar0, 1)
    IfGe(LVar0, 3)
        Set(LVar0, 0)
    EndIf
    Set(LVar0, 30)
    Call(SetActorVar, ACTOR_SELF, 13, LVar0)
    Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
    Call(LoadBattleDmaData, 1)
    Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
    Label(99)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_piranha_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetAnimatorFlags, 0, 0x40000, 0)
    Call(GetLastElement, LVarE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(56)
        CaseEq(9)
            ExecWait(TTYD64_kzn2_lava_piranha_EVS_ComboHit)
            ExecWait(TTYD64_kzn2_lava_piranha_EVS_PlayIdleAnimation)
        CaseEq(10)
            ExecWait(TTYD64_kzn2_lava_piranha_EVS_Hit)
            ExecWait(TTYD64_kzn2_lava_piranha_EVS_PlayIdleAnimation)
        CaseEq(32)
            ExecWait(TTYD64_kzn2_lava_piranha_EVS_Death)
            Return
        CaseEq(14)
            IfFlag(LVarE, 2)
                ExecWait(TTYD64_kzn2_lava_piranha_EVS_BurnHit)
            Else
                ExecWait(TTYD64_kzn2_lava_piranha_EVS_Hit)
                ExecWait(TTYD64_kzn2_lava_piranha_EVS_PlayIdleAnimation)
            EndIf
        CaseEq(36)
            ExecWait(TTYD64_kzn2_lava_piranha_EVS_Death)
            Return
        CaseEq(11)
            ExecWait(TTYD64_kzn2_lava_piranha_EVS_Hit)
            ExecWait(TTYD64_kzn2_lava_piranha_EVS_PlayIdleAnimation)
        CaseEq(33)
            ExecWait(TTYD64_kzn2_lava_piranha_EVS_Death)
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x790009)
            ExecWait(Ref(EVS_Enemy_ShockHit))
        CaseEq(38)
            ExecWait(TTYD64_kzn2_lava_piranha_EVS_Death)
            Return
        CaseEq(23)
            IfNotFlag(LVarE, 2)
                ExecWait(TTYD64_kzn2_lava_piranha_EVS_ComboHit)
                ExecWait(TTYD64_kzn2_lava_piranha_EVS_PlayIdleAnimation)
            EndIf
        CaseEq(25)
            IfNotFlag(LVarE, 2)
                ExecWait(TTYD64_kzn2_lava_piranha_EVS_Hit)
                ExecWait(TTYD64_kzn2_lava_piranha_EVS_PlayIdleAnimation)
            EndIf
        CaseEq(31)
        CaseEq(27)
        CaseEq(53)
        CaseEq(49)
            Call(SetAnimatorFlags, 0, 0x40000, 0)
        CaseEq(48)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x790009)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(1000)
        CaseDefault
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Call(ForceHomePos, ACTOR_SELF, 61, 61, 0)
    Else
        Call(GetActorVar, ACTOR_SELF, 5, LVar1)
        IfEq(LVar1, 1)
            Call(ForceHomePos, ACTOR_SELF, 61, 61, 0)
        Else
            Call(ForceHomePos, ACTOR_SELF, 83, 67, 0)
        EndIf
    EndIf
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x200000)
        Call(SetAnimatorFlags, 0, 0x40000, 1)
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_piranha_EVS_BurnHit = {
    Thread
        Wait(1)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        IfEq(LVar0, 0)
            Goto(10)
        EndIf
        Call(GetActorVar, ACTOR_SELF, 5, LVar2)
        IfEq(LVar2, 1)
            Goto(10)
        EndIf
        Set(LVar0, 512)
        ExecWait(b_area_kzn2_lava_piranha_EVS_Ignite)
        Label(10)
    EndThread
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfNe(LVar0, 0)
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        IfEq(LVar0, 0)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
            Call(LoadBattleDmaData, 14)
            Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
            Call(SetActorVar, ACTOR_SELF, 7, 0x790003)
            Call(SetActorVar, ACTOR_SELF, 8, 0x790009)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_kzn2_lava_piranha_FieryAnims))
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kzn2_lava_piranha_FieryDefense))
            Call(SetDefenseTable, ACTOR_SELF, 2, Ref(b_area_kzn2_lava_piranha_FieryDefense))
            Thread
                Wait(14)
                Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                Call(LoadBattleDmaData, 0)
                Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
            EndThread
        EndIf
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_piranha_EVS_TakeTurn = {
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x400000)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_kzn2_lava_piranha_EVS_Attack_SpitFire)
        CaseDefault
            Call(GetActorVar, ACTOR_SELF, 5, LVar0)
            IfEq(LVar0, 1)
                ExecWait(TTYD64_kzn2_lava_piranha_EVS_Attack_FireBreath)
            Else
                Call(GetActorVar, ACTOR_SELF, 11, LVar0)
                Sub(LVar0, 1)
                Call(SetActorVar, ACTOR_SELF, 11, LVar0)
                IfLe(LVar0, 0)
                    Call(EnableIdleScript, ACTOR_SELF, 0)
                    Call(UseBattleCamPreset, 19)
                    Call(SetBattleCamTarget, 80, 70, 0)
                    Call(SetBattleCamDist, 300)
                    Call(SetBattleCamOffsetY, 30)
                    Call(MoveBattleCamOver, 30)
                    Wait(30)
                    Loop(10)
                        Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                        Call(LoadBattleDmaData, 1)
                        Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
                        Wait(4)
                    EndLoop
                    Call(UseBattleCamPreset, 2)
                    Call(MoveBattleCamOver, 15)
                    Call(PlaySoundAtActor, ACTOR_SELF, 955)
                    Set(LVar0, 512)
                    ExecWait(b_area_kzn2_lava_piranha_EVS_Ignite)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x790004)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                    Call(LoadBattleDmaData, 14)
                    Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
                    Wait(14)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                    Call(LoadBattleDmaData, 0)
                    Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
                    Call(EnableIdleScript, ACTOR_SELF, 1)
                EndIf
            EndIf
    EndSwitch
    Return
    End
};
// clang-format on

FormationRow TTYD64_kzn2_lava_piranha_LeftBudFormation[] = {
    { .actor = &TTYD64_kzn2_lava_bud,
      .home = { .vec = &b_area_kzn2_lava_piranha_SummonPos },
      .priority = 80,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kzn2_lava_piranha_RightBudFormation[] = {
    { .actor = &TTYD64_kzn2_lava_bud,
      .home = { .vec = &b_area_kzn2_lava_piranha_SummonPos },
      .priority = 70,
      .var0 = 2,
      .var1 = 50,
      .var2 = 14,
      .var3 = 20 },
};

// clang-format off
EvtScript TTYD64_kzn2_lava_piranha_EVS_Attack_SpitFire = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF, 0)
    Thread
        Wait(8)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, 80, 70, 0)
        Call(SetBattleCamDist, 300)
        Call(SetBattleCamOffsetY, 30)
        Call(MoveBattleCamOver, 45)
        Wait(57)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 15)
    EndThread
    Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
    Call(LoadBattleDmaData, 2)
    Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
    Wait(14)
    Call(SetAnimation, ACTOR_SELF, 1, 0x790005)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 961)
    Wait(45)
    Call(SetAnimation, ACTOR_SELF, 1, 0x790006)
    Call(GetPartOffset, ACTOR_SELF, 1, LVar0, LVar1, LVar2)
    Sub(LVar0, 50)
    Sub(LVar1, 15)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 40)
    Set(LVar4, -10)
    Call(PlayEffect_impl, 99, 1, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.0), 20, 20, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 963)
    Wait(19)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(PlayEffect_impl, 112, 0, LVar3, 0, LVar5, 50, 50, Float(1.0), 40, 55, Float(1.0), Float(1.0), 0, 0)
    Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
    Call(LoadBattleDmaData, 3)
    Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 2, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x790003)
            Wait(19)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
            Call(LoadBattleDmaData, 0)
            Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 2, 0xFFFF, 0, 5, 32)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x790003)
            Wait(19)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
            Call(LoadBattleDmaData, 0)
            Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
            IfEq(LVarF, 10)
                Return
            EndIf
            Call(UseBattleCamPreset, 2)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_piranha_EVS_Death = {
    Call(SetActorVar, ACTOR_SELF, 1, 1)
    ExecWait(TTYD64_kzn2_lava_piranha_EVS_Hit)
    Label(0)
    Call(GetBattleFlags, LVar0)
    IfFlag(LVar0, 256)
        Wait(1)
        Goto(0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar2)
    IfEq(LVar2, 0)
        Call(ClearStatusEffects, ACTOR_SELF)
        Call(ClearStatusEffects, 513)
        Call(ClearStatusEffects, 514)
        Call(SetAnimatorFlags, 0, 0x40000, 0)
        Call(GetActorVar, 513, 0, LVar0)
        Call(SetAnimatorFlags, LVar0, 0x40000, 0)
        Call(GetActorVar, 514, 0, LVar0)
        Call(SetAnimatorFlags, LVar0, 0x40000, 0)
        Call(CancelEnemyTurn, 1)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, 90, 90, 0)
        Call(SetBattleCamDist, 360)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 240)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
        Call(LoadBattleDmaData, 9)
        Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_3_BASE)
        Call(LoadBattleDmaData, 35)
        Call(PlayModelAnimation, 3, (Bytecode) VINE_3_BASE)
        Wait(10)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
        Call(LoadBattleDmaData, 24)
        Call(PlayModelAnimation, 1, (Bytecode) VINE_1_BASE)
        Wait(5)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
        Call(LoadBattleDmaData, 24)
        Call(PlayModelAnimation, 2, (Bytecode) VINE_2_BASE)
        Wait(4)
        Thread
            Call(PlaySound, 956)
            Call(ShakeCam, 1, 0, 119, Float(0.30078125))
            Call(PlaySound, 1980)
        EndThread
        Call(b_area_kzn2_lava_piranha_StartRumbleWithParams, 80, 234)
        Call(HideHealthBar, ACTOR_SELF)
        Call(HideHealthBar, 513)
        Call(HideHealthBar, 514)
        Call(SetAnimation, ACTOR_SELF, 1, 0x79000D)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
        Call(LoadBattleDmaData, 10)
        Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
        Thread
            Call(PlaySoundAtActor, ACTOR_SELF, 966)
            Wait(35)
            Set(LVar0, 0)
            Set(LVar1, 0)
            Loop(0)
                Call(GetAnimatedModelRootPosition, 0, LVar2, LVar3, LVar4)
                Add(LVar3, LVar1)
                Call(SetAnimatedModelRootPosition, 0, LVar2, LVar3, LVar4)
                Call(b_area_kzn2_lava_piranha_GetSinkPosLavaPiranha, LVar0, LVar1)
                Add(LVar0, 1)
                Wait(1)
                IfEq(LVar1, 99)
                    BreakLoop
                EndIf
            EndLoop
        EndThread
        Wait(10)
        Call(SetAnimation, 513, 1, 0x7B000D)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
        Call(LoadBattleDmaData, 25)
        Call(PlayModelAnimation, 1, (Bytecode) VINE_1_BASE)
        Thread
            Wait(45)
            Set(LVar0, 0)
            Set(LVar1, 0)
            Loop(0)
                Call(GetAnimatedModelRootPosition, 1, LVar2, LVar3, LVar4)
                Add(LVar3, LVar1)
                Call(SetAnimatedModelRootPosition, 1, LVar2, LVar3, LVar4)
                Call(b_area_kzn2_lava_piranha_GetSinkPosLavaBud, LVar0, LVar1)
                Add(LVar0, 1)
                Wait(1)
                IfEq(LVar1, 99)
                    BreakLoop
                EndIf
            EndLoop
        EndThread
        Wait(5)
        Call(SetAnimation, 514, 1, 0x7B000D)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
        Call(LoadBattleDmaData, 25)
        Call(PlayModelAnimation, 2, (Bytecode) VINE_2_BASE)
        Thread
            Wait(45)
            Set(LVar0, 0)
            Set(LVar1, 0)
            Loop(0)
                Call(GetAnimatedModelRootPosition, 2, LVar2, LVar3, LVar4)
                Add(LVar3, LVar1)
                Call(SetAnimatedModelRootPosition, 2, LVar2, LVar3, LVar4)
                Call(b_area_kzn2_lava_piranha_GetSinkPosLavaBud, LVar0, LVar1)
                Add(LVar0, 1)
                Wait(1)
                IfEq(LVar1, 99)
                    BreakLoop
                EndIf
            EndLoop
        EndThread
        Wait(35)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, 90, 90, 0)
        Call(SetBattleCamDist, 360)
        Call(SetBattleCamOffsetY, -45)
        Call(MoveBattleCamOver, 110)
        Wait(60)
        Call(SetAnimatedModelRootPosition, 0, 0, -250, 0)
        Call(SetAnimatedModelRootPosition, 1, 0, -250, 0)
        Call(SetAnimatedModelRootPosition, 2, 0, -250, 0)
        Call(SetActorPos, ACTOR_SELF, 100, 0, 0)
        Call(DropStarPoints, ACTOR_SELF)
        Call(PlaySoundAtActor, ACTOR_SELF, 997)
        Call(ForceHomePos, ACTOR_SELF, 61, 61, 0)
        Wait(65)
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, 0, LVar0, LVar1, LVar2)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 240)
        Call(SetBattleCamOffsetY, 40)
        Call(MoveBattleCamOver, 20)
        Wait(20)
        Thread
            Call(b_area_kzn2_lava_piranha_ManageFakeoutMusic)
        EndThread
        Wait(80)
        Thread
            Call(PlaySound, 956)
            Call(ShakeCam, 1, 0, 165, Float(1.2001953125))
            Call(PlaySound, 1980)
        EndThread
        Call(b_area_kzn2_lava_piranha_StartRumbleWithParams, 80, 300)
        Call(UseIdleAnimation, 0, 0)
        Call(SetAnimation, 0, 0, 0x1002A)
        Wait(20)
        Call(PlaySoundAtActor, 0, 611)
        Call(GetActorPos, 0, LVar0, LVar1, LVar2)
        Add(LVar1, 20)
        Call(PlayEffect_impl, 16, 2, 0, LVar0, LVar1, LVar2, 20, 315, 30, 0, 0, 0, 0, 0)
        Call(GetActorPos, 256, LVar0, LVar1, LVar2)
        Add(LVar1, 10)
        Call(PlayEffect_impl, 16, 2, 0, LVar0, LVar1, LVar2, 20, 315, 30, 0, 0, 0, 0, 0)
        Wait(50)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, 90, 90, 0)
        Call(SetBattleCamDist, 360)
        Call(SetBattleCamOffsetY, -60)
        Call(MoveBattleCamOver, 30)
        Wait(40)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, 90, 90, 0)
        Call(SetBattleCamDist, 200)
        Call(SetBattleCamOffsetY, -60)
        Call(MoveBattleCamOver, 40)
        Wait(40)
        Thread
            Call(UseIdleAnimation, 0, 0)
            Call(SetAnimation, 0, 0, 0x1002B)
            Wait(40)
            Call(UseIdleAnimation, 0, 1)
        EndThread
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, 30, 90, 0)
        Call(SetBattleCamDist, 460)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 30)
        Call(b_area_kzn2_lava_piranha_StartRumbleWithParams, 180, 16)
        Thread
            Call(ShakeCam, 1, 0, 4, Float(3.0))
            Call(ShakeCam, 1, 0, 10, Float(1.0))
        EndThread
        ChildThread
            Wait(50)
            Call(UseBattleCamPreset, 19)
            Call(SetBattleCamTarget, 90, 90, 0)
            Call(SetBattleCamDist, 360)
            Call(SetBattleCamOffsetY, 0)
            Call(MoveBattleCamOver, 40)
            Wait(85)
        EndChildThread
        Call(SetActorVar, ACTOR_SELF, 0, 1)
        Call(SetActorVar, ACTOR_SELF, 7, 0x790004)
        Call(SetActorVar, ACTOR_SELF, 8, 0x79000A)
        Call(SetActorVar, 513, 7, 0x7B0004)
        Call(SetActorVar, 513, 8, 0x7B000B)
        Call(SetActorVar, 514, 7, 0x7B0004)
        Call(SetActorVar, 514, 8, 0x7B000B)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_kzn2_lava_bud_FieryAnims))
        Call(SetIdleAnimations, 513, 1, Ref(b_area_kzn2_lava_bud_FieryAnims))
        Call(SetIdleAnimations, 514, 1, Ref(b_area_kzn2_lava_bud_FieryAnims))
        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kzn2_lava_piranha_FieryDefense))
        Call(SetDefenseTable, ACTOR_SELF, 2, Ref(b_area_kzn2_lava_piranha_FieryDefense))
        Call(SetDefenseTable, 513, 1, Ref(b_area_kzn2_lava_bud_FieryDefense))
        Call(SetDefenseTable, 513, 2, Ref(b_area_kzn2_lava_bud_FieryDefense))
        Call(SetDefenseTable, 514, 1, Ref(b_area_kzn2_lava_bud_FieryDefense))
        Call(SetDefenseTable, 514, 2, Ref(b_area_kzn2_lava_bud_FieryDefense))
        Call(SetPartImmunityBits, ACTOR_SELF, 1, 2, 1)
        Call(SetPartImmunityBits, ACTOR_SELF, 2, 2, 1)
        Call(SetPartImmunityBits, 513, 1, 2, 1)
        Call(SetPartImmunityBits, 513, 2, 2, 1)
        Call(SetPartImmunityBits, 514, 1, 2, 1)
        Call(SetPartImmunityBits, 514, 2, 2, 1)
        Call(SetPartFlagBits, 513, 2, 8192, 0)
        Call(SetPartFlagBits, 514, 2, 8192, 0)
        Set(LVar0, 512)
        ExecWait(b_area_kzn2_lava_piranha_EVS_Ignite)
        Call(SetAnimation, ACTOR_SELF, 1, 0x790004)
        Set(LVar0, 513)
        ExecWait(b_area_kzn2_lava_piranha_EVS_Ignite)
        Call(SetAnimation, 513, 1, 0x7B0004)
        Set(LVar0, 514)
        ExecWait(b_area_kzn2_lava_piranha_EVS_Ignite)
        Call(SetAnimation, 514, 1, 0x7B0004)
        Call(SetActorType, ACTOR_SELF, 180)
        Call(SetActorType, 513, 182)
        Call(SetActorType, 514, 182)
        Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
        Call(SetActorFlagBits, 513, 4096, 1)
        Call(SetActorFlagBits, 514, 4096, 1)
        Call(GetEnemyMaxHP, ACTOR_SELF, LVar0)
        Call(SetEnemyHP, ACTOR_SELF, LVar0)
        Call(GetEnemyMaxHP, 513, LVar0)
        Call(SetEnemyHP, 513, LVar0)
        Call(GetEnemyMaxHP, 514, LVar0)
        Call(SetEnemyHP, 514, LVar0)
        Call(EnableModel, 78, 1)
        Call(EnableModel, 79, 1)
        Call(EnableModel, 80, 1)
        Call(EnableModel, 81, 1)
        Call(EnableModel, 82, 1)
        Call(EnableModel, 83, 1)
        Call(EnableModel, 84, 1)
        Call(EnableModel, 85, 1)
        Call(EnableModel, 87, 1)
        Call(EnableModel, 88, 1)
        Call(PlaySoundAtActor, ACTOR_SELF, 965)
        Call(PlayEffect_impl, 112, 0, 100, 0, 0, 70, 80, Float(2.5), 80, 55, Float(2.0), Float(2.0), 0, 0)
        Call(LoadAnimatedModel, 4, Ref(b_area_kzn2_lava_piranha_anim1))
        Call(PlayModelAnimation, 4, Ref(b_area_kzn2_lava_piranha_anim1_8021A364))
        Call(SetAnimatedModelRootPosition, 4, 0, 0, 0)
        Call(EnableGroup, 23, 0)
        Call(EnableGroup, 28, 1)
        Thread
            Wait(45)
            Call(DeleteAnimatedModel, 4)
        EndThread
        Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
        Call(LoadBattleDmaData, 12)
        Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
        Call(SetAnimatedModelRootPosition, 0, 0, 0, 0)
        Wait(5)
        Call(SetAnimatedModelRootPosition, 2, 50, 14, 20)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
        Call(LoadBattleDmaData, 28)
        Call(PlayModelAnimation, 2, (Bytecode) VINE_2_BASE)
        Wait(10)
        Call(SetAnimatedModelRootPosition, 1, 0, 0, 0)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
        Call(LoadBattleDmaData, 28)
        Call(PlayModelAnimation, 1, (Bytecode) VINE_1_BASE)
        Wait(45)
        Call(SetAnimatedModelRootPosition, 3, 0, 0, 0)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_3_BASE)
        Call(LoadBattleDmaData, 36)
        Call(PlayModelAnimation, 3, (Bytecode) VINE_3_BASE)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
        Call(LoadBattleDmaData, 0)
        Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
        Call(SetAnimation, ACTOR_SELF, 1, 0x79000E)
        Wait(5)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
        Call(LoadBattleDmaData, 31)
        Call(PlayModelAnimation, 2, (Bytecode) VINE_2_BASE)
        Wait(10)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
        Call(LoadBattleDmaData, 31)
        Call(PlayModelAnimation, 1, (Bytecode) VINE_1_BASE)
        Wait(30)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_3_BASE)
        Call(LoadBattleDmaData, 34)
        Call(PlayModelAnimation, 3, (Bytecode) VINE_3_BASE)
        Call(GetEnemyMaxHP, 513, LVar0)
        Call(SetEnemyHP, 513, LVar0)
        Call(GetEnemyMaxHP, 514, LVar0)
        Call(SetEnemyHP, 514, LVar0)
        Call(SetActorVar, ACTOR_SELF, 1, 0)
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
    Else
        Call(HideHealthBar, 513)
        Call(HideHealthBar, 514)
        Set(LVar0, 515)
        ExecWait(b_area_kzn2_lava_piranha_EVS_RemovePetitPiranha)
        Set(LVar0, 516)
        ExecWait(b_area_kzn2_lava_piranha_EVS_RemovePetitPiranha)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_3_BASE)
        Call(LoadBattleDmaData, 35)
        Call(PlayModelAnimation, 3, (Bytecode) VINE_3_BASE)
        Thread
            Call(PlaySound, 956)
            Call(ShakeCam, 1, 0, 100, Float(0.5))
            Call(ShakeCam, 1, 0, 8, Float(0.2001953125))
            Call(PlaySound, 1980)
        EndThread
        Call(b_area_kzn2_lava_piranha_StartRumbleWithParams, 80, 216)
        Thread
            Call(PlaySoundAtActor, ACTOR_SELF, 972)
            Call(GetActorVar, ACTOR_SELF, 5, LVar0)
            IfEq(LVar0, 0)
                Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                Call(LoadBattleDmaData, 8)
                Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
            Else
                Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                Call(LoadBattleDmaData, 9)
                Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
            EndIf
            Wait(19)
            Call(HideHealthBar, ACTOR_SELF)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
            Call(LoadBattleDmaData, 10)
            Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
            Call(GetActorVar, ACTOR_SELF, 5, LVar0)
            IfEq(LVar0, 1)
                Call(PlayEffect_impl, 112, 0, 105, 60, 2, 80, 60, Float(1.80078125), 90, 100, Float(1.5), Float(1.5), 0, 0)
            EndIf
            Wait(121)
            Call(PlaySoundAtActor, ACTOR_SELF, 973)
            Call(SetAnimation, ACTOR_SELF, 1, 0x79000A)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
            Call(LoadBattleDmaData, 11)
            Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
            Wait(30)
            Call(GetActorVar, ACTOR_SELF, 10, LVar0)
            Set(LVar1, 100)
            Loop(50)
                Sub(LVar1, 2)
                SetF(LVar2, LVar0)
                MulF(LVar2, LVar1)
                MulF(LVar2, Float(0.0107421875))
                Call(SetActorVar, ACTOR_SELF, 10, LVar2)
                Wait(1)
            EndLoop
        EndThread
        Thread
            Wait(12)
            Call(GetActorVar, 513, 5, LVar0)
            IfEq(LVar0, 0)
                Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Call(LoadBattleDmaData, 23)
                Call(PlayModelAnimation, 1, (Bytecode) VINE_1_BASE)
            Else
                Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Call(LoadBattleDmaData, 24)
                Call(PlayModelAnimation, 1, (Bytecode) VINE_1_BASE)
            EndIf
            Wait(19)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
            Call(LoadBattleDmaData, 25)
            Call(PlayModelAnimation, 1, (Bytecode) VINE_1_BASE)
            Call(GetActorVar, 513, 5, LVar0)
            IfEq(LVar0, 1)
                Call(PlayEffect_impl, 112, 0, 67, 30, 2, 50, 40, Float(1.30078125), 30, 70, Float(1.2001953125), Float(1.2001953125), 0, 0)
            EndIf
            Wait(96)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
            Call(LoadBattleDmaData, 26)
            Call(PlayModelAnimation, 1, (Bytecode) VINE_1_BASE)
            Wait(30)
            Call(GetActorVar, 513, 10, LVar0)
            Set(LVar1, 100)
            Loop(50)
                Sub(LVar1, 2)
                SetF(LVar2, LVar0)
                MulF(LVar2, LVar1)
                MulF(LVar2, Float(0.0107421875))
                Call(SetActorVar, 513, 10, LVar2)
                Wait(1)
            EndLoop
        EndThread
        Thread
            Wait(5)
            Call(GetActorVar, 514, 5, LVar0)
            IfEq(LVar0, 0)
                Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                Call(LoadBattleDmaData, 23)
                Call(PlayModelAnimation, 2, (Bytecode) VINE_2_BASE)
            Else
                Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                Call(LoadBattleDmaData, 24)
                Call(PlayModelAnimation, 2, (Bytecode) VINE_2_BASE)
            EndIf
            Wait(19)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
            Call(LoadBattleDmaData, 25)
            Call(PlayModelAnimation, 2, (Bytecode) VINE_2_BASE)
            Call(GetActorVar, 514, 5, LVar0)
            IfEq(LVar0, 1)
                Call(PlayEffect_impl, 112, 0, 120, 35, 5, 50, 40, Float(1.30078125), 30, 70, Float(1.2001953125), Float(1.2001953125), 0, 0)
            EndIf
            Wait(96)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
            Call(LoadBattleDmaData, 26)
            Call(PlayModelAnimation, 2, (Bytecode) VINE_2_BASE)
            Wait(30)
            Call(GetActorVar, 514, 10, LVar0)
            Set(LVar1, 100)
            Loop(50)
                Sub(LVar1, 2)
                SetF(LVar2, LVar0)
                MulF(LVar2, LVar1)
                MulF(LVar2, Float(0.0107421875))
                Call(SetActorVar, 514, 10, LVar2)
                Wait(1)
            EndLoop
        EndThread
        Thread
            Wait(150)
            Set(LVar0, 14)
            Loop(14)
                Sub(LVar0, 1)
                Call(SetAnimatedModelRootPosition, 2, 50, LVar0, 20)
                Wait(2)
            EndLoop
        EndThread
        Wait(212)
        Call(PlaySoundAtActor, ACTOR_SELF, 8426)
        Call(SetAnimation, ACTOR_SELF, 1, 0x79000F)
        Call(SetAnimation, 513, 1, 0x7B000F)
        Call(SetAnimation, 514, 1, 0x7B000F)
        Call(PlayEffect_impl, 37, 0, -60, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Thread
            Call(b_area_kzn2_lava_piranha_StartRumbleWithParams, 180, 16)
            Call(ShakeCam, 1, 0, 5, Float(4.0))
        EndThread
        Wait(3)
        Call(SetActorPos, ACTOR_SELF, -60, 0, 0)
        Call(DropStarPoints, ACTOR_SELF)
        Call(PlaySoundAtActor, ACTOR_SELF, 997)
        Wait(15)
        Call(GetActorVar, ACTOR_SELF, 6, LVar0)
        IfNe(LVar0, 0)
            Call(SetActorVar, ACTOR_SELF, 6, 0)
            Call(RemoveEffect, LVar0)
        EndIf
        Call(GetActorVar, 513, 6, LVar0)
        IfNe(LVar0, 0)
            Call(SetActorVar, 513, 6, 0)
            Call(RemoveEffect, LVar0)
        EndIf
        Call(GetActorVar, 514, 6, LVar0)
        IfNe(LVar0, 0)
            Call(SetActorVar, 514, 6, 0)
            Call(RemoveEffect, LVar0)
        EndIf
        Wait(5)
        Call(SetActorFlagBits, 512, 0x400000, 1)
        Call(SetPartFlagBits, 512, 1, 0x20000, 1)
        Call(SetPartFlagBits, 512, 2, 0x20000, 1)
        Call(SetActorFlagBits, 513, 0x400000, 1)
        Call(SetActorFlagBits, 514, 0x400000, 1)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_piranha_EVS_ComboHit = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Call(SetAnimation, ACTOR_SELF, 1, LVar0)
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    IfEq(LVar0, 2)
        Call(GetLastDamage, ACTOR_SELF, LVar0)
        IfLt(LVar0, 4)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
            Call(LoadBattleDmaData, 5)
        Else
            Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
            Call(LoadBattleDmaData, 4)
        EndIf
        Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
        Wait(29)
        Wait(14)
    Else
        Call(GetLastDamage, ACTOR_SELF, LVar0)
        IfLt(LVar0, 4)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
            Call(LoadBattleDmaData, 7)
        Else
            Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
            Call(LoadBattleDmaData, 6)
        EndIf
        Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
        Wait(29)
        Wait(14)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_piranha_EVS_Hit = {
    ExecWait(TTYD64_kzn2_lava_piranha_EVS_Hit_Inner)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_piranha_EVS_Hit_Inner = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Call(SetAnimation, ACTOR_SELF, 1, LVar0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Call(GetLastDamage, ACTOR_SELF, LVar0)
        IfLt(LVar0, 4)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
            Call(LoadBattleDmaData, 7)
        Else
            Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
            Call(LoadBattleDmaData, 6)
        EndIf
        Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
        Wait(29)
        Wait(14)
        Return
    EndIf
    IfFlag(LVarE, 12)
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        IfEq(LVar0, 0)
            Call(GetLastDamage, ACTOR_SELF, LVar0)
            IfLt(LVar0, 4)
                Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                Call(LoadBattleDmaData, 5)
            Else
                Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                Call(LoadBattleDmaData, 4)
            EndIf
            Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
            Wait(29)
            Wait(14)
        Else
            Call(SetActorVar, ACTOR_SELF, 11, 2)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
            Call(LoadBattleDmaData, 6)
            Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
            Call(GetActorVar, ACTOR_SELF, 6, LVar0)
            IfNe(LVar0, 0)
                Call(RemoveEffect, LVar0)
                Call(SetActorVar, ACTOR_SELF, 6, 0)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(PlayEffect_impl, 111, 0, LVar0, LVar1, LVar2, Float(3.0), 50, 0, 0, 0, 0, 0, 0, 0)
            EndIf
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_kzn2_lava_piranha_StunnedAnims))
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kzn2_lava_piranha_StunnedDefense))
            Call(SetDefenseTable, ACTOR_SELF, 2, Ref(b_area_kzn2_lava_piranha_StunnedDefense))
            Call(SetActorVar, ACTOR_SELF, 7, 0x79000A)
            Call(SetActorVar, ACTOR_SELF, 8, 0x790009)
            Call(SetPartEventBits, ACTOR_SELF, 1, 2, 0)
            Call(SetPartEventBits, ACTOR_SELF, 2, 2, 0)
            Wait(29)
            Call(PlaySoundAtActor, ACTOR_SELF, 968)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
            Call(LoadBattleDmaData, 13)
            Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
            Wait(14)
            Call(SetActorVar, ACTOR_SELF, 5, 0)
        EndIf
    Else
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        IfEq(LVar0, 0)
            Call(GetLastDamage, ACTOR_SELF, LVar0)
            IfLt(LVar0, 4)
                Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                Call(LoadBattleDmaData, 5)
            Else
                Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                Call(LoadBattleDmaData, 4)
            EndIf
            Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
            Wait(29)
            Wait(14)
        Else
            Call(GetLastDamage, ACTOR_SELF, LVar0)
            IfLt(LVar0, 4)
                Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                Call(LoadBattleDmaData, 7)
            Else
                Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                Call(LoadBattleDmaData, 6)
            EndIf
            Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
            Call(PlayEffect_impl, 112, 0, 80, 50, 0, 60, 50, Float(1.5), 36, 42, Float(0.80078125), Float(0.80078125), 0, 0)
            Wait(29)
            Wait(14)
        EndIf
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_piranha_EVS_PlayIdleAnimation = {
    Call(GetActorVar, ACTOR_SELF, 7, LVar0)
    Call(SetAnimation, ACTOR_SELF, 1, LVar0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
        Call(LoadBattleDmaData, 0)
        Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    IfEq(LVar0, 0)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
        Call(LoadBattleDmaData, 1)
        Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
    Else
        Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
        Call(LoadBattleDmaData, 0)
        Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
    EndIf
    Return
    End
};
// clang-format on

ActorBlueprint TTYD64_kzn2_petit_piranha = {
    .flags = 0x200,
    .maxHP = 1,
    .type = 0xB7,
    .level = 0,
    .partCount = 1,
    .partsData = b_area_kzn2_petit_piranha_ActorParts,
    .initScript = &TTYD64_kzn2_petit_piranha_EVS_Init,
    .statusTable = b_area_kzn2_petit_piranha_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 30, 30 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

// clang-format off
EvtScript TTYD64_kzn2_petit_piranha_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kzn2_petit_piranha_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kzn2_petit_piranha_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kzn2_petit_piranha_EVS_HandleEvent))
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_petit_piranha_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfGe(LVar1, 41)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7A0004)
        Call(UseBattleCamPreset, 14)
        Call(SetBattleCamDist, 380)
        Call(SetBattleCamOffsetY, -20)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 20)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7A0006)
        Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 15)
        Add(LVar1, 15)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(FlyToGoal, ACTOR_SELF, 20, -12, 0)
    Else
        Call(UseBattleCamPreset, 14)
        Call(SetBattleCamDist, 380)
        Call(SetBattleCamOffsetY, 0)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 20)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7A0003)
        Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
        Call(PlaySoundAtActor, ACTOR_SELF, 970)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 20)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(FlyToGoal, ACTOR_SELF, 20, 0, 0)
        Wait(10)
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Call(PlaySoundAtActor, ACTOR_SELF, 971)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Call(SetGoalPos, ACTOR_SELF, LVar0, 5, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7A0005)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(8.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -16, 3)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 1, 1)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Set(LVar1, 0)
    Add(LVar2, 2)
    Call(PlayEffect_impl, 32, 1, LVar0, LVar1, LVar2, Float(0.30078125), LVarA, 0, 0, 0, 0, 0, 0, 0)
    Thread
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Call(MakeLerp, 0, 30, 21, 0)
        Loop(0)
            Call(UpdateLerp)
            Set(LVar4, LVar3)
            Sub(LVar4, LVar0)
            Call(b_area_kzn2_petit_piranha_SetFlamePosX, LVarA, LVar4)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Call(MakeLerp, 140, 160, 2, 1)
    Loop(0)
        Call(UpdateLerp)
        MulF(LVar0, Float(0.0107421875))
        Call(b_area_kzn2_petit_piranha_SetFlameScaleH, LVarA, LVar0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(EnemyTestTarget, ACTOR_SELF, LVar9, 0, 0, 1, 16)
    Switch(LVar9)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(MakeLerp, 160, 10, 20, 1)
            Loop(0)
                Call(UpdateLerp)
                MulF(LVar0, Float(0.0107421875))
                Call(b_area_kzn2_petit_piranha_SetFlameScaleH, LVarA, LVar0)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
            Wait(1)
            Call(RemoveEffect, LVarA)
            IfEq(LVar9, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(UseBattleCamPreset, 2)
            ExecWait(b_area_kzn2_petit_piranha_EVS_Death)
            Call(RemoveActor, ACTOR_SELF)
            Return
        EndCaseGroup
    EndSwitch
    Wait(2)
    Set(LVar8, 6)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar9, 2, 0xFFFF, 0, LVar8, 32)
    Switch(LVar9)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(MakeLerp, 160, 10, 20, 1)
            Loop(0)
                Call(UpdateLerp)
                MulF(LVar0, Float(0.0107421875))
                Call(b_area_kzn2_petit_piranha_SetFlameScaleH, LVarA, LVar0)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
            Wait(1)
            Call(RemoveEffect, LVarA)
            Wait(15)
            IfEq(LVar9, 10)
                Return
            EndIf
            Call(UseBattleCamPreset, 2)
        EndCaseGroup
    EndSwitch
    ExecWait(b_area_kzn2_petit_piranha_EVS_Death)
    Call(RemoveActor, ACTOR_SELF)
    Return
    End
};
// clang-format on

ActorBlueprint TTYD64_kzn2_lava_bud = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0xB5,
    .level = 0,
    .partCount = 2,
    .partsData = b_area_kzn2_lava_bud_ActorParts,
    .initScript = &TTYD64_kzn2_lava_bud_EVS_Init,
    .statusTable = b_area_kzn2_lava_bud_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 30, 30 },
    .healthBarOffset = { 10, -42 },
    .statusIconOffset = { -18, 10 },
    .statusTextOffset = { 0, 0 },
};

// clang-format off
EvtScript TTYD64_kzn2_lava_bud_EVS_Init = {
    UseArray(Ref(TTYD64_kzn2_lava_bud_unusedArray))
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 0)
    Call(SetActorVar, ACTOR_SELF, 9, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 0)
    Call(SetActorVar, ACTOR_SELF, 13, 0)
    Call(RandInt, 20, LVar0)
    Add(LVar0, 15)
    Call(SetActorVar, ACTOR_SELF, 13, LVar0)
    Call(SetActorVar, ACTOR_SELF, 7, 0x7B0003)
    Call(SetActorVar, ACTOR_SELF, 8, 0x7B0009)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kzn2_lava_bud_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_kzn2_lava_bud_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kzn2_lava_bud_EVS_HandleEvent))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_bud_EVS_Idle = {
    Label(0)
    Call(GetActorHP, 512, LVar0)
    IfEq(LVar0, 0)
        Goto(99)
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x400000)
        Goto(99)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    IfNe(LVar0, 2)
        Goto(99)
    EndIf
    Label(10)
    Call(GetActorVar, ACTOR_SELF, 13, LVar0)
    Sub(LVar0, 1)
    Call(SetActorVar, ACTOR_SELF, 13, LVar0)
    IfNe(LVar0, 0)
        Goto(99)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 12, LVar0)
    Add(LVar0, 1)
    IfGe(LVar0, 3)
        Set(LVar0, 0)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 12, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(RandInt, 50, LVar0)
            Add(LVar0, 25)
        CaseEq(1)
            Call(RandInt, 40, LVar0)
            Add(LVar0, 20)
        CaseDefault
            Call(RandInt, 3, LVar0)
            Add(LVar0, 3)
    EndSwitch
    Call(SetActorVar, ACTOR_SELF, 13, LVar0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
    Else
        Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
    EndIf
    Call(LoadBattleDmaData, 30)
    ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
    Label(99)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine = {
    IfEq(LVar0, 1)
        Call(PlayModelAnimation, LVar0, (Bytecode) VINE_1_BASE)
    Else
        Call(PlayModelAnimation, LVar0, (Bytecode) VINE_2_BASE)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_bud_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Call(SetAnimatorFlags, LVar0, 0x40000, 0)
    Call(GetLastElement, LVarE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(56)
        CaseEq(9)
            ExecWait(TTYD64_kzn2_lava_bud_EVS_ComboHit)
        CaseEq(10)
            ExecWait(TTYD64_kzn2_lava_bud_EVS_Hit)
        CaseEq(14)
            IfFlag(LVarE, 2)
                ExecWait(TTYD64_kzn2_lava_bud_EVS_BurnHit)
            Else
                ExecWait(TTYD64_kzn2_lava_bud_EVS_Hit)
            EndIf
        CaseEq(36)
            ExecWait(TTYD64_kzn2_lava_bud_EVS_Death)
        CaseEq(11)
            ExecWait(TTYD64_kzn2_lava_bud_EVS_Hit)
        CaseEq(33)
            ExecWait(TTYD64_kzn2_lava_bud_EVS_Death)
        CaseEq(47)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 8, LVar1)
            ExecWait(Ref(EVS_Enemy_ShockHit))
        CaseEq(38)
            ExecWait(Ref(EVS_Enemy_ShockHit))
        CaseEq(23)
            IfNotFlag(LVarE, 2)
                ExecWait(TTYD64_kzn2_lava_bud_EVS_ComboHit)
            EndIf
        CaseEq(25)
            IfNotFlag(LVarE, 2)
                ExecWait(TTYD64_kzn2_lava_bud_EVS_Hit)
            EndIf
        CaseEq(31)
        CaseEq(27)
        CaseEq(32)
            ExecWait(TTYD64_kzn2_lava_bud_EVS_Death)
        CaseEq(53)
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Call(SetAnimatorFlags, LVar0, 0x40000, 0)
        CaseEq(48)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 8, LVar1)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(1000)
        CaseDefault
    EndSwitch
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x200000)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Call(SetAnimatorFlags, LVar0, 0x40000, 1)
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_bud_EVS_BurnHit = {
    Thread
        Wait(1)
        Call(GetActorVar, 512, 0, LVar0)
        IfEq(LVar0, 0)
            Goto(10)
        EndIf
        Call(GetActorVar, ACTOR_SELF, 5, LVar2)
        IfEq(LVar2, 1)
            Goto(10)
        EndIf
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        IfEq(LVar0, 1)
            Set(LVar0, 513)
        Else
            Set(LVar0, 514)
        EndIf
        ExecWait(b_area_kzn2_lava_piranha_EVS_Ignite)
        Label(10)
    EndThread
    Call(GetActorVar, 512, 0, LVar0)
    IfNe(LVar0, 0)
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        IfEq(LVar0, 2)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
            Else
                Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
            EndIf
            Call(LoadBattleDmaData, 29)
            ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
            Call(SetActorVar, ACTOR_SELF, 7, 0x7B0003)
            Call(SetActorVar, ACTOR_SELF, 8, 0x7B0009)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_kzn2_lava_bud_FieryAnims))
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kzn2_lava_bud_FieryDefense))
            Call(SetDefenseTable, ACTOR_SELF, 2, Ref(b_area_kzn2_lava_bud_FieryDefense))
            Thread
                Wait(14)
                Call(GetActorVar, ACTOR_SELF, 0, LVar0)
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 31)
                ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
            EndThread
        EndIf
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_bud_EVS_TakeTurn = {
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x400000)
        Return
    EndIf
    Call(GetActorVar, 512, 0, LVar0)
    IfEq(LVar0, 0)
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        IfEq(LVar0, 2)
            Return
        EndIf
        ExecWait(TTYD64_kzn2_lava_bud_EVS_Attack_SpitPetit)
    Else
        Call(GetActorVar, ACTOR_SELF, 4, LVar1)
        IfNe(LVar1, 0)
            Sub(LVar1, 1)
            Call(SetActorVar, ACTOR_SELF, 4, LVar1)
            Return
        EndIf
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        IfEq(LVar0, 1)
            IfNe(LVar1, 0)
                Return
            EndIf
            Call(SetActorVar, ACTOR_SELF, 4, 1)
            ExecWait(TTYD64_kzn2_lava_bud_EVS_Move_SummonPetit)
        Else
            Call(GetActorVar, ACTOR_SELF, 11, LVar0)
            Sub(LVar0, 1)
            Call(SetActorVar, ACTOR_SELF, 11, LVar0)
            IfLe(LVar0, 0)
                Call(EnableIdleScript, ACTOR_SELF, 0)
                Call(GetActorVar, ACTOR_SELF, 0, LVar0)
                IfEq(LVar0, 1)
                    Call(UseBattleCamPreset, 19)
                    Call(SetBattleCamTarget, 40, 30, 0)
                    Call(SetBattleCamDist, 270)
                    Call(SetBattleCamOffsetY, 20)
                    Call(MoveBattleCamOver, 30)
                Else
                    Call(UseBattleCamPreset, 19)
                    Call(SetBattleCamTarget, 110, 35, 0)
                    Call(SetBattleCamDist, 300)
                    Call(SetBattleCamOffsetY, 20)
                    Call(MoveBattleCamOver, 30)
                EndIf
                Wait(30)
                Loop(10)
                    IfEq(LVar0, 1)
                        Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                    Else
                        Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                    EndIf
                    Call(LoadBattleDmaData, 30)
                    ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
                    Wait(4)
                EndLoop
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 15)
                Call(GetEnemyMaxHP, ACTOR_SELF, LVar0)
                Call(SetEnemyHP, ACTOR_SELF, LVar0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x7B0004)
                Call(GetActorVar, ACTOR_SELF, 0, LVar0)
                IfEq(LVar0, 1)
                    Set(LVar0, 513)
                Else
                    Set(LVar0, 514)
                EndIf
                Call(PlaySoundAtActor, LVar0, 8383)
                ExecWait(b_area_kzn2_lava_piranha_EVS_Ignite)
                Call(GetActorVar, ACTOR_SELF, 0, LVar0)
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 29)
                ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
                Wait(14)
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 31)
                ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
                Call(GetEnemyMaxHP, ACTOR_SELF, LVar0)
                Call(SetEnemyHP, ACTOR_SELF, LVar0)
                Call(EnableIdleScript, ACTOR_SELF, 1)
            EndIf
        EndIf
    EndIf
    ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayIdleAnimation)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_bud_EVS_PlayIdleAnimation = {
    Call(GetActorVar, ACTOR_SELF, 7, LVar0)
    Call(SetAnimation, ACTOR_SELF, 1, LVar0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Call(GetActorVar, 512, 0, LVar3)
    Call(GetActorVar, ACTOR_SELF, 5, LVar3)
    IfEq(LVar3, 2)
        IfEq(LVar0, 1)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
        Else
            Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
        EndIf
        Call(LoadBattleDmaData, 30)
        ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
    Else
        IfEq(LVar0, 1)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
        Else
            Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
        EndIf
        Call(LoadBattleDmaData, 31)
        ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_bud_EVS_Move_SummonPetit = {
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    IfEq(LVar0, 2)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 9, LVar0)
    IfNe(LVar0, 0)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Wait(8)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 300)
        Call(SetBattleCamOffsetY, 30)
        Call(MoveBattleCamOver, 30)
        Wait(45)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 20)
    EndThread
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
    Else
        Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
    EndIf
    Call(LoadBattleDmaData, 18)
    ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
    Thread
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7B0007)
        Wait(34)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7B0008)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7B0004)
        IfEq(LVar0, 1)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
        Else
            Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
        EndIf
        Call(LoadBattleDmaData, 31)
        ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
    EndThread
    Wait(56)
    IfEq(LVar0, 1)
        Call(SummonEnemy, Ref(TTYD64_kzn2_lava_bud_LeftPetitFormation), 0)
    Else
        Call(SummonEnemy, Ref(TTYD64_kzn2_lava_bud_RightPetitFormation), 0)
    EndIf
    Set(LVar5, LVar0)
    Call(GetActorVar, ACTOR_SELF, 9, LVar0)
    Add(LVar0, 1)
    Call(SetActorVar, ACTOR_SELF, 9, LVar0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorVar, LVar5, 0, 513)
    Else
        Call(SetActorVar, LVar5, 0, 514)
    EndIf
    Call(GetPartOffset, ACTOR_SELF, 1, LVar0, LVar1, LVar2)
    Sub(LVar0, 15)
    Sub(LVar1, 15)
    Call(SetActorPos, LVar5, LVar0, LVar1, LVar2)
    Sub(LVar0, 30)
    Sub(LVar1, 15)
    Call(PlaySoundAtActor, LVar5, 969)
    Call(GetActorVar, ACTOR_SELF, 0, LVar9)
    IfEq(LVar9, 1)
        Call(GetActorPos, LVar5, LVar0, LVar1, LVar2)
        Set(LVar0, -12)
        Set(LVar1, 80)
        Call(SetGoalPos, LVar5, LVar0, LVar1, LVar2)
        Call(SetHomePos, LVar5, LVar0, LVar1, LVar2)
        Call(SetActorSpeed, LVar5, Float(4.0))
        Call(SetActorJumpGravity, LVar5, Float(1.0))
        Call(FlyToGoal, LVar5, 24, -42, 6)
    Else
        Call(GetActorPos, LVar5, LVar0, LVar1, LVar2)
        Set(LVar0, 18)
        Set(LVar1, 28)
        Call(SetGoalPos, LVar5, LVar0, LVar1, LVar2)
        Call(SetHomePos, LVar5, LVar0, LVar1, LVar2)
        Call(SetActorSpeed, LVar5, Float(5.0))
        Call(SetActorJumpGravity, LVar5, Float(1.2001953125))
        Call(FlyToGoal, LVar5, 16, -15, 5)
    EndIf
    Call(HPBarToHome, LVar5)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
    Else
        Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
    EndIf
    Call(LoadBattleDmaData, 31)
    ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

FormationRow TTYD64_kzn2_lava_bud_LeftPetitFormation[] = {
    { .actor = &TTYD64_kzn2_petit_piranha,
      .home = { .vec = &b_area_kzn2_lava_bud_SummonPos },
      .priority = 95,
      .var0 = -12,
      .var1 = 85,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kzn2_lava_bud_RightPetitFormation[] = {
    { .actor = &TTYD64_kzn2_petit_piranha,
      .home = { .vec = &b_area_kzn2_lava_bud_SummonPos },
      .priority = 94,
      .var0 = 18,
      .var1 = 38,
      .var2 = 0,
      .var3 = 0 },
};

// clang-format off
EvtScript TTYD64_kzn2_lava_bud_EVS_Death = {
    Call(GetActorVar, 512, 0, LVar0)
    IfNe(LVar0, 0)
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        IfEq(LVar0, 2)
            ExecWait(TTYD64_kzn2_lava_bud_EVS_Hit)
            Return
        EndIf
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(SetAnimation, ACTOR_SELF, 1, LVar0)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        IfEq(LVar0, 1)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
        Else
            Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
        EndIf
        Call(LoadBattleDmaData, 21)
        ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
        Call(SetActorVar, ACTOR_SELF, 11, 2)
        Call(GetActorVar, ACTOR_SELF, 6, LVar0)
        IfNe(LVar0, 0)
            Call(RemoveEffect, LVar0)
            Call(SetActorVar, ACTOR_SELF, 6, 0)
        EndIf
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_kzn2_lava_bud_StunnedAnims))
        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kzn2_lava_bud_StunnedDefense))
        Call(SetDefenseTable, ACTOR_SELF, 2, Ref(b_area_kzn2_lava_bud_StunnedDefense))
        Call(SetActorVar, ACTOR_SELF, 7, 0x7B000F)
        Call(SetActorVar, ACTOR_SELF, 8, 0x7B0009)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7B000F)
        Call(SetPartEventBits, ACTOR_SELF, 1, 2, 0)
        Call(SetPartEventBits, ACTOR_SELF, 2, 2, 0)
        Wait(29)
        Call(PlaySoundAtActor, ACTOR_SELF, 967)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        IfEq(LVar0, 1)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
        Else
            Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
        EndIf
        Call(LoadBattleDmaData, 27)
        ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
        Wait(14)
        Call(SetActorVar, ACTOR_SELF, 5, 2)
        Call(GetActorVar, 512, 1, LVarF)
        IfEq(LVarF, 0)
            ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayIdleAnimation)
        EndIf
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    IfEq(LVar0, 0)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        IfEq(LVar0, 1)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
        Else
            Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
        EndIf
        Call(LoadBattleDmaData, 21)
        ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_kzn2_lava_bud_StunnedAnims))
        Call(SetActorVar, ACTOR_SELF, 7, 0x7B000F)
        Call(SetActorVar, ACTOR_SELF, 8, 0x7B0009)
        Wait(29)
        Call(PlaySoundAtActor, ACTOR_SELF, 967)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        IfEq(LVar0, 1)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
        Else
            Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
        EndIf
        Call(LoadBattleDmaData, 27)
        ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
        Wait(14)
        Call(SetActorVar, ACTOR_SELF, 5, 2)
        ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayIdleAnimation)
        Call(SetPartFlagBits, ACTOR_SELF, 2, 0x22000, 1)
        Call(SetActorFlagBits, ACTOR_SELF, 0x40000, 1)
    Else
        ExecWait(TTYD64_kzn2_lava_bud_EVS_Hit)
        Return
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_bud_EVS_ComboHit = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Call(SetAnimation, ACTOR_SELF, 1, LVar0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Call(GetActorVar, 512, 0, LVar1)
    IfEq(LVar1, 0)
        Call(GetActorVar, ACTOR_SELF, 5, LVar5)
        IfNe(LVar5, 2)
            Call(GetLastDamage, ACTOR_SELF, LVar5)
            IfLt(LVar5, 4)
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 22)
            Else
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 21)
            EndIf
            ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
            Wait(29)
        Else
            Call(GetLastDamage, ACTOR_SELF, LVar5)
            IfLt(LVar5, 4)
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 20)
            Else
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 19)
            EndIf
            ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
            Wait(29)
        EndIf
    Else
        Call(GetActorVar, ACTOR_SELF, 5, LVar5)
        IfEq(LVar5, 1)
            Call(GetLastDamage, ACTOR_SELF, LVar5)
            IfLt(LVar5, 4)
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 22)
            Else
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 21)
            EndIf
            ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
            Wait(29)
        Else
            Call(GetLastDamage, ACTOR_SELF, LVar5)
            IfLt(LVar5, 4)
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 20)
            Else
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 19)
            EndIf
            ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
            Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
            Sub(LVar2, 25)
            Add(LVar3, 2)
            Call(PlayEffect_impl, 112, 0, LVar1, LVar2, LVar3, 40, 50, Float(1.2001953125), 24, 42, Float(0.80078125), Float(0.6005859375), 0, 0)
            Wait(29)
        EndIf
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_bud_EVS_Hit = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Call(SetAnimation, ACTOR_SELF, 1, LVar0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Call(GetActorVar, 512, 0, LVar5)
    IfEq(LVar5, 0)
        Call(GetActorVar, ACTOR_SELF, 5, LVar5)
        IfEq(LVar5, 0)
            Call(GetLastDamage, ACTOR_SELF, LVar5)
            IfLt(LVar5, 4)
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 22)
            Else
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 21)
            EndIf
            ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
            Wait(29)
        Else
            Call(GetLastDamage, ACTOR_SELF, LVar5)
            IfLt(LVar5, 4)
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 20)
            Else
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 19)
            EndIf
            ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
            Wait(29)
        EndIf
    Else
        IfFlag(LVarE, 12)
            Call(GetActorVar, ACTOR_SELF, 5, LVar3)
            IfEq(LVar3, 2)
                Call(GetLastDamage, ACTOR_SELF, LVar5)
                IfLt(LVar5, 4)
                    IfEq(LVar0, 1)
                        Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                    Else
                        Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                    EndIf
                    Call(LoadBattleDmaData, 20)
                Else
                    IfEq(LVar0, 1)
                        Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                    Else
                        Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                    EndIf
                    Call(LoadBattleDmaData, 19)
                EndIf
                ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
                Wait(29)
            Else
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 21)
                ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
                Call(SetActorVar, ACTOR_SELF, 11, 2)
                Call(GetActorVar, ACTOR_SELF, 6, LVar0)
                IfNe(LVar0, 0)
                    Call(RemoveEffect, LVar0)
                    Call(SetActorVar, ACTOR_SELF, 6, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(PlayEffect_impl, 111, 0, LVar0, LVar1, LVar2, Float(2.0), 45, 0, 0, 0, 0, 0, 0, 0)
                EndIf
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_kzn2_lava_bud_StunnedAnims))
                Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kzn2_lava_bud_StunnedDefense))
                Call(SetDefenseTable, ACTOR_SELF, 2, Ref(b_area_kzn2_lava_bud_StunnedDefense))
                Call(SetActorVar, ACTOR_SELF, 7, 0x7B000F)
                Call(SetActorVar, ACTOR_SELF, 8, 0x7B0009)
                Call(SetAnimation, ACTOR_SELF, 1, 0x7B000F)
                Call(SetPartEventBits, ACTOR_SELF, 1, 2, 0)
                Call(SetPartEventBits, ACTOR_SELF, 2, 2, 0)
                Wait(29)
                Call(PlaySoundAtActor, ACTOR_SELF, 967)
                Call(GetActorVar, ACTOR_SELF, 0, LVar0)
                IfEq(LVar0, 1)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                Else
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                EndIf
                Call(LoadBattleDmaData, 27)
                ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
                Wait(14)
                Call(SetActorVar, ACTOR_SELF, 5, 2)
            EndIf
        Else
            Call(GetActorVar, ACTOR_SELF, 5, LVar3)
            IfEq(LVar3, 2)
                Call(GetLastDamage, ACTOR_SELF, LVar5)
                IfEq(LVar5, 0)
                    Return
                EndIf
                Call(GetLastDamage, ACTOR_SELF, LVar5)
                IfLt(LVar5, 4)
                    IfEq(LVar0, 1)
                        Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                    Else
                        Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                    EndIf
                    Call(LoadBattleDmaData, 20)
                Else
                    IfEq(LVar0, 1)
                        Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                    Else
                        Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                    EndIf
                    Call(LoadBattleDmaData, 19)
                EndIf
                ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
                Wait(29)
            Else
                Call(GetLastDamage, ACTOR_SELF, LVar5)
                IfLt(LVar5, 4)
                    IfEq(LVar0, 1)
                        Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                    Else
                        Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                    EndIf
                    Call(LoadBattleDmaData, 22)
                Else
                    IfEq(LVar0, 1)
                        Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
                    Else
                        Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
                    EndIf
                    Call(LoadBattleDmaData, 21)
                EndIf
                ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
                Sub(LVar2, 25)
                Add(LVar3, 2)
                Call(PlayEffect_impl, 112, 0, LVar1, LVar2, LVar3, 40, 50, Float(1.2001953125), 24, 42, Float(0.80078125), Float(0.6005859375), 0, 0)
                Wait(29)
            EndIf
        EndIf
    EndIf
    Call(GetActorVar, 512, 1, LVarF)
    IfEq(LVarF, 0)
        ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayIdleAnimation)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kzn2_lava_bud_EVS_Attack_SpitPetit = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Thread
        Wait(8)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar1, 25)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 350)
        Call(SetBattleCamOffsetY, 30)
        Call(MoveBattleCamOver, 30)
        Wait(45)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 20)
    EndThread
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
    Else
        Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
    EndIf
    Call(LoadBattleDmaData, 18)
    ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
    Thread
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7B0005)
        Wait(39)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7B0006)
        Wait(5)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7B0003)
        IfEq(LVar0, 1)
            Call(OverrideBattleDmaDest, (Bytecode) VINE_1_BASE)
        Else
            Call(OverrideBattleDmaDest, (Bytecode) VINE_2_BASE)
        EndIf
        Call(LoadBattleDmaData, 31)
        ExecWait(TTYD64_kzn2_lava_bud_EVS_PlayAnimForVine)
    EndThread
    Wait(56)
    Call(SummonEnemy, Ref(b_area_kzn2_lava_bud_PetitBombFormation), 0)
    Set(LVar5, LVar0)
    Call(GetPartOffset, ACTOR_SELF, 1, LVar0, LVar1, LVar2)
    Sub(LVar0, 15)
    Sub(LVar1, 15)
    Call(SetActorPos, LVar5, LVar0, LVar1, LVar2)
    Sub(LVar0, 30)
    Sub(LVar1, 15)
    Call(SetAnimation, LVar5, 1, 0x7A0005)
    Call(SetGoalPos, LVar5, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, LVar5, Float(6.0))
    Call(SetActorJumpGravity, LVar5, Float(1.80078125))
    Call(PlaySoundAtActor, LVar5, 971)
    Call(TTYD64_SetTargetActorInFront, LVar5, 0)
    Call(SetGoalToTarget, LVar5)
    Call(EnemyTestTarget, LVar5, LVar9, 0, 0, 1, 16)
    Switch(LVar9)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(SetGoalToTarget, LVar5)
            Call(GetGoalPos, LVar5, LVar0, LVar1, LVar2)
            Set(LVar0, -180)
            Call(SetGoalPos, LVar5, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, LVar5, Float(13.0))
            Call(SetActorJumpGravity, LVar5, Float(1.80078125))
            Call(FlyToGoal, LVar5, 0, 0, 0)
            IfEq(LVar9, 5)
                Call(EnemyTestTarget, LVar5, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(RemoveActor, LVar5)
            Return
        EndCaseGroup
    EndSwitch
    Call(TTYD64_SetTargetActorInFront, LVar5, 0)
    Call(SetGoalToTarget, LVar5)
    Call(SetActorSpeed, LVar5, Float(13.0))
    Call(SetActorJumpGravity, LVar5, Float(1.80078125))
    Call(FlyToGoal, LVar5, 0, 0, 0)
    Wait(2)
    Call(SetGoalToTarget, LVar5)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar9, 2, 0xFFFF, 0, 4, 32)
    Switch(LVar9)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(SetPartFlagBits, LVar5, 1, 1, 1)
            Call(SetGoalToTarget, LVar5)
            Call(GetGoalPos, LVar5, LVar0, LVar1, LVar2)
            Set(LVar1, 10)
            Add(LVar2, 2)
            Call(PlayEffect_impl, 32, 2, LVar0, LVar1, LVar2, Float(0.30078125), LVarA, 0, 0, 0, 0, 0, 0, 0)
            Call(MakeLerp, 120, 10, 20, 1)
            Loop(0)
                Call(UpdateLerp)
                MulF(LVar0, Float(0.0107421875))
                Call(b_area_kzn2_lava_bud_SetPetitFlameSize, LVarA, LVar0)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
            Wait(1)
            Call(RemoveEffect, LVarA)
            Call(RemoveActor, LVar5)
            Wait(15)
            IfEq(LVar9, 10)
                Return
            EndIf
            Call(UseBattleCamPreset, 2)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

FormationRow TTYD64_kzn2_Formation_00[] = {
    { .actor = &TTYD64_kzn2_lava_piranha,
      .home = { .vec = &b_area_kzn2_lava_piranha_pos },
      .priority = 60,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kzn2_Formation_01[] = {
    { .actor = &TTYD64_kzn2_petit_piranha,
      .home = { .vec = &b_area_kzn2_petit_piranha_pos1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_kzn2_petit_piranha,
      .home = { .vec = &b_area_kzn2_petit_piranha_pos2 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

Battle TTYD64_kzn2_Formations[] = {
    { .name = "\203t\203@\203C\203A\203p\203b\203N\203\223",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_kzn2_Formation_00,
      .stage = &b_area_kzn2_kzn_05,
      .onBattleStart = NULL },
    { .name = "\203v\203`\203p\203b\203N\203\223",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kzn2_Formation_01,
      .stage = &b_area_kzn2_kzn_05,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_kzn2_lava_piranha_EVS_Attack_FireBreath = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Thread
        Wait(8)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, 80, 70, 0)
        Call(SetBattleCamDist, 300)
        Call(SetBattleCamOffsetY, 30)
        Call(MoveBattleCamOver, 45)
        Wait(54)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 15)
    EndThread
    Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
    Call(LoadBattleDmaData, 2)
    Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
    Wait(14)
    Call(SetAnimation, ACTOR_SELF, 1, 0x79000E)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 961)
    Wait(45)
    Call(SetAnimation, ACTOR_SELF, 1, 0x790008)
    Call(GetPartOffset, ACTOR_SELF, 1, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Set(LVar1, -10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(TTYD64_GetPartnerHP_API, LVar6)
    IfGt(LVar6, 0)
        Add(LVar3, -64)
    EndIf
    Call(PlayEffect_impl, 99, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.0), 16, 40, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 964)
    Wait(15)
    Thread
        Wait(24)
        Call(PlayEffect_impl, 112, 0, LVar3, 0, LVar5, 50, 50, Float(1.0), 40, 55, Float(1.0), Float(1.0), 0, 0)
    EndThread
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 2, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarB, 2, 0, 1, 16)
            Switch(LVarB)
                CaseOrEq(6)
                CaseOrEq(5)
                    Wait(20)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                    Call(LoadBattleDmaData, 3)
                    Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x790007)
                    Wait(19)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x790004)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                    Call(LoadBattleDmaData, 0)
                    Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
                    IfEq(LVarA, 5)
                        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
                        Call(SetGoalToTarget, ACTOR_SELF)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    IfEq(LVarB, 5)
                        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                        Call(SetGoalToTarget, ACTOR_SELF)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    Wait(15)
                    Call(UseBattleCamPreset, 2)
                    Call(EnableIdleScript, ACTOR_SELF, 1)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
                EndCaseGroup
                CaseDefault
                    Wait(2)
                    Thread
                        IfEq(LVarA, 5)
                            Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
                            Call(SetGoalToTarget, ACTOR_SELF)
                            Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                        EndIf
                    EndThread
                    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 2, 0xFFFF, 0, 7, 32)
                    Wait(20)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                    Call(LoadBattleDmaData, 3)
                    Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x790007)
                    Wait(19)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x790004)
                    Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
                    Call(LoadBattleDmaData, 0)
                    Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
                    IfEq(LVarF, 10)
                        Return
                    EndIf
                    Call(UseBattleCamPreset, 2)
                    Call(EnableIdleScript, ACTOR_SELF, 1)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
            EndSwitch
        EndCaseGroup
    EndSwitch
    Wait(2)
    Thread
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyTestTarget, ACTOR_SELF, LVarB, 2, 0, 1, 16)
        Switch(LVarB)
            CaseOrEq(6)
            CaseOrEq(5)
                IfEq(LVarB, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
            EndCaseGroup
            CaseDefault
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 2, 0xFFFF, 0, 7, 32)
        EndSwitch
    EndThread
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 2, 0xFFFF, 0, 7, 32)
    Wait(20)
    Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
    Call(LoadBattleDmaData, 3)
    Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
    Call(SetAnimation, ACTOR_SELF, 1, 0x790007)
    Wait(19)
    Call(SetAnimation, ACTOR_SELF, 1, 0x790004)
    Call(OverrideBattleDmaDest, (Bytecode) VINE_0_BASE)
    Call(LoadBattleDmaData, 0)
    Call(PlayModelAnimation, 0, (Bytecode) VINE_0_BASE)
    IfEq(LVarF, 10)
        Return
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

void TTYD64_InstallBattles_kzn2(void) {
    Mod_SetBattleList("TTYD64", 23, TTYD64_kzn2_Formations);
}
