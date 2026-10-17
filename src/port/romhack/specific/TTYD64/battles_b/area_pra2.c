#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_drop_tables.h"
#include "../include/ttyd64_rawmem.h"
#include "../include/ttyd64_symbols.h"
#include "battles_b.h"
#include "battles_b_imports.h"

API_CALLABLE(b_area_pra2_crystal_king_SetBoltColors);
API_CALLABLE(b_area_pra2_crystal_king_SetBreathColors);
API_CALLABLE(b_area_pra2_crystal_king_SetMistColors);
API_CALLABLE(b_area_pra2_crystal_king_StartRumbleWithParams);
extern Vec3i b_area_pra2_CrystalBitPos1;
extern Vec3i b_area_pra2_CrystalBitPos2;
extern Vec3i b_area_pra2_CrystalBitPos3;
extern Vec3i b_area_pra2_KingPos;
extern ActorPartBlueprint b_area_pra2_crystal_bit_CubeParts[];
extern EvtScript b_area_pra2_crystal_bit_EVS_HandlePhase;
extern EvtScript b_area_pra2_crystal_bit_EVS_Idle;
extern EvtScript b_area_pra2_crystal_bit_EVS_TakeTurn;
extern ActorPartBlueprint b_area_pra2_crystal_bit_PrismParts[];
extern ActorPartBlueprint b_area_pra2_crystal_bit_SphereParts[];
extern s32 b_area_pra2_crystal_bit_StatusTable[];
extern ActorPartBlueprint b_area_pra2_crystal_king_ActorParts[];
extern Vec3i b_area_pra2_crystal_king_CloneSummonPos;
extern u8 b_area_pra2_crystal_king_CubeBitSummonData[];
extern EvtScript b_area_pra2_crystal_king_EVS_Death;
extern EvtScript b_area_pra2_crystal_king_EVS_Idle;
extern EvtScript b_area_pra2_crystal_king_EVS_InhaleBit;
extern EvtScript b_area_pra2_crystal_king_EVS_Move_MakeClones;
extern EvtScript b_area_pra2_crystal_king_EVS_Move_Recover;
extern EvtScript b_area_pra2_crystal_king_EVS_RemoveBit;
extern EvtScript b_area_pra2_crystal_king_EVS_RemoveClone;
extern EvtScript b_area_pra2_crystal_king_EVS_SummonBit;
extern u8 b_area_pra2_crystal_king_PrismBitSummonData[];
extern u8 b_area_pra2_crystal_king_SphereBitSummonData[];
extern s32 b_area_pra2_crystal_king_StatusTable[];
extern Stage b_area_pra2_sam_04;
extern EvtScript TTYD64_imp_20_CrystalKing_Script_TripleFrostBreath_20;
extern EvtScript TTYD64_imp_20_CrystalKing_Script_HandleEvent_80219F30_20;
extern EvtScript TTYD64_imp_20_CrystalKing_Script_HandleEvent_802207C8_20;
extern EvtScript TTYD64_imp_20_CrystalKing_Script_FrostBolt_20;
extern EvtScript TTYD64_imp_20_CrystalKing_Script_FrostBreath_20;
extern EvtScript TTYD64_imp_20_CrystalKing_Script_TakeTurn_8021AEEC_20;
extern EvtScript TTYD64_imp_20_CrystalKing_Script_SpitAllRocks_20;
extern EvtScript TTYD64_imp_20_CrystalKing_Script_8021952C_20;
extern EvtScript TTYD64_imp_20_CrystalKing_Script_TripleFrostBreath_HitAnimation;
extern EvtScript TTYD64_imp_20_CrystalKing_Script_SummonRocks_20;
extern EvtScript TTYD64_imp_20_CrystalKing_Script_SpitRock_20;
extern EvtScript TTYD64_imp_20_CrystalKing_Script_FrostBreath_HitAnimation;
extern EvtScript TTYD64_imp_20_CrystalKing_Script_Init_80218B40_20;
extern FormationRow TTYD64_pra2_Formation_00[];
extern EvtScript TTYD64_imp_20_CrystalKing_Script_Init_802206BC_20;
extern ActorBlueprint TTYD64_imp_20_CrystalKing_CrystalBitA_20;
extern ActorBlueprint TTYD64_imp_20_CrystalKing_CrystalBitB_20;
extern Battle TTYD64_pra2_FormationTable[];
extern ActorBlueprint TTYD64_imp_20_CrystalKing_CrystalBitC_20;
extern ActorBlueprint TTYD64_imp_20_CrystalKing_20_CrystalKing;
extern FormationRow TTYD64_imp_20_CrystalKing_SpecialFormation_8021D5E8_20[];
extern FormationRow TTYD64_imp_20_CrystalKing_SpecialFormation_8021D620_20[];
extern FormationRow TTYD64_imp_20_CrystalKing_SpecialFormation_8021D604_20[];

