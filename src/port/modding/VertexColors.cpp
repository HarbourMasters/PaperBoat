#include "VertexColors.h"

#include <unordered_map>

#include <spdlog/spdlog.h>

#include "common.h"

extern "C" void* ResourceGetDataByName(const char* name);
extern "C" size_t ResourceGetSizeByName(const char* name);

namespace {

struct VertexAsset {
    Vtx* vertices;
    size_t count;
    bool warned;
};

std::unordered_map<const char*, VertexAsset>& Assets() {
    static std::unordered_map<const char*, VertexAsset> sAssets;
    return sAssets;
}

Vtx* ResolveVertex(const ModVertexRef& ref) {
    if (ref.vtxAsset == nullptr) {
        return nullptr;
    }
    auto& assets = Assets();
    auto it = assets.find(ref.vtxAsset);
    if (it == assets.end()) {
        VertexAsset asset = { static_cast<Vtx*>(ResourceGetDataByName(ref.vtxAsset)), 0, false };
        if (asset.vertices != nullptr) {
            asset.count = ResourceGetSizeByName(ref.vtxAsset) / sizeof(Vtx);
        } else {
            asset.warned = true;
            SPDLOG_WARN("Mod: vertex asset {} not found", ref.vtxAsset);
        }
        it = assets.emplace(ref.vtxAsset, asset).first;
    }
    VertexAsset& asset = it->second;
    if (ref.index < 0 || static_cast<size_t>(ref.index) >= asset.count) {
        if (!asset.warned) {
            asset.warned = true;
            SPDLOG_WARN("Mod: vertex {} out of range for {} ({} vertices)", ref.index, ref.vtxAsset, asset.count);
        }
        return nullptr;
    }
    return &asset.vertices[ref.index];
}

} // namespace

extern "C" void Mod_SetVertexColor(ModVertexRef ref, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    if (Vtx* vtx = ResolveVertex(ref)) {
        vtx->v.cn[0] = r;
        vtx->v.cn[1] = g;
        vtx->v.cn[2] = b;
        vtx->v.cn[3] = a;
    }
}

extern "C" void Mod_SetVertexColorRGB(ModVertexRef ref, uint8_t r, uint8_t g, uint8_t b) {
    if (Vtx* vtx = ResolveVertex(ref)) {
        vtx->v.cn[0] = r;
        vtx->v.cn[1] = g;
        vtx->v.cn[2] = b;
    }
}
