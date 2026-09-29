#include "port/ui/cvar_prefixes.h"
#include <fast/resource/type/Texture.h>
#include <libultraship/bridge/consolevariablebridge.h>
#include <ship/Context.h>
#include <ship/resource/ResourceManager.h>

#include <algorithm>
#include <cstring>
#include <map>
#include <vector>

#include "common.h"
#include "port/patches/Patches.h"

struct StatusBarElementOption {
    const char* cvar;
    s32 defaultValue;
};

// Indexed by PortStatusBarElement
static const StatusBarElementOption sElements[] = {
    { CVAR_ENHANCEMENT("StatusBar.ShowBackground"), 1 }, { CVAR_ENHANCEMENT("StatusBar.ShowHP"), 1 },
    { CVAR_ENHANCEMENT("StatusBar.ShowFP"), 1 },         { CVAR_ENHANCEMENT("StatusBar.ShowStarPower"), 1 },
    { CVAR_ENHANCEMENT("StatusBar.ShowStarPoints"), 1 }, { CVAR_ENHANCEMENT("StatusBar.ShowCoins"), 1 },
    { CVAR_ENHANCEMENT("StatusBar.ShowStarPieces"), 0 }, { CVAR_ENHANCEMENT("StatusBar.ShowBadges"), 0 },
};

static const Color_RGBA8 sDefaultHighlightColor = { 235, 230, 119, 255 };
static const Color_RGBA8 sDefaultShadowColor = { 142, 90, 37, 255 };
static const Color_RGBA8 sDefaultFillColor = { 185, 155, 75, 255 };

static WindowStyleCustom sBoxStyles[2];

struct FlatBottomCorners {
    std::shared_ptr<Fast::Texture> left;
    std::shared_ptr<Fast::Texture> right;
    std::vector<u8> leftSheet;
    u8 fmt;
    u8 siz;
};

static f32 status_bar_percent(const char* cvar, s32 min, s32 max) {
    return std::clamp(CVarGetInteger(cvar, 100), min, max) / 100.0f;
}

static std::shared_ptr<Fast::Texture> status_bar_load_corners(const char* path, bool original) {
    return std::static_pointer_cast<Fast::Texture>(
        Ship::Context::GetRawInstance()->GetResourceManager()->LoadResource(path, original)
    );
}

static bool
status_bar_corners_spliceable(const Fast::Texture* left, const Fast::Texture* right, u8* fmt, u8* siz, u32* bpp) {
    if (left == nullptr || right == nullptr || left->Type != right->Type || left->Width != 16 || right->Width != 16) {
        return false;
    }
    switch (left->Type) {
        case Fast::TextureType::RGBA32bpp:
            *fmt = G_IM_FMT_RGBA;
            *siz = G_IM_SIZ_32b;
            *bpp = 4;
            break;
        case Fast::TextureType::RGBA16bpp:
            *fmt = G_IM_FMT_RGBA;
            *siz = G_IM_SIZ_16b;
            *bpp = 2;
            break;
        case Fast::TextureType::GrayscaleAlpha16bpp:
            *fmt = G_IM_FMT_IA;
            *siz = G_IM_SIZ_16b;
            *bpp = 2;
            break;
        case Fast::TextureType::GrayscaleAlpha8bpp:
            *fmt = G_IM_FMT_IA;
            *siz = G_IM_SIZ_8b;
            *bpp = 1;
            break;
        default:
            return false;
    }
    return left->ImageDataSize >= 16 * 40 * *bpp && right->ImageDataSize >= 16 * 32 * *bpp;
}

