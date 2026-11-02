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

extern EvtScript tik_15_EVS_NpcInteract_RipCheato;
extern EvtScript tik_15_GiveItemReward;

API_CALLABLE(AddCoin);
API_CALLABLE(AddItem);
API_CALLABLE(AddStarPieces);
API_CALLABLE(ContinueSpeech);
API_CALLABLE(EndSpeech);
API_CALLABLE(ShowChoice);
API_CALLABLE(ShowCoinCounter);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(tik_15_CheckPlayerHasEnoughCoins);
API_CALLABLE(tik_15_CheckPlayerHasEnoughRoom);
API_CALLABLE(tik_15_GetNextCheatoItem);

extern EvtScript TTYD64_tik_15_Script_Interact_80242824;

// clang-format off
EvtScript TTYD64_tik_15_Script_Interact_80242824 = {
    IfEq(AreaFlag(2), 0)
        IfEq(GameFlag(389), 0)
            Set(LVar0, 0x80001)
            Set(GameFlag(389), 1)
        Else
            Set(LVar0, 0x80002)
        EndIf
        Set(AreaFlag(2), 1)
    Else
        Set(LVar0, 0x80003)
    EndIf
    Call(SpeakToPlayer, 1, 0xAE0004, 0xAE0001, 0, LVar0)
    Label(0)
    Call(ShowCoinCounter, 1)
    Call(ShowChoice, 0x1E0001)
    IfNe(LVar0, 0)
        Call(ShowCoinCounter, 0)
        Call(ContinueSpeech, 1, 0xAE0004, 0xAE0001, 0, 0x80005)
        Return
    EndIf
    Call(tik_15_CheckPlayerHasEnoughCoins, LVar0)
    IfEq(LVar0, 0)
        Call(ShowCoinCounter, 0)
        Call(ContinueSpeech, 1, 0xAE0004, 0xAE0001, 0, 0x80006)
        Return
    EndIf
    Set(LVar0, GameByte(56))
    Call(tik_15_GetNextCheatoItem)
    Switch(LVarA)
    CaseEq(0)
        Call(AddCoin, -64)
        Call(ShowCoinCounter, 0)
        Call(EndSpeech, 1, 0xAE0004, 0xAE0001, 0)
        Set(LVar0, 348)
        Set(LVar1, 3)
        ExecWait(tik_15_GiveItemReward)
        Call(AddStarPieces, 1)
    CaseEq(1)
        Call(AddCoin, -64)
        Call(ShowCoinCounter, 0)
        Call(EndSpeech, 1, 0xAE0004, 0xAE0001, 0)
        Set(LVar0, 253)
        Set(LVar1, 2)
        ExecWait(tik_15_GiveItemReward)
        Call(TTYD64_maps_AddBadge, 253, LVar0)
    CaseEq(2)
        Call(tik_15_CheckPlayerHasEnoughRoom)
        IfLe(LVar0, 0)
            Call(ShowCoinCounter, 0)
            Call(ContinueSpeech, 1, 0xAE0004, 0xAE0001, 0, 0x80007)
            Return
        EndIf
        Call(AddCoin, -64)
        Call(ShowCoinCounter, 0)
        Call(EndSpeech, 1, 0xAE0004, 0xAE0001, 0)
        Set(LVar0, LVarB)
        Set(LVar1, 0)
        ExecWait(tik_15_GiveItemReward)
        Call(AddItem, LVarB, LVar0)
    EndSwitch
    IfLt(GameByte(56), 10)
        Add(GameByte(56), 1)
    EndIf
    Call(SpeakToPlayer, 1, 0xAE0004, 0xAE0001, 0, 0x80004)
    Goto(0)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_tik_15(void) {
    Mod_ReplaceScript("TTYD64", &tik_15_EVS_NpcInteract_RipCheato, &TTYD64_tik_15_Script_Interact_80242824);
}
