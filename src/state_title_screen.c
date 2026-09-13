#include "common.h"
#include "nu/nusys.h"
#include "hud_element.h"
#include "sprite.h"
#include "game_modes.h"
#include "fio.h"
#include "dx/config.h"
#include "dx/versioning.h"
#include "port/Engine.h"
#include "port/patches/Patches.h"

#if VERSION_JP
#define TITLE_WIDTH 272
#define TITLE_TILE_HEIGHT 2
#define TITLE_HEIGHT 88
#define TITLE_POS_LEFT 25
#define TITLE_POS_TOP 34
#define FILENAME_ERROR "\x54\x77\xA2\xF7\xF7\xf7\xf7\xf7"
#else
// Properties of the title screen Paper Mario logo
#define TITLE_WIDTH  200 // Width of the texture
#define TITLE_HEIGHT 112 // Height of the texture
#define TITLE_TILE_HEIGHT 2 // Height of an individually loaded tile in the texture
#define TITLE_POS_LEFT ((SCREEN_WIDTH - TITLE_WIDTH) / 2) // Left edge of the texture on screen
#define TITLE_POS_TOP 15 // Top edge of the texture on screen (with no offset)
#define FILENAME_ERROR "ERROR\xf7\xf7\xf7"
#endif

#define TITLE_NUM_TILES (TITLE_HEIGHT / TITLE_TILE_HEIGHT) // Number of tiles in the texture
#define TITLE_TILE_PIXELS (TITLE_WIDTH * TITLE_TILE_HEIGHT) // Number of pixels in a single tile of the texture

enum TitleScreenStates {
    TITLE_STATE_INIT            = 0,
    TITLE_STATE_APPEAR          = 1,
    TITLE_STATE_HOLD            = 2,   // show the title screen with PRESS START blinking
    TITLE_STATE_UNUSED          = 3,
    TITLE_STATE_BEGIN_DISMISS   = 4,
    TITLE_STATE_DISMISS         = 5,
    TITLE_STATE_EXIT            = 6,
};

enum {
    NEXT_STATE_DEMO             = 10,
    NEXT_STATE_INTRO            = 9,
    NEXT_STATE_FILE_SELECT      = 5,
    NEXT_STATE_NONE             = 0, // used only for the initial value
};

s16 TitleScreenNextState = NEXT_STATE_NONE;

SaveFileSummary gSaveSlotSummary[4] = {
    { .filename = { FILENAME_ERROR } },
    { .filename = { FILENAME_ERROR } },
    { .filename = { FILENAME_ERROR } },
    { .filename = { FILENAME_ERROR } },
};

SaveSlotMetadata gSaveSlotMetadata[4] = {
    { .hasData = true },
    { .hasData = true },
    { .hasData = true },
    { .hasData = true },
};

s32 PressStart_Alpha = 0; // the opacity of "PRESS START" text
b32 PressStart_IsVisible = false; // toggles the visibility of "PRESS START"
s32 PressStart_BlinkCounter = 0; // counts to 16, then toggles PressStart_IsVisible

// controls whether the intro story or the demo will player after TITLE_STATE_HOLD is done
// since this state is reached for the first time after the intro has already played once or was skipped,
// this is initially false and the demo is will play first.
s32 PlayIntroNext = false;

Lights1 D_80077A38 = gdSPDefLights1(255, 255, 255, 0, 0, 0, 0, 0, 0);

Gfx TitleSetupGfx[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
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
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT),
    gsSPEndDisplayList(),
};

typedef struct TitleDataStruct {
    /* 0x0 */ s32 logo;
    /* 0x4 */ s32 copyright;
    /* 0x8 */ s32 pressStart;
    /* 0xC */ s32 copyrightPalette;
} TitleDataStruct; // size = 0x10

#if VERSION_JP
#define COPYRIGHT_WIDTH 128
#else
#define COPYRIGHT_WIDTH 144
#endif

