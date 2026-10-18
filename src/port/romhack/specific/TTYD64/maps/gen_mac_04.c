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

extern EvtScript mac_04_EVS_BindExitTriggers;
extern EvtScript mac_04_EVS_EnterMap;
extern EvtScript mac_04_EVS_ExitToybox;
extern EvtScript mac_04_EVS_ExitWalk_mac_02_0;
extern EvtScript mac_04_EVS_ExitWalk_mac_05_0;
extern EvtScript mac_04_EVS_NpcInteract_ChetRippo;
extern EvtScript mac_04_EVS_Scene_WishingToadKid;
extern ShopItemData mac_04_Inventory[];
extern MapSettings mac_04_settings;

API_CALLABLE(AddCoin);
API_CALLABLE(ContinueSpeech);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GetCurrentPartnerID);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetPartnerInUse);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(HidePlayerShadow);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(InterruptUsePartner);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtNpc);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(SetMessageText);
API_CALLABLE(SetMessageValue);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerFlagBits);
API_CALLABLE(SetPlayerImgFXFlags);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(ShowChoice);
API_CALLABLE(ShowCoinCounter);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(UpdatePlayerImgFX);
API_CALLABLE(UseExitHeading);
API_CALLABLE(mac_04_EnforceNewStatLimits);
API_CALLABLE(mac_04_ForceStatusBarToAppear);
API_CALLABLE(mac_04_GetCurrentStatMaxima);
API_CALLABLE(mac_04_GetCurrentStatValues);
API_CALLABLE(mac_04_GetPlayerCoins);
API_CALLABLE(mac_04_SetNightFogParams);
API_CALLABLE(mac_04_SetNightTintMode);
API_CALLABLE(mac_04_SetStatusBarIgnoreChanges);
API_CALLABLE(mac_04_SetStatusBarRespondToChanges);

extern EvtScript TTYD64_mac_04_Script_Exit3;
extern EvtScript TTYD64_mac_04_Script_EnterWalk_80242280;
extern ShopItemData TTYD64_mac_04_ShopInventory_80243C6C[];
extern EvtScript TTYD64_mac_04_Script_Interact_80249184;
extern EvtScript TTYD64_mac_04_Script_EnterVerticalPipe;
extern EvtScript TTYD64_mac_04_Script_ExitVerticalPipe;
extern EvtScript TTYD64_mac_04_Script_80242238;
extern EntryList TTYD64_mac_04_EntryList;
extern EvtScript TTYD64_mac_04_Script_Exit2;
extern EvtScript TTYD64_mac_04_Script_GotoMap_Exit3;

