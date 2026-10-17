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
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetSelfVar);
API_CALLABLE(UseExitHeading);
API_CALLABLE(flo_16_FlyingNoAttackAI_Main);

extern NpcData TTYD64_flo_27_NpcGroup_Ruff1[];
extern NpcData TTYD64_flo_27_NpcGroup_Ruff2[];
extern NpcData TTYD64_flo_27_NpcGroup_Ruff3[];
extern EvtScript TTYD64_flo_27_Script_InitItems;
extern EvtScript TTYD64_flo_27_Script_Main;
extern EvtScript TTYD64_flo_27_Script_NpcAI_80244058_flo_16;
extern EvtScript TTYD64_flo_27_Script_Exit0;
extern u8 TTYD64_flo_27_String_Tattle[];
extern MapSettings TTYD64_flo_27_Header;
extern EvtScript TTYD64_flo_27_Script_Entity_Shine1;
extern EvtScript TTYD64_flo_27_Script_Entity_Shine2;
extern EvtScript TTYD64_flo_27_Script_Entity_Shine3;
extern EvtScript TTYD64_flo_27_Script_Entity_Shine4;
extern EvtScript TTYD64_flo_27_Script_SetupMusic;
extern NpcGroupList TTYD64_flo_27_NpcGroupList_flo27;
extern MobileAISettings TTYD64_flo_27_AISettings_80244028_flo_16;
extern NpcSettings TTYD64_flo_27_NpcSettings_802440C8_flo_16;
extern EvtScript TTYD64_flo_27_Script_CreateExitTriggers;
extern EntryList TTYD64_flo_27_EntryList;

// clang-format off
static s32 TTYD64_flo_27_GetTattleMsg;

static s32 TTYD64_flo_27_GetTattle(void) {
    return TTYD64_flo_27_GetTattleMsg;
}

