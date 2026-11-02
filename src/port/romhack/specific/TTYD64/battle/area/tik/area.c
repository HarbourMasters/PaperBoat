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

API_CALLABLE(b_area_tik_buzzy_beetle_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_tik_dark_paratroopa_StartRumbleWithParams);
API_CALLABLE(b_area_tik_gloomba_CalculateArcsinDeg);
API_CALLABLE(b_area_tik_paragloomba_CalculateArcsinDeg);
API_CALLABLE(b_area_tik_paragloomba_StartRumbleWithParams);
API_CALLABLE(b_area_tik_spike_top_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_tik_spiked_gloomba_CalculateArcsinDeg);
extern s32 b_area_dgb_tubba_blubba_DefenseTable[];
extern EvtScript b_area_tik_buzzy_beetle_EVS_CheckToppleAnim;
extern EvtScript b_area_tik_buzzy_beetle_EVS_Idle;
extern u8 b_area_tik_buzzy_beetle_FlipPosOffsets[];
extern s32 b_area_tik_buzzy_beetle_ToppledDefense[];
extern s32 b_area_tik_buzzy_beetle_UprightDefense[];
extern EvtScript b_area_tik_dark_koopa_EVS_UpdateOffsets;
extern u8 b_area_tik_dark_koopa_FlipPosOffsets[];
extern s32 b_area_tik_dark_koopa_StatusTable[];
extern s32 b_area_tik_dark_koopa_ToppledDefenseTable[];
extern s32 b_area_tik_dark_koopa_UprightDefenseTable[];
extern EvtScript b_area_tik_dark_paratroopa_EVS_HandlePhase_Flying;
extern EvtScript b_area_tik_dark_paratroopa_EVS_ReturnHome;
extern EvtScript b_area_tik_dark_paratroopa_EVS_UpdateOffsets_Flying;
extern EvtScript b_area_tik_dark_paratroopa_EVS_UpdateOffsets_Koopa;
extern u8 b_area_tik_dark_paratroopa_FlipPosOffsets[];
extern s32 b_area_tik_dark_paratroopa_FlyingStatusTable[];
extern s32 b_area_tik_dark_paratroopa_StatusTable[];
extern s32 b_area_tik_dark_paratroopa_ToppledDefenseTable[];
extern s32 b_area_tik_dark_paratroopa_UprightDefenseTable[];
extern s32 b_area_tik_dark_paratroopa_defenseTable2[];
extern s32 b_area_tik_gloomba_DefenseTable[];
extern s32 b_area_tik_gloomba_StatusTable[];
extern s32 b_area_tik_paragloomba_DownedDefense[];
extern s32 b_area_tik_paragloomba_DownedFlyingStatusTable[];
extern EvtScript b_area_tik_paragloomba_EVS_ReturnHome;
extern s32 b_area_tik_paragloomba_FlyingDefense[];
extern s32 b_area_tik_paragloomba_FlyingStatusTable[];
extern s32 b_area_tik_paragloomba_LeftWingAnims[];
extern s32 b_area_tik_paragloomba_RightWingAnims[];
extern EvtScript b_area_tik_spike_top_EVS_CheckToppleAnim;
extern EvtScript b_area_tik_spike_top_EVS_Idle;
extern u8 b_area_tik_spike_top_FlipPosOffsets[];
extern s32 b_area_tik_spike_top_StatusTable[];
extern s32 b_area_tik_spike_top_ToppledDefense[];
extern s32 b_area_tik_spike_top_UprightDefense[];
extern s32 b_area_tik_spiked_gloomba_DefenseTable[];
extern s32 b_area_tik_spiked_gloomba_StatusTable[];
extern EvtScript b_area_tik_spiny_EVS_CheckToppleAnim;
extern EvtScript b_area_tik_spiny_EVS_Idle;
extern EvtScript b_area_tik_spiny_EVS_ReturnHome;
extern u8 b_area_tik_spiny_FlipPosOffsets[];
extern s32 b_area_tik_spiny_SpinyBallAnims[];
extern s32 b_area_tik_spiny_ToppledDefense[];
extern s32 b_area_tik_spiny_UprightDefense[];
extern Stage b_area_tik_tik_01;
extern Stage b_area_tik_tik_02;
extern Stage b_area_tik_tik_03;
extern Stage b_area_tik_tik_04;
extern EvtScript b_area_tik_tik_05_EVS_PostBattle;
extern s32 b_area_tik_tik_05_ForegroundModels[];
extern EvtScript TTYD64_imp_1A_SpikeTop_Script_HandleEvent_8022C6A8_1A;
extern EvtScript TTYD64_imp_1A_BuzzyBeetle_Script_HandleEvent_80229718_1A;
extern EvtScript TTYD64_imp_1A_SpikedGloomba_Script_TakeTurn_802249EC_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_HandleEvent_8021FE4C_1A;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_HandleEvent_8021AE4C_1A;
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_TakeTurn_80227CE8_1A;
extern EvtScript TTYD64_imp_1A_Gloomba_Script_TakeTurn_80222F10_1A;
extern EvtScript TTYD64_imp_1A_Spiny_Script_HandleEvent_8022ED44_1A;
extern EvtScript TTYD64_imp_1A_Spiny_Script_TakeTurn_8022F810_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_TakeTurn_8021E174_1A;
extern EvtScript TTYD64_imp_1A_BuzzyBeetle_Script_TakeTurn_8022A47C_1A;
extern EvtScript TTYD64_imp_1A_SpikeTop_Script_TakeTurn_8022D444_1A;
extern EvtScript TTYD64_imp_1A_SpikeTop_Script_TakeTurn_8022DEFC_1A;
extern EvtScript TTYD64_imp_1A_BuzzyBeetle_Script_TakeTurn_8022AF34_1A;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_DarkKoopa_ShellAttack;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Darkparatroopa_ShellAttack;
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_TakeTurn_8022635C_1A;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_Idle_8021A5E4_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Idle_8021F5E4_1A;
extern EvtScript TTYD64_imp_1A_SpikedGloomba_Script_HandleEvent_802240A4_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_DarkParatroopa_DizzyAttack;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_DarkKoopa_DizzyAttack;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_HandleEvent_8021DA3C_1A;
extern EvtScript TTYD64_imp_1A_Gloomba_Script_HandleEvent_802226E4_1A;
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_HandleEvent_802274BC_1A;
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_HandleEvent_80225D68_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_8021EC2C_1A;
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_80226B74_1A;
extern EvtScript TTYD64_imp_1A_SpikeTop_Script_HandleEvent_8022C150_1A;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_8021CB70_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_80221B70_1A;
extern EvtScript TTYD64_imp_1A_BuzzyBeetle_Script_HandleEvent_802291C0_1A;
extern EvtScript TTYD64_imp_1A_SpikeTop_Script_8022BD1C_1A;
extern EvtScript TTYD64_imp_1A_BuzzyBeetle_Script_80228D8C_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Idle_8021D6AC_1A;
extern EvtScript TTYD64_imp_1A_SpikedGloomba_Script_Idle_80223DC8_1A;
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_Idle_802271E0_1A;
extern EvtScript TTYD64_imp_1A_Gloomba_Script_Idle_80222408_1A;
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_Idle_80225A34_1A;
extern EvtScript TTYD64_tik_Script_BeforeBattle_802335DC;
extern Battle TTYD64_tik_FormationTable[];
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_TakeTurn_8021D014_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_TakeTurn_80222014_1A;
extern EvtScript TTYD64_imp_1A_BuzzyBeetle_Script_Init_80228BAC_1A;
extern EvtScript TTYD64_imp_1A_SpikeTop_Script_Init_8022BB3C_1A;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_Init_8021A36C_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_8021F36C_1A;
extern s32 TTYD64_imp_1A_BuzzyBeetle_StatusTable_802289D8_1A[];
extern s32 TTYD64_imp_1A_Spiny_StatusTable_8022E9DC_1A[];
extern EvtScript TTYD64_tik_Script_80233540;
extern ActorPartBlueprint TTYD64_imp_1A_Paragloomba_PartsTable_80225880_1A[];
extern EvtScript TTYD64_imp_1A_Spiny_Script_Init_8022EAF8_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Init_8021D55C_1A;
extern FormationRow TTYD64_tik_Formation_0B[];
extern FormationRow TTYD64_tik_Formation_11[];
extern FormationRow TTYD64_tik_Formation_12[];
extern FormationRow TTYD64_tik_Formation_13[];
extern FormationRow TTYD64_tik_Formation_18[];
extern FormationRow TTYD64_tik_Formation_02[];
extern FormationRow TTYD64_tik_Formation_07[];
extern ActorPartBlueprint TTYD64_imp_1A_DarkParatroopa_PartsTable_8021D3BC_1A[];
extern FormationRow TTYD64_tik_Formation_0C[];
extern FormationRow TTYD64_tik_Formation_0F[];
extern FormationRow TTYD64_tik_Formation_10[];
extern FormationRow TTYD64_tik_Formation_15[];
extern FormationRow TTYD64_tik_Formation_17[];
extern FormationRow TTYD64_tik_Formation_01[];
extern FormationRow TTYD64_tik_Formation_04[];
extern FormationRow TTYD64_tik_Formation_05[];
extern FormationRow TTYD64_tik_Formation_03[];
extern FormationRow TTYD64_tik_Formation_09[];
extern FormationRow TTYD64_tik_Formation_06[];
extern s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A2D4_1A[];
extern s32 TTYD64_imp_1A_Paragloomba_IdleAnimations_80225938_1A[];
extern s32 TTYD64_imp_1A_Spiny_IdleAnimations_8022E96C_1A[];
extern s32 TTYD64_imp_1A_Paragloomba_IdleAnimations_802270FC_1A[];
extern s32 TTYD64_imp_1A_BuzzyBeetle_IdleAnimations_80228AD0_1A[];
extern s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A288_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F2D4_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F1F0_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D4E8_1A[];
extern s32 TTYD64_imp_1A_Gloomba_IdleAnimations_80222370_1A[];
extern s32 TTYD64_imp_1A_Gloomba_IdleAnimations_80222324_1A[];
extern s32 TTYD64_imp_1A_BuzzyBeetle_IdleAnimations_80228B1C_1A[];
extern s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A320_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D450_1A[];
extern s32 TTYD64_imp_1A_Paragloomba_IdleAnimations_80225984_1A[];
extern s32 TTYD64_imp_1A_SpikeTop_IdleAnimations_8022BAAC_1A[];
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_Init_802259E8_1A;
extern s32 TTYD64_imp_1A_SpikeTop_IdleAnimations_8022BA60_1A[];
extern s32 TTYD64_imp_1A_SpikedGloomba_IdleAnimations_80223D30_1A[];
extern s32 TTYD64_imp_1A_SpikedGloomba_IdleAnimations_80223CE4_1A[];
extern s32 TTYD64_imp_1A_Spiny_IdleAnimations_8022E920_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F23C_1A[];
extern s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A23C_1A[];
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_80227194_1A;
extern EvtScript TTYD64_imp_1A_SpikedGloomba_Script_Init_80223D7C_1A;
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D49C_1A[];
extern s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A1F0_1A[];
extern EvtScript TTYD64_imp_1A_Gloomba_Script_Init_802223BC_1A;
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F288_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F320_1A[];
extern s32 TTYD64_imp_1A_Paragloomba_IdleAnimations_80227148_1A[];
extern ActorPartBlueprint TTYD64_imp_1A_Spiny_PartsTable_8022EA88_1A[];
extern s32 TTYD64_imp_1A_SpikeTop_IdleAnimations_8022BAF8_1A[];
extern s32 TTYD64_imp_1A_BuzzyBeetle_IdleAnimations_80228B68_1A[];
extern FormationRow TTYD64_tik_Formation_0A[];
extern FormationRow TTYD64_tik_Formation_0D[];
extern FormationRow TTYD64_tik_Formation_0E[];
extern FormationRow TTYD64_tik_Formation_16[];
extern FormationRow TTYD64_tik_Formation_14[];
extern FormationRow TTYD64_tik_Formation_00[];
extern FormationRow TTYD64_tik_Formation_08[];
extern StageListRow TTYD64_tik_StageTable[];
extern ActorBlueprint TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba;
extern ActorBlueprint TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa;
extern ActorBlueprint TTYD64_imp_1A_BuzzyBeetle_1A_BuzzyBeetle;
extern ActorBlueprint TTYD64_imp_1A_Paragloomba_1A_Paragloomba;
extern ActorBlueprint TTYD64_imp_1A_Spiny_1A_Spiny;
extern ActorBlueprint TTYD64_imp_1A_SpikeTop_1A_SpikeTop;
extern ActorBlueprint TTYD64_imp_1A_Gloomba_1A_Gloomba;
extern ActorBlueprint TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa;
extern Stage TTYD64_tik_Stage_80233858;
extern ActorPartBlueprint TTYD64_imp_1A_Gloomba_PartsTable_802222D8_1A[];
extern ActorPartBlueprint TTYD64_imp_1A_DarkKoopa_PartsTable_8021A1A4_1A[];
extern ActorPartBlueprint TTYD64_imp_1A_BuzzyBeetle_PartsTable_80228A84_1A[];
extern ActorPartBlueprint TTYD64_imp_1A_SpikedGloomba_PartsTable_80223C98_1A[];
extern ActorPartBlueprint TTYD64_imp_1A_SpikeTop_PartsTable_8022BA14_1A[];
extern s32 TTYD64_imp_1A_Spiny_IdleAnimations_Ball_1A[];
API_CALLABLE(TTYD64_tik_Function_80219DB0);
API_CALLABLE(TTYD64_tik_Function_80219ED4);

