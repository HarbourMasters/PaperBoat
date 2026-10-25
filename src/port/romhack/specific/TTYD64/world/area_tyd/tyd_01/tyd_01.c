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

API_CALLABLE(kmr_05_FlyingAI_Main);

extern EvtScript TTYD64_tyd_01_Script_Foliage_ShakeTree;
extern EvtScript TTYD64_tyd_01_Script_EnterVerticalPipe;
extern EvtScript TTYD64_tyd_01_Script_ExitVerticalPipe;
extern NpcData TTYD64_tyd_01_NpcGroup_Goomba[];
extern NpcData TTYD64_tyd_01_NpcGroup_SpikedGoomba[];
extern NpcData TTYD64_tyd_01_NpcGroup_Paragoomba[];
extern EvtScript TTYD64_tyd_01_Script_Cane;
extern EvtScript TTYD64_tyd_01_Script_SetupTexturePan;
extern EvtScript TTYD64_tyd_01_Script_Main;
extern EvtScript TTYD64_tyd_01_Script_MakeEntities;
extern EvtScript TTYD64_tyd_01_Script_TexturePan_Update;
extern u8 TTYD64_tyd_01_String_Tattle[];
extern EvtScript TTYD64_tyd_01_Script_NpcAI_80241B74_kmr_05;
extern EvtScript TTYD64_tyd_01_Script_CreateExitTriggers;
extern EvtScript TTYD64_tyd_01_Script_EnterMap;
extern EvtScript TTYD64_tyd_01_Script_Exit1;
extern EvtScript TTYD64_tyd_01_Script_Exit0;
extern EvtScript TTYD64_tyd_01_Script_Exit2;
extern EvtScript TTYD64_tyd_01_Script_BindFoliage;
extern MapSettings TTYD64_tyd_01_Header;
extern EvtScript TTYD64_tyd_01_Script_SetupMusic;
extern NpcGroupList TTYD64_tyd_01_NpcGroupList_tyd01;
extern EntryList TTYD64_tyd_01_EntryList;
extern MobileAISettings TTYD64_tyd_01_AISettings_80241B44_kmr_05;
extern MobileAISettings TTYD64_tyd_01_AISettings_802417F0;
extern EvtScript TTYD64_tyd_01_Script_GoToMap_Exit2;
extern EvtScript TTYD64_tyd_01_Script_GoToMap_Exit1;
extern EvtScript TTYD64_tyd_01_Script_GoToMap_Exit0;
s32 TTYD64_tyd_01_Function_Init(void);
extern NpcSettings TTYD64_tyd_01_NpcSettings_80241840;
extern NpcSettings TTYD64_tyd_01_NpcSettings_80241BE4_kmr_05;
extern EvtScript TTYD64_tyd_01_Script_NpcAI_80241820;
extern Bytecode TTYD64_tyd_01_ShakeTreeData_tree1[];
extern BombTrigger TTYD64_tyd_01_TriggerCoord_tree1;
extern s32 TTYD64_tyd_01_FoliageFXPos_tree1[];
extern s32 TTYD64_tyd_01_TrunkModels_tree1[];
extern s32 TTYD64_tyd_01_LeafModels_tree1[];

// clang-format off
static s32 TTYD64_tyd_01_GetTattleMsg;

static s32 TTYD64_tyd_01_GetTattle(void) {
    return TTYD64_tyd_01_GetTattleMsg;
}

