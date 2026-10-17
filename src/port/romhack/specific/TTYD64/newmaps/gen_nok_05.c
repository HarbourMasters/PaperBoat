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
API_CALLABLE(BindNpcIdle);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableModel);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(GetPlayerActionState);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(NpcJump0);
API_CALLABLE(PlaySoundAtNpc);
API_CALLABLE(ResetCam);
API_CALLABLE(ResetPartnerTetherDistance);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcJumpscale);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerFlagBits);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(TeleportPartnerToPlayer);
API_CALLABLE(UseExitHeading);
API_CALLABLE(WaitForCam);

extern EvtScript TTYD64_nok_05_Script_GoToNewMap;
extern EvtScript TTYD64_nok_05_Script_Idle_FuzzyPath;
extern EvtScript TTYD64_nok_05_Script_UpdateModelsAndCollisions;
extern NpcData TTYD64_nok_05_NpcGroup_Fuzzy[];
extern EvtScript TTYD64_nok_05_Script_Fuzzy_UpdateVisibility;
extern EvtScript TTYD64_nok_05_Script_DisableAllModelsAndCols;
extern EvtScript TTYD64_nok_05_Script_Main;
extern EvtScript TTYD64_nok_05_Script_MakeEntities;
extern s32 TTYD64_nok_05_VectorList_Path4[];
extern EvtScript TTYD64_nok_05_Script_CreateExitTriggers;
extern s32 TTYD64_nok_05_VectorList_Path3[];
extern s32 TTYD64_nok_05_VectorList_Path1[];
extern s32 TTYD64_nok_05_VectorList_Path2[];
extern EntryList TTYD64_nok_05_EntryList;
extern s32 TTYD64_nok_05_VectorList_Path_Final1[];
extern s32 TTYD64_nok_05_VectorList_Path_Final2[];
extern EvtScript TTYD64_nok_05_Script_Exit1;
extern EvtScript TTYD64_nok_05_Script_Exit0;
extern EvtScript TTYD64_nok_05_Script_Exit5;
extern EvtScript TTYD64_nok_05_Script_Exit4;
extern EvtScript TTYD64_nok_05_Script_Exit3;
extern EvtScript TTYD64_nok_05_Script_Exit2;
extern MapSettings TTYD64_nok_05_Header;
extern u8 TTYD64_nok_05_String_Tattle[];
extern EvtScript TTYD64_nok_05_Script_Entity_Shine1;
extern EvtScript TTYD64_nok_05_Script_SetupMusic;
extern s32 TTYD64_nok_05_VectorList_Path0_2[];
extern NpcSettings TTYD64_nok_05_NpcSettings_Fuzzy;
extern EvtScript TTYD64_nok_05_Script_Init_Fuzzy;
extern s32 TTYD64_nok_05_VectorList_Path0_0[];
extern s32 TTYD64_nok_05_VectorList_Path0_1[];
extern Bytecode TTYD64_nok_05_IntTable_Paths[];
extern NpcGroupList TTYD64_nok_05_NpcGroupList_Fuzzy;
extern EvtScript TTYD64_nok_05_Script_FuzzyStart;
extern EvtScript TTYD64_nok_05_Script_Nothing;
extern Bytecode TTYD64_nok_05_IntTable_Paths_Final[];

// clang-format off
static s32 TTYD64_nok_05_GetTattleMsg;

static s32 TTYD64_nok_05_GetTattle(void) {
    return TTYD64_nok_05_GetTattleMsg;
}

