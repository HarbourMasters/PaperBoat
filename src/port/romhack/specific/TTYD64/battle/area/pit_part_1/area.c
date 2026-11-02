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

extern EvtScript b_area_kmr_part_1_kmr_02_EVS_PostBattle;
extern EvtScript b_area_kmr_part_3_kpa_13_EVS_PreBattle;
extern s32 b_area_nok_fuzzy_StatusTable[];
extern s32 b_area_nok_koopa_troopa_StatusTable[];
extern s32 b_area_nok_paratroopa_FlyingStatusTable[];
extern s32 b_area_trd_part_1_bob_omb_StatusTable[];
API_CALLABLE(EnableGroup);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetSpriteShading);
extern ActorBlueprint TTYD64_imp_1A_Gloomba_1A_Gloomba;
extern s32 TTYD64_imp_1A_Gloomba_IdleAnimations_80222324_1A[];
extern s32 TTYD64_imp_1A_Gloomba_IdleAnimations_80222370_1A[];
extern ActorPartBlueprint TTYD64_imp_1A_Gloomba_PartsTable_802222D8_1A[];
extern EvtScript TTYD64_imp_1A_Gloomba_Script_HandleEvent_802226E4_1A;
extern EvtScript TTYD64_imp_1A_Gloomba_Script_Idle_80222408_1A;
extern EvtScript TTYD64_imp_1A_Gloomba_Script_Init_802223BC_1A;
extern EvtScript TTYD64_imp_1A_Gloomba_Script_TakeTurn_80222F10_1A;
extern ActorPartBlueprint TTYD64_nok_fuzzy_ActorParts[];
extern s32 TTYD64_nok_fuzzy_DefaultAnims[];
extern EvtScript TTYD64_nok_fuzzy_EVS_HandleEvent;
extern EvtScript TTYD64_nok_fuzzy_EVS_Init_8022B3D0;
extern EvtScript TTYD64_nok_fuzzy_EVS_TakeTurn;
extern ActorPartBlueprint TTYD64_nok_koopa_troopa_ActorParts[];
extern EvtScript TTYD64_nok_koopa_troopa_EVS_HandleEvent;
extern EvtScript TTYD64_nok_koopa_troopa_EVS_Idle;
extern EvtScript TTYD64_nok_koopa_troopa_EVS_Init;
extern EvtScript TTYD64_nok_koopa_troopa_EVS_TakeTurn;
extern s32 TTYD64_nok_koopa_troopa_FlippedAnims[];
extern s32 TTYD64_nok_koopa_troopa_ShuffleAnims[];
extern ActorPartBlueprint TTYD64_nok_paratroopa_ActorParts[];
extern s32 TTYD64_nok_paratroopa_DownedAnims[];
extern s32 TTYD64_nok_paratroopa_DownedAnims_8022B630[];
extern s32 TTYD64_nok_paratroopa_DownedFlippedAnims[];
extern s32 TTYD64_nok_paratroopa_DownedShuffleAnims[];
extern EvtScript TTYD64_nok_paratroopa_EVS_Downed_HandleEvent;
extern EvtScript TTYD64_nok_paratroopa_EVS_Downed_Idle;
extern EvtScript TTYD64_nok_paratroopa_EVS_Downed_Init;
extern EvtScript TTYD64_nok_paratroopa_EVS_Downed_TakeTurn;
extern EvtScript TTYD64_nok_paratroopa_EVS_Flying_HandleEvent;
extern EvtScript TTYD64_nok_paratroopa_EVS_Flying_Idle;
extern EvtScript TTYD64_nok_paratroopa_EVS_Flying_Init;
extern EvtScript TTYD64_nok_paratroopa_EVS_Flying_TakeTurn;
extern EvtScript TTYD64_nok_paratroopa_EVS_KnockDown;
extern s32 TTYD64_nok_paratroopa_FlyingAnims[];
extern s32 TTYD64_nok_paratroopa_FlyingShuffleAnims[];
extern s32 TTYD64_nok_paratroopa_WingAnims[];
extern ActorPartBlueprint TTYD64_trd_part_1_bob_omb_ActorParts[];
extern s32 TTYD64_trd_part_1_bob_omb_DefaultAnims[];
extern EvtScript TTYD64_trd_part_1_bob_omb_EVS_Attack_Blast;
extern EvtScript TTYD64_trd_part_1_bob_omb_EVS_Attack_Tackle;
extern EvtScript TTYD64_trd_part_1_bob_omb_EVS_Defuse;
extern EvtScript TTYD64_trd_part_1_bob_omb_EVS_HandleEvent;
extern EvtScript TTYD64_trd_part_1_bob_omb_EVS_HandleEvent_Ignited;
extern EvtScript TTYD64_trd_part_1_bob_omb_EVS_Ignite;
extern EvtScript TTYD64_trd_part_1_bob_omb_EVS_TakeTurn;
extern s32 TTYD64_trd_part_1_bob_omb_IgnitedAnims[];
extern EvtScript TTYD64_trd_part_1_paratroopa_EVS_Flying_Init;
extern Battle TTYD64_pit_part_1_FormationTable[];
extern EvtScript TTYD64_pit_part_1_Script_BeforeBattle_Pit;
extern FormationRow TTYD64_pit_part_1_Formation_Pit5_3[];
extern FormationRow TTYD64_pit_part_1_Formation_Pit5_2[];
extern FormationRow TTYD64_pit_part_1_Formation_Pit4_9_3[];
extern FormationRow TTYD64_pit_part_1_Formation_Pit3_8_3[];
extern FormationRow TTYD64_pit_part_1_Formation_Pit3_8_2[];
extern FormationRow TTYD64_pit_part_1_Formation_Pit2_7_3[];
extern FormationRow TTYD64_pit_part_1_Formation_Pit2_7_2[];
extern FormationRow TTYD64_pit_part_1_Formation_Pit1_6_3[];
extern FormationRow TTYD64_pit_part_1_Formation_Pit5_1[];
extern FormationRow TTYD64_pit_part_1_Formation_Pit4_9_2[];
extern FormationRow TTYD64_pit_part_1_Formation_Pit1_6_2[];
extern FormationRow TTYD64_pit_part_1_Formation_Pit4_9_1[];
extern FormationRow TTYD64_pit_part_1_Formation_Pit3_8_1[];
extern FormationRow TTYD64_pit_part_1_Formation_Pit2_7_1[];
extern ActorBlueprint TTYD64_pit_part_1_imp_05_Paratroopa_05_Paratroopa;
extern ActorBlueprint TTYD64_pit_part_1_imp_06_Bobomb_06_Bobomb;
extern Stage TTYD64_pit_part_1_Stage_Pit1;
extern Stage TTYD64_pit_part_1_Stage_Pit2;
extern ActorBlueprint TTYD64_pit_part_1_imp_05_KoopaTroopa_05_KoopaTroopa;
extern ActorBlueprint TTYD64_pit_part_1_imp_05_Fuzzy_05_Fuzzy;
extern FormationRow TTYD64_pit_part_1_Formation_Pit1_6_1[];
extern StageListRow TTYD64_pit_part_1_StageTable[];

