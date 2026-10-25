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

extern EvtScript mac_05_D_8024A1F8_85C368;
extern EvtScript mac_05_D_80250A5C_862BCC;
extern EvtScript mac_05_D_80250AD4_862C44;
extern EvtScript mac_05_D_80250D58_862EC8;
extern EvtScript mac_05_D_80250FA4_863114;
extern EvtScript mac_05_D_80250FB4_863124;
extern EvtScript mac_05_D_8025110C_86327C;
extern EvtScript mac_05_D_8025111C_86328C;
extern EvtScript mac_05_D_80251244_8633B4;
extern EvtScript mac_05_D_802513AC_86351C;
extern EvtScript mac_05_D_802514EC_86365C;
extern EvtScript mac_05_D_80251654_8637C4;
extern EvtScript mac_05_D_802516CC_86383C;
extern EvtScript mac_05_D_802522E0_864450;
extern EvtScript mac_05_D_80252310_864480;
extern EvtScript mac_05_D_80252580_8646F0;
extern EvtScript mac_05_D_802525B0_864720;
extern s32 mac_05_D_802526C8_864838[];
extern EvtScript mac_05_EVS_80248878;
extern EvtScript mac_05_EVS_802496FC;
extern EvtScript mac_05_EVS_AnimateClub64Sign;
extern EvtScript mac_05_EVS_BindExitTriggers;
extern EvtScript mac_05_EVS_ExitWalk_mac_04_1;
extern EvtScript mac_05_EVS_Main;
extern EvtScript mac_05_EVS_MakeEntities;
extern EvtScript mac_05_EVS_NpcInit_ArtistToad;
extern EvtScript mac_05_EVS_NpcInit_Bartender;
extern EvtScript mac_05_EVS_NpcInit_Chanterelle;
extern EvtScript mac_05_EVS_NpcInit_Toad_02;
extern EvtScript mac_05_EVS_NpcInit_Toad_04;
extern EvtScript mac_05_EVS_NpcInit_Toad_05;
extern EvtScript mac_05_EVS_NpcInit_Toad_06;
extern EvtScript mac_05_EVS_NpcInit_Toad_07;
extern EvtScript mac_05_EVS_NpcInit_TradeEventToad;
extern EvtScript mac_05_EVS_NpcInteract_Toad_01;
extern EvtScript mac_05_EVS_SetupMusic;
extern EvtScript mac_05_EVS_SetupRooms;
extern EvtScript mac_05_EVS_SetupWhale;
extern EvtScript mac_05_EVS_UpdateTexturePan;
extern NpcData mac_05_NpcData_ChuckQuizmo;
extern NpcData mac_05_NpcData_Fishmael;
extern NpcData mac_05_NpcData_Fuzzipede;
extern NpcData mac_05_NpcData_JrTroopa_01[];
extern NpcData mac_05_NpcData_Kolorado;
extern NpcSettings mac_05_NpcSettings_Toad_Stationary;
extern NpcSettings mac_05_NpcSettings_Whale;
extern MapSettings mac_05_settings;

API_CALLABLE(BindNpcInteract);
API_CALLABLE(CreateMapRoom);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableModel);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetLoadType);
API_CALLABLE(GetNpcAnimation);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetNpcVar);
API_CALLABLE(GetNpcYaw);
API_CALLABLE(GotoMap);
API_CALLABLE(InterpNpcYaw);
API_CALLABLE(InterruptUsePartner);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeLocalVertexCopy);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(NpcMoveTo);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAt);
API_CALLABLE(PlaySoundAtNpc);
API_CALLABLE(RotateGroup);
API_CALLABLE(RotateModel);
API_CALLABLE(ScaleModel);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCustomGfxBuilders);
API_CALLABLE(SetEnemyFlagBits);
API_CALLABLE(SetModelCustomGfx);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetNpcSpeed);
API_CALLABLE(SetNpcVar);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanner);
API_CALLABLE(ShakeCam);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(StopSound);
API_CALLABLE(StopTrackingSoundPos);
API_CALLABLE(TranslateGroup);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseExitHeading);
API_CALLABLE(mac_05_CreateWhaleGeyser);
API_CALLABLE(mac_05_DisposeWhaleGeyser);
API_CALLABLE(mac_05_SetWhaleGeyserPos);
API_CALLABLE(mac_05_UnkAngleFunc001);
API_CALLABLE(mac_05_UnkFloatFunc001);
API_CALLABLE(mac_05_UnkPlayerPosFunc);
API_CALLABLE(mac_05_gfx_build_club_64);
API_CALLABLE(mac_05_unkAngleFunc002);
API_CALLABLE(mac_05_unkAngleFunc003);
API_CALLABLE(sam_11_UpdateHouseShowHide);

extern NpcSettings TTYD64_mac_05_NPCSettings_Blank;
extern EvtScript TTYD64_mac_05_Script_8024457C;
extern EvtScript TTYD64_mac_05_Script_80244648;
extern EvtScript TTYD64_mac_05_Script_ExitWalk_80244810;
extern EvtScript TTYD64_mac_05_Script_EnterWalk_802448C4;
extern EvtScript TTYD64_mac_05_Script_Main;
extern EvtScript TTYD64_mac_05_Script_Init_8024B4BC;
extern EvtScript TTYD64_mac_05_Script_Init_8024D4E4;
extern NpcData TTYD64_mac_05_NpcGroup_8024E9FC[];
extern NpcData TTYD64_mac_05_NpcGroup_8024F5E8[];
extern NpcData TTYD64_mac_05_NpcGroup_8024FDA8[];
extern EvtScript TTYD64_mac_05_Script_Init_Entry4;
extern EvtScript TTYD64_mac_05_Script_80250A5C;
extern EvtScript TTYD64_mac_05_Script_80250AD4;
extern EvtScript TTYD64_mac_05_Script_80250D58;
extern EvtScript TTYD64_mac_05_Script_80250FB4;
extern EvtScript TTYD64_mac_05_Script_8025111C;
extern EvtScript TTYD64_mac_05_Script_80251244;
extern EvtScript TTYD64_mac_05_Script_802513AC;
extern EvtScript TTYD64_mac_05_Script_802514EC;
extern EvtScript TTYD64_mac_05_Script_80251654;
extern EvtScript TTYD64_mac_05_Script_802516CC;
extern EvtScript TTYD64_mac_05_Script_8025194C;
extern EvtScript TTYD64_mac_05_Script_OpenDoor_802522E0;
extern EvtScript TTYD64_mac_05_Script_MoveWalls_80252310;
extern EvtScript TTYD64_mac_05_Script_DropDoor_80252580;
extern EvtScript TTYD64_mac_05_Script_ToggleVis_802525B0;
extern EvtScript TTYD64_mac_05_Script_8024487C;
extern EvtScript TTYD64_mac_05_Script_80252748;
extern EvtScript TTYD64_mac_05_Script_Interact_Bartender;
extern EvtScript TTYD64_mac_05_Script_RevealEntrance;
extern NpcData TTYD64_mac_05_NpcGroup_Fuzzy[];
extern EvtScript TTYD64_mac_05_Script_MoveFurniture;
extern EvtScript TTYD64_mac_05_Script_ShowEmote_Bartender;
extern u8 TTYD64_mac_05_String_Bartender_HelpMe[];
extern EvtScript TTYD64_mac_05_Script_InitNewStuff;
extern EvtScript TTYD64_mac_05_Script_802526E0;
extern NpcGroupList TTYD64_mac_05_NpcGroupList_8025099C;
extern NpcGroupList TTYD64_mac_05_NpcGroupList_802509F0;
extern NpcGroupList TTYD64_mac_05_NpcGroupList_80250948;
extern EvtScript TTYD64_mac_05_Script_Exit2;
extern EntryList TTYD64_mac_05_EntryList;
extern EvtScript TTYD64_mac_05_Script_Init_Fuzzy;

