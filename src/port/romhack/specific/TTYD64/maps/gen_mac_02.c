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

extern s32 MysteryResultOptions[];
extern EvtScript mac_02_EVS_ChooseItem;
extern EvtScript mac_02_EVS_ChooseItem_OddKey;
extern EvtScript mac_02_EVS_ChooseKeyItem;
extern EvtScript mac_02_EVS_MakeEntities;
extern EvtScript mac_02_EVS_OnInspect_StreetSign;
extern EvtScript mac_02_EVS_ReadSign;
extern EvtScript mac_02_EVS_Scene_TayceTCooking;
extern EvtScript mac_02_EVS_TayceT_Cook;
extern EvtScript mac_02_EVS_TayceT_FryingPanAndCake;
extern EvtScript mac_02_EVS_TayceT_RequestCookbook;
extern EvtScript mac_02_GiveItemReward;
extern s32 mac_02_ItemList_FryingPan[];
extern s32 mac_02_ItemList_OddKey[];

API_CALLABLE(AddItem);
API_CALLABLE(AssignCrateFlag);
API_CALLABLE(AssignPanelFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(CloseMessage);
API_CALLABLE(ContinueSpeech);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(GetEntryID);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveItem);
API_CALLABLE(RemoveKeyItemAt);
API_CALLABLE(SetMessageText);
API_CALLABLE(ShowChoice);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(mac_02_CheckItemsHasRoom);
API_CALLABLE(mac_02_GetItemCount);
API_CALLABLE(mac_02_GetItemName);

extern EvtScript TTYD64_mac_02_TayceT_WalkToCook;
extern EvtScript TTYD64_mac_02_Script_HandleMysteryCooked;
extern s32 TTYD64_mac_02_IntTable_8024909C[];
extern EvtScript TTYD64_mac_02_Script_8024926C;
extern EvtScript TTYD64_mac_02_Script_80249550;
extern EvtScript TTYD64_mac_02_Script_80249684;
extern s32 TTYD64_mac_02_IntTable_RecipeTable[];
extern EvtScript TTYD64_mac_02_Script_Get1ItemRecipe;
extern s32 TTYD64_mac_02_RecipesDiscovedIDs[];
extern s32 TTYD64_mac_02_RecipesDiscovedFlags[];
extern EvtScript TTYD64_mac_02_Script_MakeEntities;
extern EvtScript TTYD64_mac_02_Script_Get2ItemRecipe;
extern EvtScript TTYD64_mac_02_Script_GetReaction;
extern s32 TTYD64_mac_02_IntTable_ItemReactions[];
extern u8 TTYD64_mac_02_AllRecipes[];
extern EvtScript TTYD64_mac_02_Script_InitNewStuff;
extern Bytecode TTYD64_mac_02_SpecialCookingResultHandlers[];

// clang-format off
EvtScript TTYD64_mac_02_TayceT_WalkToCook = {
    IfEq(0, 0)
        ExecWait(mac_02_EVS_Scene_TayceTCooking)
    EndIf
    Return
    End
};

EvtScript TTYD64_mac_02_Script_HandleMysteryCooked = {
    Call(RandInt, 1000, LVarF)
    IfGt(LVarF, 500)
        Set(LVar6, 194)
        Return
    EndIf
    Call(RandInt, 10000, LVarF)
    Mod(LVarF, 23)
    Add(LVarF, 1)
    UseBuf((Bytecode) MysteryResultOptions)
    Loop(LVarF)
        BufRead1(LVar6)
    EndLoop
    Return
    End
};

s32 TTYD64_mac_02_IntTable_8024909C[] = {
    128, 137, 427, 143, 149, 154,
    139, 182, 181, 176, 195, 199,
    201, 216, 213, 202, 189, 130,
    200, 177, 211, 192, 191
};

