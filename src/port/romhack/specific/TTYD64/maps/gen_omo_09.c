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

extern NpcGroupList omo_09_DefaultNPCs;
extern EvtScript omo_09_EVS_ExitWalk_omo_08_0;
extern EvtScript omo_09_EVS_Main;
extern EvtScript omo_09_EVS_MakeEntities;
extern EvtScript omo_09_EVS_Scene_KammySetAmbush;
extern EvtScript omo_09_EVS_SetupConveyors;
extern EvtScript omo_09_EVS_SetupGizmos;
extern EvtScript omo_09_EVS_SetupSlotMachine;
extern NpcGroupList omo_09_KammySceneNPCs;
extern NpcGroupList omo_09_KoopatrolAmbushNPCs;
extern NpcGroupList omo_09_PokeyAmbushNPCs;
extern MapSettings omo_09_settings;

API_CALLABLE(EnableGroup);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(UseExitHeading);

extern BombTrigger TTYD64_omo_09_TriggerCoord_Wall;
extern EvtScript TTYD64_omo_09_Script_Exit1;
extern EntryList TTYD64_omo_09_EntryList;
extern EvtScript TTYD64_omo_09_Script_Main_EnterWalk;
extern EvtScript TTYD64_omo_09_Script_SetMusicTrack;
extern EvtScript TTYD64_omo_09_Script_BlastWall;
extern EvtScript TTYD64_omo_09_Script_InitNewStuff;
extern EvtScript TTYD64_omo_09_Script_MakeExits;
extern EvtScript TTYD64_omo_09_Script_HideWall;

// clang-format off
BombTrigger TTYD64_omo_09_TriggerCoord_Wall = {
    .pos = { 2000.0f, 25.0f, 8.0f },
    .diameter = 0.0f
};

EvtScript TTYD64_omo_09_Script_Exit1 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 1)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "omo_18", 0)
    Wait(100)
    Return
    End
};

EntryList TTYD64_omo_09_EntryList = {
    { -980.0f, 0.0f, 0.0f, 90.0f },
    { 1936.0f, 25.0f, 7.0f, -90.0f },
};

EvtScript TTYD64_omo_09_Script_Main_EnterWalk = {
    Set(GameByte(425), 16)
    IfGe(GameByte(0), 4)
        Set(GameFlag(1146), 1)
    EndIf
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    IfEq(GameFlag(1146), 0)
        Call(MakeNpcs, 1, Ref(omo_09_KammySceneNPCs))
    Else
        IfEq(GameFlag(1104), 0)
            Switch(GameByte(218))
            CaseEq(0)
                Call(MakeNpcs, 1, Ref(omo_09_PokeyAmbushNPCs))
            CaseEq(1)
                Call(MakeNpcs, 1, Ref(omo_09_KoopatrolAmbushNPCs))
            CaseEq(2)
                Call(MakeNpcs, 1, Ref(omo_09_DefaultNPCs))
                Call(MakeItemEntity, 155, 1900, 150, 0, 17, GameFlag(1104))
            EndSwitch
        Else
            Call(MakeNpcs, 1, Ref(omo_09_DefaultNPCs))
        EndIf
    EndIf
    ExecWait(omo_09_EVS_MakeEntities)
    ExecWait(omo_09_EVS_SetupGizmos)
    ExecWait(TTYD64_omo_09_Script_SetMusicTrack)
    ExecWait(omo_09_EVS_SetupConveyors)
    ExecWait(omo_09_EVS_SetupSlotMachine)
    IfEq(GameFlag(1146), 0)
        Exec(omo_09_EVS_Scene_KammySetAmbush)
        Wait(2)
    Else
        Set(LVar0, Ref(TTYD64_omo_09_Script_MakeExits))
        Exec(EnterWalk)
        Wait(1)
    EndIf
    Return
    End
};

EvtScript TTYD64_omo_09_Script_SetMusicTrack = {
    IfEq(GameFlag(1146), 0)
        Call(SetMusic, 0, 70, 0, 8)
    Else
        Call(SetMusic, 0, 32, 0, 8)
    EndIf
    Exec(TTYD64_omo_09_Script_InitNewStuff)
    Return
    End
};

EvtScript TTYD64_omo_09_Script_BlastWall = {
    Call(PlayEffect_impl, 66, 0, 155, 155, 1, 10, 30, 0, 0, 0, 0, 0, 0)
    Exec(TTYD64_omo_09_Script_HideWall)
    Set(GameFlag(5258), 1)
    Unbind
    Return
    End
};

EvtScript TTYD64_omo_09_Script_InitNewStuff = {
    IfEq(GameFlag(5258), 1)
        Exec(TTYD64_omo_09_Script_HideWall)
    Else
        BindTrigger(TTYD64_omo_09_Script_BlastWall, 0x100000, Ref(TTYD64_omo_09_TriggerCoord_Wall), 1, 0)
    EndIf
    Return
    End
};

EvtScript TTYD64_omo_09_Script_MakeExits = {
    BindTrigger(omo_09_EVS_ExitWalk_omo_08_0, 0x80000, 0, 1, 0)
    BindTrigger(TTYD64_omo_09_Script_Exit1, 0x80000, 55, 1, 0)
    Return
    End
};

EvtScript TTYD64_omo_09_Script_HideWall = {
    Call(EnableGroup, 157, 0)
    Call(ModifyColliderFlags, 0, 53, 0x7FFFFE00)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_omo_09(void) {
    omo_09_settings.entryList = &TTYD64_omo_09_EntryList;
    omo_09_settings.entryCount = 2;
    Mod_ReplaceScript("TTYD64", &omo_09_EVS_Main, &TTYD64_omo_09_Script_Main_EnterWalk);
}
