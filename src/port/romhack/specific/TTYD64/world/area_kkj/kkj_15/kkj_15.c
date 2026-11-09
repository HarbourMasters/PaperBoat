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
#include "port/romhack/specific/TTYD64/world/maps.h"

extern EvtScript kkj_15_EVS_EnterRotatingWall;
extern EvtScript kkj_15_EVS_RotatingWall_Default;
extern EvtScript kkj_15_EVS_RotatingWall_FirstTime;
extern EvtScript kkj_15_EVS_SetupMusic;

API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(MakeLerp);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PartnerIsFlying);
API_CALLABLE(PlaySoundAt);
API_CALLABLE(RotateGroup);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(UpdateLerp);
API_CALLABLE(kkj_15_UpdateRotatingPartyPositions);

extern EvtScript TTYD64_kkj_15_Script_InitNewStuff;
extern EvtScript TTYD64_kkj_15_Script_Exit3;
extern EvtScript TTYD64_kkj_15_Script_80241550;
extern EvtScript TTYD64_kkj_15_Script_80240680;

// clang-format off
EvtScript TTYD64_kkj_15_Script_InitNewStuff = {
    Call(TTYD64_TestPlayerAnimFlags, PA_FLAG_USING_PEACH_PHYSICS, LVar1)
    IfEq(LVar1, 0)
        Call(ModifyColliderFlags, 1, 32, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 26, 0x7FFFFE00)
        BindTrigger(TTYD64_kkj_15_Script_Exit3, 256, 27, 1, 0)
        Call(GetEntryID, LVar0)
        IfNe(LVar0, 1)
            Call(RotateGroup, 95, -180, 0, 1, 0)
        EndIf
    EndIf
    Return
    End
};

EvtScript TTYD64_kkj_15_Script_Exit3 = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(DisablePartnerAI, 0)
    Call(SetPlayerPos, 50, 10, -250)
    Call(PartnerIsFlying, LVar0)
    IfEq(LVar0, 0)
        Call(SetNpcPos, -4, 10, 30, -250)
    Else
        Call(SetNpcPos, -4, 10, 0, -250)
    EndIf
    Call(SetNpcFlagBits, -4, 512, 0)
    Call(DisablePlayerInput, 1)
    Thread
        Call(PlaySoundAt, 147, 0, -237, 0, -5)
        Call(GetPlayerPos, LVar7, LVar0, LVar8)
        Call(GetNpcPos, -4, LVar9, LVar0, LVarA)
        Call(MakeLerp, 1800, 1550, 120, 0)
        Loop(0)
            Call(UpdateLerp)
            SetF(LVar2, LVar0)
            DivF(LVar2, 10)
            Call(RotateGroup, 95, LVar2, 0, 1, 0)
            Call(kkj_15_UpdateRotatingPartyPositions)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Wait(80)
    Call(GotoMap, (Bytecode) "kkj_27", 2)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_kkj_15_Script_80241550 = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(DisablePartnerAI, 0)
    Call(SetPlayerPos, 50, 10, -250)
    Call(PartnerIsFlying, LVar0)
    IfEq(LVar0, 0)
        Call(SetNpcPos, -4, 10, 30, -250)
    Else
        Call(SetNpcPos, -4, 10, 0, -250)
    EndIf
    Call(SetNpcFlagBits, -4, 512, 0)
    Call(InterpPlayerYaw, 270, 0)
    Switch(GameByte(0))
    CaseEq(-76)
        ExecWait(kkj_15_EVS_RotatingWall_FirstTime)
    CaseDefault
        ExecWait(kkj_15_EVS_RotatingWall_Default)
    EndSwitch
    Call(EnablePartnerAI)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_kkj_15_Script_80240680 = {
    Switch(GameByte(0))
    CaseOrEq(-105)
    CaseOrEq(-76)
    CaseOrEq(-14)
    CaseOrEq(88)
        Call(SetMusic, 0, 115, 0, 8)
        EndCaseGroup
    CaseOrEq(-54)
    CaseOrEq(6)
    CaseOrEq(38)
    CaseOrEq(58)
        Call(SetMusic, 0, 116, 0, 8)
        EndCaseGroup
    EndSwitch
    Exec(TTYD64_kkj_15_Script_InitNewStuff)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_kkj_15(void) {
    Mod_ReplaceScript("TTYD64", &kkj_15_EVS_EnterRotatingWall, &TTYD64_kkj_15_Script_80241550);
    Mod_ReplaceScript("TTYD64", &kkj_15_EVS_SetupMusic, &TTYD64_kkj_15_Script_80240680);
}
