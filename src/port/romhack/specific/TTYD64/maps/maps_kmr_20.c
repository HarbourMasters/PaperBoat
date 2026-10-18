#include "common.h"
#include "message_ids.h"
#include "script_api/map.h"
#include "assets/world.h"
#include "port/Engine.h"
#include "port/romhack/specific/TTYD64/maps/maps.h"

enum {
    TTYD64_RECORDS_STATE_BEGIN_FADE_IN = 0,
    TTYD64_RECORDS_STATE_FADING_IN = 1,
    TTYD64_RECORDS_STATE_IDLE = 2,
    TTYD64_RECORDS_STATE_BEGIN_FADE_OUT = 3,
    TTYD64_RECORDS_STATE_FADING_OUT = 4,
    TTYD64_RECORDS_STATE_DONE = 5,
};

typedef struct TTYD64_GameRecords {
    u16 state;
    char unk_02[0x2];
    s32 lerpTime;
    s16 unk_08;
    s16 unk_0A;
    char unk_0C[0xC];
    s16 unk_18;
    s16 alpha;
    s16 lastAlpha;
    char unk_1E[0x2];
    s32 workerID;
    u16 equippedBadges;
    s16 recipesFoundCount;
    s16 totalRecipesCount;
} TTYD64_GameRecords;

void msg_draw_frame(
    s32 posX, s32 posY, s32 sizeX, s32 sizeY, s32 style, s32 palette, s32 fading, s32 bgAlpha, s32 frameAlpha
);

static void TTYD64_kmr_20_appendGfx_records_impl(TTYD64_GameRecords* records, s32 alpha) {
    s32 width;

    if (alpha > 0) {
        gSPDisplayList(gMainGfxPos++, kmr_20_records_screen_gfx);
        gDPPipeSync(gMainGfxPos++);
        gDPSetPrimColor(gMainGfxPos++, 0, 0, 16, 120, 24, alpha * 0.65);
        gDPFillRectangle(gMainGfxPos++, 33, 43, 287, 192);
        gDPPipeSync(gMainGfxPos++);

        msg_draw_frame(30, 40, 260, 155, MSG_STYLE_INSPECT, MSG_PAL_WHITE, true, alpha * 0.55, alpha);
        draw_msg(MSG_CH0_00FC, 206 - get_msg_width(MSG_CH0_00FC, 0), 50, alpha, MSG_PAL_WHITE, DRAW_MSG_STYLE_MENU);
        draw_number(gPlayerData.totalCoinsEarned, 216, 51, 1, MSG_PAL_WHITE, alpha, 2);
        draw_msg(MSG_CH0_00FD, 206 - get_msg_width(MSG_CH0_00FD, 0), 65, alpha, MSG_PAL_WHITE, DRAW_MSG_STYLE_MENU);
        draw_number(records->equippedBadges, 231, 66, 1, MSG_PAL_WHITE, alpha, 3);
        draw_msg(MSG_MenuTip_0034, 232, 63, alpha, MSG_PAL_WHITE, 0);
        draw_number(141, 244, 66, 1, MSG_PAL_WHITE, alpha, 2);
        if (gPlayerData.starPiecesCollected == 0) {
            draw_msg(MSG_CH0_00FA, 109, 80, alpha, MSG_PAL_WHITE, 1);
        } else {
            draw_msg(MSG_CH0_00FB, 206 - get_msg_width(MSG_CH0_00FB, 0), 80, alpha, MSG_PAL_WHITE, DRAW_MSG_STYLE_MENU);
            draw_number(gPlayerData.starPiecesCollected, 231, 81, 1, MSG_PAL_WHITE, alpha, 3);
            draw_msg(MSG_MenuTip_0034, 232, 78, alpha, MSG_PAL_WHITE, 0);
            draw_number(134, 244, 80, 1, MSG_PAL_WHITE, alpha, 2);
        }

        width = get_msg_width(MSG_CH0_00FE, 0);
        if (records->recipesFoundCount == 0) {
            draw_msg(MSG_CH0_00FA, 110, 95, alpha, MSG_PAL_WHITE, DRAW_MSG_STYLE_MENU);
        } else {
            if (records->recipesFoundCount == -1) {
                draw_msg(MSG_CH0_00FE, 206 - width, 95, alpha, MSG_PAL_WHITE, DRAW_MSG_STYLE_MENU);
                draw_number(0, 231, 96, 1, MSG_PAL_WHITE, alpha, 3);
            } else {
                draw_msg(MSG_CH0_00FE, 206 - width, 95, alpha, MSG_PAL_WHITE, DRAW_MSG_STYLE_MENU);
                draw_number(records->recipesFoundCount, 231, 96, 1, MSG_PAL_WHITE, alpha, 3);
            }
            draw_msg(MSG_MenuTip_0034, 232, 93, alpha, MSG_PAL_WHITE, 0);
            draw_number(92, 244, 95, 1, MSG_PAL_WHITE, alpha, 2);
        }

        if (gPlayerData.quizzesAnswered != 0) {
            get_msg_width(MSG_CH0_00FF, 0);
        }

        draw_msg(MSG_CH0_00F4, 206 - get_msg_width(MSG_CH0_00F4, 0), 109, alpha, MSG_PAL_WHITE, DRAW_MSG_STYLE_MENU);
        draw_number(gPlayerData.battlesCount, 216, 110, 1, MSG_PAL_WHITE, alpha, 2);
        width = get_msg_width(MSG_CH0_00F7, 0);
        draw_msg(MSG_CH0_00F7, 206 - width, 125, alpha, MSG_PAL_WHITE, DRAW_MSG_STYLE_MENU);
        draw_number(gPlayerData.playerFirstStrikes, 216, 126, 1, MSG_PAL_WHITE, alpha, 2);
        draw_msg(MSG_CH0_00F8, 206 - get_msg_width(MSG_CH0_00F8, 0), 140, alpha, MSG_PAL_WHITE, DRAW_MSG_STYLE_MENU);
        draw_number(gPlayerData.enemyFirstStrikes, 216, 141, 1, MSG_PAL_WHITE, alpha, 2);

        if (gPlayerData.powerBounces == 0) {
            draw_msg(MSG_CH0_00FA, 109, 157, alpha, MSG_PAL_WHITE, DRAW_MSG_STYLE_MENU);
        } else {
            draw_msg(
                MSG_CH0_00F9, 206 - get_msg_width(MSG_CH0_00F9, 0), 157, alpha, MSG_PAL_WHITE, DRAW_MSG_STYLE_MENU
            );
            draw_number(gPlayerData.powerBounces, 216, 157, 1, MSG_PAL_WHITE, alpha, 2);
        }
    }
}