EvtScript TTYD64_nok_05_Script_GoToNewMap = {
    Set(LVar7, LVar0)
    IfEq(LVar0, 1)
        Switch(MapVar(0))
        CaseOrEq(0)
        CaseOrEq(5)
            Exec(ExitWalk)
            Call(GotoMap, (Bytecode) "nok_11", 2)
            Wait(100)
            Return
            EndCaseGroup
        EndSwitch
    EndIf
    Switch(LVar0)
    CaseOrEq(0)
    CaseOrEq(1)
    CaseOrEq(2)
        Set(LVar5, 0)
        Switch(MapVar(0))
        CaseEq(1)
            IfEq(LVar0, 1)
                Set(LVar6, 4)
                Set(LVar5, 1)
            EndIf
        CaseEq(2)
            IfEq(LVar0, 2)
                Set(LVar6, 3)
                Set(LVar5, 1)
            EndIf
        CaseEq(3)
            IfEq(LVar0, 1)
                Set(LVar6, 4)
                Set(LVar5, 1)
            EndIf
        CaseEq(4)
            IfEq(LVar0, 2)
                Set(LVar6, 3)
                Set(LVar5, 1)
            EndIf
        EndSwitch
        IfEq(LVar5, 0)
            Exec(ExitWalk)
            Call(GotoMap, (Bytecode) "nok_11", 2)
            Wait(100)
            Return
        EndIf
        EndCaseGroup
    CaseOrEq(3)
    CaseOrEq(4)
    CaseOrEq(5)
        Set(LVar5, 0)
        Switch(MapVar(0))
        CaseEq(0)
            IfEq(LVar0, 4)
                Set(LVar6, 1)
                Set(LVar5, 1)
            EndIf
        CaseEq(1)
            IfEq(LVar0, 3)
                Set(LVar6, 2)
                Set(LVar5, 1)
            EndIf
        CaseEq(2)
            IfEq(LVar0, 4)
                Set(LVar6, 1)
                Set(LVar5, 1)
            EndIf
        CaseEq(3)
            IfEq(LVar0, 3)
                Set(LVar6, 2)
                Set(LVar5, 1)
            EndIf
        CaseEq(4)
            IfEq(LVar0, 3)
                Set(LVar6, 1)
                Set(LVar5, 1)
            EndIf
        EndSwitch
        IfEq(LVar5, 0)
            Exec(ExitWalk)
            Call(GotoMap, (Bytecode) "nok_11", 2)
            Wait(100)
            Return
        EndIf
        EndCaseGroup
    EndSwitch
    SetGroup(0)
    SuspendGroup(2)
    ExecGetTID(ExitWalk, LVar9)
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(255.0))
    ExecWait(TTYD64_Script_FadeScreenOut)
    Switch(LVar7)
    CaseOrEq(0)
    CaseOrEq(1)
    CaseOrEq(2)
        Sub(MapVar(0), 1)
        EndCaseGroup
    CaseOrEq(3)
    CaseOrEq(4)
    CaseOrEq(5)
        Add(MapVar(0), 1)
        EndCaseGroup
    EndSwitch
    ExecWait(TTYD64_nok_05_Script_UpdateModelsAndCollisions)
    Switch(LVar6)
    CaseEq(0)
        Call(SetPlayerPos, -133, 0, 130)
    CaseEq(1)
        Call(SetPlayerPos, -6, 0, 177)
    CaseEq(2)
        Call(SetPlayerPos, 132, 0, 130)
    CaseEq(3)
        Call(SetPlayerPos, -125, 0, -134)
    CaseEq(4)
        Call(SetPlayerPos, 0, 0, -179)
    CaseEq(5)
        Call(SetPlayerPos, 128, 0, -131)
    EndSwitch
    KillThread(LVar9)
    Call(GetPlayerActionState, LVar0)
    IfEq(LVar0, 26)
        Call(SetPlayerActionState, 0)
        Call(TTYD64_SetPlayerColliderDiameter, 0)
    EndIf
    Call(SetPlayerFlagBits, 0x4000000, 0)
    Call(TTYD64_SetPlayerAnimFlagBits, PA_FLAG_CHANGING_MAP, 0)
    Call(ResetCam, 0, Float(100.0))
    Call(WaitForCam, 0, Float(0.0))
    Call(TeleportPartnerToPlayer)
    Call(ResetPartnerTetherDistance)
    SetF(LVar0, Float(50.0))
    SetF(LVar1, Float(5.0))
    ExecWait(TTYD64_Script_FadeScreenIn)
    ResumeGroup(2)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_nok_05_Script_Idle_FuzzyPath = {
    Call(SetNpcJumpscale, -1, Float(1.0))
    Exec(TTYD64_nok_05_Script_Fuzzy_UpdateVisibility)
    Set(LVar8, 0)
    Loop(0)
        Call(TTYD64_nm_TableWordRead, (Bytecode) TTYD64_nok_05_IntTable_Paths, LVar7, LVarE)
        IfEq(LVarE, -1)
            BreakLoop
        EndIf
        UseBuf(LVarE)
        BufRead3(LVar4, LVar5, LVar6)
        IfEq(MapVar(1), 0)
            Call(SetNpcPos, -1, LVar4, LVar5, LVar6)
        EndIf
        Loop(0)
            BufRead3(LVar4, LVar5, LVar6)
            IfEq(LVar4, -1)
                Add(LVar8, 1)
                IfGe(LVar8, 3)
                    Add(MapVar(1), 1)
                EndIf
                Add(LVar7, 4)
                BreakLoop
            EndIf
            IfEq(MapVar(0), MapVar(1))
                Call(PlaySoundAtNpc, -1, 818, 0)
            EndIf
            Call(NpcJump0, -1, LVar4, LVar5, LVar6, 20)
        EndLoop
        Call(SetNpcPos, -1, 0, -1000, 0)
    EndLoop
    IfEq(MapVar(0), 5)
        Call(SetNpcPos, -1, 0, -1000, 0)
        Return
    EndIf
    Loop(0)
        IfEq(MapVar(0), 5)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Set(LVar7, 0)
    Set(LVar8, 0)
    Loop(0)
        Call(TTYD64_nm_TableWordRead, (Bytecode) TTYD64_nok_05_IntTable_Paths_Final, LVar7, LVarE)
        IfEq(LVarE, -1)
            BreakLoop
        EndIf
        UseBuf(LVarE)
        BufRead3(LVar4, LVar5, LVar6)
        Loop(0)
            Add(LVar8, 1)
            BufRead3(LVar4, LVar5, LVar6)
            IfEq(LVar4, -1)
                Add(LVar7, 4)
                BreakLoop
            EndIf
            IfEq(MapVar(0), MapVar(1))
                IfEq(LVar8, 12)
                    Call(PlaySoundAtNpc, -1, 350, 0)
                Else
                    Call(PlaySoundAtNpc, -1, 818, 0)
                EndIf
            EndIf
            Call(NpcJump0, -1, LVar4, LVar5, LVar6, 20)
        EndLoop
    EndLoop
    Call(SetNpcPos, -1, 0, -1000, 0)
    Return
    End
};

