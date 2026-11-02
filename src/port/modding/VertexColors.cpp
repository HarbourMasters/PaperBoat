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
        it = assets.emplace(ref.vtxAsset, VertexAsset { nullptr, 0, false }).first;
    } else if (it->second.vertices == nullptr) {
        return nullptr;
    }
    VertexAsset& current = it->second;
    Vtx* vertices = static_cast<Vtx*>(ResourceGetDataByName(ref.vtxAsset));
    if (vertices == nullptr) {
        current = { nullptr, 0, true };
        SPDLOG_WARN("Mod: vertex asset {} not found", ref.vtxAsset);
        return nullptr;
    }
    if (vertices != current.vertices) {
        current.vertices = vertices;
        current.count = ResourceGetSizeByName(ref.vtxAsset) / sizeof(Vtx);
    }
    if (ref.index < 0 || static_cast<size_t>(ref.index) >= current.count) {
        if (!current.warned) {
            current.warned = true;
            SPDLOG_WARN("Mod: vertex {} out of range for {} ({} vertices)", ref.index, ref.vtxAsset, current.count);
        }
        return nullptr;
    }
    return &current.vertices[ref.index];
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
