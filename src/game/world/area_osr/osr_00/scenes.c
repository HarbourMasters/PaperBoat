#include "osr_00.h"
#include "Engine.h"
#include "assets/charset.h"

#include "sprite/npc/Luigi.h"

#include "world/common/atomic/ApplyTint.inc.c"

API_CALLABLE(N(func_80240678_AACEA8)) {
    Bytecode* args = script->ptrReadPos;
    s32 primR = *args++;
    s32 primG = *args++;
    s32 primB = *args++;
    s32 envR = *args++;
    s32 envG = *args++;
    s32 envB = *args++;
    mdl_set_remap_tint_params(primR, primG, primB, envR, envG, envB);
    return ApiStatus_DONE2;
}

BSS IMG_BIN N(PeachLetterImg)[CHARSET_PEACH_LETTER_WIDTH * CHARSET_PEACH_LETTER_HEIGHT];
BSS PAL_BIN N(PeachLetterPal)[0x100];
MAP_STATIC_PAD(2, letter);
BSS MessageImageData N(MsgImage);

API_CALLABLE(N(func_802406E0_AACF10)) {
    memcpy(&N(PeachLetterImg), LOAD_ASSET(CHARSET_PEACH_LETTER), sizeof(N(PeachLetterImg)));
    memcpy(&N(PeachLetterPal), LOAD_ASSET(CHARSET_PEACH_LETTER_PAL), sizeof(N(PeachLetterPal)));

    N(MsgImage).raster   = N(PeachLetterImg);
    N(MsgImage).palette  = N(PeachLetterPal);
    N(MsgImage).width    = CHARSET_PEACH_LETTER_WIDTH;
    N(MsgImage).height   = CHARSET_PEACH_LETTER_HEIGHT;
    N(MsgImage).format   = G_IM_FMT_CI;
    N(MsgImage).bitDepth = G_IM_SIZ_8b;
    set_message_images(&N(MsgImage));
    return ApiStatus_DONE2;
}

EvtScript N(EVS_Scene_ShowInvitation) = {
    Call(DisablePlayerInput, true)
    Call(UseSettingsFrom, CAM_DEFAULT, 0, 0, 0)
    Call(SetPanTarget, CAM_DEFAULT, 0, 0, 0)
    Call(SetCamSpeed, CAM_DEFAULT, Float(90.0))
    Call(SetCamDistance, CAM_DEFAULT, 775)
    Call(SetCamPitch, CAM_DEFAULT, 20, -19)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(N(SetModelTintMode), APPLY_TINT_BG, nullptr, ENV_TINT_REMAP)
    Call(N(SetModelTintMode), APPLY_TINT_GROUPS, -1, ENV_TINT_REMAP)
    Call(N(func_80240678_AACEA8), 200, 200, 200, 40, 40, 40)
    Call(N(func_802406E0_AACF10))
    Wait(15 * DT)
    Call(ShowMessageAtScreenPos, MSG_Intro_0022, 160, 40)
    Wait(12 * DT)
    Call(ShowMessageAtScreenPos, MSG_Intro_0023, 160, 40)
    Wait(3)
    Call(GotoMapSpecial, Ref("kmr_20"), kmr_20_ENTRY_1, TRANSITION_SLOW_FADE_TO_WHITE)
    Wait(40 * DT)
    Return
    End
};

EvtScript N(EVS_Scene_ApproachParty) = {
    Call(DisablePlayerInput, true)
    Call(UseSettingsFrom, CAM_DEFAULT, 0, 0, 0)
    Call(SetPanTarget, CAM_DEFAULT, 0, 0, 0)
    Call(SetCamDistance, CAM_DEFAULT, Float(675.0))
    Call(SetCamPitch, CAM_DEFAULT, Float(3.5), Float(-6.0))
    Call(SetCamPosA, CAM_DEFAULT, Float(60.0), 0)
    Call(SetCamSpeed, CAM_DEFAULT, Float(90.0))
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Thread
        Call(PlayerMoveTo, 0, -250, 150 * DT)
    EndThread
    Thread
        Call(SetNpcAnimation, NPC_Luigi, ANIM_Luigi_RunBack)
        Call(SetNpcPos, NPC_Luigi, 0, 0, 350)
        Call(NpcMoveTo, NPC_Luigi, 0, -200, 150 * DT)
        Call(SetNpcAnimation, NPC_Luigi, ANIM_Luigi_IdleBack)
    EndThread
    Wait(100 * DT)
    Call(GotoMap, Ref("kkj_00"), kkj_00_ENTRY_5)
    Wait(100 * DT)
    Call(DisablePlayerInput, false)
    Return
    End
};
