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

extern NpcGroupList arn_05_AfterNPCs;
extern NpcGroupList arn_05_BeforeNPCs;
extern EvtScript arn_05_EVS_ExitWalk_arn_02_0;
extern EvtScript arn_05_EVS_ExitWalk_arn_03_1;
extern EvtScript arn_05_EVS_Main;
extern EvtScript arn_05_EVS_MakeEntities;
extern EvtScript arn_05_EVS_SetupMusic;
extern EvtScript arn_05_EVS_SetupTubbaRaid;
extern MapSettings arn_05_settings;

API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnableModel);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetLoadType);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlayerJump);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);

extern BombTrigger TTYD64_arn_05_TriggerCoord_Door;
extern EvtScript TTYD64_arn_05_Script_Main;
extern EvtScript TTYD64_arn_05_Script_GetEntry;
extern EvtScript TTYD64_arn_05_Script_BlastDoor;
extern EvtScript TTYD64_arn_05_Script_UpdateDoor;
extern EvtScript TTYD64_arn_05_Script_CreateExitTriggers;
extern EvtScript TTYD64_arn_05_Script_Exit2;
extern EntryList TTYD64_arn_05_EntryList;

// clang-format off
BombTrigger TTYD64_arn_05_TriggerCoord_Door = {
    .pos = { 208.0f, 179.0f, 107.0f },
    .diameter = 2.0f
};

EvtScript TTYD64_arn_05_Script_Main = {
    Set(GameByte(425), 34)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    IfLt(GameByte(0), -16)
        Call(MakeNpcs, 0, Ref(arn_05_BeforeNPCs))
    Else
        Call(MakeNpcs, 0, Ref(arn_05_AfterNPCs))
    EndIf
    ExecWait(arn_05_EVS_MakeEntities)
    Exec(arn_05_EVS_SetupTubbaRaid)
    Exec(arn_05_EVS_SetupMusic)
    Exec(TTYD64_arn_05_Script_GetEntry)
    Return
    End
};

EvtScript TTYD64_arn_05_Script_GetEntry = {
    Exec(TTYD64_arn_05_Script_UpdateDoor)
    Call(GetLoadType, LVar1)
    IfEq(LVar1, 1)
        Exec(EnterSavePoint)
        Exec(TTYD64_arn_05_Script_CreateExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 2)
        Call(DisablePlayerInput, 1)
        Call(PlayerJump, 209, 170, 64, 20)
        Call(DisablePlayerInput, 0)
        Exec(TTYD64_arn_05_Script_CreateExitTriggers)
    Else
        Set(LVar0, Ref(TTYD64_arn_05_Script_CreateExitTriggers))
        Exec(EnterWalk)
        Wait(1)
    EndIf
    Return
    End
};

EvtScript TTYD64_arn_05_Script_BlastDoor = {
    Call(PlayEffect_impl, 66, 0, 22, 22, 1, 10, 30, 0, 0, 0, 0, 0, 0)
    Call(EnableModel, 22, 0)
    Call(EnableModel, 44, 0)
    Call(ModifyColliderFlags, 0, 28, 0x7FFFFE00)
    Set(GameFlag(5117), 1)
    Unbind
    Return
    End
};

EvtScript TTYD64_arn_05_Script_UpdateDoor = {
    IfEq(GameFlag(5117), 0)
        BindTrigger(TTYD64_arn_05_Script_BlastDoor, 0x100000, Ref(TTYD64_arn_05_TriggerCoord_Door), 1, 0)
    Else
        Call(EnableModel, 22, 0)
        Call(EnableModel, 44, 0)
        Call(ModifyColliderFlags, 0, 28, 0x7FFFFE00)
    EndIf
    Return
    End
};

EvtScript TTYD64_arn_05_Script_CreateExitTriggers = {
    BindTrigger(arn_05_EVS_ExitWalk_arn_03_1, 0x80000, 1, 1, 0)
    BindTrigger(arn_05_EVS_ExitWalk_arn_02_0, 0x80000, 5, 1, 0)
    BindTrigger(TTYD64_arn_05_Script_Exit2, 128, 31, 1, 0)
    Return
    End
};

EvtScript TTYD64_arn_05_Script_Exit2 = {
    Call(DisablePlayerInput, 1)
    Call(GotoMap, (Bytecode) "arn_21", 0)
    Wait(100)
    Return
    End
};

EntryList TTYD64_arn_05_EntryList = {
    { -77.0f, 135.0f, 150.0f, 90.0f },
    { 577.0f, 200.0f, 150.0f, 270.0f },
    { 210.0f, 131.0f, 25.0f, -180.0f },
};
// clang-format on

void TTYD64_InstallMap_arn_05(void) {
    arn_05_settings.entryList = &TTYD64_arn_05_EntryList;
    arn_05_settings.entryCount = 3;
    Mod_ReplaceScript("TTYD64", &arn_05_EVS_Main, &TTYD64_arn_05_Script_Main);
}
