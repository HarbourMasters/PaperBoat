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

extern EvtScript omo_11_EVS_MakeEntities;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(MakeEntity);
API_CALLABLE(UseDynamicShadow);

extern EvtScript TTYD64_omo_11_Script_MakeEntities;
extern EvtScript TTYD64_omo_11_Script_Entity_Shine2;
extern EvtScript TTYD64_omo_11_Script_Entity_Shine1;

// clang-format off
EvtScript TTYD64_omo_11_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SuperBlock), -115, 270, -120, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(1194))
    Call(AssignScript, Ref(TTYD64_omo_11_Script_Entity_Shine1))
    Call(MakeEntity, Ref(Entity_MulticoinBlock), 315, 270, -100, 0, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1177))
    Call(UseDynamicShadow, 1)
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), 685, 60, -100, 0, 139, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1181))
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), -600, 60, -50, 0, 129, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1182))
    Call(MakeEntity, Ref(Entity_YellowBlock), -100, 60, -45, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1180))
    Call(MakeEntity, Ref(Entity_SuperBlock), -150, 60, -45, 0, 0x80000000)
    Set(MapVar(1), LVar0)
    Call(AssignBlockFlag, GameFlag(5264))
    Call(AssignScript, Ref(TTYD64_omo_11_Script_Entity_Shine2))
    Call(AssignBlockFlag, GameFlag(1178))
    Call(MakeEntity, Ref(Entity_YellowBlock), -200, 60, -45, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1179))
    Return
    End
};

EvtScript TTYD64_omo_11_Script_Entity_Shine2 = {
    Set(LVar0, MapVar(1))
    SetConst(LVar1, GameFlag(5264))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_omo_11_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(1194))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_omo_11(void) {
    Mod_ReplaceScript("TTYD64", &omo_11_EVS_MakeEntities, &TTYD64_omo_11_Script_MakeEntities);
}
