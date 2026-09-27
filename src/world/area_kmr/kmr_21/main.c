#include "kmr_21.h"
#include "port/Engine.h"
#include "port/patches/Patches.h"

static IMG_PTR TitleImage;

s32 TitlePrimAlpha = 0;
#if VERSION_JP
s32 TitlePosY = 125;
#else
s32 TitlePosY = 106;
#endif

Gfx N(Gfx_TexSetup_TitleImage)[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetCombineMode(PM_CC_2E, PM_CC_2E),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPNoOp(),
    gsSPEndDisplayList(),
};

void worker_render_title_image(void) {
    s32 i;

    gSPDisplayList(gMainGfxPos++, N(Gfx_TexSetup_TitleImage));
    gDPSetPrimColor(gMainGfxPos++, 0, 0, 0, 0, 0, TitlePrimAlpha);
    gDPPipeSync(gMainGfxPos++);

#if VERSION_JP
    for (i = 0; i < 44; i++) {
        gDPLoadTextureTile(gMainGfxPos++, &TitleImage[2176 * i], G_IM_FMT_RGBA, G_IM_SIZ_32b, 272, 112,
                           0, 0, 271, 1, 0,
                           G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gMainGfxPos++,
            /* ulx */ 25 * 4,
            /* uly */ (i * 2 + TitlePosY) * 4,
            /* lrx */ 297 * 4,
            /* lry */ ((i * 2 + 2) + TitlePosY) * 4,
            G_TX_RENDERTILE, 0, 0, 1024, 1024);
    }
#else
    for (i = 0; i < 56; i++) {
        gDPLoadTextureTile(gMainGfxPos++, TitleImage, G_IM_FMT_RGBA, G_IM_SIZ_32b, 200, 112,
                           0, i * 2, 199, i * 2 + 1, 0,
                           G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gMainGfxPos++,
            /* ulx */ 60 * 4,
            /* uly */ (i * 2 + TitlePosY) * 4,
            /* lrx */ 260 * 4,
            /* lry */ ((i * 2 + 2) + TitlePosY) * 4,
            G_TX_RENDERTILE, 0, (i * 2) << 5, 1024, 1024);
    }
#endif
    gDPPipeSync(gMainGfxPos++);
}

API_CALLABLE(N(LoadTitleImage)) {
    TitleImage = port_named_image("__OTR__title_screen/title_logo", "_img", LOAD_ASSET("__OTR__title_screen/title_logo"));
    create_worker_frontUI(nullptr, worker_render_title_image);
    return ApiStatus_DONE2;
}

#if !VERSION_PAL
API_CALLABLE(N(AwaitConfirmInput)) {
    u32 pressedButtons = gGameStatusPtr->pressedButtons[0];
    if (pressedButtons & (BUTTON_A | BUTTON_START)) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}
#endif

API_CALLABLE(N(SetTitlePrimAlpha)) {
    TitlePrimAlpha = script->varTable[0];
    return ApiStatus_DONE2;
}

API_CALLABLE(N(SetTitlePosY)) {
    TitlePosY = script->varTable[0];
    return ApiStatus_DONE2;
}

EvtScript N(EVS_Scene_ShowTitle) = {
    Call(N(LoadTitleImage))
    Wait(15 * DT)
    Thread
        Call(MakeLerp, 0, 255, 100 * DT, EASING_CUBIC_OUT)
        Loop(0)
            Call(UpdateLerp)
            Call(N(SetTitlePrimAlpha))
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
#if VERSION_JP
    Call(MakeLerp, 125, 75, 100 * DT, EASING_CUBIC_OUT)
#else
    Call(MakeLerp, 106, 56, 100 * DT, EASING_CUBIC_OUT)
#endif
    Loop(0)
        Call(UpdateLerp)
        Call(N(SetTitlePosY))
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Wait(30 * DT)
    Call(MakeLerp, 255, 0, 50 * DT, EASING_QUADRATIC_IN)
    Loop(0)
        Call(UpdateLerp)
        Call(N(SetTitlePrimAlpha))
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Wait(15 * DT)
    Call(GotoMapSpecial, Ref("kmr_22"), kmr_22_ENTRY_0, TRANSITION_BEGIN_OR_END_CHAPTER)
    Wait(100 * DT)
    Return
    End
};

EvtScript N(EVS_Main) = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerPos, NPC_DISPOSE_LOCATION)
    Wait(1)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, PARTNER_NONE)
        Call(DisablePartnerAI, 0)
        Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_GRAVITY, false)
        Call(SetNpcPos, NPC_PARTNER, NPC_DISPOSE_LOCATION)
    EndIf
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(208, 208, 208)
    Call(SetCamType, CAM_DEFAULT, CAM_CONTROL_FIXED_POS_AND_ORIENTATION, false)
    Call(SetCamPitch, CAM_DEFAULT, 0, 0)
    Call(SetCamDistance, CAM_DEFAULT, 440)
    Call(SetCamPosA, CAM_DEFAULT, 0, 100)
    Call(SetCamPosB, CAM_DEFAULT, 0, 0)
    Call(SetCamPosC, CAM_DEFAULT, 0, 65)
    Call(SetPanTarget, CAM_DEFAULT, 0, 0, 0)
    Call(SetCamSpeed, CAM_DEFAULT, Float(90.0))
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Wait(1)
    Exec(N(EVS_Scene_ShowTitle))
    Return
    End
};
