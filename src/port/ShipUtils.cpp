#include "ShipUtils.h"
#include <libultraship/libultraship.h>
#include "fast/interpreter.h"
#include "fast/Fast3dWindow.h"
#include "fast/Fast3dGui.h"

#include "assets/ui.h"

extern "C" {
extern intptr_t gItemIconRasterOffsets[349];
extern intptr_t gItemIconPaletteOffsets[349];
}

typedef struct {
    const char* assetTexturePath;
    ImVec4 assetTint;
} TextureAsset;

typedef struct {
    const char* assetTexturePath;
    const char* assetPalettePath;
    ImVec4 assetTint;
} PaletteAsset;

constexpr f32 fourByThree = 4.0f / 3.0f;

extern "C" bool Ship_IsCStringEmpty(const char* str) {
    return str == NULL || str[0] == '\0';
}

void TableCellCenteredText(const char* text, ImVec2 size) {
    float textHeight = ImGui::GetTextLineHeight();
    float offsetY = (size.y - textHeight) * 0.5f;
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offsetY);
    ImGui::Text("%s", text);
}

char seedString[MAX_SEED_STRING_SIZE];
u32 finalSeed = 0;

extern uint32_t Ship_Hash(std::string str) {
    // FNV-1a
    const size_t len = str.size();
    uint32_t hval = 0x811c9dc5;
    for (size_t pos = 0; pos < len; pos++) {
        hval ^= (uint32_t) str[pos];
        hval *= 0x01000193;
    }
    return hval;
}

// Build vertex coordinates for a quad command
// In order of top left, top right, bottom left, then bottom right
// Supports flipping the texture horizontally
extern "C" void Ship_CreateQuadVertexGroup(Vtx* vtxList, s32 xStart, s32 yStart, s32 width, s32 height, u8 flippedH) {
    vtxList[0].v.ob[0] = xStart;
    vtxList[0].v.ob[1] = yStart;
    vtxList[0].v.tc[0] = (flippedH ? width : 0) << 5;
    vtxList[0].v.tc[1] = 0 << 5;

    vtxList[1].v.ob[0] = xStart + width;
    vtxList[1].v.ob[1] = yStart;
    vtxList[1].v.tc[0] = (flippedH ? width * 2 : width) << 5;
    vtxList[1].v.tc[1] = 0 << 5;

    vtxList[2].v.ob[0] = xStart;
    vtxList[2].v.ob[1] = yStart + height;
    vtxList[2].v.tc[0] = (flippedH ? width : 0) << 5;
    vtxList[2].v.tc[1] = height << 5;

    vtxList[3].v.ob[0] = xStart + width;
    vtxList[3].v.ob[1] = yStart + height;
    vtxList[3].v.tc[0] = (flippedH ? width * 2 : width) << 5;
    vtxList[3].v.tc[1] = height << 5;
}

std::vector<TextureAsset> digitTextures = {
    { ui_pause_small_digit_0_png }, { ui_pause_small_digit_0_pal }, { ui_pause_small_digit_1_png },
    { ui_pause_small_digit_1_pal }, { ui_pause_small_digit_2_png }, { ui_pause_small_digit_2_pal },
    { ui_pause_small_digit_3_png }, { ui_pause_small_digit_3_pal }, { ui_pause_small_digit_4_png },
    { ui_pause_small_digit_4_pal }, { ui_pause_small_digit_5_png }, { ui_pause_small_digit_5_pal },
    { ui_pause_small_digit_6_png }, { ui_pause_small_digit_6_pal }, { ui_pause_small_digit_7_png },
    { ui_pause_small_digit_7_pal }, { ui_pause_small_digit_8_png }, { ui_pause_small_digit_8_pal },
    { ui_pause_small_digit_9_png }, { ui_pause_small_digit_9_pal },
};

std::vector<TextureAsset> guiTextures = {
    { ui_stat_heart_png },
    { ui_stat_flower_png },
};

std::vector<PaletteAsset> guiPaletteTextures = {
    { ui_pause_mario_large_png, ui_pause_mario_large_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_pause_stat_bp_png, ui_pause_stat_bp_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_files_eldstar_png, ui_files_eldstar_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_status_star_point_0_png, ui_status_star_point_0_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_status_coin_0_png, ui_status_coin_0_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_status_star_piece_0_png, ui_status_star_piece_0_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_pause_stat_time_png, ui_pause_stat_time_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_goombario_png, ui_goombario_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_kooper_png, ui_kooper_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_bombette_png, ui_bombette_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_parakarry_png, ui_parakarry_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_watt_png, ui_watt_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_sushie_png, ui_sushie_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_lakilester_png, ui_lakilester_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_bow_png, ui_bow_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_pause_jp_super_png, ui_pause_jp_super_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_pause_jp_ultra_png, ui_pause_jp_ultra_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_pause_partner_rank_png, ui_pause_partner_rank_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
    { ui_battle_menu_nothing_png, ui_battle_menu_nothing_pal, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f } },
};

void LoadGuiTextures() {
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(WindowGetWindowComponent()->GetGui());

    // for (auto& asset : digitTextures) {
    //     gui->LoadGuiTexture(asset.assetTexturePath, asset.assetTexturePath);
    // }

    for (int i = 0; i < 349; i++) {
        const char* rasterPath = reinterpret_cast<const char*>(gItemIconRasterOffsets[i]);
        const char* palettePath = reinterpret_cast<const char*>(gItemIconPaletteOffsets[i]);
        gui->LoadGuiTexture(rasterPath, rasterPath, palettePath, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    for (auto& asset : guiTextures) {
        gui->LoadGuiTexture(asset.assetTexturePath, asset.assetTexturePath);
    }

    for (auto& asset : guiPaletteTextures) {
        gui->LoadGuiTexture(asset.assetTexturePath, asset.assetTexturePath, asset.assetPalettePath, asset.assetTint);
    }

    gui->LoadGuiTexture(
        "Ultra Rank", ui_pause_partner_rank_png, ui_pause_partner_rank_pal, ImVec4 { 1.0f, 0, 0, 1.0f }
    );
}