BSS s16 TitleScreen_AppearDelay;
BSS TitleDataStruct* TitleScreen_ImgList;
BSS s32* TitleScreen_ImgList_Logo;
BSS u8 (*TitleScreen_ImgList_Copyright)[COPYRIGHT_WIDTH];
BSS s32* TitleScreen_ImgList_PressStart;
BSS s32* TitleScreen_ImgList_CopyrightPalette;
BSS s16 TitleScreen_TimeLeft;

void appendGfx_title_screen(void);
void title_screen_draw_images(f32, f32);
void title_screen_draw_logo(f32);
void title_screen_draw_press_start(void);
void title_screen_draw_copyright(f32);

void state_init_title_screen(void) {
    s32 titleDataSize;
    void* titleDataDst;
    void* titleData;

    gOverrideFlags = 0;
    gTimeFreezeMode = TIME_FREEZE_NONE;
    general_heap_create();
    clear_printers();
    sfx_set_reverb_mode(0);
    gGameStatusPtr->startupState = TITLE_STATE_INIT;
    gGameStatusPtr->logoTime = 0;
    gGameStatusPtr->context = CONTEXT_WORLD;
    gGameStatusPtr->introPart = INTRO_PART_NONE;
    startup_fade_screen_update();
    // Load title screen images individually from OTR archive
    TitleScreen_ImgList_Logo = (s32*) port_named_image("__OTR__title_screen/title_logo", "_img", GameEngine_GetDataExact("__OTR__title_screen/title_logo"));
    TitleScreen_ImgList_Copyright = (u8 (*)[COPYRIGHT_WIDTH]) port_named_image("__OTR__title_screen/title_copyright", "_img", GameEngine_GetDataExact("__OTR__title_screen/title_copyright"));
    TitleScreen_ImgList_PressStart = (s32*) port_named_image("__OTR__title_screen/title_press_start", "_img", GameEngine_GetDataExact("__OTR__title_screen/title_press_start"));
#if VERSION_JP
    TitleScreen_ImgList_CopyrightPalette = (s32*) GameEngine_GetDataExact("__OTR__title_screen/title_copyright_palette");
#endif

    create_cameras();
    gCameras[CAM_DEFAULT].updateMode = CAM_UPDATE_NO_INTERP;
    gCameras[CAM_DEFAULT].needsInit = true;
    gCameras[CAM_DEFAULT].nearClip = CAM_NEAR_CLIP;
    gCameras[CAM_DEFAULT].farClip = CAM_FAR_CLIP;
    gCameras[CAM_DEFAULT].vfov = 25.0f;
    set_cam_viewport(CAM_DEFAULT, 12, 28, 296, 184);

    gCameras[CAM_DEFAULT].params.basic.skipRecalc = false;
    gCameras[CAM_DEFAULT].params.basic.pitch = 0;
    gCameras[CAM_DEFAULT].params.basic.dist = 40;
    gCameras[CAM_DEFAULT].params.basic.fovScale = 100;

    gCameras[CAM_DEFAULT].lookAt_eye.x = 500.0f;
    gCameras[CAM_DEFAULT].lookAt_eye.y = 1000.0f;
    gCameras[CAM_DEFAULT].lookAt_eye.z = 1500.0f;

    gCameras[CAM_DEFAULT].lookAt_obj_target.x = 25.0f;
    gCameras[CAM_DEFAULT].lookAt_obj_target.y = 25.0f;
    gCameras[CAM_DEFAULT].lookAt_obj_target.z = 150.0f;

    gCameras[CAM_DEFAULT].bgColor[0] = 0;
    gCameras[CAM_DEFAULT].bgColor[1] = 0;
    gCameras[CAM_DEFAULT].bgColor[2] = 0;

    gCurrentCameraID = CAM_DEFAULT;

    gCameras[CAM_DEFAULT].flags |= CAMERA_FLAG_DISABLED;
    gCameras[CAM_BATTLE].flags |= CAMERA_FLAG_DISABLED;
    gCameras[CAM_TATTLE].flags |= CAMERA_FLAG_DISABLED;
    gCameras[CAM_HUD].flags |= CAMERA_FLAG_DISABLED;

    clear_script_list();
    clear_worker_list();
    clear_render_tasks();
    spr_init_sprites(PLAYER_SPRITES_MARIO_WORLD);
    clear_animator_list();
    clear_entity_models();
    clear_npcs();
    hud_element_clear_cache();
    reset_background_settings();
    clear_entity_data(true);
    clear_effect_data();
    gOverrideFlags |= GLOBAL_OVERRIDES_DISABLE_RENDER_WORLD;
    clear_player_data();
    gOverrideFlags &= ~GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME;
    set_game_mode_render_frontUI(appendGfx_title_screen);
    port_load_map_bg("title_bg");
    set_background(&gBackgroundImage);
    // Widescreen: don't tile the title backdrop across the revealed sides, draw
    // it once and fill the side bands solid black instead.
    enable_background_solid_fill();
    bgm_set_song(0, SONG_MAIN_THEME, 0, 500, 8);
    TitleScreen_TimeLeft = 480;
}

