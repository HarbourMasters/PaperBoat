// INIT_EVENT_IDS must be defined before ANY header that can transitively pull in
// ship/events/EventTypes.h, otherwise DECLARE_EVENT resolves to the extern form
// and the event ID variables are never defined.
#define INIT_EVENT_IDS

#include "PortEnhancements.h"
#include "port/save/SaveManager.h"

#include "port/ShipUtils.h"
#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"

void PortEnhancements_Init() {
    LoadGuiTextures();
    PortEnhancements_Register();
    SaveManager_Init();
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
    REGISTER_EVENT(BackgroundPreDraw);
    REGISTER_EVENT(CameraPerspective);
    REGISTER_EVENT(CameraFitViewport);
    REGISTER_EVENT(CameraSetViewport);
    REGISTER_EVENT(BattleMenuDrawReel);
    REGISTER_EVENT(VanillaBehavior);

    // Register game events
    REGISTER_EVENT(OnSaveFileSave);
    REGISTER_EVENT(OnSaveFileLoad);
    REGISTER_EVENT(OnSaveFileErase);
    REGISTER_EVENT(OnSaveGlobalsSave);
    REGISTER_EVENT(OnSaveGlobalsLoad);
    REGISTER_EVENT(OnPlayerDamageReceived);
    REGISTER_EVENT(OnPlayerFPChange);
    REGISTER_EVENT(OnPlayerSPChange);
    REGISTER_EVENT(OnPlayerBPCostCheck);
    REGISTER_EVENT(OnPostSaveFileLoad);
    REGISTER_EVENT(OnBattleEffectsRemoved);
    REGISTER_EVENT(OnBlockWindowCheck);
    REGISTER_EVENT(OnMapLoad);
}

void PortEnhancements_Exit() {
    // @port TODO
}