EvtScript TTYD64_tyd_01_Script_Foliage_ShakeTree = {
    SetTimescale(Float(2.0))
    UseBuf(LVar0)
    BufRead4(LVar1, LVar2, LVar3, LVar4)
    BufRead1(LVar5)
    Call(GetPlayerPos, LVar6, LVarF, LVar8)
    Call(PlaySound, 357)
    Call(PlaySound, 358)
    Thread
        Set(LFlag0, 0)
        IfNe(LVar1, 0)
            Wait(1)
            Loop(5)
                UseBuf(LVar1)
                BufRead1(LVar2)
                Loop(LVar2)
                    BufRead1(LVar3)
                    Call(TTYD64_tp_TransformFoliage, LVar3, Float(0.099609375), Float(0.2001953125), LVarF, 0)
                    IfEq(LFlag0, 0)
                        Set(LFlag0, 1)
                        Call(PlaySoundAtModel, LVar3, 358, 0)
                    EndIf
                EndLoop
                Wait(1)
                UseBuf(LVar1)
                BufRead1(LVar2)
                Loop(LVar2)
                    BufRead1(LVar3)
                    Call(TTYD64_tp_TransformFoliage, LVar3, Float(0.099609375), Float(-0.2001953125), LVarF, 0)
                EndLoop
                Wait(1)
            EndLoop
            UseBuf(LVar1)
            BufRead1(LVar2)
            Loop(LVar2)
                BufRead1(LVar3)
                Call(TranslateModel, LVar3, 0, 0, 0)
            EndLoop
            Wait(1)
        EndIf
    EndThread
    Thread
        Set(LFlag0, 0)
        IfNe(LVar2, 0)
            Loop(5)
                UseBuf(LVar2)
                BufRead1(LVar3)
                Loop(LVar3)
                    BufRead1(LVar4)
                    Call(TTYD64_tp_TransformFoliage, LVar4, Float(0.099609375), Float(0.2001953125), LVarF, 0)
                    IfEq(LFlag0, 0)
                        Set(LFlag0, 1)
                        Call(PlaySoundAtModel, LVar4, 357, 0)
                    EndIf
                EndLoop
                Wait(1)
                UseBuf(LVar2)
                BufRead1(LVar3)
                Loop(LVar3)
                    BufRead1(LVar4)
                    Call(TTYD64_tp_TransformFoliage, LVar4, Float(0.099609375), Float(-0.2001953125), LVarF, 0)
                EndLoop
                Wait(1)
            EndLoop
            UseBuf(LVar2)
            BufRead1(LVar3)
            Loop(LVar3)
                BufRead1(LVar4)
                Call(TranslateModel, LVar4, 0, 0, 0)
            EndLoop
            Wait(1)
        EndIf
    EndThread
    Thread
        IfNe(LVar3, 0)
            UseBuf(LVar3)
            BufRead1(LVar4)
            Loop(LVar4)
                BufRead1(LVar5)
                BufRead3(LVar6, LVar7, LVar8)
                BufRead3(LVar9, LVarA, LVarB)
                IfEq(LVarB, 0)
                    Call(DropItemEntity, LVar5, LVar6, LVar7, LVar8, LVar9, LVarA)
                Else
                    Call(GetValueByRef, LVarB, LVarC)
                    IfEq(LVarC, 0)
                        Call(SetValueByRef, LVarB, 1)
                        Call(DropItemEntity, LVar5, LVar6, LVar7, LVar8, LVar9, LVarA)
                    EndIf
                EndIf
            EndLoop
        EndIf
    EndThread
    Thread
        IfNe(LVar4, 0)
            UseBuf(LVar4)
            BufRead1(LVar5)
            Loop(LVar5)
                BufRead3(LVar6, LVar7, LVar8)
                Call(PlayEffect_impl, 20, 0, LVar6, LVar7, LVar8, 100, 0, 0, 0, 0, 0, 0, 0, 0)
            EndLoop
        EndIf
    EndThread
    IfNe(LVar5, 0)
        ExecWait(LVar5)
    EndIf
    Wait(15)
    Return
    End
};

