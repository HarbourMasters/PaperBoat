#include "ActorBlueprintEditor.h"
#include "port/ui/UIWidgets.hpp"
#include "port/ui/Notification.h"
#include "port/ui/cvar_prefixes.h"
#include "port/ActorTypeNames.h"
#include "port/FilePicker.h"
#include "port/ShipUtils.h"
#include "port/enhancements/gameplay/ActorBlueprints.h"
#include "port/sprite/SpriteLoader.h"

#include <algorithm>
#include <climits>
#include <cstring>
#include <string>
#include <unordered_map>
#include <spdlog/fmt/fmt.h>
#include <imgui.h>
#include <ship/Context.h>
#include <ship/window/Window.h>
#include "fast/Fast3dGui.h"
#include "fast/resource/type/Texture.h"

#include "common.h"
#include "sprite.h"
#include "battle/battle.h"
#include "sprite/npc/JrTroopa.h"
#include "sprite/npc/MageJrTroopa.h"
#include "sprite/npc/ParaJrTroopa.h"
#include "sprite/npc/SpikedParaJrTroopa.h"
#include "sprite/npc/StiltGuy.h"

#pragma push_macro("End")
#undef End

using namespace ActorBlueprints;

#define CVAR_NAME_POPOUT_ACTOR_BLUEPRINT_EDITOR CVAR_WINDOW("ActorBlueprintEditor")
#define CVAR_SHOW_POPOUT_ACTOR_BLUEPRINT_EDITOR CVarGetInteger(CVAR_NAME_POPOUT_ACTOR_BLUEPRINT_EDITOR, 0)

#define CI4_PALETTE_SIZE         16
#define ALL_TAB                  -1
#define PORTRAIT_LOADS_PER_FRAME 6

static const ImVec2 sListPortraitSize = ImVec2(36.0f, 36.0f);
static const ImVec2 sDetailPortraitSize = ImVec2(112.0f, 112.0f);
static const ImVec4 sModifiedColor = ImVec4(1.0f, 0.78f, 0.25f, 1.0f);
static const ImVec4 sDimColor = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);

static ImGuiWindowFlags sWindowFlags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoFocusOnAppearing;
static ImVec4 sWindowBG = ImVec4 { 0, 0, 0, 0.5f };

static int32_t sSelectedActorType = -1;
static char sFilter[64] = "";
static bool sModifiedOnly = false;

static std::shared_ptr<Fast::Fast3dGui> GetGui() {
    return std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetRawInstance()->GetWindow()->GetGui());
}

static bool ContainsIgnoreCase(const char* haystack, const char* needle) {
    std::string h = haystack;
    std::string n = needle;
    for (auto& c : h) {
        c = (char) std::tolower((unsigned char) c);
    }
    for (auto& c : n) {
        c = (char) std::tolower((unsigned char) c);
    }
    return h.find(n) != std::string::npos;
}

static std::string GetActorName(int32_t actorType) {
    const char* name = ActorTypeNames_Get(actorType);
    return name != nullptr ? name : fmt::format("Actor 0x{:02X}", actorType);
}

// MARK: - Portraits

// Battle scripts swap these actors into their real look after the blueprint's idle set.
static const std::unordered_map<int32_t, s32> sPortraitAnims = {
    { ACTOR_TYPE_JR_TROOPA_2, ANIM_JrTroopa_EggIdle },        { ACTOR_TYPE_JR_TROOPA_3, ANIM_ParaJrTroopa_Idle },
    { ACTOR_TYPE_JR_TROOPA_4, ANIM_SpikedParaJrTroopa_Idle }, { ACTOR_TYPE_JR_TROOPA_5, ANIM_MageJrTroopa_Idle },
    { ACTOR_TYPE_JR_TROOPA_6, ANIM_SpikedParaJrTroopa_Idle }, { ACTOR_TYPE_STILT_GUY, ANIM_StiltGuy_Anim01 },
};

