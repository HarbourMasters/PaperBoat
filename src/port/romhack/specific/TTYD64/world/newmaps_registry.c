#include "common.h"
#include "map.h"
#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/world/newmaps.h"
#include <string.h>

extern MapConfig TTYD64_mapcfg_kmr_31;
extern MapConfig TTYD64_mapcfg_kmr_32;
extern MapConfig TTYD64_mapcfg_kmr_33;
extern MapConfig TTYD64_mapcfg_kmr_34;
extern MapConfig TTYD64_mapcfg_mac_07;
extern MapConfig TTYD64_mapcfg_mac_08;
extern MapConfig TTYD64_mapcfg_tik_27;
extern MapConfig TTYD64_mapcfg_tik_28;
extern MapConfig TTYD64_mapcfg_kkj_30;
extern MapConfig TTYD64_mapcfg_hos_25;
extern MapConfig TTYD64_mapcfg_nok_05;
extern MapConfig TTYD64_mapcfg_trd_11;
extern MapConfig TTYD64_mapcfg_dro_03;
extern MapConfig TTYD64_mapcfg_dro_04;
extern MapConfig TTYD64_mapcfg_isk_20;
extern MapConfig TTYD64_mapcfg_isk_21;
extern MapConfig TTYD64_mapcfg_mim_13;
extern MapConfig TTYD64_mapcfg_obk_10;
extern MapConfig TTYD64_mapcfg_obk_11;
extern MapConfig TTYD64_mapcfg_obk_12;
extern MapConfig TTYD64_mapcfg_obk_13;
extern MapConfig TTYD64_mapcfg_obk_14;
extern MapConfig TTYD64_mapcfg_arn_21;
extern MapConfig TTYD64_mapcfg_arn_22;
extern MapConfig TTYD64_mapcfg_arn_23;
extern MapConfig TTYD64_mapcfg_arn_24;
extern MapConfig TTYD64_mapcfg_omo_18;
extern MapConfig TTYD64_mapcfg_omo_19;
extern MapConfig TTYD64_mapcfg_jan_24;
extern MapConfig TTYD64_mapcfg_jan_25;
extern MapConfig TTYD64_mapcfg_jan_26;
extern MapConfig TTYD64_mapcfg_jan_27;
extern MapConfig TTYD64_mapcfg_flo_26;
extern MapConfig TTYD64_mapcfg_flo_27;
extern MapConfig TTYD64_mapcfg_flo_28;
extern MapConfig TTYD64_mapcfg_sam_13;
extern MapConfig TTYD64_mapcfg_kpa_135;
extern MapConfig TTYD64_mapcfg_kpa_136;
extern MapConfig TTYD64_mapcfg_kpa_137;
extern MapConfig TTYD64_mapcfg_kpa_138;
extern MapConfig TTYD64_mapcfg_kpa_139;
extern MapConfig TTYD64_mapcfg_kpa_140;
extern MapConfig TTYD64_mapcfg_pit_00;
extern MapConfig TTYD64_mapcfg_pit_01;
extern MapConfig TTYD64_mapcfg_pit_02;
extern MapConfig TTYD64_mapcfg_pit_03;
extern MapConfig TTYD64_mapcfg_pit_04;
extern MapConfig TTYD64_mapcfg_pit_05;
extern MapConfig TTYD64_mapcfg_pit_06;
extern MapConfig TTYD64_mapcfg_pit_07;
extern MapConfig TTYD64_mapcfg_pit_08;
extern MapConfig TTYD64_mapcfg_pit_09;
extern MapConfig TTYD64_mapcfg_pit_10;
extern MapConfig TTYD64_mapcfg_pit_11;
extern MapConfig TTYD64_mapcfg_pit_12;
extern MapConfig TTYD64_mapcfg_tyd_00;
extern MapConfig TTYD64_mapcfg_tyd_01;
extern MapConfig TTYD64_mapcfg_tyd_02;
extern MapConfig TTYD64_mapcfg_tyd_03;
extern MapConfig TTYD64_mapcfg_tyd_04;
extern MapConfig TTYD64_mapcfg_tyd_05;
extern MapConfig TTYD64_mapcfg_tyd_06;
extern MapConfig TTYD64_mapcfg_tyd_07;
extern MapConfig TTYD64_mapcfg_tyd_08;

typedef struct TTYD64_nm_MapEntry {
    const char* areaID;
    MapConfig* config;
    s32 index;
} TTYD64_nm_MapEntry;

static const char* sNewAreas[] = {
    "area_pit",
    "area_tyd",
};

