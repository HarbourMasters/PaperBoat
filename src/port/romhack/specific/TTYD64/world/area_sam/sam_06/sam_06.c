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

extern BombTrigger sam_06_BombPos_Tree2;
extern BombTrigger sam_06_BombPos_Tree3;
extern BombTrigger sam_06_BombPos_Tree4;
extern BombTrigger sam_06_BombPos_Tree5;
extern NpcGroupList sam_06_DefaultNPCs;
extern EvtScript sam_06_EVS_BindExitTriggers;
extern EvtScript sam_06_EVS_ExitWalk_sam_05_1;
extern EvtScript sam_06_EVS_Main;
extern EvtScript sam_06_EVS_MakeEntities;
extern EvtScript sam_06_EVS_ManageSnowfall;
extern EvtScript sam_06_EVS_SetupMusic;
extern EvtScript sam_06_EVS_SetupRooms;
extern EvtScript sam_06_EVS_TexPan_Fire;
extern ShakeTreeConfig sam_06_ShakeTree_Tree2;
extern ShakeTreeConfig sam_06_ShakeTree_Tree3;
extern ShakeTreeConfig sam_06_ShakeTree_Tree4;
extern ShakeTreeConfig sam_06_ShakeTree_Tree5;
extern FoliageModelList sam_06_Tree1_TrunkModels;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(ClearDefeatedEnemies);
API_CALLABLE(DropItemEntity);
API_CALLABLE(EnableModel);
API_CALLABLE(GetLoadType);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GetValueByRef);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(NpcJump0);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtModel);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetItemPos);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcJumpscale);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetRenderMode);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetValueByRef);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateLerp);

extern EvtScript TTYD64_sam_06_Script_ShakeTree_80242ACC;
extern ShakeTreeConfig TTYD64_sam_06_ShakeTreeEvent_ItemTree;
extern EvtScript TTYD64_sam_06_Script_Main_EnterWalk;
extern EvtScript TTYD64_sam_06_Script_ItemTree_Callback;
extern EvtScript TTYD64_sam_06_Script_InitNewStuff;
extern EvtScript TTYD64_sam_06_Script_LiftBranches;
extern EvtScript TTYD64_sam_06_Script_StickItemToNPC;
extern EvtScript TTYD64_sam_06_Script_Entity_Shine1;
extern EvtScript TTYD64_sam_06_Script_80243230;

// clang-format off
EvtScript TTYD64_sam_06_Script_ShakeTree_80242ACC = {
    SetTimescale(Float(2.0))
    UseBuf(LVar0)
    BufRead4(LVar1, LVar2, LVar3, LVar4)
    BufRead1(LVar5)
    Call(GetPlayerPos, LVar6, LVarF, LVar8)
    Call(PlaySound, 357)
    Call(PlaySound, 358)
    Thread
        Set(LFlag0, 0)
        IfNe(LVar1, 0)
            Wait(1)
            Loop(5)
                UseBuf(LVar1)
                BufRead1(LVar2)
                Loop(LVar2)
                    BufRead1(LVar3)
                    Call(TTYD64_maps_TransformFoliage, LVar3, Float(0.1005859375), Float(0.2001953125), LVarF, 0)
                    IfEq(LFlag0, 0)
                        Set(LFlag0, 1)
                        Call(PlaySoundAtModel, LVar3, 358, 0)
                    EndIf
                EndLoop
                Wait(1)
                UseBuf(LVar1)
                BufRead1(LVar2)
                Loop(LVar2)
                    BufRead1(LVar3)
                    Call(TTYD64_maps_TransformFoliage, LVar3, Float(0.1005859375), Float(-0.19921875), LVarF, 0)
                EndLoop
                Wait(1)
            EndLoop
            UseBuf(LVar1)
            BufRead1(LVar2)
            Loop(LVar2)
                BufRead1(LVar3)
                Call(TranslateModel, LVar3, 0, 0, 0)
            EndLoop
            Wait(1)
        EndIf
    EndThread
    Thread
        Set(LFlag0, 0)
        IfNe(LVar2, 0)
            Loop(5)
                UseBuf(LVar2)
                BufRead1(LVar3)
                Loop(LVar3)
                    BufRead1(LVar4)
                    Call(TTYD64_maps_TransformFoliage, LVar4, Float(0.1005859375), Float(0.2001953125), LVarF, 0)
                    IfEq(LFlag0, 0)
                        Set(LFlag0, 1)
                        Call(PlaySoundAtModel, LVar4, 357, 0)
                    EndIf
                EndLoop
                Wait(1)
                UseBuf(LVar2)
                BufRead1(LVar3)
                Loop(LVar3)
                    BufRead1(LVar4)
                    Call(TTYD64_maps_TransformFoliage, LVar4, Float(0.1005859375), Float(-0.19921875), LVarF, 0)
                EndLoop
                Wait(1)
            EndLoop
            UseBuf(LVar2)
            BufRead1(LVar3)
            Loop(LVar3)
                BufRead1(LVar4)
                Call(TranslateModel, LVar4, 0, 0, 0)
            EndLoop
            Wait(1)
        EndIf
    EndThread
    Thread
        IfNe(LVar3, 0)
            UseBuf(LVar3)
            BufRead1(LVar4)
            Loop(LVar4)
                BufRead1(LVar5)
                BufRead3(LVar6, LVar7, LVar8)
                BufRead3(LVar9, LVarA, LVarB)
                IfEq(LVarB, 0)
                    Call(DropItemEntity, LVar5, LVar6, LVar7, LVar8, LVar9, LVarA)
                Else
                    Call(GetValueByRef, LVarB, LVarC)
                    IfEq(LVarC, 0)
                        Call(SetValueByRef, LVarB, 1)
                        Call(DropItemEntity, LVar5, LVar6, LVar7, LVar8, LVar9, LVarA)
                    EndIf
                EndIf
            EndLoop
        EndIf
    EndThread
    Thread
        IfNe(LVar4, 0)
            UseBuf(LVar4)
            BufRead1(LVar5)
            Loop(LVar5)
                BufRead3(LVar6, LVar7, LVar8)
                Call(PlayEffect_impl, 20, 0, LVar6, LVar7, LVar8, 100, 0, 0, 0, 0, 0, 0, 0, 0)
            EndLoop
        EndIf
    EndThread
    IfNe(LVar5, 0)
        ExecWait(LVar5)
    EndIf
    Wait(15)
    Return
    End
};