Battle TTYD64_pit_part_1_FormationTable[] = {
    { .name = NULL,
      .formationSize = 1,
      .formation = (Formation*) TTYD64_pit_part_1_Formation_Pit1_6_1,
      .stage = &TTYD64_pit_part_1_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_1_Formation_Pit1_6_2,
      .stage = &TTYD64_pit_part_1_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_1_Formation_Pit1_6_3,
      .stage = &TTYD64_pit_part_1_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_1_Formation_Pit2_7_1,
      .stage = &TTYD64_pit_part_1_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_1_Formation_Pit2_7_2,
      .stage = &TTYD64_pit_part_1_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_1_Formation_Pit2_7_3,
      .stage = &TTYD64_pit_part_1_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_1_Formation_Pit3_8_1,
      .stage = &TTYD64_pit_part_1_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_1_Formation_Pit3_8_2,
      .stage = &TTYD64_pit_part_1_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_1_Formation_Pit3_8_3,
      .stage = &TTYD64_pit_part_1_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_1_Formation_Pit4_9_1,
      .stage = &TTYD64_pit_part_1_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_1_Formation_Pit4_9_2,
      .stage = &TTYD64_pit_part_1_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_1_Formation_Pit4_9_3,
      .stage = &TTYD64_pit_part_1_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_1_Formation_Pit5_1,
      .stage = &TTYD64_pit_part_1_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_1_Formation_Pit5_2,
      .stage = &TTYD64_pit_part_1_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_1_Formation_Pit5_3,
      .stage = &TTYD64_pit_part_1_Stage_Pit1,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_pit_part_1_Script_BeforeBattle_Pit = {
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

FormationRow TTYD64_pit_part_1_Formation_Pit5_3[] = {
    { .actor = &TTYD64_pit_part_1_imp_06_Bobomb_06_Bobomb,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_pit_part_1_imp_06_Bobomb_06_Bobomb,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_pit_part_1_imp_06_Bobomb_06_Bobomb,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_pit_part_1_imp_06_Bobomb_06_Bobomb,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
};

FormationRow TTYD64_pit_part_1_Formation_Pit5_2[] = {
    { .actor = &TTYD64_pit_part_1_imp_06_Bobomb_06_Bobomb,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_pit_part_1_imp_05_Fuzzy_05_Fuzzy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
    { .actor = &TTYD64_pit_part_1_imp_06_Bobomb_06_Bobomb,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_pit_part_1_imp_05_Fuzzy_05_Fuzzy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
};

FormationRow TTYD64_pit_part_1_Formation_Pit4_9_3[] = {
    { .actor = &TTYD64_pit_part_1_imp_05_Fuzzy_05_Fuzzy,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
    { .actor = &TTYD64_pit_part_1_imp_05_Fuzzy_05_Fuzzy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
    { .actor = &TTYD64_pit_part_1_imp_05_Fuzzy_05_Fuzzy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
    { .actor = &TTYD64_pit_part_1_imp_05_Fuzzy_05_Fuzzy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
};

FormationRow TTYD64_pit_part_1_Formation_Pit3_8_3[] = {
    { .actor = &TTYD64_pit_part_1_imp_05_Paratroopa_05_Paratroopa,
      .home = { .index = 4 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_pit_part_1_imp_05_Paratroopa_05_Paratroopa,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_pit_part_1_imp_05_Paratroopa_05_Paratroopa,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_pit_part_1_imp_05_Paratroopa_05_Paratroopa,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
};

FormationRow TTYD64_pit_part_1_Formation_Pit3_8_2[] = {
    { .actor = &TTYD64_pit_part_1_imp_05_Paratroopa_05_Paratroopa,
      .home = { .index = 4 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_pit_part_1_imp_05_Fuzzy_05_Fuzzy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
    { .actor = &TTYD64_pit_part_1_imp_05_Paratroopa_05_Paratroopa,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_pit_part_1_imp_05_Fuzzy_05_Fuzzy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
};

FormationRow TTYD64_pit_part_1_Formation_Pit2_7_3[] = {
    { .actor = &TTYD64_pit_part_1_imp_05_KoopaTroopa_05_KoopaTroopa,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_pit_part_1_imp_05_KoopaTroopa_05_KoopaTroopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_pit_part_1_imp_05_KoopaTroopa_05_KoopaTroopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_pit_part_1_imp_05_KoopaTroopa_05_KoopaTroopa,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
};

FormationRow TTYD64_pit_part_1_Formation_Pit2_7_2[] = {
    { .actor = &TTYD64_pit_part_1_imp_05_KoopaTroopa_05_KoopaTroopa,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_pit_part_1_imp_05_Paratroopa_05_Paratroopa,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_pit_part_1_imp_05_KoopaTroopa_05_KoopaTroopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_pit_part_1_imp_05_Paratroopa_05_Paratroopa,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
};

FormationRow TTYD64_pit_part_1_Formation_Pit1_6_3[] = {
    { .actor = &TTYD64_imp_1A_Gloomba_1A_Gloomba,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GLOOMBA },
    { .actor = &TTYD64_pit_part_1_imp_05_Paratroopa_05_Paratroopa,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_pit_part_1_imp_06_Bobomb_06_Bobomb,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
};

FormationRow TTYD64_pit_part_1_Formation_Pit5_1[] = {
    { .actor = &TTYD64_pit_part_1_imp_06_Bobomb_06_Bobomb,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_imp_1A_Gloomba_1A_Gloomba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GLOOMBA },
    { .actor = &TTYD64_pit_part_1_imp_06_Bobomb_06_Bobomb,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
};

FormationRow TTYD64_pit_part_1_Formation_Pit4_9_2[] = {
    { .actor = &TTYD64_pit_part_1_imp_05_Fuzzy_05_Fuzzy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
    { .actor = &TTYD64_pit_part_1_imp_05_KoopaTroopa_05_KoopaTroopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_pit_part_1_imp_05_KoopaTroopa_05_KoopaTroopa,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
};

FormationRow TTYD64_pit_part_1_Formation_Pit1_6_2[] = {
    { .actor = &TTYD64_imp_1A_Gloomba_1A_Gloomba,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GLOOMBA },
    { .actor = &TTYD64_pit_part_1_imp_05_Paratroopa_05_Paratroopa,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
};

FormationRow TTYD64_pit_part_1_Formation_Pit4_9_1[] = {
    { .actor = &TTYD64_pit_part_1_imp_05_Fuzzy_05_Fuzzy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
    { .actor = &TTYD64_imp_1A_Gloomba_1A_Gloomba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GLOOMBA },
};

FormationRow TTYD64_pit_part_1_Formation_Pit3_8_1[] = {
    { .actor = &TTYD64_pit_part_1_imp_05_Paratroopa_05_Paratroopa,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_imp_1A_Gloomba_1A_Gloomba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GLOOMBA },
};

FormationRow TTYD64_pit_part_1_Formation_Pit2_7_1[] = {
    { .actor = &TTYD64_pit_part_1_imp_05_KoopaTroopa_05_KoopaTroopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_imp_1A_Gloomba_1A_Gloomba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GLOOMBA },
};

ActorBlueprint TTYD64_pit_part_1_imp_05_Paratroopa_05_Paratroopa = {
    .flags = 0x200,
    .maxHP = 4,
    .type = 0x0C,
    .level = 6,
    .partCount = 3,
    .partsData = TTYD64_nok_paratroopa_ActorParts,
    .initScript = &TTYD64_nok_paratroopa_EVS_Flying_Init,
    .statusTable = b_area_nok_paratroopa_FlyingStatusTable,
    .escapeChance = 60,
    .airLiftChance = 95,
    .hurricaneChance = 100,
    .spookChance = 90,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 50, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 29 },
    .statusTextOffset = { 8, 30 },
};

ActorBlueprint TTYD64_pit_part_1_imp_06_Bobomb_06_Bobomb = {
    .flags = 0x0,
    .maxHP = 3,
    .type = 0x0D,
    .level = 6,
    .partCount = 1,
    .partsData = TTYD64_trd_part_1_bob_omb_ActorParts,
    .initScript = &TTYD64_trd_part_1_paratroopa_EVS_Flying_Init,
    .statusTable = b_area_trd_part_1_bob_omb_StatusTable,
    .escapeChance = 70,
    .airLiftChance = 90,
    .hurricaneChance = 90,
    .spookChance = 90,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 34, 35 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

Stage TTYD64_pit_part_1_Stage_Pit1 = {
    .texture = "tik_tex",
    .shape = "pit_bt01_shape",
    .hit = "pit_bt01_hit",
    .preBattle = &TTYD64_pit_part_1_Script_BeforeBattle_Pit,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

Stage TTYD64_pit_part_1_Stage_Pit2 = {
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

ActorBlueprint TTYD64_pit_part_1_imp_05_KoopaTroopa_05_KoopaTroopa = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x0B,
    .level = 6,
    .partCount = 1,
    .partsData = TTYD64_nok_koopa_troopa_ActorParts,
    .initScript = &TTYD64_nok_koopa_troopa_EVS_Init,
    .statusTable = b_area_nok_koopa_troopa_StatusTable,
    .escapeChance = 70,
    .airLiftChance = 90,
    .hurricaneChance = 90,
    .spookChance = 90,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 28, 36 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 32 },
    .statusTextOffset = { 5, 32 },
};

ActorBlueprint TTYD64_pit_part_1_imp_05_Fuzzy_05_Fuzzy = {
    .flags = 0x0,
    .maxHP = 3,
    .type = 0x0A,
    .level = 6,
    .partCount = 1,
    .partsData = TTYD64_nok_fuzzy_ActorParts,
    .initScript = &TTYD64_nok_fuzzy_EVS_Init_8022B3D0,
    .statusTable = b_area_nok_fuzzy_StatusTable,
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

FormationRow TTYD64_pit_part_1_Formation_Pit1_6_1[] = {
    { .actor = &TTYD64_imp_1A_Gloomba_1A_Gloomba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GLOOMBA },
};

StageListRow TTYD64_pit_part_1_StageTable[] = {
    { .name = "pit_01", .stage = &TTYD64_pit_part_1_Stage_Pit1 },
    { .name = "pit_12", .stage = &TTYD64_pit_part_1_Stage_Pit2 },
    {},
};

void TTYD64_InstallBattles_pit_part_1(void) {
    Mod_SetBattleList("TTYD64", 0x30, TTYD64_pit_part_1_FormationTable);
    Mod_SetStageList("TTYD64", 0x30, TTYD64_pit_part_1_StageTable);
}
