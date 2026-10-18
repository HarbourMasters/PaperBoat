#include "common.h"
#include "effects.h"
#include "entity.h"
#include "foliage.h"
#include "map.h"
#include "npc.h"
#include "script_api/map.h"
#include <string.h>
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/maps/maps.h"

extern EvtScript kkj_18_EVS_SetupMusic;
extern EvtScript kkj_18_EVS_UpdateClockPendulum;

API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(PanToTarget);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlaySound);
API_CALLABLE(ResetCam);
API_CALLABLE(RotateGroup);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetMusic);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(ShakeCam);
API_CALLABLE(StopSound);
API_CALLABLE(TranslateGroup);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseSettingsFrom);

extern EvtScript TTYD64_kkj_18_Script_80240870;
extern EvtScript TTYD64_kkj_18_Script_NewStuff;
extern EvtScript TTYD64_kkj_18_Script_MoveClock;
extern EvtScript TTYD64_kkj_18_Script_802409E0_50;
extern EvtScript TTYD64_kkj_18_Script_MoveClock_InitRight;
extern EvtScript TTYD64_kkj_18_Script_MoveClock_InitLeft;

// clang-format off
EvtScript TTYD64_kkj_18_Script_80240870 = {
    IfEq(GameByte(0), 6)
        Call(SetMusic, 0, 116, 0, 8)
    EndIf
    Exec(TTYD64_kkj_18_Script_NewStuff)
    Return
    End
};

EvtScript TTYD64_kkj_18_Script_NewStuff = {
    Call(ParentColliderToModel, 29, 38)
    Call(ParentColliderToModel, 28, 38)
    Call(ParentColliderToModel, 18, 38)
    Switch(GameByte(4176))
    CaseEq(0)
        BindTrigger(TTYD64_kkj_18_Script_MoveClock_InitLeft, 64, 29, 1, 0)
        BindTrigger(TTYD64_kkj_18_Script_MoveClock_InitRight, 64, 28, 1, 0)
    CaseOrEq(1)
    CaseOrEq(2)
        IfEq(GameByte(4176), 1)
            Call(TranslateGroup, 45, 35, 0, 0)
        Else
            Call(TranslateGroup, 45, -35, 0, 0)
        EndIf
        Call(UpdateColliderTransform, 29)
        Call(UpdateColliderTransform, 28)
        Call(UpdateColliderTransform, 18)
        EndCaseGroup
    EndSwitch
    Call(MakeItemEntity, 348, -4, 0, -166, 17, GameFlag(4612))
    Return
    End
};

EvtScript TTYD64_kkj_18_Script_MoveClock = {
    IfNe(GameByte(4176), 0)
        Unbind
        Return
    EndIf
    Call(TTYD64_ReadField, TTYD64_F_GGAMESTATUS_7E_1U, LVar1)
    IfNe(LVar1, 0)
        Return
    EndIf
    Thread
        Call(ShakeCam, 0, 0, 100, Float(0.2998046875))
    EndThread
    Thread
        Call(GetModelCenter, 38)
        Call(UseSettingsFrom, 0, LVar0, 0, LVar2)
        Call(GetPlayerPos, 0, LVar1, 0)
        Call(SetCamSpeed, 0, Float(3.0))
        Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
        Call(PanToTarget, 0, 0, 1)
    EndThread
    Set(LVar3, LVar0)
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(PlaySound, 0x80000010)
    Set(LVar0, 35)
    Mul(LVar0, LVar3)
    Call(MakeLerp, 0, LVar0, 100, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, 45, LVar0, 0, 0)
        Call(UpdateColliderTransform, 18)
        Call(UpdateColliderTransform, 29)
        Call(UpdateColliderTransform, 28)
        Set(LVar4, LVar1)
        Call(GetModelCenter, 38)
        Set(LVar5, -17)
        Mul(LVar5, LVar3)
        Add(LVar0, LVar5)
        Call(GetPlayerPos, 0, LVar1, LVar2)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetPlayerActionState, 20)
        Wait(1)
        IfEq(LVar4, 0)
            IfEq(LVar3, 1)
                Set(GameByte(4176), 1)
            Else
                Set(GameByte(4176), 2)
            EndIf
            IfEq(GameByte(4176), 1)
                Call(TranslateGroup, 45, 35, 0, 0)
            Else
                Call(TranslateGroup, 45, -35, 0, 0)
            EndIf
            BreakLoop
        EndIf
    EndLoop
    Call(StopSound, 0x80000010)
    Call(SetPlayerActionState, 0)
    Wait(10)
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerInput, 0)
    Call(DisablePlayerPhysics, 0)
    Call(ResetCam, 0, Float(5.0))
    Unbind
    Return
    End
};

EvtScript TTYD64_kkj_18_Script_802409E0_50 = {
    Loop(0)
        Call(MakeLerp, -8, 8, 30, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateGroup, 44, LVar0, 0, 0, 1)
            Switch(GameByte(4176))
            CaseEq(1)
                Call(TranslateGroup, 44, 35, 0, 0)
            CaseEq(2)
                Call(TranslateGroup, 44, -35, 0, 0)
            EndSwitch
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(MakeLerp, 8, -8, 30, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateGroup, 44, LVar0, 0, 0, 1)
            Switch(GameByte(4176))
            CaseEq(1)
                Call(TranslateGroup, 44, 35, 0, 0)
            CaseEq(2)
                Call(TranslateGroup, 44, -35, 0, 0)
            EndSwitch
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndLoop
    Return
    End
};

EvtScript TTYD64_kkj_18_Script_MoveClock_InitRight = {
    Set(LVar0, -1)
    ExecWait(TTYD64_kkj_18_Script_MoveClock)
    Return
    End
};

EvtScript TTYD64_kkj_18_Script_MoveClock_InitLeft = {
    Set(LVar0, 1)
    ExecWait(TTYD64_kkj_18_Script_MoveClock)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_kkj_18(void) {
    Mod_ReplaceScript("TTYD64", &kkj_18_EVS_SetupMusic, &TTYD64_kkj_18_Script_80240870);
    Mod_ReplaceScript("TTYD64", &kkj_18_EVS_UpdateClockPendulum, &TTYD64_kkj_18_Script_802409E0_50);
}