static const TTYD64_nm_MapEntry sNewMaps[] = {
    { "area_kmr", &TTYD64_mapcfg_kmr_31, 17 },  { "area_kmr", &TTYD64_mapcfg_kmr_32, 18 },
    { "area_kmr", &TTYD64_mapcfg_kmr_33, 19 },  { "area_kmr", &TTYD64_mapcfg_kmr_34, 20 },
    { "area_mac", &TTYD64_mapcfg_mac_07, 8 },   { "area_mac", &TTYD64_mapcfg_mac_08, 9 },
    { "area_tik", &TTYD64_mapcfg_tik_27, 22 },  { "area_tik", &TTYD64_mapcfg_tik_28, 23 },
    { "area_kkj", &TTYD64_mapcfg_kkj_30, 25 },  { "area_hos", &TTYD64_mapcfg_hos_25, 9 },
    { "area_nok", &TTYD64_mapcfg_nok_05, 9 },   { "area_trd", &TTYD64_mapcfg_trd_11, 11 },
    { "area_dro", &TTYD64_mapcfg_dro_03, 2 },   { "area_dro", &TTYD64_mapcfg_dro_04, 3 },
    { "area_isk", &TTYD64_mapcfg_isk_20, 17 },  { "area_isk", &TTYD64_mapcfg_isk_21, 18 },
    { "area_mim", &TTYD64_mapcfg_mim_13, 12 },  { "area_obk", &TTYD64_mapcfg_obk_10, 9 },
    { "area_obk", &TTYD64_mapcfg_obk_11, 10 },  { "area_obk", &TTYD64_mapcfg_obk_12, 11 },
    { "area_obk", &TTYD64_mapcfg_obk_13, 12 },  { "area_obk", &TTYD64_mapcfg_obk_14, 13 },
    { "area_arn", &TTYD64_mapcfg_arn_21, 11 },  { "area_arn", &TTYD64_mapcfg_arn_22, 12 },
    { "area_arn", &TTYD64_mapcfg_arn_23, 13 },  { "area_arn", &TTYD64_mapcfg_arn_24, 14 },
    { "area_omo", &TTYD64_mapcfg_omo_18, 17 },  { "area_omo", &TTYD64_mapcfg_omo_19, 18 },
    { "area_jan", &TTYD64_mapcfg_jan_24, 22 },  { "area_jan", &TTYD64_mapcfg_jan_25, 23 },
    { "area_jan", &TTYD64_mapcfg_jan_26, 24 },  { "area_jan", &TTYD64_mapcfg_jan_27, 25 },
    { "area_flo", &TTYD64_mapcfg_flo_26, 20 },  { "area_flo", &TTYD64_mapcfg_flo_27, 21 },
    { "area_flo", &TTYD64_mapcfg_flo_28, 22 },  { "area_sam", &TTYD64_mapcfg_sam_13, 12 },
    { "area_kpa", &TTYD64_mapcfg_kpa_135, 50 }, { "area_kpa", &TTYD64_mapcfg_kpa_136, 51 },
    { "area_kpa", &TTYD64_mapcfg_kpa_137, 52 }, { "area_kpa", &TTYD64_mapcfg_kpa_138, 53 },
    { "area_kpa", &TTYD64_mapcfg_kpa_139, 54 }, { "area_kpa", &TTYD64_mapcfg_kpa_140, 55 },
    { "area_pit", &TTYD64_mapcfg_pit_00, 0 },   { "area_pit", &TTYD64_mapcfg_pit_01, 1 },
    { "area_pit", &TTYD64_mapcfg_pit_02, 2 },   { "area_pit", &TTYD64_mapcfg_pit_03, 3 },
    { "area_pit", &TTYD64_mapcfg_pit_04, 4 },   { "area_pit", &TTYD64_mapcfg_pit_05, 5 },
    { "area_pit", &TTYD64_mapcfg_pit_06, 6 },   { "area_pit", &TTYD64_mapcfg_pit_07, 7 },
    { "area_pit", &TTYD64_mapcfg_pit_08, 8 },   { "area_pit", &TTYD64_mapcfg_pit_09, 9 },
    { "area_pit", &TTYD64_mapcfg_pit_10, 10 },  { "area_pit", &TTYD64_mapcfg_pit_11, 11 },
    { "area_pit", &TTYD64_mapcfg_pit_12, 12 },  { "area_tyd", &TTYD64_mapcfg_tyd_00, 0 },
    { "area_tyd", &TTYD64_mapcfg_tyd_01, 1 },   { "area_tyd", &TTYD64_mapcfg_tyd_02, 2 },
    { "area_tyd", &TTYD64_mapcfg_tyd_03, 3 },   { "area_tyd", &TTYD64_mapcfg_tyd_04, 4 },
    { "area_tyd", &TTYD64_mapcfg_tyd_05, 5 },   { "area_tyd", &TTYD64_mapcfg_tyd_06, 6 },
    { "area_tyd", &TTYD64_mapcfg_tyd_07, 7 },   { "area_tyd", &TTYD64_mapcfg_tyd_08, 8 },
};

static s32 TTYD64_nm_FindArea(const char* id) {
    for (s32 i = 0; i < AREA_TABLE_CAPACITY && gAreas[i].maps != NULL; i++) {
        if (strcmp(gAreas[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

static void TTYD64_nm_OnNewGameStart(IEvent* event) {
    OnNewGameStart* ev = (OnNewGameStart*) event;

    *ev->mapName = "kmr_31";
    *ev->entryID = 0;
}

void TTYD64_nm_InstallRegistry(void) {
    for (s32 i = 0; i < ARRAY_COUNT(sNewMaps); i++) {
        const TTYD64_nm_MapEntry* entry = &sNewMaps[i];
        s32 area = TTYD64_nm_FindArea(entry->areaID);

        if (area < 0) {
            for (s32 j = 0; j < ARRAY_COUNT(sNewAreas); j++) {
                if (strcmp(sNewAreas[j], entry->areaID) == 0) {
                    area = Mod_AddArea("TTYD64", sNewAreas[j], NULL);
                    break;
                }
            }
        }
        if (area < 0) {
            GameEngine_LogInfo("TTYD64: unknown area %s for map %s", entry->areaID, entry->config->id);
            continue;
        }
        if (gAreas[area].mapCount != entry->index) {
            GameEngine_LogInfo(
                "TTYD64: map %s needs index %d in %s but the next free index is %d", entry->config->id, entry->index,
                entry->areaID, gAreas[area].mapCount
            );
            continue;
        }
        Mod_AddMap("TTYD64", area, entry->config);
    }
    REGISTER_LISTENER(OnNewGameStart, EVENT_PRIORITY_NORMAL, TTYD64_nm_OnNewGameStart);
}
