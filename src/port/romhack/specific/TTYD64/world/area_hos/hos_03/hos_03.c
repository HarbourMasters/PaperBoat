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

extern EvtScript hos_03_EVS_ControlUpperVisibility;
extern EvtScript hos_03_EVS_ExitWalk_hos_02_1;
extern EvtScript hos_03_EVS_ExitWalk_hos_04_0;
extern EvtScript hos_03_EVS_Main;
extern EvtScript hos_03_EVS_MakeEntities;
extern EvtScript hos_03_EVS_NpcInit_ShopOwner;
extern EvtScript hos_03_EVS_NpcInit_StarKid_01;
extern EvtScript hos_03_EVS_NpcInit_StarKid_02;
extern EvtScript hos_03_EVS_NpcInit_StarKid_03;
extern EvtScript hos_03_EVS_NpcInit_StarKid_04;
extern EvtScript hos_03_EVS_NpcInit_StarKid_05;
extern EvtScript hos_03_EVS_NpcInit_ToadHouseKeeper;
extern EvtScript hos_03_EVS_SetupAurora;
extern EvtScript hos_03_EVS_SetupFoliage;
extern EvtScript hos_03_EVS_SetupMusic;
extern EvtScript hos_03_EVS_SetupRooms;
extern EvtScript hos_03_EVS_SetupShop;
extern ShopItemData hos_03_Inventory[];
extern NpcSettings hos_03_NpcSettings_ChuckQuizmo;
extern NpcSettings hos_03_NpcSettings_StarMan;
extern NpcSettings hos_03_NpcSettings_StarMan_Wander;
extern MapSettings hos_03_settings;

API_CALLABLE(BindNpcInteract);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(GetLoadType);
API_CALLABLE(GetPartnerInUse);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlaySound);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(ShowGotItem);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(TeleportPartnerToPlayer);
API_CALLABLE(UseExitHeading);
API_CALLABLE(UseRoomDoorSounds);

extern EvtScript TTYD64_hos_03_Script_MakeExits;
extern EvtScript TTYD64_hos_03_Script_Init_StarKid;
extern NpcGroupList TTYD64_hos_03_NpcGroupList_hos03;
extern EvtScript TTYD64_hos_03_Script_Main_EnterWalk;
extern EvtScript TTYD64_hos_03_Script_Respawn;
extern EvtScript TTYD64_hos_03_Script_Interact_StarKid;
extern u8 TTYD64_hos_03_String_StarKid_Found[];
extern EvtScript TTYD64_hos_03_Script_TogglePosTracker_On;
extern ShopItemData TTYD64_hos_03_ShopInventory_8024BB5C[];
extern NpcData TTYD64_hos_03_NpcGroup_hos03[];
extern EntryList TTYD64_hos_03_EntryList;
extern EvtScript TTYD64_hos_03_Script_TrackDeathTrigger;
extern EvtScript TTYD64_hos_03_Script_Exit2;
extern EvtScript TTYD64_hos_03_Script_TogglePosTracker_Off;

// clang-format off
EvtScript TTYD64_hos_03_Script_MakeExits = {
    BindTrigger(hos_03_EVS_ExitWalk_hos_02_1, 0x80000, 0, 1, 0)
    BindTrigger(hos_03_EVS_ExitWalk_hos_04_0, 0x80000, 4, 1, 0)
    BindTrigger(TTYD64_hos_03_Script_Exit2, 0x80000, 70, 1, 0)
    BindTrigger(TTYD64_hos_03_Script_TogglePosTracker_On, 0x80000, 22, 1, 0)
    BindTrigger(TTYD64_hos_03_Script_TogglePosTracker_Off, 0x80000, 19, 1, 0)
    Exec(TTYD64_hos_03_Script_TrackDeathTrigger)
    Return
    End
};

EvtScript TTYD64_hos_03_Script_Init_StarKid = {
    Call(BindNpcInteract, -1, Ref(TTYD64_hos_03_Script_Interact_StarKid))
    Return
    End
};

NpcGroupList TTYD64_hos_03_NpcGroupList_hos03 = {
    { .npcCount = 9, .npcs = TTYD64_hos_03_NpcGroup_hos03, .battle = 0x0000, .stage = 0 },
    {},
};