API_CALLABLE(TTYD64_tik_Function_80219DB0) {
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

API_CALLABLE(TTYD64_tik_Function_80219ED4) {
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
EvtScript TTYD64_imp_1A_SpikeTop_Script_HandleEvent_8022C6A8_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_tik_spike_top_EVS_CheckToppleAnim)
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
            ExecWait(b_area_tik_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 8, 2)
            Call(SetTargetOffset, ACTOR_SELF, 1, 1, 20)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -3, -8)
            Call(SetActorVar, ACTOR_SELF, 9, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_tik_spike_top_ToppledDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_SpikeTop_IdleAnimations_8022BAF8_1A))
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
            UseBuf(Ref(b_area_tik_spike_top_FlipPosOffsets))
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
            ExecWait(b_area_tik_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_tik_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_tik_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_tik_spike_top_EVS_CheckToppleAnim)
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
EvtScript TTYD64_imp_1A_BuzzyBeetle_Script_HandleEvent_80229718_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330007)
            SetConst(LVar2, 0x330019)
            ExecWait(b_area_tik_buzzy_beetle_EVS_CheckToppleAnim)
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
            ExecWait(b_area_tik_buzzy_beetle_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 8, 2)
            Call(SetTargetOffset, ACTOR_SELF, 1, 0, 16)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
            Call(SetActorVar, ACTOR_SELF, 9, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_tik_buzzy_beetle_ToppledDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_BuzzyBeetle_IdleAnimations_80228B68_1A))
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
            UseBuf(Ref(b_area_tik_buzzy_beetle_FlipPosOffsets))
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
            ExecWait(b_area_tik_buzzy_beetle_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330007)
            SetConst(LVar2, 0x330019)
            ExecWait(b_area_tik_buzzy_beetle_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330007)
            SetConst(LVar2, 0x330019)
            ExecWait(b_area_tik_buzzy_beetle_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330007)
            SetConst(LVar2, 0x330019)
            ExecWait(b_area_tik_buzzy_beetle_EVS_CheckToppleAnim)
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
EvtScript TTYD64_imp_1A_SpikedGloomba_Script_TakeTurn_802249EC_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x270103)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x270101)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x270104)
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
                    Call(b_area_tik_spiked_gloomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x270104)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x27010A)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 5, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 7, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x270106)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x270104)
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
                Call(SetAnimation, ACTOR_SELF, 1, 0x270104)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x270109)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x270101)
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
                    Call(b_area_tik_spiked_gloomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x270104)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x270104)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Wait(1)
    EndSwitch
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 4, 32)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x270101)
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
            Call(GetOwnerTarget, LVar1, 0)
            Call(GetLastDamage, LVar1, LVar0)
            IfGt(LVar0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x27010B)
                Wait(15)
            Else
                Call(SetAnimation, ACTOR_SELF, 1, 0x270101)
                Wait(3)
            EndIf
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x270103)
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
EvtScript TTYD64_imp_1A_DarkParatroopa_Script_HandleEvent_8021FE4C_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    IfEq(LVar0, 1)
        Call(RemoveActorDecoration, ACTOR_SELF, 1, 1)
        Call(SetActorVar, ACTOR_SELF, 1, 0)
    EndIf
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000C)
            SetConst(LVar2, 0x29000D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000C)
            SetConst(LVar2, 0x29000D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000D)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(13)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetActorVar, ACTOR_SELF, 8, 2)
                CaseEq(1)
                    Call(SetActorVar, ACTOR_SELF, 8, 3)
            EndSwitch
            Call(SetActorVar, ACTOR_SELF, 9, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_tik_dark_paratroopa_ToppledDefenseTable))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F320_1A))
            Call(SetTargetOffset, ACTOR_SELF, 1, -5, 15)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, 0)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x29000B)
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
            UseBuf(Ref(b_area_tik_dark_paratroopa_FlipPosOffsets))
            Loop(22)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x29000F)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(0.5))
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x290004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x290007)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(GetStatusFlags, ACTOR_SELF, LVar0)
                    IfNotFlag(LVar0, 0x35D000)
                        Call(SetAnimation, ACTOR_SELF, 1, 0x290008)
                        Wait(10)
                    EndIf
                EndCaseGroup
                CaseOrEq(2)
                CaseOrEq(3)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x29000F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                EndCaseGroup
            EndSwitch
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290004)
                ExecWait(Ref(EVS_Enemy_ReturnHome))
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290002)
                ExecWait(Ref(EVS_Enemy_Recover))
            EndIf
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x290004)
                    SetConst(LVar2, 0x29000B)
                    ExecWait(Ref(EVS_Enemy_ScareAway))
                    Return
                EndCaseGroup
                CaseOrEq(2)
                CaseOrEq(3)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x29000F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                EndCaseGroup
            EndSwitch
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x290017)
                EndCaseGroup
                CaseOrEq(2)
                CaseOrEq(3)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x29000F)
                EndCaseGroup
            EndSwitch
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x290017)
                EndCaseGroup
                CaseOrEq(2)
                CaseOrEq(3)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x29000F)
                EndCaseGroup
            EndSwitch
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x290001)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                EndCaseGroup
                CaseOrEq(2)
                CaseOrEq(3)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x29000F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                EndCaseGroup
            EndSwitch
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_DarkKoopa_Script_HandleEvent_8021AE4C_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    IfEq(LVar0, 1)
        Call(RemoveActorDecoration, ACTOR_SELF, 1, 1)
        Call(SetActorVar, ACTOR_SELF, 1, 0)
    EndIf
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000C)
            SetConst(LVar2, 0x29000D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000C)
            SetConst(LVar2, 0x29000D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000D)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(13)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetActorVar, ACTOR_SELF, 8, 2)
                CaseEq(1)
                    Call(SetActorVar, ACTOR_SELF, 8, 3)
            EndSwitch
            Call(SetActorVar, ACTOR_SELF, 9, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_tik_dark_koopa_ToppledDefenseTable))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A320_1A))
            Call(SetTargetOffset, ACTOR_SELF, 1, -5, 15)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, 0)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x29000B)
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
            UseBuf(Ref(b_area_tik_dark_koopa_FlipPosOffsets))
            Loop(22)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x29000F)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(0.5))
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x290004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x290007)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(GetStatusFlags, ACTOR_SELF, LVar0)
                    IfNotFlag(LVar0, 0x35D000)
                        Call(SetAnimation, ACTOR_SELF, 1, 0x290008)
                        Wait(10)
                    EndIf
                EndCaseGroup
                CaseOrEq(2)
                CaseOrEq(3)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x29000F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                EndCaseGroup
            EndSwitch
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29000B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290004)
                ExecWait(Ref(EVS_Enemy_ReturnHome))
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290002)
                ExecWait(Ref(EVS_Enemy_Recover))
            EndIf
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x290004)
                    SetConst(LVar2, 0x29000B)
                    ExecWait(Ref(EVS_Enemy_ScareAway))
                    Return
                EndCaseGroup
                CaseOrEq(2)
                CaseOrEq(3)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x29000F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                EndCaseGroup
            EndSwitch
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x290017)
                EndCaseGroup
                CaseOrEq(2)
                CaseOrEq(3)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x29000F)
                EndCaseGroup
            EndSwitch
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x290017)
                EndCaseGroup
                CaseOrEq(2)
                CaseOrEq(3)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x29000F)
                EndCaseGroup
            EndSwitch
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x290001)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                EndCaseGroup
                CaseOrEq(2)
                CaseOrEq(3)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x29000F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                EndCaseGroup
            EndSwitch
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_Paragloomba_Script_TakeTurn_80227CE8_1A = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x260403)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260401)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260404)
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
                    Call(b_area_tik_paragloomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260404)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260408)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 5, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 7, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260405)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260404)
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
                Call(SetAnimation, ACTOR_SELF, 1, 0x260404)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260407)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x260401)
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
                    Call(b_area_tik_paragloomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260404)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x26040B)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Wait(1)
    EndSwitch
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 3, 32)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x260401)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x260401)
            Wait(3)
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260403)
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
EvtScript TTYD64_imp_1A_Gloomba_Script_TakeTurn_80222F10_1A = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x260403)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260401)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260404)
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
                    Call(b_area_tik_gloomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260404)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260408)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 5, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 7, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260405)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260404)
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
                Call(SetAnimation, ACTOR_SELF, 1, 0x260404)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260407)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x260401)
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
                    Call(b_area_tik_gloomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260404)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x26040B)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Wait(1)
    EndSwitch
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 3, 32)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x260401)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x260401)
            Wait(3)
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260403)
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
EvtScript TTYD64_imp_1A_Spiny_Script_HandleEvent_8022ED44_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0009)
            SetConst(LVar2, 0x4A000A)
            ExecWait(b_area_tik_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfNe(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A000B)
                SetConst(LVar2, 0x4A000C)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A000D)
                SetConst(LVar2, 0x4A000E)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            EndIf
        CaseEq(36)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfNe(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A000B)
                SetConst(LVar2, 0x4A000C)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A000C)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A000D)
                SetConst(LVar2, 0x4A000E)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A000E)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0009)
            SetConst(LVar2, 0x4A000A)
            ExecWait(b_area_tik_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0009)
            SetConst(LVar2, 0x4A000A)
            ExecWait(b_area_tik_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0009)
            SetConst(LVar2, 0x4A000A)
            ExecWait(b_area_tik_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(13)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfGt(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A0018)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(EnableIdleScript, ACTOR_SELF, 1)
                Call(UseIdleAnimation, ACTOR_SELF, 1)
                Return
            EndIf
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                Call(SetAnimation, ACTOR_SELF, 1, 0x4A000A)
            Else
                Call(SetAnimation, ACTOR_SELF, 1, 0x4A0016)
            EndIf
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(SetActorVar, ACTOR_SELF, 1, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_tik_spiny_ToppledDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_Spiny_IdleAnimations_8022E96C_1A))
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x200000, 0)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            UseBuf(Ref(b_area_tik_spiny_FlipPosOffsets))
            Loop(19)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Wait(20)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfGt(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A0018)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(EnableIdleScript, ACTOR_SELF, 1)
                Call(UseIdleAnimation, ACTOR_SELF, 1)
                Return
            EndIf
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0006)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x4A0007)
                    Wait(10)
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0002)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndSwitch
        EndCaseGroup
        CaseEq(27)
            Wait(10)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar0, 0x80000)
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 0)
                    Add(LVar0, 0)
                EndIf
                Add(LVar1, 8)
            Else
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 0)
                    Add(LVar0, -1)
                EndIf
                Add(LVar1, 22)
            EndIf
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(20)
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0009)
            SetConst(LVar2, 0x4A000A)
            ExecWait(b_area_tik_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0009)
            SetConst(LVar2, 0x4A000A)
            ExecWait(b_area_tik_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0001)
                    ExecWait(Ref(EVS_Enemy_Recover))
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0002)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndSwitch
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0004)
                    SetConst(LVar2, 0x4A0009)
                    ExecWait(Ref(EVS_Enemy_ScareAway))
                    Return
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0002)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndSwitch
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0004)
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0002)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0004)
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0002)
            EndSwitch
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
EvtScript TTYD64_imp_1A_Spiny_Script_TakeTurn_8022F810_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(GetActorVar, ACTOR_SELF, 1, LVar0)
        Sub(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 1, LVar0)
        IfGt(LVar0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4A0014)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
        Else
            Call(SetAnimation, ACTOR_SELF, 1, 0x4A0014)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(20)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0002)
            SetConst(LVar2, 0x4A0001)
            ExecWait(Ref(EVS_Enemy_FlipBackUp))
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_tik_spiny_UprightDefense))
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_Spiny_IdleAnimations_8022E920_1A))
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x200000, 1)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
        EndIf
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfGt(LVar0, 0)
        Call(SetActorVar, ACTOR_SELF, 2, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x4A001A)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x4A0001)
        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_tik_spiny_UprightDefense))
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_Spiny_IdleAnimations_8022E920_1A))
        Return
    Else
        Call(GetBattlePhase, LVar0)
        IfNe(LVar0, 1)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 30)
                Call(SetActorVar, ACTOR_SELF, 2, 1)
                Call(SetAnimation, ACTOR_SELF, 1, 0x4A0019)
                Wait(20)
                Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_dgb_tubba_blubba_DefenseTable))
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_Spiny_IdleAnimations_Ball_1A))
                Return
            EndIf
        EndIf
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, 1, 0x4A0019)
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 1, 0x4A0018)
        Wait(10)
    Else
        Wait(20)
    EndIf
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(10)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(5)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
    EndThread
    Call(EnableActorBlur, ACTOR_SELF, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 1, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x49000C)
    Wait(10)
    Call(PlaySoundAtPart, ACTOR_SELF, 2, 711)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(SetPartSounds, ACTOR_SELF, 2, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 4, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
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
            Call(AddGoalPos, ACTOR_SELF, -200, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(EnableActorBlur, ACTOR_SELF, 0)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_tik_spiny_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
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
            Call(SetAnimation, ACTOR_SELF, 2, 0x49000B)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Add(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Add(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(EnableActorBlur, ACTOR_SELF, 0)
            Call(YieldTurn)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_tik_spiny_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableActorBlur, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_DarkParatroopa_Script_TakeTurn_8021E174_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVar1, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 5)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetTargetActor, ACTOR_SELF, LVar1)
    Call(SetAnimation, ACTOR_SELF, 2, 0x2A0003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 40, 30, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -16, 0)
    Call(UseBattleCamPresetImmediately, 1)
    Wait(5)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 3, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8416)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 2, 0x2A0004)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(AddGoalPos, ACTOR_SELF, 6, 6, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
            Wait(6)
            Call(PlaySoundAtActor, ACTOR_SELF, 705)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(GetOwnerTarget, LVar3, 0)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Sub(LVar0, 25)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x2A000C)
            Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(4.0))
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
                Set(LVar0, 0)
                Loop(8)
                    Add(LVar0, 90)
                    IfGe(LVar0, 360)
                        Sub(LVar0, 360)
                    EndIf
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, -10, 0)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x2A0007)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x2A0007)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 30)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(b_area_tik_dark_paratroopa_EVS_ReturnHome)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 8416)
    Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x2A0004)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(AddGoalPos, ACTOR_SELF, 6, 6, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
    Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
    Wait(6)
    Call(PlaySoundAtActor, ACTOR_SELF, 705)
    Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
    Call(SetAnimation, ACTOR_SELF, 2, 0x2A000C)
    Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 40, 30, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x2A000D)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
                Set(LVar0, 0)
                Loop(12)
                    Sub(LVar0, 90)
                    IfLt(LVar0, 0)
                        Add(LVar0, 360)
                    EndIf
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, -10, 0)
                Call(SetAnimation, ACTOR_SELF, 2, 0x2A0001)
            EndThread
            Call(FlyToGoal, ACTOR_SELF, 0, 30, 0)
            Wait(10)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            ExecWait(b_area_tik_dark_paratroopa_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_BuzzyBeetle_Script_TakeTurn_8022A47C_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 16)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
    Call(b_area_tik_buzzy_beetle_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_BuzzyBeetle_Script_TakeTurn_8022AF34_1A))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_BuzzyBeetle_Script_HandleEvent_80229718_1A))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_BuzzyBeetle_IdleAnimations_80228AD0_1A))
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
EvtScript TTYD64_imp_1A_SpikeTop_Script_TakeTurn_8022D444_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 24)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
    Call(b_area_tik_spike_top_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_SpikeTop_Script_TakeTurn_8022DEFC_1A))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_SpikeTop_Script_HandleEvent_8022C6A8_1A))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_SpikeTop_IdleAnimations_8022BA60_1A))
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
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
EvtScript TTYD64_imp_1A_SpikeTop_Script_TakeTurn_8022DEFC_1A = {
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
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_tik_spike_top_UprightDefense))
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_SpikeTop_IdleAnimations_8022BA60_1A))
            Call(BindIdle, ACTOR_SELF, Ref(b_area_tik_spike_top_EVS_Idle))
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 16, 1)
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
EvtScript TTYD64_imp_1A_BuzzyBeetle_Script_TakeTurn_8022AF34_1A = {
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
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_tik_buzzy_beetle_UprightDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_BuzzyBeetle_IdleAnimations_80228AD0_1A))
            Call(BindIdle, ACTOR_SELF, Ref(b_area_tik_buzzy_beetle_EVS_Idle))
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
EvtScript TTYD64_imp_1A_DarkKoopa_Script_DarkKoopa_ShellAttack = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290006)
    Else
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290007)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x290006)
        Wait(10)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x40000000, 0, 3, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetStatusFlags, ACTOR_SELF, LVar5)
            Call(AddGoalPos, ACTOR_SELF, -40, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290008)
            Wait(8)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Wait(4)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x290015)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290016)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290017)
            Wait(6)
            Sub(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290017)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290001)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
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
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x40000000, 0xFFFF, 0, 4, 32)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x290008)
            Wait(8)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x290004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x290001)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Darkparatroopa_ShellAttack = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290006)
    Else
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290007)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x290006)
        Wait(10)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x40000000, 0, 3, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetStatusFlags, ACTOR_SELF, LVar5)
            Call(AddGoalPos, ACTOR_SELF, -40, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290008)
            Wait(8)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Wait(4)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x290015)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290016)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290017)
            Wait(6)
            Sub(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290017)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290001)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
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
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x40000000, 0xFFFF, 0, 3, 32)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x290008)
            Wait(8)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x290004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x290001)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_Paragloomba_Script_TakeTurn_8022635C_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x280304)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 2, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(UseBattleCamPreset, 66)
            Call(SetBattleCamDist, 300)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(SetBattleCamTargetingModes, -1, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8416)
            Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280305)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 705)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Sub(LVar0, 80)
            Set(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280305)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
            Thread
                Loop(4)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8415)
                    Wait(4)
                EndLoop
            EndThread
            Call(SetAnimation, ACTOR_SELF, 2, 0x280302)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Call(SetAnimationRate, ACTOR_SELF, 2, Float(3.0))
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(10)
            Call(SetAnimationRate, ACTOR_SELF, 2, Float(1.0))
            Call(UseBattleCamPreset, 2)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 2, 0x280304)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(b_area_tik_paragloomba_EVS_ReturnHome)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseDefault
            Wait(10)
            Call(UseBattleCamPreset, 66)
            Call(SetBattleCamDist, 300)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(SetBattleCamTargetingModes, -1, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8416)
            Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280305)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 705)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280305)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    EndSwitch
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280304)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Wait(5)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 2, 0x280304)
            ExecWait(b_area_tik_paragloomba_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_DarkKoopa_Script_Idle_8021A5E4_1A = {
    Label(0)
    Call(RandInt, 80, LVarA)
    Add(LVarA, 80)
    Loop(LVarA)
        Label(1)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_tik_dark_koopa_EVS_UpdateOffsets)
        IfEq(LVar0, 2)
            Wait(1)
            Goto(1)
        EndIf
        IfEq(LVar0, 3)
            Wait(1)
            Goto(1)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A23C_1A))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A2D4_1A))
    EndSwitch
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A1F0_1A))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A288_1A))
        CaseOrEq(2)
        CaseOrEq(3)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A320_1A))
        EndCaseGroup
    EndSwitch
    Loop(20)
        Label(2)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_tik_dark_koopa_EVS_UpdateOffsets)
        IfEq(LVar0, 2)
            Wait(1)
            Goto(2)
        EndIf
        IfEq(LVar0, 3)
            Wait(1)
            Goto(2)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(2)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A23C_1A))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A2D4_1A))
    EndSwitch
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A1F0_1A))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A288_1A))
        CaseOrEq(2)
        CaseOrEq(3)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A320_1A))
        EndCaseGroup
    EndSwitch
    Loop(50)
        Label(3)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_tik_dark_koopa_EVS_UpdateOffsets)
        IfEq(LVar0, 2)
            Wait(1)
            Goto(3)
        EndIf
        IfEq(LVar0, 3)
            Wait(1)
            Goto(3)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(3)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 1, 1)
            Thread
                Call(MakeLerp, 720, 0, 30, 10)
                Label(10)
                Call(UpdateLerp)
                Call(SetActorYaw, ACTOR_SELF, LVar0)
                IfEq(LVar1, 1)
                    Call(GetActorVar, ACTOR_SELF, 1, LVar2)
                    IfEq(LVar2, 1)
                        Wait(1)
                        Goto(10)
                    EndIf
                EndIf
                Call(SetActorVar, ACTOR_SELF, 1, 0)
                Call(SetActorYaw, ACTOR_SELF, 0)
            EndThread
            Wait(8)
            Call(AddActorDecoration, ACTOR_SELF, 1, 1, 7)
            Wait(15)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 1)
            Wait(8)
            Call(SetActorVar, ACTOR_SELF, 1, 0)
        CaseEq(0)
        CaseEq(2)
        CaseEq(3)
    EndSwitch
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Idle_8021F5E4_1A = {
    Label(0)
    Call(RandInt, 80, LVarA)
    Add(LVarA, 80)
    Loop(LVarA)
        Label(1)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_tik_dark_paratroopa_EVS_UpdateOffsets_Koopa)
        IfEq(LVar0, 2)
            Wait(1)
            Goto(1)
        EndIf
        IfEq(LVar0, 3)
            Wait(1)
            Goto(1)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F23C_1A))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F2D4_1A))
    EndSwitch
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F1F0_1A))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F288_1A))
        CaseOrEq(2)
        CaseOrEq(3)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F320_1A))
        EndCaseGroup
    EndSwitch
    Loop(20)
        Label(2)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_tik_dark_paratroopa_EVS_UpdateOffsets_Koopa)
        IfEq(LVar0, 2)
            Wait(1)
            Goto(2)
        EndIf
        IfEq(LVar0, 3)
            Wait(1)
            Goto(2)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(2)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F23C_1A))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F2D4_1A))
    EndSwitch
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F1F0_1A))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F288_1A))
        CaseOrEq(2)
        CaseOrEq(3)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F320_1A))
        EndCaseGroup
    EndSwitch
    Loop(50)
        Label(3)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_tik_dark_paratroopa_EVS_UpdateOffsets_Koopa)
        IfEq(LVar0, 2)
            Wait(1)
            Goto(3)
        EndIf
        IfEq(LVar0, 3)
            Wait(1)
            Goto(3)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(3)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 1, 1)
            Thread
                Call(MakeLerp, 720, 0, 30, 10)
                Label(10)
                Call(UpdateLerp)
                Call(SetActorYaw, ACTOR_SELF, LVar0)
                IfEq(LVar1, 1)
                    Call(GetActorVar, ACTOR_SELF, 1, LVar2)
                    IfEq(LVar2, 1)
                        Wait(1)
                        Goto(10)
                    EndIf
                EndIf
                Call(SetActorVar, ACTOR_SELF, 1, 0)
                Call(SetActorYaw, ACTOR_SELF, 0)
            EndThread
            Wait(8)
            Call(AddActorDecoration, ACTOR_SELF, 1, 1, 7)
            Wait(15)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 1)
            Wait(8)
            Call(SetActorVar, ACTOR_SELF, 1, 0)
        CaseEq(0)
        CaseEq(2)
        CaseEq(3)
    EndSwitch
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_SpikedGloomba_Script_HandleEvent_802240A4_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270106)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270107)
            SetConst(LVar2, 0x270108)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270107)
            SetConst(LVar2, 0x270108)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270108)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270106)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270106)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270105)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x27010C)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270106)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x270109)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x270101)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x27010C)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270105)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270101)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270106)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270105)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x270103)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270101)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270103)
            SetConst(LVar2, 0x270106)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270103)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270106)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(27)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x27010B)
            EndIf
            Wait(10)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                Add(LVar1, 10)
            Else
                Add(LVar1, 26)
            EndIf
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(20)
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x270101)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_DarkParatroopa_Script_DarkParatroopa_DizzyAttack = {
    Label(10)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Wait(1)
    IfEq(LVar0, 1)
        Goto(10)
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(AddGoalPos, ACTOR_SELF, 8, 0, 0)
    Else
        Call(AddGoalPos, ACTOR_SELF, 20, 0, 0)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x290004)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x290002)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x290007)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x290006)
    Wait(20)
    Call(PlaySoundAtActor, ACTOR_SELF, 8230)
    Call(AddActorDecoration, ACTOR_SELF, 1, 1, 7)
    Wait(40)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x40000000, 0, 0, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290008)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 1)
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290017)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290002)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Return
        EndCaseGroup
    EndSwitch
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0xFFFF, -0x7FFBFDC4, 0, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Thread
                Call(WasStatusInflicted, ACTOR_SELF, LVar0)
                IfEq(LVar0, 1)
                    Call(MakeLerp, 0, 1080, 30, 10)
                    Label(0)
                    Call(UpdateLerp)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(SetActorYaw, LVar1, LVar0)
                    Wait(1)
                    IfEq(LVar1, 1)
                        Goto(0)
                    EndIf
                EndIf
            EndThread
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290008)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 1)
            Wait(10)
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x290004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x290002)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_DarkKoopa_Script_DarkKoopa_DizzyAttack = {
    Label(10)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Wait(1)
    IfEq(LVar0, 1)
        Goto(10)
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(AddGoalPos, ACTOR_SELF, 8, 0, 0)
    Else
        Call(AddGoalPos, ACTOR_SELF, 20, 0, 0)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x290004)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x290002)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x290007)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x290006)
    Wait(20)
    Call(PlaySoundAtActor, ACTOR_SELF, 8230)
    Call(AddActorDecoration, ACTOR_SELF, 1, 1, 7)
    Wait(40)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x40000000, 0, 0, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290008)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 1)
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290017)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290002)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Return
        EndCaseGroup
    EndSwitch
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0xFFFF, -0x7FFBFDC4, 0, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Thread
                Call(WasStatusInflicted, ACTOR_SELF, LVar0)
                IfEq(LVar0, 1)
                    Call(MakeLerp, 0, 1080, 30, 10)
                    Label(0)
                    Call(UpdateLerp)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(SetActorYaw, LVar1, LVar0)
                    Wait(1)
                    IfEq(LVar1, 1)
                        Goto(0)
                    EndIf
                EndIf
            EndThread
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290008)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 1)
            Wait(10)
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x290004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x290002)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_DarkParatroopa_Script_HandleEvent_8021DA3C_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0007)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0007)
            ExecWait(Ref(EVS_Enemy_Hit))
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(GetEncounterTrigger, LVar0)
                IfEq(LVar0, 4)
                    ExecWait(TTYD64_imp_1A_DarkParatroopa_Script_8021EC2C_1A)
                EndIf
            EndIf
        CaseEq(11)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0007)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0007)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(14)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0008)
            SetConst(LVar2, 0x2A0009)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0008)
            SetConst(LVar2, 0x2A0009)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0009)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(12)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0007)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_imp_1A_DarkParatroopa_Script_8021EC2C_1A)
        CaseEq(15)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2A0008)
            SetConst(LVar1, 0x2A0009)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_imp_1A_DarkParatroopa_Script_8021EC2C_1A)
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2A0007)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2A0006)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(b_area_tik_dark_paratroopa_EVS_ReturnHome)
        CaseEq(38)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0007)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A000B)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A000B)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(GetEncounterTrigger, LVar0)
                IfEq(LVar0, 4)
                    ExecWait(TTYD64_imp_1A_DarkParatroopa_Script_8021EC2C_1A)
                EndIf
            EndIf
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0007)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(b_area_tik_dark_paratroopa_EVS_ReturnHome)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0003)
            SetConst(LVar2, 0x2A0007)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0007)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_Gloomba_Script_HandleEvent_802226E4_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260405)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260409)
            SetConst(LVar2, 0x26040A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260409)
            SetConst(LVar2, 0x26040A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26040A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260405)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260405)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260406)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26040E)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260405)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260407)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260401)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26040E)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260406)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260401)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260405)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260406)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260403)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260401)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260403)
            SetConst(LVar2, 0x260405)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260403)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260405)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x260401)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_Paragloomba_Script_HandleEvent_802274BC_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260405)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260409)
            SetConst(LVar2, 0x26040A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260409)
            SetConst(LVar2, 0x26040A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26040A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260405)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260405)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260406)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26040E)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260405)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260407)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260401)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26040E)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260406)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260401)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260405)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260406)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260403)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260401)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260403)
            SetConst(LVar2, 0x260405)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260403)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260405)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x260401)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_Paragloomba_Script_HandleEvent_80225D68_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280306)
            ExecWait(Ref(EVS_Enemy_Hit))
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(GetEncounterTrigger, LVar0)
                IfEq(LVar0, 4)
                    ExecWait(TTYD64_imp_1A_Paragloomba_Script_80226B74_1A)
                EndIf
            EndIf
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28030D)
            SetConst(LVar2, 0x28030E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28030D)
            SetConst(LVar2, 0x28030E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28030E)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(12)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280306)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_imp_1A_Paragloomba_Script_80226B74_1A)
        CaseEq(15)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28030D)
            SetConst(LVar2, 0x28030E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_imp_1A_Paragloomba_Script_80226B74_1A)
        CaseEq(47)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28030F)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280306)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(SetAnimation, ACTOR_SELF, 2, 0x28030C)
            ExecWait(b_area_tik_paragloomba_EVS_ReturnHome)
        CaseEq(38)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28030F)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280307)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280301)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280306)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280307)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            Call(SetAnimation, ACTOR_SELF, 2, 0x280304)
            ExecWait(b_area_tik_paragloomba_EVS_ReturnHome)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280301)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280304)
            SetConst(LVar2, 0x280306)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280304)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280306)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_DarkParatroopa_Script_8021EC2C_1A = {
    Call(SetPartDispOffset, ACTOR_SELF, 2, 0, 0, 0)
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetPartFlags, ACTOR_SELF, 2, 0x20005)
    Call(SetPartFlags, ACTOR_SELF, 3, 0x120004)
    Call(SetPartFlags, ACTOR_SELF, 1, 0x800004)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 8)
    Sub(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x29000B)
    Call(SetActorSounds, ACTOR_SELF, 2, 769, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfEq(LVarA, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 0)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
        Call(b_area_tik_dark_paratroopa_StartRumbleWithParams, 128, 7)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(0.2998046875))
        EndThread
        Call(ResetActorSounds, ACTOR_SELF, 2)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        Loop(10)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
            Wait(1)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
            Wait(1)
        EndLoop
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 0)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
        Thread
            Loop(10)
                Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
                Wait(1)
                Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
                Wait(1)
            EndLoop
            Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
        EndThread
        Call(b_area_tik_dark_paratroopa_StartRumbleWithParams, 150, 7)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(0.2998046875))
        EndThread
        Call(ResetActorSounds, ACTOR_SELF, 2)
    EndIf
    Call(GetIndexFromHome, ACTOR_SELF, LVar0)
    Mod(LVar0, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVar0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x290001)
    Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_tik_dark_paratroopa_StatusTable))
    Call(BindHandlePhase, ACTOR_SELF, 0)
    ExecWait(TTYD64_imp_1A_DarkParatroopa_Script_8021F36C_1A)
    Call(SetActorType, ACTOR_SELF, 5)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(ResetAllActorSounds, ACTOR_SELF)
    IfNe(LVarA, 0)
        Call(DispatchEvent, ACTOR_SELF, 13)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_Paragloomba_Script_80226B74_1A = {
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetPartFlags, ACTOR_SELF, 2, 0x20005)
    Call(SetPartFlags, ACTOR_SELF, 3, 0x120004)
    Call(SetPartFlags, ACTOR_SELF, 4, 0x120004)
    Call(SetPartFlags, ACTOR_SELF, 1, 0x800004)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(SetPartDispOffset, ACTOR_SELF, 3, -9, 7, -2)
    Call(SetPartPos, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
    Call(SetPartDispOffset, ACTOR_SELF, 4, 11, 7, -2)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    IfEq(LVar0, 15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x26040A)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x260405)
    EndIf
    Call(SetActorSounds, ACTOR_SELF, 2, 769, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(b_area_tik_paragloomba_StartRumbleWithParams, 100, 10)
    Thread
        Call(ShakeCam, 1, 0, 5, Float(0.2998046875))
    EndThread
    Call(ResetActorSounds, ACTOR_SELF, 2)
    Call(GetLastEvent, ACTOR_SELF, LVar3)
    IfEq(LVar3, 15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x260405)
        Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Add(LVar4, 10)
        Add(LVar5, 5)
        Call(PlayEffect_impl, 39, 0, LVar3, LVar4, LVar5, Float(1.0), 10, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Loop(10)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
        Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 1)
        Wait(1)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
        Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 0)
        Wait(1)
    EndLoop
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 1)
    Call(GetIndexFromHome, ACTOR_SELF, LVar0)
    Mod(LVar0, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVar0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260401)
    Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_tik_paragloomba_DownedFlyingStatusTable))
    Call(SetActorType, ACTOR_SELF, 2)
    ExecWait(TTYD64_imp_1A_Paragloomba_Script_80227194_1A)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_SpikeTop_Script_HandleEvent_8022C150_1A = {
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
            ExecWait(TTYD64_imp_1A_SpikeTop_Script_8022BD1C_1A)
        CaseEq(13)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_imp_1A_SpikeTop_Script_8022BD1C_1A)
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0019)
            SetConst(LVar2, 0x4D001A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_imp_1A_SpikeTop_Script_8022BD1C_1A)
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
                ExecWait(TTYD64_imp_1A_SpikeTop_Script_8022BD1C_1A)
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
EvtScript TTYD64_imp_1A_DarkKoopa_Script_8021CB70_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 9, LVar0)
    Sub(LVar0, 1)
    IfGt(LVar0, 0)
        Call(SetActorVar, ACTOR_SELF, 9, LVar0)
        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
        Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
        Wait(30)
        Call(SetAnimationRate, ACTOR_SELF, 1, Float(0.5))
        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
    Else
        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
        Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
        Wait(20)
        Call(SetAnimationRate, ACTOR_SELF, 1, Float(0.5))
        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
        Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 8321)
        Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
        Call(SetAnimation, ACTOR_SELF, 1, 0x29000F)
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
        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_tik_dark_koopa_UprightDefenseTable))
        Call(SetTargetOffset, ACTOR_SELF, 1, -4, 32)
        Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
        Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -4)
        Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
        Call(ResetActorSounds, ACTOR_SELF, 2)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Switch(LVar0)
            CaseEq(2)
                Call(SetActorVar, ACTOR_SELF, 8, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A1F0_1A))
            CaseEq(3)
                Call(SetActorVar, ACTOR_SELF, 8, 1)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A288_1A))
        EndSwitch
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_DarkParatroopa_Script_80221B70_1A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 9, LVar0)
    Sub(LVar0, 1)
    IfGt(LVar0, 0)
        Call(SetActorVar, ACTOR_SELF, 9, LVar0)
        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
        Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
        Wait(30)
        Call(SetAnimationRate, ACTOR_SELF, 1, Float(0.5))
        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
    Else
        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
        Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
        Wait(20)
        Call(SetAnimationRate, ACTOR_SELF, 1, Float(0.5))
        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
        Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 8321)
        Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
        Call(SetAnimation, ACTOR_SELF, 1, 0x29000F)
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
        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_tik_dark_paratroopa_UprightDefenseTable))
        Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
        Call(SetTargetOffset, ACTOR_SELF, 1, -4, 32)
        Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -4)
        Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
        Call(ResetActorSounds, ACTOR_SELF, 2)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Switch(LVar0)
            CaseEq(2)
                Call(SetActorVar, ACTOR_SELF, 8, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F1F0_1A))
            CaseEq(3)
                Call(SetActorVar, ACTOR_SELF, 8, 1)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F288_1A))
        EndSwitch
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_BuzzyBeetle_Script_HandleEvent_802291C0_1A = {
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
            ExecWait(TTYD64_imp_1A_BuzzyBeetle_Script_80228D8C_1A)
        CaseEq(13)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330013)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_imp_1A_BuzzyBeetle_Script_80228D8C_1A)
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x330018)
            SetConst(LVar2, 0x330018)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_imp_1A_BuzzyBeetle_Script_80228D8C_1A)
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
                ExecWait(TTYD64_imp_1A_BuzzyBeetle_Script_80228D8C_1A)
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
EvtScript TTYD64_imp_1A_SpikeTop_Script_8022BD1C_1A = {
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 2)
    Call(SetTargetOffset, ACTOR_SELF, 1, 1, 20)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -3, -8)
    Call(b_area_tik_spike_top_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_SpikeTop_Script_TakeTurn_8022DEFC_1A))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_SpikeTop_Script_HandleEvent_8022C6A8_1A))
    Call(SetActorVar, ACTOR_SELF, 9, 1)
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_tik_spike_top_ToppledDefense))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_SpikeTop_IdleAnimations_8022BAF8_1A))
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
EvtScript TTYD64_imp_1A_BuzzyBeetle_Script_80228D8C_1A = {
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 2)
    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 16)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
    Call(b_area_tik_buzzy_beetle_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_BuzzyBeetle_Script_TakeTurn_8022AF34_1A))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_BuzzyBeetle_Script_HandleEvent_80229718_1A))
    Call(SetActorVar, ACTOR_SELF, 9, 1)
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_tik_buzzy_beetle_ToppledDefense))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_BuzzyBeetle_IdleAnimations_80228B68_1A))
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
EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Idle_8021D6AC_1A = {
    Label(10)
    Call(RandInt, 80, LVar0)
    Add(LVar0, 80)
    Loop(LVar0)
        Label(0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_tik_dark_paratroopa_EVS_UpdateOffsets_Flying)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(0)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(0.599609375))
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D49C_1A))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, -5, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D450_1A))
    Loop(20)
        Label(1)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_tik_dark_paratroopa_EVS_UpdateOffsets_Flying)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(0.599609375))
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D49C_1A))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, -5, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D450_1A))
    Loop(40)
        Label(2)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_tik_dark_paratroopa_EVS_UpdateOffsets_Flying)
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
EvtScript TTYD64_imp_1A_SpikedGloomba_Script_Idle_80223DC8_1A = {
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_SpikedGloomba_IdleAnimations_80223D30_1A))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_SpikedGloomba_IdleAnimations_80223CE4_1A))
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_SpikedGloomba_IdleAnimations_80223D30_1A))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_SpikedGloomba_IdleAnimations_80223CE4_1A))
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
EvtScript TTYD64_imp_1A_Paragloomba_Script_Idle_802271E0_1A = {
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_Paragloomba_IdleAnimations_80227148_1A))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_Paragloomba_IdleAnimations_802270FC_1A))
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_Paragloomba_IdleAnimations_80227148_1A))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_Paragloomba_IdleAnimations_802270FC_1A))
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
EvtScript TTYD64_imp_1A_Gloomba_Script_Idle_80222408_1A = {
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_Gloomba_IdleAnimations_80222370_1A))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_Gloomba_IdleAnimations_80222324_1A))
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_Gloomba_IdleAnimations_80222370_1A))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_Gloomba_IdleAnimations_80222324_1A))
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
EvtScript TTYD64_imp_1A_Paragloomba_Script_Idle_80225A34_1A = {
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
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(0.599609375))
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_imp_1A_Paragloomba_IdleAnimations_80225984_1A))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, -5, 0)
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
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(0.599609375))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, -5, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_imp_1A_Paragloomba_IdleAnimations_80225938_1A))
    Loop(40)
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
EvtScript TTYD64_tik_Script_BeforeBattle_802335DC = {
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
        Exec(TTYD64_tik_Script_80233540)
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
        Exec(TTYD64_tik_Script_80233540)
    EndThread
    Return
    End
};
// clang-format on

