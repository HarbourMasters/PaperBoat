#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_drop_tables.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/battle/area/battles_b.h"
#include "port/romhack/specific/TTYD64/battle/area/battles_b_imports.h"

API_CALLABLE(b_area_sam2_downed_goomba_CalculateArcsinDeg);
API_CALLABLE(b_area_sam2_gray_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_sam2_gray_magikoopa_ShrinkActor);
API_CALLABLE(b_area_sam2_monstar_SetBackgroundAlpha);
API_CALLABLE(b_area_sam2_monstar_StartRumbleWithParams);
API_CALLABLE(b_area_sam2_monstar_UnkBackgroundFunc3);
API_CALLABLE(b_area_sam2_paragoomba_StartRumbleWithParams);
extern Vec3i b_area_sam2_MonstarPos;
extern EvtScript b_area_sam2_downed_goomba_EVS_HandleEvent;
extern EvtScript b_area_sam2_downed_goomba_EVS_Idle;
extern EvtScript b_area_sam2_gray_magikoopa_EVS_Flee;
extern EvtScript b_area_sam2_gray_magikoopa_EVS_HandleEvent;
extern EvtScript b_area_sam2_gray_magikoopa_EVS_Idle;
extern ActorPartBlueprint b_area_sam2_gray_magikoopa_GroundParts[];
extern s32 b_area_sam2_gray_magikoopa_StatusTable[];
extern ActorPartBlueprint b_area_sam2_monstar_ActorParts[];
extern s32 b_area_sam2_monstar_DefaultAnims[];
extern EvtScript b_area_sam2_monstar_EVS_HandleEvent;
extern EvtScript b_area_sam2_monstar_EVS_HandlePhase;
extern EvtScript b_area_sam2_monstar_EVS_Idle;
extern s32 b_area_sam2_monstar_StatusTable[];
extern ActorPartBlueprint b_area_sam2_paragoomba_ActorParts[];
extern s32 b_area_sam2_paragoomba_DownedStatusTable[];
extern EvtScript b_area_sam2_paragoomba_EVS_Idle;
extern EvtScript b_area_sam2_paragoomba_EVS_Paragoomba_GoHome;
extern s32 b_area_sam2_paragoomba_FlyingStatusTable[];
extern Stage b_area_sam2_sam_01;
extern Stage b_area_sam2_sam_03;
extern ActorBlueprint TTYD64_sam2_Monstar;
extern EvtScript TTYD64_sam2_Script_Init_80219FF0;
extern EvtScript TTYD64_sam2_Script_TakeTurn_8021B394;
extern ActorBlueprint TTYD64_sam2_Paragoomba;
extern EvtScript TTYD64_sam2_Script_Init_8021C168;
extern EvtScript TTYD64_sam2_Script_HandleEvent_8021C4E8;
extern EvtScript TTYD64_sam2_Script_GRYMagikoopa_ShapeSpell;
extern EvtScript TTYD64_sam2_Script_8021D2F4;
extern EvtScript TTYD64_sam2_Script_8021D914;
extern EvtScript TTYD64_sam2_Script_8021AB64;
extern ActorBlueprint TTYD64_sam2_GRYMagikoopa;
extern EvtScript TTYD64_sam2_Script_GRYMagikoopa_WandStrike;
extern EvtScript TTYD64_sam2_Script_Init_80221568;
extern EvtScript TTYD64_sam2_Script_TakeTurn_802216B0;
extern FormationRow TTYD64_sam2_Formation_00[];
extern FormationRow TTYD64_sam2_Formation_01[];
extern Battle TTYD64_sam2_FormationTable[];
extern EvtScript TTYD64_sam2_Script_TakeTurn_8021E468;
extern EvtScript TTYD64_sam2_Script_TakeTurn_8021CADC;

