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

API_CALLABLE(action_command_stop_leech_init);
API_CALLABLE(action_command_stop_leech_start);
API_CALLABLE(b_area_tik2_blooper_SpitInk);
API_CALLABLE(b_area_tik2_blooper_baby_SpawnDrainHealthContinueFX);
API_CALLABLE(b_area_tik2_blooper_baby_SpawnDrainHealthStartFX);
API_CALLABLE(b_area_tik2_blooper_baby_StartRumbleWithParams);
API_CALLABLE(b_area_tik2_electro_blooper_FadeBackgroundDarken);
API_CALLABLE(b_area_tik2_electro_blooper_FadeBackgroundLighten);
API_CALLABLE(b_area_tik2_electro_blooper_SpitInk);
API_CALLABLE(b_area_tik2_electro_blooper_StartRumbleWithParams);
API_CALLABLE(b_area_tik2_electro_blooper_UpdateStaticEffect);
API_CALLABLE(b_area_tik2_super_blooper_FadeBackgroundDarken);
API_CALLABLE(b_area_tik2_super_blooper_FadeBackgroundLighten);
API_CALLABLE(b_area_tik2_super_blooper_SpitInk);
API_CALLABLE(b_area_tik2_super_blooper_StartRumbleWithParams);
extern Vec3i b_area_tik2_BlooperPos;
extern ActorPartBlueprint b_area_tik2_blooper_ActorParts[];
extern s32 b_area_tik2_blooper_AscendAnims[];
extern s32 b_area_tik2_blooper_DescendAnims[];
extern EvtScript b_area_tik2_blooper_EVS_Death;
extern s32 b_area_tik2_blooper_StatusTable[];
extern ActorPartBlueprint b_area_tik2_blooper_baby_ActorParts[];
extern s32 b_area_tik2_blooper_baby_AscendAnims[];
extern s32 b_area_tik2_blooper_baby_DescendAnims[];
extern EvtScript b_area_tik2_blooper_baby_EVS_Death;
extern s32 b_area_tik2_blooper_baby_StatusTable[];
extern ActorPartBlueprint b_area_tik2_electro_blooper_ActorParts[];
extern s32 b_area_tik2_electro_blooper_AscendAnims[];
extern s32 b_area_tik2_electro_blooper_ChargedStatusTable[];
extern s32 b_area_tik2_electro_blooper_DescendAnims[];
extern EvtScript b_area_tik2_electro_blooper_EVS_Death;
extern EvtScript b_area_tik2_electro_blooper_EVS_Discharge;
extern s32 b_area_tik2_electro_blooper_StatusTable[];
extern ActorPartBlueprint b_area_tik2_super_blooper_ActorParts[];
extern s32 b_area_tik2_super_blooper_AscendAnims[];
extern s32 b_area_tik2_super_blooper_DescendAnims[];
extern EvtScript b_area_tik2_super_blooper_EVS_Death;
extern EvtScript b_area_tik2_super_blooper_EVS_Enrage;
extern EvtScript b_area_tik2_super_blooper_EVS_LoseRage;
extern s32 b_area_tik2_super_blooper_StatusTable[];
extern Vec3i b_area_tik2_super_blooper_SummonPos;
extern Stage b_area_tik2_tik_01;
extern Stage b_area_tik2_tik_02;
extern Stage b_area_tik2_tik_03;
extern Stage b_area_tik2_tik_04;
extern EvtScript b_area_tik2_tik_05_EVS_PostBattle;
extern s32 b_area_tik2_tik_05_ForegroundModels[];
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_TakeTurn_8022319C_1B;
extern EvtScript TTYD64_imp_1B_Blooper_Script_SprayInk_1B;
extern EvtScript TTYD64_imp_1B_ElectroBlooper_Script_SprayInk_ElectroBlooper_1B;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_SprayInk_SuperBlooper_1B;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_EnragedTackle_1B;
extern EvtScript TTYD64_imp_1B_ElectroBlooper_Script_ElectroTackle_1B;
extern EvtScript TTYD64_imp_1B_Blooper_Script_Tackle_1B;
extern EvtScript TTYD64_imp_1B_ElectroBlooper_Script_Tackle_ElectroBlooper_1B;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_Tackle_SuperBlooper_1B;
extern EvtScript TTYD64_imp_1B_ElectroBlooper_Script_HandleEvent_8021CEE8_1B;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_HandleEvent_8021FC18_1B;
extern EvtScript TTYD64_imp_1B_Blooper_Script_8021A120_1B;
extern EvtScript TTYD64_imp_1B_ElectroBlooper_Script_8021C070_1B;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_8021EF60_1B;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_80221F40_1B;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_HandleEvent_80222CF8_1B;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_SpawnBabies_1B;
extern EvtScript TTYD64_imp_1B_Blooper_Script_HandleEvent_8021ACFC_1B;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_Idle_8021F7E0_1B;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_Idle_802228C0_1B;
extern EvtScript TTYD64_imp_1B_ElectroBlooper_Script_Idle_8021CAB0_1B;
extern EvtScript TTYD64_imp_1B_Blooper_Script_Idle_8021A8C4_1B;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_TakeTurn_SuperBlooper_1B;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_Init_80222650_1B;
extern EvtScript TTYD64_tik2_Script_BeforeBattle_8022778C;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_Enrage_1B;
extern EvtScript TTYD64_imp_1B_ElectroBlooper_Script_Electrify_1B;
extern EvtScript TTYD64_imp_1B_ElectroBlooper_Script_8021EC88_1B;
extern EvtScript TTYD64_imp_1B_ElectroBlooper_Script_UpdateElectictyPosition_1B;
extern EvtScript TTYD64_imp_1B_ElectroBlooper_Script_TakeTurn_8021D40C_1B;
extern EvtScript TTYD64_imp_1B_ElectroBlooper_Script_Init_8021C82C_1B;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_Init_8021F71C_1B;
extern EvtScript TTYD64_imp_1B_Blooper_Script_TakeTurn_Blooper_1B;
extern EvtScript TTYD64_tik2_Script_802276F0;
extern EvtScript TTYD64_imp_1B_Blooper_Script_Init_8021A830_1B;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_8022241C_1B;
extern EvtScript TTYD64_imp_1B_SuperBlooper_Script_8021F43C_1B;
extern EvtScript TTYD64_imp_1B_Blooper_Script_8021A5FC_1B;
extern EvtScript TTYD64_imp_1B_ElectroBlooper_Script_8021C54C_1B;
extern Battle TTYD64_tik2_FormationTable[];
extern StageListRow TTYD64_tik2_StageTable[];
extern ActorBlueprint TTYD64_imp_1B_ElectroBlooper_1B_ElectroBlooper;
extern ActorBlueprint TTYD64_imp_1B_Blooper_1B_Blooper;
extern Stage TTYD64_tik2_Stage_80227A08;
extern ActorBlueprint TTYD64_imp_1B_SuperBlooper_BlooperBaby_1B;
extern ActorBlueprint TTYD64_imp_1B_SuperBlooper_1B_SuperBlooper;
extern FormationRow TTYD64_imp_1B_SuperBlooper_SpecialFormation_80221EFC_1B[];
extern FormationRow TTYD64_imp_1B_SuperBlooper_SpecialFormation_80221F18_1B[];
extern FormationRow TTYD64_tik2_Formation_00[];
extern FormationRow TTYD64_tik2_Formation_01[];
extern FormationRow TTYD64_tik2_Formation_02[];
API_CALLABLE(TTYD64_tik2_Function_80219E10);
API_CALLABLE(TTYD64_tik2_Function_80219F34);