ShakeTreeConfig TTYD64_sam_06_ShakeTreeEvent_ItemTree = {
    .leaves = NULL,
    .trunk = &sam_06_Tree1_TrunkModels,
    .drops = NULL,
    .vectors = NULL,
    .callback = &TTYD64_sam_06_Script_ItemTree_Callback,
};

EvtScript TTYD64_sam_06_Script_Main_EnterWalk = {
    Set(GameByte(425), 42)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Set(GameFlag(1988), 1)
    Call(MakeNpcs, 0, Ref(sam_06_DefaultNPCs))
    Call(ClearDefeatedEnemies)
    ExecWait(sam_06_EVS_MakeEntities)
    ExecWait(sam_06_EVS_SetupMusic)
    Exec(sam_06_EVS_ManageSnowfall)
    Exec(sam_06_EVS_TexPan_Fire)
    ExecWait(sam_06_EVS_SetupRooms)
    Call(SetRenderMode, 100, 21)
    Call(SetRenderMode, 27, 21)
    Call(ModifyColliderFlags, 3, 54, 8)
    Call(ModifyColliderFlags, 3, 1, 8)
    Call(ModifyColliderFlags, 3, 43, 8)
    Call(ModifyColliderFlags, 3, 56, 8)
    Call(ModifyColliderFlags, 3, 45, 8)
    Call(ModifyColliderFlags, 3, 47, 8)
    Call(ModifyColliderFlags, 3, 48, 8)
    Call(ModifyColliderFlags, 3, 49, 8)
    Call(ModifyColliderFlags, 3, 50, 8)
    Call(ModifyColliderFlags, 3, 52, 8)
    Set(LVar0, Ref(TTYD64_sam_06_ShakeTreeEvent_ItemTree))
    BindTrigger(TTYD64_sam_06_Script_ShakeTree_80242ACC, 4096, 65, 1, 0)
    Set(LVar0, Ref(sam_06_ShakeTree_Tree2))
    BindTrigger(TTYD64_sam_06_Script_ShakeTree_80242ACC, 0x100000, Ref(sam_06_BombPos_Tree2), 1, 0)
    Set(LVar0, Ref(sam_06_ShakeTree_Tree3))
    BindTrigger(TTYD64_sam_06_Script_ShakeTree_80242ACC, 0x100000, Ref(sam_06_BombPos_Tree3), 1, 0)
    Set(LVar0, Ref(sam_06_ShakeTree_Tree4))
    BindTrigger(TTYD64_sam_06_Script_ShakeTree_80242ACC, 0x100000, Ref(sam_06_BombPos_Tree4), 1, 0)
    Set(LVar0, Ref(sam_06_ShakeTree_Tree5))
    BindTrigger(TTYD64_sam_06_Script_ShakeTree_80242ACC, 4096, 59, 1, 0)
    BindTrigger(TTYD64_sam_06_Script_ShakeTree_80242ACC, 0x100000, Ref(sam_06_BombPos_Tree5), 1, 0)
    Call(GetLoadType, LVar1)
    IfEq(LVar1, 1)
        Exec(EnterSavePoint)
        Exec(sam_06_EVS_BindExitTriggers)
        Wait(1)
    Else
        Set(LVar0, Ref(sam_06_EVS_BindExitTriggers))
        Exec(EnterWalk)
        Wait(1)
    EndIf
    Thread
        Set(LVar2, 0)
        Label(0)
        Call(MakeLerp, 100, 90, 5, 0)
        Label(1)
        Call(UpdateLerp)
        MulF(LVar0, Float(0.0107421875))
        Add(LVar2, 8)
        Mod(LVar2, 360)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(1)
        EndIf
        Call(MakeLerp, 90, 100, 5, 0)
        Label(2)
        Call(UpdateLerp)
        MulF(LVar0, Float(0.0107421875))
        Add(LVar2, 8)
        Mod(LVar2, 360)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(2)
        EndIf
        Goto(0)
    EndThread
    Return
    End
};

