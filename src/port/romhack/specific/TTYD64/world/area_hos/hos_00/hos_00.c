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

extern NpcGroupList hos_00_DefaultNPCs;
extern EvtScript hos_00_EVS_ConfusedTwinkLookingAround;
extern EvtScript hos_00_EVS_EnterMap;
extern EvtScript hos_00_EVS_Main;
extern EvtScript hos_00_EVS_MakeEntities;
extern EvtScript hos_00_EVS_PlayKammyKoopaSong;
extern EvtScript hos_00_EVS_SetupMusic;
extern EvtScript hos_00_EVS_Starfall_Directed;
extern EvtScript hos_00_EVS_TexPan_Unknown;
extern EvtScript hos_00_EVS_Twink_CancelHoverOffset;
extern EvtScript hos_00_EVS_Twink_CarryItem;
extern EvtScript hos_00_EVS_UpdateFacingMagikoopa;
extern Vec3f hos_00_FlightPath_Magikoopa[];
extern Vec3f hos_00_TwinkArrivePath[];
extern NpcGroupList hos_00_WishingNPCs;

API_CALLABLE(ContinueSpeech);
API_CALLABLE(DisableCameraLeadingPlayer);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetNextPathPos);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetNpcVar);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(LoadPath);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(NpcFacePlayer);
API_CALLABLE(NpcJump0);
API_CALLABLE(NpcMoveTo);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlaySoundAtPlayer);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamDistance);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamPitch);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetItemPos);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcJumpscale);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetNpcRotation);
API_CALLABLE(SetNpcSpeed);
API_CALLABLE(SetNpcVar);
API_CALLABLE(SetNpcYaw);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowChoice);
API_CALLABLE(ShowEmote);
API_CALLABLE(ShowGotItem);
API_CALLABLE(ShowMessageAtScreenPos);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(WaitForCam);
API_CALLABLE(func_802CF56C);
API_CALLABLE(hos_00_EnableActionCommands);
API_CALLABLE(hos_00_HavePartyFaceTwink);

extern EvtScript TTYD64_hos_00_Script_Main;
extern u8 TTYD64_hos_00_String_LuckyStarAbout[];
extern EvtScript TTYD64_hos_00_Script_Cutscene_Twink;

// clang-format off
EvtScript TTYD64_hos_00_Script_Main = {
    Set(GameByte(425), 27)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Set(GameFlag(1964), 1)
    Set(GameFlag(263), 0)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 3)
        Call(MakeNpcs, 0, Ref(hos_00_WishingNPCs))
    Else
        Call(MakeNpcs, 0, Ref(hos_00_DefaultNPCs))
    EndIf
    ExecWait(hos_00_EVS_MakeEntities)
    Call(GetEntryID, LVar0)
    IfNe(LVar0, 3)
        Exec(hos_00_EVS_Starfall_Directed)
    EndIf
    ExecWait(hos_00_EVS_SetupMusic)
    IfEq(GameByte(0), -105)
        IfEq(AreaFlag(180), 0)
            Wait(50)
            Set(AreaFlag(180), 1)
        EndIf
        Exec(TTYD64_hos_00_Script_Cutscene_Twink)
    EndIf
    Exec(hos_00_EVS_EnterMap)
    Exec(hos_00_EVS_TexPan_Unknown)
    Return
    End
};

u8 TTYD64_hos_00_String_LuckyStarAbout[] = {
    0xFC, 0x01, 0xFF, 0x2F, 0x02, 0x34, 0x48, 0x41, 0x54, 0x07, 0x53, 0xF7,
    0x54, 0x48, 0x45, 0xF7, 0x02, 0xFF, 0x05, 0x20, 0x2C, 0x55, 0x43, 0x4B,
    0x59, 0xF7, 0x33, 0x54, 0x41, 0x52, 0xFF, 0x05, 0x0A, 0x02, 0xF7, 0x46,
    0x52, 0x4F, 0x4D, 0xF0, 0x30, 0x52, 0x49, 0x4E, 0x43, 0x45, 0x53, 0x53,
    0xF7, 0x30, 0x45, 0x41, 0x43, 0x48, 0x0E, 0xF0, 0xF1, 0xFB, 0x37, 0x45,
    0x41, 0x52, 0xF7, 0x49, 0x54, 0xF7, 0x41, 0x53, 0xF7, 0x41, 0xF7, 0x47,
    0x4F, 0x4F, 0x44, 0xF7, 0x4C, 0x55, 0x43, 0x4B, 0xF7, 0x43, 0x48, 0x41,
    0x52, 0x4D, 0x0E, 0xF0, 0xF1, 0xFD
};

