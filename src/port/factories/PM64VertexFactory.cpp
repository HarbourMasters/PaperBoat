#include "PM64VertexFactory.h"
#include "fast/resource/type/Vertex.h"
#include "libultraship/libultra/gbi.h"

std::shared_ptr<Ship::IResource>
ResourceFactoryBinaryVertexV1::ReadResource(std::shared_ptr<Ship::File> file,
                                            std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto vertex = std::make_shared<Fast::Vertex>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    uint32_t count = reader->ReadUInt32();
    vertex->VertexList.reserve(count);

    for (uint32_t i = 0; i < count; i++) {
        Vtx data = {};
        data.v.ob[0] = reader->ReadFloat();   // float instead of int16
        data.v.ob[1] = reader->ReadFloat();
        data.v.ob[2] = reader->ReadFloat();
        data.v.flag = reader->ReadUInt16();
        data.v.tc[0] = reader->ReadInt16();
        data.v.tc[1] = reader->ReadInt16();
        data.v.cn[0] = reader->ReadUByte();
        data.v.cn[1] = reader->ReadUByte();
        data.v.cn[2] = reader->ReadUByte();
        data.v.cn[3] = reader->ReadUByte();
        vertex->VertexList.push_back(data);
    }

    return vertex;
}
