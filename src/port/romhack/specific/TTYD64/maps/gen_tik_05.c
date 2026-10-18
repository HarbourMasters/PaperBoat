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

extern EvtScript tik_05_EVS_BreakBlock_DropSpring;
extern EvtScript tik_05_EVS_MakeEntities;
extern EvtScript tik_05_EVS_OpenChest;

API_CALLABLE(AddItem);
API_CALLABLE(AssignChestFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(MakeEntity);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(ResetCam);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetTimeFreezeMode);
API_CALLABLE(ShowGotItem);
API_CALLABLE(UseSettingsFrom);

extern EvtScript TTYD64_tik_05_Script_GiveItem;
extern EvtScript TTYD64_tik_05_Script_ActivateNewSpring;
extern EvtScript TTYD64_tik_05_Script_MakeEntities;
extern EvtScript TTYD64_tik_05_Script_ShowGotItem;
extern EvtScript TTYD64_tik_05_Script_OpenChest;

// clang-format off
EvtScript TTYD64_tik_05_Script_GiveItem = {
    Call(DisablePlayerInput, 1)
    Set(LVar0, LVarA)
    IfNe(LVarA, 0)
        ExecWait(TTYD64_tik_05_Script_ShowGotItem)
    EndIf
    Switch(LVarB)
    CaseEq(0)
        Call(AddItem, LVarA, LVar0)
    CaseEq(1)
        Call(TTYD64_maps_AddKeyItem, LVarA)
    CaseEq(2)
        Call(TTYD64_maps_AddBadge, LVarA, LVar0)
    EndSwitch
    Wait(15)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_tik_05_Script_ActivateNewSpring = {
    SetGroup(2)
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(DisablePartnerAI, 1)
    Set(GameFlag(4541), 1)
    Call(TTYD64_GetEntityPointer, MapVar(0), LVar0)
    Call(TTYD64_ReadPtrField, LVar0, TTYD64_F_ENTITY_40_4U, LVar0)
    Call(TTYD64_WritePtrField, LVar0, TTYD64_F_SIMPLESPRINGDATA_0_4U, 210)
    Call(UseSettingsFrom, 0, -35, -10, 0)
    Call(SetCamSpeed, 0, Float(7.0))
    Call(SetPanTarget, 0, -35, -10, 0)
    Call(PanToTarget, 0, 0, 1)
    Wait(10)
    Call(PlaySound, 11)
    Set(LVar1, -35)
    Set(LVar2, -10)
    Set(LVar3, 0)
    Add(LVar2, 15)
    Call(PlayEffect_impl, 34, 0, LVar1, LVar2, LVar3, 80, 55, 8, 50, 0, 0, 0, 0, 0)
    Wait(30)
    Call(SetCamSpeed, 0, Float(1.0))
    Call(ResetCam, 0, Float(5.0))
    Call(DisablePlayerInput, 0)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePartnerAI, 0)
    Return
    End
};

EvtScript TTYD64_tik_05_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_Chest), -185, 60, -25, 0, 0, 0x80000000)
    Call(AssignChestFlag, GameFlag(403))
    Call(AssignScript, Ref(tik_05_EVS_OpenChest))
    Call(MakeEntity, Ref(Entity_BrickBlock), 25, 50, 0, 0, 0x80000000)
    Call(AssignScript, Ref(tik_05_EVS_BreakBlock_DropSpring))
    IfEq(GameFlag(4541), 0)
        IfEq(GameFlag(424), 0)
            Call(MakeEntity, Ref(Entity_SimpleSpring), 25, 75, 0, 0, 100, 0x80000000)
        Else
            Call(MakeEntity, Ref(Entity_SimpleSpring), -35, -10, 0, 0, 100, 0x80000000)
        EndIf
    Else
        Call(MakeEntity, Ref(Entity_SimpleSpring), -35, -10, 0, 0, 210, 0x80000000)
    EndIf
    Set(MapVar(0), LVar0)
    IfEq(GameFlag(4541), 0)
        Call(MakeEntity, Ref(Entity_TriggerBlock), 25, 136, -24, 0, 0x80000000)
        Call(AssignScript, Ref(TTYD64_tik_05_Script_ActivateNewSpring))
    EndIf
    Call(MakeEntity, Ref(Entity_Chest), 311, 251, -92, -45, 0, 0x80000000)
    Call(AssignChestFlag, GameFlag(4543))
    Call(AssignScript, Ref(TTYD64_tik_05_Script_OpenChest))
    Return
    End
};

EvtScript TTYD64_tik_05_Script_ShowGotItem = {
    SetGroup(0)
    Call(SetTimeFreezeMode, 2)
    Wait(40)
    Call(ShowGotItem, LVar0, 0, 0)
    Call(SetTimeFreezeMode, 0)
    Return
    Return
    End
};

EvtScript TTYD64_tik_05_Script_OpenChest = {
    Set(LVarA, 370)
    Set(LVarB, 2)
    Set(GameFlag(4543), 1)
    ExecWait(TTYD64_tik_05_Script_GiveItem)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_tik_05(void) {
    Mod_ReplaceScript("TTYD64", &tik_05_EVS_MakeEntities, &TTYD64_tik_05_Script_MakeEntities);
}