static s32 GetPartIdleAnim(const ActorPartBlueprint* part) {
    if (part->idleAnimations == nullptr) {
        return 0;
    }
    s32 fallback = 0;
    for (s32* entry = part->idleAnimations; entry[0] != STATUS_END; entry += 2) {
        if (entry[0] == STATUS_KEY_NORMAL) {
            return entry[1];
        }
        if (fallback == 0) {
            fallback = entry[1];
        }
    }
    return fallback;
}

static s32 GetIdleAnim(const ActorBlueprint* blueprint) {
    auto it = sPortraitAnims.find(blueprint->type);
    if (it != sPortraitAnims.end()) {
        return it->second;
    }
    for (bool allowInvisible : { false, true }) {
        for (s32 i = 0; i < blueprint->partCount; i++) {
            const ActorPartBlueprint* part = &blueprint->partsData[i];
            if (!allowInvisible && (part->flags & ACTOR_PART_FLAG_INVISIBLE)) {
                continue;
            }
            s32 anim = GetPartIdleAnim(part);
            if (anim != 0) {
                return anim;
            }
        }
    }
    return 0;
}

template <typename T> static s32 CountPtrList(T* const* list) {
    s32 count = 0;
    while (list[count] != (T*) PTR_LIST_END) {
        count++;
    }
    return count;
}

struct PortraitPart {
    s32 raster = -1;
    s32 palette = -1;
    s32 parent = -1;
    s32 pos[3] = {};
};

// The state a sprite component reaches at the end of its animation's first frame.
static PortraitPart ReadFirstFrame(const SpriteAnimComponent* comp) {
    PortraitPart part;
    const u16* cmd = comp->cmdList;
    const u16* end = comp->cmdList + comp->cmdListSize / 2;

    while (cmd < end) {
        u16 op = *cmd & 0xF000;
        u16 value = *cmd & 0xFFF;
        cmd++;
        switch (op) {
            case 0x0000:
                if (part.raster != -1) {
                    return part;
                }
                break;
            case 0x1000:
                part.raster = value != 0xFFF ? value : -1;
                part.palette = -1;
                break;
            case 0x2000:
                return part;
            case 0x3000:
                for (s32 i = 0; i < 3 && cmd + i < end; i++) {
                    part.pos[i] = (s16) cmd[i];
                }
                cmd += 3;
                break;
            case 0x4000:
                cmd += 2;
                break;
            case 0x5000:
            case 0x7000:
                cmd += 1;
                break;
            case 0x6000:
                part.palette = value != 0xFFF ? value : -1;
                break;
            case 0x8000:
                if ((value & 0xF00) == 0x100) {
                    part.parent = value & 0xFF;
                }
                break;
            default:
                break;
        }
    }
    return part;
}

static bool IsArchivePath(const void* ptr) {
    return ptr != nullptr && std::strncmp((const char*) ptr, "__OTR__", 7) == 0;
}

// Original (non-HD) bytes behind a sprite image or palette pointer.
static const u8* ResolveSpriteData(
    const void* ptr,
    Fast::TextureType expected,
    size_t minSize,
    std::vector<std::shared_ptr<Ship::IResource>>* keepAlive
) {
    if (!IsArchivePath(ptr)) {
        return (const u8*) ptr;
    }
    auto resource = Ship::Context::GetRawInstance()->GetResourceManager()->LoadResource((const char*) ptr, true);
    auto texture = std::dynamic_pointer_cast<Fast::Texture>(resource);
    if (texture == nullptr || texture->Type != expected || (texture->Flags & TEX_FLAG_LOAD_AS_RAW)
        || texture->ImageData == nullptr || texture->ImageDataSize < minSize)
    {
        return nullptr;
    }
    keepAlive->push_back(resource);
    return texture->ImageData;
}

struct PortraitLayer {
    s32 x, y, z, width, height;
    std::vector<u32> pixels;
};