Battle TTYD64_tik_FormationTable[] = {
    { .name = "\344\337\316\263\316\263x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_tik_Formation_00,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\316\263\316\263x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tik_Formation_01,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\316\263\316\263x\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_tik_Formation_02,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\316\263\316\263,\344\337\321\277\321\277x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tik_Formation_03,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\316\263\316\263,\310\262\341\303\310x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tik_Formation_04,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\316\263\316\263,\310\262\341\303\310,\344\337\316\263\316\263",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tik_Formation_05,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\316\263\316\263,\310\262\276\374x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tik_Formation_06,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\316\263\316\263,\310\262\276\374,\344\337\316\263\316\263,\310\262\276\374",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_tik_Formation_07,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\321\277\321\277x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_tik_Formation_08,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\321\277\321\277x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tik_Formation_09,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\257\352\334\374x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_tik_Formation_0A,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\257\352\334\374x\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_tik_Formation_0B,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\321\277\257\352x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tik_Formation_0C,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\321\277\257\352,\344\337\310\262\257\352",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_tik_Formation_0D,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\310\262\257\352x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_tik_Formation_0E,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\310\262\257\352,\344\337\257\352\334\374x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tik_Formation_0F,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\310\262\257\352,\341\303\310x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tik_Formation_10,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\310\262\257\352,\341\303\310,\344\337\310\262\257\352,\341\303\310",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_tik_Formation_11,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\344\337\310\262\257\352,\341\303\310,\344\337\321\277\257\352,\341\303\310",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_tik_Formation_12,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\310\262\341\303\310x\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_tik_Formation_13,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\310\262\341\303\310x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_tik_Formation_14,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\341\303\310,\344\337\310\262\257\352,\341\303\310",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tik_Formation_15,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\310\262\276\374x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_tik_Formation_16,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\310\262\276\374x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tik_Formation_17,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    { .name = "\310\262\276\374x\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_tik_Formation_18,
      .stage = &b_area_tik_tik_01,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_imp_1A_DarkKoopa_Script_TakeTurn_8021D014_1A = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 8, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_imp_1A_DarkKoopa_Script_DarkKoopa_ShellAttack)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 300)
                Call(SetActorVar, ACTOR_SELF, 8, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A1F0_1A))
            Else
                Call(SetActorVar, ACTOR_SELF, 8, 1)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A288_1A))
            EndIf
        CaseEq(1)
            ExecWait(TTYD64_imp_1A_DarkKoopa_Script_DarkKoopa_DizzyAttack)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 300)
                Call(SetActorVar, ACTOR_SELF, 8, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A1F0_1A))
            Else
                Call(SetActorVar, ACTOR_SELF, 8, 1)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A288_1A))
            EndIf
        CaseOrEq(2)
        CaseOrEq(3)
            ExecWait(TTYD64_imp_1A_DarkKoopa_Script_8021CB70_1A)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_DarkParatroopa_Script_TakeTurn_80222014_1A = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 8, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_imp_1A_DarkParatroopa_Script_Darkparatroopa_ShellAttack)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 300)
                Call(SetActorVar, ACTOR_SELF, 8, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F1F0_1A))
            Else
                Call(SetActorVar, ACTOR_SELF, 8, 1)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F288_1A))
            EndIf
        CaseEq(1)
            ExecWait(TTYD64_imp_1A_DarkParatroopa_Script_DarkParatroopa_DizzyAttack)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 300)
                Call(SetActorVar, ACTOR_SELF, 8, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F1F0_1A))
            Else
                Call(SetActorVar, ACTOR_SELF, 8, 1)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F288_1A))
            EndIf
        CaseOrEq(2)
        CaseOrEq(3)
            ExecWait(TTYD64_imp_1A_DarkParatroopa_Script_80221B70_1A)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_BuzzyBeetle_Script_Init_80228BAC_1A = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_tik_buzzy_beetle_EVS_Idle))
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 8, 0)
        Call(b_area_tik_buzzy_beetle_SetAbsoluteStatusOffsets, -10, 0, 10, 0)
        Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_BuzzyBeetle_Script_TakeTurn_8022A47C_1A))
        Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_BuzzyBeetle_Script_HandleEvent_802291C0_1A))
        Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 0)
    Else
        Call(SetActorVar, ACTOR_SELF, 8, 1)
        Call(SetTargetOffset, ACTOR_SELF, 1, 0, 16)
        Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
        Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_BuzzyBeetle_Script_TakeTurn_8022AF34_1A))
        Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_BuzzyBeetle_Script_HandleEvent_80229718_1A))
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_BuzzyBeetle_IdleAnimations_80228AD0_1A))
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
EvtScript TTYD64_imp_1A_SpikeTop_Script_Init_8022BB3C_1A = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_tik_spike_top_EVS_Idle))
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 8, 0)
        Call(b_area_tik_spike_top_SetAbsoluteStatusOffsets, -10, 0, 10, 0)
        Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_SpikeTop_Script_TakeTurn_8022D444_1A))
        Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_SpikeTop_Script_HandleEvent_8022C150_1A))
        Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 0)
    Else
        Call(SetActorVar, ACTOR_SELF, 8, 1)
        Call(SetTargetOffset, ACTOR_SELF, 1, 0, 24)
        Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
        Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_SpikeTop_Script_TakeTurn_8022DEFC_1A))
        Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_SpikeTop_Script_HandleEvent_8022C6A8_1A))
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_SpikeTop_IdleAnimations_8022BA60_1A))
        Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
        Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
    EndIf
    Call(HPBarToHome, ACTOR_SELF)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_DarkKoopa_Script_Init_8021A36C_1A = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_DarkKoopa_Script_TakeTurn_8021D014_1A))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_1A_DarkKoopa_Script_Idle_8021A5E4_1A))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_DarkKoopa_Script_HandleEvent_8021AE4C_1A))
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 300)
        Call(SetActorVar, ACTOR_SELF, 8, 0)
    Else
        Call(SetActorVar, ACTOR_SELF, 8, 1)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A288_1A))
        Call(SetAnimation, ACTOR_SELF, 1, 0x290002)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_DarkParatroopa_Script_8021F36C_1A = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_DarkParatroopa_Script_TakeTurn_80222014_1A))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_1A_DarkParatroopa_Script_Idle_8021F5E4_1A))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_DarkParatroopa_Script_HandleEvent_8021FE4C_1A))
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 300)
        Call(SetActorVar, ACTOR_SELF, 8, 0)
    Else
        Call(SetActorVar, ACTOR_SELF, 8, 1)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F288_1A))
        Call(SetAnimation, ACTOR_SELF, 1, 0x290002)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_1A_BuzzyBeetle_StatusTable_802289D8_1A[] = {
    1,  0, 2,  0, 6,  90, 9,  50, 7,  80, 4,  75, 3,  0, 11, 50, 5,  75, 10, 90, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, 0,  0,
};

