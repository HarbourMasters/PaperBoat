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

API_CALLABLE(AssignScript);
API_CALLABLE(BindNpcAI);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GetSelfNpcID);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerJump);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerJumpscale);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateLerp);
API_CALLABLE(func_802D2484);
API_CALLABLE(jan_01_HoppingAI_Main);
API_CALLABLE(jan_02_AdjustTrackVolumes);
API_CALLABLE(jan_11_DarkRoomUpdate);

extern EvtScript TTYD64_jan_24_Script_PullLimb;
extern EvtScript TTYD64_jan_24_Script_LimbsFX;
extern NpcData TTYD64_jan_24_NpcGroup_Fuzzy2[];
extern NpcData TTYD64_jan_24_NpcGroup_Fuzzy1[];
extern EvtScript TTYD64_jan_24_Script_Main;
extern EvtScript TTYD64_jan_24_Script_NPC_BindAI;
extern EvtScript TTYD64_jan_24_Script_ScriptedSpring_Entity_Spring;
extern EvtScript TTYD64_jan_24_Script_EnterMap_Spring;
extern EvtScript TTYD64_jan_24_Script_SetupMusic;
extern u8 TTYD64_jan_24_String_Tattle[];
extern EvtScript TTYD64_jan_24_Script_PullLimb3;
extern EvtScript TTYD64_jan_24_Script_PullLimb4;
extern EvtScript TTYD64_jan_24_Script_PullLimb5;
extern EvtScript TTYD64_jan_24_Script_PullLimb6;
extern EvtScript TTYD64_jan_24_Script_PullLimb1;
extern EvtScript TTYD64_jan_24_Script_PullLimb2;
extern EvtScript TTYD64_jan_24_Script_MakeEntities;
extern MapSettings TTYD64_jan_24_Header;
extern EvtScript TTYD64_jan_24_Script_NpcAI_802419B0_jan_01;
extern MobileAISettings TTYD64_jan_24_AISettings_80241980_jan_01;
extern NpcSettings TTYD64_jan_24_NpcSettings_802419EC_jan_01;
extern EvtScript TTYD64_jan_24_Script_SetDarkRoom;
extern NpcGroupList TTYD64_jan_24_NpcGroup_jan24;
extern EvtScript TTYD64_jan_24_Script_InitNPC_Fuzzy;
extern EntryList TTYD64_jan_24_EntryList;

// clang-format off
static s32 TTYD64_jan_24_GetTattleMsg;

static s32 TTYD64_jan_24_GetTattle(void) {
    return TTYD64_jan_24_GetTattleMsg;
}

