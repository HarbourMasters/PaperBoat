#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_drop_tables.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/battle/area/battles_new.h"

API_CALLABLE(b_area_kmr_part_1_paragoomba_StartRumbleWithParams);
API_CALLABLE(b_area_trd_part_2_fake_bowser_SetModelTintMode);
API_CALLABLE(b_area_trd_part_2_fake_bowser_SetModelTintParams);
extern u8 FakeBowserAnimState[];
extern s32 b_area_dgb_tubba_blubba_DefenseTable[];
extern EvtScript b_area_kmr_part_1_kmr_02_EVS_PostBattle;
extern s32 b_area_kmr_part_3_final_jr_troopa_BaseDefenseTable[];
extern EvtScript b_area_kmr_part_3_kpa_13_EVS_PreBattle;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_BlockArm;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathRightArm;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathShell;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_HurtBody;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_IdleBody;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_IdleFeet;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_MoveBody;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_MoveFeet;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_SpawnDamageFX;
extern u8 b_area_trd_part_2_fake_bowser_IdleBodyOffsets[];
extern u8 b_area_trd_part_2_fake_bowser_IdleFeetOffsets[];
extern s32 b_area_trd_part_2_fake_bowser_PlaceholderAnims[];
extern s32 b_area_trd_part_2_fake_bowser_StatusTable[];
API_CALLABLE(ActorSpeak);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableModel);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(ForceHomePos);
API_CALLABLE(FreezeBattleState);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetEnemyMaxHP);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartPos);
API_CALLABLE(GetPartRotation);
API_CALLABLE(GetPlayerHP);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HealActor);
API_CALLABLE(HideHealthBar);
API_CALLABLE(JumpPartTo);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlaySoundAtModel);
API_CALLABLE(RandInt);
API_CALLABLE(RotateGroup);
API_CALLABLE(RotateModel);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetDefenseTable);
API_CALLABLE(SetEnemyHP);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetModelFlags);
API_CALLABLE(SetPartDispOffset);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartRotation);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartTargetFlagBits);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(ShakeCam);
API_CALLABLE(TranslateGroup);
API_CALLABLE(UseIdleAnimation);
extern EvtScript TTYD64_imp_FakeBowser2_Script_Idle_FakeBowser2;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Attack_Bomb;
extern EvtScript TTYD64_imp_FakeBowser2_Script_HandleEvent_FakeBowser2;
extern s32 TTYD64_imp_FakeBowser2_IntTable_MachineGun_ArmRecoil_OffsetTable[];
extern EvtScript TTYD64_imp_FakeBowser2_Script_MachineGun_ShootBullets;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Attack_MachineGun;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_Head;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Attack_LeftArm_A;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Attack_LeftArm_B;
extern EvtScript TTYD64_imp_FakeBowser2_Script_TakeTurn_FakeBowser2;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Attack_FireBreath;
extern EvtScript TTYD64_imp_FakeBowser2_Script_MachineGun_UpdateCannonRotation;
extern s32 TTYD64_imp_FakeBowser2_IntTable_FireBreath_Arms_OffsetTable[];
extern s32 TTYD64_imp_FakeBowser2_IntTable_Bomb_Pannel_OffsetTable[];
extern s32 TTYD64_imp_FakeBowser2_IntTable_FireBreath_Head_OffsetTable[];
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Attack_FireBreath_Belly_RotationTable[];
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Attack_FireBreath_Head_RotationTable[];
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Attack_FireBreath_Arms_RotationTable[];
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Attack_LeftArmA_RotationTable[];
extern s32 TTYD64_imp_FakeBowser2_IntTable_Bomb_Body_OffsetTable[];
extern ActorPartBlueprint TTYD64_imp_FakeBowser2_PartsTable_FakeBowser2[];
extern EvtScript TTYD64_imp_FakeBowser2_Script_Init_FakeBowser2;
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Healing_Start_Arms_RotationTable[];
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Healing_Stop_Arms_RotationTable[];
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Healing_Start_Head_RotationTable[];
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_Tail;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_LeftArm;
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Attack0_LeftArm_RotationTable[];
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_Belly;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_WheelsBack;
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Healing_Stop_Head_RotationTable[];
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_FireBreath_UpdateBellyRotation;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_WheelsFront;
extern EvtScript TTYD64_imp_FakeBowser2_Script_NextTurn_FakeBowser2;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_Base;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Hurt_UpdateHeadRotation;
extern s32 TTYD64_imp_FakeBowser2_FloatTable_MachineGun_Arms_RotationTable[];
extern s32 TTYD64_imp_FakeBowser2_FloatTable_StopMachineGun_Arms_RotationTable[];
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_FireBreath_UpdateArmsRotation;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Healing_Stop_UpdateArmsRotation;
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Attack_LeftArmB_RotationTable[];
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_LeftArmB_UpdateLeftArmRotation;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Healing_Stop_UpdateHeadRotation;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_FireBreath_UpdateHeadRotation;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_LeftArmA_UpdateLeftArmRotation;
extern EvtScript TTYD64_imp_FakeBowser2_Script_EndFight;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Attack0_UpdateLeftArmRotation;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Healing_Start_UpdateArmsRotation;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Healing_Step_UpdateArmsRotation;
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Idle_Head_RotationTable[];
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Hurt_Head_RotationTable[];
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_AnyAttack_UpdateBasePos;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_AnyAttack_UpdateBodyPos;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_StopMachineGun_UpdateArmRotation;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_MachineGun_UpdateArmRotation;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Healing_Step_UpdateHeadRotation;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Running_UpdateWheelsRotation;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Healing_Start_UpdateHeadRotation;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_FireBreath_UpdateArmsPos;
extern EvtScript TTYD64_imp_FakeBowser2_Script_HealingMode_Stop;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Idle_UpdateHeadRotation;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Running_UpdateHeadRotation;
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Running_Wheels_RotationTable[];
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_FireBreath_UpdateHeadPos;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Bomb_UpdatePannelPos;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_MachineGun_UpdateArmRecoil;
extern EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Bomb_Recoil;
extern EvtScript TTYD64_imp_FakeBowser2_Script_HealingMode_Start;
extern EvtScript TTYD64_pit_part_11_Script_BeforeBattle_Pit;
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Running_Head_RotationTable[];
extern u8 TTYD64_pit_part_11_String_HealingMode_Start2[];
extern EvtScript TTYD64_imp_FakeBowser2_Script_Attack_LeftArm;
extern s32 TTYD64_imp_FakeBowser2_Data_BurnedModelsTable[];
extern Stage TTYD64_pit_part_11_Stage_Pit1;
extern Stage TTYD64_pit_part_11_Stage_Pit2;
extern ActorBlueprint TTYD64_imp_FakeBowser2_FakeBowser2;
extern Battle TTYD64_pit_part_11_FormationTable[];
extern u8 TTYD64_pit_part_11_String_HealingMode_Start1[];
extern FormationRow TTYD64_pit_part_11_Formation_Bowser[];
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Healing_Step_Head_RotationTable[];
extern StageListRow TTYD64_pit_part_11_StageTable[];
extern s32 TTYD64_imp_FakeBowser2_FloatTable_Healing_Step_Arms_RotationTable[];
extern s32 TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser[];
extern s32 TTYD64_imp_FakeBowser2_IdleAnimations_Bomb[];

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Idle_FakeBowser2 = {
    UseArray(Ref(FakeBowserAnimState))
    Set(LVarA, 0)
    Label(0)
    Set(LVar0, ArrayVar(0))
    Switch(LVar0)
        CaseEq(0)
            Set(ArrayVar(0), 1)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_IdleBody)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_IdleFeet)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Idle_UpdateHeadRotation)
        CaseEq(1)
        CaseEq(2)
            Set(ArrayVar(0), 3)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_HurtBody)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Hurt_UpdateHeadRotation)
        CaseEq(3)
        CaseEq(4)
            Set(ArrayVar(0), 5)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_MoveBody)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_MoveFeet)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Running_UpdateHeadRotation)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Running_UpdateWheelsRotation)
        CaseEq(5)
        CaseEq(6)
            Set(ArrayVar(0), 7)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_AnyAttack_UpdateBodyPos)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_AnyAttack_UpdateBasePos)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Attack0_UpdateLeftArmRotation)
        CaseEq(7)
        CaseEq(8)
            Call(PlaySoundAtActor, ACTOR_SELF, 949)
            Set(ArrayVar(0), 9)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_Head)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_Belly)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathShell)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_LeftArm)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathRightArm)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_Tail)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_WheelsFront)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_WheelsBack)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_Base)
            Exec(TTYD64_imp_FakeBowser2_Script_EndFight)
        CaseEq(9)
        CaseEq(10)
            Set(ArrayVar(0), 11)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_AnyAttack_UpdateBodyPos)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_AnyAttack_UpdateBasePos)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_BlockArm)
        CaseEq(11)
        CaseEq(12)
            Set(ArrayVar(0), 13)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_AnyAttack_UpdateBodyPos)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_AnyAttack_UpdateBasePos)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_LeftArmA_UpdateLeftArmRotation)
        CaseEq(13)
        CaseEq(14)
            Set(ArrayVar(0), 15)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_AnyAttack_UpdateBodyPos)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_AnyAttack_UpdateBasePos)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_LeftArmB_UpdateLeftArmRotation)
        CaseEq(15)
        CaseEq(16)
            Set(ArrayVar(0), 17)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_AnyAttack_UpdateBodyPos)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_AnyAttack_UpdateBasePos)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_FireBreath_UpdateHeadPos)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_FireBreath_UpdateArmsPos)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_FireBreath_UpdateBellyRotation)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_FireBreath_UpdateHeadRotation)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_FireBreath_UpdateArmsRotation)
        CaseEq(17)
        CaseEq(18)
            Set(ArrayVar(0), 19)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Bomb_UpdatePannelPos)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Bomb_Recoil)
        CaseEq(19)
        CaseEq(20)
            Set(ArrayVar(0), 21)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_MachineGun_UpdateArmRotation)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_MachineGun_UpdateArmRecoil)
        CaseEq(21)
        CaseEq(22)
            Set(ArrayVar(0), 23)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_StopMachineGun_UpdateArmRotation)
        CaseEq(23)
        CaseEq(24)
            Set(ArrayVar(0), 25)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Healing_Start_UpdateArmsRotation)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Healing_Start_UpdateHeadRotation)
        CaseEq(25)
        CaseEq(26)
            Set(ArrayVar(0), 27)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Healing_Stop_UpdateArmsRotation)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Healing_Stop_UpdateHeadRotation)
        CaseEq(27)
        CaseEq(28)
            Set(ArrayVar(0), 29)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Healing_Step_UpdateArmsRotation)
            Exec(TTYD64_imp_FakeBowser2_Script_Animation_Healing_Step_UpdateHeadRotation)
        CaseEq(29)
    EndSwitch
    Call(GetPartPos, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 27, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Call(RotateGroup, 27, LVar0, 1, 0, 0)
    Call(RotateGroup, 27, LVar1, 0, 1, 0)
    Call(RotateGroup, 27, LVar2, 0, 0, 1)
    Call(SetModelFlags, 18, 64, 1)
    Call(SetModelFlags, 19, 64, 1)
    Call(SetModelFlags, 20, 64, 1)
    Call(SetModelFlags, 21, 64, 1)
    Call(SetModelFlags, 22, 64, 1)
    Call(SetModelFlags, 23, 64, 1)
    Call(SetModelFlags, 24, 64, 1)
    Call(SetModelFlags, 25, 64, 1)
    Call(SetModelFlags, 26, 64, 1)
    Call(GetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 36, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(RotateGroup, 36, LVar0, 1, 0, 0)
    Call(RotateGroup, 36, LVar1, 0, 1, 0)
    Call(RotateGroup, 36, LVar2, 0, 0, 1)
    Call(SetModelFlags, 33, 64, 1)
    Call(SetModelFlags, 34, 64, 1)
    Call(SetModelFlags, 35, 64, 1)
    Call(GetPartPos, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 32, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
    Call(RotateGroup, 32, LVar0, 1, 0, 0)
    Call(RotateGroup, 32, LVar1, 0, 1, 0)
    Call(RotateGroup, 32, LVar2, 0, 0, 1)
    Call(SetModelFlags, 28, 64, 1)
    Call(SetModelFlags, 29, 64, 1)
    Call(SetModelFlags, 30, 64, 1)
    Call(SetModelFlags, 31, 64, 1)
    Call(GetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 17, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 52, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(RotateGroup, 17, LVar0, 1, 0, 0)
    Call(RotateGroup, 17, LVar1, 0, 1, 0)
    Call(RotateGroup, 17, LVar2, 0, 0, 1)
    Call(SetModelFlags, 14, 64, 1)
    Call(SetModelFlags, 15, 64, 1)
    Call(SetModelFlags, 16, 64, 1)
    Call(GetPartPos, ACTOR_SELF, 7, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 13, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 7, LVar0, LVar1, LVar2)
    Call(RotateGroup, 13, LVar0, 1, 0, 0)
    Call(RotateGroup, 13, LVar1, 0, 1, 0)
    Call(RotateGroup, 13, LVar2, 0, 0, 1)
    Call(SetModelFlags, 12, 64, 1)
    Set(LVar0, ArrayVar(0))
    IfEq(LVar0, 9)
        Call(GetPartPos, ACTOR_SELF, 8, LVar0, LVar1, LVar2)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 0)
    EndIf
    Call(SetPartPos, ACTOR_SELF, 8, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 46, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 8, LVar0, LVar1, LVar2)
    Call(RotateGroup, 46, LVar0, 1, 0, 0)
    Call(RotateGroup, 46, LVar1, 0, 1, 0)
    Call(RotateGroup, 46, LVar2, 0, 0, 1)
    Call(SetModelFlags, 45, 64, 1)
    Set(LVar0, ArrayVar(0))
    IfEq(LVar0, 9)
        Call(GetPartPos, ACTOR_SELF, 9, LVar0, LVar1, LVar2)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 0)
    EndIf
    Call(SetPartPos, ACTOR_SELF, 9, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 48, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 9, LVar0, LVar1, LVar2)
    Call(RotateGroup, 48, LVar0, 1, 0, 0)
    Call(RotateGroup, 48, LVar1, 0, 1, 0)
    Call(RotateGroup, 48, LVar2, 0, 0, 1)
    Call(SetModelFlags, 47, 64, 1)
    Call(GetPartPos, ACTOR_SELF, 11, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 40, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 11, LVar0, LVar1, LVar2)
    Call(RotateGroup, 40, LVar0, 1, 0, 0)
    Call(RotateGroup, 40, LVar1, 0, 1, 0)
    Call(RotateGroup, 40, LVar2, 0, 0, 1)
    Call(SetModelFlags, 37, 64, 1)
    Call(SetModelFlags, 38, 64, 1)
    Call(SetModelFlags, 39, 64, 1)
    Call(GetPartPos, ACTOR_SELF, 10, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 44, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 10, LVar0, LVar1, LVar2)
    Call(RotateGroup, 44, LVar0, 1, 0, 0)
    Call(RotateGroup, 44, LVar1, 0, 1, 0)
    Call(RotateGroup, 44, LVar2, 0, 0, 1)
    Call(SetModelFlags, 41, 64, 1)
    Call(SetModelFlags, 42, 64, 1)
    Call(SetModelFlags, 43, 64, 1)
    Call(GetPartPos, ACTOR_SELF, 12, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 49, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 12, LVar0, LVar1, LVar2)
    Call(RotateGroup, 49, LVar0, 1, 0, 0)
    Call(RotateGroup, 49, LVar1, 0, 1, 0)
    Call(RotateGroup, 49, LVar2, 0, 0, 1)
    Call(SetModelFlags, 49, 64, 1)
    Call(GetPartPos, ACTOR_SELF, 14, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 53, LVar0, LVar1, LVar2)
    Call(GetPartPos, ACTOR_SELF, 15, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 55, LVar0, LVar1, LVar2)
    Call(GetPartPos, ACTOR_SELF, 16, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 57, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 14, LVar0, LVar1, LVar2)
    Call(RotateGroup, 53, LVar0, 1, 0, 0)
    Call(RotateGroup, 53, LVar1, 0, 1, 0)
    Call(RotateGroup, 53, LVar2, 0, 0, 1)
    Call(GetPartRotation, ACTOR_SELF, 15, LVar0, LVar1, LVar2)
    Call(RotateGroup, 55, LVar0, 1, 0, 0)
    Call(RotateGroup, 55, LVar1, 0, 1, 0)
    Call(RotateGroup, 55, LVar2, 0, 0, 1)
    Call(GetPartRotation, ACTOR_SELF, 16, LVar0, LVar1, LVar2)
    Call(RotateGroup, 57, LVar0, 1, 0, 0)
    Call(RotateGroup, 57, LVar1, 0, 1, 0)
    Call(RotateGroup, 57, LVar2, 0, 0, 1)
    Call(SetModelFlags, 53, 64, 1)
    Call(SetModelFlags, 55, 64, 1)
    Call(SetModelFlags, 57, 64, 1)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfNotFlag(LVar0, 2)
        Call(GetActorHP, ACTOR_SELF, LVar0)
        Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
        Mul(LVar0, 100)
        Div(LVar0, LVar1)
        Switch(LVar0)
            CaseEq(0)
            CaseLt(20)
                IfGt(LVarA, 20)
                    Exec(b_area_trd_part_2_fake_bowser_EVS_SpawnDamageFX)
                    Set(LVarA, 0)
                EndIf
            CaseLt(40)
                IfGt(LVarA, 40)
                    Exec(b_area_trd_part_2_fake_bowser_EVS_SpawnDamageFX)
                    Set(LVarA, 0)
                EndIf
            CaseLt(60)
                IfGt(LVarA, 60)
                    Exec(b_area_trd_part_2_fake_bowser_EVS_SpawnDamageFX)
                    Set(LVarA, 0)
                EndIf
            CaseLt(80)
                IfGt(LVarA, 80)
                    Exec(b_area_trd_part_2_fake_bowser_EVS_SpawnDamageFX)
                    Set(LVarA, 0)
                EndIf
        EndSwitch
        Add(LVarA, 1)
    EndIf
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Attack_Bomb = {
    UseArray(Ref(FakeBowserAnimState))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Set(ArrayVar(0), 18)
    Thread
        Wait(5)
        Call(PlaySound, 123)
        Wait(60)
        Call(PlaySound, 123)
    EndThread
    Call(EnableModel, 35, 0)
    Call(EnableModel, 49, 1)
    Wait(22)
    Call(SetPartScale, ACTOR_SELF, 13, Float(1.400390625), Float(1.400390625), Float(1.400390625))
    Call(GetModelCenter, 35)
    Add(LVar0, 10)
    Add(LVar1, -20)
    Call(SetPartPos, ACTOR_SELF, 13, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 13, 1, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -12, 0, 0)
    Call(RandInt, 2, LVarD)
    Call(GetStatusFlags, 0, LVar0)
    IfNe(LVarD, 0)
        IfFlag(LVar0, 0x257000)
            Set(LVarD, 0)
        EndIf
    EndIf
    Call(GetStatusFlags, 256, LVar0)
    IfNe(LVarD, 0)
        IfFlag(LVar0, 0x257000)
            Set(LVarD, 0)
        EndIf
    EndIf
    Switch(LVarD)
        CaseEq(0)
            Call(SetAnimation, ACTOR_SELF, 13, 0x770001)
            Set(LVarE, 2)
        CaseEq(1)
            Call(SetAnimation, ACTOR_SELF, 13, 0x770301)
            Set(LVarE, 2)
            Call(TTYD64_SetPoisonDrive, 1)
        CaseEq(2)
            Call(SetAnimation, ACTOR_SELF, 13, 0x770401)
            Set(LVarE, 8)
    EndSwitch
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartJumpGravity, ACTOR_SELF, 13, Float(1.0))
    Call(PlaySound, 1018)
    Call(JumpPartTo, ACTOR_SELF, 13, LVar0, LVar1, LVar2, 11, 0)
    Call(PlayEffect_impl, 25, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 13, 1, 1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Wait(2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Switch(LVarD)
                CaseEq(0)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 2, 0xFFFF, 0, 6, 32)
                CaseEq(1)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 2, 0xFFFF, -0x7FFDF99C, 6, 32)
                CaseEq(2)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 8, 0xFFFF, -0x7FFFBE9C, 6, 32)
            EndSwitch
            Switch(LVarF)
                CaseOrEq(0)
                CaseOrEq(2)
                CaseOrEq(10)
                EndCaseGroup
            EndSwitch
    EndSwitch
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(40)
            Call(TTYD64_SetPoisonDrive, 0)
            Set(ArrayVar(0), 0)
            Call(EnableModel, 35, 1)
            Call(EnableModel, 49, 0)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Switch(LVarD)
                CaseEq(0)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 2, 0xFFFF, 0, 6, 32)
                CaseEq(1)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 2, 0xFFFF, -0x7FFDF99C, 6, 32)
                CaseEq(2)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 8, 0xFFFF, -0x7FFFBE9C, 6, 32)
            EndSwitch
    EndSwitch
    Call(TTYD64_SetPoisonDrive, 0)
    Wait(40)
    Set(ArrayVar(0), 0)
    Call(EnableModel, 35, 1)
    Call(EnableModel, 49, 0)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_HandleEvent_FakeBowser2 = {
    UseArray(Ref(FakeBowserAnimState))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Set(ArrayVar(0), 2)
            Wait(20)
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            IfEq(LVar0, 1)
                Set(ArrayVar(0), 28)
            Else
                Set(ArrayVar(0), 0)
            EndIf
        CaseEq(10)
            Set(ArrayVar(0), 2)
            Wait(20)
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            IfEq(LVar0, 1)
                Set(ArrayVar(0), 28)
            Else
                Set(ArrayVar(0), 0)
            EndIf
        CaseOrEq(23)
        CaseOrEq(25)
            Set(ArrayVar(0), 2)
            Wait(20)
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            IfEq(LVar0, 1)
                Set(ArrayVar(0), 28)
            Else
                Set(ArrayVar(0), 0)
            EndIf
        EndCaseGroup
        CaseOrEq(32)
        CaseOrEq(36)
            Call(GetActorVar, ACTOR_SELF, 7, LVar0)
            IfEq(LVar0, 0)
                Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_dgb_tubba_blubba_DefenseTable))
                Call(SetEnemyHP, ACTOR_SELF, 1)
                Return
            EndIf
            Call(HideHealthBar, ACTOR_SELF)
            IfEq(LVar0, 36)
                Call(b_area_trd_part_2_fake_bowser_SetModelTintMode, 0, Ref(TTYD64_imp_FakeBowser2_Data_BurnedModelsTable), 3)
                Call(b_area_trd_part_2_fake_bowser_SetModelTintParams, 3, 35, 35, 35, 0, 0, 0, 0, 0, 0)
            EndIf
            Set(ArrayVar(0), 2)
            Wait(20)
            IfEq(LVar0, 36)
                Call(b_area_trd_part_2_fake_bowser_SetModelTintMode, 0, Ref(TTYD64_imp_FakeBowser2_Data_BurnedModelsTable), 0)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(GetActorSize, ACTOR_SELF, LVar3, LVar4)
                DivF(LVar3, Float(2.0))
                AddF(LVar1, LVar3)
                AddF(LVar2, Float(5.0))
                DivF(LVar3, Float(10.0))
                Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
                Wait(5)
                Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
            EndIf
            Wait(30)
            Set(ArrayVar(0), 0)
            Wait(30)
            Set(ArrayVar(0), 24)
            Call(ActorSpeak, 0, ACTOR_SELF, 1, -1, -1)
            Set(ArrayVar(0), 2)
            Wait(40)
            Set(ArrayVar(0), 8)
            Label(20)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Wait(1)
            IfNotFlag(LVar0, 1)
                Goto(20)
            EndIf
            Wait(20)
            Return
        EndCaseGroup
        CaseOrEq(44)
        CaseOrEq(14)
            Call(b_area_trd_part_2_fake_bowser_SetModelTintMode, 0, Ref(TTYD64_imp_FakeBowser2_Data_BurnedModelsTable), 3)
            Call(b_area_trd_part_2_fake_bowser_SetModelTintParams, 3, 35, 35, 35, 0, 0, 0, 0, 0, 0)
            Set(ArrayVar(0), 2)
            Wait(20)
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            IfEq(LVar0, 1)
                Set(ArrayVar(0), 28)
            Else
                Set(ArrayVar(0), 0)
            EndIf
            Call(b_area_trd_part_2_fake_bowser_SetModelTintMode, 0, Ref(TTYD64_imp_FakeBowser2_Data_BurnedModelsTable), 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetActorSize, ACTOR_SELF, LVar3, LVar4)
            DivF(LVar3, Float(2.0))
            AddF(LVar1, LVar3)
            AddF(LVar2, Float(5.0))
            DivF(LVar3, Float(10.0))
            Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
            Wait(5)
            Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
        EndCaseGroup
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_FakeBowser2_IntTable_MachineGun_ArmRecoil_OffsetTable[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 2, 0, 0, 0,   0,   0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 2, 0,   0,   0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0,   2,   0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255,
};

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_MachineGun_ShootBullets = {
    Call(EnableModel, 53, 1)
    Call(EnableModel, 55, 1)
    Call(EnableModel, 57, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 14, 0x100000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 15, 0x100000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 16, 0x100000, 1)
    Call(GetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Add(LVar0, 150)
    Add(LVar1, 60)
    Add(LVar2, 0)
    Call(SetPartPos, ACTOR_SELF, 14, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 15, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 16, LVar0, LVar1, LVar2)
    Call(SetPartDispOffset, ACTOR_SELF, 14, 54, -63, 0)
    Call(SetPartDispOffset, ACTOR_SELF, 15, 54, -63, 0)
    Call(SetPartDispOffset, ACTOR_SELF, 16, 54, -63, 0)
    Call(SetPartPos, ACTOR_SELF, 14, -3, 126, 26)
    Call(SetPartPos, ACTOR_SELF, 15, -3, 126, 26)
    Call(SetPartPos, ACTOR_SELF, 16, -3, 126, 26)
    Wait(60)
    Call(SetPartJumpGravity, ACTOR_SELF, 14, Float(0.900390625))
    Call(SetPartJumpGravity, ACTOR_SELF, 15, Float(0.900390625))
    Call(SetPartJumpGravity, ACTOR_SELF, 16, Float(0.900390625))
    Thread
        Loop(0)
            Call(GetPartRotation, ACTOR_SELF, 14, LVar0, LVar1, LVar2)
            AddF(LVar2, Float(-30.0))
            Call(SetPartRotation, ACTOR_SELF, 14, LVar0, LVar1, LVar2)
            Wait(1)
            Call(GetPartPos, ACTOR_SELF, 14, LVar0, LVar1, LVar2)
            IfLe(LVar1, -15)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Thread
        Set(LVar0, 76)
        Call(RandInt, 58, LVar1)
        Add(LVar0, LVar1)
        Call(JumpPartTo, ACTOR_SELF, 14, LVar0, -15, 50, 30, 0)
    EndThread
    Wait(12)
    Thread
        Loop(0)
            Call(GetPartRotation, ACTOR_SELF, 15, LVar0, LVar1, LVar2)
            AddF(LVar2, Float(-30.0))
            Call(SetPartRotation, ACTOR_SELF, 15, LVar0, LVar1, LVar2)
            Wait(1)
            Call(GetPartPos, ACTOR_SELF, 15, LVar0, LVar1, LVar2)
            IfLe(LVar1, -15)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Thread
        Set(LVar0, 76)
        Call(RandInt, 58, LVar1)
        Add(LVar0, LVar1)
        Call(JumpPartTo, ACTOR_SELF, 15, LVar0, -15, 50, 30, 0)
    EndThread
    Wait(12)
    Thread
        Loop(0)
            Call(GetPartRotation, ACTOR_SELF, 16, LVar0, LVar1, LVar2)
            AddF(LVar2, Float(-30.0))
            Call(SetPartRotation, ACTOR_SELF, 16, LVar0, LVar1, LVar2)
            Wait(1)
            Call(GetPartPos, ACTOR_SELF, 16, LVar0, LVar1, LVar2)
            IfLe(LVar1, -15)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Thread
        Set(LVar0, 76)
        Call(RandInt, 58, LVar1)
        Add(LVar0, LVar1)
        Call(JumpPartTo, ACTOR_SELF, 16, LVar0, -15, 50, 30, 0)
    EndThread
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Attack_MachineGun = {
    UseArray(Ref(FakeBowserAnimState))
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 0)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Set(ArrayVar(0), 20)
    Thread
        Wait(15)
        Call(PlaySoundAtActor, ACTOR_SELF, 8445)
        Wait(88)
        Call(PlaySoundAtActor, ACTOR_SELF, 429)
        Wait(12)
        Call(PlaySoundAtActor, ACTOR_SELF, 429)
        Wait(12)
        Call(PlaySoundAtActor, ACTOR_SELF, 429)
        Wait(50)
        Call(PlaySoundAtActor, ACTOR_SELF, 8445)
    EndThread
    Wait(40)
    Call(EnableModel, 51, 1)
    Call(EnableModel, 14, 0)
    Exec(TTYD64_imp_FakeBowser2_Script_MachineGun_UpdateCannonRotation)
    Exec(TTYD64_imp_FakeBowser2_Script_MachineGun_ShootBullets)
    Wait(60)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVar0, 5)
                Thread
                    Wait(15)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndThread
            EndIf
            Call(SetActorVar, ACTOR_SELF, 6, 1)
        EndCaseGroup
    EndSwitch
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    IfEq(LVar0, 0)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8192, 0xFFFF, 0, 4, 64)
    EndIf
    Wait(12)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetOwnerTarget, LVar0, 0)
    IfEq(LVar0, 0)
        Call(GetPlayerHP, LVar0)
    Else
        Call(TTYD64_GetPartnerHP_API, LVar0)
    EndIf
    IfGt(LVar0, 0)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetActorVar, ACTOR_SELF, 6, LVar0)
        IfEq(LVar0, 0)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8192, 0xFFFF, 0, 4, 64)
        EndIf
    EndIf
    Wait(12)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetOwnerTarget, LVar0, 0)
    IfEq(LVar0, 0)
        Call(GetPlayerHP, LVar0)
    Else
        Call(TTYD64_GetPartnerHP_API, LVar0)
    EndIf
    IfGt(LVar0, 0)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetActorVar, ACTOR_SELF, 6, LVar0)
        IfEq(LVar0, 0)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8192, 0xFFFF, 0, 4, 64)
        EndIf
    EndIf
    Wait(6)
    Call(SetActorVar, ACTOR_SELF, 5, 1)
    Wait(35)
    Call(EnableModel, 51, 0)
    Call(EnableModel, 14, 1)
    Set(ArrayVar(0), 22)
    Wait(25)
    Set(ArrayVar(0), 0)
    Call(EnableModel, 53, 0)
    Call(EnableModel, 55, 0)
    Call(EnableModel, 57, 0)
    Call(SetPartDispOffset, ACTOR_SELF, 14, 0, 0, 0)
    Call(SetPartDispOffset, ACTOR_SELF, 15, 0, 0, 0)
    Call(SetPartDispOffset, ACTOR_SELF, 16, 0, 0, 0)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_Head = {
    UseArray(Ref(FakeBowserAnimState))
    Call(b_area_kmr_part_1_paragoomba_StartRumbleWithParams, 256, 30)
    Thread
        SetGroup(0)
        Call(ShakeCam, 1, 0, 20, Float(3.0))
    EndThread
    Call(SetPartFlagBits, ACTOR_SELF, 5, 0x100000, 1)
    Call(GetPartPos, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Call(SetPartDispOffset, ACTOR_SELF, 5, 0, -60, 0)
    Set(LVar1, 60)
    Call(SetPartPos, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Loop(60)
            Add(LVar0, 20)
            Call(SetPartRotation, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Sub(LVar0, 60)
    Set(LVar1, -200)
    Add(LVar2, 100)
    Call(SetPartJumpGravity, ACTOR_SELF, 5, Float(0.5))
    Call(JumpPartTo, ACTOR_SELF, 5, LVar0, LVar1, LVar2, 60, 1)
    Wait(30)
    Call(PlaySoundAtModel, 18, 482, 0)
    Thread
        SetGroup(0)
        Call(ShakeCam, 1, 0, 5, Float(1.0))
    EndThread
    Call(b_area_kmr_part_1_paragoomba_StartRumbleWithParams, 100, 20)
    Wait(20)
    Call(PlaySoundAtModel, 14, 482, 0)
    Thread
        SetGroup(0)
        Call(ShakeCam, 1, 0, 10, Float(1.5))
    EndThread
    Call(b_area_kmr_part_1_paragoomba_StartRumbleWithParams, 150, 20)
    Wait(30)
    Call(PlaySoundAtModel, 12, 482, 0)
    Thread
        SetGroup(0)
        Call(ShakeCam, 1, 0, 10, Float(1.0))
    EndThread
    Call(b_area_kmr_part_1_paragoomba_StartRumbleWithParams, 100, 20)
    Wait(30)
    Call(PlaySoundAtModel, 33, 482, 0)
    Thread
        SetGroup(0)
        Call(ShakeCam, 1, 0, 5, Float(0.7001953125))
    EndThread
    Call(b_area_kmr_part_1_paragoomba_StartRumbleWithParams, 70, 20)
    Wait(20)
    Call(PlaySoundAtModel, 28, 482, 0)
    Thread
        SetGroup(0)
        Call(ShakeCam, 1, 0, 10, Float(1.0))
    EndThread
    Call(b_area_kmr_part_1_paragoomba_StartRumbleWithParams, 100, 20)
    Wait(20)
    Call(PlaySoundAtModel, 45, 482, 0)
    Call(b_area_kmr_part_1_paragoomba_StartRumbleWithParams, 60, 20)
    Thread
        SetGroup(0)
        Call(ShakeCam, 1, 0, 5, Float(0.599609375))
    EndThread
    Wait(20)
    Thread
        SetGroup(0)
        Call(ShakeCam, 1, 0, 5, Float(0.2998046875))
    EndThread
    Call(b_area_kmr_part_1_paragoomba_StartRumbleWithParams, 30, 20)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Attack_LeftArm_A = {
    UseArray(Ref(FakeBowserAnimState))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Thread
        Loop(4)
            Call(b_area_kmr_part_1_paragoomba_StartRumbleWithParams, 256, 3)
            Wait(5)
        EndLoop
    EndThread
    Set(ArrayVar(0), 4)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 70, 0, 0)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Set(ArrayVar(0), 0)
    Thread
        Call(PlaySoundAtActor, ACTOR_SELF, 8445)
        Wait(34)
        Call(PlaySoundAtActor, ACTOR_SELF, 8446)
    EndThread
    Set(ArrayVar(0), 12)
    Wait(38)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVar0, 5)
                Thread
                    Wait(15)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndThread
            EndIf
            Wait(8)
            Thread
                Loop(4)
                    Call(b_area_kmr_part_1_paragoomba_StartRumbleWithParams, 256, 5)
                    Wait(8)
                EndLoop
            EndThread
            Set(ArrayVar(0), 4)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Set(ArrayVar(0), 0)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8080000, 0xFFFF, 0, 4, 64)
    Call(GetBattleFlags, LVar0)
    IfFlag(LVar0, (-0x7FFFFFFF - 1))
        Call(GetOwnerTarget, LVar0, 0)
        IfEq(LVar0, 0)
            Call(GetPlayerHP, LVar0)
        Else
            Call(TTYD64_GetPartnerHP_API, LVar0)
        EndIf
        IfNe(LVar0, 0)
            Set(ArrayVar(0), 10)
        EndIf
    EndIf
    Wait(18)
    Thread
        Loop(4)
            Call(b_area_kmr_part_1_paragoomba_StartRumbleWithParams, 256, 5)
            Wait(8)
        EndLoop
    EndThread
    Set(ArrayVar(0), 4)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Set(ArrayVar(0), 0)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Call(GetOwnerTarget, LVar0, 0)
    IfEq(LVar0, 0)
        Call(GetPlayerHP, LVar0)
    Else
        Call(TTYD64_GetPartnerHP_API, LVar0)
    EndIf
    IfLe(LVar0, 0)
        Return
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Attack_LeftArm_B = {
    UseArray(Ref(FakeBowserAnimState))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Thread
        Loop(4)
            Call(b_area_kmr_part_1_paragoomba_StartRumbleWithParams, 256, 3)
            Wait(5)
        EndLoop
    EndThread
    Set(ArrayVar(0), 4)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 70, 0, 0)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Set(ArrayVar(0), 0)
    Thread
        Wait(11)
        Call(PlaySoundAtActor, ACTOR_SELF, 8446)
    EndThread
    Set(ArrayVar(0), 14)
    Wait(21)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVar0, 5)
                Thread
                    Wait(15)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndThread
            EndIf
            Wait(8)
            Thread
                Loop(4)
                    Call(b_area_kmr_part_1_paragoomba_StartRumbleWithParams, 256, 5)
                    Wait(8)
                EndLoop
            EndThread
            Set(ArrayVar(0), 4)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Set(ArrayVar(0), 0)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8080000, 0xFFFF, 0, 4, 64)
    Call(GetBattleFlags, LVar0)
    IfFlag(LVar0, (-0x7FFFFFFF - 1))
        Call(GetOwnerTarget, LVar0, 0)
        IfEq(LVar0, 0)
            Call(GetPlayerHP, LVar0)
        Else
            Call(TTYD64_GetPartnerHP_API, LVar0)
        EndIf
        IfNe(LVar0, 0)
            Set(ArrayVar(0), 10)
        EndIf
    EndIf
    Wait(18)
    Thread
        Loop(4)
            Call(b_area_kmr_part_1_paragoomba_StartRumbleWithParams, 256, 5)
            Wait(8)
        EndLoop
    EndThread
    Set(ArrayVar(0), 4)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Set(ArrayVar(0), 0)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Call(GetOwnerTarget, LVar0, 0)
    IfEq(LVar0, 0)
        Call(GetPlayerHP, LVar0)
    Else
        Call(TTYD64_GetPartnerHP_API, LVar0)
    EndIf
    IfLe(LVar0, 0)
        Return
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_TakeTurn_FakeBowser2 = {
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    IfEq(LVar0, 1)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 7, LVar0)
    IfEq(LVar0, 0)
        Call(GetActorHP, ACTOR_SELF, LVar0)
        IfLe(LVar0, 1)
            ExecWait(TTYD64_imp_FakeBowser2_Script_HealingMode_Start)
            Call(SetActorVar, ACTOR_SELF, 2, 4)
            Return
        EndIf
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_imp_FakeBowser2_Script_Attack_LeftArm)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
        CaseEq(1)
            Call(GetActorVar, ACTOR_SELF, 7, LVar0)
            IfEq(LVar0, 0)
                Call(RandInt, 100, LVar0)
                IfLe(LVar0, 70)
                    ExecWait(TTYD64_imp_FakeBowser2_Script_Attack_LeftArm)
                Else
                    ExecWait(TTYD64_imp_FakeBowser2_Script_Attack_FireBreath)
                    Call(SetActorVar, ACTOR_SELF, 2, 2)
                EndIf
            Else
                ExecWait(TTYD64_imp_FakeBowser2_Script_Attack_Bomb)
                Call(SetActorVar, ACTOR_SELF, 2, 3)
            EndIf
        CaseEq(2)
            Call(GetActorVar, ACTOR_SELF, 7, LVar0)
            IfEq(LVar0, 0)
                Call(GetActorHP, ACTOR_SELF, LVar0)
                Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
                Mul(LVar0, 100)
                Div(LVar0, LVar1)
                IfLe(LVar0, 60)
                    ExecWait(TTYD64_imp_FakeBowser2_Script_Attack_Bomb)
                    Call(SetActorVar, ACTOR_SELF, 2, 3)
                Else
                    ExecWait(TTYD64_imp_FakeBowser2_Script_Attack_LeftArm)
                    Call(SetActorVar, ACTOR_SELF, 2, 1)
                EndIf
            Else
                ExecWait(TTYD64_imp_FakeBowser2_Script_Attack_LeftArm)
                Call(SetActorVar, ACTOR_SELF, 2, 3)
            EndIf
        CaseEq(3)
            Call(GetActorVar, ACTOR_SELF, 7, LVar0)
            IfEq(LVar0, 0)
                ExecWait(TTYD64_imp_FakeBowser2_Script_Attack_LeftArm)
                Call(SetActorVar, ACTOR_SELF, 2, 1)
            Else
                Call(RandInt, 100, LVar0)
                IfGe(LVar0, 60)
                    ExecWait(TTYD64_imp_FakeBowser2_Script_Attack_MachineGun)
                    Call(SetActorVar, ACTOR_SELF, 2, 5)
                Else
                    ExecWait(TTYD64_imp_FakeBowser2_Script_Attack_FireBreath)
                    Call(SetActorVar, ACTOR_SELF, 2, 2)
                EndIf
            EndIf
        CaseEq(4)
            Call(SetActorVar, ACTOR_SELF, 2, 6)
        CaseEq(5)
            ExecWait(TTYD64_imp_FakeBowser2_Script_Attack_LeftArm)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
        CaseEq(6)
            ExecWait(TTYD64_imp_FakeBowser2_Script_Attack_MachineGun)
            Call(SetActorVar, ACTOR_SELF, 2, 5)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Attack_FireBreath = {
    UseArray(Ref(FakeBowserAnimState))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Wait(15)
    Set(ArrayVar(0), 16)
    Call(MoveBattleCamOver, 55)
    Wait(15)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 95)
    Add(LVar1, 42)
    Add(LVar2, 10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 120)
    Set(LVar4, 20)
    Call(PlayEffect_impl, 55, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, 6, 7, 24, 0, 0, 0)
    Thread
        Call(b_area_kmr_part_1_paragoomba_StartRumbleWithParams, 50, 148)
        Call(PlaySound, 957)
        Wait(40)
        Call(PlaySound, 1981)
    EndThread
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Wait(2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x8000002, 0xFFFF, 0, 8, 32)
            Switch(LVarF)
                CaseOrEq(0)
                CaseOrEq(2)
                CaseOrEq(10)
                EndCaseGroup
            EndSwitch
    EndSwitch
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(45)
            Set(ArrayVar(0), 0)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x8000002, 0xFFFF, 0, 8, 32)
    EndSwitch
    Wait(45)
    Set(ArrayVar(0), 0)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_MachineGun_UpdateCannonRotation = {
    SetF(LVar0, Float(0.0))
    Loop(5)
        AddF(LVar0, Float(1.0))
        Call(RotateModel, 51, LVar0, -1, 0, 0)
        Wait(1)
    EndLoop
    Loop(10)
        AddF(LVar0, Float(3.0))
        Call(RotateModel, 51, LVar0, -1, 0, 0)
        Wait(1)
    EndLoop
    Loop(20)
        AddF(LVar0, Float(5.0))
        Call(RotateModel, 51, LVar0, -1, 0, 0)
        Wait(1)
    EndLoop
    Loop(10)
        AddF(LVar0, Float(10.0))
        Call(RotateModel, 51, LVar0, -1, 0, 0)
        Wait(1)
    EndLoop
    Loop(5)
        AddF(LVar0, Float(20.0))
        Call(RotateModel, 51, LVar0, -1, 0, 0)
        Wait(1)
    EndLoop
    Loop(0)
        Call(GetActorVar, ACTOR_SELF, 5, LVar1)
        IfEq(LVar1, 1)
            BreakLoop
        EndIf
        AddF(LVar0, Float(40.0))
        Call(RotateModel, 51, LVar0, -1, 0, 0)
        Wait(1)
    EndLoop
    Loop(5)
        AddF(LVar0, Float(20.0))
        Call(RotateModel, 51, LVar0, -1, 0, 0)
        Wait(1)
    EndLoop
    Loop(10)
        AddF(LVar0, Float(10.0))
        Call(RotateModel, 51, LVar0, -1, 0, 0)
        Wait(1)
    EndLoop
    Loop(20)
        AddF(LVar0, Float(5.0))
        Call(RotateModel, 51, LVar0, -1, 0, 0)
        Wait(1)
    EndLoop
    Loop(10)
        AddF(LVar0, Float(3.0))
        Call(RotateModel, 51, LVar0, -1, 0, 0)
        Wait(1)
    EndLoop
    Loop(5)
        AddF(LVar0, Float(1.0))
        Call(RotateModel, 51, LVar0, -1, 0, 0)
        Wait(1)
    EndLoop
    Call(RotateModel, 51, 0, -1, 0, 0)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_FakeBowser2_IntTable_FireBreath_Arms_OffsetTable[] = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -5,  -4,  0,   -7,  -10,
    0,   -9,  -11, 0,   -11, -15, 0,   -12, -19, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11,
    -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,
    -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20,
    0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11,
    -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,
    -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20,
    0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11,
    -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -11, -20, 0,   -10, -15, 0,   -7,  -10, 0,
    -5,  -6,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 255,
};

