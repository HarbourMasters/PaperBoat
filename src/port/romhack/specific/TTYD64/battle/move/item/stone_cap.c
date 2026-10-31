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

extern EvtScript battle_item_stone_cap_EVS_UseItem;
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetItemPower);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleFlagBits2);
API_CALLABLE(SetGoalPos);
API_CALLABLE(TTYD64_Player_Refund);
API_CALLABLE(TTYD64_Player_Refund_FreeIcons);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(battle_item_stone_cap_func_802A123C_7217DC);
EvtScript TTYD64_battle_item_stone_cap_EVS_802A1000;
EvtScript TTYD64_battle_item_stone_cap_EVS_802A151C;
EvtScript TTYD64_battle_item_stone_cap_EVS_UseItem;

// clang-format off
EvtScript TTYD64_battle_item_stone_cap_EVS_802A1000 = {
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
    Call(UseBattleCamPreset, 14)
    Call(GetOwnerTarget, LVar7, 0)
    Call(BattleCamTargetActor, LVar7)
    Call(MoveBattleCamOver, 15)
    Return
    End
};

EvtScript TTYD64_battle_item_stone_cap_EVS_802A151C = {
    SetConst(LVarA, 136)
    ExecWait(TTYD64_battle_item_stone_cap_EVS_802A1000)
    Call(TTYD64_SetActorExtraData, 0, 14, 0)
    Call(GetOwnerID, LVar3)
    Call(GetOwnerTarget, LVar4, 0)
    IfNe(LVar3, 0)
        Call(UseIdleAnimation, ACTOR_PLAYER, false)
        Call(SetBattleFlagBits2, BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER, 1)
    EndIf
    IfLt(LVar3, 512)
        Call(InitTargetIterator)
    EndIf
    IfNe(LVar4, 0)
        IfGe(LVar3, 512)
            Call(UseBattleCamPreset, 2)
        EndIf
        Call(TTYD64_ReadField, TTYD64_F_GBATTLESTATUS_PLAYERACTOR_210_1U, LVar0)
        IfNe(LVar0, 0)
            IfNe(LVar3, 0)
                Call(UseIdleAnimation, ACTOR_PLAYER, true)
            EndIf
            Return
        EndIf
        Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_EMOTE_IDEA)
        Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Add(LVar1, 18)
        Call(PlayEffect_impl, 16, 0, 0, LVar0, LVar1, LVar2, 16, 35, 15)
        Call(SetAnimation, ACTOR_PLAYER, 0, 65579)
        Wait(30)
    Else
        Call(PlaySound, SOUND_PUT_ON_CAP)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196617)
        Wait(30)
    EndIf
    Call(SetAnimation, ACTOR_PLAYER, 0, 65556)
    Call(GetItemPower, 136, LVar0, LVar1)
    Call(PlaySound, SOUND_BECOME_STONE)
    Call(battle_item_stone_cap_func_802A123C_7217DC)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Wait(20)
    Call(GetOwnerID, LVar3)
    IfNe(LVar3, 0)
        Call(UseIdleAnimation, ACTOR_PLAYER, true)
    EndIf
    Return
    End
};

EvtScript TTYD64_battle_item_stone_cap_EVS_UseItem = {
    Jump(TTYD64_battle_item_stone_cap_EVS_802A151C)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_item_stone_cap(void) {
    Mod_ReplaceScript("TTYD64", &battle_item_stone_cap_EVS_UseItem, &TTYD64_battle_item_stone_cap_EVS_UseItem);
}
