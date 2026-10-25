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
#include "port/romhack/specific/TTYD64/world/tp.h"

extern NpcSettings TTYD64_imp_Mover_NpcSettings_Mover;
extern u8 TTYD64_imp_Mover_String_Choice_Mover[];
extern u8 TTYD64_imp_Mover_String_Mover_CloseYourEyes[];
extern u8 TTYD64_imp_Mover_String_Mover_Hi[];
extern u8 TTYD64_imp_Mover_String_Mover_NotEnoughCoins[];
extern u8 TTYD64_imp_Mover_Tattle_Mover[];

API_CALLABLE(tik_15_CheckPlayerHasEnoughRoom);

extern EvtScript TTYD64_pit_11_Script_Mover_Interact;
extern EvtScript TTYD64_pit_11_Script_Rowf_Interact;
extern EvtScript TTYD64_pit_11_Script_EnterTopPipe;
extern EvtScript TTYD64_pit_11_Script_ExitHorizontalPipe;
extern EvtScript TTYD64_pit_11_Script_ExitVerticalPipe;
extern EvtScript TTYD64_pit_11_Script_AssignFlag_GiantChest;
extern EvtScript TTYD64_pit_11_Script_SetupTexturePan;
extern NpcData TTYD64_pit_11_NpcGroup_Rowf[];
extern NpcData TTYD64_pit_11_NpcGroup_Mover[];
extern EvtScript TTYD64_pit_11_Script_GoToNextMap;
extern EvtScript TTYD64_pit_11_Script_EnterMap;
extern EvtScript TTYD64_pit_11_Script_UpdateInventoryPrices;
extern u8 TTYD64_pit_11_Tattle_Rowf[];
extern EvtScript TTYD64_pit_11_Script_ShowPipe;
extern u8 TTYD64_pit_11_String_Tattle[];
extern EvtScript TTYD64_pit_11_Script_MakeEntities;
extern EvtScript TTYD64_pit_11_Script_Main;
extern EvtScript TTYD64_pit_11_Script_GiveItem;
extern u8 TTYD64_pit_11_String_Rowf_Hi[];
extern EvtScript TTYD64_pit_11_Script_TexturePan_Update;
extern EvtScript TTYD64_pit_11_Script_UpdateFloorTheme;
extern u8 TTYD64_pit_11_String_Rowf_AskConfirmation[];
extern u8 TTYD64_pit_11_String_Rowf_NoCoins[];
extern u8 TTYD64_pit_11_String_Rowf_NoInventory[];
extern EvtScript TTYD64_pit_11_Script_ReadSign_Entity_Sign;
extern EvtScript TTYD64_pit_11_Script_ShowGotItem;
extern EvtScript TTYD64_pit_11_Script_Exit1;
extern EvtScript TTYD64_pit_11_Script_Exit0;
extern u8 TTYD64_pit_11_String_Rowf_Bye[];
extern EvtScript TTYD64_pit_11_Script_OpenChest;
extern EvtScript TTYD64_pit_11_Script_CreateExitTriggers;
extern MapSettings TTYD64_pit_11_Header;
extern u8 TTYD64_pit_11_String_Rowf_RelookInventory[];
extern EvtScript TTYD64_pit_11_Script_GotoMap_Exit0;
extern u8 TTYD64_pit_11_String_Rowf_ThankYou[];
extern EvtScript TTYD64_pit_11_Script_SetupMusic;
extern EvtScript TTYD64_pit_11_Script_Init_Rowf;
extern EntryList TTYD64_pit_11_EntryList;
extern NpcSettings TTYD64_pit_11_NpcSettings_Rowf;
s32 TTYD64_pit_11_Function_Init(void);
extern EvtScript TTYD64_pit_11_Script_GotoMap_Exit1;
extern NpcGroupList TTYD64_pit_11_NpcGroupList_pit11;
extern EvtScript TTYD64_pit_11_Script_Init_Mover;
extern u8 TTYD64_pit_11_String_ReadSign_Entity_Sign[];
extern NpcGroupList TTYD64_pit_11_NpcGroupList_Mover;
extern char TTYD64_pit_11_ASCII_NextFloor[];
extern char TTYD64_pit_11_ASCII_pit12[];

// clang-format off
static s32 TTYD64_pit_11_GetTattleMsg;

static s32 TTYD64_pit_11_GetTattle(void) {
    return TTYD64_pit_11_GetTattleMsg;
}

EvtScript TTYD64_pit_11_Script_Mover_Interact = {
    Call(SetMessageValue, AreaByte(0), 0)
    Call(SpeakToPlayer, -1, 0x960104, 0x960101, 0, (Bytecode) TTYD64_imp_Mover_String_Mover_Hi)
    Call(ShowChoice, (Bytecode) TTYD64_imp_Mover_String_Choice_Mover)
    Switch(LVar0)
    CaseOrEq(0)
    CaseOrEq(1)
    CaseOrEq(2)
        Set(LVar4, LVar0)
        Call(AddCoin, 0)
        Switch(LVar4)
        CaseEq(0)
            Set(LVar1, 10)
            Set(LVar2, 2)
        CaseEq(1)
            Set(LVar1, 30)
            Set(LVar2, 5)
        CaseEq(2)
            Set(LVar1, 30)
            Set(LVar2, 0)
        EndSwitch
        IfLt(LVar0, LVar1)
            Call(ContinueSpeech, -1, 0x960104, 0x960101, 0, (Bytecode) TTYD64_imp_Mover_String_Mover_NotEnoughCoins)
            Return
        EndIf
        Mul(LVar1, -1)
        Call(AddCoin, LVar1)
        Call(ContinueSpeech, -1, 0x960104, 0x960101, 0, (Bytecode) TTYD64_imp_Mover_String_Mover_CloseYourEyes)
        Set(LVar1, AreaByte(0))
        Add(LVar1, LVar2)
        IfEq(LVar2, 0)
            Set(LVar1, 0)
        EndIf
        Call(GetCurrentPartnerID, LVar0)
        IfNe(LVar0, 0)
            Call(TTYD64_tp_SwitchPartners, 0, LVarA)
            Wait(30)
            Call(TTYD64_WriteField, TTYD64_F_GPLAYERDATA_12_1U, LVarA)
        EndIf
        Thread
            Wait(135)
            Call(TTYD64_SetUnderwaterFollowsMover, 1)
            Call(PlayEffect_impl, 93, 0, 0, 0, 0, 0, 0, 0, 1000)
        EndThread
        Set(LVar0, Float(0.0))
        Loop(0)
            AddF(LVar0, Float(0.2001953125))
            Call(UpdatePlayerImgFX, 0, 4, 0, LVar0, 0, 0)
            Call(SetNpcImgFXParams, -1, 4, 0, LVar0, 0, 0)
            Wait(3)
            IfEq(LVar0, Float(12.0))
                BreakLoop
            EndIf
        EndLoop
        Call(PlaySound, 220)
        Thread
            Wait(38)
            Call(TTYD64_SetUnderwaterFollowsMover, 0)
        EndThread
        Set(LVar0, LVar1)
        IfNe(LVar0, 0)
            ExecWait(TTYD64_pit_11_Script_GoToNextMap)
        Else
            Set(AreaByte(0), 0)
            Call(GotoMap, (Bytecode) "pit_00", 2)
        EndIf
        EndCaseGroup
    CaseEq(3)
        Call(CloseMessage)
        Return
    EndSwitch
    Return
    End
};