EvtScript TTYD64_nok_05_Script_UpdateModelsAndCollisions = {
    ExecWait(TTYD64_nok_05_Script_DisableAllModelsAndCols)
    Call(EnableGroup, 48, 1)
    Switch(MapVar(0))
    CaseEq(0)
        Call(EnableGroup, 10, 1)
        Call(ModifyColliderFlags, 1, 1, 0x7FFFFE00)
        Call(ModifyColliderFlags, 1, 2, 0x7FFFFE00)
    CaseEq(1)
        Call(EnableGroup, 18, 1)
        Call(EnableGroup, 35, 1)
        Call(EnableModel, 20, 1)
        Call(EnableModel, 23, 1)
        Call(ModifyColliderFlags, 1, 24, 0x7FFFFE00)
        Call(ModifyColliderFlags, 1, 22, 0x7FFFFE00)
        Call(ModifyColliderFlags, 1, 25, 0x7FFFFE00)
    CaseEq(2)
        Call(EnableGroup, 18, 1)
        Call(EnableGroup, 26, 1)
        Call(EnableModel, 21, 1)
        Call(ModifyColliderFlags, 1, 19, 0x7FFFFE00)
        Call(ModifyColliderFlags, 1, 23, 0x7FFFFE00)
    CaseEq(3)
        Call(EnableGroup, 18, 1)
        Call(EnableGroup, 35, 1)
        Call(EnableModel, 22, 1)
        Call(ModifyColliderFlags, 1, 24, 0x7FFFFE00)
        Call(ModifyColliderFlags, 1, 26, 0x7FFFFE00)
    CaseEq(4)
        Call(EnableGroup, 18, 1)
        Call(EnableGroup, 26, 1)
        Call(EnableGroup, 29, 1)
        Call(EnableGroup, 32, 1)
        Call(ModifyColliderFlags, 1, 19, 0x7FFFFE00)
        Call(ModifyColliderFlags, 1, 20, 0x7FFFFE00)
        Call(ModifyColliderFlags, 1, 18, 0x7FFFFE00)
    CaseEq(5)
        Call(EnableGroup, 45, 1)
        Call(EnableGroup, 48, 0)
        Call(ModifyColliderFlags, 1, 28, 0x7FFFFE00)
        Call(ModifyColliderFlags, 1, 29, 0x7FFFFE00)
        Call(ModifyColliderFlags, 1, 5, 0x7FFFFE00)
        Call(ModifyColliderFlags, 1, 1, 0x7FFFFE00)
    EndSwitch
    Return
    End
};