// clang-format off
NpcSettings TTYD64_mac_05_NPCSettings_Blank = {
    .defaultAnim = 0x00000000,
    .height = 32,
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

EvtScript TTYD64_mac_05_Script_8024457C = {
    SetGroup(0)
    Set(LVarC, 0)
    Label(0)
    IfGe(LVarC, 60)
        Set(LVarC, 0)
    EndIf
    Call(mac_05_UnkFloatFunc001, LVarC, LVar0, Float(-1.0), Float(1.0), 30, 0, 0)
    Call(ScaleModel, 107, 1, LVar0, 1)
    Add(LVarC, 1)
    Wait(1)
    Goto(0)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_80244648 = {
    Loop(0)
        Call(MakeLerp, 600, -240, 320, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateModel, 105, LVar0, -25, -75)
            Call(RotateModel, 105, 0, 0, 1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(MakeLerp, -240, 600, 320, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateModel, 105, LVar0, -25, -75)
            Call(RotateModel, 105, 180, 0, 1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndLoop
    Return
    End
};

EvtScript TTYD64_mac_05_Script_ExitWalk_80244810 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 3)
    Exec(ExitWalk)
    Set(GameByte(0), 9)
    Call(GotoMap, (Bytecode) "kgr_01", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_EnterWalk_802448C4 = {
    Call(GetLoadType, LVar1)
    IfEq(LVar1, 1)
        Exec(EnterSavePoint)
        Exec(mac_05_EVS_BindExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVar0, Ref(mac_05_EVS_BindExitTriggers))
        Exec(EnterWalk)
    CaseEq(1)
        Exec(mac_05_EVS_802496FC)
        Exec(mac_05_EVS_BindExitTriggers)
    CaseEq(2)
        Exec(mac_05_EVS_80248878)
        Exec(mac_05_EVS_BindExitTriggers)
    CaseEq(3)
        Call(DisablePlayerInput, 1)
        Call(DisablePlayerPhysics, 1)
        Call(SetPlayerPos, -160, -10, 371)
        Call(SetNpcPos, -4, -160, -10, 371)
        Call(SetEnemyFlagBits, 0, 0x8000000, 1)
        Call(DisablePartnerAI, 0)
        Call(InterruptUsePartner)
        Wait(10)
        Thread
            Call(MakeLerp, -160, -220, 30, 0)
            Loop(0)
                Call(UpdateLerp)
                Call(SetPlayerPos, LVar0, -10, 371)
                Call(SetNpcPos, -4, LVar0, -10, 371)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
        EndThread
        Call(SetNpcAnimation, 0, 0xB60002)
        Wait(30)
        Call(SetPlayerPos, -280, -10, 371)
        Call(EnablePartnerAI)
        Call(DisablePlayerPhysics, 0)
        Call(DisablePlayerInput, 0)
        Set(LVar0, Ref(mac_05_EVS_BindExitTriggers))
        ExecWait(EnterWalk)
        Call(SetNpcPos, 0, -220, 10, 372)
        Call(SetEnemyFlagBits, 0, 0x8000000, 0)
    CaseEq(4)
        Set(LVar0, Ref(mac_05_EVS_BindExitTriggers))
        Exec(EnterWalk)
        Exec(TTYD64_mac_05_Script_Init_Entry4)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_mac_05_Script_Main = {
    Set(GameByte(425), 1)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Switch(GameByte(0))
    CaseLt(7)
        Set(LVar0, Ref(TTYD64_mac_05_NpcGroupList_80250948))
    CaseLt(11)
        Set(LVar0, Ref(TTYD64_mac_05_NpcGroupList_8025099C))
    CaseLt(41)
        Call(GetEntryID, LVar1)
        IfEq(LVar1, 1)
            IfEq(GameFlag(1218), 0)
                Set(LVar0, Ref(TTYD64_mac_05_NpcGroupList_802509F0))
            Else
                Set(LVar0, Ref(TTYD64_mac_05_NpcGroupList_8025099C))
            EndIf
        Else
            Set(LVar0, Ref(TTYD64_mac_05_NpcGroupList_80250948))
        EndIf
    CaseLt(58)
        Set(LVar0, Ref(TTYD64_mac_05_NpcGroupList_80250948))
    CaseDefault
        Set(LVar0, Ref(TTYD64_mac_05_NpcGroupList_80250948))
    EndSwitch
    Call(MakeNpcs, 0, LVar0)
    ExecWait(mac_05_EVS_MakeEntities)
    Exec(mac_05_EVS_SetupWhale)
    Call(GetEntryID, LVar0)
    Exec(mac_05_EVS_SetupRooms)
    Exec(mac_05_EVS_SetupMusic)
    Call(ModifyColliderFlags, 0, 4, 0x7FFFFE00)
    Exec(TTYD64_mac_05_Script_EnterWalk_802448C4)
    Wait(1)
    Exec(TTYD64_mac_05_Script_8024457C)
    Call(SetTexPanner, 107, 1)
    Thread
        Set(LVar0, 1)
        Set(LVar1, 100)
        Set(LVar2, 100)
        Set(LVar3, -70)
        Set(LVar4, -50)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(mac_05_EVS_UpdateTexturePan)
    EndThread
    Exec(TTYD64_mac_05_Script_80244648)
    Exec(mac_05_EVS_AnimateClub64Sign)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_Init_8024B4BC = {
    Call(BindNpcInteract, -1, Ref(mac_05_EVS_NpcInteract_Toad_01))
    Call(SetNpcFlagBits, 0, 0x1000000, 1)
    Call(SetNpcFlagBits, 0, 16, 0)
    Call(InterpNpcYaw, 0, 270, 0)
    IfLt(GameByte(0), -13)
        Call(SetNpcPos, 0, 0, -1000, 0)
        Call(SetNpcAnimation, 0, 0xB60005)
        Call(ModifyColliderFlags, 0, 16, 0x7FFFFE00)
        Return
    EndIf
    IfLt(GameByte(0), 7)
        Call(SetNpcPos, 0, 0, -60, 290)
        Call(SetNpcAnimation, 0, 0xB60005)
        Call(ModifyColliderFlags, 0, 16, 0x7FFFFE00)
        Return
    EndIf
    IfLt(GameByte(0), 8)
        Call(ModifyColliderFlags, 0, 20, 0x7FFFFE00)
        Call(SetNpcAnimation, 0, 0xB60006)
        Call(ModifyColliderFlags, 0, 16, 0x7FFFFE00)
        Call(SetNpcPos, 0, -73, -53, 480)
        Exec(mac_05_D_8024A1F8_85C368)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 2)
        Call(SetNpcAnimation, 0, 0xB60008)
        Call(SetNpcPos, 0, -220, 10, 372)
        Return
    EndIf
    IfLt(GameByte(0), 10)
        Call(SetNpcAnimation, 0, 0xB60008)
        Call(SetNpcPos, 0, -220, 10, 372)
        Return
    EndIf
    Call(SetNpcAnimation, 0, 0xB60000)
    Call(SetNpcPos, 0, -220, 10, 372)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_Init_8024D4E4 = {
    Call(BindNpcInteract, -1, Ref(TTYD64_mac_05_Script_Interact_Bartender))
    Return
    End
};

NpcData TTYD64_mac_05_NpcGroup_8024E9FC[] = {
    {
        .id = 0,
        .settings = &mac_05_NpcSettings_Whale,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00400F09,
        .init = &TTYD64_mac_05_Script_Init_8024B4BC,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 32767, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 32767, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00830001, .walk = 0x00830002, .run = 0x00830003, .chase = 0x00830003, .anim_4 = 0x00830001, .anim_5 = 0x00830001, .death = 0x00830006, .hit = 0x00830006, .anim_8 = 0x00830003, .anim_9 = 0x00830003, .anim_A = 0x00830003, .anim_B = 0x00830003, .anim_C = 0x00830003, .anim_D = 0x00830003, .anim_E = 0x00830003, .anim_F = 0x00830003 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A0055,
    },
};

NpcData TTYD64_mac_05_NpcGroup_8024F5E8[] = {
    {
        .id = 12,
        .settings = &mac_05_NpcSettings_Toad_Stationary,
        .pos = { 320.0f, 0.0f, -300.0f },
        .flags = 0x00002D09,
        .init = &mac_05_EVS_NpcInit_Toad_04,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 32767, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 32767, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00830201, .walk = 0x00830202, .run = 0x00830203, .chase = 0x00830203, .anim_4 = 0x00830201, .anim_5 = 0x00830201, .death = 0x00830206, .hit = 0x00830206, .anim_8 = 0x00830203, .anim_9 = 0x00830203, .anim_A = 0x00830203, .anim_B = 0x00830203, .anim_C = 0x00830203, .anim_D = 0x00830203, .anim_E = 0x00830203, .anim_F = 0x00830203 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A005A,
    },
    {
        .id = 13,
        .settings = &mac_05_NpcSettings_Toad_Stationary,
        .pos = { -330.0f, -10.0f, -90.0f },
        .flags = 0x00002D09,
        .init = &mac_05_EVS_NpcInit_Toad_05,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 32767, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 32767, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00830201, .walk = 0x00830202, .run = 0x00830203, .chase = 0x00830203, .anim_4 = 0x00830201, .anim_5 = 0x00830201, .death = 0x00830206, .hit = 0x00830206, .anim_8 = 0x00830203, .anim_9 = 0x00830203, .anim_A = 0x00830203, .anim_B = 0x00830203, .anim_C = 0x00830203, .anim_D = 0x00830203, .anim_E = 0x00830203, .anim_F = 0x00830203 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A005B,
    },
    {
        .id = 14,
        .settings = &mac_05_NpcSettings_Toad_Stationary,
        .pos = { -50.0f, 0.0f, -400.0f },
        .flags = 0x00002D09,
        .init = &mac_05_EVS_NpcInit_Toad_06,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 32767, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 32767, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00830001, .walk = 0x00830002, .run = 0x00830003, .chase = 0x00830003, .anim_4 = 0x00830001, .anim_5 = 0x00830001, .death = 0x00830006, .hit = 0x00830006, .anim_8 = 0x00830003, .anim_9 = 0x00830003, .anim_A = 0x00830003, .anim_B = 0x00830003, .anim_C = 0x00830003, .anim_D = 0x00830003, .anim_E = 0x00830003, .anim_F = 0x00830003 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A005C,
    },
    {
        .id = 15,
        .settings = &mac_05_NpcSettings_Toad_Stationary,
        .pos = { 200.0f, 0.0f, -220.0f },
        .flags = 0x00002D09,
        .init = &mac_05_EVS_NpcInit_Toad_07,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 32767, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 32767, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .patrol = { .numPoints = 2, .points[0].x = -120, .points[0].y = 0, .points[0].z = -220, .points[1].x = 200, .points[1].y = 0, .points[1].z = -220, .points[2].x = 0, .points[2].y = 0, .points[2].z = 0, .points[3].x = 0, .points[3].y = 0, .points[3].z = 0, .points[4].x = 0, .points[4].y = 0, .points[4].z = 0, .points[5].x = 0, .points[5].y = 0, .points[5].z = 0, .points[6].x = 0, .points[6].y = 0, .points[6].z = 0, .points[7].x = 0, .points[7].y = 0, .points[7].z = 0, .points[8].x = 0, .points[8].y = 0, .points[8].z = 0, .points[9].x = 0, .points[9].y = 0, .points[9].z = 0, .moveSpeedOverride = -32767, .detectPos.x = 180, .detectPos.y = 20, .detectPos.z = -435, .detectSize.x = 10, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00830301, .walk = 0x00830302, .run = 0x00830303, .chase = 0x00830303, .anim_4 = 0x00830301, .anim_5 = 0x00830301, .death = 0x00830306, .hit = 0x00830306, .anim_8 = 0x00830303, .anim_9 = 0x00830303, .anim_A = 0x00830303, .anim_B = 0x00830303, .anim_C = 0x00830303, .anim_D = 0x00830303, .anim_E = 0x00830303, .anim_F = 0x00830303 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A005D,
    },
};

NpcData TTYD64_mac_05_NpcGroup_8024FDA8[] = {
    {
        .id = 7,
        .settings = &mac_05_NpcSettings_Toad_Stationary,
        .pos = { -85.0f, 0.0f, -520.0f },
        .flags = 0x00002D09,
        .init = &mac_05_EVS_NpcInit_Bartender,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00AC0001, .walk = 0x00AC0001, .run = 0x00AC0001, .chase = 0x00AC0001, .anim_4 = 0x00AC0001, .anim_5 = 0x00AC0001, .death = 0x00AC0001, .hit = 0x00AC0001, .anim_8 = 0x00AC0001, .anim_9 = 0x00AC0001, .anim_A = 0x00AC0001, .anim_B = 0x00AC0001, .anim_C = 0x00AC0001, .anim_D = 0x00AC0001, .anim_E = 0x00AC0001, .anim_F = 0x00AC0001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A0052,
    },
    {
        .id = 8,
        .settings = &mac_05_NpcSettings_Toad_Stationary,
        .pos = { 42.0f, 0.0f, -550.0f },
        .flags = 0x00002D09,
        .init = &mac_05_EVS_NpcInit_Toad_02,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00830001, .walk = 0x00830002, .run = 0x00830003, .chase = 0x00830003, .anim_4 = 0x00830001, .anim_5 = 0x00830001, .death = 0x00830006, .hit = 0x00830006, .anim_8 = 0x00830003, .anim_9 = 0x00830003, .anim_A = 0x00830003, .anim_B = 0x00830003, .anim_C = 0x00830003, .anim_D = 0x00830003, .anim_E = 0x00830003, .anim_F = 0x00830003 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A0056,
    },
    {
        .id = 9,
        .settings = &mac_05_NpcSettings_Toad_Stationary,
        .pos = { 208.0f, 0.0f, -530.0f },
        .flags = 0x00002D09,
        .init = &mac_05_EVS_NpcInit_Chanterelle,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00AD0001, .walk = 0x00AD0000, .run = 0x00AD0000, .chase = 0x00AD0000, .anim_4 = 0x00AD0000, .anim_5 = 0x00AD0000, .death = 0x00AD0000, .hit = 0x00AD0000, .anim_8 = 0x00AD0000, .anim_9 = 0x00AD0000, .anim_A = 0x00AD0000, .anim_B = 0x00AD0000, .anim_C = 0x00AD0000, .anim_D = 0x00AD0000, .anim_E = 0x00AD0000, .anim_F = 0x00AD0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A0057,
    },
    {
        .id = 10,
        .settings = &mac_05_NpcSettings_Toad_Stationary,
        .pos = { 158.0f, 0.0f, -555.0f },
        .flags = 0x00002D09,
        .init = &mac_05_EVS_NpcInit_ArtistToad,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x008E0001, .walk = 0x008E0001, .run = 0x008E0001, .chase = 0x008E0001, .anim_4 = 0x008E0001, .anim_5 = 0x008E0001, .death = 0x008E0001, .hit = 0x008E0001, .anim_8 = 0x008E0001, .anim_9 = 0x008E0001, .anim_A = 0x008E0001, .anim_B = 0x008E0001, .anim_C = 0x008E0001, .anim_D = 0x008E0001, .anim_E = 0x008E0001, .anim_F = 0x008E0001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A0059,
    },
    {
        .id = 11,
        .settings = &mac_05_NpcSettings_Toad_Stationary,
        .pos = { 92.0f, 0.0f, -500.0f },
        .flags = 0x00112D09,
        .init = &mac_05_EVS_NpcInit_TradeEventToad,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00830401, .walk = 0x00830402, .run = 0x00830403, .chase = 0x00830403, .anim_4 = 0x00830401, .anim_5 = 0x00830401, .death = 0x00830401, .hit = 0x00830406, .anim_8 = 0x00830403, .anim_9 = 0x00830403, .anim_A = 0x00830403, .anim_B = 0x00830403, .anim_C = 0x00830403, .anim_D = 0x00830403, .anim_E = 0x00830403, .anim_F = 0x00830403 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0x1A0007,
    },
};

EvtScript TTYD64_mac_05_Script_Init_Entry4 = {
    Set(LVar0, 0)
    ExecWait(mac_05_D_802525B0_864720)
    Set(LVar0, 0)
    ExecWait(mac_05_D_802522E0_864450)
    Set(LVar0, 90)
    ExecWait(mac_05_D_80252310_864480)
    Set(LVar0, 90)
    ExecWait(mac_05_D_80252580_8646F0)
    Set(LVar0, 0)
    Set(LVar1, 75)
    Set(LVar2, 90)
    Call(sam_11_UpdateHouseShowHide)
    Wait(5)
    Call(SetMusic, 0, 93, 0, 8)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_80250A5C = {
    Call(mac_05_UnkFloatFunc001, LVarC, LVar0, 30, 60, 30, 0, 0)
    Call(RotateModel, 94, LVar0, 1, 0, 0)
    Call(RotateModel, 92, LVar0, -1, 0, 0)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_80250AD4 = {
    Call(mac_05_UnkFloatFunc001, LVarC, LVar0, 0, 30, 30, 1, 0)
    SetF(LVar1, LVar0)
    DivF(LVar1, Float(3.0))
    Call(RotateModel, 96, LVar0, 0, 0, 1)
    Call(RotateGroup, 101, LVar1, 0, 0, -1)
    Call(TranslateModel, 88, -5, -68, 0)
    Call(TranslateModel, 90, -5, -68, 0)
    Call(TranslateModel, 94, 60, 29, -51)
    Call(TranslateModel, 92, 60, 29, 51)
    Call(RotateModel, 88, LVar1, 0, 0, -1)
    Call(RotateModel, 90, LVar1, 0, 0, -1)
    Call(RotateModel, 94, LVar1, 0, 0, -1)
    Call(RotateModel, 92, LVar1, 0, 0, -1)
    Call(TranslateModel, 88, 5, 68, 0)
    Call(TranslateModel, 90, 5, 68, 0)
    Call(TranslateModel, 94, -60, -29, 51)
    Call(TranslateModel, 92, -60, -29, -51)
    Call(mac_05_UnkFloatFunc001, LVarC, LVar0, 0, -40, 30, 1, 0)
    Call(TranslateModel, 102, LVar0, 0, 0)
    IfGe(LVarC, 30)
        Call(ModifyColliderFlags, 0, 21, 0x7FFFFE00)
        Call(ModifyColliderFlags, 1, 16, 0x7FFFFE00)
    EndIf
    Return
    End
};

EvtScript TTYD64_mac_05_Script_80250D58 = {
    Call(mac_05_UnkFloatFunc001, LVarC, LVar0, 0, -30, 8, 1, 0)
    AddF(LVar0, Float(30.0))
    SetF(LVar1, LVar0)
    DivF(LVar1, Float(3.0))
    Call(RotateModel, 96, LVar0, 0, 0, 1)
    Call(RotateGroup, 101, LVar1, 0, 0, -1)
    Call(TranslateModel, 88, -5, -68, 0)
    Call(TranslateModel, 90, -5, -68, 0)
    Call(TranslateModel, 94, 60, 29, -51)
    Call(TranslateModel, 92, 60, 29, 51)
    Call(RotateModel, 88, LVar1, 0, 0, -1)
    Call(RotateModel, 90, LVar1, 0, 0, -1)
    Call(RotateModel, 94, LVar1, 0, 0, -1)
    Call(RotateModel, 92, LVar1, 0, 0, -1)
    Call(TranslateModel, 88, 5, 68, 0)
    Call(TranslateModel, 90, 5, 68, 0)
    Call(TranslateModel, 94, -60, -29, 51)
    Call(TranslateModel, 92, -60, -29, -51)
    Call(mac_05_UnkFloatFunc001, LVarC, LVar0, 0, -40, 120, 1, 0)
    Call(TranslateModel, 102, LVar0, 0, 0)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_80250FB4 = {
    Call(GetNpcVar, 0, 0, LVar3)
    IfEq(LVar3, 0)
        Call(mac_05_UnkPlayerPosFunc)
        Call(PlaySoundAt, 0x8000004F, 0, LVar0, LVar1, LVar2)
        Call(mac_05_CreateWhaleGeyser, 0, LVar0, LVar1, LVar2, 0, -1, 0, 30)
        Call(SetNpcVar, 0, 0, LVar0)
    EndIf
    Call(GetNpcVar, 0, 0, LVar3)
    Call(mac_05_UnkPlayerPosFunc)
    Call(mac_05_SetWhaleGeyserPos, LVar3, LVar0, LVar1, LVar2)
    Call(mac_05_UnkFloatFunc001, LVarC, LVar0, 30, 60, 30, 0, 0)
    Call(RotateModel, 94, LVar0, 1, 0, 0)
    Call(RotateModel, 92, LVar0, -1, 0, 0)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_8025111C = {
    IfGe(LVarC, 0)
        IfLe(LVarC, 2)
            Call(EnableModel, 88, 0)
            Call(EnableModel, 90, 1)
            Return
        EndIf
    EndIf
    IfEq(LVarC, 15)
        Call(EnableModel, 88, 0)
        Call(EnableModel, 90, 1)
        Return
    EndIf
    IfEq(LVarC, 22)
        Call(EnableModel, 88, 0)
        Call(EnableModel, 90, 1)
        Return
    EndIf
    Call(EnableModel, 88, 1)
    Call(EnableModel, 90, 0)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_80251244 = {
    Set(LVar0, LVarC)
    Div(LVar0, 20)
    Mod(LVar0, 2)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(mac_05_UnkFloatFunc001, LVarC, LVar0, Float(-1.0), Float(1.0), 3, 0, 0)
    Call(TranslateModel, 96, LVar0, 0, 0)
    Call(TranslateGroup, 101, LVar0, 0, 0)
    Call(TranslateModel, 88, LVar0, 0, 0)
    Call(TranslateModel, 90, LVar0, 0, 0)
    Call(TranslateModel, 94, LVar0, 0, 0)
    Call(TranslateModel, 92, LVar0, 0, 0)
    Call(TranslateModel, 94, LVar0, 0, 0)
    Call(TranslateModel, 92, LVar0, 0, 0)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_802513AC = {
    Call(mac_05_UnkFloatFunc001, LVarC, LVar0, Float(-6.0), Float(6.0), 3, 0, 0)
    Call(mac_05_UnkFloatFunc001, LVarC, LVar1, Float(6.0), Float(-6.0), 2, 0, 0)
    Call(TranslateModel, 96, LVar0, LVar1, 0)
    Call(TranslateGroup, 101, LVar0, LVar1, 0)
    Call(TranslateModel, 88, LVar0, LVar1, 0)
    Call(TranslateModel, 90, LVar0, LVar1, 0)
    Call(TranslateModel, 94, LVar0, LVar1, 0)
    Call(TranslateModel, 92, LVar0, LVar1, 0)
    Call(TranslateModel, 94, LVar0, LVar1, 0)
    Call(TranslateModel, 92, LVar0, LVar1, 0)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_802514EC = {
    Set(LVar0, LVarC)
    Div(LVar0, 20)
    Mod(LVar0, 2)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(mac_05_UnkFloatFunc001, LVarC, LVar0, Float(-1.0), Float(1.0), 3, 0, 0)
    Call(TranslateModel, 96, LVar0, 0, 0)
    Call(TranslateGroup, 101, LVar0, 0, 0)
    Call(TranslateModel, 88, LVar0, 0, 0)
    Call(TranslateModel, 90, LVar0, 0, 0)
    Call(TranslateModel, 94, LVar0, 0, 0)
    Call(TranslateModel, 92, LVar0, 0, 0)
    Call(TranslateModel, 94, LVar0, 0, 0)
    Call(TranslateModel, 92, LVar0, 0, 0)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_80251654 = {
    Call(mac_05_UnkFloatFunc001, LVarC, LVar0, 30, 60, 30, 0, 0)
    Call(RotateModel, 94, LVar0, 1, 0, 0)
    Call(RotateModel, 92, LVar0, -1, 0, 0)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_802516CC = {
    Call(mac_05_UnkFloatFunc001, LVarC, LVar0, 0, 8, 3, 0, 0)
    Set(LVar1, LVar0)
    Div(LVar1, 3)
    Call(RotateModel, 96, LVar0, 0, 0, 1)
    Call(RotateGroup, 101, LVar1, 0, 0, -1)
    Call(TranslateModel, 88, -5, -68, 0)
    Call(TranslateModel, 90, -5, -68, 0)
    Call(TranslateModel, 94, 60, 29, -51)
    Call(TranslateModel, 92, 60, 29, 51)
    Call(RotateModel, 88, LVar1, 0, 0, -1)
    Call(RotateModel, 90, LVar1, 0, 0, -1)
    Call(RotateModel, 94, LVar1, 0, 0, -1)
    Call(RotateModel, 92, LVar1, 0, 0, -1)
    Call(TranslateModel, 88, 5, 68, 0)
    Call(TranslateModel, 90, 5, 68, 0)
    Call(TranslateModel, 94, -60, -29, 51)
    Call(TranslateModel, 92, -60, -29, -51)
    Set(LVar0, LVarC)
    Mul(LVar0, 2)
    Call(mac_05_UnkFloatFunc001, LVar0, LVar0, 30, 60, 3, 0, 0)
    Call(RotateModel, 94, LVar0, 1, 0, 0)
    Call(RotateModel, 92, LVar0, -1, 0, 0)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_8025194C = {
    SetGroup(0)
    Call(MakeLocalVertexCopy, 1, 98, 1)
    Call(SetCustomGfxBuilders, 1, (Bytecode) mac_05_unkAngleFunc002, 0)
    Call(SetModelCustomGfx, 98, 1, -1)
    Call(MakeLocalVertexCopy, 2, 99, 1)
    Call(SetCustomGfxBuilders, 2, (Bytecode) mac_05_unkAngleFunc003, 0)
    Call(SetModelCustomGfx, 99, 2, -1)
    Thread
        Label(0)
        Call(mac_05_UnkAngleFunc001, 0, LVar0, LVar1, LVar2)
        SubF(LVar0, -80)
        SubF(LVar1, -18)
        SubF(LVar2, 420)
        AddF(LVar0, 130)
        AddF(LVar1, -20)
        AddF(LVar2, 0)
        Call(TranslateModel, 102, LVar0, LVar1, LVar2)
        Call(TranslateModel, 88, LVar0, LVar1, LVar2)
        Call(TranslateModel, 90, LVar0, LVar1, LVar2)
        Call(TranslateModel, 96, LVar0, LVar1, LVar2)
        Call(TranslateModel, 94, LVar0, LVar1, LVar2)
        Call(TranslateModel, 92, LVar0, LVar1, LVar2)
        Call(TranslateGroup, 101, LVar0, LVar1, LVar2)
        Call(GetNpcYaw, 0, LVar0)
        MulF(LVar0, -1)
        AddF(LVar0, -90)
        Call(TranslateModel, 102, -100, 0, 0)
        Call(TranslateModel, 88, -100, 0, 0)
        Call(TranslateModel, 90, -100, 0, 0)
        Call(TranslateModel, 96, -100, 0, 0)
        Call(TranslateModel, 94, -100, 0, 0)
        Call(TranslateModel, 92, -100, 0, 0)
        Call(TranslateGroup, 101, -100, 0, 0)
        Call(TranslateModel, 102, 100, -1, 0)
        Call(TranslateModel, 88, -5, -68, 0)
        Call(TranslateModel, 90, -5, -68, 0)
        Call(TranslateModel, 96, 102, 4, 0)
        Call(TranslateModel, 94, 60, 29, -51)
        Call(TranslateModel, 92, 60, 29, 51)
        Call(RotateModel, 102, LVar0, 0, 1, 0)
        Call(RotateModel, 88, LVar0, 0, 1, 0)
        Call(RotateModel, 90, LVar0, 0, 1, 0)
        Call(RotateModel, 96, LVar0, 0, 1, 0)
        Call(RotateModel, 94, LVar0, 0, 1, 0)
        Call(RotateModel, 92, LVar0, 0, 1, 0)
        Call(RotateGroup, 101, LVar0, 0, 1, 0)
        Call(TranslateModel, 102, -100, 1, 0)
        Call(TranslateModel, 88, 5, 68, 0)
        Call(TranslateModel, 90, 5, 68, 0)
        Call(TranslateModel, 96, -102, -4, 0)
        Call(TranslateModel, 94, -60, -29, 51)
        Call(TranslateModel, 92, -60, -29, -51)
        Call(TranslateModel, 102, 100, 0, 0)
        Call(TranslateModel, 88, 100, 0, 0)
        Call(TranslateModel, 90, 100, 0, 0)
        Call(TranslateModel, 96, 100, 0, 0)
        Call(TranslateModel, 94, 100, 0, 0)
        Call(TranslateModel, 92, 100, 0, 0)
        Call(TranslateGroup, 101, 100, 0, 0)
        Call(GetNpcAnimation, 0, LVar0)
        IfNe(LVar0, LVarB)
            Set(LVarB, LVar0)
            Set(LVarC, 0)
            Call(ModifyColliderFlags, 1, 21, 0x7FFFFE00)
            Call(EnableModel, 88, 1)
            Call(EnableModel, 90, 0)
            IfNe(LVarB, 0xB60009)
                Call(GetNpcVar, 0, 0, LVar0)
                IfNe(LVar0, 0)
                    Call(PlaySound, 1091)
                    Call(StopTrackingSoundPos, 67)
                    Call(mac_05_DisposeWhaleGeyser, LVar0)
                    Call(SetNpcVar, 0, 0, 0)
                EndIf
            EndIf
            Switch(LVarB)
            CaseEq(0xB60003)
                Call(PlaySoundAtNpc, 0, 8247, 0)
                Set(LVarD, Ref(mac_05_D_80250D58_862EC8))
            CaseEq(0xB60000)
                Set(LVarD, Ref(mac_05_D_80250A5C_862BCC))
            CaseEq(0xB60002)
                Call(PlaySoundAtNpc, 0, 8246, 0)
                Set(LVarD, Ref(mac_05_D_80250AD4_862C44))
            CaseEq(0xB60001)
                Set(LVarD, Ref(mac_05_D_80251654_8637C4))
            CaseEq(0xB60004)
                Set(LVarD, Ref(mac_05_D_802516CC_86383C))
            CaseEq(0xB60005)
                Set(LVarD, Ref(mac_05_D_80250FA4_863114))
                Call(EnableModel, 88, 0)
                Call(EnableModel, 90, 0)
            CaseEq(0xB60006)
                Set(LVarD, Ref(mac_05_D_80251244_8633B4))
                Call(EnableModel, 88, 0)
                Call(EnableModel, 90, 0)
            CaseEq(0xB60007)
                Set(LVarD, Ref(mac_05_D_802513AC_86351C))
                Call(EnableModel, 88, 0)
                Call(EnableModel, 90, 0)
            CaseEq(0xB60008)
                Set(LVarD, Ref(mac_05_D_802514EC_86365C))
            CaseEq(0xB60009)
                Set(LVarD, Ref(mac_05_D_80250FB4_863124))
            CaseEq(0xB6000A)
                Set(LVarD, Ref(mac_05_D_8025110C_86327C))
            CaseEq(0xB6000C)
                Set(LVarD, Ref(mac_05_D_8025111C_86328C))
            EndSwitch
        EndIf
        ExecWait(LVarD)
        Add(LVarC, 1)
        IfGt(LVarC, 1000)
            Set(LVarC, 0)
        EndIf
        Goto(0)
    EndThread
    Return
    End
};

EvtScript TTYD64_mac_05_Script_OpenDoor_802522E0 = {
    Call(RotateModel, 45, LVar0, 0, -1, 0)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_MoveWalls_80252310 = {
    Set(LVar1, LVar0)
    Call(RotateModel, 55, LVar1, 1, 0, 0)
    Call(RotateModel, 54, LVar1, 1, 0, 0)
    Call(RotateModel, 56, LVar1, 1, 0, 0)
    Call(RotateModel, 57, LVar1, 1, 0, 0)
    Call(RotateModel, 58, LVar1, 1, 0, 0)
    Call(RotateModel, 59, LVar1, 1, 0, 0)
    Call(RotateModel, 60, LVar1, 1, 0, 0)
    Call(RotateModel, 61, LVar1, 1, 0, 0)
    Set(LVar1, LVar0)
    Call(RotateModel, 64, LVar1, 1, 0, 0)
    Call(RotateModel, 65, LVar1, 1, 0, 0)
    Call(RotateModel, 66, LVar1, 1, 0, 0)
    Set(LVar1, LVar0)
    MulF(LVar1, Float(-1.0))
    Call(RotateModel, 47, LVar1, 1, 0, 0)
    Call(RotateModel, 48, LVar1, 1, 0, 0)
    Call(RotateModel, 49, LVar1, 1, 0, 0)
    Call(RotateModel, 50, LVar1, 1, 0, 0)
    Call(RotateModel, 51, LVar1, 1, 0, 0)
    Call(RotateModel, 52, LVar1, 1, 0, 0)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_DropDoor_80252580 = {
    Call(RotateModel, 45, LVar0, 1, 0, 0)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_ToggleVis_802525B0 = {
    Switch(LVar0)
    CaseEq(0)
        Call(SetMusic, 0, 93, 0, 8)
        Call(StopSound, 0x80000058)
        Call(StopTrackingSoundPos, 57)
        Call(EnableGroup, 44, 1)
        Call(EnableModel, 69, 0)
        Call(EnableModel, 70, 0)
    CaseEq(3)
        Set(MapFlag(10), 0)
        Call(EnableGroup, 44, 0)
        Call(EnableModel, 69, 1)
        Call(EnableModel, 70, 1)
        Wait(5)
        Exec(mac_05_EVS_SetupMusic)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_mac_05_Script_8024487C = {
    BindTrigger(mac_05_EVS_ExitWalk_mac_04_1, 0x80000, 3, 1, 0)
    BindTrigger(TTYD64_mac_05_Script_ExitWalk_80244810, 128, 12, 1, 0)
    BindTrigger(TTYD64_mac_05_Script_Exit2, 128, 54, 1, 0)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_80252748 = {
    Call(MakeLocalVertexCopy, 3, 62, 1)
    Call(SetCustomGfxBuilders, 3, (Bytecode) mac_05_gfx_build_club_64, 0)
    Call(SetModelCustomGfx, 62, 3, -1)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_Interact_Bartender = {
    IfEq(GameFlag(4478), 0)
        IfGe(GameByte(0), -92)
            ExecWait(TTYD64_mac_05_Script_RevealEntrance)
            Set(GameFlag(4478), 1)
            Return
        EndIf
    EndIf
    Switch(GameByte(0))
    CaseLt(-53)
        IfEq(GameFlag(284), 0)
            Set(LVar0, 0x7000D)
        Else
            Set(LVar0, 0x7000E)
        EndIf
    CaseLt(-15)
        Set(LVar0, 0x7000F)
    CaseLt(-7)
        IfEq(GameFlag(290), 0)
            Set(LVar0, 0x70010)
        Else
            Set(LVar0, 0x70011)
        EndIf
    CaseLt(7)
        Set(LVar0, 0x70012)
    CaseLt(10)
        Set(LVar0, 0x70013)
    CaseLt(39)
        Set(LVar0, 0x70014)
    CaseLt(43)
        Set(LVar0, 0x70015)
    CaseLt(57)
        Set(LVar0, 0x70016)
    CaseLt(61)
        Set(LVar0, 0x70017)
    CaseLt(89)
        Set(LVar0, 0x70018)
    CaseLt(96)
        Set(LVar0, 0x70019)
    EndSwitch
    Call(SpeakToPlayer, -1, 0x830004, 0x830001, 0, LVar0)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_RevealEntrance = {
    Set(MapVar(0), 0)
    Call(SpeakToPlayer, -1, 0xAC0005, 0xAC0001, 0, (Bytecode) TTYD64_mac_05_String_Bartender_HelpMe)
    Call(InterpNpcYaw, -1, -90, 0)
    Wait(15)
    Call(SetNpcSpeed, -1, Float(2.0))
    Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Call(SetNpcAnimation, -1, 0xAC0003)
    Call(SetNpcFlagBits, -1, 0x4000000, 1)
    Call(NpcMoveTo, -1, LVar0, LVar2, 0)
    Call(SetNpcAnimation, -1, 0xAC0001)
    Call(PlaySound, 338)
    Wait(5)
    ExecWait(TTYD64_mac_05_Script_MoveFurniture)
    Call(InterpNpcYaw, -1, 90, 0)
    Wait(15)
    Call(SetNpcAnimation, -1, 0xAC0003)
    Call(NpcMoveTo, -1, -85, -520, 0)
    Call(SetNpcFlagBits, -1, 0x4000000, 0)
    Call(SetNpcAnimation, -1, 0xAC0001)
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(255.0))
    ExecWait(TTYD64_Script_FadeScreenOut)
    Call(SetNpcPos, -1, 0, -1000, 0)
    Wait(5)
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(5.0))
    Exec(TTYD64_Script_FadeScreenIn)
    Return
    End
};

NpcData TTYD64_mac_05_NpcGroup_Fuzzy[] = {
    {
        .id = 16,
        .settings = &TTYD64_mac_05_NPCSettings_Blank,
        .pos = { 212.0f, 96.0f, -404.0f },
        .flags = 0x00002020,
        .init = &TTYD64_mac_05_Script_Init_Fuzzy,
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

EvtScript TTYD64_mac_05_Script_MoveFurniture = {
    Call(ParentColliderToModel, 53, 34)
    Call(PlaySound, 82)
    Call(MakeLerp, 0, 70, 50, 0)
    Thread
        Call(ShakeCam, 0, 0, 50, Float(0.2001953125))
    EndThread
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, 34, LVar0, 0, 0)
        Call(TranslateGroup, 20, LVar0, 0, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(UpdateColliderTransform, 53)
    Call(StopSound, 82)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_ShowEmote_Bartender = {
    IfEq(GameFlag(4478), 0)
        IfGe(GameByte(0), -92)
            Call(GetNpcPos, 7, LVar0, LVar1, LVar2)
            Add(LVar1, 23)
            Call(PlayEffect_impl, 16, 3, 0, LVar0, LVar1, LVar2, 16, 20, 100, 0, 0, 0, 0, 0)
            Call(TTYD64_GetEffect, LVarF, LVar0)
            Set(MapVar(0), LVar0)
            Set(MapVar(1), MapVar(0))
            Thread
                Call(TTYD64_mac_05_Function_Bartender_FreezeEmoteFX)
            EndThread
        EndIf
    EndIf
    Return
    End
};

u8 TTYD64_mac_05_String_Bartender_HelpMe[] = {
    0xFC, 0x01, 0xFF, 0x05, 0x24, 0x28, 0x45, 0x59, 0xF7, 0x53, 0x4F, 0x4D,
    0x45, 0x4F, 0x4E, 0x45, 0xF7, 0x54, 0x4F, 0x4C, 0x44, 0xF7, 0x4D, 0x45,
    0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x48, 0x45, 0x4C, 0x50, 0x45, 0x44, 0xF0,
    0x2B, 0x4F, 0x4F, 0x50, 0x41, 0xF7, 0x36, 0x49, 0x4C, 0x4C, 0x41, 0x47,
    0x45, 0xF7, 0x57, 0x49, 0x54, 0x48, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0xF7,
    0x50, 0x52, 0x4F, 0x42, 0x4C, 0x45, 0x4D, 0x53, 0xF0, 0x57, 0x49, 0x54,
    0x48, 0xF7, 0x46, 0x55, 0x5A, 0x5A, 0x49, 0x45, 0x53, 0x0E, 0xF0, 0xF1,
    0xFB, 0x2C, 0x4F, 0x4F, 0x4B, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C,
    0xF7, 0x54, 0x4F, 0xF7, 0x42, 0x45, 0xF7, 0x48, 0x4F, 0x4E, 0x45, 0x53,
    0x54, 0xF7, 0x29, 0xF7, 0x4E, 0x45, 0x45, 0x44, 0xF0, 0x59, 0x4F, 0x55,
    0x52, 0xF7, 0x48, 0x45, 0x4C, 0x50, 0x0C, 0xF7, 0x42, 0x55, 0x54, 0xF7,
    0x57, 0x48, 0x41, 0x54, 0xF7, 0x49, 0x46, 0xF7, 0x57, 0x45, 0xF7, 0x54,
    0x41, 0x4C, 0x4B, 0xF0, 0x4D, 0x4F, 0x52, 0x45, 0xF7, 0x41, 0x42, 0x4F,
    0x55, 0x54, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7, 0x53, 0x4F, 0x4D, 0x45,
    0x57, 0x48, 0x45, 0x52, 0x45, 0xF7, 0x45, 0x4C, 0x53, 0x45, 0x1F, 0xF1,
    0xFD
};

EvtScript TTYD64_mac_05_Script_InitNewStuff = {
    IfEq(GameFlag(4478), 1)
        Call(ParentColliderToModel, 53, 34)
        Call(TranslateGroup, 34, 70, 0, 0)
        Call(TranslateGroup, 20, 70, 0, 0)
        Call(UpdateColliderTransform, 53)
    EndIf
    Exec(TTYD64_mac_05_Script_ShowEmote_Bartender)
    Return
    End
};

EvtScript TTYD64_mac_05_Script_802526E0 = {
    Call(CreateMapRoom, 2, Ref(mac_05_D_802522E0_864450), Ref(mac_05_D_80252310_864480), Ref(mac_05_D_80252580_8646F0), Ref(mac_05_D_802525B0_864720), 32, 37, 75, (Bytecode) mac_05_D_802526C8_864838)
    Set(LVar0, 3)
    Exec(mac_05_D_802525B0_864720)
    Exec(TTYD64_mac_05_Script_InitNewStuff)
    Return
    End
};

NpcGroupList TTYD64_mac_05_NpcGroupList_8025099C = {
    { .npcCount = 1, .npcs = &mac_05_NpcData_Kolorado, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = &mac_05_NpcData_Fuzzipede, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = &mac_05_NpcData_Fishmael, .battle = 0x0000, .stage = 0 },
    { .npcCount = 5, .npcs = TTYD64_mac_05_NpcGroup_8024FDA8, .battle = 0x0000, .stage = 0 },
    { .npcCount = 4, .npcs = TTYD64_mac_05_NpcGroup_8024F5E8, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_05_NpcGroup_8024E9FC, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_05_NpcGroup_Fuzzy, .battle = 0x0000, .stage = 0 },
    {},
};

NpcGroupList TTYD64_mac_05_NpcGroupList_802509F0 = {
    { .npcCount = 2, .npcs = mac_05_NpcData_JrTroopa_01, .battle = 0x0205, .stage = 0 },
    { .npcCount = 1, .npcs = &mac_05_NpcData_Kolorado, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = &mac_05_NpcData_Fishmael, .battle = 0x0000, .stage = 0 },
    { .npcCount = 5, .npcs = TTYD64_mac_05_NpcGroup_8024FDA8, .battle = 0x0000, .stage = 0 },
    { .npcCount = 4, .npcs = TTYD64_mac_05_NpcGroup_8024F5E8, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_05_NpcGroup_8024E9FC, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_05_NpcGroup_Fuzzy, .battle = 0x0000, .stage = 0 },
    {},
};

NpcGroupList TTYD64_mac_05_NpcGroupList_80250948 = {
    { .npcCount = 1, .npcs = &mac_05_NpcData_Fuzzipede, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = &mac_05_NpcData_Fishmael, .battle = 0x0000, .stage = 0 },
    { .npcCount = 5, .npcs = TTYD64_mac_05_NpcGroup_8024FDA8, .battle = 0x0000, .stage = 0 },
    { .npcCount = 4, .npcs = TTYD64_mac_05_NpcGroup_8024F5E8, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_05_NpcGroup_8024E9FC, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = &mac_05_NpcData_ChuckQuizmo, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_mac_05_NpcGroup_Fuzzy, .battle = 0x0000, .stage = 0 },
    {},
};

EvtScript TTYD64_mac_05_Script_Exit2 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 4)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "mac_08", 0)
    Wait(100)
    Return
    End
};

EntryList TTYD64_mac_05_EntryList = {
    { 426.0f, 0.0f, -426.0f, 225.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { -120.0f, 24.0f, 375.0f, 0.0f },
    { -280.0f, -10.0f, 371.0f, 270.0f },
    { -101.0f, 0.0f, -661.0f, 90.0f },
};

EvtScript TTYD64_mac_05_Script_Init_Fuzzy = {
    IfEq(GameFlag(4480), 1)
        Call(SetNpcPos, -1, 0, -1000, 0)
    EndIf
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_mac_05(void) {
    mac_05_settings.entryList = &TTYD64_mac_05_EntryList;
    mac_05_settings.entryCount = 5;
    Mod_ReplaceScript("TTYD64", &mac_05_EVS_Main, &TTYD64_mac_05_Script_Main);
    Mod_ReplaceScript("TTYD64", &mac_05_EVS_NpcInit_Bartender, &TTYD64_mac_05_Script_Init_8024D4E4);
    Mod_ReplaceScript("TTYD64", &mac_05_D_80250A5C_862BCC, &TTYD64_mac_05_Script_80250A5C);
    Mod_ReplaceScript("TTYD64", &mac_05_D_80250AD4_862C44, &TTYD64_mac_05_Script_80250AD4);
    Mod_ReplaceScript("TTYD64", &mac_05_D_80250D58_862EC8, &TTYD64_mac_05_Script_80250D58);
    Mod_ReplaceScript("TTYD64", &mac_05_D_80250FB4_863124, &TTYD64_mac_05_Script_80250FB4);
    Mod_ReplaceScript("TTYD64", &mac_05_D_8025111C_86328C, &TTYD64_mac_05_Script_8025111C);
    Mod_ReplaceScript("TTYD64", &mac_05_D_80251244_8633B4, &TTYD64_mac_05_Script_80251244);
    Mod_ReplaceScript("TTYD64", &mac_05_D_802513AC_86351C, &TTYD64_mac_05_Script_802513AC);
    Mod_ReplaceScript("TTYD64", &mac_05_D_802514EC_86365C, &TTYD64_mac_05_Script_802514EC);
    Mod_ReplaceScript("TTYD64", &mac_05_D_80251654_8637C4, &TTYD64_mac_05_Script_80251654);
    Mod_ReplaceScript("TTYD64", &mac_05_D_802516CC_86383C, &TTYD64_mac_05_Script_802516CC);
    Mod_ReplaceScript("TTYD64", &mac_05_EVS_SetupWhale, &TTYD64_mac_05_Script_8025194C);
    Mod_ReplaceScript("TTYD64", &mac_05_D_802522E0_864450, &TTYD64_mac_05_Script_OpenDoor_802522E0);
    Mod_ReplaceScript("TTYD64", &mac_05_D_80252310_864480, &TTYD64_mac_05_Script_MoveWalls_80252310);
    Mod_ReplaceScript("TTYD64", &mac_05_D_80252580_8646F0, &TTYD64_mac_05_Script_DropDoor_80252580);
    Mod_ReplaceScript("TTYD64", &mac_05_D_802525B0_864720, &TTYD64_mac_05_Script_ToggleVis_802525B0);
    Mod_ReplaceScript("TTYD64", &mac_05_EVS_BindExitTriggers, &TTYD64_mac_05_Script_8024487C);
    Mod_ReplaceScript("TTYD64", &mac_05_EVS_AnimateClub64Sign, &TTYD64_mac_05_Script_80252748);
    Mod_ReplaceScript("TTYD64", &mac_05_EVS_SetupRooms, &TTYD64_mac_05_Script_802526E0);
    TTYD64_maps_BindInlineMessage(TTYD64_mac_05_Script_RevealEntrance, TTYD64_mac_05_String_Bartender_HelpMe);
}
