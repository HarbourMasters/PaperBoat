#include "mgm_01.h"
#include "assets/world.h"
#include "port/Engine.h"

// All panel textures and palettes extracted to OTR via world.yml
// Symbols defined in assets/world.h

MessageImageData N(MsgImgs_Panels)[] = {
    {
        .raster   = N(panel_1_coin_img),
        .palette  = N(panel_1_coin_pal),
        .format   = G_IM_FMT_CI,
        .bitDepth = G_IM_SIZ_4b,
    },
    {
        .raster   = N(panel_5_coins_img),
        .palette  = N(panel_5_coins_pal),
        .format   = G_IM_FMT_CI,
        .bitDepth = G_IM_SIZ_4b,
    },
    {
        .raster   = N(panel_times_5_img),
        .palette  = N(panel_times_5_pal),
        .format   = G_IM_FMT_CI,
        .bitDepth = G_IM_SIZ_4b,
    },
    {
        .raster   = N(panel_bowser_img),
        .palette  = N(panel_bowser_pal),
        .format   = G_IM_FMT_CI,
        .bitDepth = G_IM_SIZ_4b,
    }
};

API_CALLABLE(N(SetMsgImgs_Panels)) {
    // query OTR texture dimensions at runtime for HD texture support
    N(MsgImgs_Panels)[0].width  = LOAD_ASSET_TEX_WIDTH(N(panel_1_coin_img));
    N(MsgImgs_Panels)[0].height = LOAD_ASSET_TEX_HEIGHT(N(panel_1_coin_img));
    N(MsgImgs_Panels)[1].width  = LOAD_ASSET_TEX_WIDTH(N(panel_5_coins_img));
    N(MsgImgs_Panels)[1].height = LOAD_ASSET_TEX_HEIGHT(N(panel_5_coins_img));
    N(MsgImgs_Panels)[2].width  = LOAD_ASSET_TEX_WIDTH(N(panel_times_5_img));
    N(MsgImgs_Panels)[2].height = LOAD_ASSET_TEX_HEIGHT(N(panel_times_5_img));
    N(MsgImgs_Panels)[3].width  = LOAD_ASSET_TEX_WIDTH(N(panel_bowser_img));
    N(MsgImgs_Panels)[3].height = LOAD_ASSET_TEX_HEIGHT(N(panel_bowser_img));
    set_message_images(N(MsgImgs_Panels));
    return ApiStatus_DONE2;
}
