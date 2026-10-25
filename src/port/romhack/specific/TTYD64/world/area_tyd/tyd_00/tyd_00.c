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
#include "port/romhack/specific/TTYD64/world/tyd_pit.h"

extern EvtScript TTYD64_tyd_00_Script_MarioDrowned;
extern EvtScript TTYD64_tyd_00_Script_EnterVerticalPipe;
extern EvtScript TTYD64_tyd_00_Script_ExitVerticalPipe;
extern EvtScript TTYD64_tyd_00_Script_Interact_Gus;
extern EvtScript TTYD64_tyd_00_Script_EnterMap;
extern NpcData TTYD64_tyd_00_NpcGroup_Gus[];
extern EvtScript TTYD64_tyd_00_Script_Defeat_Gus;
extern EvtScript TTYD64_tyd_00_Script_MakeEntities;
extern EvtScript TTYD64_tyd_00_Script_SetupTexturePan;
extern EvtScript TTYD64_tyd_00_Script_UpdateCollider;
extern EvtScript TTYD64_tyd_00_Script_Main;
extern EvtScript TTYD64_tyd_00_Script_GiveItem;
extern u8 TTYD64_tyd_00_String_Gus_RunAway[];
extern u8 TTYD64_tyd_00_String_Tattle[];
extern u8 TTYD64_tyd_00_Tattle_Gus[];
extern u8 TTYD64_tyd_00_String_Gus_Fight[];
extern EvtScript TTYD64_tyd_00_Script_TexturePan_Update;
extern u8 TTYD64_tyd_00_String_Gus_Defeated[];
extern EvtScript TTYD64_tyd_00_Script_Init_Gus;
extern EvtScript TTYD64_tyd_00_Script_ShowGotItem;
extern u8 TTYD64_tyd_00_String_Gus_Hi[];
extern u8 TTYD64_tyd_00_String_Choice_Gus[];
extern EvtScript TTYD64_tyd_00_Script_Exit0;
extern u8 TTYD64_tyd_00_String_Gus_NotEnoughCoins[];
extern EvtScript TTYD64_tyd_00_Script_OpenChest;
extern u8 TTYD64_tyd_00_String_Gus_Pay[];
extern MapSettings TTYD64_tyd_00_Header;
extern u8 TTYD64_tyd_00_String_Gus_DontPay[];
extern EvtScript TTYD64_tyd_00_Script_SetupMusic;
extern EvtScript TTYD64_tyd_00_Script_GoToMap_Exit0;
extern NpcSettings TTYD64_tyd_00_NpcSettings_Generic;
s32 TTYD64_tyd_00_Function_Init(void);
extern EvtScript TTYD64_tyd_00_Script_CreateExitTriggers;
extern EvtScript TTYD64_tyd_00_Script_UpdateRespawnPoint_1;
extern EvtScript TTYD64_tyd_00_Script_UpdateRespawnPoint_4;
extern EvtScript TTYD64_tyd_00_Script_UpdateRespawnPoint_3;
extern EvtScript TTYD64_tyd_00_Script_UpdateRespawnPoint_2;
extern NpcGroupList TTYD64_tyd_00_NpcGroupList_tyd00;
extern u8 TTYD64_tyd_00_String_Gus_Payed[];
extern EntryList TTYD64_tyd_00_EntryList;

// clang-format off
static s32 TTYD64_tyd_00_GetTattleMsg;

static s32 TTYD64_tyd_00_GetTattle(void) {
    return TTYD64_tyd_00_GetTattleMsg;
}