EvtScript TTYD64_mac_02_Script_8024926C = {
    IfEq(GameFlag(281), 1)
        Call(mac_02_CheckItemsHasRoom, LVar0)
        IfNe(LVar0, 0)
            Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x4001A)
            Set(LVar0, 439)
            Set(LVar1, 0)
            ExecWait(mac_02_GiveItemReward)
            Call(AddItem, 439, LVar0)
            Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x4001B)
            Set(GameByte(0), -3)
        Else
            Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x4001C)
            Set(GameFlag(281), 1)
        EndIf
        Return
    EndIf
    Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0006, 0, 0x40017)
    Set(LVar0, (Bytecode) mac_02_ItemList_FryingPan)
    Set(LVar1, 0)
    ExecWait(mac_02_EVS_ChooseKeyItem)
    Switch(LVar0)
    CaseEq(0)
    CaseEq(-1)
        Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0006, 0, 0x40018)
    CaseDefault
        Call(SpeakToPlayer, 0, 0xAA0005, 0xAA0001, 0, 0x40019)
        ExecWait(mac_02_EVS_Scene_TayceTCooking)
        Call(mac_02_CheckItemsHasRoom, LVar0)
        IfNe(LVar0, 0)
            Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x4001A)
            Set(LVar0, 439)
            Set(LVar1, 0)
            ExecWait(mac_02_GiveItemReward)
            Call(AddItem, 439, LVar0)
            Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x4001B)
            Set(GameByte(0), -3)
        Else
            Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x4001C)
            Set(GameFlag(281), 1)
        EndIf
    EndSwitch
    Return
    End
};

EvtScript TTYD64_mac_02_Script_80249550 = {
    Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x4001D)
    Set(GameFlag(282), 1)
    Call(TTYD64_maps_FindKeyItem, 41, LVar0)
    Call(RemoveKeyItemAt, LVar0)
    Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x40020)
    Return
    End
};