EvtScript TTYD64_pit_11_Script_Rowf_Interact = {
    Call(SpeakToPlayer, -1, 0xA7000C, 0xA70009, 0, (Bytecode) TTYD64_pit_11_String_Rowf_Hi)
    Call(ShowChoice, 0x1E000D)
    IfNe(LVar0, 0)
        Call(CloseMessage)
        Call(SpeakToPlayer, -1, 0xA7000C, 0xA70009, 0, (Bytecode) TTYD64_pit_11_String_Rowf_Bye)
        Return
    EndIf
    Call(CloseMessage)
    Label(0)
    Call(ShowCoinCounter, 1)
    Call(TTYD64_SetShopBuyPopup, 1)
    Call(TTYD64_tp_ShowShopInventory)
    Call(TTYD64_SetShopBuyPopup, 0)
    Call(ShowCoinCounter, 0)
    IfEq(LVar0, -1)
        Call(SpeakToPlayer, -1, 0xA7000C, 0xA70009, 0, (Bytecode) TTYD64_pit_11_String_Rowf_Bye)
        Return
    EndIf
    Set(LVar6, LVar0)
    Call(AddCoin, 0)
    IfLt(LVar0, LVar1)
        Call(SpeakToPlayer, -1, 0xA7000C, 0xA70009, 0, (Bytecode) TTYD64_pit_11_String_Rowf_NoCoins)
        Wait(1)
        Goto(0)
    EndIf
    Call(SetMessageText, LVar4, 0)
    Call(SetMessageValue, LVar1, 1)
    Call(SpeakToPlayer, -1, 0xA7000C, 0xA70009, 0, (Bytecode) TTYD64_pit_11_String_Rowf_AskConfirmation)
    Set(LVar3, LVar6)
    Call(ShowChoice, 0x1E000D)
    IfNe(LVar0, 0)
        Call(ContinueSpeech, -1, 0xA7000C, 0xA70009, 0, (Bytecode) TTYD64_pit_11_String_Rowf_RelookInventory)
        Wait(1)
        Goto(0)
    EndIf
    Call(tik_15_CheckPlayerHasEnoughRoom)
    IfEq(LVar0, 0)
        Call(ContinueSpeech, -1, 0xA7000C, 0xA70009, 0, (Bytecode) TTYD64_pit_11_String_Rowf_NoInventory)
        Return
    EndIf
    Call(CloseMessage)
    Mul(LVar1, -1)
    Call(AddCoin, LVar1)
    Set(LVar0, LVar3)
    Call(ShowGotItem, LVar0, 1, 0)
    Call(AddItem, LVar0, 0)
    Call(SpeakToPlayer, -1, 0xA7000C, 0xA70009, 0, (Bytecode) TTYD64_pit_11_String_Rowf_ThankYou)
    Return
    End
};

EvtScript TTYD64_pit_11_Script_EnterTopPipe = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(HidePlayerShadow, 1)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Call(DisablePartnerAI, 0)
        Call(EnableNpcShadow, -4, 0)
        Call(SetNpcFlagBits, -4, 2, 1)
        Call(SetNpcPos, -4, 0, LVarA, 0)
    EndIf
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
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(SetPlayerImgFXFlags, 256)
    Call(UpdatePlayerImgFX, 0x10000, 5, 2, 1, 1, 0)
    Wait(4)
    Call(PlaySound, 355)
    Loop(40)
        Sub(LVar1, 1)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Wait(1)
    Call(UpdatePlayerImgFX, 0x10000, 0, 0, 0, 0, 0)
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Call(HidePlayerShadow, 0)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Wait(4)
        Call(GetPlayerPos, LVar4, LVar5, LVar6)
        Call(SetNpcPos, -4, LVar4, LVar5, LVar6)
        Call(SetNpcFlagBits, -4, 2, 0)
        Call(EnablePartnerAI)
        Call(EnableNpcShadow, -4, 1)
    EndIf
    Exec(LVarC)
    Return
    End
};

