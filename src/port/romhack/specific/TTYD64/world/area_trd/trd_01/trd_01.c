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

extern EvtScript trd_01_EVS_BindLockTrigger;
extern EvtScript trd_01_EVS_MakeEntities;

API_CALLABLE(AssignScript);
API_CALLABLE(AssignSwitchFlag);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);

extern EvtScript TTYD64_trd_01_Script_MakeEntities;

// clang-format off
EvtScript TTYD64_trd_01_Script_MakeEntities = {
    IfEq(GameFlag(650), 0)
        Call(MakeEntity, Ref(Entity_Padlock), 315, 8, 0, -80, 0x80000000)
        Call(AssignScript, Ref(trd_01_EVS_BindLockTrigger))
        Set(MapVar(0), LVar0)
    EndIf
    IfLt(GameByte(0), -80)
        Call(MakeEntity, Ref(Entity_BlueSwitch), 0, 220, 255, 0, 0x80000000)
        Call(AssignSwitchFlag, 1)
    EndIf
    Call(MakeItemEntity, 348, -268, 656, -40, 17, GameFlag(638))
    IfEq(GameFlag(665), 1)
        IfEq(GameFlag(645), 0)
            Call(MakeItemEntity, 16, 254, 0, 30, 0, GameFlag(645))
        EndIf
    EndIf
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_trd_01(void) {
    Mod_ReplaceScript("TTYD64", &trd_01_EVS_MakeEntities, &TTYD64_trd_01_Script_MakeEntities);
}
