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

extern NpcGroupList iwa_00_DefaultNPCs;
extern EvtScript iwa_00_EVS_BindSlideTriggers;
extern EvtScript iwa_00_EVS_ExitWalk_iwa_01_0;
extern EvtScript iwa_00_EVS_ExitWalk_iwa_10_1;
extern EvtScript iwa_00_EVS_Main;
extern EvtScript iwa_00_EVS_MakeEntities;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(EnableTexPanning);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(PlaySoundAtF);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(iwa_00_SetupSlidingCheck);
API_CALLABLE(SetTexPanOffset);

extern EvtScript TTYD64_iwa_00_Script_80240408;
extern EvtScript TTYD64_iwa_00_Script_Entity_Shine1;
extern EvtScript TTYD64_iwa_00_Script_Main_EnterWalk;
extern EvtScript TTYD64_iwa_00_Script_BindExits;

// clang-format off
EvtScript TTYD64_iwa_00_Script_80240408 = {
    Call(EnableTexPanning, 23, 1)
    Call(EnableTexPanning, 22, 1)
    Set(LVar0, 0)
    Loop(0)
        Add(LVar0, 3000)
        Call(SetTexPanOffset, 1, 0, 0, LVar0)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_iwa_00_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(4825))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_iwa_00_Script_Main_EnterWalk = {
    Set(GameByte(425), 8)
    Call(SetSpriteShading, -1)
    Call(iwa_00_SetupSlidingCheck)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 1, Ref(iwa_00_DefaultNPCs))
    ExecWait(iwa_00_EVS_MakeEntities)
    Exec(TTYD64_iwa_00_Script_80240408)
    Exec(iwa_00_EVS_BindSlideTriggers)
    Call(SetMusic, 0, 22, 0, 8)
    Call(PlaySoundAtF, 0x8000000B, 1, 35, -80, -120)
    Call(PlaySoundAtF, 0x8000000C, 1, 500, 85, -120)
    Set(LVar0, Ref(TTYD64_iwa_00_Script_BindExits))
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};

EvtScript TTYD64_iwa_00_Script_BindExits = {
    BindTrigger(iwa_00_EVS_ExitWalk_iwa_10_1, 0x80000, 1, 1, 0)
    BindTrigger(iwa_00_EVS_ExitWalk_iwa_01_0, 0x80000, 4, 1, 0)
    Call(MakeItemEntity, 343, 396, -1, -24, 17, AreaFlag(3))
    Call(MakeEntity, Ref(Entity_SuperBlock), 518, 55, -24, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(4825))
    Call(AssignScript, Ref(TTYD64_iwa_00_Script_Entity_Shine1))
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_iwa_00(void) {
    Mod_ReplaceScript("TTYD64", &iwa_00_EVS_Main, &TTYD64_iwa_00_Script_Main_EnterWalk);
}
