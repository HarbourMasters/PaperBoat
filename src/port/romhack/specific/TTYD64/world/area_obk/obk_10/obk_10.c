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
#include "port/romhack/specific/TTYD64/world/newmaps.h"

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlaySound);
API_CALLABLE(ResetFromLava);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_obk_10_Script_UpdateSpikes;
extern EvtScript TTYD64_obk_10_Script_Main;
extern u8 TTYD64_obk_10_String_Tattle[];
extern EvtScript TTYD64_obk_10_Script_MakeEntities;
extern EvtScript TTYD64_obk_10_Script_Exit0;
extern MapSettings TTYD64_obk_10_Header;
extern EvtScript TTYD64_obk_10_Script_Entity_Shine1;
extern LavaReset TTYD64_obk_10_LaveReset_Pos[];
extern EvtScript TTYD64_obk_10_Script_CreateExitTriggers;
extern EntryList TTYD64_obk_10_EntryList;

// clang-format off
static s32 TTYD64_obk_10_GetTattleMsg;

static s32 TTYD64_obk_10_GetTattle(void) {
    return TTYD64_obk_10_GetTattleMsg;
}

EvtScript TTYD64_obk_10_Script_UpdateSpikes = {
    SetGroup(239)
    Call(ModifyColliderFlags, 3, 6, 2)
    Thread
        Call(ResetFromLava, (Bytecode) TTYD64_obk_10_LaveReset_Pos)
    EndThread
    Set(MapVar(2), 0)
    Loop(0)
        Set(LVar6, 6)
        Set(LVar7, 5)
        Wait(1)
        Call(TranslateModel, LVar7, 0, 0, 0)
        Call(ParentColliderToModel, LVar6, LVar7)
        Call(PlaySound, 8339)
        Call(MakeLerp, 0, 50, 4, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateModel, LVar7, 0, LVar0, 0)
            Call(UpdateColliderTransform, LVar6)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(10)
        Call(MakeLerp, 50, 0, 15, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateModel, LVar7, 0, LVar0, 0)
            Call(UpdateColliderTransform, LVar6)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(60)
    EndLoop
    Return
    End
};

EvtScript TTYD64_obk_10_Script_Main = {
    Set(GameByte(425), 13)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_obk_10_Script_MakeEntities)
    Exec(TTYD64_obk_10_Script_UpdateSpikes)
    Set(LVar0, (Bytecode) TTYD64_obk_10_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};

u8 TTYD64_obk_10_String_Tattle[] = {
    0xFC, 0x04, 0x21, 0xF7, 0x48, 0x49, 0x44, 0x44, 0x45, 0x4E, 0xF7, 0x50,
    0x41, 0x54, 0x48, 0xF7, 0x49, 0x4E, 0x53, 0x49, 0x44, 0x45, 0xF7, 0x54,
    0x48, 0x45, 0xF7, 0x43, 0x48, 0x49, 0x4D, 0x4E, 0x45, 0x59, 0x1F, 0xF0,
    0x25, 0x57, 0x0C, 0xF7, 0x54, 0x48, 0x45, 0x52, 0x45, 0x07, 0x53, 0xF7,
    0x41, 0xF7, 0x4C, 0x4F, 0x54, 0xF7, 0x4F, 0x46, 0xF7, 0x44, 0x55, 0x53,
    0x54, 0xF7, 0x41, 0x52, 0x4F, 0x55, 0x4E, 0x44, 0xF7, 0x48, 0x45, 0x52,
    0x45, 0x0C, 0xF0, 0x29, 0xF7, 0x48, 0x4F, 0x50, 0x45, 0xF7, 0x54, 0x48,
    0x45, 0x52, 0x45, 0xF7, 0x49, 0x53, 0xF7, 0x41, 0x54, 0xF7, 0x4C, 0x45,
    0x41, 0x53, 0x54, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0x54, 0x48, 0x49, 0x4E,
    0x47, 0xF0, 0x57, 0x4F, 0x52, 0x54, 0x48, 0x57, 0x48, 0x49, 0x4C, 0x45,
    0x0E, 0x0E, 0x0E, 0xF0, 0xF1, 0xFD
};

EvtScript TTYD64_obk_10_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SuperBlock), 637, 65, 2, -180, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(5090))
    Call(AssignScript, (Bytecode) TTYD64_obk_10_Script_Entity_Shine1)
    Return
    End
};

EvtScript TTYD64_obk_10_Script_Exit0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "obk_07", 1)
    Wait(100)
    Return
    End
};

MapSettings TTYD64_obk_10_Header = {
    .main = &TTYD64_obk_10_Script_Main,
    .entryList = &TTYD64_obk_10_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_obk_10_GetTattle },
};

EvtScript TTYD64_obk_10_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(5090))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

LavaReset TTYD64_obk_10_LaveReset_Pos[] = {
    { .colliderID = 7, .pos = { -349.0f, 0.0f, 0.0f } },
    { .colliderID = 8, .pos = { 598.0f, 0.0f, 2.0f } },
    { .colliderID = -1 },
};

EvtScript TTYD64_obk_10_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_obk_10_Script_Exit0, 0x80000, 5, 1, 0)
    Return
    End
};

EntryList TTYD64_obk_10_EntryList = {
    { -479.0f, 0.0f, -13.0f, 0.0f },
};

MapConfig TTYD64_mapcfg_obk_10 = {
    .id = "obk_10",
    .settings = &TTYD64_obk_10_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 1,
};
// clang-format on

void TTYD64_nm_Install_obk_10(void) {
    TTYD64_obk_10_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_obk_10_String_Tattle);
}