EvtScript TTYD64_sam_06_Script_ItemTree_Callback = {
    Switch(MapVar(3))
    CaseEq(0)
        Add(MapVar(3), 1)
        Set(LVar2, 167)
        ExecWait(TTYD64_sam_06_Script_LiftBranches)
    CaseEq(1)
        Add(MapVar(3), 1)
        Set(LVar2, 166)
        ExecWait(TTYD64_sam_06_Script_LiftBranches)
    CaseEq(2)
        Add(MapVar(3), 1)
        Set(LVar2, 165)
        ExecWait(TTYD64_sam_06_Script_LiftBranches)
    CaseEq(3)
        IfEq(GameFlag(5567), 0)
            Call(SetNpcFlagBits, 3, 0x1000000, 1)
            IfEq(MapVar(2), 0)
                Set(MapVar(2), 1)
                Call(SetNpcPos, 3, -183, 157, -238)
                ExecGetTID(TTYD64_sam_06_Script_StickItemToNPC, LVarA)
                Call(SetNpcJumpscale, 3, Float(2.0))
                Call(NpcJump0, 3, -130, 90, -176, 20)
                KillThread(LVarA)
                Wait(1)
                Call(SetNpcPos, 3, 127, 0, 445)
                Call(SetNpcFlagBits, 3, 0x1000000, 0)
            EndIf
        EndIf
    EndSwitch
    Return
    End
};

EvtScript TTYD64_sam_06_Script_InitNewStuff = {
    Call(MakeItemEntity, 348, -183, 157, -238, 17, GameFlag(5567))
    Set(MapVar(1), LVar0)
    Call(MakeItemEntity, 343, 463, 80, 69, 17, 0)
    Call(MakeEntity, Ref(Entity_SuperBlock), 474, 146, -14, 0, 0x80000000)
    Set(MapVar(4), LVar0)
    Call(AssignBlockFlag, GameFlag(5566))
    Call(AssignScript, Ref(TTYD64_sam_06_Script_Entity_Shine1))
    Return
    End
};

EvtScript TTYD64_sam_06_Script_LiftBranches = {
    Call(MakeLerp, 0, 255, 20, 3)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateModel, LVar2, 0, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(EnableModel, LVar2, 0)
    Return
    End
};

EvtScript TTYD64_sam_06_Script_StickItemToNPC = {
    Loop(0)
        Call(GetNpcPos, 3, LVar0, LVar1, LVar2)
        Call(SetItemPos, MapVar(1), LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_sam_06_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(4))
    SetConst(LVar1, GameFlag(5566))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_sam_06_Script_80243230 = {
    BindTrigger(sam_06_EVS_ExitWalk_sam_05_1, 0x80000, 1, 1, 0)
    Exec(TTYD64_sam_06_Script_InitNewStuff)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_sam_06(void) {
    Mod_ReplaceScript("TTYD64", &sam_06_EVS_Main, &TTYD64_sam_06_Script_Main_EnterWalk);
    Mod_ReplaceScript("TTYD64", &sam_06_EVS_BindExitTriggers, &TTYD64_sam_06_Script_80243230);
    Mod_RegisterWideEvtBuffer("TTYD64", (const intptr_t*) &TTYD64_sam_06_ShakeTreeEvent_ItemTree, 5);
    Mod_RegisterWideEvtBuffer("TTYD64", (const intptr_t*) &sam_06_ShakeTree_Tree2, 5);
    Mod_RegisterWideEvtBuffer("TTYD64", (const intptr_t*) &sam_06_ShakeTree_Tree3, 5);
    Mod_RegisterWideEvtBuffer("TTYD64", (const intptr_t*) &sam_06_ShakeTree_Tree4, 5);
    Mod_RegisterWideEvtBuffer("TTYD64", (const intptr_t*) &sam_06_ShakeTree_Tree5, 5);
}
