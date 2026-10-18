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

extern NpcGroupList nok_01_CrisisNPCs;
extern EvtScript nok_01_EVS_EnterMap;
extern EvtScript nok_01_EVS_Main;
extern EvtScript nok_01_EVS_MakeEntities;
extern EvtScript nok_01_EVS_MakeRooms;
extern EvtScript nok_01_EVS_NpcInit_Bobomb_01_Normal;
extern EvtScript nok_01_EVS_NpcInit_Bobomb_02_Normal;
extern EvtScript nok_01_EVS_NpcInit_Bobomb_03_Normal;
extern EvtScript nok_01_EVS_SetupFoliage;
extern EvtScript nok_01_EVS_SetupMusic;
extern EvtScript nok_01_EVS_SetupRadio;
extern EvtScript nok_01_EVS_SetupShop;
extern EvtScript nok_01_EVS_TexPan_Flowers;
extern ShopItemData nok_01_Inventory[];
extern NpcGroupList nok_01_NormalNPCs;

API_CALLABLE(AddStarPieces);
API_CALLABLE(BindNpcInteract);
API_CALLABLE(BringPartnerOut);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(ClearDefeatedEnemies);
API_CALLABLE(CloseMessage);
API_CALLABLE(ContinueSpeech);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetNpcVar);
API_CALLABLE(GetSelfNpcID);
API_CALLABLE(GetSelfVar);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(NpcFaceNpc);
API_CALLABLE(NpcFacePlayer);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtNpc);
API_CALLABLE(PlayerFaceNpc);
API_CALLABLE(PutPartnerAway);
API_CALLABLE(RemoveNpc);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcVar);
API_CALLABLE(SetSelfVar);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(ShowChoice);
API_CALLABLE(ShowGotItem);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(nok_01_SpawnExplosionEffect);

extern EvtScript TTYD64_nok_01_Script_Bombs_Minigame_Init;
extern EvtScript TTYD64_nok_01_Script_DoBombExplotion;
extern EvtScript TTYD64_nok_01_Script_RestoreMusicTrack;
extern u8 TTYD64_nok_01_String_BobOmb_1[];
extern EvtScript TTYD64_nok_01_Script_Init_8024D164;
extern EvtScript TTYD64_nok_01_Script_Init_8024D188;
extern u8 TTYD64_nok_01_String_BobOmb_2[];
extern ShopItemData TTYD64_nok_01_ShopInventory_8024FB6C[];
extern EvtScript TTYD64_nok_01_Script_Interact_8024C868_NEW;
extern EvtScript TTYD64_nok_01_Script_Bombs_Minigame;
extern EvtScript TTYD64_nok_01_Script_Interact_8024CD08_NEW;
extern EvtScript TTYD64_nok_01_Script_BombGame_PickBomb;
extern EvtScript TTYD64_nok_01_Script_Interact_8024C694_NEW;
extern EvtScript TTYD64_nok_01_Script_Main;
extern u8 TTYD64_nok_01_String_BobOmb_6[];
extern EvtScript TTYD64_nok_01_Script_Init_8024D1AC;
extern u8 TTYD64_nok_01_String_BobOmb_4[];
extern EvtScript TTYD64_nok_01_Script_ShopItem;
extern u8 TTYD64_nok_01_String_BobOmb_5[];
extern u8 TTYD64_nok_01_String_BobOmb_Ask[];
extern s32 TTYD64_nok_01_Data_BombMinigame_Level3_Order[];
extern u8 TTYD64_nok_01_String_BobOmb_3[];
extern s32 TTYD64_nok_01_Data_BombMinigame_Level2_Order[];
extern s32 TTYD64_nok_01_Data_BombMinigame_Level1_Order[];
extern u8 TTYD64_nok_01_String_BobOmb_Cancel[];

