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

extern ActorBlueprint battle_partner_watt;
API_CALLABLE(AddBattleCamDist);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(CheckButtonDown);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(EnableActorBlur);
API_CALLABLE(FlyToGoal);
API_CALLABLE(GetActionProgress);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartnerActionQuality);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(InterruptActionCommand);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(LoadItemScript);
API_CALLABLE(LoadStarPowerScript);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PartnerAfflictEnemy);
API_CALLABLE(PartnerDamageEnemy);
API_CALLABLE(PartnerTestEnemy);
API_CALLABLE(PartnerYieldTurn);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlayLoopingSoundAtActor);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerHopToGoal);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActionHudPrepareTime);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPaletteEffect);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetDamageSource);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(SetupMashMeter);
API_CALLABLE(ShowActionHud);
API_CALLABLE(ShowVariableMessageBox);
API_CALLABLE(StopLoopingSoundAtActor);
API_CALLABLE(TTYD64_Player_partner6_WattFXBounce);
API_CALLABLE(TTYD64_Player_partner6_WattFXDisable);
API_CALLABLE(TTYD64_Player_partner6_WattFXDisableBounce);
API_CALLABLE(TTYD64_Player_partner6_WattFXEnable);
API_CALLABLE(TTYD64_Player_partner6_WattFXRemove);
API_CALLABLE(TTYD64_Player_partner6_WattFXSetEffect);
API_CALLABLE(TTYD64_Player_partner6_Watt_UpdateSparkles);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(WaitForMessageBoxDone);
API_CALLABLE(action_command_body_slam_init);
API_CALLABLE(action_command_body_slam_start);
API_CALLABLE(action_command_mega_shock_init);
API_CALLABLE(action_command_mega_shock_start);
API_CALLABLE(action_command_power_shock_init);
API_CALLABLE(action_command_power_shock_start);
API_CALLABLE(action_command_three_chances_init);
API_CALLABLE(action_command_three_chances_start);
API_CALLABLE(battle_partner_watt_AverageTargetParalyzeChance);
API_CALLABLE(battle_partner_watt_ElectroDashFX);
API_CALLABLE(battle_partner_watt_ElectroDashFXDisable);
API_CALLABLE(battle_partner_watt_MegaShockFX);
API_CALLABLE(battle_partner_watt_PowerShockDischargeFX);
API_CALLABLE(battle_partner_watt_PowerShockFX);
API_CALLABLE(battle_partner_watt_SetBackgroundAlpha);
API_CALLABLE(battle_partner_watt_TargetParalyzeChance);
API_CALLABLE(battle_partner_watt_TurboChargeFX);
API_CALLABLE(battle_partner_watt_TurboChargeUnwindWatt);
API_CALLABLE(battle_partner_watt_UnkBackgroundFunc3);
EvtScript TTYD64_battle_partner_watt_EVS_80238000;
EvtScript TTYD64_battle_partner_watt_EVS_802382A4;
EvtScript TTYD64_battle_partner_watt_EVS_80238338;
EvtScript TTYD64_battle_partner_watt_EVS_80238F84;
extern s32 TTYD64_battle_partner_watt_DefenseTable_Watt_80238FCC[];
extern ActorBlueprint TTYD64_battle_partner_watt;
EvtScript TTYD64_battle_partner_watt_EVS_802390D8;
extern s32 TTYD64_battle_partner_watt_StatusTable_Watt_80238FE0[];
EvtScript TTYD64_battle_partner_watt_EVS_80239A10;
EvtScript TTYD64_battle_partner_watt_EVS_8023A4D8;
EvtScript TTYD64_battle_partner_watt_EVS_8023AC2C;
EvtScript TTYD64_battle_partner_watt_EVS_8023B09C;
EvtScript TTYD64_battle_partner_watt_EVS_8023B2A0;
EvtScript TTYD64_battle_partner_watt_EVS_8023B3E4;
EvtScript TTYD64_battle_partner_watt_EVS_8023B460;
extern s32 TTYD64_battle_partner_watt_IdleAnimations_Watt_80238F90[];
EvtScript TTYD64_battle_partner_watt_EVS_8023B524;
extern ActorPartBlueprint TTYD64_battle_partner_watt_PartsTable_Watt_8023908C[];
EvtScript TTYD64_battle_partner_watt_EVS_8023B970;
EvtScript TTYD64_battle_partner_watt_EVS_8023C370;
EvtScript TTYD64_battle_partner_watt_EVS_8023CD28;
EvtScript TTYD64_battle_partner_watt_EVS_8023CE9C;
EvtScript TTYD64_battle_partner_watt_EVS_8023CF88;
EvtScript TTYD64_battle_partner_watt_EVS_8023D000;
EvtScript TTYD64_battle_partner_watt_EVS_8023D060;
EvtScript TTYD64_battle_partner_watt_EVS_8023D0B8;
EvtScript TTYD64_battle_partner_watt_EVS_8023D0E0;

// clang-format off
s32 TTYD64_battle_partner_watt_DefenseTable_Watt_80238FCC[] = {
    1, 0, 12, 99, 0,
};

