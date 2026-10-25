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
extern NpcData TTYD64_imp_Duplighost_Npc_Duplighost[];
extern NpcData TTYD64_imp_FrostPiranha_Npc_FrostPiranha[];
extern NpcData TTYD64_imp_Gulpit_Npc_Gulpit[];
extern NpcData TTYD64_imp_HammerBros_Npc_DarkHammerBros[];
extern NpcData TTYD64_imp_Lakitu_Npc_Lakitu[];
extern NpcData TTYD64_imp_Lakitu_Npc_SpinyA[];
extern NpcData TTYD64_imp_Lakitu_Npc_SpinyB[];
extern NpcData TTYD64_imp_Lakitu_Npc_SpinyC[];
extern NpcData TTYD64_imp_Lakitu_Npc_SpinyD[];
extern NpcGroupList TTYD64_imp_Mover_NpcGroupList_Mover;
extern NpcGroupList TTYD64_imp_Pit_NpcGroupList_pit;
extern char TTYD64_imp_Pit_ASCII_NextFloor[];
extern u8 TTYD64_imp_Pit_String_Tattle_1[];
extern u8 TTYD64_imp_Pit_String_Tattle_2[];
extern u8 TTYD64_imp_Pit_String_Tattle_3[];
s32 TTYD64_imp_Pit_Function_Init(void);

extern EvtScript TTYD64_pit_08_Script_Main;
extern NpcGroupList TTYD64_pit_08_NpcGroupList_Lakitu;
extern MapSettings TTYD64_pit_08_Header;
extern TTYD64_PitNpcsEntry TTYD64_pit_08_IntTable_70s_NpcData[];
extern EvtScript TTYD64_pit_08_Script_SpawnNpcs_70s;
extern EvtScript TTYD64_pit_08_Script_SpawnNpcs_Init;

// clang-format off
static s32 TTYD64_pit_08_GetTattleMsg[3];

static s32 TTYD64_pit_08_GetTattle(void) {
    return TTYD64_tp_PitTattle(TTYD64_pit_08_GetTattleMsg);
}

EvtScript TTYD64_pit_08_Script_Main = {
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
        ExecWait(TTYD64_pit_08_Script_SpawnNpcs_Init)
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

NpcGroupList TTYD64_pit_08_NpcGroupList_Lakitu = {
    { .npcCount = 1, .npcs = TTYD64_imp_Lakitu_Npc_Lakitu, .battle = 0x3000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_imp_Lakitu_Npc_SpinyA, .battle = 0x370F, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_imp_Lakitu_Npc_SpinyB, .battle = 0x370F, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_imp_Lakitu_Npc_SpinyC, .battle = 0x370F, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_imp_Lakitu_Npc_SpinyD, .battle = 0x370F, .stage = 0 },
    {},
};

MapSettings TTYD64_pit_08_Header = {
    .main = TTYD64_pit_08_Script_Main,
    .entryList = &TTYD64_imp_Pit_EntryList,
    .entryCount = 2,
    .background = NULL,
    .tattle = { .get = TTYD64_pit_08_GetTattle },
};

TTYD64_PitNpcsEntry TTYD64_pit_08_IntTable_70s_NpcData[] = {
    { 7, (Bytecode) TTYD64_imp_HammerBros_Npc_DarkHammerBros },
    { (Bytecode) TTYD64_pit_08_NpcGroupList_Lakitu, 0 },
    { 2, (Bytecode) TTYD64_imp_Gulpit_Npc_Gulpit },
    { 2, (Bytecode) TTYD64_imp_FrostPiranha_Npc_FrostPiranha },
    { 1, (Bytecode) TTYD64_imp_Duplighost_Npc_Duplighost },
    { -1, -1 },
};

EvtScript TTYD64_pit_08_Script_SpawnNpcs_70s = {
    Set(LVar0, (Bytecode) TTYD64_pit_08_IntTable_70s_NpcData)
    ExecWait(TTYD64_imp_Pit_Script_SpawnNpcs)
    Return
    End
};

EvtScript TTYD64_pit_08_Script_SpawnNpcs_Init = {
    ExecWait(TTYD64_pit_08_Script_SpawnNpcs_70s)
    Return
    End
};

MapConfig TTYD64_mapcfg_pit_08 = {
    .id = "pit_08",
    .settings = &TTYD64_pit_08_Header,
    .bgName = NULL,
    .init = TTYD64_imp_Pit_Function_Init,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_tp_Install_pit_08(void) {
    TTYD64_pit_08_GetTattleMsg[0] = Mod_RegisterInlineMessage("TTYD64", TTYD64_imp_Pit_String_Tattle_1);
    TTYD64_pit_08_GetTattleMsg[1] = Mod_RegisterInlineMessage("TTYD64", TTYD64_imp_Pit_String_Tattle_2);
    TTYD64_pit_08_GetTattleMsg[2] = Mod_RegisterInlineMessage("TTYD64", TTYD64_imp_Pit_String_Tattle_3);
    TTYD64_tp_RegisterNpcsTable(TTYD64_pit_08_IntTable_70s_NpcData, 6);
    Mod_RegisterMapResetData("TTYD64", "pit_08", TTYD64_pit_08_NpcGroupList_Lakitu, 6 * sizeof(NpcGroup));
    Mod_RegisterMapResetData("TTYD64", "pit_08", TTYD64_imp_Pit_NpcGroupList_pit, 2 * sizeof(NpcGroup));
    Mod_RegisterMapResetData("TTYD64", "pit_08", TTYD64_imp_Pit_ASCII_NextFloor, 12);
}
