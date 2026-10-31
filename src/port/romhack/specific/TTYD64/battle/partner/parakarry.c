#include "common.h"
#include "script_api/battle.h"
#include "effects.h"
#include "entity.h"
#include "battle/battle.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/battle/player_internal.h"

extern ActorBlueprint battle_partner_parakarry;
extern s32 battle_partner_parakarry_actionCommandTable[];
API_CALLABLE(AddCoin);
API_CALLABLE(AddGoalPos);
API_CALLABLE(AddItem);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(CheckButtonDown);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(DispatchEvent);
API_CALLABLE(EnableActorBlur);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(FlyToGoal);
API_CALLABLE(GetActionProgress);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetDistanceToGoal);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartnerActionQuality);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(InterruptActionCommand);
API_CALLABLE(JumpToGoal);
API_CALLABLE(JumpWithBounce);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(LoadItemScript);
API_CALLABLE(LoadStarPowerScript);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PartnerDamageEnemy);
API_CALLABLE(PartnerTestEnemy);
API_CALLABLE(PartnerYieldTurn);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActionDifficultyTable);
API_CALLABLE(SetActionHudPrepareTime);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetMessageText);
API_CALLABLE(SetupMashMeter);
API_CALLABLE(ShowActionHud);
API_CALLABLE(ShowMessageBox);
API_CALLABLE(StopSound);
API_CALLABLE(TTYD64_Player_AC_802A9000);
API_CALLABLE(TTYD64_Player_AddBadge);
API_CALLABLE(TTYD64_Player_partner4_ParcelCheck_TryToGetRandomItem);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(WaitForMessageBoxDone);
API_CALLABLE(action_command_air_raid_init);
API_CALLABLE(action_command_air_raid_start);
API_CALLABLE(action_command_body_slam_init);
API_CALLABLE(action_command_body_slam_start);
API_CALLABLE(action_command_jump_start);
API_CALLABLE(battle_partner_parakarry_FlyAround);
API_CALLABLE(battle_partner_parakarry_GetAirRaidDamage);
API_CALLABLE(battle_partner_parakarry_GetShellShotDamage);
API_CALLABLE(battle_partner_parakarry_ShellShotActionCommand);
EvtScript TTYD64_battle_partner_parakarry_EVS_80238C88;
EvtScript TTYD64_battle_partner_parakarry_EVS_80239430;
EvtScript TTYD64_battle_partner_parakarry_EVS_80239640;
extern u8 TTYD64_battle_partner_parakarry_String_Coin[];
extern ActorBlueprint TTYD64_battle_partner_parakarry;
EvtScript TTYD64_battle_partner_parakarry_EVS_80239950;
EvtScript TTYD64_battle_partner_parakarry_EVS_8023A0D4;
extern s32 TTYD64_battle_partner_parakarry_StatusTable_Parakarry_80239858[];
extern s32 TTYD64_battle_partner_parakarry_DefenseTable_Parakarry_8023984C[];
EvtScript TTYD64_battle_partner_parakarry_EVS_8023A4D4;
EvtScript TTYD64_battle_partner_parakarry_EVS_8023B1CC;
EvtScript TTYD64_battle_partner_parakarry_EVS_8023B824;
EvtScript TTYD64_battle_partner_parakarry_EVS_8023BC24;
EvtScript TTYD64_battle_partner_parakarry_EVS_8023C47C;
EvtScript TTYD64_battle_partner_parakarry_EVS_8023C884;
EvtScript TTYD64_battle_partner_parakarry_EVS_8023CABC;
EvtScript TTYD64_battle_partner_parakarry_EVS_8023CDAC;
EvtScript TTYD64_battle_partner_parakarry_EVS_8023CE58;
EvtScript TTYD64_battle_partner_parakarry_EVS_8023CEFC;
EvtScript TTYD64_battle_partner_parakarry_EVS_8023CF5C;
extern s32 TTYD64_battle_partner_parakarry_IdleAnimations_Parakarry_80239810[];
EvtScript TTYD64_battle_partner_parakarry_EVS_8023D014;
EvtScript TTYD64_battle_partner_parakarry_EVS_8023D050;
EvtScript TTYD64_battle_partner_parakarry_EVS_8023D084;
extern ActorPartBlueprint TTYD64_battle_partner_parakarry_PartsTable_Parakarry_80239904[];
EvtScript TTYD64_battle_partner_parakarry_EVS_8023D0D0;
EvtScript TTYD64_battle_partner_parakarry_EVS_8023D0E0;
EvtScript TTYD64_battle_partner_parakarry_EVS_8023D0F0;