// clang-format off
EvtScript TTYD64_nok_01_Script_Bombs_Minigame_Init = {
    Call(SpeakToPlayer, 14, 0x910104, 0x910101, 0, (Bytecode) TTYD64_nok_01_String_BobOmb_1)
    Call(ShowChoice, 0x1E001D)
    IfNe(LVar0, 0)
        Call(ContinueSpeech, 14, 0x910104, 0x910101, 0, (Bytecode) TTYD64_nok_01_String_BobOmb_Cancel)
        Call(SetSelfVar, 0, 0)
        Return
    Else
        Call(ContinueSpeech, 14, 0x910104, 0x910101, 0, (Bytecode) TTYD64_nok_01_String_BobOmb_2)
        ExecWait(TTYD64_nok_01_Script_Bombs_Minigame)
    EndIf
    Return
    End
};

EvtScript TTYD64_nok_01_Script_DoBombExplotion = {
    Call(SetNpcAnimation, LVar0, 0x910103)
    Wait(LVar1)
    Call(SetNpcAnimation, LVar0, 0x910101)
    Wait(3)
    Call(GetNpcPos, LVar0, LVar2, LVar3, LVar4)
    Call(PlaySoundAtNpc, LVar0, 8214, 0)
    Call(nok_01_SpawnExplosionEffect, LVar2, LVar3, LVar4)
    Return
    End
};

EvtScript TTYD64_nok_01_Script_RestoreMusicTrack = {
    IfLt(GameByte(0), -92)
        Call(SetMusic, 0, 18, 0, 8)
    Else
        Call(SetMusic, 0, 19, 0, 8)
    EndIf
    Call(ClearAmbientSounds, 250)
    Return
    End
};

u8 TTYD64_nok_01_String_BobOmb_1[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0xF7,
    0x44, 0x4F, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x57, 0x41, 0x4E, 0x54, 0xF7,
    0x54, 0x4F, 0xF7, 0x50, 0x4C, 0x41, 0x59, 0xF0, 0x41, 0xF7, 0x47, 0x41,
    0x4D, 0x45, 0xF7, 0x57, 0x49, 0x54, 0x48, 0xF7, 0x55, 0x53, 0x1F, 0xF0,
    0xFF, 0x04, 0xFD
};

EvtScript TTYD64_nok_01_Script_Init_8024D164 = {
    Call(BindNpcInteract, -1, Ref(TTYD64_nok_01_Script_Interact_8024C694_NEW))
    Return
    End
};

EvtScript TTYD64_nok_01_Script_Init_8024D188 = {
    Call(BindNpcInteract, -1, Ref(TTYD64_nok_01_Script_Interact_8024C868_NEW))
    Return
    End
};

u8 TTYD64_nok_01_String_BobOmb_2[] = {
    0xFB, 0x21, 0x57, 0x45, 0x53, 0x4F, 0x4D, 0x45, 0x01, 0xF0, 0xF1, 0xFB,
    0x34, 0x52, 0x59, 0xF7, 0x54, 0x4F, 0xF7, 0x52, 0x45, 0x4D, 0x45, 0x4D,
    0x42, 0x45, 0x52, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x4F, 0x52, 0x44, 0x45,
    0x52, 0xF7, 0x4F, 0x46, 0xF0, 0x45, 0x41, 0x43, 0x48, 0xF7, 0x45, 0x58,
    0x50, 0x4C, 0x4F, 0x53, 0x49, 0x4F, 0x4E, 0x0E, 0xF1, 0xFD
};

ShopItemData TTYD64_nok_01_ShopInventory_8024FB6C[] = {
    { .itemID = 398, .price = 5, .descMsg = 0x230133 },
    { .itemID = 144, .price = 4, .descMsg = 0x240027 },
    { .itemID = 128, .price = 8, .descMsg = 0x240000 },
    { .itemID = 405, .price = 15, .descMsg = 0x23013A },
    { .itemID = 413, .price = 8, .descMsg = 0x230141 },
    { .itemID = 419, .price = 15, .descMsg = 0x230147 },
    { .itemID = 0, .price = 0, .descMsg = 0x000000 },
};

