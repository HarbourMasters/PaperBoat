#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_drop_tables.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/battles_a/battles_a.h"

API_CALLABLE(ActorSpeak);
API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddActorVar);
API_CALLABLE(AddBattleCamDist);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(CopyBuffs);
API_CALLABLE(CopyStatusEffects);
API_CALLABLE(EnableActorBlur);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnablePlayerBlur);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyToGoal);
API_CALLABLE(ForceHomePos);
API_CALLABLE(FreezeBattleState);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetEnemyMaxHP);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetIndexFromPos);
API_CALLABLE(GetLastDamage);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPlayerHP);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HideHealthBar);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(JumpWithBounce);
API_CALLABLE(LandJump);
API_CALLABLE(MakeLerp);
API_CALLABLE(ModifyActorDecoration);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerHopToGoal);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActor);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(ResetActorSounds);
API_CALLABLE(ResetAllActorSounds);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPaletteEffect);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetAnimationRate);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLookTarget);
API_CALLABLE(SetCamNoDraw);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamViewport);
API_CALLABLE(SetDamageSource);
API_CALLABLE(SetDefenseTable);
API_CALLABLE(SetEnemyHP);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetInterpCamParams);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(SetPartAlpha);
API_CALLABLE(SetPartDispOffset);
API_CALLABLE(SetPartEventBits);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetPartYaw);
API_CALLABLE(SetProjectileTargetOffset);
API_CALLABLE(SetTargetActor);
API_CALLABLE(SetTargetOffset);
API_CALLABLE(ShakeCam);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseBattleCamPresetImmediately);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
API_CALLABLE(b_area_mac_bombette_lee_UnkActorPosFunc);
API_CALLABLE(b_area_mac_chan_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_mac_goombario_lee_ActorJumpToPos);
API_CALLABLE(b_area_mac_goombario_lee_CalculateTattleCamBoomLength);
API_CALLABLE(b_area_mac_goombario_lee_CloseTattleWindow);
API_CALLABLE(b_area_mac_goombario_lee_OpenTattleWindow);
API_CALLABLE(b_area_mac_goombario_lee_UnkFunc62);
API_CALLABLE(b_area_mac_kooper_lee_UnkActorPosFunc);
API_CALLABLE(b_area_mac_lee_GetPartnerAndLevel);
API_CALLABLE(b_area_mac_lee_InitPartnerCopyHistory);
API_CALLABLE(b_area_mac_lee_RegisterPartnerToCopy);
API_CALLABLE(b_area_mac_watt_lee_SetBackgroundAlpha);
API_CALLABLE(b_area_mac_watt_lee_UnkBackgroundFunc3);
API_CALLABLE(b_area_mac_watt_lee_WattFXRemove);
API_CALLABLE(b_area_mac_watt_lee_WattFXSetActive);
API_CALLABLE(b_area_mac_watt_lee_WattFXSetBouncing);
API_CALLABLE(b_area_mac_watt_lee_WattFXSetEffect);
extern EvtScript b_area_mac_EVS_Lee_RemoveParentActor;
extern Vec3i b_area_mac_Lee_SummonPos;
extern EvtScript b_area_mac_chan_EVS_CheckToppleAnim;
extern EvtScript b_area_mac_chan_EVS_Idle;
extern u8 b_area_mac_chan_FlipPosOffsets[];
extern s32 b_area_mac_chan_StatusTable[];
extern s32 b_area_mac_chan_ToppledDefenseTable[];
extern s32 b_area_mac_chan_UprightDefenseTable[];
extern EvtScript b_area_mac_goombario_lee_EVS_CalculateJumpTime;
extern EvtScript b_area_mac_goombario_lee_EVS_HeadbonkFollowthrough;
extern EvtScript b_area_mac_kooper_lee_EVS_Idle;
extern u8 b_area_mac_kooper_lee_FlipPosOffsets[];
extern s32 b_area_mac_kooper_lee_ToppledDefenseTable[];
extern s32 b_area_mac_lakilester_lee_DefenseTable[];
extern EvtScript b_area_mac_lakilester_lee_EVS_HandleEvent;
extern s32 b_area_mac_lakilester_lee_SpinyAnims[];
extern s32 b_area_mac_lakilester_lee_StatusTable[];
extern EvtScript b_area_mac_lee_EVS_HandleEvent;
extern EvtScript b_area_mac_lee_EVS_ReturnHome;
extern s32 b_area_mac_lee_FlailingAnims[];
extern s32 b_area_mac_lee_StatusTable[];
extern Stage b_area_mac_mac_02;
extern s32 b_area_mac_master1_StatusTable[];
extern s32 b_area_mac_master2_DefenseTable[];
extern s32 b_area_mac_master2_StatusTable[];
extern s32 b_area_mac_master3_DefenseTable[];
extern EvtScript b_area_mac_master3_EVS_AscendToFinalForm;
extern EvtScript b_area_mac_master3_EVS_Idle;
extern s32 b_area_mac_master3_StatusTable[];
extern s32 b_area_mac_watt_lee_DefenseTable[];
extern EvtScript b_area_mac_watt_lee_EVS_HandleEvent;
extern EvtScript b_area_mac_watt_lee_EVS_Idle;
extern EvtScript TTYD64_mac_sushie_lee_EVS_TakeTurn;
extern EvtScript TTYD64_mac_kooper_lee_EVS_TakeTurn;
extern EvtScript TTYD64_mac_master3_EVS_Attack_StrikeThrice;
extern EvtScript TTYD64_mac_chan_EVS_HandleEvent_Ground;
extern EvtScript TTYD64_mac_bow_lee_EVS_TakeTurn;
extern EvtScript TTYD64_mac_lakilester_lee_EVS_TakeTurn;
extern EvtScript TTYD64_mac_chan_EVS_TakeTurn_Ceiling;
extern EvtScript TTYD64_mac_goombario_lee_EVS_Attack_Headbonk;
extern EvtScript TTYD64_mac_chan_EVS_TakeTurn_Ground;
extern EvtScript TTYD64_mac_master3_EVS_Attack_StrikeTwice;
extern EvtScript TTYD64_mac_master3_EVS_Attack_StrikeTwice_8021FF4C;
extern EvtScript TTYD64_mac_kooper_lee_EVS_HandleEvent;
extern EvtScript TTYD64_mac_watt_lee_EVS_TakeTurn;
extern EvtScript TTYD64_mac_bombette_lee_EVS_TakeTurn;
extern EvtScript TTYD64_mac_lee_EVS_Move_CopyPartner;
extern EvtScript TTYD64_mac_parakarry_lee_EVS_Attack_SkyDive;
extern EvtScript TTYD64_mac_master3_EVS_Attack_StrikeOnce;
extern EvtScript TTYD64_mac_master3_EVS_HandlePhase;
extern EvtScript TTYD64_mac_master3_EVS_HandleEvent_Inner;
extern EvtScript TTYD64_mac_bow_lee_EVS_HandleEvent;
extern EvtScript TTYD64_mac_master3_EVS_Attack_StrikeOnce_80225E68;
extern EvtScript TTYD64_mac_master2_EVS_HandlePhase;
extern EvtScript TTYD64_mac_master1_EVS_TakeTurn;
extern EvtScript TTYD64_mac_parakarry_lee_EVS_HandleEvent;
extern EvtScript TTYD64_mac_lee_EVS_Attack_FlyingTackle;
extern EvtScript TTYD64_mac_master2_EVS_HandleEvent_Inner;
extern EvtScript TTYD64_mac_master2_EVS_HandleEvent_Inner_802282E8;
extern EvtScript TTYD64_mac_sushie_lee_EVS_HandleEvent;
extern EvtScript TTYD64_mac_sushie_lee_EVS_HandleEvent_80228E00;
extern EvtScript TTYD64_mac_bombette_lee_EVS_HandleEvent;
extern EvtScript TTYD64_mac_EVS_Lee_LoseDisguise;
extern EvtScript TTYD64_mac_chan_EVS_HandleEvent_Ceiling;
extern EvtScript TTYD64_mac_chan_EVS_FallFromCeiling;
extern EvtScript TTYD64_mac_chan_EVS_HandlePhase;
extern EvtScript TTYD64_mac_master3_EVS_Attack_SpiritStrike;
extern EvtScript TTYD64_mac_master3_EVS_HandleEvent;
extern EvtScript TTYD64_mac_master3_EVS_HandleEvent_8022D0D0;
extern EvtScript TTYD64_mac_master3_EVS_HandleEvent_8022D438;
extern EvtScript TTYD64_mac_EVS_Lee_ShockKnockback;
extern EvtScript TTYD64_mac_EVS_8022DE60;
extern EvtScript TTYD64_mac_goombario_lee_EVS_Move_Tattle;
extern EvtScript TTYD64_mac_master1_EVS_HandlePhase;
extern EvtScript TTYD64_mac_chan_EVS_HandleEvent_Initial;
extern EvtScript TTYD64_mac_lee_EVS_HandlePhase;
extern EvtScript TTYD64_mac_master3_EVS_TakeTurn;
extern EvtScript TTYD64_mac_master3_EVS_Attack_FlyingGrab;
extern EvtScript TTYD64_mac_chan_EVS_SetInitialState;
extern EvtScript TTYD64_mac_goombario_lee_EVS_ApproachPlayer;
extern EvtScript TTYD64_mac_lee_EVS_Init;
extern EvtScript TTYD64_mac_master1_EVS_Init;
extern EvtScript TTYD64_mac_watt_lee_EVS_HandlePhase;
extern EvtScript TTYD64_mac_lakilester_lee_EVS_HandlePhase;
extern EvtScript TTYD64_mac_lakilester_lee_EVS_HandlePhase_8022FF9C;
extern EvtScript TTYD64_mac_lakilester_lee_EVS_HandlePhase_80230070;
extern EvtScript TTYD64_mac_master3_EVS_Init;
extern EvtScript TTYD64_mac_master3_EVS_Init_80230218;
extern EvtScript TTYD64_mac_lakilester_lee_EVS_HandlePhase_802302EC;
extern EvtScript TTYD64_mac_lakilester_lee_EVS_HandlePhase_802303C0;
extern EvtScript TTYD64_mac_lakilester_lee_EVS_HandlePhase_80230494;
extern EvtScript TTYD64_mac_lakilester_lee_EVS_HandlePhase_80230568;
extern EvtScript TTYD64_mac_master2_EVS_TakeTurn;
extern EvtScript TTYD64_mac_kooper_lee_EVS_Init;
extern EvtScript TTYD64_mac_chan_EVS_Init;
extern EvtScript TTYD64_mac_lee_EVS_TakeTurn;
extern EvtScript TTYD64_mac_lakilester_lee_EVS_Init;
extern EvtScript TTYD64_mac_lakilester_lee_EVS_Init_8023151C;
extern EvtScript TTYD64_mac_lakilester_lee_EVS_Init_80231594;
extern EvtScript TTYD64_mac_lakilester_lee_EVS_Init_8023160C;
extern EvtScript TTYD64_mac_lakilester_lee_EVS_Init_80231684;
extern EvtScript TTYD64_mac_lakilester_lee_EVS_Init_802316FC;
extern EvtScript TTYD64_mac_lakilester_lee_EVS_Init_80231774;
extern EvtScript TTYD64_mac_goombario_lee_EVS_TakeTurn;
extern ActorBlueprint TTYD64_mac_watt_lee;
extern ActorBlueprint TTYD64_mac_bow_lee;
extern ActorBlueprint TTYD64_mac_master2;
extern ActorBlueprint TTYD64_mac_master1;
extern ActorBlueprint TTYD64_mac_master3;
extern ActorBlueprint TTYD64_mac_kooper_lee;
extern ActorBlueprint TTYD64_mac_sushie_lee;
extern ActorBlueprint TTYD64_mac_chan;
extern ActorBlueprint TTYD64_mac_lakilester_lee;
extern ActorBlueprint TTYD64_mac_bombette_lee;
extern ActorBlueprint TTYD64_mac_goombario_lee;
extern ActorBlueprint TTYD64_mac_lee;
extern ActorBlueprint TTYD64_mac_parakarry_lee;
extern EvtScript TTYD64_mac_parakarry_lee_EVS_TakeTurn;
extern Battle TTYD64_mac_Formations[];
extern s32 TTYD64_mac_chan_UprightAnims[];
extern s32 TTYD64_mac_goombario_lee_DefaultAnims[];
extern s32 TTYD64_mac_bombette_lee_DefaultAnims[];
extern s32 TTYD64_mac_lee_DefaultAnims[];
extern s32 TTYD64_mac_lakilester_lee_DefaultAnims[];
extern s32 TTYD64_mac_watt_lee_DefaultAnims[];
extern s32 TTYD64_mac_kooper_lee_ToppledAnims[];
extern s32 TTYD64_mac_master3_AscendedAnims[];
extern s32 TTYD64_mac_kooper_lee_DefaultAnims[];
extern s32 TTYD64_mac_sushie_lee_DefaultAnims[];
extern s32 TTYD64_mac_master3_AscendedAnims_80231DD0[];
extern s32 TTYD64_mac_chan_DefaultAnims[];
extern s32 TTYD64_mac_bow_lee_DefaultAnims[];
extern s32 TTYD64_mac_master3_BaseAnims[];
extern s32 TTYD64_mac_master3_BaseAnims_80232030[];
extern s32 TTYD64_mac_master3_BaseAnims_8023207C[];
extern s32 TTYD64_mac_parakarry_lee_DefaultAnims[];
extern ActorPartBlueprint TTYD64_mac_watt_lee_ActorParts[];
extern ActorPartBlueprint TTYD64_mac_bow_lee_ActorParts[];
extern ActorPartBlueprint TTYD64_mac_master3_ActorParts[];
extern ActorPartBlueprint TTYD64_mac_lakilester_lee_ActorParts[];
extern ActorPartBlueprint TTYD64_mac_parakarry_lee_ActorParts[];
extern s32 TTYD64_mac_chan_ToppledAnims[];
extern ActorPartBlueprint TTYD64_mac_master3_ActorParts_802326A8[];
extern ActorPartBlueprint TTYD64_mac_lee_ActorParts[];
extern ActorPartBlueprint TTYD64_mac_sushie_lee_ActorParts[];
extern ActorPartBlueprint TTYD64_mac_bombette_lee_ActorParts[];
extern ActorPartBlueprint TTYD64_mac_kooper_lee_ActorParts[];
extern ActorPartBlueprint TTYD64_mac_chan_ActorParts[];
extern ActorPartBlueprint TTYD64_mac_master3_ActorParts_802327A4[];
extern ActorPartBlueprint TTYD64_mac_goombario_lee_ActorParts[];
extern FormationRow TTYD64_mac_LeeGoombarioFormation[];
extern FormationRow TTYD64_mac_Formation_00[];
extern FormationRow TTYD64_mac_Formation_01[];
extern FormationRow TTYD64_mac_Formation_04[];
extern FormationRow TTYD64_mac_Formation_02[];
extern FormationRow TTYD64_mac_Formation_03[];
extern FormationRow TTYD64_mac_LeeBowFormation[];
extern FormationRow TTYD64_mac_LeeSushieFormation[];
extern FormationRow TTYD64_mac_LeeLakilesterFormation[];
extern FormationRow TTYD64_mac_LeeBombetteFormation[];
extern FormationRow TTYD64_mac_LeeParakarryFormation[];
extern FormationRow TTYD64_mac_LeeKooperFormation[];
extern FormationRow TTYD64_mac_LeeWattFormation[];