s32 TTYD64_imp_FakeBowser2_IntTable_Bomb_Pannel_OffsetTable[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 2, 0, 0, 2,   0,   0,   3, 0, 0,
    3, 0, 0, 4, 0, 0, 4, 0, 0, 5, 0, 0, 5, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6,   0,   0,   6, 0, 0,
    6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6,   0,   0,   6, 0, 0,
    6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6,   0,   0,   6, 0, 0,
    6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6,   0,   0,   6, 0, 0,
    6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 5, 0, 0, 5, 0, 0, 4, 0, 0, 4, 0, 0, 3,   0,   0,   3, 0, 0,
    2, 0, 0, 2, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255,
};

s32 TTYD64_imp_FakeBowser2_IntTable_FireBreath_Head_OffsetTable[] = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -8,  -5,  0,   -12, -8,  0,   -15, -13,
    0,   -17, -18, 0,   -20, -25, 0,   -20, -29, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21,
    -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,
    -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31,
    0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21,
    -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,
    -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31,
    0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21,
    -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -21, -31, 0,   -12, -8,  0,   -8,  -3,  0,
    -6,  -1,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 255,
};

s32 TTYD64_imp_FakeBowser2_FloatTable_Attack_FireBreath_Belly_RotationTable[] = {
    0, 0, 0,          0, 0, 0,          0, 0, 0,          0,   0,   0,          0, 0, 0,          0, 0, -0xDB59180,
    0, 0, -0xDB59D80, 0, 0, -0xDB5A980, 0, 0, -0xDB5B580, 0,   0,   -0xDB5C180, 0, 0, -0xDB5CD80, 0, 0, -0xDB5D580,
    0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0,   0,   -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580,
    0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0,   0,   -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580,
    0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0,   0,   -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580,
    0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0,   0,   -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580,
    0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0,   0,   -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580,
    0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0,   0,   -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580,
    0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0,   0,   -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580,
    0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0,   0,   -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580,
    0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580, 0,   0,   -0xDB5D580, 0, 0, -0xDB5D580, 0, 0, -0xDB5D580,
    0, 0, -0xDB5D580, 0, 0, -0xDB5C180, 0, 0, -0xDB5AD80, 0,   0,   -0xDB59980, 0, 0, 0,          0, 0, 0,
    0, 0, 0,          0, 0, 0,          0, 0, 0,          255, 255, 255,
};