EvtScript TTYD64_nok_01_Script_Interact_8024C868_NEW = {
    IfGt(GameByte(0), -75)
        Call(GetNpcVar, 14, 0, LVar0)
        IfEq(LVar0, 1)
            ExecWait(TTYD64_nok_01_Script_BombGame_PickBomb)
            Return
        EndIf
    EndIf
    Switch(GameByte(0))
    CaseLt(-75)
        IfEq(AreaFlag(12), 0)
            Set(AreaFlag(12), 1)
            Set(LVar0, 0xC0046)
        Else
            Set(AreaFlag(12), 0)
            Set(LVar0, 0xC0047)
        EndIf
        Call(SpeakToPlayer, -1, 0x910104, 0x910101, 0, LVar0)
    CaseLt(7)
        IfEq(AreaFlag(12), 0)
            Set(AreaFlag(12), 1)
            Call(NpcFacePlayer, -1, 0)
            Call(BringPartnerOut, 3)
            Call(NpcFaceNpc, -4, -1, 0)
            Call(SpeakToPlayer, -1, 0x910104, 0x910101, 0, 0xC0048)
            Call(DisablePartnerAI, 0)
            Call(SpeakToPlayer, -4, 0x3000E, 0x30003, 0, 0xC0049)
            Call(EnablePartnerAI)
            Call(SpeakToPlayer, -1, 0x910104, 0x910101, 0, 0xC004A)
            Call(SetNpcAnimation, -1, 0x910103)
            Wait(10)
            Call(SetNpcAnimation, -1, 0x910101)
            Wait(3)
            Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
            Call(PlaySoundAtNpc, -1, 8214, 0)
            Call(nok_01_SpawnExplosionEffect, LVar0, LVar1, LVar2)
            Wait(30)
            Call(PutPartnerAway)
        Else
            Call(NpcFacePlayer, -1, 0)
            Call(SpeakToPlayer, -1, 0x910104, 0x910101, 0, 0xC004B)
            Call(SetNpcAnimation, -1, 0x910103)
            Wait(10)
            Call(SetNpcAnimation, -1, 0x910101)
            Wait(3)
            Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
            Call(PlaySoundAtNpc, -1, 8214, 0)
            Call(nok_01_SpawnExplosionEffect, LVar0, LVar1, LVar2)
        EndIf
    CaseLt(89)
        Call(NpcFacePlayer, -1, 0)
        Call(SpeakToPlayer, -1, 0x910104, 0x910101, 0, 0xC004C)
        Call(SetNpcAnimation, -1, 0x910103)
        Wait(10)
        Call(SetNpcAnimation, -1, 0x910101)
        Wait(3)
        Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
        Call(PlaySoundAtNpc, -1, 8214, 0)
        Call(nok_01_SpawnExplosionEffect, LVar0, LVar1, LVar2)
    CaseGe(89)
        Call(NpcFacePlayer, -1, 0)
        Call(SpeakToPlayer, -1, 0x910104, 0x910101, 0, 0xC004D)
        Call(SetNpcAnimation, -1, 0x910103)
        Wait(10)
        Call(SetNpcAnimation, -1, 0x910101)
        Wait(3)
        Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
        Call(PlaySoundAtNpc, -1, 8214, 0)
        Call(nok_01_SpawnExplosionEffect, LVar0, LVar1, LVar2)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_nok_01_Script_Bombs_Minigame = {
    Switch(GameByte(102))
    CaseEq(0)
        Set(LVar0, 13)
        Set(LVar1, 10)
        Exec(TTYD64_nok_01_Script_DoBombExplotion)
        Wait(20)
        Set(LVar0, 14)
        Set(LVar1, 10)
        Exec(TTYD64_nok_01_Script_DoBombExplotion)
        Wait(20)
        Set(LVar0, 13)
        Set(LVar1, 10)
        Exec(TTYD64_nok_01_Script_DoBombExplotion)
        Wait(20)
        Set(LVar0, 12)
        Set(LVar1, 10)
        Exec(TTYD64_nok_01_Script_DoBombExplotion)
        Wait(20)
        Set(MapVar(0), (Bytecode) TTYD64_nok_01_Data_BombMinigame_Level1_Order)
    CaseEq(1)
        Set(LVar0, 14)
        Set(LVar1, 15)
        Exec(TTYD64_nok_01_Script_DoBombExplotion)
        Wait(15)
        Set(LVar0, 12)
        Set(LVar1, 15)
        Exec(TTYD64_nok_01_Script_DoBombExplotion)
        Wait(15)
        Set(LVar0, 14)
        Set(LVar1, 15)
        Exec(TTYD64_nok_01_Script_DoBombExplotion)
        Wait(15)
        Set(LVar0, 13)
        Set(LVar1, 15)
        Exec(TTYD64_nok_01_Script_DoBombExplotion)
        Wait(15)
        Set(LVar0, 13)
        Set(LVar1, 15)
        Exec(TTYD64_nok_01_Script_DoBombExplotion)
        Wait(15)
        Set(MapVar(0), (Bytecode) TTYD64_nok_01_Data_BombMinigame_Level2_Order)
    CaseGe(2)
        Set(LVar0, 13)
        Set(LVar1, 10)
        Exec(TTYD64_nok_01_Script_DoBombExplotion)
        Wait(10)
        Set(LVar0, 13)
        Set(LVar1, 10)
        Exec(TTYD64_nok_01_Script_DoBombExplotion)
        Wait(10)
        Set(LVar0, 14)
        Set(LVar1, 10)
        Exec(TTYD64_nok_01_Script_DoBombExplotion)
        Wait(10)
        Set(LVar0, 13)
        Set(LVar1, 10)
        Exec(TTYD64_nok_01_Script_DoBombExplotion)
        Wait(10)
        Set(LVar0, 12)
        Set(LVar1, 10)
        Exec(TTYD64_nok_01_Script_DoBombExplotion)
        Wait(10)
        Set(LVar0, 14)
        Set(LVar1, 10)
        Exec(TTYD64_nok_01_Script_DoBombExplotion)
        Wait(10)
        Set(MapVar(0), (Bytecode) TTYD64_nok_01_Data_BombMinigame_Level3_Order)
    EndSwitch
    Call(SetNpcAnimation, 13, 0x910101)
    Call(SetNpcAnimation, 12, 0x910101)
    Call(SetNpcAnimation, 14, 0x910101)
    Call(SpeakToPlayer, 14, 0x910104, 0x910101, 0, (Bytecode) TTYD64_nok_01_String_BobOmb_3)
    Set(MapVar(1), 0)
    Set(MapVar(2), 0)
    Call(SetSelfVar, 0, 1)
    Return
    End
};

EvtScript TTYD64_nok_01_Script_Interact_8024CD08_NEW = {
    IfEq(GameFlag(4719), 0)
        Call(GetSelfVar, 0, LVar0)
        IfEq(LVar0, 0)
            ExecWait(TTYD64_nok_01_Script_Bombs_Minigame_Init)
        Else
            ExecWait(TTYD64_nok_01_Script_BombGame_PickBomb)
        EndIf
        Return
    EndIf
    Switch(GameByte(0))
    CaseLt(7)
        IfEq(AreaFlag(14), 0)
            Set(AreaFlag(14), 1)
            Call(NpcFacePlayer, -1, 0)
            Call(NpcFacePlayer, 12, 0)
            Call(NpcFacePlayer, 13, 0)
            Call(SpeakToPlayer, -1, 0x910104, 0x910101, 0, 0xC004E)
            Call(PlayerFaceNpc, 12, 0)
            Call(SpeakToPlayer, 12, 0x910104, 0x910101, 0, 0xC004F)
            Call(PlayerFaceNpc, 13, 0)
            Call(SpeakToPlayer, 13, 0x910104, 0x910101, 0, 0xC0050)
            Thread
                Call(SetNpcAnimation, 13, 0x910103)
                Wait(10)
                Call(SetNpcAnimation, 13, 0x910101)
                Wait(3)
                Call(GetNpcPos, 13, LVar0, LVar1, LVar2)
                Call(PlaySoundAtNpc, 13, 8214, 0)
                Call(nok_01_SpawnExplosionEffect, LVar0, LVar1, LVar2)
            EndThread
            Wait(20)
            Thread
                Call(PlayerFaceNpc, 12, 0)
                Call(SetNpcAnimation, 12, 0x910103)
                Wait(10)
                Call(SetNpcAnimation, 12, 0x910101)
                Wait(3)
                Call(GetNpcPos, 12, LVar0, LVar1, LVar2)
                Call(PlaySoundAtNpc, 12, 8214, 0)
                Call(nok_01_SpawnExplosionEffect, LVar0, LVar1, LVar2)
            EndThread
            Wait(20)
            Thread
                Call(PlayerFaceNpc, -1, 0)
                Call(SetNpcAnimation, -1, 0x910103)
                Wait(10)
                Call(SetNpcAnimation, -1, 0x910101)
                Wait(3)
                Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
                Call(PlaySoundAtNpc, -1, 8214, 0)
                Call(nok_01_SpawnExplosionEffect, LVar0, LVar1, LVar2)
            EndThread
        Else
            Call(SpeakToPlayer, -1, 0x910104, 0x910101, 0, 0xC0051)
        EndIf
    CaseLt(89)
        Call(SpeakToPlayer, -1, 0x910104, 0x910101, 0, 0xC0052)
    CaseGe(89)
        Call(SpeakToPlayer, -1, 0x910104, 0x910101, 0, 0xC0053)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_nok_01_Script_BombGame_PickBomb = {
    Switch(GameByte(102))
    CaseEq(0)
        UseBuf((Bytecode) TTYD64_nok_01_Data_BombMinigame_Level1_Order)
    CaseEq(1)
        UseBuf((Bytecode) TTYD64_nok_01_Data_BombMinigame_Level2_Order)
    CaseGe(2)
        UseBuf((Bytecode) TTYD64_nok_01_Data_BombMinigame_Level3_Order)
    EndSwitch
    BufPeek(LVar0, MapVar(1))
    Call(GetSelfNpcID, LVar1)
    IfEq(LVar0, LVar1)
        Call(PlaySound, 540)
        Set(LVar0, MapVar(1))
        Add(LVar0, 1)
        BufPeek(LVar1, LVar0)
        IfEq(LVar1, -1)
            Add(GameByte(102), 1)
            Set(MapVar(1), 0)
            Switch(GameByte(102))
            CaseOrEq(0)
            CaseOrEq(1)
            CaseOrEq(2)
                Call(SpeakToPlayer, 14, 0x910104, 0x910101, 0, (Bytecode) TTYD64_nok_01_String_BobOmb_5)
                ExecWait(TTYD64_nok_01_Script_Bombs_Minigame)
                EndCaseGroup
            CaseGe(3)
                Call(SetMusic, 0, 78, 0, 8)
                Call(SpeakToPlayer, 14, 0x910104, 0x910101, 0, (Bytecode) TTYD64_nok_01_String_BobOmb_6)
                Exec(TTYD64_nok_01_Script_RestoreMusicTrack)
                Set(LVar0, 348)
                Call(ShowGotItem, LVar0, 1, 0)
                Call(AddStarPieces, 1)
                Set(GameFlag(4719), 1)
            EndSwitch
        Else
            Add(MapVar(1), 1)
        EndIf
    Else
        Call(PlaySound, 541)
        Call(SpeakToPlayer, 14, 0x910104, 0x910101, 0, (Bytecode) TTYD64_nok_01_String_BobOmb_4)
        Call(SpeakToPlayer, 14, 0x910104, 0x910101, 0, (Bytecode) TTYD64_nok_01_String_BobOmb_Ask)
        Call(ShowChoice, 0x1E001D)
        IfNe(LVar0, 0)
            Call(ContinueSpeech, 14, 0x910104, 0x910101, 0, (Bytecode) TTYD64_nok_01_String_BobOmb_Cancel)
            Call(SetNpcVar, 14, 0, 0)
            Return
        Else
            Call(CloseMessage)
            ExecWait(TTYD64_nok_01_Script_Bombs_Minigame)
        EndIf
    EndIf
    Return
    End
};

EvtScript TTYD64_nok_01_Script_Interact_8024C694_NEW = {
    IfGt(GameByte(0), -75)
        Call(GetNpcVar, 14, 0, LVar0)
        IfEq(LVar0, 1)
            ExecWait(TTYD64_nok_01_Script_BombGame_PickBomb)
            Return
        EndIf
    EndIf
    Switch(GameByte(0))
    CaseLt(-75)
        IfEq(AreaFlag(11), 0)
            Set(AreaFlag(11), 1)
            Set(LVar0, 0xC003F)
        Else
            Set(AreaFlag(11), 0)
            Set(LVar0, 0xC0040)
        EndIf
        Call(SpeakToPlayer, -1, 0x910104, 0x910101, 0, LVar0)
    CaseLt(7)
        Call(SpeakToPlayer, -1, 0x910104, 0x910101, 0, 0xC0041)
    CaseLt(89)
        Call(SpeakToPlayer, -1, 0x910104, 0x910101, 0, 0xC0042)
    CaseGe(89)
        Call(NpcFacePlayer, -1, 0)
        Call(SpeakToPlayer, -1, 0x910104, 0x910101, 0, 0xC0043)
        Call(SetNpcAnimation, -1, 0x910103)
        Wait(10)
        Call(SetNpcAnimation, -1, 0x910101)
        Wait(3)
        Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
        Call(PlaySoundAtNpc, -1, 8214, 0)
        Call(nok_01_SpawnExplosionEffect, LVar0, LVar1, LVar2)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_nok_01_Script_Main = {
    Set(GameByte(425), 33)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Set(GameFlag(1969), 1)
    Set(AreaFlag(9), 0)
    Set(AreaFlag(10), 0)
    Set(AreaFlag(12), 0)
    Set(AreaFlag(14), 0)
    Set(GameFlag(590), 0)
    IfGe(GameByte(0), -92)
        Set(GameFlag(566), 1)
        Set(GameFlag(567), 1)
        Set(GameFlag(568), 1)
    EndIf
    IfLt(GameByte(0), -92)
        Call(MakeNpcs, 0, Ref(nok_01_CrisisNPCs))
    Else
        Call(MakeNpcs, 0, Ref(nok_01_NormalNPCs))
    EndIf
    Call(ClearDefeatedEnemies)
    Exec(nok_01_EVS_SetupShop)
    Exec(nok_01_EVS_SetupRadio)
    Exec(nok_01_EVS_TexPan_Flowers)
    ExecWait(nok_01_EVS_MakeEntities)
    Exec(nok_01_EVS_MakeRooms)
    Wait(1)
    ExecWait(nok_01_EVS_SetupFoliage)
    Exec(nok_01_EVS_SetupMusic)
    Set(AreaByte(0), 0)
    Exec(nok_01_EVS_EnterMap)
    Exec(TTYD64_nok_01_Script_ShopItem)
    Return
    End
};

u8 TTYD64_nok_01_String_BobOmb_6[] = {
    0xFC, 0x01, 0xFF, 0x07, 0xFF, 0x2E, 0xFF, 0xFF, 0x26, 0x01, 0xFF, 0x0D,
    0x20, 0x20, 0x26, 0x29, 0x2E, 0x29, 0x33, 0x28, 0x01, 0x01, 0x01, 0xFF,
    0x27, 0x01, 0xFF, 0x0E, 0xF0, 0xF0, 0xF0, 0xF2, 0x14, 0xFB, 0xFF, 0x08,
    0xFF, 0x2E, 0xBF, 0x37, 0x4F, 0x57, 0x0C, 0xF7, 0x2D, 0x41, 0x52, 0x49,
    0x4F, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x41, 0x43, 0x54, 0x55, 0x41, 0x4C,
    0x4C, 0x59, 0xF7, 0x44, 0x49, 0x44, 0xF7, 0x49, 0x54, 0x01, 0xF0, 0xF1,
    0xFB, 0x37, 0x45, 0x4C, 0x4C, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x41, 0x52,
    0x45, 0x4E, 0x07, 0x54, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x4F, 0x4E, 0x45,
    0xF7, 0x41, 0x4E, 0x44, 0xF7, 0x4F, 0x4E, 0x4C, 0x59, 0xF0, 0x2D, 0x41,
    0x52, 0x49, 0x4F, 0xF7, 0x4A, 0x55, 0x53, 0x54, 0xF7, 0x46, 0x4F, 0x52,
    0xF7, 0x4E, 0x4F, 0x54, 0x48, 0x49, 0x4E, 0x47, 0x0C, 0xF7, 0x54, 0x48,
    0x49, 0x53, 0xF7, 0x57, 0x41, 0x53, 0xF0, 0x46, 0x55, 0x4E, 0x0C, 0xF7,
    0x54, 0x41, 0x4B, 0x45, 0xF7, 0x54, 0x48, 0x49, 0x53, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_nok_01_Script_Init_8024D1AC = {
    Call(BindNpcInteract, -1, Ref(TTYD64_nok_01_Script_Interact_8024CD08_NEW))
    IfLt(GameByte(0), -75)
        Call(RemoveNpc, -1)
    EndIf
    IfEq(GameFlag(4719), 0)
        Call(SetNpcAnimation, -1, 0x910103)
    EndIf
    Return
    End
};

u8 TTYD64_nok_01_String_BobOmb_4[] = {
    0xFC, 0x01, 0xFF, 0x2E, 0xFF, 0xFF, 0x26, 0x01, 0xFF, 0x0D, 0x20, 0x20,
    0x37, 0x32, 0x2F, 0x2E, 0x27, 0x01, 0xFF, 0x27, 0x01, 0xFF, 0x0E, 0xF0,
    0xF0, 0xF0, 0xF1, 0xFB, 0xFF, 0x2E, 0xBF, 0x28, 0x45, 0x59, 0x0C, 0xF7,
    0x50, 0x55, 0x54, 0xF7, 0x41, 0xF7, 0x4C, 0x49, 0x54, 0x54, 0x4C, 0x45,
    0xF7, 0x4D, 0x4F, 0x52, 0x45, 0xF7, 0x41, 0x54, 0x54, 0x45, 0x4E, 0x54,
    0x49, 0x4F, 0x4E, 0x0C, 0xF0, 0x57, 0x45, 0xF7, 0x4B, 0x4E, 0x4F, 0x57,
    0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x43, 0x41, 0x4E, 0xF7, 0x44, 0x4F, 0xF7,
    0x49, 0x54, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_nok_01_Script_ShopItem = {
    Call(MakeItemEntity, 348, -130, 0, -412, 17, GameFlag(4717))
    Return
    End
};

u8 TTYD64_nok_01_String_BobOmb_5[] = {
    0xFC, 0x01, 0x34, 0x48, 0x41, 0x54, 0xF7, 0x57, 0x41, 0x53, 0xF7, 0x4A,
    0x55, 0x53, 0x54, 0xF7, 0x41, 0xF7, 0x57, 0x41, 0x52, 0x4D, 0x0D, 0x55,
    0x50, 0x0E, 0x0E, 0x0E, 0xF0, 0xF1, 0xFB, 0x27, 0x45, 0x54, 0xF7, 0x52,
    0x45, 0x41, 0x44, 0x59, 0x01, 0xF1, 0xFD
};

u8 TTYD64_nok_01_String_BobOmb_Ask[] = {
    0xFC, 0x01, 0x24, 0x4F, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x57, 0x41, 0x4E,
    0x54, 0xF7, 0x54, 0x4F, 0xF7, 0x54, 0x52, 0x59, 0xF7, 0x49, 0x54, 0xF7,
    0x4F, 0x4E, 0x45, 0xF0, 0x4D, 0x4F, 0x52, 0x45, 0xF7, 0x54, 0x49, 0x4D,
    0x45, 0x1F, 0xF0, 0xFF, 0x04, 0xFD
};

s32 TTYD64_nok_01_Data_BombMinigame_Level3_Order[] = {
    13, 13, 14, 13, 12, 14,
    -1
};

u8 TTYD64_nok_01_String_BobOmb_3[] = {
    0xFC, 0x01, 0x37, 0x48, 0x4F, 0xF7, 0x57, 0x41, 0x53, 0xF7, 0x54, 0x48,
    0x45, 0xF7, 0x46, 0x49, 0x52, 0x53, 0x54, 0xF7, 0x4F, 0x4E, 0x45, 0x1F,
    0xF1, 0xFD
};

s32 TTYD64_nok_01_Data_BombMinigame_Level2_Order[] = {
    14, 12, 14, 13, 13, -1
};

s32 TTYD64_nok_01_Data_BombMinigame_Level1_Order[] = {
    13, 14, 13, 12, -1
};

u8 TTYD64_nok_01_String_BobOmb_Cancel[] = {
    0xFB, 0x37, 0x45, 0x4C, 0x4C, 0x0C, 0xF7, 0x59, 0x4F, 0x55, 0x52, 0xF7,
    0x4C, 0x4F, 0x53, 0x53, 0x0E, 0xF1, 0xFD
};
// clang-format on

void TTYD64_InstallMap_nok_01(void) {
    Mod_ReplaceScript("TTYD64", &nok_01_EVS_NpcInit_Bobomb_01_Normal, &TTYD64_nok_01_Script_Init_8024D164);
    Mod_ReplaceScript("TTYD64", &nok_01_EVS_NpcInit_Bobomb_02_Normal, &TTYD64_nok_01_Script_Init_8024D188);
    memcpy(&nok_01_Inventory, &TTYD64_nok_01_ShopInventory_8024FB6C, sizeof(TTYD64_nok_01_ShopInventory_8024FB6C));
    Mod_ReplaceScript("TTYD64", &nok_01_EVS_Main, &TTYD64_nok_01_Script_Main);
    Mod_ReplaceScript("TTYD64", &nok_01_EVS_NpcInit_Bobomb_03_Normal, &TTYD64_nok_01_Script_Init_8024D1AC);
    TTYD64_maps_BindInlineMessage(TTYD64_nok_01_Script_Bombs_Minigame_Init, TTYD64_nok_01_String_BobOmb_1);
    TTYD64_maps_BindInlineMessage(TTYD64_nok_01_Script_Bombs_Minigame_Init, TTYD64_nok_01_String_BobOmb_Cancel);
    TTYD64_maps_BindInlineMessage(TTYD64_nok_01_Script_Bombs_Minigame_Init, TTYD64_nok_01_String_BobOmb_2);
    TTYD64_maps_BindInlineMessage(TTYD64_nok_01_Script_Bombs_Minigame, TTYD64_nok_01_String_BobOmb_3);
    TTYD64_maps_BindInlineMessage(TTYD64_nok_01_Script_BombGame_PickBomb, TTYD64_nok_01_String_BobOmb_5);
    TTYD64_maps_BindInlineMessage(TTYD64_nok_01_Script_BombGame_PickBomb, TTYD64_nok_01_String_BobOmb_6);
    TTYD64_maps_BindInlineMessage(TTYD64_nok_01_Script_BombGame_PickBomb, TTYD64_nok_01_String_BobOmb_4);
    TTYD64_maps_BindInlineMessage(TTYD64_nok_01_Script_BombGame_PickBomb, TTYD64_nok_01_String_BobOmb_Ask);
    TTYD64_maps_BindInlineMessage(TTYD64_nok_01_Script_BombGame_PickBomb, TTYD64_nok_01_String_BobOmb_Cancel);
}
