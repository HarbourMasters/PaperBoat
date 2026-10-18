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

extern FoliageDropList nok_02_Bush1_Drops;
extern FoliageDropList nok_02_Bush6_Drops;
extern NpcGroupList nok_02_CrisisNPCs;
extern EvtScript nok_02_EVS_EnterMap;
extern EvtScript nok_02_EVS_Main;
extern EvtScript nok_02_EVS_MakeEntities;
extern EvtScript nok_02_EVS_RoomListener_KoloradoHouse;
extern EvtScript nok_02_EVS_Scene_Epilogue;
extern EvtScript nok_02_EVS_SetupDemo;
extern EvtScript nok_02_EVS_SetupFoliage;
extern EvtScript nok_02_EVS_SetupMusic;
extern EvtScript nok_02_EVS_SetupRooms;
extern EvtScript nok_02_EVS_Setup_Bookshelf;
extern EvtScript nok_02_EVS_TexPan_Flowers;
extern NpcGroupList nok_02_EpilogueNPCs;
extern NpcGroupList nok_02_NormalNPCs;

API_CALLABLE(ClearDefeatedEnemies);
API_CALLABLE(FadeInMusic);
API_CALLABLE(GetDemoState);
API_CALLABLE(GetEntryID);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetGroupVisibility);
API_CALLABLE(SetItemFlags);
API_CALLABLE(SetSpriteShading);

extern EvtScript TTYD64_nok_02_Script_ToggleVis_80246A2C;
extern EvtScript TTYD64_nok_02_Script_KoloradoHouseItem;
extern EvtScript TTYD64_nok_02_Script_Main;
extern EvtScript TTYD64_nok_02_Script_ItemShelf;

// clang-format off
EvtScript TTYD64_nok_02_Script_ToggleVis_80246A2C = {
    Switch(LVar0)
    CaseEq(0)
        Call(SetGroupVisibility, 39, 1)
        IfEq(GameFlag(4718), 0)
            Call(SetItemFlags, MapVar(11), 1, 1)
        EndIf
    CaseEq(1)
    CaseEq(2)
    CaseEq(3)
        Call(SetGroupVisibility, 39, 0)
        IfEq(GameFlag(4718), 0)
            Call(SetItemFlags, MapVar(11), 1, 0)
        EndIf
    EndSwitch
    Return
    End
};

EvtScript TTYD64_nok_02_Script_KoloradoHouseItem = {
    BindTrigger(TTYD64_nok_02_Script_ItemShelf, 0x80000, 86, 1, 0)
    Call(MakeItemEntity, 348, -378, 86, -305, 17, GameFlag(4718))
    Set(MapVar(11), LVar0)
    Return
    End
};

EvtScript TTYD64_nok_02_Script_Main = {
    Set(GameByte(425), 33)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_nok_02_Script_KoloradoHouseItem)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 3)
        Call(MakeNpcs, 0, Ref(nok_02_EpilogueNPCs))
        ExecWait(nok_02_EVS_MakeEntities)
        Exec(nok_02_EVS_TexPan_Flowers)
        Exec(nok_02_EVS_Scene_Epilogue)
        Call(FadeInMusic, 0, 19, 0, 3000, 0, 127)
        Wait(1)
        Return
    EndIf
    Set(AreaFlag(15), 0)
    Set(AreaFlag(16), 0)
    Set(AreaFlag(18), 0)
    Set(GameFlag(592), 0)
    Set(GameFlag(4767), 0)
    Set(AreaFlag(19), 0)
    IfGe(GameByte(0), -92)
        Set(GameFlag(570), 1)
        Set(GameFlag(572), 1)
    EndIf
    IfLt(GameByte(0), -92)
        Call(MakeNpcs, 0, Ref(nok_02_CrisisNPCs))
    Else
        Call(MakeNpcs, 0, Ref(nok_02_NormalNPCs))
    EndIf
    Call(ClearDefeatedEnemies)
    ExecWait(nok_02_EVS_MakeEntities)
    ExecWait(nok_02_EVS_SetupFoliage)
    Exec(nok_02_EVS_TexPan_Flowers)
    BindTrigger(nok_02_EVS_Setup_Bookshelf, 256, 26, 1, 0)
    ExecWait(nok_02_EVS_SetupRooms)
    Call(GetDemoState, LVar0)
    IfNe(LVar0, 0)
        ExecWait(nok_02_EVS_SetupDemo)
        Return
    EndIf
    Exec(nok_02_EVS_SetupMusic)
    Call(ModifyColliderFlags, 0, 5, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
    Exec(nok_02_EVS_EnterMap)
    Wait(1)
    Return
    End
};

EvtScript TTYD64_nok_02_Script_ItemShelf = {
    Call(SetCamSpeed, 0, Float(4.0))
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_nok_02(void) {
    nok_02_Bush1_Drops.count = 1;
    nok_02_Bush1_Drops.drops[0].itemID = 404;
    nok_02_Bush1_Drops.drops[0].pos.x = -407;
    nok_02_Bush1_Drops.drops[0].pos.y = 16;
    nok_02_Bush1_Drops.drops[0].pos.z = 90;
    nok_02_Bush1_Drops.drops[0].spawnMode = 7;
    nok_02_Bush1_Drops.drops[0].pickupFlag = GameFlag(592);
    nok_02_Bush1_Drops.drops[0].spawnFlag = MapFlag(10);
    nok_02_Bush6_Drops.count = 1;
    nok_02_Bush6_Drops.drops[0].itemID = 399;
    nok_02_Bush6_Drops.drops[0].pos.x = 387;
    nok_02_Bush6_Drops.drops[0].pos.y = 16;
    nok_02_Bush6_Drops.drops[0].pos.z = 202;
    nok_02_Bush6_Drops.drops[0].spawnMode = 7;
    nok_02_Bush6_Drops.drops[0].pickupFlag = GameFlag(4767);
    nok_02_Bush6_Drops.drops[0].spawnFlag = MapFlag(10);
    Mod_ReplaceScript("TTYD64", &nok_02_EVS_RoomListener_KoloradoHouse, &TTYD64_nok_02_Script_ToggleVis_80246A2C);
    Mod_ReplaceScript("TTYD64", &nok_02_EVS_Main, &TTYD64_nok_02_Script_Main);
}