s32 TTYD64_imp_FakeBowser2_FloatTable_Attack_FireBreath_Head_RotationTable[] = {
    0, 0, 0,          0,   0,   0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    0, 0, 0,          0,   0,   0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    0, 0, 0,          0,   0,   -0xDB58980, 0, 0, -0xDB58D80, 0, 0, -0xDB59180, 0, 0, -0xDB58D80, 0, 0, -0xDB58980,
    0, 0, -0xDB58D80, 0,   0,   -0xDB59180, 0, 0, -0xDB58D80, 0, 0, -0xDB58980, 0, 0, -0xDB58D80, 0, 0, -0xDB59180,
    0, 0, -0xDB58D80, 0,   0,   -0xDB58980, 0, 0, -0xDB58D80, 0, 0, -0xDB59180, 0, 0, -0xDB58D80, 0, 0, -0xDB58980,
    0, 0, -0xDB58D80, 0,   0,   -0xDB59180, 0, 0, -0xDB58D80, 0, 0, -0xDB58980, 0, 0, -0xDB58D80, 0, 0, -0xDB59180,
    0, 0, -0xDB58D80, 0,   0,   -0xDB58980, 0, 0, -0xDB58D80, 0, 0, -0xDB59180, 0, 0, -0xDB58D80, 0, 0, -0xDB58980,
    0, 0, -0xDB58D80, 0,   0,   -0xDB59180, 0, 0, -0xDB58D80, 0, 0, -0xDB58980, 0, 0, -0xDB58D80, 0, 0, -0xDB59180,
    0, 0, -0xDB58D80, 0,   0,   -0xDB58980, 0, 0, -0xDB58D80, 0, 0, -0xDB59180, 0, 0, -0xDB58D80, 0, 0, -0xDB58980,
    0, 0, -0xDB58D80, 0,   0,   -0xDB59180, 0, 0, -0xDB58D80, 0, 0, -0xDB58980, 0, 0, -0xDB58D80, 0, 0, -0xDB59180,
    0, 0, -0xDB58D80, 0,   0,   -0xDB58980, 0, 0, -0xDB58D80, 0, 0, -0xDB59180, 0, 0, -0xDB58D80, 0, 0, 0,
    0, 0, 0,          0,   0,   0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    0, 0, 0,          255, 255, 255,
};