static bool LoadPortrait(const ActorBlueprint* blueprint, const std::string& name) {
    s32 anim = GetIdleAnim(blueprint);
    s32 spriteIdx = ((anim >> 16) & 0x7FFF) - 1;
    s32 animPalette = (anim >> 8) & 0xFF;
    s32 animIdx = anim & 0xFF;
    if (anim == 0 || spriteIdx < 0) {
        return false;
    }

    size_t size = Sprite_GetNPCSize(spriteIdx);
    if (size == 0) {
        return false;
    }
    std::vector<u8> buffer(size);
    auto* sprite = (SpriteAnimData*) Sprite_LoadNPC(spriteIdx, buffer.data(), buffer.size());
    if (sprite == nullptr) {
        return false;
    }

    s32 animCount = 0;
    while (sprite->animListStart[animCount] != (SpriteAnimComponent**) PTR_LIST_END) {
        animCount++;
    }
    if (animIdx >= animCount) {
        return false;
    }
    s32 rasterCount = CountPtrList(sprite->rastersOffset);
    s32 paletteCount = 0;
    while (sprite->palettesOffset[paletteCount] != (PAL_PTR) PTR_LIST_END) {
        paletteCount++;
    }

    SpriteAnimComponent** comps = sprite->animListStart[animIdx];
    std::vector<PortraitPart> parts;
    for (s32 c = 0; comps[c] != (SpriteAnimComponent*) PTR_LIST_END; c++) {
        parts.push_back(ReadFirstFrame(comps[c]));
    }
    for (PortraitPart& part : parts) {
        if (part.parent >= 0 && part.parent < (s32) parts.size()) {
            for (s32 i = 0; i < 3; i++) {
                part.pos[i] += parts[part.parent].pos[i];
            }
        }
    }

    std::vector<std::shared_ptr<Ship::IResource>> keepAlive;
    std::vector<PortraitLayer> layers;
    for (size_t c = 0; c < parts.size(); c++) {
        const PortraitPart& part = parts[c];
        if (part.raster < 0 || part.raster >= rasterCount) {
            continue;
        }
        SpriteRasterCacheEntry* entry = sprite->rastersOffset[part.raster];
        s32 palette = part.palette;
        if (palette == -1) {
            palette = entry->palette;
            if (animPalette != 0 && palette == 0) {
                palette = animPalette;
            }
        }
        if (palette < 0 || palette >= paletteCount) {
            continue;
        }
        s32 width = entry->width;
        s32 height = entry->height;
        const u8* image =
            ResolveSpriteData(entry->image, Fast::TextureType::Palette4bpp, width * height / 2, &keepAlive);
        const u8* colors = ResolveSpriteData(
            sprite->palettesOffset[palette], Fast::TextureType::RGBA16bpp, CI4_PALETTE_SIZE * 2, &keepAlive
        );
        if (image == nullptr || colors == nullptr) {
            continue;
        }

        const SpriteAnimComponent* comp = comps[c];
        PortraitLayer layer;
        layer.width = width;
        layer.height = height;
        layer.x = part.pos[0] + comp->compOffset.x - width / 2;
        layer.y = -(part.pos[1] + comp->compOffset.y + height);
        layer.z = part.pos[2] + comp->compOffset.z;
        layer.pixels.resize(width * height);
        for (s32 i = 0; i < width * height; i++) {
            u8 index = (i & 1) ? (image[i / 2] & 0xF) : (image[i / 2] >> 4);
            u16 color = (colors[index * 2] << 8) | colors[index * 2 + 1];
            u32 r = ((color >> 11) & 0x1F) * 0xFF / 0x1F;
            u32 g = ((color >> 6) & 0x1F) * 0xFF / 0x1F;
            u32 b = ((color >> 1) & 0x1F) * 0xFF / 0x1F;
            u32 a = (color & 1) ? 0xFF : 0;
            layer.pixels[i] = r | (g << 8) | (b << 16) | (a << 24);
        }
        layers.push_back(std::move(layer));
    }
    if (layers.empty()) {
        return false;
    }

    std::stable_sort(layers.begin(), layers.end(), [](const PortraitLayer& a, const PortraitLayer& b) {
        return a.z < b.z;
    });
    s32 minX = INT32_MAX, minY = INT32_MAX, maxX = INT32_MIN, maxY = INT32_MIN;
    for (const PortraitLayer& layer : layers) {
        minX = std::min<s32>(minX, layer.x);
        minY = std::min<s32>(minY, layer.y);
        maxX = std::max<s32>(maxX, layer.x + layer.width);
        maxY = std::max<s32>(maxY, layer.y + layer.height);
    }
    s32 outWidth = maxX - minX;
    s32 outHeight = maxY - minY;
    auto pixels = std::make_shared<std::vector<char>>(outWidth * outHeight * 4, 0);
    u32* out = (u32*) pixels->data();
    for (const PortraitLayer& layer : layers) {
        for (s32 y = 0; y < layer.height; y++) {
            for (s32 x = 0; x < layer.width; x++) {
                u32 px = layer.pixels[y * layer.width + x];
                if (px >> 24) {
                    out[(layer.y - minY + y) * outWidth + (layer.x - minX + x)] = px;
                }
            }
        }
    }

    Fast::Texture texture;
    texture.Type = Fast::TextureType::RGBA32bpp;
    texture.Width = outWidth;
    texture.Height = outHeight;
    texture.ImageDataSize = pixels->size();
    texture.mImageBuffer = pixels;
    texture.ImageData = (u8*) pixels->data();
    GetGui()->LoadGuiTexture(name, texture);
    return GetGui()->HasTextureByName(name);
}