void state_step_title_screen(void) {
    u32 pressedButtons = gGameStatusPtr->pressedButtons[0];

    set_curtain_scale(1.0f);
    set_curtain_fade(0.0f);

    if (TitleScreen_TimeLeft > 0) {
        TitleScreen_TimeLeft--;
    }

    switch (gGameStatusPtr->startupState) {
        case TITLE_STATE_INIT:
            TitleScreen_AppearDelay = 3;
            gOverrideFlags |= GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME;
            gGameStatusPtr->titleScreenDismissTime = 20;
            gGameStatusPtr->titleScreenTimer = gGameStatusPtr->titleScreenDismissTime;
            gGameStatusPtr->startupState++;
            break;
        case TITLE_STATE_APPEAR:
            if (TitleScreen_AppearDelay != 0) {
                TitleScreen_AppearDelay--;
                break;
            }
            if (gGameStatusPtr->titleScreenTimer != 0) {
                gGameStatusPtr->titleScreenTimer--;
            }
            gOverrideFlags &= ~GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME;
            if (startup_fade_screen_in(6) != 0) {
                if (gGameStatusPtr->titleScreenTimer == 0) {
                    gGameStatusPtr->startupState = TITLE_STATE_HOLD;
                }
            }
            startup_fade_screen_update();
            break;
        case TITLE_STATE_HOLD:

            #if DX_SKIP_DEMO && DX_SKIP_STORY
            // play neither demo nor story
            TitleScreen_TimeLeft = 200;
            #elif DX_SKIP_DEMO
            // only the story may play
            if (TitleScreen_TimeLeft == 120) {
                bgm_set_song(0, -1, 0, 3900, 8);
            }
            if (TitleScreen_TimeLeft == 0) {
                gGameStatusPtr->startupState = TITLE_STATE_BEGIN_DISMISS;
                TitleScreenNextState = NEXT_STATE_INTRO;
                return;
            }
            #elif DX_SKIP_STORY
            // only the demo may play
            if (TitleScreen_TimeLeft == 0) {
                gGameStatusPtr->startupState = TITLE_STATE_BEGIN_DISMISS;
                TitleScreenNextState = NEXT_STATE_DEMO;
                return;
            }
            #else
            // allow either demo or story to play
            if (PlayIntroNext && TitleScreen_TimeLeft == 120) {
                bgm_set_song(0, -1, 0, 3900, 8);
            }
            if (TitleScreen_TimeLeft == 0) {
                gGameStatusPtr->startupState = TITLE_STATE_BEGIN_DISMISS;
                if (!PlayIntroNext) {
                    TitleScreenNextState = NEXT_STATE_DEMO;
                } else {
                    TitleScreenNextState = NEXT_STATE_INTRO;
                }
                PlayIntroNext ^= 1;
                return;
            }
            #endif
            if (pressedButtons & (BUTTON_A | BUTTON_START)) {
                gGameStatusPtr->startupState = TITLE_STATE_BEGIN_DISMISS;
                TitleScreenNextState = NEXT_STATE_FILE_SELECT;
                sfx_play_sound(SOUND_FILE_MENU_IN);
                bgm_set_song(0, SONG_FILE_SELECT, 0, 500, 8);
                return;
            }
            break;
        case TITLE_STATE_BEGIN_DISMISS:
            gGameStatusPtr->startupState = TITLE_STATE_DISMISS;
            startup_set_fade_screen_color(208);
            if (TitleScreenNextState == NEXT_STATE_INTRO || TitleScreenNextState == NEXT_STATE_DEMO) {
                gGameStatusPtr->titleScreenDismissTime = 20;
            } else {
                gGameStatusPtr->titleScreenDismissTime = 10;
            }
            gGameStatusPtr->titleScreenTimer = gGameStatusPtr->titleScreenDismissTime;
            break;
        case TITLE_STATE_DISMISS:
            if (TitleScreenNextState == NEXT_STATE_INTRO || TitleScreenNextState == NEXT_STATE_DEMO) {
                if (gGameStatusPtr->titleScreenTimer != 0) {
                    gGameStatusPtr->titleScreenTimer--;
                }
                if (startup_fade_screen_out(10) != 0) {
                    if (gGameStatusPtr->titleScreenTimer == 0) {
                        gGameStatusPtr->titleScreenTimer = 3;
                        gOverrideFlags |= GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME;
                        gGameStatusPtr->startupState = TITLE_STATE_EXIT;
                    }
                }
                startup_fade_screen_update();
            } else if (TitleScreenNextState == NEXT_STATE_FILE_SELECT) {
                if (gGameStatusPtr->titleScreenTimer == 0) {
                    gGameStatusPtr->titleScreenTimer = 3;
                    gOverrideFlags |= GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME;
                    gGameStatusPtr->startupState = TITLE_STATE_EXIT;
                } else {
                    gGameStatusPtr->titleScreenTimer--;
                }
            } else {
                gGameStatusPtr->titleScreenTimer = 3;
                gOverrideFlags |= GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME;
                gGameStatusPtr->startupState = TITLE_STATE_EXIT;
            }
            break;
        case TITLE_STATE_EXIT:
            if (gGameStatusPtr->titleScreenTimer != 0) {
                gGameStatusPtr->titleScreenTimer--;
                break;
            }
            general_heap_create();
            clear_render_tasks();
            create_cameras();
            clear_entity_models();
            clear_animator_list();
            clear_npcs();
            hud_element_clear_cache();
            spr_init_sprites(PLAYER_SPRITES_MARIO_WORLD);
            clear_entity_data(true);
            clear_windows();
            gOverrideFlags &= ~GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME;
            gOverrideFlags &= ~GLOBAL_OVERRIDES_DISABLE_RENDER_WORLD;
            gGameStatusPtr->entryID = 0;

            switch (TitleScreenNextState) {
                case NEXT_STATE_INTRO:
                    gGameStatusPtr->introPart = INTRO_PART_0;
                    set_game_mode(GAME_MODE_INTRO);
                    break;
                case NEXT_STATE_DEMO:
                    set_game_mode(GAME_MODE_DEMO);
                    break;
                case NEXT_STATE_FILE_SELECT:
                    gGameStatusPtr->areaID = AREA_KMR;
                    gGameStatusPtr->mapID = 0xB; //TODO hardcoded map IDs
                    gGameStatusPtr->entryID = 0;
                    set_game_mode(GAME_MODE_FILE_SELECT);
                    break;
            }
            return;
    }

    if (!(gOverrideFlags & GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME)) {
        update_npcs();
        update_cameras();
    }
}

