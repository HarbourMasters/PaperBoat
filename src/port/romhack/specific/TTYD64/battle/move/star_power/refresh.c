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

extern EvtScript battle_move_refresh_EVS_UsePower;
extern EvtScript battle_move_refresh_EVS_StarPower_EndWish;
extern EvtScript battle_move_refresh_EVS_StarPower_WishForSpirit;
API_CALLABLE(CreateNpc);
API_CALLABLE(DeleteNpc);
API_CALLABLE(EnableNpcBlur);
API_CALLABLE(GetActorPos);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(NpcFlyTo);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerYieldTurn);
API_CALLABLE(SetForegroundModelsVisible);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcDecoration);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetNpcRotation);
API_CALLABLE(ShowStartRecoveryShimmer);
API_CALLABLE(TTYD64_Player_starpower1_ClearDebuffs);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseBattleCamPresetImmediately);
API_CALLABLE(battle_move_refresh_AddFP);
API_CALLABLE(battle_move_refresh_AddHP);
API_CALLABLE(battle_move_refresh_FlyAroundPlayer);
API_CALLABLE(battle_move_refresh_RemovePlayerDebuffs);
API_CALLABLE(battle_move_refresh_SetStarSpiritSize);
API_CALLABLE(battle_move_refresh_SpawnFlowerRecoverFX);
API_CALLABLE(battle_move_refresh_SpawnHeartRecoverFX);
API_CALLABLE(battle_move_refresh_SpawnStarSpiritArriveFX);
EvtScript TTYD64_battle_move_refresh_EVS_UsePower;
EvtScript TTYD64_battle_move_refresh_EVS_802A2944;
EvtScript TTYD64_battle_move_refresh_EVS_802A2C54;

// clang-format off
EvtScript TTYD64_battle_move_refresh_EVS_UsePower = {
    ExecWait(TTYD64_battle_move_refresh_EVS_802A2944)
    Return
    End
};

EvtScript TTYD64_battle_move_refresh_EVS_802A2944 = {
    ExecWait(battle_move_refresh_EVS_StarPower_WishForSpirit)
    SetConst(LVar0, 1638401)
    ExecWait(TTYD64_battle_move_refresh_EVS_802A2C54)
    Call(SetNpcAnimation, 100, 1638402)
    Wait(16)
    Thread
        Wait(10)
        Call(UseBattleCamPreset, 2)
    EndThread
    Call(PlaySound, SOUND_REFRESH)
    Call(EnableNpcBlur, 100, 1)
    Call(battle_move_refresh_FlyAroundPlayer, 100)
    Call(EnableNpcBlur, 100, 0)
    Call(DeleteNpc, 100)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 0)
    Add(LVar1, 35)
    Call(battle_move_refresh_SpawnHeartRecoverFX, LVar0, LVar1, LVar2, 5)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Add(LVar1, 25)
    Call(battle_move_refresh_SpawnFlowerRecoverFX, LVar0, LVar1, LVar2, 5)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar1, 25)
    Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, 5)
    Call(battle_move_refresh_AddHP, 5)
    Call(battle_move_refresh_AddFP, 5)
    Call(battle_move_refresh_RemovePlayerDebuffs)
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfGt(LVar0, 0)
        Call(TTYD64_Heal_PlayerTeam, 256, 5)
        Call(TTYD64_Player_starpower1_ClearDebuffs, 256)
        Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Add(LVar0, 20)
        Add(LVar1, 25)
        Call(battle_move_refresh_SpawnHeartRecoverFX, LVar0, LVar1, LVar2, 5)
        Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Add(LVar1, 25)
        Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, 5)
    EndIf
    Wait(30)
    Call(PlayerYieldTurn)
    ExecWait(battle_move_refresh_EVS_StarPower_EndWish)
    Return
    End
};

EvtScript TTYD64_battle_move_refresh_EVS_802A2C54 = {
    Wait(8)
    Call(SetForegroundModelsVisible, 0)
    Call(UseBattleCamPresetImmediately, 73)
    Call(MoveBattleCamOver, 1)
    Call(PlaySound, 8257)
    Call(CreateNpc, 100, LVar0)
    Call(battle_move_refresh_SetStarSpiritSize)
    Call(SetNpcFlagBits, 100, NPC_FLAG_IGNORE_CAMERA_FOR_YAW, true)
    Call(SetNpcPos, 100, -75, 150, 0)
    Call(SetNpcDecoration, 100, 0, 5)
    Call(battle_move_refresh_SpawnStarSpiritArriveFX, -75, 167, 0)
    Wait(10)
    Call(EnableNpcBlur, 100, 1)
    Set(LVar0, 0)
    Loop(8)
        Add(LVar0, 67)
        Call(SetNpcRotation, 100, 0, LVar0, 0)
        Wait(1)
    EndLoop
    Wait(10)
    Call(EnableNpcBlur, 100, 0)
    Thread
        Wait(10)
        Call(UseBattleCamPreset, 69)
    EndThread
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar1, 50)
    Call(TTYD64_GetPartnerHP_API, LVar3)
    IfGt(LVar3, 0)
        Call(TTYD64_GetMarioPos, LVar3)
        IfEq(LVar3, 0)
            Add(LVar0, 25)
        Else
            Sub(LVar0, 25)
        EndIf
    EndIf
    Call(NpcFlyTo, 100, LVar0, LVar1, LVar2, 30, 0, 10)
    Call(SetForegroundModelsVisible, 1)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_refresh(void) {
    Mod_ReplaceScript("TTYD64", &battle_move_refresh_EVS_UsePower, &TTYD64_battle_move_refresh_EVS_UsePower);
}
