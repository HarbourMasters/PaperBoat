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

extern NpcGroupList obk_08_DefaultNPCs;
extern EvtScript obk_08_EVS_EnterMap;
extern EvtScript obk_08_EVS_ExitMap_obk_01_4;
extern EvtScript obk_08_EVS_Main;
extern EvtScript obk_08_EVS_MakeEntities;
extern EvtScript obk_08_EVS_SetupCabinets;
extern EvtScript obk_08_EVS_SetupMusic;

API_CALLABLE(AwaitPlayerApproach);
API_CALLABLE(AwaitPlayerLeave);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlaySoundAtModel);
API_CALLABLE(PlaySoundWithVolume);
API_CALLABLE(RotateModel);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanOffset);
API_CALLABLE(SetTexPanner);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UpdateLerp);
API_CALLABLE(obk_08_ShutterCrashRumble);

extern EvtScript TTYD64_obk_08_Script_80241970;
extern EvtScript TTYD64_obk_08_Script_ShakeWindows_Left;
extern EvtScript TTYD64_obk_08_Script_ShakeWindows_Right;
extern EvtScript TTYD64_obk_08_Script_ShakeWindows;
extern EvtScript TTYD64_obk_08_Script_Main;

// clang-format off
EvtScript TTYD64_obk_08_Script_80241970 = {
    Call(SetTexPanner, 83, 0)
    Call(SetTexPanner, 84, 0)
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

EvtScript TTYD64_obk_08_Script_ShakeWindows_Left = {
    Call(PlaySoundWithVolume, 0xB0000011, 0)
    Call(PlaySoundAtModel, LVar2, 0xB0000011, 0)
    Call(obk_08_ShutterCrashRumble, 5)
    Set(LVar3, 90)
    Call(MakeLerp, 0, LVar3, 15, 8)
    Label(10)
    Call(UpdateLerp)
    Call(RotateModel, LVar2, LVar0, 0, 1, 0)
    Call(UpdateColliderTransform, LVarA)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(10)
    EndIf
    Call(obk_08_ShutterCrashRumble, 5)
    Set(LVar4, 0)
    Label(15)
    Call(MakeLerp, LVar3, 20, 20, 8)
    Label(20)
    Call(UpdateLerp)
    Call(RotateModel, LVar2, LVar0, 0, 1, 0)
    Call(UpdateColliderTransform, LVarA)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(20)
    EndIf
    Call(obk_08_ShutterCrashRumble, 5)
    Call(MakeLerp, 20, LVar3, 5, 8)
    Label(30)
    Call(UpdateLerp)
    Call(RotateModel, LVar2, LVar0, 0, 1, 0)
    Call(UpdateColliderTransform, LVarA)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(30)
    EndIf
    Call(obk_08_ShutterCrashRumble, 5)
    IfNe(MapVar(11), 0)
        Goto(35)
    EndIf
    Add(LVar4, 1)
    IfNe(LVar4, 2)
        Goto(15)
    EndIf
    Label(35)
    Call(MakeLerp, LVar3, 0, 15, 1)
    Label(40)
    Call(UpdateLerp)
    Call(RotateModel, LVar2, LVar0, 0, 1, 0)
    Call(UpdateColliderTransform, LVarA)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(40)
    EndIf
    Call(PlaySoundWithVolume, 0xB0000012, 0)
    Call(PlaySoundAtModel, LVar2, 0xB0000012, 0)
    Return
    End
};

EvtScript TTYD64_obk_08_Script_ShakeWindows_Right = {
    Call(obk_08_ShutterCrashRumble, 5)
    Set(LVar3, 90)
    Call(MakeLerp, 0, LVar3, 15, 8)
    Label(10)
    Call(UpdateLerp)
    Call(RotateModel, LVar2, LVar0, 0, -1, 0)
    Call(UpdateColliderTransform, LVarA)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(10)
    EndIf
    Call(obk_08_ShutterCrashRumble, 5)
    Set(LVar4, 0)
    Label(15)
    Call(MakeLerp, LVar3, 20, 17, 8)
    Label(20)
    Call(UpdateLerp)
    Call(RotateModel, LVar2, LVar0, 0, -1, 0)
    Call(UpdateColliderTransform, LVarA)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(20)
    EndIf
    Call(obk_08_ShutterCrashRumble, 5)
    Call(MakeLerp, 20, LVar3, 8, 8)
    Label(30)
    Call(UpdateLerp)
    Call(RotateModel, LVar2, LVar0, 0, -1, 0)
    Call(UpdateColliderTransform, LVarA)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(30)
    EndIf
    Call(obk_08_ShutterCrashRumble, 5)
    IfNe(MapVar(11), 0)
        Goto(35)
    EndIf
    Add(LVar4, 1)
    IfNe(LVar4, 2)
        Goto(15)
    EndIf
    Label(35)
    Call(MakeLerp, LVar3, 0, 15, 1)
    Label(40)
    Call(UpdateLerp)
    Call(RotateModel, LVar2, LVar0, 0, -1, 0)
    Call(UpdateColliderTransform, LVarA)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(40)
    EndIf
    Return
    End
};

EvtScript TTYD64_obk_08_Script_ShakeWindows = {
    Call(ParentColliderToModel, 24, 36)
    Call(ParentColliderToModel, 25, 38)
    Call(ParentColliderToModel, 27, 41)
    Call(ParentColliderToModel, 28, 43)
    Call(ParentColliderToModel, 30, 46)
    Call(ParentColliderToModel, 31, 48)
    Call(ParentColliderToModel, 33, 51)
    Call(ParentColliderToModel, 34, 53)
    Label(10)
    Call(AwaitPlayerApproach, 0, -390, 150)
    Set(MapVar(11), 0)
    Set(LVar5, 0)
    Set(LVar2, 41)
    Set(LVarA, 27)
    Exec(TTYD64_obk_08_Script_ShakeWindows_Left)
    Wait(3)
    Set(LVar2, 43)
    Set(LVarA, 28)
    Exec(TTYD64_obk_08_Script_ShakeWindows_Right)
    Wait(2)
    Set(LVar5, 1)
    Set(LVar2, 51)
    Set(LVarA, 33)
    Exec(TTYD64_obk_08_Script_ShakeWindows_Left)
    Wait(3)
    Set(LVar2, 53)
    Set(LVarA, 34)
    Exec(TTYD64_obk_08_Script_ShakeWindows_Right)
    Wait(2)
    Set(LVar5, 0)
    Set(LVar2, 46)
    Set(LVarA, 30)
    Exec(TTYD64_obk_08_Script_ShakeWindows_Left)
    Wait(2)
    Set(LVar2, 48)
    Set(LVarA, 31)
    Exec(TTYD64_obk_08_Script_ShakeWindows_Right)
    Wait(2)
    Set(LVar5, 1)
    Set(LVar2, 36)
    Set(LVarA, 24)
    Exec(TTYD64_obk_08_Script_ShakeWindows_Left)
    Wait(3)
    Set(LVar2, 38)
    Set(LVarA, 25)
    Exec(TTYD64_obk_08_Script_ShakeWindows_Right)
    Wait(2)
    Call(AwaitPlayerLeave, 0, -390, 170)
    Set(MapVar(11), 1)
    Goto(10)
    Return
    End
};

EvtScript TTYD64_obk_08_Script_Main = {
    Set(GameByte(425), 13)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeNpcs, 0, Ref(obk_08_DefaultNPCs))
    ExecWait(obk_08_EVS_MakeEntities)
    Set(AreaFlag(8), 0)
    Exec(obk_08_EVS_SetupCabinets)
    Exec(TTYD64_obk_08_Script_ShakeWindows)
    Exec(TTYD64_obk_08_Script_80241970)
    BindTrigger(obk_08_EVS_ExitMap_obk_01_4, 256, 3, 1, 0)
    Exec(obk_08_EVS_EnterMap)
    Exec(obk_08_EVS_SetupMusic)
    Call(MakeItemEntity, 348, -174, 0, -314, 17, GameFlag(5089))
    Call(MakeItemEntity, 343, -44, 37, -421, 17, GameFlag(5088))
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_obk_08(void) {
    Mod_ReplaceScript("TTYD64", &obk_08_EVS_Main, &TTYD64_obk_08_Script_Main);
}