void state_drawUI_title_screen(void) {
    switch (gGameStatusPtr->startupState) {
        case TITLE_STATE_INIT:
            PressStart_Alpha = 0;
            PressStart_IsVisible = false;
            PressStart_BlinkCounter = 0;
            break;
        case TITLE_STATE_HOLD:
            if (gGameStatusPtr->contBitPattern & 1) {
                title_screen_draw_press_start();
            }
        case TITLE_STATE_UNUSED:
            break;
        case TITLE_STATE_APPEAR:
        case TITLE_STATE_BEGIN_DISMISS:
        case TITLE_STATE_DISMISS:
            break;
    }
}

void appendGfx_title_screen(void) {
    f32 alpha;

    switch (gGameStatusPtr->startupState) {
        case TITLE_STATE_INIT:
        case TITLE_STATE_UNUSED:
            break;
        case TITLE_STATE_APPEAR:
            alpha = gGameStatusPtr->titleScreenTimer;
            alpha /= gGameStatusPtr->titleScreenDismissTime;
            alpha = SQ(alpha);
            title_screen_draw_images(alpha, alpha);
            break;
        case TITLE_STATE_HOLD:
            title_screen_draw_images(0.0f, 0.0f);
            break;
        case TITLE_STATE_BEGIN_DISMISS:
            title_screen_draw_images(0.0f, 0.0f);
            break;
        case TITLE_STATE_DISMISS:
            alpha = gGameStatusPtr->titleScreenDismissTime - gGameStatusPtr->titleScreenTimer + 1;
            alpha /= gGameStatusPtr->titleScreenDismissTime;
            alpha = SQ(alpha);
            title_screen_draw_images(alpha, alpha);
            break;
    }

    gDPPipeSync(gMainGfxPos++);
    gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(nuGfxCfb_ptr));
    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
    gDPPipeSync(gMainGfxPos++);
    gSPClearGeometryMode(gMainGfxPos++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING |
                            G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gMainGfxPos++, G_ZBUFFER | G_SHADE | G_LIGHTING | G_SHADING_SMOOTH);
    gSPSetLights1(gMainGfxPos++, D_80077A38);

    gSPTexture(gMainGfxPos++, -1, -1, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTextureLOD(gMainGfxPos++, G_TL_TILE);
    gDPSetTexturePersp(gMainGfxPos++, G_TP_PERSP);
    gDPSetTextureFilter(gMainGfxPos++, G_TF_BILERP);
    gDPSetColorDither(gMainGfxPos++, G_CD_DISABLE);
    gDPSetTextureDetail(gMainGfxPos++, G_TD_CLAMP);
    gDPSetTextureConvert(gMainGfxPos++, G_TC_FILT);
    gDPSetCombineKey(gMainGfxPos++, G_CK_NONE);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
    render_frame(false);
    render_frame(true);
}

