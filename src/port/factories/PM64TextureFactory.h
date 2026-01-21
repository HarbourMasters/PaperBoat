#pragma once

#include "ship/resource/ResourceFactoryBinary.h"

namespace PM64 {
class ResourceFactoryBinaryTextureV0 : public Ship::ResourceFactoryBinary {
  public:
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file,
                                                  std::shared_ptr<Ship::ResourceInitData> initData) override;
};
}
