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

extern NpcGroupList flo_15_DefaultNPCs;
extern EvtScript flo_15_EVS_BindExitTriggers;
extern EvtScript flo_15_EVS_Main;
extern EvtScript flo_15_EVS_MakeEntities;
extern EvtScript flo_15_EVS_MonitorFallingStairs;
extern EvtScript flo_15_EVS_Scene_SunReturns;

API_CALLABLE(EnableGroup);
API_CALLABLE(GetEntryID);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetSpriteShading);

extern EvtScript TTYD64_flo_15_Script_InitNewStuff;
extern EvtScript TTYD64_flo_15_Script_HideCrack;
extern EvtScript TTYD64_flo_15_Script_Main_EnterWalk;
extern EvtScript TTYD64_flo_15_Script_SetMusicTrack;
extern EvtScript TTYD64_flo_15_Script_BlastDoor;
extern BombTrigger TTYD64_flo_15_TriggerCoord_Door;

// clang-format off
EvtScript TTYD64_flo_15_Script_InitNewStuff = {
    IfEq(GameFlag(5511), 0)
        BindTrigger(TTYD64_flo_15_Script_BlastDoor, 0x100000, Ref(TTYD64_flo_15_TriggerCoord_Door), 1, 0)
    Else
        Exec(TTYD64_flo_15_Script_HideCrack)
    EndIf
    Call(MakeItemEntity, 384, -64, 39, 97, 17, GameFlag(5512))
    Return
    End
};

EvtScript TTYD64_flo_15_Script_HideCrack = {
    Call(EnableGroup, 57, 0)
    Call(ModifyColliderFlags, 0, 29, 0x7FFFFE00)
    Return
    End
};

EvtScript TTYD64_flo_15_Script_Main_EnterWalk = {
    Set(GameByte(425), 38)
    Call(SetSpriteShading, -1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 0, Ref(flo_15_DefaultNPCs))
    ExecWait(flo_15_EVS_MakeEntities)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 1)
        Exec(flo_15_EVS_Scene_SunReturns)
    Else
        Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
        Set(LVar0, Ref(flo_15_EVS_BindExitTriggers))
        Exec(EnterWalk)
    EndIf
    Call(ModifyColliderFlags, 0, 14, 0x7FFFFE00)
    Exec(flo_15_EVS_MonitorFallingStairs)
    ExecWait(TTYD64_flo_15_Script_SetMusicTrack)
    Return
    End
};

EvtScript TTYD64_flo_15_Script_SetMusicTrack = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 1)
        Call(SetMusic, 0, 127, 0, 8)
    Else
        Switch(GameByte(0))
        CaseLt(53)
            Call(SetMusic, 0, 52, 0, 8)
        CaseDefault
            Call(SetMusic, 0, 53, 0, 8)
        EndSwitch
    EndIf
    Exec(TTYD64_flo_15_Script_InitNewStuff)
    Return
    End
};

EvtScript TTYD64_flo_15_Script_BlastDoor = {
    Call(PlayEffect_impl, 66, 0, 56, 56, 1, 10, 30, 0, 0, 0, 0, 0, 0)
    Exec(TTYD64_flo_15_Script_HideCrack)
    Set(GameFlag(5511), 1)
    Unbind
    Return
    End
};

BombTrigger TTYD64_flo_15_TriggerCoord_Door = {
    .pos = { -123.0f, 80.0f, -3.0f },
    .diameter = 0.0f
};
// clang-format on

void TTYD64_InstallMap_flo_15(void) {
    Mod_ReplaceScript("TTYD64", &flo_15_EVS_Main, &TTYD64_flo_15_Script_Main_EnterWalk);
}