static const FlatBottomCorners* status_bar_flat_bottom_corners() {
    static auto& sSheets = *new std::map<std::pair<const u8*, const u8*>, FlatBottomCorners>();
    u8 fmt, siz;
    u32 bpp;

    auto left = status_bar_load_corners("ui/box/corners6", false);
    auto right = status_bar_load_corners("ui/box/corners7", false);
    if (!status_bar_corners_spliceable(left.get(), right.get(), &fmt, &siz, &bpp)) {
        left = status_bar_load_corners("ui/box/corners6", true);
        right = status_bar_load_corners("ui/box/corners7", true);
        if (!status_bar_corners_spliceable(left.get(), right.get(), &fmt, &siz, &bpp)) {
            return nullptr;
        }
    }

    auto [it, inserted] = sSheets.try_emplace({ left->ImageData, right->ImageData });
    FlatBottomCorners& corners = it->second;
    if (inserted) {
        corners.left = left;
        corners.right = right;
        corners.fmt = fmt;
        corners.siz = siz;
        corners.leftSheet.resize(16 * 32 * bpp);
        memcpy(corners.leftSheet.data(), left->ImageData, 16 * 24 * bpp);
        memcpy(corners.leftSheet.data() + 16 * 24 * bpp, right->ImageData + 16 * 16 * bpp, 16 * 8 * bpp);
    }
    return &corners;
}

extern "C" b32 port_status_bar_show(s32 element) {
    return CVarGetInteger(sElements[element].cvar, sElements[element].defaultValue) != 0;
}

extern "C" b32 port_status_bar_always_show(void) {
    return CVarGetInteger(CVAR_ENHANCEMENT("StatusBar.AlwaysShow"), 0) && gGameStatusPtr->context == CONTEXT_WORLD;
}

extern "C" b32 port_status_bar_flat_bottom(void) {
    return CVarGetInteger(CVAR_ENHANCEMENT("StatusBar.FlatBottom"), 0) && status_bar_flat_bottom_corners() != nullptr;
}

extern "C" f32 port_status_bar_scale(void) {
    return status_bar_percent(CVAR_ENHANCEMENT("StatusBar.Scale"), 50, 200);
}

extern "C" f32 port_status_bar_box_width(void) {
    return status_bar_percent(CVAR_ENHANCEMENT("StatusBar.BoxWidth"), 20, 100);
}

extern "C" f32 port_status_bar_box_height(void) {
    return status_bar_percent(CVAR_ENHANCEMENT("StatusBar.BoxHeight"), 50, 200);
}

extern "C" s32 port_status_bar_retracted_y(void) {
    return -100 * MAX(1.0f, port_status_bar_scale() * MAX(1.0f, port_status_bar_box_height()));
}

extern "C" void* port_status_bar_box_style(s32 styleID) {
    WindowStyleCustom* style = &sBoxStyles[styleID == WINDOW_STYLE_6];

    port_box_default_style(style, styleID);
    if (CVarGetInteger(CVAR_ENHANCEMENT("StatusBar.FlatColor"), 0)) {
        style->color1 = CVarGetColor(CVAR_ENHANCEMENT("StatusBar.FillColor.Value"), sDefaultFillColor);
        style->color2 = style->color1;
    } else {
        style->color1 = CVarGetColor(CVAR_ENHANCEMENT("StatusBar.HighlightColor.Value"), sDefaultHighlightColor);
        style->color2 = CVarGetColor(CVAR_ENHANCEMENT("StatusBar.ShadowColor.Value"), sDefaultShadowColor);
    }
    if (CVarGetInteger(CVAR_ENHANCEMENT("StatusBar.FlatBottom"), 0)) {
        if (const FlatBottomCorners* corners = status_bar_flat_bottom_corners()) {
            style->corners.fmt = corners->fmt;
            style->corners.bitDepth = corners->siz;
            if (styleID == WINDOW_STYLE_5) {
                style->corners.imgData = (IMG_PTR) corners->leftSheet.data();
                style->corners.size4.y = 8;
            } else {
                style->corners.imgData = corners->right->ImageData;
            }
        }
    }

    // A hidden box is still drawn, fully transparent: the icons after it rely on the render state it sets
    if (!port_status_bar_show(PORT_STATUS_BAR_BACKGROUND)) {
        style->color1.a = 0;
    }
    return style;
}
