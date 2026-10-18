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

extern EvtScript kpa_41_EVS_BindExitTriggers;
extern EvtScript kpa_41_EVS_EnterMap;
extern EvtScript kpa_41_EVS_ExitWalk_LowerLeft;
extern EvtScript kpa_41_EVS_ExitWalk_UpperLeft;

API_CALLABLE(GetEntryID);
API_CALLABLE(GotoMap);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_kpa_41_Script_EnterWalk_8024041C;
extern EvtScript TTYD64_kpa_41_Script_8024039C;
extern EvtScript TTYD64_kpa_41_Script_ExitWalk_Up;
extern EvtScript TTYD64_kpa_41_Script_ExitWalk_Down;

// clang-format off
EvtScript TTYD64_kpa_41_Script_EnterWalk_8024041C = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(1)
        Set(AreaByte(15), 5)
    CaseEq(2)
        Set(AreaByte(11), 5)
    CaseDefault
    EndSwitch
    Set(LVar0, Ref(kpa_41_EVS_BindExitTriggers))
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};

EvtScript TTYD64_kpa_41_Script_8024039C = {
    BindTrigger(kpa_41_EVS_ExitWalk_LowerLeft, 0x80000, 12, 1, 0)
    BindTrigger(TTYD64_kpa_41_Script_ExitWalk_Down, 0x80000, 17, 1, 0)
    BindTrigger(kpa_41_EVS_ExitWalk_UpperLeft, 0x80000, 22, 1, 0)
    BindTrigger(TTYD64_kpa_41_Script_ExitWalk_Up, 0x80000, 27, 1, 0)
    Return
    End
};

EvtScript TTYD64_kpa_41_Script_ExitWalk_Up = {
    SetGroup(27)
    Call(UseExitHeading, 60, 2)
    Exec(ExitWalk)
    IfEq(AreaByte(15), 0)
        Switch(AreaByte(11))
        CaseEq(5)
            Set(AreaByte(11), 0)
            Set(AreaByte(15), 0)
            Call(GotoMap, (Bytecode) "kpa_102", 0)
        CaseEq(3)
            Add(AreaByte(11), 1)
            Call(GotoMap, (Bytecode) "kpa_41", 3)
        CaseOrEq(0)
        CaseOrEq(1)
        CaseOrEq(2)
        CaseOrEq(4)
            Call(GotoMap, (Bytecode) "kpa_40", 3)
            EndCaseGroup
        EndSwitch
    Else
        Switch(AreaByte(15))
        CaseOrEq(1)
        CaseOrEq(2)
        CaseOrEq(4)
            Add(AreaByte(15), 1)
            Call(GotoMap, (Bytecode) "kpa_41", 3)
            EndCaseGroup
        CaseOrEq(0)
        CaseOrEq(3)
        CaseOrEq(5)
            Call(GotoMap, (Bytecode) "kpa_40", 3)
            EndCaseGroup
        EndSwitch
    EndIf
    Wait(100)
    Return
    End
};

EvtScript TTYD64_kpa_41_Script_ExitWalk_Down = {
    SetGroup(27)
    Call(UseExitHeading, 60, 1)
    Exec(ExitWalk)
    IfEq(AreaByte(15), 0)
        Switch(AreaByte(11))
        CaseOrEq(1)
        CaseOrEq(2)
        CaseOrEq(4)
            Add(AreaByte(11), 1)
            Call(GotoMap, (Bytecode) "kpa_41", 0)
            EndCaseGroup
        CaseOrEq(0)
        CaseOrEq(3)
        CaseOrEq(5)
            Call(GotoMap, (Bytecode) "kpa_40", 3)
            EndCaseGroup
        EndSwitch
    Else
        Switch(AreaByte(15))
        CaseEq(5)
            Set(AreaByte(11), 0)
            Set(AreaByte(15), 0)
            Call(GotoMap, (Bytecode) "kpa_140", 0)
        CaseEq(3)
            Add(AreaByte(15), 1)
            Call(GotoMap, (Bytecode) "kpa_41", 0)
        CaseOrEq(0)
        CaseOrEq(1)
        CaseOrEq(2)
        CaseOrEq(4)
            Call(GotoMap, (Bytecode) "kpa_40", 3)
            EndCaseGroup
        EndSwitch
    EndIf
    Wait(100)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_kpa_41(void) {
    Mod_ReplaceScript("TTYD64", &kpa_41_EVS_EnterMap, &TTYD64_kpa_41_Script_EnterWalk_8024041C);
    Mod_ReplaceScript("TTYD64", &kpa_41_EVS_BindExitTriggers, &TTYD64_kpa_41_Script_8024039C);
}