EvtScript TTYD64_hos_03_Script_Main_EnterWalk = {
    Set(GameByte(425), 29)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamLeadPlayer, 0, 0)
    Call(SetCamEnabled, 0, 1)
    IfEq(GameByte(0), 90)
        Set(GameByte(0), 91)
    EndIf
    Set(GameFlag(1992), 1)
    Call(MakeNpcs, 0, Ref(TTYD64_hos_03_NpcGroupList_hos03))
    ExecWait(hos_03_EVS_MakeEntities)
    Call(ModifyColliderFlags, 0, 5, 0x7FFFFE00)
    Call(GetLoadType, LVar1)
    IfEq(LVar1, 1)
        Exec(EnterSavePoint)
        Exec(TTYD64_hos_03_Script_MakeExits)
    Else
        Set(LVar0, Ref(TTYD64_hos_03_Script_MakeExits))
        Exec(EnterWalk)
        Wait(1)
    EndIf
    Exec(hos_03_EVS_SetupAurora)
    Call(UseRoomDoorSounds, 6)
    Exec(hos_03_EVS_SetupMusic)
    Call(PlaySound, 0x80000063)
    Exec(hos_03_EVS_SetupRooms)
    Exec(hos_03_EVS_SetupShop)
    Exec(hos_03_EVS_SetupFoliage)
    Exec(hos_03_EVS_ControlUpperVisibility)
    Return
    End
};

EvtScript TTYD64_hos_03_Script_Respawn = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Thread
        Loop(8)
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Sub(LVar1, 8)
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Thread
        Call(SetPlayerActionState, 8)
        Wait(1)
        Call(SetPlayerAnimation, 0x10002)
        Call(SetPlayerAnimation, 0x1001B)
    EndThread
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(255.0))
    ExecWait(TTYD64_Script_FadeScreenOut)
    Call(DisablePlayerPhysics, 0)
    Call(GetPartnerInUse, LVar0)
    Switch(LVar0)
    CaseOrEq(9)
    CaseOrEq(6)
    CaseOrEq(8)
        Call(TTYD64_SetPlayerAnimFlagBits, PA_FLAG_INTERRUPT_USE_PARTNER, 1)
        EndCaseGroup
    EndSwitch
    Call(SetPlayerPos, -337, 250, 52)
    Wait(1)
    Call(TeleportPartnerToPlayer)
    Call(InterpPlayerYaw, -90, 0)
    Wait(5)
    Call(SetPlayerAnimation, 0x10002)
    Call(SetPlayerAnimation, 0x1000F)
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(5.0))
    Exec(TTYD64_Script_FadeScreenIn)
    Wait(10)
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
    Return
    End
};

EvtScript TTYD64_hos_03_Script_Interact_StarKid = {
    Call(SpeakToPlayer, -1, 0xB30002, 0xB30001, 0, (Bytecode) TTYD64_hos_03_String_StarKid_Found)
    IfEq(GameFlag(4641), 0)
        Call(TTYD64_maps_AddBadge, 263, 0)
        Call(ShowGotItem, 263, 1, 0)
        Set(GameFlag(4641), 1)
    EndIf
    Return
    End
};

u8 TTYD64_hos_03_String_StarKid_Found[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C,
    0xF7, 0x4C, 0x4F, 0x4F, 0x4B, 0x53, 0xF7, 0x4C, 0x49, 0x4B, 0x45, 0xF7,
    0x59, 0x4F, 0x55, 0xF7, 0x46, 0x49, 0x4E, 0x41, 0x4C, 0x4C, 0x59, 0xF0,
    0x46, 0x4F, 0x55, 0x4E, 0x44, 0xF7, 0x4D, 0x45, 0x01, 0xF0, 0xF1, 0xFB,
    0x29, 0xF7, 0x52, 0x45, 0x41, 0x4C, 0x4C, 0x59, 0xF7, 0x57, 0x41, 0x53,
    0x4E, 0x07, 0x54, 0xF7, 0x45, 0x58, 0x50, 0x45, 0x43, 0x54, 0x49, 0x4E,
    0x47, 0xF7, 0x41, 0x4E, 0x59, 0x4F, 0x4E, 0x45, 0xF0, 0x54, 0x4F, 0xF7,
    0x44, 0x4F, 0xF7, 0x49, 0x54, 0x0E, 0xF1, 0xFD
};

EvtScript TTYD64_hos_03_Script_TogglePosTracker_On = {
    Set(MapVar(0), 1)
    Return
    End
};

ShopItemData TTYD64_hos_03_ShopInventory_8024BB5C[] = {
    { .itemID = 146, .price = 15, .descMsg = 0x240028 },
    { .itemID = 131, .price = 15, .descMsg = 0x240004 },
    { .itemID = 401, .price = 15, .descMsg = 0x230136 },
    { .itemID = 163, .price = 10, .descMsg = 0x240017 },
    { .itemID = 149, .price = 25, .descMsg = 0x24000C },
    { .itemID = 140, .price = 10, .descMsg = 0x24000A },
    { .itemID = 0, .price = 0, .descMsg = 0x000000 },
};

