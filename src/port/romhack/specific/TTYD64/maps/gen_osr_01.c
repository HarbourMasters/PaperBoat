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

extern NpcGroupList osr_01_DefaultNPCs;
extern EvtScript osr_01_EVS_BindExitTriggers;
extern EvtScript osr_01_EVS_Main;
extern EvtScript osr_01_EVS_PlaySong_Starship;
extern EvtScript osr_01_EVS_Scene_Wishing;
extern EvtScript osr_01_EVS_SetupMusic;
extern EvtScript osr_01_EVS_TexPan_Fountain;
extern MapSettings osr_01_settings;

API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableModel);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GetCurrentPartnerID);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(HidePlayerShadow);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtF);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerImgFXFlags);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(UpdatePlayerImgFX);

extern EvtScript TTYD64_osr_01_Script_InitNewStuff;
extern EntryList TTYD64_osr_01_EntryList;
extern EvtScript TTYD64_osr_01_Script_Main_EnterWalk;
extern EvtScript TTYD64_osr_01_Script_EnterVerticalPipe;
extern EvtScript TTYD64_osr_01_Script_EnterMap;
extern EvtScript TTYD64_osr_01_Script_80240B40;
extern EvtScript TTYD64_osr_01_Script_GoToMap_Warp;

// clang-format off
EvtScript TTYD64_osr_01_Script_InitNewStuff = {
    Call(MakeEntity, Ref(Entity_BlueWarpPipe), 138, 0, 519, 0, 4, Ref(TTYD64_osr_01_Script_GoToMap_Warp), 5740, 0x80000000)
    Return
    End
};

EntryList TTYD64_osr_01_EntryList = {
    { 0.0f, 0.0f, 604.0f, 0.0f },
    { 612.0f, 0.0f, 111.0f, 270.0f },
    { 0.0f, 0.0f, -290.0f, 180.0f },
    { 0.0f, -1000.0f, 0.0f, 0.0f },
    { 138.0f, 35.0f, 519.0f, -180.0f },
};

EvtScript TTYD64_osr_01_Script_Main_EnterWalk = {
    Set(GameByte(425), 25)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Set(AreaFlag(1), 0)
    Set(GameFlag(1963), 1)
    Call(MakeNpcs, 0, Ref(osr_01_DefaultNPCs))
    ExecWait(osr_01_EVS_PlaySong_Starship)
    Exec(osr_01_EVS_TexPan_Fountain)
    Call(PlaySoundAtF, 0x8000005A, 1, 300, 2, 399)
    Exec(TTYD64_osr_01_Script_EnterMap)
    Wait(1)
    Return
    End
};

EvtScript TTYD64_osr_01_Script_EnterVerticalPipe = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(DisablePartnerAI, 0)
    Call(HidePlayerShadow, 1)
    Call(SetPlayerAnimation, 0x10000)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Call(EnableNpcShadow, -4, 0)
        Call(SetNpcPos, -4, 0, -1000, 0)
    EndIf
    Call(GetEntryID, LVar0)
    Call(TTYD64_Pipe_GetEntryCoords)
    Sub(LVar2, 40)
    Call(SetPlayerPos, LVar1, LVar2, LVar3)
    Call(InterpPlayerYaw, LVar4, 0)
    Call(PlaySound, 355)
    Call(SetPlayerImgFXFlags, 256)
    Call(UpdatePlayerImgFX, 0x10000, 5, 2, 1, 1, 0)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Loop(40)
        Add(LVar1, 1)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Wait(3)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Thread
            Call(DisablePartnerAI, 0)
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Sub(LVar2, 3)
            Call(SetNpcPos, -4, LVar0, LVar1, LVar2)
            Call(SetNpcFlagBits, -4, 2, 0)
            Call(EnablePartnerAI)
            Call(EnableNpcShadow, -4, 1)
        EndThread
    EndIf
    Wait(2)
    Call(UpdatePlayerImgFX, 0x10000, 0, 0, 0, 0, 0)
    Wait(1)
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Call(HidePlayerShadow, 0)
    Label(0)
    Call(TTYD64_Pipe_GetCurrentFloor)
    Wait(1)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Exec(LVarA)
    Return
    End
};

EvtScript TTYD64_osr_01_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(3)
        Call(EnableModel, 40, 0)
        Exec(osr_01_EVS_Scene_Wishing)
    CaseEq(4)
        IfEq(GameFlag(5740), 0)
            Call(DisablePlayerInput, 1)
            Call(DisablePlayerPhysics, 1)
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Call(SetNpcPos, -4, LVar0, LVar1, LVar2)
            Call(SetPlayerPos, LVar0, -1000, LVar2)
            Wait(30)
            Call(PlaySound, 8334)
            Set(GameFlag(5740), 1)
            Wait(30)
            Call(SetPlayerActionState, 0)
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Call(SetNpcPos, -4, LVar0, LVar1, LVar2)
            Call(DisablePlayerPhysics, 0)
            Call(DisablePlayerInput, 0)
        EndIf
        Set(LVarA, Ref(osr_01_EVS_BindExitTriggers))
        ExecWait(TTYD64_osr_01_Script_EnterVerticalPipe)
    CaseDefault
        Set(LVar0, Ref(osr_01_EVS_BindExitTriggers))
        Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_osr_01_Script_80240B40 = {
    Switch(GameByte(0))
    CaseRange(-13, 5)
        Call(SetMusic, 0, 74, 0, 6)
    CaseDefault
        Call(SetMusic, 0, 0, 0, 6)
    EndSwitch
    Exec(TTYD64_osr_01_Script_InitNewStuff)
    Return
    End
};

EvtScript TTYD64_osr_01_Script_GoToMap_Warp = {
    Call(GotoMap, (Bytecode) "osr_02", 3)
    Wait(100)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_osr_01(void) {
    osr_01_settings.entryList = &TTYD64_osr_01_EntryList;
    osr_01_settings.entryCount = 5;
    Mod_ReplaceScript("TTYD64", &osr_01_EVS_Main, &TTYD64_osr_01_Script_Main_EnterWalk);
    Mod_ReplaceScript("TTYD64", &osr_01_EVS_SetupMusic, &TTYD64_osr_01_Script_80240B40);
}
