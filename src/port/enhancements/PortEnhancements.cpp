#include "PortEnhancements.h"

#define INIT_EVENT_IDS

#include "port/hooks/Events.h"
#include "port/ShipUtils.h"
#include "port/ui/cvar_prefixes.h"

void PortEnhancements_Init() {
  PortEnhancements_Register();

  // Cheats
  REGISTER_LISTENER(PlayerDamage, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
    if (!CVarGetInteger(CVAR_PREFIX_CHEAT ".InfiniteHealth", 0)) return;
    PlayerDamage* ev = (PlayerDamage*)event;
    *ev->damage = 0;
  });

  REGISTER_LISTENER(PlayerFPDeduct, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
    if (!CVarGetInteger(CVAR_PREFIX_CHEAT ".InfiniteFlowerPoints", 0)) return;
    event->cancelled = true;
  });

  REGISTER_LISTENER(StarPowerDeduct, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
    if (!CVarGetInteger(CVAR_PREFIX_CHEAT ".MaxStarPower", 0)) return;
    event->cancelled = true;
  });

  REGISTER_LISTENER(BadgeBPCostCheck, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
    if (!CVarGetInteger(CVAR_PREFIX_CHEAT ".NoBPCost", 0)) return;
    event->cancelled = true;
  });
}

void PortEnhancements_Register() {
  // Register engine events
  REGISTER_EVENT(GameFrameUpdate);
  REGISTER_EVENT(VanillaBehavior);

  // Register game events
  REGISTER_EVENT(PlayerDamage);
  REGISTER_EVENT(PlayerFPDeduct);
  REGISTER_EVENT(StarPowerDeduct);
  REGISTER_EVENT(BadgeBPCostCheck);
}

void PortEnhancements_Exit() {
  // @port TODO
}