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

extern EvtScript jan_13_EVS_BindExitTriggers;
extern EvtScript jan_13_EVS_BoulderTremble;
extern EvtScript jan_13_EVS_Main;
extern EvtScript jan_13_EVS_MakeEntities;
extern EvtScript jan_13_EVS_ManageGeyserSounds;
extern EvtScript jan_13_EVS_ManageLargeGeyser;
extern EvtScript jan_13_EVS_ManageSmallGeyser;
extern EvtScript jan_13_EVS_SetupTrees;
extern Vec3i jan_13_GeyserSoundPositions[];

API_CALLABLE(CreatePushBlockGrid);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnableModel);
API_CALLABLE(EnableTexPanning);
API_CALLABLE(FacePlayerTowardPoint);
API_CALLABLE(GetGridIndexFromPos);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GetPushBlock);
API_CALLABLE(InterruptUsePartner);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlayAmbientSounds);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAt);
API_CALLABLE(PlaySoundAtPlayer);
API_CALLABLE(RandInt);
API_CALLABLE(ResetCam);
API_CALLABLE(RotateModel);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamDistance);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetCustomGfxBuilders);
API_CALLABLE(SetModelCustomGfx);
API_CALLABLE(SetMusic);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetPushBlock);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanOffset);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowEmote);
API_CALLABLE(StopSound);
API_CALLABLE(TranslateModel);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(jan_13_AdjustEnvSoundPosition);
API_CALLABLE(jan_13_GetPlayerPosAfterPush);
API_CALLABLE(jan_13_setup_gfx_geyser);

extern EvtScript TTYD64_jan_13_Script_Main_EnterWalk;
extern EvtScript TTYD64_jan_13_Script_80240FB8;
extern EvtScript TTYD64_jan_13_Script_PushGrid_UpdateCompletedAnimation;
extern EvtScript TTYD64_jan_13_Script_PushGrid_KnockBackMario;
extern EvtScript TTYD64_jan_13_Script_PushGrid_Init;

// clang-format off
EvtScript TTYD64_jan_13_Script_Main_EnterWalk = {
    Set(GameByte(425), 36)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Exec(jan_13_EVS_MakeEntities)
    Exec(TTYD64_jan_13_Script_PushGrid_Init)
    Exec(jan_13_EVS_SetupTrees)
    Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 5, 0x7FFFFE00)
    Set(LVar0, Ref(jan_13_EVS_BindExitTriggers))
    Exec(EnterWalk)
    Call(SetMusic, 0, 37, 0, 8)
    Call(PlayAmbientSounds, 3)
    Return
    End
};

EvtScript TTYD64_jan_13_Script_80240FB8 = {
    IfNe(AreaByte(3), MapVar(0))
        Set(AreaByte(3), MapVar(0))
        Set(MapFlag(10), 0)
        Call(StopSound, 0x8000001C)
        Call(StopSound, 0x8000001D)
        IfEq(MapVar(0), 5)
            IfEq(GameFlag(1271), 0)
                Return
            EndIf
        Else
            IfEq(MapVar(0), 10)
                Return
            EndIf
        EndIf
        Call(PlaySound, 0x8000001C)
        Set(MapFlag(10), 1)
        Set(LVar0, MapVar(0))
        Add(LVar0, 1)
        UseBuf((Bytecode) jan_13_GeyserSoundPositions)
        Loop(LVar0)
            BufRead3(LVar1, LVar2, LVar3)
        EndLoop
        Call(jan_13_AdjustEnvSoundPosition, MapFlag(10), LVar1, LVar2, LVar3)
    EndIf
    Return
    End
};