NpcData TTYD64_flo_27_NpcGroup_Ruff1[] = {
    {
        .id = 0,
        .settings = &TTYD64_flo_27_NpcSettings_802440C8_flo_16,
        .pos = { -513.0f, 69.0f, 233.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 16, .itemDrops = { { 130, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = -513, .centerPos.y = 69, .centerPos.z = 233, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = -513, .detectPos.y = 69, .detectPos.z = 243, .detectSize.x = 200, .detectSize.z = 125, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x007D0000, .walk = 0x007D0000, .run = 0x007D0005, .chase = 0x007D0005, .anim_4 = 0x007D0000, .anim_5 = 0x007D0000, .death = 0x007D0006, .hit = 0x007D0006, .anim_8 = 0x007D0005, .anim_9 = 0x007D0001, .anim_A = 0x007D0001, .anim_B = 0x007D0001, .anim_C = 0x007D0001, .anim_D = 0x007D0001, .anim_E = 0x007D0001, .anim_F = 0x007D0001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_flo_27_NpcGroup_Ruff2[] = {
    {
        .id = 1,
        .settings = &TTYD64_flo_27_NpcSettings_802440C8_flo_16,
        .pos = { -855.0f, 69.0f, 50.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 16, .itemDrops = { { 130, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = -855, .centerPos.y = 69, .centerPos.z = 50, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = -855, .detectPos.y = 69, .detectPos.z = 60, .detectSize.x = 180, .detectSize.z = 125, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x007D0000, .walk = 0x007D0000, .run = 0x007D0005, .chase = 0x007D0005, .anim_4 = 0x007D0000, .anim_5 = 0x007D0000, .death = 0x007D0006, .hit = 0x007D0006, .anim_8 = 0x007D0005, .anim_9 = 0x007D0001, .anim_A = 0x007D0001, .anim_B = 0x007D0001, .anim_C = 0x007D0001, .anim_D = 0x007D0001, .anim_E = 0x007D0001, .anim_F = 0x007D0001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_flo_27_NpcGroup_Ruff3[] = {
    {
        .id = 2,
        .settings = &TTYD64_flo_27_NpcSettings_802440C8_flo_16,
        .pos = { -596.0f, 69.0f, -193.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 16, .itemDrops = { { 130, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = -596, .centerPos.y = 69, .centerPos.z = -193, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = -596, .detectPos.y = 69, .detectPos.z = -183, .detectSize.x = 180, .detectSize.z = 125, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x007D0000, .walk = 0x007D0000, .run = 0x007D0005, .chase = 0x007D0005, .anim_4 = 0x007D0000, .anim_5 = 0x007D0000, .death = 0x007D0006, .hit = 0x007D0006, .anim_8 = 0x007D0005, .anim_9 = 0x007D0001, .anim_A = 0x007D0001, .anim_B = 0x007D0001, .anim_C = 0x007D0001, .anim_D = 0x007D0001, .anim_E = 0x007D0001, .anim_F = 0x007D0001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_flo_27_Script_InitItems = {
    Call(MakeItemEntity, 348, 332, 151, -47, 17, GameFlag(5513))
    Call(MakeEntity, Ref(Entity_SuperBlock), -784, 242, -269, -180, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(5514))
    Call(AssignScript, (Bytecode) TTYD64_flo_27_Script_Entity_Shine1)
    Call(MakeEntity, Ref(Entity_SuperBlock), -438, 242, -236, -180, 0x80000000)
    Set(MapVar(1), LVar0)
    Call(AssignBlockFlag, GameFlag(5515))
    Call(AssignScript, (Bytecode) TTYD64_flo_27_Script_Entity_Shine2)
    Call(MakeEntity, Ref(Entity_SuperBlock), -277, 242, 129, -180, 0x80000000)
    Set(MapVar(2), LVar0)
    Call(AssignBlockFlag, GameFlag(5516))
    Call(AssignScript, (Bytecode) TTYD64_flo_27_Script_Entity_Shine3)
    Call(MakeEntity, Ref(Entity_SuperBlock), -995, 242, 73, -180, 0x80000000)
    Set(MapVar(3), LVar0)
    Call(AssignBlockFlag, GameFlag(5517))
    Call(AssignScript, (Bytecode) TTYD64_flo_27_Script_Entity_Shine4)
    Return
    End
};

EvtScript TTYD64_flo_27_Script_Main = {
    Set(GameByte(425), 39)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(ModifyColliderFlags, 3, 7, 7)
    Exec(TTYD64_flo_27_Script_SetupMusic)
    Exec(TTYD64_flo_27_Script_InitItems)
    Call(MakeNpcs, 1, (Bytecode) TTYD64_flo_27_NpcGroupList_flo27)
    Set(LVar0, (Bytecode) TTYD64_flo_27_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

EvtScript TTYD64_flo_27_Script_NpcAI_80244058_flo_16 = {
    Call(SetSelfVar, 0, 1)
    Call(SetSelfVar, 5, 0)
    Call(SetSelfVar, 6, 0)
    Call(SetSelfVar, 1, 600)
    Call(flo_16_FlyingNoAttackAI_Main, Ref(TTYD64_flo_27_AISettings_80244028_flo_16))
    Return
    End
};

EvtScript TTYD64_flo_27_Script_Exit0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "flo_19", 4)
    Wait(100)
    Return
    End
};

u8 TTYD64_flo_27_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x37, 0x4F, 0x57, 0x0C, 0xF7, 0x4C, 0x4F, 0x54,
    0x53, 0xF7, 0x4F, 0x46, 0xF7, 0x52, 0x4F, 0x4F, 0x54, 0x53, 0x01, 0xF0,
    0x29, 0xF7, 0x57, 0x4F, 0x4E, 0x44, 0x45, 0x52, 0xF7, 0x46, 0x52, 0x4F,
    0x4D, 0xF7, 0x57, 0x48, 0x45, 0x52, 0x45, 0xF7, 0x54, 0x48, 0x45, 0x59,
    0xF7, 0x43, 0x4F, 0x4D, 0x45, 0xF0, 0x46, 0x52, 0x4F, 0x4D, 0x0E, 0xF1,
    0xFD
};

MapSettings TTYD64_flo_27_Header = {
    .main = &TTYD64_flo_27_Script_Main,
    .entryList = &TTYD64_flo_27_EntryList,
    .entryCount = 1,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_flo_27_GetTattle },
};

EvtScript TTYD64_flo_27_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(5514))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_flo_27_Script_Entity_Shine2 = {
    Set(LVar0, MapVar(1))
    SetConst(LVar1, GameFlag(5515))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_flo_27_Script_Entity_Shine3 = {
    Set(LVar0, MapVar(2))
    SetConst(LVar1, GameFlag(5516))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_flo_27_Script_Entity_Shine4 = {
    Set(LVar0, MapVar(3))
    SetConst(LVar1, GameFlag(5517))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_flo_27_Script_SetupMusic = {
    Call(SetMusic, 0, 50, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

NpcGroupList TTYD64_flo_27_NpcGroupList_flo27 = {
    { .npcCount = 1, .npcs = TTYD64_flo_27_NpcGroup_Ruff1, .battle = 0x1824, .stage = 8 },
    { .npcCount = 1, .npcs = TTYD64_flo_27_NpcGroup_Ruff2, .battle = 0x181F, .stage = 8 },
    { .npcCount = 1, .npcs = TTYD64_flo_27_NpcGroup_Ruff3, .battle = 0x181F, .stage = 8 },
    {},
};

MobileAISettings TTYD64_flo_27_AISettings_80244028_flo_16 = {
    .moveSpeed = 1.0f,
    .moveTime = 45,
    .waitTime = 60,
    .alertRadius = 100.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 3.5999999f,
    .chaseTurnRate = 10,
    .chaseUpdateInterval = 1,
    .chaseRadius = 120.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_flo_27_NpcSettings_802440C8_flo_16 = {
    .defaultAnim = 0x00000000,
    .height = 24,
    .radius = 28,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = &TTYD64_flo_27_Script_NpcAI_80244058_flo_16,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 19,
    .actionFlags = 0,
};

EvtScript TTYD64_flo_27_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_flo_27_Script_Exit0, 0x80000, 2, 1, 0)
    Return
    End
};

EntryList TTYD64_flo_27_EntryList = {
    { 480.0f, 0.0f, 0.0f, -90.0f },
};

MapConfig TTYD64_mapcfg_flo_27 = {
    .id = "flo_27",
    .settings = &TTYD64_flo_27_Header,
    .bgName = "sra_bg",
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_flo_27(void) {
    TTYD64_flo_27_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_flo_27_String_Tattle);
}
