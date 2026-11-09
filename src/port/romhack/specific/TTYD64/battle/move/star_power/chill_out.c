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

extern EvtScript battle_move_chill_out_EVS_UsePower;
extern EvtScript battle_move_chill_out_EVS_StarPower_EndWish;
extern EvtScript battle_move_chill_out_EVS_StarPower_SpiritDeparts;
extern EvtScript battle_move_chill_out_EVS_StarPower_SpiritSummoned;
extern EvtScript battle_move_chill_out_EVS_StarPower_WishForSpirit;
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(ItemCheckHit);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerDamageEnemy);
API_CALLABLE(PlayerYieldTurn);
API_CALLABLE(SetActorScaleModifier);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(ShowMessageBox);
API_CALLABLE(TTYD64_Player_starpower4_802A16F4);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(WaitForMessageBoxDone);
API_CALLABLE(battle_move_chill_out_CanChillOutHit);
API_CALLABLE(battle_move_chill_out_DidMoveHit);
API_CALLABLE(battle_move_chill_out_InitHitCheck);
API_CALLABLE(battle_move_chill_out_SpawnChillOutFX);
EvtScript TTYD64_battle_move_chill_out_EVS_UsePower;
EvtScript TTYD64_battle_move_chill_out_EVS_802A27C4;

// clang-format off
EvtScript TTYD64_battle_move_chill_out_EVS_UsePower = {
    ExecWait(TTYD64_battle_move_chill_out_EVS_802A27C4)
    Return
    End
};

EvtScript TTYD64_battle_move_chill_out_EVS_802A27C4 = {
    Call(battle_move_chill_out_InitHitCheck)
    ExecWait(battle_move_chill_out_EVS_StarPower_WishForSpirit)
    SetConst(LVar0, 1835009)
    ExecWait(battle_move_chill_out_EVS_StarPower_SpiritSummoned)
    Call(SetNpcAnimation, 100, 1835010)
    Wait(16)
    Call(UseBattleCamPreset, 3)
    Call(PlaySound, SOUND_CHILL_OUT)
    Call(InitTargetIterator)
    Label(10)
    Call(ItemCheckHit, LVar0, 0, 0, 0, 0)
    IfEq(LVar0, 6)
        Goto(11)
    EndIf
    Call(battle_move_chill_out_CanChillOutHit)
    IfEq(LVar0, 1)
        Call(GetOwnerTarget, LVarA, LVarB)
        Thread
            Loop(5)
                Call(SetActorScaleModifier, LVarA, Float(1.0), Float(1.0), Float(1.0))
                Wait(1)
                Call(SetActorScaleModifier, LVarA, Float(1.0996), Float(1.0), Float(1.0))
                Wait(1)
                Call(SetActorScaleModifier, LVarA, Float(1.2), Float(0.95), Float(1.0))
                Wait(1)
                Call(SetActorScaleModifier, LVarA, Float(1.2998), Float(0.9), Float(1.0))
                Wait(1)
                Call(SetActorScaleModifier, LVarA, Float(1.3496), Float(0.8496), Float(1.0))
                Wait(1)
                Call(SetActorScaleModifier, LVarA, Float(1.3799), Float(0.7998), Float(1.0))
                Wait(1)
                Call(SetActorScaleModifier, LVarA, Float(1.4), Float(0.7998), Float(1.0))
                Wait(1)
                Call(SetActorScaleModifier, LVarA, Float(1.2998), Float(0.8496), Float(1.0))
                Wait(1)
                Call(SetActorScaleModifier, LVarA, Float(1.2), Float(0.9), Float(1.0))
                Wait(1)
                Call(SetActorScaleModifier, LVarA, Float(1.0996), Float(0.95), Float(1.0))
                Wait(1)
            EndLoop
            Call(SetActorScaleModifier, LVarA, Float(1.0), Float(1.0), Float(1.0))
        EndThread
    EndIf
    Label(11)
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(10)
    EndIf
    Loop(30)
        Call(battle_move_chill_out_SpawnChillOutFX)
        Wait(2)
    EndLoop
    Call(ChooseNextTarget, -1, 0)
    Label(0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(ItemCheckHit, LVar0, 0, 0, 0, 0)
    IfEq(LVar0, 6)
        Goto(1)
    EndIf
    Call(battle_move_chill_out_CanChillOutHit)
    IfEq(LVar0, 1)
        Call(GetOwnerTarget, LVar0, 0)
        Call(TTYD64_AddAttackBoost, LVar0, -3, 5)
        Call(TTYD64_Player_starpower4_802A16F4)
    Else
        Call(PlayerDamageEnemy, LVar0, 0, 65535, 0, 0, 2080)
    EndIf
    Label(1)
    Wait(5)
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Wait(5)
    Call(battle_move_chill_out_DidMoveHit)
    IfEq(LVar0, 1)
        Call(ShowMessageBox, 44, 60)
    EndIf
    Call(PlayerYieldTurn)
    ExecWait(battle_move_chill_out_EVS_StarPower_SpiritDeparts)
    ExecWait(battle_move_chill_out_EVS_StarPower_EndWish)
    Call(battle_move_chill_out_DidMoveHit)
    IfEq(LVar0, 1)
        Call(WaitForMessageBoxDone)
    EndIf
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_chill_out(void) {
    Mod_ReplaceScript("TTYD64", &battle_move_chill_out_EVS_UsePower, &TTYD64_battle_move_chill_out_EVS_UsePower);
}
