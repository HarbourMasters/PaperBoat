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
    REGISTER_EVENT(MessageTextFilterSet);
    REGISTER_EVENT(HudElementUpdate);
    REGISTER_EVENT(HudElementPreDraw);
    REGISTER_EVENT(HudElementPostDraw);
    REGISTER_EVENT(SpriteComponentPreDraw);
    REGISTER_EVENT(SpriteShadingPreDraw);
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
    REGISTER_EVENT(OnPlayerDataClear);
    REGISTER_EVENT(OnBattleEffectsRemoved);
    REGISTER_EVENT(OnBlockWindowCheck);
    REGISTER_EVENT(OnActionCommandDifficulty);
    REGISTER_EVENT(OnPowerBounceChance);
    REGISTER_EVENT(OnStarPointDrop);
    REGISTER_EVENT(OnCoinDrop);
    REGISTER_EVENT(OnActionCommandLoad);
    REGISTER_EVENT(OnActorBlueprintLoad);
    REGISTER_EVENT(OnActorCreated);
    REGISTER_EVENT(OnEnemyAttackDamage);
    REGISTER_EVENT(OnPartnerAttackDamage);
    REGISTER_EVENT(OnActorDefenseCheck);
    REGISTER_EVENT(OnMapLoad);
    REGISTER_EVENT(OnPlayerSpeedUpdate);
    REGISTER_EVENT(OnPlayerSpinStart);
    REGISTER_EVENT(OnMapReady);
    REGISTER_EVENT(OnTitleScreenTimeout);
    REGISTER_EVENT(OnHitCheck);
    REGISTER_EVENT(OnDamageCalc);
    REGISTER_EVENT(OnDamageAttackerResolve);
    REGISTER_EVENT(OnAttackBegin);
    REGISTER_EVENT(OnPowerBounceDamage);
    REGISTER_EVENT(OnDamageDefense);
    REGISTER_EVENT(OnActorHpChange);
    REGISTER_EVENT(OnActorDefeatCheck);
    REGISTER_EVENT(OnDamageEventDispatch);
    REGISTER_EVENT(OnContactHazard);
    REGISTER_EVENT(OnContactCounter);
    REGISTER_EVENT(OnGuardCheck);
    REGISTER_EVENT(OnGuardInput);
    REGISTER_EVENT(OnDamagePopupKind);
    REGISTER_EVENT(OnAttackStatusSelect);
    REGISTER_EVENT(OnAbilityCount);
    REGISTER_EVENT(OnAbilityEffect);
    REGISTER_EVENT(OnTurnEndRecovery);
    REGISTER_EVENT(OnActorBoost);
    REGISTER_EVENT(OnPlayerPoisonDamage);
    REGISTER_EVENT(OnStarPowerRegen);
    REGISTER_EVENT(OnBattleCleanup);
    REGISTER_EVENT(OnActorStat);
    REGISTER_EVENT(OnBuffsClear);
    REGISTER_EVENT(OnInflictStatus);
    REGISTER_EVENT(OnStatusChance);
    REGISTER_EVENT(OnStatusTick);
    REGISTER_EVENT(OnStatusIconDraw);
    REGISTER_EVENT(OnTurnOrder);
    REGISTER_EVENT(OnActorAnim);
    REGISTER_EVENT(OnPerilState);
    REGISTER_EVENT(OnPartnerChange);
    REGISTER_EVENT(OnStatusAfflictedNotice);
    REGISTER_EVENT(OnBattleInit);
    REGISTER_EVENT(OnBattleMenusEnabled);
    REGISTER_EVENT(OnBattleStateChanged);
    REGISTER_EVENT(OnBattleStateUpdate);
    REGISTER_EVENT(OnBattleCelebration);
    REGISTER_EVENT(OnBattleScriptLoad);
    REGISTER_EVENT(OnBattlePartnerSelect);
    REGISTER_EVENT(OnMoveFPCost);
    REGISTER_EVENT(OnMoveCostDisplay);
    REGISTER_EVENT(OnBattleBadgeMenuEntry);
    REGISTER_EVENT(OnBattleDefendBegin);
    REGISTER_EVENT(OnBattleDefendEnd);
    REGISTER_EVENT(OnBattleMenuOpen);
    REGISTER_EVENT(OnBattleMainMenuInput);
    REGISTER_EVENT(OnSwapRefused);
    REGISTER_EVENT(OnTargetName);
    REGISTER_EVENT(OnBattleMenuBuilt);
    REGISTER_EVENT(OnBattleMenuSelect);
    REGISTER_EVENT(OnBattleMenuDrawEntry);
    REGISTER_EVENT(OnBattleMenuErrorText);
    REGISTER_EVENT(OnBattleMenuCostStyle);
    REGISTER_EVENT(OnBattleMenuCreated);
    REGISTER_EVENT(OnBattleMenuDestroyed);
    REGISTER_EVENT(OnBattlePopupMessage);
    REGISTER_EVENT(OnPopupMenu);
    REGISTER_EVENT(OnPopupMenuLayout);
    REGISTER_EVENT(OnPopupMenuDrawEntry);
    REGISTER_EVENT(OnPopupMenuText);
    REGISTER_EVENT(OnPopupMenuChoose);
    REGISTER_EVENT(OnBadgeBPCost);
    REGISTER_EVENT(OnPauseMenuDrawElement);
    REGISTER_EVENT(OnPauseMenu);
    REGISTER_EVENT(OnStatusBarPanel);
    REGISTER_EVENT(OnPauseBadgeList);
    REGISTER_EVENT(OnPauseBadgeEquipped);
    REGISTER_EVENT(OnPauseBadgeTabButtons);
    REGISTER_EVENT(OnPauseBadgesView);
    REGISTER_EVENT(OnPauseStatsView);
    REGISTER_EVENT(OnPauseLabelPos);
    REGISTER_EVENT(OnPausePartnersOverlay);
    REGISTER_EVENT(OnStatLimits);
    REGISTER_EVENT(OnMaxStatsRecalculated);
    REGISTER_EVENT(OnSpriteComponentPalette);
    REGISTER_EVENT(OnWindowStyle);
    REGISTER_EVENT(OnFileSlotHighlightStyle);
    REGISTER_EVENT(OnFileMenuModLabel);
    REGISTER_EVENT(OnMessageLoad);
    REGISTER_EVENT(OnMessageSpeed);
    REGISTER_EVENT(OnMessageOpen);
    REGISTER_EVENT(OnBgmSong);
    REGISTER_EVENT(OnItemSpawnPick);
    REGISTER_EVENT(OnItemSpawned);
    REGISTER_EVENT(OnScriptResolve);
    REGISTER_EVENT(OnPlayerMovementConstraint);
    REGISTER_EVENT(OnPlayerLandAnim);
    REGISTER_EVENT(OnPlayerIdleTick);
    REGISTER_EVENT(OnPlayerIdleAnim);
    REGISTER_EVENT(OnPartnerAnim);
    REGISTER_EVENT(OnPlayerSpriteAnim);
    REGISTER_EVENT(OnStatusBarUpdated);
    REGISTER_EVENT(OnChangeMapInit);
    REGISTER_EVENT(OnChangeMapStep);
}

void PortEnhancements_Exit() {
    // @port TODO
}
