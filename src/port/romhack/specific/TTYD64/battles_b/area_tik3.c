#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_drop_tables.h"
#include "../include/ttyd64_rawmem.h"
#include "../include/ttyd64_symbols.h"
#include "battles_b.h"
#include "battles_b_imports.h"

API_CALLABLE(action_command_stop_leech_init);
API_CALLABLE(action_command_stop_leech_start);
API_CALLABLE(b_area_tik3_swooper_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_tik3_swoopula_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_tik3_swoopula_SpawnDrainHealthContinueFX);
API_CALLABLE(b_area_tik3_swoopula_SpawnDrainHealthStartFX);
extern s32 b_area_tik3_swooper_DefenseTable[];
extern EvtScript b_area_tik3_swooper_EVS_Idle;
extern s32 b_area_tik3_swooper_StatusTable[];
extern s32 b_area_tik3_swoopula_DefenseTable[];
extern EvtScript b_area_tik3_swoopula_EVS_Idle;
extern s32 b_area_tik3_swoopula_StatusTable[];
extern Stage b_area_tik3_tik_01;
extern Stage b_area_tik3_tik_02;
extern Stage b_area_tik3_tik_03;
extern Stage b_area_tik3_tik_04;
extern EvtScript b_area_tik3_tik_05_EVS_PostBattle;
extern s32 b_area_tik3_tik_05_ForegroundModels[];
extern EvtScript TTYD64_imp_1C_Swoopula_Script_8021CB94_1C;
extern EvtScript TTYD64_imp_1C_Swoopula_Script_TakeTurn_8021E7B4_1C;
extern EvtScript TTYD64_imp_1C_Swooper_Script_HandleEvent_8021A404_1C;
extern EvtScript TTYD64_imp_1C_Swoopula_Script_HandleEvent_8021C414_1C;
extern EvtScript TTYD64_imp_1C_Swooper_Script_8021AB84_1C;
extern EvtScript TTYD64_imp_1C_Swooper_Script_TakeTurn_8021B274_1C;
extern EvtScript TTYD64_imp_1C_Swooper_Script_80219C20_1C;
extern EvtScript TTYD64_imp_1C_Swoopula_Script_8021BC30_1C;
extern EvtScript TTYD64_imp_1C_Swooper_Script_8021A0A4_1C;
extern EvtScript TTYD64_imp_1C_Swoopula_Script_8021C0B4_1C;
extern EvtScript TTYD64_tik3_Script_BeforeBattle_80222F2C;
extern EvtScript TTYD64_imp_1C_Swooper_Script_80219A60_1C;
extern EvtScript TTYD64_imp_1C_Swoopula_Script_8021BA70_1C;
extern EvtScript TTYD64_tik3_Script_80222E90;
extern EvtScript TTYD64_imp_1C_Swoopula_Script_Init_8021B9FC_1C;
extern Battle TTYD64_tik3_FormationTable[];
extern EvtScript TTYD64_imp_1C_Swooper_Script_Init_802199EC_1C;
extern FormationRow TTYD64_tik3_Formation_01[];
extern FormationRow TTYD64_tik3_Formation_03[];
extern s32 TTYD64_imp_1C_Swooper_IdleAnimations_80219954_1C[];
extern s32 TTYD64_imp_1C_Swooper_IdleAnimations_802199A0_1C[];
extern s32 TTYD64_imp_1C_Swoopula_IdleAnimations_8021B964_1C[];
extern s32 TTYD64_imp_1C_Swoopula_IdleAnimations_8021B9B0_1C[];
extern FormationRow TTYD64_tik3_Formation_00[];
extern FormationRow TTYD64_tik3_Formation_02[];
extern StageListRow TTYD64_tik3_StageTable[];
extern ActorBlueprint TTYD64_imp_1C_Swoopula_1C_Swoopula;
extern ActorBlueprint TTYD64_imp_1C_Swooper_1C_Swooper;
extern Stage TTYD64_tik3_Stage_802231A8;
extern ActorPartBlueprint TTYD64_imp_1C_Swooper_PartsTable_80219908_1C[];
extern ActorPartBlueprint TTYD64_imp_1C_Swoopula_PartsTable_8021B918_1C[];
API_CALLABLE(TTYD64_tik3_Function_80219540);
API_CALLABLE(TTYD64_tik3_Function_80219664);

