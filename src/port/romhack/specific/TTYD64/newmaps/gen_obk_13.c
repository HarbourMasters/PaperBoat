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
#include "port/romhack/specific/TTYD64/newmaps/nm.h"

API_CALLABLE(AssignScript);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DropItemEntity);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(PlaySound);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(StopSound);

extern EvtScript TTYD64_obk_13_Script_MakeCoins;
extern EvtScript TTYD64_obk_13_Script_Main;
extern EvtScript TTYD64_obk_13_Script_SetupMusic;
extern EvtScript TTYD64_obk_13_Script_Exit0;
extern EvtScript TTYD64_obk_13_Script_EnterMap;
extern EvtScript TTYD64_obk_13_Script_MakeEntities;
extern MapSettings TTYD64_obk_13_Header;
extern EvtScript TTYD64_obk_13_Script_CreateExitTriggers;
extern EntryList TTYD64_obk_13_EntryList;

// clang-format off
EvtScript TTYD64_obk_13_Script_MakeCoins = {
    Call(PlaySound, 142)
    Call(DropItemEntity, 343, -59, 95, -10, 17, 0)
    Wait(8)
    Call(DropItemEntity, 343, -59, 114, -10, 17, 0)
    Wait(8)
    Call(DropItemEntity, 343, -59, 133, -10, 17, 0)
    Wait(8)
    Call(DropItemEntity, 343, -59, 152, -10, 17, 0)
    Wait(8)
    Call(DropItemEntity, 343, -59, 171, -10, 17, 0)
    Wait(8)
    Call(DropItemEntity, 343, -59, 190, -10, 17, 0)
    Wait(8)
    Call(DropItemEntity, 343, -59, 209, -10, 17, 0)
    Wait(8)
    Call(StopSound, 142)
    Return
    End
};

EvtScript TTYD64_obk_13_Script_Main = {
    Set(GameByte(425), 13)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(TTYD64_SetPlayerAnimFlagBits, PA_FLAG_8BIT_MARIO, 1)
    Exec(TTYD64_obk_13_Script_SetupMusic)
    Exec(TTYD64_obk_13_Script_MakeEntities)
    Exec(TTYD64_obk_13_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_obk_13_Script_SetupMusic = {
    IfLt(GameByte(0), -16)
        Call(SetMusic, 0, 27, 0, 8)
    Else
        Call(SetMusic, 0, 28, 0, 8)
    EndIf
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_obk_13_Script_Exit0 = {
    Call(StopSound, 142)
    Call(DisablePlayerInput, 1)
    Call(PlaySound, 449)
    Call(GotoMap, (Bytecode) "obk_12", 0)
    Return
    End
};

EvtScript TTYD64_obk_13_Script_EnterMap = {
    Exec(TTYD64_obk_13_Script_CreateExitTriggers)
    Call(DisablePlayerInput, 1)
    Wait(5)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_obk_13_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_TriggerBlock), -58, 63, -10, -180, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_obk_13_Script_MakeCoins)
    Return
    End
};

MapSettings TTYD64_obk_13_Header = {
    .main = &TTYD64_obk_13_Script_Main,
    .entryList = &TTYD64_obk_13_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = NULL },
};

EvtScript TTYD64_obk_13_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_obk_13_Script_Exit0, 256, 0, 1, 0)
    Return
    End
};

EntryList TTYD64_obk_13_EntryList = {
    { -196.0f, 0.0f, -10.0f, 90.0f },
};

MapConfig TTYD64_mapcfg_obk_13 = {
    .id = "obk_13",
    .settings = &TTYD64_obk_13_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 1,
};
// clang-format on

void TTYD64_nm_Install_obk_13(void) {
}
