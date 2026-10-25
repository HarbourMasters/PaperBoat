#include "common.h"
#include "effects.h"
#include "entity.h"
#include "map.h"
#include "npc.h"
#include "script_api/map.h"
#include <stdio.h>
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/world/tyd_pit.h"

extern EntryList TTYD64_imp_Pit_EntryList;
extern EvtScript TTYD64_imp_Pit_Script_EnterMap;
extern EvtScript TTYD64_imp_Pit_Script_MakeEntities;
extern EvtScript TTYD64_imp_Pit_Script_SetupMusic;
extern EvtScript TTYD64_imp_Pit_Script_SetupTexturePan;
extern EvtScript TTYD64_imp_Pit_Script_SpawnNpcs;
extern EvtScript TTYD64_imp_Pit_Script_UpdateNpcSpawnPos;
extern NpcData TTYD64_imp_Bobomb_Npc_Bobomb[];
extern NpcData TTYD64_imp_Fuzzy_Npc_Fuzzy[];
extern NpcData TTYD64_imp_Gloomba_Npc_Gloomba[];
extern NpcData TTYD64_imp_KoopaTroopa_Npc_KoopaTroopa[];
extern NpcData TTYD64_imp_Paratroopa_Npc_Paratroopa[];
extern NpcGroupList TTYD64_imp_Mover_NpcGroupList_Mover;
extern NpcGroupList TTYD64_imp_Pit_NpcGroupList_pit;
extern char TTYD64_imp_Pit_ASCII_NextFloor[];
extern u8 TTYD64_imp_Pit_String_Tattle_1[];
extern u8 TTYD64_imp_Pit_String_Tattle_2[];
extern u8 TTYD64_imp_Pit_String_Tattle_3[];
s32 TTYD64_imp_Pit_Function_Init(void);

extern EvtScript TTYD64_pit_01_Script_Main;
extern MapSettings TTYD64_pit_01_Header;
extern TTYD64_PitNpcsEntry TTYD64_pit_01_IntTable_00s_NpcData[];
extern EvtScript TTYD64_pit_01_Script_SpawnNpcs_00s;
extern EvtScript TTYD64_pit_01_Script_SpawnNpcs_Init;

// clang-format off
static s32 TTYD64_pit_01_GetTattleMsg[3];

static s32 TTYD64_pit_01_GetTattle(void) {
    return TTYD64_tp_PitTattle(TTYD64_pit_01_GetTattleMsg);
}

EvtScript TTYD64_pit_01_Script_Main = {
    Set(GameByte(425), 2)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(ClearDefeatedEnemies)
    Call(RandInt, 100, LVar0)
    IfGt(AreaByte(0), 95)
        Set(LVar0, 0)
    EndIf
    IfGe(LVar0, 95)
        Set(MapVar(0), 1)
        Call(MakeNpcs, 0, (Bytecode) TTYD64_imp_Mover_NpcGroupList_Mover)
    Else
        ExecWait(TTYD64_pit_01_Script_SpawnNpcs_Init)
        ExecWait(TTYD64_imp_Pit_Script_UpdateNpcSpawnPos)
    EndIf
    Exec(TTYD64_imp_Pit_Script_MakeEntities)
    Exec(TTYD64_imp_Pit_Script_SetupMusic)
    Exec(TTYD64_imp_Pit_Script_SetupTexturePan)
    Exec(TTYD64_imp_Pit_Script_EnterMap)
    Set(GameFlag(4101), 0)
    Wait(5)
    Return
    End
};

MapSettings TTYD64_pit_01_Header = {
    .main = TTYD64_pit_01_Script_Main,
    .entryList = &TTYD64_imp_Pit_EntryList,
    .entryCount = 2,
    .background = NULL,
    .tattle = { .get = TTYD64_pit_01_GetTattle },
};

TTYD64_PitNpcsEntry TTYD64_pit_01_IntTable_00s_NpcData[] = {
    { 1, (Bytecode) TTYD64_imp_Gloomba_Npc_Gloomba },
    { 1, (Bytecode) TTYD64_imp_KoopaTroopa_Npc_KoopaTroopa },
    { 1, (Bytecode) TTYD64_imp_Paratroopa_Npc_Paratroopa },
    { 1, (Bytecode) TTYD64_imp_Fuzzy_Npc_Fuzzy },
    { 1, (Bytecode) TTYD64_imp_Bobomb_Npc_Bobomb },
    { -1, -1 },
};

EvtScript TTYD64_pit_01_Script_SpawnNpcs_00s = {
    Set(LVar0, (Bytecode) TTYD64_pit_01_IntTable_00s_NpcData)
    ExecWait(TTYD64_imp_Pit_Script_SpawnNpcs)
    Return
    End
};

EvtScript TTYD64_pit_01_Script_SpawnNpcs_Init = {
    ExecWait(TTYD64_pit_01_Script_SpawnNpcs_00s)
    Return
    End
};

MapConfig TTYD64_mapcfg_pit_01 = {
    .id = "pit_01",
    .settings = &TTYD64_pit_01_Header,
    .bgName = NULL,
    .init = TTYD64_imp_Pit_Function_Init,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_tp_Install_pit_01(void) {
    TTYD64_pit_01_GetTattleMsg[0] = Mod_RegisterInlineMessage("TTYD64", TTYD64_imp_Pit_String_Tattle_1);
    TTYD64_pit_01_GetTattleMsg[1] = Mod_RegisterInlineMessage("TTYD64", TTYD64_imp_Pit_String_Tattle_2);
    TTYD64_pit_01_GetTattleMsg[2] = Mod_RegisterInlineMessage("TTYD64", TTYD64_imp_Pit_String_Tattle_3);
    TTYD64_tp_RegisterNpcsTable(TTYD64_pit_01_IntTable_00s_NpcData, 6);
    Mod_RegisterMapResetData("TTYD64", "pit_01", TTYD64_imp_Pit_NpcGroupList_pit, 2 * sizeof(NpcGroup));
    Mod_RegisterMapResetData("TTYD64", "pit_01", TTYD64_imp_Pit_ASCII_NextFloor, 12);
}