NpcData TTYD64_nok_05_NpcGroup_Fuzzy[] = {
    {
        .id = 0,
        .settings = &TTYD64_nok_05_NpcSettings_Fuzzy,
        .pos = { -2.0f, 0.0f, 3.0f },
        .flags = 0x19700F01,
        .init = &TTYD64_nok_05_Script_Init_Fuzzy,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002B0002, .walk = 0x002B0002, .run = 0x002B0003, .chase = 0x002B0003, .anim_4 = 0x002B0000, .anim_5 = 0x002B0000, .death = 0x002B0000, .hit = 0x002B0000, .anim_8 = 0x002B0000, .anim_9 = 0x002B0000, .anim_A = 0x002B0000, .anim_B = 0x002B0000, .anim_C = 0x002B0000, .anim_D = 0x002B0000, .anim_E = 0x002B0000, .anim_F = 0x002B0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_nok_05_Script_Fuzzy_UpdateVisibility = {
    SetGroup(0)
    Loop(0)
        IfNe(MapVar(0), MapVar(1))
            Call(SetNpcFlagBits, -1, 0x1000000, 1)
            Call(SetNpcFlagBits, -1, 0x400000, 0)
            Call(EnableNpcShadow, -1, 0)
        Else
            Call(SetNpcFlagBits, -1, 0x1000000, 0)
            Call(SetNpcFlagBits, -1, 0x400000, 1)
            Call(EnableNpcShadow, -1, 1)
        EndIf
        IfNe(MapVar(0), 5)
            Call(TTYD64_GetEntityPointer, MapVar(2), LVar1)
            Call(TTYD64_WritePtrField, LVar1, TTYD64_F_ENTITY_48_4U, 0)
            Call(TTYD64_WritePtrField, LVar1, TTYD64_F_ENTITY_4C_4U, 0xC47A0000)
            Call(TTYD64_WritePtrField, LVar1, TTYD64_F_ENTITY_50_4U, 0)
        Else
            Call(TTYD64_GetEntityPointer, MapVar(2), LVar1)
            Call(TTYD64_WritePtrField, LVar1, TTYD64_F_ENTITY_48_4U, 0xBF800000)
            Call(TTYD64_WritePtrField, LVar1, TTYD64_F_ENTITY_4C_4U, 0x42800000)
            Call(TTYD64_WritePtrField, LVar1, TTYD64_F_ENTITY_50_4U, 0)
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_nok_05_Script_DisableAllModelsAndCols = {
    Call(EnableGroup, 49, 0)
    Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 2, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 5, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 19, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 20, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 18, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 21, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 22, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 23, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 24, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 26, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 25, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 28, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 29, 0x7FFFFE00)
    Return
    End
};

EvtScript TTYD64_nok_05_Script_Main = {
    Set(GameByte(425), 32)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Set(MapVar(0), 0)
    Exec(TTYD64_nok_05_Script_SetupMusic)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_nok_05_NpcGroupList_Fuzzy)
    Exec(TTYD64_nok_05_Script_MakeEntities)
    Set(LVar0, (Bytecode) TTYD64_nok_05_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Exec(TTYD64_nok_05_Script_UpdateModelsAndCollisions)
    Return
    End
};

EvtScript TTYD64_nok_05_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SuperBlock), -1, 64, 0, -180, 0x80000000)
    Set(MapVar(2), LVar0)
    Call(AssignBlockFlag, GameFlag(4720))
    Call(AssignScript, (Bytecode) TTYD64_nok_05_Script_Entity_Shine1)
    Call(TTYD64_GetEntityPointer, MapVar(2), LVar1)
    Call(TTYD64_WritePtrField, LVar1, TTYD64_F_ENTITY_48_4U, 0)
    Call(TTYD64_WritePtrField, LVar1, TTYD64_F_ENTITY_4C_4U, 0xC47A0000)
    Call(TTYD64_WritePtrField, LVar1, TTYD64_F_ENTITY_50_4U, 0)
    Return
    End
};

