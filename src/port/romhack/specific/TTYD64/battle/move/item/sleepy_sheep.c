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

extern EvtScript battle_item_sleepy_sheep_EVS_UseItem;
extern s32 battle_item_sleepy_sheep_modelCommandList[];
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(CreateVirtualEntity);
API_CALLABLE(DeleteVirtualEntity);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetItemPower);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(ItemAfflictEnemy);
API_CALLABLE(ItemCheckHit);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeStatusField);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerHopToGoal);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(SetOwnerTarget);
API_CALLABLE(SetTargetActor);
API_CALLABLE(SetVirtualEntityJumpGravity);
API_CALLABLE(SetVirtualEntityMoveSpeed);
API_CALLABLE(SetVirtualEntityPosition);
API_CALLABLE(SetVirtualEntityScale);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowEmote);
API_CALLABLE(StartRumble);
API_CALLABLE(TTYD64_Player_Refund);
API_CALLABLE(TTYD64_Player_Refund_FreeIcons);
API_CALLABLE(TTYD64_Player_item11_RotateTargets_End);
API_CALLABLE(TTYD64_Player_item11_RotateTargets_Start);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(VirtualEntityJumpTo);
API_CALLABLE(VirtualEntityMoveTo);
API_CALLABLE(battle_item_sleepy_sheep_func_802A123C_71E88C);
EvtScript TTYD64_battle_item_sleepy_sheep_EVS_802A1000;
EvtScript TTYD64_battle_item_sleepy_sheep_EVS_UseItem;
EvtScript TTYD64_battle_item_sleepy_sheep_EVS_802A3F50;