ActorBlueprint TTYD64_battle_partner_watt = {
    .flags = 512,
    .type = 116,
    .level = 0,
    .maxHP = 99,
    .partCount = 1,
    .unk_0A = { 0, 0 },
    .partsData = TTYD64_battle_partner_watt_PartsTable_Watt_8023908C,
    .initScript = &TTYD64_battle_partner_watt_EVS_8023D000,
    .statusTable = TTYD64_battle_partner_watt_StatusTable_Watt_80238FE0,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 34, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

s32 TTYD64_battle_partner_watt_StatusTable_Watt_80238FE0[] = {
    1, 100, 2, 100, 6, 100, 9, 100,
    7, 100, 4, 100, 3, 100, 11, 100,
    5, 100, 10, 100, 8, 100, 31, 0,
    32, 0, 37, 0, 34, 0, 36, 0,
    35, 0, 33, 0, 38, 0, 39, 0,
    41, 0, 0,
};

s32 TTYD64_battle_partner_watt_IdleAnimations_Watt_80238F90[] = {
    1, 917506, 12, 917504, 6, 917524, 9, 917525,
    8, 917504, 4, 917519, 13, 917519, 18, 917504,
    26, 917525, 7, 917504, 48, 917523, 0,
};

ActorPartBlueprint TTYD64_battle_partner_watt_PartsTable_Watt_8023908C[] = {
    {
        .flags = 8388608,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 10, 22 },
        .opacity = 255,
        .idleAnimations = TTYD64_battle_partner_watt_IdleAnimations_Watt_80238F90,
        .defenseTable = TTYD64_battle_partner_watt_DefenseTable_Watt_80238FCC,
        .eventFlags = 128,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
        .unk_1E = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

EvtScript TTYD64_battle_partner_watt_EVS_80238000 = {
    Call(GetMenuSelection, 0, 0, LVar0)
    IfLe(LVar0, 163)
        Exec(TTYD64_Script_InitTracker)
    EndIf
    Call(UseBattleCamPreset, 4)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetAnimation, ACTOR_PARTNER, -1, 917507)
    Call(FlyToGoal, ACTOR_PARTNER, 30, 0, 10)
    Call(GetMenuSelection, 0, 0, LVar0)
    IfLe(LVar0, 163)
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
                    Call(UseIdleAnimation, ACTOR_PARTNER, false)
                    Call(SetAnimation, ACTOR_PARTNER, -1, 917512)
                    Wait(25)
                    Call(UseIdleAnimation, ACTOR_PARTNER, true)
                    Return
                EndIf
                Wait(1)
            EndLoop
        EndIf
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
    EndIf
    Call(SetAnimation, ACTOR_PARTNER, -1, 917505)
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_802382A4 = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_battle_partner_watt_EVS_8023CD28)
        CaseEq(5)
            ExecWait(TTYD64_battle_partner_watt_EVS_8023CF88)
        CaseEq(3)
            ExecWait(TTYD64_battle_partner_watt_EVS_8023D060)
        CaseEq(7)
            ExecWait(TTYD64_battle_partner_watt_EVS_80238F84)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_80238338 = {
    Loop(30)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_80238F84 = {
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(TTYD64_Player_partner6_WattFXEnable)
    Call(TTYD64_Player_partner6_WattFXSetEffect, 1)
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetActorSpeed, ACTOR_PARTNER, Float(6.0))
    Call(SetAnimation, ACTOR_PARTNER, -1, 917507)
    Call(SetActorYaw, ACTOR_PARTNER, 0)
    Call(RunToGoal, ACTOR_PARTNER, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 917505)
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Call(TTYD64_Player_partner6_WattFXSetEffect, 0)
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_802390D8 = {
    Call(LoadActionCommand, ACTION_COMMAND_POWER_SHOCK)
    Exec(TTYD64_Script_NukeTracker)
    Call(action_command_power_shock_init)
    Call(SetupMashMeter, 1, 100, 0, 0, 0, 0)
    Call(SetActionHudPrepareTime, 0)
    Set(LFlagF, 0)
    Call(GetOwnerTarget, LVarA, LVarB)
    Call(GetActorFlags, LVarA, LVar0)
    IfFlag(LVar0, 2048)
        Set(LFlagF, 1)
    EndIf
    Call(UseBattleCamPreset, 47)
    Call(MoveBattleCamOver, 40)
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(SetAnimation, ACTOR_PARTNER, -1, 917507)
    Call(TTYD64_Player_partner6_WattFXSetEffect, 1)
    Call(AddGoalPos, ACTOR_PARTNER, -15, -10, 0)
    Call(FlyToGoal, ACTOR_PARTNER, 30, 0, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 917505)
    Call(PartnerTestEnemy, LVar0, 0, 4, 0, 1, 16)
    Call(AddBattleCamDist, -100)
    Call(MoveBattleCamOver, 80)
    Call(TTYD64_Player_partner6_WattFXDisable)
    Call(battle_partner_watt_TargetParalyzeChance)
    Call(action_command_power_shock_start, 0, 72, 3, LVar0)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar1, 15)
    Add(LVar2, 5)
    Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(1.0), 75, 0, 0, 0, 0, 0, 0, 0)
    Call(battle_partner_watt_UnkBackgroundFunc3)
    Set(LVar9, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 917510)
    Call(SetActorPaletteEffect, ACTOR_SELF, 1, 10)
    Thread
        Loop(75)
            Add(LVar9, 3)
            Call(battle_partner_watt_SetBackgroundAlpha, LVar9)
            Wait(1)
        EndLoop
    EndThread
    Wait(75)
    Call(SetActorPaletteEffect, ACTOR_SELF, 1, 9)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_WATT_POWER_SHOCK)
    Thread
        SetF(LVar0, Float(1.0))
        Loop(3)
            AddF(LVar0, Float(0.4))
            Call(SetActorScale, ACTOR_PARTNER, LVar0, LVar0, LVar0)
            Wait(1)
        EndLoop
        Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Add(LVar1, 8)
        Call(PlayEffect_impl, 107, 6, LVar0, LVar1, LVar2, Float(1.7998), 30, 0, 0, 0, 0, 0, 0, 0)
    EndThread
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Add(LVar2, 5)
    Call(battle_partner_watt_PowerShockFX, LVar0, LVar1, LVar2)
    Call(UseBattleCamPreset, 47)
    Call(AddBattleCamDist, 100)
    Call(MoveBattleCamOver, 5)
    Thread
        Call(battle_partner_watt_PowerShockDischargeFX, 20)
    EndThread
    Loop(3)
        Call(battle_partner_watt_SetBackgroundAlpha, 0)
        Wait(1)
        Call(battle_partner_watt_SetBackgroundAlpha, 200)
        Wait(1)
    EndLoop
    Call(battle_partner_watt_SetBackgroundAlpha, 0)
    Wait(10)
    Call(TTYD64_Player_partner6_WattFXEnable)
    Call(TTYD64_Player_partner6_WattFXSetEffect, 0)
    Exec(TTYD64_Script_InitTracker)
    Thread
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 20, 0)
        SetF(LVar0, Float(2.2))
        Loop(12)
            SubF(LVar0, Float(0.0996))
            Call(SetActorScale, ACTOR_PARTNER, LVar0, LVar0, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 917505)
    EndThread
    Call(PartnerTestEnemy, LVar0, 0, 4, 0, 1, 16)
    IfEq(LVar0, 6)
        Wait(15)
        ExecWait(TTYD64_battle_partner_watt_EVS_8023B3E4)
        Return
    EndIf
    IfNe(LFlagF, 1)
        Call(AddGoalPos, ACTOR_PARTNER, -25, 10, 0)
        Call(FlyToGoal, ACTOR_PARTNER, 15, -10, 10)
    Else
        Call(AddGoalPos, ACTOR_PARTNER, -25, -10, 0)
        Call(FlyToGoal, ACTOR_PARTNER, 15, -10, 10)
    EndIf
    ExecGetTID(TTYD64_battle_partner_watt_EVS_8023B09C, LVar9)
    Loop(0)
        IsThreadRunning(LVar9, LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(GetActionProgress, LVarF)
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(PartnerAfflictEnemy, LVar0, 1342177312, 0, (Bytecode) (s32) 0xC0010300, 254, 0, 112)
        CaseDefault
            Call(PartnerAfflictEnemy, LVar0, 1342177312, 0, (Bytecode) (s32) 0xC0010300, 255, 0, 48)
    EndSwitch
    Call(PartnerYieldTurn)
    Wait(30)
    Switch(LVar0)
        CaseOrEq(1)
        CaseOrEq(3)
            ExecWait(TTYD64_battle_partner_watt_EVS_80238000)
        EndCaseGroup
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_partner_watt_EVS_8023B3E4)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_80239A10 = {
    Call(LoadActionCommand, ACTION_COMMAND_BODY_SLAM)
    Exec(TTYD64_Script_NukeTracker)
    Call(action_command_body_slam_init)
    Call(SetupMashMeter, 1, 100, 0, 0, 0, 0)
    Wait(10)
    Call(UseBattleCamPreset, 48)
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(AddGoalPos, ACTOR_PARTNER, -20, 0, 0)
    Set(LFlag2, 0)
    Loop(60)
        Call(CheckButtonDown, 32768, LVar0)
        IfNe(LVar0, 0)
            Set(LFlag2, 1)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(MoveBattleCamOver, 75)
    IfEq(LFlag2, 1)
        Call(action_command_body_slam_start, 0, 102, 3, 1)
        Set(LFlag0, 0)
        ExecGetTID(TTYD64_battle_partner_watt_EVS_8023B524, LVarA)
        Loop(20)
            Call(CheckButtonDown, 32768, LVar0)
            IfEq(LVar0, 0)
                Set(LFlag0, 1)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        IfEq(LFlag0, 1)
            KillThread(LVarA)
            Goto(10)
        EndIf
        Call(PartnerTestEnemy, LVar0, 0, 4, 0, 1, 16)
        Set(LFlag0, 0)
        ExecGetTID(TTYD64_battle_partner_watt_EVS_8023B2A0, LVarA)
        Loop(55)
            Call(CheckButtonDown, 32768, LVar0)
            IfEq(LVar0, 0)
                Set(LFlag0, 1)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        IfEq(LFlag0, 1)
            KillThread(LVarA)
            Goto(10)
        EndIf
        IfEq(LFlag0, 0)
            ExecGetTID(TTYD64_battle_partner_watt_EVS_80238338, LVarA)
            Loop(30)
                Call(CheckButtonDown, 32768, LVar0)
                IfEq(LVar0, 0)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                KillThread(LVarA)
                Goto(10)
            EndIf
        EndIf
    Else
        Set(LFlag0, 0)
        ExecGetTID(TTYD64_battle_partner_watt_EVS_8023B524, LVarA)
        Loop(20)
            Call(CheckButtonDown, 32768, LVar0)
            IfNe(LVar0, 0)
                IfEq(LFlag2, 0)
                    Call(action_command_body_slam_start, 0, 92, 3, 1)
                    Set(LFlag2, 1)
                EndIf
            EndIf
            IfEq(LFlag2, 1)
                IfEq(LVar0, 0)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
            EndIf
            Wait(1)
        EndLoop
        IfEq(LFlag0, 1)
            KillThread(LVarA)
            Goto(10)
        EndIf
        Call(PartnerTestEnemy, LVar0, 0, 4, 0, 1, 16)
        Set(LFlag0, 0)
        ExecGetTID(TTYD64_battle_partner_watt_EVS_8023B2A0, LVarA)
        Loop(55)
            Call(CheckButtonDown, 32768, LVar0)
            IfNe(LVar0, 0)
                IfEq(LFlag2, 0)
                    Call(action_command_body_slam_start, 0, 92, 3, 1)
                    Set(LFlag2, 1)
                EndIf
            EndIf
            IfEq(LFlag2, 1)
                IfEq(LVar0, 0)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
            EndIf
            Wait(1)
        EndLoop
        IfEq(LFlag0, 1)
            KillThread(LVarA)
            Goto(10)
        EndIf
        IfEq(LFlag0, 0)
            ExecGetTID(TTYD64_battle_partner_watt_EVS_80238338, LVarA)
            Loop(30)
                Call(CheckButtonDown, 32768, LVar0)
                IfEq(LVar0, 0)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                KillThread(LVarA)
                Goto(10)
            EndIf
        EndIf
    EndIf
    Label(10)
    Wait(2)
    Call(InterruptActionCommand)
    Call(battle_partner_watt_ElectroDashFXDisable)
    Call(StopLoopingSoundAtActor, ACTOR_PARTNER, 0)
    Call(SetDamageSource, 19)
    Call(SetAnimation, ACTOR_PARTNER, -1, 917509)
    Call(SetActorPaletteEffect, ACTOR_SELF, 1, 10)
    Call(SetGoalToTarget, ACTOR_PARTNER)
    Call(AddGoalPos, ACTOR_PARTNER, -5, 0, 0)
    Call(FlyToGoal, ACTOR_PARTNER, 5, 0, 0)
    Thread
        Wait(2)
        Call(battle_partner_watt_SetBackgroundAlpha, 0)
    EndThread
    Call(PartnerTestEnemy, LVar0, 0, 4, 0, 1, 16)
    IfEq(LVar0, 6)
        Thread
            Wait(5)
            Call(SetAnimation, ACTOR_PARTNER, -1, 917505)
        EndThread
        Call(SetGoalToTarget, ACTOR_PARTNER)
        Call(AddGoalPos, ACTOR_PARTNER, 40, 10, 0)
        Call(FlyToGoal, ACTOR_PARTNER, 10, -20, 4)
        Wait(20)
        Call(SetGoalToHome, ACTOR_PARTNER)
        Call(SetAnimation, ACTOR_PARTNER, -1, 917507)
        Call(FlyToGoal, ACTOR_PARTNER, 30, 0, 10)
        Call(SetAnimation, ACTOR_PARTNER, -1, 917505)
        Return
    EndIf
    Call(TTYD64_Player_partner6_WattFXEnable)
    Call(TTYD64_Player_partner6_WattFXBounce)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar2)
        CaseEq(161)
            Set(LVarE, 1)
            Set(LVarF, 3)
        CaseEq(162)
            Set(LVarE, 1)
            Set(LVarF, 4)
        CaseEq(163)
            Set(LVarE, 1)
            Set(LVarF, 5)
    EndSwitch
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(PartnerDamageEnemy, LVar0, 134217760, 141, 0, LVarF, 112)
        CaseDefault
            Call(PartnerDamageEnemy, LVar0, 134217760, 141, 0, LVarE, 48)
    EndSwitch
    Call(PartnerYieldTurn)
    Switch(LVar0)
        CaseOrEq(1)
        CaseOrEq(3)
            ExecWait(TTYD64_battle_partner_watt_EVS_80238000)
        EndCaseGroup
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_partner_watt_EVS_8023B3E4)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023A4D8 = {
    Call(LoadActionCommand, ACTION_COMMAND_THREE_CHANCES)
    Call(action_command_three_chances_init, 1)
    Call(SetActionHudPrepareTime, 0)
    Call(SetActorFlagBits, ACTOR_PLAYER, ACTOR_FLAG_NO_INACTIVE_ANIM, 1)
    Call(UseIdleAnimation, ACTOR_PLAYER, false)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65567)
    Wait(5)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, -125, 42, 0)
    Call(SetBattleCamOffsetY, 0)
    Call(SetBattleCamDist, 340)
    Call(MoveBattleCamOver, 30)
    Call(SetActorYaw, ACTOR_PARTNER, 30)
    Wait(1)
    Call(SetActorYaw, ACTOR_PARTNER, 60)
    Wait(1)
    Call(SetActorYaw, ACTOR_PARTNER, 90)
    Wait(1)
    Call(SetActorYaw, ACTOR_PARTNER, 120)
    Wait(1)
    Call(SetActorYaw, ACTOR_PARTNER, 150)
    Wait(1)
    Call(SetActorYaw, ACTOR_PARTNER, 180)
    Wait(10)
    Call(action_command_three_chances_start, 0, 100, 3)
    Call(AddBattleCamDist, -75)
    Call(MoveBattleCamOver, 100)
    Call(SetBattleCamTargetingModes, 0, 0, 1)
    Thread
        Wait(88)
        Exec(TTYD64_Script_InitTracker)
    EndThread
    Thread
        Call(EnableActorBlur, ACTOR_PARTNER, 1)
        Call(SetAnimation, ACTOR_PARTNER, -1, 917509)
        Call(battle_partner_watt_TurboChargeUnwindWatt, 0)
        Call(SetAnimation, ACTOR_PARTNER, -1, 917507)
        Call(SetGoalToHome, ACTOR_PARTNER)
        Exec(TTYD64_battle_partner_watt_EVS_8023CE9C)
        Call(FlyToGoal, ACTOR_PARTNER, 10, -10, 5)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Call(TTYD64_StylishAddCount, LVar0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            Call(UseIdleAnimation, ACTOR_PARTNER, false)
            Call(SetAnimation, ACTOR_PARTNER, -1, 917512)
            Wait(25)
            Call(UseIdleAnimation, ACTOR_PARTNER, true)
        EndIf
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Call(SetAnimation, ACTOR_PARTNER, -1, 917505)
        Wait(10)
        Call(EnableActorBlur, ACTOR_PARTNER, 0)
    EndThread
    Wait(30)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_WATT_TURBO_CHARGE)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar1, 42)
    Call(battle_partner_watt_TurboChargeFX, LVar0, LVar1, LVar2)
    Wait(59)
    Call(AddBattleCamDist, 100)
    Call(MoveBattleCamOver, 5)
    Thread
        Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_LONG_PLAYER_JUMP)
        Call(SetActorJumpGravity, ACTOR_PLAYER, Float(1.0))
        Call(SetActorSpeed, ACTOR_PLAYER, Float(1.0))
        Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 65545)
        Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Call(PlayerHopToGoal, 20, 0, 0)
        Call(SetAnimation, ACTOR_PLAYER, 0, 65545)
        Wait(4)
        Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    EndThread
    Wait(30)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8334)
    Call(GetPartnerActionQuality, LVar0)
    Call(TTYD64_AddAttackBoost, 0, 1, LVar0)
    Set(LVarE, LVarF)
    IfGt(LVarA, 0)
        Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Add(LVar0, 15)
        Add(LVar1, 35)
        Add(LVarF, 0)
        Call(PlayEffect_impl, 86, LVarF, LVar0, LVar1, LVar2, Float(1.5), 60, 0, 0, 0, 0, 0, 0, 0)
        Wait(4)
    EndIf
    IfEq(LVar0, 0)
    Else
        Call(ShowVariableMessageBox, 42, 60, LVarA)
    EndIf
    Call(WaitForMessageBoxDone)
    Call(SetActorFlagBits, ACTOR_PLAYER, ACTOR_FLAG_NO_INACTIVE_ANIM, 0)
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023AC2C = {
    Call(UseIdleAnimation, ACTOR_PARTNER, false)
    Call(InterruptActionCommand)
    Call(TTYD64_Player_partner6_WattFXDisableBounce)
    Call(TTYD64_Player_partner6_WattFXEnable)
    Call(TTYD64_Player_partner6_WattFXSetEffect, 0)
    Call(GetLastEvent, ACTOR_PARTNER, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, -1)
            Set(LVar1, 917516)
            ExecWait(EVS_Enemy_Hit)
            Call(SetAnimation, ACTOR_PARTNER, -1, 917505)
        EndCaseGroup
        CaseOrEq(23)
        CaseOrEq(25)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8332)
            Call(TTYD64_GetPartnerExtraBattleData_API, 14, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 917504)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 917523)
            EndIf
            ExecWait(EVS_Enemy_NoDamageHit)
            Call(TTYD64_Player_partner6_WattFXBounce)
        EndCaseGroup
        CaseEq(42)
            SetConst(LVar1, 917516)
            SetConst(LVar2, 12)
            ExecWait(EVS_Partner_SpikeContact)
        CaseEq(44)
            Call(TTYD64_Player_partner6_WattFXDisable)
            SetConst(LVar1, 917517)
            Set(LVar2, 12)
            SetConst(LVar3, 917518)
            ExecWait(EVS_Partner_BurnContact)
            Call(TTYD64_Player_partner6_WattFXEnable)
        CaseEq(14)
            SetConst(LVar1, 917517)
            SetConst(LVar2, 917518)
            ExecWait(EVS_Partner_BurnHit)
        CaseEq(47)
            SetConst(LVar1, 917516)
            Set(LVar2, 12)
            ExecWait(EVS_Partner_ShockHit)
        CaseEq(51)
        CaseEq(52)
            Call(TTYD64_Player_partner6_WattFXBounce)
            SetConst(LVar0, 1)
            SetConst(LVar1, 917505)
            SetConst(LVar2, 917507)
            Set(LVar3, 11)
            ExecWait(EVS_Partner_Recover)
            Call(TTYD64_Player_partner6_WattFXBounce)
        CaseEq(62)
            Call(TTYD64_Player_partner6_WattFXRemove)
        CaseOrEq(24)
        CaseOrEq(26)
            Call(PlaySoundAtActor, ACTOR_PARTNER, 8332)
            SetConst(LVar0, 1)
            SetConst(LVar1, 917523)
            ExecWait(EVS_Enemy_NoDamageHit)
            Wait(10)
        EndCaseGroup
        CaseEq(64)
            Call(TTYD64_Player_partner6_WattFXDisable)
        CaseEq(65)
            Call(TTYD64_Player_partner6_WattFXEnable)
        CaseEq(32)
            Set(LVar0, -1)
            Set(LVar1, 917516)
            ExecWait(TTYD64_PartnerDies)
            Return
        CaseEq(TTYD64_EVENT_SUPERGUARD)
            Set(LVar0, -1)
            Set(LVar1, 917523)
            ExecWait(TTYD64_DoSuperguard)
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_PARTNER, true)
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023B09C = {
    Call(TTYD64_GetActionMeterFill, LVar0)
    IfGe(LVar0, 9984)
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
                    Call(UseIdleAnimation, ACTOR_PARTNER, false)
                    Call(SetAnimation, ACTOR_PARTNER, -1, 917512)
                    Wait(25)
                    Call(UseIdleAnimation, ACTOR_PARTNER, true)
                    Return
                EndIf
                Wait(1)
            EndLoop
        EndIf
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
    EndIf
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023B2A0 = {
    Call(SetAnimation, ACTOR_PARTNER, -1, 917509)
    Call(TTYD64_Player_partner6_WattFXDisable)
    Call(PlayLoopingSoundAtActor, ACTOR_PARTNER, 0, SOUND_WATT_CHARGE)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar1, 12)
    Call(battle_partner_watt_ElectroDashFX, LVar0, LVar1, LVar2)
    Call(battle_partner_watt_UnkBackgroundFunc3)
    Set(LVar9, 0)
    Call(SetAnimation, ACTOR_PARTNER, -1, 917510)
    Loop(55)
        Add(LVar9, 30)
        IfGt(LVar9, 200)
            Set(LVar9, 200)
        EndIf
        Call(battle_partner_watt_SetBackgroundAlpha, LVar9)
        Wait(1)
    EndLoop
    Call(SetActorPaletteEffect, ACTOR_SELF, 1, 9)
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023B3E4 = {
    Call(UseBattleCamPreset, 51)
    Call(SetGoalToHome, ACTOR_PARTNER)
    Call(SetAnimation, ACTOR_PARTNER, -1, 917507)
    Call(FlyToGoal, ACTOR_PARTNER, 30, 0, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 917505)
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023B460 = {
    Exec(TTYD64_Script_NukeTracker)
    Call(GetStatusFlags, ACTOR_PLAYER, LVar0)
    IfFlag(LVar0, 3526656)
        ExecWait(TTYD64_battle_partner_watt_EVS_8023C370)
    Else
        ExecWait(TTYD64_battle_partner_watt_EVS_8023A4D8)
    EndIf
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023B524 = {
    Call(SetAnimation, ACTOR_PARTNER, -1, 917507)
    Call(FlyToGoal, ACTOR_PARTNER, 20, 0, 0)
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023B970 = {
    Call(LoadActionCommand, ACTION_COMMAND_MEGA_SHOCK)
    Exec(TTYD64_Script_NukeTracker)
    Call(action_command_mega_shock_init)
    Call(SetupMashMeter, 1, 100, 0, 0, 0, 0)
    Call(SetActionHudPrepareTime, 0)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, -54, 63, 10)
    Call(SetBattleCamOffsetY, 15)
    Call(SetBattleCamDist, 314)
    Call(MoveBattleCamOver, 30)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar0, 40)
    Add(LVar1, 30)
    Call(SetAnimation, ACTOR_PARTNER, -1, 917507)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_PARTNER, 20, 0, 10)
    Call(SetAnimation, ACTOR_PARTNER, -1, 917505)
    Call(battle_partner_watt_UnkBackgroundFunc3)
    Set(LVar9, 0)
    Thread
        Loop(75)
            Add(LVar9, 3)
            Call(battle_partner_watt_SetBackgroundAlpha, LVar9)
            Wait(1)
        EndLoop
    EndThread
    Call(battle_partner_watt_AverageTargetParalyzeChance)
    Call(action_command_mega_shock_start, 0, 87, 3, LVar0)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar1, 15)
    Add(LVar2, 5)
    Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(1.0), 90, 0, 0, 0, 0, 0, 0, 0)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Add(LVar1, 12)
    Call(PlayEffect_impl, 51, 8, LVar0, LVar1, LVar2, Float(1.2998), 90, 0, 0, 0, 0, 0, 0, 0)
    Call(AddBattleCamDist, -100)
    Call(MoveBattleCamOver, 90)
    Call(SetBattleCamTargetingModes, 0, 0, 1)
    Call(SetAnimation, ACTOR_PARTNER, -1, 917510)
    Call(SetActorPaletteEffect, ACTOR_SELF, 1, 10)
    Call(TTYD64_Player_partner6_WattFXDisable)
    Call(GetActionProgress, LVar1)
    Wait(90)
    Call(battle_partner_watt_SetBackgroundAlpha, 0)
    Thread
        Set(LVar9, 60)
        Loop(20)
            Sub(LVar9, 3)
            Call(battle_partner_watt_SetBackgroundAlpha, LVar9)
            Wait(1)
        EndLoop
    EndThread
    Call(SetActorPaletteEffect, ACTOR_SELF, 1, 9)
    Call(InitTargetIterator)
    Thread
        Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Add(LVar1, 12)
        Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_WATT_MEGA_DISCHARGE)
        Call(PlayEffect_impl, 74, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(10)
        Call(PlaySoundAtActor, ACTOR_PARTNER, 8228)
        Call(PlayEffect_impl, 74, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    EndThread
    Thread
        Call(SetAnimation, ACTOR_PARTNER, -1, 917511)
        Wait(5)
        Exec(TTYD64_Script_InitTracker)
        Call(SetAnimation, ACTOR_PARTNER, -1, 917509)
        Wait(15)
        Call(SetAnimation, ACTOR_PARTNER, -1, 917505)
    EndThread
    Thread
        Call(SetBattleCamDist, 420)
        Call(SetBattleCamTarget, 6, 63, 10)
        Call(MoveBattleCamOver, 15)
        Wait(4)
        Set(LVar0, 6)
        Loop(30)
            Add(LVar0, 1)
            Call(SetBattleCamTarget, LVar0, 63, 10)
            Wait(1)
        EndLoop
    EndThread
    Thread
        Call(battle_partner_watt_PowerShockDischargeFX, 10)
    EndThread
    Call(GetActionProgress, LVar0)
    Call(GetActorPos, ACTOR_PARTNER, LVar1, LVar2, LVar3)
    Add(LVar2, 12)
    Call(battle_partner_watt_MegaShockFX, LVar0, LVar1, LVar2, LVar3)
    Loop(0)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetPartnerActionQuality, LVarF)
        Call(PartnerTestEnemy, LVar0, 0, 20, 0, 1, 16)
        IfEq(LVar0, 6)
            Goto(11)
        EndIf
        IfEq(LVarF, 100)
            Call(TTYD64_StylishIsArmed, LVar0)
            IfEq(LVar0, 1)
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
                            Call(SetAnimation, ACTOR_PARTNER, -1, 917512)
                            Wait(25)
                            BreakLoop
                        EndIf
                        Wait(1)
                    EndLoop
                EndIf
                Call(TTYD64_StylishDisarm)
                Call(TTYD64_StylishConsume)
            EndIf
            Call(PartnerAfflictEnemy, LVar0, 1879048224, 0, (Bytecode) (s32) 0xC0010300, 254, 0, 112)
        Else
            Call(PartnerAfflictEnemy, LVar0, 1879048224, 0, (Bytecode) (s32) 0xC0010300, LVarF, 0, 112)
        EndIf
        Label(11)
        Call(ChooseNextTarget, 0, LVar0)
        IfEq(LVar0, -1)
            BreakLoop
        EndIf
        Wait(5)
    EndLoop
    Call(TTYD64_Player_partner6_WattFXEnable)
    Call(PartnerYieldTurn)
    Wait(30)
    Call(GetPartnerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(99)
            ExecWait(TTYD64_battle_partner_watt_EVS_80238000)
        CaseDefault
            ExecWait(TTYD64_battle_partner_watt_EVS_8023B3E4)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023C370 = {
    Call(LoadActionCommand, ACTION_COMMAND_THREE_CHANCES)
    Call(action_command_three_chances_init, 1)
    Call(SetActionHudPrepareTime, 0)
    Call(UseIdleAnimation, ACTOR_PLAYER, false)
    Wait(5)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, -125, 42, 0)
    Call(SetBattleCamOffsetY, 0)
    Call(SetBattleCamDist, 340)
    Call(MoveBattleCamOver, 30)
    Call(SetActorYaw, ACTOR_PARTNER, 30)
    Wait(1)
    Call(SetActorYaw, ACTOR_PARTNER, 60)
    Wait(1)
    Call(SetActorYaw, ACTOR_PARTNER, 90)
    Wait(1)
    Call(SetActorYaw, ACTOR_PARTNER, 120)
    Wait(1)
    Call(SetActorYaw, ACTOR_PARTNER, 150)
    Wait(1)
    Call(SetActorYaw, ACTOR_PARTNER, 180)
    Wait(10)
    Call(action_command_three_chances_start, 0, 100, 3)
    Call(AddBattleCamDist, -100)
    Call(MoveBattleCamOver, 100)
    Call(SetBattleCamTargetingModes, 0, 0, 1)
    Thread
        Wait(88)
        Exec(TTYD64_Script_InitTracker)
    EndThread
    Thread
        Call(EnableActorBlur, ACTOR_PARTNER, 1)
        Call(SetAnimation, ACTOR_PARTNER, -1, 917509)
        Call(battle_partner_watt_TurboChargeUnwindWatt, 1)
        Call(SetAnimation, ACTOR_PARTNER, -1, 917507)
        Call(SetGoalToHome, ACTOR_PARTNER)
        Exec(TTYD64_battle_partner_watt_EVS_8023CE9C)
        Call(FlyToGoal, ACTOR_PARTNER, 10, -10, 5)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Call(TTYD64_StylishAddCount, LVar0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            Call(UseIdleAnimation, ACTOR_PARTNER, false)
            Call(SetAnimation, ACTOR_PARTNER, -1, 917512)
            Wait(25)
            Call(UseIdleAnimation, ACTOR_PARTNER, true)
        EndIf
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Call(SetAnimation, ACTOR_PARTNER, -1, 917505)
        Wait(10)
        Call(EnableActorBlur, ACTOR_PARTNER, 0)
    EndThread
    Wait(30)
    Call(PlaySoundAtActor, ACTOR_PARTNER, SOUND_WATT_TURBO_CHARGE)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar1, 42)
    Call(battle_partner_watt_TurboChargeFX, LVar0, LVar1, LVar2)
    Wait(59)
    Call(AddBattleCamDist, 100)
    Call(MoveBattleCamOver, 5)
    Wait(30)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Call(PlaySoundAtActor, ACTOR_PARTNER, 8334)
    Call(GetPartnerActionQuality, LVar0)
    Call(TTYD64_AddAttackBoost, 0, 1, LVar0)
    Set(LVarE, LVarF)
    IfGt(LVarA, 0)
        Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Add(LVar0, 15)
        Add(LVar1, 35)
        Add(LVarF, 0)
        Call(PlayEffect_impl, 86, LVarF, LVar0, LVar1, LVar2, Float(1.5), 60, 0, 0, 0, 0, 0, 0, 0)
        Wait(4)
    EndIf
    IfEq(LVar0, 0)
    Else
        Call(ShowVariableMessageBox, 42, 60, LVarA)
    EndIf
    Call(WaitForMessageBoxDone)
    Call(SetActorFlagBits, ACTOR_PLAYER, ACTOR_FLAG_NO_INACTIVE_ANIM, 0)
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023CD28 = {
    Call(ShowActionHud, 1)
    Call(SetBattleFlagBits, BS_FLAGS1_4000, 0)
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
        CaseEq(161)
            ExecWait(TTYD64_battle_partner_watt_EVS_80239A10)
        CaseEq(162)
            ExecWait(TTYD64_battle_partner_watt_EVS_80239A10)
        CaseEq(163)
            ExecWait(TTYD64_battle_partner_watt_EVS_80239A10)
        CaseEq(164)
            ExecWait(TTYD64_battle_partner_watt_EVS_802390D8)
        CaseEq(165)
            ExecWait(TTYD64_battle_partner_watt_EVS_8023B460)
        CaseEq(166)
            ExecWait(TTYD64_battle_partner_watt_EVS_8023B970)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023CE9C = {
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 0)
        Loop(4)
            ExecWait(TTYD64_Script_TimingTutor)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    Else
        Call(TTYD64_StylishConsume)
    EndIf
    Call(TTYD64_StylishDisarm)
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023CF88 = {
    Call(TTYD64_Player_partner6_WattFXEnable)
    Call(TTYD64_Player_partner6_WattFXSetEffect, 1)
    SetConst(LVar0, 1)
    SetConst(LVar1, 917512)
    SetConst(LVar2, 917506)
    SetConst(LVar3, 917505)
    ExecWait(EVS_Partner_Celebrate)
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023D000 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_battle_partner_watt_EVS_802382A4))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_battle_partner_watt_EVS_8023D0B8))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_battle_partner_watt_EVS_8023AC2C))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_battle_partner_watt_EVS_8023D0E0))
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023D060 = {
    Call(TTYD64_Player_partner6_WattFXEnable)
    Call(TTYD64_Player_partner6_WattFXSetEffect, 1)
    SetConst(LVar0, 1)
    SetConst(LVar1, 917507)
    ExecWait(EVS_Partner_RunAway)
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023D0B8 = {
    SetPriority(99)
    Call(TTYD64_Player_partner6_Watt_UpdateSparkles)
    Return
    End
};

EvtScript TTYD64_battle_partner_watt_EVS_8023D0E0 = {
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_partner_watt(void) {
    Mod_ReplaceActorBlueprint("TTYD64", &battle_partner_watt, &TTYD64_battle_partner_watt);
}