EvtScript TTYD64_mac_02_Script_80249684 = {
    Call(DisablePlayerInput, 1)
    IfEq(GameFlag(280), 0)
        Set(GameFlag(280), 1)
        Set(AreaFlag(1), 1)
        Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x40000)
    Else
        IfEq(AreaFlag(1), 0)
            Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x40001)
            Set(AreaFlag(1), 1)
        Else
            Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x40002)
        EndIf
    EndIf
    Call(mac_02_GetItemCount, LVar0)
    IfLe(LVar0, 0)
        Call(ContinueSpeech, 0, 0xAA0004, 0xAA0001, 0, 0x40003)
        Goto(9)
    EndIf
    Call(ShowChoice, 0x1E0010)
    IfEq(LVar0, 1)
        Call(ContinueSpeech, 0, 0xAA0004, 0xAA0001, 0, 0x40004)
        Goto(9)
    EndIf
    Call(ContinueSpeech, 0, 0xAA0004, 0xAA0001, 0, 0x40005)
    Label(1)
    Set(LVar3, 0)
    Call(TTYD64_mac_02_TayceT_MakeItemList)
    Set(LVar0, (Bytecode) TTYD64_mac_02_TayceT_ItemChoiceList)
    Set(LVar1, 0)
    ExecWait(mac_02_EVS_ChooseItem)
    Switch(LVar0)
    CaseEq(0)
    CaseEq(-1)
        Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x40006)
        Call(ShowChoice, 0x1E0009)
        IfEq(LVar0, 0)
            Call(ContinueSpeech, 0, 0xAA0004, 0xAA0001, 0, 0x40004)
            Goto(9)
        EndIf
        Call(CloseMessage)
        Set(LVar3, 1)
    CaseDefault
        Set(LVar8, LVar0)
        Call(AddItem, LVar0, LVar1)
    EndSwitch
    IfEq(LVar3, 1)
        Goto(1)
    EndIf
    IfEq(GameFlag(282), 0)
        Goto(5)
    EndIf
    Call(mac_02_GetItemCount, LVar0)
    IfLt(LVar0, 2)
        Goto(5)
    EndIf
    Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x40007)
    Call(ShowChoice, 0x1E0010)
    Call(CloseMessage)
    IfEq(LVar0, 1)
        Goto(5)
    EndIf
    Label(2)
    Call(RemoveItem, LVar8, LVar0)
    Set(LVar3, 0)
    Call(TTYD64_mac_02_TayceT_MakeItemList)
    Set(LVar0, (Bytecode) TTYD64_mac_02_TayceT_ItemChoiceList)
    Set(LVar1, 0)
    ExecWait(mac_02_EVS_ChooseItem)
    Call(AddItem, LVar8, LVar1)
    Switch(LVar0)
    CaseEq(0)
    CaseEq(-1)
        Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x40008)
        Call(ShowChoice, 0x1E0008)
        IfEq(LVar0, 0)
            Call(CloseMessage)
            Goto(5)
        EndIf
        IfEq(LVar0, 2)
            Call(ContinueSpeech, 0, 0xAA0004, 0xAA0001, 0, 0x40004)
            Goto(9)
        EndIf
        Call(CloseMessage)
        Set(LVar3, 1)
    CaseDefault
        Set(LVar9, LVar0)
        Call(AddItem, LVar0, LVar1)
        IfEq(LVar8, LVar9)
            Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x40009)
            Set(LVar3, 1)
        EndIf
    EndSwitch
    IfEq(LVar3, 1)
        Goto(2)
    EndIf
    Set(LVar0, LVar8)
    Call(mac_02_GetItemName, LVar0)
    Call(SetMessageText, LVar0, 0)
    Set(LVar1, LVar9)
    Call(mac_02_GetItemName, LVar1)
    Call(SetMessageText, LVar1, 1)
    Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x4000B)
    Call(ShowChoice, 0x1E0010)
    IfEq(LVar0, 1)
        Call(ContinueSpeech, 0, 0xAA0004, 0xAA0001, 0, 0x4000C)
        Goto(9)
    EndIf
    ExecWait(TTYD64_mac_02_Script_Get2ItemRecipe)
    Call(RemoveItem, LVar8, LVar0)
    Call(RemoveItem, LVar9, LVar0)
    Goto(6)
    Label(5)
    Set(LVar0, LVar8)
    Call(mac_02_GetItemName, LVar0)
    Call(SetMessageText, LVar0, 0)
    Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x4000A)
    Call(ShowChoice, 0x1E0010)
    IfEq(LVar0, 1)
        Call(ContinueSpeech, 0, 0xAA0004, 0xAA0001, 0, 0x4000C)
        Goto(9)
    EndIf
    ExecWait(TTYD64_mac_02_Script_Get1ItemRecipe)
    Call(RemoveItem, LVar8, LVar0)
    Label(6)
    Call(ContinueSpeech, 0, 0xAA0004, 0xAA0001, 0, 0x4000D)
    ExecWait(TTYD64_mac_02_TayceT_WalkToCook)
    Switch(LVar7)
    CaseEq(0)
        Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x40012)
    CaseEq(2)
        Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x4000F)
    CaseEq(3)
        Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x40010)
    CaseEq(4)
        Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x40013)
    CaseDefault
        Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x40011)
    EndSwitch
    Call(ContinueSpeech, 0, 0xAA0004, 0xAA0001, 0, 0x40014)
    Call(TTYD64_mac_02_SetRecipeDiscovered, LVar6)
    Set(LVar0, LVar6)
    Set(LVar1, 0)
    ExecWait(mac_02_GiveItemReward)
    Call(AddItem, LVar6, LVar0)
    IfEq(GameFlag(4481), 0)
        Call(TTYD64_mac_02_Function_UnusedItem, LVar2)
        IfEq(LVar2, -1)
            Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, (Bytecode) TTYD64_mac_02_AllRecipes)
            Set(GameFlag(4481), 1)
        EndIf
    EndIf
    Call(SpeakToPlayer, 0, 0xAA0004, 0xAA0001, 0, 0x40015)
    Label(9)
    Call(DisablePlayerInput, 0)
    Return
    End
};