// clang-format off
u8 TTYD64_battle_partner_parakarry_String_Coin[] = {
    0x23, 0x4F, 0x49, 0x4E, 0xFD,
};

ActorBlueprint TTYD64_battle_partner_parakarry = {
    .flags = 512,
    .type = 114,
    .level = 0,
    .maxHP = 99,
    .partCount = 1,
    .unk_0A = { 0, 0 },
    .partsData = TTYD64_battle_partner_parakarry_PartsTable_Parakarry_80239904,
    .initScript = &TTYD64_battle_partner_parakarry_EVS_8023CEFC,
    .statusTable = TTYD64_battle_partner_parakarry_StatusTable_Parakarry_80239858,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 38, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 30 },
    .statusTextOffset = { 10, 30 },
};

s32 TTYD64_battle_partner_parakarry_StatusTable_Parakarry_80239858[] = {
    1, 100, 2, 100, 6, 100, 9, 100,
    7, 100, 4, 100, 3, 100, 11, 100,
    5, 100, 10, 100, 8, 100, 31, 0,
    32, 0, 37, 0, 34, 0, 36, 0,
    35, 0, 33, 0, 38, 0, 39, 0,
    41, 0, 0,
};

s32 TTYD64_battle_partner_parakarry_DefenseTable_Parakarry_8023984C[] = {
    1, 1, 0,
};

s32 TTYD64_battle_partner_parakarry_IdleAnimations_Parakarry_80239810[] = {
    1, 786434, 12, 786432, 6, 786459, 9, 786460,
    8, 786432, 4, 786446, 13, 786457, 18, 786432,
    26, 786460, 7, 786432, 48, 786440, 0,
};

