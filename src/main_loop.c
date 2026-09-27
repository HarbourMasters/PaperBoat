#include "common.h"
#include "nu/nusys.h"
#include "ld_addrs.h"
#include "hud_element.h"
#include "sprite.h"
#include "overlay.h"
#include "game_modes.h"
#include "audio/public.h"
#include "dx/profiling.h"
#include "port/interpolation/FrameInterpolation.h"

s32 gOverrideFlags;
s32 gTimeFreezeMode;
u16** nuGfxCfb;
BSS s16 SoftResetDelay;

DisplayContext DisplayContexts[2];

s8 gGameStepDelayAmount = 1;
s8 gGameStepDelayCount = 5;

GameStatus gGameStatus = {
    .curButtons = { 0 },
    .pressedButtons = { 0 },
    .heldButtons = { 0 },
    .prevButtons = { 0 },
    .stickX = { 0 },
    .stickY = { 0 },
    .holdDelayTime = { 0 },
    .holdRepeatInterval = { 0 },
};

GameStatus* gGameStatusPtr = &gGameStatus;
s16 SoftResetOverlayAlpha = 0;
s16 SoftResetState = 0;
s32 D_800741A4 = 0;

Mtx MasterIdentityMtx = RDP_MATRIX(
    1.000000, 0.000000, 0.000000, 0.000000,
    0.000000, 1.000000, 0.000000, 0.000000,
    0.000000, 0.000000, 1.000000, 0.000000,
    0.000000, 0.000000, 0.000000, 1.000000
);

s32 D_800741E8[2] = {0, 0}; // padding?
u16 gMatrixListPos = 0;
u16 D_800741F2 = 0;
s32 gCurrentDisplayContextIndex = 0;
s32 gPauseBackgroundFade = 0;
s32 D_800741FC = 0;

void gfx_init_state(void);
void gfx_draw_background(void);

void step_game_loop(void) {
    profiler_frame_setup();

    PlayerData* playerData = &gPlayerData;
    const int MAX_GAME_TIME = (1000*60*60*60) - 1; // 1000 hours minus one frame at 60 fps

    CALL_EVENT(GameFrameUpdate);

#if !VERSION_JP
    update_input();
    profiler_update(PROFILER_TIME_CONTROLLERS, 0);
#endif

    gGameStatusPtr->frameCounter++;

    playerData->frameCounter += 2;
    if (playerData->frameCounter > MAX_GAME_TIME) {
        playerData->frameCounter = MAX_GAME_TIME;
    }

#if VERSION_JP
    update_input();
    profiler_update(PROFILER_TIME_CONTROLLERS, 0);
#endif

    update_max_rumble_duration();

    if (gGameStepDelayCount != 0) {
        gGameStepDelayCount-- ;
        if (gGameStepDelayCount == 0) {
            gGameStepDelayCount = gGameStepDelayAmount;
        } else {
            return;
        }
    }

    mdl_reset_transform_flags();
    update_workers();
    profiler_update(PROFILER_TIME_WORKERS, 0);
    update_triggers();
    profiler_update(PROFILER_TIME_TRIGGERS, 0);
    update_scripts();
    profiler_update(PROFILER_TIME_EVT, 0);
    update_messages();
    profiler_update(PROFILER_TIME_MESSAGES, 0);
    update_hud_elements();
    profiler_update(PROFILER_TIME_HUD_ELEMENTS, 0);
    step_game_mode();
    profiler_update(PROFILER_TIME_STEP_GAME_MODE, 0);
    update_entities();
    profiler_update(PROFILER_TIME_ENTITIES, 0);
    bgm_update_music_control();
    update_ambient_sounds();
    sfx_update_env_sound_params();
    update_windows();
    update_curtains();

    if (gOverrideFlags & GLOBAL_OVERRIDES_SOFT_RESET) {
        switch (SoftResetState) {
            case 0:
                gOverrideFlags |= GLOBAL_OVERRIDES_200;
                disable_player_input();

                if (SoftResetOverlayAlpha == 255) {
                    SoftResetState = 1;
                    SoftResetDelay = 3;
                } else {
                    SoftResetOverlayAlpha += 10;
                    if (SoftResetOverlayAlpha > 255) {
                        SoftResetOverlayAlpha = 255;
                    }
                }
                break;
            case 1:
                gOverrideFlags |= GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME;
                SoftResetDelay--;
                if (SoftResetDelay == 0) {
                    sfx_stop_env_sounds();
                    set_game_mode(GAME_MODE_STARTUP);
                    gOverrideFlags &= ~GLOBAL_OVERRIDES_SOFT_RESET;
                }
                break;
        }
    } else {
        SoftResetOverlayAlpha = 0;
        SoftResetState = 0;
    }

    if (gOverrideFlags & GLOBAL_OVERRIDES_DISABLE_BATTLES) {
        gOverrideFlags |= GLOBAL_OVERRIDES_PREV_DISABLE_BATTLES;
    } else {
        gOverrideFlags &= ~GLOBAL_OVERRIDES_PREV_DISABLE_BATTLES;
    }

    if (gOverrideFlags & GLOBAL_OVERRIDES_200) {
        gOverrideFlags |= GLOBAL_OVERRIDES_PREV_200;
    } else {
        gOverrideFlags &= ~GLOBAL_OVERRIDES_PREV_200;
    }

    if (gOverrideFlags & GLOBAL_OVERRIDES_400) {
        gOverrideFlags |= GLOBAL_OVERRIDES_PREV_400;
    } else {
        gOverrideFlags &= ~GLOBAL_OVERRIDES_PREV_400;
    }

    if (gOverrideFlags & GLOBAL_OVERRIDES_800) {
        gOverrideFlags |= GLOBAL_OVERRIDES_PREV_800;
    } else {
        gOverrideFlags &= ~GLOBAL_OVERRIDES_PREV_800;
    }

    // Unused rand_int used to advance the global random seed each visual frame
    rand_int(1);
}

