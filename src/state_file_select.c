#include "common.h"
#include "ld_addrs.h"
#include "nu/nusys.h"
#include "hud_element.h"
#include "sprite.h"
#include "model.h"
#include "game_modes.h"
#include "port/Engine.h"
#include "port/shape_loader.h"

#if VERSION_JP
// TODO: split the filemenu segment
extern Addr filemenu_ROM_START;
extern Addr filemenu_ROM_END;
extern Addr filemenu_VRAM;
extern Addr filemenu_TEXT_START;
extern Addr filemenu_TEXT_END;
extern Addr filemenu_DATA_START;
extern Addr filemenu_RODATA_END;
extern Addr filemenu_BSS_START;
extern Addr filemenu_BSS_END;
#endif

extern u16 gFrameBuf0[];
extern u16 gFrameBuf1[];
extern u16 gFrameBuf2[];
u16* fsFrameBuffers[] = { gFrameBuf0, gFrameBuf1, gFrameBuf2 };

NUPiOverlaySegment D_8007798C = {
    .romStart = filemenu_ROM_START,
    .romEnd = filemenu_ROM_END,
    .ramStart = filemenu_VRAM,
    .textStart = filemenu_TEXT_START,
    .textEnd = filemenu_TEXT_END,
    .dataStart = filemenu_DATA_START,
    .dataEnd = filemenu_RODATA_END,
    .bssStart = filemenu_BSS_START,
    .bssEnd = filemenu_BSS_END,
};

u8 IntroMessageIdx = 0;

extern s32 D_80200000;
extern ShapeFile gMapShapeData;

BSS s8 D_800A0930;
BSS s8 D_800A0931;
static s16 D_800A0932;

void state_init_file_select(void) {
    D_800A0931 = 0;
    D_800A0932 = 0;
    disable_player_input();
    set_time_freeze_mode(TIME_FREEZE_FULL);
    general_heap_create();
    hud_element_set_aux_cache(0, 0);
    hud_element_clear_cache();
    mdl_load_all_textures(nullptr, 0, 0);

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

    gOverrideFlags |= GLOBAL_OVERRIDES_WINDOWS_OVER_CURTAINS;
}

void state_step_file_select(void) {
    switch (D_800A0931) {
        case 0:
            D_800A0931 = 1;
            break;
        case 1:
            set_windows_visible(WINDOW_GROUP_FILES);
            D_800A0930 = 1;
            D_800A0931 = 2;
            break;
        case 2:
            if (D_800A0930 >= 0) {
                D_800A0930--;
                if (D_800A0930 == 0) {
                    D_800A0930 = -1;
                    battle_heap_create();
                    nuPiReadRomOverlay(&D_8007798C);
                    filemenu_init(0);
                }
            }

            if (D_800A0930 < 0) {
                filemenu_update();
            }
            break;
    }
}

void state_drawUI_file_select(void) {
}

void state_init_exit_file_select(void) {
    D_800A0931 = 0;
    D_800A0932 = 0;
    D_800A0930 = 0;

    if (filemenu_get_exit_mode() == 0) {
        set_map_transition_effect(TRANSITION_SLOW_FADE_TO_WHITE);
    } else {
        set_map_transition_effect(TRANSITION_ENTER_WORLD);
        gOverrideFlags &= ~GLOBAL_OVERRIDES_WINDOWS_OVER_CURTAINS;
        bgm_set_song(0, -1, 0, 1000, 8);
    }
    gOverrideFlags &= ~GLOBAL_OVERRIDES_40;
}

void state_step_exit_file_select(void) {
    s32 exitMode = filemenu_get_exit_mode();
    s32 flagSum;
    s32 i;

    switch (D_800A0931) {
        case 0:
            flagSum = 0;

            for (i = 44; i < ARRAY_COUNT(gWindows); i++) {
                Window* window = &gWindows[i];

                if (window->parent == WIN_FILES_MAIN || window->parent == WIN_NONE) {
                    flagSum += window->flags & WINDOW_FLAG_INITIAL_ANIMATION;
                }
            }

            if (flagSum == 0) {
                D_800A0931 = 1;
            }
            break;
        case 1:
            if (exitMode == 0 || update_exit_map_screen_overlay(&D_800A0932) != 0) {
                D_800A0931 = 2;
            }
            break;
        case 2:
            filemenu_cleanup();
            set_windows_visible(WINDOW_GROUP_ALL);
            D_800A0931 = 3;
        case 3:
            set_time_freeze_mode(TIME_FREEZE_NONE);
            if (exitMode == 0) {
                set_game_mode(GAME_MODE_TITLE_SCREEN);
                gOverrideFlags &= ~GLOBAL_OVERRIDES_WINDOWS_OVER_CURTAINS;
            } else {
                D_800A0930 = 10;
                D_800A0931 = 4;
            }
            break;
        case 4:
            if (D_800A0930 > 0) {
                D_800A0930--;
            } else {
                set_curtain_scale_goal(2.0f);
                D_800A0930 = 10;
                D_800A0931 = 5;
            }
            break;
        case 5:
            if (D_800A0930 > 0) {
                D_800A0930--;
            } else {
                // This is the last frame drawn before the map load freezes it on screen, and
                // render_curtains() draws after the fade, so snap the theater fully open,
                // the zoom-out only reaches ~1.65 here, leaving its floor over the bottom rows.
                set_curtain_scale(2.0f);
                D_800A0931 = 6;
            }
            break;
        case 6:
            set_game_mode(GAME_MODE_ENTER_WORLD);
            break;
    }
}

void state_drawUI_exit_file_select(void) {
}
