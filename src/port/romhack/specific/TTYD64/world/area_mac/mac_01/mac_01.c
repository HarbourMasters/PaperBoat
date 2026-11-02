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

extern s32 mac_01_D_802555AC_815E2C[];
extern EvtScript mac_01_EVS_EnterBadgeShop;
extern EvtScript mac_01_EVS_EnterMap;
extern EvtScript mac_01_EVS_ExitBadgeShop;
extern EvtScript mac_01_EVS_Main;
extern EvtScript mac_01_EVS_MakeEntities;
extern EvtScript mac_01_EVS_Merlon_GiveHint;
extern EvtScript mac_01_EVS_NpcIdle_Rowf;
extern EvtScript mac_01_EVS_NpcInit_Rowf;
extern EvtScript mac_01_EVS_NpcInteract_Rhuff_C;
extern EvtScript mac_01_EVS_NpcInteract_Rowf_A;
extern EvtScript mac_01_EVS_NpcInteract_Rowf_C;
extern EvtScript mac_01_EVS_OnBuy;
extern EvtScript mac_01_EVS_Rhuff_HideBadges;
extern EvtScript mac_01_EVS_Rhuff_RevealBadges;
extern EvtScript mac_01_EVS_Scene_IntroWalking;
extern EvtScript mac_01_EVS_SetupBadgeShop;
extern EvtScript mac_01_EVS_SetupBulletinBoard;
extern EvtScript mac_01_EVS_SetupCrystalBallGfx;
extern EvtScript mac_01_EVS_SetupFlowerModels;
extern EvtScript mac_01_EVS_SetupFoliage;
extern EvtScript mac_01_EVS_SetupMusic;
extern EvtScript mac_01_EVS_SetupQuickChangeTrigger;
extern EvtScript mac_01_EVS_SetupRooms;
extern EvtScript mac_01_EVS_UpdateRhuffAnims;
extern NpcGroupList mac_01_EpilogueNPCs;
extern NpcGroupList mac_01_IntroNPCs;
extern NpcData mac_01_NpcData_ChuckQuizmo;
extern NpcData mac_01_NpcData_DarkToads[];
extern NpcData mac_01_NpcData_Kolorado;
extern NpcData mac_01_NpcData_KoopaBros[];
extern NpcData mac_01_NpcData_Merlon;
extern NpcData mac_01_NpcData_Ninji;
extern NpcData mac_01_NpcData_Parakarry;
extern NpcData mac_01_NpcData_RowfAndRhuff[];
extern NpcData mac_01_NpcData_ShyGuys[];
extern NpcData mac_01_NpcData_Townsfolk[];
extern NpcData mac_01_NpcData_Twink;
extern ShopSellPriceData mac_01_RowfDummyPriceList[];
extern ShopOwner mac_01_ShopOwnerRowf;

API_CALLABLE(AddCoin);
API_CALLABLE(BindNpcIdle);
API_CALLABLE(BindNpcInteract);
API_CALLABLE(CloseMessage);
API_CALLABLE(ContinueSpeech);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableModel);
API_CALLABLE(EnableTexPanning);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GetNpcPointer);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeLocalVertexCopy);
API_CALLABLE(MakeNpcs);
API_CALLABLE(MakeShop);
API_CALLABLE(MakeShopOwner);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(NpcJump0);
API_CALLABLE(NpcMoveTo);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlaySoundAt);
API_CALLABLE(PlaySoundAtCollider);
API_CALLABLE(RotateGroup);
API_CALLABLE(RotateModel);
API_CALLABLE(ScaleGroup);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamDistance);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetCustomGfxBuilders);
API_CALLABLE(SetMessageText);
API_CALLABLE(SetMessageValue);
API_CALLABLE(SetModelCustomGfx);
API_CALLABLE(SetModelFlags);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcJumpscale);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetNpcSpeed);
API_CALLABLE(SetNpcYaw);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanOffset);
API_CALLABLE(ShowChoice);
API_CALLABLE(ShowCoinCounter);
API_CALLABLE(ShowGotItem);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(TTYD64_maps_WriteModBytesBE16);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseDoorSounds);
API_CALLABLE(UseRoomDoorSounds);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(WaitForCam);
API_CALLABLE(func_802D1270);
API_CALLABLE(mac_01_RhuffUnravelUpdate);
API_CALLABLE(mac_01_RowfShop_SetBadgePos);
API_CALLABLE(mac_01_gfx_build_rowf_rug_with_ripples);

extern NpcData TTYD64_mac_01_NpcGroup_NGPlus[];
extern u8 TTYD64_mac_01_String_Rowf_PressA[];
extern NpcGroupList TTYD64_mac_01_NpcGroupList_8025EFF0;
extern NpcGroupList TTYD64_mac_01_NpcGroupList_8025F0F8;
extern u8 TTYD64_mac_01_Tattle_SettingsNPC[];
extern u8 TTYD64_mac_01_String_Choice_Merlon[];
extern EvtScript TTYD64_mac_01_Script_Main;
extern s32 TTYD64_mac_01_IntTable_80247E00[];
extern EvtScript TTYD64_mac_01_Script_Interact_80254A58;
extern ShopOwner TTYD64_mac_01_ShopOwnerRowf;
extern EvtScript TTYD64_mac_01_Script_80248070;
extern u8 TTYD64_mac_01_String_Rowf_Choice1[];
extern u8 TTYD64_mac_01_String_Rowf_NoBadges[];
extern EvtScript TTYD64_mac_01_Script_InteractCrystalBall;
extern ShopItemLocation TTYD64_mac_01_RowfItemPositions_New[];
extern EvtScript TTYD64_mac_01_Script_Idle_80255500;
extern EvtScript TTYD64_mac_01_Script_InitRowf;
extern u8 TTYD64_mac_01_String_Rowf_TooMuchStock[];
extern NpcGroupList TTYD64_mac_01_NpcGroupList_8025F044;
extern u8 TTYD64_mac_01_String_Rowf_NoStock[];
extern u8 TTYD64_mac_01_Script_Merlon_Start[];
extern EvtScript TTYD64_mac_01_Script_Init_802560B4;
extern NpcData TTYD64_mac_01_NpcGroup_Settings[];
extern u8 TTYD64_mac_01_String_Rowf_Welcome[];
extern u8 TTYD64_mac_01_Tattle_NGPlus[];
extern NpcGroupList TTYD64_mac_01_NpcGroupList_8025F0BC;
extern NpcSettings TTYD64_mac_01_NpcSettings_8024C5BC;
extern EvtScript TTYD64_mac_01_Script_80247E74;
extern u8 TTYD64_mac_01_String_Rowf_PleaseComeBack[];
extern EvtScript TTYD64_mac_01_Script_80261880;
extern EvtScript TTYD64_mac_01_Script_Interact_Rowf;
extern EvtScript TTYD64_mac_01_Script_80255B30;
extern EvtScript TTYD64_mac_01_Script_8025573C;
extern u8 TTYD64_mac_01_String_Rowf_Sell_Confirmation[];
extern NpcGroupList TTYD64_mac_01_NpcGroupList_8025EFA8;
extern NpcGroupList TTYD64_mac_01_NpcGroupList_8025F080;
extern u8 TTYD64_mac_01_String_Rowf_Choice2[];
extern u8 TTYD64_mac_01_String_Rowf_WhatKind[];

