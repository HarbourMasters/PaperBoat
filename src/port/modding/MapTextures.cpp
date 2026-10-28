#include "MapTextures.h"

#include <iterator>
#include <map>
#include <string>
#include <utility>

#include <spdlog/spdlog.h>

#include "ModInternal.h"

static std::map<std::string, Mod::OwnerStack<std::pair<uint16_t, uint16_t>>>& MapTextureSizes() {
    static std::map<std::string, Mod::OwnerStack<std::pair<uint16_t, uint16_t>>> sSizes;
    return sSizes;
}

extern "C" void
Mod_OverrideMapTextureSize(const char* owner, const char* archive, const char* name, uint16_t width, uint16_t height) {
    const std::string ownerName = Mod::OwnerName(owner);
    const std::string key = std::string(archive) + "/" + name;
    if (const std::string* previous = MapTextureSizes()[key].Push(ownerName, { width, height })) {
        SPDLOG_WARN("Mod: {} resizes map texture {} already resized by {}", ownerName, key, *previous);
    }
}

extern "C" bool Mod_GetMapTextureSize(const char* archive, const char* name, uint16_t* width, uint16_t* height) {
    auto& sizes = MapTextureSizes();
    if (sizes.empty()) {
        return false;
    }
    auto it = sizes.find(std::string(archive) + "/" + name);
    if (it == sizes.end()) {
        return false;
    }
    *width = it->second.Top().first;
    *height = it->second.Top().second;
    return true;
}

static std::map<std::string, Mod::OwnerStack<std::string>>& MapTexArchiveBlobs() {
    static std::map<std::string, Mod::OwnerStack<std::string>> sBlobs;
    return sBlobs;
}

extern "C" void Mod_RegisterMapTexArchive(const char* owner, const char* archive, const char* blobPath) {
    const std::string ownerName = Mod::OwnerName(owner);
    if (const std::string* previous = MapTexArchiveBlobs()[archive].Push(ownerName, blobPath)) {
        SPDLOG_WARN("Mod: {} replaces map texture archive {} already replaced by {}", ownerName, archive, *previous);
    }
}

extern "C" const char* Mod_GetMapTexArchiveBlob(const char* archive) {
    auto& blobs = MapTexArchiveBlobs();
    if (blobs.empty()) {
        return nullptr;
    }
    auto it = blobs.find(archive);
    return it != blobs.end() ? it->second.Top().c_str() : nullptr;
}

void Mod::UnregisterMapTextures(const std::string& owner) {
    auto& sizes = MapTextureSizes();
    for (auto it = sizes.begin(); it != sizes.end();) {
        it->second.Remove(owner);
        it = it->second.Empty() ? sizes.erase(it) : std::next(it);
    }
    auto& blobs = MapTexArchiveBlobs();
    for (auto it = blobs.begin(); it != blobs.end();) {
        it->second.Remove(owner);
        it = it->second.Empty() ? blobs.erase(it) : std::next(it);
    }
}