static Vec3f TTYD64_pra2_crystal_king_BitSuctionPaths[3][3];
// clang-format off
EvtScript TTYD64_imp_20_CrystalKing_Script_TripleFrostBreath_20 = {
    Call(GetActorVar, ACTOR_SELF, 2, LVarA)
    Call(GetActorVar, ACTOR_SELF, 3, LVarB)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(UseIdleAnimation, LVarA, 0)
    Call(UseIdleAnimation, LVarB, 0)
    Call(GetActorVar, 512, 0, LVar0)
    BitwiseOrConst(LVar0, 64)
    Call(SetActorVar, 512, 0, LVar0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamDist, 350)
    Call(SetBattleCamOffsetY, 35)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        Call(SetBattleCamTarget, 70, 41, 5)
    Else
        Call(SetBattleCamTarget, 70, 0, 5)
    EndIf
    Call(MoveBattleCamOver, 15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7F0013)
    Call(SetAnimation, LVarA, 1, 0x7F0013)
    Call(SetAnimation, LVarB, 1, 0x7F0013)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 8301)
    Call(PlaySoundAtActor, LVarA, 8301)
    Call(PlaySoundAtActor, LVarB, 8301)
    Call(GetStatusFlags, ACTOR_SELF, LVar9)
    IfNotFlag(LVar9, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 20)
        Add(LVar2, -5)
        Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
        Add(LVar1, 20)
        Add(LVar2, -5)
        Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
        Add(LVar1, 20)
        Add(LVar2, -5)
        Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 8)
        Add(LVar2, -2)
        Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 8, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
        Add(LVar1, 8)
        Add(LVar2, -2)
        Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 8, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
        Add(LVar1, 8)
        Add(LVar2, -2)
        Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 8, 0, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Wait(30)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7F001C)
    Call(SetAnimation, LVarA, 1, 0x7F001C)
    Call(SetAnimation, LVarB, 1, 0x7F001C)
    Wait(3)
    Call(PlaySoundAtActor, ACTOR_SELF, 861)
    Call(EnemyTestTarget, ACTOR_SELF, LVar5, 0, 0, 1, 16)
    Switch(LVar5)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVar6, 0, 0, 1, 16)
            Switch(LVar6)
                CaseOrEq(6)
                CaseOrEq(5)
                    Call(GetActorFlags, ACTOR_SELF, LVar0)
                    IfFlag(LVar0, 512)
                        SetF(LVar3, Float(195.0))
                    Else
                        SetF(LVar3, Float(180.0))
                    EndIf
                    Call(b_area_pra2_crystal_king_StartRumbleWithParams, 100, 60)
                    Thread
                        Call(ShakeCam, 1, 0, 30, Float(0.2998046875))
                    EndThread
                    Call(GetStatusFlags, ACTOR_SELF, LVar9)
                    IfNotFlag(LVar9, 0x80000)
                        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                        Add(LVar0, -15)
                        Add(LVar1, 20)
                        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, LVar3, Float(2.0), Float(1.0), 30, 0, 0, 0, 0, 0)
                        Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
                        Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
                        Add(LVar0, -15)
                        Add(LVar1, 20)
                        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, LVar3, Float(2.0), Float(1.0), 30, 0, 0, 0, 0, 0)
                        Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
                        Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
                        Add(LVar0, -15)
                        Add(LVar1, 20)
                        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, LVar3, Float(2.0), Float(1.0), 30, 0, 0, 0, 0, 0)
                        Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
                    Else
                        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                        Add(LVar0, -6)
                        Add(LVar1, 8)
                        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, LVar3, Float(2.0), Float(0.400390625), 30, 0, 0, 0, 0, 0)
                        Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
                        Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
                        Add(LVar0, -6)
                        Add(LVar1, 8)
                        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, LVar3, Float(2.0), Float(0.400390625), 30, 0, 0, 0, 0, 0)
                        Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
                        Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
                        Add(LVar0, -6)
                        Add(LVar1, 8)
                        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, LVar3, Float(2.0), Float(0.400390625), 30, 0, 0, 0, 0, 0)
                        Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
                    EndIf
                    Wait(30)
                    Call(StopSound, 861)
                    IfEq(LVar5, 5)
                        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
                        Call(SetGoalToTarget, ACTOR_SELF)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    IfEq(LVar6, 5)
                        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                        Call(SetGoalToTarget, ACTOR_SELF)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    Wait(20)
                    Call(UseBattleCamPreset, 2)
                    Call(GetActorVar, 512, 0, LVar0)
                    BitwiseAndConst(LVar0, -65)
                    Call(SetActorVar, 512, 0, LVar0)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Call(UseIdleAnimation, LVarA, 1)
                    Call(UseIdleAnimation, LVarB, 1)
                    Return
                EndCaseGroup
                CaseDefault
                    IfEq(LVar5, 5)
                        Thread
                            Wait(30)
                            Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
                            Call(SetGoalToTarget, ACTOR_SELF)
                            Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                        EndThread
                    EndIf
                    ExecWait(TTYD64_imp_20_CrystalKing_Script_TripleFrostBreath_HitAnimation)
                    Wait(2)
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000008, 0, 0, 8, 32)
                    Switch(LVar0)
                        CaseOrEq(0)
                        CaseOrEq(2)
                            Call(UseBattleCamPreset, 2)
                            Wait(20)
                        EndCaseGroup
                    EndSwitch
                    Call(GetActorVar, 512, 0, LVar0)
                    BitwiseAndConst(LVar0, -65)
                    Call(SetActorVar, 512, 0, LVar0)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Call(UseIdleAnimation, LVarA, 1)
                    Call(UseIdleAnimation, LVarB, 1)
                    Return
            EndSwitch
    EndSwitch
    ExecWait(TTYD64_imp_20_CrystalKing_Script_TripleFrostBreath_HitAnimation)
    Wait(2)
    Thread
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyTestTarget, ACTOR_SELF, LVar6, 0, 0, 1, 16)
        Switch(LVar6)
            CaseOrEq(6)
            CaseOrEq(5)
                IfEq(LVar6, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
            EndCaseGroup
            CaseDefault
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000008, 0, 0, 8, 32)
        EndSwitch
    EndThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000008, 0, 0, 8, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(20)
        EndCaseGroup
    EndSwitch
    Call(GetActorVar, 512, 0, LVar0)
    BitwiseAndConst(LVar0, -65)
    Call(SetActorVar, 512, 0, LVar0)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Call(UseIdleAnimation, LVarA, 1)
    Call(UseIdleAnimation, LVarB, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_20_CrystalKing_Script_HandleEvent_80219F30_20 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, 512, 0, LVar0)
    BitwiseOrConst(LVar0, 64)
    Call(SetActorVar, 512, 0, LVar0)
    Call(SetPartAlpha, ACTOR_SELF, 1, 255)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Call(GetActorVar, 512, 0, LVar0)
            BitwiseOrConst(LVar0, 1)
            Call(SetActorVar, 512, 0, LVar0)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            Call(ActorExists, LVar0, LVar1)
            IfEq(LVar1, 1)
                Thread
                    Call(SetOwnerID, LVar0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x7F0019)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x7F0009)
                EndThread
            EndIf
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            Call(ActorExists, LVar0, LVar1)
            IfEq(LVar1, 1)
                Thread
                    Call(SetOwnerID, LVar0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x7F0019)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x7F0009)
                EndThread
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7F0019)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            Call(ActorExists, LVar0, LVar1)
            IfEq(LVar1, 1)
                Thread
                    Call(SetOwnerID, LVar0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x7F0019)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x7F0009)
                EndThread
            EndIf
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            Call(ActorExists, LVar0, LVar1)
            IfEq(LVar1, 1)
                Thread
                    Call(SetOwnerID, LVar0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x7F0019)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x7F0009)
                EndThread
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7F0019)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_imp_20_CrystalKing_Script_8021952C_20)
        CaseEq(14)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            Call(ActorExists, LVar0, LVar1)
            IfEq(LVar1, 1)
                Thread
                    Call(SetOwnerID, LVar0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x7F0020)
                    SetConst(LVar2, 0x7F0021)
                    ExecWait(Ref(EVS_Enemy_BurnHit))
                EndThread
            EndIf
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            Call(ActorExists, LVar0, LVar1)
            IfEq(LVar1, 1)
                Thread
                    Call(SetOwnerID, LVar0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x7F0020)
                    SetConst(LVar2, 0x7F0021)
                    ExecWait(Ref(EVS_Enemy_BurnHit))
                EndThread
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7F0020)
            SetConst(LVar2, 0x7F0021)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Call(SetAnimation, ACTOR_SELF, 1, 0x7F0019)
            ExecWait(TTYD64_imp_20_CrystalKing_Script_8021952C_20)
        CaseEq(23)
        CaseEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7F0009)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7F0009)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Call(GetActorVar, 512, 0, LVar0)
            IfFlag(LVar0, 1)
                ExecWait(TTYD64_imp_20_CrystalKing_Script_8021952C_20)
                Return
            EndIf
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x35D000)
                ExecWait(TTYD64_imp_20_CrystalKing_Script_8021952C_20)
                Return
            EndIf
        CaseEq(32)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            Call(ActorExists, LVar0, LVar1)
            IfEq(LVar1, 1)
                Thread
                    Call(SetOwnerID, LVar0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x7F0019)
                    ExecWait(Ref(EVS_Enemy_Hit))
                EndThread
            EndIf
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            Call(ActorExists, LVar0, LVar1)
            IfEq(LVar1, 1)
                Thread
                    Call(SetOwnerID, LVar0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x7F0019)
                    ExecWait(Ref(EVS_Enemy_Hit))
                EndThread
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7F0019)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_pra2_crystal_king_EVS_Death)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7F0019)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(36)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            Call(ActorExists, LVar0, LVar1)
            IfEq(LVar1, 1)
                Thread
                    Call(SetOwnerID, LVar0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x7F0020)
                    SetConst(LVar2, 0x7F0021)
                    ExecWait(Ref(EVS_Enemy_BurnHit))
                EndThread
            EndIf
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            Call(ActorExists, LVar0, LVar1)
            IfEq(LVar1, 1)
                Thread
                    Call(SetOwnerID, LVar0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x7F0020)
                    SetConst(LVar2, 0x7F0021)
                    ExecWait(Ref(EVS_Enemy_BurnHit))
                EndThread
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7F0020)
            SetConst(LVar2, 0x7F0021)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_pra2_crystal_king_EVS_Death)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7F0021)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            Thread
                Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                Switch(LVar0)
                    CaseOrEq(4)
                    CaseOrEq(5)
                        SetF(LVar0, Float(0.400390625))
                        Loop(30)
                            SetF(LVar1, Float(1.0))
                            SubF(LVar1, LVar0)
                            DivF(LVar1, Float(6.0))
                            AddF(LVar0, LVar1)
                            Call(GetActorVar, ACTOR_SELF, 2, LVarA)
                            Call(ActorExists, LVarA, LVarB)
                            IfEq(LVarB, 1)
                                Call(SetPartScale, LVarA, 1, LVar0, LVar0, LVar0)
                            EndIf
                            Call(GetActorVar, ACTOR_SELF, 3, LVarA)
                            Call(ActorExists, LVarA, LVarB)
                            IfEq(LVarB, 1)
                                Call(SetPartScale, LVarA, 1, LVar0, LVar0, LVar0)
                            EndIf
                            Wait(1)
                        EndLoop
                    EndCaseGroup
                    CaseOrEq(0)
                    CaseOrEq(2)
                        SetF(LVar0, Float(0.400390625))
                        Loop(30)
                            SetF(LVar1, Float(1.0))
                            SubF(LVar1, LVar0)
                            DivF(LVar1, Float(6.0))
                            AddF(LVar0, LVar1)
                            Call(GetActorVar, ACTOR_SELF, 4, LVarA)
                            Call(ActorExists, LVarA, LVarB)
                            IfEq(LVarB, 1)
                                Call(SetPartScale, LVarA, 1, LVar0, LVar0, LVar0)
                            EndIf
                            Call(GetActorVar, ACTOR_SELF, 5, LVarA)
                            Call(ActorExists, LVarA, LVarB)
                            IfEq(LVarB, 1)
                                Call(SetPartScale, LVarA, 1, LVar0, LVar0, LVar0)
                            EndIf
                            Call(GetActorVar, ACTOR_SELF, 6, LVarA)
                            Call(ActorExists, LVarA, LVarB)
                            IfEq(LVarB, 1)
                                Call(SetPartScale, LVarA, 1, LVar0, LVar0, LVar0)
                            EndIf
                            Wait(1)
                        EndLoop
                    EndCaseGroup
                EndSwitch
            EndThread
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7F0009)
            ExecWait(Ref(EVS_Enemy_Recover))
            Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
            IfLe(LVar0, 1)
                Call(SetAnimation, ACTOR_SELF, 1, 0x7F000E)
                Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
                Call(SetGoalPos, ACTOR_SELF, 70, 0, 5)
                Call(RunToGoal, ACTOR_SELF, 0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x7F0009)
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7F0019)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(63)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
        CaseDefault
    EndSwitch
    Call(GetActorVar, 512, 0, LVar0)
    BitwiseAndConst(LVar0, -65)
    Call(SetActorVar, 512, 0, LVar0)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_20_CrystalKing_Script_HandleEvent_802207C8_20 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            Call(GetAnimation, ACTOR_SELF, 1, LVar1)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            Call(GetOwnerID, LVar0)
            Call(GetActorVar, 512, 4, LVar3)
            IfEq(LVar0, LVar3)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x7F0022)
                SetConst(LVar2, -1)
            EndIf
            Call(GetActorVar, 512, 5, LVar3)
            IfEq(LVar0, LVar3)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x7F0023)
                SetConst(LVar2, -1)
            EndIf
            Call(GetActorVar, 512, 6, LVar3)
            IfEq(LVar0, LVar3)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x7F0024)
                SetConst(LVar2, -1)
            EndIf
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            Call(GetAnimation, ACTOR_SELF, 1, LVar1)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            Call(GetAnimation, ACTOR_SELF, 1, LVar1)
            ExecWait(Ref(EVS_Enemy_Hit))
            Call(HideHealthBar, ACTOR_SELF)
            Call(PlaySoundAtActor, ACTOR_SELF, 769)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
            Call(SetGoalPos, ACTOR_SELF, LVar1, 0, LVar3)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(GetOwnerID, LVar0)
            Call(GetActorVar, 512, 4, LVar1)
            IfEq(LVar0, LVar1)
                Call(SetAnimation, ACTOR_SELF, 1, 0x7F0005)
            EndIf
            Call(GetActorVar, 512, 5, LVar1)
            IfEq(LVar0, LVar1)
                Call(SetAnimation, ACTOR_SELF, 1, 0x7F0006)
            EndIf
            Call(GetActorVar, 512, 6, LVar1)
            IfEq(LVar0, LVar1)
                Call(SetAnimation, ACTOR_SELF, 1, 0x7F0007)
            EndIf
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Call(RandInt, 360, LVar0)
            Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
            Call(AddVectorPolar, LVar1, LVar3, Float(30.0), LVar0)
            Call(SetGoalPos, ACTOR_SELF, LVar1, 0, LVar3)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(AddVectorPolar, LVar1, LVar3, Float(20.0), LVar0)
            Call(SetGoalPos, ACTOR_SELF, LVar1, 0, LVar3)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(AddVectorPolar, LVar1, LVar3, Float(10.0), LVar0)
            Call(SetGoalPos, ACTOR_SELF, LVar1, 0, LVar3)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Set(LVar0, 255)
            Loop(20)
                Sub(LVar0, 12)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Call(RemoveEffect, LVar0)
            Call(RemoveActor, ACTOR_SELF)
            Return
        CaseEq(36)
            Call(GetOwnerID, LVar0)
            Call(GetActorVar, 512, 4, LVar3)
            IfEq(LVar0, LVar3)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x7F0022)
                SetConst(LVar2, -1)
            EndIf
            Call(GetActorVar, 512, 5, LVar3)
            IfEq(LVar0, LVar3)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x7F0023)
                SetConst(LVar2, -1)
            EndIf
            Call(GetActorVar, 512, 6, LVar3)
            IfEq(LVar0, LVar3)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x7F0024)
                SetConst(LVar2, -1)
            EndIf
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Call(HideHealthBar, ACTOR_SELF)
            Call(PlaySoundAtActor, ACTOR_SELF, 769)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
            Call(SetGoalPos, ACTOR_SELF, LVar1, 0, LVar3)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Call(RandInt, 360, LVar0)
            Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
            Call(AddVectorPolar, LVar1, LVar3, Float(30.0), LVar0)
            Call(SetGoalPos, ACTOR_SELF, LVar1, 0, LVar3)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(AddVectorPolar, LVar1, LVar3, Float(20.0), LVar0)
            Call(SetGoalPos, ACTOR_SELF, LVar1, 0, LVar3)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(AddVectorPolar, LVar1, LVar3, Float(10.0), LVar0)
            Call(SetGoalPos, ACTOR_SELF, LVar1, 0, LVar3)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Set(LVar0, 255)
            Loop(20)
                Sub(LVar0, 12)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Call(RemoveEffect, LVar0)
            Call(RemoveActor, ACTOR_SELF)
            Return
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Call(RemoveEffect, LVar0)
            Return
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_20_CrystalKing_Script_FrostBolt_20 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7F0013)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 8301)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 20)
        Add(LVar2, -5)
        Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 8)
        Add(LVar2, -2)
        Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 8, 0, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Wait(30)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7F001C)
    Wait(3)
    Call(PlaySoundAtActor, ACTOR_SELF, 736)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfNotFlag(LVar3, 0x80000)
                Add(LVar0, -15)
                Add(LVar1, 20)
            Else
                Add(LVar0, -6)
                Add(LVar1, 8)
            EndIf
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -50, 20, 0)
            Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Thread
                Sub(LVar3, LVar0)
                Sub(LVar4, LVar1)
                Sub(LVar5, LVar2)
                Div(LVar3, 10)
                Div(LVar4, 10)
                Div(LVar5, 10)
                Loop(10)
                    Add(LVar0, LVar3)
                    Add(LVar1, LVar4)
                    Add(LVar2, LVar5)
                    Call(PlayEffect_impl, 114, 1, LVar0, LVar1, LVar2, 20, -20, Float(1.0), 5, 30, 0, 0, 0, 0)
                    Wait(1)
                EndLoop
            EndThread
            Wait(3)
            Call(PlayEffect_impl, 94, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.0), 20, 0, 0, 0, 0)
            Call(b_area_pra2_crystal_king_SetBoltColors, LVarF)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x7F0015)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
    EndSwitch
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar0, -15)
        Add(LVar1, 20)
    Else
        Add(LVar0, -6)
        Add(LVar1, 8)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Thread
        Sub(LVar3, LVar0)
        Sub(LVar4, LVar1)
        Sub(LVar5, LVar2)
        Div(LVar3, 10)
        Div(LVar4, 10)
        Div(LVar5, 10)
        Loop(10)
            Add(LVar0, LVar3)
            Add(LVar1, LVar4)
            Add(LVar2, LVar5)
            Call(PlayEffect_impl, 114, 1, LVar0, LVar1, LVar2, 20, -20, Float(1.0), 5, 30, 0, 0, 0, 0)
            Wait(1)
        EndLoop
    EndThread
    Wait(3)
    Call(PlayEffect_impl, 94, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.0), 20, 0, 0, 0, 0)
    Call(b_area_pra2_crystal_king_SetBoltColors, LVarF)
    Wait(7)
    Thread
        Wait(3)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7F0015)
    EndThread
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000008, 0, 0x42FE, 6, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 111, 0, LVar0, LVar1, LVar2, Float(2.0), 30, 0, 0, 0, 0, 0, 0, 0)
            Call(b_area_pra2_crystal_king_SetMistColors, LVarF)
            Wait(30)
            Call(UseBattleCamPreset, 2)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_20_CrystalKing_Script_FrostBreath_20 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7F0013)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 8301)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 20)
        Add(LVar2, -5)
        Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 8)
        Add(LVar2, -2)
        Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 8, 0, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Wait(30)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7F001C)
    Wait(3)
    Call(PlaySoundAtActor, ACTOR_SELF, 861)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar0, -15)
                Add(LVar1, 20)
                Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, Float(180.0), Float(2.0), Float(0.5), 30, 0, 0, 0, 0, 0)
                Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
            Else
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar0, -6)
                Add(LVar1, 8)
                Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, Float(180.0), Float(2.0), Float(0.2001953125), 30, 0, 0, 0, 0, 0)
                Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
            EndIf
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarB, 0, 0, 1, 16)
            Switch(LVarB)
                CaseOrEq(6)
                CaseOrEq(5)
                    Call(b_area_pra2_crystal_king_StartRumbleWithParams, 70, 60)
                    Thread
                        Call(ShakeCam, 1, 0, 30, Float(0.2998046875))
                    EndThread
                    Wait(30)
                    Call(StopSound, 861)
                    IfEq(LVarA, 5)
                        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
                        Call(SetGoalToTarget, ACTOR_SELF)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    IfEq(LVarB, 5)
                        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                        Call(SetGoalToTarget, ACTOR_SELF)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    Wait(20)
                    Call(UseBattleCamPreset, 2)
                    Call(EnableIdleScript, ACTOR_SELF, 1)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
                EndCaseGroup
                CaseDefault
                    IfEq(LVarA, 5)
                        Thread
                            Wait(30)
                            Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
                            Call(SetGoalToTarget, ACTOR_SELF)
                            Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                        EndThread
                    EndIf
                    ExecWait(TTYD64_imp_20_CrystalKing_Script_FrostBreath_HitAnimation)
                    Wait(2)
                    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000008, 0, 0, 8, 32)
                    Switch(LVar0)
                        CaseOrEq(0)
                        CaseOrEq(2)
                            Call(UseBattleCamPreset, 2)
                        EndCaseGroup
                    EndSwitch
            EndSwitch
    EndSwitch
    ExecWait(TTYD64_imp_20_CrystalKing_Script_FrostBreath_HitAnimation)
    Wait(2)
    Thread
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyTestTarget, ACTOR_SELF, LVarB, 0, 0, 1, 16)
        Switch(LVarB)
            CaseOrEq(6)
            CaseOrEq(5)
                IfEq(LVarB, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
            EndCaseGroup
            CaseDefault
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000008, 0, 0, 8, 32)
        EndSwitch
    EndThread
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000008, 0, 0, 8, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_20_CrystalKing_Script_TakeTurn_8021AEEC_20 = {
    Call(GetActorHP, ACTOR_SELF, LVar0)
    IfLe(LVar0, 20)
        Call(GetActorVar, 512, 0, LVar0)
        BitwiseOrConst(LVar0, 2)
        Call(SetActorVar, 512, 0, LVar0)
    EndIf
    Set(LFlag0, 0)
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
    Mul(LVar0, 100)
    Div(LVar0, LVar1)
    Switch(LVar0)
        CaseLt(25)
            Call(RandInt, 99, LVar0)
            Add(LVar0, 1)
            IfLe(LVar0, 100)
                Call(GetActorVar, ACTOR_SELF, 7, LVar0)
                IfLt(LVar0, 2)
                    Set(LFlag0, 1)
                EndIf
            EndIf
        CaseLt(40)
            Call(RandInt, 99, LVar0)
            Add(LVar0, 1)
            IfLe(LVar0, 30)
                Call(GetActorVar, ACTOR_SELF, 7, LVar0)
                IfLt(LVar0, 2)
                    Set(LFlag0, 1)
                EndIf
            EndIf
        CaseLt(55)
            Call(RandInt, 99, LVar0)
            Add(LVar0, 1)
            IfLe(LVar0, 10)
                Call(GetActorVar, ACTOR_SELF, 7, LVar0)
                IfLt(LVar0, 2)
                    Set(LFlag0, 1)
                EndIf
            EndIf
    EndSwitch
    IfEq(LFlag0, 1)
        Call(GetActorVar, ACTOR_SELF, 7, LVar0)
        Add(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 7, LVar0)
        ExecWait(b_area_pra2_crystal_king_EVS_Move_Recover)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
            IfLe(LVar0, 1)
                ExecWait(TTYD64_imp_20_CrystalKing_Script_SummonRocks_20)
                Call(SetActorVar, ACTOR_SELF, 1, 2)
            Else
                ExecWait(TTYD64_imp_20_CrystalKing_Script_SpitAllRocks_20)
                Call(SetActorVar, ACTOR_SELF, 1, 1)
            EndIf
        CaseEq(1)
            ExecWait(TTYD64_imp_20_CrystalKing_Script_SummonRocks_20)
            Call(SetActorVar, ACTOR_SELF, 1, 2)
        CaseEq(2)
            Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
            IfLe(LVar0, 1)
                Call(GetStatusFlags, 0, LVar0)
                IfNotFlag(LVar0, 0x4000)
                    Call(TTYD64_GetPartnerHP_API, LVar1)
                    IfGt(LVar1, 0)
                        Call(GetStatusFlags, 256, LVar0)
                    EndIf
                EndIf
                IfFlag(LVar0, 0x4000)
                    ExecWait(TTYD64_imp_20_CrystalKing_Script_FrostBreath_20)
                Else
                    ExecWait(TTYD64_imp_20_CrystalKing_Script_FrostBolt_20)
                EndIf
            Else
                ExecWait(TTYD64_imp_20_CrystalKing_Script_SpitAllRocks_20)
            EndIf
            Call(SetActorVar, ACTOR_SELF, 1, 3)
        CaseEq(3)
            Call(GetActorHP, ACTOR_SELF, LVar0)
            IfGt(LVar0, 35)
                Call(GetActorVar, 512, 0, LVar0)
                IfNotFlag(LVar0, 4)
                    ExecWait(TTYD64_imp_20_CrystalKing_Script_SummonRocks_20)
                    Call(SetActorVar, ACTOR_SELF, 1, 2)
                    Return
                EndIf
            EndIf
            Call(GetActorVar, 512, 0, LVar0)
            IfNotFlag(LVar0, 16)
                ExecWait(TTYD64_imp_20_CrystalKing_Script_FrostBolt_20)
                Call(GetActorVar, 512, 0, LVar0)
                BitwiseOrConst(LVar0, 16)
                Call(SetActorVar, 512, 0, LVar0)
            Else
                ExecWait(b_area_pra2_crystal_king_EVS_Move_MakeClones)
                Call(SetActorVar, ACTOR_SELF, 1, 4)
                Call(GetActorVar, 512, 0, LVar0)
                BitwiseOrConst(LVar0, 4)
                Call(SetActorVar, 512, 0, LVar0)
            EndIf
        CaseEq(4)
            Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
            IfLe(LVar0, 1)
                Call(GetStatusFlags, 0, LVar0)
                IfNotFlag(LVar0, 0x4000)
                    Call(TTYD64_GetPartnerHP_API, LVar1)
                    IfGt(LVar1, 0)
                        Call(GetStatusFlags, 256, LVar0)
                    EndIf
                EndIf
                IfFlag(LVar0, 0x4000)
                    ExecWait(TTYD64_imp_20_CrystalKing_Script_FrostBreath_20)
                Else
                    ExecWait(TTYD64_imp_20_CrystalKing_Script_FrostBolt_20)
                EndIf
                Call(SetActorVar, ACTOR_SELF, 1, 3)
            Else
                ExecWait(TTYD64_imp_20_CrystalKing_Script_TripleFrostBreath_20)
                Call(SetActorVar, ACTOR_SELF, 1, 5)
            EndIf
        CaseEq(5)
            Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
            IfGt(LVar0, 1)
                ExecWait(TTYD64_imp_20_CrystalKing_Script_TripleFrostBreath_20)
                Return
            EndIf
            ExecWait(b_area_pra2_crystal_king_EVS_Move_MakeClones)
            Call(SetActorVar, ACTOR_SELF, 1, 4)
            Call(GetActorVar, 512, 0, LVar0)
            BitwiseOrConst(LVar0, 4)
            Call(SetActorVar, 512, 0, LVar0)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_20_CrystalKing_Script_SpitAllRocks_20 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7F001C)
    Wait(20)
    Call(b_area_pra2_crystal_king_StartRumbleWithParams, 70, 60)
    Thread
        Call(ShakeCam, 1, 0, 30, Float(0.2001953125))
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 943)
    Call(GetActorVar, ACTOR_SELF, 4, LVar0)
    Call(ActorExists, LVar0, LVar1)
    IfEq(LVar1, 1)
        Set(LVar1, Ref(TTYD64_pra2_crystal_king_BitSuctionPaths))
        ExecGetTID(b_area_pra2_crystal_king_EVS_InhaleBit, LVarA)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    Call(ActorExists, LVar0, LVar1)
    IfEq(LVar1, 1)
        Set(LVar1, (Bytecode) (((u8*) &TTYD64_pra2_crystal_king_BitSuctionPaths + 0x24)))
        ExecGetTID(b_area_pra2_crystal_king_EVS_InhaleBit, LVarA)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    Call(ActorExists, LVar0, LVar1)
    IfEq(LVar1, 1)
        Set(LVar1, (Bytecode) (((u8*) &TTYD64_pra2_crystal_king_BitSuctionPaths + 0x48)))
        ExecGetTID(b_area_pra2_crystal_king_EVS_InhaleBit, LVarA)
    EndIf
    Label(0)
    IsThreadRunning(LVarA, LVar0)
    IfEq(LVar0, 1)
        Wait(1)
        Goto(0)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x7F0013)
    Wait(30)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 15)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVar9, LVar0)
            Call(GetActorVar, ACTOR_SELF, 4, LVar0)
            Call(ActorExists, LVar0, LVar1)
            IfEq(LVar1, 1)
                Call(SetAnimation, ACTOR_SELF, 1, 0x7F001C)
                ExecGetTID(b_area_pra2_crystal_king_EVS_RemoveBit, LVarA)
                Wait(4)
                Call(SetAnimation, ACTOR_SELF, 1, 0x7F0015)
                Wait(6)
            EndIf
            Call(GetActorVar, ACTOR_SELF, 5, LVar0)
            Call(ActorExists, LVar0, LVar1)
            IfEq(LVar1, 1)
                Call(SetAnimation, ACTOR_SELF, 1, 0x7F001C)
                ExecGetTID(b_area_pra2_crystal_king_EVS_RemoveBit, LVarA)
                Wait(4)
                Call(SetAnimation, ACTOR_SELF, 1, 0x7F0015)
                Wait(6)
            EndIf
            Call(GetActorVar, ACTOR_SELF, 6, LVar0)
            Call(ActorExists, LVar0, LVar1)
            IfEq(LVar1, 1)
                Call(SetAnimation, ACTOR_SELF, 1, 0x7F001C)
                ExecGetTID(b_area_pra2_crystal_king_EVS_RemoveBit, LVarA)
                Wait(4)
                Call(SetAnimation, ACTOR_SELF, 1, 0x7F0015)
                Wait(6)
            EndIf
            Label(1)
            IsThreadRunning(LVarA, LVar0)
            IfEq(LVar0, 1)
                Wait(1)
                Goto(1)
            EndIf
            IfEq(LVar9, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(30)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 4, LVar0)
    Call(ActorExists, LVar0, LVar1)
    IfEq(LVar1, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7F001C)
        ExecGetTID(TTYD64_imp_20_CrystalKing_Script_SpitRock_20, LVarA)
        Wait(4)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7F0015)
        Wait(6)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    Call(ActorExists, LVar0, LVar1)
    IfEq(LVar1, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7F001C)
        ExecGetTID(TTYD64_imp_20_CrystalKing_Script_SpitRock_20, LVarA)
        Wait(4)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7F0015)
        Wait(6)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    Call(ActorExists, LVar0, LVar1)
    IfEq(LVar1, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7F001C)
        ExecGetTID(TTYD64_imp_20_CrystalKing_Script_SpitRock_20, LVarA)
        Wait(4)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7F0015)
        Wait(6)
    EndIf
    Label(4)
    IsThreadRunning(LVarA, LVar0)
    IfEq(LVar0, 1)
        Wait(1)
        Goto(4)
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_20_CrystalKing_Script_8021952C_20 = {
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseOrEq(4)
        CaseOrEq(5)
        EndCaseGroup
        CaseOrEq(0)
        CaseOrEq(2)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x3DD000)
                Call(GetActorVar, ACTOR_SELF, 4, LVar0)
                Call(ActorExists, LVar0, LVar1)
                IfEq(LVar1, 1)
                    Call(SetDamageSource, 0)
                    Call(DispatchEvent, LVar0, 32)
                EndIf
                Call(GetActorVar, ACTOR_SELF, 5, LVar0)
                Call(ActorExists, LVar0, LVar1)
                IfEq(LVar1, 1)
                    Call(SetDamageSource, 0)
                    Call(DispatchEvent, LVar0, 32)
                EndIf
                Call(GetActorVar, ACTOR_SELF, 6, LVar0)
                Call(ActorExists, LVar0, LVar1)
                IfEq(LVar1, 1)
                    Call(SetDamageSource, 0)
                    Call(DispatchEvent, LVar0, 32)
                EndIf
            EndIf
            Return
        EndCaseGroup
        CaseDefault
            Return
    EndSwitch
    Call(GetLastElement, LVar0)
    IfFlag(LVar0, 0x20000000)
        Label(0)
        Call(GetBattleFlags, LVar0)
        IfFlag(LVar0, 256)
            Wait(1)
            Goto(0)
        EndIf
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar9)
    Call(ActorExists, LVar9, LVarA)
    IfEq(LVarA, 1)
        Call(GetActorVar, ACTOR_SELF, 2, LVar9)
        Exec(b_area_pra2_crystal_king_EVS_RemoveClone)
        Call(GetActorVar, ACTOR_SELF, 3, LVar9)
        ExecGetTID(b_area_pra2_crystal_king_EVS_RemoveClone, LVar0)
        Label(1)
        IsThreadRunning(LVar0, LVar1)
        IfEq(LVar1, 1)
            Wait(1)
            Goto(1)
        EndIf
    EndIf
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7F0019)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfNe(LVar1, 0)
        Call(UseBattleCamPreset, 2)
        Call(GetActorVar, ACTOR_SELF, 8, LVarA)
        KillThread(LVarA)
        Call(PlaySoundAtActor, ACTOR_SELF, 8419)
        Set(LVar1, 0)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
        Call(b_area_pra2_crystal_king_StartRumbleWithParams, 150, 10)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(0.7001953125))
        EndThread
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        Wait(15)
        Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    EndIf
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x35D000)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7F000E)
        Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
        Call(SetGoalPos, ACTOR_SELF, 70, 0, 5)
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7F0009)
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Call(GetActorVar, 512, 0, LVar0)
    BitwiseAndConst(LVar0, -2)
    Call(SetActorVar, 512, 0, LVar0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_20_CrystalKing_Script_TripleFrostBreath_HitAnimation = {
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        SetF(LVar3, Float(195.0))
    Else
        SetF(LVar3, Float(180.0))
    EndIf
    Call(b_area_pra2_crystal_king_StartRumbleWithParams, 100, 120)
    Thread
        Call(ShakeCam, 1, 0, 60, Float(0.2998046875))
    EndThread
    Call(GetStatusFlags, ACTOR_SELF, LVar9)
    IfNotFlag(LVar9, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, -15)
        Add(LVar1, 20)
        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, LVar3, Float(2.0), Float(1.0), 60, 0, 0, 0, 0, 0)
        Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
        Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
        Add(LVar0, -15)
        Add(LVar1, 20)
        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, LVar3, Float(2.0), Float(1.0), 60, 0, 0, 0, 0, 0)
        Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
        Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
        Add(LVar0, -15)
        Add(LVar1, 20)
        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, LVar3, Float(2.0), Float(1.0), 60, 0, 0, 0, 0, 0)
        Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, -6)
        Add(LVar1, 8)
        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, LVar3, Float(2.0), Float(1.0), 60, 0, 0, 0, 0, 0)
        Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
        Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
        Add(LVar0, -6)
        Add(LVar1, 8)
        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, LVar3, Float(2.0), Float(1.0), 60, 0, 0, 0, 0, 0)
        Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
        Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
        Add(LVar0, -6)
        Add(LVar1, 8)
        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, LVar3, Float(2.0), Float(1.0), 60, 0, 0, 0, 0, 0)
        Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
    EndIf
    Wait(60)
    Call(StopSound, 861)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7F0015)
    Call(SetAnimation, LVarA, 1, 0x7F0015)
    Call(SetAnimation, LVarB, 1, 0x7F0015)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_20_CrystalKing_Script_SummonRocks_20 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7F001E)
    Wait(20)
    Call(SummonEnemy, Ref(TTYD64_imp_20_CrystalKing_SpecialFormation_8021D5E8_20), 0)
    Call(SetActorVar, ACTOR_SELF, 4, LVar0)
    Call(SummonEnemy, Ref(TTYD64_imp_20_CrystalKing_SpecialFormation_8021D604_20), 0)
    Call(SetActorVar, ACTOR_SELF, 5, LVar0)
    Call(SummonEnemy, Ref(TTYD64_imp_20_CrystalKing_SpecialFormation_8021D620_20), 0)
    Call(SetActorVar, ACTOR_SELF, 6, LVar0)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(GetActorVar, ACTOR_SELF, 4, LVar0)
        Call(SetPartScale, LVar0, 1, Float(0.400390625), Float(0.400390625), Float(0.400390625))
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        Call(SetPartScale, LVar0, 1, Float(0.400390625), Float(0.400390625), Float(0.400390625))
        Call(GetActorVar, ACTOR_SELF, 6, LVar0)
        Call(SetPartScale, LVar0, 1, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x7F001F)
    Call(PlaySoundAtActor, ACTOR_SELF, 734)
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    SetF(LVar1, Float(42.0))
    SetF(LVar2, Float(85.0))
    SetF(LVar3, Float(-10.0))
    Set(LVar4, Ref(b_area_pra2_crystal_king_PrismBitSummonData))
    Exec(b_area_pra2_crystal_king_EVS_SummonBit)
    Wait(10)
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    SetF(LVar1, Float(112.0))
    SetF(LVar2, Float(52.0))
    SetF(LVar3, Float(-5.0))
    Set(LVar4, Ref(b_area_pra2_crystal_king_SphereBitSummonData))
    Exec(b_area_pra2_crystal_king_EVS_SummonBit)
    Wait(24)
    Call(GetActorVar, ACTOR_SELF, 4, LVar0)
    SetF(LVar1, Float(10.0))
    SetF(LVar2, Float(35.0))
    SetF(LVar3, Float(-5.0))
    Set(LVar4, Ref(b_area_pra2_crystal_king_CubeBitSummonData))
    Exec(b_area_pra2_crystal_king_EVS_SummonBit)
    Wait(130)
    Call(GetActorVar, ACTOR_SELF, 4, LVar0)
    Call(ForceHomePos, LVar0, 10, 35, -5)
    Call(HPBarToHome, LVar0)
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    Call(ForceHomePos, LVar0, 112, 52, -5)
    Call(HPBarToHome, LVar0)
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    Call(ForceHomePos, LVar0, 42, 85, -10)
    Call(HPBarToHome, LVar0)
    Call(UseBattleCamPreset, 2)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_20_CrystalKing_Script_SpitRock_20 = {
    Call(PlaySoundAtActor, ACTOR_SELF, 985)
    Set(LVarA, LVar0)
    Call(SetPartFlagBits, LVarA, 1, 1, 0)
    Call(SetActorFlagBits, LVarA, 4, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetActorPos, LVarA, LVar3, LVar4, LVar5)
    Thread
        Sub(LVar0, LVar3)
        Sub(LVar1, LVar4)
        Sub(LVar2, LVar5)
        Div(LVar0, 10)
        Div(LVar1, 10)
        Div(LVar2, 10)
        Loop(10)
            Add(LVar3, LVar0)
            Add(LVar4, LVar1)
            Add(LVar5, LVar2)
            Call(PlayEffect_impl, 114, 1, LVar3, LVar4, LVar5, 20, -20, Float(1.0), 5, 30, 0, 0, 0, 0)
            Wait(1)
        EndLoop
    EndThread
    Call(SetActorSpeed, LVarA, Float(16.0))
    Call(SetGoalPos, LVarA, LVar0, LVar1, LVar2)
    Call(FlyToGoal, LVarA, 0, 0, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002008, 0, 0, 4, 0)
    Call(SetActorJumpGravity, LVarA, Float(1.0))
    Call(GetActorPos, LVarA, LVar1, LVar2, LVar3)
    Sub(LVar1, 100)
    Call(RandInt, 50, LVar4)
    Add(LVar2, LVar4)
    Call(SetGoalPos, LVarA, LVar1, LVar2, LVar3)
    Call(JumpToGoal, LVarA, 20, 0, 1, 0)
    Call(GetActorVar, LVarA, 0, LVarF)
    Call(RemoveEffect, LVarF)
    Call(RemoveActor, LVarA)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_20_CrystalKing_Script_FrostBreath_HitAnimation = {
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, -15)
        Add(LVar1, 20)
        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, Float(180.0), Float(2.0), Float(1.0), 60, 0, 0, 0, 0, 0)
        Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, -6)
        Add(LVar1, 8)
        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, Float(180.0), Float(2.0), Float(1.0), 60, 0, 0, 0, 0, 0)
        Call(b_area_pra2_crystal_king_SetBreathColors, LVarF)
    EndIf
    Call(b_area_pra2_crystal_king_StartRumbleWithParams, 70, 100)
    Thread
        Call(ShakeCam, 1, 0, 50, Float(0.2998046875))
    EndThread
    Wait(60)
    Call(StopSound, 861)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7F0015)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_20_CrystalKing_Script_Init_80218B40_20 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_20_CrystalKing_Script_TakeTurn_8021AEEC_20))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra2_crystal_king_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_20_CrystalKing_Script_HandleEvent_80219F30_20))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 7, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, -1)
    Call(SetActorVar, ACTOR_SELF, 3, -1)
    Call(SetActorVar, ACTOR_SELF, 4, 513)
    Call(SetActorVar, ACTOR_SELF, 5, 514)
    Call(SetActorVar, ACTOR_SELF, 6, 515)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pra2_Formation_00[] = {
    { .actor = &TTYD64_imp_20_CrystalKing_20_CrystalKing,
      .home = { .vec = &b_area_pra2_KingPos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_20_CrystalKing_CrystalBitA_20,
      .home = { .vec = &b_area_pra2_CrystalBitPos1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_20_CrystalKing_CrystalBitB_20,
      .home = { .vec = &b_area_pra2_CrystalBitPos2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_20_CrystalKing_CrystalBitC_20,
      .home = { .vec = &b_area_pra2_CrystalBitPos3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

// clang-format off
EvtScript TTYD64_imp_20_CrystalKing_Script_Init_802206BC_20 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(b_area_pra2_crystal_bit_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra2_crystal_bit_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_20_CrystalKing_Script_HandleEvent_802207C8_20))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_pra2_crystal_bit_EVS_HandlePhase))
    Return
    End
};
// clang-format on

ActorBlueprint TTYD64_imp_20_CrystalKing_CrystalBitA_20 = {
    .flags = 0x200200,
    .maxHP = 1,
    .type = 0xBF,
    .level = 0,
    .partCount = 2,
    .partsData = b_area_pra2_crystal_bit_CubeParts,
    .initScript = &TTYD64_imp_20_CrystalKing_Script_Init_802206BC_20,
    .statusTable = b_area_pra2_crystal_bit_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 18, 15 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_20_CrystalKing_CrystalBitB_20 = {
    .flags = 0x200200,
    .maxHP = 1,
    .type = 0xBF,
    .level = 0,
    .partCount = 2,
    .partsData = b_area_pra2_crystal_bit_SphereParts,
    .initScript = &TTYD64_imp_20_CrystalKing_Script_Init_802206BC_20,
    .statusTable = b_area_pra2_crystal_bit_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 18, 15 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

Battle TTYD64_pra2_FormationTable[] = {
    { .name = "\321\351\354\351\374",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pra2_Formation_00,
      .stage = &b_area_pra2_sam_04,
      .onBattleStart = NULL },
    {},
};

ActorBlueprint TTYD64_imp_20_CrystalKing_CrystalBitC_20 = {
    .flags = 0x200200,
    .maxHP = 1,
    .type = 0xBF,
    .level = 0,
    .partCount = 2,
    .partsData = b_area_pra2_crystal_bit_PrismParts,
    .initScript = &TTYD64_imp_20_CrystalKing_Script_Init_802206BC_20,
    .statusTable = b_area_pra2_crystal_bit_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 18, 15 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_20_CrystalKing_20_CrystalKing = {
    .flags = 0x0,
    .maxHP = 70,
    .type = 0xBD,
    .level = 85,
    .partCount = 1,
    .partsData = b_area_pra2_crystal_king_ActorParts,
    .initScript = &TTYD64_imp_20_CrystalKing_Script_Init_80218B40_20,
    .statusTable = b_area_pra2_crystal_king_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 70,
    .coinReward = 0,
    .size = { 56, 56 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 40 },
    .statusTextOffset = { 15, 40 },
};

FormationRow TTYD64_imp_20_CrystalKing_SpecialFormation_8021D5E8_20[] = {
    { .actor = &TTYD64_imp_20_CrystalKing_CrystalBitA_20,
      .home = { .vec = &b_area_pra2_crystal_king_CloneSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_20_CrystalKing_SpecialFormation_8021D620_20[] = {
    { .actor = &TTYD64_imp_20_CrystalKing_CrystalBitC_20,
      .home = { .vec = &b_area_pra2_crystal_king_CloneSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_20_CrystalKing_SpecialFormation_8021D604_20[] = {
    { .actor = &TTYD64_imp_20_CrystalKing_CrystalBitB_20,
      .home = { .vec = &b_area_pra2_crystal_king_CloneSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

void TTYD64_InstallBattles_pra2(void) {
    Mod_SetBattleList("TTYD64", 0x20, TTYD64_pra2_FormationTable);
}