EvtScript TTYD64_jan_13_Script_PushGrid_UpdateCompletedAnimation = {
    Set(LFlag0, 0)
    Set(AreaByte(2), 0)
    Set(AreaByte(3), -1)
    Exec(jan_13_EVS_ManageGeyserSounds)
    Label(0)
    IfEq(GameFlag(1271), 1)
        IfEq(LFlag0, 0)
            Call(EnableModel, 59, 0)
            Call(ModifyColliderFlags, 0, 25, 0x7FFFFE00)
            Call(SetPushBlock, 0, 15, 0, 0)
            Call(SetPushBlock, 0, 16, 0, 0)
            Call(SetPushBlock, 0, 17, 0, 0)
            Call(SetPushBlock, 0, 18, 0, 0)
            Call(SetPushBlock, 0, 19, 0, 0)
            Call(SetPushBlock, 0, 15, 1, 0)
            Call(SetPushBlock, 0, 16, 1, 0)
            Call(SetPushBlock, 0, 17, 1, 0)
            Call(SetPushBlock, 0, 18, 1, 0)
            Call(SetPushBlock, 0, 19, 1, 0)
            Call(SetPushBlock, 0, 15, 2, 0)
            Call(SetPushBlock, 0, 16, 2, 0)
            Call(SetPushBlock, 0, 17, 2, 0)
            Call(SetPushBlock, 0, 18, 2, 0)
            Call(SetPushBlock, 0, 19, 2, 0)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetPushBlock, 0, 28, 6, LVar0)
    IfEq(LVar0, 0)
        Set(MapVar(0), 0)
        Goto(1)
    EndIf
    Call(GetPushBlock, 0, 25, 4, LVar0)
    IfEq(LVar0, 0)
        Set(MapVar(0), 1)
        Goto(1)
    EndIf
    Call(GetPushBlock, 0, 21, 8, LVar0)
    IfEq(LVar0, 0)
        Set(MapVar(0), 2)
        Goto(1)
    EndIf
    Call(GetPushBlock, 0, 4, 4, LVar0)
    IfEq(LVar0, 0)
        Set(MapVar(0), 3)
        Goto(1)
    EndIf
    Call(GetPushBlock, 0, 14, 6, LVar0)
    IfEq(LVar0, 0)
        Set(MapVar(0), 4)
        Goto(1)
    EndIf
    IfEq(GameFlag(1271), 0)
        Call(DisablePlayerInput, 1)
        Call(SetPushBlock, 0, 15, 0, 0)
        Call(SetPushBlock, 0, 16, 0, 0)
        Call(SetPushBlock, 0, 17, 0, 0)
        Call(SetPushBlock, 0, 18, 0, 0)
        Call(SetPushBlock, 0, 19, 0, 0)
        Call(SetPushBlock, 0, 15, 1, 0)
        Call(SetPushBlock, 0, 16, 1, 0)
        Call(SetPushBlock, 0, 17, 1, 0)
        Call(SetPushBlock, 0, 18, 1, 0)
        Call(SetPushBlock, 0, 19, 1, 0)
        Call(SetPushBlock, 0, 15, 2, 0)
        Call(SetPushBlock, 0, 16, 2, 0)
        Call(SetPushBlock, 0, 17, 2, 0)
        Call(SetPushBlock, 0, 18, 2, 0)
        Call(SetPushBlock, 0, 19, 2, 0)
        Set(MapVar(0), 5)
        Wait(30)
        Loop(2)
            Exec(jan_13_EVS_BoulderTremble)
            Call(RotateModel, 59, 3, 0, Float(0.2001953125), 1)
            Wait(8)
            Call(RotateModel, 59, -3, 0, Float(0.2001953125), 1)
            Wait(8)
        EndLoop
        Thread
            Call(PlaySoundAtPlayer, 610, 0)
            Call(ShowEmote, 0, 0, 0, 20, 0, 0, 0, 0, 0)
            Call(GetModelCenter, 59)
            Call(FacePlayerTowardPoint, LVar0, LVar2, 4)
            Call(GetPlayerPos, LVar3, LVar1, LVar2)
            Set(LVar4, LVar0)
            Set(LVar5, LVar0)
            Sub(LVar4, 120)
            Add(LVar5, 120)
            Switch(LVar3)
            CaseRange(LVar4, LVar5)
                Add(LVar0, LVar3)
                Div(LVar0, 2)
            EndSwitch
            Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
            Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
            Call(SetCamDistance, 0, 400)
            Call(SetCamSpeed, 0, Float(3.0))
            Call(PanToTarget, 0, 0, 1)
        EndThread
        Loop(3)
            Exec(jan_13_EVS_BoulderTremble)
            Call(RotateModel, 59, 5, 0, Float(0.2001953125), 1)
            Wait(5)
            Call(RotateModel, 59, -5, 0, Float(0.2001953125), 1)
            Wait(5)
        EndLoop
        Loop(7)
            Exec(jan_13_EVS_BoulderTremble)
            Call(RotateModel, 59, 7, 0, Float(0.2001953125), 1)
            Wait(3)
            Call(RotateModel, 59, -7, 0, Float(0.2001953125), 1)
            Wait(3)
        EndLoop
        Loop(8)
            Call(RandInt, 2, LVar0)
            Switch(LVar0)
            CaseEq(0)
                Call(PlayEffect_impl, 6, 1, 8, 0, -82, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            CaseEq(1)
                Call(PlayEffect_impl, 6, 1, 38, 0, -62, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            CaseEq(2)
                Call(PlayEffect_impl, 6, 1, 78, 0, -77, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            EndSwitch
            Exec(jan_13_EVS_BoulderTremble)
            Call(RotateModel, 59, 10, 0, Float(0.2001953125), 1)
            Wait(3)
            Call(RotateModel, 59, -10, 0, Float(0.2001953125), 1)
            Wait(3)
        EndLoop
        Thread
            Call(ShakeCam, 0, 0, 15, Float(0.400390625))
        EndThread
        Call(PlaySoundAt, 0x8000001D, 0, 37, 0, -138)
        Set(AreaByte(2), 1)
        Thread
            Loop(200)
                Call(RotateModel, 59, 10, 0, Float(0.2001953125), 1)
                Wait(3)
                Call(RotateModel, 59, -10, 0, Float(0.2001953125), 1)
                Wait(3)
            EndLoop
        EndThread
        Set(LVar0, 0)
        Loop(18)
            Add(LVar0, 3)
            Call(TranslateModel, 59, 0, LVar0, 0)
            Wait(1)
        EndLoop
        Loop(60)
            Call(TranslateModel, 59, 0, LVar0, 0)
            Wait(1)
        EndLoop
        Set(AreaByte(2), 2)
        Loop(25)
            Add(LVar0, 8)
            Call(TranslateModel, 59, 0, LVar0, 0)
            Wait(1)
        EndLoop
        Set(LVar0, 200)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Loop(60)
            Add(LVar1, 1)
            Sub(LVar0, LVar1)
            Add(LVar2, 10)
            Add(LVar2, -10)
            Call(TranslateModel, 59, -200, LVar0, -500)
            Call(RotateModel, 59, LVar2, -1, Float(0.099609375), Float(0.099609375))
            Wait(1)
        EndLoop
        Call(EnableModel, 59, 0)
        Call(ModifyColliderFlags, 0, 25, 0x7FFFFE00)
        Set(GameFlag(1271), 1)
        Set(LFlag0, 1)
        Call(ResetCam, 0, Float(5.0))
        Call(DisablePlayerInput, 0)
    Else
        Call(GetPushBlock, 0, 17, 0, LVar0)
        IfEq(LVar0, 0)
            Set(MapVar(0), 5)
            Goto(1)
        EndIf
        Call(GetPushBlock, 0, 20, 3, LVar0)
        IfEq(LVar0, 0)
            Set(MapVar(0), 6)
            Goto(1)
        EndIf
        Call(GetPushBlock, 0, 10, 4, LVar0)
        IfEq(LVar0, 0)
            Set(MapVar(0), 7)
            Goto(1)
        EndIf
        Call(GetPushBlock, 0, 9, 9, LVar0)
        IfEq(LVar0, 0)
            Set(MapVar(0), 8)
            Goto(1)
        EndIf
        Call(GetPushBlock, 0, 26, 9, LVar0)
        IfEq(LVar0, 0)
            Set(MapVar(0), 9)
            IfEq(GameFlag(5386), 0)
                Set(GameFlag(5386), 1)
                Call(MakeItemEntity, 348, 261, 0, 89, 5, GameFlag(5387))
                Call(TTYD64_SetPlayerAnimFlagBits, PA_FLAG_NO_OOB_RESPAWN, 1)
                Call(PlaySound, 8197)
            EndIf
            Goto(1)
        EndIf
    EndIf
    Set(MapVar(0), 10)
    Label(1)
    Exec(jan_13_EVS_ManageGeyserSounds)
    Wait(1)
    Goto(0)
    Return
    End
};

EvtScript TTYD64_jan_13_Script_PushGrid_KnockBackMario = {
    Loop(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(GetGridIndexFromPos, 0, LVar0, LVar1, LVar2, LVar3, LVar4)
        Set(LVar5, 0)
        IfEq(MapVar(0), 0)
            IfEq(LVar3, 28)
                IfEq(LVar4, 6)
                    Set(LVar5, 1)
                EndIf
            EndIf
        EndIf
        IfEq(MapVar(0), 1)
            IfEq(LVar3, 25)
                IfEq(LVar4, 4)
                    Set(LVar5, 1)
                EndIf
            EndIf
        EndIf
        IfEq(MapVar(0), 2)
            IfEq(LVar3, 21)
                IfEq(LVar4, 8)
                    Set(LVar5, 1)
                EndIf
            EndIf
        EndIf
        IfEq(MapVar(0), 3)
            IfEq(LVar3, 4)
                IfEq(LVar4, 4)
                    Set(LVar5, 1)
                EndIf
            EndIf
        EndIf
        IfEq(MapVar(0), 4)
            IfEq(LVar3, 14)
                IfEq(LVar4, 6)
                    Set(LVar5, 1)
                EndIf
            EndIf
        EndIf
        IfEq(MapVar(0), 5)
            IfEq(LVar3, 17)
                IfEq(LVar4, 0)
                    Set(LVar5, 1)
                EndIf
            EndIf
        EndIf
        IfEq(MapVar(0), 5)
            IfEq(LVar3, 16)
                IfEq(LVar4, 0)
                    Set(LVar5, 1)
                EndIf
            EndIf
        EndIf
        IfEq(MapVar(0), 5)
            IfEq(LVar3, 18)
                IfEq(LVar4, 0)
                    Set(LVar5, 1)
                EndIf
            EndIf
        EndIf
        IfEq(MapVar(0), 5)
            IfEq(LVar3, 19)
                IfEq(LVar4, 0)
                    Set(LVar5, 1)
                EndIf
            EndIf
        EndIf
        IfEq(MapVar(0), 6)
            IfEq(LVar3, 20)
                IfEq(LVar4, 3)
                    Set(LVar5, 1)
                EndIf
            EndIf
        EndIf
        IfEq(MapVar(0), 7)
            IfEq(LVar3, 10)
                IfEq(LVar4, 4)
                    Set(LVar5, 1)
                EndIf
            EndIf
        EndIf
        IfEq(MapVar(0), 8)
            IfEq(LVar3, 9)
                IfEq(LVar4, 9)
                    Set(LVar5, 1)
                EndIf
            EndIf
        EndIf
        IfEq(MapVar(0), 9)
            IfEq(LVar3, 26)
                IfEq(LVar4, 9)
                    Set(LVar5, 1)
                EndIf
            EndIf
        EndIf
        IfEq(LVar5, 1)
            Call(DisablePlayerInput, 1)
            Call(jan_13_GetPlayerPosAfterPush)
            Call(InterruptUsePartner)
            Loop(10)
                Call(GetPlayerPos, LVar3, LVar4, LVar5)
                IfLt(LVar4, 40)
                    AddF(LVar4, 6)
                EndIf
                MulF(LVar3, 10)
                MulF(LVar5, 10)
                AddF(LVar3, LVar0)
                AddF(LVar5, LVar2)
                DivF(LVar3, 11)
                DivF(LVar5, 11)
                Call(SetPlayerPos, LVar3, LVar4, LVar5)
                Call(SetPlayerAnimation, 0x1002E)
                Wait(1)
            EndLoop
            Call(SetPlayerAnimation, 0x10002)
            Call(DisablePlayerInput, 0)
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_jan_13_Script_PushGrid_Init = {
    IfEq(GameFlag(5386), 1)
        Call(MakeItemEntity, 348, 230, 0, 120, 17, GameFlag(5387))
    EndIf
    Call(CreatePushBlockGrid, 0, 32, 12, -400, 0, -150, 0)
    Call(SetPushBlock, 0, 7, 5, 1)
    Call(SetPushBlock, 0, 13, 9, 1)
    Call(SetPushBlock, 0, 16, 5, 1)
    Call(SetPushBlock, 0, 21, 2, 1)
    Call(SetPushBlock, 0, 22, 4, 1)
    Call(SetPushBlock, 0, 26, 6, 1)
    Call(SetPushBlock, 0, 27, 7, 1)
    Call(SetPushBlock, 0, 5, 8, 1)
    Call(SetPushBlock, 0, 17, 8, 1)
    Call(SetPushBlock, 0, 8, 9, 1)
    Call(SetPushBlock, 0, 22, 8, 1)
    Call(SetPushBlock, 0, 15, 0, 2)
    Call(SetPushBlock, 0, 16, 0, 2)
    Call(SetPushBlock, 0, 17, 0, 2)
    Call(SetPushBlock, 0, 18, 0, 2)
    Call(SetPushBlock, 0, 19, 0, 2)
    Call(SetPushBlock, 0, 15, 1, 2)
    Call(SetPushBlock, 0, 16, 1, 2)
    Call(SetPushBlock, 0, 17, 1, 2)
    Call(SetPushBlock, 0, 18, 1, 2)
    Call(SetPushBlock, 0, 19, 1, 2)
    Call(SetPushBlock, 0, 15, 2, 2)
    Call(SetPushBlock, 0, 16, 2, 2)
    Call(SetPushBlock, 0, 17, 2, 2)
    Call(SetPushBlock, 0, 18, 2, 2)
    Call(SetPushBlock, 0, 19, 2, 2)
    Set(LVar0, 0)
    Loop(32)
        Call(SetPushBlock, 0, LVar0, 0, 2)
        Add(LVar0, 1)
    EndLoop
    Set(LVar0, 0)
    Loop(15)
        Call(SetPushBlock, 0, LVar0, 1, 2)
        Add(LVar0, 1)
    EndLoop
    Set(LVar0, 20)
    Loop(12)
        Call(SetPushBlock, 0, LVar0, 1, 2)
        Add(LVar0, 1)
    EndLoop
    Set(LVar0, 0)
    Loop(3)
        Call(SetPushBlock, 0, LVar0, 2, 2)
        Add(LVar0, 1)
    EndLoop
    Set(LVar0, 10)
    Loop(4)
        Call(SetPushBlock, 0, LVar0, 2, 2)
        Add(LVar0, 1)
    EndLoop
    Set(LVar0, 26)
    Loop(6)
        Call(SetPushBlock, 0, LVar0, 2, 2)
        Add(LVar0, 1)
    EndLoop
    Set(LVar0, 0)
    Loop(2)
        Call(SetPushBlock, 0, LVar0, 3, 2)
        Add(LVar0, 1)
    EndLoop
    Set(LVar0, 10)
    Loop(4)
        Call(SetPushBlock, 0, LVar0, 3, 2)
        Add(LVar0, 1)
    EndLoop
    Exec(TTYD64_jan_13_Script_PushGrid_UpdateCompletedAnimation)
    Set(LVar0, 46)
    Set(LVar1, 0)
    Set(LVar2, 19)
    Call(ModifyColliderFlags, 0, LVar2, 0x7FFFFE00)
    Exec(jan_13_EVS_ManageSmallGeyser)
    Set(LVar0, 48)
    Set(LVar1, 1)
    Set(LVar2, 20)
    Call(ModifyColliderFlags, 0, LVar2, 0x7FFFFE00)
    Exec(jan_13_EVS_ManageSmallGeyser)
    Set(LVar0, 50)
    Set(LVar1, 2)
    Set(LVar2, 21)
    Call(ModifyColliderFlags, 0, LVar2, 0x7FFFFE00)
    Exec(jan_13_EVS_ManageSmallGeyser)
    Set(LVar0, 52)
    Set(LVar1, 3)
    Set(LVar2, 22)
    Call(ModifyColliderFlags, 0, LVar2, 0x7FFFFE00)
    Exec(jan_13_EVS_ManageSmallGeyser)
    Set(LVar0, 54)
    Set(LVar1, 4)
    Set(LVar2, 23)
    Call(ModifyColliderFlags, 0, LVar2, 0x7FFFFE00)
    Exec(jan_13_EVS_ManageSmallGeyser)
    Set(LVar0, 56)
    Set(LVar1, 5)
    Set(LVar2, 26)
    Call(ModifyColliderFlags, 0, LVar2, 0x7FFFFE00)
    Exec(jan_13_EVS_ManageLargeGeyser)
    Set(LVar0, 66)
    Set(LVar1, 6)
    Set(LVar2, 29)
    Call(ModifyColliderFlags, 0, LVar2, 0x7FFFFE00)
    Exec(jan_13_EVS_ManageSmallGeyser)
    Set(LVar0, 68)
    Set(LVar1, 7)
    Set(LVar2, 30)
    Call(ModifyColliderFlags, 0, LVar2, 0x7FFFFE00)
    Exec(jan_13_EVS_ManageSmallGeyser)
    Set(LVar0, 70)
    Set(LVar1, 8)
    Set(LVar2, 31)
    Call(ModifyColliderFlags, 0, LVar2, 0x7FFFFE00)
    Exec(jan_13_EVS_ManageSmallGeyser)
    Set(LVar0, 72)
    Set(LVar1, 9)
    Set(LVar2, 32)
    Call(ModifyColliderFlags, 0, LVar2, 0x7FFFFE00)
    Exec(jan_13_EVS_ManageSmallGeyser)
    Exec(TTYD64_jan_13_Script_PushGrid_KnockBackMario)
    Call(EnableTexPanning, 46, 1)
    Call(EnableTexPanning, 48, 1)
    Call(EnableTexPanning, 50, 1)
    Call(EnableTexPanning, 52, 1)
    Call(EnableTexPanning, 54, 1)
    Call(EnableTexPanning, 56, 1)
    Call(EnableTexPanning, 66, 1)
    Call(EnableTexPanning, 68, 1)
    Call(EnableTexPanning, 70, 1)
    Call(EnableTexPanning, 72, 1)
    Call(SetModelCustomGfx, 46, 0, -1)
    Call(SetModelCustomGfx, 48, 0, -1)
    Call(SetModelCustomGfx, 50, 0, -1)
    Call(SetModelCustomGfx, 52, 0, -1)
    Call(SetModelCustomGfx, 54, 0, -1)
    Call(SetModelCustomGfx, 56, 0, -1)
    Call(SetModelCustomGfx, 66, 0, -1)
    Call(SetModelCustomGfx, 68, 0, -1)
    Call(SetModelCustomGfx, 70, 0, -1)
    Call(SetModelCustomGfx, 72, 0, -1)
    Call(SetCustomGfxBuilders, 0, (Bytecode) jan_13_setup_gfx_geyser, 0)
    Set(LVar0, 0)
    Loop(0)
        Sub(LVar0, 2000)
        IfLt(LVar0, -65536)
            Add(LVar0, 0x10000)
        EndIf
        Call(SetTexPanOffset, 1, 0, 0, LVar0)
        Wait(1)
    EndLoop
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_jan_13(void) {
    Mod_ReplaceScript("TTYD64", &jan_13_EVS_Main, &TTYD64_jan_13_Script_Main_EnterWalk);
    Mod_ReplaceScript("TTYD64", &jan_13_EVS_ManageGeyserSounds, &TTYD64_jan_13_Script_80240FB8);
}
