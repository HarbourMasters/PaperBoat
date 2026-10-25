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

extern EvtScript mac_00_EVS_BindExitTriggers;
extern EvtScript mac_00_EVS_DropDoor_Dojo;
extern EvtScript mac_00_EVS_DropDoor_RussHouse;
extern EvtScript mac_00_EVS_ExitPipe_kmr_20_4;
extern EvtScript mac_00_EVS_ExitPipe_tik_19_9;
extern EvtScript mac_00_EVS_ExitWalk_kmr_10_1;
extern EvtScript mac_00_EVS_ExitWalk_mac_01_0;
extern EvtScript mac_00_EVS_RoomListener_Dojo;
extern EvtScript mac_00_EVS_RoomListener_RussHouse;
extern EvtScript mac_00_EVS_RoomListener_Shop;
extern EvtScript mac_00_EVS_RoomListener_Waterfront;
extern EvtScript mac_00_EVS_SetDoorRot_Dojo;
extern EvtScript mac_00_EVS_SetDoorRot_RussHouse;
extern EvtScript mac_00_EVS_SetDoorRot_Shop;
extern EvtScript mac_00_EVS_SetDoorRot_Waterfront;
extern EvtScript mac_00_EVS_SetWallRot_Dojo;
extern EvtScript mac_00_EVS_SetWallRot_RussHouse;
extern EvtScript mac_00_EVS_SetWallRot_Shop;
extern EvtScript mac_00_EVS_SetWallRot_Waterfront;
extern EvtScript mac_00_EVS_SetupRooms;
extern s32 mac_00_InteriorNPCs_Dojo[];
extern s32 mac_00_InteriorNPCs_RussHouse[];
extern s32 mac_00_InteriorNPCs_Shop[];
extern s32 mac_00_InteriorNPCs_WaterfrontHouse[];

API_CALLABLE(CreateMapRoom);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(PanToTarget);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(RotateModel);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(ShowGotItem);

extern EvtScript TTYD64_mac_00_Script_GetItem;
extern EvtScript TTYD64_mac_00_Script_80244CD4;
extern EvtScript TTYD64_mac_00_Script_ToggleVis_NewDoor;
extern EvtScript TTYD64_mac_00_Script_MoveWalls_NewDoor;
extern EvtScript TTYD64_mac_00_Script_80245BF8;
extern EvtScript TTYD64_mac_00_Script_InitNewStuff;
extern EvtScript TTYD64_mac_00_Script_OpenDoor_NewDoor;

// clang-format off
EvtScript TTYD64_mac_00_Script_GetItem = {
    Call(DisablePlayerInput, 1)
    Call(SetPlayerAnimation, 0x60006)
    Wait(5)
    Call(RemoveItemEntity, MapVar(1))
    Call(TTYD64_maps_AddBadge, 372, 0)
    Call(ShowGotItem, 372, 1, 0)
    Set(GameFlag(4465), 1)
    Unbind
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_mac_00_Script_80244CD4 = {
    BindTrigger(mac_00_EVS_ExitWalk_mac_01_0, 0x80000, 13, 1, 0)
    BindTrigger(mac_00_EVS_ExitPipe_kmr_20_4, 0x80000, 107, 1, 0)
    IfGe(GameByte(0), 96)
        Return
    EndIf
    BindTrigger(mac_00_EVS_ExitWalk_kmr_10_1, 0x80000, 53, 1, 0)
    BindTrigger(mac_00_EVS_ExitPipe_tik_19_9, 128, 27, 1, 0)
    Exec(TTYD64_mac_00_Script_InitNewStuff)
    Return
    End
};

EvtScript TTYD64_mac_00_Script_ToggleVis_NewDoor = {
    Switch(LVar0)
    CaseEq(0)
        Call(PanToTarget, 0, 0, 0)
    CaseEq(1)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_mac_00_Script_MoveWalls_NewDoor = {
    Return
    End
};

EvtScript TTYD64_mac_00_Script_80245BF8 = {
    Call(CreateMapRoom, 0, Ref(mac_00_EVS_SetDoorRot_RussHouse), Ref(mac_00_EVS_SetWallRot_RussHouse), Ref(mac_00_EVS_DropDoor_RussHouse), Ref(mac_00_EVS_RoomListener_RussHouse), 40, 41, 177, (Bytecode) mac_00_InteriorNPCs_RussHouse)
    Call(CreateMapRoom, 4098, Ref(mac_00_EVS_SetDoorRot_Shop), Ref(mac_00_EVS_SetWallRot_Shop), 0, Ref(mac_00_EVS_RoomListener_Shop), 82, 83, 104, (Bytecode) mac_00_InteriorNPCs_Shop)
    Call(CreateMapRoom, 2, Ref(mac_00_EVS_SetDoorRot_Dojo), Ref(mac_00_EVS_SetWallRot_Dojo), Ref(mac_00_EVS_DropDoor_Dojo), Ref(mac_00_EVS_RoomListener_Dojo), 31, 32, 138, (Bytecode) mac_00_InteriorNPCs_Dojo)
    Call(CreateMapRoom, 2, Ref(mac_00_EVS_SetDoorRot_Waterfront), Ref(mac_00_EVS_SetWallRot_Waterfront), 0, Ref(mac_00_EVS_RoomListener_Waterfront), 7, 8, 211, (Bytecode) mac_00_InteriorNPCs_WaterfrontHouse)
    Call(CreateMapRoom, 7, Ref(TTYD64_mac_00_Script_OpenDoor_NewDoor), Ref(TTYD64_mac_00_Script_MoveWalls_NewDoor), 0, Ref(TTYD64_mac_00_Script_ToggleVis_NewDoor), 111, 110, 211, (Bytecode) mac_00_InteriorNPCs_WaterfrontHouse)
    Set(LVar0, 3)
    Exec(mac_00_EVS_RoomListener_RussHouse)
    Exec(mac_00_EVS_RoomListener_Waterfront)
    Exec(mac_00_EVS_RoomListener_Shop)
    Exec(mac_00_EVS_RoomListener_Dojo)
    Return
    End
};

EvtScript TTYD64_mac_00_Script_InitNewStuff = {
    Call(MakeItemEntity, 372, -460, 20, -137, 17, GameFlag(4465))
    Set(MapVar(1), LVar0)
    Call(MakeItemEntity, 348, 1, 20, 271, 17, GameFlag(4466))
    IfEq(GameFlag(4465), 0)
        BindTrigger(TTYD64_mac_00_Script_GetItem, 256, 116, 1, 0)
    EndIf
    Return
    End
};

EvtScript TTYD64_mac_00_Script_OpenDoor_NewDoor = {
    Call(RotateModel, 222, LVar0, 0, 1, 0)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_mac_00(void) {
    Mod_ReplaceScript("TTYD64", &mac_00_EVS_BindExitTriggers, &TTYD64_mac_00_Script_80244CD4);
    Mod_ReplaceScript("TTYD64", &mac_00_EVS_SetupRooms, &TTYD64_mac_00_Script_80245BF8);
}