API_CALLABLE(TTYD64_tik3_Function_80219540) {
    script->varTable[9] += script->varTable[1];
    if (script->varTable[9] < 0) {
        script->varTable[9] += 0x20000;
    } else if (script->varTable[9] > 0x20000) {
        script->varTable[9] -= 0x20000;
    }

    script->varTable[10] += script->varTable[2];
    if (script->varTable[10] < 0) {
        script->varTable[10] += 0x20000;
    } else if (script->varTable[10] > 0x20000) {
        script->varTable[10] -= 0x20000;
    }

    script->varTable[11] += script->varTable[3];
    if (script->varTable[11] < 0) {
        script->varTable[11] += 0x20000;
    } else if (script->varTable[11] > 0x20000) {
        script->varTable[11] -= 0x20000;
    }

    script->varTable[12] += script->varTable[4];
    if (script->varTable[12] < 0) {
        script->varTable[12] += 0x20000;
    } else if (script->varTable[12] > 0x20000) {
        script->varTable[12] -= 0x20000;
    }

    set_main_pan_u(script->varTable[0], script->varTable[9]);
    set_main_pan_v(script->varTable[0], script->varTable[10]);
    set_aux_pan_u(script->varTable[0], script->varTable[11]);
    set_aux_pan_v(script->varTable[0], script->varTable[12]);
    return ApiStatus_BLOCK;
}

API_CALLABLE(TTYD64_tik3_Function_80219664) {
    if (isInitialCall) {
        script->functionTemp[0] = 0;
        script->functionTemp[1] = 0;
        script->functionTemp[2] = 0;
        script->functionTemp[3] = 0;
    }

    if (script->functionTemp[0] == 0) {
        script->varTable[9] += script->varTable[1];
        if (script->varTable[9] < 0) {
            script->varTable[9] += 0x20000;
        } else if (script->varTable[9] > 0x20000) {
            script->varTable[9] -= 0x20000;
        }
    }

    if (script->functionTemp[1] == 0) {
        script->varTable[10] += script->varTable[2];
        if (script->varTable[10] < 0) {
            script->varTable[10] += 0x20000;
        } else if (script->varTable[10] > 0x20000) {
            script->varTable[10] -= 0x20000;
        }
    }

    if (script->functionTemp[2] == 0) {
        script->varTable[11] += script->varTable[3];
        if (script->varTable[11] < 0) {
            script->varTable[11] += 0x20000;
        } else if (script->varTable[11] > 0x20000) {
            script->varTable[11] -= 0x20000;
        }
    }

    if (script->functionTemp[3] == 0) {
        script->varTable[12] += script->varTable[4];
        if (script->varTable[12] < 0) {
            script->varTable[12] += 0x20000;
        } else if (script->varTable[12] > 0x20000) {
            script->varTable[12] -= 0x20000;
        }
    }

    set_main_pan_u(script->varTable[0], script->varTable[9]);
    set_main_pan_v(script->varTable[0], script->varTable[10]);
    set_aux_pan_u(script->varTable[0], script->varTable[11]);
    set_aux_pan_v(script->varTable[0], script->varTable[12]);

    script->functionTemp[0]++;
    script->functionTemp[1]++;
    script->functionTemp[2]++;
    script->functionTemp[3]++;

    if (script->functionTemp[0] >= script->varTable[5]) {
        script->functionTemp[0] = 0;
    }
    if (script->functionTemp[1] >= script->varTable[6]) {
        script->functionTemp[1] = 0;
    }
    if (script->functionTemp[2] >= script->varTable[7]) {
        script->functionTemp[2] = 0;
    }
    if (script->functionTemp[3] >= script->varTable[8]) {
        script->functionTemp[3] = 0;
    }

    return ApiStatus_BLOCK;
}