static API_CALLABLE(TTYD64_mac_lee_AdjustFormationPriority) {
    Bytecode* args = script->ptrReadPos;
    s32 partnerID = evt_get_variable(script, *args++);
    Actor* actor = get_actor(script->owner1.enemyID);
    FormationRow* formation = nullptr;

    switch (partnerID) {
        case PARTNER_GOOMBARIO:
            formation = TTYD64_mac_LeeGoombarioFormation;
            break;
        case PARTNER_KOOPER:
            formation = TTYD64_mac_LeeKooperFormation;
            break;
        case PARTNER_BOMBETTE:
            formation = TTYD64_mac_LeeBombetteFormation;
            break;
        case PARTNER_PARAKARRY:
            formation = TTYD64_mac_LeeParakarryFormation;
            break;
        case PARTNER_BOW:
            formation = TTYD64_mac_LeeBowFormation;
            break;
        case PARTNER_WATT:
            formation = TTYD64_mac_LeeWattFormation;
            break;
        case PARTNER_SUSHIE:
            formation = TTYD64_mac_LeeSushieFormation;
            break;
        case PARTNER_LAKILESTER:
            formation = TTYD64_mac_LeeLakilesterFormation;
            break;
    }
    formation->priority = actor->turnPriority + 10;
    return ApiStatus_DONE2;
}