static ImTextureID GetPortrait(const ActorBlueprint* blueprint, ImVec2* textureSize) {
    static std::unordered_map<const ActorBlueprint*, bool> sLoaded;
    static int sBudgetFrame = -1;
    static int sBudget = 0;
    std::string name = fmt::format("ActorPortrait_{:p}", (const void*) blueprint);

    auto it = sLoaded.find(blueprint);
    if (it == sLoaded.end()) {
        if (sBudgetFrame != ImGui::GetFrameCount()) {
            sBudgetFrame = ImGui::GetFrameCount();
            sBudget = PORTRAIT_LOADS_PER_FRAME;
        }
        if (sBudget <= 0) {
            return nullptr;
        }
        sBudget--;
        it = sLoaded.emplace(blueprint, LoadPortrait(blueprint, name)).first;
    }
    if (!it->second) {
        return nullptr;
    }
    *textureSize = GetGui()->GetTextureSize(name);
    return GetGui()->GetTextureByName(name);
}

static void DrawPortraitAt(const ActorBlueprint* blueprint, ImVec2 min, ImVec2 box) {
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 size;
    ImTextureID texture = GetPortrait(blueprint, &size);

    if (texture != nullptr && size.x > 0 && size.y > 0) {
        float scale = std::min(box.x / size.x, box.y / size.y);
        ImVec2 drawMin = ImVec2(min.x + (box.x - size.x * scale) / 2, min.y + (box.y - size.y * scale) / 2);
        drawList->AddImage(texture, drawMin, ImVec2(drawMin.x + size.x * scale, drawMin.y + size.y * scale));
    } else {
        ImVec2 max = ImVec2(min.x + box.x, min.y + box.y);
        ImVec2 textSize = ImGui::CalcTextSize("?");
        drawList->AddRect(min, max, ImGui::GetColorU32(sDimColor), 4.0f);
        drawList->AddText(
            ImVec2((min.x + max.x - textSize.x) / 2, (min.y + max.y - textSize.y) / 2), ImGui::GetColorU32(sDimColor),
            "?"
        );
    }
}

static void DrawPortrait(const ActorBlueprint* blueprint, ImVec2 box) {
    ImGui::Dummy(box);
    DrawPortraitAt(blueprint, ImGui::GetItemRectMin(), box);
}

// MARK: - Preset files

static void NotifyResult(const char* prefix, bool ok, const std::string& message) {
    Notification::Emit(
        {
            .prefix = prefix,
            .message = message,
            .messageColor = ok ? ImVec4(0.7f, 0.7f, 0.7f, 1.0f) : ImVec4(1.0f, 0.5f, 0.5f, 1.0f),
        }
    );
}

