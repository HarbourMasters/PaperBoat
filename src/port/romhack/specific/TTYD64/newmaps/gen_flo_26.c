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

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(ResetFromLava);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetTexPanner);
API_CALLABLE(UseExitHeading);
API_CALLABLE(flo_00_SpawnSunEffect);

extern EvtScript TTYD64_flo_26_Script_SetupTexturePan;
extern EvtScript TTYD64_flo_26_Script_Main;
extern EvtScript TTYD64_flo_26_Script_MakeEntities;
extern EvtScript TTYD64_flo_26_Script_TexturePan_Update;
extern EvtScript TTYD64_flo_26_Script_SetupMusic;
extern EvtScript TTYD64_flo_26_Script_Exit0;
extern u8 TTYD64_flo_26_String_Tattle[];
extern LavaReset TTYD64_flo_26_LavaResetList_flo26[];
extern MapSettings TTYD64_flo_26_Header;
extern EvtScript TTYD64_flo_26_Script_Entity_Shine1;
extern EvtScript TTYD64_flo_26_Script_CreateExitTriggers;
extern EntryList TTYD64_flo_26_EntryList;

// clang-format off
static s32 TTYD64_flo_26_GetTattleMsg;

static s32 TTYD64_flo_26_GetTattle(void) {
    return TTYD64_flo_26_GetTattleMsg;
}

EvtScript TTYD64_flo_26_Script_SetupTexturePan = {
    Call(SetTexPanner, 2, 0)
    Call(SetTexPanner, 3, 1)
    Thread
        Set(LVar0, 0)
        Set(LVar1, -140)
        Set(LVar2, 0)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 1)
        Set(LVar6, 0)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_flo_26_Script_TexturePan_Update)
    EndThread
    Thread
        Set(LVar0, 1)
        Set(LVar1, 200)
        Set(LVar2, 0)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 1)
        Set(LVar6, 0)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_flo_26_Script_TexturePan_Update)
    EndThread
    Return
    End
};

EvtScript TTYD64_flo_26_Script_Main = {
    Set(GameByte(425), 38)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Thread
        Call(ResetFromLava, (Bytecode) TTYD64_flo_26_LavaResetList_flo26)
    EndThread
    Exec(TTYD64_flo_26_Script_SetupMusic)
    Exec(TTYD64_flo_26_Script_SetupTexturePan)
    ExecWait(TTYD64_flo_26_Script_MakeEntities)
    Set(LVar0, (Bytecode) TTYD64_flo_26_Script_CreateExitTriggers)
    Exec(EnterWalk)
    IfGe(GameByte(0), 53)
        Call(flo_00_SpawnSunEffect)
    EndIf
    Return
    End
};

EvtScript TTYD64_flo_26_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_RedBlock), 247, 78, 332, 0, 394, 0x80000000)
    Call(AssignBlockFlag, GameFlag(5518))
    Call(MakeEntity, Ref(Entity_SuperBlock), 414, 78, -130, -180, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(5519))
    Call(AssignScript, (Bytecode) TTYD64_flo_26_Script_Entity_Shine1)
    Return
    End
};

EvtScript TTYD64_flo_26_Script_TexturePan_Update = {
    SetGroup(0)
    IfEq(LVar5, 1)
        IfEq(LVar6, 1)
            IfEq(LVar7, 1)
                IfEq(LVar8, 1)
                    Call(TTYD64_TexturePan_Simple)
                    Return
                EndIf
            EndIf
        EndIf
    EndIf
    Call(TTYD64_TexturePan_Complex)
    Return
    End
};

EvtScript TTYD64_flo_26_Script_SetupMusic = {
    Switch(GameByte(0))
    CaseLt(53)
        Call(SetMusic, 0, 48, 0, 8)
    CaseDefault
        Call(SetMusic, 0, 49, 0, 8)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_flo_26_Script_Exit0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "flo_14", 2)
    Wait(100)
    Return
    End
};

u8 TTYD64_flo_26_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x29, 0x54, 0x07, 0x53, 0xF7, 0x47, 0x4F, 0x4F,
    0x44, 0xF7, 0x54, 0x48, 0x41, 0x54, 0xF7, 0x57, 0x45, 0xF7, 0x48, 0x41,
    0x56, 0x45, 0xF0, 0x2C, 0x41, 0x4B, 0x49, 0x4C, 0x45, 0x53, 0x54, 0x45,
    0x52, 0x0C, 0xF7, 0x4F, 0x54, 0x48, 0x45, 0x52, 0x57, 0x49, 0x53, 0x45,
    0xF7, 0x57, 0x45, 0x07, 0x44, 0xF0, 0x42, 0x45, 0xF7, 0x49, 0x4E, 0xF7,
    0x42, 0x49, 0x47, 0xF7, 0x54, 0x52, 0x4F, 0x55, 0x42, 0x4C, 0x45, 0x0C,
    0xF7, 0x52, 0x49, 0x47, 0x48, 0x54, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F,
    0x1F, 0xF1, 0xFD
};

LavaReset TTYD64_flo_26_LavaResetList_flo26[] = {
    { .colliderID = 8, .pos = { -120.0f, 0.0f, -18.0f } },
    { .colliderID = 9, .pos = { 449.0f, 32.0f, -113.0f } },
    { .colliderID = 10, .pos = { 285.0f, 31.0f, 340.0f } },
    { .colliderID = -1 },
};

MapSettings TTYD64_flo_26_Header = {
    .main = &TTYD64_flo_26_Script_Main,
    .entryList = &TTYD64_flo_26_EntryList,
    .entryCount = 1,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_flo_26_GetTattle },
};

EvtScript TTYD64_flo_26_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(5519))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_flo_26_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_flo_26_Script_Exit0, 0x80000, 5, 1, 0)
    Return
    End
};

EntryList TTYD64_flo_26_EntryList = {
    { -120.0f, 0.0f, -18.0f, 0.0f },
};

MapConfig TTYD64_mapcfg_flo_26 = {
    .id = "flo_26",
    .settings = &TTYD64_flo_26_Header,
    .bgName = "fla_bg",
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_flo_26(void) {
    TTYD64_flo_26_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_flo_26_String_Tattle);
}
