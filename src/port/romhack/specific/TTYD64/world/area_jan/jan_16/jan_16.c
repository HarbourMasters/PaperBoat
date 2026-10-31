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

extern EvtScript jan_16_D_802412D4_B812D4;
extern NpcGroupList jan_16_DefaultNPCs;
extern EvtScript jan_16_EVS_EnterFalling;
extern EvtScript jan_16_EVS_ExitWalk_jan_15_1;
extern EvtScript jan_16_EVS_ExitWalk_jan_17_0;
extern EvtScript jan_16_EVS_ExitWalk_jan_22_1;
extern EvtScript jan_16_EVS_Main;
extern EvtScript jan_16_EVS_MakeEntities;
extern EvtScript jan_16_EVS_SetupBushes;
extern EvtScript jan_16_EVS_SetupMusic;
extern EvtScript jan_16_EVS_SpawnButterflies;
extern MapSettings jan_16_settings;

API_CALLABLE(GetEntryID);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(UseExitHeading);
API_CALLABLE(jan_16_SetModelTintMode);
API_CALLABLE(jan_16_SetModelTintParams);

extern EvtScript TTYD64_jan_16_Script_Exit4;
extern EvtScript TTYD64_jan_16_Script_Main_EnterWalk;
extern EvtScript TTYD64_jan_16_Script_MakeExits;
extern EntryList TTYD64_jan_16_EntryList;

// clang-format off
EvtScript TTYD64_jan_16_Script_Exit4 = {
    Call(UseExitHeading, 60, 5)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "jan_27", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_jan_16_Script_Main_EnterWalk = {
    Set(GameByte(425), 36)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamLeadPlayer, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 0, Ref(jan_16_DefaultNPCs))
    ExecWait(jan_16_EVS_MakeEntities)
    Exec(jan_16_D_802412D4_B812D4)
    Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 5, 0x7FFFFE00)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 4)
        Exec(jan_16_EVS_EnterFalling)
        Exec(TTYD64_jan_16_Script_MakeExits)
    Else
        Set(LVar0, Ref(TTYD64_jan_16_Script_MakeExits))
        Exec(EnterWalk)
    EndIf
    ExecWait(jan_16_EVS_SetupMusic)
    Exec(jan_16_EVS_SetupBushes)
    Exec(jan_16_EVS_SpawnButterflies)
    Call(jan_16_SetModelTintMode, 0, -1, 3)
    Call(jan_16_SetModelTintMode, 2, 0, 3)
    Call(jan_16_SetModelTintParams, 3, 255, 255, 255, 0, 0, 25, 0, 0, 0)
    Return
    End
};

EvtScript TTYD64_jan_16_Script_MakeExits = {
    BindTrigger(jan_16_EVS_ExitWalk_jan_15_1, 0x80000, 0, 1, 0)
    BindTrigger(jan_16_EVS_ExitWalk_jan_22_1, 0x80000, 4, 1, 0)
    BindTrigger(jan_16_EVS_ExitWalk_jan_17_0, 0x80000, 9, 1, 0)
    BindTrigger(TTYD64_jan_16_Script_Exit4, 0x80000, 46, 1, 0)
    Return
    End
};

EntryList TTYD64_jan_16_EntryList = {
    { -480.0f, 0.0f, 0.0f, 90.0f },
    { 480.0f, 0.0f, 0.0f, 270.0f },
    { -247.0f, 0.0f, 0.0f, 225.0f },
    { -390.0f, 0.0f, 20.0f, 100.0f },
    { 35.0f, 600.0f, 330.0f, 180.0f },
    { 360.0f, 0.0f, -21.0f, 139.200989f },
};
// clang-format on

void TTYD64_InstallMap_jan_16(void) {
    jan_16_settings.entryList = &TTYD64_jan_16_EntryList;
    jan_16_settings.entryCount = 6;
    Mod_ReplaceScript("TTYD64", &jan_16_EVS_Main, &TTYD64_jan_16_Script_Main_EnterWalk);
}