s32 TTYD64_imp_1A_Spiny_StatusTable_8022E9DC_1A[] = {
    1,  0, 2,  0, 6,  60, 9,  50, 7,  75, 4,  75, 3,  0, 11, 50, 5,  75, 10, 75, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, 0,  0,
};

// clang-format off
EvtScript TTYD64_tik_Script_80233540 = {
    SetGroup(0)
    IfEq(LVar5, 1)
        IfEq(LVar6, 1)
            IfEq(LVar7, 1)
                IfEq(LVar8, 1)
                    Call(TTYD64_tik_Function_80219DB0)
                    Return
                EndIf
            EndIf
        EndIf
    EndIf
    Call(TTYD64_tik_Function_80219ED4)
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_imp_1A_Paragloomba_PartsTable_80225880_1A[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1A_Paragloomba_IdleAnimations_802270FC_1A,
        .defenseTable = b_area_tik_paragloomba_DownedDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1A_Paragloomba_IdleAnimations_80225938_1A,
        .defenseTable = b_area_tik_paragloomba_FlyingDefense,
        .eventFlags = 0x4000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -16, 24 },
        .opacity = 255,
        .idleAnimations = b_area_tik_paragloomba_LeftWingAnims,
        .defenseTable = b_area_tik_paragloomba_DownedDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -16, 24 },
        .opacity = 255,
        .idleAnimations = b_area_tik_paragloomba_RightWingAnims,
        .defenseTable = b_area_tik_paragloomba_DownedDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_imp_1A_Spiny_Script_Init_8022EAF8_1A = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_tik_spiny_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_Spiny_Script_TakeTurn_8022F810_1A))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_Spiny_Script_HandleEvent_8022ED44_1A))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Init_8021D55C_1A = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_DarkParatroopa_Script_TakeTurn_8021E174_1A))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_1A_DarkParatroopa_Script_Idle_8021D6AC_1A))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_DarkParatroopa_Script_HandleEvent_8021DA3C_1A))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_tik_dark_paratroopa_EVS_HandlePhase_Flying))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_tik_Formation_0B[] = {
    { .actor = &TTYD64_imp_1A_Gloomba_1A_Gloomba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GLOOMBA },
    { .actor = &TTYD64_imp_1A_Gloomba_1A_Gloomba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GLOOMBA },
    { .actor = &TTYD64_imp_1A_Gloomba_1A_Gloomba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GLOOMBA },
    { .actor = &TTYD64_imp_1A_Gloomba_1A_Gloomba,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GLOOMBA },
};

