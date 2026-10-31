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

extern NpcGroupList obk_07_DefaultNPCs;
extern EvtScript obk_07_EVS_EnterMap;
extern EvtScript obk_07_EVS_ExitDoors_obk_01_3;
extern EvtScript obk_07_EVS_Main;
extern EvtScript obk_07_EVS_MakeEntities;
extern EvtScript obk_07_EVS_PlayExplosionFX;
extern EvtScript obk_07_EVS_PlaySmokeFX;
extern EvtScript obk_07_EVS_SetupFireplace;
extern EvtScript obk_07_EVS_SetupMusic;
extern EvtScript obk_07_EVS_SetupPhonograph;
extern Vec3i obk_07_ExplosionPositions1[];
extern Vec3i obk_07_ExplosionPositions2[];
extern Vec3i obk_07_ExplosionPositions3[];
extern MapSettings obk_07_settings;

API_CALLABLE(AdjustCam);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnableModel);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(EnableTexPanning);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(InterpNpcYaw);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(NpcMoveTo);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtModel);
API_CALLABLE(PlaySoundAtPlayer);
API_CALLABLE(ResetCam);
API_CALLABLE(RotateModel);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanOffset);
API_CALLABLE(SetTexPanner);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_obk_07_Script_80241D60;
extern EvtScript TTYD64_obk_07_Script_Main;
extern EntryList TTYD64_obk_07_EntryList;
extern EvtScript TTYD64_obk_07_Script_802428D0;
extern EvtScript TTYD64_obk_07_Script_BurnMario;
extern EvtScript TTYD64_obk_07_Script_TrackEntry;
extern EvtScript TTYD64_obk_07_Script_Exit1;
extern EvtScript TTYD64_obk_07_Script_CreateExitTriggers;

// clang-format off
EvtScript TTYD64_obk_07_Script_80241D60 = {
    Thread
        Call(EnableTexPanning, 67, 1)
        Set(LVar0, 0)
        Set(LVar1, 0)
        Loop(0)
            Call(SetTexPanOffset, 2, 1, LVar0, LVar1)
            Add(LVar0, 300)
            Add(LVar1, 100)
            Wait(1)
        EndLoop
    EndThread
    Call(SetTexPanner, 70, 0)
    Set(LVar0, 0)
    Set(LVar1, 0)
    Loop(0)
        Add(LVar0, 300)
        Add(LVar1, 100)
        Call(SetTexPanOffset, 0, 0, LVar0, LVar1)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_obk_07_Script_Main = {
    Set(GameByte(425), 13)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeNpcs, 0, Ref(obk_07_DefaultNPCs))
    ExecWait(obk_07_EVS_MakeEntities)
    Exec(TTYD64_obk_07_Script_80241D60)
    Exec(obk_07_EVS_SetupFireplace)
    Exec(obk_07_EVS_SetupPhonograph)
    Exec(TTYD64_obk_07_Script_TrackEntry)
    Exec(obk_07_EVS_SetupMusic)
    Return
    End
};

EntryList TTYD64_obk_07_EntryList = {
    { 68.0f, 0.0f, 235.0f, 0.0f },
    { 0.0f, 0.0f, -181.0f, -180.0f },
};

EvtScript TTYD64_obk_07_Script_802428D0 = {
    BindTrigger(TTYD64_obk_07_Script_BurnMario, 256, 6, 1, 0)
    Return
    End
};

EvtScript TTYD64_obk_07_Script_BurnMario = {
    IfEq(MapVar(0), 1)
        Return
    EndIf
    Set(MapVar(0), 1)
    Call(DisablePlayerInput, 1)
    Thread
        Call(AdjustCam, 0, Float(4.0), 0, Float(250.0), Float(17.5), Float(-10.0))
    EndThread
    Wait(10)
    Thread
        Call(DisablePartnerAI, 0)
        Wait(1)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Sub(LVar0, 25)
        Call(SetNpcFlagBits, -4, 256, 1)
        Call(NpcMoveTo, -4, LVar0, LVar2, 10)
        Call(SetNpcFlagBits, -4, 256, 0)
        Call(EnablePartnerAI)
        Call(InterpPlayerYaw, 90, 0)
        Call(InterpNpcYaw, -4, 90, 0)
    EndThread
    Call(PlaySoundAtPlayer, 245, 0)
    Set(LVar0, (Bytecode) obk_07_ExplosionPositions1)
    Exec(obk_07_EVS_PlayExplosionFX)
    Set(LVar0, (Bytecode) obk_07_ExplosionPositions2)
    Exec(obk_07_EVS_PlayExplosionFX)
    Set(LVar0, (Bytecode) obk_07_ExplosionPositions3)
    Exec(obk_07_EVS_PlayExplosionFX)
    Wait(5)
    Call(SetPlayerAnimation, 0x1002F)
    Wait(60)
    ExecWait(obk_07_EVS_PlaySmokeFX)
    Wait(40)
    IfEq(GameFlag(5078), 0)
        Set(LVar2, 10)
        Call(MakeLerp, 0, 90, LVar2, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, 67, LVar0, -1, 0, 0)
            Sub(LVar2, 1)
            IfEq(LVar2, 3)
                Call(GetModelCenter, 67)
                Add(LVar1, 3)
                Call(PlayEffect_impl, 6, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                Call(PlaySoundAtModel, 67, 1019, 0)
            EndIf
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(ModifyColliderFlags, 0, 6, 0x7FFFFE00)
        Set(GameFlag(5078), 1)
    EndIf
    Wait(5)
    Set(LVar0, 0x80016)
    Set(LVar1, 1)
    Set(LVar2, 35)
    ExecWait(TTYD64_SetPlayerAnimation)
    Call(SetPlayerAnimation, 0x10002)
    Call(ResetCam, 0, Float(4.0))
    Set(MapVar(0), 0)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_obk_07_Script_TrackEntry = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 0)
        Exec(TTYD64_obk_07_Script_CreateExitTriggers)
        Exec(obk_07_EVS_EnterMap)
    Else
        Set(LVar0, Ref(TTYD64_obk_07_Script_CreateExitTriggers))
        Exec(EnterWalk)
        Wait(1)
    EndIf
    IfEq(GameFlag(5078), 1)
        Call(EnableModel, 67, 0)
        Call(ModifyColliderFlags, 0, 6, 0x7FFFFE00)
    EndIf
    Return
    End
};

EvtScript TTYD64_obk_07_Script_Exit1 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 1)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "obk_10", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_obk_07_Script_CreateExitTriggers = {
    BindTrigger(obk_07_EVS_ExitDoors_obk_01_3, 256, 3, 1, 0)
    BindTrigger(TTYD64_obk_07_Script_Exit1, 0x80000, 30, 1, 0)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_obk_07(void) {
    obk_07_settings.entryList = &TTYD64_obk_07_EntryList;
    obk_07_settings.entryCount = 2;
    Mod_ReplaceScript("TTYD64", &obk_07_EVS_Main, &TTYD64_obk_07_Script_Main);
    Mod_ReplaceScript("TTYD64", &obk_07_EVS_SetupFireplace, &TTYD64_obk_07_Script_802428D0);
}