static void ExportPresetWithPicker() {
    Ship::FileBrowserRequest request;
    request.Title = "Export actor blueprint preset";
    request.StartDir = Ship::Context::GetAppDirectoryPath();
    request.Filters = { { "Blueprint Preset", { "*.json" } } };
    request.Save = true;
    request.DefaultName = "actor_blueprints.json";
    Paperboat::PickFile(std::move(request), [](std::optional<std::filesystem::path> path) {
        if (!path) {
            return;
        }
        std::string error;
        bool ok = ExportPreset(*path, &error);
        NotifyResult("Blueprint Editor", ok, ok ? "Exported " + path->filename().string() : error);
    });
}

static void ImportPresetWithPicker() {
    Ship::FileBrowserRequest request;
    request.Title = "Import actor blueprint preset";
    request.StartDir = Ship::Context::GetAppDirectoryPath();
    request.Filters = { { "Blueprint Preset", { "*.json" } }, { "All Files", { "*" } } };
    Paperboat::PickFile(std::move(request), [](std::optional<std::filesystem::path> path) {
        if (!path) {
            return;
        }
        std::string error;
        bool ok = ImportPreset(*path, &error);
        NotifyResult("Blueprint Editor", ok, ok ? "Imported " + path->filename().string() : error);
    });
}

// MARK: - Drawing

static bool PassesFilters(const CatalogEntry& entry, int32_t tab) {
    if (tab == ALL_TAB ? entry.chapter == CHAPTER_PARTNERS : entry.chapter != tab) {
        return false;
    }
    if (sModifiedOnly && !GetOverride(entry.actorType).Any()) {
        return false;
    }
    return ContainsIgnoreCase(GetActorName(entry.actorType).c_str(), sFilter);
}

static void DrawToolbar() {
    bool enabled = IsEnabled();
    if (UIWidgets::Checkbox("Apply blueprint overrides", &enabled, UIWidgets::CheckboxOptions().Color(WIDGET_COLOR))) {
        SetEnabled(enabled);
    }
    UIWidgets::Tooltip("When off, every enemy uses its vanilla stats. Edits are kept either way.");

    ImGui::SameLine();
    ImGui::TextColored(sDimColor, "%d modified", CountModifiedActors());

    float buttonWidth = 90.0f;
    ImGui::SameLine(ImGui::GetContentRegionMax().x - buttonWidth * 3 - ImGui::GetStyle().ItemSpacing.x * 2);
    if (UIWidgets::Button(
            "Import",
            UIWidgets::ButtonOptions()
                .Size(ImVec2(buttonWidth, 0))
                .Color(WIDGET_COLOR)
                .Tooltip("Load a preset JSON. Replaces the current edits.")
        ))
    {
        ImportPresetWithPicker();
    }
    ImGui::SameLine();
    if (UIWidgets::Button(
            "Export",
            UIWidgets::ButtonOptions().Size(ImVec2(buttonWidth, 0)).Color(WIDGET_COLOR).Tooltip("Save edits as JSON.")
        ))
    {
        ExportPresetWithPicker();
    }
    ImGui::SameLine();
    if (UIWidgets::Button(
            "Reset All",
            UIWidgets::ButtonOptions()
                .Size(ImVec2(buttonWidth, 0))
                .Color(UIWidgets::Colors::Red)
                .Tooltip("Restore every enemy to vanilla.")
        ))
    {
        ClearAll();
    }

    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.5f);
    ImGui::InputTextWithHint("##actorFilter", "Filter by name...", sFilter, sizeof(sFilter));
    ImGui::SameLine();
    UIWidgets::Checkbox("Modified only", &sModifiedOnly, UIWidgets::CheckboxOptions().Color(WIDGET_COLOR));
}