EvtScript TTYD64_jan_24_Script_PullLimb = {
    Set(LVar5, LVar0)
    Set(LVar6, LVar1)
    Call(TTYD64_TestPlayerAnimFlags, PA_FLAG_USING_WATT, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_SetPartnerAbilityState, PARTNER_WATT, 2)
        Wait(1)
    EndIf
    SetGroup(0)
    SuspendGroup(2)
    Call(DisablePartnerAI, 0)
    Call(SetPlayerActionState, 9)
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerAnimation, 0x10002)
    Call(SetPlayerAnimation, 0x80005)
    Call(GetModelCenter, LVar6)
    IfGt(LVar0, 0)
        Sub(LVar0, 2)
    Else
        Add(LVar0, 2)
    EndIf
    Sub(LVar1, 98)
    Add(LVar2, 5)
    Call(SetPlayerPos, LVar0, LVar1, LVar2)
    Wait(3)
    Call(PlaySound, 8386)
    Call(MakeLerp, 0, -4, 4, 0)
    Loop(0)
        Call(UpdateLerp)
        Set(LVar3, LVar0)
        Set(LVar4, LVar1)
        Call(TranslateModel, LVar6, 0, LVar3, 0)
        Call(GetModelCenter, LVar6)
        Sub(LVar0, 2)
        Sub(LVar1, 98)
        Add(LVar2, 5)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
        IfEq(LVar4, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(MakeLerp, -4, 0, 4, 0)
    Loop(0)
        Call(UpdateLerp)
        Set(LVar3, LVar0)
        Set(LVar4, LVar1)
        Call(TranslateModel, LVar6, 0, LVar3, 0)
        Call(GetModelCenter, LVar6)
        Sub(LVar0, 2)
        Sub(LVar1, 98)
        Add(LVar2, 5)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
        IfEq(LVar4, 0)
            BreakLoop
        EndIf
    EndLoop
    Wait(2)
    Thread
        Wait(10)
        Switch(LVar5)
        CaseEq(0)
            IfEq(GameFlag(5388), 0)
                Set(LVar0, -107)
                Set(LVar1, 0)
                Set(LVar2, 15)
                Add(LVar1, 285)
                Call(MakeItemEntity, 348, LVar0, LVar1, LVar2, 13, GameFlag(5388))
            EndIf
        CaseEq(1)
            Set(LVar0, -120)
            Set(LVar1, 0)
            Set(LVar2, 117)
            Add(LVar1, 100)
            Call(SetNpcPos, 0, LVar0, LVar1, LVar2)
            Call(PlaySound, 818)
        CaseEq(2)
            IfEq(GameFlag(5390), 0)
                Set(LVar0, -75)
                Set(LVar1, 0)
                Set(LVar2, -36)
                Add(LVar1, 285)
                Call(MakeItemEntity, 343, LVar0, LVar1, LVar2, 13, GameFlag(5390))
            EndIf
        CaseEq(3)
            IfEq(GameFlag(5391), 0)
                Set(LVar0, 224)
                Set(LVar1, 0)
                Set(LVar2, 130)
                Add(LVar1, 100)
                Call(MakeItemEntity, 273, LVar0, LVar1, LVar2, 13, GameFlag(5391))
            EndIf
        CaseEq(4)
            IfEq(GameFlag(5389), 0)
                Set(LVar0, 153)
                Set(LVar1, 0)
                Set(LVar2, -59)
                Add(LVar1, 285)
                Call(MakeItemEntity, 343, LVar0, LVar1, LVar2, 13, GameFlag(5389))
            EndIf
        CaseEq(5)
            Set(LVar0, 190)
            Set(LVar1, 0)
            Set(LVar2, 50)
            Add(LVar1, 285)
            Call(SetNpcPos, 1, LVar0, LVar1, LVar2)
            Call(PlaySound, 818)
        EndSwitch
    EndThread
    Call(MakeLerp, 0, -20, 25, 0)
    Loop(0)
        Call(UpdateLerp)
        Set(LVar3, LVar0)
        Set(LVar4, LVar1)
        Call(TranslateModel, LVar6, 0, LVar3, 0)
        Call(GetModelCenter, LVar6)
        Sub(LVar0, 2)
        Sub(LVar1, 98)
        Add(LVar2, 5)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
        IfEq(LVar4, 0)
            BreakLoop
        EndIf
    EndLoop
    Wait(1)
    Call(SetPlayerAnimation, 0x10002)
    Call(SetPlayerAnimation, 0x10008)
    Call(DisablePlayerPhysics, 0)
    Call(PlaySound, 8329)
    Call(MakeLerp, -32, 7, 5, 0)
    Loop(0)
        Call(UpdateLerp)
        Set(LVar3, LVar0)
        Set(LVar4, LVar1)
        Call(TranslateModel, LVar6, 0, LVar3, 0)
        Wait(1)
        IfEq(LVar4, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(MakeLerp, 7, 0, 6, 0)
    Loop(0)
        Call(UpdateLerp)
        Set(LVar3, LVar0)
        Set(LVar4, LVar1)
        Call(TranslateModel, LVar6, 0, LVar3, 0)
        Wait(1)
        IfEq(LVar4, 0)
            BreakLoop
        EndIf
    EndLoop
    ResumeGroup(2)
    Call(DisablePlayerInput, 0)
    Call(EnablePartnerAI)
    Return
    End
};

EvtScript TTYD64_jan_24_Script_LimbsFX = {
    Loop(0)
        IfEq(MapFlag(1), 0)
            Call(PlayEffect_impl, 109, 0, -162, 53, 18, Float(1.2998046875), 0, 0, 0, 0, 0, 0, 0, 0)
        EndIf
        IfEq(MapFlag(2), 0)
            Call(PlayEffect_impl, 109, 0, -58, 53, 116, Float(1.2998046875), 0, 0, 0, 0, 0, 0, 0, 0)
        EndIf
        IfEq(MapFlag(3), 0)
            Call(PlayEffect_impl, 109, 0, -22, 53, -28, Float(1.2998046875), 0, 0, 0, 0, 0, 0, 0, 0)
        EndIf
        IfEq(MapFlag(4), 0)
            Call(PlayEffect_impl, 109, 0, 178, 53, 130, Float(1.2998046875), 0, 0, 0, 0, 0, 0, 0, 0)
        EndIf
        IfEq(MapFlag(5), 0)
            Call(PlayEffect_impl, 109, 0, 193, 53, -54, Float(1.2998046875), 0, 0, 0, 0, 0, 0, 0, 0)
        EndIf
        IfEq(MapFlag(6), 0)
            Call(PlayEffect_impl, 109, 0, 241, 53, 47, Float(1.2998046875), 0, 0, 0, 0, 0, 0, 0, 0)
        EndIf
        Wait(20)
    EndLoop
    Return
    End
};

NpcData TTYD64_jan_24_NpcGroup_Fuzzy2[] = {
    {
        .id = 1,
        .settings = &TTYD64_jan_24_NpcSettings_802419EC_jan_01,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00200000,
        .init = &TTYD64_jan_24_Script_InitNPC_Fuzzy,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 16, .itemDrops = { { 154, 5, 0 }, { 139, 5, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 190, .centerPos.y = 0, .centerPos.z = 50, .wanderSize.x = 50, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 190, .detectPos.y = 0, .detectPos.z = 50, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002B0301, .walk = 0x002B0302, .run = 0x002B0303, .chase = 0x002B0303, .anim_4 = 0x002B0300, .anim_5 = 0x002B0300, .death = 0x002B0313, .hit = 0x002B0308, .anim_8 = 0x002B0300, .anim_9 = 0x002B0300, .anim_A = 0x002B0300, .anim_B = 0x002B0300, .anim_C = 0x002B0300, .anim_D = 0x002B0300, .anim_E = 0x002B0300, .anim_F = 0x002B0300 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x02,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_jan_24_NpcGroup_Fuzzy1[] = {
    {
        .id = 0,
        .settings = &TTYD64_jan_24_NpcSettings_802419EC_jan_01,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00200000,
        .init = &TTYD64_jan_24_Script_InitNPC_Fuzzy,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 16, .itemDrops = { { 154, 5, 0 }, { 139, 5, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = -120, .centerPos.y = 0, .centerPos.z = 117, .wanderSize.x = 50, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = -120, .detectPos.y = 0, .detectPos.z = 117, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002B0301, .walk = 0x002B0302, .run = 0x002B0303, .chase = 0x002B0303, .anim_4 = 0x002B0300, .anim_5 = 0x002B0300, .death = 0x002B0313, .hit = 0x002B0308, .anim_8 = 0x002B0300, .anim_9 = 0x002B0300, .anim_A = 0x002B0300, .anim_B = 0x002B0300, .anim_C = 0x002B0300, .anim_D = 0x002B0300, .anim_E = 0x002B0300, .anim_F = 0x002B0300 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x02,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_jan_24_Script_Main = {
    Set(GameByte(425), 36)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    ExecWait(TTYD64_jan_24_Script_MakeEntities)
    Exec(TTYD64_jan_24_Script_SetupMusic)
    Exec(TTYD64_jan_24_Script_SetDarkRoom)
    BindTrigger(TTYD64_jan_24_Script_PullLimb1, 0x40000, 12, 1, 0)
    BindTrigger(TTYD64_jan_24_Script_PullLimb2, 0x40000, 15, 1, 0)
    BindTrigger(TTYD64_jan_24_Script_PullLimb3, 0x40000, 18, 1, 0)
    BindTrigger(TTYD64_jan_24_Script_PullLimb4, 0x40000, 21, 1, 0)
    BindTrigger(TTYD64_jan_24_Script_PullLimb5, 0x40000, 24, 1, 0)
    BindTrigger(TTYD64_jan_24_Script_PullLimb6, 0x40000, 27, 1, 0)
    Exec(TTYD64_jan_24_Script_LimbsFX)
    Exec(TTYD64_jan_24_Script_EnterMap_Spring)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_jan_24_NpcGroup_jan24)
    Return
    End
};

EvtScript TTYD64_jan_24_Script_NPC_BindAI = {
    Loop(0)
        Call(GetSelfNpcID, LVar0)
        IfEq(LVar0, 0)
            Set(LVar0, MapFlag(2))
        Else
            Set(LVar0, MapFlag(6))
        EndIf
        IfEq(LVar0, 1)
            Loop(0)
                Call(TTYD64_TestPlayerFlags, PS_FLAG_INPUT_DISABLED, LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            Call(SetNpcFlagBits, -1, 512, 1)
            Call(BindNpcAI, -1, (Bytecode) TTYD64_jan_24_Script_NpcAI_802419B0_jan_01)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_jan_24_Script_ScriptedSpring_Entity_Spring = {
    IfEq(MapFlag(0), 1)
        Return
    EndIf
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerActionState, 6)
    Wait(1)
    Call(SetPlayerJumpscale, Float(0.7001953125))
    Thread
        Wait(10)
        Call(GotoMap, (Bytecode) "jan_02", 2)
    EndThread
    Call(PlayerJump, 75, 208, -7, 30)
    Return
    End
};

EvtScript TTYD64_jan_24_Script_EnterMap_Spring = {
    Set(MapFlag(0), 1)
    Call(DisablePlayerInput, 1)
    Call(SetPlayerActionState, 8)
    Call(func_802D2484)
    Call(SetPlayerActionState, 6)
    Call(SetPlayerJumpscale, Float(1.5))
    Call(PlayerJump, 105, 85, 25, 16)
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerInput, 0)
    Set(MapFlag(0), 0)
    Return
    End
};

EvtScript TTYD64_jan_24_Script_SetupMusic = {
    Switch(GameByte(0))
    CaseRange(14, 15)
        Call(SetMusic, 0, 39, 0, 8)
    CaseDefault
        Call(SetMusic, 0, 38, 0, 8)
        Thread
            Wait(3)
            Call(jan_02_AdjustTrackVolumes)
        EndThread
    EndSwitch
    Call(ClearAmbientSounds, 250)
    Return
    End
};

u8 TTYD64_jan_24_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x35, 0x48, 0x1F, 0xF7, 0x21, 0xF7, 0x53, 0x45,
    0x43, 0x52, 0x45, 0x54, 0xF7, 0x50, 0x41, 0x53, 0x53, 0x41, 0x47, 0x45,
    0xF7, 0x42, 0x45, 0x4C, 0x4F, 0x57, 0xF0, 0x54, 0x48, 0x45, 0xF7, 0x32,
    0x41, 0x56, 0x45, 0x4E, 0xF7, 0x53, 0x54, 0x41, 0x54, 0x55, 0x45, 0x1F,
    0xF0, 0xF1, 0xFB, 0x37, 0x41, 0x49, 0x54, 0x0C, 0xF7, 0x49, 0x53, 0xF7,
    0x54, 0x48, 0x49, 0x53, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0xF7, 0x4B, 0x49,
    0x4E, 0x44, 0xF7, 0x4F, 0x46, 0xF7, 0x54, 0x4F, 0x4D, 0x42, 0x1F, 0xF0,
    0xF1, 0xFB, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0xF7, 0x29, 0x07, 0x4D, 0xF7,
    0x47, 0x45, 0x54, 0x54, 0x49, 0x4E, 0x47, 0xF7, 0x57, 0x4F, 0x52, 0x52,
    0x49, 0x45, 0x44, 0xF7, 0x4C, 0x45, 0x54, 0x07, 0x53, 0xF7, 0x48, 0x55,
    0x52, 0x52, 0x59, 0xF0, 0x54, 0x4F, 0xF7, 0x4C, 0x45, 0x41, 0x56, 0x45,
    0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7, 0x50, 0x4C, 0x41, 0x43, 0x45, 0xF7,
    0x4F, 0x4E, 0x43, 0x45, 0xF7, 0x41, 0x4E, 0x44, 0xF7, 0x46, 0x4F, 0x52,
    0xF7, 0x41, 0x4C, 0x4C, 0x0E, 0xF0, 0xF1, 0xFD
};

EvtScript TTYD64_jan_24_Script_PullLimb3 = {
    Set(LVar0, 2)
    Set(LVar1, 42)
    Set(MapFlag(3), 1)
    Exec(TTYD64_jan_24_Script_PullLimb)
    Unbind
    Return
    End
};

EvtScript TTYD64_jan_24_Script_PullLimb4 = {
    Set(LVar0, 3)
    Set(LVar1, 43)
    Set(MapFlag(4), 1)
    Exec(TTYD64_jan_24_Script_PullLimb)
    Unbind
    Return
    End
};

EvtScript TTYD64_jan_24_Script_PullLimb5 = {
    Set(LVar0, 4)
    Set(LVar1, 44)
    Set(MapFlag(5), 1)
    Exec(TTYD64_jan_24_Script_PullLimb)
    Unbind
    Return
    End
};

EvtScript TTYD64_jan_24_Script_PullLimb6 = {
    Set(LVar0, 5)
    Set(LVar1, 45)
    Set(MapFlag(6), 1)
    Exec(TTYD64_jan_24_Script_PullLimb)
    Unbind
    Return
    End
};

EvtScript TTYD64_jan_24_Script_PullLimb1 = {
    Set(LVar0, 0)
    Set(LVar1, 40)
    Set(MapFlag(1), 1)
    Exec(TTYD64_jan_24_Script_PullLimb)
    Unbind
    Return
    End
};

EvtScript TTYD64_jan_24_Script_PullLimb2 = {
    Set(LVar0, 1)
    Set(LVar1, 41)
    Set(MapFlag(2), 1)
    Exec(TTYD64_jan_24_Script_PullLimb)
    Unbind
    Return
    End
};

EvtScript TTYD64_jan_24_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_ScriptSpring), 75, 85, -7, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_jan_24_Script_ScriptedSpring_Entity_Spring)
    Return
    End
};

MapSettings TTYD64_jan_24_Header = {
    .main = &TTYD64_jan_24_Script_Main,
    .entryList = &TTYD64_jan_24_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_jan_24_GetTattle },
};

EvtScript TTYD64_jan_24_Script_NpcAI_802419B0_jan_01 = {
    Call(SetNpcFlagBits, -1, 64, 1)
    Call(jan_01_HoppingAI_Main, Ref(TTYD64_jan_24_AISettings_80241980_jan_01), 2)
    Return
    End
};

MobileAISettings TTYD64_jan_24_AISettings_80241980_jan_01 = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 10,
    .alertRadius = 150.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 5.0f,
    .chaseTurnRate = 70,
    .chaseUpdateInterval = 5,
    .chaseRadius = 200.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_jan_24_NpcSettings_802419EC_jan_01 = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = NULL,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 16,
    .actionFlags = 0,
};

EvtScript TTYD64_jan_24_Script_SetDarkRoom = {
    Thread
        Call(jan_11_DarkRoomUpdate)
    EndThread
    Return
    End
};

NpcGroupList TTYD64_jan_24_NpcGroup_jan24 = {
    { .npcCount = 1, .npcs = TTYD64_jan_24_NpcGroup_Fuzzy1, .battle = 0x1411, .stage = 9 },
    { .npcCount = 1, .npcs = TTYD64_jan_24_NpcGroup_Fuzzy2, .battle = 0x1411, .stage = 9 },
    {},
};

EvtScript TTYD64_jan_24_Script_InitNPC_Fuzzy = {
    Exec(TTYD64_jan_24_Script_NPC_BindAI)
    Return
    End
};

EntryList TTYD64_jan_24_EntryList = {
    { 75.0f, 208.0f, -7.0f, -270.0f },
};

MapConfig TTYD64_mapcfg_jan_24 = {
    .id = "jan_24",
    .settings = &TTYD64_jan_24_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_jan_24(void) {
    TTYD64_jan_24_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_jan_24_String_Tattle);
}