ActorBlueprint TTYD64_sam2_Monstar = {
    .flags = 0x200,
    .maxHP = 20,
    .type = 0xBC,
    .level = 45,
    .partCount = 2,
    .partsData = b_area_sam2_monstar_ActorParts,
    .initScript = &TTYD64_sam2_Script_Init_80219FF0,
    .statusTable = b_area_sam2_monstar_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 100, 98 },
    .healthBarOffset = { 0, 16 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

// clang-format off
EvtScript TTYD64_sam2_Script_Init_80219FF0 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_sam2_Script_TakeTurn_8021B394))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam2_monstar_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_sam2_monstar_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_sam2_monstar_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sam2_Script_TakeTurn_8021B394 = {
    ExecWait(TTYD64_sam2_Script_8021AB64)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 72)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 340)
    Call(MoveBattleCamOver, 20)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(ActorSpeak, 0x1200E5, ACTOR_SELF, 1, 0x7E0009, 0x7E0009)
        CaseEq(1)
            Call(ActorSpeak, 0x1200E6, ACTOR_SELF, 1, 0x7E0009, 0x7E0009)
        CaseEq(2)
            Call(ActorSpeak, 0x1200E7, ACTOR_SELF, 1, 0x7E0009, 0x7E0009)
        CaseDefault
            Call(ActorSpeak, 0x1200E6, ACTOR_SELF, 1, 0x7E0009, 0x7E0009)
    EndSwitch
    Call(AddActorVar, ACTOR_SELF, 3, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Return
    End
};
// clang-format on