EvtScript TTYD64_tyd_00_Script_MarioDrowned = {
    Call(GetPartnerInUse, LVarA)
    IfEq(LVarA, 7)
        Return
    EndIf
    Call(PlaySound, 8419)
    IfEq(LVarA, 8)
        Call(TTYD64_SetPartnerAbilityState, PARTNER_LAKILESTER, 3)
    Else
        Call(DisablePlayerInput, 1)
        Loop(0)
            Call(GetPlayerActionState, LVar0)
            IfEq(LVar0, 0)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Call(DisablePlayerPhysics, 1)
        Thread
            Loop(5)
                Call(GetPlayerPos, LVar0, LVar1, LVar2)
                Sub(LVar1, 1)
                Call(SetPlayerPos, LVar0, LVar1, LVar2)
                Wait(1)
            EndLoop
        EndThread
        Call(SetPlayerAnimation, 0x10002)
        Call(SetPlayerAnimation, 0x1001B)
    EndIf
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(255.0))
    ExecWait(TTYD64_Script_FadeScreenOut)
    IfNe(LVarA, 8)
        Call(DisablePlayerPhysics, 0)
    EndIf
    Switch(MapVar(0))
    CaseEq(0)
        Call(SetPlayerPos, -301, 0, 348)
    CaseEq(1)
        Call(SetPlayerPos, 136, 0, 225)
    CaseEq(2)
        Call(SetPlayerPos, 483, 0, 275)
    CaseEq(3)
        Call(SetPlayerPos, 259, -24, -526)
    EndSwitch
    Switch(LVarA)
    CaseOrEq(9)
    CaseOrEq(6)
        Call(TTYD64_SetPlayerAnimFlagBits, PA_FLAG_INTERRUPT_USE_PARTNER, 1)
        EndCaseGroup
    EndSwitch
    Call(TeleportPartnerToPlayer)
    Call(InterpPlayerYaw, 90, 0)
    Wait(5)
    IfNe(LVarA, 8)
        Call(SetPlayerAnimation, 0x10002)
        Call(SetPlayerAnimation, 0x1000F)
    EndIf
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(5.0))
    Exec(TTYD64_Script_FadeScreenIn)
    Wait(10)
    IfEq(LVarA, 8)
        Return
    Else
        Call(SetPlayerAnimation, 0x10030)
        Wait(15)
        Call(SetPlayerAnimation, 0x10031)
        Thread
            Call(PlaySound, 370)
            Wait(12)
            Call(PlaySound, 370)
        EndThread
        Wait(25)
        Call(SetPlayerAnimation, 0x10002)
        Call(DisablePlayerInput, 0)
    EndIf
    Return
    End
};

