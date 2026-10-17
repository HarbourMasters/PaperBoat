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
#include "port/romhack/specific/TTYD64/newmaps/nm.h"

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(BasicAI_Main);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableModel);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerJump);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(ResetCam);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamTarget);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerJumpscale);
API_CALLABLE(SetSelfVar);
API_CALLABLE(SetTexPanner);
API_CALLABLE(ShowGotItem);
API_CALLABLE(ShowMessageAtScreenPos);
API_CALLABLE(UseExitHeading);
API_CALLABLE(jan_05_SpearGuyAI_Main);

extern EvtScript TTYD64_jan_26_Script_Main;
extern EvtScript TTYD64_jan_26_Script_DestroyRaven;
extern NpcData TTYD64_jan_26_NpcGroup_JungleGuy[];
extern NpcData TTYD64_jan_26_NpcGroup_MBush[];
extern EvtScript TTYD64_jan_26_Script_RespawnPlayer;
extern EvtScript TTYD64_jan_26_Script_SetupTexturePan;
extern u8 TTYD64_jan_26_String_Tattle[];
extern EvtScript TTYD64_jan_26_Script_Respawn_1;
extern EvtScript TTYD64_jan_26_Script_ScriptedSpring_Entity_Spring;
extern EvtScript TTYD64_jan_26_Script_Respawn_2;
extern EvtScript TTYD64_jan_26_Script_Respawn_3;
extern EvtScript TTYD64_jan_26_Script_Respawn_4;
extern EvtScript TTYD64_jan_26_Script_Respawn_5;
extern EvtScript TTYD64_jan_26_Script_TexturePan_Update;
extern EvtScript TTYD64_jan_26_Script_MakeEntities;
extern EvtScript TTYD64_jan_26_Script_ClearMapVar0;
extern EvtScript TTYD64_jan_26_Script_GetItem;
extern EvtScript TTYD64_jan_26_Script_NpcAI_80245240_jan_05;
extern EvtScript TTYD64_jan_26_Script_RespawnMain;
extern EvtScript TTYD64_jan_26_Script_ScriptedSpring_FollowCam;
extern EvtScript TTYD64_jan_26_Script_Exit0;
extern EvtScript TTYD64_jan_26_Script_DestroyRaven_1;
extern EvtScript TTYD64_jan_26_Script_DestroyRaven_2;
extern EvtScript TTYD64_jan_26_Script_Sign2;
extern MapSettings TTYD64_jan_26_Header;
extern EvtScript TTYD64_jan_26_Script_Entity_Shine1;
extern EvtScript TTYD64_jan_26_Script_SetupMusic;
extern MobileAISettings TTYD64_jan_26_AISettings_80245210_jan_05;
extern MobileAISettings TTYD64_jan_26_AISettings_802413D0_arn_02;
extern NpcSettings TTYD64_jan_26_NpcSettings_80241420_arn_02;
extern NpcSettings TTYD64_jan_26_NpcSettings_802452B0_jan_05;
extern EvtScript TTYD64_jan_26_Script_CreateExitTriggers;
extern AnimID TTYD64_jan_26_ExtraAnimationList_80245124_jan_05[];
extern EvtScript TTYD64_jan_26_Script_Sign1;
extern NpcGroupList TTYD64_jan_26_NpcGroupList_jan26;
extern u8 TTYD64_jan_26_String_ShieldDestroyed[];
extern u8 TTYD64_jan_26_String_Sign1[];
extern EntryList TTYD64_jan_26_EntryList;
extern EvtScript TTYD64_jan_26_Script_NpcAI_80241400_arn_02;
extern u8 TTYD64_jan_26_String_Sign2[];

// clang-format off
static s32 TTYD64_jan_26_GetTattleMsg;

static s32 TTYD64_jan_26_GetTattle(void) {
    return TTYD64_jan_26_GetTattleMsg;
}