// clang-format off
NpcData TTYD64_mac_01_NpcGroup_NGPlus[] = {
    {
        .id = 40,
        .settings = &TTYD64_mac_01_NpcSettings_8024C5BC,
        .pos = { 376.0f, 34.0f, -161.0f },
        .flags = 0x00400D09,
        .init = &TTYD64_Script_Init_NPC_NGPlus,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00120001, .walk = 0x00120000, .run = 0x00120000, .chase = 0x00120000, .anim_4 = 0x00120000, .anim_5 = 0x00120000, .death = 0x00120000, .hit = 0x00120000, .anim_8 = 0x00120000, .anim_9 = 0x00120000, .anim_A = 0x00120000, .anim_B = 0x00120000, .anim_C = 0x00120000, .anim_D = 0x00120000, .anim_E = 0x00120000, .anim_F = 0x00120000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

u8 TTYD64_mac_01_String_Rowf_PressA[] = {
    0xFB, 0x29, 0x46, 0xF7, 0x59, 0x4F, 0x55, 0x07, 0x52, 0x45, 0xF7, 0x4C,
    0x4F, 0x4F, 0x4B, 0x49, 0x4E, 0x47, 0xF7, 0x46, 0x4F, 0x52, 0xF7, 0x53,
    0x50, 0x45, 0x43, 0x49, 0x41, 0x4C, 0xF0, 0x44, 0x45, 0x41, 0x4C, 0x53,
    0x0C, 0xF7, 0x59, 0x4F, 0x55, 0x07, 0x4C, 0x4C, 0xF7, 0x46, 0x49, 0x4E,
    0x44, 0xF7, 0x07, 0x45, 0x4D, 0xF7, 0x4F, 0x4E, 0xF7, 0x54, 0x48, 0x41,
    0x54, 0xF0, 0x43, 0x41, 0x52, 0x50, 0x45, 0x54, 0x01, 0xF0, 0xF1, 0xFB,
    0x2A, 0x55, 0x53, 0x54, 0xF7, 0x50, 0x52, 0x45, 0x53, 0x53, 0xF7, 0xFF,
    0x24, 0xFF, 0x05, 0x10, 0x98, 0xFF, 0x25, 0xF7, 0x49, 0x4E, 0xF7, 0x46,
    0x52, 0x4F, 0x4E, 0x54, 0xF7, 0x4F, 0x46, 0xF7, 0x41, 0xF0, 0x22, 0x41,
    0x44, 0x47, 0x45, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x57, 0x41, 0x4E, 0x54,
    0xF7, 0x54, 0x4F, 0xF7, 0x42, 0x55, 0x59, 0x0E, 0xF1, 0xFD
};

NpcGroupList TTYD64_mac_01_NpcGroupList_8025EFF0 = {
    { .npcCount = 1, .npcs = &mac_01_NpcData_Parakarry, .battle = 0x0000, .stage = 0 },
    { .npcCount = 4, .npcs = mac_01_NpcData_KoopaBros, .battle = 0x0000, .stage = 0 },
    { .npcCount = 4, .npcs = mac_01_NpcData_DarkToads, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = &mac_01_NpcData_Merlon, .battle = 0x0000, .stage = 0 },
    { .npcCount = 2, .npcs = mac_01_NpcData_RowfAndRhuff, .battle = 0x0000, .stage = 0 },
    { .npcCount = 10, .npcs = mac_01_NpcData_Townsfolk, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_01_NpcGroup_Settings, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_01_NpcGroup_NGPlus, .battle = 0x0000, .stage = 0 },
    {},
};

NpcGroupList TTYD64_mac_01_NpcGroupList_8025F0F8 = {
    { .npcCount = 1, .npcs = &mac_01_NpcData_Ninji, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = &mac_01_NpcData_Merlon, .battle = 0x0000, .stage = 0 },
    { .npcCount = 2, .npcs = mac_01_NpcData_RowfAndRhuff, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = &mac_01_NpcData_Kolorado, .battle = 0x0000, .stage = 0 },
    { .npcCount = 10, .npcs = mac_01_NpcData_Townsfolk, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_01_NpcGroup_Settings, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_01_NpcGroup_NGPlus, .battle = 0x0000, .stage = 0 },
    {},
};

u8 TTYD64_mac_01_Tattle_SettingsNPC[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x34, 0x41, 0x4C, 0x4B, 0xF7, 0x54, 0x4F, 0xF7,
    0x48, 0x49, 0x4D, 0xF7, 0x54, 0x4F, 0xF7, 0x43, 0x48, 0x41, 0x4E, 0x47,
    0x45, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0xF0, 0x53, 0x45, 0x54, 0x54, 0x49,
    0x4E, 0x47, 0x53, 0xF7, 0x49, 0x4E, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x47,
    0x41, 0x4D, 0x45, 0x0E, 0xF1, 0xFD
};

u8 TTYD64_mac_01_String_Choice_Merlon[] = {
    0xFC, 0x05, 0x52, 0x5A, 0xA5, 0x2E, 0xFF, 0x09, 0xFF, 0x1E, 0x00, 0xFF,
    0x21, 0x00, 0x30, 0x52, 0x45, 0x44, 0x49, 0x43, 0x54, 0xF7, 0x50, 0x41,
    0x54, 0x48, 0xF0, 0xFF, 0x1E, 0x01, 0xFF, 0x21, 0x01, 0x35, 0x50, 0x47,
    0x52, 0x41, 0x44, 0x45, 0xF7, 0x50, 0x41, 0x52, 0x54, 0x4E, 0x45, 0x52,
    0x53, 0xF0, 0xFF, 0x21, 0xFF, 0xFF, 0x0A, 0xFF, 0x20, 0x02, 0xFF, 0x1F,
    0x02, 0xFD
};

EvtScript TTYD64_mac_01_Script_Main = {
    Set(GameByte(425), 1)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 90, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Set(AreaFlag(14), 0)
    Set(AreaFlag(15), 0)
    Set(AreaFlag(16), 0)
    Set(AreaFlag(17), 0)
    Set(AreaFlag(18), 0)
    Set(AreaFlag(19), 0)
    Set(AreaFlag(20), 0)
    Set(AreaFlag(21), 0)
    IfLt(GameByte(0), 96)
        Exec(mac_01_EVS_SetupBadgeShop)
    Else
        Call(EnableGroup, 211, 0)
    EndIf
    Switch(GameByte(0))
    CaseEq(-128)
        Call(MakeNpcs, 0, Ref(mac_01_IntroNPCs))
    CaseGe(96)
        Call(MakeNpcs, 0, Ref(mac_01_EpilogueNPCs))
    CaseLt(-100)
        Call(MakeNpcs, 0, Ref(TTYD64_mac_01_NpcGroupList_8025EFF0))
    CaseLt(-75)
        Call(MakeNpcs, 0, Ref(TTYD64_mac_01_NpcGroupList_8025F044))
    CaseEq(-74)
        Call(MakeNpcs, 0, Ref(TTYD64_mac_01_NpcGroupList_8025F080))
    CaseRange(-13, 5)
        Call(MakeNpcs, 0, Ref(TTYD64_mac_01_NpcGroupList_8025F0BC))
    CaseEq(60)
        Call(MakeNpcs, 0, Ref(TTYD64_mac_01_NpcGroupList_8025F0F8))
    CaseDefault
        Call(MakeNpcs, 0, Ref(TTYD64_mac_01_NpcGroupList_8025EFA8))
    EndSwitch
    IfGe(GameByte(0), -100)
        Call(ModifyColliderFlags, 0, 19, 0x7FFFFE00)
    EndIf
    Exec(mac_01_EVS_SetupFlowerModels)
    Exec(mac_01_EVS_MakeEntities)
    Exec(mac_01_EVS_SetupRooms)
    Exec(mac_01_EVS_SetupBulletinBoard)
    Exec(mac_01_EVS_SetupCrystalBallGfx)
    Exec(mac_01_EVS_SetupMusic)
    Call(UseDoorSounds, 2)
    Call(UseRoomDoorSounds, 0)
    Exec(mac_01_EVS_EnterMap)
    Wait(1)
    Call(EnableTexPanning, 45, 1)
    Thread
        SetGroup(0)
        Set(LVar0, 0)
        Set(LVar1, 0)
        Label(0)
        Add(LVar0, -100)
        Add(LVar1, -200)
        IfLt(LVar0, 0)
            Add(LVar0, 0x10000)
        EndIf
        IfLt(LVar1, 0)
            Add(LVar0, 0x10000)
        EndIf
        Call(SetTexPanOffset, 3, 0, LVar0, 0)
        Call(SetTexPanOffset, 3, 1, LVar1, LVar1)
        Wait(1)
        Goto(0)
    EndThread
    BindTrigger(TTYD64_mac_01_Script_InteractCrystalBall, 256, 78, 1, 0)
    Exec(mac_01_EVS_SetupQuickChangeTrigger)
    Exec(mac_01_EVS_SetupFoliage)
    Call(SetCamSpeed, 0, Float(2.0))
    Return
    End
};

s32 TTYD64_mac_01_IntTable_80247E00[] = {
    2555927, 2555928, 2555906, 2555929, 2555908, 2555909,
    2555910, 2555911, 2555912, 2555913, 2555914, 2555915,
    2555916, 2555917, 2555918, 2555919, 2555920, 2555921,
    2555922, 2555923, 2555924, 2555925, 2555930, -2143076160
};

EvtScript TTYD64_mac_01_Script_Interact_80254A58 = {
    Call(TTYD64_mac_01_Function_AllBadgesHasBeenBought)
    IfEq(LVar0, 255)
        Call(SpeakToPlayer, 2, 0xA70004, 0xA70001, 0, 0x3000F)
    Else
        Set(LVar0, GameFlag(4218))
        Add(LVar0, GameFlag(4219))
        Add(LVar0, GameFlag(4220))
        Add(LVar0, GameFlag(4221))
        Add(LVar0, GameFlag(4222))
        IfEq(LVar0, 5)
            Call(SpeakToPlayer, 2, 0xA70004, 0xA70001, 0, 0x3000E)
        Else
            Call(SpeakToPlayer, 2, 0xA70004, 0xA70001, 0, 0x3000D)
        EndIf
    EndIf
    Return
    End
};

ShopOwner TTYD64_mac_01_ShopOwnerRowf = {
    .npcID = 1,
    .idleAnim = 0x00A70001,
    .talkAnim = 0x00A70004,
    .onBuyEvt = &mac_01_EVS_OnBuy,
    .unk_10Evt = NULL,
    .onTalkEvt = NULL,
    .shopMsgIDs = TTYD64_mac_01_IntTable_80247E00,
};

EvtScript TTYD64_mac_01_Script_80248070 = {
    Call(TTYD64_mac_01_Function_InitSaleInventory)
    Set(MapVar(2), LVar1)
    IfEq(LVar3, 0)
        Set(GameFlag(4218), 0)
        Set(GameFlag(4219), 0)
        Set(GameFlag(4220), 0)
        Set(GameFlag(4221), 0)
        Set(GameFlag(4222), 0)
        IfLt(LVar0, 5)
            Set(GameFlag(4222), 1)
        EndIf
        IfLt(LVar0, 4)
            Set(GameFlag(4221), 1)
        EndIf
        IfLt(LVar0, 3)
            Set(GameFlag(4220), 1)
        EndIf
        IfLt(LVar0, 2)
            Set(GameFlag(4219), 1)
        EndIf
        IfLt(LVar0, 1)
            Set(GameFlag(4218), 1)
        EndIf
    EndIf
    Call(MakeShop, (Bytecode) TTYD64_mac_01_RowfItemPositions_New, LVar2, (Bytecode) mac_01_RowfDummyPriceList, 0)
    Call(MakeShopOwner, Ref(mac_01_ShopOwnerRowf))
    IfEq(LVar3, 1)
        IfGe(LVar0, 5)
            IfEq(GameFlag(4222), 1)
                Call(TTYD64_mac_01_Function_SetSaleBadgeGlobalFlag, 4)
            EndIf
        EndIf
        IfGe(LVar0, 4)
            IfEq(GameFlag(4221), 1)
                Call(TTYD64_mac_01_Function_SetSaleBadgeGlobalFlag, 3)
            EndIf
        EndIf
        IfGe(LVar0, 3)
            IfEq(GameFlag(4220), 1)
                Call(TTYD64_mac_01_Function_SetSaleBadgeGlobalFlag, 2)
            EndIf
        EndIf
        IfGe(LVar0, 2)
            IfEq(GameFlag(4219), 1)
                Call(TTYD64_mac_01_Function_SetSaleBadgeGlobalFlag, 1)
            EndIf
        EndIf
        IfGe(LVar0, 1)
            IfEq(GameFlag(4218), 1)
                Call(TTYD64_mac_01_Function_SetSaleBadgeGlobalFlag, 0)
            EndIf
        EndIf
    EndIf
    Return
    End
};

u8 TTYD64_mac_01_String_Rowf_Choice1[] = {
    0xFC, 0x05, 0x65, 0x5A, 0x7A, 0x2E, 0xFF, 0x09, 0xFF, 0x1E, 0x00, 0xFF,
    0x21, 0x00, 0x29, 0x07, 0x4D, 0xF7, 0x42, 0x55, 0x59, 0x49, 0x4E, 0x47,
    0x01, 0xF0, 0xFF, 0x1E, 0x01, 0xFF, 0x21, 0x01, 0x29, 0x07, 0x4D, 0xF7,
    0x53, 0x45, 0x4C, 0x4C, 0x49, 0x4E, 0x47, 0x01, 0xF0, 0xFF, 0x21, 0xFF,
    0xFF, 0x0A, 0xFF, 0x20, 0x02, 0xFF, 0x1F, 0x02, 0xFD
};

u8 TTYD64_mac_01_String_Rowf_NoBadges[] = {
    0xFC, 0x01, 0x33, 0x4F, 0x52, 0x52, 0x59, 0xF7, 0x42, 0x55, 0x44, 0x0C,
    0xF7, 0x42, 0x55, 0x54, 0xF7, 0x4C, 0x4F, 0x4F, 0x4B, 0x53, 0xF7, 0x4C,
    0x49, 0x4B, 0x45, 0xF7, 0x59, 0x4F, 0x55, 0x0C, 0xF0, 0x44, 0x4F, 0x4E,
    0x07, 0x54, 0xF7, 0x48, 0x41, 0x56, 0x45, 0xF7, 0x41, 0x4E, 0x59, 0xF7,
    0x42, 0x41, 0x44, 0x47, 0x45, 0x0C, 0xF7, 0x50, 0x4C, 0x45, 0x41, 0x53,
    0x45, 0xF0, 0x43, 0x4F, 0x4D, 0x45, 0xF7, 0x42, 0x41, 0x43, 0x4B, 0xF7,
    0x57, 0x48, 0x45, 0x4E, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x48, 0x41, 0x56,
    0x45, 0xF7, 0x41, 0xF7, 0x46, 0x45, 0x57, 0x0E, 0xF1, 0xFD
};

EvtScript TTYD64_mac_01_Script_InteractCrystalBall = {
    Call(DisablePlayerInput, 1)
    Call(SpeakToPlayer, 0, 0xA50004, 0xA50001, 0, (Bytecode) TTYD64_mac_01_Script_Merlon_Start)
    Call(ShowChoice, (Bytecode) TTYD64_mac_01_String_Choice_Merlon)
    Switch(LVar0)
    CaseEq(0)
        Call(CloseMessage)
        Call(DisablePlayerInput, 0)
        ExecWait(mac_01_EVS_Merlon_GiveHint)
    CaseEq(1)
        ExecWait(TTYD64_Script_UpgradePartners_Main)
    CaseEq(2)
        Call(CloseMessage)
        Call(DisablePlayerInput, 0)
    EndSwitch
    Return
    End
};

ShopItemLocation TTYD64_mac_01_RowfItemPositions_New[] = {
    { .posModelID = 210, .triggerColliderID = 102 },
    { .posModelID = 209, .triggerColliderID = 101 },
    { .posModelID = 208, .triggerColliderID = 100 },
    { .posModelID = 207, .triggerColliderID = 99 },
    { .posModelID = 206, .triggerColliderID = 98 },
};

EvtScript TTYD64_mac_01_Script_Idle_80255500 = {
    Set(LVar0, Float(58.0))
    Set(LVar1, Float(-192.0))
    Set(LVar2, Float(-300.0))
    Set(LVar3, Float(425.0))
    Call(GetNpcPointer, 2, LVar7)
    Loop(0)
        Call(mac_01_RhuffUnravelUpdate)
        Call(SetNpcPos, 2, LVar4, 0, LVar5)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_mac_01_Script_InitRowf = {
    Set(MapVar(13), 0)
    Set(MapVar(14), 0)
    Set(AreaFlag(64), 0)
    Switch(GameByte(0))
    CaseLt(-74)
        Call(BindNpcInteract, -1, Ref(mac_01_EVS_NpcInteract_Rowf_A))
        Call(BindNpcIdle, -1, Ref(mac_01_EVS_NpcIdle_Rowf))
    CaseLt(-13)
        Call(BindNpcInteract, -1, Ref(TTYD64_mac_01_Script_Interact_Rowf))
        Set(AreaFlag(64), 1)
    CaseDefault
        IfEq(GameFlag(258), 1)
            Call(BindNpcInteract, -1, Ref(TTYD64_mac_01_Script_Interact_Rowf))
            Set(AreaFlag(64), 1)
        Else
            Call(BindNpcInteract, -1, Ref(mac_01_EVS_NpcInteract_Rowf_C))
            Call(SetNpcPos, 1, -250, 0, 295)
        EndIf
    EndSwitch
    Set(AreaFlag(65), 0)
    Call(SetModelFlags, 146, 512, 0)
    Call(EnableGroup, 211, 0)
    Call(ModifyColliderFlags, 0, 98, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 99, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 100, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 101, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 102, 0x7FFFFE00)
    Call(RotateGroup, 211, 60, 0, 1, 0)
    Call(RotateGroup, 147, 0, 0, 1, 0)
    Call(ScaleGroup, 147, Float(1.2998046875), 1, Float(1.2998046875))
    Set(MapVar(1), 60)
    Call(MakeLocalVertexCopy, 0, 205, 1)
    Call(SetCustomGfxBuilders, 0, (Bytecode) mac_01_gfx_build_rowf_rug_with_ripples, 0)
    Call(SetModelCustomGfx, 205, 0, -1)
    IfEq(AreaFlag(64), 1)
        BindTrigger(mac_01_EVS_EnterBadgeShop, 128, 66, 1, 0)
        BindTrigger(mac_01_EVS_ExitBadgeShop, 128, 14, 1, 0)
        Call(SetNpcJumpscale, 1, 1)
    EndIf
    Thread
        Wait(5)
        Call(SetModelFlags, 206, 4, 0)
        Call(SetModelFlags, 207, 4, 0)
        Call(SetModelFlags, 208, 4, 0)
        Call(SetModelFlags, 209, 4, 0)
        Call(SetModelFlags, 210, 4, 0)
        Call(TTYD64_mac_01_Function_80244D68_2)
        Label(0)
        IfEq(GameFlag(4218), 0)
            Call(GetModelCenter, 210)
            Call(mac_01_RowfShop_SetBadgePos, 0)
        EndIf
        IfEq(GameFlag(4219), 0)
            Call(GetModelCenter, 209)
            Call(mac_01_RowfShop_SetBadgePos, 1)
        EndIf
        IfEq(GameFlag(4220), 0)
            Call(GetModelCenter, 208)
            Call(mac_01_RowfShop_SetBadgePos, 2)
        EndIf
        IfEq(GameFlag(4221), 0)
            Call(GetModelCenter, 207)
            Call(mac_01_RowfShop_SetBadgePos, 3)
        EndIf
        IfEq(GameFlag(4222), 0)
            Call(GetModelCenter, 206)
            Call(mac_01_RowfShop_SetBadgePos, 4)
        EndIf
        Wait(1)
        Goto(0)
    EndThread
    Return
    End
};

u8 TTYD64_mac_01_String_Rowf_TooMuchStock[] = {
    0xFC, 0x01, 0x33, 0x4F, 0x52, 0x52, 0x59, 0xF7, 0x42, 0x55, 0x44, 0x0C,
    0xF7, 0x42, 0x55, 0x54, 0xF7, 0x49, 0x54, 0xF7, 0x53, 0x45, 0x45, 0x4D,
    0x53, 0xF7, 0x54, 0x48, 0x41, 0x54, 0xF7, 0x4E, 0x4F, 0x57, 0xF0, 0x29,
    0xF7, 0x41, 0x4C, 0x52, 0x45, 0x41, 0x44, 0x59, 0xF7, 0x48, 0x41, 0x56,
    0x45, 0xF7, 0x54, 0x4F, 0x4F, 0xF7, 0x42, 0x49, 0x47, 0xF7, 0x49, 0x4E,
    0x56, 0x45, 0x4E, 0x54, 0x4F, 0x52, 0x59, 0x0C, 0xF0, 0x29, 0xF7, 0x43,
    0x41, 0x4E, 0x07, 0x54, 0xF7, 0x42, 0x55, 0x59, 0xF7, 0x41, 0x4E, 0x59,
    0x54, 0x48, 0x49, 0x4E, 0x47, 0xF7, 0x46, 0x52, 0x4F, 0x4D, 0xF7, 0x59,
    0x4F, 0x55, 0xF7, 0x46, 0x4F, 0x52, 0xF0, 0x4E, 0x4F, 0x57, 0x0E, 0xF1,
    0xFD
};

NpcGroupList TTYD64_mac_01_NpcGroupList_8025F044 = {
    { .npcCount = 1, .npcs = &mac_01_NpcData_Parakarry, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = &mac_01_NpcData_Merlon, .battle = 0x0000, .stage = 0 },
    { .npcCount = 2, .npcs = mac_01_NpcData_RowfAndRhuff, .battle = 0x0000, .stage = 0 },
    { .npcCount = 10, .npcs = mac_01_NpcData_Townsfolk, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_01_NpcGroup_Settings, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_01_NpcGroup_NGPlus, .battle = 0x0000, .stage = 0 },
    {},
};

u8 TTYD64_mac_01_String_Rowf_NoStock[] = {
    0xFC, 0x01, 0x33, 0x4F, 0x52, 0x52, 0x59, 0xF7, 0x42, 0x55, 0x44, 0x0C,
    0xF7, 0x42, 0x55, 0x54, 0xF7, 0x52, 0x49, 0x47, 0x48, 0x54, 0xF7, 0x4E,
    0x4F, 0x57, 0x0C, 0xF7, 0x57, 0x45, 0xF7, 0x41, 0x52, 0x45, 0xF0, 0x4F,
    0x55, 0x54, 0xF7, 0x4F, 0x46, 0xF7, 0x53, 0x54, 0x4F, 0x43, 0x4B, 0x0C,
    0xF7, 0x50, 0x4C, 0x45, 0x41, 0x53, 0x45, 0xF7, 0x43, 0x4F, 0x4D, 0x45,
    0xF7, 0x42, 0x41, 0x43, 0x4B, 0xF0, 0x4C, 0x41, 0x54, 0x45, 0x52, 0x0E,
    0xF1, 0xFD
};

u8 TTYD64_mac_01_Script_Merlon_Start[] = {
    0xFC, 0x01, 0x28, 0x45, 0x4C, 0x4C, 0x4F, 0xF7, 0x2D, 0x41, 0x52, 0x49,
    0x4F, 0x0C, 0xF7, 0x48, 0x4F, 0x57, 0xF7, 0x43, 0x41, 0x4E, 0xF7, 0x29,
    0xF7, 0x48, 0x45, 0x4C, 0x50, 0xF7, 0x59, 0x4F, 0x55, 0xF0, 0x54, 0x4F,
    0x44, 0x41, 0x59, 0x1F, 0xF0, 0xFF, 0x04, 0xFD
};

EvtScript TTYD64_mac_01_Script_Init_802560B4 = {
    ExecWait(TTYD64_mac_01_Script_InitRowf)
    Return
    End
};

NpcData TTYD64_mac_01_NpcGroup_Settings[] = {
    {
        .id = 39,
        .settings = &TTYD64_mac_01_NpcSettings_8024C5BC,
        .pos = { 335.0f, 20.0f, -161.0f },
        .flags = 0x00402D09,
        .init = &TTYD64_Script_Init_NPC_Settings,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x008C0401, .walk = 0x008C0400, .run = 0x008C0400, .chase = 0x008C0400, .anim_4 = 0x008C0400, .anim_5 = 0x008C0400, .death = 0x008C0400, .hit = 0x008C0400, .anim_8 = 0x008C0400, .anim_9 = 0x008C0400, .anim_A = 0x008C0400, .anim_B = 0x008C0400, .anim_C = 0x008C0400, .anim_D = 0x008C0400, .anim_E = 0x008C0400, .anim_F = 0x008C0400 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

u8 TTYD64_mac_01_String_Rowf_Welcome[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0x01, 0xF7, 0x37, 0x45, 0x4C, 0x43, 0x4F,
    0x4D, 0x45, 0x0C, 0xF7, 0x42, 0x55, 0x44, 0x44, 0x59, 0x01, 0xF0, 0xF2,
    0x0A, 0x37, 0x45, 0x4C, 0x4C, 0x0C, 0xF7, 0x57, 0x45, 0xF7, 0x47, 0x4F,
    0x54, 0xF7, 0x49, 0x54, 0xF7, 0x4F, 0x50, 0x45, 0x4E, 0x01, 0xF0, 0xF2,
    0x0A, 0x37, 0x48, 0x41, 0x54, 0xF7, 0x44, 0x4F, 0xF7, 0x59, 0x4F, 0x55,
    0xF7, 0x54, 0x48, 0x49, 0x4E, 0x4B, 0x1F, 0xF0, 0x30, 0x52, 0x45, 0x54,
    0x54, 0x59, 0xF7, 0x53, 0x50, 0x45, 0x43, 0x54, 0x41, 0x43, 0x55, 0x4C,
    0x41, 0x52, 0xF7, 0x53, 0x48, 0x4F, 0x50, 0x0C, 0xF7, 0x48, 0x55, 0x48,
    0x1F, 0xF0, 0xF1, 0xFB, 0x28, 0x4F, 0x57, 0xF7, 0x41, 0x42, 0x4F, 0x55,
    0x54, 0xF7, 0x42, 0x55, 0x59, 0x49, 0x4E, 0x47, 0xF7, 0x53, 0x4F, 0x4D,
    0x45, 0x54, 0x48, 0x49, 0x4E, 0x47, 0x1F, 0xF0, 0xFF, 0x04, 0xFD
};

u8 TTYD64_mac_01_Tattle_NGPlus[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x28, 0x45, 0xF7, 0x49, 0x53, 0xF7, 0x25, 0x4C,
    0x44, 0x53, 0x54, 0x41, 0x52, 0x0C, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x43,
    0x41, 0x4E, 0xF7, 0x54, 0x41, 0x4C, 0x4B, 0xF7, 0x54, 0x4F, 0xF0, 0x49,
    0x46, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x57, 0x41, 0x4E, 0x54, 0xF7, 0x54,
    0x4F, 0xF7, 0x53, 0x54, 0x41, 0x52, 0x54, 0xF7, 0x41, 0xF7, 0x4E, 0x45,
    0x57, 0xF7, 0x47, 0x41, 0x4D, 0x45, 0xF0, 0x50, 0x4C, 0x55, 0x53, 0xF7,
    0x50, 0x4C, 0x41, 0x59, 0x54, 0x48, 0x52, 0x4F, 0x55, 0x47, 0x48, 0x0E,
    0xF1, 0xFD
};

NpcGroupList TTYD64_mac_01_NpcGroupList_8025F0BC = {
    { .npcCount = 4, .npcs = mac_01_NpcData_ShyGuys, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = &mac_01_NpcData_Merlon, .battle = 0x0000, .stage = 0 },
    { .npcCount = 2, .npcs = mac_01_NpcData_RowfAndRhuff, .battle = 0x0000, .stage = 0 },
    { .npcCount = 10, .npcs = mac_01_NpcData_Townsfolk, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_01_NpcGroup_Settings, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_01_NpcGroup_NGPlus, .battle = 0x0000, .stage = 0 },
    {},
};

NpcSettings TTYD64_mac_01_NpcSettings_8024C5BC = {
    .defaultAnim = 0x00000000,
    .height = 26,
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

EvtScript TTYD64_mac_01_Script_80247E74 = {
    Switch(LVar0)
    CaseEq(3)
    CaseEq(4)
    CaseEq(1)
        Switch(LVar2)
        CaseEq(0)
            Set(GameFlag(4218), 1)
            Call(ModifyColliderFlags, 0, 102, 0x7FFFFE00)
        CaseEq(1)
            Set(GameFlag(4219), 1)
            Call(ModifyColliderFlags, 0, 101, 0x7FFFFE00)
        CaseEq(2)
            Set(GameFlag(4220), 1)
            Call(ModifyColliderFlags, 0, 100, 0x7FFFFE00)
        CaseEq(3)
            Set(GameFlag(4221), 1)
            Call(ModifyColliderFlags, 0, 99, 0x7FFFFE00)
        CaseEq(4)
            Set(GameFlag(4222), 1)
            Call(ModifyColliderFlags, 0, 98, 0x7FFFFE00)
        EndSwitch
        Call(TTYD64_mac_01_Function_SetSaleBadgeGlobalFlag, LVar2)
    CaseEq(2)
    EndSwitch
    Return
    End
};

u8 TTYD64_mac_01_String_Rowf_PleaseComeBack[] = {
    0xFB, 0x30, 0x4C, 0x45, 0x41, 0x53, 0x45, 0xF7, 0x43, 0x4F, 0x4D, 0x45,
    0xF7, 0x41, 0x47, 0x41, 0x49, 0x4E, 0x0E, 0xF1, 0xFD
};

EvtScript TTYD64_mac_01_Script_80261880 = {
    Call(DisablePlayerInput, 1)
    Call(EnableModel, 205, 0)
    Call(TTYD64_mac_01_Function_802463E0_2)
    Call(UseSettingsFrom, 0, -560, 0, 0)
    Call(SetPanTarget, 0, -560, 0, 0)
    Call(SetCamDistance, 0, Float(250.0))
    Call(SetCamSpeed, 0, Float(90.0))
    Call(PanToTarget, 0, 0, 1)
    Call(WaitForCam, 0, Float(1.0))
    Call(SetNpcPos, 0, -460, 0, 0)
    Call(SetNpcYaw, 0, 90)
    Thread
        Call(func_802D1270, -100, 0, Float(4.0))
        Call(func_802D1270, -25, -25, Float(4.0))
        Call(func_802D1270, 0, -100, Float(4.0))
        Call(func_802D1270, 0, -400, Float(4.0))
    EndThread
    Thread
        Call(SetNpcSpeed, 0, Float(4.0))
        Call(SetNpcAnimation, 0, 0x82000A)
        Call(NpcMoveTo, 0, -100, 0, 0)
        Call(SetNpcAnimation, 0, 0x82001E)
        Call(NpcMoveTo, 0, -25, -25, 0)
        Call(NpcMoveTo, 0, 0, -100, 0)
        Call(NpcMoveTo, 0, 0, -340, 0)
        Call(SetNpcAnimation, 0, 0x82001C)
    EndThread
    Call(SetCamSpeed, 0, Float(90.0))
    Call(MakeLerp, 300, 400, 100, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(GetPlayerPos, LVar2, LVar3, LVar4)
        Call(SetPanTarget, 0, LVar2, LVar3, LVar4)
        Call(SetCamDistance, 0, LVar0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(PanToTarget, 0, 0, 0)
    Wait(75)
    Call(GotoMap, (Bytecode) "osr_00", 4)
    Wait(100)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_mac_01_Script_Interact_Rowf = {
    Call(SpeakToPlayer, -1, 0xA70004, 0xA70001, 0, (Bytecode) TTYD64_mac_01_String_Rowf_Welcome)
    Call(ShowChoice, (Bytecode) TTYD64_mac_01_String_Rowf_Choice1)
    Switch(LVar0)
    CaseEq(0)
        Call(ContinueSpeech, -1, 0xA70004, 0xA70001, 0, (Bytecode) TTYD64_mac_01_String_Rowf_WhatKind)
        Call(ShowChoice, (Bytecode) TTYD64_mac_01_String_Rowf_Choice2)
        Switch(LVar0)
        CaseEq(0)
            Call(ContinueSpeech, -1, 0xA70004, 0xA70001, 0, (Bytecode) TTYD64_mac_01_String_Rowf_PressA)
        CaseEq(1)
            Call(CloseMessage)
            Call(TTYD64_Function_GetOtherBadgesAmount, LVar0)
            IfEq(LVar0, 0)
                Call(SpeakToPlayer, -1, 0xA70004, 0xA70001, 0, (Bytecode) TTYD64_mac_01_String_Rowf_NoStock)
                Return
            EndIf
            Set(LVarA, 0)
            Set(LVarB, 0)
            Set(LVar3, 0)
            Label(0)
            Call(ShowCoinCounter, 1)
            Call(TTYD64_SetShopBuyPopup, 1)
            Call(TTYD64_Function_ShowInventory_Others)
            Call(TTYD64_SetShopBuyPopup, 0)
            IfEq(LVar0, -1)
                IfNe(LVar3, 0)
                    Wait(10)
                    Goto(0)
                EndIf
                Call(ShowCoinCounter, 0)
                Return
            EndIf
            Set(LVar9, LVar0)
            Call(TTYD64_GetItemGlobalData, LVar0, LVar5)
            Call(TTYD64_ReadPtrField, LVar5, TTYD64_F_ITEMDATA_0_4U, LVar7)
            Call(TTYD64_ReadPtrField, LVar5, TTYD64_F_ITEMDATA_1A_1U, LVar8)
            Call(TTYD64_GetMoveData, LVar8, LVar8)
            Call(TTYD64_ReadPtrField, LVar8, TTYD64_F_MOVEDATA_12_1U, LVar8)
            Call(SetMessageText, LVar4, 0)
            Call(SetMessageValue, LVar1, 1)
            Call(SetMessageValue, LVar8, 2)
            Call(SpeakToPlayer, -1, 0xA70004, 0xA70001, 0, 0x270017)
            Call(ShowChoice, 0x1E000D)
            IfNe(LVar0, 0)
                Call(CloseMessage)
                Wait(10)
                Goto(0)
            EndIf
            Mul(LVar1, -1)
            Call(AddCoin, LVar1)
            Call(ShowCoinCounter, 0)
            Call(ContinueSpeech, -1, 0xA70004, 0xA70001, 0, (Bytecode) TTYD64_mac_01_String_Rowf_PleaseComeBack)
            Call(ShowGotItem, LVar9, 1, 0)
            Call(TTYD64_maps_AddBadge, LVar9, 0)
            Call(TTYD64_Function_GetTypeOfBadge, LVar6, LVar7)
            IfNe(LVar7, 0)
                Call(TTYD64_maps_WriteModBytesBE16, LVar6, 0)
            Else
                Call(TTYD64_mac_01_Function_SetVarFromVar, LVar6, 1)
            EndIf
            Call(TTYD64_Function_GetOtherBadgesAmount, LVar0)
            IfGt(LVar0, 0)
                Wait(10)
                Goto(0)
            EndIf
        CaseEq(2)
            Call(CloseMessage)
        EndSwitch
    CaseEq(1)
        Call(CloseMessage)
        Call(TTYD64_Function_GetPlayerBadgesAmount, LVar0)
        IfEq(LVar0, 0)
            Call(SpeakToPlayer, -1, 0xA70004, 0xA70001, 0, (Bytecode) TTYD64_mac_01_String_Rowf_NoBadges)
            Return
        EndIf
        Call(TTYD64_Function_GetSoldBadgesAmount, LVar0)
        IfGe(LVar0, 130)
            Call(SpeakToPlayer, -1, 0xA70004, 0xA70001, 0, (Bytecode) TTYD64_mac_01_String_Rowf_TooMuchStock)
            Return
        EndIf
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVar3, 0)
        Label(1)
        Call(ShowCoinCounter, 1)
        Call(TTYD64_Function_ShowInventory_PlayerBadges)
        IfEq(LVar0, -1)
            IfNe(LVar3, 0)
                Wait(15)
                Goto(1)
            EndIf
            Call(ShowCoinCounter, 0)
            Return
        EndIf
        Set(LVar9, LVar0)
        Call(TTYD64_GetItemGlobalData, LVar0, LVar5)
        Call(TTYD64_ReadPtrField, LVar5, TTYD64_F_ITEMDATA_0_4U, LVar7)
        Call(TTYD64_ReadPtrField, LVar5, TTYD64_F_ITEMDATA_1A_1U, LVar8)
        Call(TTYD64_GetMoveData, LVar8, LVar8)
        Call(TTYD64_ReadPtrField, LVar8, TTYD64_F_MOVEDATA_12_1U, LVar8)
        Call(SetMessageText, LVar4, 0)
        Call(SetMessageValue, LVar1, 1)
        Call(ShowCoinCounter, 1)
        Call(SpeakToPlayer, -1, 0xA70004, 0xA70001, 0, (Bytecode) TTYD64_mac_01_String_Rowf_Sell_Confirmation)
        Call(ShowChoice, 0x1E000D)
        IfNe(LVar0, 0)
            Call(CloseMessage)
            Wait(15)
            Goto(1)
        EndIf
        Call(AddCoin, LVar1)
        Call(ShowCoinCounter, 0)
        Call(ContinueSpeech, -1, 0xA70004, 0xA70001, 0, (Bytecode) TTYD64_mac_01_String_Rowf_PleaseComeBack)
        Call(TTYD64_maps_RemoveBadge, LVar9)
        Call(TTYD64_Function_AddBadgeToSoldInventory, LVar9)
        Call(TTYD64_Function_GetSoldBadgesAmount, LVar0)
        IfLt(LVar0, 130)
            Call(TTYD64_Function_GetPlayerBadgesAmount, LVar0)
            IfGt(LVar0, 0)
                Wait(15)
                Goto(1)
            EndIf
        EndIf
    CaseEq(2)
        Call(CloseMessage)
        Return
    EndSwitch
    Call(TTYD64_Function_Inventory_ClearPageData)
    Return
    End
};

EvtScript TTYD64_mac_01_Script_80255B30 = {
    Set(MapFlag(11), 0)
    IfEq(GameFlag(4218), 0)
        Call(ModifyColliderFlags, 0, 102, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4219), 0)
        Call(ModifyColliderFlags, 0, 101, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4220), 0)
        Call(ModifyColliderFlags, 0, 100, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4221), 0)
        Call(ModifyColliderFlags, 0, 99, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4222), 0)
        Call(ModifyColliderFlags, 0, 98, 0x7FFFFE00)
    EndIf
    Call(NpcJump0, 1, -220, -54, 261, 16)
    Thread
        Call(PlaySoundAtCollider, 67, 172, 0)
        Call(MakeLerp, 0, 600, 50, 0)
        Label(10)
        Call(UpdateLerp)
        Call(RotateGroup, 147, LVar0, 0, 1, 0)
        DivF(LVar0, Float(10.0))
        Set(MapVar(1), LVar0)
        Call(RotateGroup, 211, LVar0, 0, 1, 0)
        DivF(LVar0, Float(200.0))
        AddF(LVar0, Float(1.0))
        Call(ScaleGroup, 147, LVar0, 1, LVar0)
        IfEq(LVar1, 1)
            Wait(1)
            Goto(10)
        EndIf
        Call(EnableModel, 205, 0)
        Call(TTYD64_mac_01_Function_80244D68_2)
    EndThread
    Wait(10)
    Thread
        Call(MakeLerp, -220, 0, 20, 1)
        Label(0)
        Call(UpdateLerp)
        Call(RotateModel, 148, LVar0, 1, 0, 0)
        IfEq(LVar1, 1)
            Wait(1)
            Goto(0)
        EndIf
        Call(PlaySoundAt, 171, 0, -220, 37, 271)
    EndThread
    Wait(15)
    Thread
        Call(MakeLerp, -120, 0, 10, 10)
        Label(1)
        Call(UpdateLerp)
        DivF(LVar0, Float(10.0))
        Call(TranslateModel, 150, 0, LVar0, 0)
        IfEq(LVar1, 1)
            Wait(1)
            Goto(1)
        EndIf
    EndThread
    Thread
        Call(MakeLerp, 100, 0, 5, 10)
        Label(2)
        Call(UpdateLerp)
        DivF(LVar0, Float(10.0))
        Call(TranslateModel, 152, 0, 0, LVar0)
        IfEq(LVar1, 1)
            Wait(1)
            Goto(2)
        EndIf
    EndThread
    Wait(31)
    Return
    End
};

EvtScript TTYD64_mac_01_Script_8025573C = {
    Set(MapFlag(11), 1)
    Call(SetNpcYaw, 1, 270)
    Thread
        Call(PlaySoundAt, 169, 0, -220, 37, 271)
        Call(MakeLerp, 0, -220, 30, 9)
        Label(0)
        Call(UpdateLerp)
        Call(RotateModel, 148, LVar0, 1, 0, 0)
        IfEq(LVar1, 1)
            Wait(1)
            Goto(0)
        EndIf
    EndThread
    Wait(4)
    Thread
        Call(MakeLerp, 0, -120, 10, 7)
        Label(1)
        Call(UpdateLerp)
        DivF(LVar0, Float(10.0))
        Call(TranslateModel, 150, 0, LVar0, 0)
        IfEq(LVar1, 1)
            Wait(1)
            Goto(1)
        EndIf
    EndThread
    Thread
        Call(MakeLerp, 0, 100, 5, 7)
        Label(2)
        Call(UpdateLerp)
        DivF(LVar0, Float(10.0))
        Call(TranslateModel, 152, 0, 0, LVar0)
        IfEq(LVar1, 1)
            Wait(1)
            Goto(2)
        EndIf
    EndThread
    Call(EnableModel, 205, 1)
    Call(TTYD64_mac_01_Function_80244CC0_2)
    Call(PlaySoundAtCollider, 67, 170, 0)
    UseBuf((Bytecode) mac_01_D_802555AC_815E2C)
    Loop(50)
        BufRead2(LVar0, MapVar(0))
        Call(RotateGroup, 147, LVar0, 0, 1, 0)
        DivF(LVar0, Float(10.0))
        Set(MapVar(1), LVar0)
        Call(RotateGroup, 211, LVar0, 0, 1, 0)
        DivF(LVar0, Float(200.0))
        AddF(LVar0, Float(1.0))
        Call(ScaleGroup, 147, LVar0, 1, LVar0)
        Wait(1)
    EndLoop
    Call(NpcJump0, 1, -213, 6, 256, 16)
    IfEq(GameFlag(4218), 0)
        Call(ModifyColliderFlags, 1, 102, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4219), 0)
        Call(ModifyColliderFlags, 1, 101, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4220), 0)
        Call(ModifyColliderFlags, 1, 100, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4221), 0)
        Call(ModifyColliderFlags, 1, 99, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4222), 0)
        Call(ModifyColliderFlags, 1, 98, 0x7FFFFE00)
    EndIf
    Return
    End
};

