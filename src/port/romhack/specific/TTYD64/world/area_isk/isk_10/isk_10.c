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

extern EvtScript isk_10_EVS_ExitWalk_isk_08_1;
extern EvtScript isk_10_EVS_ExitWalk_isk_14_0;
extern EvtScript isk_10_EVS_ExitWalk_isk_18_0;
extern EvtScript isk_10_EVS_Main;
extern EvtScript isk_10_EVS_MakeEntities;
extern EvtScript isk_10_EVS_SetupBombableWall;
extern EvtScript isk_10_EVS_UseSpring;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetMusic);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(isk_10_MonitorPlayerLastFloor);

extern EvtScript TTYD64_isk_10_Script_Main_EnterWalk;
extern EvtScript TTYD64_isk_10_Script_MakeExits;
extern EvtScript TTYD64_isk_10_Script_MakeEntities;
extern EvtScript TTYD64_isk_10_Script_Entity_Shine1;

// clang-format off
EvtScript TTYD64_isk_10_Script_Main_EnterWalk = {
    Set(GameByte(425), 11)
    Call(SetSpriteShading, 0x20007)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(SetCamSpeed, 0, Float(2.80078125))
    ExecWait(isk_10_EVS_MakeEntities)
    ExecWait(isk_10_EVS_SetupBombableWall)
    Switch(GameByte(0))
    CaseLt(-57)
        Call(SetMusic, 0, 24, 0, 8)
    CaseLt(-56)
        Call(SetMusic, 0, 25, 0, 8)
    CaseGe(-56)
        Call(SetMusic, 0, 24, 0, 8)
    EndSwitch
    Set(LVar0, Ref(TTYD64_isk_10_Script_MakeExits))
    Exec(EnterWalk)
    Return
    End
};

EvtScript TTYD64_isk_10_Script_MakeExits = {
    BindTrigger(isk_10_EVS_ExitWalk_isk_08_1, 0x80000, 10, 1, 0)
    BindTrigger(isk_10_EVS_ExitWalk_isk_14_0, 0x80000, 1, 1, 0)
    BindTrigger(isk_10_EVS_ExitWalk_isk_18_0, 0x80000, 6, 1, 0)
    Call(MakeItemEntity, 390, -550, -695, 137, 17, GameFlag(5003))
    Return
    End
};

EvtScript TTYD64_isk_10_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SuperBlock), -550, -720, 0, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(903))
    Call(AssignScript, Ref(TTYD64_isk_10_Script_Entity_Shine1))
    Thread
        Call(isk_10_MonitorPlayerLastFloor)
    EndThread
    Call(MakeEntity, Ref(Entity_ScriptSpring), -516, -780, -71, 0, 0x80000000)
    Call(AssignScript, Ref(isk_10_EVS_UseSpring))
    Call(PlayEffect_impl, 32, 1, -510, -453, 43, Float(0.30078125), LVar0, 0, 0, 0, 0, 0, 0, 0)
    Call(PlayEffect_impl, 32, 1, -510, -713, 43, Float(0.30078125), LVar0, 0, 0, 0, 0, 0, 0, 0)
    Return
    End
};

EvtScript TTYD64_isk_10_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(903))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_isk_10(void) {
    Mod_ReplaceScript("TTYD64", &isk_10_EVS_Main, &TTYD64_isk_10_Script_Main_EnterWalk);
    Mod_ReplaceScript("TTYD64", &isk_10_EVS_MakeEntities, &TTYD64_isk_10_Script_MakeEntities);
}
