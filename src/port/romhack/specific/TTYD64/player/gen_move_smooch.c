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

extern EvtScript battle_move_smooch_EVS_UsePower;
extern EvtScript battle_move_smooch_EVS_StarPower_SpiritDeparts;
extern EvtScript battle_move_smooch_EVS_StarPower_SpiritSummoned;
extern EvtScript battle_move_smooch_EVS_StarPower_WishForSpirit;
extern s32 battle_move_smooch_RecoverEffectPositions[];
API_CALLABLE(GetActorPos);
API_CALLABLE(JumpToGoal);
API_CALLABLE(NpcFlyTo);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerHopToGoal);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(PlayerYieldTurn);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcRotation);
API_CALLABLE(ShowStartRecoveryShimmer);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(battle_move_smooch_AddHP);
API_CALLABLE(battle_move_smooch_FadeBackgroundLighten);
API_CALLABLE(battle_move_smooch_SpawnRecoverFX);
API_CALLABLE(battle_move_smooch_SpawnStarSparkleFX);
EvtScript TTYD64_battle_move_smooch_EVS_UsePower;
EvtScript TTYD64_battle_move_smooch_EVS_802A252C;
EvtScript TTYD64_battle_move_smooch_EVS_802A30AC;
EvtScript TTYD64_battle_move_smooch_EVS_802A3418;

// clang-format off
EvtScript TTYD64_battle_move_smooch_EVS_UsePower = {
    ExecWait(TTYD64_battle_move_smooch_EVS_802A252C)
    Return
    End
};

EvtScript TTYD64_battle_move_smooch_EVS_802A252C = {
    ExecWait(battle_move_smooch_EVS_StarPower_WishForSpirit)
    SetConst(LVar0, 1900544)
    ExecWait(battle_move_smooch_EVS_StarPower_SpiritSummoned)
    Wait(16)
    Thread
        Wait(10)
        Call(SetNpcRotation, 100, 0, 180, 0)
        Wait(1)
        Call(SetNpcRotation, 100, 0, 150, 0)
        Wait(1)
        Call(SetNpcRotation, 100, 0, 120, 0)
        Wait(1)
        Call(SetNpcRotation, 100, 0, 90, 0)
        Wait(1)
        Call(SetNpcRotation, 100, 0, 60, 0)
        Wait(1)
        Call(SetNpcRotation, 100, 0, 30, 0)
        Wait(1)
        Call(SetNpcRotation, 100, 0, 0, 0)
    EndThread
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar1, 25)
    Add(LVar0, 30)
    Call(NpcFlyTo, 100, LVar0, LVar1, LVar2, 20, 0, 10)
    Wait(15)
    Call(SetNpcAnimation, 100, 1900545)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 15)
    Add(LVar1, 15)
    Add(LVar2, -5)
    Call(NpcFlyTo, 100, LVar0, LVar1, LVar2, 10, 0, 10)
    Call(PlaySound, SOUND_SMOOCH)
    Thread
        Call(PlayEffect_impl, 64, 2, LVar0, LVar1, LVar2, 1, 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(2)
        UseBuf(battle_move_smooch_RecoverEffectPositions)
        Loop(5)
            BufRead2(LVar5, LVar6)
            Set(LVar3, LVar0)
            Set(LVar4, LVar1)
            Add(LVar3, LVar5)
            Add(LVar4, LVar6)
            Call(PlayEffect_impl, 64, 2, LVar3, LVar4, LVar2, 1, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(2)
        EndLoop
    EndThread
    Thread
        Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Add(LVar1, 15)
        Add(LVar0, 5)
        Call(battle_move_smooch_SpawnStarSparkleFX, LVar0, LVar1, LVar2)
        Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Add(LVar1, 20)
        Add(LVar0, 25)
        Call(NpcFlyTo, 100, LVar0, LVar1, LVar2, 10, 0, 10)
    EndThread
    Call(SetAnimation, ACTOR_PLAYER, 0, 65582)
    Wait(12)
    Thread
        ExecWait(battle_move_smooch_EVS_StarPower_SpiritDeparts)
    EndThread
    Thread
        Call(TTYD64_GetPartnerHP_API, LVar0)
        IfGt(LVar0, 0)
            Exec(TTYD64_battle_move_smooch_EVS_802A30AC)
        EndIf
        Loop(2)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0996), Float(1.0), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2), Float(0.95), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998), Float(0.9), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.3496), Float(0.8496), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.3799), Float(0.7998), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.4), Float(0.7998), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998), Float(0.8496), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2), Float(0.9), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0996), Float(0.95), Float(1.0))
            Wait(1)
        EndLoop
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(1.0996), Float(1.0), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(1.2), Float(0.95), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(1.2998), Float(0.9), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(1.3496), Float(0.8496), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(1.3799), Float(0.7998), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(1.4), Float(0.7998), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(0.9), Float(1.2998), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(0.9), Float(1.2), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(0.95), Float(1.0996), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
        Wait(1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    EndThread
    Loop(10)
        Wait(3)
    EndLoop
    Call(UseBattleCamPreset, 2)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 0)
    Add(LVar1, 35)
    Call(battle_move_smooch_SpawnRecoverFX, LVar0, LVar1, LVar2, 20)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar1, 25)
    Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, 20)
    Call(battle_move_smooch_AddHP, 20)
    Thread
        Call(battle_move_smooch_FadeBackgroundLighten)
    EndThread
    Call(PlayerYieldTurn)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_LONG_PLAYER_JUMP)
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfGt(LVar0, 0)
        Exec(TTYD64_battle_move_smooch_EVS_802A3418)
        Call(TTYD64_Heal_PlayerTeam, 256, 20)
        Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Add(LVar1, 35)
        Call(battle_move_smooch_SpawnRecoverFX, LVar0, LVar1, LVar2, 20)
        Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Add(LVar1, 25)
        Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, 20)
    EndIf
    Call(SetActorJumpGravity, ACTOR_PLAYER, Float(1.0))
    Call(SetActorSpeed, ACTOR_PLAYER, Float(1.0))
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 65545)
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(PlayerHopToGoal, 20, 0, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65545)
    Wait(4)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Return
    End
};

EvtScript TTYD64_battle_move_smooch_EVS_802A30AC = {
    Loop(2)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0996), Float(1.0), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.2), Float(0.95), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.2998), Float(0.9), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.3496), Float(0.8496), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.3799), Float(0.7998), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.4), Float(0.7998), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.2998), Float(0.8496), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.2), Float(0.9), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0996), Float(0.95), Float(1.0))
        Wait(1)
    EndLoop
    Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_PARTNER, Float(1.0996), Float(1.0), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_PARTNER, Float(1.2), Float(0.95), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_PARTNER, Float(1.2998), Float(0.9), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_PARTNER, Float(1.3496), Float(0.8496), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_PARTNER, Float(1.3799), Float(0.7998), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_PARTNER, Float(1.4), Float(0.7998), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_PARTNER, Float(0.9), Float(1.2998), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_PARTNER, Float(0.9), Float(1.2), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_PARTNER, Float(0.95), Float(1.0996), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    Wait(1)
    Return
    End
};

EvtScript TTYD64_battle_move_smooch_EVS_802A3418 = {
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.0))
    Call(SetActorSpeed, ACTOR_PARTNER, Float(1.0))
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 20, false, true, false)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_smooch(void) {
    Mod_ReplaceScript("TTYD64", &battle_move_smooch_EVS_UsePower, &TTYD64_battle_move_smooch_EVS_UsePower);
}
