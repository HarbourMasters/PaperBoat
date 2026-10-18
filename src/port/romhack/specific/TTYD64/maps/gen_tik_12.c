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

extern EvtScript tik_12_EVS_MakeEntities;
extern EvtScript tik_12_EVS_SetupMusic;
extern EvtScript tik_12_EVS_SmashBlockA;
extern EvtScript tik_12_EVS_SmashBlockB;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(EnableGroup);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtCollider);
API_CALLABLE(SetMusic);
API_CALLABLE(TranslateGroup);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UpdateLerp);

extern EvtScript TTYD64_tik_12_Script_InitNewStuff;
extern EvtScript TTYD64_tik_12_Script_UpdatePlatform_Z;
extern EvtScript TTYD64_tik_12_Script_VerticalPlatform;
extern EvtScript TTYD64_tik_12_Script_BlastWall;
extern EvtScript TTYD64_tik_12_Script_UpdateWall;
extern EvtScript TTYD64_tik_12_Script_InitPlatform_3;
extern EvtScript TTYD64_tik_12_Script_InitMovingPlatforms;
extern EvtScript TTYD64_tik_12_Script_Entity_Shine1;
extern BombTrigger TTYD64_tik_12_TriggerCoord_Wall;
extern EvtScript TTYD64_tik_12_Script_UpdatePlatform_X;
extern EvtScript TTYD64_tik_12_Script_MakeEntities;
extern EvtScript TTYD64_tik_12_Script_InitHorizontalPlatforms;
extern EvtScript TTYD64_tik_12_Script_Entity_Shine2;
extern EvtScript TTYD64_tik_12_Script_InitPlatform_2;
extern EvtScript TTYD64_tik_12_Script_InitPlatform_6;
extern EvtScript TTYD64_tik_12_Script_InitPlatform_5;
extern EvtScript TTYD64_tik_12_Script_InitPlatform_4;
extern EvtScript TTYD64_tik_12_Script_802422A0;

// clang-format off
EvtScript TTYD64_tik_12_Script_InitNewStuff = {
    Exec(TTYD64_tik_12_Script_UpdateWall)
    Exec(TTYD64_tik_12_Script_InitMovingPlatforms)
    Return
    End
};

EvtScript TTYD64_tik_12_Script_UpdatePlatform_Z = {
    Set(LVar8, LVar0)
    Set(LVar9, LVar1)
    Loop(0)
        Call(PlaySoundAtCollider, LVar9, 221, 0)
        Call(MakeLerp, 0, -114, 5, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, LVar8, 0, 0, LVar0)
            Call(UpdateColliderTransform, LVar9)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(40)
        Call(PlaySoundAtCollider, LVar9, 123, 0)
        Call(MakeLerp, -114, 0, 10, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, LVar8, 0, 0, LVar0)
            Call(UpdateColliderTransform, LVar9)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(30)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tik_12_Script_VerticalPlatform = {
    Loop(0)
        Call(MakeLerp, 0, 125, 125, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, 35, 0, LVar0, 0)
            Call(UpdateColliderTransform, 8)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(40)
        Call(MakeLerp, 125, 0, 125, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, 35, 0, LVar0, 0)
            Call(UpdateColliderTransform, 8)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(40)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tik_12_Script_BlastWall = {
    Call(PlayEffect_impl, 66, 0, 18, 18, 1, 10, 30, 0, 0, 0, 0, 0, 0)
    Call(EnableGroup, 20, 0)
    Call(ModifyColliderFlags, 0, 15, 0x7FFFFE00)
    Set(GameFlag(4539), 1)
    Unbind
    Return
    End
};

EvtScript TTYD64_tik_12_Script_UpdateWall = {
    IfEq(GameFlag(4539), 0)
        BindTrigger(TTYD64_tik_12_Script_BlastWall, 0x100000, Ref(TTYD64_tik_12_TriggerCoord_Wall), 1, 0)
    Else
        Call(EnableGroup, 20, 0)
        Call(ModifyColliderFlags, 0, 15, 0x7FFFFE00)
    EndIf
    Return
    End
};

EvtScript TTYD64_tik_12_Script_InitPlatform_3 = {
    Set(LVar0, 37)
    Set(LVar1, 10)
    Exec(TTYD64_tik_12_Script_UpdatePlatform_Z)
    Return
    End
};

EvtScript TTYD64_tik_12_Script_InitMovingPlatforms = {
    Call(ParentColliderToModel, 8, 35)
    Call(ParentColliderToModel, 9, 36)
    Call(ParentColliderToModel, 10, 37)
    Call(ParentColliderToModel, 11, 38)
    Call(ParentColliderToModel, 12, 39)
    Call(ParentColliderToModel, 13, 40)
    Exec(TTYD64_tik_12_Script_InitHorizontalPlatforms)
    Wait(20)
    Exec(TTYD64_tik_12_Script_VerticalPlatform)
    Return
    End
};

EvtScript TTYD64_tik_12_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(435))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

BombTrigger TTYD64_tik_12_TriggerCoord_Wall = {
    .pos = { -254.0f, -135.0f, 19.0f },
    .diameter = 0.0f
};

EvtScript TTYD64_tik_12_Script_UpdatePlatform_X = {
    Set(LVar8, LVar0)
    Set(LVar9, LVar1)
    Loop(0)
        Call(PlaySoundAtCollider, LVar9, 221, 0)
        Call(MakeLerp, 0, -103, 5, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, LVar8, LVar0, 0, 0)
            Call(UpdateColliderTransform, LVar9)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(40)
        Call(PlaySoundAtCollider, LVar9, 123, 0)
        Call(MakeLerp, -103, 0, 10, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, LVar8, LVar0, 0, 0)
            Call(UpdateColliderTransform, LVar9)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(30)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tik_12_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SuperBlock), 240, 0, -40, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(435))
    Call(AssignScript, Ref(TTYD64_tik_12_Script_Entity_Shine1))
    IfEq(GameFlag(395), 0)
        Call(MakeEntity, Ref(Entity_Hammer3Block), 140, -135, 55, 0, 0x80000000)
        Call(AssignScript, Ref(tik_12_EVS_SmashBlockA))
    EndIf
    IfEq(GameFlag(396), 0)
        Call(MakeEntity, Ref(Entity_Hammer3Block), 140, -135, 105, 0, 0x80000000)
        Call(AssignScript, Ref(tik_12_EVS_SmashBlockB))
    EndIf
    Call(MakeEntity, Ref(Entity_SuperBlock), -715, 57, 103, 90, 0x80000000)
    Set(MapVar(1), LVar0)
    Call(AssignBlockFlag, GameFlag(4540))
    Call(AssignScript, Ref(TTYD64_tik_12_Script_Entity_Shine2))
    Return
    End
};