EvtScript TTYD64_jan_26_Script_Main = {
    Set(GameByte(425), 36)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_jan_26_Script_MakeEntities)
    Exec(TTYD64_jan_26_Script_SetupMusic)
    Exec(TTYD64_jan_26_Script_SetupTexturePan)
    IfEq(GameFlag(5394), 1)
        Call(EnableGroup, 86, 0)
        Call(ModifyColliderFlags, 0, 10, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 30, 0x7FFFFE00)
        IfEq(GameFlag(5395), 0)
            BindTrigger(TTYD64_jan_26_Script_GetItem, 256, 20, 1, 0)
        EndIf
    Else
        BindTrigger(TTYD64_jan_26_Script_DestroyRaven_1, 4096, 10, 1, 0)
        BindTrigger(TTYD64_jan_26_Script_DestroyRaven_2, 4096, 30, 1, 0)
        BindTrigger(TTYD64_jan_26_Script_RespawnMain, 128, 37, 1, 0)
        BindTrigger(TTYD64_jan_26_Script_Respawn_1, 128, 32, 1, 0)
        BindTrigger(TTYD64_jan_26_Script_Respawn_2, 128, 33, 1, 0)
        BindTrigger(TTYD64_jan_26_Script_Respawn_3, 128, 34, 1, 0)
        BindTrigger(TTYD64_jan_26_Script_Respawn_4, 128, 35, 1, 0)
        BindTrigger(TTYD64_jan_26_Script_Respawn_5, 128, 36, 1, 0)
        BindTrigger(TTYD64_jan_26_Script_ClearMapVar0, 128, 40, 1, 0)
    EndIf
    BindTrigger(TTYD64_jan_26_Script_Sign1, 0x80000, 41, 1, 0)
    BindTrigger(TTYD64_jan_26_Script_Sign2, 256, 19, 1, 0)
    Call(ModifyColliderFlags, 3, 12, 4)
    Call(ModifyColliderFlags, 3, 14, 4)
    Call(ModifyColliderFlags, 3, 24, 4)
    Call(ModifyColliderFlags, 0, 12, 0x80000)
    Call(ModifyColliderFlags, 0, 14, 0x80000)
    Call(ModifyColliderFlags, 0, 24, 0x80000)
    Call(MakeItemEntity, 385, 0, 13, -411, 17, GameFlag(5395))
    Call(MakeNpcs, 0, (Bytecode) TTYD64_jan_26_NpcGroupList_jan26)
    Set(MapVar(1), LVar0)
    Set(LVar0, (Bytecode) TTYD64_jan_26_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

EvtScript TTYD64_jan_26_Script_DestroyRaven = {
    SetGroup(0)
    SuspendGroup(2)
    Set(LVar3, LVar0)
    Set(LVar4, LVar1)
    Call(DisablePlayerInput, 1)
    Call(GetModelCenter, LVar3)
    Sub(LVar1, 1)
    Add(LVar2, 17)
    Call(PlayEffect_impl, 36, 1, LVar0, LVar1, LVar2, Float(1.2001953125), 20, 0, 0, 0, 0, 0, 0, 0)
    Wait(2)
    Call(GetModelCenter, LVar3)
    Sub(LVar1, 15)
    Call(PlayEffect_impl, 34, 4, LVar0, LVar1, LVar2, 30, 20, 5, 150, 0, 0, 0, 0, 0)
    Call(PlaySound, 8273)
    Wait(10)
    Call(EnableModel, LVar3, 0)
    Wait(10)
    Set(LVar0, MapFlag(0))
    Add(LVar0, MapFlag(1))
    IfGe(LVar0, 2)
        Call(ShowMessageAtScreenPos, (Bytecode) TTYD64_jan_26_String_ShieldDestroyed, 160, 40)
        Set(GameFlag(5394), 1)
        Call(EnableModel, 83, 0)
        BindTrigger(TTYD64_jan_26_Script_GetItem, 256, 20, 1, 0)
    EndIf
    ResumeGroup(2)
    Call(ModifyColliderFlags, 0, LVar4, 0x7FFFFE00)
    Call(DisablePlayerInput, 0)
    Return
    End
};

NpcData TTYD64_jan_26_NpcGroup_JungleGuy[] = {
    {
        .id = 0,
        .settings = &TTYD64_jan_26_NpcSettings_802452B0_jan_05,
        .pos = { 275.0f, 0.0f, -127.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 143, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 275, .centerPos.y = 0, .centerPos.z = -127, .wanderSize.x = 20, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 310, .detectPos.y = 0, .detectPos.z = -127, .detectSize.x = 82, .detectSize.z = 100, .detectShape = 1, .isFlying = 1 } },
        .animations = { .idle = 0x00420003, .walk = 0x00420005, .run = 0x00420006, .chase = 0x00420006, .anim_4 = 0x00420000, .anim_5 = 0x00420000, .death = 0x00420007, .hit = 0x00420007, .anim_8 = 0x00420000, .anim_9 = 0x00420000, .anim_A = 0x00420000, .anim_B = 0x00420000, .anim_C = 0x00420000, .anim_D = 0x00420000, .anim_E = 0x00420000, .anim_F = 0x00420000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_jan_26_ExtraAnimationList_80245124_jan_05,
        .tattle = 0,
    },
};

NpcData TTYD64_jan_26_NpcGroup_MBush[] = {
    {
        .id = 1,
        .settings = &TTYD64_jan_26_NpcSettings_80241420_arn_02,
        .pos = { 356.0f, 0.0f, 16.0f },
        .flags = 0x00000400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 32, .itemDrops = { { 141, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 356, .centerPos.y = 0, .centerPos.z = 16, .wanderSize.x = 20, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 356, .detectPos.y = 0, .detectPos.z = 16, .detectSize.x = 80, .detectSize.z = 82, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x00450002, .walk = 0x00450004, .run = 0x00450005, .chase = 0x00450005, .anim_4 = 0x00450002, .anim_5 = 0x00450002, .death = 0x00450007, .hit = 0x00450007, .anim_8 = 0x00450002, .anim_9 = 0x00450002, .anim_A = 0x00450002, .anim_B = 0x00450002, .anim_C = 0x00450002, .anim_D = 0x00450002, .anim_E = 0x00450002, .anim_F = 0x00450002 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_jan_26_Script_RespawnPlayer = {
    Call(DisablePlayerInput, 1)
    Call(PlaySound, 217)
    Call(TTYD64_SetScreenOverlayColor, SCREEN_LAYER_FRONT, 0xD0, 0xD0, 0xD0)
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(255.0))
    ExecWait(TTYD64_Script_FadeScreenOut)
    Call(SetNpcPos, -4, -241, -20, 366)
    Wait(1)
    Call(ResetCam, 0, 100)
    Wait(20)
    Call(PlaySound, 218)
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(5.0))
    ExecWait(TTYD64_Script_FadeScreenIn)
    Call(DisablePlayerInput, 0)
    Call(TTYD64_SetScreenOverlayColor, SCREEN_LAYER_FRONT, 0, 0, 0)
    Set(MapVar(0), 0)
    Return
    End
};

EvtScript TTYD64_jan_26_Script_SetupTexturePan = {
    Call(SetTexPanner, 9, 1)
    Call(SetTexPanner, 83, 1)
    Thread
        Set(LVar0, 1)
        Set(LVar1, -80)
        Set(LVar2, 140)
        Set(LVar3, 80)
        Set(LVar4, -100)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_jan_26_Script_TexturePan_Update)
    EndThread
    Return
    End
};

u8 TTYD64_jan_26_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x34, 0x48, 0x45, 0x52, 0x45, 0x07, 0x53, 0xF7,
    0x41, 0xF7, 0x4C, 0x4F, 0x54, 0xF7, 0x4F, 0x46, 0xF7, 0x52, 0x41, 0x56,
    0x45, 0x4E, 0x53, 0xF7, 0x53, 0x54, 0x55, 0x46, 0x46, 0xF0, 0x41, 0x52,
    0x4F, 0x55, 0x4E, 0x44, 0xF7, 0x48, 0x45, 0x52, 0x45, 0x0E, 0xF0, 0xF1,
    0xFB, 0x29, 0x53, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7, 0x53, 0x4F, 0x4D,
    0x45, 0xF7, 0x4B, 0x49, 0x4E, 0x44, 0xF7, 0x4F, 0x46, 0xF0, 0x56, 0x45,
    0x4E, 0x45, 0x52, 0x41, 0x54, 0x49, 0x4F, 0x4E, 0xF7, 0x41, 0x52, 0x45,
    0x41, 0x1F, 0xF0, 0xF1, 0xFB, 0x2C, 0x4F, 0x4F, 0x4B, 0x53, 0xF7, 0x4C,
    0x49, 0x4B, 0x45, 0xF7, 0x54, 0x48, 0x45, 0x52, 0x45, 0x07, 0x53, 0xF7,
    0x41, 0xF7, 0x53, 0x49, 0x47, 0x4E, 0xF0, 0x4E, 0x45, 0x58, 0x54, 0xF7,
    0x54, 0x4F, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x42, 0x49, 0x47, 0xF7, 0x52,
    0x41, 0x56, 0x45, 0x4E, 0xF7, 0x41, 0x4C, 0x54, 0x41, 0x52, 0x0C, 0xF0,
    0x57, 0x45, 0xF7, 0x53, 0x48, 0x4F, 0x55, 0x4C, 0x44, 0xF7, 0x52, 0x45,
    0x41, 0x44, 0xF7, 0x57, 0x48, 0x41, 0x54, 0xF7, 0x49, 0x54, 0xF7, 0x53,
    0x41, 0x59, 0x0E, 0xF0, 0xF1, 0xFB, 0x2D, 0x41, 0x59, 0x42, 0x45, 0xF7,
    0x54, 0x48, 0x45, 0x52, 0x45, 0x07, 0x53, 0xF7, 0x41, 0xF7, 0x54, 0x49,
    0x50, 0xF7, 0x41, 0x42, 0x4F, 0x55, 0x54, 0xF7, 0x57, 0x48, 0x41, 0x54,
    0xF0, 0x57, 0x45, 0xF7, 0x4E, 0x45, 0x45, 0x44, 0xF7, 0x54, 0x4F, 0xF7,
    0x45, 0x58, 0x41, 0x43, 0x54, 0x4C, 0x59, 0xF7, 0x44, 0x4F, 0xF7, 0x48,
    0x45, 0x52, 0x45, 0x0E, 0xF0, 0xF1, 0xFD
};

EvtScript TTYD64_jan_26_Script_Respawn_1 = {
    Call(TTYD64_ReadField, TTYD64_F_GMESSAGEPRINTERS_4F8_1U, LVar0)
    IfEq(LVar0, 5)
        Call(TTYD64_WriteField, TTYD64_F_GMESSAGEPRINTERS_4F8_1U, 3)
        Call(TTYD64_ResetFFWD)
    EndIf
    Set(LVar0, GameFlag(5394))
    Add(LVar0, MapFlag(0))
    IfGt(LVar0, 0)
        Unbind
        Return
    EndIf
    Set(MapVar(0), 1)
    Return
    End
};

EvtScript TTYD64_jan_26_Script_ScriptedSpring_Entity_Spring = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerActionState, 6)
    Wait(1)
    ExecGetTID(TTYD64_jan_26_Script_ScriptedSpring_FollowCam, LVarA)
    Call(SetPlayerJumpscale, Float(0.7001953125))
    Call(PlayerJump, 456, 90, -4, 30)
    KillThread(LVarA)
    Call(SetPlayerActionState, 0)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_jan_26_Script_Respawn_2 = {
    Set(LVar0, GameFlag(5394))
    Add(LVar0, MapFlag(0))
    IfGt(LVar0, 0)
        Unbind
        Return
    EndIf
    Switch(MapVar(0))
    CaseOrEq(1)
    CaseOrEq(2)
        Set(MapVar(0), 2)
        EndCaseGroup
    CaseDefault
        ExecWait(TTYD64_jan_26_Script_RespawnPlayer)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_jan_26_Script_Respawn_3 = {
    Set(LVar0, GameFlag(5394))
    Add(LVar0, MapFlag(0))
    IfGt(LVar0, 0)
        Unbind
        Return
    EndIf
    Switch(MapVar(0))
    CaseOrEq(2)
    CaseOrEq(3)
        Set(MapVar(0), 3)
        EndCaseGroup
    CaseDefault
        ExecWait(TTYD64_jan_26_Script_RespawnPlayer)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_jan_26_Script_Respawn_4 = {
    Set(LVar0, GameFlag(5394))
    Add(LVar0, MapFlag(0))
    IfGt(LVar0, 0)
        Unbind
        Return
    EndIf
    Switch(MapVar(0))
    CaseOrEq(3)
    CaseOrEq(4)
        Set(MapVar(0), 4)
        EndCaseGroup
    CaseDefault
        ExecWait(TTYD64_jan_26_Script_RespawnPlayer)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_jan_26_Script_Respawn_5 = {
    Set(LVar0, GameFlag(5394))
    Add(LVar0, MapFlag(0))
    IfGt(LVar0, 0)
        Unbind
        Return
    EndIf
    Switch(MapVar(0))
    CaseOrEq(4)
    CaseOrEq(5)
        Set(MapVar(0), 5)
        EndCaseGroup
    CaseDefault
        ExecWait(TTYD64_jan_26_Script_RespawnPlayer)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_jan_26_Script_TexturePan_Update = {
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

EvtScript TTYD64_jan_26_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_ScriptSpring), 447, 0, 83, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_jan_26_Script_ScriptedSpring_Entity_Spring)
    Call(MakeEntity, Ref(Entity_SuperBlock), 463, 146, -94, 0, 0x80000000)
    Set(MapVar(2), LVar0)
    Call(AssignBlockFlag, GameFlag(5437))
    Call(AssignScript, (Bytecode) TTYD64_jan_26_Script_Entity_Shine1)
    Return
    End
};

EvtScript TTYD64_jan_26_Script_ClearMapVar0 = {
    Set(MapVar(0), 0)
    Call(TTYD64_ReadField, TTYD64_F_GMESSAGEPRINTERS_4F8_1U, LVar0)
    IfEq(LVar0, 5)
        Call(TTYD64_WriteField, TTYD64_F_GMESSAGEPRINTERS_4F8_1U, 3)
        Call(TTYD64_ResetFFWD)
    EndIf
    Return
    End
};

EvtScript TTYD64_jan_26_Script_GetItem = {
    Call(DisablePlayerInput, 1)
    Call(TTYD64_nm_AddBadge, 385, 0)
    Call(RemoveItemEntity, MapVar(1))
    Call(ShowGotItem, 385, 1, 0)
    Set(GameFlag(5395), 1)
    Unbind
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_jan_26_Script_NpcAI_80245240_jan_05 = {
    Call(SetSelfVar, 0, 0)
    Call(SetSelfVar, 1, 5)
    Call(SetSelfVar, 2, 12)
    Call(SetSelfVar, 3, 9)
    Call(jan_05_SpearGuyAI_Main, Ref(TTYD64_jan_26_AISettings_80245210_jan_05))
    Return
    End
};

EvtScript TTYD64_jan_26_Script_RespawnMain = {
    Set(LVar0, GameFlag(5394))
    Add(LVar0, MapFlag(0))
    IfGt(LVar0, 0)
        Unbind
        Return
    EndIf
    ExecWait(TTYD64_jan_26_Script_RespawnPlayer)
    Return
    End
};

EvtScript TTYD64_jan_26_Script_ScriptedSpring_FollowCam = {
    Loop(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetCamTarget, 0, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_jan_26_Script_Exit0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "jan_10", 1)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_jan_26_Script_DestroyRaven_1 = {
    Set(LVar0, 84)
    Set(LVar1, 10)
    Set(MapFlag(0), 1)
    ExecWait(TTYD64_jan_26_Script_DestroyRaven)
    Return
    End
};

EvtScript TTYD64_jan_26_Script_DestroyRaven_2 = {
    Set(LVar0, 85)
    Set(LVar1, 30)
    Set(MapFlag(1), 1)
    ExecWait(TTYD64_jan_26_Script_DestroyRaven)
    Return
    End
};

EvtScript TTYD64_jan_26_Script_Sign2 = {
    Call(DisablePlayerInput, 1)
    Call(ShowMessageAtScreenPos, (Bytecode) TTYD64_jan_26_String_Sign2, 160, 40)
    Call(DisablePlayerInput, 0)
    Return
    End
};

MapSettings TTYD64_jan_26_Header = {
    .main = &TTYD64_jan_26_Script_Main,
    .entryList = &TTYD64_jan_26_EntryList,
    .entryCount = 2,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_jan_26_GetTattle },
};

EvtScript TTYD64_jan_26_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(2))
    SetConst(LVar1, GameFlag(5437))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_jan_26_Script_SetupMusic = {
    Call(SetMusic, 0, 36, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

MobileAISettings TTYD64_jan_26_AISettings_80245210_jan_05 = {
    .moveSpeed = 1.70000005f,
    .moveTime = 100,
    .waitTime = 1,
    .alertRadius = 100.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 3.5f,
    .chaseTurnRate = 20,
    .chaseUpdateInterval = 1,
    .chaseRadius = 120.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

MobileAISettings TTYD64_jan_26_AISettings_802413D0_arn_02 = {
    .moveSpeed = 1.79999995f,
    .moveTime = 40,
    .waitTime = 15,
    .alertRadius = 150.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 2,
    .chaseSpeed = 3.29999995f,
    .chaseTurnRate = 70,
    .chaseUpdateInterval = 1,
    .chaseRadius = 180.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_jan_26_NpcSettings_80241420_arn_02 = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 23,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = &TTYD64_jan_26_Script_NpcAI_80241400_arn_02,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 12,
    .actionFlags = 0,
};

NpcSettings TTYD64_jan_26_NpcSettings_802452B0_jan_05 = {
    .defaultAnim = 0x00000000,
    .height = 23,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = &TTYD64_jan_26_Script_NpcAI_80245240_jan_05,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 16,
    .actionFlags = 0,
};

EvtScript TTYD64_jan_26_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_jan_26_Script_Exit0, 0x80000, 3, 1, 0)
    Return
    End
};

AnimID TTYD64_jan_26_ExtraAnimationList_80245124_jan_05[] = {
    0x00420000, 0x00420003, 0x00420005, 0x00420006, 0x00420007, 0x0042000F, 0x00420010, 0x0042001A, 0x0042001B, -1
};

EvtScript TTYD64_jan_26_Script_Sign1 = {
    Call(ShowMessageAtScreenPos, (Bytecode) TTYD64_jan_26_String_Sign1, 160, 40)
    Return
    End
};

NpcGroupList TTYD64_jan_26_NpcGroupList_jan26 = {
    { .npcCount = 1, .npcs = TTYD64_jan_26_NpcGroup_JungleGuy, .battle = 0x1400, .stage = 4 },
    { .npcCount = 1, .npcs = TTYD64_jan_26_NpcGroup_MBush, .battle = 0x140E, .stage = 4 },
    {},
};

u8 TTYD64_jan_26_String_ShieldDestroyed[] = {
    0xFC, 0x06, 0xFF, 0x09, 0x34, 0x48, 0x45, 0xF7, 0x53, 0x45, 0x41, 0x4C,
    0xF7, 0x4F, 0x4E, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x53, 0x54, 0x41, 0x54,
    0x55, 0x45, 0xF7, 0x4F, 0x50, 0x45, 0x4E, 0x45, 0x44, 0x0E, 0xF1, 0xFD
};

u8 TTYD64_jan_26_String_Sign1[] = {
    0xFC, 0x06, 0xFF, 0x09, 0x34, 0x48, 0x45, 0xF7, 0x50, 0x49, 0x4C, 0x4C,
    0x41, 0x52, 0x53, 0xF7, 0x41, 0x52, 0x45, 0xF7, 0x54, 0x48, 0x45, 0xF7,
    0x57, 0x41, 0x59, 0x0E, 0xFF, 0x07, 0xF1, 0xFD
};

EntryList TTYD64_jan_26_EntryList = {
    { 0.0f, -20.0f, 471.0f, 0.0f },
    { 0.0f, 0.0f, -290.0f, -180.0f },
};

EvtScript TTYD64_jan_26_Script_NpcAI_80241400_arn_02 = {
    Call(BasicAI_Main, Ref(TTYD64_jan_26_AISettings_802413D0_arn_02))
    Return
    End
};

u8 TTYD64_jan_26_String_Sign2[] = {
    0xFC, 0x06, 0xFF, 0x09, 0x33, 0x45, 0x45, 0x4B, 0xF7, 0x54, 0x48, 0x45,
    0xF7, 0x52, 0x41, 0x56, 0x45, 0x4E, 0x53, 0x0E, 0xF1, 0xFD
};

MapConfig TTYD64_mapcfg_jan_26 = {
    .id = "jan_26",
    .settings = &TTYD64_jan_26_Header,
    .bgName = "yos_bg",
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_jan_26(void) {
    TTYD64_nm_BindMessage(TTYD64_jan_26_Script_DestroyRaven, TTYD64_jan_26_String_ShieldDestroyed);
    TTYD64_nm_BindMessage(TTYD64_jan_26_Script_Sign2, TTYD64_jan_26_String_Sign2);
    TTYD64_nm_BindMessage(TTYD64_jan_26_Script_Sign1, TTYD64_jan_26_String_Sign1);
    TTYD64_jan_26_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_jan_26_String_Tattle);
}
