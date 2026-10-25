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
#include "port/romhack/specific/TTYD64/world/tp.h"

extern EntryList TTYD64_imp_Pit_EntryList;
extern EvtScript TTYD64_imp_Pit_Script_EnterMap;
extern EvtScript TTYD64_imp_Pit_Script_MakeEntities;
extern EvtScript TTYD64_imp_Pit_Script_SetupMusic;
extern EvtScript TTYD64_imp_Pit_Script_SetupTexturePan;
extern EvtScript TTYD64_imp_Pit_Script_SpawnNpcs;
extern EvtScript TTYD64_imp_Pit_Script_UpdateNpcSpawnPos;
extern NpcData TTYD64_imp_Bzzap_Npc_Bzzap[];
extern NpcData TTYD64_imp_CrazeeDayzee_Npc_CrazeeDayzee[];
extern NpcData TTYD64_imp_Lakitu_Npc_BlueSpinyA[];
extern NpcData TTYD64_imp_Lakitu_Npc_BlueSpinyB[];
extern NpcData TTYD64_imp_Lakitu_Npc_BlueSpinyC[];
extern NpcData TTYD64_imp_Lakitu_Npc_BlueSpinyD[];
extern NpcData TTYD64_imp_Lakitu_Npc_DarkLakitu[];
extern NpcData TTYD64_imp_RuffPuff_Npc_RuffPuff[];
extern NpcData TTYD64_imp_SpikeTop_Npc_SpikeTop[];
extern NpcGroupList TTYD64_imp_Mover_NpcGroupList_Mover;
extern NpcGroupList TTYD64_imp_Pit_NpcGroupList_pit;
extern char TTYD64_imp_Pit_ASCII_NextFloor[];
extern u8 TTYD64_imp_Pit_String_Tattle_1[];
extern u8 TTYD64_imp_Pit_String_Tattle_2[];
extern u8 TTYD64_imp_Pit_String_Tattle_3[];
s32 TTYD64_imp_Pit_Function_Init(void);

extern EvtScript TTYD64_pit_07_Script_Main;
extern NpcGroupList TTYD64_pit_07_NpcGroupList_DarkLakitu;
extern MapSettings TTYD64_pit_07_Header;
extern TTYD64_PitNpcsEntry TTYD64_pit_07_IntTable_60s_NpcData[];
extern EvtScript TTYD64_pit_07_Script_SpawnNpcs_60s;
extern EvtScript TTYD64_pit_07_Script_SpawnNpcs_Init;

// clang-format off
static s32 TTYD64_pit_07_GetTattleMsg[3];

static s32 TTYD64_pit_07_GetTattle(void) {
    return TTYD64_tp_PitTattle(TTYD64_pit_07_GetTattleMsg);
}

EvtScript TTYD64_pit_07_Script_Main = {
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
        ExecWait(TTYD64_pit_07_Script_SpawnNpcs_Init)
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

NpcGroupList TTYD64_pit_07_NpcGroupList_DarkLakitu = {
    { .npcCount = 1, .npcs = TTYD64_imp_Lakitu_Npc_DarkLakitu, .battle = 0x3000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_imp_Lakitu_Npc_BlueSpinyA, .battle = 0x360F, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_imp_Lakitu_Npc_BlueSpinyB, .battle = 0x360F, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_imp_Lakitu_Npc_BlueSpinyC, .battle = 0x360F, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_imp_Lakitu_Npc_BlueSpinyD, .battle = 0x360F, .stage = 0 },
    {},
};

MapSettings TTYD64_pit_07_Header = {
    .main = TTYD64_pit_07_Script_Main,
    .entryList = &TTYD64_imp_Pit_EntryList,
    .entryCount = 2,
    .background = NULL,
    .tattle = { .get = TTYD64_pit_07_GetTattle },
};

TTYD64_PitNpcsEntry TTYD64_pit_07_IntTable_60s_NpcData[] = {
    { (Bytecode) TTYD64_pit_07_NpcGroupList_DarkLakitu, 0 },
    { 1, (Bytecode) TTYD64_imp_SpikeTop_Npc_SpikeTop },
    { 1, (Bytecode) TTYD64_imp_CrazeeDayzee_Npc_CrazeeDayzee },
    { 1, (Bytecode) TTYD64_imp_Bzzap_Npc_Bzzap },
    { 1, (Bytecode) TTYD64_imp_RuffPuff_Npc_RuffPuff },
    { -1, -1 },
};

EvtScript TTYD64_pit_07_Script_SpawnNpcs_60s = {
    Set(LVar0, (Bytecode) TTYD64_pit_07_IntTable_60s_NpcData)
    ExecWait(TTYD64_imp_Pit_Script_SpawnNpcs)
    Return
    End
};

EvtScript TTYD64_pit_07_Script_SpawnNpcs_Init = {
    ExecWait(TTYD64_pit_07_Script_SpawnNpcs_60s)
    Return
    End
};

MapConfig TTYD64_mapcfg_pit_07 = {
    .id = "pit_07",
    .settings = &TTYD64_pit_07_Header,
    .bgName = NULL,
    .init = TTYD64_imp_Pit_Function_Init,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_tp_Install_pit_07(void) {
    TTYD64_pit_07_GetTattleMsg[0] = Mod_RegisterInlineMessage("TTYD64", TTYD64_imp_Pit_String_Tattle_1);
    TTYD64_pit_07_GetTattleMsg[1] = Mod_RegisterInlineMessage("TTYD64", TTYD64_imp_Pit_String_Tattle_2);
    TTYD64_pit_07_GetTattleMsg[2] = Mod_RegisterInlineMessage("TTYD64", TTYD64_imp_Pit_String_Tattle_3);
    TTYD64_tp_RegisterNpcsTable(TTYD64_pit_07_IntTable_60s_NpcData, 6);
    Mod_RegisterMapResetData("TTYD64", "pit_07", TTYD64_pit_07_NpcGroupList_DarkLakitu, 6 * sizeof(NpcGroup));
    Mod_RegisterMapResetData("TTYD64", "pit_07", TTYD64_imp_Pit_NpcGroupList_pit, 2 * sizeof(NpcGroup));
    Mod_RegisterMapResetData("TTYD64", "pit_07", TTYD64_imp_Pit_ASCII_NextFloor, 12);
}