// clang-format off
EvtScript TTYD64_battle_item_sleepy_sheep_EVS_802A1000 = {
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

EvtScript TTYD64_battle_item_sleepy_sheep_EVS_UseItem = {
    Jump(TTYD64_battle_item_sleepy_sheep_EVS_802A3F50)
    Return
    End
};

EvtScript TTYD64_battle_item_sleepy_sheep_EVS_802A3F50 = {
    SetConst(LVarA, 143)
    ExecWait(TTYD64_battle_item_sleepy_sheep_EVS_802A1000)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, -15)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamOffsetY, 45)
    Call(SetBattleCamDist, 169)
    Call(MoveBattleCamOver, 50)
    Thread
        Call(PlaySoundAtActor, ACTOR_SELF, SOUND_SHEEP_STAMPEDE)
        Loop(7)
            Call(StartRumble, 2)
            Call(ShakeCam, 1, 0, 2, Float(0.5))
            Call(ShakeCam, 1, 0, 2, Float(1.5))
            Call(ShakeCam, 1, 0, 2, Float(0.5))
            Call(ShakeCam, 1, 0, 2, Float(0.2))
            Call(ShakeCam, 1, 0, 2, Float(0.5))
            Call(ShakeCam, 1, 0, 2, Float(2.0))
            Call(ShakeCam, 1, 0, 2, Float(1.5))
            Call(ShakeCam, 1, 0, 2, Float(1.0))
            Call(ShakeCam, 1, 0, 2, Float(0.5))
            Call(ShakeCam, 1, 0, 2, Float(0.25))
            Wait(2)
            Call(ShakeCam, 1, 0, 2, Float(0.5))
            Call(ShakeCam, 1, 0, 2, Float(1.5))
            Call(ShakeCam, 1, 0, 2, Float(0.5))
            Call(ShakeCam, 1, 0, 2, Float(0.2))
        EndLoop
    EndThread
    Wait(20)
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseEq(0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
        CaseEq(256)
            Set(LVar0, 0)
            Exec(TTYD64_SetPartnerAnimation_Battle)
        CaseDefault
    EndSwitch
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 32)
    Call(ShowEmote, -127, EMOTE_QUESTION, -45, 20, 2, LVar0, LVar1, LVar2, 10)
    Wait(30)
    Call(GetOwnerID, LVar2)
    IfGe(LVar2, 512)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 20)
        Wait(8)
        Thread
            Call(battle_item_sleepy_sheep_func_802A123C_71E88C)
        EndThread
        Goto(0)
    EndIf
    Call(SetActorYaw, ACTOR_SELF, 30)
    Wait(1)
    Call(SetActorYaw, ACTOR_SELF, 60)
    Wait(1)
    Call(SetActorYaw, ACTOR_SELF, 90)
    Wait(1)
    Call(SetActorYaw, ACTOR_SELF, 120)
    Wait(1)
    Call(SetActorYaw, ACTOR_SELF, 150)
    Wait(1)
    Call(SetActorYaw, ACTOR_SELF, 180)
    Thread
        Call(battle_item_sleepy_sheep_func_802A123C_71E88C)
    EndThread
    Call(InitTargetIterator)
    Thread
        Wait(40)
        Call(TTYD64_GetActorPointer, -127, LVar0)
        Call(TTYD64_Player_item11_RotateTargets_Start, LVar0)
        Call(TTYD64_Player_item11_RotateTargets_End, LVar0)
    EndThread
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Wait(8)
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseEq(0)
            Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65579, 65579, 65544)
            Call(SetActorJumpGravity, LVar7, Float(1.7998))
            Call(GetActorPos, LVar7, LVar0, LVar1, LVar2)
            Call(SetGoalPos, LVar7, LVar0, LVar1, LVar2)
            Call(PlayerHopToGoal, 15, 0, 0)
        CaseEq(256)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Set(LVar0, 9)
            Exec(TTYD64_SetPartnerAnimation_Battle)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 15, false, false, true)
            Set(LVar0, 0)
            Exec(TTYD64_SetPartnerAnimation_Battle)
        CaseDefault
    EndSwitch
    Thread
        Wait(5)
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
    EndThread
    Label(0)
    Wait(40)
    Call(CreateVirtualEntity, LVarA, Ref(battle_item_sleepy_sheep_modelCommandList))
    Set(LVar7, -200)
    Set(LVar8, 0)
    Set(LVar9, 0)
    Call(SetVirtualEntityPosition, LVarA, LVar7, LVar8, LVar9)
    Call(SetVirtualEntityScale, LVarA, Float(0.71), Float(0.71), Float(0.71))
    Call(SetVirtualEntityMoveSpeed, LVarA, Float(7.0))
    Call(SetVirtualEntityJumpGravity, LVarA, Float(1.4))
    Call(GetOwnerID, LVar7)
    IfLt(LVar7, 512)
        Call(SetOwnerTarget, -127, 0)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 60)
    Call(VirtualEntityMoveTo, LVarA, LVar0, LVar1, LVar2, 0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetOwnerID, LVar7)
    IfGe(LVar7, 512)
        Goto(1)
    EndIf
    Call(VirtualEntityJumpTo, LVarA, LVar0, LVar1, LVar2, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_HIT_BLOCK)
    Thread
        Call(GetOwnerID, LVar7)
        Switch(LVar7)
            CaseEq(0)
                Call(SetAnimation, ACTOR_PLAYER, 0, 65571)
            CaseEq(256)
                Set(LVar0, 6)
                Exec(TTYD64_SetPartnerAnimation_Battle)
            CaseDefault
        EndSwitch
        Call(SetActorScale, ACTOR_SELF, Float(1.2), Float(0.9), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(1.2998), Float(0.7998), Float(1.0))
        Wait(3)
        Call(SetActorScale, ACTOR_SELF, Float(1.2), Float(0.9), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    EndThread
    Call(PlayEffect_impl, 6, 3, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Wait(2)
    Call(SetVirtualEntityJumpGravity, LVarA, Float(1.4))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 60)
    Call(VirtualEntityJumpTo, LVarA, LVar0, LVar1, LVar2, 0)
    Call(PlayEffect_impl, 6, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseEq(0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
        CaseEq(256)
            Set(LVar0, 0)
            Exec(TTYD64_SetPartnerAnimation_Battle)
        CaseDefault
    EndSwitch
    Add(LVar0, 20)
    Call(VirtualEntityJumpTo, LVarA, LVar0, LVar1, LVar2, 0)
    Call(PlayEffect_impl, 6, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Add(LVar0, 10)
    Call(VirtualEntityJumpTo, LVarA, LVar0, LVar1, LVar2, 0)
    Call(PlayEffect_impl, 6, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Label(1)
    Wait(5)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 270)
        Call(VirtualEntityMoveTo, LVarA, LVar0, LVar1, LVar2, 0)
        Call(DeleteVirtualEntity, LVarA)
    EndThread
    Wait(30)
    Call(GetOwnerID, LVar2)
    IfLt(LVar2, 512)
        Call(UseBattleCamPreset, 3)
        Call(MoveBattleCamOver, 20)
        Call(InitTargetIterator)
    EndIf
    Label(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(ItemCheckHit, LVar0, 268435456, 0, LVar0, 0)
    IfEq(LVar0, 6)
        Goto(3)
    EndIf
    Call(GetItemPower, 143, LVar0, LVar1)
    Call(MakeStatusField, LVar0, 4096, 100, LVar0)
    Call(ItemAfflictEnemy, LVar0, 1342177280, LVar0, 0, 32)
    Label(3)
    Wait(5)
    Call(GetOwnerID, LVar2)
    IfGe(LVar2, 512)
        Call(GetOwnerTarget, LVar0, LVar1)
        Call(TTYD64_GetPartnerHP_API, LVar1)
        IfLe(LVar1, 0)
            Set(LVar0, 256)
        EndIf
        IfNe(LVar0, 256)
            Call(SetTargetActor, ACTOR_SELF, ACTOR_PARTNER)
            Goto(2)
        EndIf
    Else
        Call(ChooseNextTarget, 0, LVar0)
        IfNe(LVar0, -1)
            Goto(2)
        EndIf
    EndIf
    Wait(30)
    ExecWait(TTYD64_BattleScript_GoBackToHome_Item)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_item_sleepy_sheep(void) {
    Mod_ReplaceScript("TTYD64", &battle_item_sleepy_sheep_EVS_UseItem, &TTYD64_battle_item_sleepy_sheep_EVS_UseItem);
}
