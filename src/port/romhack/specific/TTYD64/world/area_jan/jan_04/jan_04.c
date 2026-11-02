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

extern BombTrigger jan_04_BombPos_SushieTree;
extern EvtScript jan_04_EVS_NpcIdle_Sushie;
extern EvtScript jan_04_EVS_PushNewPartnerSong;
extern EvtScript jan_04_EVS_ShakeTree_Sushie;
extern EvtScript jan_04_EVS_Sushie_ScoldPlayerLeaving;
extern EvtScript jan_04_EVS_Sushie_ShoutAtChildren;

API_CALLABLE(AdjustCam);
API_CALLABLE(CloseMessage);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(FadeOutMusic);
API_CALLABLE(GetSelfVar);
API_CALLABLE(PlayerFaceNpc);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(PopSong);
API_CALLABLE(ResetCam);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerSpeed);
API_CALLABLE(SetSelfVar);
API_CALLABLE(ShowMessageAtScreenPos);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(jan_04_ChangeNpcToPartner);
API_CALLABLE(jan_04_LoadPartyImage);

extern EvtScript TTYD64_jan_04_Script_Idle_802421EC;
extern EvtScript TTYD64_jan_04_Script_StopMusic;

// clang-format off
EvtScript TTYD64_jan_04_Script_Idle_802421EC = {
    Set(LVar0, GameFlag(1225))
    Set(LVar1, GameFlag(1226))
    Add(LVar0, LVar1)
    IfEq(LVar0, 0)
        ExecWait(jan_04_EVS_Sushie_ShoutAtChildren)
    Else
        Call(SetSelfVar, 0, 1)
    EndIf
    Set(AreaFlag(8), 0)
    BindTrigger(jan_04_EVS_ShakeTree_Sushie, 4096, 43, 1, 0)
    BindTrigger(jan_04_EVS_ShakeTree_Sushie, 0x100000, Ref(jan_04_BombPos_SushieTree), 1, 0)
    ExecGetTID(jan_04_EVS_Sushie_ScoldPlayerLeaving, LVar9)
    Label(0)
    Call(GetSelfVar, 0, LVar0)
    IfNe(LVar0, 10)
        Wait(1)
        Goto(0)
    EndIf
    KillThread(LVar9)
    Call(DisablePlayerInput, 1)
    Call(SetPlayerSpeed, Float(4.0))
    Call(PlayerMoveTo, 10, 0, 0)
    Call(PlayerFaceNpc, -1, 0)
    Call(SetNpcAnimation, -1, 0x70001)
    Call(AdjustCam, 0, Float(5.0), 20, 301, Float(17.0), Float(-7.0))
    Wait(10)
    Call(SpeakToPlayer, -1, 0x70004, 0x70001, 0, 0x1000A4)
    Call(SetPlayerAnimation, 0x80007)
    Wait(40)
    Call(SetPlayerAnimation, 0x10002)
    Call(SpeakToPlayer, -1, 0x70004, 0x70001, 0, 0x1000A5)
    Call(SetNpcAnimation, -1, 0x70007)
    Wait(30)
    Call(SetNpcAnimation, -1, 0x70001)
    Call(SpeakToPlayer, -1, 0x70004, 0x70001, 0, 0x1000A6)
    Call(SetPlayerAnimation, 0x80007)
    Wait(40)
    Call(SetPlayerAnimation, 0x10002)
    Call(SpeakToPlayer, -1, 0x70004, 0x70001, 0, 0x1000A7)
    Call(CloseMessage)
    Call(jan_04_ChangeNpcToPartner, 0, 7)
    Call(jan_04_LoadPartyImage)
    Exec(jan_04_EVS_PushNewPartnerSong)
    Wait(15)
    Call(ShowMessageAtScreenPos, 0x1D018F, 160, 40)
    Exec(TTYD64_jan_04_Script_StopMusic)
    Wait(10)
    Call(ResetCam, 0, Float(5.0))
    Set(GameByte(0), 15)
    Call(EnablePartnerAI)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_jan_04_Script_StopMusic = {
    Call(FadeOutMusic, 0, 500)
    Wait(15)
    Call(PopSong)
    Call(TTYD64_RaisePartnerMaxHP, 7)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_jan_04(void) {
    Mod_ReplaceScript("TTYD64", &jan_04_EVS_NpcIdle_Sushie, &TTYD64_jan_04_Script_Idle_802421EC);
}