// clang-format off
EvtScript TTYD64_mac_sushie_lee_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 70, 0, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, LVar0)
    Div(LVar3, Float(3.0))
    Set(LVarA, LVar3)
    IfLt(LVarA, 0)
        Mul(LVarA, -1)
    EndIf
    Call(MoveBattleCamOver, LVarA)
    Call(SetAnimation, ACTOR_SELF, 1, 0xF0003)
    Call(RunToGoal, ACTOR_SELF, LVarA, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xF0001)
    Wait(10)
    Call(UseBattleCamPreset, 8)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(AddBattleCamDist, -50)
    Call(MoveBattleCamOver, 30)
    Call(SetBattleCamTargetingModes, 1, 1, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0xF0004)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0xF0008)
    Wait(15)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(SetAnimation, ACTOR_SELF, 1, 0xF0005)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
                Set(LVar0, 0)
                Loop(10)
                    Add(LVar0, 36)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 20)
            EndThread
            Thread
                Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                Switch(LVar0)
                    CaseEq(0)
                        Wait(13)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
                    CaseEq(1)
                        Wait(13)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0498046875), Float(1.0498046875), Float(1.0498046875))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.099609375), Float(1.099609375), Float(1.099609375))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.150390625), Float(1.150390625), Float(1.150390625))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.2001953125), Float(1.2001953125), Float(1.2001953125))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.25), Float(1.25), Float(1.25))
                    CaseEq(2)
                        Wait(13)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.099609375), Float(1.099609375), Float(1.099609375))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.2001953125), Float(1.2001953125), Float(1.2001953125))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.2998046875), Float(1.2998046875), Float(1.2998046875))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.400390625), Float(1.400390625), Float(1.400390625))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.5), Float(1.5), Float(1.5))
                EndSwitch
            EndThread
            Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8244)
            Call(SetGoalToTarget, ACTOR_SELF)
            Thread
                Call(SetAnimation, ACTOR_SELF, 1, 0xF0005)
                Wait(10)
                Call(SetAnimation, ACTOR_SELF, 1, 0xF0006)
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xF0007)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
            Call(LandJump, ACTOR_SELF)
            Call(PlaySoundAtActor, ACTOR_SELF, 666)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(AddGoalPos, ACTOR_SELF, -15, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 666)
            Call(AddGoalPos, ACTOR_SELF, -10, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 666)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0xF0003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Call(SetAnimation, ACTOR_SELF, 1, 0xF0005)
    Thread
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
        Set(LVar0, 0)
        Loop(10)
            Add(LVar0, 36)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 20)
    EndThread
    Thread
        Call(GetActorVar, ACTOR_SELF, 1, LVar0)
        Switch(LVar0)
            CaseEq(0)
                Wait(13)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.099609375), Float(1.099609375), Float(1.099609375))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.099609375), Float(1.099609375), Float(1.099609375))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.2001953125), Float(1.2001953125), Float(1.2001953125))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.2001953125), Float(1.2001953125), Float(1.2001953125))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.2998046875), Float(1.2998046875), Float(1.2998046875))
            CaseEq(1)
                Wait(13)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.150390625), Float(1.150390625), Float(1.150390625))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.2001953125), Float(1.2001953125), Float(1.2001953125))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.349609375), Float(1.349609375), Float(1.349609375))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.400390625), Float(1.400390625), Float(1.400390625))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.5498046875), Float(1.5498046875), Float(1.5498046875))
            CaseEq(2)
                Wait(13)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.2001953125), Float(1.2001953125), Float(1.2001953125))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.2998046875), Float(1.2998046875), Float(1.2998046875))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.5), Float(1.5), Float(1.5))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.599609375), Float(1.599609375), Float(1.599609375))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.7998046875), Float(1.7998046875), Float(1.7998046875))
        EndSwitch
    EndThread
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8244)
    Call(SetGoalToTarget, ACTOR_SELF)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0xF0005)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, 1, 0xF0006)
    EndThread
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xF0007)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
    Thread
        Wait(3)
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
    EndThread
    Call(GetActorVar, ACTOR_SELF, 1, LVarA)
    Switch(LVarA)
        CaseEq(0)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 3, 32)
        CaseEq(1)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 4, 32)
        CaseEq(2)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 5, 32)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0xF0006)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 60)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 666)
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 666)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 666)
            Add(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 666)
            Call(SetAnimation, ACTOR_SELF, 1, 0xF0001)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0xF0003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_kooper_lee_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 4, LVar0)
    IfEq(LVar0, 1)
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        Sub(LVar0, 1)
        IfGt(LVar0, 0)
            Call(SetActorVar, ACTOR_SELF, 5, LVar0)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
            Wait(30)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
        Else
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
            Wait(20)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA0019)
            Set(LVar0, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            Thread
                Loop(5)
                    Add(LVar0, 15)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA0004)
            Call(SetActorVar, ACTOR_SELF, 4, 0)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_mac_master3_DefenseTable))
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_mac_kooper_lee_DefaultAnims))
            Call(SetTargetOffset, ACTOR_SELF, 1, -2, 38)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -3, -9)
        EndIf
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Return
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0xA000E)
    Call(PlaySoundAtActor, ACTOR_SELF, 0)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA000A)
    Call(PlaySoundAtActor, ACTOR_SELF, 8204)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 75)
    Call(SetBattleCamTargetingModes, 1, 1, 1)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Set(LVar0, 10)
        CaseEq(1)
            Set(LVar0, 20)
        CaseEq(2)
            Set(LVar0, 30)
    EndSwitch
    Set(LVar9, 0)
    Loop(LVar0)
        Add(LVar9, 1)
        Switch(LVar9)
            CaseLt(20)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA000A)
                Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
            CaseEq(20)
                Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseLt(40)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA000B)
                Call(SetActorSpeed, ACTOR_SELF, Float(12.0))
            CaseEq(40)
                Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseLt(50)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA000C)
                Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
            CaseEq(50)
                Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseLt(60)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA000D)
                Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            CaseEq(60)
                Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        EndSwitch
        Wait(1)
    EndLoop
    Call(PlaySoundAtActor, ACTOR_SELF, 8202)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 15)
    Call(AddActorDecoration, ACTOR_SELF, 0, 0, 5)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Call(b_area_mac_kooper_lee_UnkActorPosFunc)
                Call(RemoveActorDecoration, ACTOR_SELF, 0, 0)
            EndThread
            Wait(4)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA0009)
            Call(SetActorRotationOffset, ACTOR_SELF, -8, 0, 0)
            Set(LVar0, 0)
            Loop(2)
                Add(LVar0, 30)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                Wait(1)
            EndLoop
            Wait(5)
            Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
            Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 16, 4, 0, 10, 0, 0, 0, 0, 0)
            Loop(5)
                Add(LVar0, -12)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                Wait(1)
            EndLoop
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 2)
            Wait(2)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, -2)
            Wait(2)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA000F)
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA0006)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.5))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(RemoveActorDecoration, ACTOR_SELF, 0, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 2, 32)
        CaseEq(1)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 3, 32)
        CaseEq(2)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 5, 32)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 8)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 60)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Add(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA000F)
            Wait(15)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA0006)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.5))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master3_EVS_Attack_StrikeThrice = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 8)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamDist, 200)
    Call(SetBattleCamOffsetY, 13)
    Call(MoveBattleCamOver, 60)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20015)
    Wait(20)
    Call(ActorSpeak, 0x2003C, ACTOR_SELF, 1, 0xA2000A, 0xA20006)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 7)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 1)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 953)
    Call(PlaySoundAtActor, ACTOR_SELF, 8379)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 0, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(UseBattleCamPreset, 2)
            Call(EnableActorBlur, ACTOR_SELF, 1)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -50, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20013)
            Call(RunToGoal, ACTOR_SELF, 10, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
            Call(EnableActorBlur, ACTOR_SELF, 0)
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
            Return
        EndCaseGroup
    EndSwitch
    Call(EnableActorBlur, ACTOR_SELF, 1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20013)
    Call(RunToGoal, ACTOR_SELF, 5, 0)
    Call(EnableActorBlur, ACTOR_SELF, 0)
    Thread
        Call(ShakeCam, 1, 0, 2, Float(1.0))
        Call(ShakeCam, 1, 0, 2, Float(4.0))
        Call(ShakeCam, 1, 0, 2, Float(3.0))
        Call(ShakeCam, 1, 0, 2, Float(2.0))
        Call(ShakeCam, 1, 0, 2, Float(1.0))
        Call(ShakeCam, 1, 0, 2, Float(0.5))
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 1005)
    Call(PlaySoundAtActor, ACTOR_SELF, 8379)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0xA0000, 0xFFFF, 0, 5, 16)
    Wait(15)
    Call(UseBattleCamPreset, 2)
    Thread
        Call(EnableActorBlur, ACTOR_SELF, 1)
        Wait(5)
        Call(PlaySoundAtActor, ACTOR_SELF, 8321)
        Call(SetAnimation, ACTOR_SELF, 1, 0xA20014)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
        Call(JumpToGoal, ACTOR_SELF, 25, 0, 1, 0)
        Call(EnableActorBlur, ACTOR_SELF, 0)
    EndThread
    Thread
        Call(ShakeCam, 1, 0, 2, Float(0.5))
        Call(ShakeCam, 1, 0, 2, Float(1.5))
        Call(ShakeCam, 1, 0, 2, Float(0.5))
        Call(ShakeCam, 1, 0, 2, Float(0.2001953125))
    EndThread
    Wait(2)
    Call(PlaySoundAtActor, ACTOR_SELF, 1005)
    Call(PlaySoundAtActor, ACTOR_SELF, 8379)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0xA0000, 0xFFFF, 0, 6, 0)
    Thread
        Wait(5)
        Call(GetOwnerTarget, LVar3, 0)
        IfEq(LVar3, 0)
            Call(EnablePlayerBlur, 1)
        Else
            Call(EnableActorBlur, 256, 1)
        EndIf
        Call(SetActorJumpGravity, LVar3, Float(0.2998046875))
        Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
        Call(SetJumpAnimations, LVar3, 0, 0x10017, 0x10017, 0x10017)
        Call(SetGoalPos, LVar3, LVar0, LVar1, LVar2)
        IfEq(LVar3, 0)
            Call(PlayerHopToGoal, 50, 0, 0)
            Call(EnablePlayerBlur, 0)
        Else
            Set(LVar0, 9)
            Exec(TTYD64_SetPartnerAnimation_Battle)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 50, 0, 0, 1)
            Set(LVar0, 0)
            Exec(TTYD64_SetPartnerAnimation_Battle)
            Call(EnableActorBlur, 256, 0)
        EndIf
    EndThread
    Wait(15)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20021)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 30, 0, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8378)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20023)
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
    Wait(3)
    Add(LVar0, 20)
    Set(LVar1, 0)
    Thread
        Wait(5)
        Call(PlaySoundAtActor, ACTOR_SELF, 8381)
        Wait(10)
        Call(PlaySoundAtActor, ACTOR_SELF, 8381)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0xA2000E)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 948)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA2000F)
    Call(EnableActorBlur, ACTOR_SELF, 1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 0, 0, 0)
    Call(RunToGoal, ACTOR_SELF, 3, 0)
    Call(EnableActorBlur, ACTOR_SELF, 0)
    Thread
        Call(ShakeCam, 1, 0, 2, Float(1.0))
        Call(ShakeCam, 1, 0, 2, Float(3.0))
        Call(ShakeCam, 1, 0, 2, Float(6.0))
        Call(ShakeCam, 1, 0, 2, Float(5.0))
        Call(ShakeCam, 1, 0, 2, Float(4.0))
        Call(ShakeCam, 1, 0, 2, Float(3.0))
        Call(ShakeCam, 1, 0, 2, Float(2.0))
        Call(ShakeCam, 1, 0, 2, Float(1.0))
        Call(ShakeCam, 1, 0, 2, Float(0.5))
        Call(ShakeCam, 1, 0, 2, Float(0.2001953125))
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 1006)
    Call(PlaySoundAtActor, ACTOR_SELF, 8379)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0xA0000, 0xFFFF, 0, 7, 32)
    Wait(15)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(PlaySoundAtActor, ACTOR_SELF, 8382)
            Call(PlaySoundAtActor, ACTOR_SELF, 8379)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
                Set(LVar0, 0)
                Loop(10)
                    Add(LVar0, 36)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 50)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20021)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 30, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8378)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20023)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Wait(3)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20021)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 948)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20023)
            Wait(20)
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_chan_EVS_HandleEvent_Ground = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            SetConst(LVar2, 0xA30007)
            ExecWait(b_area_mac_chan_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfNe(LVar0, 2)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30006)
                SetConst(LVar2, 0xA30006)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30014)
                SetConst(LVar2, 0xA30015)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            EndIf
        CaseEq(36)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfNe(LVar0, 2)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30006)
                SetConst(LVar2, 0xA30006)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30006)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30014)
                SetConst(LVar2, 0xA30015)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30015)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            SetConst(LVar2, 0xA30007)
            ExecWait(b_area_mac_chan_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 8, 2)
            Call(SetTargetOffset, ACTOR_SELF, 1, 0, 16)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
            Call(SetActorVar, ACTOR_SELF, 9, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_mac_chan_ToppledDefenseTable))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_mac_chan_ToppledAnims))
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA30006)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            Thread
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -45)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -90)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -135)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -180)
                Wait(1)
            EndThread
            UseBuf(Ref(b_area_mac_chan_FlipPosOffsets))
            Loop(19)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA30007)
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA3000C)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(SetAnimation, ACTOR_SELF, 1, 0xA3000D)
                Wait(8)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30002)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(25)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA3000C)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(SetAnimation, ACTOR_SELF, 1, 0xA3000D)
                Wait(8)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30002)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(27)
            Wait(10)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                Add(LVar1, 9)
            Else
                Add(LVar1, 24)
            EndIf
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(20)
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            SetConst(LVar2, 0xA30007)
            ExecWait(b_area_mac_chan_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            SetConst(LVar2, 0xA30007)
            ExecWait(b_area_mac_chan_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            SetConst(LVar2, 0xA30007)
            ExecWait(b_area_mac_chan_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            SetConst(LVar2, 0xA30007)
            ExecWait(b_area_mac_chan_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30001)
                ExecWait(Ref(EVS_Enemy_Recover))
            EndIf
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30004)
                SetConst(LVar2, 0xA30006)
                ExecWait(Ref(EVS_Enemy_ScareAway))
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30002)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30004)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30002)
            EndIf
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30006)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30007)
            EndIf
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA3000C)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(SetAnimation, ACTOR_SELF, 1, 0xA3000D)
                Wait(8)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA30002)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_bow_lee_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Wait(10)
    Thread
        Set(LVar0, 200)
        Loop(20)
            Sub(LVar0, 10)
            Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Wait(10)
    Call(UseBattleCamPreset, 1)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0xD0003)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Call(AddGoalPos, ACTOR_SELF, 4, -4, 0)
        Else
            Call(AddGoalPos, ACTOR_SELF, 10, -10, 0)
        EndIf
        Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
        Call(SetAnimation, ACTOR_SELF, 1, 0xD0001)
    EndThread
    Wait(15)
    Call(UseBattleCamPreset, 15)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Set(LVar0, 55)
    Loop(20)
        Add(LVar0, 10)
        Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_SELF, 1, 255)
    Call(SetAnimation, ACTOR_SELF, 1, 0xD0005)
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(15)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(UseBattleCamPreset, 2)
            Call(SetPartScale, ACTOR_SELF, 1, Float(1.400390625), Float(1.400390625), Float(1.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0007)
            Wait(2)
            Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
            Set(LVar0, 0)
            Loop(20)
                Add(LVar0, -45)
                Call(SetActorYaw, ACTOR_SELF, LVar0)
                Wait(1)
            EndLoop
            Call(SetActorYaw, ACTOR_SELF, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0xD001A)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 3)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0001)
            Wait(10)
            Call(YieldTurn)
            Thread
                Set(LVar0, 200)
                Loop(20)
                    Sub(LVar0, 10)
                    Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 60)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0003)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0001)
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
    Set(LVarA, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar8)
    Switch(LVar8)
        CaseEq(0)
            Set(LVar8, 4)
        CaseEq(1)
            Set(LVar8, 5)
        CaseEq(2)
            Set(LVar8, 6)
    EndSwitch
    Set(LVar7, LVar8)
    Loop(LVar7)
        Call(PlaySoundAtActor, ACTOR_SELF, 8217)
        Add(LVarA, 1)
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.400390625), Float(1.400390625), Float(1.0))
        IfEq(LFlag0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0007)
            Set(LFlag0, 1)
            IfEq(LVarA, LVar8)
                Call(SetDamageSource, 12)
            Else
                Call(SetDamageSource, 10)
            EndIf
        Else
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0008)
            Set(LFlag0, 0)
            IfEq(LVarA, LVar8)
                Call(SetDamageSource, 13)
            Else
                Call(SetDamageSource, 11)
            EndIf
        EndIf
        Wait(2)
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
        Thread
            Call(ShakeCam, 1, 0, 2, Float(0.5))
            Call(ShakeCam, 1, 0, 2, Float(1.5))
            Call(ShakeCam, 1, 0, 1, Float(0.5))
            Call(ShakeCam, 1, 0, 1, Float(0.2001953125))
        EndThread
        Call(GetActorVar, ACTOR_SELF, 1, LVar9)
        Switch(LVar9)
            CaseEq(0)
                Wait(2)
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8192, 0, 0, 1, 16)
            CaseEq(1)
                Wait(2)
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8192, 0, 0, 1, 16)
            CaseEq(2)
                Wait(2)
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8192, 0, 0, 1, 16)
        EndSwitch
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 1, 0xD0001)
        Call(GetOwnerTarget, LVar2, 0)
        IfEq(LVar2, 0)
            Call(GetActorHP, LVar2, LVar1)
        Else
            Call(TTYD64_GetPartnerHP_API, LVar1)
        EndIf
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(10)
            Call(YieldTurn)
            Thread
                Set(LVar0, 200)
                Loop(20)
                    Sub(LVar0, 10)
                    Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 30)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0003)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0001)
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
EvtScript TTYD64_mac_lakilester_lee_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x100003)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, 20, 30, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x100001)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, -1)
        Add(LVar1, 4)
        Add(LVar2, 2)
        Call(SetPartScale, ACTOR_SELF, 3, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Else
        Add(LVar0, -3)
        Add(LVar1, 10)
        Add(LVar2, 5)
        Call(SetPartScale, ACTOR_SELF, 3, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Wait(1)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 3, 0x100014)
    Call(SetAnimation, ACTOR_SELF, 1, 0x10000F)
    Loop(4)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            AddF(LVar1, Float(2.400390625))
        Else
            Add(LVar1, 6)
        EndIf
        Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, -3)
        Add(LVar1, 16)
        Add(LVar2, 2)
        SetF(LVar3, Float(0.400390625))
    Else
        Add(LVar0, -8)
        Add(LVar1, 40)
        Add(LVar2, 5)
        SetF(LVar3, Float(1.0))
    EndIf
    Call(PlayEffect_impl, 107, 0, LVar0, LVar1, LVar2, LVar3, 30, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 709)
    Thread
        Loop(15)
            Call(SetActorDispOffset, ACTOR_SELF, 1, 0, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 3, 1, 0, 0)
            Wait(1)
            Call(SetActorDispOffset, ACTOR_SELF, -1, 0, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 3, -1, 0, 0)
            Wait(1)
        EndLoop
        Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
        Call(SetPartDispOffset, ACTOR_SELF, 3, 0, 0, 0)
    EndThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x100010)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x100011)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x100012)
    Wait(3)
    Call(SetPartSounds, ACTOR_SELF, 3, 2, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8219)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 3, 0x100015)
            Call(SetPartJumpGravity, ACTOR_SELF, 3, Float(1.5))
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(RandInt, 100, LVar3)
            Sub(LVar3, 50)
            Add(LVar0, LVar3)
            Call(JumpPartTo, ACTOR_SELF, 3, LVar0, 0, LVar2, 20, 1)
            Thread
                Add(LVar0, -50)
                Call(JumpPartTo, ACTOR_SELF, 3, LVar0, 0, LVar2, 15, 1)
                Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
            EndThread
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 60)
            Call(SetAnimation, ACTOR_SELF, 1, 0x100003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 3, 0x100015)
    Call(SetPartJumpGravity, ACTOR_SELF, 3, Float(1.5))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 20, 1)
    Thread
        Add(LVar0, -50)
        Call(JumpPartTo, ACTOR_SELF, 3, LVar0, 0, LVar2, 15, 1)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    EndThread
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
        CaseEq(1)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 4, 32)
        CaseEq(2)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 5, 32)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(15)
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 8)
            Call(SetAnimation, ACTOR_SELF, 1, 0x100003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_chan_EVS_TakeTurn_Ceiling = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 16)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
    Call(b_area_mac_chan_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_chan_EVS_TakeTurn_Ground))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mac_chan_EVS_HandleEvent_Ground))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_mac_chan_UprightAnims))
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
    Call(GetIndexFromPos, ACTOR_SELF, LVar0)
    Mod(LVar0, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVar0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar4, LVar2)
        Call(SetAnimation, ACTOR_SELF, 1, 0xA30000)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0xA30004)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar4, LVar2)
        Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0xA30000)
        Wait(8)
    EndIf
    Call(SetActorSounds, ACTOR_SELF, 2, 769, 0)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 5)
        Call(SetBattleCamDist, 430)
        Call(SetBattleCamOffsetY, 20)
        Call(MoveBattleCamOver, 10)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 3, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(SetPartYaw, ACTOR_SELF, 1, 180)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA30007)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar1, 24)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(ResetAllActorSounds, ACTOR_SELF)
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Thread
                Wait(5)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA30000)
            EndThread
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(8)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA30004)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA30001)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA30007)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 24)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, LVar4)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Thread
                Wait(5)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA30000)
            EndThread
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(8)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA30001)
        EndCaseGroup
    EndSwitch
    Label(10)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_goombario_lee_EVS_Attack_Headbonk = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    ExecWait(TTYD64_mac_goombario_lee_EVS_ApproachPlayer)
    ExecWait(b_area_mac_goombario_lee_EVS_CalculateJumpTime)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        SetF(LVar0, Float(7.2001953125))
        SetF(LVar1, Float(7.599609375))
        SetF(LVar1, Float(3.599609375))
    Else
        Set(LVar0, 18)
        Set(LVar1, 19)
        Set(LVar2, 9)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x90007)
    Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, LVar1, 0)
    Wait(1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x90006)
    Call(SetActorDispOffset, ACTOR_SELF, 0, LVar2, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 0, 0, 5)
    Call(SetJumpAnimations, ACTOR_SELF, 1, 0x90006, 0x90006, 0x90006)
    Call(b_area_mac_goombario_lee_UnkFunc62, LVarA, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetJumpAnimations, ACTOR_SELF, 1, 0x90006, 0x90006, 0x90006)
            Call(b_area_mac_goombario_lee_ActorJumpToPos)
            Thread
                Call(ShakeCam, 1, 0, 5, Float(1.0))
            EndThread
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(20)
            Call(YieldTurn)
            ExecWait(b_area_mac_goombario_lee_EVS_HeadbonkFollowthrough)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    ChildThread
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.099609375), Float(0.7998046875), Float(1.0))
        Wait(1)
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.2998046875), Float(0.5), Float(1.0))
        Wait(1)
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
    EndChildThread
    Wait(1)
    Wait(2)
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8320, 0, 0, 1, 16)
        CaseEq(1)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8320, 0, 0, 2, 16)
        CaseEq(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8320, 0, 0, 3, 16)
    EndSwitch
    Call(GetOwnerTarget, LVarA, 0)
    IfEq(LVarA, 0)
        Call(GetActorHP, 0, LVar0)
    Else
        Call(TTYD64_GetPartnerHP_API, LVar0)
    EndIf
    IfEq(LVar0, 0)
        Goto(100)
    EndIf
    Set(LVarA, 24)
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Thread
                Wait(4)
                Set(LVar0, 0)
                Loop(6)
                    Add(LVar0, 30)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetJumpAnimations, ACTOR_SELF, 1, 0x90006, 0x90006, 0x90006)
            Call(b_area_mac_goombario_lee_UnkFunc62, LVarA, 3)
        CaseEq(1)
            Thread
                Wait(4)
                Set(LVar0, 0)
                Loop(6)
                    Add(LVar0, 30)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnableActorBlur, ACTOR_SELF, 1)
            Call(SetJumpAnimations, ACTOR_SELF, 1, 0x90006, 0x90006, 0x90006)
            Call(b_area_mac_goombario_lee_UnkFunc62, LVarA, 3)
            Call(EnableActorBlur, ACTOR_SELF, 0)
        CaseEq(2)
            Thread
                Wait(4)
                Set(LVar0, 0)
                Loop(6)
                    Add(LVar0, 30)
                    Call(SetActorRotation, ACTOR_SELF, 0, -0xEE6B280, LVar0)
                    Wait(1)
                EndLoop
                Call(SetAnimation, ACTOR_SELF, 1, 0x90006)
            EndThread
            Thread
                Set(LVar0, 0)
                Loop(LVarA)
                    Add(LVar0, 133)
                    Call(SetActorRotation, ACTOR_SELF, -0xEE6B280, LVar0, -0xEE6B280)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnableActorBlur, ACTOR_SELF, 1)
            Call(SetJumpAnimations, ACTOR_SELF, 1, 0x90006, 0x90006, 0x90006)
            Call(b_area_mac_goombario_lee_UnkFunc62, LVarA, 3)
            Call(EnableActorBlur, ACTOR_SELF, 0)
    EndSwitch
    ChildThread
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.099609375), Float(0.7998046875), Float(1.0))
        Wait(1)
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.2998046875), Float(0.5), Float(1.0))
        Wait(1)
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
    EndChildThread
    Wait(1)
    Wait(2)
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8320, 0, 0, 1, 32)
        CaseEq(1)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8320, 0, 0, 2, 32)
        CaseEq(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8320, 0, 0, 3, 32)
    EndSwitch
    Label(100)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(YieldTurn)
            ExecWait(b_area_mac_goombario_lee_EVS_HeadbonkFollowthrough)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_chan_EVS_TakeTurn_Ground = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 2)
        Call(GetActorVar, ACTOR_SELF, 9, LVar0)
        Sub(LVar0, 1)
        IfGt(LVar0, 0)
            Call(SetActorVar, ACTOR_SELF, 9, LVar0)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(UseBattleCamPreset, 2)
        Else
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(20)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30002)
            SetConst(LVar2, 0xA30001)
            ExecWait(Ref(EVS_Enemy_FlipBackUp))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetActorVar, ACTOR_SELF, 8, 1)
            Call(SetTargetOffset, ACTOR_SELF, 1, 0, 16)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_mac_chan_UprightDefenseTable))
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_mac_chan_UprightAnims))
            Call(BindIdle, ACTOR_SELF, Ref(b_area_mac_chan_EVS_Idle))
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
        EndIf
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Return
    EndIf
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA3000C)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA30009)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(10)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(5)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 8225)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA30005)
    Wait(20)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 2, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Loop(0)
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Add(LVar0, 30)
                    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
                    IfGt(LVar0, LVar3)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                Call(UseBattleCamPreset, 1)
                IfEq(LVarA, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
                Wait(15)
                Call(UseBattleCamPreset, 2)
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -150, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Wait(15)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 200)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA3000D)
            Wait(10)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0xA30001)
            Wait(8)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA30001)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master3_EVS_Attack_StrikeTwice = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 8)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamDist, 200)
    Call(SetBattleCamOffsetY, 13)
    Call(MoveBattleCamOver, 60)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20015)
    Wait(40)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 7)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 1)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 953)
    Call(PlaySoundAtActor, ACTOR_SELF, 8379)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 0, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(UseBattleCamPreset, 2)
            Call(EnableActorBlur, ACTOR_SELF, 1)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -50, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20013)
            Call(RunToGoal, ACTOR_SELF, 10, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
            Call(EnableActorBlur, ACTOR_SELF, 0)
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
            Return
        EndCaseGroup
    EndSwitch
    Call(EnableActorBlur, ACTOR_SELF, 1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20013)
    Call(RunToGoal, ACTOR_SELF, 5, 0)
    Call(EnableActorBlur, ACTOR_SELF, 0)
    Thread
        Call(ShakeCam, 1, 0, 2, Float(1.0))
        Call(ShakeCam, 1, 0, 2, Float(4.0))
        Call(ShakeCam, 1, 0, 2, Float(3.0))
        Call(ShakeCam, 1, 0, 2, Float(2.0))
        Call(ShakeCam, 1, 0, 2, Float(1.0))
        Call(ShakeCam, 1, 0, 2, Float(0.5))
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 1005)
    Call(PlaySoundAtActor, ACTOR_SELF, 8379)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0xA0000, 0xFFFF, 0, 6, 16)
    Wait(15)
    Call(UseBattleCamPreset, 2)
    Thread
        Call(PlaySoundAtActor, ACTOR_SELF, 8321)
        Call(EnableActorBlur, ACTOR_SELF, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0xA20014)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.900390625))
        Call(JumpToGoal, ACTOR_SELF, 25, 0, 1, 0)
        Call(EnableActorBlur, ACTOR_SELF, 0)
    EndThread
    Thread
        Call(ShakeCam, 1, 0, 2, Float(0.5))
        Call(ShakeCam, 1, 0, 2, Float(1.5))
        Call(ShakeCam, 1, 0, 2, Float(0.5))
        Call(ShakeCam, 1, 0, 2, Float(0.2001953125))
    EndThread
    Wait(2)
    Call(PlaySoundAtActor, ACTOR_SELF, 1005)
    Call(PlaySoundAtActor, ACTOR_SELF, 8379)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0xA0000, 0xFFFF, 0, 7, 32)
    Wait(15)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(PlaySoundAtActor, ACTOR_SELF, 8382)
            Call(PlaySoundAtActor, ACTOR_SELF, 8379)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
                Set(LVar0, 0)
                Loop(10)
                    Add(LVar0, 36)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 50)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20021)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 30, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8378)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20023)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Wait(3)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20021)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 948)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20023)
            Wait(20)
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master3_EVS_Attack_StrikeTwice_8021FF4C = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 8)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamDist, 200)
    Call(SetBattleCamOffsetY, 13)
    Call(MoveBattleCamOver, 60)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20015)
    Wait(40)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 7)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 1)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 953)
    Call(PlaySoundAtActor, ACTOR_SELF, 8379)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 0, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(UseBattleCamPreset, 2)
            Call(EnableActorBlur, ACTOR_SELF, 1)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -50, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20013)
            Call(RunToGoal, ACTOR_SELF, 10, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
            Call(EnableActorBlur, ACTOR_SELF, 0)
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
            Return
        EndCaseGroup
    EndSwitch
    Call(EnableActorBlur, ACTOR_SELF, 1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20013)
    Call(RunToGoal, ACTOR_SELF, 5, 0)
    Call(EnableActorBlur, ACTOR_SELF, 0)
    Thread
        Call(ShakeCam, 1, 0, 2, Float(1.0))
        Call(ShakeCam, 1, 0, 2, Float(4.0))
        Call(ShakeCam, 1, 0, 2, Float(3.0))
        Call(ShakeCam, 1, 0, 2, Float(2.0))
        Call(ShakeCam, 1, 0, 2, Float(1.0))
        Call(ShakeCam, 1, 0, 2, Float(0.5))
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 1005)
    Call(PlaySoundAtActor, ACTOR_SELF, 8379)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8192, 0, 0, 5, 16)
    Wait(15)
    Call(UseBattleCamPreset, 2)
    Thread
        Call(PlaySoundAtActor, ACTOR_SELF, 8321)
        Call(EnableActorBlur, ACTOR_SELF, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0xA20014)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.900390625))
        Call(JumpToGoal, ACTOR_SELF, 25, 0, 1, 0)
        Call(EnableActorBlur, ACTOR_SELF, 0)
    EndThread
    Thread
        Call(ShakeCam, 1, 0, 2, Float(0.5))
        Call(ShakeCam, 1, 0, 2, Float(1.5))
        Call(ShakeCam, 1, 0, 2, Float(0.5))
        Call(ShakeCam, 1, 0, 2, Float(0.2001953125))
    EndThread
    Wait(2)
    Call(PlaySoundAtActor, ACTOR_SELF, 1005)
    Call(PlaySoundAtActor, ACTOR_SELF, 8379)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8192, 0, 0, 6, 32)
    Wait(15)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(PlaySoundAtActor, ACTOR_SELF, 8382)
            Call(PlaySoundAtActor, ACTOR_SELF, 8379)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
                Set(LVar0, 0)
                Loop(10)
                    Add(LVar0, 36)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 50)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20021)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 30, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8378)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20023)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Wait(3)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20021)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 948)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20023)
            Wait(20)
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_kooper_lee_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0011)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0012)
            SetConst(LVar2, 0xA0013)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0012)
            SetConst(LVar2, 0xA0013)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0013)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0011)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0011)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0011)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 4, 1)
            Call(SetActorVar, ACTOR_SELF, 5, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_mac_kooper_lee_ToppledDefenseTable))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_mac_kooper_lee_ToppledAnims))
            Call(SetTargetOffset, ACTOR_SELF, 1, 5, 15)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, -6)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA0011)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            Thread
                Wait(4)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -60)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -75)
                Wait(1)
            EndThread
            UseBuf(Ref(b_area_mac_kooper_lee_FlipPosOffsets))
            Loop(22)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA0019)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            Call(GetActorVar, ACTOR_SELF, 4, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0xA0004)
                CaseEq(1)
                    Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0xA0019)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0011)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0011)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 4, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA0019)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA0004)
                ExecWait(Ref(EVS_Enemy_Recover))
            EndIf
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0006)
            SetConst(LVar2, 0xA0011)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 4, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0xA0006)
                CaseEq(1)
                    Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0xA0019)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 4, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(GetStatusFlags, ACTOR_SELF, LVar0)
                    IfNotFlag(LVar0, 0x35D000)
                        IfFlag(LVar0, 0x80000)
                            Call(SetActorDispOffset, ACTOR_SELF, 0, 1, 0)
                        Else
                            Call(SetActorDispOffset, ACTOR_SELF, 0, 3, 0)
                        EndIf
                    EndIf
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0xA0006)
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0xA0019)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_watt_lee_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 19)
    Call(RandInt, 100, LVar3)
    IfLt(LVar3, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 350)
    Call(SetBattleCamOffsetY, 40)
    Call(MoveBattleCamOver, 80)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetTargetActor, ACTOR_SELF, LVar3)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0xE0003)
    Call(b_area_mac_watt_lee_WattFXSetEffect, 1)
    Call(AddGoalPos, ACTOR_SELF, 15, -10, 5)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
    Call(SetAnimation, ACTOR_SELF, 1, 0xE0001)
    Call(b_area_mac_watt_lee_WattFXSetEffect, 0)
    Wait(5)
    Call(b_area_mac_watt_lee_WattFXSetBouncing, 0)
    Call(AddGoalPos, ACTOR_SELF, 25, 20, 0)
    Call(FlyToGoal, ACTOR_SELF, 15, -20, 10)
    Call(SetAnimation, ACTOR_SELF, 1, 0xE0005)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(FlyToGoal, ACTOR_SELF, 5, 0, 10)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Wait(5)
                Call(SetAnimation, ACTOR_SELF, 1, 0xE0001)
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -40, 10, 0)
            Call(FlyToGoal, ACTOR_SELF, 10, -20, 4)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(b_area_mac_watt_lee_WattFXSetActive, 1)
            Call(b_area_mac_watt_lee_WattFXSetBouncing, 1)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0xE0003)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Call(SetAnimation, ACTOR_SELF, 1, 0xE0001)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(b_area_mac_watt_lee_WattFXSetActive, 0)
    Set(LVarA, 40)
    Call(AddBattleCamDist, -75)
    Call(MoveBattleCamOver, LVarA)
    Call(SetBattleCamTargetingModes, 0, 0, 1)
    Call(PlaySoundAtActor, ACTOR_SELF, 649)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 4)
        Call(PlayEffect_impl, 51, 8, LVar0, LVar1, LVar2, Float(0.51953125), LVarA, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 12)
        Call(PlayEffect_impl, 51, 8, LVar0, LVar1, LVar2, Float(1.2998046875), LVarA, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Call(b_area_mac_watt_lee_UnkBackgroundFunc3)
    Set(LVar9, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xE0006)
    Loop(LVarA)
        Add(LVar9, 3)
        IfGt(LVar9, 200)
            Set(LVar9, 200)
        EndIf
        Call(b_area_mac_watt_lee_SetBackgroundAlpha, LVar9)
        Wait(1)
    EndLoop
    Call(SetAnimation, ACTOR_SELF, 1, 0xE0001)
    Call(SetActorPaletteEffect, ACTOR_SELF, 1, 9)
    Call(AddBattleCamDist, 75)
    Call(MoveBattleCamOver, 5)
    Thread
        Wait(2)
        Call(b_area_mac_watt_lee_SetBackgroundAlpha, 0)
    EndThread
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000020, 0xFFFF, 0, 3, 32)
        CaseEq(1)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000020, 0xFFFF, 0, 4, 32)
        CaseEq(2)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000020, 0xFFFF, 0, 5, 32)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(b_area_mac_watt_lee_WattFXSetActive, 1)
            Call(b_area_mac_watt_lee_WattFXSetBouncing, 1)
            Call(AddGoalPos, ACTOR_SELF, 25, 10, 0)
            Call(FlyToGoal, ACTOR_SELF, 15, -10, 10)
            Wait(15)
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0xE0003)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Call(SetAnimation, ACTOR_SELF, 1, 0xE0001)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_bombette_lee_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Wait(10)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 40, 0, 0)
    Call(MoveBattleCamOver, 30)
    Call(SetAnimation, ACTOR_SELF, 1, 0xB0008)
    Call(RunToGoal, ACTOR_SELF, 30, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xB0004)
    Call(SetAnimation, ACTOR_SELF, 1, 0xB000F)
    Wait(15)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8224)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -10, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0010)
            Call(RunToGoal, ACTOR_SELF, 5, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0004)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 15, 0)
                Set(LVar0, 0)
                Loop(10)
                    Add(LVar0, 72)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(AddGoalPos, ACTOR_SELF, -60, 0, 0)
            Call(RunToGoal, ACTOR_SELF, 10, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0004)
            Thread
                Call(b_area_mac_bombette_lee_UnkActorPosFunc)
            EndThread
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0008)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Set(LVarA, LVar0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0xB0010)
    Call(RunToGoal, ACTOR_SELF, 4, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
        CaseEq(1)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 3, 32)
        CaseEq(2)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 5, 32)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0004)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 8)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0011)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB000E)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0011)
            Add(LVar0, 40)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB000E)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0011)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB000E)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0011)
            Add(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB000E)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0004)
            Wait(8)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0008)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lee_EVS_Move_CopyPartner = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(ActorSpeak, 0x20027, ACTOR_SELF, 1, 0xA40006, 0xA40003)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 8376)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA40007)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar1, 8)
        SetF(LVar3, Float(0.400390625))
    Else
        Add(LVar1, 20)
        SetF(LVar3, Float(1.0))
    EndIf
    Call(PlayEffect_impl, 19, 1, LVar0, LVar1, LVar2, LVar3, 40, 0, 0, 0, 0, 0, 0, 0)
    Call(b_area_mac_watt_lee_UnkBackgroundFunc3)
    Call(MakeLerp, 0, 200, 20, 0)
    Label(0)
    Call(UpdateLerp)
    Call(b_area_mac_watt_lee_SetBackgroundAlpha, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    Wait(10)
    Call(b_area_mac_lee_GetPartnerAndLevel, LVar5, LVar6)
    Call(b_area_mac_lee_RegisterPartnerToCopy)
    Call(TTYD64_mac_lee_AdjustFormationPriority, LVar5)
    Switch(LVar5)
        CaseEq(1)
            Call(SummonEnemy, Ref(TTYD64_mac_LeeGoombarioFormation), 0)
        CaseEq(2)
            Call(SummonEnemy, Ref(TTYD64_mac_LeeKooperFormation), 0)
        CaseEq(3)
            Call(SummonEnemy, Ref(TTYD64_mac_LeeBombetteFormation), 0)
        CaseEq(4)
            Call(SummonEnemy, Ref(TTYD64_mac_LeeParakarryFormation), 0)
        CaseEq(9)
            Call(SummonEnemy, Ref(TTYD64_mac_LeeBowFormation), 0)
        CaseEq(6)
            Call(SummonEnemy, Ref(TTYD64_mac_LeeWattFormation), 0)
        CaseEq(7)
            Call(SummonEnemy, Ref(TTYD64_mac_LeeSushieFormation), 0)
        CaseEq(8)
            Call(SummonEnemy, Ref(TTYD64_mac_LeeLakilesterFormation), 0)
    EndSwitch
    Set(LVarA, LVar0)
    Call(CopyStatusEffects, ACTOR_SELF, LVarA)
    Call(PlaySoundAtActor, ACTOR_SELF, 717)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 3)
        Add(LVar2, 5)
        Loop(3)
            Call(PlayEffect_impl, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(3)
        EndLoop
    EndThread
    Wait(5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20001, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x800000, 0)
    Call(SetActorFlagBits, ACTOR_SELF, 0x400004, 1)
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(SetEnemyHP, LVarA, LVar0)
    Call(CopyBuffs, ACTOR_SELF, LVarA)
    Call(GetOwnerID, LVar0)
    Call(SetActorVar, LVarA, 0, LVar0)
    Call(SetActorVar, LVarA, 1, LVar6)
    Wait(20)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Thread
        Call(MakeLerp, 200, 0, 20, 0)
        Label(1)
        Call(UpdateLerp)
        Call(b_area_mac_watt_lee_SetBackgroundAlpha, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(1)
        EndIf
    EndThread
    Call(SetActorSounds, LVarA, 2, 0, 0)
    Switch(LVar5)
        CaseEq(8)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, LVarA, Float(0.009765625))
            Call(SetGoalPos, LVarA, LVar0, 10, LVar2)
            Call(JumpToGoal, LVarA, 10, 0, 0, 0)
            Wait(10)
        CaseOrEq(6)
        CaseOrEq(9)
        CaseOrEq(4)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, LVarA, Float(0.009765625))
            Call(SetGoalPos, LVarA, LVar0, 30, LVar2)
            Call(JumpToGoal, LVarA, 20, 0, 0, 0)
        EndCaseGroup
    EndSwitch
    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(ForceHomePos, LVarA, LVar0, LVar1, LVar2)
    Call(HPBarToHome, LVarA)
    Call(ResetActorSounds, LVarA, 2)
    Wait(20)
    Call(SetActorPos, ACTOR_SELF, 0, -1000, 0)
    Call(ForceHomePos, ACTOR_SELF, 0, -1000, 0)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_parakarry_lee_EVS_Attack_SkyDive = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xC0003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 20, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 10)
    Call(SetAnimation, ACTOR_SELF, 1, 0xC0000)
    Wait(3)
    Call(UseBattleCamPresetImmediately, 1)
    Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8196)
    Call(SetAnimation, ACTOR_SELF, 1, 0xC0014)
    Call(AddGoalPos, ACTOR_SELF, 0, 10, 0)
    Call(FlyToGoal, ACTOR_SELF, 5, 0, 0)
    Wait(2)
    Thread
        Wait(3)
        Call(SetAnimation, ACTOR_SELF, 1, 0xC0004)
    EndThread
    Call(AddGoalPos, ACTOR_SELF, 40, 15, 0)
    Call(FlyToGoal, ACTOR_SELF, 20, -20, 6)
    Call(PlaySoundAtActor, ACTOR_SELF, 8197)
    Call(EnableActorBlur, ACTOR_SELF, 1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0xC0005)
    Call(FlyToGoal, ACTOR_SELF, 5, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Wait(5)
                Call(SetAnimation, ACTOR_SELF, 1, 0xC0001)
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -40, 10, 0)
            Call(FlyToGoal, ACTOR_SELF, 10, -20, 4)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(20)
            Call(EnableActorBlur, ACTOR_SELF, 0)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xC0003)
            Call(FlyToGoal, ACTOR_SELF, 0, -5, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(EnableActorBlur, ACTOR_SELF, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xC0006)
    Wait(1)
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
        CaseEq(1)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 3, 32)
        CaseEq(2)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 5, 32)
    EndSwitch
    Call(PlaySound, 0)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0xC0005)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
            Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xC0000)
            Thread
                Wait(4)
                Call(SetAnimation, ACTOR_SELF, 1, 0xC0003)
            EndThread
            Call(AddGoalPos, ACTOR_SELF, 30, 0, 0)
            Call(JumpWithBounce, ACTOR_SELF, 10, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xC0001)
            Wait(6)
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xC0003)
            Call(FlyToGoal, ACTOR_SELF, 0, -5, 0)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master3_EVS_Attack_StrikeOnce = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.7998046875))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 8381)
    Thread
        Wait(15)
        Call(PlaySoundAtActor, ACTOR_SELF, 8381)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0xA2000E)
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA2000F)
    Call(PlaySoundAtActor, ACTOR_SELF, 8380)
    Call(PlaySoundAtActor, ACTOR_SELF, 8379)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 0, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(UseBattleCamPreset, 2)
            Call(EnableActorBlur, ACTOR_SELF, 1)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -50, 0, 0)
            Call(RunToGoal, ACTOR_SELF, 10, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
            Call(EnableActorBlur, ACTOR_SELF, 0)
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
            Return
        EndCaseGroup
    EndSwitch
    Call(EnableActorBlur, ACTOR_SELF, 1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 0, 0, 0)
    Call(RunToGoal, ACTOR_SELF, 5, 0)
    Call(EnableActorBlur, ACTOR_SELF, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 1005)
    Call(PlaySoundAtActor, ACTOR_SELF, 8379)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 8, 48)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(PlaySoundAtActor, ACTOR_SELF, 8379)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 20, 0)
                Set(LVar0, 0)
                Loop(10)
                    Add(LVar0, 36)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 50)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2001953125))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20021)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8378)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20023)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Wait(3)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20021)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 948)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20023)
            Wait(20)
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master3_EVS_HandlePhase = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(10)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 0)
                Call(UseBattleCamPreset, 13)
                Call(BattleCamTargetActor, ACTOR_SELF)
                Call(SetTargetActor, ACTOR_SELF, 0)
                Wait(10)
                Call(ActorSpeak, 0x2002E, ACTOR_SELF, 1, 0xA20009, 0xA20005)
                Call(SetActorVar, ACTOR_SELF, 0, 1)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA2000D)
                Wait(15)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA2000C)
                Wait(5)
                Call(PlaySoundAtActor, ACTOR_SELF, 8376)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 20)
                Call(PlayEffect_impl, 19, 1, LVar0, LVar1, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
                Set(LVar0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA20000)
                Loop(15)
                    Add(LVar0, 24)
                    Call(SetActorRotation, ACTOR_SELF, 0, LVar0, 0)
                    Wait(1)
                EndLoop
                Set(LVar0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA20000)
                Loop(5)
                    Add(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, LVar0, 0)
                    Wait(1)
                EndLoop
                Call(PlaySoundAtActor, ACTOR_SELF, 717)
                Thread
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Add(LVar1, 3)
                    Loop(3)
                        Call(PlayEffect_impl, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                        Wait(3)
                    EndLoop
                EndThread
                Call(SetAnimation, ACTOR_SELF, 1, 0xA20000)
                Loop(5)
                    Add(LVar0, 36)
                    Call(SetActorRotation, ACTOR_SELF, 0, LVar0, 0)
                    Wait(1)
                EndLoop
                Call(SetAnimation, ACTOR_SELF, 1, 0xA20001)
                Loop(5)
                    Add(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, LVar0, 0)
                    Wait(1)
                EndLoop
                Wait(15)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_mac_master3_AscendedAnims))
                Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA20014)
                Wait(2)
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 1)
                Wait(1)
                Call(ModifyActorDecoration, ACTOR_SELF, 1, 0, 50, 50, 0, 0)
                Wait(15)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(ActorSpeak, 0x20038, ACTOR_SELF, 1, 0xA2000A, 0xA20006)
            EndIf
        CaseEq(12)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x351000)
                BreakSwitch
            EndIf
            Call(GetActorHP, ACTOR_SELF, LVar0)
            Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
            Div(LVar1, 2)
            IfLe(LVar0, LVar1)
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(ActorSpeak, 0x2003B, ACTOR_SELF, 1, 0xA2000A, 0xA20006)
                BreakSwitch
            EndIf
            Call(GetOwnerTarget, LVar0, 0)
            IfEq(LVar0, 0)
                Call(GetPlayerHP, LVar0)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar0)
            EndIf
            IfLe(LVar0, 10)
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(ActorSpeak, 0x2003D, ACTOR_SELF, 1, 0xA2000A, 0xA20006)
                BreakSwitch
            EndIf
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master3_EVS_HandleEvent_Inner = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20016)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA2001A)
            SetConst(LVar2, 0xA2001B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 1)
            Wait(1)
            Call(ModifyActorDecoration, ACTOR_SELF, 1, 0, 50, 50, 0, 0)
        CaseEq(36)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA2001A)
            SetConst(LVar2, 0xA2001B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20018)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20016)
            ChildThread
                Wait(30)
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                Wait(10)
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 1)
                Wait(1)
                Call(ModifyActorDecoration, ACTOR_SELF, 1, 0, 50, 50, 0, 0)
            EndChildThread
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20016)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20016)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20006)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20003)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20016)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20018)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20016)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20018)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20016)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20018)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20003)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20003)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20008)
            SetConst(LVar2, 0xA20016)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_bow_lee_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0018)
            SetConst(LVar2, 0xD0019)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0018)
            SetConst(LVar2, 0xD0019)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0019)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(UseBattleCamPreset, 2)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            Set(LVar2, 14)
            ExecWait(TTYD64_mac_EVS_Lee_ShockKnockback)
            Thread
                Set(LVar0, 200)
                Loop(20)
                    Sub(LVar0, 10)
                    Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 60)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0003)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0001)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
        CaseEq(38)
            Call(UseBattleCamPreset, 2)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            Set(LVar2, 14)
            ExecWait(TTYD64_mac_EVS_Lee_ShockKnockback)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0003)
            SetConst(LVar2, 0xD0015)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master3_EVS_Attack_StrikeOnce_80225E68 = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.7998046875))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 8381)
    Thread
        Wait(15)
        Call(PlaySoundAtActor, ACTOR_SELF, 8381)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0xA2000E)
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA2000F)
    Call(PlaySoundAtActor, ACTOR_SELF, 8380)
    Call(PlaySoundAtActor, ACTOR_SELF, 8379)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 0, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 0, 16)
            Switch(LVarA)
                CaseOrEq(6)
                CaseOrEq(5)
                    Call(UseBattleCamPreset, 2)
                    Call(EnableActorBlur, ACTOR_SELF, 1)
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(AddGoalPos, ACTOR_SELF, -50, 0, 0)
                    Call(RunToGoal, ACTOR_SELF, 10, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
                    Call(EnableActorBlur, ACTOR_SELF, 0)
                    Wait(10)
                    IfEq(LVarA, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
                    Return
            EndSwitch
            Call(EnableActorBlur, ACTOR_SELF, 1)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -33, 0, 0)
            Call(RunToGoal, ACTOR_SELF, 5, 0)
            Call(EnableActorBlur, ACTOR_SELF, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 1005)
            Call(PlaySoundAtActor, ACTOR_SELF, 8379)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x80000, 0xFFFF, 0, 10, 48)
            ExecWait(TTYD64_mac_EVS_8022DE60)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(EnableActorBlur, ACTOR_SELF, 1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -65, 0, 0)
    Call(RunToGoal, ACTOR_SELF, 5, 0)
    Call(EnableActorBlur, ACTOR_SELF, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 1005)
    Call(PlaySoundAtActor, ACTOR_SELF, 8379)
    Wait(2)
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 0, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
        EndCaseGroup
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x80000, 0xFFFF, 0, 10, 48)
    EndSwitch
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x80000, 0xFFFF, 0, 10, 48)
    ExecWait(TTYD64_mac_EVS_8022DE60)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master2_EVS_HandlePhase = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(10)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 0)
                Call(UseBattleCamPreset, 13)
                Call(BattleCamTargetActor, ACTOR_SELF)
                Call(SetTargetActor, ACTOR_SELF, 0)
                Wait(10)
                Call(ActorSpeak, 0x2002E, ACTOR_SELF, 1, 0xA20009, 0xA20005)
                Call(SetActorVar, ACTOR_SELF, 0, 1)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA2000D)
                Wait(15)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA2000C)
                Wait(5)
                Call(PlaySoundAtActor, ACTOR_SELF, 8376)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 20)
                Call(PlayEffect_impl, 19, 1, LVar0, LVar1, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
                Set(LVar0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA20000)
                Loop(15)
                    Add(LVar0, 24)
                    Call(SetActorRotation, ACTOR_SELF, 0, LVar0, 0)
                    Wait(1)
                EndLoop
                Set(LVar0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA20000)
                Loop(5)
                    Add(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, LVar0, 0)
                    Wait(1)
                EndLoop
                Call(PlaySoundAtActor, ACTOR_SELF, 717)
                Thread
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Add(LVar1, 3)
                    Loop(3)
                        Call(PlayEffect_impl, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                        Wait(3)
                    EndLoop
                EndThread
                Call(SetAnimation, ACTOR_SELF, 1, 0xA20000)
                Loop(5)
                    Add(LVar0, 36)
                    Call(SetActorRotation, ACTOR_SELF, 0, LVar0, 0)
                    Wait(1)
                EndLoop
                Call(SetAnimation, ACTOR_SELF, 1, 0xA20001)
                Loop(5)
                    Add(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, LVar0, 0)
                    Wait(1)
                EndLoop
                Wait(15)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_mac_master3_AscendedAnims_80231DD0))
                Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
                Wait(15)
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(ActorSpeak, 0x20033, ACTOR_SELF, 1, 0xA2000A, 0xA20006)
            EndIf
        CaseEq(12)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x351000)
                BreakSwitch
            EndIf
            Call(GetActorHP, ACTOR_SELF, LVar0)
            Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
            Div(LVar1, 2)
            IfLe(LVar0, LVar1)
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(ActorSpeak, 0x20036, ACTOR_SELF, 1, 0xA2000A, 0xA20006)
                BreakSwitch
            EndIf
            Call(GetOwnerTarget, LVar0, 0)
            IfEq(LVar0, 0)
                Call(GetPlayerHP, LVar0)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar0)
            EndIf
            IfLe(LVar0, 5)
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(ActorSpeak, 0x20037, ACTOR_SELF, 1, 0xA2000A, 0xA20006)
                BreakSwitch
            EndIf
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master1_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20007)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 30, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.599609375))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20002)
    Wait(10)
    Thread
        Call(PlaySoundAtActor, ACTOR_SELF, 8379)
        Wait(5)
        Call(PlaySoundAtActor, ACTOR_SELF, 8379)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20010)
    Wait(10)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0xA20011)
        Wait(7)
        Call(SetAnimation, ACTOR_SELF, 1, 0xA20012)
    EndThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(RunToGoal, ACTOR_SELF, 8, 1)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 0, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20007)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(RunToGoal, ACTOR_SELF, 10, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20002)
            Wait(3)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20002)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(3.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20007)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20002)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 1005)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 6, 48)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20007)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(RunToGoal, ACTOR_SELF, 10, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20002)
            Wait(20)
        EndCaseGroup
    EndSwitch
    Call(UseBattleCamPreset, 2)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20002)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20007)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20002)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_parakarry_lee_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000F)
            SetConst(LVar2, 0xC0010)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000F)
            SetConst(LVar2, 0xC0010)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC0010)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000D)
            Set(LVar2, 22)
            ExecWait(TTYD64_mac_EVS_Lee_ShockKnockback)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xC0003)
            Call(FlyToGoal, ACTOR_SELF, 0, -5, 0)
        CaseEq(38)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000D)
            Set(LVar2, 22)
            ExecWait(TTYD64_mac_EVS_Lee_ShockKnockback)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC0001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC0003)
            SetConst(LVar2, 0xC000D)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC0003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                IfFlag(LVar0, 0x80000)
                    Call(SetActorDispOffset, ACTOR_SELF, 0, 1, 0)
                Else
                    Call(SetActorDispOffset, ACTOR_SELF, 0, 3, 0)
                EndIf
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lee_EVS_Attack_FlyingTackle = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA40008)
    Wait(20)
    Call(SetActorSounds, ACTOR_SELF, 2, 715, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA40009)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -100, 0, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
            Call(JumpToGoal, ACTOR_SELF, 17, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(10)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorPos, ACTOR_SELF, LVar0, 0, LVar2)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA40002)
            Call(ResetActorSounds, ACTOR_SELF, 2)
            Wait(15)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(b_area_mac_lee_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0xA40009)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Call(AddGoalPos, ACTOR_SELF, Float(4.0), Float(-6.0), 0)
    Else
        Call(AddGoalPos, ACTOR_SELF, 10, -15, 0)
    EndIf
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 5, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(ResetActorSounds, ACTOR_SELF, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA4000A)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Wait(10)
            Call(YieldTurn)
            ExecWait(b_area_mac_lee_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master2_EVS_HandleEvent_Inner = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20016)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA2001A)
            SetConst(LVar2, 0xA2001B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA2001A)
            SetConst(LVar2, 0xA2001B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20018)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20016)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20016)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20016)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20006)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20003)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20016)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20018)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20016)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20018)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20016)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20018)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20003)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20003)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20008)
            SetConst(LVar2, 0xA20016)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master2_EVS_HandleEvent_Inner_802282E8 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20017)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA2001A)
            SetConst(LVar2, 0xA2001B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA2001A)
            SetConst(LVar2, 0xA2001B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20019)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20017)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20017)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20017)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20007)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20005)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20002)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20017)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20019)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20017)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20019)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20017)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20019)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20002)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20002)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA20007)
            SetConst(LVar2, 0xA20017)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_sushie_lee_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000E)
            SetConst(LVar2, 0xF000F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000E)
            SetConst(LVar2, 0xF000F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000F)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            Set(LVar2, 20)
            ExecWait(TTYD64_mac_EVS_Lee_ShockKnockback)
            Call(SetAnimation, ACTOR_SELF, 1, 0xF0003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
        CaseEq(38)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            Set(LVar2, 20)
            ExecWait(TTYD64_mac_EVS_Lee_ShockKnockback)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF0001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF0003)
            SetConst(LVar2, 0xF000D)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF0003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_sushie_lee_EVS_HandleEvent_80228E00 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000B)
            SetConst(LVar2, 0x9000C)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000B)
            SetConst(LVar2, 0x9000C)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000C)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            Set(LVar2, 12)
            ExecWait(TTYD64_mac_EVS_Lee_ShockKnockback)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x90003)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
        CaseEq(38)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            Set(LVar2, 12)
            ExecWait(TTYD64_mac_EVS_Lee_ShockKnockback)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x90001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x90001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x90003)
            SetConst(LVar2, 0x9000A)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x90003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_bombette_lee_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0012)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0013)
            SetConst(LVar2, 0xB0014)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0013)
            SetConst(LVar2, 0xB0014)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0014)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0012)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0012)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0012)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0012)
            Set(LVar2, 15)
            ExecWait(TTYD64_mac_EVS_Lee_ShockKnockback)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0008)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
        CaseEq(38)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0012)
            Set(LVar2, 15)
            ExecWait(TTYD64_mac_EVS_Lee_ShockKnockback)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0014)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0004)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            ExecWait(b_area_mac_EVS_Lee_RemoveParentActor)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0012)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0012)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0004)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0008)
            SetConst(LVar2, 0xB0012)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0008)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0012)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_EVS_Lee_LoseDisguise = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    Wait(30)
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    Call(UseIdleAnimation, LVarA, 0)
    Call(HideHealthBar, LVarA)
    Call(CopyStatusEffects, ACTOR_SELF, LVarA)
    Call(PlaySoundAtActor, ACTOR_SELF, 717)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 3)
        Add(LVar2, 5)
        Loop(3)
            Call(PlayEffect_impl, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(3)
        EndLoop
    EndThread
    Wait(5)
    Call(GetActorHP, ACTOR_SELF, LVarB)
    Call(SetEnemyHP, LVarA, LVarB)
    Call(CopyBuffs, ACTOR_SELF, LVarA)
    Call(GetActorPos, ACTOR_SELF, LVarB, LVarC, LVarD)
    Call(SetActorPos, LVarA, LVarB, LVarC, LVarD)
    Call(SetPartFlagBits, LVarA, 1, 0x800000, 1)
    Call(SetPartFlagBits, LVarA, 1, 0x20001, 0)
    Call(SetActorFlagBits, LVarA, 0x400004, 0)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
    Call(SetActorVar, LVarA, 8, 2)
    Call(SetPartFlagBits, ACTOR_SELF, LVar0, 1, 1)
    Call(SetIdleAnimations, LVarA, 1, Ref(b_area_mac_lee_FlailingAnims))
    Call(SetAnimation, LVarA, 1, 0xA4000B)
    Wait(30)
    Call(UseBattleCamPreset, 2)
    Call(GetActorPos, LVarA, LVarB, LVarC, LVarD)
    IfGt(LVarC, 0)
        Set(LVarC, 0)
        Call(SetActorJumpGravity, LVarA, Float(0.5))
        Call(SetActorSounds, LVarA, 2, 769, 0)
        Call(SetGoalPos, LVarA, LVarB, LVarC, LVarD)
        Call(JumpToGoal, LVarA, 15, 0, 1, 0)
        Call(ResetActorSounds, LVarA, 2)
        Call(SetGoalPos, LVarA, LVarB, LVarC, LVarD)
        Call(JumpToGoal, LVarA, 10, 0, 1, 0)
        Call(SetGoalPos, LVarA, LVarB, LVarC, LVarD)
        Call(JumpToGoal, LVarA, 5, 0, 1, 0)
    EndIf
    Call(ForceHomePos, LVarA, LVarB, LVarC, LVarD)
    Call(HPBarToHome, LVarA)
    Call(SetIdleAnimations, LVarA, 1, Ref(TTYD64_mac_lee_DefaultAnims))
    Call(SetAnimation, LVarA, 1, 0xA40002)
    Call(SetActorPos, ACTOR_SELF, 0, -1000, 0)
    Call(ForceHomePos, ACTOR_SELF, 0, -1000, 0)
    Call(HPBarToHome, ACTOR_SELF)
    Call(RemoveActor, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_chan_EVS_HandleEvent_Ceiling = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_mac_chan_EVS_FallFromCeiling)
        CaseEq(13)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_mac_chan_EVS_FallFromCeiling)
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            SetConst(LVar2, 0xA30006)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_mac_chan_EVS_FallFromCeiling)
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            SetConst(LVar2, 0xA30006)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA3000C)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA3000C)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Wait(2)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x200000)
                ExecWait(TTYD64_mac_chan_EVS_FallFromCeiling)
            EndIf
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 1)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA30004)
            SetConst(LVar2, 0xA30006)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_chan_EVS_FallFromCeiling = {
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 2)
    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 16)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
    Call(b_area_mac_chan_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_chan_EVS_TakeTurn_Ground))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mac_chan_EVS_HandleEvent_Ground))
    Call(SetActorVar, ACTOR_SELF, 9, 1)
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_mac_chan_ToppledDefenseTable))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_mac_chan_ToppledAnims))
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(SetPartEventBits, ACTOR_SELF, 1, 16, 0)
    Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
    Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA30007)
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 24)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetActorSounds, ACTOR_SELF, 2, 769, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(GetIndexFromPos, ACTOR_SELF, LVarA)
    Mod(LVarA, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVarA)
    Call(GetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(SetHomePos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Set(LVarD, LVarA)
    Set(LVarE, LVarB)
    Set(LVarF, LVarC)
    Sub(LVarD, LVar0)
    Sub(LVarE, LVar1)
    Sub(LVarF, LVar2)
    Div(LVarD, 2)
    Div(LVarE, 2)
    Div(LVarF, 2)
    Add(LVar0, LVarD)
    Add(LVar1, LVarE)
    Add(LVar2, LVarF)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA30002)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_chan_EVS_HandlePhase = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(10)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 0)
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(ActorSpeak, 0x2001F, ACTOR_SELF, 1, 0xA30004, 0xA30003)
                Call(SetActorVar, ACTOR_SELF, 0, 1)
            EndIf
        CaseEq(12)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 2)
                BreakSwitch
            EndIf
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x37100A)
                BreakSwitch
            EndIf
            SetConst(LVarA, 0xA30004)
            SetConst(LVarB, 0xA30003)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 2)
                SetConst(LVarA, 0xA30007)
                SetConst(LVarB, 0xA30002)
            EndIf
            Call(GetActorHP, ACTOR_SELF, LVar0)
            Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
            Div(LVar1, 2)
            IfLe(LVar0, LVar1)
                Call(GetActorVar, ACTOR_SELF, 2, LVar0)
                IfEq(LVar0, 0)
                    Call(UseBattleCamPreset, 2)
                    Call(MoveBattleCamOver, 10)
                    Call(ActorSpeak, 0x20021, ACTOR_SELF, 1, LVarA, LVarB)
                    Call(SetActorVar, ACTOR_SELF, 2, 1)
                    BreakSwitch
                EndIf
            EndIf
            Call(GetOwnerTarget, LVar0, 0)
            IfEq(LVar0, 0)
                Call(GetPlayerHP, LVar0)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar0)
            EndIf
            IfLe(LVar0, 5)
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(ActorSpeak, 0x20022, ACTOR_SELF, 1, LVarA, LVarB)
                BreakSwitch
            EndIf
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master3_EVS_Attack_SpiritStrike = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 8)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamDist, 200)
    Call(SetBattleCamOffsetY, 13)
    Call(MoveBattleCamOver, 60)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20015)
    Set(LVar0, 80)
    Loop(30)
        Add(LVar0, 2)
        Call(ModifyActorDecoration, ACTOR_SELF, 1, 0, 80, LVar0, 0, 0)
        Wait(1)
    EndLoop
    Call(UseBattleCamPreset, 2)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA2000E)
    Thread
        Set(LVar0, 140)
        Loop(30)
            Sub(LVar0, 2)
            Call(ModifyActorDecoration, ACTOR_SELF, 1, 0, 80, LVar0, 0, 0)
            Wait(1)
        EndLoop
    EndThread
    Call(AddActorDecoration, ACTOR_SELF, 2, 0, 1)
    Wait(1)
    Call(ModifyActorDecoration, ACTOR_SELF, 2, 0, 40, 40, 0, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Call(SetPartAlpha, ACTOR_SELF, 2, 80)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.099609375))
    Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 10, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x80000, 0xFFFF, 0, 10, 16)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master3_EVS_HandleEvent = {
    ExecWait(TTYD64_mac_master2_EVS_HandleEvent_Inner_802282E8)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x351000)
        Return
    EndIf
    Call(GetBattleFlags, LVar0)
    IfFlag(LVar0, 576)
        Call(GetLastDamage, ACTOR_SELF, LVar0)
        IfGt(LVar0, 0)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
            Call(AddActorVar, ACTOR_SELF, 3, 1)
        EndIf
    EndIf
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(10)
        CaseOrEq(14)
        CaseOrEq(11)
        CaseOrEq(25)
        CaseOrEq(31)
            Call(GetActorVar, ACTOR_SELF, 2, LVarA)
            Call(GetActorVar, ACTOR_SELF, 3, LVarB)
            Call(SetActorVar, ACTOR_SELF, 2, 0)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x3F1000)
                BreakSwitch
            EndIf
            Set(LFlag0, 0)
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar0)
                CaseOrEq(1)
                CaseOrEq(0)
                    Set(LFlag0, 1)
                EndCaseGroup
            EndSwitch
            IfEq(LFlag0, 0)
                BreakSwitch
            EndIf
            Call(UseIdleAnimation, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 0)
            IfEq(LVarA, 1)
                IfGt(LVarB, 2)
                    Call(UseBattleCamPreset, 2)
                    Call(MoveBattleCamOver, 10)
                    Call(ActorSpeak, 0x20030, ACTOR_SELF, 1, 0xA20009, 0xA20005)
                    Call(SetActorVar, ACTOR_SELF, 3, 0)
                EndIf
            Else
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(ActorSpeak, 0x2002F, ACTOR_SELF, 1, 0xA20009, 0xA20005)
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master3_EVS_HandleEvent_8022D0D0 = {
    ExecWait(TTYD64_mac_master3_EVS_HandleEvent_Inner)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x351000)
        Return
    EndIf
    Call(GetBattleFlags, LVar0)
    IfFlag(LVar0, 576)
        Call(GetLastDamage, ACTOR_SELF, LVar0)
        IfGt(LVar0, 0)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
            Call(AddActorVar, ACTOR_SELF, 3, 1)
        EndIf
    EndIf
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(10)
        CaseOrEq(14)
        CaseOrEq(11)
        CaseOrEq(25)
        CaseOrEq(31)
            Call(GetActorVar, ACTOR_SELF, 2, LVarA)
            Call(GetActorVar, ACTOR_SELF, 3, LVarB)
            Call(SetActorVar, ACTOR_SELF, 2, 0)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x3F1000)
                BreakSwitch
            EndIf
            Set(LFlag0, 0)
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar0)
                CaseOrEq(1)
                CaseOrEq(0)
                    Set(LFlag0, 1)
                EndCaseGroup
            EndSwitch
            IfEq(LFlag0, 0)
                BreakSwitch
            EndIf
            Call(UseIdleAnimation, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 0)
            IfEq(LVarA, 1)
                IfGt(LVarB, 2)
                    Call(UseBattleCamPreset, 2)
                    Call(MoveBattleCamOver, 10)
                    Call(ActorSpeak, 0x2003A, ACTOR_SELF, 1, 0xA2000A, 0xA20006)
                    Call(SetActorVar, ACTOR_SELF, 3, 0)
                EndIf
            Else
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(ActorSpeak, 0x20039, ACTOR_SELF, 1, 0xA2000A, 0xA20006)
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master3_EVS_HandleEvent_8022D438 = {
    ExecWait(TTYD64_mac_master2_EVS_HandleEvent_Inner)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x351000)
        Return
    EndIf
    Call(GetBattleFlags, LVar0)
    IfFlag(LVar0, 576)
        Call(GetLastDamage, ACTOR_SELF, LVar0)
        IfGt(LVar0, 0)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
            Call(AddActorVar, ACTOR_SELF, 3, 1)
        EndIf
    EndIf
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(10)
        CaseOrEq(14)
        CaseOrEq(11)
        CaseOrEq(25)
        CaseOrEq(31)
            Call(GetActorVar, ACTOR_SELF, 2, LVarA)
            Call(GetActorVar, ACTOR_SELF, 3, LVarB)
            Call(SetActorVar, ACTOR_SELF, 2, 0)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x3F1000)
                BreakSwitch
            EndIf
            Set(LFlag0, 0)
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar0)
                CaseOrEq(1)
                CaseOrEq(0)
                    Set(LFlag0, 1)
                EndCaseGroup
            EndSwitch
            IfEq(LFlag0, 0)
                BreakSwitch
            EndIf
            Call(UseIdleAnimation, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 0)
            IfEq(LVarA, 1)
                IfGt(LVarB, 2)
                    Call(UseBattleCamPreset, 2)
                    Call(MoveBattleCamOver, 10)
                    Call(ActorSpeak, 0x20035, ACTOR_SELF, 1, 0xA2000A, 0xA20006)
                    Call(SetActorVar, ACTOR_SELF, 3, 0)
                EndIf
            Else
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(ActorSpeak, 0x20034, ACTOR_SELF, 1, 0xA2000A, 0xA20006)
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_EVS_Lee_ShockKnockback = {
    Call(HideHealthBar, ACTOR_SELF)
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Set(LVarC, LVar2)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, LVarA, LVarB)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 15)
    Add(LVar1, 10)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.099609375))
    Call(SetAnimation, ACTOR_SELF, LVarA, LVarB)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 0, 0)
    Set(LVar0, LVarA)
    Set(LVar1, LVarB)
    ExecWait(Ref(EVS_Enemy_ShockHit))
    Call(UseBattleCamPreset, 2)
    Thread
        Call(SetActorRotationOffset, ACTOR_SELF, 0, LVarC, 0)
        Set(LVar0, 0)
        Loop(15)
            Add(LVar0, -48)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 60)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Add(LVar0, 20)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Add(LVar0, 10)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_EVS_8022DE60 = {
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(PlaySoundAtActor, ACTOR_SELF, 8379)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 20, 0)
                Set(LVar0, 0)
                Loop(10)
                    Add(LVar0, 36)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 50)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2001953125))
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20021)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8378)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20023)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Wait(3)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20021)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 948)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA20023)
            Wait(20)
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20008)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_goombario_lee_EVS_Move_Tattle = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Wait(10)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetBattleFlagBits, 4, 1)
    Call(b_area_mac_goombario_lee_OpenTattleWindow, LVar5)
    Wait(12)
    Call(SetCamEnabled, 2, 1)
    Call(SetCamNoDraw, 2, 0)
    Call(SetCamPerspective, 2, 6, 25, 16, 1024)
    Call(SetCamViewport, 2, 37, 95, 138, 99)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 8)
    Set(LVar1, 0)
    Call(b_area_mac_goombario_lee_CalculateTattleCamBoomLength)
    Wait(1)
    Call(SetCamLookTarget, 2, LVar0, LVar1, LVar2)
    Call(SetInterpCamParams, 2, 0, LVar3, 100, 4)
    Wait(2)
    Call(PlaySoundAtActor, ACTOR_SELF, 642)
    Call(SetCamNoDraw, 2, 1)
    Wait(10)
    Call(ActorSpeak, 0x1C0092, ACTOR_SELF, 1, 0x9000F, 0x90001)
    Call(b_area_mac_goombario_lee_CloseTattleWindow, LVar5)
    Wait(12)
    Call(SetCamEnabled, 2, 0)
    Wait(32)
    Call(UseBattleCamPreset, 2)
    Call(SetBattleFlagBits, 4, 0)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master1_EVS_HandlePhase = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(10)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 0)
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(ActorSpeak, 0x2002E, ACTOR_SELF, 1, 0xA20009, 0xA20005)
                Call(SetActorVar, ACTOR_SELF, 0, 1)
            EndIf
        CaseEq(12)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x351000)
                BreakSwitch
            EndIf
            Call(GetActorHP, ACTOR_SELF, LVar0)
            Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
            Div(LVar1, 2)
            IfLe(LVar0, LVar1)
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(ActorSpeak, 0x20031, ACTOR_SELF, 1, 0xA20009, 0xA20005)
                BreakSwitch
            EndIf
            Call(GetOwnerTarget, LVar0, 0)
            IfEq(LVar0, 0)
                Call(GetPlayerHP, LVar0)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar0)
            EndIf
            IfLe(LVar0, 5)
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(ActorSpeak, 0x20032, ACTOR_SELF, 1, 0xA20009, 0xA20005)
                BreakSwitch
            EndIf
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_chan_EVS_HandleEvent_Initial = {
    ExecWait(TTYD64_mac_chan_EVS_HandleEvent_Ground)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(13)
            Call(GetBattleFlags, LVar0)
            IfNotFlag(LVar0, 32)
                BreakSwitch
            EndIf
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x3F1000)
                BreakSwitch
            EndIf
            Set(LFlag0, 0)
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar0)
                CaseOrEq(1)
                CaseOrEq(0)
                    Set(LFlag0, 1)
                EndCaseGroup
            EndSwitch
            IfEq(LFlag0, 0)
                BreakSwitch
            EndIf
            Call(UseIdleAnimation, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 0)
            Wait(30)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 2)
                Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                Add(LVar0, 1)
                Switch(LVar0)
                    CaseEq(1)
                        Call(UseBattleCamPreset, 2)
                        Call(MoveBattleCamOver, 10)
                        Call(ActorSpeak, 0x20020, ACTOR_SELF, 1, 0xA30007, 0xA30002)
                    CaseEq(2)
                    CaseEq(3)
                        Set(LVar0, 0)
                EndSwitch
                Call(SetActorVar, ACTOR_SELF, 1, LVar0)
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lee_EVS_HandlePhase = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(12)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x3F1000)
                BreakSwitch
            EndIf
            Call(GetActorHP, ACTOR_SELF, LVar0)
            Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
            Div(LVar1, 2)
            IfLe(LVar0, LVar1)
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(GetActorVar, ACTOR_SELF, 8, LVar0)
                IfEq(LVar0, 1)
                    Call(ActorSpeak, 0x20028, 513, 1, 0xA40006, 0xA40003)
                Else
                    Call(ActorSpeak, 0x20028, ACTOR_SELF, 1, 0xA40006, 0xA40003)
                EndIf
                BreakSwitch
            EndIf
            Call(GetOwnerTarget, LVar0, 0)
            IfEq(LVar0, 0)
                Call(GetPlayerHP, LVar0)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar0)
            EndIf
            IfLe(LVar0, 5)
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 10)
                Call(ActorSpeak, 0x20029, ACTOR_SELF, 1, 0xA40006, 0xA40003)
                BreakSwitch
            EndIf
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master3_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    IfEq(LVar0, 0)
        Call(GetActorHP, ACTOR_SELF, LVar0)
        IfLt(LVar0, 0)
            ExecWait(b_area_mac_master3_EVS_AscendToFinalForm)
        Else
            Call(TTYD64_GetMarioPos, LVar0)
            IfEq(LVar0, 1)
                Call(GetPlayerHP, LVar0)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar0)
            EndIf
            IfGt(LVar0, 20)
                Call(RandInt, 100, LVar0)
                Switch(LVar0)
                    CaseLt(30)
                        ExecWait(TTYD64_mac_master3_EVS_Attack_StrikeThrice)
                    CaseLt(50)
                        ExecWait(TTYD64_mac_master3_EVS_Attack_StrikeTwice)
                    CaseDefault
                        ExecWait(TTYD64_mac_master3_EVS_Attack_StrikeOnce_80225E68)
                EndSwitch
            Else
                Call(RandInt, 100, LVar0)
                Switch(LVar0)
                    CaseLt(50)
                        ExecWait(TTYD64_mac_master3_EVS_Attack_StrikeTwice)
                    CaseDefault
                        ExecWait(TTYD64_mac_master3_EVS_Attack_StrikeOnce_80225E68)
                EndSwitch
            EndIf
        EndIf
    Else
        Call(RandInt, 100, LVar0)
        Switch(LVar0)
            CaseLt(100)
                ExecWait(TTYD64_mac_master3_EVS_Attack_FlyingGrab)
            CaseLt(50)
                ExecWait(TTYD64_mac_master3_EVS_Attack_SpiritStrike)
        EndSwitch
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master3_EVS_Attack_FlyingGrab = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 8)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamDist, 200)
    Call(SetBattleCamOffsetY, 13)
    Call(MoveBattleCamOver, 60)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20015)
    Set(LVar0, 80)
    Loop(30)
        Add(LVar0, 2)
        Call(ModifyActorDecoration, ACTOR_SELF, 1, 0, 80, LVar0, 0, 0)
        Wait(1)
    EndLoop
    Call(SetAnimation, ACTOR_SELF, 1, 0xA20003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, 0)
    Wait(0x2710)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x80000, 0xFFFF, 0, 10, 16)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_chan_EVS_SetInitialState = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mac_chan_EVS_Idle))
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 8, 0)
        Call(b_area_mac_chan_SetAbsoluteStatusOffsets, -10, 0, 10, 0)
        Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_chan_EVS_TakeTurn_Ceiling))
        Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mac_chan_EVS_HandleEvent_Ceiling))
        Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 0)
    Else
        Call(SetActorVar, ACTOR_SELF, 8, 1)
        Call(SetTargetOffset, ACTOR_SELF, 1, 0, 16)
        Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
        Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_chan_EVS_TakeTurn_Ground))
        Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mac_chan_EVS_HandleEvent_Ground))
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_mac_chan_UprightAnims))
        Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
        Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
    EndIf
    Call(HPBarToHome, ACTOR_SELF)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_goombario_lee_EVS_ApproachPlayer = {
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 70, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x90003)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x90001)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lee_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_lee_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mac_master3_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_mac_lee_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_mac_lee_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Thread
        Call(FreezeBattleState, 1)
        ExecWait(TTYD64_mac_lee_EVS_Move_CopyPartner)
        Call(FreezeBattleState, 0)
    EndThread
    Call(b_area_mac_lee_InitPartnerCopyHistory)
    Call(SetBattleFlagBits, 0x800000, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master1_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_master1_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mac_master3_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mac_master3_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_mac_master1_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 2)
    Set(GameFlag(102), 1)
    Call(SetBattleFlagBits, 0x800000, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_watt_lee_EVS_HandlePhase = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(12)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfGt(LVar0, 0)
                Sub(LVar0, 1)
                Call(SetActorVar, ACTOR_SELF, 2, LVar0)
                BreakSwitch
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xE000C)
            Call(b_area_mac_watt_lee_WattFXRemove)
            ExecWait(TTYD64_mac_EVS_Lee_LoseDisguise)
            Return
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lakilester_lee_EVS_HandlePhase = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(12)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfGt(LVar0, 0)
                Sub(LVar0, 1)
                Call(SetActorVar, ACTOR_SELF, 2, LVar0)
                BreakSwitch
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xB0012)
            ExecWait(TTYD64_mac_EVS_Lee_LoseDisguise)
            Return
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lakilester_lee_EVS_HandlePhase_8022FF9C = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(12)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfGt(LVar0, 0)
                Sub(LVar0, 1)
                Call(SetActorVar, ACTOR_SELF, 2, LVar0)
                BreakSwitch
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x10000A)
            ExecWait(TTYD64_mac_EVS_Lee_LoseDisguise)
            Return
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lakilester_lee_EVS_HandlePhase_80230070 = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(12)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfGt(LVar0, 0)
                Sub(LVar0, 1)
                Call(SetActorVar, ACTOR_SELF, 2, LVar0)
                BreakSwitch
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000D)
            ExecWait(TTYD64_mac_EVS_Lee_LoseDisguise)
            Return
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master3_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_master2_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mac_master3_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mac_master3_EVS_HandleEvent_8022D438))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_mac_master2_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 2)
    Call(SetBattleFlagBits, 0x800000, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master3_EVS_Init_80230218 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_master3_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mac_master3_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mac_master3_EVS_HandleEvent_8022D0D0))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_mac_master3_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 2)
    Call(SetBattleFlagBits, 0x800000, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lakilester_lee_EVS_HandlePhase_802302EC = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(12)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfGt(LVar0, 0)
                Sub(LVar0, 1)
                Call(SetActorVar, ACTOR_SELF, 2, LVar0)
                BreakSwitch
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(TTYD64_mac_EVS_Lee_LoseDisguise)
            Return
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lakilester_lee_EVS_HandlePhase_802303C0 = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(12)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfGt(LVar0, 0)
                Sub(LVar0, 1)
                Call(SetActorVar, ACTOR_SELF, 2, LVar0)
                BreakSwitch
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(TTYD64_mac_EVS_Lee_LoseDisguise)
            Return
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lakilester_lee_EVS_HandlePhase_80230494 = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(12)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfGt(LVar0, 0)
                Sub(LVar0, 1)
                Call(SetActorVar, ACTOR_SELF, 2, LVar0)
                BreakSwitch
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0011)
            ExecWait(TTYD64_mac_EVS_Lee_LoseDisguise)
            Return
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lakilester_lee_EVS_HandlePhase_80230568 = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(12)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfGt(LVar0, 0)
                Sub(LVar0, 1)
                Call(SetActorVar, ACTOR_SELF, 2, LVar0)
                BreakSwitch
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(TTYD64_mac_EVS_Lee_LoseDisguise)
            Return
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_master2_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    Switch(LVar0)
        CaseLt(20)
            ExecWait(TTYD64_mac_master3_EVS_Attack_StrikeTwice_8021FF4C)
        CaseDefault
            ExecWait(TTYD64_mac_master3_EVS_Attack_StrikeOnce)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_kooper_lee_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_kooper_lee_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mac_kooper_lee_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mac_kooper_lee_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_mac_lakilester_lee_EVS_HandlePhase_80230494))
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_chan_EVS_Init = {
    ExecWait(TTYD64_mac_chan_EVS_SetInitialState)
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mac_chan_EVS_HandleEvent_Initial))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_mac_chan_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetBattleFlagBits, 0x800000, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lee_EVS_TakeTurn = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_mac_lee_EVS_Move_CopyPartner)
        CaseEq(1)
        CaseEq(2)
            ExecWait(TTYD64_mac_lee_EVS_Attack_FlyingTackle)
        CaseEq(3)
            Call(SetActorVar, ACTOR_SELF, 8, 2)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lakilester_lee_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_goombario_lee_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mac_master3_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mac_sushie_lee_EVS_HandleEvent_80228E00))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_mac_lakilester_lee_EVS_HandlePhase_80230568))
    Call(SetActorVar, ACTOR_SELF, 2, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lakilester_lee_EVS_Init_8023151C = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_bow_lee_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mac_master3_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mac_bow_lee_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_mac_lakilester_lee_EVS_HandlePhase_802303C0))
    Call(SetActorVar, ACTOR_SELF, 2, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lakilester_lee_EVS_Init_80231594 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_sushie_lee_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mac_master3_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mac_sushie_lee_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_mac_lakilester_lee_EVS_HandlePhase_802302EC))
    Call(SetActorVar, ACTOR_SELF, 2, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lakilester_lee_EVS_Init_8023160C = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_parakarry_lee_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mac_master3_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mac_parakarry_lee_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_mac_lakilester_lee_EVS_HandlePhase_80230070))
    Call(SetActorVar, ACTOR_SELF, 2, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lakilester_lee_EVS_Init_80231684 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_watt_lee_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mac_watt_lee_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_mac_watt_lee_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_mac_watt_lee_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 2, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lakilester_lee_EVS_Init_802316FC = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_bombette_lee_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mac_master3_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mac_bombette_lee_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_mac_lakilester_lee_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 2, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mac_lakilester_lee_EVS_Init_80231774 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mac_lakilester_lee_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mac_master3_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_mac_lakilester_lee_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_mac_lakilester_lee_EVS_HandlePhase_8022FF9C))
    Call(SetActorVar, ACTOR_SELF, 2, 1)
    Return
    End
};
// clang-format on