u8 TTYD64_mac_01_String_Rowf_Sell_Confirmation[] = {
    0xFC, 0x01, 0x2C, 0x4F, 0x4F, 0x4B, 0x0C, 0xF7, 0x4A, 0x55, 0x53, 0x54,
    0xF7, 0x42, 0x45, 0x43, 0x41, 0x55, 0x53, 0x45, 0xF7, 0x49, 0x54, 0x07,
    0x53, 0xF7, 0x59, 0x4F, 0x55, 0x0C, 0xF7, 0x29, 0x07, 0x4C, 0x4C, 0xF0,
    0x42, 0x55, 0x59, 0xF7, 0x54, 0x48, 0x41, 0x54, 0xF7, 0xFF, 0x24, 0xFF,
    0x05, 0x20, 0xFF, 0x28, 0x00, 0xFF, 0x25, 0xF7, 0x46, 0x4F, 0x52, 0xF7,
    0x4F, 0x4E, 0x4C, 0x59, 0xF0, 0xFF, 0x24, 0xFF, 0x05, 0x20, 0xFF, 0x28,
    0x01, 0xF7, 0x43, 0x4F, 0x49, 0x4E, 0x53, 0xFF, 0x25, 0x0C, 0xF7, 0x57,
    0x48, 0x41, 0x54, 0xF7, 0x44, 0x4F, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x54,
    0x48, 0x49, 0x4E, 0x4B, 0xF0, 0x42, 0x55, 0x44, 0x44, 0x59, 0x1F, 0xF0,
    0xFF, 0x04, 0xFD
};