// clang-format off
EvtScript TTYD64_imp_1C_Swoopula_Script_8021CB94_1C = {
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
        Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Else
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
        Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
        Call(FlyToGoal, ACTOR_SELF, 0, -4, 0)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 2, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
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
            ExecWait(TTYD64_imp_1C_Swoopula_Script_8021BA70_1C)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -4, -8, -15)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    IfEq(LFlag0, 1)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 0, 32)
        Return
    EndIf
    Call(GetOwnerTarget, LVar1, 0)
    Call(GetStatusFlags, LVar1, LVar0)
    IfFlag(LVar0, 0x100000)
        Wait(10)
        Loop(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
            Wait(21)
            Loop(2)
                Call(PlaySoundAtActor, ACTOR_SELF, 992)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Wait(1)
            EndLoop
            Wait(5)
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
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 2, 32)
            Wait(30)
        EndLoop
    Else
        Call(ShowMessageBox, 49, 0x7FFF)
        Call(ShowActionHud, 1)
        Call(LoadActionCommand, 6)
        Call(action_command_stop_leech_init)
        Call(SetupMashMeter, 1, 30, 0, 0, 0, 0)
        Wait(10)
        Call(SetBattleFlagBits, 0x4000, 0)
        Call(action_command_stop_leech_start, 0, 0x7FFF, 3)
        Set(LVarD, 0)
        Loop(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
            Set(LFlag0, 0)
            Loop(21)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(GetOwnerTarget, LVar1, 0)
            Switch(LVar1)
                CaseEq(0)
                    Call(UseIdleAnimation, 0, 0)
                    Call(SetAnimation, 0, 0, 0x3000C)
                CaseEq(256)
                    Call(UseIdleAnimation, 256, 0)
                    Set(LVar0, 4)
                    Exec(TTYD64_SetPartnerAnimation_Battle)
            EndSwitch
            Loop(2)
                Call(PlaySoundAtActor, ACTOR_SELF, 992)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
            EndLoop
            IfEq(LFlag0, 1)
                BreakLoop
            EndIf
            Set(LFlag0, 0)
            Loop(5)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(PlaySoundAtActor, ACTOR_SELF, 992)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
            Set(LFlag0, 0)
            Loop(2)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.599609375), Float(1.599609375), Float(1.0))
            Set(LFlag0, 0)
            Loop(10)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Set(LFlag0, 0)
            Loop(2)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(GetOwnerTarget, LVar1, 0)
            Call(UseIdleAnimation, LVar1, 1)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0xA000000, 0, 0, 2, 32)
            Call(GetLastDamage, LVar1, LVar3)
            IfNe(LVar3, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8301)
                Call(PlaySoundAtActor, ACTOR_SELF, 532)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 15)
                Call(b_area_tik3_swoopula_SpawnDrainHealthStartFX, LVar0, LVar1, LVar2, LVar3)
                Thread
                    Wait(15)
                    Call(PlaySoundAtActor, ACTOR_SELF, 604)
                    Call(b_area_tik3_swoopula_SpawnDrainHealthContinueFX, LVar0, LVar1, LVar2, LVar3)
                EndThread
                Add(LVar0, 20)
                Add(LVar1, 20)
                Call(PlayEffect_impl, 64, 0, LVar0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0)
                Call(GetActorHP, ACTOR_SELF, LVar0)
                Add(LVar0, LVar3)
                Call(SetEnemyHP, ACTOR_SELF, LVar0)
            Else
                Add(LVarD, 1)
                IfGt(LVarD, 1)
                    Call(InterruptLeechActionCommand)
                    BreakLoop
                EndIf
            EndIf
            Call(GetOwnerTarget, LVar2, 0)
            IfEq(LVar2, 0)
                Call(GetPlayerHP, LVar1)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar1)
            EndIf
            IfEq(LVar1, 0)
                Call(InterruptLeechActionCommand)
                BreakLoop
            EndIf
            Set(LFlag0, 0)
            Loop(30)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                BreakLoop
            EndIf
        EndLoop
        Call(InterruptLeechActionCommand)
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    Wait(10)
    Call(YieldTurn)
    ExecWait(TTYD64_imp_1C_Swoopula_Script_8021BA70_1C)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1C_Swoopula_Script_TakeTurn_8021E7B4_1C = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_1C_Swoopula_Script_8021CB94_1C)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 24)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 2, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(AddGoalPos, ACTOR_SELF, -50, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
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
            ExecWait(TTYD64_imp_1C_Swoopula_Script_8021BA70_1C)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -4, -8, -15)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
    Call(FlyToGoal, ACTOR_SELF, 0, -40, 0)
    IfEq(LFlag0, 1)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 0, 32)
        Return
    EndIf
    Call(GetOwnerTarget, LVar1, 0)
    Call(GetStatusFlags, LVar1, LVar0)
    IfFlag(LVar0, 0x100000)
        Wait(10)
        Loop(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
            Wait(21)
            Loop(2)
                Call(PlaySoundAtActor, ACTOR_SELF, 992)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Wait(1)
            EndLoop
            Wait(5)
            Call(PlaySoundAtActor, ACTOR_SELF, 992)
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
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 2, 32)
            Wait(30)
        EndLoop
    Else
        Call(ShowMessageBox, 49, 0x7FFF)
        Call(ShowActionHud, 1)
        Call(LoadActionCommand, 6)
        Call(action_command_stop_leech_init)
        Call(SetupMashMeter, 1, 30, 0, 0, 0, 0)
        Wait(10)
        Call(SetBattleFlagBits, 0x4000, 0)
        Call(action_command_stop_leech_start, 0, 0x7FFF, 3)
        Set(LVarD, 0)
        Loop(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
            Set(LFlag0, 0)
            Loop(21)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(GetOwnerTarget, LVar1, 0)
            Switch(LVar1)
                CaseEq(0)
                    Call(UseIdleAnimation, 0, 0)
                    Call(SetAnimation, 0, 0, 0x3000C)
                CaseEq(256)
                    Call(UseIdleAnimation, 256, 0)
                    Set(LVar0, 4)
                    Exec(TTYD64_SetPartnerAnimation_Battle)
            EndSwitch
            Call(PlaySoundAtActor, ACTOR_SELF, 992)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
            Set(LFlag0, 0)
            Loop(2)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.599609375), Float(1.599609375), Float(1.0))
            Set(LFlag0, 0)
            Loop(10)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Set(LFlag0, 0)
            Loop(2)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(GetOwnerTarget, LVar1, 0)
            Call(UseIdleAnimation, LVar1, 1)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0xA000000, 0, 0, 2, 32)
            Call(GetLastDamage, LVar1, LVar3)
            IfNe(LVar3, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8301)
                Call(PlaySoundAtActor, ACTOR_SELF, 532)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 15)
                Call(b_area_tik3_swoopula_SpawnDrainHealthStartFX, LVar0, LVar1, LVar2, LVar3)
                Thread
                    Wait(15)
                    Call(PlaySoundAtActor, ACTOR_SELF, 604)
                    Call(b_area_tik3_swoopula_SpawnDrainHealthContinueFX, LVar0, LVar1, LVar2, LVar3)
                EndThread
                Add(LVar0, 20)
                Add(LVar1, 20)
                Call(PlayEffect_impl, 64, 0, LVar0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0)
                Call(GetActorHP, ACTOR_SELF, LVar0)
                Add(LVar0, LVar3)
                Call(SetEnemyHP, ACTOR_SELF, LVar0)
            Else
                Add(LVarD, 1)
                IfGt(LVarD, 1)
                    Call(InterruptLeechActionCommand)
                    BreakLoop
                EndIf
            EndIf
            Call(GetOwnerTarget, LVar2, 0)
            IfEq(LVar2, 0)
                Call(GetPlayerHP, LVar1)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar1)
            EndIf
            IfEq(LVar1, 0)
                Call(InterruptLeechActionCommand)
                BreakLoop
            EndIf
            Set(LFlag0, 0)
            Loop(35)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                BreakLoop
            EndIf
        EndLoop
        Call(InterruptLeechActionCommand)
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    Wait(10)
    Call(YieldTurn)
    ExecWait(TTYD64_imp_1C_Swoopula_Script_8021BA70_1C)
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
EvtScript TTYD64_imp_1C_Swooper_Script_HandleEvent_8021A404_1C = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_1C_Swooper_Script_80219C20_1C)
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
                ExecWait(TTYD64_imp_1C_Swooper_Script_8021A0A4_1C)
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
                ExecWait(TTYD64_imp_1C_Swooper_Script_8021A0A4_1C)
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
            ExecWait(TTYD64_imp_1C_Swooper_Script_80219A60_1C)
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
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1C_Swooper_IdleAnimations_802199A0_1C))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340002)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(TTYD64_imp_1C_Swooper_Script_80219A60_1C)
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
EvtScript TTYD64_imp_1C_Swoopula_Script_HandleEvent_8021C414_1C = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_1C_Swoopula_Script_8021BC30_1C)
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
                SetConst(LVar1, 0x340115)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34010E)
                ExecWait(Ref(EVS_Enemy_Hit))
            EndIf
        CaseEq(10)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340115)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34010E)
                ExecWait(Ref(EVS_Enemy_Hit))
                ExecWait(TTYD64_imp_1C_Swoopula_Script_8021C0B4_1C)
            EndIf
        CaseEq(14)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340117)
                SetConst(LVar2, 0x340118)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340111)
                SetConst(LVar2, 0x340112)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                ExecWait(TTYD64_imp_1C_Swoopula_Script_8021C0B4_1C)
            EndIf
        CaseEq(36)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340117)
                SetConst(LVar2, 0x340118)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340118)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340111)
                SetConst(LVar2, 0x340112)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340112)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(47)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_ShockHit_Impl))
            Call(UseBattleCamPreset, 2)
            ExecWait(TTYD64_imp_1C_Swoopula_Script_8021BA70_1C)
        CaseEq(38)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_ShockHit_Impl))
            Thread
                Wait(30)
                Call(UseBattleCamPreset, 2)
            EndThread
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x34010C)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340115)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340115)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34010E)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34010E)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(56)
            Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1C_Swoopula_IdleAnimations_8021B9B0_1C))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(TTYD64_imp_1C_Swoopula_Script_8021BA70_1C)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 1)
            Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, -24, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340102)
            SetConst(LVar2, 0x340115)
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
EvtScript TTYD64_imp_1C_Swooper_Script_8021AB84_1C = {
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
            ExecWait(TTYD64_imp_1C_Swooper_Script_80219A60_1C)
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
    ExecWait(TTYD64_imp_1C_Swooper_Script_80219A60_1C)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1C_Swooper_Script_TakeTurn_8021B274_1C = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_1C_Swooper_Script_8021AB84_1C)
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
            ExecWait(TTYD64_imp_1C_Swooper_Script_80219A60_1C)
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
    ExecWait(TTYD64_imp_1C_Swooper_Script_80219A60_1C)
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
EvtScript TTYD64_imp_1C_Swooper_Script_80219C20_1C = {
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
            ExecWait(TTYD64_imp_1C_Swooper_Script_80219A60_1C)
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
EvtScript TTYD64_imp_1C_Swoopula_Script_8021BC30_1C = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340117)
            SetConst(LVar2, 0x340118)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340117)
            SetConst(LVar2, 0x340118)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340118)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Call(UseBattleCamPreset, 2)
            ExecWait(TTYD64_imp_1C_Swoopula_Script_8021BA70_1C)
        CaseEq(38)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Thread
                Wait(30)
                Call(UseBattleCamPreset, 2)
            EndThread
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340102)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340102)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340102)
            SetConst(LVar2, 0x340115)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340102)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
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
EvtScript TTYD64_imp_1C_Swooper_Script_8021A0A4_1C = {
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
    Call(b_area_tik3_swooper_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1C_Swooper_IdleAnimations_802199A0_1C))
    Call(SetActorFlagBits, ACTOR_SELF, 512, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1C_Swoopula_Script_8021C0B4_1C = {
    Call(HideHealthBar, ACTOR_SELF)
    Call(GetLastDamage, ACTOR_SELF, LVar0)
    IfLe(LVar0, 0)
        Return
    EndIf
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
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
    Call(b_area_tik3_swoopula_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1C_Swoopula_IdleAnimations_8021B9B0_1C))
    Call(SetActorFlagBits, ACTOR_SELF, 512, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_tik3_Script_BeforeBattle_80222F2C = {
    Call(SetSpriteShading, -1)
    Call(SetCamBGColor, 1, 0, 0, 0)
    Call(SetTexPanner, 15, 1)
    Call(EnableTexPanning, 15, 1)
    Thread
        Set(LVar0, 1)
        Set(LVar1, 0)
        Set(LVar2, -2700)
        Set(LVar3, 0)
        Set(LVar4, -3000)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_tik3_Script_80222E90)
    EndThread
    Call(SetTexPanner, 16, 2)
    Call(EnableTexPanning, 16, 1)
    Thread
        Set(LVar0, 2)
        Set(LVar1, 50)
        Set(LVar2, -200)
        Set(LVar3, 110)
        Set(LVar4, -500)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_tik3_Script_80222E90)
    EndThread
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1C_Swooper_Script_80219A60_1C = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340002)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 0, -24, 0)
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 11)
            Call(SetActorFlagBits, ACTOR_SELF, 2048, 1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1C_Swooper_IdleAnimations_80219954_1C))
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