FormationRow TTYD64_tik_Formation_11[] = {
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
    { .actor = &TTYD64_imp_1A_BuzzyBeetle_1A_BuzzyBeetle,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
    { .actor = &TTYD64_imp_1A_BuzzyBeetle_1A_BuzzyBeetle,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
};

FormationRow TTYD64_tik_Formation_12[] = {
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
    { .actor = &TTYD64_imp_1A_BuzzyBeetle_1A_BuzzyBeetle,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_imp_1A_Paragloomba_1A_Paragloomba,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGLOOMBA },
    { .actor = &TTYD64_imp_1A_BuzzyBeetle_1A_BuzzyBeetle,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
};

FormationRow TTYD64_tik_Formation_13[] = {
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
};

FormationRow TTYD64_tik_Formation_18[] = {
    { .actor = &TTYD64_imp_1A_Spiny_1A_Spiny,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
    { .actor = &TTYD64_imp_1A_Spiny_1A_Spiny,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
    { .actor = &TTYD64_imp_1A_Spiny_1A_Spiny,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
    { .actor = &TTYD64_imp_1A_Spiny_1A_Spiny,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
};

FormationRow TTYD64_tik_Formation_02[] = {
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
};

FormationRow TTYD64_tik_Formation_07[] = {
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_imp_1A_Spiny_1A_Spiny,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_imp_1A_Spiny_1A_Spiny,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
};

ActorPartBlueprint TTYD64_imp_1A_DarkParatroopa_PartsTable_8021D3BC_1A[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 36 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F1F0_1A,
        .defenseTable = b_area_tik_dark_paratroopa_UprightDefenseTable,
        .eventFlags = 0x1000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -7 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -4, 36 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D450_1A,
        .defenseTable = b_area_tik_dark_paratroopa_defenseTable2,
        .eventFlags = 0x4000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 2, -14 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D4E8_1A,
        .defenseTable = b_area_tik_dark_paratroopa_UprightDefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_tik_Formation_0C[] = {
    { .actor = &TTYD64_imp_1A_Paragloomba_1A_Paragloomba,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGLOOMBA },
    { .actor = &TTYD64_imp_1A_Paragloomba_1A_Paragloomba,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGLOOMBA },
    { .actor = &TTYD64_imp_1A_Paragloomba_1A_Paragloomba,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGLOOMBA },
};

FormationRow TTYD64_tik_Formation_0F[] = {
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
    { .actor = &TTYD64_imp_1A_Gloomba_1A_Gloomba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GLOOMBA },
    { .actor = &TTYD64_imp_1A_Gloomba_1A_Gloomba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GLOOMBA },
};

FormationRow TTYD64_tik_Formation_10[] = {
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
    { .actor = &TTYD64_imp_1A_BuzzyBeetle_1A_BuzzyBeetle,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_imp_1A_BuzzyBeetle_1A_BuzzyBeetle,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
};

FormationRow TTYD64_tik_Formation_15[] = {
    { .actor = &TTYD64_imp_1A_BuzzyBeetle_1A_BuzzyBeetle,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
    { .actor = &TTYD64_imp_1A_BuzzyBeetle_1A_BuzzyBeetle,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
};

FormationRow TTYD64_tik_Formation_17[] = {
    { .actor = &TTYD64_imp_1A_Spiny_1A_Spiny,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
    { .actor = &TTYD64_imp_1A_Spiny_1A_Spiny,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
    { .actor = &TTYD64_imp_1A_Spiny_1A_Spiny,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
};

FormationRow TTYD64_tik_Formation_01[] = {
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
};

FormationRow TTYD64_tik_Formation_04[] = {
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
};

FormationRow TTYD64_tik_Formation_05[] = {
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
};

FormationRow TTYD64_tik_Formation_03[] = {
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
};

FormationRow TTYD64_tik_Formation_09[] = {
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
};

FormationRow TTYD64_tik_Formation_06[] = {
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_imp_1A_Spiny_1A_Spiny,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
    { .actor = &TTYD64_imp_1A_Spiny_1A_Spiny,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
};

s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A2D4_1A[] = {
    1,  0x290003, 7, 0x290000, 6, 0x290011, 9, 0x290003, 8, 0x290000,
    11, 0x290003, 5, 0x290000, 4, 0x290013, 3, 0x290013, 0,
};

s32 TTYD64_imp_1A_Paragloomba_IdleAnimations_80225938_1A[] = {
    1,  0x280301, 7, 0x280300, 6, 0x28030B, 9, 0x280301, 8, 0x280300,
    11, 0x280301, 5, 0x280300, 4, 0x28030C, 3, 0x28030C, 0,
};

s32 TTYD64_imp_1A_Spiny_IdleAnimations_8022E96C_1A[] = {
    1,  0x4A0002, 7, 0x4A0015, 6, 0x4A0011, 9, 0x4A0002, 8, 0x4A0015,
    11, 0x4A0002, 5, 0x4A0015, 4, 0x4A0013, 3, 0x4A0013, 0,
};

s32 TTYD64_imp_1A_Paragloomba_IdleAnimations_802270FC_1A[] = {
    1,  0x260401, 7, 0x260400, 6, 0x260408, 9, 0x260401, 8, 0x260400,
    11, 0x260401, 5, 0x260400, 4, 0x260407, 3, 0x260407, 0,
};

s32 TTYD64_imp_1A_BuzzyBeetle_IdleAnimations_80228AD0_1A[] = {
    1,  0x330001, 7, 0x330000, 6, 0x330009, 9, 0x330001, 8, 0x330000,
    11, 0x330001, 5, 0x330000, 4, 0x33000A, 3, 0x33000A, 0,
};

s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A288_1A[] = {
    1,  0x290002, 7, 0x290000, 6, 0x290011, 9, 0x290002, 8, 0x290000,
    11, 0x290002, 5, 0x290000, 4, 0x290013, 3, 0x290013, 0,
};

s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F2D4_1A[] = {
    1,  0x290003, 7, 0x290000, 6, 0x290011, 9, 0x290003, 8, 0x290000,
    11, 0x290003, 5, 0x290000, 4, 0x290013, 3, 0x290013, 0,
};

s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F1F0_1A[] = {
    1,  0x290001, 7, 0x290000, 6, 0x290011, 9, 0x290001, 8, 0x290000,
    11, 0x290001, 5, 0x290000, 4, 0x290013, 3, 0x290013, 0,
};

s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D4E8_1A[] = {
    1,  0x2A000F, 7, 0x2A0000, 6, 0x2A0012, 9, 0x2A0000, 8, 0x2A0000,
    11, 0x2A000F, 5, 0x2A0000, 4, 0x2A0013, 3, 0x2A0013, 0,
};

s32 TTYD64_imp_1A_Gloomba_IdleAnimations_80222370_1A[] = {
    1,  0x260403, 7, 0x260400, 6, 0x260408, 9, 0x260401, 8, 0x260400,
    11, 0x260403, 5, 0x260400, 4, 0x260407, 3, 0x260407, 0,
};

s32 TTYD64_imp_1A_Gloomba_IdleAnimations_80222324_1A[] = {
    1,  0x260401, 7, 0x260400, 6, 0x260408, 9, 0x260401, 8, 0x260400,
    11, 0x260401, 5, 0x260400, 4, 0x260407, 3, 0x260407, 0,
};

s32 TTYD64_imp_1A_BuzzyBeetle_IdleAnimations_80228B1C_1A[] = {
    1,  0x33000F, 7, 0x33000E, 6, 0x330014, 9, 0x33000F, 8, 0x33000E,
    11, 0x33000F, 5, 0x33000E, 4, 0x330015, 3, 0x330015, 0,
};

s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A320_1A[] = {
    1,  0x29000F, 7, 0x290010, 6, 0x290012, 9, 0x29000F, 8, 0x290010,
    11, 0x29000F, 5, 0x290010, 4, 0x290014, 3, 0x290014, 0,
};

s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D450_1A[] = {
    1,  0x2A0001, 7, 0x2A0000, 6, 0x2A0012, 9, 0x2A0000, 8, 0x2A0000,
    11, 0x2A0001, 5, 0x2A0000, 4, 0x2A0013, 3, 0x2A0013, 0,
};

s32 TTYD64_imp_1A_Paragloomba_IdleAnimations_80225984_1A[] = {
    1,  0x280304, 7, 0x280300, 6, 0x28030B, 9, 0x280301, 8, 0x280300,
    11, 0x280304, 5, 0x280300, 4, 0x28030C, 3, 0x28030C, 0,
};

s32 TTYD64_imp_1A_SpikeTop_IdleAnimations_8022BAAC_1A[] = {
    1,  0x4D0004, 7, 0x4D0001, 6, 0x4D001C, 9, 0x4D0004, 8, 0x4D0001,
    11, 0x4D0004, 5, 0x4D0001, 4, 0x4D001F, 3, 0x4D001F, 0,
};

// clang-format off
EvtScript TTYD64_imp_1A_Paragloomba_Script_Init_802259E8_1A = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_Paragloomba_Script_TakeTurn_8022635C_1A))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_1A_Paragloomba_Script_Idle_80225A34_1A))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_Paragloomba_Script_HandleEvent_80225D68_1A))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_1A_SpikeTop_IdleAnimations_8022BA60_1A[] = {
    1,  0x4D0003, 7, 0x4D0000, 6, 0x4D001B, 9, 0x4D0003, 8, 0x4D0000,
    11, 0x4D0003, 5, 0x4D0000, 4, 0x4D001E, 3, 0x4D001E, 0,
};

s32 TTYD64_imp_1A_SpikedGloomba_IdleAnimations_80223D30_1A[] = {
    1,  0x270103, 7, 0x270100, 6, 0x27010A, 9, 0x270101, 8, 0x270100,
    11, 0x270103, 5, 0x270100, 4, 0x270109, 3, 0x270109, 0,
};

s32 TTYD64_imp_1A_SpikedGloomba_IdleAnimations_80223CE4_1A[] = {
    1,  0x270101, 7, 0x270100, 6, 0x27010A, 9, 0x270101, 8, 0x270100,
    11, 0x270101, 5, 0x270100, 4, 0x270109, 3, 0x270109, 0,
};

s32 TTYD64_imp_1A_Spiny_IdleAnimations_8022E920_1A[] = {
    1,  0x4A0001, 7, 0x4A0000, 6, 0x4A0010, 9, 0x4A0001, 8, 0x4A0000,
    11, 0x4A0001, 5, 0x4A0000, 4, 0x4A0012, 3, 0x4A0012, 0,
};

s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F23C_1A[] = {
    1,  0x290003, 7, 0x290000, 6, 0x290011, 9, 0x290003, 8, 0x290000,
    11, 0x290003, 5, 0x290000, 4, 0x290013, 3, 0x290013, 0,
};

s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A23C_1A[] = {
    1,  0x290003, 7, 0x290000, 6, 0x290011, 9, 0x290003, 8, 0x290000,
    11, 0x290003, 5, 0x290000, 4, 0x290013, 3, 0x290013, 0,
};

// clang-format off
EvtScript TTYD64_imp_1A_Paragloomba_Script_80227194_1A = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_Paragloomba_Script_TakeTurn_80227CE8_1A))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_1A_Paragloomba_Script_Idle_802271E0_1A))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_Paragloomba_Script_HandleEvent_802274BC_1A))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1A_SpikedGloomba_Script_Init_80223D7C_1A = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_SpikedGloomba_Script_TakeTurn_802249EC_1A))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_1A_SpikedGloomba_Script_Idle_80223DC8_1A))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_SpikedGloomba_Script_HandleEvent_802240A4_1A))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D49C_1A[] = {
    1,  0x2A0001, 7, 0x2A0000, 6, 0x2A0012, 9, 0x2A0000, 8, 0x2A0000,
    11, 0x2A0001, 5, 0x2A0000, 4, 0x2A0013, 3, 0x2A0013, 0,
};

