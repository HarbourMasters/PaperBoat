#pragma once

#include <cstdint>
#include <memory>

#include "Romhack.h"

namespace Ship {
class Blob;
}

namespace Romhack {

// Per-hack code port. Subclass it in specific/<Id>.cpp and list <Id> in ROMHACK_PORT_LIST.
class Port {
  public:
    virtual ~Port() = default;

    // Runs at the end of FinishInit, before ShipInit, so enhancements that snapshot compiled
    // tables see the hack's values.
    virtual void ApplyDataTables() {
    }
    // Runs at ShipInit.
    virtual void Init() {
    }

  protected:
    // The hack's romhack/<name> blob, or null when the archive has none.
    static std::shared_ptr<Ship::Blob> LoadTable(const char* name);
    static int32_t ReadBE32(const uint8_t* p);
};

// The active hack's port, or null on vanilla and for hacks without code.
Port* ActivePort();

} // namespace Romhack