API_CALLABLE(TTYD64_tik2_Function_80219E10) {
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

API_CALLABLE(TTYD64_tik2_Function_80219F34) {
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
EvtScript TTYD64_imp_1B_SuperBlooper_Script_TakeTurn_8022319C_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 100)
    Set(LVar3, 12)
    ExecWait(TTYD64_imp_1B_SuperBlooper_Script_80221F40_1B)
    Thread
        Wait(2)
        Call(PlaySoundAtActor, ACTOR_SELF, 769)
    EndThread
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0, 0, 1, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x510002)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            IfEq(LVarF, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8022241C_1B)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseOrEq(7)
        CaseOrEq(8)
            Call(SetAnimation, ACTOR_SELF, 1, 0x510002)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            IfEq(LVarF, 7)
                Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0, 0, 0, 64)
            EndIf
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8022241C_1B)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Add(LVar1, 50)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 325)
    Call(MoveBattleCamOver, 30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x510002)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 10)
    Sub(LVar2, 5)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x510008)
    Call(ShowMessageBox, 49, 0x7FFF)
    Call(ShowActionHud, 1)
    Call(LoadActionCommand, 6)
    Call(action_command_stop_leech_init)
    Call(SetupMashMeter, 1, 15, 0, 0, 0, 0)
    Wait(10)
    Call(SetBattleFlagBits, 0x4000, 0)
    Call(action_command_stop_leech_start, 0, 0x7FFF, 3)
    Loop(5)
        Call(GetOwnerTarget, LVar4, 0)
        Switch(LVar4)
            CaseEq(0)
                Call(UseIdleAnimation, 0, 0)
                Call(SetAnimation, 0, 0, 0x3000C)
            CaseEq(256)
                Call(UseIdleAnimation, 256, 0)
                Set(LVar0, 4)
                Exec(TTYD64_SetPartnerAnimation_Battle)
        EndSwitch
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
            IfEq(LVar4, 0)
                Call(DispatchEventPlayer, 66)
            Else
                Call(DispatchEvent, 256, 66)
            EndIf
            Call(UseIdleAnimation, LVar4, 1)
            BreakLoop
        EndIf
        Call(PlaySoundAtActor, ACTOR_SELF, 992)
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
            IfEq(LVar4, 0)
                Call(DispatchEventPlayer, 66)
            Else
                Call(DispatchEvent, 256, 66)
            EndIf
            Call(UseIdleAnimation, LVar4, 1)
            BreakLoop
        EndIf
        Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.099609375), Float(1.0))
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
            IfEq(LVar4, 0)
                Call(DispatchEventPlayer, 66)
            Else
                Call(DispatchEvent, 256, 66)
            EndIf
            Call(UseIdleAnimation, LVar4, 1)
            BreakLoop
        EndIf
        Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2001953125), Float(1.0))
        Set(LFlag0, 0)
        Loop(3)
            Call(GetMashActionQuality, LVar1)
            IfEq(LVar1, 1)
                Set(LFlag0, 1)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        IfEq(LFlag0, 1)
            IfEq(LVar4, 0)
                Call(DispatchEventPlayer, 66)
            Else
                Call(DispatchEvent, 256, 66)
            EndIf
            Call(UseIdleAnimation, LVar4, 1)
            BreakLoop
        EndIf
        Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
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
            IfEq(LVar4, 0)
                Call(DispatchEventPlayer, 66)
            Else
                Call(DispatchEvent, 256, 66)
            EndIf
            Call(UseIdleAnimation, LVar4, 1)
            BreakLoop
        EndIf
        Call(UseIdleAnimation, LVar4, 1)
        Call(SetDamageSource, 1)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0xA000000, 0, 0, 2, 64)
        Call(StartRumble, 2)
        Call(GetLastDamage, LVar4, LVar3)
        IfNe(LVar3, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8301)
            Call(PlaySoundAtActor, ACTOR_SELF, 532)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 10)
            Call(b_area_tik2_blooper_baby_SpawnDrainHealthStartFX, LVar0, LVar1, LVar2, LVar3)
            Thread
                Wait(15)
                Call(PlaySoundAtActor, ACTOR_SELF, 604)
                Call(b_area_tik2_blooper_baby_SpawnDrainHealthContinueFX, LVar0, LVar1, LVar2, LVar3)
            EndThread
            Add(LVar0, 20)
            Add(LVar1, 20)
            Call(PlayEffect_impl, 64, 0, LVar0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0)
            Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
            Call(GetActorHP, ACTOR_SELF, LVar0)
            Add(LVar0, LVar3)
            IfGt(LVar0, LVar1)
                Set(LVar0, LVar1)
            EndIf
            Call(SetEnemyHP, ACTOR_SELF, LVar0)
        Else
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            IfEq(LVar4, 0)
                Call(DispatchEventPlayer, 66)
            Else
                Call(DispatchEvent, 256, 66)
            EndIf
            Call(InterruptLeechActionCommand)
            BreakLoop
        EndIf
        Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
        Set(LFlag0, 0)
        Loop(3)
            Call(GetMashActionQuality, LVar1)
            IfEq(LVar1, 1)
                Set(LFlag0, 1)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        IfEq(LFlag0, 1)
            IfEq(LVar4, 0)
                Call(DispatchEventPlayer, 66)
            Else
                Call(DispatchEvent, 256, 66)
            EndIf
            Call(UseIdleAnimation, LVar4, 1)
            BreakLoop
        EndIf
        Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2001953125), Float(1.0))
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
            IfEq(LVar4, 0)
                Call(DispatchEventPlayer, 66)
            Else
                Call(DispatchEvent, 256, 66)
            EndIf
            Call(UseIdleAnimation, LVar4, 1)
            BreakLoop
        EndIf
        Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.099609375), Float(1.0))
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
            IfEq(LVar4, 0)
                Call(DispatchEventPlayer, 66)
            Else
                Call(DispatchEvent, 256, 66)
            EndIf
            Call(UseIdleAnimation, LVar4, 1)
            BreakLoop
        EndIf
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
        IfEq(LVar4, 0)
            Call(GetPlayerHP, LVar1)
        Else
            Call(TTYD64_GetPartnerHP_API, LVar1)
        EndIf
        IfEq(LVar1, 0)
            IfEq(LVar4, 0)
                Call(DispatchEventPlayer, 66)
            Else
                Call(DispatchEvent, 256, 66)
            EndIf
            Call(InterruptLeechActionCommand)
            BreakLoop
        EndIf
        Set(LFlag0, 0)
        Loop(12)
            Call(GetMashActionQuality, LVar1)
            IfEq(LVar1, 1)
                Set(LFlag0, 1)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        IfEq(LFlag0, 1)
            IfEq(LVar4, 0)
                Call(DispatchEventPlayer, 66)
            Else
                Call(DispatchEvent, 256, 66)
            EndIf
            BreakLoop
        EndIf
    EndLoop
    IfEq(LVar4, 0)
        Call(DispatchEventPlayer, 66)
    Else
        Call(DispatchEvent, 256, 66)
    EndIf
    Call(InterruptLeechActionCommand)
    Call(UseIdleAnimation, LVar4, 1)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(GetStatusFlags, LVar4, LVar0)
    IfFlag(LVar0, 0x100000)
        Call(SetAnimation, ACTOR_SELF, 1, 0x510002)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x510000)
    EndIf
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Sub(LVar1, 15)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8022241C_1B)
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_Blooper_Script_SprayInk_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 85)
    Add(LVar1, 45)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    IfGt(LVarB, 30)
        Sub(LVarB, 30)
    Else
        Set(LVarB, 0)
    EndIf
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(FallToGoal, ACTOR_SELF, 8)
    Thread
        Call(UseBattleCamPreset, 19)
        Sub(LVar0, 30)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 350)
        Call(MoveBattleCamOver, 50)
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
    Call(PlaySoundAtActor, ACTOR_SELF, 988)
    Set(LVar7, LVar4)
    Add(LVar7, LVar0)
    MulF(LVar7, Float(0.5))
    Set(LVar8, LVar5)
    Add(LVar8, LVar1)
    MulF(LVar8, Float(0.5))
    Set(LVar9, LVar6)
    Add(LVar9, LVar2)
    MulF(LVar9, Float(0.5))
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar7, LVar8, LVar9)
    Call(FlyToGoal, ACTOR_SELF, 15, -2, 5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Sub(LVarB, 20)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(PlaySoundAtActor, ACTOR_SELF, 988)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 15, -2, 5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500003)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Sub(LVarB, 30)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2001953125))
    Call(SetActorSpeed, ACTOR_SELF, Float(1.0))
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(FlyToGoal, ACTOR_SELF, 16, 0, 0)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 40, 0)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, -40)
    Call(PlaySoundAtActor, ACTOR_SELF, 990)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Add(LVar3, 1)
    Sub(LVar4, 27)
    Sub(LVar5, 3)
    Call(GetOwnerTarget, LVarD, 0)
    Call(GetActorPos, LVarD, LVar0, LVar1, LVar2)
    Call(b_area_tik2_blooper_SpitInk, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0x10000000, 0, 1, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(10)
            IfEq(LVarF, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarE, 0x10000000, 0, 1, 16)
            Switch(LVarE)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarE, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVarE, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                    Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                    ExecWait(TTYD64_imp_1B_Blooper_Script_8021A5FC_1B)
                    Call(EnableIdleScript, ACTOR_SELF, -1)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
                EndCaseGroup
                CaseDefault
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000000, 0, 0, 3, 32)
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                    Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                    ExecWait(TTYD64_imp_1B_Blooper_Script_8021A5FC_1B)
                    Call(EnableIdleScript, ACTOR_SELF, -1)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
            EndSwitch
        EndCaseGroup
        CaseDefault
            Wait(10)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetDamageSource, 26)
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000000, 0, 0, 3, 32)
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarE, 0x10000000, 0, 1, 16)
            Switch(LVarE)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarE, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVarE, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                EndCaseGroup
                CaseDefault
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarE, 0x10000000, 0, 0, 3, 32)
            EndSwitch
            Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
            Wait(30)
            Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            ExecWait(TTYD64_imp_1B_Blooper_Script_8021A5FC_1B)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_ElectroBlooper_Script_SprayInk_ElectroBlooper_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 85)
    Add(LVar1, 45)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    IfGt(LVarB, 30)
        Sub(LVarB, 30)
    Else
        Set(LVarB, 0)
    EndIf
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(FallToGoal, ACTOR_SELF, 8)
    Thread
        Call(UseBattleCamPreset, 19)
        Sub(LVar0, 30)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 350)
        Call(MoveBattleCamOver, 80)
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
    Call(PlaySoundAtActor, ACTOR_SELF, 988)
    Set(LVar7, LVar4)
    Add(LVar7, LVar0)
    MulF(LVar7, Float(0.5))
    Set(LVar8, LVar5)
    Add(LVar8, LVar1)
    MulF(LVar8, Float(0.5))
    Set(LVar9, LVar6)
    Add(LVar9, LVar2)
    MulF(LVar9, Float(0.5))
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar7, LVar8, LVar9)
    Call(FlyToGoal, ACTOR_SELF, 15, -2, 5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Sub(LVarB, 20)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(PlaySoundAtActor, ACTOR_SELF, 988)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 15, -2, 5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500003)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Sub(LVarB, 30)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2001953125))
    Call(SetActorSpeed, ACTOR_SELF, Float(1.0))
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(FlyToGoal, ACTOR_SELF, 16, 0, 0)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 40, 0)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, -40)
    Call(PlaySoundAtActor, ACTOR_SELF, 990)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Add(LVar3, 1)
    Sub(LVar4, 28)
    Sub(LVar5, 3)
    Call(GetOwnerTarget, LVarD, 0)
    Call(GetActorPos, LVarD, LVar0, LVar1, LVar2)
    Call(b_area_tik2_electro_blooper_SpitInk, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0x10000000, 0, 1, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(10)
            IfEq(LVarF, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarE, 0x10000000, 0, 1, 16)
            Switch(LVarE)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarE, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVarE, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                    Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                    ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_8021C54C_1B)
                    Call(EnableIdleScript, ACTOR_SELF, -1)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
                EndCaseGroup
                CaseDefault
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000000, 0, 0, 4, 32)
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                    Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                    ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_8021C54C_1B)
                    Call(EnableIdleScript, ACTOR_SELF, -1)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
            EndSwitch
        EndCaseGroup
        CaseDefault
            Wait(10)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetDamageSource, 26)
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000000, 0, 0, 4, 32)
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarE, 0x10000000, 0, 1, 16)
            Switch(LVarE)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarE, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVarE, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                EndCaseGroup
                CaseDefault
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarE, 0x10000000, 0, 0, 4, 32)
            EndSwitch
            Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
            Wait(30)
            Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_8021C54C_1B)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_SprayInk_SuperBlooper_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 85)
    Add(LVar1, 45)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    IfGt(LVarB, 30)
        Sub(LVarB, 30)
    Else
        Set(LVarB, 0)
    EndIf
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
    Call(PlaySoundAtActor, ACTOR_SELF, 988)
    Set(LVar7, LVar4)
    Add(LVar7, LVar0)
    MulF(LVar7, Float(0.5))
    Set(LVar8, LVar5)
    Add(LVar8, LVar1)
    MulF(LVar8, Float(0.5))
    Set(LVar9, LVar6)
    Add(LVar9, LVar2)
    MulF(LVar9, Float(0.5))
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar7, LVar8, LVar9)
    Call(FlyToGoal, ACTOR_SELF, 15, -2, 5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Sub(LVarB, 20)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(PlaySoundAtActor, ACTOR_SELF, 988)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 15, -2, 5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500003)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Sub(LVarB, 30)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2001953125))
    Call(SetActorSpeed, ACTOR_SELF, Float(1.0))
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(FlyToGoal, ACTOR_SELF, 16, 0, 0)
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 40, 0)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, -40)
    Call(PlaySoundAtActor, ACTOR_SELF, 990)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Add(LVar3, 1)
    Sub(LVar4, 30)
    Call(GetOwnerTarget, LVarD, 0)
    Call(GetActorPos, LVarD, LVar0, LVar1, LVar2)
    Call(b_area_tik2_super_blooper_SpitInk, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0x10000000, 0, 1, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(10)
            IfEq(LVarF, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarE, 0x10000000, 0, 1, 16)
            Switch(LVarE)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarE, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVarE, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                    Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                    ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8021F43C_1B)
                    Call(EnableIdleScript, ACTOR_SELF, -1)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
                EndCaseGroup
                CaseDefault
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000000, 0, 0, 5, 32)
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                    Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                    ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8021F43C_1B)
                    Call(EnableIdleScript, ACTOR_SELF, -1)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
            EndSwitch
        EndCaseGroup
        CaseDefault
            Wait(10)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetDamageSource, 26)
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000000, 0, 0, 5, 32)
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarE, 0x10000000, 0, 1, 16)
            Switch(LVarE)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarE, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVarE, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                EndCaseGroup
                CaseDefault
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarE, 0x10000000, 0, 0, 5, 32)
            EndSwitch
            Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
            Wait(30)
            Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8021F43C_1B)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_EnragedTackle_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Set(LVar1, 100)
    Set(LVar3, 15)
    ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8021EF60_1B)
    Call(PlaySoundAtActor, ACTOR_SELF, 989)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0, 0, 1, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            Thread
                Set(LVar0, 0)
                Loop(36)
                    Add(LVar0, 30)
                    Call(SetActorYaw, ACTOR_SELF, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorYaw, ACTOR_SELF, 0)
            EndThread
            Call(SetAnimation, ACTOR_SELF, 1, 0x50000D)
            Call(GetOwnerTarget, LVar3, 0)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            ExecWait(b_area_tik2_super_blooper_EVS_LoseRage)
            IfEq(LVarF, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8021F43C_1B)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Set(LVar0, 0)
        Loop(16)
            Add(LVar0, 30)
            Call(SetActorYaw, ACTOR_SELF, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorYaw, ACTOR_SELF, 0)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000D)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Add(LVar1, 30)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetStatusFlags, LVar3, LVarE)
    IfFlag(LVarE, 0x100000)
        Goto(0)
    EndIf
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 8320, 0, 0, 10, 64)
    Call(GetOwnerTarget, LVar3, 0)
    IfEq(LVar3, 0)
        Call(GetPlayerHP, LVarE)
    Else
        Call(TTYD64_GetPartnerHP_API, LVarE)
    EndIf
    IfEq(LVarE, 0)
        Goto(1)
    EndIf
    Thread
        Set(LVar0, 0)
        Loop(20)
            Add(LVar0, 36)
            Call(SetActorYaw, ACTOR_SELF, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorYaw, ACTOR_SELF, 0)
    EndThread
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.400390625))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
    Label(0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 8320, 0, 0, 10, 32)
    Label(1)
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetStatusFlags, LVar3, LVar0)
    IfFlag(LVar0, 0x100000)
        Call(SetAnimation, ACTOR_SELF, 1, 0x500004)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Sub(LVar1, 15)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    ExecWait(b_area_tik2_super_blooper_EVS_LoseRage)
    ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8021F43C_1B)
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_ElectroBlooper_Script_ElectroTackle_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
        Add(LVar1, 112)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 500)
        Call(MoveBattleCamOver, 130)
    Else
        Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
        Add(LVar1, 82)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 385)
        Call(MoveBattleCamOver, 130)
    EndIf
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Set(LVar1, 100)
    Set(LVar3, 15)
    ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_8021C070_1B)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 32, 0, 1, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            Thread
                Set(LVar0, 0)
                Loop(36)
                    Add(LVar0, 30)
                    Call(SetActorYaw, ACTOR_SELF, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorYaw, ACTOR_SELF, 0)
            EndThread
            Call(SetAnimation, ACTOR_SELF, 1, 0x50000D)
            Call(GetOwnerTarget, LVar3, 0)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            IfEq(LVarF, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_8021C54C_1B)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Set(LVar0, 0)
        Loop(16)
            Add(LVar0, 30)
            Call(SetActorYaw, ACTOR_SELF, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorYaw, ACTOR_SELF, 0)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000D)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Add(LVar1, 30)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 160, 8, 0, 6, 32)
    IfNe(LVarF, 7)
        ExecWait(b_area_tik2_electro_blooper_EVS_Discharge)
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetStatusFlags, LVar3, LVar0)
    IfFlag(LVar0, 0x100000)
        Call(SetAnimation, ACTOR_SELF, 1, 0x500004)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Sub(LVar1, 15)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_8021C54C_1B)
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_Blooper_Script_Tackle_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
        Add(LVar1, 95)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 400)
        Call(MoveBattleCamOver, 130)
    Else
        Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
        Add(LVar1, 72)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 340)
        Call(MoveBattleCamOver, 130)
    EndIf
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Set(LVar1, 100)
    Set(LVar3, 15)
    ExecWait(TTYD64_imp_1B_Blooper_Script_8021A120_1B)
    Call(PlaySoundAtActor, ACTOR_SELF, 989)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0, 0, 1, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            Thread
                Set(LVar0, 0)
                Loop(36)
                    Add(LVar0, 30)
                    Call(SetActorYaw, ACTOR_SELF, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorYaw, ACTOR_SELF, 0)
            EndThread
            Call(SetAnimation, ACTOR_SELF, 1, 0x50000D)
            Call(GetOwnerTarget, LVar3, 0)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            IfEq(LVarF, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            ExecWait(TTYD64_imp_1B_Blooper_Script_8021A5FC_1B)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Set(LVar0, 0)
        Loop(16)
            Add(LVar0, 30)
            Call(SetActorYaw, ACTOR_SELF, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorYaw, ACTOR_SELF, 0)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000D)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Add(LVar1, 30)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 3, 32)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetStatusFlags, LVar3, LVar0)
    IfFlag(LVar0, 0x100000)
        Call(SetAnimation, ACTOR_SELF, 1, 0x500004)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Sub(LVar1, 15)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    ExecWait(TTYD64_imp_1B_Blooper_Script_8021A5FC_1B)
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_ElectroBlooper_Script_Tackle_ElectroBlooper_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
        Add(LVar1, 112)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 500)
        Call(MoveBattleCamOver, 130)
    Else
        Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
        Add(LVar1, 82)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 385)
        Call(MoveBattleCamOver, 130)
    EndIf
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Set(LVar1, 100)
    Set(LVar3, 15)
    ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_8021C070_1B)
    Call(PlaySoundAtActor, ACTOR_SELF, 989)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0, 0, 1, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            Thread
                Set(LVar0, 0)
                Loop(36)
                    Add(LVar0, 30)
                    Call(SetActorYaw, ACTOR_SELF, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorYaw, ACTOR_SELF, 0)
            EndThread
            Call(SetAnimation, ACTOR_SELF, 1, 0x50000D)
            Call(GetOwnerTarget, LVar3, 0)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            IfEq(LVarF, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_8021C54C_1B)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Set(LVar0, 0)
        Loop(16)
            Add(LVar0, 30)
            Call(SetActorYaw, ACTOR_SELF, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorYaw, ACTOR_SELF, 0)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000D)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Add(LVar1, 30)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 4, 32)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetStatusFlags, LVar3, LVar0)
    IfFlag(LVar0, 0x100000)
        Call(SetAnimation, ACTOR_SELF, 1, 0x500004)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Sub(LVar1, 15)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_8021C54C_1B)
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_Tackle_SuperBlooper_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Set(LVar1, 100)
    Set(LVar3, 15)
    ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8021EF60_1B)
    Call(PlaySoundAtActor, ACTOR_SELF, 989)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0, 0, 1, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            Thread
                Set(LVar0, 0)
                Loop(36)
                    Add(LVar0, 30)
                    Call(SetActorYaw, ACTOR_SELF, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorYaw, ACTOR_SELF, 0)
            EndThread
            Call(SetAnimation, ACTOR_SELF, 1, 0x50000D)
            Call(GetOwnerTarget, LVar3, 0)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            IfEq(LVarF, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8021F43C_1B)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Set(LVar0, 0)
        Loop(16)
            Add(LVar0, 30)
            Call(SetActorYaw, ACTOR_SELF, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorYaw, ACTOR_SELF, 0)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000D)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Add(LVar1, 30)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 5, 32)
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetStatusFlags, LVar3, LVar0)
    IfFlag(LVar0, 0x100000)
        Call(SetAnimation, ACTOR_SELF, 1, 0x500004)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Sub(LVar1, 15)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8021F43C_1B)
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_ElectroBlooper_Script_HandleEvent_8021CEE8_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_tik2_electro_blooper_EVS_Discharge)
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_tik2_electro_blooper_EVS_Discharge)
            SetConst(LVar1, 0x500004)
            ExecWait(b_area_tik2_electro_blooper_EVS_Death)
            Return
        CaseEq(14)
            Set(LVar0, 1)
            Set(LVar1, 0x500005)
            Set(LVar2, 0x500006)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_tik2_electro_blooper_EVS_Discharge)
        CaseEq(36)
            Set(LVar0, 1)
            Set(LVar1, 0x500005)
            Set(LVar2, 0x500006)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_tik2_electro_blooper_EVS_Discharge)
            SetConst(LVar1, 0x500006)
            ExecWait(b_area_tik2_electro_blooper_EVS_Death)
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            ExecWait(b_area_tik2_electro_blooper_EVS_Discharge)
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            ExecWait(b_area_tik2_electro_blooper_EVS_Discharge)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(b_area_tik2_electro_blooper_EVS_Death)
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
        CaseOrEq(29)
        CaseOrEq(30)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500000)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseOrEq(19)
        CaseOrEq(20)
            ExecWait(b_area_tik2_electro_blooper_EVS_Discharge)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_8021C54C_1B)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(b_area_tik2_electro_blooper_EVS_Death)
            Return
        CaseEq(53)
            ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_8021C54C_1B)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500000)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_HandleEvent_8021FC18_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_Hit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(b_area_tik2_super_blooper_EVS_Death)
            Return
        CaseEq(14)
            Set(LVar0, 1)
            Set(LVar1, 0x500005)
            Set(LVar2, 0x500006)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            Set(LVar0, 1)
            Set(LVar1, 0x500005)
            Set(LVar2, 0x500006)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500006)
            ExecWait(b_area_tik2_super_blooper_EVS_Death)
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(b_area_tik2_super_blooper_EVS_Death)
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
        CaseOrEq(29)
        CaseOrEq(30)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500000)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseOrEq(19)
        CaseOrEq(20)
            ExecWait(b_area_tik2_super_blooper_EVS_LoseRage)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(47)
            ExecWait(b_area_tik2_super_blooper_EVS_LoseRage)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8021F43C_1B)
        CaseEq(38)
            ExecWait(b_area_tik2_super_blooper_EVS_LoseRage)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(b_area_tik2_super_blooper_EVS_Death)
            Return
        CaseEq(53)
            ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8021F43C_1B)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500000)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_Blooper_Script_8021A120_1B = {
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    IfGt(LVarB, 20)
        Sub(LVarB, 20)
    Else
        Set(LVarB, 0)
    EndIf
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
    Call(PlaySoundAtActor, ACTOR_SELF, 988)
    Set(LVar7, LVar4)
    Add(LVar7, LVar4)
    Add(LVar7, LVar0)
    MulF(LVar7, Float(0.330078125))
    Set(LVar8, LVar5)
    Add(LVar8, LVar5)
    Add(LVar8, LVar1)
    MulF(LVar8, Float(0.330078125))
    Set(LVar9, LVar6)
    Add(LVar9, LVar6)
    Add(LVar9, LVar2)
    MulF(LVar9, Float(0.330078125))
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar7, LVar8, LVar9)
    Call(FlyToGoal, ACTOR_SELF, LVar3, -2, 5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Sub(LVarB, 20)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(PlaySoundAtActor, ACTOR_SELF, 988)
    Set(LVar7, LVar0)
    Add(LVar7, LVar0)
    Add(LVar7, LVar4)
    MulF(LVar7, Float(0.330078125))
    Set(LVar8, LVar1)
    Add(LVar8, LVar1)
    Add(LVar8, LVar5)
    MulF(LVar8, Float(0.330078125))
    Set(LVar9, LVar2)
    Add(LVar9, LVar2)
    Add(LVar9, LVar6)
    MulF(LVar9, Float(0.330078125))
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar7, LVar8, LVar9)
    Call(FlyToGoal, ACTOR_SELF, LVar3, -2, 5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Sub(LVarB, 20)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(PlaySoundAtActor, ACTOR_SELF, 988)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, LVar3, -2, 5)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_ElectroBlooper_Script_8021C070_1B = {
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    IfGt(LVarB, 20)
        Sub(LVarB, 20)
    Else
        Set(LVarB, 0)
    EndIf
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
    Call(PlaySoundAtActor, ACTOR_SELF, 988)
    Set(LVar7, LVar4)
    Add(LVar7, LVar4)
    Add(LVar7, LVar0)
    MulF(LVar7, Float(0.330078125))
    Set(LVar8, LVar5)
    Add(LVar8, LVar5)
    Add(LVar8, LVar1)
    MulF(LVar8, Float(0.330078125))
    Set(LVar9, LVar6)
    Add(LVar9, LVar6)
    Add(LVar9, LVar2)
    MulF(LVar9, Float(0.330078125))
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar7, LVar8, LVar9)
    Call(FlyToGoal, ACTOR_SELF, LVar3, -2, 5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Sub(LVarB, 20)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(PlaySoundAtActor, ACTOR_SELF, 988)
    Set(LVar7, LVar0)
    Add(LVar7, LVar0)
    Add(LVar7, LVar4)
    MulF(LVar7, Float(0.330078125))
    Set(LVar8, LVar1)
    Add(LVar8, LVar1)
    Add(LVar8, LVar5)
    MulF(LVar8, Float(0.330078125))
    Set(LVar9, LVar2)
    Add(LVar9, LVar2)
    Add(LVar9, LVar6)
    MulF(LVar9, Float(0.330078125))
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar7, LVar8, LVar9)
    Call(FlyToGoal, ACTOR_SELF, LVar3, -2, 5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Sub(LVarB, 20)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(PlaySoundAtActor, ACTOR_SELF, 988)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, LVar3, -2, 5)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_8021EF60_1B = {
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    IfGt(LVarB, 20)
        Sub(LVarB, 20)
    Else
        Set(LVarB, 0)
    EndIf
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
    Call(PlaySoundAtActor, ACTOR_SELF, 988)
    Set(LVar7, LVar4)
    Add(LVar7, LVar4)
    Add(LVar7, LVar0)
    MulF(LVar7, Float(0.330078125))
    Set(LVar8, LVar5)
    Add(LVar8, LVar5)
    Add(LVar8, LVar1)
    MulF(LVar8, Float(0.330078125))
    Set(LVar9, LVar6)
    Add(LVar9, LVar6)
    Add(LVar9, LVar2)
    MulF(LVar9, Float(0.330078125))
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar7, LVar8, LVar9)
    Call(FlyToGoal, ACTOR_SELF, LVar3, -2, 5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Sub(LVarB, 20)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(PlaySoundAtActor, ACTOR_SELF, 988)
    Set(LVar7, LVar0)
    Add(LVar7, LVar0)
    Add(LVar7, LVar4)
    MulF(LVar7, Float(0.330078125))
    Set(LVar8, LVar1)
    Add(LVar8, LVar1)
    Add(LVar8, LVar5)
    MulF(LVar8, Float(0.330078125))
    Set(LVar9, LVar2)
    Add(LVar9, LVar2)
    Add(LVar9, LVar6)
    MulF(LVar9, Float(0.330078125))
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar7, LVar8, LVar9)
    Call(FlyToGoal, ACTOR_SELF, LVar3, -2, 5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Sub(LVarB, 20)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(PlaySoundAtActor, ACTOR_SELF, 988)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, LVar3, -2, 5)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_80221F40_1B = {
    Call(SetAnimation, ACTOR_SELF, 1, 0x510000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x510001)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    IfGt(LVarB, 20)
        Sub(LVarB, 20)
    Else
        Set(LVarB, 0)
    EndIf
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
    Call(PlaySoundAtActor, ACTOR_SELF, 863)
    Set(LVar7, LVar4)
    Add(LVar7, LVar4)
    Add(LVar7, LVar0)
    MulF(LVar7, Float(0.330078125))
    Set(LVar8, LVar5)
    Add(LVar8, LVar5)
    Add(LVar8, LVar1)
    MulF(LVar8, Float(0.330078125))
    Set(LVar9, LVar6)
    Add(LVar9, LVar6)
    Add(LVar9, LVar2)
    MulF(LVar9, Float(0.330078125))
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar7, LVar8, LVar9)
    Call(FlyToGoal, ACTOR_SELF, LVar3, -2, 5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x510000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x510001)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Sub(LVarB, 20)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(PlaySoundAtActor, ACTOR_SELF, 863)
    Set(LVar7, LVar0)
    Add(LVar7, LVar0)
    Add(LVar7, LVar4)
    MulF(LVar7, Float(0.330078125))
    Set(LVar8, LVar1)
    Add(LVar8, LVar1)
    Add(LVar8, LVar5)
    MulF(LVar8, Float(0.330078125))
    Set(LVar9, LVar2)
    Add(LVar9, LVar2)
    Add(LVar9, LVar6)
    MulF(LVar9, Float(0.330078125))
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar7, LVar8, LVar9)
    Call(FlyToGoal, ACTOR_SELF, LVar3, -2, 5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x510000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x510001)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Sub(LVarB, 20)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(FallToGoal, ACTOR_SELF, 8)
    Call(PlaySoundAtActor, ACTOR_SELF, 863)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, LVar3, -2, 5)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_HandleEvent_80222CF8_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x510002)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x510002)
            ExecWait(Ref(EVS_Enemy_Hit))
            SetConst(LVar1, 0x510003)
            ExecWait(b_area_tik2_blooper_baby_EVS_Death)
            Return
        CaseEq(14)
            Set(LVar0, 1)
            Set(LVar1, 0x510004)
            Set(LVar2, 0x510005)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            Set(LVar0, 1)
            Set(LVar1, 0x510004)
            Set(LVar2, 0x510005)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar1, 0x510005)
            ExecWait(b_area_tik2_blooper_baby_EVS_Death)
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x510002)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x510002)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x510003)
            ExecWait(b_area_tik2_blooper_baby_EVS_Death)
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x510000)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(47)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x510002)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x510002)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8022241C_1B)
        CaseOrEq(38)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x510002)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x510002)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x510003)
            ExecWait(b_area_tik2_blooper_baby_EVS_Death)
            Return
        CaseEq(53)
            ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8022241C_1B)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x510000)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_SpawnBabies_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(UseBattleCamPreset, 7)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamOffsetY, 50)
    Call(SetBattleCamDist, 330)
    Call(MoveBattleCamOver, 40)
    Wait(20)
    Call(PlaySoundAtActor, ACTOR_SELF, 998)
    Call(b_area_tik2_super_blooper_FadeBackgroundDarken)
    Call(b_area_tik2_super_blooper_StartRumbleWithParams, 50, 20)
    Thread
        Call(ShakeCam, 1, 0, 10, Float(0.2998046875))
    EndThread
    Call(UseBattleCamPreset, 7)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamOffsetY, 65)
    Call(SetBattleCamDist, 240)
    Call(MoveBattleCamOver, 15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500009)
    Wait(15)
    Call(b_area_tik2_super_blooper_StartRumbleWithParams, 100, 20)
    Thread
        Call(ShakeCam, 1, 0, 10, Float(0.400390625))
    EndThread
    Call(UseBattleCamPreset, 7)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamOffsetY, 80)
    Call(SetBattleCamDist, 150)
    Call(MoveBattleCamOver, 15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000A)
    Wait(15)
    Call(b_area_tik2_super_blooper_StartRumbleWithParams, 150, 20)
    Thread
        Call(ShakeCam, 1, 0, 10, Float(0.5))
    EndThread
    Call(UseBattleCamPreset, 7)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamOffsetY, 95)
    Call(SetBattleCamDist, 60)
    Call(MoveBattleCamOver, 15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000B)
    Wait(30)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x500003)
    Wait(10)
    Call(ActorExists, 513, LVar1)
    IfEq(LVar1, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 985)
        Call(SummonEnemy, Ref(TTYD64_imp_1B_SuperBlooper_SpecialFormation_80221EFC_1B), 0)
    EndIf
    Call(ActorExists, 514, LVar1)
    IfEq(LVar1, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 985)
        Call(SummonEnemy, Ref(TTYD64_imp_1B_SuperBlooper_SpecialFormation_80221F18_1B), 0)
    EndIf
    Wait(2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(b_area_tik2_super_blooper_FadeBackgroundLighten)
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_Blooper_Script_HandleEvent_8021ACFC_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_Hit))
            SetConst(LVar1, 0x500004)
            ExecWait(b_area_tik2_blooper_EVS_Death)
            Return
        CaseEq(14)
            Set(LVar0, 1)
            Set(LVar1, 0x500005)
            Set(LVar2, 0x500006)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            Set(LVar0, 1)
            Set(LVar1, 0x500005)
            Set(LVar2, 0x500006)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar1, 0x500006)
            ExecWait(b_area_tik2_blooper_EVS_Death)
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(b_area_tik2_blooper_EVS_Death)
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500000)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(TTYD64_imp_1B_Blooper_Script_8021A5FC_1B)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500004)
            ExecWait(b_area_tik2_blooper_EVS_Death)
            Return
        CaseEq(53)
            ExecWait(TTYD64_imp_1B_Blooper_Script_8021A5FC_1B)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x500000)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_Idle_8021F7E0_1B = {
    Label(0)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x351000)
        Wait(1)
        Goto(0)
    EndIf
    Call(SetIdleGoalToHome, ACTOR_SELF)
    Call(GetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 0)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    IfGe(LVar4, LVar1)
        Goto(11)
    EndIf
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_tik2_super_blooper_AscendAnims))
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Wait(9)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, 0, 11)
    Label(11)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x351000)
        Wait(1)
        Goto(0)
    EndIf
    Call(SetIdleGoalToHome, ACTOR_SELF)
    Call(GetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 10)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    IfGe(LVar4, LVar1)
        Goto(12)
    EndIf
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_tik2_super_blooper_AscendAnims))
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Wait(9)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, 0, 11)
    Wait(3)
    Label(12)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x351000)
        Wait(1)
        Goto(0)
    EndIf
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_tik2_super_blooper_DescendAnims))
    Call(SetIdleGoalToHome, ACTOR_SELF)
    Call(GetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, -10)
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(0.2998046875))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, 1, 11)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_Idle_802228C0_1B = {
    Label(0)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x351000)
        Wait(1)
        Goto(0)
    EndIf
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 0)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    IfGe(LVar4, LVar1)
        Goto(11)
    EndIf
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_tik2_blooper_baby_AscendAnims))
    Call(SetAnimation, ACTOR_SELF, 1, 0x510000)
    Wait(9)
    Call(SetAnimation, ACTOR_SELF, 1, 0x510001)
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, 0, 11)
    Label(11)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x351000)
        Wait(1)
        Goto(0)
    EndIf
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 5)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    IfGe(LVar4, LVar1)
        Goto(12)
    EndIf
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_tik2_blooper_baby_AscendAnims))
    Call(SetAnimation, ACTOR_SELF, 1, 0x510000)
    Wait(9)
    Call(SetAnimation, ACTOR_SELF, 1, 0x510001)
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, 0, 11)
    Wait(3)
    Label(12)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x351000)
        Wait(1)
        Goto(0)
    EndIf
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_tik2_blooper_baby_DescendAnims))
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, -5)
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(0.2998046875))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, 1, 11)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_ElectroBlooper_Script_Idle_8021CAB0_1B = {
    Label(0)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x351000)
        Wait(1)
        Goto(0)
    EndIf
    Call(SetIdleGoalToHome, ACTOR_SELF)
    Call(GetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 0)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    IfGe(LVar4, LVar1)
        Goto(11)
    EndIf
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_tik2_electro_blooper_AscendAnims))
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Wait(9)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, 0, 11)
    Label(11)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x351000)
        Wait(1)
        Goto(0)
    EndIf
    Call(SetIdleGoalToHome, ACTOR_SELF)
    Call(GetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 10)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    IfGe(LVar4, LVar1)
        Goto(12)
    EndIf
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_tik2_electro_blooper_AscendAnims))
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Wait(9)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, 0, 11)
    Wait(3)
    Label(12)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x351000)
        Wait(1)
        Goto(0)
    EndIf
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_tik2_electro_blooper_DescendAnims))
    Call(SetIdleGoalToHome, ACTOR_SELF)
    Call(GetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, -10)
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(0.2998046875))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, 1, 11)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_Blooper_Script_Idle_8021A8C4_1B = {
    Label(0)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x351000)
        Wait(1)
        Goto(0)
    EndIf
    Call(SetIdleGoalToHome, ACTOR_SELF)
    Call(GetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 0)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    IfGe(LVar4, LVar1)
        Goto(11)
    EndIf
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_tik2_blooper_AscendAnims))
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Wait(9)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, 0, 11)
    Label(11)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x351000)
        Wait(1)
        Goto(0)
    EndIf
    Call(SetIdleGoalToHome, ACTOR_SELF)
    Call(GetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 10)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    IfGe(LVar4, LVar1)
        Goto(12)
    EndIf
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_tik2_blooper_AscendAnims))
    Call(SetAnimation, ACTOR_SELF, 1, 0x500000)
    Wait(9)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000C)
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, 0, 11)
    Wait(3)
    Label(12)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x351000)
        Wait(1)
        Goto(0)
    EndIf
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_tik2_blooper_DescendAnims))
    Call(SetIdleGoalToHome, ACTOR_SELF)
    Call(GetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, -10)
    Call(SetActorIdleJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(0.2998046875))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, 1, 11)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_TakeTurn_SuperBlooper_1B = {
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseEq(3)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 0)
                Call(SetActorVar, ACTOR_SELF, 1, 0)
            EndIf
        CaseEq(1)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x80000)
                Call(SetActorVar, ACTOR_SELF, 1, 2)
            Else
                Call(ActorExists, 513, LVar0)
                IfNe(LVar0, 0)
                    Call(ActorExists, 514, LVar0)
                    IfNe(LVar0, 0)
                        Call(SetActorVar, ACTOR_SELF, 1, 2)
                    EndIf
                EndIf
            EndIf
        CaseDefault
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 1, 2)
            ExecWait(TTYD64_imp_1B_SuperBlooper_Script_SpawnBabies_1B)
            Return
        CaseEq(2)
            Call(SetActorVar, ACTOR_SELF, 1, 3)
            ExecWait(TTYD64_imp_1B_SuperBlooper_Script_Enrage_1B)
            Return
        CaseEq(3)
            Call(SetActorVar, ACTOR_SELF, 1, 0)
            ExecWait(TTYD64_imp_1B_SuperBlooper_Script_EnragedTackle_1B)
            Return
        CaseDefault
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Call(SetActorVar, ACTOR_SELF, 1, 1)
                Call(RandInt, 100, LVar0)
                IfLt(LVar0, 50)
                    ExecWait(TTYD64_imp_1B_SuperBlooper_Script_Tackle_SuperBlooper_1B)
                Else
                    ExecWait(TTYD64_imp_1B_SuperBlooper_Script_SprayInk_SuperBlooper_1B)
                EndIf
            Else
                ExecWait(TTYD64_imp_1B_SuperBlooper_Script_Tackle_SuperBlooper_1B)
            EndIf
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_Init_80222650_1B = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1B_SuperBlooper_Script_TakeTurn_8022319C_1B))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1B_SuperBlooper_Script_HandleEvent_80222CF8_1B))
    Call(PlaySoundAtActor, ACTOR_SELF, 863)
    Call(b_area_tik2_blooper_baby_StartRumbleWithParams, 80, 20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x510000)
    Call(SetAnimation, ACTOR_SELF, 1, 0x510001)
    Call(GetActorPos, 512, LVar0, LVar1, LVar2)
    Add(LVar1, 10)
    Sub(LVar2, 10)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 20)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(SetActorSpeed, ACTOR_SELF, Float(0.2998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 8, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 863)
    Call(b_area_tik2_blooper_baby_StartRumbleWithParams, 80, 20)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar1)
    Call(GetActorVar, ACTOR_SELF, 2, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 12, -2, 5)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_1B_SuperBlooper_Script_Idle_802228C0_1B))
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_tik2_Script_BeforeBattle_8022778C = {
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
        Exec(TTYD64_tik2_Script_802276F0)
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
        Exec(TTYD64_tik2_Script_802276F0)
    EndThread
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_Enrage_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(UseBattleCamPreset, 7)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamOffsetY, 28)
    Call(SetBattleCamDist, 297)
    Call(MoveBattleCamOver, 50)
    Wait(20)
    Call(PlaySoundAtActor, ACTOR_SELF, 998)
    Call(b_area_tik2_super_blooper_FadeBackgroundDarken)
    Call(b_area_tik2_super_blooper_StartRumbleWithParams, 70, 80)
    Thread
        Call(ShakeCam, 1, 0, 40, Float(0.2998046875))
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x500009)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000A)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000B)
    Wait(10)
    ExecWait(b_area_tik2_super_blooper_EVS_Enrage)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Call(b_area_tik2_super_blooper_FadeBackgroundLighten)
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_ElectroBlooper_Script_Electrify_1B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 65)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 320)
    Call(MoveBattleCamOver, 50)
    Wait(20)
    Call(b_area_tik2_electro_blooper_FadeBackgroundDarken)
    Call(b_area_tik2_electro_blooper_StartRumbleWithParams, 70, 80)
    Thread
        Call(ShakeCam, 1, 0, 40, Float(0.2998046875))
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x500009)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000A)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x50000B)
    Wait(10)
    ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_8021EC88_1B)
    Wait(20)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Call(b_area_tik2_electro_blooper_FadeBackgroundLighten)
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_ElectroBlooper_Script_8021EC88_1B = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfNe(LVar0, 0)
        Return
    EndIf
    Call(SetActorVar, ACTOR_SELF, 0, 1)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar1, 45)
        SetF(LVar3, Float(1.599609375))
    Else
        Add(LVar1, 18)
        SetF(LVar3, Float(0.6396484375))
    EndIf
    Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, LVar3, -1, 0, 0, 0, 0, 0, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, LVarF)
    Call(PlaySoundAtActor, ACTOR_SELF, 860)
    Call(SetPartEventFlags, ACTOR_SELF, 2, 0x400080)
    Call(EnableActorPaletteEffects, ACTOR_SELF, 1, 1)
    Call(SetActorPaletteEffect, ACTOR_SELF, 1, 4)
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_tik2_electro_blooper_ChargedStatusTable))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_ElectroBlooper_Script_UpdateElectictyPosition_1B = {
    Label(0)
    Call(ActorExists, ACTOR_SELF, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfNe(LVar0, 1)
        Goto(99)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    IfEq(LVar0, 0)
        Goto(99)
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Call(GetStatusFlags, ACTOR_SELF, LVar4)
    IfNotFlag(LVar4, 0x80000)
        Add(LVar2, 45)
        SetF(LVar4, Float(1.599609375))
    Else
        Add(LVar2, 18)
        SetF(LVar4, Float(0.6396484375))
    EndIf
    Call(b_area_tik2_electro_blooper_UpdateStaticEffect, LVar0, LVar1, LVar2, LVar3, LVar4)
    Label(99)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_ElectroBlooper_Script_TakeTurn_8021D40C_1B = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 2, 0)
        ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_ElectroTackle_1B)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_Electrify_1B)
        Return
    Else
        Call(GetStatusFlags, ACTOR_SELF, LVar0)
        IfNotFlag(LVar0, 0x80000)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 50)
                ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_Tackle_ElectroBlooper_1B)
            Else
                ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_SprayInk_ElectroBlooper_1B)
            EndIf
        Else
            ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_Tackle_ElectroBlooper_1B)
        EndIf
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_ElectroBlooper_Script_Init_8021C82C_1B = {
    Call(ForceHomePos, ACTOR_SELF, 90, 45, -10)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetActorScale, ACTOR_SELF, Float(1.25), Float(1.25), Float(1.0))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Exec(TTYD64_imp_1B_ElectroBlooper_Script_UpdateElectictyPosition_1B)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1B_ElectroBlooper_Script_TakeTurn_8021D40C_1B))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_1B_ElectroBlooper_Script_Idle_8021CAB0_1B))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1B_ElectroBlooper_Script_HandleEvent_8021CEE8_1B))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_Init_8021F71C_1B = {
    Call(ForceHomePos, ACTOR_SELF, 90, 45, -10)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetActorScale, ACTOR_SELF, Float(2.0), Float(2.0), Float(2.0))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1B_SuperBlooper_Script_TakeTurn_SuperBlooper_1B))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_1B_SuperBlooper_Script_Idle_8021F7E0_1B))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1B_SuperBlooper_Script_HandleEvent_8021FC18_1B))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_Blooper_Script_TakeTurn_Blooper_1B = {
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(RandInt, 100, LVar0)
        IfLt(LVar0, 50)
            ExecWait(TTYD64_imp_1B_Blooper_Script_Tackle_1B)
        Else
            ExecWait(TTYD64_imp_1B_Blooper_Script_SprayInk_1B)
        EndIf
    Else
        ExecWait(TTYD64_imp_1B_Blooper_Script_Tackle_1B)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_tik2_Script_802276F0 = {
    SetGroup(0)
    IfEq(LVar5, 1)
        IfEq(LVar6, 1)
            IfEq(LVar7, 1)
                IfEq(LVar8, 1)
                    Call(TTYD64_tik2_Function_80219E10)
                    Return
                EndIf
            EndIf
        EndIf
    EndIf
    Call(TTYD64_tik2_Function_80219F34)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_Blooper_Script_Init_8021A830_1B = {
    Call(SetActorScale, ACTOR_SELF, Float(0.75), Float(0.75), Float(1.0))
    Call(ForceHomePos, ACTOR_SELF, 90, 45, -10)
    Call(HPBarToHome, ACTOR_SELF)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1B_Blooper_Script_TakeTurn_Blooper_1B))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_1B_Blooper_Script_Idle_8021A8C4_1B))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1B_Blooper_Script_HandleEvent_8021ACFC_1B))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_8022241C_1B = {
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar3, 12)
    ExecWait(TTYD64_imp_1B_SuperBlooper_Script_80221F40_1B)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_SuperBlooper_Script_8021F43C_1B = {
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar3, 12)
    ExecWait(TTYD64_imp_1B_SuperBlooper_Script_8021EF60_1B)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_Blooper_Script_8021A5FC_1B = {
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar3, 12)
    ExecWait(TTYD64_imp_1B_Blooper_Script_8021A120_1B)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1B_ElectroBlooper_Script_8021C54C_1B = {
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar3, 12)
    ExecWait(TTYD64_imp_1B_ElectroBlooper_Script_8021C070_1B)
    Return
    End
};
// clang-format on