s32 TTYD64_mac_02_IntTable_RecipeTable[] = {
    148, 170, 177, 171, 170, 192,
    165, 170, 192, 159, 170, 192,
    160, 170, 192, 158, 170, 192,
    166, 165, 189, 166, 159, 189,
    166, 160, 189, 166, 158, 189,
    169, 165, 189, 169, 167, 189,
    175, 138, 189, 175, 139, 189,
    175, 140, 189, 175, 149, 189,
    175, 170, 189, 175, 171, 189,
    175, 172, 189, 175, 167, 189,
    128, 165, 189, 128, 139, 189,
    128, 140, 189, 128, 149, 189,
    182, 213, 189, 171, 139, 189,
    171, 167, 189, 167, 165, 189,
    167, 172, 189, 167, 138, 189,
    167, 139, 189, 167, 140, 189,
    167, 149, 189, 167, 159, 189,
    167, 160, 189, 167, 158, 189,
    171, 169, 216, 171, 174, 216,
    170, -1, 439, 172, 170, 423,
    213, 184, 190, 147, 169, 190,
    169, -1, 154, 169, 139, 154,
    169, 174, 154, 128, 171, 200,
    139, 170, 204, 168, 169, 128,
    170, 128, 205, 171, -1, 201,
    141, -1, 182, 138, -1, 182,
    140, -1, 182, 141, 138, 182,
    141, 128, 182, 128, 175, 212,
    191, 174, 188, 191, 141, 188,
    191, 169, 188, 170, 164, 203,
    138, 164, 202, 140, 164, 196,
    149, 164, 196, 139, 164, 196,
    142, 164, 178, 141, 140, 185,
    138, 140, 185, 141, 139, 185,
    138, 139, 185, 140, 139, 185,
    138, 128, 185, 149, -1, 185,
    139, -1, 185, 170, 162, 434,
    138, 162, 218, 140, 162, 198,
    149, 162, 198, 139, 162, 198,
    142, 162, 180, 170, 166, 211,
    170, 174, 211, 170, 163, 211,
    166, 167, 181, 166, -1, 195,
    156, 170, 208, 140, 166, 149,
    139, 166, 149, 142, 166, 149,
    149, 166, 149, 140, 165, 149,
    139, 165, 149, 142, 165, 149,
    149, 165, 149, 140, 169, 149,
    142, 169, 149, 149, 169, 149,
    157, 170, 206, 138, 163, 215,
    140, 163, 197, 149, 163, 197,
    139, 163, 197, 142, 163, 179,
    165, -1, 214, 175, -1, 213,
    138, 170, 183, 140, 170, 183,
    142, -1, 184, 142, 138, 184,
    142, 140, 184, 149, 138, 184,
    149, 140, 184, 149, 142, 184,
    139, 142, 184, 141, 142, 184,
    141, 149, 184, 159, 169, 143,
    160, 169, 143, 158, 169, 143,
    167, -1, 199, 173, -1, 191,
    173, 157, 191, 173, 156, 191,
    173, 164, 191, 173, 163, 191,
    173, 162, 191, 173, 148, 191,
    173, 159, 191, 173, 160, 191,
    173, 158, 191, 173, 166, 191,
    173, 169, 191, 162, 172, 191,
    162, 157, 191, 162, 156, 191,
    162, 164, 191, 162, 163, 191,
    162, 148, 191, 162, 159, 191,
    162, 160, 191, 162, 158, 191,
    128, -1, 176, 169, 170, 436,
    171, 437, 436, 164, -1, 427,
    163, -1, 427, 148, -1, 427,
    158, -1, 427, 159, -1, 427,
    160, -1, 427, 162, -1, 427,
    164, 163, 427, 164, 166, 427,
    157, 163, 427, 148, 163, 427,
    157, 166, 427, 157, 156, 427,
    157, 158, 427, 157, 159, 427,
    157, 160, 427, 157, 148, 427,
    156, 158, 427, 156, 159, 427,
    156, 160, 427, 156, 163, 427,
    156, 166, 427, 156, 148, 427,
    148, 158, 427, 148, 159, 427,
    148, 160, 427, 162, 166, 427,
    160, 158, 427, 160, 159, 427,
    158, 159, 427, 172, 158, 427,
    172, 159, 427, 172, 160, 427,
    172, 148, 427, 172, 173, 427,
    172, 166, 427, 158, 163, 427,
    159, 163, 427, 160, 163, 427,
    166, 163, 427, 172, 163, 427,
    170, 149, 186, 159, 164, 137,
    160, 164, 137, 158, 164, 137,
    148, 164, 137, 156, 164, 137,
    157, 164, 137, 172, 164, 137,
    157, -1, 137, 156, -1, 137,
    161, -1, 137, 172, -1, 137,
    168, 139, 130, 138, 166, 139,
    138, 165, 139, 138, 169, 139,
    138, 168, 139, 140, 168, 139,
    142, 168, 139, 149, 168, 139,
    173, 170, 217, 147, -1, 187,
    168, 167, 187, 168, 175, 187,
    128, 142, 187, 167, 142, 187,
    171, 142, 187, 175, 142, 187,
    169, 175, 187, 185, 213, 187,
    199, 213, 187, 415, 413, 398,
    399, 426, 398, 415, 132, 400,
    415, 128, 410, 415, 417, 412,
    415, 398, 413, 433, 419, 416,
    415, 419, 416, 399, 421, 416,
    403, 415, 402, 415, 420, 418,
    412, 415, 417, 418, 415, 420,
    419, 405, 419, 433, 170, 422,
    433, 439, 422, 172, 128, 424,
    445, 176, 425, 398, 449, 426,
    398, 450, 426, 398, 453, 426,
    411, 405, 428, 411, 164, 428,
    411, 162, 428, 411, 163, 428,
    411, 414, 428, 414, 164, 428,
    414, 162, 428, 414, 163, 428,
    166, 404, 429, 166, 406, 429,
    418, 170, 430, 418, 414, 430,
    164, 410, 431, 164, 129, 431,
    433, 401, 432, 433, 181, 432,
    433, 199, 432, 433, 447, 432,
    408, 427, 433, 408, 195, 433,
    408, 442, 433, 408, 166, 433,
    408, 454, 433, 408, 137, 433,
    411, 166, 435, 170, 411, 437,
    131, 182, 438, 131, 444, 438,
    131, 184, 438, 171, 406, 440,
    171, 138, 440, 171, 140, 440,
    171, 149, 440, 414, 170, 441,
    404, 416, 442, 404, 419, 442,
    166, 416, 442, 166, 419, 442,
    170, 142, 443, 419, -1, 444,
    149, 139, 444, 138, 128, 444,
    138, 140, 444, 138, 139, 444,
    138, 405, 444, 140, 141, 444,
    140, 139, 444, 140, 166, 444,
    140, 404, 444, 404, 410, 445,
    399, 138, 446, 399, 140, 446,
    399, 142, 446, 399, 149, 446,
    408, 401, 447, 408, 199, 447,
    408, 181, 447, 170, 405, 448,
    170, 163, 448, 170, 171, 448,
    147, 404, 449, 184, 429, 449,
    142, 401, 449, 138, 406, 450,
    140, 128, 450, 140, 405, 450,
    140, 406, 450, 140, 411, 450,
    140, 414, 450, 142, 411, 450,
    142, 414, 450, 149, 128, 450,
    149, 405, 450, 149, 406, 450,
    401, 141, 450, 401, 138, 450,
    401, 140, 450, 401, 149, 450,
    401, 171, 450, 401, 172, 450,
    401, 429, 450, 429, 182, 450,
    429, 181, 450, 429, 199, 450,
    447, 172, 450, 438, 428, 450,
    200, 424, 451, 410, 163, 452,
    410, 162, 452, 147, -1, 453,
    142, 401, 453, 142, 128, 453,
    142, 405, 453, 142, 406, 453,
    142, 432, 453, 142, 444, 453,
    142, 447, 453, 404, -1, 454,
    163, 162, 454, 416, 425, 421,
    132, 130, 421, 410, 415, 128,
    129, 415, 128, 405, 415, 164,
    138, 415, 164, 142, 415, 162,
    140, 415, 163, 141, 415, 138,
    141, 417, 138, 141, 408, 138,
    141, 414, 138, 402, 415, 138,
    130, 415, 131, 137, 415, 143,
    163, 415, 140, 149, 415, 140,
    139, 415, 140, 143, 415, 137,
    400, 415, 132, 131, 415, 130,
    399, 139, 130, 416, 415, 142,
    162, 415, 142, 399, 424, 172,
    413, 149, 141, 413, 138, 141,
    413, 140, 141, 413, 142, 141,
    399, 451, 200, 408, 170, 205,
    404, 138, 149, 404, 140, 149,
    404, 142, 149, 404, 149, 149,
    419, 162, 197, 169, 401, 189,
    404, 401, 189, 404, 167, 189,
    401, 165, 189, 401, 172, 189,
    401, 138, 189, 401, 139, 189,
    401, 140, 189, 401, 149, 189,
    401, 159, 189, 401, 160, 189,
    401, 158, 189, 166, 401, 181,
    404, 401, 181, 404, 167, 181,
    401, -1, 199, 168, 401, 187,
    399, 401, 187, 399, 167, 187,
    401, 142, 187, 399, 169, 128,
    399, 404, 128, 168, 404, 128,
    399, 139, 130, 138, 399, 139,
    140, 399, 139, 142, 399, 139,
    149, 399, 139, 399, 175, 187,
    404, 165, 189, 171, 404, 216,
    147, 404, 190, 404, -1, 154,
    404, 139, 154, 404, 174, 154,
    191, 404, 188, 159, 404, 143,
    160, 404, 143, 158, 404, 143,
    173, 404, 191, 404, 170, 436,
    138, 404, 139, 404, 175, 187,
    1886417008, 1886417008, 1886417008, 1886417008, 1886417008, 1886417008
};