EvtScript TTYD64_pit_11_Script_ExitHorizontalPipe = {
    Call(IsPlayerOnValidFloor, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(GetPlayerActionState, LVar0)
    IfEq(LVar0, 26)
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
    Call(ModifyColliderFlags, 0, LVarB, 0x7FFFFE00)
    Set(LVar0, LVarA)
    Call(TTYD64_Pipe_GetEntryCoords)
    Set(LVar5, LVar1)
    Set(LVar6, LVar2)
    Add(LVar6, 2)
    Set(LVar7, LVar3)
    Set(LVar8, LVar4)
    Add(LVar8, 180)
    IfGe(LVar4, 360)
        Sub(LVar4, 360)
    EndIf
    Call(InterpPlayerYaw, LVar8, 1)
    Wait(1)
    Call(PlaySound, 355)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(SetPlayerPos, LVar0, LVar6, LVar7)
    Call(SetPlayerAnimation, 0x10000)
    Call(SetPlayerImgFXFlags, 2048)
    Call(UpdatePlayerImgFX, 0x10000, 5, 3, 1, 1, 0)
    Thread
        Wait(8)
        Call(HidePlayerShadow, 1)
    EndThread
    Thread
        Wait(3)
        Loop(40)
            Call(TTYD64_Pipe_GetPointInFrontOfPlayer, Float(1.0))
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Wait(25)
    ExecWait(LVarC)
    Return
    End
};

EvtScript TTYD64_pit_11_Script_ExitVerticalPipe = {
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

EvtScript TTYD64_pit_11_Script_AssignFlag_GiantChest = {
    Switch(AreaByte(0))
    CaseEq(10)
        Set(MapVar(0), 235)
        Set(MapVar(1), 2)
        Call(AssignChestFlag, GameFlag(4724))
    CaseEq(20)
        Set(MapVar(0), 375)
        Set(MapVar(1), 2)
        Call(AssignChestFlag, GameFlag(4725))
    CaseEq(30)
        Set(MapVar(0), 256)
        Set(MapVar(1), 2)
        Call(AssignChestFlag, GameFlag(4726))
    CaseEq(40)
        Set(MapVar(0), 367)
        Set(MapVar(1), 2)
        Call(AssignChestFlag, GameFlag(4727))
    CaseEq(50)
        Set(MapVar(0), 455)
        Set(MapVar(1), 1)
        Call(AssignChestFlag, GameFlag(4728))
    CaseEq(60)
        Set(MapVar(0), 297)
        Set(MapVar(1), 2)
        Call(AssignChestFlag, GameFlag(4729))
    CaseEq(70)
        Set(MapVar(0), 323)
        Set(MapVar(1), 2)
        Call(AssignChestFlag, GameFlag(4730))
    CaseEq(80)
        Set(MapVar(0), 288)
        Set(MapVar(1), 2)
        Call(AssignChestFlag, GameFlag(4731))
    CaseEq(90)
        Set(MapVar(0), 276)
        Set(MapVar(1), 2)
        Call(AssignChestFlag, GameFlag(4732))
    CaseEq(100)
        Set(MapVar(0), 374)
        Set(MapVar(1), 2)
        Call(AssignChestFlag, GameFlag(4733))
    EndSwitch
    Return
    End
};

EvtScript TTYD64_pit_11_Script_SetupTexturePan = {
    Call(SetTexPanner, 1, 1)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 50)
        Set(LVar2, 200)
        Set(LVar3, 110)
        Set(LVar4, 500)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_pit_11_Script_TexturePan_Update)
    EndThread
    Thread
        Set(LVar0, 1)
        Set(LVar1, 0)
        Set(LVar2, -200)
        Set(LVar3, -100)
        Set(LVar4, -500)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_pit_11_Script_TexturePan_Update)
    EndThread
    Return
    End
};

