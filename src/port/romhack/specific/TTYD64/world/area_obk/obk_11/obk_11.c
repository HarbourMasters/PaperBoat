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

API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(PlayerJump);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerJumpscale);
API_CALLABLE(SetPlayerPos);

extern EvtScript TTYD64_obk_11_Script_EnterMap;
extern EvtScript TTYD64_obk_11_Script_Main;
extern EvtScript TTYD64_obk_11_Script_Exit0;
extern u8 TTYD64_obk_11_String_Tattle[];
extern EvtScript TTYD64_obk_11_Script_SetupMusic;
extern MapSettings TTYD64_obk_11_Header;
extern EvtScript TTYD64_obk_11_Script_CreateExitTriggers;
extern EntryList TTYD64_obk_11_EntryList;

// clang-format off
static s32 TTYD64_obk_11_GetTattleMsg;

static s32 TTYD64_obk_11_GetTattle(void) {
    return TTYD64_obk_11_GetTattleMsg;
}

EvtScript TTYD64_obk_11_Script_EnterMap = {
    Call(SetPlayerPos, -59, -6, -51)
    Wait(1)
    Call(DisablePlayerPhysics, 1)
    Call(DisablePartnerAI, 0)
    Call(SetNpcPos, -4, LVar0, LVar1, LVar2)
    Wait(1)
    Call(SetPlayerJumpscale, Float(1.0))
    Call(PlayerJump, -59, -6, -51, 15)
    Call(SetNpcPos, -4, -59, -6, -51)
    Call(EnablePartnerAI)
    Wait(10)
    Call(DisablePlayerPhysics, 0)
    Return
    End
};

EvtScript TTYD64_obk_11_Script_Main = {
    Set(GameByte(425), 13)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeItemEntity, 387, 28, 307, -61, 17, GameFlag(5091))
    Exec(TTYD64_obk_11_Script_SetupMusic)
    Exec(TTYD64_obk_11_Script_EnterMap)
    Exec(TTYD64_obk_11_Script_CreateExitTriggers)
    Return
    End
};

EvtScript TTYD64_obk_11_Script_Exit0 = {
    Call(DisablePlayerPhysics, 1)
    Call(DisablePartnerAI, 0)
    Call(SetPlayerJumpscale, Float(1.0))
    Call(SetPlayerAnimation, 0x10002)
    Call(SetPlayerAnimation, 0x10006)
    Wait(10)
    Call(PlayerJump, 0, -65, 0, 22)
    Wait(5)
    Call(GotoMap, (Bytecode) "obk_02", 3)
    Return
    End
};

u8 TTYD64_obk_11_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x37, 0x4F, 0x57, 0x0C, 0xF7, 0x54, 0x48, 0x49,
    0x53, 0xF7, 0x4D, 0x41, 0x4E, 0x53, 0x49, 0x4F, 0x4E, 0xF7, 0x49, 0x53,
    0xF7, 0x46, 0x49, 0x4C, 0x4C, 0x45, 0x44, 0xF7, 0x57, 0x49, 0x54, 0x48,
    0xF7, 0x41, 0xF0, 0x42, 0x55, 0x4E, 0x43, 0x48, 0xF7, 0x4F, 0x46, 0xF7,
    0x53, 0x45, 0x43, 0x52, 0x45, 0x54, 0xF7, 0x50, 0x41, 0x53, 0x53, 0x41,
    0x47, 0x45, 0x53, 0x0E, 0xF0, 0xF1, 0xFB, 0x29, 0xF7, 0x48, 0x4F, 0x50,
    0x45, 0xF7, 0x54, 0x48, 0x45, 0x52, 0x45, 0x07, 0x53, 0xF7, 0x41, 0x54,
    0xF7, 0x4C, 0x45, 0x41, 0x53, 0x54, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0x54,
    0x48, 0x49, 0x4E, 0x47, 0xF0, 0x47, 0x4F, 0x4F, 0x44, 0xF7, 0x41, 0x52,
    0x4F, 0x55, 0x4E, 0x44, 0xF7, 0x48, 0x45, 0x52, 0x45, 0xF7, 0x2D, 0x41,
    0x52, 0x49, 0x4F, 0x0E, 0xF0, 0xF1, 0xFD
};

EvtScript TTYD64_obk_11_Script_SetupMusic = {
    IfLt(GameByte(0), -16)
        Call(SetMusic, 0, 27, 0, 8)
    Else
        Call(SetMusic, 0, 28, 0, 8)
    EndIf
    Call(ClearAmbientSounds, 250)
    Return
    End
};

MapSettings TTYD64_obk_11_Header = {
    .main = &TTYD64_obk_11_Script_Main,
    .entryList = &TTYD64_obk_11_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_obk_11_GetTattle },
};

EvtScript TTYD64_obk_11_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_obk_11_Script_Exit0, 256, 2, 1, 0)
    Return
    End
};

EntryList TTYD64_obk_11_EntryList = {
    { -8.0f, 0.0f, -8.0f, -45.0f },
};

MapConfig TTYD64_mapcfg_obk_11 = {
    .id = "obk_11",
    .settings = &TTYD64_obk_11_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 1,
};
// clang-format on

void TTYD64_nm_Install_obk_11(void) {
    TTYD64_obk_11_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_obk_11_String_Tattle);
}