ActorBlueprint TTYD64_sam2_Paragoomba = {
    .flags = 0x200,
    .maxHP = 2,
    .type = 0x08,
    .level = 6,
    .partCount = 4,
    .partsData = b_area_sam2_paragoomba_ActorParts,
    .initScript = &TTYD64_sam2_Script_Init_8021C168,
    .statusTable = b_area_sam2_paragoomba_FlyingStatusTable,
    .escapeChance = 90,
    .airLiftChance = 100,
    .hurricaneChance = 100,
    .spookChance = 100,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 36, 26 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

// clang-format off
EvtScript TTYD64_sam2_Script_Init_8021C168 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_sam2_Script_TakeTurn_8021CADC))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam2_paragoomba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_sam2_Script_HandleEvent_8021C4E8))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sam2_Script_HandleEvent_8021C4E8 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280006)
            ExecWait(Ref(EVS_Enemy_Hit))
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(GetEncounterTrigger, LVar0)
                IfEq(LVar0, 4)
                    ExecWait(TTYD64_sam2_Script_8021D2F4)
                EndIf
            EndIf
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000D)
            SetConst(LVar2, 0x28000E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000D)
            SetConst(LVar2, 0x28000E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000E)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(12)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280006)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_sam2_Script_8021D2F4)
        CaseEq(15)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000D)
            SetConst(LVar2, 0x28000E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_sam2_Script_8021D2F4)
        CaseEq(47)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000F)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280006)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(SetAnimation, ACTOR_SELF, 2, 0x28000C)
            ExecWait(b_area_sam2_paragoomba_EVS_Paragoomba_GoHome)
        CaseEq(38)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000F)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280007)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280006)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280007)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            Call(SetAnimation, ACTOR_SELF, 2, 0x280004)
            ExecWait(b_area_sam2_paragoomba_EVS_Paragoomba_GoHome)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280004)
            SetConst(LVar2, 0x280006)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280004)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280006)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sam2_Script_GRYMagikoopa_ShapeSpell = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    Else
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 10)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 12)
        Add(LVar1, 14)
    Else
        Sub(LVar0, 30)
        Add(LVar1, 36)
    EndIf
    Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570502)
    Wait(30)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8405)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570503)
            Wait(5)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar9)
            IfFlag(LVar9, 0x80000)
                Sub(LVar0, 8)
                Add(LVar1, 8)
            Else
                Sub(LVar0, 20)
                Add(LVar1, 20)
            EndIf
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Sub(LVar3, 50)
            Set(LVar4, 0)
            Call(b_area_sam2_gray_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
            Wait(50)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(14)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 8405)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570503)
    Wait(5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 8)
        Add(LVar1, 8)
    Else
        Sub(LVar0, 20)
        Add(LVar1, 20)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 10)
    Call(b_area_sam2_gray_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
    Wait(18)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000010, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(19)
            Call(YieldTurn)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sam2_Script_8021D2F4 = {
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetPartFlags, ACTOR_SELF, 2, 0x20005)
    Call(SetPartFlags, ACTOR_SELF, 3, 0x120004)
    Call(SetPartFlags, ACTOR_SELF, 4, 0x120004)
    Call(SetPartFlags, ACTOR_SELF, 1, 0x800004)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(SetPartDispOffset, ACTOR_SELF, 3, -9, 7, -2)
    Call(SetPartPos, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
    Call(SetPartDispOffset, ACTOR_SELF, 4, 11, 7, -2)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    IfEq(LVar0, 15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x26000A)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x260005)
    EndIf
    Call(SetActorSounds, ACTOR_SELF, 2, 769, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.80078125))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(b_area_sam2_paragoomba_StartRumbleWithParams, 100, 10)
    Thread
        Call(ShakeCam, 1, 0, 5, Float(0.30078125))
    EndThread
    Call(ResetActorSounds, ACTOR_SELF, 2)
    Call(GetLastEvent, ACTOR_SELF, LVar3)
    IfEq(LVar3, 15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x260005)
        Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Add(LVar4, 10)
        Add(LVar5, 5)
        Call(PlayEffect_impl, 39, 0, LVar3, LVar4, LVar5, Float(1.0), 10, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Loop(10)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
        Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 1)
        Wait(1)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
        Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 0)
        Wait(1)
    EndLoop
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 1)
    Call(GetIndexFromHome, ACTOR_SELF, LVar0)
    Mod(LVar0, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVar0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
    Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_sam2_paragoomba_DownedStatusTable))
    Call(SetActorType, ACTOR_SELF, 7)
    ExecWait(TTYD64_sam2_Script_8021D914)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sam2_Script_8021D914 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_sam2_Script_TakeTurn_8021E468))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam2_downed_goomba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_sam2_downed_goomba_EVS_HandleEvent))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sam2_Script_8021AB64 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 1)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 250)
    Call(SetBattleCamOffsetY, 55)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Wait(30)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x7E0004)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7E0005)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7E0006)
    EndThread
    Thread
        Call(b_area_sam2_monstar_UnkBackgroundFunc3)
        Call(MakeLerp, 0, 200, 60, 1)
        Label(0)
        Call(UpdateLerp)
        Call(b_area_sam2_monstar_SetBackgroundAlpha, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 998)
    Call(b_area_sam2_monstar_StartRumbleWithParams, 80, 120)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 100)
    Call(SetBattleCamOffsetY, 60)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 60)
    Wait(60)
    Call(PlaySoundAtActor, ACTOR_SELF, 746)
    Call(PlaySoundAtActor, ACTOR_SELF, 878)
    Thread
        Wait(10)
        Loop(18)
            Call(RandInt, 150, LVar0)
            Add(LVar0, 100)
            Call(b_area_sam2_monstar_StartRumbleWithParams, LVar0, 20)
            Wait(10)
        EndLoop
    EndThread
    Thread
        Loop(60)
            Call(RandInt, 1, LVar0)
            Add(LVar0, 2)
            Call(RandInt, 400, LVar1)
            Sub(LVar1, 100)
            Call(RandInt, 100, LVar2)
            Sub(LVar2, 50)
            Set(LVar3, LVar1)
            Sub(LVar3, 200)
            Set(LVar4, LVar2)
            Call(RandInt, 10, LVar5)
            Add(LVar5, 10)
            Call(PlayEffect_impl, 15, LVar0, LVar1, 240, LVar2, LVar3, 0, LVar4, LVar5, 0, 0, 0, 0, 0)
            Wait(3)
        EndLoop
    EndThread
    Wait(8)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 50)
    Add(LVar2, 5)
    Call(PlayEffect_impl, 51, 11, LVar0, LVar1, LVar2, Float(0.7998046875), 160, 0, 0, 0, 0, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7E0007)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(170)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 16)
            Switch(LVar0)
                CaseOrEq(6)
                CaseOrEq(5)
                    Set(LVarB, LVar0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x7E0001)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_sam2_monstar_DefaultAnims))
                    Call(MakeLerp, 200, 0, 60, 0)
                    Label(1)
                    Call(UpdateLerp)
                    Call(b_area_sam2_monstar_SetBackgroundAlpha, LVar0)
                    Wait(1)
                    IfEq(LVar1, 1)
                        Goto(1)
                    EndIf
                    IfEq(LVarB, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    Wait(20)
                    Call(SetActorVar, ACTOR_SELF, 1, 0)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
                EndCaseGroup
                CaseDefault
                    Wait(2)
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000100, 0, 0, 1, 32)
                    Switch(LVar0)
                        CaseOrEq(0)
                        CaseOrEq(2)
                            Call(SetAnimation, ACTOR_SELF, 1, 0x7E0001)
                            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_sam2_monstar_DefaultAnims))
                            Call(MakeLerp, 200, 0, 60, 0)
                            Label(0)
                            Call(UpdateLerp)
                            Call(b_area_sam2_monstar_SetBackgroundAlpha, LVar0)
                            Wait(1)
                            IfEq(LVar1, 1)
                                Goto(0)
                            EndIf
                            Wait(20)
                        EndCaseGroup
                    EndSwitch
                    Call(SetActorVar, ACTOR_SELF, 1, 0)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
            EndSwitch
        EndCaseGroup
    EndSwitch
    Wait(170)
    Wait(2)
    Thread
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 16)
        Switch(LVar0)
            CaseOrEq(6)
            CaseOrEq(5)
                IfEq(LVar0, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
            EndCaseGroup
            CaseDefault
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000100, 0, 0, 1, 32)
        EndSwitch
    EndThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000100, 0, 0, 1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x7E0001)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_sam2_monstar_DefaultAnims))
            Call(MakeLerp, 200, 0, 60, 0)
            Label(2)
            Call(UpdateLerp)
            Call(b_area_sam2_monstar_SetBackgroundAlpha, LVar0)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(2)
            EndIf
            Wait(20)
        EndCaseGroup
    EndSwitch
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