EvtScript TTYD64_tik_12_Script_InitHorizontalPlatforms = {
    Wait(400)
    Exec(TTYD64_tik_12_Script_InitPlatform_2)
    Wait(5)
    Exec(TTYD64_tik_12_Script_InitPlatform_3)
    Wait(5)
    Exec(TTYD64_tik_12_Script_InitPlatform_4)
    Wait(5)
    Exec(TTYD64_tik_12_Script_InitPlatform_5)
    Wait(5)
    Exec(TTYD64_tik_12_Script_InitPlatform_6)
    Return
    End
};

EvtScript TTYD64_tik_12_Script_Entity_Shine2 = {
    Set(LVar0, MapVar(1))
    SetConst(LVar1, GameFlag(4540))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_tik_12_Script_InitPlatform_2 = {
    Set(LVar0, 36)
    Set(LVar1, 9)
    Exec(TTYD64_tik_12_Script_UpdatePlatform_Z)
    Return
    End
};

EvtScript TTYD64_tik_12_Script_InitPlatform_6 = {
    Set(LVar0, 40)
    Set(LVar1, 13)
    Exec(TTYD64_tik_12_Script_UpdatePlatform_X)
    Return
    End
};

EvtScript TTYD64_tik_12_Script_InitPlatform_5 = {
    Set(LVar0, 39)
    Set(LVar1, 12)
    Exec(TTYD64_tik_12_Script_UpdatePlatform_X)
    Return
    End
};

EvtScript TTYD64_tik_12_Script_InitPlatform_4 = {
    Set(LVar0, 38)
    Set(LVar1, 11)
    Exec(TTYD64_tik_12_Script_UpdatePlatform_Z)
    Return
    End
};

EvtScript TTYD64_tik_12_Script_802422A0 = {
    Call(SetMusic, 0, 75, 0, 8)
    Exec(TTYD64_tik_12_Script_InitNewStuff)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_tik_12(void) {
    Mod_ReplaceScript("TTYD64", &tik_12_EVS_MakeEntities, &TTYD64_tik_12_Script_MakeEntities);
    Mod_ReplaceScript("TTYD64", &tik_12_EVS_SetupMusic, &TTYD64_tik_12_Script_802422A0);
}
