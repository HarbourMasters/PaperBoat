#ifdef ENABLE_SCRIPTING

#include "port/api/texture.h"

#include "port/ShipInit.hpp"
#include "port/api/ModOwner.hpp"

#include <fast/resource/type/Texture.h>
#include <ship/Context.h>
#include <ship/resource/File.h>
#include <ship/resource/ResourceManager.h>
#include <ship/resource/archive/ArchiveManager.h>
#include <spdlog/spdlog.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

extern "C" void GameEngine_InvalidateTextureCache(const void* addr);

namespace {

// What each mod loaded, kept alive until it unloads.
std::map<std::string, std::vector<std::shared_ptr<void>>> sHeld;

std::string StripPrefix(const char* path) {
    const std::string text = path;
    return text.rfind("__OTR__", 0) == 0 ? text.substr(7) : text;
}

void Hold(std::shared_ptr<void> resource) {
    sHeld[ModOwner::Current()].push_back(std::move(resource));
}

void InitTextureApi() {
    ModOwner::AddReleaser([](const std::string& mod) { sHeld.erase(mod); });
}

RegisterShipInitFunc sInitTextureApi(InitTextureApi);

} // namespace

extern "C" const void* C_LoadFile(const char* path, uint32_t* size) {
    if (path == nullptr) {
        return nullptr;
    }
    auto archives = Ship::Context::GetRawInstance()->GetResourceManager()->GetArchiveManager();
    auto file = archives->LoadFile(StripPrefix(path));
    if (file == nullptr || !file->IsLoaded || file->Buffer == nullptr) {
        return nullptr;
    }
    if (size != nullptr) {
        *size = (uint32_t) file->Buffer->size();
    }
    const void* data = file->Buffer->data();
    Hold(file);
    return data;
}

extern "C" int C_LoadTexture(const char* path, C_TextureInfo* info) {
    if (path == nullptr || info == nullptr) {
        return 0;
    }
    auto resource = Ship::Context::GetRawInstance()->GetResourceManager()->LoadResource(StripPrefix(path), true);
    auto texture = std::dynamic_pointer_cast<Fast::Texture>(resource);
    if (texture == nullptr || texture->ImageData == nullptr) {
        SPDLOG_ERROR("Texture: {} is not a texture", path);
        return 0;
    }
    info->width = texture->Width;
    info->height = texture->Height;
    info->format = (C_TextureFormat) texture->Type;
    info->data = texture->ImageData;
    info->size = texture->ImageDataSize;
    Hold(texture);
    return 1;
}

extern "C" void C_InvalidateTexture(const void* address) {
    GameEngine_InvalidateTextureCache(address);
}

#endif