EvtScript TTYD64_hos_00_Script_Cutscene_Twink = {
    Loop(0)
        Wait(1)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        IfLt(LVar0, -100)
            BreakLoop
        EndIf
    EndLoop
    Call(DisablePlayerInput, 1)
    Call(func_802CF56C, 2)
    Thread
        Add(LVar0, -20)
        Call(PlayerMoveTo, LVar0, LVar2, 10)
    EndThread
    Call(SetNpcPos, 0, 50, 180, 0)
    Call(SetNpcJumpscale, 0, 0)
    Add(LVar0, -10)
    Call(NpcJump0, 0, LVar0, 20, LVar2, 15)
    Call(PlaySoundAtPlayer, 225, 0)
    Call(SetPlayerAnimation, 0x10023)
    Call(SetNpcAnimation, 0, 0x20000E)
    Thread
        Call(SetNpcAnimation, 0, 0x200016)
        Call(SetNpcJumpscale, 0, Float(0.599609375))
        Call(GetNpcPos, 0, LVar0, LVar1, LVar2)
        Add(LVar0, -100)
        Call(NpcJump0, 0, LVar0, 10, LVar2, 20)
        Call(SetPlayerAnimation, 0x10002)
    EndThread
    Thread
        Call(ShakeCam, 0, 0, 5, Float(2.0))
    EndThread
    Thread
        Set(LVar3, 360)
        Loop(3)
            Label(22)
            Wait(1)
            Sub(LVar3, 45)
            IfGt(LVar3, 0)
                Call(SetNpcRotation, 0, 0, LVar3, 0)
                IfEq(LVar3, 270)
                    Call(SetNpcAnimation, 0, 0x20001A)
                EndIf
                IfEq(LVar3, 90)
                    Call(SetNpcAnimation, 0, 0x200016)
                EndIf
                Goto(22)
            EndIf
        EndLoop
        Call(SetNpcRotation, 0, 0, 0, 0)
    EndThread
    Call(ShowMessageAtScreenPos, 0xA000D, 160, 40)
    Call(SetMusic, 0, 112, 0, 8)
    Call(SetPlayerAnimation, 0x10002)
    Call(SetNpcAnimation, 0, 0x200001)
    Call(NpcFacePlayer, 0, 0)
    Call(SpeakToPlayer, 0, 0x20000C, 0x200001, 0, 0xA000E)
    Call(DisableCameraLeadingPlayer)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Add(LVar0, -20)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
    Call(SetCamDistance, 0, 275)
    Call(SetCamPitch, 0, Float(16.0), Float(-8.5))
    Call(SetCamSpeed, 0, Float(3.0))
    Call(PanToTarget, 0, 0, 1)
    Call(SetNpcSpeed, 0, Float(3.0))
    Call(GetNpcPos, 0, LVar0, LVar1, LVar2)
    Add(LVar0, 40)
    Call(NpcMoveTo, 0, LVar0, LVar2, 0)
    Call(ShowEmote, 0, 1, 45, 20, 1, 0, 0, 0, 0)
    Wait(20)
    Call(SetNpcAnimation, 0, 0x20000F)
    Call(SetNpcJumpscale, 0, Float(1.0))
    Loop(2)
        Call(GetNpcPos, 0, LVar0, LVar1, LVar2)
        Call(NpcJump0, 0, LVar0, LVar1, LVar2, 15)
    EndLoop
    Call(DisablePartnerAI, 0)
    Call(SetNpcJumpscale, -4, 0)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Add(LVar0, 25)
    Call(NpcJump0, -4, LVar0, LVar1, LVar2, 10)
    Call(SpeakToPlayer, 0, 0x200009, 0x200001, 0, 0xA000F)
    Wait(5)
    Call(GetNpcPos, 0, LVar4, LVar5, LVar6)
    Call(LoadPath, 70, (Bytecode) hos_00_TwinkArrivePath, 10, 0)
    Label(1)
    Call(GetNextPathPos)
    AddF(LVar1, LVar4)
    AddF(LVar2, LVar5)
    AddF(LVar3, LVar6)
    Call(SetNpcPos, 0, LVar1, LVar2, LVar3)
    Call(hos_00_HavePartyFaceTwink)
    Wait(1)
    IfEq(LVar0, 1)
        Goto(1)
    EndIf
    Call(SetNpcAnimation, 0, 0x200001)
    Wait(10)
    Call(SpeakToPlayer, 0, 0x200009, 0x200001, 0, 0xA0010)
    Call(SetNpcYaw, 0, 270)
    Call(SetNpcAnimation, 0, 0x20001A)
    Call(SpeakToPlayer, 0, -1, -1, 5, 0xA0011)
    Call(GetNpcPos, 0, LVar0, LVar1, LVar2)
    Add(LVar1, 15)
    Call(MakeItemEntity, 7, LVar0, LVar1, LVar2, 1, 0)
    Set(MapVar(10), LVar0)
    ExecGetTID(hos_00_EVS_Twink_CancelHoverOffset, LVar8)
    ExecGetTID(hos_00_EVS_Twink_CarryItem, LVar9)
    Call(SetNpcAnimation, 0, 0x200017)
    Call(ContinueSpeech, 0, -1, -1, 512, 0xA0012)
    Call(GetPlayerPos, LVar5, LVar3, LVar4)
    Add(LVar5, -30)
    Call(NpcMoveTo, 0, LVar5, LVar4, 15)
    KillThread(LVar9)
    KillThread(LVar8)
    Thread
        Call(GetNpcPos, 0, LVar0, LVar1, LVar2)
        Add(LVar1, 15)
        Set(LVar4, LVar1)
        Add(LVar4, 30)
        Set(LVar3, LVar0)
        Call(MakeLerp, LVar1, LVar4, 7, 4)
        Loop(0)
            Call(UpdateLerp)
            Call(SetItemPos, MapVar(10), LVar3, LVar0, LVar2)
            Wait(1)
            Add(LVar3, 2)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(GetPlayerPos, LVar5, LVar6, LVar7)
        Add(LVar6, 38)
        Call(MakeLerp, LVar0, LVar6, 7, 1)
        Loop(0)
            Call(UpdateLerp)
            Call(SetItemPos, MapVar(10), LVar3, LVar0, LVar2)
            Wait(1)
            Add(LVar3, 2)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(RemoveItemEntity, MapVar(10))
    EndThread
    Call(SetNpcAnimation, 0, 0x200014)
    Wait(11)
    Call(SetNpcAnimation, 0, 0x200015)
    Set(LVar0, 7)
    Set(LVar1, 4)
    Call(ShowGotItem, LVar0, 1, 0)
    Call(TTYD64_maps_AddKeyItem, LVar0)
    Call(hos_00_EnableActionCommands)
    Call(SetNpcAnimation, 0, 0x200001)
    Wait(20)
    IfEq(GameByte(4106), 0)
        Call(SpeakToPlayer, 0, 0x200009, 0x200001, 0, 0xA0013)
        Call(ShowChoice, 0x1E0013)
        IfEq(LVar0, 1)
            Call(ContinueSpeech, 0, 0x200009, 0x200001, 0, 0xA0014)
            Call(ShowChoice, 0x1E0013)
            IfNe(LVar0, 0)
                Call(ContinueSpeech, 0, 0x200009, 0x200001, 0, 0xA0015)
            Else
                Goto(15)
            EndIf
        Else
            Label(15)
            Call(ContinueSpeech, 0, 0x200009, 0x200001, 0, 0xA0016)
            Call(SpeakToPlayer, -4, 0x10008, 0x10001, 0, 0xA0017)
            Call(SpeakToPlayer, 0, 0x200009, 0x200001, 0, 0xA0018)
            Call(SetPlayerAnimation, 0x80007)
            Call(SetNpcVar, 0, 0, 1)
            Loop(0)
                Call(GetNpcVar, 0, 0, LVar0)
                IfEq(LVar0, 2)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        EndIf
    Else
        Call(SpeakToPlayer, 0, 0x200009, 0x200001, 0, (Bytecode) TTYD64_hos_00_String_LuckyStarAbout)
    EndIf
    Call(DisablePartnerAI, 0)
    Call(SetNpcAnimation, -4, 262)
    Call(SpeakToPlayer, 0, 0x200009, 0x200001, 0, 0xA002F)
    Call(SpeakToPlayer, -4, 0x10008, 0x10001, 0, 0xA0030)
    Wait(20)
    Exec(hos_00_EVS_PlayKammyKoopaSong)
    Call(ShowMessageAtScreenPos, 0xA0031, 320, 0)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(SetCamSpeed, 0, Float(3.0))
    Call(PanToTarget, 0, 0, 1)
    Call(WaitForCam, 0, Float(1.0))
    Thread
        Wait(20)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Add(LVar0, -250)
        Div(LVar0, 2)
        Call(SetPanTarget, 0, -250, 53, 0)
        Call(SetCamSpeed, 0, Float(1.400390625))
        Call(PanToTarget, 0, 0, 1)
        Call(WaitForCam, 0, Float(1.0))
        Wait(10)
        Call(SetPanTarget, 0, LVar0, 0, 0)
        Call(SetCamSpeed, 0, Float(2.0))
        Call(PanToTarget, 0, 0, 1)
        Call(WaitForCam, 0, Float(1.0))
    EndThread
    ExecGetTID(hos_00_EVS_UpdateFacingMagikoopa, LVarA)
    Call(LoadPath, 67, (Bytecode) hos_00_FlightPath_Magikoopa, 5, 0)
    Label(2)
    Call(GetNextPathPos)
    Call(SetNpcPos, 1, LVar1, LVar2, LVar3)
    Wait(1)
    IfEq(LVar0, 1)
        Goto(2)
    EndIf
    KillThread(LVarA)
    ChildThread
        Loop(0)
            Loop(10)
                Call(GetNpcPos, 1, LVar0, LVar1, LVar2)
                Add(LVar1, 1)
                Call(SetNpcPos, 1, LVar0, LVar1, LVar2)
                Wait(2)
            EndLoop
            Wait(3)
            Loop(10)
                Call(GetNpcPos, 1, LVar0, LVar1, LVar2)
                Add(LVar1, -1)
                Call(SetNpcPos, 1, LVar0, LVar1, LVar2)
                Wait(2)
            EndLoop
            Wait(3)
        EndLoop
    EndChildThread
    Call(SetNpcAnimation, 1, 0x570000)
    Loop(3)
        Call(SetNpcRotation, 1, 0, 0, 10)
        Wait(1)
        Call(SetNpcRotation, 1, 0, 0, 0)
        Wait(1)
    EndLoop
    Wait(20)
    ExecGetTID(hos_00_EVS_ConfusedTwinkLookingAround, LVarA)
    Call(SpeakToPlayer, 0, 0x200009, 0x200000, 5, 0xA0032)
    KillThread(LVarA)
    Wait(10)
    Call(GetNpcPos, 1, LVar0, LVar1, LVar2)
    Call(UseSettingsFrom, 0, LVar0, 0, LVar2)
    Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
    Call(SetCamDistance, 0, Float(260.0))
    Call(SetCamPitch, 0, Float(13.0), Float(-8.0))
    Call(SetCamSpeed, 0, Float(90.0))
    Call(PanToTarget, 0, 0, 1)
    Wait(1)
    Call(SpeakToPlayer, 1, 0x570009, 0x570000, 512, 0xA0033)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Add(LVar0, -250)
    Div(LVar0, 2)
    Call(UseSettingsFrom, 0, LVar0, 0, 0)
    Call(SetPanTarget, 0, LVar0, 0, 0)
    Call(SetCamSpeed, 0, Float(4.0))
    Call(PanToTarget, 0, 0, 1)
    Call(SetNpcVar, 1, 0, 1)
    Call(EnablePartnerAI)
    Unbind
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_hos_00(void) {
    Mod_ReplaceScript("TTYD64", &hos_00_EVS_Main, &TTYD64_hos_00_Script_Main);
    TTYD64_maps_BindInlineMessage(TTYD64_hos_00_Script_Cutscene_Twink, TTYD64_hos_00_String_LuckyStarAbout);
}