s32 TTYD64_imp_FakeBowser2_FloatTable_Attack_FireBreath_Arms_RotationTable[] = {
    0, 0, 0,          0,   0,   0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    0, 0, 0,          0,   0,   -0xDB56780, 0, 0, -0xDB55D80, 0, 0, -0xDB55580, 0, 0, -0xDB54980, 0, 0, -0xDB54980,
    0, 0, -0xDB54980, 0,   0,   -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980,
    0, 0, -0xDB54980, 0,   0,   -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980,
    0, 0, -0xDB54980, 0,   0,   -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980,
    0, 0, -0xDB54980, 0,   0,   -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980,
    0, 0, -0xDB54980, 0,   0,   -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980,
    0, 0, -0xDB54980, 0,   0,   -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980,
    0, 0, -0xDB54980, 0,   0,   -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980,
    0, 0, -0xDB54980, 0,   0,   -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980,
    0, 0, -0xDB54980, 0,   0,   -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB54980, 0, 0, -0xDB55380,
    0, 0, -0xDB56180, 0,   0,   -0xDB57180, 0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    0, 0, 0,          255, 255, 255,
};

s32 TTYD64_imp_FakeBowser2_FloatTable_Attack_LeftArmA_RotationTable[] = {
    0, 0, -0xDB57180, 0, 0, -0xDB55D80, 0, 0, -0xDB54980, 0, 0, -0xDB53580, 0, 0, -0xDB52180, 0,   0,   -0xDB50D80,
    0, 0, -0xDB4F980, 0, 0, -0xDB4E580, 0, 0, -0xDB4D180, 0, 0, -0xDB4D180, 0, 0, -0xDB4C580, 0,   0,   -0xDB4D180,
    0, 0, -0xDB4C580, 0, 0, -0xDB4D180, 0, 0, -0xDB4C580, 0, 0, -0xDB4D180, 0, 0, -0xDB4C580, 0,   0,   -0xDB4D180,
    0, 0, -0xDB4C580, 0, 0, -0xDB4D180, 0, 0, -0xDB4C580, 0, 0, -0xDB4D180, 0, 0, -0xDB4C580, 0,   0,   -0xDB4D180,
    0, 0, -0xDB4C580, 0, 0, -0xDB4D180, 0, 0, -0xDB4C580, 0, 0, -0xDB4D180, 0, 0, -0xDB4C580, 0,   0,   -0xDB4D180,
    0, 0, -0xDB49D80, 0, 0, -0xDB44D80, 0, 0, -0xDB3FD80, 0, 0, -0xDB3D580, 0, 0, -0xDB36D80, 0,   0,   -0xDB33180,
    0, 0, -0xDB2E180, 0, 0, -0xDB55D80, 0, 0, -0xDB52180, 0, 0, -0xDB4F980, 0, 0, -0xDB4F980, 0,   0,   -0xDB4F980,
    0, 0, -0xDB4F980, 0, 0, -0xDB4F980, 0, 0, -0xDB4F980, 0, 0, -0xDB4F980, 0, 0, -0xDB4F980, 0,   0,   -0xDB52180,
    0, 0, -0xDB54980, 0, 0, -0xDB57180, 0, 0, 0,          0, 0, 0,          0, 0, 0,          0,   0,   0,
    0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          255, 255, 255,
};