Battle TTYD64_tik2_FormationTable[] = {
    { .name = "\262\303\275\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_tik2_Formation_00,
      .stage = &b_area_tik2_tik_01,
      .onBattleStart = NULL },
    { .name = "\323\352\323\352\262\303\275\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_tik2_Formation_01,
      .stage = &b_area_tik2_tik_01,
      .onBattleStart = NULL },
    { .name = "\323\303\260\262\303\275\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_tik2_Formation_02,
      .stage = &b_area_tik2_tik_01,
      .onBattleStart = NULL },
    {},
};

StageListRow TTYD64_tik2_StageTable[] = {
    { .name = "tik_01", .stage = &b_area_tik2_tik_01 },         { .name = "tik_02", .stage = &b_area_tik2_tik_02 },
    { .name = "tik_03", .stage = &b_area_tik2_tik_03 },         { .name = "tik_04", .stage = &b_area_tik2_tik_04 },
    { .name = "tik_05", .stage = &TTYD64_tik2_Stage_80227A08 }, {},
};

ActorBlueprint TTYD64_imp_1B_ElectroBlooper_1B_ElectroBlooper = {
    .flags = 0x200,
    .maxHP = 50,
    .type = 0xC8,
    .level = 50,
    .partCount = 2,
    .partsData = b_area_tik2_electro_blooper_ActorParts,
    .initScript = &TTYD64_imp_1B_ElectroBlooper_Script_Init_8021C82C_1B,
    .statusTable = b_area_tik2_electro_blooper_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 85,
    .coinReward = 0,
    .size = { 95, 105 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { 0, 40 },
    .statusTextOffset = { 25, 85 },
};

ActorBlueprint TTYD64_imp_1B_Blooper_1B_Blooper = {
    .flags = 0x200,
    .maxHP = 30,
    .type = 0xC7,
    .level = 44,
    .partCount = 2,
    .partsData = b_area_tik2_blooper_ActorParts,
    .initScript = &TTYD64_imp_1B_Blooper_Script_Init_8021A830_1B,
    .statusTable = b_area_tik2_blooper_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 57, 61 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { 0, 22 },
    .statusTextOffset = { 15, 55 },
};

Stage TTYD64_tik2_Stage_80227A08 = {
    .texture = "tik_tex",
    .shape = "tik_bt05_shape",
    .hit = "tik_bt05_hit",
    .preBattle = &TTYD64_tik2_Script_BeforeBattle_8022778C,
    .postBattle = &b_area_tik2_tik_05_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = b_area_tik2_tik_05_ForegroundModels,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_imp_1B_SuperBlooper_BlooperBaby_1B = {
    .flags = 0x200,
    .maxHP = 6,
    .type = 0xCC,
    .level = 0,
    .partCount = 2,
    .partsData = b_area_tik2_blooper_baby_ActorParts,
    .initScript = &TTYD64_imp_1B_SuperBlooper_Script_Init_80222650_1B,
    .statusTable = b_area_tik2_blooper_baby_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 0,
    .size = { 28, 25 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -12, 20 },
    .statusTextOffset = { 10, 25 },
};

ActorBlueprint TTYD64_imp_1B_SuperBlooper_1B_SuperBlooper = {
    .flags = 0x200,
    .maxHP = 70,
    .type = 0xCA,
    .level = 65,
    .partCount = 2,
    .partsData = b_area_tik2_super_blooper_ActorParts,
    .initScript = &TTYD64_imp_1B_SuperBlooper_Script_Init_8021F71C_1B,
    .statusTable = b_area_tik2_super_blooper_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { -111, -88 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { 0, 60 },
    .statusTextOffset = { 40, 80 },
};

FormationRow TTYD64_imp_1B_SuperBlooper_SpecialFormation_80221EFC_1B[] = {
    { .actor = &TTYD64_imp_1B_SuperBlooper_BlooperBaby_1B,
      .home = { .vec = &b_area_tik2_super_blooper_SummonPos },
      .priority = 95,
      .var0 = 30,
      .var1 = 68,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_1B_SuperBlooper_SpecialFormation_80221F18_1B[] = {
    { .actor = &TTYD64_imp_1B_SuperBlooper_BlooperBaby_1B,
      .home = { .vec = &b_area_tik2_super_blooper_SummonPos },
      .priority = 94,
      .var0 = 134,
      .var1 = 45,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_tik2_Formation_00[] = {
    { .actor = &TTYD64_imp_1B_Blooper_1B_Blooper,
      .home = { .vec = &b_area_tik2_BlooperPos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_tik2_Formation_01[] = {
    { .actor = &TTYD64_imp_1B_ElectroBlooper_1B_ElectroBlooper,
      .home = { .vec = &b_area_tik2_BlooperPos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_tik2_Formation_02[] = {
    { .actor = &TTYD64_imp_1B_SuperBlooper_1B_SuperBlooper,
      .home = { .vec = &b_area_tik2_BlooperPos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

void TTYD64_InstallBattles_tik2(void) {
    Mod_SetBattleList("TTYD64", 0x1B, TTYD64_tik2_FormationTable);
    Mod_SetStageList("TTYD64", 0x1B, TTYD64_tik2_StageTable);
}
