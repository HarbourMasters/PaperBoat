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

extern NpcGroupList flo_23_DefaultNPCs;
extern EvtScript flo_23_EVS_BindExitTriggers;
extern EvtScript flo_23_EVS_FlowerSpawnRegion;
extern EvtScript flo_23_EVS_Main;
extern EvtScript flo_23_EVS_MakeEntities;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(flo_23_SpawnSunEffect);

extern EvtScript TTYD64_flo_23_Script_Main_EnterWalk;
extern EvtScript TTYD64_flo_23_Script_InitNewStuff;
extern EvtScript TTYD64_flo_23_Script_SetMusicTrack;

// clang-format off
EvtScript TTYD64_flo_23_Script_Main_EnterWalk = {
    Set(GameByte(425), 38)
    Call(SetSpriteShading, -1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 0, Ref(flo_23_DefaultNPCs))
    ExecWait(flo_23_EVS_MakeEntities)
    Set(LVar0, -290)
    Set(LVar1, -190)
    Set(LVar2, 480)
    Set(LVar3, -90)
    Set(LVar4, 0)
    Exec(flo_23_EVS_FlowerSpawnRegion)
    Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 5, 0x7FFFFE00)
    Set(LVar0, Ref(flo_23_EVS_BindExitTriggers))
    Exec(EnterWalk)
    ExecWait(TTYD64_flo_23_Script_SetMusicTrack)
    IfGe(GameByte(0), 53)
        Call(flo_23_SpawnSunEffect)
    EndIf
    Return
    End
};

EvtScript TTYD64_flo_23_Script_InitNewStuff = {
    Call(MakeEntity, Ref(Entity_RedBlock), -190, 135, 0, 0, 382, 0x80000000)
    Call(AssignBlockFlag, GameFlag(5509))
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), -88, 110, 0, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(5510))
    Return
    End
};

EvtScript TTYD64_flo_23_Script_SetMusicTrack = {
    Switch(GameByte(0))
    CaseLt(53)
        Call(SetMusic, 0, 48, 0, 8)
    CaseDefault
        Call(SetMusic, 0, 49, 0, 8)
    EndSwitch
    Exec(TTYD64_flo_23_Script_InitNewStuff)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_flo_23(void) {
    Mod_ReplaceScript("TTYD64", &flo_23_EVS_Main, &TTYD64_flo_23_Script_Main_EnterWalk);
}