s32 TTYD64_imp_FakeBowser2_IntTable_Bomb_Body_OffsetTable[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,   0,   0,   6,
    0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0,   6,   0,   0,
    6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 5, 0, 0, 4, 0, 0, 3, 0,   0,   2,   0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255,
};

ActorPartBlueprint TTYD64_imp_FakeBowser2_PartsTable_FakeBowser2[] = {
    {
        .flags = 0x800001,
        .index = 1,
        .posOffset = { 0, 0, 15 },
        .targetOffset = { -46, 110 },
        .opacity = 255,
        .idleAnimations = b_area_trd_part_2_fake_bowser_PlaceholderAnims,
        .defenseTable = TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_kmr_part_3_final_jr_troopa_BaseDefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 10 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 10 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 10 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 6,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 10 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 7,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 10 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120000,
        .index = 8,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 10 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120000,
        .index = 9,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 10 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 10,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 10 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 11,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 10 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 12,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 10 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20120001,
        .index = 13,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_FakeBowser2_IdleAnimations_Bomb,
        .defenseTable = TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 14,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 15,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 16,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Init_FakeBowser2 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_FakeBowser2_Script_TakeTurn_FakeBowser2))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_FakeBowser2_Script_Idle_FakeBowser2))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_FakeBowser2_Script_HandleEvent_FakeBowser2))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_imp_FakeBowser2_Script_NextTurn_FakeBowser2))
    UseArray(Ref(FakeBowserAnimState))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 0)
    Call(SetActorVar, ACTOR_SELF, 7, 0)
    Set(ArrayVar(0), 0)
    Call(SetActorPos, ACTOR_SELF, 96, 0, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetPartTargetFlagBits, ACTOR_SELF, 2, 4, 1)
    Call(EnableModel, 49, 0)
    Call(EnableModel, 51, 0)
    Call(EnableModel, 53, 0)
    Call(EnableModel, 55, 0)
    Call(EnableModel, 57, 0)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_FakeBowser2_FloatTable_Healing_Start_Arms_RotationTable[] = {
    0,   0,   0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    0,   0,   0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    0,   0,   0,          0, 0, 0,          0, 0, -0xDB58F80, 0, 0, -0xDB5A180, 0, 0, -0xDB5B180, 0, 0, -0xDB5C180,
    0,   0,   -0xDB5C980, 0, 0, -0xDB5D180, 0, 0, -0xDB5D980, 0, 0, -0xDB5DD80, 0, 0, -0xDB5D180, 0, 0, -0xDB5C980,
    0,   0,   -0xDB5C180, 0, 0, -0xDB5B980, 0, 0, -0xDB5B180, 0, 0, -0xDB5AD80, 0, 0, -0xDB5B580, 0, 0, -0xDB5BD80,
    0,   0,   -0xDB5C180, 0, 0, -0xDB5C180, 0, 0, -0xDB5C180, 0, 0, -0xDB5C180, 0, 0, -0xDB5C180, 0, 0, -0xDB5C180,
    255, 255, 255,
};

s32 TTYD64_imp_FakeBowser2_FloatTable_Healing_Stop_Arms_RotationTable[] = {
    0,   0,   -0xDB5C180, 0, 0, -0xDB5C180, 0, 0, -0xDB5C180, 0, 0, -0xDB5C180, 0, 0, -0xDB5C180, 0, 0, -0xDB5C180,
    0,   0,   -0xDB5C180, 0, 0, -0xDB5C180, 0, 0, -0xDB5C180, 0, 0, -0xDB5C180, 0, 0, -0xDB5C180, 0, 0, -0xDB5C180,
    0,   0,   -0xDB5C180, 0, 0, -0xDB5C180, 0, 0, -0xDB5C180, 0, 0, -0xDB5B180, 0, 0, -0xDB5A180, 0, 0, -0xDB58F80,
    0,   0,   0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    0,   0,   0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    0,   0,   0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    255, 255, 255,
};