static void DrawActorList(const std::vector<CatalogEntry>& catalog, int32_t tab) {
    for (const CatalogEntry& entry : catalog) {
        if (!PassesFilters(entry, tab)) {
            continue;
        }
        ImGui::PushID(entry.actorType);
        bool selected = entry.actorType == sSelectedActorType;
        bool modified = GetOverride(entry.actorType).Any();
        if (ImGui::Selectable("##row", selected, 0, ImVec2(0, sListPortraitSize.y))) {
            sSelectedActorType = entry.actorType;
        }
        ImVec2 rowMin = ImGui::GetItemRectMin();
        DrawPortraitAt(entry.blueprint, rowMin, sListPortraitSize);
        std::string label = GetActorName(entry.actorType) + (modified ? " *" : "");
        ImGui::GetWindowDrawList()->AddText(
            ImVec2(
                rowMin.x + sListPortraitSize.x + ImGui::GetStyle().ItemSpacing.x,
                rowMin.y + (sListPortraitSize.y - ImGui::GetTextLineHeight()) / 2
            ),
            ImGui::GetColorU32(modified ? sModifiedColor : ImGui::GetStyleColorVec4(ImGuiCol_Text)), label.c_str()
        );
        ImGui::PopID();
    }
}

static void DrawField(const CatalogEntry& entry, const Override& ov, Field field) {
    if (!FieldApplies(entry, field)) {
        return;
    }
    const FieldInfo& info = GetFieldInfo(field);
    int32_t defaultValue = GetDefault(entry.blueprint, field);
    int32_t value = ov.isSet[field] ? ov.value[field] : defaultValue;
    bool isChance = field >= FIELD_ESCAPE_CHANCE && field <= FIELD_UP_AND_AWAY_CHANCE;

    ImGui::PushID(field);
    if (ov.isSet[field]) {
        ImGui::TextColored(sModifiedColor, "%s", info.label);
    } else {
        ImGui::TextUnformatted(info.label);
    }
    ImGui::SameLine();
    ImGui::TextColored(sDimColor, "(vanilla %d)", defaultValue);
    if (ov.isSet[field]) {
        ImGui::SameLine(ImGui::GetContentRegionMax().x - 60.0f);
        if (UIWidgets::Button("Reset", UIWidgets::ButtonOptions().Size(ImVec2(60.0f, 0)).Color(WIDGET_COLOR))) {
            ClearOverride(entry.actorType, field);
        }
    }

    if (UIWidgets::SliderInt(
            info.label, &value,
            UIWidgets::IntSliderOptions()
                .Min(info.min)
                .Max(info.max)
                .DefaultValue(defaultValue)
                .Format(field == FIELD_ATTACK_PERCENT || isChance ? "%d%%" : "%d")
                .LabelPosition(UIWidgets::LabelPositions::None)
                .Color(WIDGET_COLOR)
                .Tooltip(info.tooltip)
        ))
    {
        if (value == defaultValue) {
            ClearOverride(entry.actorType, field);
        } else {
            SetOverride(entry.actorType, field, value);
        }
    }
    ImGui::PopID();
}

static void DrawActorDetails(const CatalogEntry& entry) {
    Override ov = GetOverride(entry.actorType);

    ImGui::BeginGroup();
    DrawPortrait(entry.blueprint, sDetailPortraitSize);
    ImGui::EndGroup();
    ImGui::SameLine();
    ImGui::BeginGroup();
    ImGui::SetWindowFontScale(1.3f);
    ImGui::TextUnformatted(GetActorName(entry.actorType).c_str());
    ImGui::SetWindowFontScale(1.0f);
    ImGui::TextColored(sDimColor, "Type 0x%02X  -  %s", entry.actorType, GetChapterName(entry.chapter));
    if (entry.variantCount > 1) {
        ImGui::TextColored(sDimColor, "%d blueprint variants share this type; edits apply to all.", entry.variantCount);
    }
    if (ov.Any()) {
        if (UIWidgets::Button(
                "Reset Enemy", UIWidgets::ButtonOptions().Size(ImVec2(130.0f, 0)).Color(UIWidgets::Colors::Red)
            ))
        {
            ClearActor(entry.actorType);
            ov = Override {};
        }
    }
    ImGui::EndGroup();

    ImGui::SeparatorText("Combat");
    DrawField(entry, ov, FIELD_MAX_HP);
    DrawField(entry, ov, FIELD_ATTACK_PERCENT);
    DrawField(entry, ov, FIELD_ATTACK_BONUS);

    if (entry.chapter == CHAPTER_PARTNERS) {
        ImGui::Spacing();
        ImGui::TextColored(
            sDimColor,
            "Applies to every move this partner uses, at any rank. Rank and upgrades come\n"
            "from your save; change them in the Save Editor."
        );
        return;
    }

    ImGui::SeparatorText("Rewards");
    DrawField(entry, ov, FIELD_LEVEL);
    DrawField(entry, ov, FIELD_COIN_REWARD);

    ImGui::SeparatorText("Susceptibility");
    for (int32_t field = FIELD_ESCAPE_CHANCE; field <= FIELD_SPIN_SMASH_REQ; field++) {
        DrawField(entry, ov, (Field) field);
    }

    ImGui::Spacing();
    ImGui::TextColored(
        sDimColor,
        "Changes apply from the next battle. Move choice odds live in each enemy's script\n"
        "and aren't editable here yet."
    );
}

