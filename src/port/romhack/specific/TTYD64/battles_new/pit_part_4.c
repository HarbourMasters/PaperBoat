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
#include "battles_new.h"

extern EvtScript b_area_kmr_part_1_kmr_02_EVS_PostBattle;
extern EvtScript b_area_kmr_part_3_kpa_13_EVS_PreBattle;
API_CALLABLE(EnableGroup);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetSpriteShading);
extern ActorPartBlueprint TTYD64_arn_hyper_cleft_ActorParts[];
extern EvtScript TTYD64_arn_hyper_cleft_EVS_Attack_Tackle;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_FlipOver;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_HandleEvent;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_Init;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_Move_Charge;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_TakeTurn;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_TryGettingUp;
extern s32 TTYD64_arn_hyper_cleft_HyperAnims[];
extern s32 TTYD64_arn_hyper_cleft_StatusTable[];
extern s32 TTYD64_arn_hyper_cleft_ToppledAnims[];
extern s32 TTYD64_arn_hyper_cleft_UprightAnims[];
extern ActorPartBlueprint TTYD64_arn_hyper_goomba_ActorParts[];
extern EvtScript TTYD64_arn_hyper_goomba_EVS_Attack_Headbonk;
extern EvtScript TTYD64_arn_hyper_goomba_EVS_HandleEvent;
extern EvtScript TTYD64_arn_hyper_goomba_EVS_Idle;
extern EvtScript TTYD64_arn_hyper_goomba_EVS_Move_Charge;
extern EvtScript TTYD64_arn_hyper_goomba_EVS_TakeTurn;
extern s32 TTYD64_arn_hyper_goomba_HyperAnims[];
extern s32 TTYD64_arn_hyper_goomba_ShuffleAnims[];
extern s32 TTYD64_arn_hyper_goomba_StatusTable[];
extern ActorPartBlueprint TTYD64_arn_hyper_paragoomba_ActorParts[];
extern s32 TTYD64_arn_hyper_paragoomba_ChargedFlyingAnims[];
extern s32 TTYD64_arn_hyper_paragoomba_DownedAnims[];
extern s32 TTYD64_arn_hyper_paragoomba_DownedAnims_80227C08[];
extern s32 TTYD64_arn_hyper_paragoomba_DownedChargedAnims[];
extern s32 TTYD64_arn_hyper_paragoomba_DownedShuffleAnims[];
extern s32 TTYD64_arn_hyper_paragoomba_DownedStatusTable[];
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Attack_ChargedDive;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Attack_Headbonk;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Attack_SkyDive;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Downed_HandleEvent;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Downed_Idle;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Downed_Move_Charge;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Downed_TakeTurn;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Flying_TakeTurn;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_HandleEvent;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Idle;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Init;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Init_80227010;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_KnockDown;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_KnockDown_Init;
extern s32 TTYD64_arn_hyper_paragoomba_FlyingAnims[];
extern s32 TTYD64_arn_hyper_paragoomba_FlyingShuffleAnims[];
extern s32 TTYD64_arn_hyper_paragoomba_FlyingStatusTable[];
extern ActorPartBlueprint TTYD64_dgb_clubba_ActorParts[];
extern s32 TTYD64_dgb_clubba_DefaultAnims[];
extern EvtScript TTYD64_dgb_clubba_EVS_Init;
extern EvtScript TTYD64_dgb_clubba_EVS_TakeTurn;
extern s32 TTYD64_dgb_clubba_StatusTable[];
extern ActorBlueprint TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa;
extern s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A1F0_1A[];
extern s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A23C_1A[];
extern s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A288_1A[];
extern s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A2D4_1A[];
extern s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A320_1A[];
extern ActorPartBlueprint TTYD64_imp_1A_DarkKoopa_PartsTable_8021A1A4_1A[];
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_8021CB70_1A;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_DarkKoopa_DizzyAttack;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_DarkKoopa_ShellAttack;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_HandleEvent_8021AE4C_1A;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_Idle_8021A5E4_1A;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_Init_8021A36C_1A;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_TakeTurn_8021D014_1A;
extern Battle TTYD64_pit_part_4_FormationTable[];
extern EvtScript TTYD64_pit_part_4_Script_BeforeBattle_Pit;
extern FormationRow TTYD64_pit_part_4_Formation_Pit35_3[];
extern FormationRow TTYD64_pit_part_4_Formation_Pit33_38_2[];
extern FormationRow TTYD64_pit_part_4_Formation_Pit33_38_3[];
extern FormationRow TTYD64_pit_part_4_Formation_Pit31_36_3[];
extern FormationRow TTYD64_pit_part_4_Formation_Pit31_36_2[];
extern FormationRow TTYD64_pit_part_4_Formation_Pit32_37_1[];
extern FormationRow TTYD64_pit_part_4_Formation_Pit32_37_3[];
extern FormationRow TTYD64_pit_part_4_Formation_Pit32_37_2[];
extern FormationRow TTYD64_pit_part_4_Formation_Pit35_2[];
extern FormationRow TTYD64_pit_part_4_Formation_Pit34_39_3[];
extern FormationRow TTYD64_pit_part_4_Formation_Pit34_39_2[];
extern FormationRow TTYD64_pit_part_4_Formation_Pit34_39_1[];
extern FormationRow TTYD64_pit_part_4_Formation_Pit31_36_1[];
extern FormationRow TTYD64_pit_part_4_Formation_Pit35_1[];
extern FormationRow TTYD64_pit_part_4_Formation_Pit33_38_1[];
extern Stage TTYD64_pit_part_4_Stage_Pit1;
extern Stage TTYD64_pit_part_4_Stage_Pit2;
extern ActorBlueprint TTYD64_pit_part_4_imp_0E_HyperCleft_0E_HyperCleft;
extern ActorBlueprint TTYD64_pit_part_4_imp_0F_Clubba_0F_Clubba;
extern ActorBlueprint TTYD64_pit_part_4_imp_0E_HyperGoomba_0E_HyperGoomba;
extern ActorBlueprint TTYD64_pit_part_4_imp_0E_HyperParagoomba_0E_HyperParagoomba;
extern StageListRow TTYD64_pit_part_4_StageTable[];