s32 TTYD64_imp_FakeBowser2_FloatTable_Healing_Start_Head_RotationTable[] = {
    0,   0,   0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    0,   0,   0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    0,   0,   0,          0, 0, 0,          0, 0, -0xDB58980, 0, 0, -0xDB58D80, 0, 0, -0xDB59180, 0, 0, -0xDB59580,
    0,   0,   -0xDB59980, 0, 0, -0xDB59D80, 0, 0, -0xDB5A180, 0, 0, -0xDB5A580, 0, 0, -0xDB5A980, 0, 0, -0xDB5AD80,
    0,   0,   -0xDB5AD80, 0, 0, -0xDB5AD80, 0, 0, -0xDB5AD80, 0, 0, -0xDB5AD80, 0, 0, -0xDB5AD80, 0, 0, -0xDB5AD80,
    0,   0,   -0xDB5AD80, 0, 0, -0xDB5AD80, 0, 0, -0xDB5AD80, 0, 0, -0xDB5AD80, 0, 0, -0xDB5AD80, 0, 0, -0xDB5AD80,
    255, 255, 255,
};

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_Tail = {
    UseArray(Ref(FakeBowserAnimState))
    Call(SetPartFlagBits, ACTOR_SELF, 7, 0x100000, 1)
    Call(GetPartPos, ACTOR_SELF, 7, LVar0, LVar1, LVar2)
    Call(SetPartDispOffset, ACTOR_SELF, 7, 0, -30, 0)
    Set(LVar1, 30)
    Call(SetPartPos, ACTOR_SELF, 7, LVar0, LVar1, LVar2)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Loop(80)
            Add(LVar0, 25)
            Add(LVar1, 1)
            Call(SetPartRotation, ACTOR_SELF, 7, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Sub(LVar0, 0)
    Set(LVar1, -200)
    Add(LVar2, 200)
    Call(SetPartJumpGravity, ACTOR_SELF, 7, Float(0.2998046875))
    Call(JumpPartTo, ACTOR_SELF, 7, LVar0, LVar1, LVar2, 80, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_LeftArm = {
    UseArray(Ref(FakeBowserAnimState))
    Call(SetPartFlagBits, ACTOR_SELF, 6, 0x100000, 1)
    Call(GetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(SetPartDispOffset, ACTOR_SELF, 6, 0, -60, 0)
    Set(LVar1, 60)
    Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Loop(80)
            Add(LVar0, 8)
            Add(LVar1, 10)
            Call(SetPartRotation, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Sub(LVar0, 0)
    Set(LVar1, -200)
    Add(LVar2, 100)
    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.599609375))
    Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 80, 1)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_FakeBowser2_FloatTable_Attack0_LeftArm_RotationTable[] = {
    0, 0, -0xDB57180, 0, 0, -0xDB55D80, 0, 0, -0xDB54980, 0, 0, -0xDB53580, 0, 0, -0xDB52180, 0,   0,   -0xDB50D80,
    0, 0, -0xDB4F980, 0, 0, -0xDB4E580, 0, 0, -0xDB4D180, 0, 0, -0xDB4D180, 0, 0, -0xDB4C580, 0,   0,   -0xDB4D180,
    0, 0, -0xDB4C580, 0, 0, -0xDB4D180, 0, 0, -0xDB4C580, 0, 0, -0xDB4D180, 0, 0, -0xDB4C580, 0,   0,   -0xDB4D180,
    0, 0, -0xDB4C580, 0, 0, -0xDB4D180, 0, 0, -0xDB4C580, 0, 0, -0xDB4D180, 0, 0, -0xDB4F980, 0,   0,   -0xDB52180,
    0, 0, -0xDB54980, 0, 0, -0xDB57180, 0, 0, 0,          0, 0, 0,          0, 0, 0,          0,   0,   0,
    0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          255, 255, 255,
};

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_Belly = {
    UseArray(Ref(FakeBowserAnimState))
    Call(SetPartFlagBits, ACTOR_SELF, 3, 0x100000, 1)
    Call(GetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(SetPartDispOffset, ACTOR_SELF, 3, 0, -30, 0)
    Set(LVar1, 30)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Loop(80)
            Add(LVar0, -20)
            Call(SetPartRotation, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Sub(LVar0, 150)
    Set(LVar1, -200)
    Sub(LVar2, 200)
    Call(SetPartJumpGravity, ACTOR_SELF, 3, Float(0.2998046875))
    Call(JumpPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 80, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_WheelsBack = {
    UseArray(Ref(FakeBowserAnimState))
    Call(SetPartFlagBits, ACTOR_SELF, 9, 0x100000, 1)
    Call(GetPartPos, ACTOR_SELF, 9, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 9, LVar0, LVar1, LVar2)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Loop(80)
            Add(LVar0, 8)
            Call(SetPartRotation, ACTOR_SELF, 9, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Sub(LVar0, 50)
    Set(LVar1, -200)
    Sub(LVar2, 100)
    Call(SetPartJumpGravity, ACTOR_SELF, 9, Float(0.2998046875))
    Call(JumpPartTo, ACTOR_SELF, 9, LVar0, LVar1, LVar2, 80, 1)
    Wait(100)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_FakeBowser2_FloatTable_Healing_Stop_Head_RotationTable[] = {
    0, 0, -0xDB5AD80, 0,   0,   -0xDB5AD80, 0, 0, -0xDB5AD80, 0, 0, -0xDB5AD80, 0, 0, -0xDB5AD80, 0, 0, -0xDB5AD80,
    0, 0, -0xDB5AD80, 0,   0,   -0xDB5AD80, 0, 0, -0xDB5AD80, 0, 0, -0xDB5AD80, 0, 0, -0xDB5AD80, 0, 0, -0xDB5AD80,
    0, 0, -0xDB5AD80, 0,   0,   -0xDB5AD80, 0, 0, -0xDB5AD80, 0, 0, -0xDB5A180, 0, 0, -0xDB59980, 0, 0, -0xDB59180,
    0, 0, -0xDB58980, 0,   0,   0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    0, 0, 0,          0,   0,   0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    0, 0, 0,          255, 255, 255,
};

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_FireBreath_UpdateBellyRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Attack_FireBreath_Belly_RotationTable))
    Set(LVarF, 0)
    Label(0)
    Set(LVar3, ArrayVar(0))
    IfNe(LVar3, 17)
        Return
    EndIf
    IfEq(LVarF, 0)
        FBufRead3(LVar0, LVar1, LVar2)
        IfEq(LVar0, 255)
            Set(LVarF, 1)
            Set(LVar0, Float(0.0))
            Set(LVar1, Float(0.0))
            Set(LVar2, Float(0.0))
        EndIf
    EndIf
    MulF(LVar2, Float(-2.0))
    Call(SetPartRotation, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(SetPartRotation, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
    Call(SetPartRotation, ACTOR_SELF, 7, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_WheelsFront = {
    UseArray(Ref(FakeBowserAnimState))
    Call(SetPartFlagBits, ACTOR_SELF, 8, 0x100000, 1)
    Call(GetPartPos, ACTOR_SELF, 8, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 8, LVar0, LVar1, LVar2)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Loop(80)
            Add(LVar0, 8)
            Call(SetPartRotation, ACTOR_SELF, 8, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Sub(LVar0, 150)
    Set(LVar1, -200)
    Add(LVar2, 100)
    Call(SetPartJumpGravity, ACTOR_SELF, 8, Float(0.2998046875))
    Call(JumpPartTo, ACTOR_SELF, 8, LVar0, LVar1, LVar2, 80, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_NextTurn_FakeBowser2 = {
    UseArray(Ref(FakeBowserAnimState))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(10)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfNotFlag(LVar0, 8)
                Call(GetActorVar, ACTOR_SELF, 0, LVar0)
                BitwiseOrConst(LVar0, 8)
                Call(SetActorVar, ACTOR_SELF, 0, LVar0)
            EndIf
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    IfEq(LVar0, 1)
        Call(GetActorVar, ACTOR_SELF, 4, LVar0)
        Add(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 4, LVar0)
        IfGe(LVar0, 3)
            ExecWait(TTYD64_imp_FakeBowser2_Script_HealingMode_Stop)
        EndIf
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Dying_JumpPart_Base = {
    UseArray(Ref(FakeBowserAnimState))
    Call(SetPartFlagBits, ACTOR_SELF, 10, 0x100000, 1)
    Call(GetPartPos, ACTOR_SELF, 10, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 10, LVar0, LVar1, LVar2)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Loop(80)
            Add(LVar0, -10)
            Call(SetPartRotation, ACTOR_SELF, 10, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Sub(LVar0, 50)
    Set(LVar1, -200)
    Sub(LVar2, 200)
    Call(SetPartJumpGravity, ACTOR_SELF, 10, Float(0.2998046875))
    Call(JumpPartTo, ACTOR_SELF, 10, LVar0, LVar1, LVar2, 80, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Hurt_UpdateHeadRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Hurt_Head_RotationTable))
    Label(0)
    Set(LVar0, ArrayVar(0))
    IfNe(LVar0, 3)
        Return
    EndIf
    FBufRead3(LVar0, LVar1, LVar2)
    IfEq(LVar0, 255)
        UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Hurt_Head_RotationTable))
        FBufRead3(LVar0, LVar1, LVar2)
    EndIf
    Call(RandInt, 100, LVarA)
    IfLt(LVarA, 50)
        SetF(LVarA, Float(0.0))
        SubF(LVarA, LVar0)
        SetF(LVar0, LVarA)
        SetF(LVarA, Float(0.0))
        SubF(LVarA, LVar1)
        SetF(LVar1, LVarA)
    EndIf
    Call(SetPartRotation, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_FakeBowser2_FloatTable_MachineGun_Arms_RotationTable[] = {
    0,   0,   0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    0,   0,   0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,
    0,   0,   0,          0, 0, 0,          0, 0, -0xDB57180, 0, 0, -0xDB55D80, 0, 0, -0xDB54980, 0, 0, -0xDB53580,
    0,   0,   -0xDB52180, 0, 0, -0xDB50D80, 0, 0, -0xDB50580, 0, 0, -0xDB50D80, 0, 0, -0xDB51580, 0, 0, -0xDB50D80,
    0,   0,   -0xDB50D80, 0, 0, -0xDB50D80, 0, 0, -0xDB50D80, 0, 0, -0xDB50D80, 0, 0, -0xDB50D80, 0, 0, -0xDB50D80,
    255, 255, 255,
};

s32 TTYD64_imp_FakeBowser2_FloatTable_StopMachineGun_Arms_RotationTable[] = {
    0, 0, -0xDB50D80, 0, 0, -0xDB50D80, 0, 0, -0xDB50D80, 0, 0, -0xDB50D80, 0, 0, -0xDB50D80, 0,   0,   -0xDB50D80,
    0, 0, -0xDB50D80, 0, 0, -0xDB50D80, 0, 0, -0xDB50D80, 0, 0, -0xDB50D80, 0, 0, -0xDB50D80, 0,   0,   -0xDB50D80,
    0, 0, -0xDB50D80, 0, 0, -0xDB50D80, 0, 0, -0xDB50D80, 0, 0, -0xDB52180, 0, 0, -0xDB53580, 0,   0,   -0xDB54980,
    0, 0, -0xDB55D80, 0, 0, -0xDB57180, 0, 0, 0,          0, 0, 0,          0, 0, 0,          0,   0,   0,
    0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          255, 255, 255,
};

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_FireBreath_UpdateArmsRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Attack_FireBreath_Arms_RotationTable))
    Set(LVarF, 0)
    Label(0)
    Set(LVar3, ArrayVar(0))
    IfNe(LVar3, 17)
        Return
    EndIf
    IfEq(LVarF, 0)
        FBufRead3(LVar0, LVar1, LVar2)
        IfEq(LVar0, 255)
            Set(LVarF, 1)
            Set(LVar0, Float(0.0))
            Set(LVar1, Float(0.0))
            Set(LVar2, Float(0.0))
        EndIf
    EndIf
    MulF(LVar2, Float(-2.0))
    Call(SetPartRotation, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(SetPartRotation, ACTOR_SELF, 11, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Healing_Stop_UpdateArmsRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Healing_Stop_Arms_RotationTable))
    Set(LVarF, 0)
    Label(0)
    Set(LVar3, ArrayVar(0))
    IfNe(LVar3, 27)
        Return
    EndIf
    IfEq(LVarF, 0)
        FBufRead3(LVar0, LVar1, LVar2)
        IfEq(LVar0, 255)
            Set(LVarF, 1)
            Set(LVar0, Float(0.0))
            Set(LVar1, Float(0.0))
            Set(LVar2, Float(0.0))
        EndIf
    EndIf
    MulF(LVar2, Float(-2.0))
    Call(SetPartRotation, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(SetPartRotation, ACTOR_SELF, 11, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_FakeBowser2_FloatTable_Attack_LeftArmB_RotationTable[] = {
    0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0,   0,   0,          0, 0, 0,
    0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          0,   0,   0,          0, 0, -0xDB59980,
    0, 0, -0xDB5C180, 0, 0, -0xDB5E980, 0, 0, -0xDB61180, 0, 0, -0xDB63980, 0,   0,   -0xDB67580, 0, 0, -0xDB6B180,
    0, 0, -0xDB6ED80, 0, 0, -0xDB72980, 0, 0, -0xDB78D80, 0, 0, -0xDB7DD80, 0,   0,   -0xDB50D80, 0, 0, 0,
    0, 0, 0,          0, 0, 0,          0, 0, 0,          0, 0, 0,          255, 255, 255,
};

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_LeftArmB_UpdateLeftArmRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Attack_LeftArmB_RotationTable))
    Set(LVarF, 0)
    Label(0)
    Set(LVar3, ArrayVar(0))
    IfNe(LVar3, 15)
        Return
    EndIf
    IfEq(LVarF, 0)
        FBufRead3(LVar0, LVar1, LVar2)
        IfEq(LVar0, 255)
            Set(LVarF, 1)
            Set(LVar0, Float(0.0))
            Set(LVar1, Float(0.0))
            Set(LVar2, Float(0.0))
        EndIf
    EndIf
    MulF(LVar2, Float(-2.0))
    Call(SetPartRotation, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Healing_Stop_UpdateHeadRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Healing_Stop_Head_RotationTable))
    Set(LVarF, 0)
    Label(0)
    Set(LVar3, ArrayVar(0))
    IfNe(LVar3, 27)
        Return
    EndIf
    IfEq(LVarF, 0)
        FBufRead3(LVar0, LVar1, LVar2)
        IfEq(LVar0, 255)
            Set(LVarF, 1)
            Set(LVar0, Float(0.0))
            Set(LVar1, Float(0.0))
            Set(LVar2, Float(0.0))
        EndIf
    EndIf
    MulF(LVar2, Float(-2.0))
    Call(SetPartRotation, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_FireBreath_UpdateHeadRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Attack_FireBreath_Head_RotationTable))
    Set(LVarF, 0)
    Label(0)
    Set(LVar3, ArrayVar(0))
    IfNe(LVar3, 17)
        Return
    EndIf
    IfEq(LVarF, 0)
        FBufRead3(LVar0, LVar1, LVar2)
        IfEq(LVar0, 255)
            Set(LVarF, 1)
            Set(LVar0, Float(0.0))
            Set(LVar1, Float(0.0))
            Set(LVar2, Float(0.0))
        EndIf
    EndIf
    MulF(LVar2, Float(-2.0))
    Call(SetPartRotation, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_LeftArmA_UpdateLeftArmRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Attack_LeftArmA_RotationTable))
    Set(LVarF, 0)
    Label(0)
    Set(LVar3, ArrayVar(0))
    IfNe(LVar3, 13)
        Return
    EndIf
    IfEq(LVarF, 0)
        FBufRead3(LVar0, LVar1, LVar2)
        IfEq(LVar0, 255)
            Set(LVarF, 1)
            Set(LVar0, Float(0.0))
            Set(LVar1, Float(0.0))
            Set(LVar2, Float(0.0))
        EndIf
    EndIf
    MulF(LVar2, Float(-2.0))
    Call(SetPartRotation, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_EndFight = {
    Wait(100)
    Call(EnableGroup, 27, 0)
    Call(EnableGroup, 17, 0)
    Call(EnableGroup, 13, 0)
    Call(EnableGroup, 36, 0)
    Call(EnableGroup, 32, 0)
    Call(EnableGroup, 46, 0)
    Call(EnableGroup, 48, 0)
    Call(EnableGroup, 40, 0)
    Call(EnableGroup, 44, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 3)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    BitwiseOrConst(LVar0, 1)
    Call(SetActorVar, ACTOR_SELF, 0, LVar0)
    Call(SetActorFlagBits, ACTOR_SELF, 0x400000, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Attack0_UpdateLeftArmRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Attack0_LeftArm_RotationTable))
    Set(LVarF, 0)
    Label(0)
    Set(LVar0, ArrayVar(0))
    IfNe(LVar0, 7)
        Return
    EndIf
    IfEq(LVarF, 0)
        FBufRead3(LVar0, LVar1, LVar2)
        IfEq(LVar0, 255)
            Set(LVarF, 1)
            Set(LVar0, Float(0.0))
            Set(LVar1, Float(0.0))
            Set(LVar2, Float(0.0))
        EndIf
    EndIf
    MulF(LVar2, Float(-2.0))
    Call(SetPartRotation, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Healing_Start_UpdateArmsRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Healing_Start_Arms_RotationTable))
    Set(LVarF, 0)
    Label(0)
    Set(LVar3, ArrayVar(0))
    IfNe(LVar3, 25)
        Return
    EndIf
    IfEq(LVarF, 0)
        FBufRead3(LVar0, LVar1, LVar2)
        IfEq(LVar0, 255)
            Return
        EndIf
    EndIf
    MulF(LVar2, Float(-2.0))
    Call(SetPartRotation, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(SetPartRotation, ACTOR_SELF, 11, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Healing_Step_UpdateArmsRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Healing_Step_Arms_RotationTable))
    Set(LVarF, 0)
    Label(0)
    Set(LVar0, ArrayVar(0))
    IfNe(LVar0, 29)
        Return
    EndIf
    IfEq(LVarF, 0)
        FBufRead3(LVar0, LVar1, LVar2)
        IfEq(LVar0, 255)
            Return
        EndIf
    EndIf
    MulF(LVar2, Float(-2.0))
    Call(SetPartRotation, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(SetPartRotation, ACTOR_SELF, 11, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_FakeBowser2_FloatTable_Idle_Head_RotationTable[] = {
    0, 0, 0,          0, 0, 0,          0, 0, -0xDB58180, 0, 0, -0xDB57D80, 0, 0, -0xDB57B80, 0,   0,   -0xDB57980,
    0, 0, -0xDB57580, 0, 0, -0xDB57580, 0, 0, -0xDB57580, 0, 0, -0xDB57580, 0, 0, -0xDB57580, 0,   0,   -0xDB57580,
    0, 0, -0xDB57580, 0, 0, -0xDB57580, 0, 0, -0xDB57780, 0, 0, -0xDB57980, 0, 0, -0xDB57B80, 0,   0,   -0xDB57980,
    0, 0, -0xDB57D80, 0, 0, -0xDB58180, 0, 0, -0xDB58380, 0, 0, 0,          0, 0, 0,          255, 255, 255,
};

s32 TTYD64_imp_FakeBowser2_FloatTable_Hurt_Head_RotationTable[] = {
    0,          -0xDB55D80, 0,          -0xDB53580, 0,          -0xDB57180, 0,          0,          0,
    -0xDB57180, -0xDB53580, 0,          -0xDB55D80, 0,          0,          0,          -0xDB50D80, 0,
    0,          -0xDB57180, -0xDB57D80, -0xDB50D80, 0,          -0xDB55D80, -0xDB50D80, -0xDB55D80, 0,
    0,          -0xDB4E580, -0xDB57D80, 0,          0,          -0xDB57180, -0xDB57180, 0,          -0xDB56580,
    -0xDB55D80, 0,          0,          0,          -0xDB50D80, 0,          -0xDB53580, 0,          -0xDB57180,
    0,          0,          0,          0,          -0xDB57180, 0,          -0xDB55D80, 0,          -0xDB56580,
    0,          -0xDB53580, 0,          -0xDB57180, 0,          0,          0,          -0xDB57180, -0xDB57180,
    -0xDB50D80, 0,          0,          0,          0,          0,          255,        255,        255,
};

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_AnyAttack_UpdateBasePos = {
    UseArray(Ref(FakeBowserAnimState))
    UseBuf(Ref(b_area_trd_part_2_fake_bowser_IdleFeetOffsets))
    Label(0)
    Set(LVar0, ArrayVar(0))
    Switch(LVar0)
        CaseEq(7)
        CaseEq(11)
        CaseEq(13)
        CaseEq(15)
        CaseDefault
            Return
    EndSwitch
    BufRead3(LVar0, LVar1, LVar2)
    IfEq(LVar0, 255)
        UseBuf(Ref(b_area_trd_part_2_fake_bowser_IdleFeetOffsets))
        BufRead3(LVar0, LVar1, LVar2)
    EndIf
    Call(SetPartPos, ACTOR_SELF, 10, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_AnyAttack_UpdateBodyPos = {
    UseArray(Ref(FakeBowserAnimState))
    UseBuf(Ref(b_area_trd_part_2_fake_bowser_IdleBodyOffsets))
    Label(0)
    Set(LVar0, ArrayVar(0))
    Switch(LVar0)
        CaseEq(7)
        CaseEq(11)
        CaseEq(13)
        CaseEq(15)
        CaseDefault
            Return
    EndSwitch
    BufRead3(LVar0, LVar1, LVar2)
    IfEq(LVar0, 255)
        UseBuf(Ref(b_area_trd_part_2_fake_bowser_IdleBodyOffsets))
        BufRead3(LVar0, LVar1, LVar2)
    EndIf
    Call(SetActorDispOffset, ACTOR_SELF, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_StopMachineGun_UpdateArmRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_StopMachineGun_Arms_RotationTable))
    Set(LVarF, 0)
    Label(0)
    Set(LVar3, ArrayVar(0))
    IfNe(LVar3, 23)
        Return
    EndIf
    IfEq(LVarF, 0)
        FBufRead3(LVar0, LVar1, LVar2)
        IfEq(LVar0, 255)
            Return
        EndIf
    EndIf
    MulF(LVar2, Float(-2.0))
    Call(SetPartRotation, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_MachineGun_UpdateArmRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_MachineGun_Arms_RotationTable))
    Set(LVarF, 0)
    Label(0)
    Set(LVar3, ArrayVar(0))
    IfNe(LVar3, 21)
        Return
    EndIf
    IfEq(LVarF, 0)
        FBufRead3(LVar0, LVar1, LVar2)
        IfEq(LVar0, 255)
            Return
        EndIf
    EndIf
    MulF(LVar2, Float(-2.0))
    Call(SetPartRotation, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Healing_Step_UpdateHeadRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Healing_Step_Head_RotationTable))
    Set(LVarF, 0)
    Label(0)
    Set(LVar0, ArrayVar(0))
    IfNe(LVar0, 29)
        Return
    EndIf
    IfEq(LVarF, 0)
        FBufRead3(LVar0, LVar1, LVar2)
        IfEq(LVar0, 255)
            Return
        EndIf
    EndIf
    MulF(LVar2, Float(-2.0))
    Call(SetPartRotation, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Running_UpdateWheelsRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Running_Wheels_RotationTable))
    Label(0)
    Set(LVar0, ArrayVar(0))
    IfNe(LVar0, 5)
        Return
    EndIf
    FBufRead3(LVar0, LVar1, LVar2)
    IfEq(LVar0, 255)
        UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Running_Wheels_RotationTable))
        FBufRead3(LVar0, LVar1, LVar2)
    EndIf
    Call(SetPartRotation, ACTOR_SELF, 8, LVar0, LVar1, LVar2)
    Call(SetPartRotation, ACTOR_SELF, 9, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Healing_Start_UpdateHeadRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Healing_Start_Head_RotationTable))
    Set(LVarF, 0)
    Label(0)
    Set(LVar3, ArrayVar(0))
    IfNe(LVar3, 25)
        Return
    EndIf
    IfEq(LVarF, 0)
        FBufRead3(LVar0, LVar1, LVar2)
        IfEq(LVar0, 255)
            Return
        EndIf
    EndIf
    MulF(LVar2, Float(-2.0))
    Call(SetPartRotation, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_FireBreath_UpdateArmsPos = {
    UseArray(Ref(FakeBowserAnimState))
    UseBuf(Ref(TTYD64_imp_FakeBowser2_IntTable_FireBreath_Arms_OffsetTable))
    Label(0)
    Set(LVar0, ArrayVar(0))
    Switch(LVar0)
        CaseEq(17)
        CaseDefault
            Return
    EndSwitch
    BufRead3(LVar0, LVar1, LVar2)
    IfEq(LVar0, 255)
        Return
    EndIf
    Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 11, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_HealingMode_Stop = {
    UseArray(Ref(FakeBowserAnimState))
    Set(ArrayVar(0), 26)
    Thread
        Call(FreezeBattleState, 1)
        Call(HealActor, ACTOR_SELF, 99, 0)
        Call(FreezeBattleState, 0)
    EndThread
    Wait(30)
    Set(ArrayVar(0), 0)
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser))
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(SetActorVar, ACTOR_SELF, 7, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Idle_UpdateHeadRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Idle_Head_RotationTable))
    Label(0)
    Set(LVar0, ArrayVar(0))
    IfNe(LVar0, 1)
        Return
    EndIf
    FBufRead3(LVar0, LVar1, LVar2)
    IfEq(LVar0, 255)
        UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Idle_Head_RotationTable))
        FBufRead3(LVar0, LVar1, LVar2)
    EndIf
    Call(SetPartRotation, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Running_UpdateHeadRotation = {
    UseArray(Ref(FakeBowserAnimState))
    UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Running_Head_RotationTable))
    Label(0)
    Set(LVar0, ArrayVar(0))
    IfNe(LVar0, 5)
        Return
    EndIf
    FBufRead3(LVar0, LVar1, LVar2)
    IfEq(LVar0, 255)
        UseFBuf(Ref(TTYD64_imp_FakeBowser2_FloatTable_Running_Head_RotationTable))
        FBufRead3(LVar0, LVar1, LVar2)
    EndIf
    Call(SetPartRotation, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_FakeBowser2_FloatTable_Running_Wheels_RotationTable[] = {
    0, 0, -0xDB53580, 0, 0, -0xDB4E580, 0, 0, -0xDB49580, 0,   0,   -0xDB44580, 0, 0, -0xDB3F580,
    0, 0, -0xDB3A580, 0, 0, -0xDB35580, 0, 0, -0xDB30580, 0,   0,   -0xDB2B580, 0, 0, -0xDB26580,
    0, 0, -0xDB21580, 0, 0, -0xDB1C580, 0, 0, -0xDB17580, 0,   0,   -0xDB12580, 0, 0, -0xDB0D580,
    0, 0, -0xDB08580, 0, 0, -0xDB03580, 0, 0, 0,          255, 255, 255,
};

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_FireBreath_UpdateHeadPos = {
    UseArray(Ref(FakeBowserAnimState))
    UseBuf(Ref(TTYD64_imp_FakeBowser2_IntTable_FireBreath_Head_OffsetTable))
    Label(0)
    Set(LVar0, ArrayVar(0))
    Switch(LVar0)
        CaseEq(17)
        CaseDefault
            Return
    EndSwitch
    BufRead3(LVar0, LVar1, LVar2)
    IfEq(LVar0, 255)
        Return
    EndIf
    Call(SetPartPos, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Bomb_UpdatePannelPos = {
    UseArray(Ref(FakeBowserAnimState))
    UseBuf(Ref(TTYD64_imp_FakeBowser2_IntTable_Bomb_Pannel_OffsetTable))
    Label(0)
    Set(LVar0, ArrayVar(0))
    Switch(LVar0)
        CaseEq(19)
        CaseDefault
            Return
    EndSwitch
    BufRead3(LVar0, LVar1, LVar2)
    IfEq(LVar0, 255)
        Return
    EndIf
    Call(SetPartPos, ACTOR_SELF, 12, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_MachineGun_UpdateArmRecoil = {
    UseArray(Ref(FakeBowserAnimState))
    UseBuf(Ref(TTYD64_imp_FakeBowser2_IntTable_MachineGun_ArmRecoil_OffsetTable))
    Label(0)
    Set(LVar0, ArrayVar(0))
    Switch(LVar0)
        CaseEq(21)
        CaseDefault
            Return
    EndSwitch
    BufRead3(LVar0, LVar1, LVar2)
    IfEq(LVar0, 255)
        Return
    EndIf
    Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Animation_Bomb_Recoil = {
    UseArray(Ref(FakeBowserAnimState))
    UseBuf(Ref(TTYD64_imp_FakeBowser2_IntTable_Bomb_Body_OffsetTable))
    Label(0)
    Set(LVar0, ArrayVar(0))
    Switch(LVar0)
        CaseEq(19)
        CaseDefault
            Return
    EndSwitch
    BufRead3(LVar0, LVar1, LVar2)
    IfEq(LVar0, 255)
        Return
    EndIf
    Call(SetActorDispOffset, ACTOR_SELF, LVar0, LVar1, LVar2)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_HealingMode_Start = {
    UseArray(Ref(FakeBowserAnimState))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Set(ArrayVar(0), 24)
    Call(ActorSpeak, 0, ACTOR_SELF, 1, -1, -1)
    Wait(40)
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_dgb_tubba_blubba_DefenseTable))
    Call(SetActorVar, ACTOR_SELF, 3, 1)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_pit_part_11_Script_BeforeBattle_Pit = {
    Call(EnableGroup, 26, 0)
    Switch(AreaByte(0))
        CaseGe(80)
            Call(EnableGroup, 25, 1)
        CaseGe(50)
            Call(EnableGroup, 19, 1)
        CaseDefault
            Call(EnableGroup, 13, 1)
    EndSwitch
    Call(SetSpriteShading, -1)
    Call(SetCamBGColor, 1, 0, 0, 0)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_FakeBowser2_FloatTable_Running_Head_RotationTable[] = {
    0, 0, 0,          0, 0, -0xDB57D80, 0,   0,   -0xDB57180, 0, 0, -0xDB56580, 0, 0, -0xDB56580,
    0, 0, -0xDB56580, 0, 0, -0xDB56580, 0,   0,   -0xDB56980, 0, 0, -0xDB57180, 0, 0, -0xDB57580,
    0, 0, -0xDB58180, 0, 0, 0,          255, 255, 255,
};

// clang-format off
EvtScript TTYD64_imp_FakeBowser2_Script_Attack_LeftArm = {
    Call(RandInt, 1, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_imp_FakeBowser2_Script_Attack_LeftArm_A)
        CaseEq(1)
            ExecWait(TTYD64_imp_FakeBowser2_Script_Attack_LeftArm_B)
    EndSwitch
    Return
    End
};
// clang-format on

s32 TTYD64_imp_FakeBowser2_Data_BurnedModelsTable[] = {
    12, 14, 15, 16, 18, 19, 20, 21, 22, 23, 28, 29, 30, 31, 33, 34, 35, 37, 38, 39, 41, 42, 43, 45, 47, 0xFFFF,
};

Stage TTYD64_pit_part_11_Stage_Pit1 = {
    .texture = "tik_tex",
    .shape = "pit_bt01_shape",
    .hit = "pit_bt01_hit",
    .preBattle = &TTYD64_pit_part_11_Script_BeforeBattle_Pit,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

Stage TTYD64_pit_part_11_Stage_Pit2 = {
    .texture = "tik_tex",
    .shape = "pit_bt02_shape",
    .hit = "pit_bt02_hit",
    .preBattle = &b_area_kmr_part_3_kpa_13_EVS_PreBattle,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_imp_FakeBowser2_FakeBowser2 = {
    .flags = 0x4,
    .maxHP = 100,
    .type = 0x5B,
    .level = 0,
    .partCount = 16,
    .partsData = TTYD64_imp_FakeBowser2_PartsTable_FakeBowser2,
    .initScript = &TTYD64_imp_FakeBowser2_Script_Init_FakeBowser2,
    .statusTable = b_area_trd_part_2_fake_bowser_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 60,
    .coinReward = 0,
    .size = { -71, 125 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

Battle TTYD64_pit_part_11_FormationTable[] = {
    { .name = NULL,
      .formationSize = 1,
      .formation = (Formation*) TTYD64_pit_part_11_Formation_Bowser,
      .stage = &TTYD64_pit_part_11_Stage_Pit2,
      .onBattleStart = NULL },
    {},
};

FormationRow TTYD64_pit_part_11_Formation_Bowser[] = {
    { .actor = &TTYD64_imp_FakeBowser2_FakeBowser2,
      .home = { .index = 3 },
      .priority = 6,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

s32 TTYD64_imp_FakeBowser2_FloatTable_Healing_Step_Head_RotationTable[] = {
    0, 0, -0xDB5AD80, 255, 255, 255,
};

StageListRow TTYD64_pit_part_11_StageTable[] = {
    { .name = "pit_01", .stage = &TTYD64_pit_part_11_Stage_Pit1 },
    { .name = "pit_12", .stage = &TTYD64_pit_part_11_Stage_Pit2 },
    {},
};

s32 TTYD64_imp_FakeBowser2_FloatTable_Healing_Step_Arms_RotationTable[] = {
    0, 0, -0xDB5C180, 255, 255, 255,
};

s32 TTYD64_imp_FakeBowser2_DefenseTable_FakeBowser[] = {
    1, 2, 11, 2, 0,
};

s32 TTYD64_imp_FakeBowser2_IdleAnimations_Bomb[] = {
    1,
    0x770001,
    0,
};

u8 TTYD64_pit_part_11_String_HealingMode_Start2[] = {
    0xFC, 0x06, 0x25, 0x4E, 0x54, 0x45, 0x52, 0x49, 0x4E, 0x47, 0xF7, 0x52, 0x45, 0x43, 0x4F, 0xFF, 0x26, 0x0C, 0x5A,
    0x56, 0x56, 0x53, 0x46, 0x47, 0x4A, 0x4F, 0x49, 0x55, 0x54, 0x46, 0x44, 0x47, 0x4A, 0x42, 0x4B, 0x4D, 0x4F, 0x45,
    0xF0, 0x4D, 0x56, 0x58, 0x43, 0x4B, 0x4C, 0x55, 0x4A, 0x47, 0x46, 0x4F, 0x41, 0x52, 0x49, 0x54, 0x55, 0x46, 0x4C,
    0x4B, 0x4A, 0x47, 0x42, 0x4D, 0x43, 0x56, 0x4C, 0x4D, 0x42, 0x4E, 0x4B, 0x41, 0x4A, 0x53, 0x41, 0xF0, 0x41, 0x4C,
    0x53, 0x44, 0x4D, 0x46, 0x58, 0x4D, 0x4C, 0x41, 0x4F, 0x45, 0x49, 0x46, 0x4B, 0x56, 0x43, 0x58, 0x46, 0x4D, 0x42,
    0x43, 0x56, 0x4B, 0x4C, 0x4A, 0x42, 0x4E, 0x48, 0x53, 0x54, 0x49, 0x4F, 0x50, 0xF0, 0x41, 0x53, 0x44, 0x4B, 0x4E,
    0x46, 0x4A, 0x58, 0x43, 0x4E, 0x56, 0x4D, 0x56, 0x58, 0x43, 0x4B, 0x4C, 0x48, 0x56, 0x46, 0x4F, 0x53, 0x57, 0x55,
    0x49, 0x45, 0x52, 0x52, 0x48, 0x54, 0x4A, 0x4C, 0x4F, 0xF0, 0xF1, 0xFD,
};

u8 TTYD64_pit_part_11_String_HealingMode_Start1[] = {
    0xFC, 0x06, 0xFF, 0x09, 0x25, 0x4E, 0x54, 0x45, 0x52, 0x49, 0x4E, 0x47, 0xF7, 0x52, 0x45,
    0x43, 0x4F, 0x56, 0x45, 0x52, 0x59, 0xF7, 0x4D, 0x4F, 0x44, 0x45, 0x0E, 0xF1, 0xFD,
};

void TTYD64_InstallBattles_pit_part_11(void) {
    Mod_SetBattleList("TTYD64", 0x3A, TTYD64_pit_part_11_FormationTable);
    Mod_SetStageList("TTYD64", 0x3A, TTYD64_pit_part_11_StageTable);
    {
        Bytecode id = Mod_RegisterInlineMessage("TTYD64", TTYD64_pit_part_11_String_HealingMode_Start2);
        TTYD64_imp_FakeBowser2_Script_HandleEvent_FakeBowser2[279] = id;
    }
    {
        Bytecode id = Mod_RegisterInlineMessage("TTYD64", TTYD64_pit_part_11_String_HealingMode_Start1);
        TTYD64_imp_FakeBowser2_Script_HealingMode_Start[15] = id;
    }
}
