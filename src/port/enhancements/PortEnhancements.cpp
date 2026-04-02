#include "PortEnhancements.h"

#define INIT_EVENT_IDS

#include "port/ShipUtils.h"
#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"

void PortEnhancements_Init() {
  PortEnhancements_Register();

  // Cheats
  REGISTER_LISTENER(PlayerDamage, EVENT_PRIORITY_NORMAL, [](IEvent *event) {
    if (!CVarGetInteger(CVAR_PREFIX_CHEAT ".InfiniteHealth", 0))
      return;
    PlayerDamage *ev = (PlayerDamage *)event;
    *ev->damage = 0;
  });

  REGISTER_LISTENER(PlayerFPDeduct, EVENT_PRIORITY_NORMAL, [](IEvent *event) {
    if (!CVarGetInteger(CVAR_PREFIX_CHEAT ".InfiniteFlowerPoints", 0))
      return;
    event->cancelled = true;
  });

  REGISTER_LISTENER(StarPowerDeduct, EVENT_PRIORITY_NORMAL, [](IEvent *event) {
    if (!CVarGetInteger(CVAR_PREFIX_CHEAT ".MaxStarPower", 0))
      return;
    event->cancelled = true;
  });

  REGISTER_LISTENER(BadgeBPCostCheck, EVENT_PRIORITY_NORMAL, [](IEvent *event) {
    if (!CVarGetInteger(CVAR_PREFIX_CHEAT ".NoBPCost", 0))
      return;
    event->cancelled = true;
  });
}

void PortEnhancements_Register() {
  // Register engine events
  REGISTER_EVENT(GameFrameUpdate);
  REGISTER_EVENT(WorkerUpdate);
  REGISTER_EVENT(WorkerDraw);
  REGISTER_EVENT(TriggerUpdate);
  REGISTER_EVENT(TriggerActivate);
  REGISTER_EVENT(ScriptRequestUpdate);
  REGISTER_EVENT(ScriptFrameUpdate);
  REGISTER_EVENT(MessageUpdate);
  REGISTER_EVENT(MessageDrawSetup);
  REGISTER_EVENT(MessagePreDraw);
  REGISTER_EVENT(MessagePostDraw);
  REGISTER_EVENT(HudElementUpdate);
  REGISTER_EVENT(HudElementPreDraw);
  REGISTER_EVENT(HudElementPostDraw);
  REGISTER_EVENT(EntityPreUpdate);
  REGISTER_EVENT(EntityPostUpdate);
  REGISTER_EVENT(EntityPreDraw);
  REGISTER_EVENT(EntityPostDraw);
  REGISTER_EVENT(ShadowPreUpdate);
  REGISTER_EVENT(ShadowPostUpdate);
  REGISTER_EVENT(ShadowPreDraw);
  REGISTER_EVENT(ShadowPostDraw);
  REGISTER_EVENT(MusicControlPreUpdate);
  REGISTER_EVENT(MusicControlPostUpdate);
  REGISTER_EVENT(MusicControlSetSong);
  REGISTER_EVENT(AmbientSoundPreUpdate);
  REGISTER_EVENT(AmbientSoundPostUpdate);
  REGISTER_EVENT(AmbientSoundPlay);
  REGISTER_EVENT(WindowUpdate);
  REGISTER_EVENT(WindowRootPreDraw);
  REGISTER_EVENT(WindowRootPostDraw);
  REGISTER_EVENT(WindowPreDraw);
  REGISTER_EVENT(WindowPostDraw);
  REGISTER_EVENT(TheaterPreDraw);
  REGISTER_EVENT(TheaterPostDraw);
  REGISTER_EVENT(CurtainsPreDraw);
  REGISTER_EVENT(CurtainsPostDraw);
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