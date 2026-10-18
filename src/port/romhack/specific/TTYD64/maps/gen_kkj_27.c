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

extern EvtScript kkj_27_EVS_BindExitTriggers;
extern EvtScript kkj_27_EVS_Main;
extern EvtScript kkj_27_EVS_SetupMusic;
extern EvtScript kkj_27_EVS_SetupRotatingWall;
extern EvtScript kkj_27_EVS_UpdateTexturePan;
extern MapSettings kkj_27_settings;
extern Gfx kkj_27_setup_gfx_candle_lights[];

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(GetEntryID);
API_CALLABLE(MakeEntity);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetCustomGfx);
API_CALLABLE(SetModelCustomGfx);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanner);
API_CALLABLE(StopSound);

extern EvtScript TTYD64_kkj_27_Script_InitNewStuff;
extern EvtScript TTYD64_kkj_27_Script_Main;
extern EvtScript TTYD64_kkj_27_Script_EnterMap;
extern EntryList TTYD64_kkj_27_EntryList;

// clang-format off
EvtScript TTYD64_kkj_27_Script_InitNewStuff = {
    Call(MakeEntity, Ref(Entity_RedBlock), 474, 60, 0, 0, 247, 0x80000000)
    Call(AssignBlockFlag, GameFlag(4613))
    Return
    End
};

EvtScript TTYD64_kkj_27_Script_Main = {
    Set(GameByte(425), 26)
    Call(SetSpriteShading, 0x5000B)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(kkj_27_EVS_SetupRotatingWall)
    Exec(kkj_27_EVS_SetupMusic)
    Exec(TTYD64_kkj_27_Script_EnterMap)
    Call(SetTexPanner, 32, 0)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Set(LVar3, 40)
        Set(LVar4, 900)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(kkj_27_EVS_UpdateTexturePan)
    EndThread
    Call(SetModelCustomGfx, 32, 0, -1)
    Call(SetCustomGfx, 0, (Bytecode) kkj_27_setup_gfx_candle_lights, 0)
    Call(SetTexPanner, 37, 0)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Set(LVar3, 40)
        Set(LVar4, 900)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(kkj_27_EVS_UpdateTexturePan)
    EndThread
    Call(SetModelCustomGfx, 37, 0, -1)
    Call(SetCustomGfx, 0, (Bytecode) kkj_27_setup_gfx_candle_lights, 0)
    Call(SetCamSpeed, 0, Float(3.0))
    Return
    End
};

EvtScript TTYD64_kkj_27_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVar0, Ref(kkj_27_EVS_BindExitTriggers))
        Exec(EnterWalk)
    CaseDefault
    EndSwitch
    Call(StopSound, 147)
    Exec(TTYD64_kkj_27_Script_InitNewStuff)
    Return
    End
};

EntryList TTYD64_kkj_27_EntryList = {
    { 425.0f, 0.0f, 40.0f, 0.0f },
    { -250.0f, 10.0f, 0.0f, 0.0f },
    { -203.0f, 10.0f, 2.0f, 90.0f },
};
// clang-format on

void TTYD64_InstallMap_kkj_27(void) {
    kkj_27_settings.entryList = &TTYD64_kkj_27_EntryList;
    kkj_27_settings.entryCount = 3;
    Mod_ReplaceScript("TTYD64", &kkj_27_EVS_Main, &TTYD64_kkj_27_Script_Main);
}
