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
#include "port/romhack/specific/TTYD64/battle/area/battles_b.h"
#include "port/romhack/specific/TTYD64/battle/area/battles_b_imports.h"

API_CALLABLE(b_area_kpa4_koopatrol_StartRumbleWithParams);
API_CALLABLE(b_area_kpa4_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_kpa4_magikoopa_ShrinkActor);
extern s32 b_area_dgb_tubba_blubba_DefenseTable[];
extern Vec3i b_area_kpa4_blaster_pos_1;
extern Vec3i b_area_kpa4_blaster_pos_2;
extern EvtScript b_area_kpa4_bombshell_bill_EVS_HandleEvent;
extern EvtScript b_area_kpa4_bombshell_bill_EVS_Idle;
extern EvtScript b_area_kpa4_bombshell_bill_EVS_MakeExplosionFX;
extern s32 b_area_kpa4_bombshell_bill_StatusTable[];
extern s32 b_area_kpa4_bombshell_blaster_DefenseTable[];
extern EvtScript b_area_kpa4_bombshell_blaster_EVS_HandleEvent;
extern EvtScript b_area_kpa4_bombshell_blaster_EVS_Idle;
extern s32 b_area_kpa4_bombshell_blaster_StatusTable[];
extern Vec3i b_area_kpa4_bombshell_blaster_SummonPos;
extern s32 b_area_kpa4_koopatrol_ChargedDefense[];
extern s32 b_area_kpa4_koopatrol_ChargedStatusTable[];
extern s32 b_area_kpa4_koopatrol_DefenseTable[];
extern EvtScript b_area_kpa4_koopatrol_EVS_CountActiveSummoners;
extern EvtScript b_area_kpa4_koopatrol_EVS_GetAvailableColumn;
extern EvtScript b_area_kpa4_koopatrol_EVS_HandlePhase;
extern EvtScript b_area_kpa4_koopatrol_EVS_UpdateOffsets;
extern u8 b_area_kpa4_koopatrol_FlipPosOffsets[];
extern Vec3i b_area_kpa4_koopatrol_SummonPos;
extern s32 b_area_kpa4_koopatrol_ToppledDefense[];
extern Stage b_area_kpa4_kpa_01;
extern Stage b_area_kpa4_kpa_01b;
extern Stage b_area_kpa4_kpa_02;
extern Stage b_area_kpa4_kpa_04;
extern Stage b_area_kpa4_kpa_04b;
extern Stage b_area_kpa4_kpa_04c;
extern Stage b_area_kpa4_kpa_05;
extern Stage b_area_kpa4_kpa_07;
extern Stage b_area_kpa4_kpa_08;
extern Stage b_area_kpa4_kpa_09;
extern Stage b_area_kpa4_kpa_11;
extern Stage b_area_kpa4_kpa_13;
extern Stage b_area_kpa4_kpa_14;
extern s32 b_area_kpa4_magikoopa_CloneStatusTable[];
extern EvtScript b_area_kpa4_magikoopa_EVS_Clone_Init;
extern EvtScript b_area_kpa4_magikoopa_EVS_Flee;
extern EvtScript b_area_kpa4_magikoopa_EVS_FlyingClone_Init;
extern EvtScript b_area_kpa4_magikoopa_EVS_GetAvailableColumn;
extern EvtScript b_area_kpa4_magikoopa_EVS_HandleEvent;
extern EvtScript b_area_kpa4_magikoopa_EVS_HandlePhase;
extern EvtScript b_area_kpa4_magikoopa_EVS_Idle;
extern s32 b_area_kpa4_magikoopa_FlyingCloneStatusTable[];
extern s32 b_area_kpa4_magikoopa_StatusTable[];
extern Vec3i b_area_kpa4_magikoopa_SummonPos;
extern Vec3i b_area_kpa4_pos_3;
extern EvtScript TTYD64_imp_25_Koopatrol_Script_HandleEvent_80228C44_12;
extern EvtScript TTYD64_imp_25_Magikoopa_Script_TakeTurn_80225034_25;
extern EvtScript TTYD64_imp_25_Magikoopa_Script_ShapeSpell_25;
extern EvtScript TTYD64_imp_25_Koopatrol_Script_Koopatrol_ChargeAttack_12;
extern EvtScript TTYD64_imp_25_Koopatrol_Script_Koopatrol_ShellToss_12;
extern EvtScript TTYD64_imp_25_Koopatrol_Script_TakeTurn_8022C454_12;
extern EvtScript TTYD64_imp_25_Magikoopa_Script_Electrify_25;
extern EvtScript TTYD64_imp_25_Koopatrol_Script_Koopatrol_PowerShell_12;
extern EvtScript TTYD64_imp_25_Magikoopa_Script_BoostDefense_25;
extern EvtScript TTYD64_imp_25_Magikoopa_Script_BoostAttack_25;
extern EvtScript TTYD64_imp_25_Magikoopa_Script_Vanish_25;
extern EvtScript TTYD64_imp_25_Magikoopa_Script_MakeCopy_25;
extern EvtScript TTYD64_imp_25_Magikoopa_Script_HealAll_25;
extern EvtScript TTYD64_imp_25_Koopatrol_Script_Koopatrol_Summon_12;
extern EvtScript TTYD64_imp_25_Magikoopa_Script_HealOne_25;
extern EvtScript TTYD64_imp_25_Koopatrol_Script_Idle_8022875C_12;
extern EvtScript TTYD64_imp_25_BombshellBill_Script_TakeTurn_80219670_25;
extern EvtScript TTYD64_imp_25_BombshellBlaster_Script_FireBombshell_25;
extern EvtScript TTYD64_imp_25_BombshellBill_Script_Init_80218F38_25;
extern EvtScript TTYD64_imp_25_BombshellBlaster_Script_TakeTurn_80218B0C_25;
extern EvtScript TTYD64_imp_25_BombshellBlaster_Script_FireTwoBombshells_25;
extern EvtScript TTYD64_imp_25_Magikoopa_Script_Init_8021F610_25;
extern EvtScript TTYD64_imp_25_Koopatrol_Script_Koopatrol_Hide_12;
extern EvtScript TTYD64_imp_25_Koopatrol_Script_Init_802283E8_12;
extern EvtScript TTYD64_imp_25_Koopatrol_Script_Koopatrol_Unhide_12;
extern s32 TTYD64_imp_25_Koopatrol_StatusTable_80228254_12[];
extern StageListRow TTYD64_kpa4_StageTable[];
extern Battle TTYD64_kpa4_FormationTable[];
extern EvtScript TTYD64_imp_25_BombshellBlaster_Script_Init_80218778_25;
extern FormationRow TTYD64_kpa4_Formation_01[];
extern FormationRow TTYD64_kpa4_Formation_04[];
extern FormationRow TTYD64_kpa4_Formation_03[];
extern s32 TTYD64_imp_25_Koopatrol_IdleAnimations_8022813C_12[];
extern s32 TTYD64_imp_25_Magikoopa_IdleAnimations_8021EA20_25[];
extern s32 TTYD64_imp_25_Koopatrol_IdleAnimations_802280F0_12[];
extern s32 TTYD64_imp_25_Koopatrol_IdleAnimations_80228188_12[];
extern s32 TTYD64_imp_25_Koopatrol_IdleAnimations_802281D4_12[];
extern s32 TTYD64_imp_25_Magikoopa_IdleAnimations_8021EA6C_25[];
extern FormationRow TTYD64_kpa4_Formation_00[];
extern FormationRow TTYD64_kpa4_Formation_02[];
extern ActorBlueprint TTYD64_imp_25_BombshellBill_25_BombshellBill;
extern ActorBlueprint TTYD64_imp_25_Koopatrol_25_Koopatrol;
extern ActorBlueprint TTYD64_imp_25_Magikoopa_25_Magikoopa;
extern ActorBlueprint TTYD64_imp_25_Magikoopa_FlyingMagiclone_25;
extern ActorBlueprint TTYD64_imp_25_BombshellBlaster_BombshellBill_25;
extern ActorBlueprint TTYD64_imp_25_BombshellBlaster_25_BombshellBlaster;
extern ActorBlueprint TTYD64_imp_25_Magikoopa_Magiclone_25;
extern ActorBlueprint TTYD64_imp_25_Koopatrol_Koopatrol_12;
extern s32 TTYD64_imp_25_BombshellBlaster_IdleAnimations_80218754_25[];
extern ActorPartBlueprint TTYD64_imp_25_Magikoopa_PartsTable_8021E940_25[];
extern ActorPartBlueprint TTYD64_imp_25_Magikoopa_PartsTable_80222B34_25[];
extern ActorPartBlueprint TTYD64_imp_25_Magikoopa_PartsTable_80222B58_25[];
extern ActorPartBlueprint TTYD64_imp_25_BombshellBill_PartsTable_80218EC8_25[];
extern ActorPartBlueprint TTYD64_imp_25_BombshellBlaster_PartsTable_80218708_25[];
extern ActorPartBlueprint TTYD64_imp_25_Koopatrol_PartsTable_8022839C_12[];
extern s32 TTYD64_imp_25_BombshellBill_IdleAnimations_80218F14_25[];
extern FormationRow TTYD64_imp_25_Magikoopa_SpecialFormation_80222BF4_25[];
extern FormationRow TTYD64_imp_25_Magikoopa_SpecialFormation_80222BD8_25[];
extern FormationRow TTYD64_imp_25_Koopatrol_SpecialFormation_8022BBC8_12[];
extern FormationRow TTYD64_imp_25_BombshellBlaster_SpecialFormation_80218DF4_25[];
extern s32 TTYD64_imp_25_BombshellBill_DefenseTable_80218E10_25[];
extern s32 TTYD64_imp_25_Koopatrol_IdleAnimations_Koopatrol_Hide_12[];
extern s32 TTYD64_imp_25_Magikoopa_DefenseTable_802229D0_25[];
extern s32 TTYD64_imp_25_Magikoopa_DefenseTable_802229C4_25[];
extern s32 TTYD64_imp_25_Magikoopa_DefenseTable_8021E7D0_25[];
API_CALLABLE(TTYD64_imp_25_BombshellBlaster_Function_80218000_25);