NpcGroupList TTYD64_mac_01_NpcGroupList_8025EFA8 = {
    { .npcCount = 1, .npcs = &mac_01_NpcData_Merlon, .battle = 0x0000, .stage = 0 },
    { .npcCount = 2, .npcs = mac_01_NpcData_RowfAndRhuff, .battle = 0x0000, .stage = 0 },
    { .npcCount = 10, .npcs = mac_01_NpcData_Townsfolk, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = &mac_01_NpcData_Kolorado, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = &mac_01_NpcData_ChuckQuizmo, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_01_NpcGroup_Settings, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_01_NpcGroup_NGPlus, .battle = 0x0000, .stage = 0 },
    {},
};

NpcGroupList TTYD64_mac_01_NpcGroupList_8025F080 = {
    { .npcCount = 1, .npcs = &mac_01_NpcData_Twink, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = &mac_01_NpcData_Merlon, .battle = 0x0000, .stage = 0 },
    { .npcCount = 2, .npcs = mac_01_NpcData_RowfAndRhuff, .battle = 0x0000, .stage = 0 },
    { .npcCount = 10, .npcs = mac_01_NpcData_Townsfolk, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_01_NpcGroup_Settings, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_01_NpcGroup_NGPlus, .battle = 0x0000, .stage = 0 },
    {},
};

