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

extern NpcGroupList jan_00_DefaultNPCs;
extern EvtScript jan_00_EVS_802467AC;
extern EvtScript jan_00_EVS_80247A2C;
extern EvtScript jan_00_EVS_BindExitTriggers;
extern EvtScript jan_00_EVS_Main;
extern EvtScript jan_00_EVS_MakeEntities;
extern EvtScript jan_00_EVS_UpdateTexturePan;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(EnableTexPanning);
API_CALLABLE(GetEntryID);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlaySound);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(func_8024030C_B2084C);

extern EvtScript TTYD64_jan_00_Script_Main_EnterWalk;
extern EvtScript TTYD64_jan_00_Script_InitNewStuff;
extern EvtScript TTYD64_jan_00_Script_SetMusicTrack;
extern EvtScript TTYD64_jan_00_Script_Entity_Shine1;

// clang-format off
EvtScript TTYD64_jan_00_Script_Main_EnterWalk = {
    Set(GameByte(425), 36)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Set(GameFlag(1981), 1)
    Call(MakeNpcs, 0, Ref(jan_00_DefaultNPCs))
    ExecWait(jan_00_EVS_MakeEntities)
    Call(EnableTexPanning, 15, 1)
    Call(EnableTexPanning, 13, 1)
    Call(EnableTexPanning, 14, 1)
    Thread
        Set(LVar0, 1)
        Set(LVar1, 0)
        Set(LVar2, 400)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 0)
        Set(LVar6, 1)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(jan_00_EVS_UpdateTexturePan)
    EndThread
    Thread
        Set(LVar0, 3)
        Set(LVar1, -100)
        Set(LVar2, 200)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(jan_00_EVS_UpdateTexturePan)
    EndThread
    Exec(jan_00_EVS_802467AC)
    Exec(jan_00_EVS_80247A2C)
    Call(ModifyColliderFlags, 0, 5, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 0)
        Exec(jan_00_EVS_BindExitTriggers)
    Else
        Set(LVar0, Ref(jan_00_EVS_BindExitTriggers))
        Exec(EnterWalk)
    EndIf
    Call(func_8024030C_B2084C)
    ExecWait(TTYD64_jan_00_Script_SetMusicTrack)
    Call(PlaySound, 0x80000017)
    Return
    End
};

EvtScript TTYD64_jan_00_Script_InitNewStuff = {
    Call(MakeEntity, Ref(Entity_SuperBlock), -18, 348, -426, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(5379))
    Call(AssignScript, Ref(TTYD64_jan_00_Script_Entity_Shine1))
    Return
    End
};

EvtScript TTYD64_jan_00_Script_SetMusicTrack = {
    Call(SetMusic, 0, 38, 0, 8)
    Call(ClearAmbientSounds, 250)
    Exec(TTYD64_jan_00_Script_InitNewStuff)
    Return
    End
};

EvtScript TTYD64_jan_00_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(5379))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_jan_00(void) {
    Mod_ReplaceScript("TTYD64", &jan_00_EVS_Main, &TTYD64_jan_00_Script_Main_EnterWalk);
}