s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A1F0_1A[] = {
    1,  0x290001, 7, 0x290000, 6, 0x290011, 9, 0x290001, 8, 0x290000,
    11, 0x290001, 5, 0x290000, 4, 0x290013, 3, 0x290013, 0,
};

// clang-format off
EvtScript TTYD64_imp_1A_Gloomba_Script_Init_802223BC_1A = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1A_Gloomba_Script_TakeTurn_80222F10_1A))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_1A_Gloomba_Script_Idle_80222408_1A))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1A_Gloomba_Script_HandleEvent_802226E4_1A))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F288_1A[] = {
    1,  0x290002, 7, 0x290000, 6, 0x290011, 9, 0x290002, 8, 0x290000,
    11, 0x290002, 5, 0x290000, 4, 0x290013, 3, 0x290013, 0,
};

s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F320_1A[] = {
    1,  0x29000F, 7, 0x290010, 6, 0x290012, 9, 0x29000F, 8, 0x290010,
    11, 0x29000F, 5, 0x290010, 4, 0x290014, 3, 0x290014, 0,
};

s32 TTYD64_imp_1A_Paragloomba_IdleAnimations_80227148_1A[] = {
    1,  0x260403, 7, 0x260400, 6, 0x260408, 9, 0x260401, 8, 0x260400,
    11, 0x260403, 5, 0x260400, 4, 0x260407, 3, 0x260407, 0,
};

