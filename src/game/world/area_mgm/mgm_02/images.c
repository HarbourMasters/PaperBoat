#include "mgm_02.h"
#include "assets/world.h"
#include "port/Engine.h"

// Panel peach texture and palette extracted to OTR via world.yml
// Symbols defined in assets/world.h

MessageImageData N(MsgImg_PeachPanel)[] = {
    {
        .raster   = N(panel_peach_img),
        .palette  = N(panel_peach_pal),
        .format   = G_IM_FMT_CI,
        .bitDepth = G_IM_SIZ_4b,
    }
};

API_CALLABLE(N(SetMsgImgs_Panel)) {
    // query OTR texture dimensions at runtime for HD texture support
    N(MsgImg_PeachPanel)[0].width  = LOAD_ASSET_TEX_WIDTH(N(panel_peach_img));
    N(MsgImg_PeachPanel)[0].height = LOAD_ASSET_TEX_HEIGHT(N(panel_peach_img));
    set_message_images(N(MsgImg_PeachPanel));
    return ApiStatus_DONE2;
}