Battle TTYD64_mac_Formations[] = {
    { .name = "\301\247\363",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_mac_Formation_00,
      .stage = &b_area_mac_mac_02,
      .onBattleStart = NULL },
    { .name = "\352\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_mac_Formation_01,
      .stage = &b_area_mac_mac_02,
      .onBattleStart = NULL },
    { .name = "\267\267\347\374 ]n\021",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_mac_Formation_02,
      .stage = &b_area_mac_mac_02,
      .onBattleStart = NULL },
    { .name = "\267\267\347\374 ]n\022",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_mac_Formation_03,
      .stage = &b_area_mac_mac_02,
      .onBattleStart = NULL },
    { .name = "\267\267\347\374 ]n\023",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_mac_Formation_04,
      .stage = &b_area_mac_mac_02,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_mac_goombario_lee_EVS_TakeTurn = {
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        ExecWait(TTYD64_mac_goombario_lee_EVS_Move_Tattle)
    Else
        ExecWait(TTYD64_mac_goombario_lee_EVS_Attack_Headbonk)
    EndIf
    Return
    End
};
// clang-format on

s32 TTYD64_mac_chan_UprightAnims[] = {
    1,  0xA30001, 7, 0xA30000, 6, 0xA3000A, 9, 0xA30001, 8, 0xA30000,
    11, 0xA30001, 5, 0xA30000, 4, 0xA3000B, 3, 0xA3000B, 0,
};

s32 TTYD64_mac_goombario_lee_DefaultAnims[] = {
    1, 0x90001, 7, 0x90000, 6, 0x90000, 9, 0x90001, 8, 0x90000, 11, 0x90001, 5, 0x90000, 4, 0x90014, 3, 0x90014, 0,
};

s32 TTYD64_mac_bombette_lee_DefaultAnims[] = {
    1, 0xB0004, 7, 0xB0000, 6, 0xB0000, 9, 0xB0004, 8, 0xB0000, 11, 0xB0004, 5, 0xB0000, 4, 0xB001E, 3, 0xB001E, 0,
};

s32 TTYD64_mac_lee_DefaultAnims[] = {
    1,  0xA40002, 7, 0xA40000, 6, 0xA4000E, 9, 0xA40002, 8, 0xA40000,
    11, 0xA40002, 5, 0xA40000, 4, 0xA4000F, 4, 0xA4000F, 0,
};

s32 TTYD64_mac_lakilester_lee_DefaultAnims[] = {
    1,  0x100001, 7, 0x100000, 6, 0x100000, 9, 0x100001, 8, 0x100000,
    11, 0x100001, 5, 0x100000, 4, 0x100008, 3, 0x100001, 0,
};

s32 TTYD64_mac_watt_lee_DefaultAnims[] = {
    1, 0xE0001, 7, 0xE0000, 6, 0xE0000, 9, 0xE0001, 8, 0xE0000, 11, 0xE0001, 5, 0xE0000, 4, 0xE000F, 3, 0xE000F, 0,
};

s32 TTYD64_mac_kooper_lee_ToppledAnims[] = {
    1, 0xA0019, 7, 0xA0003, 6, 0xA0003, 9, 0xA0019, 8, 0xA0003, 11, 0xA0019, 5, 0xA0003, 4, 0xA0019, 3, 0xA0019, 0,
};

s32 TTYD64_mac_master3_AscendedAnims[] = {
    1,  0xA20006, 7, 0xA20001, 6, 0xA2001D, 9, 0xA20001, 8, 0xA20001,
    11, 0xA20001, 5, 0xA20001, 4, 0xA2001F, 4, 0xA2001F, 0,
};

s32 TTYD64_mac_kooper_lee_DefaultAnims[] = {
    1, 0xA0004, 7, 0xA0000, 6, 0xA0000, 9, 0xA0004, 8, 0xA0000, 11, 0xA0004, 5, 0xA0000, 4, 0xA001C, 3, 0xA001C, 0,
};

s32 TTYD64_mac_sushie_lee_DefaultAnims[] = {
    1, 0xF0001, 7, 0xF0000, 6, 0xF0000, 9, 0xF0001, 8, 0xF0000, 11, 0xF0001, 5, 0xF0000, 4, 0xF0010, 3, 0xF0010, 0,
};

s32 TTYD64_mac_master3_AscendedAnims_80231DD0[] = {
    1,  0xA20006, 7, 0xA20001, 6, 0xA2001D, 9, 0xA20001, 8, 0xA20001,
    11, 0xA20001, 5, 0xA20001, 4, 0xA2001F, 4, 0xA2001F, 0,
};

s32 TTYD64_mac_chan_DefaultAnims[] = {
    1,  0xA30001, 7, 0xA30000, 6, 0xA3000A, 9, 0xA30001, 8, 0xA30000,
    11, 0xA30001, 5, 0xA30000, 4, 0xA3000B, 3, 0xA3000B, 0,
};

s32 TTYD64_mac_bow_lee_DefaultAnims[] = {
    1, 0xD0001, 7, 0xD0000, 6, 0xD0000, 9, 0xD0001, 8, 0xD0000, 11, 0xD0001, 5, 0xD0000, 4, 0xD001A, 3, 0xD001A, 0,
};

s32 TTYD64_mac_master3_BaseAnims[] = {
    1,  0xA20005, 7, 0xA20000, 6, 0xA2001C, 9, 0xA20000, 8, 0xA20000,
    11, 0xA20000, 5, 0xA20000, 4, 0xA2001E, 4, 0xA2001E, 0,
};

s32 TTYD64_mac_master3_BaseAnims_80232030[] = {
    1,  0xA20005, 7, 0xA20000, 6, 0xA2001C, 9, 0xA20000, 8, 0xA20000,
    11, 0xA20000, 5, 0xA20000, 4, 0xA2001E, 4, 0xA2001E, 0,
};

s32 TTYD64_mac_master3_BaseAnims_8023207C[] = {
    1,  0xA20005, 7, 0xA20000, 6, 0xA2001C, 9, 0xA20000, 8, 0xA20000,
    11, 0xA20000, 5, 0xA20000, 4, 0xA2001E, 4, 0xA2001E, 0,
};

s32 TTYD64_mac_parakarry_lee_DefaultAnims[] = {
    1, 0xC0001, 7, 0xC0000, 6, 0xC0000, 9, 0xC0001, 8, 0xC0000, 11, 0xC0001, 5, 0xC0000, 4, 0xC0001, 3, 0xC0001, 0,
};

ActorPartBlueprint TTYD64_mac_watt_lee_ActorParts[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -1, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_mac_watt_lee_DefaultAnims,
        .defenseTable = b_area_mac_watt_lee_DefenseTable,
        .eventFlags = 0x80,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800001,
        .index = 2,
        .posOffset = { 0, 50, 0 },
        .targetOffset = { -1, -30 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_mac_watt_lee_DefenseTable,
        .eventFlags = 0x80,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_mac_bow_lee_ActorParts[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_mac_bow_lee_DefaultAnims,
        .defenseTable = b_area_mac_master2_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800001,
        .index = 2,
        .posOffset = { 0, 50, 0 },
        .targetOffset = { 0, -26 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_mac_master2_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_mac_master3_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -5, 28 },
        .opacity = 255,
        .idleAnimations = TTYD64_mac_master3_BaseAnims_80232030,
        .defenseTable = b_area_mac_master3_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 2, -7 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = TTYD64_mac_master3_BaseAnims_80232030,
        .defenseTable = b_area_mac_master3_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_mac_lakilester_lee_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -3, 33 },
        .opacity = 255,
        .idleAnimations = TTYD64_mac_lakilester_lee_DefaultAnims,
        .defenseTable = b_area_mac_master2_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -2, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_mac_lakilester_lee_SpinyAnims,
        .defenseTable = b_area_mac_master2_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_mac_parakarry_lee_ActorParts[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -3, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_mac_parakarry_lee_DefaultAnims,
        .defenseTable = b_area_mac_master3_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -16 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800001,
        .index = 2,
        .posOffset = { 0, 50, 0 },
        .targetOffset = { -3, -18 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_mac_master3_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -16 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_mac_chan_ToppledAnims[] = {
    1, 0xA30002, 7, 0xA3000F, 6, 0xA30010, 9, 0xA30002, 8, 0xA3000F, 11, 0xA30002, 4, 0xA30011, 3, 0xA30011, 0,
};

ActorBlueprint TTYD64_mac_watt_lee = {
    .flags = 0x200,
    .maxHP = 20,
    .type = 0x84,
    .level = 0,
    .partCount = 2,
    .partsData = TTYD64_mac_watt_lee_ActorParts,
    .initScript = &TTYD64_mac_lakilester_lee_EVS_Init_80231684,
    .statusTable = b_area_mac_lakilester_lee_StatusTable,
    .escapeChance = 100,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 34, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_mac_bow_lee = {
    .flags = 0x200,
    .maxHP = 20,
    .type = 0x83,
    .level = 0,
    .partCount = 2,
    .partsData = TTYD64_mac_bow_lee_ActorParts,
    .initScript = &TTYD64_mac_lakilester_lee_EVS_Init_8023151C,
    .statusTable = b_area_mac_lakilester_lee_StatusTable,
    .escapeChance = 100,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 36, 29 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_mac_master2 = {
    .flags = 0x0,
    .maxHP = 75,
    .type = 0x7B,
    .level = 0,
    .partCount = 1,
    .partsData = TTYD64_mac_master3_ActorParts_802327A4,
    .initScript = &TTYD64_mac_master3_EVS_Init,
    .statusTable = b_area_mac_master2_StatusTable,
    .escapeChance = 100,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 30, 35 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 30 },
    .statusTextOffset = { 10, 30 },
};

ActorBlueprint TTYD64_mac_master1 = {
    .flags = 0x0,
    .maxHP = 50,
    .type = 0x7A,
    .level = 0,
    .partCount = 1,
    .partsData = TTYD64_mac_master3_ActorParts_802326A8,
    .initScript = &TTYD64_mac_master1_EVS_Init,
    .statusTable = b_area_mac_master1_StatusTable,
    .escapeChance = 100,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 30, 35 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 30 },
    .statusTextOffset = { 10, 30 },
};

ActorBlueprint TTYD64_mac_master3 = {
    .flags = 0x0,
    .maxHP = 99,
    .type = 0x7C,
    .level = 0,
    .partCount = 2,
    .partsData = TTYD64_mac_master3_ActorParts,
    .initScript = &TTYD64_mac_master3_EVS_Init_80230218,
    .statusTable = b_area_mac_master3_StatusTable,
    .escapeChance = 100,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 70,
    .coinReward = 0,
    .size = { 30, 35 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 30 },
    .statusTextOffset = { 10, 30 },
};

ActorBlueprint TTYD64_mac_kooper_lee = {
    .flags = 0x0,
    .maxHP = 20,
    .type = 0x80,
    .level = 0,
    .partCount = 1,
    .partsData = TTYD64_mac_kooper_lee_ActorParts,
    .initScript = &TTYD64_mac_kooper_lee_EVS_Init,
    .statusTable = b_area_mac_lakilester_lee_StatusTable,
    .escapeChance = 100,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 32, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_mac_sushie_lee = {
    .flags = 0x0,
    .maxHP = 20,
    .type = 0x85,
    .level = 0,
    .partCount = 1,
    .partsData = TTYD64_mac_sushie_lee_ActorParts,
    .initScript = &TTYD64_mac_lakilester_lee_EVS_Init_80231594,
    .statusTable = b_area_mac_lakilester_lee_StatusTable,
    .escapeChance = 100,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 37, 26 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_mac_chan = {
    .flags = 0x800,
    .maxHP = 15,
    .type = 0x7D,
    .level = 0,
    .partCount = 1,
    .partsData = TTYD64_mac_chan_ActorParts,
    .initScript = &TTYD64_mac_chan_EVS_Init,
    .statusTable = b_area_mac_chan_StatusTable,
    .escapeChance = 100,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 0,
    .size = { 22, 18 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_mac_lakilester_lee = {
    .flags = 0x200,
    .maxHP = 20,
    .type = 0x86,
    .level = 0,
    .partCount = 2,
    .partsData = TTYD64_mac_lakilester_lee_ActorParts,
    .initScript = &TTYD64_mac_lakilester_lee_EVS_Init_80231774,
    .statusTable = b_area_mac_lakilester_lee_StatusTable,
    .escapeChance = 100,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 44, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_mac_bombette_lee = {
    .flags = 0x0,
    .maxHP = 20,
    .type = 0x81,
    .level = 0,
    .partCount = 1,
    .partsData = TTYD64_mac_bombette_lee_ActorParts,
    .initScript = &TTYD64_mac_lakilester_lee_EVS_Init_802316FC,
    .statusTable = b_area_mac_lakilester_lee_StatusTable,
    .escapeChance = 100,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 30, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_mac_goombario_lee = {
    .flags = 0x0,
    .maxHP = 20,
    .type = 0x7F,
    .level = 0,
    .partCount = 1,
    .partsData = TTYD64_mac_goombario_lee_ActorParts,
    .initScript = &TTYD64_mac_lakilester_lee_EVS_Init,
    .statusTable = b_area_mac_lakilester_lee_StatusTable,
    .escapeChance = 100,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 29, 26 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_mac_lee = {
    .flags = 0x0,
    .maxHP = 20,
    .type = 0x7E,
    .level = 0,
    .partCount = 1,
    .partsData = TTYD64_mac_lee_ActorParts,
    .initScript = &TTYD64_mac_lee_EVS_Init,
    .statusTable = b_area_mac_lee_StatusTable,
    .escapeChance = 100,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 36, 36 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_mac_parakarry_lee = {
    .flags = 0x200,
    .maxHP = 20,
    .type = 0x82,
    .level = 0,
    .partCount = 2,
    .partsData = TTYD64_mac_parakarry_lee_ActorParts,
    .initScript = &TTYD64_mac_lakilester_lee_EVS_Init_8023160C,
    .statusTable = b_area_mac_lakilester_lee_StatusTable,
    .escapeChance = 100,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 38, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorPartBlueprint TTYD64_mac_master3_ActorParts_802326A8[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -5, 28 },
        .opacity = 255,
        .idleAnimations = TTYD64_mac_master3_BaseAnims,
        .defenseTable = b_area_mac_master2_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 2, -7 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_mac_lee_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -5, 25 },
        .opacity = 255,
        .idleAnimations = TTYD64_mac_lee_DefaultAnims,
        .defenseTable = b_area_mac_lakilester_lee_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -2, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_mac_sushie_lee_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_mac_sushie_lee_DefaultAnims,
        .defenseTable = b_area_mac_master2_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_mac_bombette_lee_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 22 },
        .opacity = 255,
        .idleAnimations = TTYD64_mac_bombette_lee_DefaultAnims,
        .defenseTable = b_area_mac_master2_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -2, -7 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_mac_kooper_lee_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_mac_kooper_lee_DefaultAnims,
        .defenseTable = b_area_mac_master3_DefenseTable,
        .eventFlags = 0x1000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -16 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_mac_chan_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 16 },
        .opacity = 255,
        .idleAnimations = TTYD64_mac_chan_DefaultAnims,
        .defenseTable = b_area_mac_chan_UprightDefenseTable,
        .eventFlags = 0x1000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 1, 7 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_mac_master3_ActorParts_802327A4[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -5, 28 },
        .opacity = 255,
        .idleAnimations = TTYD64_mac_master3_BaseAnims_8023207C,
        .defenseTable = b_area_mac_master2_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 2, -7 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_mac_goombario_lee_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_mac_goombario_lee_DefaultAnims,
        .defenseTable = b_area_mac_lakilester_lee_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -9 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_mac_parakarry_lee_EVS_TakeTurn = {
    ExecWait(TTYD64_mac_parakarry_lee_EVS_Attack_SkyDive)
    Return
    End
};
// clang-format on

FormationRow TTYD64_mac_LeeGoombarioFormation[] = {
    { .actor = &TTYD64_mac_goombario_lee,
      .home = { .vec = &b_area_mac_Lee_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_mac_Formation_00[] = {
    { .actor = &TTYD64_mac_chan, .home = { .index = 2 }, .priority = 10, .var0 = 0, .var1 = 0, .var2 = 0, .var3 = 0 },
};

FormationRow TTYD64_mac_Formation_01[] = {
    { .actor = &TTYD64_mac_lee, .home = { .index = 2 }, .priority = 10, .var0 = 0, .var1 = 0, .var2 = 0, .var3 = 0 },
};

FormationRow TTYD64_mac_Formation_04[] = {
    { .actor = &TTYD64_mac_master3,
      .home = { .index = 2 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_mac_Formation_02[] = {
    { .actor = &TTYD64_mac_master1,
      .home = { .index = 2 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_mac_Formation_03[] = {
    { .actor = &TTYD64_mac_master2,
      .home = { .index = 2 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_mac_LeeBowFormation[] = {
    { .actor = &TTYD64_mac_bow_lee,
      .home = { .vec = &b_area_mac_Lee_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_mac_LeeSushieFormation[] = {
    { .actor = &TTYD64_mac_sushie_lee,
      .home = { .vec = &b_area_mac_Lee_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_mac_LeeLakilesterFormation[] = {
    { .actor = &TTYD64_mac_lakilester_lee,
      .home = { .vec = &b_area_mac_Lee_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_mac_LeeBombetteFormation[] = {
    { .actor = &TTYD64_mac_bombette_lee,
      .home = { .vec = &b_area_mac_Lee_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_mac_LeeParakarryFormation[] = {
    { .actor = &TTYD64_mac_parakarry_lee,
      .home = { .vec = &b_area_mac_Lee_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_mac_LeeKooperFormation[] = {
    { .actor = &TTYD64_mac_kooper_lee,
      .home = { .vec = &b_area_mac_Lee_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_mac_LeeWattFormation[] = {
    { .actor = &TTYD64_mac_watt_lee,
      .home = { .vec = &b_area_mac_Lee_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

void TTYD64_InstallBattles_mac(void) {
    Mod_SetBattleList("TTYD64", 3, TTYD64_mac_Formations);
}
