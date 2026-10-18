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

extern NpcGroupList osr_02_DefaultNPCs;
extern EvtScript osr_02_EVS_BindExitTriggers;
extern EvtScript osr_02_EVS_Main;
extern EvtScript osr_02_EVS_MakeEntities;
extern EvtScript osr_02_EVS_Scene_ReturnStarRod;
extern NpcGroupList osr_02_PeachNPCs;
extern MapSettings osr_02_settings;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(FadeOutMusic);
API_CALLABLE(GetCurrentPartnerID);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetLoadType);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(HidePlayerShadow);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerImgFXFlags);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(UpdatePlayerImgFX);
API_CALLABLE(UseDoorSounds);
API_CALLABLE(osr_02_SetAvailableDisguise);

extern EntryList TTYD64_osr_02_EntryList;
extern EvtScript TTYD64_osr_02_Script_Main;
extern EvtScript TTYD64_osr_02_Script_EnterVerticalPipe;
extern EvtScript TTYD64_osr_02_Script_EnterMap;
extern EvtScript TTYD64_osr_02_Script_MakeEntities;
extern EvtScript TTYD64_osr_02_Script_GoToMap_Warp;

// clang-format off
EntryList TTYD64_osr_02_EntryList = {
    { -205.0f, 0.0f, 55.0f, 135.0f },
    { 0.0f, 20.0f, -290.0f, 180.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 259.0f, 35.0f, -21.0f, -180.0f },
};

EvtScript TTYD64_osr_02_Script_Main = {
    Set(GameByte(425), 26)
    IfGt(GameByte(0), 94)
        Set(GameFlag(1994), 1)
    EndIf
    Call(SetSpriteShading, 0x40000)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    IfEq(GameByte(0), 58)
        Call(osr_02_SetAvailableDisguise, 3)
        Call(MakeNpcs, 0, Ref(osr_02_PeachNPCs))
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(2)
        Call(MakeNpcs, 0, Ref(osr_02_DefaultNPCs))
    EndSwitch
    ExecWait(osr_02_EVS_MakeEntities)
    IfEq(GameFlag(509), 0)
        Call(PlayEffect_impl, 32, 3, Float(-269.1689453125), Float(50.0), Float(100.220703125), 1, LVar0, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 3, Float(-2.6025390625), Float(50.0), Float(161.5830078125), 1, LVar0, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 3, Float(182.146484375), Float(50.0), Float(158.033203125), 1, LVar0, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 3, Float(346.9384765625), Float(50.0), Float(31.861328125), 1, LVar0, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 3, Float(291.044921875), Float(86.2060546875), Float(-191.08203125), 1, LVar0, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 3, Float(-105.3916015625), Float(70.0), Float(-203.115234375), 1, LVar0, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 3, Float(-52.5), Float(70.0), Float(-233.7373046875), 1, LVar0, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 3, Float(52.5), Float(70.0), Float(-233.7373046875), 1, LVar0, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 3, Float(108.2294921875), Float(70.0), Float(-200.599609375), 1, LVar0, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(EnableGroup, 42, 0)
    EndIf
    IfGe(GameByte(0), 94)
        Call(FadeOutMusic, 0, 500)
    EndIf
    Exec(TTYD64_osr_02_Script_EnterMap)
    Wait(1)
    IfEq(GameByte(0), 94)
        Set(GameByte(0), 95)
    EndIf
    Return
    End
};

EvtScript TTYD64_osr_02_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_osr_02_Script_EnterMap = {
    Call(GetLoadType, LVar1)
    IfEq(LVar1, 1)
        Exec(EnterSavePoint)
        Exec(osr_02_EVS_BindExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Call(UseDoorSounds, 1)
        Set(LVar2, 49)
        Set(LVar3, -1)
        ExecWait(EnterSingleDoor)
    CaseEq(1)
        Call(UseDoorSounds, 2)
        Set(LVar2, 46)
        Set(LVar3, 44)
        ExecWait(EnterDoubleDoor)
    CaseEq(2)
        Exec(osr_02_EVS_Scene_ReturnStarRod)
    CaseEq(3)
        Set(LVarA, Ref(osr_02_EVS_BindExitTriggers))
        ExecWait(TTYD64_osr_02_Script_EnterVerticalPipe)
    EndSwitch
    Call(GetEntryID, LVar0)
    IfNe(LVar0, 3)
        Exec(osr_02_EVS_BindExitTriggers)
    EndIf
    Return
    End
};

EvtScript TTYD64_osr_02_Script_MakeEntities = {
    IfEq(GameFlag(509), 1)
        Return
    EndIf
    IfLt(GameByte(0), 89)
        Return
    EndIf
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), 180, 60, -15, 0, 142, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1643))
    Call(MakeEntity, Ref(Entity_SavePoint), -100, 60, -50, 0, 0x80000000)
    Call(MakeEntity, Ref(Entity_BlueWarpPipe), 259, 0, -21, 0, 3, Ref(TTYD64_osr_02_Script_GoToMap_Warp), 1, 0x80000000)
    Return
    End
};

EvtScript TTYD64_osr_02_Script_GoToMap_Warp = {
    Call(GotoMap, (Bytecode) "osr_01", 4)
    Wait(100)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_osr_02(void) {
    osr_02_settings.entryList = &TTYD64_osr_02_EntryList;
    osr_02_settings.entryCount = 4;
    Mod_ReplaceScript("TTYD64", &osr_02_EVS_Main, &TTYD64_osr_02_Script_Main);
    Mod_ReplaceScript("TTYD64", &osr_02_EVS_MakeEntities, &TTYD64_osr_02_Script_MakeEntities);
}
