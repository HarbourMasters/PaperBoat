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

API_CALLABLE(BindNpcAux);
API_CALLABLE(BindNpcHit);
API_CALLABLE(BindNpcIdle);
API_CALLABLE(BindNpcInteract);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(CloseMessage);
API_CALLABLE(ContinueSpeech);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableModel);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(FadeOutMusic);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetSelfVar);
API_CALLABLE(GotoMap);
API_CALLABLE(InterpNpcYaw);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(NpcJump0);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtNpc);
API_CALLABLE(PushSong);
API_CALLABLE(RandInt);
API_CALLABLE(RestartNpcAux);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetEnemyFlagBits);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcJumpscale);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetNpcVar);
API_CALLABLE(SetPlayerFlagBits);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetSelfEnemyFlagBits);
API_CALLABLE(ShowChoice);
API_CALLABLE(ShowGotItem);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(TeleportPartnerToPlayer);
API_CALLABLE(TranslateGroup);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_mac_08_Script_EnterMap;
extern EvtScript TTYD64_mac_08_Script_Aux_Fuzzy;
extern EvtScript TTYD64_mac_08_Script_Hit_Fuzzy;
extern NpcData TTYD64_mac_08_NpcGroup_Fuzzy6[];
extern NpcData TTYD64_mac_08_NpcGroup_Fuzzy5[];
extern NpcData TTYD64_mac_08_NpcGroup_Fuzzy7[];
extern NpcData TTYD64_mac_08_NpcGroup_Fuzzy2[];
extern NpcData TTYD64_mac_08_NpcGroup_Fuzzy1[];
extern NpcData TTYD64_mac_08_NpcGroup_Fuzzy4[];
extern NpcData TTYD64_mac_08_NpcGroup_Fuzzy3[];
extern NpcData TTYD64_mac_08_NpcGroup_Bartender[];
extern EvtScript TTYD64_mac_08_Script_Bartender_Interact;
extern EvtScript TTYD64_mac_08_Script_InitGame;
extern EvtScript TTYD64_mac_08_Script_MoveBartender;
extern EvtScript TTYD64_mac_08_Script_Bartender_Idle;
extern EvtScript TTYD64_mac_08_Script_UpdateModels;
extern u8 TTYD64_mac_08_String_Bartender_Beaten2[];
extern u8 TTYD64_mac_08_String_Bartender_FirstTime1[];
extern EvtScript TTYD64_mac_08_Script_Main;
extern EvtScript TTYD64_mac_08_Script_FreeFuzzies;
extern u8 TTYD64_mac_08_String_Bartender_Cancel[];
extern u8 TTYD64_mac_08_String_Tattle[];
extern u8 TTYD64_mac_08_String_Bartender_FirstTime2[];
extern EvtScript TTYD64_mac_08_Script_Init_Fuzzy;
extern u8 TTYD64_mac_08_String_Bartender_Instructions[];
extern EvtScript TTYD64_mac_08_Script_Init_Bartneder;
extern EvtScript TTYD64_mac_08_Script_Exit0;
extern NpcGroupList TTYD64_mac_08_NpcGroupList_mac08;
extern u8 TTYD64_mac_08_String_Bartender_Hi[];
extern u8 TTYD64_mac_08_String_Bartender_GameOver[];
extern MapSettings TTYD64_mac_08_Header;
extern u8 TTYD64_mac_08_String_Bartender_Beaten1[];
extern EvtScript TTYD64_mac_08_Script_SetupMusic;
extern u8 TTYD64_mac_08_String_Bartender_ImReady[];
extern EntryList TTYD64_mac_08_EntryList;
extern NpcSettings TTYD64_mac_08_NpcSettings_Generic;
extern EvtScript TTYD64_mac_08_Script_CreateExitTriggers;

// clang-format off
static s32 TTYD64_mac_08_GetTattleMsg;

static s32 TTYD64_mac_08_GetTattle(void) {
    return TTYD64_mac_08_GetTattleMsg;
}