void title_screen_draw_images(f32 logoMoveAlpha, f32 copyrightMoveAlpha) {
    title_screen_draw_logo(logoMoveAlpha);
    title_screen_draw_copyright(copyrightMoveAlpha);
}

void title_screen_draw_logo(f32 moveAlpha) {
    s32 yOffset;
    s32 i;

    gSPDisplayList(gMainGfxPos++, TitleSetupGfx);
    gDPPipeSync(gMainGfxPos++);
    yOffset = -100 * moveAlpha;

    for (i = 0; i < TITLE_NUM_TILES; i++) {
        // Load a tile from the logo texture
        gDPLoadTextureTile(gMainGfxPos++, TitleScreen_ImgList_Logo, G_IM_FMT_RGBA, G_IM_SIZ_32b,
                           TITLE_WIDTH, TITLE_HEIGHT, // width, height
                           0, i * TITLE_TILE_HEIGHT, (TITLE_WIDTH - 1), (i + 1) * TITLE_TILE_HEIGHT - 1, // uls, ult, lrs, lrt
                           0, // pal
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, // cms, cmt
                           G_TX_NOMASK, G_TX_NOMASK, // masks, maskt
                           G_TX_NOLOD, G_TX_NOLOD); // shifts, shiftt
        // Draw a scissored texture rectangle with the loaded tile
        gSPScisTextureRectangle(gMainGfxPos++,
            (TITLE_POS_LEFT)                                                      << 2, // ulx
            (TITLE_POS_TOP + TITLE_TILE_HEIGHT * i + yOffset)                     << 2, // uly
            (TITLE_POS_LEFT + TITLE_WIDTH)                                        << 2, // lrx
            (TITLE_POS_TOP + TITLE_TILE_HEIGHT + TITLE_TILE_HEIGHT * i + yOffset) << 2, // lry
            G_TX_RENDERTILE, 0, (i * TITLE_TILE_HEIGHT) << 5, 1 << 10, 1 << 10); // sample from the tile's rows
    }

    gDPPipeSync(gMainGfxPos++);
}

#if VERSION_IQUE
#define VAR_1 20
#define VAR_2 628
#else
#define VAR_1 32
#define VAR_2 676
#endif

