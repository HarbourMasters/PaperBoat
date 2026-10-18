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

extern NpcGroupList iwa_03_DefaultNPCs;
extern EvtScript iwa_03_EVS_BindSlideTriggers;
extern EvtScript iwa_03_EVS_ExitWalk_iwa_01_1;
extern EvtScript iwa_03_EVS_Main;
extern EvtScript iwa_03_EVS_MakeEntities;

API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetSpriteShading);

extern EvtScript TTYD64_iwa_03_Script_Main_EnterWalk;
extern EvtScript TTYD64_iwa_03_Script_InitSecret;
extern EvtScript TTYD64_iwa_03_Script_BindExits;

// clang-format off
EvtScript TTYD64_iwa_03_Script_Main_EnterWalk = {
    Set(GameByte(425), 8)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 1, Ref(iwa_03_DefaultNPCs))
    ExecWait(iwa_03_EVS_MakeEntities)
    Exec(iwa_03_EVS_BindSlideTriggers)
    Call(SetMusic, 0, 22, 0, 8)
    Set(LVar0, Ref(TTYD64_iwa_03_Script_BindExits))
    Exec(EnterWalk)
    Wait(1)
    Call(ModifyColliderFlags, 0, 18, 0x7FFFFE00)
    Return
    End
};

EvtScript TTYD64_iwa_03_Script_InitSecret = {
    Call(MakeItemEntity, 343, -1309, 23, -81, 17, AreaFlag(4))
    Call(MakeItemEntity, 343, -1226, 23, -81, 17, AreaFlag(5))
    Call(MakeItemEntity, 343, -1153, 23, -81, 17, AreaFlag(6))
    Call(MakeItemEntity, 343, -1093, 23, -78, 17, AreaFlag(7))
    Call(MakeItemEntity, 343, -1039, 22, -75, 17, AreaFlag(8))
    Call(MakeItemEntity, 348, -991, 7, -81, 17, GameFlag(4826))
    Return
    End
};

EvtScript TTYD64_iwa_03_Script_BindExits = {
    BindTrigger(iwa_03_EVS_ExitWalk_iwa_01_1, 0x80000, 24, 1, 0)
    Exec(TTYD64_iwa_03_Script_InitSecret)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_iwa_03(void) {
    Mod_ReplaceScript("TTYD64", &iwa_03_EVS_Main, &TTYD64_iwa_03_Script_Main_EnterWalk);
}