EvtScript TTYD64_mac_02_Script_Get1ItemRecipe = {
    UseBuf((Bytecode) TTYD64_mac_02_SpecialCookingResultHandlers)
    Loop(0)
        BufRead1(LVarD)
        IfEq(LVarD, -1)
            BreakLoop
        EndIf
        BufRead1(LVar7)
        IfEq(LVarD, LVar8)
            ExecWait(LVar7)
            ExecWait(TTYD64_mac_02_Script_GetReaction)
            Return
        EndIf
    EndLoop
    UseBuf((Bytecode) TTYD64_mac_02_IntTable_RecipeTable)
    Loop(0)
        BufRead1(LVarD)
        IfEq(LVarD, 0x70707070)
            Set(LVar6, 194)
            Set(LVar7, 0)
            Return
        EndIf
        IfEq(LVarD, -1)
            Set(LVar6, 194)
            Set(LVar7, 0)
            Return
        EndIf
        BufRead1(LVar7)
        BufRead1(LVar6)
        IfEq(LVarD, LVar8)
            IfEq(LVar7, -1)
                ExecWait(TTYD64_mac_02_Script_GetReaction)
                Return
            EndIf
        EndIf
    EndLoop
    Return
    End
};

s32 TTYD64_mac_02_RecipesDiscovedIDs[] = {
    176, 177, 178, 179, 180, 181,
    182, 183, 184, 185, 186, 189,
    187, 190, 191, 188, 192, 439,
    194, 195, 196, 197, 198, 199,
    200, 201, 202, 203, 204, 205,
    206, 423, 208, 434, 436, 211,
    212, 213, 214, 215, 216, 217,
    218, 137, 154, 427, 151, 149,
    139, 143, 130, 128, 400, 402,
    410, 412, 413, 416, 418, 398,
    417, 420, 419, 422, 424, 425,
    426, 428, 429, 430, 431, 432,
    433, 435, 437, 438, 440, 441,
    442, 443, 444, 445, 446, 447,
    421, 448, 449, 450, 451, 452,
    453, 454, 0
};