NpcData TTYD64_hos_03_NpcGroup_hos03[] = {
    {
        .id = 0,
        .settings = &hos_03_NpcSettings_StarMan,
        .pos = { -463.0f, 10.0f, 400.0f },
        .flags = 0x00000D09,
        .init = &hos_03_EVS_NpcInit_StarKid_01,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30001, .run = 0x00B30001, .chase = 0x00B30001, .anim_4 = 0x00B30001, .anim_5 = 0x00B30001, .death = 0x00B30001, .hit = 0x00B30001, .anim_8 = 0x00B30001, .anim_9 = 0x00B30001, .anim_A = 0x00B30001, .anim_B = 0x00B30001, .anim_C = 0x00B30001, .anim_D = 0x00B30001, .anim_E = 0x00B30001, .anim_F = 0x00B30001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A010E,
    },
    {
        .id = 1,
        .settings = &hos_03_NpcSettings_StarMan,
        .pos = { -325.0f, 10.0f, 600.0f },
        .flags = 0x00000D09,
        .init = &hos_03_EVS_NpcInit_StarKid_02,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30001, .run = 0x00B30001, .chase = 0x00B30001, .anim_4 = 0x00B30001, .anim_5 = 0x00B30001, .death = 0x00B30001, .hit = 0x00B30001, .anim_8 = 0x00B30001, .anim_9 = 0x00B30001, .anim_A = 0x00B30001, .anim_B = 0x00B30001, .anim_C = 0x00B30001, .anim_D = 0x00B30001, .anim_E = 0x00B30001, .anim_F = 0x00B30001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A010F,
    },
    {
        .id = 2,
        .settings = &hos_03_NpcSettings_StarMan_Wander,
        .pos = { 0.0f, 10.0f, 300.0f },
        .flags = 0x00000D09,
        .init = &hos_03_EVS_NpcInit_StarKid_03,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 10, .centerPos.z = 300, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 10, .detectPos.z = 300, .detectSize.x = 30, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30001, .run = 0x00B30001, .chase = 0x00B30001, .anim_4 = 0x00B30001, .anim_5 = 0x00B30001, .death = 0x00B30001, .hit = 0x00B30001, .anim_8 = 0x00B30001, .anim_9 = 0x00B30001, .anim_A = 0x00B30001, .anim_B = 0x00B30001, .anim_C = 0x00B30001, .anim_D = 0x00B30001, .anim_E = 0x00B30001, .anim_F = 0x00B30001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A0110,
    },
    {
        .id = 3,
        .settings = &hos_03_NpcSettings_StarMan_Wander,
        .pos = { 250.0f, 10.0f, 500.0f },
        .flags = 0x00000D09,
        .init = &hos_03_EVS_NpcInit_StarKid_04,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 250, .centerPos.y = 10, .centerPos.z = 500, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 250, .detectPos.y = 10, .detectPos.z = 500, .detectSize.x = 30, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30001, .run = 0x00B30001, .chase = 0x00B30001, .anim_4 = 0x00B30001, .anim_5 = 0x00B30001, .death = 0x00B30001, .hit = 0x00B30001, .anim_8 = 0x00B30001, .anim_9 = 0x00B30001, .anim_A = 0x00B30001, .anim_B = 0x00B30001, .anim_C = 0x00B30001, .anim_D = 0x00B30001, .anim_E = 0x00B30001, .anim_F = 0x00B30001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A0111,
    },
    {
        .id = 4,
        .settings = &hos_03_NpcSettings_StarMan,
        .pos = { -485.0f, 335.0f, -100.0f },
        .flags = 0x00000D09,
        .init = &hos_03_EVS_NpcInit_StarKid_05,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30001, .run = 0x00B30001, .chase = 0x00B30001, .anim_4 = 0x00B30001, .anim_5 = 0x00B30001, .death = 0x00B30001, .hit = 0x00B30001, .anim_8 = 0x00B30001, .anim_9 = 0x00B30001, .anim_A = 0x00B30001, .anim_B = 0x00B30001, .anim_C = 0x00B30001, .anim_D = 0x00B30001, .anim_E = 0x00B30001, .anim_F = 0x00B30001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A0112,
    },
    {
        .id = 5,
        .settings = &hos_03_NpcSettings_StarMan,
        .pos = { 458.0f, 35.0f, 233.0f },
        .flags = 0x00000D09,
        .init = &hos_03_EVS_NpcInit_ToadHouseKeeper,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30001, .run = 0x00B30001, .chase = 0x00B30001, .anim_4 = 0x00B30001, .anim_5 = 0x00B30001, .death = 0x00B30001, .hit = 0x00B30001, .anim_8 = 0x00B30001, .anim_9 = 0x00B30001, .anim_A = 0x00B30001, .anim_B = 0x00B30001, .anim_C = 0x00B30001, .anim_D = 0x00B30001, .anim_E = 0x00B30001, .anim_F = 0x00B30001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A010D,
    },
    {
        .id = 6,
        .settings = &hos_03_NpcSettings_StarMan,
        .pos = { 140.0f, 285.0f, -315.0f },
        .flags = 0x00000D09,
        .init = &hos_03_EVS_NpcInit_ShopOwner,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30001, .run = 0x00B30001, .chase = 0x00B30001, .anim_4 = 0x00B30001, .anim_5 = 0x00B30001, .death = 0x00B30001, .hit = 0x00B30001, .anim_8 = 0x00B30001, .anim_9 = 0x00B30001, .anim_A = 0x00B30001, .anim_B = 0x00B30001, .anim_C = 0x00B30001, .anim_D = 0x00B30001, .anim_E = 0x00B30001, .anim_F = 0x00B30001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A010C,
    },
    {
        .id = 7,
        .settings = &hos_03_NpcSettings_ChuckQuizmo,
        .pos = { -200.0f, 0.0f, 400.0f },
        .flags = 0x00002D09,
        .init = NULL,
        .initVarCount = 1,
        .initVar = { .value = 0x00060100 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00AF0001, .walk = 0x00AF0002, .run = 0x00AF0003, .chase = 0x00AF0003, .anim_4 = 0x00AF0001, .anim_5 = 0x00AF0001, .death = 0x00AF0000, .hit = 0x00AF0000, .anim_8 = 0x00AF0003, .anim_9 = 0x00AF0003, .anim_A = 0x00AF0003, .anim_B = 0x00AF0003, .anim_C = 0x00AF0003, .anim_D = 0x00AF0003, .anim_E = 0x00AF0003, .anim_F = 0x00AF0003 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A0002,
    },
    {
        .id = 8,
        .settings = &hos_03_NpcSettings_StarMan,
        .pos = { -586.0f, 170.0f, -24.0f },
        .flags = 0x00000D09,
        .init = &TTYD64_hos_03_Script_Init_StarKid,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30001, .run = 0x00B30001, .chase = 0x00B30001, .anim_4 = 0x00B30001, .anim_5 = 0x00B30001, .death = 0x00B30001, .hit = 0x00B30001, .anim_8 = 0x00B30001, .anim_9 = 0x00B30001, .anim_A = 0x00B30001, .anim_B = 0x00B30001, .anim_C = 0x00B30001, .anim_D = 0x00B30001, .anim_E = 0x00B30001, .anim_F = 0x00B30001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A010E,
    },
};

EntryList TTYD64_hos_03_EntryList = {
    { -497.0f, 0.0f, 479.0f, 45.0f },
    { 705.0f, 0.0f, 0.0f, 270.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 354.0f, 0.0f, 294.0f, 117.0f },
    { 47.0f, 0.0f, 24.0f, 90.0f },
};

EvtScript TTYD64_hos_03_Script_TrackDeathTrigger = {
    Loop(0)
        IfEq(MapVar(0), 1)
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            IfLt(LVar1, 54)
                ExecWait(TTYD64_hos_03_Script_Respawn)
            EndIf
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_hos_03_Script_Exit2 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 11)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "hos_25", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_hos_03_Script_TogglePosTracker_Off = {
    Set(MapVar(0), 0)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_hos_03(void) {
    hos_03_settings.entryList = &TTYD64_hos_03_EntryList;
    hos_03_settings.entryCount = 12;
    Mod_ReplaceScript("TTYD64", &hos_03_EVS_Main, &TTYD64_hos_03_Script_Main_EnterWalk);
    memcpy(&hos_03_Inventory, &TTYD64_hos_03_ShopInventory_8024BB5C, sizeof(TTYD64_hos_03_ShopInventory_8024BB5C));
    TTYD64_maps_BindInlineMessage(TTYD64_hos_03_Script_Interact_StarKid, TTYD64_hos_03_String_StarKid_Found);
}
