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
#include "port/romhack/specific/TTYD64/world/maps.h"

extern NpcGroupList kpa_03_DefaultNPCs;
extern EvtScript kpa_03_EVS_BindExitTriggers;
extern EvtScript kpa_03_EVS_CreateDarkness;
extern EvtScript kpa_03_EVS_EnterMap;
extern EvtScript kpa_03_EVS_ExitWalk_kpa_01_1;
extern EvtScript kpa_03_EVS_ExitWalk_kpa_04_0;
extern EvtScript kpa_03_EVS_Main;
extern EvtScript kpa_03_EVS_MakeEntities;
extern EvtScript kpa_03_EVS_SetupMusic;
extern MapSettings kpa_03_settings;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(UseExitHeading);

extern EntryList TTYD64_kpa_03_EntryList;
extern EvtScript TTYD64_kpa_03_Script_80242044;
extern EvtScript TTYD64_kpa_03_Script_Main;
extern EvtScript TTYD64_kpa_03_Script_Exit2;

// clang-format off
EntryList TTYD64_kpa_03_EntryList = {
    { 1888.0f, -410.0f, -93.0f, 270.0f },
    { -1575.0f, -105.0f, -158.0f, 90.0f },
    { -1210.0f, 190.0f, -156.0f, 90.0f },
};

EvtScript TTYD64_kpa_03_Script_80242044 = {
    BindTrigger(kpa_03_EVS_ExitWalk_kpa_01_1, 0x80000, 42, 1, 0)
    BindTrigger(kpa_03_EVS_ExitWalk_kpa_04_0, 0x80000, 37, 1, 0)
    BindTrigger(TTYD64_kpa_03_Script_Exit2, 0x80000, 46, 1, 0)
    Return
    End
};

EvtScript TTYD64_kpa_03_Script_Main = {
    Set(GameByte(425), 22)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), -508, -264, 198, 0, 417, 0x80000000)
    Call(AssignBlockFlag, GameFlag(5694))
    Call(MakeNpcs, 1, Ref(kpa_03_DefaultNPCs))
    ExecWait(kpa_03_EVS_MakeEntities)
    Exec(kpa_03_EVS_CreateDarkness)
    Exec(kpa_03_EVS_EnterMap)
    Wait(1)
    Exec(kpa_03_EVS_SetupMusic)
    Return
    End
};

EvtScript TTYD64_kpa_03_Script_Exit2 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 2)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "kpa_137", 0)
    Wait(100)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_kpa_03(void) {
    kpa_03_settings.entryList = &TTYD64_kpa_03_EntryList;
    kpa_03_settings.entryCount = 3;
    Mod_ReplaceScript("TTYD64", &kpa_03_EVS_BindExitTriggers, &TTYD64_kpa_03_Script_80242044);
    Mod_ReplaceScript("TTYD64", &kpa_03_EVS_Main, &TTYD64_kpa_03_Script_Main);
}