NpcData TTYD64_pit_11_NpcGroup_Rowf[] = {
    {
        .id = 1,
        .settings = &TTYD64_pit_11_NpcSettings_Rowf,
        .pos = { 165.0f, 0.0f, -18.0f },
        .flags = 0x00112D09,
        .init = TTYD64_pit_11_Script_Init_Rowf,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00A70109, .walk = 0x00A70102, .run = 0x00A70103, .chase = 0x00A70103, .anim_4 = 0x00A70100, .anim_5 = 0x00A70100, .death = 0x00A70107, .hit = 0x00A70107, .anim_8 = 0x00A70100, .anim_9 = 0x00A70100, .anim_A = 0x00A70100, .anim_B = 0x00A70100, .anim_C = 0x00A70100, .anim_D = 0x00A70100, .anim_E = 0x00A70100, .anim_F = 0x00A70100 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_pit_11_NpcGroup_Mover[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_Mover_NpcSettings_Mover,
        .pos = { -30.0f, 0.0f, 102.0f },
        .flags = 0x00112D09,
        .init = TTYD64_pit_11_Script_Init_Mover,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00960101, .walk = 0x00960102, .run = 0x00960103, .chase = 0x00960103, .anim_4 = 0x00960100, .anim_5 = 0x00960100, .death = 0x00960107, .hit = 0x00960107, .anim_8 = 0x00960100, .anim_9 = 0x00960100, .anim_A = 0x00960100, .anim_B = 0x00960100, .anim_C = 0x00960100, .anim_D = 0x00960100, .anim_E = 0x00960100, .anim_F = 0x00960100 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_pit_11_Script_GoToNextMap = {
    Set(LVar5, LVar0)
    IfGe(LVar0, 100)
        Call(GotoMap, (Bytecode) TTYD64_pit_11_ASCII_pit12, 0)
    Else
        Call(TTYD64_tp_GetReminderFromDiv, LVar5, 10, LVar1)
        IfEq(LVar1, 0)
            Call(TTYD64_tp_SetNextFloorDigit, (Bytecode) TTYD64_pit_11_ASCII_NextFloor, TTYD64_TP_FLOOR_TENS, 49)
            Call(TTYD64_tp_SetNextFloorDigit, (Bytecode) TTYD64_pit_11_ASCII_NextFloor, TTYD64_TP_FLOOR_ONES, 49)
        Else
            Set(LVar1, LVar0)
            Div(LVar1, 10)
            Set(LVar0, 49)
            IfNe(LVar1, 9)
                Add(LVar0, LVar1)
                Call(TTYD64_tp_SetNextFloorDigit, (Bytecode) TTYD64_pit_11_ASCII_NextFloor, TTYD64_TP_FLOOR_ONES, LVar0)
            Else
                Call(TTYD64_tp_SetNextFloorDigit, (Bytecode) TTYD64_pit_11_ASCII_NextFloor, TTYD64_TP_FLOOR_TENS, LVar0)
            EndIf
        EndIf
        Call(GotoMap, (Bytecode) TTYD64_pit_11_ASCII_NextFloor, 0)
    EndIf
    Set(AreaByte(0), LVar5)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_pit_11_Script_EnterMap = {
    Set(LVarA, 0)
    Set(LVarB, 5)
    Set(LVarC, (Bytecode) TTYD64_pit_11_Script_CreateExitTriggers)
    Exec(TTYD64_pit_11_Script_EnterTopPipe)
    Call(ParentColliderToModel, 0, 2)
    Call(ParentColliderToModel, 1, 2)
    Call(TranslateModel, 2, 0, -40, 0)
    Call(UpdateColliderTransform, 0)
    Call(UpdateColliderTransform, 1)
    Exec(TTYD64_pit_11_Script_UpdateFloorTheme)
    Call(RandInt, 100, LVar0)
    IfGt(LVar0, 5)
        Call(SetNpcPos, 0, 0, -1000, 0)
    EndIf
    Call(RandInt, 100, LVar0)
    IfGt(LVar0, 30)
        Call(SetNpcPos, 1, 0, -1000, 0)
    EndIf
    Set(GameFlag(4101), 1)
    Return
    End
};

EvtScript TTYD64_pit_11_Script_UpdateInventoryPrices = {
    Set(LVar5, AreaByte(0))
    Div(LVar5, 10)
    Sub(LVar5, 1)
    Set(LVar0, 0)
    Loop(0)
        Call(TTYD64_tp_GetShopBasePrice, LVar0, LVar2)
        Call(TTYD64_tp_GetShopPrice, LVar0, LVar3)
        IfEq(LVar2, -1)
            BreakLoop
        EndIf
        Div(LVar2, 2)
        Mul(LVar2, LVar5)
        Add(LVar3, LVar2)
        Call(TTYD64_tp_SetShopPrice, LVar0, LVar3)
        Add(LVar0, 1)
        Wait(1)
    EndLoop
    Return
    End
};

u8 TTYD64_pit_11_Tattle_Rowf[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x28, 0x45, 0xF7, 0x49, 0x53, 0xF7, 0x32, 0x4F,
    0x57, 0x46, 0x0C, 0xF7, 0x57, 0x45, 0xF7, 0x43, 0x41, 0x4E, 0xF7, 0x42,
    0x55, 0x59, 0xF7, 0x41, 0xF7, 0x46, 0x45, 0x57, 0xF7, 0x49, 0x54, 0x45,
    0x4D, 0x53, 0xF0, 0x46, 0x4F, 0x52, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0xF7,
    0x43, 0x4F, 0x49, 0x4E, 0x53, 0x0C, 0xF7, 0x4A, 0x55, 0x53, 0x54, 0xF7,
    0x4B, 0x45, 0x45, 0x50, 0xF7, 0x49, 0x4E, 0xF7, 0x4D, 0x49, 0x4E, 0x44,
    0xF0, 0x54, 0x48, 0x41, 0x54, 0xF7, 0x50, 0x52, 0x49, 0x43, 0x45, 0x53,
    0xF7, 0x49, 0x4E, 0x43, 0x52, 0x45, 0x41, 0x53, 0x45, 0xF7, 0x44, 0x45,
    0x50, 0x45, 0x4E, 0x44, 0x49, 0x4E, 0x47, 0xF7, 0x4F, 0x4E, 0xF0, 0x48,
    0x4F, 0x57, 0xF7, 0x44, 0x45, 0x45, 0x50, 0xF7, 0x57, 0x45, 0xF7, 0x41,
    0x52, 0x45, 0xF7, 0x49, 0x4E, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x50, 0x49,
    0x54, 0x0E, 0xF0, 0xF1, 0xFB, 0x22, 0x59, 0xF7, 0x54, 0x48, 0x45, 0xF7,
    0x57, 0x41, 0x59, 0x0C, 0xF7, 0x44, 0x49, 0x44, 0xF7, 0x48, 0x45, 0xF7,
    0x43, 0x4F, 0x4D, 0x45, 0xF7, 0x46, 0x52, 0x4F, 0x4D, 0xF0, 0x34, 0x4F,
    0x41, 0x44, 0xF7, 0x34, 0x4F, 0x57, 0x4E, 0xF7, 0x54, 0x4F, 0xF7, 0x48,
    0x45, 0x52, 0x45, 0x1F, 0xF7, 0x37, 0x4F, 0x57, 0x0C, 0xF7, 0x29, 0xF7,
    0x44, 0x49, 0x44, 0x4E, 0x07, 0x54, 0xF0, 0x4B, 0x4E, 0x4F, 0x57, 0xF7,
    0x48, 0x45, 0xF7, 0x57, 0x41, 0x53, 0xF7, 0x54, 0x48, 0x41, 0x54, 0xF7,
    0x53, 0x54, 0x52, 0x4F, 0x4E, 0x47, 0xF0, 0xF1, 0xFB, 0x2D, 0x41, 0x52,
    0x49, 0x4F, 0x0C, 0xF7, 0x4D, 0x41, 0x59, 0x42, 0x45, 0xF7, 0x48, 0x45,
    0xF7, 0x43, 0x4F, 0x55, 0x4C, 0x44, 0xF7, 0x48, 0x45, 0x4C, 0x50, 0xF7,
    0x55, 0x53, 0xF7, 0x44, 0x45, 0x46, 0x45, 0x41, 0x54, 0xF0, 0x22, 0x4F,
    0x57, 0x53, 0x45, 0x52, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_pit_11_Script_ShowPipe = {
    SetGroup(0)
    SuspendGroup(2)
    Call(DisablePlayerInput, 1)
    Call(PlaySound, 8334)
    Call(MakeLerp, -40, 0, 25, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, 2, 0, LVar0, 10)
        Call(UpdateColliderTransform, 1)
        Call(UpdateColliderTransform, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    ResumeGroup(2)
    Call(DisablePlayerInput, 0)
    Return
    End
};

u8 TTYD64_pit_11_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x34, 0x48, 0x49, 0x53, 0xF7, 0x49, 0x53, 0xF7,
    0x54, 0x48, 0x45, 0xF7, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x4D, 0x45, 0x44,
    0x49, 0x41, 0x54, 0x45, 0xF7, 0x46, 0x4C, 0x4F, 0x4F, 0x52, 0xF7, 0x4F,
    0x46, 0xF0, 0x54, 0x48, 0x45, 0xF7, 0x50, 0x49, 0x54, 0x0C, 0xF7, 0x53,
    0x4F, 0x4D, 0x45, 0x54, 0x49, 0x4D, 0x45, 0x53, 0xF7, 0x32, 0x4F, 0x57,
    0x46, 0xF7, 0x43, 0x41, 0x4E, 0xF7, 0x41, 0x50, 0x50, 0x45, 0x41, 0x52,
    0xF0, 0x48, 0x45, 0x52, 0x45, 0xF7, 0x54, 0x4F, 0xF7, 0x53, 0x45, 0x4C,
    0x4C, 0xF7, 0x55, 0x53, 0xF7, 0x49, 0x54, 0x45, 0x4D, 0x53, 0x0E, 0xF0,
    0xF1, 0xFB, 0x21, 0x4C, 0x53, 0x4F, 0xF7, 0x57, 0x45, 0xF7, 0x43, 0x41,
    0x4E, 0xF7, 0x55, 0x53, 0x45, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x54, 0x55,
    0x42, 0x45, 0xF7, 0x4F, 0x4E, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x4C, 0x45,
    0x46, 0x54, 0xF0, 0x54, 0x4F, 0xF7, 0x47, 0x4F, 0xF7, 0x42, 0x41, 0x43,
    0x4B, 0xF7, 0x54, 0x4F, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x45, 0x4E, 0x54,
    0x52, 0x41, 0x4E, 0x43, 0x45, 0xF7, 0x4F, 0x46, 0xF7, 0x54, 0x48, 0x45,
    0xF0, 0x50, 0x49, 0x54, 0xF0, 0xF1, 0xFB, 0x2A, 0x55, 0x53, 0x54, 0xF7,
    0x4B, 0x45, 0x45, 0x50, 0xF7, 0x49, 0x4E, 0xF7, 0x4D, 0x49, 0x4E, 0x44,
    0xF7, 0x54, 0x48, 0x41, 0x54, 0xF7, 0x57, 0x45, 0xF7, 0x57, 0x49, 0x4C,
    0x4C, 0xF7, 0x48, 0x41, 0x56, 0x45, 0xF0, 0x54, 0x4F, 0xF7, 0x47, 0x4F,
    0xF7, 0x54, 0x48, 0x52, 0x4F, 0x55, 0x47, 0x48, 0xF7, 0x41, 0x4C, 0x4C,
    0xF7, 0x54, 0x48, 0x45, 0xF7, 0x46, 0x4C, 0x4F, 0x4F, 0x52, 0x53, 0xF7,
    0x4F, 0x4E, 0x43, 0x45, 0xF0, 0x41, 0x47, 0x41, 0x49, 0x4E, 0x0E, 0xF1,
    0xFD
};

EvtScript TTYD64_pit_11_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_Signpost), 126, -9, -130, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_pit_11_Script_ReadSign_Entity_Sign)
    Call(MakeEntity, Ref(Entity_BlueSwitch), 41, 0, 80, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_pit_11_Script_ShowPipe)
    Call(MakeEntity, Ref(Entity_GiantChest), 7, 20, -112, 0, 0x80000000)
    ExecWait(TTYD64_pit_11_Script_AssignFlag_GiantChest)
    Call(AssignScript, (Bytecode) TTYD64_pit_11_Script_OpenChest)
    Call(MakeEntity, Ref(Entity_BlueWarpPipe), 6, 0, 43, 0, 0, 0, -1, 0x80000000)
    Return
    End
};

EvtScript TTYD64_pit_11_Script_Main = {
    Set(GameByte(425), 2)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(ClearDefeatedEnemies)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_pit_11_NpcGroupList_pit11)
    Exec(TTYD64_pit_11_Script_MakeEntities)
    Exec(TTYD64_pit_11_Script_SetupMusic)
    Exec(TTYD64_pit_11_Script_SetupTexturePan)
    Exec(TTYD64_pit_11_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_pit_11_Script_GiveItem = {
    Set(LVar0, LVarA)
    IfNe(LVarA, 0)
        ExecWait(TTYD64_pit_11_Script_ShowGotItem)
    EndIf
    Switch(LVarB)
    CaseEq(0)
        Call(AddItem, LVarA, LVar0)
    CaseEq(1)
        Call(TTYD64_tp_AddKeyItem, LVarA)
    CaseEq(2)
        Call(TTYD64_tp_AddBadge, LVarA, LVar0)
    EndSwitch
    Wait(15)
    Call(DisablePlayerInput, 0)
    Return
    End
};

u8 TTYD64_pit_11_String_Rowf_Hi[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0xF7, 0x57, 0x48, 0x41, 0x54, 0x07, 0x53,
    0xF7, 0x55, 0x50, 0xF7, 0x42, 0x55, 0x44, 0x44, 0x59, 0x01, 0xF0, 0x41,
    0x52, 0x45, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x41, 0x4C, 0x53, 0x4F, 0xF7,
    0x4C, 0x4F, 0x4F, 0x4B, 0x49, 0x4E, 0x47, 0xF7, 0x46, 0x4F, 0x52, 0xF0,
    0x53, 0x4F, 0x4D, 0x45, 0xF7, 0x54, 0x52, 0x45, 0x41, 0x53, 0x55, 0x52,
    0x45, 0x53, 0xF7, 0x41, 0x52, 0x4F, 0x55, 0x4E, 0x44, 0xF7, 0x48, 0x45,
    0x52, 0x45, 0x1F, 0xF0, 0xF1, 0xFB, 0x22, 0x59, 0xF7, 0x54, 0x48, 0x45,
    0xF7, 0x57, 0x41, 0x59, 0x0C, 0xF7, 0x29, 0xF7, 0x48, 0x41, 0x56, 0x45,
    0xF7, 0x41, 0xF7, 0x46, 0x45, 0x57, 0xF7, 0x54, 0x48, 0x49, 0x4E, 0x47,
    0x53, 0xF0, 0x49, 0x4E, 0xF7, 0x4D, 0x59, 0xF7, 0x42, 0x41, 0x43, 0x4B,
    0x50, 0x41, 0x43, 0x4B, 0xF7, 0x54, 0x48, 0x41, 0x54, 0xF7, 0x59, 0x4F,
    0x55, 0xF7, 0x4D, 0x49, 0x47, 0x48, 0x54, 0xF7, 0x42, 0x45, 0xF0, 0x49,
    0x4E, 0x54, 0x45, 0x52, 0x45, 0x53, 0x54, 0x45, 0x44, 0x0C, 0xF7, 0x44,
    0x4F, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x57, 0x41, 0x4E, 0x54, 0xF7, 0x54,
    0x4F, 0xF7, 0x54, 0x41, 0x4B, 0x45, 0xF0, 0x41, 0xF7, 0x4C, 0x4F, 0x4F,
    0x4B, 0xF7, 0x41, 0x54, 0xF7, 0x54, 0x48, 0x45, 0x4D, 0x1F, 0xF0, 0xFF,
    0x04, 0xFD
};

EvtScript TTYD64_pit_11_Script_TexturePan_Update = {
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

EvtScript TTYD64_pit_11_Script_UpdateFloorTheme = {
    Call(EnableGroup, 28, 0)
    Switch(AreaByte(0))
    CaseGe(80)
        Call(EnableGroup, 27, 1)
    CaseGe(50)
        Call(EnableGroup, 19, 1)
    CaseDefault
        Call(EnableGroup, 11, 1)
    EndSwitch
    Return
    End
};

u8 TTYD64_pit_11_String_Rowf_AskConfirmation[] = {
    0xFC, 0x01, 0x34, 0x48, 0x41, 0x54, 0x07, 0x53, 0xF7, 0x4D, 0x59, 0xF7,
    0x4D, 0x41, 0x4E, 0x0C, 0xF7, 0x52, 0x49, 0x47, 0x48, 0x54, 0xF7, 0x54,
    0x48, 0x45, 0x52, 0x45, 0x01, 0xF0, 0x39, 0x4F, 0x55, 0x07, 0x56, 0x45,
    0xF7, 0x47, 0x4F, 0x54, 0xF7, 0x41, 0x4E, 0xF7, 0x45, 0x59, 0x45, 0xF7,
    0x46, 0x4F, 0x52, 0xF7, 0x51, 0x55, 0x41, 0x4C, 0x49, 0x54, 0x59, 0x01,
    0xF0, 0xF1, 0xFB, 0x34, 0x48, 0x41, 0x54, 0xF7, 0xFF, 0x24, 0xFF, 0x05,
    0x20, 0xFF, 0x28, 0x00, 0xFF, 0x25, 0xF7, 0x48, 0x41, 0x53, 0xF7, 0x41,
    0xF7, 0x50, 0x52, 0x49, 0x43, 0x45, 0xF0, 0x4F, 0x46, 0xF7, 0xFF, 0x24,
    0xFF, 0x05, 0x20, 0xFF, 0x28, 0x01, 0xFF, 0x25, 0xF7, 0x43, 0x4F, 0x49,
    0x4E, 0x53, 0x01, 0xF0, 0xF0, 0x24, 0x4F, 0xF7, 0x59, 0x4F, 0x55, 0xF7,
    0x57, 0x41, 0x4E, 0x4E, 0x41, 0xF7, 0x42, 0x55, 0x59, 0xF7, 0x49, 0x54,
    0x1F, 0xF0, 0xFF, 0x04, 0xFD
};

u8 TTYD64_pit_11_String_Rowf_NoCoins[] = {
    0xFC, 0x01, 0x33, 0x4F, 0x52, 0x52, 0x59, 0x0E, 0x0E, 0x0E, 0xF7, 0x42,
    0x55, 0x44, 0x0C, 0xF7, 0x49, 0x54, 0xF7, 0x53, 0x45, 0x45, 0x4D, 0x53,
    0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF0, 0x48,
    0x41, 0x56, 0x45, 0xF7, 0x45, 0x4E, 0x4F, 0x55, 0x47, 0x48, 0xF7, 0x43,
    0x4F, 0x49, 0x4E, 0x53, 0xF7, 0x41, 0x4E, 0x44, 0xF7, 0x29, 0xF7, 0x48,
    0x41, 0x56, 0x45, 0xF7, 0x41, 0xF0, 0x46, 0x41, 0x4D, 0x49, 0x4C, 0x59,
    0xF7, 0x54, 0x4F, 0xF7, 0x46, 0x45, 0x45, 0x44, 0x0C, 0xF7, 0x59, 0x4F,
    0x55, 0xF7, 0x4B, 0x4E, 0x4F, 0x57, 0xF7, 0x57, 0x48, 0x41, 0x54, 0xF7,
    0x29, 0xF0, 0x4D, 0x45, 0x41, 0x4E, 0x1F, 0xF1, 0xFD
};

u8 TTYD64_pit_11_String_Rowf_NoInventory[] = {
    0xFB, 0x37, 0x41, 0x49, 0x54, 0xF7, 0x41, 0xF7, 0x4C, 0x49, 0x54, 0x54,
    0x4C, 0x45, 0xF7, 0x42, 0x49, 0x54, 0xF7, 0x42, 0x55, 0x44, 0x44, 0x59,
    0x0C, 0xF7, 0x29, 0x07, 0x4D, 0xF7, 0x53, 0x4F, 0x52, 0x52, 0x59, 0xF0,
    0x42, 0x55, 0x54, 0xF7, 0x49, 0x54, 0xF7, 0x53, 0x45, 0x45, 0x4D, 0x53,
    0xF7, 0x54, 0x48, 0x41, 0x54, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x44, 0x4F,
    0x4E, 0x07, 0x54, 0xF7, 0x48, 0x41, 0x56, 0x45, 0xF0, 0x4D, 0x4F, 0x52,
    0x45, 0xF7, 0x53, 0x50, 0x41, 0x43, 0x45, 0xF7, 0x49, 0x4E, 0xF7, 0x59,
    0x4F, 0x55, 0x52, 0xF7, 0x50, 0x4F, 0x43, 0x4B, 0x45, 0x54, 0x53, 0x0E,
    0xF1, 0xFD
};

EvtScript TTYD64_pit_11_Script_ReadSign_Entity_Sign = {
    Call(DisablePlayerInput, 1)
    Call(SetMessageValue, AreaByte(0), 0)
    Call(ShowMessageAtScreenPos, (Bytecode) TTYD64_pit_11_String_ReadSign_Entity_Sign, 160, 40)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_pit_11_Script_ShowGotItem = {
    SetGroup(0)
    Call(SetTimeFreezeMode, 2)
    Call(ShowGotItem, LVar0, 1, 0)
    Call(SetTimeFreezeMode, 0)
    Return
    Return
    End
};

EvtScript TTYD64_pit_11_Script_Exit1 = {
    SetGroup(27)
    Set(LVarA, 2)
    Set(LVarB, 9)
    Set(LVarC, (Bytecode) TTYD64_pit_11_Script_GotoMap_Exit1)
    ExecWait(TTYD64_pit_11_Script_ExitHorizontalPipe)
    Return
    End
};

EvtScript TTYD64_pit_11_Script_Exit0 = {
    SetGroup(27)
    Set(LVarA, 1)
    Set(LVarB, 0)
    Set(LVarC, (Bytecode) TTYD64_pit_11_Script_GotoMap_Exit0)
    ExecWait(TTYD64_pit_11_Script_ExitVerticalPipe)
    Return
    End
};

ShopItemData TTYD64_pit_11_Shop_Inventory[] = {
    { 0x8A, 10, 0x00230009 },
    { 0x8C, 30, 0x0023000A },
    { 0xA4, 10, 0x00230016 },
    { 0xA3, 40, 0x00230017 },
    { 0x80, 20, 0x00230000 },
    { 0x82, 40, 0x00230002 },
    { 0xFFFFFFFF, -1, -1 },
};

ShopItemData TTYD64_pit_11_Shop_Inventory_Updated[] = {
    { 0x8A, 10, 0x00230009 },
    { 0x8C, 30, 0x0023000A },
    { 0xA4, 10, 0x00230016 },
    { 0xA3, 40, 0x00230017 },
    { 0x80, 20, 0x00230000 },
    { 0x82, 40, 0x00230002 },
    { 0xFFFFFFFF, -1, -1 },
};

u8 TTYD64_pit_11_String_Rowf_Bye[] = {
    0xFC, 0x01, 0x35, 0x4E, 0x44, 0x45, 0x52, 0x53, 0x54, 0x4F, 0x4F, 0x44,
    0x0C, 0xF7, 0x52, 0x45, 0x4D, 0x45, 0x4D, 0x42, 0x45, 0x52, 0xF7, 0x54,
    0x48, 0x41, 0x54, 0xF0, 0x54, 0x48, 0x45, 0x52, 0x45, 0xF7, 0x41, 0x52,
    0x45, 0xF7, 0x4D, 0x41, 0x4E, 0x59, 0xF7, 0x44, 0x41, 0x4E, 0x47, 0x45,
    0x52, 0x53, 0xF7, 0x42, 0x45, 0x4C, 0x4F, 0x57, 0x0C, 0xF0, 0x54, 0x48,
    0x45, 0xF7, 0x42, 0x45, 0x53, 0x54, 0xF7, 0x4F, 0x46, 0xF7, 0x4C, 0x55,
    0x43, 0x4B, 0xF7, 0x42, 0x55, 0x44, 0x44, 0x59, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_pit_11_Script_OpenChest = {
    Set(GameFlag(4101), 0)
    Set(LVarA, MapVar(0))
    Set(LVarB, MapVar(1))
    ExecWait(TTYD64_pit_11_Script_GiveItem)
    Return
    End
};

EvtScript TTYD64_pit_11_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_pit_11_Script_Exit0, 128, 0, 1, 0)
    BindTrigger(TTYD64_pit_11_Script_Exit1, 64, 9, 1, 0)
    Return
    End
};

MapSettings TTYD64_pit_11_Header = {
    .main = TTYD64_pit_11_Script_Main,
    .entryList = &TTYD64_pit_11_EntryList,
    .entryCount = 3,
    .background = NULL,
    .tattle = { .get = TTYD64_pit_11_GetTattle },
};

u8 TTYD64_pit_11_String_Rowf_RelookInventory[] = {
    0xFB, 0x2F, 0x48, 0x0C, 0xF7, 0x41, 0x52, 0x45, 0x4E, 0x07, 0x54, 0xF7,
    0x59, 0x4F, 0x55, 0xF7, 0x43, 0x4F, 0x4D, 0x50, 0x4C, 0x45, 0x54, 0x45,
    0x4C, 0x59, 0xF7, 0x53, 0x55, 0x52, 0x45, 0x1F, 0xF0, 0x54, 0x48, 0x45,
    0x52, 0x45, 0xF7, 0x49, 0x53, 0xF7, 0x4E, 0x4F, 0xF7, 0x50, 0x52, 0x4F,
    0x42, 0x4C, 0x45, 0x4D, 0xF7, 0x42, 0x55, 0x44, 0x0E, 0xF1, 0xFD
};

EvtScript TTYD64_pit_11_Script_GotoMap_Exit0 = {
    Set(LVar0, AreaByte(0))
    Add(LVar0, 1)
    ExecWait(TTYD64_pit_11_Script_GoToNextMap)
    Return
    End
};

u8 TTYD64_pit_11_String_Rowf_ThankYou[] = {
    0xFC, 0x01, 0x34, 0x48, 0x41, 0x4E, 0x4B, 0xF7, 0x59, 0x4F, 0x55, 0xF7,
    0x56, 0x45, 0x52, 0x59, 0xF7, 0x4D, 0x55, 0x43, 0x48, 0x0C, 0xF7, 0x54,
    0x48, 0x45, 0xF7, 0x42, 0x45, 0x53, 0x54, 0xF0, 0x4F, 0x46, 0xF7, 0x4C,
    0x55, 0x43, 0x4B, 0xF7, 0x4F, 0x55, 0x54, 0xF7, 0x54, 0x48, 0x45, 0x52,
    0x45, 0xF7, 0x42, 0x55, 0x44, 0x44, 0x59, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_pit_11_Script_SetupMusic = {
    Call(SetMusic, 0, 75, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_pit_11_Script_Init_Rowf = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_pit_11_Script_Rowf_Interact)
    Exec(TTYD64_pit_11_Script_UpdateInventoryPrices)
    Return
    End
};

EntryList TTYD64_pit_11_EntryList = {
    { 7.0f, 149.0f, -2.0f, -270.0f },
    { 7.0f, 28.0f, 34.0f, -270.0f },
    { -120.0f, -1.0f, -136.0f, -270.0f },
};

NpcSettings TTYD64_pit_11_NpcSettings_Rowf = {
    .defaultAnim = 0x00000000,
    .height = 34,
    .radius = 32,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = NULL,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 99,
    .actionFlags = 0,
};

s32 TTYD64_pit_11_Function_Init(void) {
    sprintf(wMapTexName, "tik_tex");
    return false;
}

EvtScript TTYD64_pit_11_Script_GotoMap_Exit1 = {
    Call(GotoMap, (Bytecode) "pit_00", 2)
    Return
    End
};

NpcGroupList TTYD64_pit_11_NpcGroupList_pit11 = {
    { .npcCount = 1, .npcs = TTYD64_pit_11_NpcGroup_Mover, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_pit_11_NpcGroup_Rowf, .battle = 0x0000, .stage = 0 },
    {},
};

EvtScript TTYD64_pit_11_Script_Init_Mover = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_pit_11_Script_Mover_Interact)
    Return
    End
};

u8 TTYD64_pit_11_String_ReadSign_Entity_Sign[] = {
    0xFF, 0x09, 0xFC, 0x07, 0xFF, 0x29, 0xFF, 0xFF, 0x13, 0x10, 0x26, 0x4C,
    0x4F, 0x4F, 0x52, 0xF7, 0xFF, 0x28, 0x00, 0xFF, 0x0A, 0xF1, 0xFD
};

NpcGroupList TTYD64_pit_11_NpcGroupList_Mover = {
    { .npcCount = 1, .npcs = TTYD64_pit_11_NpcGroup_Mover, .battle = 0x0000, .stage = 0 },
    {},
};

char TTYD64_pit_11_ASCII_NextFloor[12] = "pit_00";

char TTYD64_pit_11_ASCII_pit12[12] = "pit_12";

MapConfig TTYD64_mapcfg_pit_11 = {
    .id = "pit_11",
    .settings = &TTYD64_pit_11_Header,
    .bgName = NULL,
    .init = TTYD64_pit_11_Function_Init,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_tp_Install_pit_11(void) {
    TTYD64_tp_BindMessage(TTYD64_pit_11_Script_Mover_Interact, TTYD64_imp_Mover_String_Mover_Hi);
    TTYD64_tp_BindMessage(TTYD64_pit_11_Script_Mover_Interact, TTYD64_imp_Mover_String_Choice_Mover);
    TTYD64_tp_BindMessage(TTYD64_pit_11_Script_Mover_Interact, TTYD64_imp_Mover_String_Mover_NotEnoughCoins);
    TTYD64_tp_BindMessage(TTYD64_pit_11_Script_Mover_Interact, TTYD64_imp_Mover_String_Mover_CloseYourEyes);
    TTYD64_tp_BindMessage(TTYD64_pit_11_Script_Rowf_Interact, TTYD64_pit_11_String_Rowf_Hi);
    TTYD64_tp_BindMessage(TTYD64_pit_11_Script_Rowf_Interact, TTYD64_pit_11_String_Rowf_Bye);
    TTYD64_tp_BindMessage(TTYD64_pit_11_Script_Rowf_Interact, TTYD64_pit_11_String_Rowf_NoCoins);
    TTYD64_tp_BindMessage(TTYD64_pit_11_Script_Rowf_Interact, TTYD64_pit_11_String_Rowf_AskConfirmation);
    TTYD64_tp_BindMessage(TTYD64_pit_11_Script_Rowf_Interact, TTYD64_pit_11_String_Rowf_RelookInventory);
    TTYD64_tp_BindMessage(TTYD64_pit_11_Script_Rowf_Interact, TTYD64_pit_11_String_Rowf_NoInventory);
    TTYD64_tp_BindMessage(TTYD64_pit_11_Script_Rowf_Interact, TTYD64_pit_11_String_Rowf_ThankYou);
    TTYD64_tp_BindMessage(TTYD64_pit_11_Script_ReadSign_Entity_Sign, TTYD64_pit_11_String_ReadSign_Entity_Sign);
    TTYD64_pit_11_NpcGroup_Rowf[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_pit_11_Tattle_Rowf);
    TTYD64_pit_11_NpcGroup_Mover[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_imp_Mover_Tattle_Mover);
    TTYD64_pit_11_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_pit_11_String_Tattle);
    Mod_RegisterMapResetData(
        "TTYD64", "pit_11", TTYD64_pit_11_Shop_Inventory_Updated, sizeof(TTYD64_pit_11_Shop_Inventory_Updated)
    );
    Mod_RegisterMapResetData("TTYD64", "pit_11", TTYD64_pit_11_ASCII_NextFloor, 12);
}