// clang-format off
EvtScript TTYD64_mac_04_Script_Exit3 = {
    SetGroup(27)
    Set(LVarA, 7)
    Set(LVarB, 84)
    Set(LVarC, Ref(TTYD64_mac_04_Script_GotoMap_Exit3))
    ExecWait(TTYD64_mac_04_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_mac_04_Script_EnterWalk_80242280 = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(2)
        Exec(mac_04_EVS_BindExitTriggers)
        Exec(mac_04_EVS_ExitToybox)
        Thread
            Wait(20)
            Set(MapFlag(10), 1)
        EndThread
    CaseEq(3)
        Exec(mac_04_EVS_BindExitTriggers)
        Call(SetPlayerPos, -420, 20, -95)
        Call(SetNpcPos, -4, -420, 20, -65)
        Thread
            Wait(20)
            Set(MapFlag(10), 1)
        EndThread
    CaseEq(4)
        Call(mac_04_SetNightTintMode)
        Call(mac_04_SetNightFogParams, 0, 0, 0, 0, 0, 0, 0, 950, 1000)
        Exec(mac_04_EVS_Scene_WishingToadKid)
    CaseEq(5)
        Exec(mac_04_EVS_BindExitTriggers)
    CaseEq(7)
        Set(LVarA, Ref(mac_04_EVS_BindExitTriggers))
        Exec(TTYD64_mac_04_Script_EnterVerticalPipe)
    CaseDefault
        Set(LVar0, Ref(mac_04_EVS_BindExitTriggers))
        Exec(EnterWalk)
    EndSwitch
    Return
    End
};

ShopItemData TTYD64_mac_04_ShopInventory_80243C6C[] = {
    { .itemID = 398, .price = 5, .descMsg = 0x230133 },
    { .itemID = 410, .price = 15, .descMsg = 0x23013E },
    { .itemID = 130, .price = 20, .descMsg = 0x240002 },
    { .itemID = 412, .price = 8, .descMsg = 0x230140 },
    { .itemID = 139, .price = 10, .descMsg = 0x240008 },
    { .itemID = 140, .price = 20, .descMsg = 0x24000A },
    { .itemID = 0, .price = 0, .descMsg = 0x000000 },
};

EvtScript TTYD64_mac_04_Script_Interact_80249184 = {
    IfEq(GameFlag(291), 0)
        Set(LVar0, 0x600A8)
        Set(GameFlag(291), 1)
    Else
        Set(LVar0, 0x600A9)
    EndIf
    Call(mac_04_SetStatusBarIgnoreChanges)
    Call(SpeakToPlayer, 13, 0xA60004, 0xA60001, 0, LVar0)
    Call(ShowCoinCounter, 1)
    Call(ShowChoice, 0x1E000E)
    IfNe(LVar0, 0)
        Call(ShowCoinCounter, 0)
        Call(ContinueSpeech, 13, 0xA60004, 0xA60001, 0, 0x600AA)
        Call(mac_04_SetStatusBarRespondToChanges)
        Return
    EndIf
    Call(mac_04_GetPlayerCoins)
    IfLt(LVar0, 39)
        Call(ShowCoinCounter, 0)
        Call(ContinueSpeech, 13, 0xA60004, 0xA60001, 0, 0x600AB)
        Call(mac_04_SetStatusBarRespondToChanges)
        Return
    EndIf
    Call(mac_04_GetCurrentStatValues)
    Call(SetMessageValue, LVar0, 0)
    Call(SetMessageValue, LVar1, 1)
    Call(SetMessageValue, LVar2, 2)
    Call(ContinueSpeech, 13, 0xA60004, 0xA60001, 0, 0x600AC)
    Call(ShowChoice, 0x1E000B)
    IfEq(LVar0, 3)
        Call(ShowCoinCounter, 0)
        Call(ContinueSpeech, 13, 0xA60004, 0xA60001, 0, 0x600AD)
        Call(mac_04_SetStatusBarRespondToChanges)
        Return
    EndIf
    Set(LVar2, 0)
    Call(mac_04_GetCurrentStatMaxima, LVar3, LVar4, LVar5)
    Switch(LVar0)
    CaseEq(0)
        IfGt(LVar3, 85)
            Set(LVar2, 1)
        EndIf
        Set(LVar1, 0x1D00D1)
    CaseEq(1)
        IfGt(LVar4, 85)
            Set(LVar2, 1)
        EndIf
        Set(LVar1, 0x1D00D2)
    CaseEq(2)
        IfGt(LVar5, 93)
            Set(LVar2, 1)
        EndIf
        Set(LVar1, 0x1D00D3)
    EndSwitch
    Set(LVarA, LVar0)
    IfEq(LVar2, 1)
        Call(ShowCoinCounter, 0)
        Call(ContinueSpeech, 13, 0xA60004, 0xA60001, 0, 0x600B1)
        Call(mac_04_SetStatusBarRespondToChanges)
        Return
    EndIf
    Call(AddCoin, -39)
    Call(ShowCoinCounter, 0)
    Call(SetMessageText, LVar1, 0)
    Call(ContinueSpeech, 13, 0xA60004, 0xA60001, 0, 0x600AE)
    Wait(10)
    Call(SetNpcAnimation, 13, 0xA60005)
    Wait(10)
    Call(PlaySoundAtNpc, 13, 587, 0)
    Call(GetNpcPos, 13, LVar6, LVar7, LVar8)
    Add(LVar7, 26)
    Call(PlayEffect_impl, 56, 0, LVar6, LVar7, LVar8, 1, 60, 0, 0, 0, 0, 0, 0, 0)
    Call(SetNpcAnimation, 13, 0xA60006)
    Wait(80)
    Call(SetNpcAnimation, 13, 0xA60001)
    Call(TTYD64_mac_04_AdjustStatMaxima)
    Call(mac_04_EnforceNewStatLimits, LVar6)
    IfEq(LVar6, 0)
        Set(LVar7, 0x600AF)
    Else
        Set(LVar7, 0x600B0)
    EndIf
    Call(SpeakToPlayer, 13, 0xA60004, 0xA60001, 0, LVar7)
    Wait(10)
    Call(GetNpcPos, 13, LVar0, LVar1, LVar2)
    Call(PlaySoundAtNpc, 13, 8344, 0)
    Call(PlayEffect_impl, 1, LVar0, LVar1, LVar2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0)
    Call(SetNpcPos, 13, 0, -1000, 0)
    Set(AreaFlag(50), 1)
    Call(mac_04_ForceStatusBarToAppear)
    Return
    End
};

EvtScript TTYD64_mac_04_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_mac_04_Script_ExitVerticalPipe = {
    Call(TTYD64_Pipe_CheckDownInput)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(GetPartnerInUse, LVar0)
    IfNe(LVar0, 0)
        Call(GetCurrentPartnerID, LVar1)
        IfNe(LVar1, 6)
            Return
        Else
            Call(InterruptUsePartner)
            Call(DisablePlayerInput, 1)
        EndIf
    Else
        Call(DisablePlayerInput, 1)
    EndIf
    SetGroup(27)
    Call(TTYD64_Pipe_SetAnimFlag)
    Call(DisablePlayerPhysics, 1)
    Call(HidePlayerShadow, 1)
    Set(LVar0, LVarA)
    Call(TTYD64_Pipe_GetEntryCoords)
    Call(PlayerMoveTo, LVar1, LVar3, 3)
    Set(LVar0, LVarA)
    Call(TTYD64_Pipe_GetEntryCoords)
    Call(SetPlayerPos, LVar1, LVar2, LVar3)
    Call(SetPlayerFlagBits, 0x200000, 1)
    Call(TTYD64_Pipe_GetCameraYaw)
    Call(InterpPlayerYaw, LVar0, 0)
    Wait(2)
    Call(SetPlayerFlagBits, 0x200000, 0)
    Call(PlaySound, 355)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Thread
        Wait(4)
        Loop(40)
            Sub(LVar1, 1)
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Call(SetPlayerImgFXFlags, 2048)
    Call(UpdatePlayerImgFX, 0x10002, 5, 2, 1, 1, 0)
    Wait(25)
    ExecWait(LVarC)
    Return
    End
};

EvtScript TTYD64_mac_04_Script_80242238 = {
    BindTrigger(mac_04_EVS_ExitWalk_mac_05_0, 0x80000, 65, 1, 0)
    BindTrigger(mac_04_EVS_ExitWalk_mac_02_0, 0x80000, 66, 1, 0)
    BindTrigger(TTYD64_mac_04_Script_Exit2, 0x80000, 83, 1, 0)
    BindTrigger(TTYD64_mac_04_Script_Exit3, 0x80000, 84, 1, 0)
    Return
    End
};

EntryList TTYD64_mac_04_EntryList = {
    { 610.0f, 0.0f, 0.0f, 280.0f },
    { -420.0f, 0.0f, 430.0f, 35.0f },
    { -490.0f, 20.0f, -150.0f, 180.0f },
    { -420.0f, 20.0f, -95.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f, 0.0f },
    { -420.0f, 20.0f, 235.0f, 270.0f },
    { -325.0f, 20.0f, -48.0f, -180.0f },
    { 261.0f, 52.0f, -599.0f, -360.0f },
};

EvtScript TTYD64_mac_04_Script_Exit2 = {
    Call(UseExitHeading, 60, 6)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "mac_07", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_mac_04_Script_GotoMap_Exit3 = {
    Call(GotoMap, (Bytecode) "tyd_00", 0)
    Wait(100)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_mac_04(void) {
    mac_04_settings.entryList = &TTYD64_mac_04_EntryList;
    mac_04_settings.entryCount = 8;
    Mod_ReplaceScript("TTYD64", &mac_04_EVS_EnterMap, &TTYD64_mac_04_Script_EnterWalk_80242280);
    memcpy(&mac_04_Inventory, &TTYD64_mac_04_ShopInventory_80243C6C, sizeof(TTYD64_mac_04_ShopInventory_80243C6C));
    Mod_ReplaceScript("TTYD64", &mac_04_EVS_NpcInteract_ChetRippo, &TTYD64_mac_04_Script_Interact_80249184);
    Mod_ReplaceScript("TTYD64", &mac_04_EVS_BindExitTriggers, &TTYD64_mac_04_Script_80242238);
}
