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

extern BombTrigger kpa_133_BombPos_Wall;
extern EvtScript kpa_133_D_80241A90_AA8F10;
extern NpcGroupList kpa_133_DefaultNPCs;
extern EvtScript kpa_133_EVS_BindExitTriggers;
extern EvtScript kpa_133_EVS_BlastWall;
extern EvtScript kpa_133_EVS_ExitDoors_kpa_51_1;
extern EvtScript kpa_133_EVS_ExitWalk_kpa_134_0;
extern EvtScript kpa_133_EVS_ExitWalk_kpa_134_2;
extern EvtScript kpa_133_EVS_ExitWalk_kpa_134_3;
extern EvtScript kpa_133_EVS_Main;
extern EvtScript kpa_133_EVS_MakeEntities;
extern EvtScript kpa_133_EVS_SetWaterLevel;
extern EvtScript kpa_133_EVS_SetupMusic;
extern EvtScript kpa_133_EVS_UpdateTexturePan;
extern MapSettings kpa_133_settings;

API_CALLABLE(EnableModel);
API_CALLABLE(EnableTexPanning);
API_CALLABLE(GetEntryID);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);

extern EvtScript TTYD64_kpa_133_Script_EnterMap;
extern EntryList TTYD64_kpa_133_EntryList;
extern EvtScript TTYD64_kpa_133_Script_Main;
extern EvtScript TTYD64_kpa_133_Script_802407B4;
extern EvtScript TTYD64_kpa_133_Script_Exit4;

// clang-format off
EvtScript TTYD64_kpa_133_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVar0, 0)
        Set(LVar2, 50)
        Set(LVar3, 48)
        Exec(EnterDoubleDoor)
        Exec(kpa_133_EVS_BindExitTriggers)
    CaseEq(1)
        Set(LVar0, Ref(kpa_133_EVS_BindExitTriggers))
        Exec(EnterWalk)
    CaseEq(2)
        Set(LVar0, Ref(kpa_133_EVS_BindExitTriggers))
        Exec(EnterWalk)
    CaseEq(3)
        Set(LVar0, Ref(kpa_133_EVS_BindExitTriggers))
        Exec(EnterWalk)
    CaseEq(4)
        Set(LVar0, Ref(kpa_133_EVS_BindExitTriggers))
        Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EntryList TTYD64_kpa_133_EntryList = {
    { -387.0f, 0.0f, 115.0f, 90.0f },
    { 370.0f, 0.0f, 120.0f, 270.0f },
    { 370.0f, 100.0f, 120.0f, 270.0f },
    { 365.0f, 240.0f, -20.0f, 270.0f },
    { -350.0f, 198.0f, 116.0f, 90.0f },
};

EvtScript TTYD64_kpa_133_Script_Main = {
    Set(GameByte(425), 22)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 1, Ref(kpa_133_DefaultNPCs))
    ExecWait(kpa_133_EVS_MakeEntities)
    IfEq(GameFlag(1585), 0)
        Call(EnableModel, 57, 0)
        BindTrigger(kpa_133_EVS_BlastWall, 0x100000, Ref(kpa_133_BombPos_Wall), 1, 0)
    Else
        Call(EnableModel, 56, 0)
        Call(EnableModel, 58, 0)
        Call(ModifyColliderFlags, 0, 35, 0x7FFFFE00)
    EndIf
    Exec(kpa_133_EVS_SetWaterLevel)
    BindTrigger(kpa_133_D_80241A90_AA8F10, 0x20000, AreaFlag(8), 1, 0)
    Call(EnableTexPanning, 61, 1)
    Call(EnableTexPanning, 63, 1)
    Call(EnableTexPanning, 65, 1)
    Thread
        Set(LVar0, 1)
        Set(LVar1, -100)
        Set(LVar2, 100)
        Set(LVar3, 70)
        Set(LVar4, -70)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(kpa_133_EVS_UpdateTexturePan)
    EndThread
    Thread
        Set(LVar0, 4)
        Set(LVar1, 200)
        Set(LVar2, -100)
        Set(LVar3, 20)
        Set(LVar4, -20)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(kpa_133_EVS_UpdateTexturePan)
    EndThread
    Exec(kpa_133_EVS_SetupMusic)
    Exec(TTYD64_kpa_133_Script_EnterMap)
    Wait(1)
    Return
    End
};

EvtScript TTYD64_kpa_133_Script_802407B4 = {
    BindTrigger(kpa_133_EVS_ExitDoors_kpa_51_1, 256, 24, 1, 0)
    BindTrigger(kpa_133_EVS_ExitWalk_kpa_134_0, 0x80000, 27, 1, 0)
    BindTrigger(kpa_133_EVS_ExitWalk_kpa_134_2, 0x80000, 28, 1, 0)
    BindTrigger(kpa_133_EVS_ExitWalk_kpa_134_3, 0x80000, 33, 1, 0)
    BindTrigger(TTYD64_kpa_133_Script_Exit4, 0x80000, 48, 1, 0)
    Return
    End
};

EvtScript TTYD64_kpa_133_Script_Exit4 = {
    Call(TTYD64_WriteField, TTYD64_F_GGAMESTATUS_7D_1U, 1)
    Call(GotoMap, (Bytecode) "kpa_138", 0)
    Wait(100)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_kpa_133(void) {
    kpa_133_settings.entryList = &TTYD64_kpa_133_EntryList;
    kpa_133_settings.entryCount = 5;
    Mod_ReplaceScript("TTYD64", &kpa_133_EVS_Main, &TTYD64_kpa_133_Script_Main);
    Mod_ReplaceScript("TTYD64", &kpa_133_EVS_BindExitTriggers, &TTYD64_kpa_133_Script_802407B4);
}