static void DrawTabContents(const std::vector<CatalogEntry>& catalog, int32_t tab) {
    float listWidth = std::max(220.0f, ImGui::GetContentRegionAvail().x * 0.34f);

    if (ImGui::BeginChild("ActorList", ImVec2(listWidth, 0), ImGuiChildFlags_Borders)) {
        DrawActorList(catalog, tab);
    }
    ImGui::EndChild();
    ImGui::SameLine();

    if (ImGui::BeginChild("ActorDetails", ImVec2(0, 0), ImGuiChildFlags_Borders)) {
        const CatalogEntry* selected = nullptr;
        for (const CatalogEntry& entry : catalog) {
            if (entry.actorType == sSelectedActorType && PassesFilters(entry, tab)) {
                selected = &entry;
                break;
            }
        }
        if (selected != nullptr) {
            DrawActorDetails(*selected);
        } else {
            ImGui::TextColored(sDimColor, "Select an enemy to edit its blueprint.");
        }
    }
    ImGui::EndChild();
}

static void DrawEditor() {
    std::vector<CatalogEntry> catalog = GetCatalog();

    DrawToolbar();
    UIWidgets::PushStyleTabs(WIDGET_COLOR);
    if (ImGui::BeginTabBar("ActorBlueprintTabs", ImGuiTabBarFlags_FittingPolicyScroll)) {
        if (ImGui::BeginTabItem("All")) {
            DrawTabContents(catalog, ALL_TAB);
            ImGui::EndTabItem();
        }
        for (int32_t chapter = 0; chapter < CHAPTER_COUNT; chapter++) {
            bool hasEnemies = std::any_of(catalog.begin(), catalog.end(), [chapter](const CatalogEntry& entry) {
                return entry.chapter == chapter;
            });
            if (!hasEnemies) {
                continue;
            }
            if (ImGui::BeginTabItem(GetChapterName((Chapter) chapter))) {
                DrawTabContents(catalog, chapter);
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
    UIWidgets::PopStyleTabs();
}

void ActorBlueprintEditorWindow::DrawElement() {
    if (CVAR_SHOW_POPOUT_ACTOR_BLUEPRINT_EDITOR) {
        return;
    }
    DrawEditor();
}

void ActorBlueprintEditorWindow::Draw() {
    if (!CVAR_SHOW_POPOUT_ACTOR_BLUEPRINT_EDITOR) {
        return;
    }

    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, sWindowBG);
    ImGui::PushStyleColor(ImGuiCol_TitleBg, sWindowBG);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, sWindowBG);
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);
    ImGui::SetNextWindowSize(ImVec2(820.0f, 560.0f), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Blueprint Editor", nullptr, sWindowFlags)) {
        DrawEditor();
    }
    ImGui::End();

    ImGui::PopStyleColor(4);
    ImGui::PopStyleVar(1);
}

#pragma pop_macro("End")
