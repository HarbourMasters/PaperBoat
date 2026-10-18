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

extern NpcGroupList obk_05_DefaultNPCs;
extern EvtScript obk_05_EVS_ExitDoor_obk_01_2;
extern EvtScript obk_05_EVS_Main;
extern EvtScript obk_05_EVS_MakeEntities;
extern EvtScript obk_05_EVS_ManageHole;
extern EvtScript obk_05_EVS_ManageRetroJar;
extern EvtScript obk_05_EVS_SetupMusic;
extern EvtScript obk_05_EVS_SetupRockingChairs;
extern MapSettings obk_05_settings;

API_CALLABLE(GetEntryID);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanOffset);
API_CALLABLE(SetTexPanner);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_obk_05_Script_80240BD0;
extern EvtScript TTYD64_obk_05_Script_Main;
extern EvtScript TTYD64_obk_05_Script_Exit1;
extern EvtScript TTYD64_obk_05_TrackEntry;
extern EvtScript TTYD64_obk_05_Script_MakeExits;
extern EntryList TTYD64_obk_05_EntryList;

// clang-format off
EvtScript TTYD64_obk_05_Script_80240BD0 = {
    Call(SetTexPanner, 33, 0)
    Call(SetTexPanner, 34, 0)
    Set(LVar0, 0)
    Set(LVar1, 0)
    Loop(0)
        Add(LVar0, 300)
        Add(LVar1, 100)
        Call(SetTexPanOffset, 0, 0, LVar0, LVar1)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_obk_05_Script_Main = {
    Set(GameByte(425), 13)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeNpcs, 0, Ref(obk_05_DefaultNPCs))
    ExecWait(obk_05_EVS_MakeEntities)
    Exec(obk_05_EVS_SetupRockingChairs)
    Exec(obk_05_EVS_ManageHole)
    Exec(TTYD64_obk_05_Script_80240BD0)
    Exec(TTYD64_obk_05_Script_MakeExits)
    Exec(TTYD64_obk_05_TrackEntry)
    Call(ModifyColliderFlags, 0, 17, 0x7FFFFE00)
    Exec(obk_05_EVS_SetupMusic)
    Exec(obk_05_EVS_ManageRetroJar)
    Return
    End
};

EvtScript TTYD64_obk_05_Script_Exit1 = {
    Call(UseExitHeading, 60, 1)
    Exec(ExitWalk)
    Call(TTYD64_TestPlayerAnimFlags, PA_FLAG_8BIT_MARIO, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_SetVerticalMovementLocked, 1)
        Call(GotoMap, (Bytecode) "obk_12", 0)
    Else
        Call(GotoMap, (Bytecode) "obk_05", 1)
    EndIf
    Wait(100)
    Return
    End
};

EvtScript TTYD64_obk_05_TrackEntry = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVar2, 49)
        Set(LVar4, 50)
        Set(LVar3, 1)
        ExecWait(EnterSplitSingleDoor)
    CaseEq(1)
        Set(LVar0, Ref(TTYD64_obk_05_Script_MakeExits))
        Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_obk_05_Script_MakeExits = {
    Call(TTYD64_SetVerticalMovementLocked, 0)
    BindTrigger(obk_05_EVS_ExitDoor_obk_01_2, 256, 12, 1, 0)
    BindTrigger(TTYD64_obk_05_Script_Exit1, 0x80000, 24, 1, 0)
    Return
    End
};

EntryList TTYD64_obk_05_EntryList = {
    { -68.0f, 0.0f, 235.0f, 0.0f },
    { 182.0f, 60.0f, -100.0f, -90.0f },
};
// clang-format on

void TTYD64_InstallMap_obk_05(void) {
    obk_05_settings.entryList = &TTYD64_obk_05_EntryList;
    obk_05_settings.entryCount = 2;
    Mod_ReplaceScript("TTYD64", &obk_05_EVS_Main, &TTYD64_obk_05_Script_Main);
}