EvtScript TTYD64_tyd_01_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_tyd_01_Script_ExitVerticalPipe = {
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

NpcData TTYD64_tyd_01_NpcGroup_Goomba[] = {
    {
        .id = 0,
        .settings = &TTYD64_tyd_01_NpcSettings_80241840,
        .pos = { -336.0f, 0.0f, 58.0f },
        .flags = 0x00002C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 138, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 26213, 2, 19660 }, { 9830, 22936, 2, 16383 }, { 16383, 19660, 2, 16383 }, { 26213, 16383, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = -336, .centerPos.y = 0, .centerPos.z = 58, .wanderSize.x = 50, .wanderSize.z = 20, .moveSpeedOverride = -32767, .wanderShape = 1, .detectPos.x = -336, .detectPos.y = 0, .detectPos.z = 58, .detectSize.x = 250, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00260001, .walk = 0x00260002, .run = 0x00260003, .chase = 0x00260003, .anim_4 = 0x00260000, .anim_5 = 0x00260000, .death = 0x00260005, .hit = 0x00260005, .anim_8 = 0x00260000, .anim_9 = 0x00260000, .anim_A = 0x00260000, .anim_B = 0x00260000, .anim_C = 0x00260000, .anim_D = 0x00260000, .anim_E = 0x00260000, .anim_F = 0x00260000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_tyd_01_NpcGroup_SpikedGoomba[] = {
    {
        .id = 2,
        .settings = &TTYD64_tyd_01_NpcSettings_80241840,
        .pos = { 156.0f, 0.0f, 89.0f },
        .flags = 0x00002C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 138, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 156, .centerPos.y = 0, .centerPos.z = 89, .wanderSize.x = 50, .wanderSize.z = 20, .moveSpeedOverride = -32767, .wanderShape = 1, .detectPos.x = 156, .detectPos.y = 0, .detectPos.z = 89, .detectSize.x = 250, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00270001, .walk = 0x00270002, .run = 0x00270003, .chase = 0x00270003, .anim_4 = 0x00270000, .anim_5 = 0x00270000, .death = 0x00270006, .hit = 0x00270006, .anim_8 = 0x00270000, .anim_9 = 0x00270000, .anim_A = 0x00270000, .anim_B = 0x00270000, .anim_C = 0x00270000, .anim_D = 0x00270000, .anim_E = 0x00270000, .anim_F = 0x00270000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_tyd_01_NpcGroup_Paragoomba[] = {
    {
        .id = 1,
        .settings = &TTYD64_tyd_01_NpcSettings_80241BE4_kmr_05,
        .pos = { -82.0f, 42.0f, 0.0f },
        .flags = 0x00000400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 138, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = -82, .centerPos.y = 42, .centerPos.z = 0, .wanderSize.x = 50, .wanderSize.z = 20, .moveSpeedOverride = -32767, .wanderShape = 1, .detectPos.x = -82, .detectPos.y = 42, .detectPos.z = 0, .detectSize.x = 250, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00280001, .walk = 0x00280001, .run = 0x00280004, .chase = 0x00280004, .anim_4 = 0x00280000, .anim_5 = 0x00280000, .death = 0x00280006, .hit = 0x00280006, .anim_8 = 0x00280000, .anim_9 = 0x00280000, .anim_A = 0x00280000, .anim_B = 0x00280000, .anim_C = 0x00280000, .anim_D = 0x00280000, .anim_E = 0x00280000, .anim_F = 0x00280000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_tyd_01_Script_Cane = {
    Call(MakeLerp, 0, -35, 1, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateModel, 31, 0, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Add(MapVar(0), 1)
    IfEq(MapVar(0), 10)
        Call(MakeItemEntity, 406, 550, 0, -118, 4, 0)
    EndIf
    Call(MakeLerp, -35, 0, 5, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateModel, 31, 0, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_01_Script_SetupTexturePan = {
    Call(SetTexPanner, 9, 0)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 16384)
        Set(LVar2, 0)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 10)
        Set(LVar6, 0)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_tyd_01_Script_TexturePan_Update)
    EndThread
    Return
    End
};

EvtScript TTYD64_tyd_01_Script_Main = {
    Set(GameByte(425), 33)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_tyd_01_Script_SetupMusic)
    Exec(TTYD64_tyd_01_Script_SetupTexturePan)
    Exec(TTYD64_tyd_01_Script_MakeEntities)
    Exec(TTYD64_tyd_01_Script_EnterMap)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_tyd_01_NpcGroupList_tyd01)
    Set(LVarA, (Bytecode) TTYD64_tyd_01_Script_CreateExitTriggers)
    Exec(TTYD64_tyd_01_Script_EnterVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tyd_01_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_RedBlock), -313, 54, -130, 0, 274, 0x80000000)
    Call(AssignBlockFlag, GameFlag(4721))
    Call(MakeEntity, Ref(Entity_MulticoinBlock), 310, 54, -130, 0, 0x80000000)
    Call(AssignBlockFlag, GameFlag(4722))
    Call(MakeEntity, Ref(Entity_BrickBlock), 310, 175, -130, 0, 0x80000000)
    Return
    End
};

EvtScript TTYD64_tyd_01_Script_TexturePan_Update = {
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

u8 TTYD64_tyd_01_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x37, 0x48, 0x41, 0x54, 0xF7, 0x41, 0xF7, 0x42,
    0x45, 0x41, 0x55, 0x54, 0x49, 0x46, 0x55, 0x4C, 0xF7, 0x46, 0x4C, 0x4F,
    0x57, 0x45, 0x52, 0xF7, 0x46, 0x49, 0x45, 0x4C, 0x44, 0x0C, 0xF0, 0x29,
    0xF7, 0x57, 0x4F, 0x4E, 0x44, 0x45, 0x52, 0xF7, 0x57, 0x48, 0x45, 0x52,
    0x45, 0xF7, 0x45, 0x58, 0x41, 0x43, 0x54, 0x4C, 0x59, 0xF7, 0x41, 0x52,
    0x45, 0xF7, 0x57, 0x45, 0x1F, 0xF0, 0xF1, 0xFB, 0x24, 0x55, 0x45, 0xF7,
    0x54, 0x4F, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x54, 0x59, 0x50, 0x45, 0xF7,
    0x4F, 0x46, 0xF7, 0x46, 0x4C, 0x4F, 0x57, 0x45, 0x52, 0x53, 0x0C, 0xF7,
    0x49, 0x54, 0xF0, 0x53, 0x45, 0x45, 0x4D, 0x53, 0xF7, 0x56, 0x45, 0x52,
    0x59, 0xF7, 0x46, 0x41, 0x52, 0xF7, 0x46, 0x52, 0x4F, 0x4D, 0xF7, 0x4F,
    0x55, 0x52, 0xF7, 0x48, 0x4F, 0x4D, 0x45, 0x53, 0x0E, 0xF1, 0xFD
};

EvtScript TTYD64_tyd_01_Script_NpcAI_80241B74_kmr_05 = {
    Call(SetSelfVar, 0, 0)
    Call(SetSelfVar, 5, -500)
    Call(SetSelfVar, 6, 21)
    Call(SetSelfVar, 1, 580)
    Call(kmr_05_FlyingAI_Main, Ref(TTYD64_tyd_01_AISettings_80241B44_kmr_05))
    Return
    End
};

EvtScript TTYD64_tyd_01_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_tyd_01_Script_Exit0, 128, 1, 1, 0)
    BindTrigger(TTYD64_tyd_01_Script_Exit1, 128, 2, 1, 0)
    BindTrigger(TTYD64_tyd_01_Script_Exit2, 128, 3, 1, 0)
    Return
    End
};

EvtScript TTYD64_tyd_01_Script_EnterMap = {
    Exec(TTYD64_tyd_01_Script_BindFoliage)
    Call(MakeItemEntity, 348, 310, 200, -130, 17, GameFlag(4713))
    BindTrigger(TTYD64_tyd_01_Script_Cane, 4096, 11, 1, 0)
    Return
    End
};

EvtScript TTYD64_tyd_01_Script_Exit1 = {
    SetGroup(27)
    Set(LVarA, 1)
    Set(LVarB, 2)
    Set(LVarC, (Bytecode) TTYD64_tyd_01_Script_GoToMap_Exit1)
    ExecWait(TTYD64_tyd_01_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tyd_01_Script_Exit0 = {
    SetGroup(27)
    Set(LVarA, 0)
    Set(LVarB, 1)
    Set(LVarC, (Bytecode) TTYD64_tyd_01_Script_GoToMap_Exit0)
    ExecWait(TTYD64_tyd_01_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tyd_01_Script_Exit2 = {
    SetGroup(27)
    Set(LVarA, 2)
    Set(LVarB, 3)
    Set(LVarC, (Bytecode) TTYD64_tyd_01_Script_GoToMap_Exit2)
    ExecWait(TTYD64_tyd_01_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tyd_01_Script_BindFoliage = {
    Set(LVar0, (Bytecode) TTYD64_tyd_01_ShakeTreeData_tree1)
    BindTrigger(TTYD64_tyd_01_Script_Foliage_ShakeTree, 4096, 19, 1, 0)
    BindTrigger(TTYD64_tyd_01_Script_Foliage_ShakeTree, 0x100000, Ref(TTYD64_tyd_01_TriggerCoord_tree1), 1, 0)
    Return
    End
};

MapSettings TTYD64_tyd_01_Header = {
    .main = TTYD64_tyd_01_Script_Main,
    .entryList = &TTYD64_tyd_01_EntryList,
    .entryCount = 3,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_tyd_01_GetTattle },
};

EvtScript TTYD64_tyd_01_Script_SetupMusic = {
    Call(SetMusic, 0, 167, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

NpcGroupList TTYD64_tyd_01_NpcGroupList_tyd01 = {
    { .npcCount = 1, .npcs = TTYD64_tyd_01_NpcGroup_Goomba, .battle = 0x3B01, .stage = 2 },
    { .npcCount = 1, .npcs = TTYD64_tyd_01_NpcGroup_Paragoomba, .battle = 0x3B02, .stage = 2 },
    { .npcCount = 1, .npcs = TTYD64_tyd_01_NpcGroup_SpikedGoomba, .battle = 0x3B03, .stage = 2 },
    {},
};

EntryList TTYD64_tyd_01_EntryList = {
    { -523.0f, 31.0f, -41.0f, 90.0f },
    { 132.0f, 31.0f, -134.0f, 90.0f },
    { 450.0f, 200.0f, -123.0f, -90.0f },
};

MobileAISettings TTYD64_tyd_01_AISettings_80241B44_kmr_05 = {
    .moveSpeed = 1.60000002f,
    .moveTime = 60,
    .waitTime = 30,
    .alertRadius = 80.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 5,
    .chaseSpeed = 2.20000005f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 15,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

MobileAISettings TTYD64_tyd_01_AISettings_802417F0 = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 130.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 2.5f,
    .chaseTurnRate = 180,
    .chaseUpdateInterval = 3,
    .chaseRadius = 150.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

EvtScript TTYD64_tyd_01_Script_GoToMap_Exit2 = {
    Call(GotoMap, (Bytecode) "tyd_01", 1)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_tyd_01_Script_GoToMap_Exit1 = {
    Call(GotoMap, (Bytecode) "tyd_01", 2)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_tyd_01_Script_GoToMap_Exit0 = {
    Call(GotoMap, (Bytecode) "nok_13", 3)
    Wait(100)
    Return
    End
};

s32 TTYD64_tyd_01_Function_Init(void) {
    sprintf(wMapTexName, "tst_tex");
    return false;
}

NpcSettings TTYD64_tyd_01_NpcSettings_80241840 = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 23,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_tyd_01_Script_NpcAI_80241820,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 5,
    .actionFlags = 0,
};

NpcSettings TTYD64_tyd_01_NpcSettings_80241BE4_kmr_05 = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 21,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_tyd_01_Script_NpcAI_80241B74_kmr_05,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 6,
    .actionFlags = 2,
};

EvtScript TTYD64_tyd_01_Script_NpcAI_80241820 = {
    Call(BasicAI_Main, Ref(TTYD64_tyd_01_AISettings_802417F0))
    Return
    End
};

Bytecode TTYD64_tyd_01_ShakeTreeData_tree1[] = {
    (Bytecode) TTYD64_tyd_01_TrunkModels_tree1, (Bytecode) TTYD64_tyd_01_LeafModels_tree1, 0, (Bytecode) TTYD64_tyd_01_FoliageFXPos_tree1, 0
};

BombTrigger TTYD64_tyd_01_TriggerCoord_tree1 = {
    .pos = { -441.0f, 0.0f, -130.0f },
    .diameter = 0.0f,
};

s32 TTYD64_tyd_01_FoliageFXPos_tree1[] = {
    1, -436, 125, -103
};

s32 TTYD64_tyd_01_TrunkModels_tree1[] = {
    1, 0
};

s32 TTYD64_tyd_01_LeafModels_tree1[] = {
    1, 1
};

MapConfig TTYD64_mapcfg_tyd_01 = {
    .id = "tyd_01",
    .settings = &TTYD64_tyd_01_Header,
    .bgName = "nok_bg",
    .init = TTYD64_tyd_01_Function_Init,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_tp_Install_tyd_01(void) {
    TTYD64_tyd_01_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_tyd_01_String_Tattle);
    Mod_RegisterWideEvtBuffer(
        "TTYD64", TTYD64_tyd_01_ShakeTreeData_tree1, ARRAY_COUNT(TTYD64_tyd_01_ShakeTreeData_tree1)
    );
}
