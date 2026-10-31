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

extern EvtScript kkj_16_EVS_AutoRemovePowerRush;
extern EvtScript kkj_16_EVS_MakeEntities;
extern MapSettings kkj_16_settings;

API_CALLABLE(DisablePlayerInput);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlaySound);
API_CALLABLE(ShakeCam);
API_CALLABLE(StopSound);
API_CALLABLE(TranslateGroup);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_kkj_16_Script_Exit1;
extern EvtScript TTYD64_kkj_16_Script_ShowPassage;
extern EvtScript TTYD64_kkj_16_Script_NewStuff;
extern EvtScript TTYD64_kkj_16_Script_8024476C;
extern EntryList TTYD64_kkj_16_EntryList;

// clang-format off
EvtScript TTYD64_kkj_16_Script_Exit1 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 1)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "kkj_30", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_kkj_16_Script_ShowPassage = {
    Call(DisablePlayerInput, 1)
    Call(PlaySound, 338)
    Call(MakeLerp, 0, -5, 10, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, 151, 0, 0, LVar0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Wait(10)
    Call(PlaySound, 82)
    Call(MakeLerp, 0, -53, 25, 0)
    Thread
        Call(ShakeCam, 0, 0, 25, Float(0.2001953125))
    EndThread
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateModel, 79, 0, 0, LVar0)
        Call(TranslateModel, 80, 0, 0, LVar0)
        Call(TranslateModel, 81, 0, 0, LVar0)
        Call(TranslateModel, 82, 0, 0, LVar0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Unbind
    Call(StopSound, 82)
    Call(ModifyColliderFlags, 0, 49, 0x7FFFFE00)
    Call(DisablePlayerInput, 0)
    Set(GameFlag(4607), 1)
    Return
    End
};

EvtScript TTYD64_kkj_16_Script_NewStuff = {
    Call(MakeItemEntity, 348, -660, 100, 78, 17, GameFlag(4608))
    IfEq(GameFlag(4607), 1)
        Call(ModifyColliderFlags, 0, 49, 0x7FFFFE00)
        Call(TranslateModel, 79, 0, 0, -53)
        Call(TranslateModel, 80, 0, 0, -53)
        Call(TranslateModel, 81, 0, 0, -53)
        Call(TranslateModel, 82, 0, 0, -53)
        Call(TranslateModel, 151, 0, 0, -5)
    Else
        BindTrigger(TTYD64_kkj_16_Script_ShowPassage, 256, 50, 1, 0)
    EndIf
    BindTrigger(TTYD64_kkj_16_Script_Exit1, 0x80000, 46, 1, 0)
    Return
    End
};

EvtScript TTYD64_kkj_16_Script_8024476C = {
    Call(MakeItemEntity, 149, -840, 110, 10, 17, GameFlag(504))
    Call(MakeItemEntity, 269, -550, 0, -120, 17, GameFlag(484))
    ExecWait(TTYD64_kkj_16_Script_NewStuff)
    IfLt(GameByte(0), 95)
        IfEq(GameFlag(484), 0)
            Exec(kkj_16_EVS_AutoRemovePowerRush)
        EndIf
    EndIf
    Return
    End
};

EntryList TTYD64_kkj_16_EntryList = {
    { 435.0f, 0.0f, -25.0f, 270.0f },
    { -800.0f, 110.0f, -175.0f, 90.0f },
};
// clang-format on

void TTYD64_InstallMap_kkj_16(void) {
    kkj_16_settings.entryList = &TTYD64_kkj_16_EntryList;
    kkj_16_settings.entryCount = 2;
    Mod_ReplaceScript("TTYD64", &kkj_16_EVS_MakeEntities, &TTYD64_kkj_16_Script_8024476C);
}