u8 TTYD64_mac_01_String_Rowf_Choice2[] = {
    0xFC, 0x05, 0x65, 0x5A, 0x8A, 0x2E, 0xFF, 0x09, 0xFF, 0x1E, 0x00, 0xFF,
    0x21, 0x00, 0x33, 0x50, 0x45, 0x43, 0x49, 0x41, 0x4C, 0xF7, 0x24, 0x45,
    0x41, 0x4C, 0x53, 0xF0, 0xFF, 0x1E, 0x01, 0xFF, 0x21, 0x01, 0x2F, 0x54,
    0x48, 0x45, 0x52, 0x53, 0xF0, 0xFF, 0x21, 0xFF, 0xFF, 0x0A, 0xFF, 0x20,
    0x02, 0xFF, 0x1F, 0x02, 0xFD
};

u8 TTYD64_mac_01_String_Rowf_WhatKind[] = {
    0xFB, 0x37, 0x48, 0x41, 0x54, 0xF7, 0x4B, 0x49, 0x4E, 0x44, 0xF7, 0x4F,
    0x46, 0xF7, 0x42, 0x41, 0x44, 0x47, 0x45, 0x53, 0xF7, 0x49, 0x4E, 0x54,
    0x45, 0x52, 0x45, 0x53, 0x54, 0xF0, 0x59, 0x4F, 0x55, 0x1F, 0x01, 0x1F,
    0xF0, 0xFF, 0x04, 0xFD
};
// clang-format on

