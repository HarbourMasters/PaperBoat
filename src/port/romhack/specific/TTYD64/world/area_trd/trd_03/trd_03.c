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

extern BombTrigger trd_03_BombPos_MiddleCell;
extern BombTrigger trd_03_BombPos_RightCell;
extern NpcGroupList trd_03_DefaultNPCs;
extern EvtScript trd_03_EVS_BombWall_MiddleCell;
extern EvtScript trd_03_EVS_BombWall_RightCell;
extern EvtScript trd_03_EVS_EnterMap;
extern EvtScript trd_03_EVS_HiddenDoor;
extern EvtScript trd_03_EVS_InitializePlatforms;
extern EvtScript trd_03_EVS_Main;
extern EvtScript trd_03_EVS_MakeEntities;
extern EvtScript trd_03_EVS_Scene_GreenKoopaBros;
extern EvtScript trd_03_EVS_SetupMusic;

API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableModel);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(ResetCam);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamDistance);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetGroupVisibility);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(StopSound);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(WaitForCam);

extern EvtScript TTYD64_trd_03_Script_NewStuff;
extern EvtScript TTYD64_trd_03_Script_PullChain;
extern EvtScript TTYD64_trd_03_Script_Main;
extern EvtScript TTYD64_trd_03_Script_ChainFX;

// clang-format off
EvtScript TTYD64_trd_03_Script_NewStuff = {
    Call(MakeItemEntity, 348, -518, 0, -74, 17, GameFlag(4766))
    IfEq(GameFlag(4764), 0)
        Exec(TTYD64_trd_03_Script_ChainFX)
        BindTrigger(TTYD64_trd_03_Script_PullChain, 1024, 61, 1, 0)
    Else
        Call(ModifyColliderFlags, 0, 61, 0x7FFFFE00)
        Call(MakeItemEntity, 389, -333, 0, 0, 17, GameFlag(4765))
    EndIf
    Return
    End
};

EvtScript TTYD64_trd_03_Script_PullChain = {
    SetGroup(0)
    SuspendGroup(2)
    Set(GameFlag(4764), 1)
    Call(DisablePartnerAI, 0)
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerAnimation, 0x10002)
    Call(SetPlayerAnimation, 0x80005)
    Call(SetPlayerPos, -271, 69, 0)
    Wait(3)
    Call(PlaySound, 84)
    Call(MakeLerp, 0, -4, 4, 0)
    Loop(0)
        Call(UpdateLerp)
        Set(LVar3, LVar0)
        Set(LVar4, LVar1)
        Call(TranslateModel, 67, 0, LVar3, 0)
        Call(GetModelCenter, 67)
        Sub(LVar1, 160)
        Add(LVar2, 1)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
        IfEq(LVar4, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(SetCamSpeed, 0, Float(4.0))
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Set(LVar0, -271)
    Set(LVar1, 69)
    Set(LVar2, 0)
    Add(LVar1, -50)
    Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
    Call(SetCamDistance, 0, 350)
    Call(PanToTarget, 0, 0, 1)
    Wait(7)
    Call(PlaySound, 63)
    Thread
        Wait(10)
        Set(LVar0, -333)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Add(LVar1, 285)
        Call(MakeItemEntity, 389, LVar0, LVar1, LVar2, 13, GameFlag(4765))
    EndThread
    Call(MakeLerp, 0, -20, 25, 0)
    Loop(0)
        Call(UpdateLerp)
        Set(LVar3, LVar0)
        Set(LVar4, LVar1)
        Call(TranslateModel, 67, 0, LVar3, 0)
        Call(GetModelCenter, 67)
        Sub(LVar1, 160)
        Add(LVar2, 1)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
        IfEq(LVar4, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(StopSound, 63)
    Wait(25)
    Call(SetPlayerAnimation, 0x10002)
    Call(SetPlayerAnimation, 0x10008)
    Unbind
    Call(ModifyColliderFlags, 0, 61, 0x7FFFFE00)
    Call(DisablePlayerPhysics, 0)
    Call(ResetCam, 0, Float(4.0))
    Call(WaitForCam, 0, Float(1.0))
    ResumeGroup(2)
    Call(DisablePlayerInput, 0)
    Call(EnablePartnerAI)
    Return
    End
};

EvtScript TTYD64_trd_03_Script_Main = {
    Set(GameByte(425), 7)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamLeadPlayer, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 1, Ref(trd_03_DefaultNPCs))
    ExecWait(trd_03_EVS_MakeEntities)
    IfLt(GameByte(0), -88)
        Exec(trd_03_EVS_Scene_GreenKoopaBros)
    Else
        Exec(trd_03_EVS_EnterMap)
    EndIf
    IfEq(GameFlag(655), 0)
        Call(EnableModel, 30, 0)
    Else
        Call(SetGroupVisibility, 37, 0)
        Call(ModifyColliderFlags, 0, 20, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 22, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(656), 0)
        Call(EnableModel, 32, 0)
        BindTrigger(trd_03_EVS_BombWall_MiddleCell, 0x100000, Ref(trd_03_BombPos_MiddleCell), 1, 0)
    Else
        Call(SetGroupVisibility, 40, 0)
        Call(ModifyColliderFlags, 0, 25, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 27, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(657), 0)
        Call(EnableModel, 33, 0)
        BindTrigger(trd_03_EVS_BombWall_RightCell, 0x100000, Ref(trd_03_BombPos_RightCell), 1, 0)
    Else
        Call(SetGroupVisibility, 43, 0)
        Call(ModifyColliderFlags, 0, 30, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 32, 0x7FFFFE00)
    EndIf
    Exec(trd_03_EVS_SetupMusic)
    IfLt(GameByte(0), -88)
        Call(TranslateModel, 12, 0, 100, -1)
    EndIf
    ExecWait(trd_03_EVS_InitializePlatforms)
    Exec(trd_03_EVS_HiddenDoor)
    Exec(TTYD64_trd_03_Script_NewStuff)
    Return
    End
};

EvtScript TTYD64_trd_03_Script_ChainFX = {
    Loop(0)
        Call(PlayEffect_impl, 109, 0, -271, 100, 0, Float(1.2998046875), 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(20)
        IfEq(GameFlag(4764), 1)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_trd_03(void) {
    Mod_ReplaceScript("TTYD64", &trd_03_EVS_Main, &TTYD64_trd_03_Script_Main);
}
