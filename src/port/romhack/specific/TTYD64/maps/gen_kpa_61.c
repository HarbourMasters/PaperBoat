#include "common.h"
#include "effects.h"
#include "entity.h"
#include "foliage.h"
#include "map.h"
#include "npc.h"
#include "script_api/map.h"
#include <string.h>
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/maps/maps.h"

extern NpcGroupList kpa_61_DefaultNPCs;
extern EvtScript kpa_61_EVS_BindExitTriggers;
extern EvtScript kpa_61_EVS_EnterMap;
extern EvtScript kpa_61_EVS_ExitDoors_kpa_33_1;
extern EvtScript kpa_61_EVS_ExitDoors_kpa_82_1;
extern EvtScript kpa_61_EVS_Main;
extern EvtScript kpa_61_EVS_MakeEntities;
extern EvtScript kpa_61_EVS_SetupMusic;
extern EvtScript kpa_61_EVS_TexPan_Clouds;
extern MapSettings kpa_61_settings;

API_CALLABLE(DisablePlayerInput);
API_CALLABLE(GetEntryID);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeNpcs);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);

extern EvtScript TTYD64_kpa_61_Script_Exit2;
extern EvtScript TTYD64_kpa_61_Script_Main;
extern EvtScript TTYD64_kpa_61_Script_802425F4;
extern EvtScript TTYD64_kpa_61_Script_InitNewStuff;
extern EntryList TTYD64_kpa_61_EntryList;

// clang-format off
EvtScript TTYD64_kpa_61_Script_Exit2 = {
    Call(DisablePlayerInput, 1)
    Call(GotoMap, (Bytecode) "kpa_139", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_kpa_61_Script_Main = {
    Set(GameByte(425), 22)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 1, Ref(kpa_61_DefaultNPCs))
    ExecWait(kpa_61_EVS_MakeEntities)
    Wait(1)
    Exec(kpa_61_EVS_TexPan_Clouds)
    Exec(TTYD64_kpa_61_Script_InitNewStuff)
    Return
    End
};

EvtScript TTYD64_kpa_61_Script_802425F4 = {
    BindTrigger(kpa_61_EVS_ExitDoors_kpa_82_1, 256, 13, 1, 0)
    BindTrigger(kpa_61_EVS_ExitDoors_kpa_33_1, 256, 18, 1, 0)
    BindTrigger(TTYD64_kpa_61_Script_Exit2, 128, 24, 1, 0)
    Return
    End
};

EvtScript TTYD64_kpa_61_Script_InitNewStuff = {
    Call(GetEntryID, LVar0)
    IfNe(LVar0, 2)
        Exec(kpa_61_EVS_EnterMap)
    Else
        Exec(kpa_61_EVS_BindExitTriggers)
    EndIf
    Exec(kpa_61_EVS_SetupMusic)
    Return
    End
};

EntryList TTYD64_kpa_61_EntryList = {
    { -100.0f, -160.0f, 116.0f, 120.0f },
    { -100.0f, 200.0f, 102.0f, 120.0f },
    { -143.0f, 200.0f, 167.0f, 90.0f },
};
// clang-format on

void TTYD64_InstallMap_kpa_61(void) {
    kpa_61_settings.entryList = &TTYD64_kpa_61_EntryList;
    kpa_61_settings.entryCount = 3;
    Mod_ReplaceScript("TTYD64", &kpa_61_EVS_Main, &TTYD64_kpa_61_Script_Main);
    Mod_ReplaceScript("TTYD64", &kpa_61_EVS_BindExitTriggers, &TTYD64_kpa_61_Script_802425F4);
}