Battle TTYD64_pit_part_4_FormationTable[] = {
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_4_Formation_Pit31_36_1,
      .stage = &TTYD64_pit_part_4_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_4_Formation_Pit31_36_2,
      .stage = &TTYD64_pit_part_4_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_4_Formation_Pit31_36_3,
      .stage = &TTYD64_pit_part_4_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_4_Formation_Pit32_37_1,
      .stage = &TTYD64_pit_part_4_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_4_Formation_Pit32_37_2,
      .stage = &TTYD64_pit_part_4_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_4_Formation_Pit32_37_3,
      .stage = &TTYD64_pit_part_4_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_4_Formation_Pit33_38_1,
      .stage = &TTYD64_pit_part_4_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_4_Formation_Pit33_38_2,
      .stage = &TTYD64_pit_part_4_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_4_Formation_Pit33_38_3,
      .stage = &TTYD64_pit_part_4_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_4_Formation_Pit34_39_1,
      .stage = &TTYD64_pit_part_4_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_4_Formation_Pit34_39_2,
      .stage = &TTYD64_pit_part_4_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_4_Formation_Pit34_39_3,
      .stage = &TTYD64_pit_part_4_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_4_Formation_Pit35_1,
      .stage = &TTYD64_pit_part_4_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_4_Formation_Pit35_2,
      .stage = &TTYD64_pit_part_4_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_4_Formation_Pit35_3,
      .stage = &TTYD64_pit_part_4_Stage_Pit1,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_pit_part_4_Script_BeforeBattle_Pit = {
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

FormationRow TTYD64_pit_part_4_Formation_Pit35_3[] = {
    { .actor = &TTYD64_pit_part_4_imp_0F_Clubba_0F_Clubba,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
    { .actor = &TTYD64_pit_part_4_imp_0F_Clubba_0F_Clubba,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
    { .actor = &TTYD64_pit_part_4_imp_0F_Clubba_0F_Clubba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
    { .actor = &TTYD64_pit_part_4_imp_0F_Clubba_0F_Clubba,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
};

FormationRow TTYD64_pit_part_4_Formation_Pit33_38_2[] = {
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperCleft_0E_HyperCleft,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperCleft_0E_HyperCleft,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
};

FormationRow TTYD64_pit_part_4_Formation_Pit33_38_3[] = {
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperCleft_0E_HyperCleft,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperCleft_0E_HyperCleft,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperCleft_0E_HyperCleft,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperCleft_0E_HyperCleft,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
};

FormationRow TTYD64_pit_part_4_Formation_Pit31_36_3[] = {
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperGoomba_0E_HyperGoomba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperGoomba_0E_HyperGoomba,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
};

FormationRow TTYD64_pit_part_4_Formation_Pit31_36_2[] = {
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_pit_part_4_imp_0F_Clubba_0F_Clubba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
    { .actor = &TTYD64_pit_part_4_imp_0F_Clubba_0F_Clubba,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
};

FormationRow TTYD64_pit_part_4_Formation_Pit32_37_1[] = {
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperParagoomba_0E_HyperParagoomba,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperParagoomba_0E_HyperParagoomba,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
};

FormationRow TTYD64_pit_part_4_Formation_Pit32_37_3[] = {
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperParagoomba_0E_HyperParagoomba,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperParagoomba_0E_HyperParagoomba,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperParagoomba_0E_HyperParagoomba,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
};

FormationRow TTYD64_pit_part_4_Formation_Pit32_37_2[] = {
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperParagoomba_0E_HyperParagoomba,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperParagoomba_0E_HyperParagoomba,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperCleft_0E_HyperCleft,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
};

FormationRow TTYD64_pit_part_4_Formation_Pit35_2[] = {
    { .actor = &TTYD64_pit_part_4_imp_0F_Clubba_0F_Clubba,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
    { .actor = &TTYD64_pit_part_4_imp_0F_Clubba_0F_Clubba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
};

FormationRow TTYD64_pit_part_4_Formation_Pit34_39_3[] = {
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperGoomba_0E_HyperGoomba,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperGoomba_0E_HyperGoomba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperGoomba_0E_HyperGoomba,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
};

FormationRow TTYD64_pit_part_4_Formation_Pit34_39_2[] = {
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperGoomba_0E_HyperGoomba,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperGoomba_0E_HyperGoomba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
};

FormationRow TTYD64_pit_part_4_Formation_Pit34_39_1[] = {
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperGoomba_0E_HyperGoomba,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_pit_part_4_imp_0F_Clubba_0F_Clubba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
    { .actor = &TTYD64_pit_part_4_imp_0F_Clubba_0F_Clubba,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
};

FormationRow TTYD64_pit_part_4_Formation_Pit31_36_1[] = {
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKKOOPA },
};

FormationRow TTYD64_pit_part_4_Formation_Pit35_1[] = {
    { .actor = &TTYD64_pit_part_4_imp_0F_Clubba_0F_Clubba,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperCleft_0E_HyperCleft,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
};

FormationRow TTYD64_pit_part_4_Formation_Pit33_38_1[] = {
    { .actor = &TTYD64_pit_part_4_imp_0E_HyperCleft_0E_HyperCleft,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
    { .actor = &TTYD64_pit_part_4_imp_0F_Clubba_0F_Clubba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
};

Stage TTYD64_pit_part_4_Stage_Pit1 = {
    .texture = "tik_tex",
    .shape = "pit_bt01_shape",
    .hit = "pit_bt01_hit",
    .preBattle = &TTYD64_pit_part_4_Script_BeforeBattle_Pit,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

Stage TTYD64_pit_part_4_Stage_Pit2 = {
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

ActorBlueprint TTYD64_pit_part_4_imp_0E_HyperCleft_0E_HyperCleft = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x1D,
    .level = 15,
    .partCount = 1,
    .partsData = TTYD64_arn_hyper_cleft_ActorParts,
    .initScript = &TTYD64_arn_hyper_cleft_EVS_Init,
    .statusTable = TTYD64_arn_hyper_cleft_StatusTable,
    .escapeChance = 70,
    .airLiftChance = 30,
    .hurricaneChance = 30,
    .spookChance = 30,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 2,
    .size = { 44, 36 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_pit_part_4_imp_0F_Clubba_0F_Clubba = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x1E,
    .level = 13,
    .partCount = 1,
    .partsData = TTYD64_dgb_clubba_ActorParts,
    .initScript = &TTYD64_dgb_clubba_EVS_Init,
    .statusTable = TTYD64_dgb_clubba_StatusTable,
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

ActorBlueprint TTYD64_pit_part_4_imp_0E_HyperGoomba_0E_HyperGoomba = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x1B,
    .level = 12,
    .partCount = 1,
    .partsData = TTYD64_arn_hyper_goomba_ActorParts,
    .initScript = &TTYD64_arn_hyper_paragoomba_EVS_Init_80227010,
    .statusTable = TTYD64_arn_hyper_goomba_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 90,
    .hurricaneChance = 90,
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

ActorBlueprint TTYD64_pit_part_4_imp_0E_HyperParagoomba_0E_HyperParagoomba = {
    .flags = 0x200,
    .maxHP = 8,
    .type = 0x1C,
    .level = 12,
    .partCount = 4,
    .partsData = TTYD64_arn_hyper_paragoomba_ActorParts,
    .initScript = &TTYD64_arn_hyper_paragoomba_EVS_Init,
    .statusTable = TTYD64_arn_hyper_paragoomba_FlyingStatusTable,
    .escapeChance = 50,
    .airLiftChance = 95,
    .hurricaneChance = 95,
    .spookChance = 80,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 36, 26 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

StageListRow TTYD64_pit_part_4_StageTable[] = {
    { .name = "pit_01", .stage = &TTYD64_pit_part_4_Stage_Pit1 },
    { .name = "pit_12", .stage = &TTYD64_pit_part_4_Stage_Pit2 },
    {},
};

void TTYD64_InstallBattles_pit_part_4(void) {
    Mod_SetBattleList("TTYD64", 0x33, TTYD64_pit_part_4_FormationTable);
    Mod_SetStageList("TTYD64", 0x33, TTYD64_pit_part_4_StageTable);
}