EvtScript TTYD64_mac_08_Script_EnterMap = {
    Exec(TTYD64_mac_08_Script_UpdateModels)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(1)
        Call(DisablePlayerInput, 1)
        Call(SpeakToPlayer, 7, 0xAC0005, 0xAC0001, 0, (Bytecode) TTYD64_mac_08_String_Bartender_GameOver)
        Call(DisablePlayerInput, 0)
    CaseEq(2)
        Call(DisablePlayerInput, 1)
        Call(SetNpcPos, 7, -353, 0, 81)
        Exec(TTYD64_mac_08_Script_UpdateModels)
        Call(TranslateGroup, 33, -745, 0, 95)
        Call(SpeakToPlayer, 7, 0xAC0005, 0xAC0001, 0, (Bytecode) TTYD64_mac_08_String_Bartender_Beaten1)
        SetF(LVar0, Float(25.0))
        SetF(LVar1, Float(255.0))
        ExecWait(TTYD64_Script_FadeScreenOut)
        Call(TranslateGroup, 33, 0, 0, 0)
        Set(GameFlag(4480), 1)
        Call(EnableGroup, 38, 0)
        Call(EnableModel, 22, 1)
        Call(ModifyColliderFlags, 0, 4, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 5, 0x7FFFFE00)
        Call(SetEnemyFlagBits, 0, 8192, 1)
        Call(SetEnemyFlagBits, 1, 8192, 1)
        Call(SetEnemyFlagBits, 2, 8192, 1)
        Call(SetEnemyFlagBits, 3, 8192, 1)
        Call(SetEnemyFlagBits, 4, 8192, 1)
        Thread
            Loop(8)
                Call(PlaySound, 818)
                Wait(10)
            EndLoop
        EndThread
        Call(PlaySound, 8321)
        Wait(10)
        Call(PlaySound, 225)
        Wait(15)
        Call(PlaySound, 225)
        Wait(15)
        Call(PlaySound, 225)
        Wait(15)
        Call(PlaySound, 225)
        Wait(30)
        Call(PlaySound, 11)
        SetF(LVar0, Float(25.0))
        SetF(LVar1, Float(5.0))
        Exec(TTYD64_Script_FadeScreenIn)
        Call(SpeakToPlayer, 7, 0xAC0005, 0xAC0001, 0, (Bytecode) TTYD64_mac_08_String_Bartender_Beaten2)
        Call(ShowGotItem, 366, 1, 0)
        Call(TTYD64_nm_AddBadge, 366, 0)
        SetF(LVar0, Float(25.0))
        SetF(LVar1, Float(255.0))
        ExecWait(TTYD64_Script_FadeScreenOut)
        Call(SetNpcPos, 7, 0, -1000, 0)
        Wait(5)
        SetF(LVar0, Float(25.0))
        SetF(LVar1, Float(5.0))
        Exec(TTYD64_Script_FadeScreenIn)
        Call(DisablePlayerInput, 0)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_mac_08_Script_Aux_Fuzzy = {
    Loop(0)
        Call(GetSelfVar, 0, LVar5)
        IfEq(LVar5, 0)
            Call(SetNpcPos, -1, 0, -1000, 0)
        Else
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(SetNpcPos, -1, -188, 115, -185)
    Call(SetNpcJumpscale, -1, Float(1.0))
    Call(NpcJump0, -1, -186, 47, -184, 10)
    Call(PlaySoundAtNpc, -1, 818, 0)
    Call(NpcJump0, -1, -186, 0, -108, 20)
    Call(SetNpcJumpscale, -1, Float(0.5))
    Add(MapVar(1), 1)
    Label(2)
    Call(GetNpcPos, 7, LVar0, LVar1, LVar2)
    Call(GetNpcPos, -1, LVar3, LVar4, LVar5)
    IfGt(LVar3, LVar0)
        Set(LVar3, 0)
    Else
        Set(LVar3, 1)
    EndIf
    Call(RandInt, 15, LVar4)
    Set(LVar5, 30)
    Add(LVar5, LVar4)
    IfEq(LVar3, 0)
        Mul(LVar5, -1)
    EndIf
    Set(LVar6, 25)
    Call(RandInt, 32, LVar4)
    Add(LVar6, LVar4)
    Call(RandInt, 1, LVar4)
    IfNe(LVar4, 0)
        Mul(LVar6, -1)
    EndIf
    Add(LVar0, LVar5)
    Add(LVar2, LVar6)
    Call(PlaySoundAtNpc, -1, 818, 0)
    Call(NpcJump0, -1, LVar0, LVar1, LVar2, 0)
    IfNe(MapVar(0), 0)
        Sub(MapVar(0), 1)
    EndIf
    IfEq(MapVar(0), 0)
        SetGroup(0)
        SuspendGroup(2)
        Call(DisablePlayerInput, 1)
        Call(PlaySound, 8419)
        Call(GotoMap, (Bytecode) "mac_08", 1)
        Return
    EndIf
    Wait(1)
    Goto(2)
    Return
    End
};

EvtScript TTYD64_mac_08_Script_Hit_Fuzzy = {
    Call(SetSelfEnemyFlagBits, 33, 1)
    IfNe(MapVar(1), 0)
        Sub(MapVar(1), 1)
    EndIf
    Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
    Call(SetNpcAnimation, -1, 0x2B0008)
    Call(PlaySoundAtNpc, -1, 818, 0)
    Call(NpcJump0, -1, LVar0, 0, LVar2, 25)
    Add(LVar0, 40)
    Add(LVar2, -40)
    Call(SetNpcAnimation, -1, 0x2B0008)
    Call(PlaySoundAtNpc, -1, 818, 0)
    Call(NpcJump0, -1, LVar0, 0, LVar2, 15)
    Add(LVar0, 30)
    Add(LVar2, -30)
    Call(SetNpcAnimation, -1, 0x2B0009)
    Call(PlaySoundAtNpc, -1, 818, 0)
    Call(NpcJump0, -1, LVar0, 0, LVar2, 13)
    Add(LVar0, 20)
    Add(LVar2, -20)
    Call(PlaySoundAtNpc, -1, 818, 0)
    Call(NpcJump0, -1, LVar0, 0, LVar2, 11)
    Add(LVar0, 10)
    Add(LVar2, 10)
    Call(PlaySoundAtNpc, -1, 818, 0)
    Call(NpcJump0, -1, LVar0, 0, LVar2, 9)
    Add(LVar0, 80)
    Add(LVar2, -80)
    Call(SetNpcAnimation, -1, 0x2B0003)
    Call(PlaySoundAtNpc, -1, 818, 0)
    Call(NpcJump0, -1, LVar0, 0, LVar2, 15)
    Call(EnableNpcShadow, -1, 0)
    Call(SetNpcPos, -1, 0, -1000, 0)
    Wait(50)
    Call(RestartNpcAux, -1)
    Call(SetSelfEnemyFlagBits, 33, 0)
    Return
    End
};

NpcData TTYD64_mac_08_NpcGroup_Fuzzy6[] = {
    {
        .id = 5,
        .settings = &TTYD64_mac_08_NpcSettings_Generic,
        .pos = { -188.0f, 115.0f, -185.0f },
        .flags = 0x19700F00,
        .init = &TTYD64_mac_08_Script_Init_Fuzzy,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002B0002, .walk = 0x002B0000, .run = 0x002B0000, .chase = 0x002B0000, .anim_4 = 0x002B0000, .anim_5 = 0x002B0000, .death = 0x002B0000, .hit = 0x002B0000, .anim_8 = 0x002B0000, .anim_9 = 0x002B0000, .anim_A = 0x002B0000, .anim_B = 0x002B0000, .anim_C = 0x002B0000, .anim_D = 0x002B0000, .anim_E = 0x002B0000, .anim_F = 0x002B0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_mac_08_NpcGroup_Fuzzy5[] = {
    {
        .id = 4,
        .settings = &TTYD64_mac_08_NpcSettings_Generic,
        .pos = { -188.0f, 115.0f, -185.0f },
        .flags = 0x19700F00,
        .init = &TTYD64_mac_08_Script_Init_Fuzzy,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002B0002, .walk = 0x002B0000, .run = 0x002B0000, .chase = 0x002B0000, .anim_4 = 0x002B0000, .anim_5 = 0x002B0000, .death = 0x002B0000, .hit = 0x002B0000, .anim_8 = 0x002B0000, .anim_9 = 0x002B0000, .anim_A = 0x002B0000, .anim_B = 0x002B0000, .anim_C = 0x002B0000, .anim_D = 0x002B0000, .anim_E = 0x002B0000, .anim_F = 0x002B0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_mac_08_NpcGroup_Fuzzy7[] = {
    {
        .id = 6,
        .settings = &TTYD64_mac_08_NpcSettings_Generic,
        .pos = { -188.0f, 115.0f, -185.0f },
        .flags = 0x19700F00,
        .init = &TTYD64_mac_08_Script_Init_Fuzzy,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002B0002, .walk = 0x002B0000, .run = 0x002B0000, .chase = 0x002B0000, .anim_4 = 0x002B0000, .anim_5 = 0x002B0000, .death = 0x002B0000, .hit = 0x002B0000, .anim_8 = 0x002B0000, .anim_9 = 0x002B0000, .anim_A = 0x002B0000, .anim_B = 0x002B0000, .anim_C = 0x002B0000, .anim_D = 0x002B0000, .anim_E = 0x002B0000, .anim_F = 0x002B0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_mac_08_NpcGroup_Fuzzy2[] = {
    {
        .id = 1,
        .settings = &TTYD64_mac_08_NpcSettings_Generic,
        .pos = { -188.0f, 115.0f, -185.0f },
        .flags = 0x19700F00,
        .init = &TTYD64_mac_08_Script_Init_Fuzzy,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002B0002, .walk = 0x002B0000, .run = 0x002B0000, .chase = 0x002B0000, .anim_4 = 0x002B0000, .anim_5 = 0x002B0000, .death = 0x002B0000, .hit = 0x002B0000, .anim_8 = 0x002B0000, .anim_9 = 0x002B0000, .anim_A = 0x002B0000, .anim_B = 0x002B0000, .anim_C = 0x002B0000, .anim_D = 0x002B0000, .anim_E = 0x002B0000, .anim_F = 0x002B0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_mac_08_NpcGroup_Fuzzy1[] = {
    {
        .id = 0,
        .settings = &TTYD64_mac_08_NpcSettings_Generic,
        .pos = { -188.0f, 115.0f, -185.0f },
        .flags = 0x19700F00,
        .init = &TTYD64_mac_08_Script_Init_Fuzzy,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002B0002, .walk = 0x002B0000, .run = 0x002B0000, .chase = 0x002B0000, .anim_4 = 0x002B0000, .anim_5 = 0x002B0000, .death = 0x002B0000, .hit = 0x002B0000, .anim_8 = 0x002B0000, .anim_9 = 0x002B0000, .anim_A = 0x002B0000, .anim_B = 0x002B0000, .anim_C = 0x002B0000, .anim_D = 0x002B0000, .anim_E = 0x002B0000, .anim_F = 0x002B0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_mac_08_NpcGroup_Fuzzy4[] = {
    {
        .id = 3,
        .settings = &TTYD64_mac_08_NpcSettings_Generic,
        .pos = { -188.0f, 115.0f, -185.0f },
        .flags = 0x19700F00,
        .init = &TTYD64_mac_08_Script_Init_Fuzzy,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002B0002, .walk = 0x002B0000, .run = 0x002B0000, .chase = 0x002B0000, .anim_4 = 0x002B0000, .anim_5 = 0x002B0000, .death = 0x002B0000, .hit = 0x002B0000, .anim_8 = 0x002B0000, .anim_9 = 0x002B0000, .anim_A = 0x002B0000, .anim_B = 0x002B0000, .anim_C = 0x002B0000, .anim_D = 0x002B0000, .anim_E = 0x002B0000, .anim_F = 0x002B0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_mac_08_NpcGroup_Fuzzy3[] = {
    {
        .id = 2,
        .settings = &TTYD64_mac_08_NpcSettings_Generic,
        .pos = { -188.0f, 115.0f, -185.0f },
        .flags = 0x19700F00,
        .init = &TTYD64_mac_08_Script_Init_Fuzzy,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002B0002, .walk = 0x002B0000, .run = 0x002B0000, .chase = 0x002B0000, .anim_4 = 0x002B0000, .anim_5 = 0x002B0000, .death = 0x002B0000, .hit = 0x002B0000, .anim_8 = 0x002B0000, .anim_9 = 0x002B0000, .anim_A = 0x002B0000, .anim_B = 0x002B0000, .anim_C = 0x002B0000, .anim_D = 0x002B0000, .anim_E = 0x002B0000, .anim_F = 0x002B0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_mac_08_NpcGroup_Bartender[] = {
    {
        .id = 7,
        .settings = &TTYD64_mac_08_NpcSettings_Generic,
        .pos = { 337.0f, 0.0f, -14.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_mac_08_Script_Init_Bartneder,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00AC0001, .walk = 0x00AC0000, .run = 0x00AC0000, .chase = 0x00AC0000, .anim_4 = 0x00AC0000, .anim_5 = 0x00AC0000, .death = 0x00AC0000, .hit = 0x00AC0000, .anim_8 = 0x00AC0000, .anim_9 = 0x00AC0000, .anim_A = 0x00AC0000, .anim_B = 0x00AC0000, .anim_C = 0x00AC0000, .anim_D = 0x00AC0000, .anim_E = 0x00AC0000, .anim_F = 0x00AC0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A0052,
    },
};

EvtScript TTYD64_mac_08_Script_Bartender_Interact = {
    IfEq(GameFlag(4479), 0)
        Call(SpeakToPlayer, -1, 0xAC0005, 0xAC0001, 0, (Bytecode) TTYD64_mac_08_String_Bartender_FirstTime1)
        Call(SpeakToPlayer, -1, 0xAC0005, 0xAC0001, 0, (Bytecode) TTYD64_mac_08_String_Bartender_FirstTime2)
        Set(GameFlag(4479), 1)
    EndIf
    Call(SpeakToPlayer, -1, 0xAC0005, 0xAC0001, 0, (Bytecode) TTYD64_mac_08_String_Bartender_Hi)
    Call(ShowChoice, 0x1E000D)
    IfNe(LVar0, 0)
        Call(ContinueSpeech, -1, 0xAC0005, 0xAC0001, 0, (Bytecode) TTYD64_mac_08_String_Bartender_Cancel)
        Return
    EndIf
    Call(CloseMessage)
    Call(SpeakToPlayer, -1, 0xAC0005, 0xAC0001, 0, (Bytecode) TTYD64_mac_08_String_Bartender_Instructions)
    Call(InterpNpcYaw, -1, 90, 0)
    Wait(15)
    Call(PlaySound, 250)
    Call(EnableGroup, 33, 0)
    Wait(15)
    Call(InterpNpcYaw, -1, -90, 0)
    Wait(15)
    Call(SpeakToPlayer, -1, 0xAC0005, 0xAC0001, 0, (Bytecode) TTYD64_mac_08_String_Bartender_ImReady)
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(255.0))
    ExecWait(TTYD64_Script_FadeScreenOut)
    ExecWait(TTYD64_mac_08_Script_InitGame)
    Return
    End
};

EvtScript TTYD64_mac_08_Script_InitGame = {
    Call(FadeOutMusic, 0, 500)
    Call(SetNpcPos, 7, 258, 0, 8)
    Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Call(SetPlayerPos, LVar0, LVar1, LVar2)
    Call(InterpPlayerYaw, -90, 0)
    Call(InterpNpcYaw, 7, -90, 0)
    Call(TeleportPartnerToPlayer)
    Set(MapVar(0), 100)
    Call(TTYD64_Bar_SetState, 1)
    Call(SetPlayerFlagBits, 256, 1)
    Call(SetEnemyFlagBits, -1, 0x8000000, 1)
    Wait(15)
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(5.0))
    ExecWait(TTYD64_Script_FadeScreenIn)
    Wait(95)
    Exec(TTYD64_mac_08_Script_FreeFuzzies)
    Call(PushSong, 133, 0)
    Return
    End
};

EvtScript TTYD64_mac_08_Script_MoveBartender = {
    SetGroup(1)
    Call(SetNpcAnimation, -1, 0xAC0002)
    Loop(0)
        Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
        Switch(MapVar(1))
        CaseEq(0)
            Set(LVar3, 1)
        CaseEq(1)
            Set(LVar3, 2)
        CaseEq(2)
            Set(LVar3, 3)
        CaseEq(3)
            Set(LVar3, 4)
        CaseEq(4)
            Set(LVar3, 5)
        CaseEq(5)
            Set(LVar3, 6)
        CaseEq(6)
            Set(LVar3, 7)
        EndSwitch
        Sub(LVar0, 1)
        Call(SetNpcPos, -1, LVar0, LVar1, LVar2)
        Wait(LVar3)
    EndLoop
    Return
    End
};

EvtScript TTYD64_mac_08_Script_Bartender_Idle = {
    Loop(0)
        Call(TTYD64_Bar_GetState, LVar0)
        IfEq(LVar0, 2)
            Exec(TTYD64_mac_08_Script_MoveBartender)
            Loop(0)
                Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
                IfLe(LVar0, -327)
                    SuspendGroup(2)
                    Call(DisablePlayerInput, 1)
                    Call(GotoMap, (Bytecode) "mac_08", 2)
                    Return
                EndIf
                Wait(1)
            EndLoop
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_mac_08_Script_UpdateModels = {
    Call(EnableGroup, 38, 0)
    Call(ModifyColliderFlags, 0, 5, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 4, 0x7FFFFE00)
    IfEq(GameFlag(4480), 0)
        Call(EnableGroup, 38, 1)
        Call(EnableModel, 22, 0)
        Call(ModifyColliderFlags, 1, 4, 0x7FFFFE00)
    Else
        Call(EnableModel, 22, 1)
        Call(ModifyColliderFlags, 1, 5, 0x7FFFFE00)
    EndIf
    Return
    End
};

u8 TTYD64_mac_08_String_Bartender_Beaten2[] = {
    0xFC, 0x01, 0x37, 0x4F, 0x57, 0x0C, 0xF7, 0x54, 0x48, 0x41, 0x4E, 0x4B,
    0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x53, 0x4F, 0xF7, 0x4D, 0x55, 0x43, 0x48,
    0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C, 0xF0, 0x29, 0xF7, 0x52, 0x45,
    0x41, 0x4C, 0x4C, 0x59, 0xF7, 0x57, 0x4F, 0x55, 0x4C, 0x44, 0x4E, 0x07,
    0x54, 0xF7, 0x4B, 0x4E, 0x4F, 0x57, 0xF7, 0x48, 0x4F, 0x57, 0xF7, 0x29,
    0xF7, 0x57, 0x4F, 0x55, 0x4C, 0x44, 0xF0, 0x48, 0x41, 0x56, 0x45, 0xF7,
    0x44, 0x4F, 0x4E, 0x45, 0xF7, 0x49, 0x54, 0xF7, 0x57, 0x49, 0x54, 0x48,
    0x4F, 0x55, 0x54, 0xF7, 0x59, 0x4F, 0x55, 0x0E, 0xF0, 0xF1, 0xFB, 0x21,
    0x4E, 0x44, 0xF7, 0x4C, 0x4F, 0x4F, 0x4B, 0x53, 0xF7, 0x4C, 0x49, 0x4B,
    0x45, 0xF7, 0x41, 0x4C, 0x4C, 0xF7, 0x54, 0x48, 0x4F, 0x53, 0x45, 0xF7,
    0x46, 0x55, 0x5A, 0x5A, 0x49, 0x45, 0x53, 0xF0, 0x41, 0x43, 0x54, 0x55,
    0x41, 0x4C, 0x4C, 0x59, 0xF7, 0x4C, 0x45, 0x46, 0x54, 0x0C, 0xF7, 0x54,
    0x48, 0x41, 0x4E, 0x4B, 0xF7, 0x59, 0x4F, 0x55, 0x0C, 0xF7, 0x59, 0x4F,
    0x55, 0xF7, 0x4B, 0x4E, 0x4F, 0x57, 0xF0, 0x57, 0x48, 0x41, 0x54, 0x1F,
    0xF0, 0xF1, 0xFB, 0x34, 0x41, 0x4B, 0x45, 0xF7, 0x54, 0x48, 0x49, 0x53,
    0xF7, 0x41, 0x53, 0xF7, 0x41, 0xF7, 0x54, 0x4F, 0x4B, 0x45, 0x4E, 0xF7,
    0x4F, 0x46, 0xF0, 0x41, 0x50, 0x50, 0x52, 0x45, 0x43, 0x49, 0x41, 0x54,
    0x49, 0x4F, 0x4E, 0xF7, 0x4D, 0x59, 0xF7, 0x46, 0x52, 0x49, 0x45, 0x4E,
    0x44, 0x0E, 0xF1, 0xFD
};

u8 TTYD64_mac_08_String_Bartender_FirstTime1[] = {
    0xFC, 0x01, 0x2C, 0x4F, 0x4F, 0x4B, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F,
    0x0E, 0x0E, 0x0E, 0xF7, 0x29, 0xF7, 0x46, 0x45, 0x45, 0x4C, 0xF7, 0x42,
    0x41, 0x44, 0xF7, 0x41, 0x44, 0x4D, 0x49, 0x54, 0x54, 0x49, 0x4E, 0x47,
    0xF0, 0x54, 0x48, 0x49, 0x53, 0x0C, 0xF7, 0x42, 0x55, 0x54, 0xF7, 0x29,
    0xF7, 0x48, 0x41, 0x56, 0x45, 0xF7, 0x41, 0xF7, 0x26, 0x55, 0x5A, 0x5A,
    0x59, 0xF7, 0x50, 0x52, 0x4F, 0x42, 0x4C, 0x45, 0x4D, 0x0C, 0xF0, 0x29,
    0xF7, 0x52, 0x45, 0x41, 0x4C, 0x4C, 0x59, 0xF7, 0x4E, 0x45, 0x45, 0x44,
    0xF7, 0x53, 0x4F, 0x4D, 0x45, 0x4F, 0x4E, 0x45, 0x07, 0x53, 0xF7, 0x48,
    0x45, 0x4C, 0x50, 0x01, 0xF0, 0xF1, 0xFB, 0x21, 0x4E, 0x44, 0xF7, 0x29,
    0xF7, 0x54, 0x48, 0x49, 0x4E, 0x4B, 0xF7, 0x59, 0x4F, 0x55, 0x07, 0x52,
    0x45, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x4F, 0x4E, 0x4C, 0x59, 0xF7, 0x4F,
    0x4E, 0x45, 0xF0, 0x29, 0xF7, 0x43, 0x41, 0x4E, 0xF7, 0x54, 0x52, 0x55,
    0x53, 0x54, 0x0E, 0xF0, 0xF1, 0xFB, 0x22, 0x41, 0x53, 0x49, 0x43, 0x41,
    0x4C, 0x4C, 0x59, 0xF7, 0x54, 0x48, 0x45, 0x52, 0x45, 0x07, 0x53, 0xF7,
    0x41, 0xF7, 0x4E, 0x45, 0x53, 0x54, 0xF7, 0x4F, 0x46, 0xF0, 0x46, 0x55,
    0x5A, 0x5A, 0x49, 0x45, 0x53, 0xF7, 0x49, 0x4E, 0xF7, 0x54, 0x48, 0x45,
    0xF7, 0x46, 0x52, 0x45, 0x45, 0x5A, 0x45, 0x52, 0x07, 0x53, 0xF7, 0x44,
    0x55, 0x43, 0x54, 0x01, 0xF0, 0xF1, 0xFD
};

EvtScript TTYD64_mac_08_Script_Main = {
    Set(GameByte(425), 1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(TTYD64_Bar_ClearData)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_mac_08_NpcGroupList_mac08)
    Exec(TTYD64_mac_08_Script_SetupMusic)
    Exec(TTYD64_mac_08_Script_EnterMap)
    Exec(TTYD64_mac_08_Script_CreateExitTriggers)
    Return
    End
};

EvtScript TTYD64_mac_08_Script_FreeFuzzies = {
    Call(SetNpcVar, 0, 0, 1)
    Wait(100)
    Call(SetNpcVar, 1, 0, 1)
    Wait(100)
    Call(SetNpcVar, 2, 0, 1)
    Wait(300)
    Call(SetNpcVar, 3, 0, 1)
    Wait(200)
    Call(SetNpcVar, 4, 0, 1)
    Return
    End
};

u8 TTYD64_mac_08_String_Bartender_Cancel[] = {
    0xFB, 0x2F, 0x48, 0xF7, 0x29, 0xF7, 0x55, 0x4E, 0x44, 0x45, 0x52, 0x53,
    0x54, 0x41, 0x4E, 0x44, 0x0C, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x48, 0x41,
    0x56, 0x45, 0xF7, 0x4F, 0x54, 0x48, 0x45, 0x52, 0xF0, 0x49, 0x53, 0x53,
    0x55, 0x45, 0x53, 0xF7, 0x54, 0x4F, 0xF7, 0x41, 0x54, 0x54, 0x45, 0x4E,
    0x44, 0xF7, 0x46, 0x49, 0x52, 0x53, 0x54, 0x0C, 0xF7, 0x44, 0x4F, 0x4E,
    0x07, 0x54, 0xF0, 0x57, 0x4F, 0x52, 0x52, 0x59, 0x0C, 0xF7, 0x29, 0x07,
    0x4C, 0x4C, 0xF7, 0x57, 0x41, 0x49, 0x54, 0xF7, 0x48, 0x45, 0x52, 0x45,
    0xF7, 0x46, 0x4F, 0x52, 0xF7, 0x59, 0x4F, 0x55, 0x0C, 0xF7, 0x42, 0x55,
    0x54, 0xF0, 0x50, 0x4C, 0x45, 0x41, 0x53, 0x45, 0xF7, 0x44, 0x4F, 0x4E,
    0x07, 0x54, 0xF7, 0x54, 0x41, 0x4B, 0x45, 0xF7, 0x54, 0x4F, 0x4F, 0xF7,
    0x4D, 0x55, 0x43, 0x48, 0xF7, 0x54, 0x49, 0x4D, 0x45, 0x0E, 0xF0, 0xF1,
    0xFB, 0x29, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x57, 0x41, 0x4E,
    0x54, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x50, 0x52, 0x4F, 0x42, 0x4C, 0x45,
    0x4D, 0xF7, 0x54, 0x4F, 0xF7, 0x47, 0x52, 0x4F, 0x57, 0xF0, 0x45, 0x56,
    0x45, 0x4E, 0xF7, 0x4D, 0x4F, 0x52, 0x45, 0x0E, 0xF1, 0xFD
};

u8 TTYD64_mac_08_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x29, 0xF7, 0x48, 0x41, 0x56, 0x45, 0xF7, 0x41,
    0xF7, 0x4C, 0x4F, 0x54, 0xF7, 0x4F, 0x46, 0xF7, 0x51, 0x55, 0x45, 0x53,
    0x54, 0x49, 0x4F, 0x4E, 0x53, 0xF7, 0x41, 0x42, 0x4F, 0x55, 0x54, 0xF7,
    0x48, 0x4F, 0x57, 0xF0, 0x45, 0x58, 0x41, 0x43, 0x54, 0x4C, 0x59, 0xF7,
    0x54, 0x48, 0x4F, 0x53, 0x45, 0xF7, 0x26, 0x55, 0x5A, 0x5A, 0x49, 0x45,
    0x53, 0xF7, 0x47, 0x4F, 0x54, 0xF7, 0x54, 0x4F, 0xF7, 0x54, 0x48, 0x49,
    0x53, 0xF0, 0x50, 0x4C, 0x41, 0x43, 0x45, 0x0C, 0xF7, 0x42, 0x55, 0x54,
    0xF7, 0x29, 0xF7, 0x54, 0x48, 0x49, 0x4E, 0x4B, 0xF7, 0x54, 0x48, 0x45,
    0xF7, 0x42, 0x49, 0x47, 0x47, 0x45, 0x53, 0x54, 0xF0, 0x51, 0x55, 0x45,
    0x53, 0x54, 0x49, 0x4F, 0x4E, 0xF7, 0x29, 0xF7, 0x48, 0x41, 0x56, 0x45,
    0xF7, 0x49, 0x53, 0x0E, 0x0E, 0x0E, 0xF0, 0xF1, 0xFB, 0x37, 0x48, 0x59,
    0xF7, 0x49, 0x53, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x57, 0x41, 0x52, 0x45,
    0x48, 0x4F, 0x55, 0x53, 0x45, 0xF7, 0x42, 0x49, 0x47, 0x47, 0x45, 0x52,
    0xF7, 0x54, 0x48, 0x41, 0x4E, 0xF0, 0x23, 0x4C, 0x55, 0x42, 0x16, 0x14,
    0x1F, 0xF1, 0xFD
};

u8 TTYD64_mac_08_String_Bartender_FirstTime2[] = {
    0xFC, 0x01, 0x21, 0x4E, 0x44, 0xF7, 0x29, 0xF7, 0x48, 0x41, 0x56, 0x45,
    0xF7, 0x54, 0x4F, 0xF7, 0x4D, 0x4F, 0x56, 0x45, 0xF7, 0x54, 0x48, 0x45,
    0x53, 0x45, 0xF7, 0x42, 0x4F, 0x58, 0x45, 0x53, 0xF0, 0x54, 0x4F, 0xF7,
    0x54, 0x48, 0x45, 0xF7, 0x4F, 0x54, 0x48, 0x45, 0x52, 0xF7, 0x45, 0x4E,
    0x44, 0xF7, 0x4F, 0x46, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x52, 0x4F, 0x4F,
    0x4D, 0xF7, 0x42, 0x55, 0x54, 0xF0, 0x54, 0x48, 0x4F, 0x53, 0x45, 0xF7,
    0x46, 0x55, 0x5A, 0x5A, 0x49, 0x45, 0x53, 0xF7, 0x57, 0x4F, 0x4E, 0x07,
    0x54, 0xF7, 0x4C, 0x45, 0x54, 0xF7, 0x4D, 0x45, 0x0E, 0xF0, 0xF1, 0xFB,
    0x23, 0x4F, 0x55, 0x4C, 0x44, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x50, 0x4C,
    0x45, 0x41, 0x53, 0x45, 0xF7, 0x53, 0x54, 0x4F, 0x50, 0xF7, 0x54, 0x48,
    0x45, 0x4D, 0xF7, 0x57, 0x48, 0x49, 0x4C, 0x45, 0xF0, 0x29, 0xF7, 0x4D,
    0x4F, 0x56, 0x45, 0xF7, 0x41, 0x4C, 0x4C, 0xF7, 0x54, 0x48, 0x45, 0x53,
    0x45, 0xF7, 0x42, 0x4F, 0x58, 0x45, 0x53, 0x1F, 0xF1, 0xFD
};

EvtScript TTYD64_mac_08_Script_Init_Fuzzy = {
    Call(BindNpcAux, -1, (Bytecode) TTYD64_mac_08_Script_Aux_Fuzzy)
    Call(BindNpcHit, -1, (Bytecode) TTYD64_mac_08_Script_Hit_Fuzzy)
    IfEq(GameFlag(4480), 1)
        Call(SetEnemyFlagBits, -1, 8192, 1)
    EndIf
    Call(SetEnemyFlagBits, -1, 8192, 1)
    Call(SetNpcFlagBits, -1, 0, 1)
    Return
    End
};

u8 TTYD64_mac_08_String_Bartender_Instructions[] = {
    0xFC, 0x01, 0x34, 0x48, 0x49, 0x53, 0xF7, 0x49, 0x53, 0xF7, 0x57, 0x48,
    0x41, 0x54, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x4E, 0x45, 0x45, 0x44, 0xF7,
    0x54, 0x4F, 0xF7, 0x44, 0x4F, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C,
    0xF0, 0x54, 0x52, 0x59, 0xF7, 0x54, 0x4F, 0xF7, 0x53, 0x54, 0x4F, 0x50,
    0xF7, 0x54, 0x48, 0x4F, 0x53, 0x45, 0xF7, 0x46, 0x55, 0x5A, 0x5A, 0x49,
    0x45, 0x53, 0xF7, 0x55, 0x4E, 0x54, 0x49, 0x4C, 0xF7, 0x29, 0xF0, 0x52,
    0x45, 0x41, 0x43, 0x48, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x4F, 0x54, 0x48,
    0x45, 0x52, 0xF7, 0x53, 0x49, 0x44, 0x45, 0xF7, 0x4F, 0x46, 0xF7, 0x54,
    0x48, 0x45, 0xF0, 0x57, 0x41, 0x52, 0x45, 0x48, 0x4F, 0x55, 0x53, 0x45,
    0x0C, 0xF7, 0x4F, 0x4B, 0x1F, 0xF1, 0xFD
};

EvtScript TTYD64_mac_08_Script_Init_Bartneder = {
    IfEq(GameFlag(4480), 1)
        Call(SetNpcPos, -1, 0, -1000, 0)
    EndIf
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_mac_08_Script_Bartender_Interact)
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_mac_08_Script_Bartender_Idle)
    Return
    End
};

EvtScript TTYD64_mac_08_Script_Exit0 = {
    SetGroup(27)
    Call(TTYD64_Bar_ClearData)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "mac_05", 4)
    Wait(100)
    Return
    End
};

NpcGroupList TTYD64_mac_08_NpcGroupList_mac08 = {
    { .npcCount = 1, .npcs = TTYD64_mac_08_NpcGroup_Bartender, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_08_NpcGroup_Fuzzy1, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_08_NpcGroup_Fuzzy2, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_08_NpcGroup_Fuzzy3, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_08_NpcGroup_Fuzzy4, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_08_NpcGroup_Fuzzy5, .battle = 0x0000, .stage = 0 },
    {},
};

u8 TTYD64_mac_08_String_Bartender_Hi[] = {
    0xFC, 0x01, 0x33, 0x4F, 0x0E, 0x0E, 0x0E, 0xF7, 0x57, 0x49, 0x4C, 0x4C,
    0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x48, 0x45, 0x4C, 0x50, 0xF7, 0x4D, 0x45,
    0x1F, 0xF0, 0x29, 0xF7, 0x50, 0x52, 0x4F, 0x4D, 0x49, 0x53, 0x45, 0xF7,
    0x59, 0x4F, 0x55, 0x0C, 0xF7, 0x29, 0xF7, 0x57, 0x49, 0x4C, 0x4C, 0xF7,
    0x50, 0x41, 0x59, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x42, 0x41, 0x43, 0x4B,
    0x0E, 0xF0, 0xFF, 0x04, 0xFD
};

u8 TTYD64_mac_08_String_Bartender_GameOver[] = {
    0xFC, 0x01, 0x37, 0x45, 0x4C, 0x4C, 0xF7, 0x54, 0x48, 0x41, 0x54, 0xF7,
    0x44, 0x49, 0x44, 0x4E, 0x07, 0x54, 0xF7, 0x54, 0x55, 0x52, 0x4E, 0xF7,
    0x4F, 0x55, 0x54, 0xF7, 0x41, 0x53, 0xF0, 0x45, 0x58, 0x50, 0x45, 0x43,
    0x54, 0x45, 0x44, 0x0E, 0x0E, 0x0E, 0xF7, 0x54, 0x48, 0x45, 0x59, 0x07,
    0x52, 0x45, 0xF7, 0x54, 0x4F, 0x4F, 0xF7, 0x46, 0x41, 0x53, 0x54, 0x01,
    0xF1, 0xFD
};

MapSettings TTYD64_mac_08_Header = {
    .main = &TTYD64_mac_08_Script_Main,
    .entryList = &TTYD64_mac_08_EntryList,
    .entryCount = 3,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_mac_08_GetTattle },
};

u8 TTYD64_mac_08_String_Bartender_Beaten1[] = {
    0xFC, 0x01, 0x27, 0x4F, 0x4F, 0x44, 0xF7, 0x4A, 0x4F, 0x42, 0x0C, 0xF7,
    0x57, 0x45, 0xF7, 0x48, 0x41, 0x56, 0x45, 0xF7, 0x41, 0xF7, 0x42, 0x4F,
    0x58, 0x0C, 0xF7, 0x4C, 0x45, 0x54, 0x07, 0x53, 0xF7, 0x47, 0x4F, 0xF0,
    0x46, 0x4F, 0x52, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x4F, 0x54, 0x48, 0x45,
    0x52, 0x53, 0xF7, 0x4F, 0x4E, 0x45, 0x53, 0x0E, 0xF1, 0xFD
};

EvtScript TTYD64_mac_08_Script_SetupMusic = {
    Call(SetMusic, 0, 93, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

u8 TTYD64_mac_08_String_Bartender_ImReady[] = {
    0xFC, 0x01, 0x2F, 0x4B, 0x41, 0x59, 0x0C, 0xF7, 0x29, 0xF7, 0x54, 0x48,
    0x49, 0x4E, 0x4B, 0xF7, 0x29, 0x07, 0x4D, 0xF7, 0x52, 0x45, 0x41, 0x44,
    0x59, 0x0C, 0xF7, 0x4C, 0x45, 0x54, 0x07, 0x53, 0xF7, 0x47, 0x4F, 0x0C,
    0xF0, 0x57, 0x45, 0xF7, 0x43, 0x41, 0x4E, 0xF7, 0x44, 0x4F, 0xF7, 0x49,
    0x54, 0x0E, 0xF1, 0xFD
};

EntryList TTYD64_mac_08_EntryList = {
    { 327.0f, 0.0f, -255.0f, -90.0f },
    { 299.0f, 0.0f, -14.0f, 90.0f },
    { -327.0f, 0.0f, 81.0f, -90.0f },
};

NpcSettings TTYD64_mac_08_NpcSettings_Generic = {
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

EvtScript TTYD64_mac_08_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_mac_08_Script_Exit0, 128, 7, 1, 0)
    Return
    End
};

MapConfig TTYD64_mapcfg_mac_08 = {
    .id = "mac_08",
    .settings = &TTYD64_mac_08_Header,
    .bgName = "obk_bg",
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_mac_08(void) {
    TTYD64_nm_BindMessage(TTYD64_mac_08_Script_EnterMap, TTYD64_mac_08_String_Bartender_GameOver);
    TTYD64_nm_BindMessage(TTYD64_mac_08_Script_EnterMap, TTYD64_mac_08_String_Bartender_Beaten1);
    TTYD64_nm_BindMessage(TTYD64_mac_08_Script_EnterMap, TTYD64_mac_08_String_Bartender_Beaten2);
    TTYD64_nm_BindMessage(TTYD64_mac_08_Script_Bartender_Interact, TTYD64_mac_08_String_Bartender_FirstTime1);
    TTYD64_nm_BindMessage(TTYD64_mac_08_Script_Bartender_Interact, TTYD64_mac_08_String_Bartender_FirstTime2);
    TTYD64_nm_BindMessage(TTYD64_mac_08_Script_Bartender_Interact, TTYD64_mac_08_String_Bartender_Hi);
    TTYD64_nm_BindMessage(TTYD64_mac_08_Script_Bartender_Interact, TTYD64_mac_08_String_Bartender_Cancel);
    TTYD64_nm_BindMessage(TTYD64_mac_08_Script_Bartender_Interact, TTYD64_mac_08_String_Bartender_Instructions);
    TTYD64_nm_BindMessage(TTYD64_mac_08_Script_Bartender_Interact, TTYD64_mac_08_String_Bartender_ImReady);
    TTYD64_mac_08_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_08_String_Tattle);
}