ActorPartBlueprint TTYD64_battle_partner_parakarry_PartsTable_Parakarry_80239904[] = {
    {
        .flags = 0,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 11, 28 },
        .opacity = 255,
        .idleAnimations = TTYD64_battle_partner_parakarry_IdleAnimations_Parakarry_80239810,
        .defenseTable = TTYD64_battle_partner_parakarry_DefenseTable_Parakarry_8023984C,
        .eventFlags = 16384,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
        .unk_1E = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

EvtScript TTYD64_battle_partner_parakarry_EVS_80238C88 = {
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786439)
    Wait(15)
    Call(InitTargetIterator)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786440)
    Call(battle_partner_parakarry_ShellShotActionCommand)
    Call(StopSound, 785)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8198)
    Call(GetActionProgress, LVar0)
    Call(PartnerTestEnemy, LVarA, 0, 20, 0, 1, 16)
    IfEq(LVarA, 6)
        Set(LVar0, -2)
    EndIf
    Switch(LVar0)
        CaseEq(1)
            Call(UseBattleCamPreset, 52)
            Call(MoveBattleCamOver, 5)
            Call(EnableActorBlur, ACTOR_PARTNER, 1)
            Call(SetGoalToTarget, ACTOR_PARTNER)
            Call(SetAnimation, ACTOR_PARTNER, -1, 786442)
            Call(FlyToGoal, ACTOR_PARTNER, 7, 0, 0)
            Call(EnableActorBlur, ACTOR_PARTNER, 0)
        CaseEq(-1)
            Call(UseBattleCamPreset, 52)
            Call(MoveBattleCamOver, 5)
            Call(EnableActorBlur, ACTOR_PARTNER, 1)
            Call(SetGoalToTarget, ACTOR_PARTNER)
            Call(AddGoalPos, ACTOR_PARTNER, 50, -50, 0)
            Call(SetAnimation, ACTOR_PARTNER, -1, 786442)
            Call(FlyToGoal, ACTOR_PARTNER, 7, 0, 100)
            Call(EnableActorBlur, ACTOR_PARTNER, 0)
        CaseEq(0)
            Call(UseBattleCamPreset, 52)
            Call(MoveBattleCamOver, 5)
            Call(EnableActorBlur, ACTOR_PARTNER, 1)
            Call(SetGoalToTarget, ACTOR_PARTNER)
            Call(AddGoalPos, ACTOR_PARTNER, 50, 50, 0)
            Call(SetAnimation, ACTOR_PARTNER, -1, 786442)
            Call(FlyToGoal, ACTOR_PARTNER, 7, 0, 0)
            Call(EnableActorBlur, ACTOR_PARTNER, 0)
        CaseEq(-2)
            Call(UseBattleCamPreset, 52)
            Call(MoveBattleCamOver, 5)
            Call(EnableActorBlur, ACTOR_PARTNER, 1)
            Call(SetGoalToTarget, ACTOR_PARTNER)
            Call(AddGoalPos, ACTOR_PARTNER, 40, 0, 0)
            Call(SetAnimation, ACTOR_PARTNER, -1, 786442)
            Call(FlyToGoal, ACTOR_PARTNER, 7, 0, 0)
            Call(EnableActorBlur, ACTOR_PARTNER, 0)
    EndSwitch
    Call(battle_partner_parakarry_GetShellShotDamage)
    Switch(LVar0)
        CaseGt(0)
            Call(PartnerDamageEnemy, LVar0, 0, 159, 0, LVarF, 112)
            Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_HIT_RATTLE)
        CaseDefault
            Set(LVar0, 2)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Label(10)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            IfEq(LFlag0, 1)
                SetConst(LVarA, 786445)
            Else
                SetConst(LVarA, 786455)
            EndIf
            ExecWait(TTYD64_battle_partner_parakarry_EVS_8023CABC)
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
            SetConst(LVarA, 786440)
            ExecWait(TTYD64_battle_partner_parakarry_EVS_8023C47C)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_80239430 = {
    Call(ShowActionHud, 1)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar0)
        CaseEq(8)
            Call(LoadStarPowerScript)
            ExecWait(LVar0)
            Return
        CaseEq(2)
            Call(LoadItemScript)
            ExecWait(LVar0)
            Return
    EndSwitch
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(149)
            Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
            Set(LVarE, 1)
            Set(LVarF, 2)
            ExecWait(TTYD64_battle_partner_parakarry_EVS_80239950)
        CaseEq(150)
            Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
            Set(LVarE, 2)
            Set(LVarF, 3)
            ExecWait(TTYD64_battle_partner_parakarry_EVS_80239950)
        CaseEq(151)
            Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
            Set(LVarE, 4)
            Set(LVarF, 5)
            ExecWait(TTYD64_battle_partner_parakarry_EVS_80239950)
        CaseEq(152)
            Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
            ExecWait(TTYD64_battle_partner_parakarry_EVS_80238C88)
        CaseEq(153)
            ExecWait(TTYD64_battle_partner_parakarry_EVS_8023A4D4)
        CaseEq(154)
            ExecWait(TTYD64_battle_partner_parakarry_EVS_8023B1CC)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_80239640 = {
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Call(TTYD64_StylishAddCount, LVar0)
        Call(TTYD64_WriteField, TTYD64_F_GACTIONCOMMANDSTATUS_60_1U, 0)
        Set(LVarA, 0)
        ExecWait(TTYD64_Script_DoStylishFX)
        Call(SetAnimation, ACTOR_PARTNER, -1, 786451)
        Wait(25)
    EndIf
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_80239950 = {
    Call(EnableIdleScript, ACTOR_PARTNER, 0)
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Exec(TTYD64_battle_partner_parakarry_EVS_8023D084)
    Call(SetActionDifficultyTable, Ref(battle_partner_parakarry_actionCommandTable))
    Call(UseBattleCamPreset, 52)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(InitTargetIterator)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786435)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(AddGoalPos, ACTOR_PARTNER, -20, 0, 0)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(5.0))
    Thread
        Wait(2)
        Exec(TTYD64_Script_InitTracker)
        Loop(0)
            Call(GetDistanceToGoal, ACTOR_SELF, LVar0)
            IfLe(LVar0, 20)
                Call(TTYD64_StylishPressed, LVar0)
                IfEq(LVar0, 1)
                    Call(TTYD64_StylishDisarm)
                    Call(TTYD64_StylishConsume)
                    Wait(1)
                    Goto(0)
                EndIf
                Loop(2)
                    ExecWait(TTYD64_Script_TimingTutor)
                    Call(TTYD64_StylishPressed, LVar0)
                    IfEq(LVar0, 1)
                        Wait(1)
                        Goto(0)
                    EndIf
                    Wait(1)
                EndLoop
                Wait(1)
                Goto(0)
            EndIf
            Wait(1)
        EndLoop
        Label(0)
    EndThread
    Call(FlyToGoal, ACTOR_PARTNER, 0, -10, 10)
    ExecGetTID(TTYD64_battle_partner_parakarry_EVS_80239640, LVar9)
    Loop(0)
        IsThreadRunning(LVar9, LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(SetAnimation, ACTOR_PARTNER, -1, 786432)
    Wait(3)
    Call(action_command_jump_start, 32, 3)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8196)
    Call(UseBattleCamPreset, 52)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786452)
    Call(AddGoalPos, ACTOR_PARTNER, 0, 10, 0)
    Call(FlyToGoal, ACTOR_PARTNER, 5, 0, 0)
    Wait(2)
    ChildThread
        Wait(3)
        Call(SetAnimation, ACTOR_PARTNER, -1, 786436)
    EndChildThread
    Call(UseBattleCamPreset, 52)
    Call(AddGoalPos, ACTOR_PARTNER, -26, 25, 0)
    Call(FlyToGoal, ACTOR_PARTNER, 20, -20, 6)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8197)
    Call(EnableActorBlur, ACTOR_PARTNER, 1)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(AddGoalPos, ACTOR_PARTNER, -10, 0, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786437)
    Call(FlyToGoal, ACTOR_PARTNER, 5, 0, 0)
    Call(PartnerTestEnemy, LVar0, 0, 20, 0, 1, 16)
    IfEq(LVar0, 6)
        ChildThread
            Wait(5)
            Call(SetAnimation, ACTOR_PARTNER, -1, 786433)
        EndChildThread
        Call(SetGoalToTarget, ACTOR_PARTNER)
        Call(AddGoalPos, ACTOR_PARTNER, 40, 10, 0)
        Call(FlyToGoal, ACTOR_PARTNER, 10, -20, 4)
        Wait(20)
        Call(EnableActorBlur, ACTOR_PARTNER, 0)
        Call(SetGoalToHome, ACTOR_PARTNER)
        Call(SetActorSpeed, ACTOR_PARTNER, Float(8.0))
        Call(SetAnimation, ACTOR_PARTNER, -1, 786435)
        Call(FlyToGoal, ACTOR_PARTNER, 0, -5, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 786434)
        Return
    EndIf
    Call(EnableActorBlur, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786438)
    Wait(2)
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(PartnerDamageEnemy, LVar0, 0, 4, 0, LVarF, 112)
        CaseDefault
            Call(PartnerDamageEnemy, LVar0, 0, 4, 0, LVarE, 48)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            SetConst(LVarA, 786455)
            ExecWait(TTYD64_battle_partner_parakarry_EVS_8023CABC)
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
            SetConst(LVarA, 786437)
            ExecWait(TTYD64_battle_partner_parakarry_EVS_8023C47C)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_PARTNER, 1)
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023A0D4 = {
    Set(LVar4, LVar0)
    Call(TTYD64_GetItemFlags, LVar4, LVar0, 0)
    IfFlag(LVar0, 64)
        Call(TTYD64_Player_AddBadge, LVar4, LVar1)
    Else
        IfFlag(LVar0, 512)
            Set(LVar1, 1)
        Else
            Call(AddItem, LVar4, LVar1)
        EndIf
    EndIf
    IfEq(LVar1, -1)
        Return
    EndIf
    Set(LVar0, 7)
    Exec(TTYD64_SetPartnerAnimation_Battle)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 45)
    Add(LVar2, 3)
    Set(LVar3, LVar1)
    Add(LVar3, 12)
    Call(PlayEffect_impl, 51, 1, LVar0, LVar3, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
    Call(MakeItemEntity, LVar4, LVar0, LVar1, LVar2, 1, 0)
    Set(LVar5, LVar0)
    Call(TTYD64_GetItemFlags, LVar4, LVar0, 0)
    IfFlag(LVar0, 64)
        Call(PlaySoundAtActor, ACTOR_SELF, SOUND_JINGLE_GOT_BADGE)
    Else
        IfFlag(LVar0, 512)
            Call(PlaySoundAtActor, ACTOR_SELF, SOUND_COIN_PICKUP)
            Call(AddCoin, 1)
        Else
            Call(PlaySoundAtActor, ACTOR_SELF, SOUND_JINGLE_GOT_ITEM)
        EndIf
    EndIf
    IfEq(LVar4, 343)
        Set(LVar0, TTYD64_battle_partner_parakarry_String_Coin)
    Else
        Call(TTYD64_GetItemGlobalData, LVar4, LVar0)
        Call(TTYD64_ReadPtrField, LVar0, TTYD64_F_ITEMDATA_0_4U, LVar0)
    EndIf
    Call(SetMessageText, LVar0, 0)
    Call(ShowMessageBox, 261, 60)
    Call(WaitForMessageBoxDone)
    Call(RemoveItemEntity, LVar5)
    Set(LVar0, 0)
    Exec(TTYD64_SetPartnerAnimation_Battle)
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023A4D4 = {
    Call(EnableIdleScript, ACTOR_PARTNER, 0)
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Exec(TTYD64_Script_NukeTracker)
    Wait(10)
    Call(UseBattleCamPreset, 52)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(InitTargetIterator)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786435)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(AddGoalPos, ACTOR_PARTNER, -36, -11, 0)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(5.0))
    Thread
        Wait(2)
        Exec(TTYD64_Script_InitTracker)
        Loop(0)
            Call(GetDistanceToGoal, ACTOR_SELF, LVar0)
            IfLe(LVar0, 20)
                Call(TTYD64_StylishPressed, LVar0)
                IfEq(LVar0, 1)
                    Call(TTYD64_StylishDisarm)
                    Call(TTYD64_StylishConsume)
                    Wait(1)
                    Goto(0)
                EndIf
                Loop(2)
                    ExecWait(TTYD64_Script_TimingTutor)
                    Call(TTYD64_StylishPressed, LVar0)
                    IfEq(LVar0, 1)
                        Wait(1)
                        Goto(0)
                    EndIf
                    Wait(1)
                EndLoop
                Wait(1)
                Goto(0)
            EndIf
            Wait(1)
        EndLoop
        Label(0)
    EndThread
    Call(FlyToGoal, ACTOR_PARTNER, 0, -10, 10)
    ExecGetTID(TTYD64_battle_partner_parakarry_EVS_80239640, LVar9)
    Loop(0)
        IsThreadRunning(LVar9, LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(SetAnimation, ACTOR_PARTNER, -1, 786432)
    Wait(3)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8196)
    Call(UseBattleCamPreset, 52)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786452)
    Call(AddGoalPos, ACTOR_PARTNER, 0, 10, 0)
    Call(FlyToGoal, ACTOR_PARTNER, 5, 0, 0)
    Wait(2)
    ChildThread
        Wait(3)
        Call(SetAnimation, ACTOR_PARTNER, -1, 786436)
    EndChildThread
    Call(LoadActionCommand, ACTION_COMMAND_BODY_SLAM)
    Call(action_command_body_slam_init)
    Call(SetupMashMeter, 1, 100, 0, 0, 0, 0)
    Call(UseBattleCamPreset, 52)
    Call(AddGoalPos, ACTOR_PARTNER, -10, 5, 0)
    Call(FlyToGoal, ACTOR_PARTNER, 20, -20, 6)
    Set(LFlag2, 0)
    Loop(60)
        Call(CheckButtonDown, 32768, LVar0)
        IfNe(LVar0, 0)
            Set(LFlag2, 1)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    IfEq(LFlag2, 1)
        Call(action_command_body_slam_start, 0, 102, 3, 1)
        Set(LFlag0, 0)
        Loop(100)
            Call(CheckButtonDown, 32768, LVar0)
            IfEq(LVar0, 0)
                Set(LFlag0, 1)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        IfEq(LFlag0, 1)
            Goto(10)
        EndIf
    Else
        Set(LFlag0, 0)
        Loop(100)
            Call(CheckButtonDown, 32768, LVar0)
            IfEq(LVar0, 0)
                Set(LFlag0, 1)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        IfEq(LFlag0, 1)
            Goto(10)
        EndIf
    EndIf
    Label(10)
    Wait(2)
    Call(InterruptActionCommand)
    Call(GetPartnerActionQuality, LVarA)
    Switch(LVarA)
        CaseGt(0)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8435)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 8)
            Add(LVar1, 32)
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 15, 0, 0, 0, 0, 0, 0, 0, 0)
            Add(LVar0, 2)
            Sub(LVar1, 1)
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 15, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(10)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8197)
    Call(EnableActorBlur, ACTOR_PARTNER, 1)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(AddGoalPos, ACTOR_PARTNER, -10, 0, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786437)
    Call(FlyToGoal, ACTOR_PARTNER, 5, 0, 0)
    Call(PartnerTestEnemy, LVar0, 0, 20, 0, 1, 16)
    IfLe(LVarA, 0)
        Set(LVar0, 6)
    EndIf
    IfEq(LVar0, 6)
        ChildThread
            Wait(5)
            Call(SetAnimation, ACTOR_PARTNER, -1, 786433)
        EndChildThread
        Call(SetGoalToTarget, ACTOR_PARTNER)
        Call(AddGoalPos, ACTOR_PARTNER, 40, 10, 0)
        Call(FlyToGoal, ACTOR_PARTNER, 10, -20, 4)
        Wait(20)
        ExecWait(TTYD64_battle_partner_parakarry_EVS_8023CE58)
        Return
    EndIf
    Call(PartnerTestEnemy, LVar0, 32768, 4, 0, 0, 48)
    IfEq(LVar0, -1)
        ChildThread
            Wait(5)
            Call(SetAnimation, ACTOR_PARTNER, -1, 786433)
        EndChildThread
        Call(SetGoalToTarget, ACTOR_PARTNER)
        Call(AddGoalPos, ACTOR_PARTNER, 40, 10, 0)
        Call(FlyToGoal, ACTOR_PARTNER, 10, -20, 4)
        Wait(20)
        ExecWait(TTYD64_battle_partner_parakarry_EVS_8023CE58)
        Return
    EndIf
    Set(LVarB, 0)
    Call(GetPartnerActionQuality, LVarA)
    Switch(LVarA)
        CaseGt(0)
            Call(GetOwnerTarget, LVar0, 0)
            Call(DispatchEvent, LVar0, EVENT_HIT)
            Call(TTYD64_GetActorPointer, LVar0, LVar1)
            Call(TTYD64_HasHeldItem, LVar1, LVar2)
            IfGt(LVar2, 0)
                Call(TTYD64_EnemyItemTable_SetStolenByte, LVar0)
                Call(TTYD64_GetHeldItem, LVar1, LVarB)
                Call(TTYD64_GetHeldItemEntity, LVar1, LVar3)
                Call(RemoveItemEntity, LVar3)
                Call(TTYD64_SetActorItemData, LVar0, 0)
            EndIf
        CaseDefault
    EndSwitch
    Call(EnableActorBlur, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786438)
    Wait(2)
    ChildThread
        Wait(5)
        Call(SetAnimation, ACTOR_PARTNER, -1, 786433)
    EndChildThread
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(AddGoalPos, ACTOR_PARTNER, 40, 10, 0)
    Call(FlyToGoal, ACTOR_PARTNER, 10, -20, 4)
    Wait(5)
    Call(EnableActorBlur, ACTOR_PARTNER, 0)
    Call(GetPartnerActionQuality, LVarA)
    Switch(LVarA)
        CaseGt(0)
            Call(GetOwnerTarget, LVar0, 0)
            IfEq(LVarB, 0)
                ExecWait(TTYD64_battle_partner_parakarry_EVS_8023CE58)
                Call(TTYD64_Player_partner4_ParcelCheck_TryToGetRandomItem, LVar0, LVar2)
                Set(LVar0, LVar2)
                ExecWait(TTYD64_battle_partner_parakarry_EVS_8023A0D4)
            Else
                ExecWait(TTYD64_battle_partner_parakarry_EVS_8023CE58)
                Set(LVar0, LVarB)
                ExecWait(TTYD64_battle_partner_parakarry_EVS_8023A0D4)
            EndIf
        CaseDefault
    EndSwitch
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Call(EnableIdleScript, ACTOR_PARTNER, 1)
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023B1CC = {
    Call(LoadActionCommand, ACTION_COMMAND_AIR_RAID)
    Call(action_command_air_raid_init)
    Call(SetupMashMeter, 4, 25, 50, 75, 100, 0)
    Call(SetActionHudPrepareTime, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar0, 70)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786435)
    Call(FlyToGoal, ACTOR_PARTNER, 15, -2, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786433)
    Call(action_command_air_raid_start, 0, 90, 3)
    Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
    Wait(2)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786436)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Sub(LVar0, 50)
    Add(LVar1, 30)
    Add(LVar2, 40)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_PARTNER, 10, -10, 10)
    Wait(2)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(EnableActorBlur, ACTOR_PARTNER, 1)
    ChildThread
        Loop(5)
            Wait(18)
            Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 10, 0, 0, 0, 0, 0, 0, 0, 0)
        EndLoop
    EndChildThread
    ChildThread
        Loop(5)
            Wait(18)
            Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 17, 1, LVar0, LVar1, LVar2, 40, 0, 0, 0, 0, 0, 0, 0, 0)
        EndLoop
    EndChildThread
    Call(SetAnimation, ACTOR_PARTNER, -1, 786442)
    Call(battle_partner_parakarry_FlyAround)
    Call(EnableActorBlur, ACTOR_PARTNER, 0)
    Call(UseBattleCamPreset, 3)
    Call(MoveBattleCamOver, 20)
    Call(GetActionProgress, LVar0)
    Call(battle_partner_parakarry_GetAirRaidDamage)
    Call(InitTargetIterator)
    Label(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(PartnerTestEnemy, LVar0, 0, 20, 0, 1, 16)
    IfEq(LVar0, 6)
        Goto(11)
    EndIf
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(99)
            Call(PartnerDamageEnemy, LVar0, 805306368, 149, 0, LVarF, 112)
            Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_HIT_RATTLE)
        CaseDefault
            Call(PartnerDamageEnemy, LVar0, 805306368, 149, 0, LVarF, 48)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_NONE)
    Wait(5)
    Label(11)
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(10)
    EndIf
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(99)
            Call(UseBattleCamPreset, 4)
        CaseDefault
            Call(UseBattleCamPreset, 51)
    EndSwitch
    ChildThread
        ExecWait(TTYD64_battle_partner_parakarry_EVS_8023D050)
        Call(SetActorPos, ACTOR_PARTNER, -200, 50, 0)
        Call(SetGoalToHome, ACTOR_PARTNER)
        Call(SetActorSpeed, ACTOR_PARTNER, Float(12.0))
        Call(SetAnimation, ACTOR_PARTNER, -1, 786435)
        Call(FlyToGoal, ACTOR_PARTNER, 0, 0, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 786434)
    EndChildThread
    Jump(TTYD64_battle_partner_parakarry_EVS_8023C884)
    Call(PartnerYieldTurn)
    Wait(20)
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023B824 = {
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(InterruptActionCommand)
    Call(GetLastEvent, ACTOR_PARTNER, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, -1)
            Set(LVar1, 786446)
            ExecWait(EVS_Enemy_Hit)
            Call(SetAnimation, ACTOR_PARTNER, -1, 786433)
        EndCaseGroup
        CaseOrEq(23)
        CaseOrEq(25)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8332)
            Call(TTYD64_GetPartnerExtraBattleData_API, 14, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 786444)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 786440)
            EndIf
            ExecWait(EVS_Enemy_NoDamageHit)
        EndCaseGroup
        CaseEq(42)
            SetConst(LVar0, 1)
            SetConst(LVar1, 786445)
            Set(LVar2, 22)
            ExecWait(EVS_Partner_SpikeContact)
        CaseEq(44)
            SetConst(LVar1, 786447)
            Set(LVar2, 22)
            SetConst(LVar3, 786448)
            ExecWait(EVS_Partner_BurnContact)
        CaseOrEq(14)
        CaseOrEq(15)
            SetConst(LVar1, 786447)
            SetConst(LVar2, 786448)
            ExecWait(EVS_Partner_BurnHit)
        EndCaseGroup
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 786445)
            Set(LVar2, 22)
            ExecWait(EVS_Partner_ShockHit)
        CaseEq(51)
        CaseEq(52)
            SetConst(LVar1, 786434)
            SetConst(LVar2, 786435)
            Set(LVar3, 4)
            ExecWait(EVS_Partner_Recover)
        CaseOrEq(24)
        CaseOrEq(26)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8332)
            SetConst(LVar0, 1)
            SetConst(LVar1, 786444)
            ExecWait(EVS_Enemy_NoDamageHit)
            Wait(10)
            Call(SetAnimation, ACTOR_PARTNER, -1, 786443)
        EndCaseGroup
        CaseEq(32)
            Set(LVar0, -1)
            Set(LVar1, 786446)
            ExecWait(TTYD64_PartnerDies)
            Return
        CaseEq(TTYD64_EVENT_SUPERGUARD)
            Set(LVar0, -1)
            Set(LVar1, 786458)
            ExecWait(TTYD64_DoSuperguard)
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023BC24 = {
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(6.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 786435)
    Call(SetActorYaw, ACTOR_PARTNER, 0)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786434)
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023C47C = {
    Call(GetMenuSelection, 0, 0, LVar0)
    IfGt(LVar0, 151)
        Exec(TTYD64_Script_NukeTracker)
        Thread
            Wait(1)
            Exec(TTYD64_Script_InitTracker)
        EndThread
    EndIf
    Call(PartnerYieldTurn)
    Call(UseBattleCamPreset, 4)
    Call(SetAnimation, ACTOR_PARTNER, -1, LVarA)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.4))
    Call(AddGoalPos, ACTOR_PARTNER, -50, 0, 0)
    Call(JumpToGoal, ACTOR_PARTNER, 15, false, false, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786432)
    ChildThread
        Wait(4)
        Call(SetAnimation, ACTOR_PARTNER, -1, 786435)
    EndChildThread
    Call(AddGoalPos, ACTOR_PARTNER, -30, 0, 0)
    Call(JumpWithBounce, ACTOR_PARTNER, 5, Float(4.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 786433)
    Call(GetMenuSelection, 0, 0, LVar0)
    IfGt(LVar0, 151)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 0)
            Loop(4)
                ExecWait(TTYD64_Script_TimingTutor)
                Call(TTYD64_StylishPressed, LVar0)
                IfEq(LVar0, 1)
                    Call(TTYD64_StylishDisarm)
                    Call(TTYD64_StylishConsume)
                    Call(TTYD64_StylishAddCount, LVar0)
                    Set(LVarA, 0)
                    ExecWait(TTYD64_Script_DoStylishFX)
                    Call(SetAnimation, ACTOR_PARTNER, -1, 786451)
                    Wait(25)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        Else
            Wait(4)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
        EndIf
    EndIf
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(8.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 786435)
    Call(FlyToGoal, ACTOR_PARTNER, 0, -5, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786434)
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023C884 = {
    Wait(20)
    Call(GetPartnerActionQuality, LVar0)
    IfEq(LVar0, 100)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Wait(4)
            Goto(0)
        EndIf
        Loop(4)
            ExecWait(TTYD64_Script_TimingTutor)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                Call(TTYD64_StylishDisarm)
                Call(TTYD64_StylishConsume)
                Call(TTYD64_StylishAddCount, LVar0)
                Set(LVarA, 0)
                ExecWait(TTYD64_Script_DoStylishFX)
                Call(SetAnimation, ACTOR_PARTNER, -1, 786451)
                Wait(25)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndIf
    Label(0)
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786434)
    Wait(20)
    Call(PartnerYieldTurn)
    Wait(20)
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023CABC = {
    Call(PartnerYieldTurn)
    Call(UseBattleCamPreset, 51)
    Call(SetAnimation, ACTOR_PARTNER, -1, LVarA)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.0))
    Call(AddGoalPos, ACTOR_PARTNER, -30, 0, 0)
    Call(JumpToGoal, ACTOR_PARTNER, 15, false, false, false)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786432)
    ChildThread
        Wait(4)
        Call(SetAnimation, ACTOR_PARTNER, -1, 786435)
    EndChildThread
    Call(AddGoalPos, ACTOR_PARTNER, -20, 0, 0)
    Call(JumpWithBounce, ACTOR_PARTNER, 5, Float(4.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 786433)
    Wait(2)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(8.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 786435)
    Call(FlyToGoal, ACTOR_PARTNER, 0, -5, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786434)
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023CDAC = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(1)
            ExecWait(TTYD64_battle_partner_parakarry_EVS_8023D0E0)
        CaseEq(0)
            ExecWait(TTYD64_battle_partner_parakarry_EVS_80239430)
        CaseEq(5)
            ExecWait(TTYD64_battle_partner_parakarry_EVS_8023CF5C)
        CaseEq(3)
            ExecWait(TTYD64_battle_partner_parakarry_EVS_8023D014)
        CaseEq(7)
            ExecWait(TTYD64_battle_partner_parakarry_EVS_8023BC24)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023CE58 = {
    Call(UseBattleCamPreset, 2)
    Call(EnableActorBlur, ACTOR_PARTNER, 0)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(10.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 786435)
    Call(FlyToGoal, ACTOR_PARTNER, 0, -5, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 786434)
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023CEFC = {
    Call(BindTakeTurn, ACTOR_PARTNER, Ref(TTYD64_battle_partner_parakarry_EVS_8023CDAC))
    Call(BindIdle, ACTOR_PARTNER, Ref(TTYD64_battle_partner_parakarry_EVS_8023D0F0))
    Call(BindHandleEvent, ACTOR_PARTNER, Ref(TTYD64_battle_partner_parakarry_EVS_8023B824))
    Call(BindHandlePhase, ACTOR_PARTNER, Ref(TTYD64_battle_partner_parakarry_EVS_8023D0D0))
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023CF5C = {
    SetConst(LVar0, 1)
    SetConst(LVar1, 786451)
    SetConst(LVar2, 786434)
    SetConst(LVar3, 786433)
    ExecWait(EVS_Partner_Celebrate)
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023D014 = {
    SetConst(LVar0, 1)
    SetConst(LVar1, 786435)
    ExecWait(EVS_Partner_RunAway)
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023D050 = {
    Exec(TTYD64_Script_NukeTracker)
    Wait(10)
    Exec(TTYD64_Script_InitTracker)
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023D084 = {
    Call(TTYD64_Player_AC_802A9000)
    Exec(TTYD64_Script_NukeTracker)
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023D0D0 = {
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023D0E0 = {
    Return
    End
};

EvtScript TTYD64_battle_partner_parakarry_EVS_8023D0F0 = {
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_partner_parakarry(void) {
    TTYD64_Player_BindMessage(
        TTYD64_battle_partner_parakarry_EVS_8023A0D4, TTYD64_battle_partner_parakarry_String_Coin
    );
    Mod_ReplaceActorBlueprint("TTYD64", &battle_partner_parakarry, &TTYD64_battle_partner_parakarry);
}