ActorBlueprint TTYD64_sam2_GRYMagikoopa = {
    .flags = 0x0,
    .maxHP = 11,
    .type = 0x57,
    .level = 21,
    .partCount = 1,
    .partsData = b_area_sam2_gray_magikoopa_GroundParts,
    .initScript = &TTYD64_sam2_Script_Init_80221568,
    .statusTable = b_area_sam2_gray_magikoopa_StatusTable,
    .escapeChance = 40,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 2,
    .size = { 36, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 32 },
};

// clang-format off
EvtScript TTYD64_sam2_Script_GRYMagikoopa_WandStrike = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 731)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x560502)
        Set(LVar0, 200)
        Loop(20)
            Sub(LVar0, 10)
            Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 5)
    Else
        Add(LVar0, 25)
    EndIf
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
    Set(LVar0, 55)
    Loop(20)
        Add(LVar0, 10)
        Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_SELF, 1, 255)
    Call(SetAnimation, ACTOR_SELF, 1, 0x560503)
    Wait(11)
    Call(PlaySoundAtActor, ACTOR_SELF, 732)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(UseBattleCamPreset, 2)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560501)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560501)
            Call(FlyToGoal, ACTOR_SELF, 20, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sam2_Script_Init_80221568 = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam2_gray_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_sam2_Script_TakeTurn_802216B0))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_sam2_gray_magikoopa_EVS_HandleEvent))
    Call(GetBattleVar, 2, LVar0)
    IfEq(LVar0, 0)
        Call(SetBattleVar, 2, -1)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sam2_Script_TakeTurn_802216B0 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_sam2_gray_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
        IfEq(LVar3, 0)
            Call(GetStatusFlags, LVar0, LVar4)
            IfNotFlag(LVar4, 0x4002000)
                Set(LVar8, LVar0)
                Call(SetBattleVar, 2, LVar1)
                Goto(100)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfEq(LFlag0, 0)
        Set(LFlag0, 1)
        Call(SetBattleVar, 2, -1)
        Goto(10)
    EndIf
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_sam2_gray_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        ExecWait(TTYD64_sam2_Script_GRYMagikoopa_ShapeSpell)
    Else
        ExecWait(TTYD64_sam2_Script_GRYMagikoopa_WandStrike)
    EndIf
    Return
    Label(100)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560502)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570502)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.30078125), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.30078125), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560501)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570501)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Call(PlaySoundAtActor, LVar8, 731)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(VanishActor, LVar8, 2)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