s32 TTYD64_mac_02_RecipesDiscovedFlags[] = {
    -129994066, -129994065, -129994064, -129994063, -129994062, -129994061,
    -129994060, -129994059, -129994058, -129994057, -129994056, -129994055,
    -129994054, -129994053, -129994052, -129994051, -129994050, -129994049,
    -129994047, -129994046, -129994045, -129994044, -129994043, -129994042,
    -129994041, -129994040, -129994039, -129994038, -129994037, -129994036,
    -129994035, -129994034, -129994033, -129994032, -129994031, -129994030,
    -129994029, -129994028, -129994027, -129994026, -129994025, -129994024,
    -129994023, -129994022, -129994021, -129994019, -129994018, -129994017,
    -129994016, -129994015, -129994014, -129994013, -129994012, -129994011,
    -129994010, -129994009, -129994008, -129994007, -129994006, -129994005,
    -129994004, -129994003, -129994002, -129994001, -129994000, -129993999,
    -129993998, -129993997, -129993996, -129993995, -129993994, -129993993,
    -129993992, -129993991, -129993990, -129993989, -129993988, -129993987,
    -129993986, -129993985, -129993984, -129993983, -129993982, -129993981,
    -129993980, -129993979, -129993978, -129993977, -129993976, -129993975,
    0
};