s32 TTYD64_nok_05_VectorList_Path4[] = {
    184, 64, 195, 176, 64, 182, 144, 0, 90, 127, 0, 19, 80, 23, -102, -60, 0, -113, -99, 23, 20, -140, 0, -68, -153, 0, -147, -7, 0, -193, 125, 0, -149, 24, 0, -206, -114, 0, -168, 55, 0, -146, -20, 0, -79, -273, 0, -268, -1, -1, -1
};

EvtScript TTYD64_nok_05_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_nok_05_Script_Exit0, 0x80000, 11, 1, 0)
    BindTrigger(TTYD64_nok_05_Script_Exit1, 0x80000, 12, 1, 0)
    BindTrigger(TTYD64_nok_05_Script_Exit2, 0x80000, 13, 1, 0)
    BindTrigger(TTYD64_nok_05_Script_Exit3, 0x80000, 14, 1, 0)
    BindTrigger(TTYD64_nok_05_Script_Exit4, 0x80000, 15, 1, 0)
    BindTrigger(TTYD64_nok_05_Script_Exit5, 0x80000, 16, 1, 0)
    Return
    End
};

s32 TTYD64_nok_05_VectorList_Path3[] = {
    171, 53, 178, 162, 53, 168, 127, 0, 65, 80, 0, 7, -35, 0, -67, -46, 0, 46, 89, 0, 138, 144, 0, -59, 42, 0, -181, -80, 0, -160, -157, 0, -160, -267, 0, -295, -1, -1, -1
};

s32 TTYD64_nok_05_VectorList_Path1[] = {
    2, 41, 272, 5, 41, 266, 32, 0, 180, 95, 0, 28, -31, 0, -93, -122, 0, 56, 141, 0, 52, -86, 0, -75, -285, 0, -276, -1, -1, -1
};

s32 TTYD64_nok_05_VectorList_Path2[] = {
    179, 35, 186, 167, 35, 177, 47, 0, 161, -48, 0, 113, 22, 0, -49, 152, 0, -97, 2, 0, -184, 2, 0, -375, -1, -1, -1
};

EntryList TTYD64_nok_05_EntryList = {
    { -133.0f, 0.0f, 130.0f, 45.0f },
    { -6.0f, 0.0f, 177.0f, 0.0f },
    { 132.0f, 0.0f, 130.0f, -45.0f },
    { -125.0f, 0.0f, -134.0f, 120.0f },
    { 0.0f, 0.0f, -179.0f, -180.0f },
    { 128.0f, 0.0f, -131.0f, -135.0f },
};

s32 TTYD64_nok_05_VectorList_Path_Final1[] = {
    -2, 0, 40, 33, 0, 5, 59, 0, -112, 47, 0, -184, 12, 0, -191, -21, 0, -191, -47, 0, -201, -1, -1, -1
};

s32 TTYD64_nok_05_VectorList_Path_Final2[] = {
    -47, 0, -200, -78, 0, -115, -75, 0, -27, 6, 0, 14, 50, 0, -17, 204, 40, 260, -1, -1, -1
};

EvtScript TTYD64_nok_05_Script_Exit1 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 1)
    Set(LVar0, 1)
    ExecWait(TTYD64_nok_05_Script_GoToNewMap)
    Return
    End
};

EvtScript TTYD64_nok_05_Script_Exit0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Set(LVar0, 0)
    ExecWait(TTYD64_nok_05_Script_GoToNewMap)
    Return
    End
};

