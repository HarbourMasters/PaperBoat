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

extern EvtScript battle_move_focus_EVS_UsePower;
extern EvtScript battle_move_focus_EVS_StarPower_WishForSpirit;
API_CALLABLE(EnableBattleStatusBar);
API_CALLABLE(GetOwnerID);
API_CALLABLE(PartnerYieldTurn);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(PlayerYieldTurn);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(ShowMessageBox);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(WaitForMessageBoxDone);
API_CALLABLE(battle_move_focus_FadeBackgroundLighten);
API_CALLABLE(battle_move_focus_RestoreStarPowerFromPlayer);
API_CALLABLE(battle_move_focus_SetPartnerWishAnim);
EvtScript TTYD64_battle_move_focus_EVS_UsePower;

// clang-format off
EvtScript TTYD64_battle_move_focus_EVS_UsePower = {
    ExecWait(battle_move_focus_EVS_StarPower_WishForSpirit)
    Call(EnableBattleStatusBar, 1)
    Call(GetOwnerID, LVarA)
    IfEq(LVarA, 0)
        Call(PlaySound, 8275)
        Call(battle_move_focus_RestoreStarPowerFromPlayer)
        Wait(30)
        Call(battle_move_focus_FadeBackgroundLighten)
        Call(UseBattleCamPreset, 2)
        Switch(LVar0)
            CaseEq(0)
                Call(ShowMessageBox, 26, 60)
            CaseEq(1)
                Call(ShowMessageBox, 27, 60)
            CaseEq(2)
                Call(ShowMessageBox, 28, 60)
        EndSwitch
        Call(WaitForMessageBoxDone)
        Call(PlayerYieldTurn)
        Call(SetGoalToHome, ACTOR_PLAYER)
        Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
        Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
        Call(PlayerRunToGoal, 0)
        Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Else
        Call(PlaySound, 8275)
        Call(TTYD64_Function_PartnerFocus)
        Wait(30)
        Call(battle_move_focus_FadeBackgroundLighten)
        Call(UseBattleCamPreset, 2)
        Switch(LVar0)
            CaseEq(0)
                Call(ShowMessageBox, 26, 60)
            CaseEq(1)
                Call(ShowMessageBox, 27, 60)
            CaseEq(2)
                Call(ShowMessageBox, 28, 60)
        EndSwitch
        Call(WaitForMessageBoxDone)
        Call(PartnerYieldTurn)
        Call(SetGoalToHome, ACTOR_PARTNER)
        Call(SetActorSpeed, ACTOR_PARTNER, Float(8.0))
        Call(battle_move_focus_SetPartnerWishAnim, 3)
        Call(RunToGoal, ACTOR_PARTNER, 0)
        Call(battle_move_focus_SetPartnerWishAnim, 4)
    EndIf
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_focus(void) {
    Mod_ReplaceScript("TTYD64", &battle_move_focus_EVS_UsePower, &TTYD64_battle_move_focus_EVS_UsePower);
}