ActorPartBlueprint TTYD64_imp_1A_Spiny_PartsTable_8022EA88_1A[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1A_Spiny_IdleAnimations_8022E920_1A,
        .defenseTable = b_area_tik_spiny_UprightDefense,
        .eventFlags = 0x201000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -4 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_tik_spiny_SpinyBallAnims,
        .defenseTable = b_area_tik_spiny_UprightDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_imp_1A_SpikeTop_IdleAnimations_8022BAF8_1A[] = {
    1, 0x4D0005, 7, 0x4D0002, 6, 0x4D001D, 9, 0x4D0005, 8, 0x4D0002, 11, 0x4D0005, 4, 0x4D0020, 3, 0x4D0020, 0,
};

s32 TTYD64_imp_1A_BuzzyBeetle_IdleAnimations_80228B68_1A[] = {
    1, 0x330002, 7, 0x33001A, 6, 0x33001B, 9, 0x330002, 8, 0x33001A, 11, 0x330002, 4, 0x33001C, 3, 0x33001C, 0,
};

FormationRow TTYD64_tik_Formation_0A[] = {
    { .actor = &TTYD64_imp_1A_Gloomba_1A_Gloomba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GLOOMBA },
    { .actor = &TTYD64_imp_1A_Gloomba_1A_Gloomba,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GLOOMBA },
};

FormationRow TTYD64_tik_Formation_0D[] = {
    { .actor = &TTYD64_imp_1A_Paragloomba_1A_Paragloomba,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGLOOMBA },
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
};

FormationRow TTYD64_tik_Formation_0E[] = {
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
};

FormationRow TTYD64_tik_Formation_16[] = {
    { .actor = &TTYD64_imp_1A_Spiny_1A_Spiny,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
    { .actor = &TTYD64_imp_1A_Spiny_1A_Spiny,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
};

FormationRow TTYD64_tik_Formation_14[] = {
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
};

FormationRow TTYD64_tik_Formation_00[] = {
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
};

FormationRow TTYD64_tik_Formation_08[] = {
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
};

StageListRow TTYD64_tik_StageTable[] = {
    { .name = "tik_01", .stage = &b_area_tik_tik_01 },         { .name = "tik_02", .stage = &b_area_tik_tik_02 },
    { .name = "tik_03", .stage = &b_area_tik_tik_03 },         { .name = "tik_04", .stage = &b_area_tik_tik_04 },
    { .name = "tik_05", .stage = &TTYD64_tik_Stage_80233858 }, {},
};

ActorBlueprint TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x04,
    .level = 12,
    .partCount = 1,
    .partsData = TTYD64_imp_1A_SpikedGloomba_PartsTable_80223C98_1A,
    .initScript = &TTYD64_imp_1A_SpikedGloomba_Script_Init_80223D7C_1A,
    .statusTable = b_area_tik_spiked_gloomba_StatusTable,
    .escapeChance = 65,
    .airLiftChance = 90,
    .hurricaneChance = 85,
    .spookChance = 75,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 24, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa = {
    .flags = 0x200,
    .maxHP = 8,
    .type = 0x06,
    .level = 18,
    .partCount = 3,
    .partsData = TTYD64_imp_1A_DarkParatroopa_PartsTable_8021D3BC_1A,
    .initScript = &TTYD64_imp_1A_DarkParatroopa_Script_Init_8021D55C_1A,
    .statusTable = b_area_tik_dark_paratroopa_FlyingStatusTable,
    .escapeChance = 50,
    .airLiftChance = 90,
    .hurricaneChance = 80,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 2,
    .size = { 50, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 29 },
    .statusTextOffset = { 8, 30 },
};

ActorBlueprint TTYD64_imp_1A_BuzzyBeetle_1A_BuzzyBeetle = {
    .flags = 0x800,
    .maxHP = 3,
    .type = 0x17,
    .level = 10,
    .partCount = 1,
    .partsData = TTYD64_imp_1A_BuzzyBeetle_PartsTable_80228A84_1A,
    .initScript = &TTYD64_imp_1A_BuzzyBeetle_Script_Init_80228BAC_1A,
    .statusTable = TTYD64_imp_1A_BuzzyBeetle_StatusTable_802289D8_1A,
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

ActorBlueprint TTYD64_imp_1A_Paragloomba_1A_Paragloomba = {
    .flags = 0x200,
    .maxHP = 7,
    .type = 0x03,
    .level = 11,
    .partCount = 4,
    .partsData = TTYD64_imp_1A_Paragloomba_PartsTable_80225880_1A,
    .initScript = &TTYD64_imp_1A_Paragloomba_Script_Init_802259E8_1A,
    .statusTable = b_area_tik_paragloomba_FlyingStatusTable,
    .escapeChance = 65,
    .airLiftChance = 95,
    .hurricaneChance = 90,
    .spookChance = 80,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 36, 26 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_1A_Spiny_1A_Spiny = {
    .flags = 0x0,
    .maxHP = 5,
    .type = 0x2F,
    .level = 19,
    .partCount = 2,
    .partsData = TTYD64_imp_1A_Spiny_PartsTable_8022EA88_1A,
    .initScript = &TTYD64_imp_1A_Spiny_Script_Init_8022EAF8_1A,
    .statusTable = TTYD64_imp_1A_Spiny_StatusTable_8022E9DC_1A,
    .escapeChance = 60,
    .airLiftChance = 75,
    .hurricaneChance = 75,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 24, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_1A_SpikeTop_1A_SpikeTop = {
    .flags = 0x800,
    .maxHP = 5,
    .type = 0x2C,
    .level = 17,
    .partCount = 1,
    .partsData = TTYD64_imp_1A_SpikeTop_PartsTable_8022BA14_1A,
    .initScript = &TTYD64_imp_1A_SpikeTop_Script_Init_8022BB3C_1A,
    .statusTable = b_area_tik_spike_top_StatusTable,
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

ActorBlueprint TTYD64_imp_1A_Gloomba_1A_Gloomba = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x02,
    .level = 11,
    .partCount = 1,
    .partsData = TTYD64_imp_1A_Gloomba_PartsTable_802222D8_1A,
    .initScript = &TTYD64_imp_1A_Gloomba_Script_Init_802223BC_1A,
    .statusTable = b_area_tik_gloomba_StatusTable,
    .escapeChance = 70,
    .airLiftChance = 90,
    .hurricaneChance = 85,
    .spookChance = 80,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 24, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x05,
    .level = 18,
    .partCount = 1,
    .partsData = TTYD64_imp_1A_DarkKoopa_PartsTable_8021A1A4_1A,
    .initScript = &TTYD64_imp_1A_DarkKoopa_Script_Init_8021A36C_1A,
    .statusTable = b_area_tik_dark_koopa_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 85,
    .hurricaneChance = 75,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 2,
    .size = { 28, 36 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 32 },
    .statusTextOffset = { 5, 32 },
};

Stage TTYD64_tik_Stage_80233858 = {
    .texture = "tik_tex",
    .shape = "tik_bt05_shape",
    .hit = "tik_bt05_hit",
    .preBattle = &TTYD64_tik_Script_BeforeBattle_802335DC,
    .postBattle = &b_area_tik_tik_05_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = b_area_tik_tik_05_ForegroundModels,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorPartBlueprint TTYD64_imp_1A_Gloomba_PartsTable_802222D8_1A[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1A_Gloomba_IdleAnimations_80222324_1A,
        .defenseTable = b_area_tik_gloomba_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1A_DarkKoopa_PartsTable_8021A1A4_1A[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 36 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A1F0_1A,
        .defenseTable = b_area_tik_dark_koopa_UprightDefenseTable,
        .eventFlags = 0x1000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -7 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1A_BuzzyBeetle_PartsTable_80228A84_1A[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 16 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1A_BuzzyBeetle_IdleAnimations_80228B1C_1A,
        .defenseTable = b_area_tik_buzzy_beetle_UprightDefense,
        .eventFlags = 0x1000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 1, 7 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1A_SpikedGloomba_PartsTable_80223C98_1A[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1A_SpikedGloomba_IdleAnimations_80223CE4_1A,
        .defenseTable = b_area_tik_spiked_gloomba_DefenseTable,
        .eventFlags = 0x10,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1A_SpikeTop_PartsTable_8022BA14_1A[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1A_SpikeTop_IdleAnimations_8022BAAC_1A,
        .defenseTable = b_area_tik_spike_top_UprightDefense,
        .eventFlags = 0x1010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 14 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_imp_1A_Spiny_IdleAnimations_Ball_1A[] = {
    1,
    0x4A0018,
    0,
};

void TTYD64_InstallBattles_tik(void) {
    Mod_SetBattleList("TTYD64", 0x1A, TTYD64_tik_FormationTable);
    Mod_SetStageList("TTYD64", 0x1A, TTYD64_tik_StageTable);
}
