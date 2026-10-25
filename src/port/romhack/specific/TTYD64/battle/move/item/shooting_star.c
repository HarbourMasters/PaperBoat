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

extern EvtScript battle_item_shooting_star_EVS_UseItem;
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetItemPower);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(ItemCheckHit);
API_CALLABLE(ItemDamageEnemy);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetTargetActor);
API_CALLABLE(ShakeCam);
API_CALLABLE(StartRumble);
API_CALLABLE(TTYD64_Player_Refund);
API_CALLABLE(TTYD64_Player_Refund_FreeIcons);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(battle_item_shooting_star_CustomFadeBackgroundDarken);
API_CALLABLE(battle_item_shooting_star_CustomFadeBackgroundLighten);
API_CALLABLE(battle_item_shooting_star_SpawnDamageStarsFX);
API_CALLABLE(battle_item_shooting_star_SpawnShootingStarFX);
EvtScript TTYD64_battle_item_shooting_star_EVS_802A1000;
EvtScript TTYD64_battle_item_shooting_star_EVS_UseItem;
EvtScript TTYD64_battle_item_shooting_star_EVS_802A1B28;

// clang-format off
EvtScript TTYD64_battle_item_shooting_star_EVS_802A1000 = {
    Call(GetOwnerID, LVar7)
    IfEq(LVar1, 0)
        Call(UseBattleCamPreset, 69)
        Wait(10)
        Call(PlaySoundAtActor, LVar7, 8333)
        Switch(LVar7)
            CaseEq(0)
                Call(SetAnimation, LVar7, 0, 65567)
            CaseEq(256)
                Set(LVar0, 7)
                Exec(TTYD64_SetPartnerAnimation_Battle)
            CaseDefault
        EndSwitch
        Call(GetActorPos, LVar7, LVar0, LVar1, LVar2)
        Add(LVar0, 10)
        Call(SetActorSpeed, LVar7, Float(4.0))
        Call(SetGoalPos, LVar7, LVar0, LVar1, LVar2)
        Switch(LVar7)
            CaseEq(0)
                Call(PlayerRunToGoal, 0)
            CaseEq(256)
                Call(RunToGoal, LVar7, 0, false)
        EndSwitch
        Add(LVar1, 45)
        Set(LVar3, LVar1)
        Add(LVar3, 10)
        Add(LVar3, 2)
        Call(PlayEffect_impl, 51, 1, LVar0, LVar3, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
        Call(MakeItemEntity, LVarA, LVar0, LVar1, LVar2, 1, 0)
        Set(LVarA, LVar0)
        Call(TTYD64_Player_Refund)
        Wait(LVar0)
        Wait(15)
        Call(TTYD64_Player_Refund_FreeIcons)
        Call(RemoveItemEntity, LVarA)
    Else
        Call(UseBattleCamPreset, 15)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 15)
        Call(PlaySoundAtActor, LVar7, 8333)
        Switch(LVar7)
            CaseEq(0)
                Call(SetAnimation, LVar7, 0, 65567)
            CaseEq(256)
                Set(LVar0, 7)
                Exec(TTYD64_SetPartnerAnimation_Battle)
            CaseDefault
        EndSwitch
        Wait(4)
        Call(GetActorPos, LVar7, LVar0, LVar1, LVar2)
        IfGe(LVar7, 512)
            Call(GetActorFlags, LVar7, LVar3)
            IfFlag(LVar3, 2048)
                Call(GetActorSize, LVar7, 0, LVar3)
                Sub(LVar1, LVar3)
            EndIf
        EndIf
        Add(LVar1, 45)
        Set(LVar3, LVar1)
        Add(LVar3, 10)
        Add(LVar3, 2)
        Call(PlayEffect_impl, 51, 1, LVar0, LVar3, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
        Call(MakeItemEntity, LVarA, LVar0, LVar1, LVar2, 1, 0)
        Set(LVarA, LVar0)
        Wait(15)
        Call(RemoveItemEntity, LVarA)
    EndIf
    Call(GetOwnerID, LVar7)
    IfEq(LVar7, 256)
        Set(LVar0, 0)
        Exec(TTYD64_SetPartnerAnimation_Battle)
    EndIf
    Return
    End
};

EvtScript TTYD64_battle_item_shooting_star_EVS_UseItem = {
    Jump(TTYD64_battle_item_shooting_star_EVS_802A1B28)
    Return
    End
};

EvtScript TTYD64_battle_item_shooting_star_EVS_802A1B28 = {
    SetConst(LVarA, 131)
    ExecWait(TTYD64_battle_item_shooting_star_EVS_802A1000)
    Thread
        Wait(5)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 20)
    EndThread
    Call(battle_item_shooting_star_CustomFadeBackgroundDarken)
    Thread
        Set(LVar0, 0)
        Loop(10)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_SHOOTING_STAR_FALL_A)
            Call(battle_item_shooting_star_SpawnShootingStarFX)
            Add(LVar0, 1)
            Wait(5)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_SHOOTING_STAR_FALL_B)
            Call(battle_item_shooting_star_SpawnShootingStarFX)
            Add(LVar0, 1)
            Wait(5)
        EndLoop
    EndThread
    Thread
        Set(LVar0, 0)
        Wait(50)
        Loop(10)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_STAR_BOUNCE_A)
            Add(LVar0, 1)
            Wait(5)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_STAR_BOUNCE_B)
            Add(LVar0, 1)
            Wait(5)
        EndLoop
    EndThread
    Thread
        Loop(5)
            Wait(15)
            Call(StartRumble, 8)
            Call(ShakeCam, 1, 0, 5, Float(1.0))
        EndLoop
    EndThread
    Wait(90)
    Call(GetOwnerID, LVar2)
    IfLt(LVar2, 512)
        Call(UseBattleCamPreset, 3)
        Call(MoveBattleCamOver, 20)
        Call(InitTargetIterator)
    EndIf
    Label(0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(ItemCheckHit, LVar0, 268435456, 0, LVar0, 0)
    IfEq(LVar0, 6)
        Goto(1)
    EndIf
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(battle_item_shooting_star_SpawnDamageStarsFX, LVar0, LVar1, LVar2)
    Call(GetItemPower, 131, LVar0, LVar1)
    Call(ItemDamageEnemy, LVar0, 973078784, 0, LVar0, 32)
    Label(1)
    Wait(10)
    Call(GetOwnerID, LVar2)
    IfGe(LVar2, 512)
        Call(GetOwnerTarget, LVar0, LVar1)
        Call(TTYD64_GetPartnerHP_API, LVar1)
        IfLe(LVar1, 0)
            Set(LVar0, 256)
        EndIf
        IfNe(LVar0, 256)
            Call(SetTargetActor, ACTOR_SELF, ACTOR_PARTNER)
            Goto(0)
        EndIf
    Else
        Call(ChooseNextTarget, 0, LVar0)
        IfNe(LVar0, -1)
            Goto(0)
        EndIf
    EndIf
    Wait(20)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    ExecWait(TTYD64_BattleScript_GoBackToHome_Item)
    Thread
        Call(battle_item_shooting_star_CustomFadeBackgroundLighten)
    EndThread
    Wait(30)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_item_shooting_star(void) {
    Mod_ReplaceScript("TTYD64", &battle_item_shooting_star_EVS_UseItem, &TTYD64_battle_item_shooting_star_EVS_UseItem);
}