void title_screen_draw_press_start(void) {
    switch (PressStart_IsVisible) {
        case false:
            PressStart_Alpha -= 128;
            if (PressStart_Alpha < 0) {
                PressStart_Alpha = 0;
            }

            PressStart_BlinkCounter++;
            if (PressStart_BlinkCounter >= 16) {
                PressStart_BlinkCounter = 0;
                PressStart_IsVisible = true;
            }
            break;
        case true:
            PressStart_Alpha += 128;
            if (PressStart_Alpha > 255) {
                PressStart_Alpha = 255;
            }

            PressStart_BlinkCounter++;
            if (PressStart_BlinkCounter >= 16) {
                PressStart_BlinkCounter = 0;
                PressStart_IsVisible = false;
            }
    }

    gSPDisplayList(gMainGfxPos++, TitleSetupGfx);
    gDPSetCombineMode(gMainGfxPos++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gMainGfxPos++, 0, 0, 248, 240, 152, PressStart_Alpha);
    gDPPipeSync(gMainGfxPos++);
    gDPLoadTextureBlock(gMainGfxPos++, TitleScreen_ImgList_PressStart, G_IM_FMT_IA, G_IM_SIZ_8b, 128, VAR_1, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(gMainGfxPos++, 384, 548, 896, VAR_2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
    gDPPipeSync(gMainGfxPos++);
}

#if VERSION_IQUE
#define RECT_SIZE 0x28
#define YL_BASE 724
#define YH_BASE 764
#define COPYRIGHT_TEX_CHUNKS 4
#define COPYRIGHT_IMG(k, i) &TitleScreen_ImgList_Copyright[k]
#define LTT_LRT 9
#else
#define RECT_SIZE 0x40
#define YL_BASE 764
#define YH_BASE 828
#define COPYRIGHT_TEX_CHUNKS 2
#define COPYRIGHT_IMG(k, i) &TitleScreen_ImgList_Copyright[16 * i]
#define LTT_LRT 15
#endif

void title_screen_draw_copyright(f32 moveAlpha) {
    s32 alpha;
    s32 i;

    gSPDisplayList(gMainGfxPos++, &TitleSetupGfx);
#if VERSION_JP
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
#endif
    gDPPipeSync(gMainGfxPos++);

    alpha = 255.0f - (moveAlpha * 255.0f);
    if (alpha < 255) {
        if (alpha < 0) {
            alpha = 0;
        }
        gDPSetCombineMode(gMainGfxPos++, PM_CC_02, PM_CC_02);
        gDPSetPrimColor(gMainGfxPos++, 0, 0, 0, 0, 0, alpha);
    }

#if VERSION_JP
    gDPLoadTLUT_pal16(gMainGfxPos++, 0, TitleScreen_ImgList_CopyrightPalette);
    gDPLoadTextureTile_4b(gMainGfxPos++, TitleScreen_ImgList_Copyright, G_IM_FMT_CI,
                          COPYRIGHT_WIDTH, 0, 0, 0, 127, 31, 0,
                          G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                          G_TX_NOLOD);
    gSPTextureRectangle(gMainGfxPos++, 388, YL_BASE, 900, 892, G_TX_RENDERTILE,
                        0, 0, 0x0400, 0x0400);
#else
    for (i = 0; i < COPYRIGHT_TEX_CHUNKS; i++) {
        alpha = 0; // TODO figure out why this is needed

        // Chunk rows through the tile origin
        gDPLoadTextureTile(gMainGfxPos++, TitleScreen_ImgList_Copyright, G_IM_FMT_IA, G_IM_SIZ_8b,
                           COPYRIGHT_WIDTH, 32, 0, 16 * i, 143, 16 * i + LTT_LRT, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
        gSPTextureRectangle(gMainGfxPos++, 356, YL_BASE + (RECT_SIZE * i), 932, YH_BASE + (RECT_SIZE * i),
                            G_TX_RENDERTILE, 0, (16 * i) << 5, 0x0400, 0x0400);
    }
#endif
    gDPPipeSync(gMainGfxPos++);
}
