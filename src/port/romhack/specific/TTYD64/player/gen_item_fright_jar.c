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

extern EvtScript battle_item_fright_jar_EVS_UseItem;
API_CALLABLE(AddBattleCamDist);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetOwnerID);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(ItemCheckHit);
API_CALLABLE(ItemSpookEnemy);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetDamageSource);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(TTYD64_Player_Refund);
API_CALLABLE(TTYD64_Player_Refund_FreeIcons);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(battle_item_fire_flower_FadeBackgroundDarken);
API_CALLABLE(battle_item_fire_flower_FadeBackgroundLighten);
EvtScript TTYD64_battle_item_fright_jar_EVS_802A1000;
EvtScript TTYD64_battle_item_fright_jar_EVS_UseItem;
EvtScript TTYD64_battle_item_fright_jar_EVS_802A1938;

// clang-format off
EvtScript TTYD64_battle_item_fright_jar_EVS_802A1000 = {
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

EvtScript TTYD64_battle_item_fright_jar_EVS_UseItem = {
    Jump(TTYD64_battle_item_fright_jar_EVS_802A1938)
    Return
    End
};

EvtScript TTYD64_battle_item_fright_jar_EVS_802A1938 = {
    SetConst(LVarA, 152)
    ExecWait(TTYD64_battle_item_fright_jar_EVS_802A1000)
    Call(battle_item_fire_flower_FadeBackgroundDarken)
    Thread
        Wait(5)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 50)
    EndThread
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseEq(0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65556)
        CaseEq(256)
            Set(LVar0, 6)
            Exec(TTYD64_SetPartnerAnimation_Battle)
        CaseDefault
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_FRIGHT_JAR)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, -40)
    Add(LVar1, 5)
    SetF(LVar3, Float(0.7))
    Loop(5)
        Call(PlayEffect_impl, 97, 0, LVar0, LVar1, LVar2, LVar3, 25, 0, 0, 0, 0, 0, 0, 0)
        Add(LVar0, 5)
        AddF(LVar3, Float(0.15))
        Wait(7)
    EndLoop
    Call(PlayEffect_impl, 97, 0, LVar0, LVar1, LVar2, Float(1.5), 60, 0, 0, 0, 0, 0, 0, 0)
    Wait(20)
    Loop(4)
        Call(AddBattleCamDist, -100)
        Call(MoveBattleCamOver, 2)
        Wait(2)
        Call(AddBattleCamDist, 100)
        Call(MoveBattleCamOver, 2)
        Wait(2)
    EndLoop
    Call(UseBattleCamPreset, 3)
    Call(MoveBattleCamOver, 20)
    Call(GetOwnerID, LVar1)
    IfLt(LVar1, 512)
        Call(InitTargetIterator)
    EndIf
    Label(0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(ItemCheckHit, LVar0, 268435456, 0, LVar0, 0)
    IfEq(LVar0, 6)
        Goto(1)
    EndIf
    Call(SetDamageSource, 21)
    Call(ItemSpookEnemy, LVar0, 1912606720, 0, 100, 0, 32)
    Label(1)
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Wait(10)
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseEq(0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65540)
        CaseEq(256)
            Set(LVar0, 0)
            Exec(TTYD64_SetPartnerAnimation_Battle)
        CaseDefault
    EndSwitch
    Call(battle_item_fire_flower_FadeBackgroundLighten)
    Wait(20)
    ExecWait(TTYD64_BattleScript_GoBackToHome_Item)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_item_fright_jar(void) {
    Mod_ReplaceScript("TTYD64", &battle_item_fright_jar_EVS_UseItem, &TTYD64_battle_item_fright_jar_EVS_UseItem);
}
