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

extern EvtScript kpa_12_EVS_BindExitTriggers;
extern EvtScript kpa_12_EVS_ExitWalk_kpa_13_0;
extern EvtScript kpa_12_EVS_ExitWalk_kpa_1X_Lower;
extern EvtScript kpa_12_EVS_ExitWalk_kpa_1X_Upper;
extern EvtScript kpa_12_EVS_Main;
extern EvtScript kpa_12_EVS_SetupMusic;
extern EvtScript kpa_12_EVS_SetupPlatforms;
extern EvtScript kpa_12_EVS_TexPan_Lava;
extern LavaReset kpa_12_SafeFloorColliders[];
extern MapSettings kpa_12_settings;

API_CALLABLE(EnableGroup);
API_CALLABLE(GotoMap);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(ResetFromLava);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_kpa_12_Script_Exit3;
extern EvtScript TTYD64_kpa_12_Script_80240788;
extern EvtScript TTYD64_kpa_12_Script_Main_EnterWalk;
extern EntryList TTYD64_kpa_12_EntryList;

// clang-format off
EvtScript TTYD64_kpa_12_Script_Exit3 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 3)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "kpa_136", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_kpa_12_Script_80240788 = {
    BindTrigger(kpa_12_EVS_ExitWalk_kpa_1X_Upper, 0x80000, 73, 1, 0)
    BindTrigger(kpa_12_EVS_ExitWalk_kpa_1X_Lower, 0x80000, 76, 1, 0)
    BindTrigger(kpa_12_EVS_ExitWalk_kpa_13_0, 0x80000, 70, 1, 0)
    BindTrigger(TTYD64_kpa_12_Script_Exit3, 0x80000, 85, 1, 0)
    Return
    End
};

EvtScript TTYD64_kpa_12_Script_Main_EnterWalk = {
    Set(GameByte(425), 22)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    IfEq(GameFlag(1556), 0)
        Call(EnableGroup, 233, 0)
        Call(EnableGroup, 229, 0)
        Exec(kpa_12_EVS_TexPan_Lava)
    Else
        Call(EnableGroup, 114, 0)
        Call(ModifyColliderFlags, 0, 86, 0x7FFFFE00)
    EndIf
    Exec(kpa_12_EVS_SetupMusic)
    IfEq(GameFlag(1556), 0)
        Exec(kpa_12_EVS_SetupPlatforms)
    EndIf
    Set(LVar0, Ref(kpa_12_EVS_BindExitTriggers))
    Exec(EnterWalk)
    IfEq(GameFlag(1556), 0)
        Thread
            Wait(2)
            Call(ModifyColliderFlags, 3, 9, 3)
            Call(ModifyColliderFlags, 3, 10, 3)
            Call(ModifyColliderFlags, 3, 11, 3)
            Call(ModifyColliderFlags, 3, 12, 3)
            Call(ModifyColliderFlags, 3, 13, 3)
            Call(ModifyColliderFlags, 3, 14, 3)
            Call(ModifyColliderFlags, 3, 15, 3)
            Call(ModifyColliderFlags, 3, 16, 3)
            Call(ModifyColliderFlags, 3, 17, 3)
            Call(ModifyColliderFlags, 3, 18, 3)
            Call(ModifyColliderFlags, 3, 19, 3)
            Call(ModifyColliderFlags, 3, 80, 3)
            Call(ModifyColliderFlags, 3, 81, 3)
            Call(ModifyColliderFlags, 3, 76, 3)
            Thread
                Call(ResetFromLava, (Bytecode) kpa_12_SafeFloorColliders)
            EndThread
        EndThread
    EndIf
    Wait(1)
    Return
    End
};

EntryList TTYD64_kpa_12_EntryList = {
    { 30.0f, 30.0f, -150.0f, 90.0f },
    { 1470.0f, 30.0f, -150.0f, 270.0f },
    { 17.0f, -20.0f, -17.0f, 90.0f },
    { 479.0f, -20.0f, -37.0f, 0.0f },
};
// clang-format on

void TTYD64_InstallMap_kpa_12(void) {
    kpa_12_settings.entryList = &TTYD64_kpa_12_EntryList;
    kpa_12_settings.entryCount = 4;
    Mod_ReplaceScript("TTYD64", &kpa_12_EVS_BindExitTriggers, &TTYD64_kpa_12_Script_80240788);
    Mod_ReplaceScript("TTYD64", &kpa_12_EVS_Main, &TTYD64_kpa_12_Script_Main_EnterWalk);
}
