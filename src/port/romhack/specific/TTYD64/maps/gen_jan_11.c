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

extern EvtScript jan_11_D_80241F38_B72798;
extern NpcGroupList jan_11_DefaultNPCs;
extern EvtScript jan_11_EVS_CreateDarkness;
extern EvtScript jan_11_EVS_Main;
extern EvtScript jan_11_EVS_SetupDrips;
extern EvtScript jan_11_EVS_SetupMusic;

API_CALLABLE(EnableModel);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);

extern EvtScript TTYD64_jan_11_Script_Main_EnterWalk;
extern EvtScript TTYD64_jan_11_Script_InitNewItems;
extern EvtScript TTYD64_jan_11_Script_BlastRock;
extern BombTrigger TTYD64_jan_11_TriggerCoord_Rock;

// clang-format off
EvtScript TTYD64_jan_11_Script_Main_EnterWalk = {
    Set(GameByte(425), 36)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamLeadPlayer, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 0, Ref(jan_11_DefaultNPCs))
    Exec(jan_11_EVS_CreateDarkness)
    Set(LVar0, Ref(jan_11_D_80241F38_B72798))
    Exec(EnterWalk)
    Exec(TTYD64_jan_11_Script_InitNewItems)
    ExecWait(jan_11_EVS_SetupDrips)
    Return
    End
};

EvtScript TTYD64_jan_11_Script_InitNewItems = {
    IfEq(GameFlag(5380), 1)
        Call(EnableModel, 3, 0)
        Call(EnableModel, 39, 0)
        Call(ModifyColliderFlags, 0, 11, 0x7FFFFE00)
    Else
        BindTrigger(TTYD64_jan_11_Script_BlastRock, 0x100000, Ref(TTYD64_jan_11_TriggerCoord_Rock), 1, 0)
    EndIf
    Call(MakeItemEntity, 225, -31, 0, 63, 17, GameFlag(5381))
    Call(MakeItemEntity, 348, 29, 0, -63, 17, GameFlag(5382))
    Exec(jan_11_EVS_SetupMusic)
    Return
    End
};

EvtScript TTYD64_jan_11_Script_BlastRock = {
    Call(PlayEffect_impl, 66, 0, 3, 3, 1, 10, 30, 0, 0, 0, 0, 0, 0)
    Call(EnableModel, 3, 0)
    Call(EnableModel, 39, 0)
    Call(ModifyColliderFlags, 0, 11, 0x7FFFFE00)
    Set(GameFlag(5380), 1)
    Unbind
    Return
    End
};

BombTrigger TTYD64_jan_11_TriggerCoord_Rock = {
    .pos = { -31.0f, 0.0f, 63.0f },
    .diameter = 2.0f
};
// clang-format on

void TTYD64_InstallMap_jan_11(void) {
    Mod_ReplaceScript("TTYD64", &jan_11_EVS_Main, &TTYD64_jan_11_Script_Main_EnterWalk);
}