void gfx_task_background(void) {
    gDisplayContext = &DisplayContexts[gCurrentDisplayContextIndex];
    gMainGfxPos = &gDisplayContext->backgroundGfx[0];

    gfx_init_state();
    gfx_draw_background();

    gDPFullSync(gMainGfxPos++);
    gSPEndDisplayList(gMainGfxPos++);

    // TODO these << 3 >> 3 shouldn't be necessary. There's almost definitely something we're missing here...
    ASSERT((s32)((u32)((gMainGfxPos - gDisplayContext->backgroundGfx) << 3) >> 3) < ARRAY_COUNT(
               gDisplayContext->backgroundGfx))

    nuGfxTaskStart(&gDisplayContext->backgroundGfx[0], (u32)(gMainGfxPos - gDisplayContext->backgroundGfx) * 8,
                   NU_GFX_UCODE_F3DEX2, NU_SC_NOSWAPBUFFER);
}

void gfx_draw_frame(void) {
    profiler_gfx_started();

    gMatrixListPos = 0;
    gMainGfxPos = &gDisplayContext->mainGfx[0];

    if (gOverrideFlags & GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME) {
        gCurrentDisplayContextIndex = gCurrentDisplayContextIndex ^ 1;
        return;
    }

    gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, GFX_COLOR_IMAGE_SENTINEL);
    gDPSetDepthImage(gMainGfxPos++, GFX_DEPTH_IMAGE_SENTINEL);

    gSPMatrix(gMainGfxPos++, &MasterIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    FrameInterpolation_RecordOpenChild("gfx_sprite_init", 0);
    spr_render_init();
    FrameInterpolation_RecordCloseChild();

    GFX_PROFILER_COMPLETE(PROFILER_TIME_SUB_GFX_UPDATE); // dummy

    FrameInterpolation_RecordOpenChild("gfx_world", 0);
    if (!(gOverrideFlags & GLOBAL_OVERRIDES_DISABLE_RENDER_WORLD)) {
        render_frame(false);
    }
    FrameInterpolation_RecordCloseChild();

    player_render_interact_prompts();
    //func_802C3EE4();

    GFX_PROFILER_SWITCH(PROFILER_TIME_SUB_GFX_HUD_ELEMENTS, PROFILER_TIME_SUB_GFX_BACK_UI);
    FrameInterpolation_RecordOpenChild("gfx_back_ui", 0);
    render_screen_overlay_backUI();
    render_workers_backUI();
    render_hud_elements_backUI();
    render_effects_UI();
    render_game_mode_backUI();
    FrameInterpolation_RecordCloseChild();

    FrameInterpolation_RecordOpenChild("gfx_window_root", 0);
    if (!(gOverrideFlags & GLOBAL_OVERRIDES_WINDOWS_OVER_CURTAINS)) {
        render_window_root();
    }
    FrameInterpolation_RecordCloseChild();

    GFX_PROFILER_SWITCH(PROFILER_TIME_SUB_GFX_BACK_UI, PROFILER_TIME_SUB_GFX_FRONT_UI);

    FrameInterpolation_RecordOpenChild("gfx_world_hud", 0);
    if (!(gOverrideFlags & GLOBAL_OVERRIDES_DISABLE_RENDER_WORLD) && gGameStatusPtr->debugScripts == DEBUG_SCRIPTS_NONE) {
        render_frame(true);
    }
    FrameInterpolation_RecordCloseChild();

    FrameInterpolation_RecordOpenChild("gfx_messages_mid", 0);
    if (!(gOverrideFlags & GLOBAL_OVERRIDES_MESSAGES_OVER_CURTAINS)
        && !(gOverrideFlags & GLOBAL_OVERRIDES_MESSAGES_OVER_FRONTUI)
    ) {
        render_messages();
    }
    FrameInterpolation_RecordCloseChild();

    FrameInterpolation_RecordOpenChild("gfx_front_ui", 0);
    render_workers_frontUI();
    render_hud_elements_frontUI();
    render_screen_overlay_frontUI();
    FrameInterpolation_RecordCloseChild();

    FrameInterpolation_RecordOpenChild("gfx_messages_front", 0);
    if (!(gOverrideFlags & GLOBAL_OVERRIDES_MESSAGES_OVER_CURTAINS)
        && (gOverrideFlags & GLOBAL_OVERRIDES_MESSAGES_OVER_FRONTUI)
    ) {
        render_messages();
    }
    FrameInterpolation_RecordCloseChild();

    FrameInterpolation_RecordOpenChild("gfx_curtains", 0);
    render_curtains();
    FrameInterpolation_RecordCloseChild();

    FrameInterpolation_RecordOpenChild("gfx_messages_over_curtains", 0);
    if (gOverrideFlags & GLOBAL_OVERRIDES_MESSAGES_OVER_CURTAINS) {
        render_messages();
    }
    FrameInterpolation_RecordCloseChild();

    FrameInterpolation_RecordOpenChild("gfx_window_over_curtains", 0);
    if (gOverrideFlags & GLOBAL_OVERRIDES_WINDOWS_OVER_CURTAINS) {
        render_window_root();
    }
    FrameInterpolation_RecordCloseChild();

    FrameInterpolation_RecordOpenChild("gfx_game_mode_front_ui", 0);
    render_game_mode_frontUI();
    FrameInterpolation_RecordCloseChild();

    if (gOverrideFlags & GLOBAL_OVERRIDES_SOFT_RESET) {
        switch (SoftResetState) {
            case 0:
            case 1:
                _render_transition_stencil(OVERLAY_SCREEN_MARIO, SoftResetOverlayAlpha, nullptr);
                break;
        }
    }

    GFX_PROFILER_COMPLETE(PROFILER_TIME_SUB_GFX_FRONT_UI);

    profiler_gfx_completed();
    profiler_print_times();

    #if DX_DEBUG_MENU
    dx_debug_console_main();
    #endif

    ASSERT((s32)(((u32)(gMainGfxPos - gDisplayContext->mainGfx) << 3) >> 3) < ARRAY_COUNT(gDisplayContext->mainGfx));

    gDPFullSync(gMainGfxPos++);
    gSPEndDisplayList(gMainGfxPos++);

    nuGfxTaskStart(gDisplayContext->mainGfx, (u32)(gMainGfxPos - gDisplayContext->mainGfx) * 8, NU_GFX_UCODE_F3DEX2,
                   NU_SC_TASK_LODABLE | NU_SC_SWAPBUFFER);
    gCurrentDisplayContextIndex = gCurrentDisplayContextIndex ^ 1;
    crash_screen_set_draw_info(nuGfxCfb_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void load_engine_data(void) {
    s32 i;


    gOverrideFlags = 0;
    gGameStatusPtr->unk_79 = 0;
    gGameStatusPtr->backgroundFlags = 0;
    gGameStatusPtr->musicEnabled = true;
    gGameStatusPtr->healthBarsEnabled = true;
    gGameStatusPtr->introPart = INTRO_PART_NONE;
    gGameStatusPtr->demoBattleFlags = 0;
    gGameStatusPtr->multiplayerEnabled = false;
    gGameStatusPtr->altViewportOffset.x = -8;
    gGameStatusPtr->altViewportOffset.y = 4;
    gTimeFreezeMode = TIME_FREEZE_NONE;
    gGameStatusPtr->debugQuizmo = gGameStatusPtr->unk_13C = 0;
    gGameStepDelayCount = 5;
    gGameStatusPtr->saveCount = 0;
    fio_init_flash();
    clear_input();
    general_heap_create();
    clear_render_tasks();
    clear_worker_list();
    clear_script_list();
    create_cameras();
    clear_player_status();
    spr_init_sprites(PLAYER_SPRITES_MARIO_WORLD);
    clear_entity_models();
    clear_animator_list();
    clear_model_data();
    clear_sprite_shading_data();
    reset_background_settings();
    clear_character_set();
    clear_printers();
    clear_game_mode();
    clear_npcs();
    hud_element_clear_cache();
    clear_trigger_data();
    clear_entity_data(false);
    clear_player_data();
    init_encounter_status();
    clear_screen_overlays();
    clear_effect_data();
    clear_saved_variables();
    clear_item_entity_data();
    bgm_reset_sequence_players();
    reset_ambient_sounds();
    sfx_clear_sounds();
    clear_windows();
    initialize_curtains();
    poll_rumble();

    for (i = 0; i < ARRAY_COUNT(gGameStatusPtr->holdRepeatInterval); i++) {
        gGameStatusPtr->holdRepeatInterval[i] = 3;
        gGameStatusPtr->holdDelayTime[i] = 12;
    }

    gOverrideFlags |= GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME;
    set_game_mode(GAME_MODE_STARTUP);
}

/// Time freeze modes:
///  0: none
///  1: NPCs move, can't be interacted with
///  2: NPCs don't move, no partner ability, can't interact, can't use exits
///  3: NPCs don't more or animate
///  4: NPCs can move, animations don't update, can use exits
void set_time_freeze_mode(s32 mode) {
    switch (mode) {
        case TIME_FREEZE_NONE:
            gTimeFreezeMode = mode;
            gOverrideFlags &= ~(GLOBAL_OVERRIDES_800 | GLOBAL_OVERRIDES_400 | GLOBAL_OVERRIDES_200 | GLOBAL_OVERRIDES_DISABLE_BATTLES);
            resume_all_group(EVT_GROUP_FLAG_INTERACT | EVT_GROUP_FLAG_MENUS);
            break;
        case TIME_FREEZE_PARTIAL:
            gTimeFreezeMode = mode;
            gOverrideFlags &= ~(GLOBAL_OVERRIDES_800 | GLOBAL_OVERRIDES_400 | GLOBAL_OVERRIDES_200);
            gOverrideFlags |= GLOBAL_OVERRIDES_DISABLE_BATTLES;
            suspend_all_group(EVT_GROUP_FLAG_INTERACT);
            break;
        case TIME_FREEZE_FULL:
            gTimeFreezeMode = mode;
            gOverrideFlags &= ~(GLOBAL_OVERRIDES_400 | GLOBAL_OVERRIDES_800);
            gOverrideFlags |= GLOBAL_OVERRIDES_200 | GLOBAL_OVERRIDES_DISABLE_BATTLES;
            suspend_all_group(EVT_GROUP_FLAG_MENUS);
            break;
        case TIME_FREEZE_POPUP_MENU:
            gTimeFreezeMode = mode;
            gOverrideFlags &= ~GLOBAL_OVERRIDES_800;
            gOverrideFlags |= GLOBAL_OVERRIDES_400 | GLOBAL_OVERRIDES_200 | GLOBAL_OVERRIDES_DISABLE_BATTLES;
            suspend_all_group(EVT_GROUP_FLAG_MENUS);
            break;
        case TIME_FREEZE_EXIT:
            gTimeFreezeMode = mode;
            gOverrideFlags |= GLOBAL_OVERRIDES_800 | GLOBAL_OVERRIDES_400 | GLOBAL_OVERRIDES_200 | GLOBAL_OVERRIDES_DISABLE_BATTLES;
            break;
    }
}

s32 get_time_freeze_mode(void) {
    return gTimeFreezeMode;
}

