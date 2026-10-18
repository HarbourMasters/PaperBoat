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

extern EvtScript sam_08_EVS_MakeEntities;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(AssignSwitchFlag);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);

extern EvtScript TTYD64_sam_08_Script_Entity_Shine1;
extern EvtScript TTYD64_sam_08_Script_MakeEntities;

// clang-format off
EvtScript TTYD64_sam_08_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(1))
    SetConst(LVar1, GameFlag(1457))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_sam_08_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SuperBlock), -800, 210, -130, 0, 0x80000000)
    Set(MapVar(1), LVar0)
    Call(AssignBlockFlag, GameFlag(1457))
    Call(AssignScript, Ref(TTYD64_sam_08_Script_Entity_Shine1))
    Call(MakeItemEntity, 133, -770, -240, 30, 19, 0)
    IfLt(GameByte(0), 75)
        Call(MakeEntity, Ref(Entity_BlueSwitch), -960, -120, -37, 0, 0x80000000)
        Call(AssignSwitchFlag, 6)
    EndIf
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_sam_08(void) {
    Mod_ReplaceScript("TTYD64", &sam_08_EVS_MakeEntities, &TTYD64_sam_08_Script_MakeEntities);
}
