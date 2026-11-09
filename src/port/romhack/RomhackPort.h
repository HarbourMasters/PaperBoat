#pragma once

#include "Romhack.h"

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
};

// The active hack's port, or null on vanilla and for hacks without code.
Port* ActivePort();

} // namespace Romhack