EvtScript TTYD64_tyd_00_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_tyd_00_Script_ExitVerticalPipe = {
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

EvtScript TTYD64_tyd_00_Script_Interact_Gus = {
    Call(GetSelfVar, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SpeakToPlayer, -1, 0xEA0003, 0xEA0001, 0, (Bytecode) TTYD64_tyd_00_String_Gus_Payed)
        Return
    EndIf
    Call(ShowCoinCounter, 1)
    Call(SpeakToPlayer, -1, 0xEA0003, 0xEA0001, 0, (Bytecode) TTYD64_tyd_00_String_Gus_Hi)
    Call(ShowChoice, (Bytecode) TTYD64_tyd_00_String_Choice_Gus)
    Switch(LVar0)
    CaseEq(0)
        Call(AddCoin, 0)
        IfLt(LVar0, 10)
            Call(ShowCoinCounter, 0)
            Call(ContinueSpeech, -1, 0xEA0003, 0xEA0001, 0, (Bytecode) TTYD64_tyd_00_String_Gus_NotEnoughCoins)
            Return
        EndIf
        Call(AddCoin, -10)
        Call(SetNpcFlagBits, -1, 0x4000000, 1)
        Call(SetNpcSpeed, -1, Float(3.0))
        Call(SetNpcAnimation, -1, 0xEA0002)
        Call(NpcMoveTo, -1, -115, 198, 0)
        Call(SetNpcFlagBits, -1, 0x4000000, 0)
        Call(ShowCoinCounter, 0)
        Call(CloseMessage)
        Call(SetNpcAnimation, -1, 1)
        Call(SetSelfVar, 0, 1)
        Call(ModifyColliderFlags, 0, 97, 0x7FFFFE00)
    CaseEq(1)
        Call(ShowCoinCounter, 0)
        Call(ContinueSpeech, -1, 0xEA0003, 0xEA0001, 0, (Bytecode) TTYD64_tyd_00_String_Gus_DontPay)
    CaseEq(2)
        Call(ShowCoinCounter, 0)
        Call(ContinueSpeech, -1, 0xEA0003, 0xEA0001, 0, (Bytecode) TTYD64_tyd_00_String_Gus_Fight)
        Call(StartBattleWith, 3)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_tyd_00_Script_EnterMap = {
    Call(MakeItemEntity, 348, -73, 184, -553, 17, GameFlag(4556))
    Call(MakeItemEntity, 383, 544, 4, -152, 17, GameFlag(4557))
    Call(MakeItemEntity, 348, -55, 48, -264, 17, GameFlag(4558))
    Call(MakeItemEntity, 348, 107, 0, -348, 17, GameFlag(4559))
    Call(MakeItemEntity, 348, 61, 154, -135, 17, GameFlag(4560))
    IfEq(GameFlag(4563), 1)
        Call(ModifyColliderFlags, 0, 97, 0x7FFFFE00)
    EndIf
    Call(ModifyColliderFlags, 3, 77, 4)
    Call(ModifyColliderFlags, 3, 75, 4)
    Call(ModifyColliderFlags, 0, 77, 0x80000)
    Call(ModifyColliderFlags, 0, 75, 0x80000)
    BindTrigger(TTYD64_tyd_00_Script_UpdateRespawnPoint_1, 128, 2, 1, 0)
    BindTrigger(TTYD64_tyd_00_Script_UpdateRespawnPoint_2, 128, 4, 1, 0)
    BindTrigger(TTYD64_tyd_00_Script_UpdateRespawnPoint_2, 128, 96, 1, 0)
    BindTrigger(TTYD64_tyd_00_Script_UpdateRespawnPoint_3, 128, 7, 1, 0)
    BindTrigger(TTYD64_tyd_00_Script_UpdateRespawnPoint_4, 128, 8, 1, 0)
    BindTrigger(TTYD64_tyd_00_Script_MarioDrowned, 128, 79, 1, 0)
    Exec(TTYD64_tyd_00_Script_UpdateCollider)
    Return
    End
};

NpcData TTYD64_tyd_00_NpcGroup_Gus[] = {
    {
        .id = 0,
        .settings = &TTYD64_tyd_00_NpcSettings_Generic,
        .pos = { -104.0f, 0.0f, 234.0f },
        .flags = 0x00112D09,
        .init = TTYD64_tyd_00_Script_Init_Gus,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00EA0001, .walk = 0x00EA0000, .run = 0x00EA0000, .chase = 0x00EA0000, .anim_4 = 0x00EA0000, .anim_5 = 0x00EA0000, .death = 0x00EA0000, .hit = 0x00EA0000, .anim_8 = 0x00EA0000, .anim_9 = 0x00EA0000, .anim_A = 0x00EA0000, .anim_B = 0x00EA0000, .anim_C = 0x00EA0000, .anim_D = 0x00EA0000, .anim_E = 0x00EA0000, .anim_F = 0x00EA0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_tyd_00_Script_Defeat_Gus = {
    Call(SetSelfEnemyFlagBits, 4, 1)
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Call(SpeakToPlayer, -1, 0xEA0003, 0xEA0001, 0, (Bytecode) TTYD64_tyd_00_String_Gus_Defeated)
        Call(InterpNpcYaw, -1, 90, 0)
        Wait(15)
        Call(SetNpcAnimation, -1, 0xEA0002)
        Call(SetNpcSpeed, -1, Float(6.0))
        Call(PlaySoundAtNpc, -1, 350, 0)
        Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
        Add(LVar0, 200)
        Call(NpcMoveTo, -1, LVar0, LVar2, 0)
        Call(SetNpcPos, -1, 0, -1000, 0)
        Call(ModifyColliderFlags, 0, 97, 0x7FFFFE00)
        Set(GameFlag(4563), 1)
    CaseEq(2)
        Call(SpeakToPlayer, -1, 0xEA0003, 0xEA0001, 0, (Bytecode) TTYD64_tyd_00_String_Gus_RunAway)
        EndCaseGroup
    EndSwitch
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_tyd_00_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_HiddenPanel), 512, 126, 0, 0, 96, 0x80000000)
    Call(AssignPanelFlag, GameFlag(4561))
    Call(MakeEntity, Ref(Entity_HiddenPanel), -257, 0, 145, 0, 124, 0x80000000)
    Call(AssignPanelFlag, GameFlag(4562))
    Call(MakeEntity, Ref(Entity_Chest), 248, -48, 385, 0, 0, 0x80000000)
    Call(AssignChestFlag, GameFlag(4564))
    Call(AssignScript, (Bytecode) TTYD64_tyd_00_Script_OpenChest)
    Call(MakeEntity, Ref(Entity_Padlock), 477, 23, 118, 0, 0x80000000)
    Call(TTYD64_GetEntityPointer, LVar0, LVar0)
    Call(TTYD64_WritePtrField, LVar0, TTYD64_F_ENTITY_0_4U, 0)
    Return
    End
};

EvtScript TTYD64_tyd_00_Script_SetupTexturePan = {
    Call(SetTexPanner, 86, 0)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Set(LVar3, 0)
        Set(LVar4, -120)
        Set(LVar5, 0)
        Set(LVar6, 0)
        Set(LVar7, 1)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_tyd_00_Script_TexturePan_Update)
    EndThread
    Return
    End
};

EvtScript TTYD64_tyd_00_Script_UpdateCollider = {
    Set(LVar1, 0)
    Loop(0)
        Call(GetPartnerInUse, LVar0)
        IfEq(LVar0, 7)
            IfEq(LVar1, 0)
                Call(ModifyColliderFlags, 0, 96, 0x7FFFFE00)
                Set(LVar1, 1)
            EndIf
        Else
            IfEq(LVar1, 1)
                Call(ModifyColliderFlags, 1, 96, 0x7FFFFE00)
                Set(LVar1, 0)
            EndIf
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_00_Script_Main = {
    Set(GameByte(425), 1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_tyd_00_NpcGroupList_tyd00)
    Exec(TTYD64_tyd_00_Script_SetupMusic)
    Exec(TTYD64_tyd_00_Script_SetupTexturePan)
    Exec(TTYD64_tyd_00_Script_MakeEntities)
    Exec(TTYD64_tyd_00_Script_EnterMap)
    Set(LVarA, (Bytecode) TTYD64_tyd_00_Script_CreateExitTriggers)
    Exec(TTYD64_tyd_00_Script_EnterVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tyd_00_Script_GiveItem = {
    Call(DisablePlayerInput, 1)
    Set(LVar0, LVarA)
    IfNe(LVarA, 0)
        ExecWait(TTYD64_tyd_00_Script_ShowGotItem)
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

u8 TTYD64_tyd_00_String_Gus_RunAway[] = {
    0xFC, 0x01, 0x28, 0x41, 0x01, 0xF7, 0x2C, 0x45, 0x41, 0x52, 0x4E, 0xF7,
    0x59, 0x4F, 0x55, 0x52, 0xF7, 0x4C, 0x45, 0x53, 0x53, 0x4F, 0x4E, 0x1F,
    0xF0, 0x30, 0x52, 0x45, 0x44, 0x49, 0x43, 0x54, 0x49, 0x4F, 0x4E, 0x1A,
    0xF7, 0x59, 0x4F, 0x55, 0x07, 0x4C, 0x4C, 0xF7, 0x2E, 0x25, 0x36, 0x25,
    0x32, 0xF7, 0x54, 0x52, 0x59, 0xF0, 0x54, 0x4F, 0xF7, 0x46, 0x49, 0x47,
    0x48, 0x54, 0xF7, 0x54, 0x48, 0x52, 0x4F, 0x55, 0x47, 0x48, 0xF7, 0x48,
    0x45, 0x52, 0x45, 0xF7, 0x41, 0x47, 0x41, 0x49, 0x4E, 0x0E, 0xF0, 0xF1,
    0xFB, 0x29, 0xF7, 0x46, 0x49, 0x47, 0x55, 0x52, 0x45, 0xF7, 0x59, 0x4F,
    0x55, 0xF7, 0x4A, 0x55, 0x53, 0x54, 0xF7, 0x48, 0x41, 0x44, 0xF7, 0x41,
    0xF7, 0x54, 0x52, 0x49, 0x50, 0x4C, 0x45, 0xF0, 0x48, 0x45, 0x4C, 0x50,
    0x49, 0x4E, 0x47, 0xF7, 0x4F, 0x46, 0xF7, 0x48, 0x55, 0x4D, 0x42, 0x4C,
    0x45, 0xF7, 0x50, 0x49, 0x45, 0x0C, 0xF7, 0x53, 0x4F, 0xF7, 0x29, 0x07,
    0x4C, 0x4C, 0xF0, 0x4C, 0x45, 0x54, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7,
    0x53, 0x4C, 0x49, 0x44, 0x45, 0x0E, 0xF7, 0x2E, 0x4F, 0x57, 0xF7, 0x54,
    0x41, 0x4B, 0x45, 0xF7, 0x4F, 0x46, 0x46, 0x01, 0xF1, 0xFD
};

u8 TTYD64_tyd_00_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x34, 0x48, 0x49, 0x53, 0xF7, 0x50, 0x4C, 0x41,
    0x43, 0x45, 0xF7, 0x4C, 0x4F, 0x4F, 0x4B, 0x53, 0xF7, 0x4C, 0x49, 0x4B,
    0x45, 0xF7, 0x41, 0xF7, 0x54, 0x59, 0x50, 0x45, 0xF7, 0x4F, 0x46, 0xF7,
    0x50, 0x4F, 0x52, 0x54, 0xF0, 0x49, 0x4E, 0xF7, 0x41, 0xF7, 0x54, 0x48,
    0x49, 0x52, 0x44, 0x0D, 0x43, 0x4C, 0x41, 0x53, 0x53, 0xF7, 0x43, 0x49,
    0x54, 0x59, 0x0C, 0xF7, 0x29, 0xF7, 0x57, 0x4F, 0x4E, 0x44, 0x45, 0x52,
    0xF0, 0x57, 0x48, 0x4F, 0xF7, 0x57, 0x4F, 0x55, 0x4C, 0x44, 0xF7, 0x4C,
    0x49, 0x56, 0x45, 0xF7, 0x48, 0x45, 0x52, 0x45, 0x1F, 0xF0, 0xF1, 0xFB,
    0x2E, 0x4F, 0x54, 0x48, 0x49, 0x4E, 0x47, 0xF7, 0x4C, 0x49, 0x4B, 0x45,
    0xF7, 0x4C, 0x49, 0x56, 0x49, 0x4E, 0x47, 0xF7, 0x53, 0x55, 0x52, 0x52,
    0x4F, 0x55, 0x4E, 0x44, 0x45, 0x44, 0xF7, 0x42, 0x59, 0xF0, 0x4E, 0x41,
    0x54, 0x55, 0x52, 0x45, 0xF7, 0x4C, 0x49, 0x4B, 0x45, 0xF7, 0x4D, 0x59,
    0xF7, 0x46, 0x41, 0x4D, 0x49, 0x4C, 0x59, 0x0C, 0xF7, 0x52, 0x49, 0x47,
    0x48, 0x54, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x1F, 0xF1, 0xFD
};

u8 TTYD64_tyd_00_Tattle_Gus[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x34, 0x48, 0x41, 0x54, 0x07, 0x53, 0xF7, 0x27,
    0x55, 0x53, 0x0E, 0xF7, 0x2C, 0x4F, 0x4F, 0x4B, 0x07, 0x53, 0xF7, 0x4C,
    0x49, 0x4B, 0x45, 0xF7, 0x48, 0x45, 0xF7, 0x49, 0x53, 0xF0, 0x50, 0x41,
    0x52, 0x54, 0xF7, 0x4F, 0x46, 0xF7, 0x41, 0xF7, 0x42, 0x41, 0x4E, 0x44,
    0xF7, 0x4F, 0x46, 0xF7, 0x54, 0x48, 0x49, 0x45, 0x56, 0x45, 0x53, 0x0E,
    0xF0, 0xF1, 0xFB, 0x28, 0x45, 0xF7, 0x4C, 0x4F, 0x4F, 0x4B, 0x53, 0xF7,
    0x4C, 0x49, 0x4B, 0x45, 0xF7, 0x41, 0xF7, 0x54, 0x4F, 0x54, 0x41, 0x4C,
    0xF7, 0x4D, 0x41, 0x4E, 0x49, 0x41, 0x43, 0x0C, 0xF0, 0x42, 0x55, 0x54,
    0xF7, 0x29, 0x07, 0x4D, 0xF7, 0x53, 0x55, 0x52, 0x45, 0xF7, 0x48, 0x45,
    0x07, 0x53, 0xF7, 0x41, 0x43, 0x54, 0x55, 0x41, 0x4C, 0x4C, 0x59, 0xF7,
    0x41, 0xF0, 0x52, 0x45, 0x41, 0x4C, 0x4C, 0x59, 0xF7, 0x4E, 0x49, 0x43,
    0x45, 0xF7, 0x47, 0x55, 0x59, 0x0E, 0xF0, 0xF1, 0xFB, 0x24, 0x4F, 0x4E,
    0x07, 0x54, 0xF7, 0x4A, 0x55, 0x44, 0x47, 0x45, 0xF7, 0x42, 0x4F, 0x4F,
    0x4B, 0x53, 0xF7, 0x42, 0x59, 0xF7, 0x43, 0x4F, 0x56, 0x45, 0x52, 0x53,
    0x01, 0xF1, 0xFD
};

u8 TTYD64_tyd_00_String_Gus_Fight[] = {
    0xFB, 0x37, 0x48, 0x41, 0x54, 0x1F, 0xF7, 0x39, 0x4F, 0x55, 0xF7, 0x47,
    0x4F, 0x54, 0x54, 0x41, 0xF7, 0x42, 0x45, 0xF7, 0x4B, 0x49, 0x44, 0x44,
    0x49, 0x4E, 0x47, 0x0E, 0xF0, 0x39, 0x4F, 0x55, 0xF7, 0x54, 0x48, 0x49,
    0x4E, 0x4B, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x43, 0x41, 0x4E, 0xF7, 0x46,
    0x49, 0x47, 0x48, 0x54, 0xF7, 0x59, 0x4F, 0x55, 0x52, 0xF0, 0x57, 0x41,
    0x59, 0xF7, 0x54, 0x48, 0x52, 0x4F, 0x55, 0x47, 0x48, 0xF7, 0x48, 0x45,
    0x52, 0x45, 0x1F, 0xF0, 0xF1, 0xFB, 0x29, 0x07, 0x4D, 0xF7, 0x47, 0x4F,
    0x4E, 0x4E, 0x41, 0xF7, 0x4D, 0x41, 0x4B, 0x45, 0xF7, 0x59, 0x4F, 0x55,
    0xF7, 0x45, 0x41, 0x54, 0xF7, 0x59, 0x4F, 0x55, 0x52, 0xF0, 0x57, 0x4F,
    0x52, 0x44, 0x53, 0x0C, 0xF7, 0x54, 0x4F, 0x55, 0x47, 0x48, 0xF7, 0x47,
    0x55, 0x59, 0x01, 0xF7, 0x2C, 0x45, 0x54, 0x07, 0x53, 0xF7, 0x47, 0x45,
    0x54, 0xF0, 0x54, 0x48, 0x49, 0x53, 0xF7, 0x50, 0x41, 0x52, 0x54, 0x59,
    0xF7, 0x53, 0x54, 0x41, 0x52, 0x54, 0x45, 0x44, 0x01, 0xF0, 0xF1, 0xFD
};

EvtScript TTYD64_tyd_00_Script_TexturePan_Update = {
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

u8 TTYD64_tyd_00_String_Gus_Defeated[] = {
    0xFC, 0x01, 0x23, 0x32, 0x35, 0x24, 0x01, 0xF7, 0x39, 0x4F, 0x55, 0xF7,
    0x44, 0x55, 0x4D, 0x42, 0xF7, 0x56, 0x49, 0x44, 0x45, 0x4F, 0x0D, 0x47,
    0x41, 0x4D, 0x45, 0xF0, 0x48, 0x45, 0x52, 0x4F, 0x45, 0x53, 0xF7, 0x21,
    0x2C, 0x37, 0x21, 0x39, 0x33, 0xF7, 0x50, 0x55, 0x4C, 0x4C, 0xF7, 0x54,
    0x48, 0x49, 0x53, 0xF0, 0x53, 0x54, 0x55, 0x46, 0x46, 0x01, 0xF7, 0x29,
    0x54, 0x07, 0x53, 0xF7, 0x32, 0x29, 0x24, 0x29, 0x23, 0x35, 0x2C, 0x2F,
    0x35, 0x33, 0x01, 0xF0, 0xF1, 0xFB, 0x39, 0x4F, 0x55, 0xF7, 0x54, 0x48,
    0x49, 0x4E, 0x4B, 0xF7, 0x56, 0x49, 0x4F, 0x4C, 0x45, 0x4E, 0x43, 0x45,
    0xF7, 0x53, 0x4F, 0x4C, 0x56, 0x45, 0x53, 0xF0, 0x45, 0x56, 0x45, 0x52,
    0x59, 0x54, 0x48, 0x49, 0x4E, 0x47, 0x0C, 0xF7, 0x44, 0x4F, 0x4E, 0x07,
    0x54, 0xF7, 0x59, 0x4F, 0x55, 0x1F, 0xF7, 0x28, 0x55, 0x48, 0x1F, 0xF0,
    0x24, 0x2F, 0x2E, 0x07, 0x34, 0xF7, 0x39, 0x2F, 0x35, 0x1F, 0x01, 0x1F,
    0xF0, 0xF1, 0xFD
};

EvtScript TTYD64_tyd_00_Script_Init_Gus = {
    IfEq(GameFlag(4563), 1)
        Call(SetNpcPos, -1, 0, -1000, 0)
    EndIf
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_tyd_00_Script_Interact_Gus)
    Call(BindNpcDefeat, -1, (Bytecode) TTYD64_tyd_00_Script_Defeat_Gus)
    Return
    End
};

EvtScript TTYD64_tyd_00_Script_ShowGotItem = {
    SetGroup(0)
    Call(SetTimeFreezeMode, 2)
    Wait(40)
    Call(ShowGotItem, LVar0, 0, 0)
    Call(SetTimeFreezeMode, 0)
    Return
    Return
    End
};

u8 TTYD64_tyd_00_String_Gus_Hi[] = {
    0xFC, 0x01, 0x37, 0x48, 0x4F, 0x41, 0x01, 0xF7, 0x37, 0x48, 0x4F, 0x41,
    0x01, 0xF7, 0x28, 0x4F, 0x4C, 0x44, 0xF7, 0x55, 0x50, 0x0C, 0xF7, 0x4E,
    0x4F, 0x57, 0x01, 0xF0, 0x29, 0x46, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x57,
    0x41, 0x4E, 0x54, 0xF7, 0x54, 0x4F, 0xF7, 0x50, 0x41, 0x53, 0x53, 0xF7,
    0x54, 0x48, 0x52, 0x4F, 0x55, 0x47, 0x48, 0xF0, 0x48, 0x45, 0x52, 0x45,
    0x0C, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x47, 0x4F, 0x54, 0x54, 0x41, 0xF7,
    0x50, 0x41, 0x59, 0xF7, 0x11, 0x10, 0xF7, 0x43, 0x4F, 0x49, 0x4E, 0x53,
    0x0E, 0xF0, 0xFF, 0x04, 0xFD
};

u8 TTYD64_tyd_00_String_Choice_Gus[] = {
    0xFC, 0x05, 0x5D, 0x5A, 0x9B, 0x40, 0xFF, 0x09, 0xFF, 0x1E, 0x00, 0xFF,
    0x21, 0x00, 0x26, 0x49, 0x4E, 0x45, 0x0C, 0xF7, 0x29, 0x07, 0x4C, 0x4C,
    0xF7, 0x50, 0x41, 0x59, 0x0E, 0xF0, 0xFF, 0x1E, 0x01, 0xFF, 0x21, 0x01,
    0x29, 0x07, 0x4D, 0xF7, 0x4E, 0x4F, 0x54, 0xF7, 0x50, 0x41, 0x59, 0x49,
    0x4E, 0x47, 0x0E, 0xF0, 0xFF, 0x1E, 0x02, 0xFF, 0x21, 0x02, 0x29, 0xF7,
    0x43, 0x41, 0x4E, 0xF7, 0x54, 0x41, 0x4B, 0x45, 0xF7, 0x59, 0x4F, 0x55,
    0x01, 0xF0, 0xFF, 0x21, 0xFF, 0xFF, 0x0A, 0xFF, 0x20, 0x01, 0xFF, 0x1F,
    0x03, 0xFD
};

EvtScript TTYD64_tyd_00_Script_Exit0 = {
    SetGroup(27)
    Set(LVarA, 0)
    Set(LVarB, 88)
    Set(LVarC, (Bytecode) TTYD64_tyd_00_Script_GoToMap_Exit0)
    ExecWait(TTYD64_tyd_00_Script_ExitVerticalPipe)
    Return
    End
};

u8 TTYD64_tyd_00_String_Gus_NotEnoughCoins[] = {
    0xFB, 0x37, 0x48, 0x4F, 0x41, 0x01, 0xF7, 0x37, 0x48, 0x4F, 0x41, 0x01,
    0xF7, 0x28, 0x4F, 0x4C, 0x44, 0xF7, 0x55, 0x50, 0x0C, 0xF7, 0x4E, 0x4F,
    0x57, 0x01, 0xF0, 0x39, 0x4F, 0x55, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54,
    0xF7, 0x48, 0x41, 0x56, 0x45, 0xF7, 0x45, 0x4E, 0x4F, 0x55, 0x47, 0x48,
    0xF7, 0x43, 0x41, 0x53, 0x48, 0x01, 0xF0, 0x39, 0x4F, 0x55, 0xF7, 0x44,
    0x49, 0x52, 0x54, 0x59, 0x0C, 0xF7, 0x4C, 0x59, 0x49, 0x4E, 0x47, 0xF7,
    0x43, 0x48, 0x45, 0x41, 0x50, 0x53, 0x4B, 0x41, 0x54, 0x45, 0x01, 0xF1,
    0xFD
};

EvtScript TTYD64_tyd_00_Script_OpenChest = {
    Set(LVarA, 386)
    Set(LVarB, 2)
    Set(GameFlag(4862), 1)
    ExecWait(TTYD64_tyd_00_Script_GiveItem)
    Return
    End
};

u8 TTYD64_tyd_00_String_Gus_Pay[] = {
    0xFB, 0x2F, 0x4E, 0x45, 0x0C, 0xF7, 0x54, 0x57, 0x4F, 0x0C, 0xF7, 0x54,
    0x48, 0x52, 0x45, 0x45, 0x0E, 0x0E, 0x0E, 0xF7, 0x39, 0x55, 0x50, 0x01,
    0xF0, 0x34, 0x48, 0x41, 0x54, 0x07, 0x53, 0xF7, 0x11, 0x10, 0xF7, 0x43,
    0x4F, 0x49, 0x4E, 0x53, 0xF7, 0x41, 0x4C, 0x4C, 0xF7, 0x52, 0x49, 0x47,
    0x48, 0x54, 0x01, 0xF0, 0xF1, 0xFB, 0x39, 0x4F, 0x55, 0xF7, 0x43, 0x41,
    0x4E, 0xF7, 0x50, 0x41, 0x53, 0x53, 0x0E, 0xF1, 0xFD
};

MapSettings TTYD64_tyd_00_Header = {
    .main = TTYD64_tyd_00_Script_Main,
    .entryList = &TTYD64_tyd_00_EntryList,
    .entryCount = 1,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_tyd_00_GetTattle },
};

u8 TTYD64_tyd_00_String_Gus_DontPay[] = {
    0xFB, 0x29, 0x54, 0x07, 0x53, 0xF7, 0x52, 0x45, 0x41, 0x4C, 0x4C, 0x59,
    0xF7, 0x53, 0x49, 0x4D, 0x50, 0x4C, 0x45, 0x0E, 0xF7, 0x29, 0x46, 0xF7,
    0x59, 0x4F, 0x55, 0xF0, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x50, 0x41,
    0x59, 0x0C, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54,
    0xF7, 0x50, 0x41, 0x53, 0x53, 0x0E, 0xF0, 0xF1, 0xFD
};

EvtScript TTYD64_tyd_00_Script_SetupMusic = {
    Call(SetMusic, 0, 166, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_tyd_00_Script_GoToMap_Exit0 = {
    Call(GotoMap, (Bytecode) "mac_04", 7)
    Wait(100)
    Return
    End
};

NpcSettings TTYD64_tyd_00_NpcSettings_Generic = {
    .defaultAnim = 0x00000000,
    .height = 30,
    .radius = 24,
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

s32 TTYD64_tyd_00_Function_Init(void) {
    sprintf(wMapTexName, "mac_tex");
    return false;
}

EvtScript TTYD64_tyd_00_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_tyd_00_Script_Exit0, 128, 88, 1, 0)
    Return
    End
};

EvtScript TTYD64_tyd_00_Script_UpdateRespawnPoint_1 = {
    Set(MapVar(0), 0)
    Return
    End
};

EvtScript TTYD64_tyd_00_Script_UpdateRespawnPoint_4 = {
    Set(MapVar(0), 3)
    Return
    End
};

EvtScript TTYD64_tyd_00_Script_UpdateRespawnPoint_3 = {
    Set(MapVar(0), 2)
    Return
    End
};

EvtScript TTYD64_tyd_00_Script_UpdateRespawnPoint_2 = {
    Set(MapVar(0), 1)
    Return
    End
};

NpcGroupList TTYD64_tyd_00_NpcGroupList_tyd00 = {
    { .npcCount = 1, .npcs = TTYD64_tyd_00_NpcGroup_Gus, .battle = 0x3B00, .stage = 0 },
    {},
};

u8 TTYD64_tyd_00_String_Gus_Payed[] = {
    0xFC, 0x01, 0x39, 0x4F, 0x55, 0xF7, 0x43, 0x41, 0x4E, 0xF7, 0x50, 0x41,
    0x53, 0x53, 0x0E, 0xF1, 0xFD
};

EntryList TTYD64_tyd_00_EntryList = {
    { -211.0f, 31.0f, 379.0f, 90.0f },
};

MapConfig TTYD64_mapcfg_tyd_00 = {
    .id = "tyd_00",
    .settings = &TTYD64_tyd_00_Header,
    .bgName = "nok_bg",
    .init = TTYD64_tyd_00_Function_Init,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_tp_Install_tyd_00(void) {
    TTYD64_tp_BindMessage(TTYD64_tyd_00_Script_Interact_Gus, TTYD64_tyd_00_String_Gus_Payed);
    TTYD64_tp_BindMessage(TTYD64_tyd_00_Script_Interact_Gus, TTYD64_tyd_00_String_Gus_Hi);
    TTYD64_tp_BindMessage(TTYD64_tyd_00_Script_Interact_Gus, TTYD64_tyd_00_String_Choice_Gus);
    TTYD64_tp_BindMessage(TTYD64_tyd_00_Script_Interact_Gus, TTYD64_tyd_00_String_Gus_NotEnoughCoins);
    TTYD64_tp_BindMessage(TTYD64_tyd_00_Script_Interact_Gus, TTYD64_tyd_00_String_Gus_DontPay);
    TTYD64_tp_BindMessage(TTYD64_tyd_00_Script_Interact_Gus, TTYD64_tyd_00_String_Gus_Fight);
    TTYD64_tp_BindMessage(TTYD64_tyd_00_Script_Defeat_Gus, TTYD64_tyd_00_String_Gus_Defeated);
    TTYD64_tp_BindMessage(TTYD64_tyd_00_Script_Defeat_Gus, TTYD64_tyd_00_String_Gus_RunAway);
    TTYD64_tyd_00_NpcGroup_Gus[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_tyd_00_Tattle_Gus);
    TTYD64_tyd_00_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_tyd_00_String_Tattle);
}