EvtScript TTYD64_mac_02_Script_MakeEntities = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 5)
        IfEq(GameFlag(131), 0)
            Call(MakeEntity, Ref(Entity_Padlock), -470, 30, -155, 180, 0x80000000)
            Set(MapVar(0), LVar0)
            BindPadlock(mac_02_EVS_ChooseItem_OddKey, 256, 16384, (Bytecode) mac_02_ItemList_OddKey, 0, 1)
        EndIf
    EndIf
    Call(MakeItemEntity, 107, -412, 20, -320, 17, GameFlag(132))
    Call(MakeEntity, Ref(Entity_HiddenPanel), 400, 0, 100, 0, 20, 0x80000000)
    Call(AssignPanelFlag, GameFlag(297))
    Call(MakeEntity, Ref(Entity_Signpost), -375, 0, 190, 0, 0x80000000)
    Call(AssignScript, Ref(mac_02_EVS_ReadSign))
    BindTrigger(mac_02_EVS_OnInspect_StreetSign, 256, 12, 1, 0)
    Exec(TTYD64_mac_02_Script_InitNewStuff)
    Return
    End
};

EvtScript TTYD64_mac_02_Script_Get2ItemRecipe = {
    UseBuf((Bytecode) TTYD64_mac_02_IntTable_RecipeTable)
    Loop(0)
        BufRead1(LVarD)
        IfEq(LVarD, 0x70707070)
            Set(LVar6, 194)
            Set(LVar7, 0)
            Return
        EndIf
        IfEq(LVarD, -1)
            Set(LVar6, 194)
            Set(LVar7, 0)
            Return
        EndIf
        BufRead1(LVarE)
        BufRead1(LVar6)
        IfEq(LVarD, LVar8)
            IfEq(LVarE, LVar9)
                ExecWait(TTYD64_mac_02_Script_GetReaction)
                Return
            EndIf
        EndIf
        IfEq(LVarD, LVar9)
            IfEq(LVarE, LVar8)
                ExecWait(TTYD64_mac_02_Script_GetReaction)
                Return
            EndIf
        EndIf
    EndLoop
    Return
    End
};

