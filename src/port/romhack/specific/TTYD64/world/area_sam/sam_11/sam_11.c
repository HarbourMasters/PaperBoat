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

extern NpcGroupList sam_11_AfterNPCs;
extern NpcGroupList sam_11_BeforeNPCs;
extern BombTrigger sam_11_BombPos_Tree1;
extern BombTrigger sam_11_BombPos_Tree2;
extern BombTrigger sam_11_BombPos_Tree3;
extern EvtScript sam_11_EVS_BindExitTriggers;
extern EvtScript sam_11_EVS_Main;
extern EvtScript sam_11_EVS_MakeEntities;
extern EvtScript sam_11_EVS_ManageSnowfall;
extern EvtScript sam_11_EVS_SetupPond;
extern EvtScript sam_11_EVS_SetupRooms;
extern EvtScript sam_11_EVS_SetupStaircase;
extern NpcGroupList sam_11_EpilogueNPCs;
extern NpcGroupList sam_11_MysteryNPCs;
extern ShakeTreeConfig sam_11_ShakeTree_Tree1;
extern ShakeTreeConfig sam_11_ShakeTree_Tree2;
extern ShakeTreeConfig sam_11_ShakeTree_Tree3;

API_CALLABLE(DropItemEntity);
API_CALLABLE(FadeInMusic);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GetValueByRef);
API_CALLABLE(InitAnimatedModels);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtModel);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetRenderMode);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetValueByRef);
API_CALLABLE(TranslateModel);

extern EvtScript TTYD64_sam_11_Script_ShakeTree_80242648;
extern EvtScript TTYD64_sam_11_Script_Main_EnterWalk;
extern EvtScript TTYD64_sam_11_Script_SetMusicTrack;

// clang-format off
EvtScript TTYD64_sam_11_Script_ShakeTree_80242648 = {
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

EvtScript TTYD64_sam_11_Script_Main_EnterWalk = {
    Set(GameByte(425), 40)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(GetEntryID, LVar0)
    IfNe(LVar0, 2)
        Goto(10)
    EndIf
    Call(MakeNpcs, 0, Ref(sam_11_EpilogueNPCs))
    Call(FadeInMusic, 0, 56, 0, 3000, 0, 127)
    Return
    Label(10)
    Switch(GameByte(0))
    CaseLt(63)
        Call(MakeNpcs, 0, Ref(sam_11_BeforeNPCs))
    CaseLt(67)
        Call(MakeNpcs, 0, Ref(sam_11_MysteryNPCs))
    CaseGe(67)
        Call(MakeNpcs, 0, Ref(sam_11_AfterNPCs))
        Call(ModifyColliderFlags, 0, 71, 0x7FFFFE00)
    EndSwitch
    ExecWait(sam_11_EVS_MakeEntities)
    Call(SetRenderMode, 160, 22)
    ExecWait(TTYD64_sam_11_Script_SetMusicTrack)
    Exec(sam_11_EVS_ManageSnowfall)
    ExecWait(sam_11_EVS_SetupRooms)
    ExecWait(sam_11_EVS_SetupPond)
    ExecWait(sam_11_EVS_SetupStaircase)
    Call(ModifyColliderFlags, 3, 8, 8)
    Call(ModifyColliderFlags, 3, 56, 8)
    Call(ModifyColliderFlags, 3, 10, 8)
    Call(ModifyColliderFlags, 3, 9, 8)
    Call(ModifyColliderFlags, 3, 11, 8)
    Call(ModifyColliderFlags, 3, 61, 8)
    Call(ModifyColliderFlags, 3, 20, 8)
    Call(ModifyColliderFlags, 3, 64, 8)
    Call(ModifyColliderFlags, 3, 5, 8)
    Call(ModifyColliderFlags, 3, 1, 8)
    Set(LVar0, Ref(sam_11_ShakeTree_Tree1))
    BindTrigger(TTYD64_sam_11_Script_ShakeTree_80242648, 0x100000, Ref(sam_11_BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(sam_11_ShakeTree_Tree2))
    BindTrigger(TTYD64_sam_11_Script_ShakeTree_80242648, 4096, 57, 1, 0)
    BindTrigger(TTYD64_sam_11_Script_ShakeTree_80242648, 0x100000, Ref(sam_11_BombPos_Tree2), 1, 0)
    Set(LVar0, Ref(sam_11_ShakeTree_Tree3))
    BindTrigger(TTYD64_sam_11_Script_ShakeTree_80242648, 4096, 58, 1, 0)
    BindTrigger(TTYD64_sam_11_Script_ShakeTree_80242648, 0x100000, Ref(sam_11_BombPos_Tree3), 1, 0)
    Call(InitAnimatedModels)
    Call(GetEntryID, LVar0)
    IfNe(LVar0, 2)
        Set(LVar0, Ref(sam_11_EVS_BindExitTriggers))
        Exec(EnterWalk)
        Wait(1)
    EndIf
    Return
    End
};

EvtScript TTYD64_sam_11_Script_SetMusicTrack = {
    Switch(GameByte(0))
    CaseLt(63)
        Call(SetMusic, 0, 56, 0, 8)
    CaseLt(67)
        Call(SetMusic, 0, 57, 0, 8)
    CaseGe(67)
        Call(SetMusic, 0, 56, 0, 8)
    EndSwitch
    Call(MakeItemEntity, 445, -290, 0, -330, 17, GameFlag(5565))
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_sam_11(void) {
    Mod_ReplaceScript("TTYD64", &sam_11_EVS_Main, &TTYD64_sam_11_Script_Main_EnterWalk);
    Mod_RegisterWideEvtBuffer("TTYD64", (const intptr_t*) &sam_11_ShakeTree_Tree1, 5);
    Mod_RegisterWideEvtBuffer("TTYD64", (const intptr_t*) &sam_11_ShakeTree_Tree2, 5);
    Mod_RegisterWideEvtBuffer("TTYD64", (const intptr_t*) &sam_11_ShakeTree_Tree3, 5);
}
