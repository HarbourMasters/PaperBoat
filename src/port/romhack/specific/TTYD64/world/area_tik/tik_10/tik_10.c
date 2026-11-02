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

extern EvtScript tik_10_EVS_BindExitTriggers;
extern EvtScript tik_10_EVS_ExitWalk_tik_09_0;
extern EvtScript tik_10_EVS_MakeEntities;
extern MapSettings tik_10_settings;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(CreatePushBlockGrid);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(SetPushBlock);
API_CALLABLE(UseDynamicShadow);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_tik_10_Script_80241538;
extern EvtScript TTYD64_tik_10_Script_Exit2;
extern EntryList TTYD64_tik_10_EntryList;
extern EvtScript TTYD64_tik_10_Script_MakeEntities;
extern EvtScript TTYD64_tik_10_Script_Exit1;
extern EvtScript TTYD64_tik_10_Script_Entity_Shine1;

// clang-format off
EvtScript TTYD64_tik_10_Script_80241538 = {
    BindTrigger(tik_10_EVS_ExitWalk_tik_09_0, 0x80000, 9, 1, 0)
    BindTrigger(TTYD64_tik_10_Script_Exit1, 0x80000, 17, 1, 0)
    BindTrigger(TTYD64_tik_10_Script_Exit2, 0x80000, 18, 1, 0)
    Return
    End
};

EvtScript TTYD64_tik_10_Script_Exit2 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 2)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "tik_27", 0)
    Wait(100)
    Return
    End
};

EntryList TTYD64_tik_10_EntryList = {
    { 330.0f, 20.0f, 0.0f, 270.0f },
    { 326.0f, -18.0f, 158.0f, -90.0f },
    { -228.0f, -18.0f, 158.0f, 90.0f },
};

EvtScript TTYD64_tik_10_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SuperBlock), -140, 160, -40, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(434))
    Call(AssignScript, Ref(TTYD64_tik_10_Script_Entity_Shine1))
    Call(CreatePushBlockGrid, 0, 7, 6, -64, -15, -94, 0)
    Call(SetPushBlock, 0, 1, 4, 1)
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), -52, 70, -32, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(405))
    Call(UseDynamicShadow, 1)
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), 23, 70, -32, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(406))
    Call(UseDynamicShadow, 1)
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), 98, 70, -32, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(407))
    Call(UseDynamicShadow, 1)
    Return
    End
};

EvtScript TTYD64_tik_10_Script_Exit1 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 1)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "tik_09", 4)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_tik_10_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(434))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_tik_10(void) {
    tik_10_settings.entryList = &TTYD64_tik_10_EntryList;
    tik_10_settings.entryCount = 3;
    Mod_ReplaceScript("TTYD64", &tik_10_EVS_BindExitTriggers, &TTYD64_tik_10_Script_80241538);
    Mod_ReplaceScript("TTYD64", &tik_10_EVS_MakeEntities, &TTYD64_tik_10_Script_MakeEntities);
}
