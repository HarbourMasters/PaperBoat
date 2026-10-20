#pragma once

#include <stdint.h>

#include "port/hooks/impl/EventSystem.h"

// Satella

// Fires on the game thread once Satella is connected and has accepted the player key: at startup, and again after
// the connection drops and comes back. Relay channels are subscribed again by then; rooms are joined again right
// after.
DEFINE_EVENT(SatellaConnected);

// Fires on the game thread when the connection to Satella drops. It reconnects on its own.
DEFINE_EVENT(SatellaDisconnected);
