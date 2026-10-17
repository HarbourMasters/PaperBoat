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
#include "port/romhack/specific/TTYD64/player/player_internal.h"

extern EvtScript battle_move_peach_focus_EVS_UsePower;
API_CALLABLE(ActorSpeak);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(ModifyActorDecoration);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(PlayerYieldTurn);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(battle_move_peach_focus_FadeBackgroundDarken);
API_CALLABLE(battle_move_peach_focus_FadeBackgroundLighten);
API_CALLABLE(battle_move_peach_focus_IncreaseTwinkDefense);
API_CALLABLE(battle_move_peach_focus_SpawnStarSparkleFX);
API_CALLABLE(battle_move_peach_focus_SpawnWishSparkleFX);
EvtScript TTYD64_battle_move_peach_focus_EVS_UsePower;

// clang-format off
EvtScript TTYD64_battle_move_peach_focus_EVS_UsePower = {
    Call(UseBattleCamPreset, 69)
    Wait(10)
    Call(SetAnimation, ACTOR_PLAYER, 0, 655363)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 16)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(4.0))
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_PLAYER, 0, 786445)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, -105, -7, 0)
    Call(SetBattleCamDist, 213)
    Call(MoveBattleCamOver, 60)
    Wait(10)
    Call(SetAnimation, ACTOR_PLAYER, 0, 851983)
    Call(PlaySound, SOUND_BEGIN_WISH)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(battle_move_peach_focus_SpawnStarSparkleFX, LVar0, LVar1, LVar2)
    Call(battle_move_peach_focus_FadeBackgroundDarken)
    Call(GetActorVar, ACTOR_PARTNER, 0, LVar0)
    IfEq(LVar0, 0)
        Call(ActorSpeak, 1245334, 0, 0, 851983, 851983)
    EndIf
    Wait(20)
    Call(SetAnimation, ACTOR_PLAYER, 0, 655361)
    Wait(10)
    Call(PlaySound, 8273)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(battle_move_peach_focus_SpawnWishSparkleFX, LVar0, LVar1, LVar2)
    Wait(30)
    Call(PlaySound, 8275)
    Call(GetActorVar, ACTOR_PARTNER, 0, LVar0)
    Add(LVar0, 1)
    Call(SetActorVar, ACTOR_PARTNER, 0, LVar0)
    Call(ModifyActorDecoration, 256, 1, 0, LVar0, 0, 0, 0)
    Call(GetActorVar, ACTOR_PARTNER, 1, LVar0)
    Call(battle_move_peach_focus_IncreaseTwinkDefense)
    Wait(10)
    Call(UseBattleCamPreset, 2)
    Call(SetActorYaw, ACTOR_SELF, 150)
    Wait(1)
    Call(SetActorYaw, ACTOR_SELF, 120)
    Wait(1)
    Call(SetActorYaw, ACTOR_SELF, 90)
    Wait(1)
    Call(SetActorYaw, ACTOR_SELF, 60)
    Wait(1)
    Call(SetActorYaw, ACTOR_SELF, 30)
    Wait(1)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Wait(1)
    Call(PlayerYieldTurn)
    Call(battle_move_peach_focus_FadeBackgroundLighten)
    Wait(15)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 655363)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 655362)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_peach_focus(void) {
    Mod_ReplaceScript("TTYD64", &battle_move_peach_focus_EVS_UsePower, &TTYD64_battle_move_peach_focus_EVS_UsePower);
}