static void TTYD64_kmr_20_appendGfx_records(void* data) {
    TTYD64_GameRecords* records = (TTYD64_GameRecords*) evt_get_variable(NULL, MapVar(10));

    switch (records->state) {
        case TTYD64_RECORDS_STATE_BEGIN_FADE_IN:
            records->unk_18 = 0;
            records->unk_08 = 0;
            records->unk_0A = 0;
            records->lerpTime = 0;
            records->state = TTYD64_RECORDS_STATE_FADING_IN;
            snd_start_sound(SOUND_APPROVE, 0, 0);
            __attribute__((fallthrough));
        case TTYD64_RECORDS_STATE_FADING_IN:
            records->lerpTime++;
            records->alpha = update_lerp(EASING_LINEAR, 32.0f, 255.0f, records->lerpTime, 3);
            records->lastAlpha = records->alpha;
            if (records->lerpTime >= 3) {
                records->state = TTYD64_RECORDS_STATE_IDLE;
                records->alpha = 255;
                records->lastAlpha = records->alpha;
            }
            break;
        case TTYD64_RECORDS_STATE_IDLE:
            records->alpha = 255;
            records->lastAlpha = records->alpha;
            if (gGameStatusPtr->curButtons[0] & (BUTTON_A | BUTTON_B)) {
                records->state = TTYD64_RECORDS_STATE_BEGIN_FADE_OUT;
            }
            if (records->state != TTYD64_RECORDS_STATE_BEGIN_FADE_OUT) {
                break;
            }
            __attribute__((fallthrough));
        case TTYD64_RECORDS_STATE_BEGIN_FADE_OUT:
            records->lerpTime = 0;
            records->state = TTYD64_RECORDS_STATE_FADING_OUT;
            snd_start_sound(SOUND_MENU_BACK, 0, 0);
            __attribute__((fallthrough));
        case TTYD64_RECORDS_STATE_FADING_OUT:
            records->lerpTime++;
            records->alpha = update_lerp(EASING_LINEAR, records->lastAlpha, 0.0f, records->lerpTime, 3);
            if (records->lerpTime >= 3) {
                records->state = TTYD64_RECORDS_STATE_DONE;
            }
            break;
    }
    TTYD64_kmr_20_appendGfx_records_impl(records, records->alpha);
}

static void TTYD64_kmr_20_worker_draw_game_records(void) {
    RenderTask rt;

    rt.renderMode = RENDER_MODE_CLOUD_NO_ZCMP;
    rt.appendGfxArg = NULL;
    rt.appendGfx = TTYD64_kmr_20_appendGfx_records;
    rt.dist = 0;
    queue_render_task(&rt);
}

static void TTYD64_kmr_20_calculate_records(TTYD64_GameRecords* records) {
    PlayerData* playerData = &gPlayerData;
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < ARRAY_COUNT(playerData->badges); i++) {
        if (playerData->badges[i] != 0) {
            count++;
        }
    }
    records->equippedBadges = count;

    count = 0;
    for (i = 0; true; i++) {
        if (TTYD64_kmr_20_DataTable_80252DC0[i] != 0) {
            if (evt_get_variable(NULL, TTYD64_kmr_20_DataTable_80252DC0[i]) != 0) {
                count++;
            }
        } else {
            break;
        }
    }
    records->totalRecipesCount = i;
    records->recipesFoundCount = count;
    if (records->recipesFoundCount == 0 && evt_get_variable(NULL, GF_MAC02_DiscoveredRecipe_12)) {
        records->recipesFoundCount = -1;
    }
}

API_CALLABLE(TTYD64_kmr_20_ShowGameRecords) {
    TTYD64_GameRecords* records;

    if (isInitialCall) {
        static TTYD64_GameRecords recordsStorage;
        records = script->functionTempPtr[0] = &recordsStorage;
        records->state = TTYD64_RECORDS_STATE_BEGIN_FADE_IN;
        records->alpha = 255;
        records->workerID = create_worker_scene(NULL, TTYD64_kmr_20_worker_draw_game_records);
        evt_set_variable(script, MapVar(10), (Bytecode) records);
        TTYD64_kmr_20_calculate_records(records);
    }

    records = script->functionTempPtr[0];
    if (records->state == TTYD64_RECORDS_STATE_DONE) {
        free_worker(records->workerID);
        return ApiStatus_DONE1;
    }
    return ApiStatus_BLOCK;
}