void TTYD64_InstallMap_mac_01(void) {
    Mod_ReplaceScript("TTYD64", &mac_01_EVS_Main, &TTYD64_mac_01_Script_Main);
    Mod_ReplaceScript("TTYD64", &mac_01_EVS_NpcInteract_Rhuff_C, &TTYD64_mac_01_Script_Interact_80254A58);
    memcpy(&mac_01_ShopOwnerRowf, &TTYD64_mac_01_ShopOwnerRowf, sizeof(TTYD64_mac_01_ShopOwnerRowf));
    Mod_ReplaceScript("TTYD64", &mac_01_EVS_SetupBadgeShop, &TTYD64_mac_01_Script_80248070);
    Mod_ReplaceScript("TTYD64", &mac_01_EVS_UpdateRhuffAnims, &TTYD64_mac_01_Script_Idle_80255500);
    Mod_ReplaceScript("TTYD64", &mac_01_EVS_NpcInit_Rowf, &TTYD64_mac_01_Script_Init_802560B4);
    Mod_ReplaceScript("TTYD64", &mac_01_EVS_OnBuy, &TTYD64_mac_01_Script_80247E74);
    Mod_ReplaceScript("TTYD64", &mac_01_EVS_Scene_IntroWalking, &TTYD64_mac_01_Script_80261880);
    Mod_ReplaceScript("TTYD64", &mac_01_EVS_Rhuff_HideBadges, &TTYD64_mac_01_Script_80255B30);
    Mod_ReplaceScript("TTYD64", &mac_01_EVS_Rhuff_RevealBadges, &TTYD64_mac_01_Script_8025573C);
    TTYD64_mac_01_NpcGroup_NGPlus[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_01_Tattle_NGPlus);
    TTYD64_mac_01_NpcGroup_Settings[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_01_Tattle_SettingsNPC);
    TTYD64_maps_BindInlineMessage(TTYD64_mac_01_Script_InteractCrystalBall, TTYD64_mac_01_Script_Merlon_Start);
    TTYD64_maps_BindInlineMessage(TTYD64_mac_01_Script_InteractCrystalBall, TTYD64_mac_01_String_Choice_Merlon);
    TTYD64_maps_BindInlineMessage(TTYD64_mac_01_Script_Interact_Rowf, TTYD64_mac_01_String_Rowf_Welcome);
    TTYD64_maps_BindInlineMessage(TTYD64_mac_01_Script_Interact_Rowf, TTYD64_mac_01_String_Rowf_Choice1);
    TTYD64_maps_BindInlineMessage(TTYD64_mac_01_Script_Interact_Rowf, TTYD64_mac_01_String_Rowf_WhatKind);
    TTYD64_maps_BindInlineMessage(TTYD64_mac_01_Script_Interact_Rowf, TTYD64_mac_01_String_Rowf_Choice2);
    TTYD64_maps_BindInlineMessage(TTYD64_mac_01_Script_Interact_Rowf, TTYD64_mac_01_String_Rowf_PressA);
    TTYD64_maps_BindInlineMessage(TTYD64_mac_01_Script_Interact_Rowf, TTYD64_mac_01_String_Rowf_NoStock);
    TTYD64_maps_BindInlineMessage(TTYD64_mac_01_Script_Interact_Rowf, TTYD64_mac_01_String_Rowf_PleaseComeBack);
    TTYD64_maps_BindInlineMessage(TTYD64_mac_01_Script_Interact_Rowf, TTYD64_mac_01_String_Rowf_NoBadges);
    TTYD64_maps_BindInlineMessage(TTYD64_mac_01_Script_Interact_Rowf, TTYD64_mac_01_String_Rowf_TooMuchStock);
    TTYD64_maps_BindInlineMessage(TTYD64_mac_01_Script_Interact_Rowf, TTYD64_mac_01_String_Rowf_Sell_Confirmation);
}
