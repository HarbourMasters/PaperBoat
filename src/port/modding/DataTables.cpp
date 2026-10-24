#include "DataTables.h"

#include <ship/Context.h>
#include <ship/resource/ResourceManager.h>
#include <ship/resource/type/Blob.h>

std::shared_ptr<Ship::Blob> Mod_LoadTable(const char* resourcePath) {
    auto resource = Ship::Context::GetRawInstance()->GetResourceManager()->LoadResource(resourcePath);
    return std::dynamic_pointer_cast<Ship::Blob>(resource);
}

extern "C" int32_t Mod_ReadBE32(const uint8_t* p) {
    return (int32_t) (((uint32_t) p[0] << 24) | ((uint32_t) p[1] << 16) | ((uint32_t) p[2] << 8) | p[3]);
}

extern "C" int16_t Mod_ReadBE16(const uint8_t* p) {
    return (int16_t) (((uint16_t) p[0] << 8) | p[1]);
}