FormationRow TTYD64_sam2_Formation_00[] = {
    { .actor = &TTYD64_sam2_Monstar,
      .home = { .vec = &b_area_sam2_MonstarPos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_sam2_Formation_01[] = {
    { .actor = &TTYD64_sam2_Paragoomba,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_sam2_GRYMagikoopa,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

Battle TTYD64_sam2_FormationTable[] = {
    { .name = "\202\251\202\242\202\324\202\302",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_sam2_Formation_00,
      .stage = &b_area_sam2_sam_03,
      .onBattleStart = NULL },
    { .name = "\203p\203^\203N\203\212,\203O\203\214\203C\203J\203\201\203b\203N\201i\203`"
              "\203F\203b\203N\202\346\202\244\201j",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_sam2_Formation_01,
      .stage = &b_area_sam2_sam_01,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_sam2_Script_TakeTurn_8021E468 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 10)
            Set(LVar1, 10)
            Add(LVar2, 3)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_sam2_downed_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260008)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 5, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 7, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260005)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Thread
                Wait(4)
                Set(LVar0, 180)
                Loop(4)
                    Sub(LVar0, 45)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260007)
            Wait(5)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_sam2_downed_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x26000B)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Wait(1)
    EndSwitch
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(1)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
            Wait(3)
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sam2_Script_TakeTurn_8021CADC = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x280004)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(UseBattleCamPreset, 66)
            Call(SetBattleCamDist, 300)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(SetBattleCamTargetingModes, -1, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8416)
            Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280005)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 705)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Sub(LVar0, 80)
            Set(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280005)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
            Thread
                Loop(4)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8415)
                    Wait(4)
                EndLoop
            EndThread
            Call(SetAnimation, ACTOR_SELF, 2, 0x280002)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Call(SetAnimationRate, ACTOR_SELF, 2, Float(3.0))
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(10)
            Call(SetAnimationRate, ACTOR_SELF, 2, Float(1.0))
            Call(UseBattleCamPreset, 2)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 2, 0x280004)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(b_area_sam2_paragoomba_EVS_Paragoomba_GoHome)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseDefault
            Wait(10)
            Call(UseBattleCamPreset, 66)
            Call(SetBattleCamDist, 300)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(SetBattleCamTargetingModes, -1, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8416)
            Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280005)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 705)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280005)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    EndSwitch
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280004)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Wait(5)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 2, 0x280004)
            ExecWait(b_area_sam2_paragoomba_EVS_Paragoomba_GoHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

void TTYD64_InstallBattles_sam2(void) {
    Mod_SetBattleList("TTYD64", 0x1E, TTYD64_sam2_FormationTable);
}