// clang-format off
EvtScript TTYD64_imp_1C_Swoopula_Script_8021BA70_1C = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 0, -24, 0)
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 11)
            Call(SetActorFlagBits, ACTOR_SELF, 2048, 1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1C_Swoopula_IdleAnimations_8021B964_1C))
            Call(SetAnimation, ACTOR_SELF, 1, 0x34010C)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 24)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 11)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_tik3_Script_80222E90 = {
    SetGroup(0)
    IfEq(LVar5, 1)
        IfEq(LVar6, 1)
            IfEq(LVar7, 1)
                IfEq(LVar8, 1)
                    Call(TTYD64_tik3_Function_80219540)
                    Return
                EndIf
            EndIf
        EndIf
    EndIf
    Call(TTYD64_tik3_Function_80219664)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1C_Swoopula_Script_Init_8021B9FC_1C = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1C_Swoopula_Script_TakeTurn_8021E7B4_1C))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_tik3_swoopula_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1C_Swoopula_Script_HandleEvent_8021C414_1C))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

Battle TTYD64_tik3_FormationTable[] = {
    { .name = "\320\265\320\265x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_tik3_Formation_00,
      .stage = &b_area_tik3_tik_01,
      .onBattleStart = NULL },
    { .name = "\320\265\320\265x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tik3_Formation_01,
      .stage = &b_area_tik3_tik_01,
      .onBattleStart = NULL },
    { .name = "\320\265\320\265\301\345\353\353x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_tik3_Formation_02,
      .stage = &b_area_tik3_tik_01,
      .onBattleStart = NULL },
    { .name = "\320\265\320\265\301\345\353\353x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tik3_Formation_03,
      .stage = &b_area_tik3_tik_01,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_imp_1C_Swooper_Script_Init_802199EC_1C = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1C_Swooper_Script_TakeTurn_8021B274_1C))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_tik3_swooper_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1C_Swooper_Script_HandleEvent_8021A404_1C))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_tik3_Formation_01[] = {
    { .actor = &TTYD64_imp_1C_Swooper_1C_Swooper,
      .home = { .index = 12 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
    { .actor = &TTYD64_imp_1C_Swooper_1C_Swooper,
      .home = { .index = 13 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
    { .actor = &TTYD64_imp_1C_Swooper_1C_Swooper,
      .home = { .index = 14 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
};

FormationRow TTYD64_tik3_Formation_03[] = {
    { .actor = &TTYD64_imp_1C_Swoopula_1C_Swoopula,
      .home = { .index = 12 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
    { .actor = &TTYD64_imp_1C_Swoopula_1C_Swoopula,
      .home = { .index = 13 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
    { .actor = &TTYD64_imp_1C_Swoopula_1C_Swoopula,
      .home = { .index = 14 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
};

s32 TTYD64_imp_1C_Swooper_IdleAnimations_80219954_1C[] = {
    1,  0x34000C, 7, 0x34000B, 6, 0x34000F, 9, 0x34000C, 8, 0x34000B,
    11, 0x34000C, 5, 0x34000B, 4, 0x340010, 3, 0x340010, 0,
};

s32 TTYD64_imp_1C_Swooper_IdleAnimations_802199A0_1C[] = {
    1,  0x340002, 7, 0x340001, 6, 0x340013, 9, 0x340002, 8, 0x340001,
    11, 0x340002, 5, 0x340001, 4, 0x340014, 3, 0x340014, 0,
};

s32 TTYD64_imp_1C_Swoopula_IdleAnimations_8021B964_1C[] = {
    1,  0x34010C, 7, 0x34010B, 6, 0x34010F, 9, 0x34010C, 8, 0x34010B,
    11, 0x34010C, 5, 0x34010B, 4, 0x340110, 3, 0x340110, 0,
};

s32 TTYD64_imp_1C_Swoopula_IdleAnimations_8021B9B0_1C[] = {
    1,  0x340102, 7, 0x340101, 6, 0x340113, 9, 0x340102, 8, 0x340101,
    11, 0x340102, 5, 0x340101, 4, 0x340114, 3, 0x340114, 0,
};

FormationRow TTYD64_tik3_Formation_00[] = {
    { .actor = &TTYD64_imp_1C_Swooper_1C_Swooper,
      .home = { .index = 13 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
    { .actor = &TTYD64_imp_1C_Swooper_1C_Swooper,
      .home = { .index = 14 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPER },
};

FormationRow TTYD64_tik3_Formation_02[] = {
    { .actor = &TTYD64_imp_1C_Swoopula_1C_Swoopula,
      .home = { .index = 13 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
    { .actor = &TTYD64_imp_1C_Swoopula_1C_Swoopula,
      .home = { .index = 14 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
};

StageListRow TTYD64_tik3_StageTable[] = {
    { .name = "tik_01", .stage = &b_area_tik3_tik_01 },         { .name = "tik_02", .stage = &b_area_tik3_tik_02 },
    { .name = "tik_03", .stage = &b_area_tik3_tik_03 },         { .name = "tik_04", .stage = &b_area_tik3_tik_04 },
    { .name = "tik_05", .stage = &TTYD64_tik3_Stage_802231A8 }, {},
};

ActorBlueprint TTYD64_imp_1C_Swoopula_1C_Swoopula = {
    .flags = 0x800,
    .maxHP = 8,
    .type = 0x3A,
    .level = 22,
    .partCount = 1,
    .partsData = TTYD64_imp_1C_Swoopula_PartsTable_8021B918_1C,
    .initScript = &TTYD64_imp_1C_Swoopula_Script_Init_8021B9FC_1C,
    .statusTable = b_area_tik3_swoopula_StatusTable,
    .escapeChance = 30,
    .airLiftChance = 95,
    .hurricaneChance = 95,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 1,
    .size = { 31, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, -20 },
    .statusTextOffset = { 10, -20 },
};

ActorBlueprint TTYD64_imp_1C_Swooper_1C_Swooper = {
    .flags = 0x800,
    .maxHP = 4,
    .type = 0x16,
    .level = 10,
    .partCount = 1,
    .partsData = TTYD64_imp_1C_Swooper_PartsTable_80219908_1C,
    .initScript = &TTYD64_imp_1C_Swooper_Script_Init_802199EC_1C,
    .statusTable = b_area_tik3_swooper_StatusTable,
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

Stage TTYD64_tik3_Stage_802231A8 = {
    .texture = "tik_tex",
    .shape = "tik_bt05_shape",
    .hit = "tik_bt05_hit",
    .preBattle = &TTYD64_tik3_Script_BeforeBattle_80222F2C,
    .postBattle = &b_area_tik3_tik_05_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = b_area_tik3_tik_05_ForegroundModels,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorPartBlueprint TTYD64_imp_1C_Swooper_PartsTable_80219908_1C[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 29 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1C_Swooper_IdleAnimations_80219954_1C,
        .defenseTable = b_area_tik3_swooper_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 1, 15 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1C_Swoopula_PartsTable_8021B918_1C[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 29 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1C_Swoopula_IdleAnimations_8021B964_1C,
        .defenseTable = b_area_tik3_swoopula_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 1, 15 },
        .overrideNameMsg = 0,
    },
};

void TTYD64_InstallBattles_tik3(void) {
    Mod_SetBattleList("TTYD64", 0x1C, TTYD64_tik3_FormationTable);
    Mod_SetStageList("TTYD64", 0x1C, TTYD64_tik3_StageTable);
}
