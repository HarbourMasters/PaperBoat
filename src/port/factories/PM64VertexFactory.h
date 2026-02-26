#pragma once

#include "ship/resource/ResourceFactoryBinary.h"

// V1 Vertex factory: reads float ob[] (GBI_FLOATS format)
// V0 is handled by libultraship's built-in ResourceFactoryBinaryVertexV0
class ResourceFactoryBinaryVertexV1 final : public Ship::ResourceFactoryBinary {
  public:
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file,
                                                  std::shared_ptr<Ship::ResourceInitData> initData) override;
};