EvtScript TTYD64_nok_05_Script_Exit5 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 5)
    Set(LVar0, 5)
    ExecWait(TTYD64_nok_05_Script_GoToNewMap)
    Return
    End
};

EvtScript TTYD64_nok_05_Script_Exit4 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 4)
    Set(LVar0, 4)
    ExecWait(TTYD64_nok_05_Script_GoToNewMap)
    Return
    End
};

EvtScript TTYD64_nok_05_Script_Exit3 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 3)
    Set(LVar0, 3)
    ExecWait(TTYD64_nok_05_Script_GoToNewMap)
    Return
    End
};

EvtScript TTYD64_nok_05_Script_Exit2 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 2)
    Set(LVar0, 2)
    ExecWait(TTYD64_nok_05_Script_GoToNewMap)
    Return
    End
};

MapSettings TTYD64_nok_05_Header = {
    .main = &TTYD64_nok_05_Script_Main,
    .entryList = &TTYD64_nok_05_EntryList,
    .entryCount = 6,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_nok_05_GetTattle },
};

u8 TTYD64_nok_05_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x37, 0x45, 0xF7, 0x53, 0x48, 0x4F, 0x55, 0x4C,
    0x44, 0xF7, 0x54, 0x52, 0x59, 0xF7, 0x46, 0x4F, 0x4C, 0x4C, 0x4F, 0x57,
    0x49, 0x4E, 0x47, 0xF7, 0x54, 0x48, 0x41, 0x54, 0xF0, 0x26, 0x55, 0x5A,
    0x5A, 0x59, 0x0C, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0xF7, 0x48, 0x55,
    0x52, 0x52, 0x59, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_nok_05_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(2))
    SetConst(LVar1, GameFlag(4720))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_nok_05_Script_SetupMusic = {
    Call(SetMusic, 0, 17, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

s32 TTYD64_nok_05_VectorList_Path0_2[] = {
    -17, 0, 5, 1, 0, -100, 1, 0, -190, 1, 0, -392, -1, -1, -1
};

NpcSettings TTYD64_nok_05_NpcSettings_Fuzzy = {
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
    .level = 6,
    .actionFlags = 0,
};

EvtScript TTYD64_nok_05_Script_Init_Fuzzy = {
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_nok_05_Script_Idle_FuzzyPath)
    Return
    End
};

s32 TTYD64_nok_05_VectorList_Path0_0[] = {
    -26, 182, -172, -65, 0, 8, -1, -1, -1
};

s32 TTYD64_nok_05_VectorList_Path0_1[] = {
    -65, 0, 9, -17, 0, 4, -1, -1, -1
};

Bytecode TTYD64_nok_05_IntTable_Paths[] = {
    (Bytecode) TTYD64_nok_05_VectorList_Path0_0, (Bytecode) TTYD64_nok_05_VectorList_Path0_1, (Bytecode) TTYD64_nok_05_VectorList_Path0_2, (Bytecode) TTYD64_nok_05_VectorList_Path1, (Bytecode) TTYD64_nok_05_VectorList_Path2, (Bytecode) TTYD64_nok_05_VectorList_Path3, (Bytecode) TTYD64_nok_05_VectorList_Path4, -1
};

NpcGroupList TTYD64_nok_05_NpcGroupList_Fuzzy = {
    { .npcCount = 1, .npcs = TTYD64_nok_05_NpcGroup_Fuzzy, .battle = 0x0000, .stage = 0 },
    {},
};

EvtScript TTYD64_nok_05_Script_FuzzyStart = {
    Return
    End
};

EvtScript TTYD64_nok_05_Script_Nothing = {
    Return
    End
};

Bytecode TTYD64_nok_05_IntTable_Paths_Final[] = {
    (Bytecode) TTYD64_nok_05_VectorList_Path_Final1, (Bytecode) TTYD64_nok_05_VectorList_Path_Final2, -1
};

MapConfig TTYD64_mapcfg_nok_05 = {
    .id = "nok_05",
    .settings = &TTYD64_nok_05_Header,
    .bgName = "nok_bg",
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_nok_05(void) {
    TTYD64_nok_05_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_nok_05_String_Tattle);
}