API_CALLABLE(TTYD64_imp_25_BombshellBlaster_Function_80218000_25) {
    TTYD64_imp_25_BombshellBlaster_SpecialFormation_80218DF4_25[0].var0 = true;
    TTYD64_imp_25_BombshellBlaster_SpecialFormation_80218DF4_25[0].var1 = script->owner1.actorID;

    return ApiStatus_DONE2;
}

// clang-format off
EvtScript TTYD64_imp_25_Koopatrol_Script_HandleEvent_80228C44_12 = {
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
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa4_koopatrol_ToppledDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_25_Koopatrol_IdleAnimations_80228188_12))
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
            UseBuf(Ref(b_area_kpa4_koopatrol_FlipPosOffsets))
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
                Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_imp_25_Koopatrol_StatusTable_80228254_12))
                Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa4_koopatrol_DefenseTable))
                Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
                Call(SetActorVar, ACTOR_SELF, 0, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_25_Koopatrol_IdleAnimations_802280F0_12))
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
EvtScript TTYD64_imp_25_Magikoopa_Script_TakeTurn_80225034_25 = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_25_Magikoopa_Script_ShapeSpell_25)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 10, LVar0)
    IfEq(LVar0, 1)
        Goto(20)
    EndIf
    Set(LVarA, 0)
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
    Call(GetActorHP, LVar0, LVar2)
    Call(GetEnemyMaxHP, LVar0, LVar3)
    MulF(LVar2, Float(100.0))
    DivF(LVar2, LVar3)
    IfEq(LFlag0, 0)
        IfLe(LVar2, 25)
            Call(RandInt, 99, LVar4)
            Add(LVar4, 1)
            IfLt(LVar4, 75)
                Add(LVarA, 1)
                Set(LVarB, LVar0)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfGt(LVarA, 0)
        Goto(10)
    EndIf
    Set(LVarA, 0)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(1)
    Set(LFlag0, 0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar1)
    IfEq(LVar1, 71)
        Call(GetActorVar, LVar0, 8, LVar1)
        IfEq(LVar1, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetActorHP, LVar0, LVar2)
    Call(GetEnemyMaxHP, LVar0, LVar3)
    MulF(LVar2, Float(100.0))
    DivF(LVar2, LVar3)
    IfEq(LFlag0, 0)
        IfLe(LVar2, 20)
            Call(RandInt, 99, LVar4)
            Add(LVar4, 1)
            IfLt(LVar4, 80)
                Add(LVarA, 1)
                Set(LVarB, LVar0)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(1)
    EndIf
    IfGt(LVarA, 0)
        Goto(10)
    EndIf
    Set(LVarA, 0)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(2)
    Set(LFlag0, 0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar1)
    IfEq(LVar1, 71)
        Call(GetActorVar, LVar0, 8, LVar1)
        IfEq(LVar1, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetActorHP, LVar0, LVar2)
    Call(GetEnemyMaxHP, LVar0, LVar3)
    MulF(LVar2, Float(100.0))
    DivF(LVar2, LVar3)
    IfEq(LFlag0, 0)
        IfLe(LVar2, 15)
            Call(RandInt, 99, LVar4)
            Add(LVar4, 1)
            IfLt(LVar4, 100)
                Add(LVarA, 1)
                Set(LVarB, LVar0)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(2)
    EndIf
    IfGt(LVarA, 0)
        Goto(10)
    EndIf
    Goto(20)
    Label(10)
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_kpa4_magikoopa_EVS_Flee)
        Return
    EndIf
    IfEq(LVarA, 1)
        Call(GetActorVar, ACTOR_SELF, 4, LVar0)
        IfLt(LVar0, 2)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 500)
                ExecWait(TTYD64_imp_25_Magikoopa_Script_HealOne_25)
                Return
            EndIf
        Else
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            IfLt(LVar0, 2)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 500)
                    ExecWait(TTYD64_imp_25_Magikoopa_Script_HealAll_25)
                    Return
                EndIf
            EndIf
        EndIf
    Else
        Call(GetActorVar, ACTOR_SELF, 3, LVar0)
        IfLt(LVar0, 2)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 500)
                ExecWait(TTYD64_imp_25_Magikoopa_Script_HealAll_25)
                Return
            EndIf
        Else
            Call(GetActorVar, ACTOR_SELF, 4, LVar0)
            IfLt(LVar0, 2)
                SetF(LVar9, Float(100.0))
                Call(CreateHomeTargetList, 0x8002)
                Call(InitTargetIterator)
                Label(11)
                Set(LFlag0, 0)
                Call(GetOwnerTarget, LVar0, LVar1)
                Call(GetOriginalActorType, LVar0, LVar1)
                IfEq(LVar1, 71)
                    Call(GetActorVar, LVar0, 8, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                    EndIf
                EndIf
                Call(GetActorHP, LVar0, LVar2)
                Call(GetEnemyMaxHP, LVar0, LVar3)
                MulF(LVar2, Float(100.0))
                DivF(LVar2, LVar3)
                IfEq(LFlag0, 0)
                    IfLe(LVar2, LVar9)
                        SetF(LVar9, LVar2)
                        Set(LVarB, LVar0)
                    EndIf
                EndIf
                Call(ChooseNextTarget, 0, LVar0)
                IfNe(LVar0, -1)
                    Goto(11)
                EndIf
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 500)
                    ExecWait(TTYD64_imp_25_Magikoopa_Script_HealOne_25)
                    Return
                EndIf
            EndIf
        EndIf
    EndIf
    Label(20)
    Set(LVarA, 10)
    Set(LVarB, 10)
    Set(LVarC, 10)
    Set(LVarD, 10)
    Set(LVarE, 10)
    Set(LVarF, 10)
    Call(GetActorVar, ACTOR_SELF, 10, LVar0)
    IfEq(LVar0, 1)
        Set(LVarA, 100)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Set(LVarD, 0)
        Set(LVarE, 0)
        Set(LVarF, 0)
        Goto(123)
    Else
        ExecWait(b_area_kpa4_magikoopa_EVS_GetAvailableColumn)
        IfEq(LVar0, -1)
            Set(LVarB, 0)
        EndIf
    EndIf
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNe(LVar0, 0)
        Set(LVarB, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 11, LVar0)
    Switch(LVar0)
        CaseEq(4)
            Call(GetActorVar, ACTOR_SELF, 5, LVar1)
            IfLt(LVar1, 3)
                Call(RandInt, 99, LVar0)
                Add(LVar0, 1)
                IfLe(LVar0, 50)
                    Set(LVarA, 0)
                    Set(LVarB, 0)
                    Set(LVarC, 100)
                    Set(LVarD, 0)
                    Set(LVarE, 0)
                    Set(LVarF, 0)
                EndIf
            EndIf
        CaseEq(5)
            Call(GetActorVar, ACTOR_SELF, 6, LVar1)
            IfLt(LVar1, 3)
                Call(RandInt, 99, LVar0)
                Add(LVar0, 1)
                IfLe(LVar0, 50)
                    Set(LVarA, 0)
                    Set(LVarB, 0)
                    Set(LVarC, 0)
                    Set(LVarD, 100)
                    Set(LVarE, 0)
                    Set(LVarF, 0)
                EndIf
            EndIf
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    IfGe(LVar0, 3)
        Set(LVarC, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    IfGe(LVar0, 3)
        Set(LVarD, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 7, LVar0)
    IfGe(LVar0, 3)
        Set(LVarE, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfGe(LVar0, 3)
        Set(LVarF, 0)
    EndIf
    Label(123)
    Set(LVar9, 0)
    Add(LVar9, LVarA)
    Add(LVar9, LVarB)
    Add(LVar9, LVarC)
    Add(LVar9, LVarD)
    Add(LVar9, LVarE)
    Add(LVar9, LVarF)
    Sub(LVar9, 1)
    Call(RandInt, LVar9, LVar0)
    Add(LVar0, 1)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_imp_25_Magikoopa_Script_ShapeSpell_25)
        Return
    EndIf
    Add(LVarA, LVarB)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_imp_25_Magikoopa_Script_MakeCopy_25)
        Return
    EndIf
    Add(LVarA, LVarC)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_imp_25_Magikoopa_Script_BoostAttack_25)
        Return
    EndIf
    Add(LVarA, LVarD)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_imp_25_Magikoopa_Script_BoostDefense_25)
        Return
    EndIf
    Add(LVarA, LVarE)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_imp_25_Magikoopa_Script_Electrify_25)
        Return
    EndIf
    ExecWait(TTYD64_imp_25_Magikoopa_Script_Vanish_25)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_25_Magikoopa_Script_ShapeSpell_25 = {
    Call(SetActorVar, ACTOR_SELF, 11, 2)
    Set(LFlag0, 0)
    Set(LFlag1, 0)
    Call(GetActorVar, ACTOR_SELF, 10, LVar0)
    IfEq(LVar0, 1)
        Set(LFlag0, 1)
        Call(GetActorVar, ACTOR_SELF, 9, LVarA)
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        Set(LFlag1, 1)
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    IfEq(LFlag0, 1)
        Call(UseIdleAnimation, LVarA, 0)
    EndIf
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
    IfEq(LFlag1, 0)
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x560002)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 17)
            Add(LVar1, 33)
            Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 13)
        Else
            Sub(LVar0, 17)
            Add(LVar1, 33)
        EndIf
        Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    Else
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x570002)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
        EndIf
        Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Wait(30)
    Call(EnemyTestTarget, ACTOR_SELF, LVar9, 0, 0, 1, 16)
    Switch(LVar9)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LFlag0, 1)
                Call(PlaySoundAtActor, LVarA, 8405)
            EndIf
            Call(PlaySoundAtActor, ACTOR_SELF, 8405)
            IfEq(LFlag1, 0)
                IfEq(LFlag0, 1)
                    Call(SetAnimation, LVarA, 1, 0x560003)
                EndIf
                Call(SetAnimation, ACTOR_SELF, 1, 0x560003)
            Else
                IfEq(LFlag0, 1)
                    Call(SetAnimation, LVarA, 1, 0x570003)
                EndIf
                Call(SetAnimation, ACTOR_SELF, 2, 0x570003)
            EndIf
            Wait(5)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
            Sub(LVar4, 50)
            Set(LVar5, 0)
            IfEq(LFlag1, 0)
                IfEq(LFlag0, 1)
                    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                    Call(b_area_kpa4_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
                EndIf
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfFlag(LVar3, 0x80000)
                    Sub(LVar0, 8)
                    Add(LVar1, 8)
                Else
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                EndIf
                Call(b_area_kpa4_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
            Else
                IfEq(LFlag0, 1)
                    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                    Call(b_area_kpa4_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
                EndIf
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfFlag(LVar3, 0x80000)
                    Sub(LVar0, 8)
                    Add(LVar1, 8)
                Else
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                EndIf
                Call(b_area_kpa4_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
            EndIf
            Wait(50)
            IfEq(LVar9, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(YieldTurn)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            IfEq(LFlag0, 1)
                Call(UseIdleAnimation, LVarA, 1)
            EndIf
            Return
        EndCaseGroup
    EndSwitch
    IfEq(LFlag0, 1)
        Call(PlaySoundAtActor, LVarA, 8405)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8405)
    IfEq(LFlag1, 0)
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x560003)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 1, 0x560003)
    Else
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x570003)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 2, 0x570003)
    EndIf
    Wait(5)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
    IfEq(LFlag1, 0)
        IfEq(LFlag0, 1)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Add(LVar1, 20)
            Call(b_area_kpa4_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
        EndIf
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 8)
            Add(LVar1, 8)
        Else
            Sub(LVar0, 20)
            Add(LVar1, 20)
        EndIf
        Call(b_area_kpa4_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
    Else
        IfEq(LFlag0, 1)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Add(LVar1, 20)
            Call(b_area_kpa4_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
        EndIf
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 8)
            Add(LVar1, 8)
        Else
            Sub(LVar0, 20)
            Add(LVar1, 20)
        EndIf
        Call(b_area_kpa4_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
    EndIf
    Wait(18)
    IfEq(LFlag0, 1)
        Wait(2)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 6, 32)
    Else
        Wait(2)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 6, 32)
    EndIf
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(20)
            Call(YieldTurn)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    IfEq(LFlag0, 1)
        Call(UseIdleAnimation, LVarA, 1)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_25_Koopatrol_Script_Koopatrol_ChargeAttack_12 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_Unhide_12)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Call(RandInt, 100, LVar0)
        IfLt(LVar0, 50)
            ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_Hide_12)
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
        Call(b_area_kpa4_koopatrol_StartRumbleWithParams, 128, 10)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(0.5))
        EndThread
        Call(SetAnimation, ACTOR_SELF, 1, 0x590006)
        Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kpa4_koopatrol_ChargedStatusTable))
        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa4_koopatrol_ChargedDefense))
        Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 0)
        Call(SetActorVar, ACTOR_SELF, 0, 2)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_25_Koopatrol_IdleAnimations_802281D4_12))
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
            Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_imp_25_Koopatrol_StatusTable_80228254_12))
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa4_koopatrol_DefenseTable))
            Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_25_Koopatrol_IdleAnimations_802280F0_12))
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
            Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_imp_25_Koopatrol_StatusTable_80228254_12))
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa4_koopatrol_DefenseTable))
            Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_25_Koopatrol_IdleAnimations_802280F0_12))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_25_Koopatrol_Script_Koopatrol_ShellToss_12 = {
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
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_25_Koopatrol_IdleAnimations_802280F0_12))
                Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa4_koopatrol_DefenseTable))
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
            ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_PowerShell_12)
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
EvtScript TTYD64_imp_25_Koopatrol_Script_TakeTurn_8022C454_12 = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetBattleVar, 1, 1)
        ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ShellToss_12)
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
                                    ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ChargeAttack_12)
                                Else
                                    Call(SetBattleVar, 1, 1)
                                    ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ShellToss_12)
                                EndIf
                                Return
                            EndIf
                        EndCaseGroup
                        CaseEq(2)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 300)
                                Call(SetBattleVar, 1, 2)
                                ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ChargeAttack_12)
                            Else
                                Call(SetBattleVar, 1, 1)
                                ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ShellToss_12)
                            EndIf
                            Return
                    EndSwitch
                    ExecWait(b_area_kpa4_koopatrol_EVS_GetAvailableColumn)
                    IfEq(LVarA, -1)
                        Call(RandInt, 1000, LVar0)
                        IfLt(LVar0, 300)
                            Call(SetBattleVar, 1, 2)
                            ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ChargeAttack_12)
                        Else
                            Call(SetBattleVar, 1, 1)
                            ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ShellToss_12)
                        EndIf
                        Return
                    EndIf
                    ExecWait(b_area_kpa4_koopatrol_EVS_CountActiveSummoners)
                    Switch(LVar9)
                        CaseEq(1)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 400)
                                Call(SetBattleVar, 1, 1)
                                ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_Summon_12)
                                Return
                            EndIf
                        CaseEq(2)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 200)
                                Call(SetBattleVar, 1, 1)
                                ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_Summon_12)
                                Return
                            EndIf
                        CaseEq(3)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 100)
                                Call(SetBattleVar, 1, 1)
                                ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_Summon_12)
                                Return
                            EndIf
                    EndSwitch
                    Call(RandInt, 1000, LVar0)
                    IfLt(LVar0, 300)
                        Call(SetBattleVar, 1, 2)
                        ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ChargeAttack_12)
                    Else
                        Call(SetBattleVar, 1, 1)
                        ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ShellToss_12)
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
                                    ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ChargeAttack_12)
                                Else
                                    Call(SetBattleVar, 1, 1)
                                    ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ShellToss_12)
                                EndIf
                                Return
                            EndIf
                        EndCaseGroup
                        CaseEq(2)
                            ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ShellToss_12)
                            Return
                    EndSwitch
                    ExecWait(b_area_kpa4_koopatrol_EVS_GetAvailableColumn)
                    IfEq(LVarA, -1)
                        ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ShellToss_12)
                        Return
                    EndIf
                    ExecWait(b_area_kpa4_koopatrol_EVS_CountActiveSummoners)
                    Switch(LVar9)
                        CaseEq(1)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 400)
                                ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_Summon_12)
                                Return
                            EndIf
                        CaseEq(2)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 200)
                                ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_Summon_12)
                                Return
                            EndIf
                        CaseEq(3)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 100)
                                ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_Summon_12)
                                Return
                            EndIf
                    EndSwitch
                    ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ShellToss_12)
                CaseEq(2)
                    ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ChargeAttack_12)
            EndSwitch
        CaseEq(1)
            Call(SetBattleVar, 1, 1)
            ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ShellToss_12)
        CaseEq(2)
            ExecWait(TTYD64_imp_25_Koopatrol_Script_Koopatrol_ChargeAttack_12)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_25_Magikoopa_Script_Electrify_25 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_kpa4_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
        IfEq(LVar3, 0)
            Call(GetStatusFlags, LVar0, LVar4)
            IfNotFlag(LVar4, 0x4002000)
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
        ExecWait(b_area_kpa4_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_imp_25_Magikoopa_Script_ShapeSpell_25)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 6)
    Call(AddActorVar, ACTOR_SELF, 7, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 752)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Loop(4)
            Call(PlaySoundAtActor, LVar8, 978)
            Call(RandInt, 3, LVar0)
            Add(LVar0, 3)
            Wait(LVar0)
        EndLoop
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(ElectrifyActor, LVar8, 3)
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
EvtScript TTYD64_imp_25_Koopatrol_Script_Koopatrol_PowerShell_12 = {
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
EvtScript TTYD64_imp_25_Magikoopa_Script_BoostDefense_25 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_kpa4_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
        IfEq(LVar3, 0)
            Call(GetActorDefenseBoost, LVar0, LVar4)
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
        ExecWait(b_area_kpa4_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_imp_25_Magikoopa_Script_ShapeSpell_25)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 5)
    Call(AddActorVar, ACTOR_SELF, 6, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Call(PlaySoundAtActor, LVar8, 733)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(TTYD64_BoostDefense, LVar8, 1, 3)
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
EvtScript TTYD64_imp_25_Magikoopa_Script_BoostAttack_25 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_kpa4_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
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
        ExecWait(b_area_kpa4_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_imp_25_Magikoopa_Script_ShapeSpell_25)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 4)
    Call(AddActorVar, ACTOR_SELF, 5, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
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
EvtScript TTYD64_imp_25_Magikoopa_Script_Vanish_25 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_kpa4_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
        IfEq(LVar3, 0)
            Call(GetStatusFlags, LVar0, LVar4)
            IfNotFlag(LVar4, 0x4002000)
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
        ExecWait(b_area_kpa4_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_imp_25_Magikoopa_Script_ShapeSpell_25)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 7)
    Call(AddActorVar, ACTOR_SELF, 8, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Call(PlaySoundAtActor, LVar8, 731)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(VanishActor, LVar8, 2)
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
EvtScript TTYD64_imp_25_Magikoopa_Script_MakeCopy_25 = {
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_kpa4_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(SetActorVar, ACTOR_SELF, 10, 1)
    Call(SetActorVar, ACTOR_SELF, 11, 3)
    Set(LFlag0, 0)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        Set(LFlag0, 1)
    EndIf
    IfEq(LFlag0, 0)
        Call(SummonEnemy, Ref(TTYD64_imp_25_Magikoopa_SpecialFormation_80222BD8_25), 0)
    Else
        Call(SummonEnemy, Ref(TTYD64_imp_25_Magikoopa_SpecialFormation_80222BF4_25), 0)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 9, LVar0)
    Set(LVarA, LVar0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(EnableIdleScript, LVarA, 0)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(UseIdleAnimation, LVarA, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 25)
    Wait(25)
    Call(PlaySoundAtActor, ACTOR_SELF, 8406)
    IfEq(LFlag0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
        Call(SetAnimation, LVarA, 1, 0x560002)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 23)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
        Call(SetAnimation, LVarA, 1, 0x570002)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 23)
    EndIf
    Call(PlayEffect_impl, 107, 1, LVar0, LVar1, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
    Wait(10)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(EnableIdleScript, LVar9, 1)
    Wait(30)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, -3)
    Call(SetActorPos, LVarA, LVar0, LVar1, LVar2)
    Set(LVar9, LVarA)
    Wait(15)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Call(PlaySoundAtActor, ACTOR_SELF, 8407)
    Call(PlaySoundAtActor, LVar9, 8407)
    Call(SetPartFlagBits, LVar9, 1, 0x800000, 0)
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 500)
        Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
        ExecWait(b_area_kpa4_magikoopa_EVS_GetAvailableColumn)
        Call(SetGoalToIndex, ACTOR_SELF, LVar0)
        Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
    Else
        Call(SetActorSpeed, LVar9, Float(2.0))
        ExecWait(b_area_kpa4_magikoopa_EVS_GetAvailableColumn)
        Call(SetGoalToIndex, LVar9, LVar0)
        Call(FlyToGoal, LVar9, 0, 0, 0)
    EndIf
    Call(SetPartFlagBits, LVar9, 1, 0x800000, 1)
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(SetEnemyHP, LVar9, LVar0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Call(GetActorPos, LVar9, LVar0, LVar1, LVar2)
    Call(ForceHomePos, LVar9, LVar0, LVar1, LVar2)
    Call(HPBarToHome, LVar9)
    IfEq(LFlag0, 0)
        Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 1)
    Else
        Call(SetPartEventBits, ACTOR_SELF, 2, 0x400000, 1)
    EndIf
    IfEq(LFlag0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
        Call(SetAnimation, LVar9, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
        Call(SetAnimation, LVar9, 1, 0x570001)
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Call(UseIdleAnimation, LVar9, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_25_Magikoopa_Script_HealAll_25 = {
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 1)
    Call(AddActorVar, ACTOR_SELF, 3, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
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
    Call(MoveBattleCamOver, 10)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_25_Koopatrol_Script_Koopatrol_Summon_12 = {
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
    Call(SummonEnemy, Ref(TTYD64_imp_25_Koopatrol_SpecialFormation_8022BBC8_12), 0)
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
EvtScript TTYD64_imp_25_Magikoopa_Script_HealOne_25 = {
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 0)
    Call(AddActorVar, ACTOR_SELF, 4, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
    EndIf
    Wait(5)
    Thread
        Wait(5)
        Call(PlaySoundAtActor, LVarB, 8301)
        Call(PlaySoundAtActor, LVarB, 532)
        Wait(30)
        Call(PlaySoundAtActor, LVarB, 604)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(HealActor, LVarB, 8, 0)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_25_Koopatrol_Script_Idle_8022875C_12 = {
    Label(0)
    Call(RandInt, 80, LVarA)
    Add(LVarA, 80)
    Loop(LVarA)
        Label(1)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        Call(GetActorVar, ACTOR_SELF, 3, LVar2)
        ExecWait(b_area_kpa4_koopatrol_EVS_UpdateOffsets)
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_25_Koopatrol_IdleAnimations_8022813C_12))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_25_Koopatrol_IdleAnimations_802280F0_12))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_25_Koopatrol_IdleAnimations_80228188_12))
    EndSwitch
    Loop(20)
        Label(2)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        Call(GetActorVar, ACTOR_SELF, 3, LVar2)
        ExecWait(b_area_kpa4_koopatrol_EVS_UpdateOffsets)
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_25_Koopatrol_IdleAnimations_8022813C_12))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_25_Koopatrol_IdleAnimations_802280F0_12))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_25_Koopatrol_IdleAnimations_80228188_12))
    EndSwitch
    Loop(80)
        Label(3)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        Call(GetActorVar, ACTOR_SELF, 3, LVar2)
        ExecWait(b_area_kpa4_koopatrol_EVS_UpdateOffsets)
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
EvtScript TTYD64_imp_25_BombshellBill_Script_TakeTurn_80219670_25 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2D0104)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(15)
    Call(UseBattleCamPresetImmediately, 19)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 6, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Set(LVar3, LVar1)
            Call(GetOwnerTarget, LVar4, 0)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Set(LVar1, LVar3)
            Sub(LVar0, 90)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.009765625))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 18, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(HideHealthBar, ACTOR_SELF)
            Call(UseIdleAnimation, ACTOR_SELF, 0)
            Call(RemoveActor, ACTOR_SELF)
            Return
        EndCaseGroup
    EndSwitch
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar3, LVar1)
    Call(GetOwnerTarget, LVar4, 0)
    Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
    Set(LVar1, LVar3)
    Add(LVar0, 10)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.009765625))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
    ExecWait(b_area_kpa4_bombshell_bill_EVS_MakeExplosionFX)
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 6, 32)
    Call(UseBattleCamPreset, 2)
    Call(YieldTurn)
    SetConst(LVar0, 1)
    SetConst(LVar1, 0x2D0107)
    Set(LVar2, -0x3039)
    ExecWait(Ref(EVS_Enemy_Death))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_25_BombshellBlaster_Script_FireBombshell_25 = {
    Call(SetAnimation, ACTOR_SELF, 1, 0x2E0102)
    Wait(13)
    Thread
        Call(ShakeCam, 1, 0, 10, Float(1.0))
    EndThread
    Call(StartRumble, 9)
    Call(PlaySoundAtActor, ACTOR_SELF, 712)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 33)
    Add(LVar1, 19)
    Add(LVar2, 3)
    Call(PlayEffect_impl, 0, LVar0, LVar1, LVar2, 2, 5, 0, 2, 0, 0, 0, 0, 0, 0)
    Call(PlayEffect_impl, 0, LVar0, LVar1, LVar2, 2, 5, 2, 2, 0, 0, 0, 0, 0, 0)
    Wait(2)
    Call(TTYD64_imp_25_BombshellBlaster_Function_80218000_25)
    Set(LVar3, 0)
    Call(RandInt, 100, LVar0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar1)
    Call(ActorExists, LVar1, LVar2)
    IfEq(LVar1, 0)
        Set(LVar2, 0)
    EndIf
    IfEq(LVar2, 1)
        Set(LVar0, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar1)
    Call(ActorExists, LVar1, LVar2)
    IfEq(LVar1, 0)
        Set(LVar2, 0)
    EndIf
    IfEq(LVar2, 1)
        Set(LVar0, 100)
    EndIf
    IfGt(LVar0, 50)
        Set(LVar3, 1)
        Call(TTYD64_BattlesB_SetFormationField, Ref(TTYD64_imp_25_BombshellBlaster_SpecialFormation_80218DF4_25), TTYD64_BATTLESB_FORMATION_VAR2, 1)
    EndIf
    Call(SummonEnemy, Ref(TTYD64_imp_25_BombshellBlaster_SpecialFormation_80218DF4_25), 0)
    IfEq(LVar3, 1)
        Call(SetActorVar, ACTOR_SELF, 1, LVar0)
    Else
        Call(SetActorVar, ACTOR_SELF, 0, LVar0)
    EndIf
    Call(TTYD64_BattlesB_SetFormationField, Ref(TTYD64_imp_25_BombshellBlaster_SpecialFormation_80218DF4_25), TTYD64_BATTLESB_FORMATION_VAR2, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_25_BombshellBill_Script_Init_80218F38_25 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_25_BombshellBill_Script_TakeTurn_80219670_25))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa4_bombshell_bill_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kpa4_bombshell_bill_EVS_HandleEvent))
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 16)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(HPBarToHome, ACTOR_SELF)
    Else
        Call(GetActorVar, ACTOR_SELF, 1, LVar0)
        Call(GetActorPos, LVar0, LVar1, LVar2, LVar3)
        Call(GetStatusFlags, LVar0, LVar4)
        IfFlag(LVar4, 0x80000)
            Set(LVar5, -13)
            Set(LVar6, 4)
        Else
            Set(LVar5, -33)
            Set(LVar6, 11)
        EndIf
        Add(LVar1, LVar5)
        Add(LVar2, LVar6)
        Call(GetActorVar, ACTOR_SELF, 2, LVar4)
        IfGt(LVar4, 0)
            Add(LVar2, 30)
        EndIf
        Call(SetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
        Call(CopyStatusEffects, LVar0, ACTOR_SELF)
        Call(CopyBuffs, LVar0, ACTOR_SELF)
        Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
        Call(GetActorPos, LVar0, LVar1, LVarB, LVarC)
        Sub(LVar1, 90)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.009765625))
        Call(SetAnimation, ACTOR_SELF, 1, 0x2D0103)
        Call(SetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
        Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x2D0101)
        Call(ForceHomePos, ACTOR_SELF, LVar1, LVar2, LVar3)
        Call(HPBarToHome, ACTOR_SELF)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_25_BombshellBlaster_Script_TakeTurn_80218B0C_25 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Call(ActorExists, LVar0, LVar1)
    IfEq(LVar0, 0)
        Set(LVar1, 0)
    EndIf
    IfEq(LVar1, 0)
        Call(SetActorVar, ACTOR_SELF, 0, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Call(ActorExists, LVar0, LVar2)
    IfEq(LVar0, 0)
        Set(LVar2, 0)
    EndIf
    IfEq(LVar2, 0)
        Call(SetActorVar, ACTOR_SELF, 1, 0)
    EndIf
    Add(LVar2, LVar1)
    IfEq(LVar2, 0)
        Call(RandInt, 100, LVar2)
        IfLt(LVar2, 30)
            ExecWait(TTYD64_imp_25_BombshellBlaster_Script_FireTwoBombshells_25)
            Goto(0)
        EndIf
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar1)
    IfEq(LVar0, 0)
        ExecWait(TTYD64_imp_25_BombshellBlaster_Script_FireBombshell_25)
        Goto(0)
    EndIf
    IfEq(LVar1, 0)
        ExecWait(TTYD64_imp_25_BombshellBlaster_Script_FireBombshell_25)
    EndIf
    Label(0)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_25_BombshellBlaster_Script_FireTwoBombshells_25 = {
    Set(LVarA, 2)
    Loop(LVarA)
        Call(SetAnimation, ACTOR_SELF, 1, 0x2E0102)
        Wait(13)
        Thread
            Call(ShakeCam, 1, 0, 10, Float(1.0))
        EndThread
        Call(StartRumble, 9)
        Call(PlaySoundAtActor, ACTOR_SELF, 712)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 33)
        Add(LVar1, 19)
        Add(LVar2, 3)
        Call(PlayEffect_impl, 0, LVar0, LVar1, LVar2, 2, 5, 0, 2, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 0, LVar0, LVar1, LVar2, 2, 5, 2, 2, 0, 0, 0, 0, 0, 0)
        Wait(2)
        Call(TTYD64_imp_25_BombshellBlaster_Function_80218000_25)
        Switch(LVarA)
            CaseEq(2)
                Call(TTYD64_BattlesB_SetFormationField, Ref(TTYD64_imp_25_BombshellBlaster_SpecialFormation_80218DF4_25), TTYD64_BATTLESB_FORMATION_VAR2, 1)
                Call(SummonEnemy, Ref(TTYD64_imp_25_BombshellBlaster_SpecialFormation_80218DF4_25), 0)
                Call(SetActorVar, ACTOR_SELF, 1, LVar0)
            CaseEq(1)
                Call(SummonEnemy, Ref(TTYD64_imp_25_BombshellBlaster_SpecialFormation_80218DF4_25), 0)
                Call(SetActorVar, ACTOR_SELF, 0, LVar0)
        EndSwitch
        Call(TTYD64_BattlesB_SetFormationField, Ref(TTYD64_imp_25_BombshellBlaster_SpecialFormation_80218DF4_25), TTYD64_BATTLESB_FORMATION_VAR2, 0)
    EndLoop
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_25_Magikoopa_Script_Init_8021F610_25 = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa4_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_25_Magikoopa_Script_TakeTurn_80225034_25))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kpa4_magikoopa_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kpa4_magikoopa_EVS_HandlePhase))
    Call(GetBattleVar, 2, LVar0)
    IfEq(LVar0, 0)
        Call(SetBattleVar, 2, -1)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 0)
    Call(SetActorVar, ACTOR_SELF, 7, 0)
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(SetActorVar, ACTOR_SELF, 9, -1)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, -1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_25_Koopatrol_Script_Koopatrol_Hide_12 = {
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
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kpa4_koopatrol_ChargedStatusTable))
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_dgb_tubba_blubba_DefenseTable))
    Call(SetActorVar, ACTOR_SELF, 0, 2)
    Call(SetActorVar, ACTOR_SELF, 3, 1)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_25_Koopatrol_IdleAnimations_Koopatrol_Hide_12))
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
EvtScript TTYD64_imp_25_Koopatrol_Script_Init_802283E8_12 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_25_Koopatrol_Script_TakeTurn_8022C454_12))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_25_Koopatrol_Script_Idle_8022875C_12))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_25_Koopatrol_Script_HandleEvent_80228C44_12))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kpa4_koopatrol_EVS_HandlePhase))
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
EvtScript TTYD64_imp_25_Koopatrol_Script_Koopatrol_Unhide_12 = {
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590001)
    Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_imp_25_Koopatrol_StatusTable_80228254_12))
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa4_koopatrol_DefenseTable))
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_25_Koopatrol_IdleAnimations_802280F0_12))
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_25_Koopatrol_StatusTable_80228254_12[] = {
    1,  0, 2,  0,  6,  50, 9,  60, 7,  60, 4,  75, 3,  0, 11, 80, 5,  75, 10, 70, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

StageListRow TTYD64_kpa4_StageTable[] = {
    { .name = "kpa_01", .stage = &b_area_kpa4_kpa_01 },
    { .name = "kpa_01b", .stage = &b_area_kpa4_kpa_01b },
    { .name = "kpa_02", .stage = &b_area_kpa4_kpa_02 },
    { .name = "kpa_03", .stage = &b_area_kpa4_kpa_04 },
    { .name = "kpa_04", .stage = &b_area_kpa4_kpa_04 },
    { .name = "kpa_04b", .stage = &b_area_kpa4_kpa_04b },
    { .name = "kpa_04c", .stage = &b_area_kpa4_kpa_04c },
    { .name = "kpa_05", .stage = &b_area_kpa4_kpa_05 },
    { .name = "kpa_07", .stage = &b_area_kpa4_kpa_07 },
    { .name = "kpa_08", .stage = &b_area_kpa4_kpa_08 },
    { .name = "kpa_09", .stage = &b_area_kpa4_kpa_09 },
    { .name = "kpa_11", .stage = &b_area_kpa4_kpa_11 },
    { .name = "kpa_13", .stage = &b_area_kpa4_kpa_13 },
    { .name = "kpa_14", .stage = &b_area_kpa4_kpa_14 },
    {},
};

Battle TTYD64_kpa4_FormationTable[] = {
    { .name = "\271\374\321\374\255\351\374x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kpa4_Formation_00,
      .stage = &b_area_kpa4_kpa_01,
      .onBattleStart = NULL },
    { .name = "\271\374\321\374\255\351\374x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa4_Formation_01,
      .stage = &b_area_kpa4_kpa_01,
      .onBattleStart = NULL },
    { .name = "\271\374\321\374\255\351\374_D{Fx\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kpa4_Formation_02,
      .stage = &b_area_kpa4_kpa_01,
      .onBattleStart = NULL },
    { .name = "\271\374\321\374\255\351\374_D{Fx\022,\310\262\316\263",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa4_Formation_03,
      .stage = &b_area_kpa4_kpa_01,
      .onBattleStart = NULL },
    { .name = "\271\374\321\374\255\351\374_D{Fx\022,\253\341\303\257",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa4_Formation_04,
      .stage = &b_area_kpa4_kpa_01,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_imp_25_BombshellBlaster_Script_Init_80218778_25 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_25_BombshellBlaster_Script_TakeTurn_80218B0C_25))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa4_bombshell_blaster_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kpa4_bombshell_blaster_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_kpa4_Formation_01[] = {
    { .actor = &TTYD64_imp_25_BombshellBill_25_BombshellBill,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_25_BombshellBill_25_BombshellBill,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_25_BombshellBill_25_BombshellBill,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kpa4_Formation_04[] = {
    { .actor = &TTYD64_imp_25_BombshellBlaster_25_BombshellBlaster,
      .home = { .vec = &b_area_kpa4_blaster_pos_1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOMBSHELLBLASTER },
    { .actor = &TTYD64_imp_25_BombshellBlaster_25_BombshellBlaster,
      .home = { .vec = &b_area_kpa4_blaster_pos_2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOMBSHELLBLASTER },
    { .actor = &TTYD64_imp_25_Magikoopa_25_Magikoopa,
      .home = { .vec = &b_area_kpa4_pos_3 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa4_Formation_03[] = {
    { .actor = &TTYD64_imp_25_BombshellBlaster_25_BombshellBlaster,
      .home = { .vec = &b_area_kpa4_blaster_pos_1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOMBSHELLBLASTER },
    { .actor = &TTYD64_imp_25_BombshellBlaster_25_BombshellBlaster,
      .home = { .vec = &b_area_kpa4_blaster_pos_2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOMBSHELLBLASTER },
    { .actor = &TTYD64_imp_25_Koopatrol_25_Koopatrol,
      .home = { .vec = &b_area_kpa4_pos_3 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

s32 TTYD64_imp_25_Koopatrol_IdleAnimations_8022813C_12[] = {
    1,  0x590003, 7, 0x590000, 6, 0x590011, 9, 0x590003, 8, 0x590000,
    11, 0x590003, 5, 0x590000, 4, 0x590013, 3, 0x590013, 0,
};

s32 TTYD64_imp_25_Magikoopa_IdleAnimations_8021EA20_25[] = {
    1,  0x560001, 7, 0x560000, 6, 0x560008, 9, 0x560001, 8, 0x560000,
    11, 0x560001, 5, 0x560000, 4, 0x560007, 3, 0x560007, 0,
};

s32 TTYD64_imp_25_Koopatrol_IdleAnimations_802280F0_12[] = {
    1,  0x590001, 7, 0x590000, 6, 0x590011, 9, 0x590001, 8, 0x590000,
    11, 0x590001, 5, 0x590000, 4, 0x590013, 3, 0x590013, 0,
};

s32 TTYD64_imp_25_Koopatrol_IdleAnimations_80228188_12[] = {
    1,  0x59000F, 7, 0x590010, 6, 0x590012, 9, 0x59000F, 8, 0x590010,
    11, 0x59000F, 5, 0x590010, 4, 0x590014, 3, 0x590014, 0,
};

s32 TTYD64_imp_25_Koopatrol_IdleAnimations_802281D4_12[] = {
    1,  0x590006, 7, 0x590006, 6, 0x590006, 9, 0x590006, 8, 0x590006,
    11, 0x590006, 5, 0x590006, 4, 0x590006, 3, 0x590006, 0,
};

s32 TTYD64_imp_25_Magikoopa_IdleAnimations_8021EA6C_25[] = {
    1,  0x570001, 7, 0x570000, 6, 0x570008, 9, 0x570001, 8, 0x570000,
    11, 0x570001, 5, 0x570000, 4, 0x570007, 3, 0x570007, 0,
};

FormationRow TTYD64_kpa4_Formation_00[] = {
    { .actor = &TTYD64_imp_25_BombshellBill_25_BombshellBill,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_25_BombshellBill_25_BombshellBill,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kpa4_Formation_02[] = {
    { .actor = &TTYD64_imp_25_BombshellBlaster_25_BombshellBlaster,
      .home = { .vec = &b_area_kpa4_blaster_pos_1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOMBSHELLBLASTER },
    { .actor = &TTYD64_imp_25_BombshellBlaster_25_BombshellBlaster,
      .home = { .vec = &b_area_kpa4_blaster_pos_2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOMBSHELLBLASTER },
};

ActorBlueprint TTYD64_imp_25_BombshellBill_25_BombshellBill = {
    .flags = 0x200,
    .maxHP = 3,
    .type = 0x4A,
    .level = 24,
    .partCount = 1,
    .partsData = TTYD64_imp_25_BombshellBill_PartsTable_80218EC8_25,
    .initScript = &TTYD64_imp_25_BombshellBill_Script_Init_80218F38_25,
    .statusTable = b_area_kpa4_bombshell_bill_StatusTable,
    .escapeChance = 40,
    .airLiftChance = 100,
    .hurricaneChance = 95,
    .spookChance = 0,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 28, 22 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_25_Koopatrol_25_Koopatrol = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x4C,
    .level = 25,
    .partCount = 1,
    .partsData = TTYD64_imp_25_Koopatrol_PartsTable_8022839C_12,
    .initScript = &TTYD64_imp_25_Koopatrol_Script_Init_802283E8_12,
    .statusTable = TTYD64_imp_25_Koopatrol_StatusTable_80228254_12,
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

ActorBlueprint TTYD64_imp_25_Magikoopa_25_Magikoopa = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x4D,
    .level = 26,
    .partCount = 1,
    .partsData = TTYD64_imp_25_Magikoopa_PartsTable_8021E940_25,
    .initScript = &TTYD64_imp_25_Magikoopa_Script_Init_8021F610_25,
    .statusTable = b_area_kpa4_magikoopa_StatusTable,
    .escapeChance = 40,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 36, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 32 },
};

ActorBlueprint TTYD64_imp_25_Magikoopa_FlyingMagiclone_25 = {
    .flags = 0x200200,
    .maxHP = 7,
    .type = 0x50,
    .level = 26,
    .partCount = 1,
    .partsData = TTYD64_imp_25_Magikoopa_PartsTable_80222B58_25,
    .initScript = &b_area_kpa4_magikoopa_EVS_FlyingClone_Init,
    .statusTable = b_area_kpa4_magikoopa_FlyingCloneStatusTable,
    .escapeChance = 40,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 2,
    .size = { 48, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -25, 20 },
    .statusTextOffset = { 1, 34 },
};

ActorBlueprint TTYD64_imp_25_BombshellBlaster_BombshellBill_25 = {
    .flags = 0x200,
    .maxHP = 3,
    .type = 0x4A,
    .level = 24,
    .partCount = 1,
    .partsData = TTYD64_imp_25_BombshellBill_PartsTable_80218EC8_25,
    .initScript = &TTYD64_imp_25_BombshellBill_Script_Init_80218F38_25,
    .statusTable = b_area_kpa4_bombshell_bill_StatusTable,
    .escapeChance = 40,
    .airLiftChance = 100,
    .hurricaneChance = 95,
    .spookChance = 0,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 28, 22 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_25_BombshellBlaster_25_BombshellBlaster = {
    .flags = 0x0,
    .maxHP = 10,
    .type = 0x49,
    .level = 27,
    .partCount = 1,
    .partsData = TTYD64_imp_25_BombshellBlaster_PartsTable_80218708_25,
    .initScript = &TTYD64_imp_25_BombshellBlaster_Script_Init_80218778_25,
    .statusTable = b_area_kpa4_bombshell_blaster_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 15,
    .hurricaneChance = 10,
    .spookChance = 0,
    .upAndAwayChance = 95,
    .spinSmashReq = 4,
    .powerBounceChance = 100,
    .coinReward = 2,
    .size = { 55, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -24, 20 },
    .statusTextOffset = { 5, 25 },
};

ActorBlueprint TTYD64_imp_25_Magikoopa_Magiclone_25 = {
    .flags = 0x200000,
    .maxHP = 7,
    .type = 0x4F,
    .level = 26,
    .partCount = 1,
    .partsData = TTYD64_imp_25_Magikoopa_PartsTable_80222B34_25,
    .initScript = &b_area_kpa4_magikoopa_EVS_Clone_Init,
    .statusTable = b_area_kpa4_magikoopa_CloneStatusTable,
    .escapeChance = 40,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 36, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 32 },
};

ActorBlueprint TTYD64_imp_25_Koopatrol_Koopatrol_12 = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x4C,
    .level = 25,
    .partCount = 1,
    .partsData = TTYD64_imp_25_Koopatrol_PartsTable_8022839C_12,
    .initScript = &TTYD64_imp_25_Koopatrol_Script_Init_802283E8_12,
    .statusTable = TTYD64_imp_25_Koopatrol_StatusTable_80228254_12,
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

s32 TTYD64_imp_25_BombshellBlaster_IdleAnimations_80218754_25[] = {
    1, 0x2E0101, 7, 0x2E0100, 8, 0x2E0100, 5, 0x2E0100, 0,
};

ActorPartBlueprint TTYD64_imp_25_Magikoopa_PartsTable_8021E940_25[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_25_Magikoopa_IdleAnimations_8021EA20_25,
        .defenseTable = TTYD64_imp_25_Magikoopa_DefenseTable_8021E7D0_25,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_25_Magikoopa_PartsTable_80222B34_25[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_25_Magikoopa_IdleAnimations_8021EA20_25,
        .defenseTable = TTYD64_imp_25_Magikoopa_DefenseTable_802229C4_25,
        .eventFlags = 0x20,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_25_Magikoopa_PartsTable_80222B58_25[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -10, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_25_Magikoopa_IdleAnimations_8021EA6C_25,
        .defenseTable = TTYD64_imp_25_Magikoopa_DefenseTable_802229D0_25,
        .eventFlags = 0x20,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_25_BombshellBill_PartsTable_80218EC8_25[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 16 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_25_BombshellBill_IdleAnimations_80218F14_25,
        .defenseTable = TTYD64_imp_25_BombshellBill_DefenseTable_80218E10_25,
        .eventFlags = 0x400,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -6 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_25_BombshellBlaster_PartsTable_80218708_25[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -6, 29 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_25_BombshellBlaster_IdleAnimations_80218754_25,
        .defenseTable = b_area_kpa4_bombshell_blaster_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -9 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_25_Koopatrol_PartsTable_8022839C_12[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_25_Koopatrol_IdleAnimations_802280F0_12,
        .defenseTable = b_area_kpa4_koopatrol_DefenseTable,
        .eventFlags = 0x1010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -12 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_imp_25_BombshellBill_IdleAnimations_80218F14_25[] = {
    1, 0x2D0101, 7, 0x2D0100, 8, 0x2D0100, 5, 0x2D0100, 0,
};

FormationRow TTYD64_imp_25_Magikoopa_SpecialFormation_80222BF4_25[] = {
    { .actor = &TTYD64_imp_25_Magikoopa_FlyingMagiclone_25,
      .home = { .vec = &b_area_kpa4_magikoopa_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_25_Magikoopa_SpecialFormation_80222BD8_25[] = {
    { .actor = &TTYD64_imp_25_Magikoopa_Magiclone_25,
      .home = { .vec = &b_area_kpa4_magikoopa_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_25_Koopatrol_SpecialFormation_8022BBC8_12[] = {
    { .actor = &TTYD64_imp_25_Koopatrol_Koopatrol_12,
      .home = { .vec = &b_area_kpa4_koopatrol_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_25_BombshellBlaster_SpecialFormation_80218DF4_25[] = {
    { .actor = &TTYD64_imp_25_BombshellBlaster_BombshellBill_25,
      .home = { .vec = &b_area_kpa4_bombshell_blaster_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

s32 TTYD64_imp_25_BombshellBill_DefenseTable_80218E10_25[] = {
    1,
    2,
    0,
};

s32 TTYD64_imp_25_Koopatrol_IdleAnimations_Koopatrol_Hide_12[] = {
    1,
    0x590005,
    0,
};

s32 TTYD64_imp_25_Magikoopa_DefenseTable_802229D0_25[] = {
    1,
    2,
    0,
};

s32 TTYD64_imp_25_Magikoopa_DefenseTable_802229C4_25[] = {
    1,
    2,
    0,
};

s32 TTYD64_imp_25_Magikoopa_DefenseTable_8021E7D0_25[] = {
    1,
    2,
    0,
};

void TTYD64_InstallBattles_kpa4(void) {
    Mod_SetBattleList("TTYD64", 0x25, TTYD64_kpa4_FormationTable);
    Mod_SetStageList("TTYD64", 0x25, TTYD64_kpa4_StageTable);
}
