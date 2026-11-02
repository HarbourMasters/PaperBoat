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

extern NpcGroupList omo_04_ClubbaAmbushNPCs;
extern NpcGroupList omo_04_DefaultNPCs;
extern EvtScript omo_04_EVS_BindExitTriggers;
extern EvtScript omo_04_EVS_Main;
extern EvtScript omo_04_EVS_MakeEntities;
extern EvtScript omo_04_EVS_Scene_KammySetAmbush;
extern EvtScript omo_04_EVS_SetupGizmos;
extern NpcGroupList omo_04_GoombaAmbushNPCs;
extern NpcGroupList omo_04_KammySceneNPCs;

API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetSpriteShading);

extern EvtScript TTYD64_omo_04_Script_Main_EnterWalk;
extern EvtScript TTYD64_omo_04_Script_InitNewStuff;
extern EvtScript TTYD64_omo_04_Script_SetMusicTrack;

// clang-format off
EvtScript TTYD64_omo_04_Script_Main_EnterWalk = {
    Set(GameByte(425), 16)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    IfEq(GameFlag(1118), 0)
        Call(MakeNpcs, 1, Ref(omo_04_KammySceneNPCs))
    Else
        IfEq(GameFlag(1102), 0)
            Switch(GameByte(216))
            CaseEq(0)
                Call(MakeNpcs, 1, Ref(omo_04_GoombaAmbushNPCs))
            CaseEq(1)
                Call(MakeNpcs, 1, Ref(omo_04_ClubbaAmbushNPCs))
            CaseEq(2)
                Call(MakeNpcs, 1, Ref(omo_04_DefaultNPCs))
                Call(MakeItemEntity, 138, 1100, 0, 0, 17, GameFlag(1102))
            EndSwitch
        Else
            Call(MakeNpcs, 1, Ref(omo_04_DefaultNPCs))
        EndIf
    EndIf
    ExecWait(omo_04_EVS_MakeEntities)
    ExecWait(omo_04_EVS_SetupGizmos)
    ExecWait(TTYD64_omo_04_Script_SetMusicTrack)
    IfEq(GameFlag(1118), 0)
        Exec(omo_04_EVS_Scene_KammySetAmbush)
    Else
        Set(LVar0, Ref(omo_04_EVS_BindExitTriggers))
        Exec(EnterWalk)
        Wait(1)
    EndIf
    Return
    End
};

EvtScript TTYD64_omo_04_Script_InitNewStuff = {
    Call(MakeItemEntity, 343, -833, 26, -177, 17, 0)
    Call(MakeItemEntity, 348, -892, 0, -177, 17, GameFlag(5252))
    Call(MakeItemEntity, 388, 630, 0, -96, 17, GameFlag(5253))
    Return
    End
};

EvtScript TTYD64_omo_04_Script_SetMusicTrack = {
    IfEq(GameFlag(1118), 0)
        Call(SetMusic, 0, 70, 0, 8)
    Else
        Call(SetMusic, 0, 32, 0, 8)
    EndIf
    Exec(TTYD64_omo_04_Script_InitNewStuff)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_omo_04(void) {
    Mod_ReplaceScript("TTYD64", &omo_04_EVS_Main, &TTYD64_omo_04_Script_Main_EnterWalk);
}