EvtScript TTYD64_mac_02_Script_GetReaction = {
    UseBuf((Bytecode) TTYD64_mac_02_IntTable_ItemReactions)
    Loop(0)
        BufRead1(LVar7)
        BufRead1(LVarD)
        IfEq(LVarD, LVar6)
            Return
        EndIf
        IfEq(LVarD, -1)
            Set(LVar7, 1)
            Return
        EndIf
    EndLoop
    Return
    End
};

s32 TTYD64_mac_02_IntTable_ItemReactions[] = {
    0, 194, 2, 189, 2, 440,
    2, 192, 2, 217, 2, 436,
    2, 191, 2, 187, 3, 190,
    3, 188, 4, 154, 4, 143,
    4, 130, 4, 128, 4, 151,
    -1, -1
};

u8 TTYD64_mac_02_AllRecipes[] = {
    0xFC, 0x01, 0x37, 0x4F, 0x57, 0x01, 0xF7, 0x29, 0x54, 0xF7, 0x4C, 0x4F,
    0x4F, 0x4B, 0x53, 0xF7, 0x4C, 0x49, 0x4B, 0x45, 0xF7, 0x29, 0x07, 0x56,
    0x45, 0xF7, 0x4D, 0x41, 0x44, 0x45, 0xF0, 0x45, 0x56, 0x45, 0x52, 0x59,
    0x54, 0x48, 0x49, 0x4E, 0x47, 0xF7, 0x49, 0x4E, 0xF7, 0x54, 0x48, 0x49,
    0x53, 0xF7, 0x43, 0x4F, 0x4F, 0x4B, 0x42, 0x4F, 0x4F, 0x4B, 0x01, 0xF0,
    0x29, 0xF7, 0x43, 0x4F, 0x55, 0x4C, 0x44, 0x4E, 0x07, 0x54, 0xF7, 0x48,
    0x41, 0x56, 0x45, 0xF7, 0x44, 0x4F, 0x4E, 0x45, 0xF7, 0x49, 0x54, 0xF7,
    0x57, 0x49, 0x54, 0x48, 0x4F, 0x55, 0x54, 0xF0, 0x59, 0x4F, 0x55, 0x0C,
    0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0E, 0xF7, 0x90, 0xF0, 0xF1, 0xFB,
    0xFD
};

EvtScript TTYD64_mac_02_Script_InitNewStuff = {
    Call(MakeEntity, Ref(Entity_WoodenCrate), 496, 0, -159, 0, 348, 0x80000000)
    Call(AssignCrateFlag, GameFlag(4467))
    Return
    End
};

Bytecode TTYD64_mac_02_SpecialCookingResultHandlers[] = {
    150, Ref(TTYD64_mac_02_Script_HandleMysteryCooked), -1, -1
};
// clang-format on

void TTYD64_InstallMap_mac_02(void) {
    memcpy(&MysteryResultOptions, &TTYD64_mac_02_IntTable_8024909C, sizeof(TTYD64_mac_02_IntTable_8024909C));
    Mod_ReplaceScript("TTYD64", &mac_02_EVS_TayceT_FryingPanAndCake, &TTYD64_mac_02_Script_8024926C);
    Mod_ReplaceScript("TTYD64", &mac_02_EVS_TayceT_RequestCookbook, &TTYD64_mac_02_Script_80249550);
    Mod_ReplaceScript("TTYD64", &mac_02_EVS_TayceT_Cook, &TTYD64_mac_02_Script_80249684);
    Mod_ReplaceScript("TTYD64", &mac_02_EVS_MakeEntities, &TTYD64_mac_02_Script_MakeEntities);
    Mod_RegisterWideEvtBuffer("TTYD64", TTYD64_mac_02_SpecialCookingResultHandlers, 4);
    TTYD64_maps_BindInlineMessage(TTYD64_mac_02_Script_80249684, TTYD64_mac_02_AllRecipes);
}
