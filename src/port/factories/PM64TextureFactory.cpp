#include "PM64TextureFactory.h"
#include "fast/resource/type/Texture.h"
#include "spdlog/spdlog.h"
#include <sstream>
#include <iomanip>

namespace PM64 {

std::shared_ptr<Ship::IResource>
ResourceFactoryBinaryTextureV0::ReadResource(std::shared_ptr<Ship::File> file,
                                             std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto texture = std::make_shared<Fast::Texture>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    uint32_t type = reader->ReadUInt32();
    uint32_t width = reader->ReadUInt32();
    uint32_t height = reader->ReadUInt32();
    uint32_t imageDataSize = reader->ReadUInt32();

    texture->Type = (Fast::TextureType)type;
    texture->Width = static_cast<uint16_t>(width);
    texture->Height = static_cast<uint16_t>(height);
    texture->ImageDataSize = imageDataSize;

    texture->ImageData = new uint8_t[texture->ImageDataSize];
    reader->Read((char*)texture->ImageData, texture->ImageDataSize);

    return texture;
}

}
