#pragma once

#include "port/hooks/impl/EventSystem.h"
#include "common_structs.h"
#include "hud_element.h"

struct DefaultWindowStyle;

typedef enum ActorStatBoostType {
    ACTOR_STAT_BOOST_ATTACK,
    ACTOR_STAT_BOOST_DEFENSE,
} ActorStatBoostType;

typedef enum PauseMenuElement {
    PAUSE_MENU_ELEMENT_BADGES_AVAILABLE_BP,
} PauseMenuElement;

// SaveManager
DEFINE_EVENT(OnSaveFileSave,
    void* saveData;
);

DEFINE_EVENT(OnSaveFileLoad,
    int32_t saveSlot;
);

DEFINE_EVENT(OnSaveFileErase,
    int32_t saveSlot;
);

DEFINE_EVENT(OnSaveGlobalsSave,
    void* saveGlobals;
);

DEFINE_EVENT(OnSaveGlobalsLoad,
    void* saveGlobals;
);

DEFINE_EVENT(OnPlayerDataClear);

// Cheats
DEFINE_EVENT(OnPlayerDamageReceived,
    int32_t* damage;
);

DEFINE_EVENT(OnPlayerFPChange,
    int32_t fpCost;
);

DEFINE_EVENT(OnPlayerSPChange,
    int32_t spCost;
);

DEFINE_EVENT(OnPlayerBPCostCheck);

// Gameplay > CutsceneSkips
DEFINE_EVENT(OnPostSaveFileLoad);

// Battle
DEFINE_EVENT(OnBattleEffectsRemoved);

DEFINE_EVENT(OnBlockWindowCheck,
    int32_t* blockWindow;
    int32_t* mashWindow;
    int32_t buttonMask;
    int32_t* consumeInput;
);

DEFINE_EVENT(OnActionCommandDifficulty,
    int32_t* difficultyLevel;
);

DEFINE_EVENT(OnPowerBounceChance,
    int32_t* hitChance;
    int32_t targetChance;
);

DEFINE_EVENT(OnStarPointDrop,
    int32_t* count;
    int32_t* level;
);

DEFINE_EVENT(OnCoinDrop,
    int32_t* count;
);

DEFINE_EVENT(OnActionCommandLoad,
    int32_t actionCommandID;
);

// Battle > Actors
DEFINE_EVENT(OnActorBlueprintLoad,
    struct ActorBlueprint** blueprint;
);

DEFINE_EVENT(OnActorCreated,
    Actor* actor;
);

DEFINE_EVENT(OnEnemyAttackDamage,
    Actor* attacker;
    int32_t* damage;
);

DEFINE_EVENT(OnPartnerAttackDamage,
    Actor* partner;
    Actor* target;
    int32_t* damage;
);

DEFINE_EVENT(OnActorDefenseCheck,
    Actor* target;
    int32_t* defenseTable;
    int32_t elementFlags;
    int32_t* defense;
);

// World
DEFINE_EVENT(OnMapLoad,
    const char* mapName;
);

DEFINE_EVENT(OnPlayerSpeedUpdate,
    float* walkSpeed;
    float* runSpeed;
);

DEFINE_EVENT(OnPlayerSpinStart,
    float* spinSpeedScale;
);

DEFINE_EVENT(OnMapReady,
    const char* mapName;
);

// Title screen
DEFINE_EVENT(OnTitleScreenTimeout,
    int32_t* nextState;
);

// Battle > Damage
DEFINE_EVENT(OnHitCheck,
    Actor* attacker;
    Actor* target;
    int32_t source;
    int32_t phase;
    int32_t* hitResult;
);

DEFINE_EVENT(OnDamageCalc,
    Actor* attacker;
    Actor* target;
    int32_t source;
    int32_t stage;
    int32_t* damage;
);

DEFINE_EVENT(OnDamageAttackerResolve,
    int32_t source;
    Actor* owner;
    Actor** attacker;
);

DEFINE_EVENT(OnAttackBegin,
    int32_t api;
    Actor* owner;
    Actor** attacker;
    int32_t* damage;
    int32_t* status;
);

DEFINE_EVENT(OnPowerBounceDamage,
    Actor* attacker;
    int32_t counter;
    int32_t* damage;
);

DEFINE_EVENT(OnDamageDefense,
    Actor* attacker;
    Actor* target;
    int32_t source;
    int32_t damage;
    int32_t* defense;
);

DEFINE_EVENT(OnActorHpChange,
    Actor* actor;
    int32_t source;
    int32_t* delta;
);

DEFINE_EVENT(OnActorDefeatCheck,
    Actor* actor;
    int32_t* defeated;
);

DEFINE_EVENT(OnDamageEventDispatch,
    Actor* target;
    int32_t source;
    int32_t* event;
);

DEFINE_EVENT(OnContactHazard,
    Actor* attacker;
    Actor* victim;
    int32_t hazard;
    int32_t* damage;
);

DEFINE_EVENT(OnContactCounter,
    Actor* attacker;
    Actor* target;
    int32_t* counter;
);

DEFINE_EVENT(OnGuardCheck,
    Actor* attacker;
    Actor* target;
    int32_t* canGuard;
);

DEFINE_EVENT(OnGuardInput,
    Actor* target;
    int32_t* result;
);

DEFINE_EVENT(OnDamagePopupKind,
    Actor* target;
    int32_t* kind;
);

DEFINE_EVENT(OnAttackStatusSelect,
    Actor* attacker;
    Actor* target;
    int32_t* status;
);

DEFINE_EVENT(OnAbilityCount,
    Actor* actor;
    int32_t ability;
    int32_t* count;
);

DEFINE_EVENT(OnAbilityEffect,
    Actor* actor;
    int32_t ability;
    int32_t* value;
);

DEFINE_EVENT(OnTurnEndRecovery,
    Actor* actor;
    int32_t* drain;
    int32_t* hp;
    int32_t* fp;
);

DEFINE_EVENT(OnActorBoost,
    Actor* actor;
    int32_t stat;
    int32_t amount;
    int32_t turns;
);

DEFINE_EVENT(OnPlayerPoisonDamage,
    int32_t* damage;
);

DEFINE_EVENT(OnStarPowerRegen,
    int32_t* amount;
);

DEFINE_EVENT(OnBattleCleanup);

typedef enum AttackSource {
    ATTACK_SOURCE_ENEMY,
    ATTACK_SOURCE_PLAYER,
    ATTACK_SOURCE_PARTNER,
    ATTACK_SOURCE_ITEM,
} AttackSource;

typedef enum HitCheckPhase {
    HIT_CHECK_TEST,
    HIT_CHECK_STRIKE,
} HitCheckPhase;

typedef enum DamageStage {
    DAMAGE_STAGE_BASE,
    DAMAGE_STAGE_AFTER_BOOSTS,
    DAMAGE_STAGE_AFTER_DEFENSE,
    DAMAGE_STAGE_AFTER_BADGES,
    DAMAGE_STAGE_GUARD,
    DAMAGE_STAGE_FINAL,
} DamageStage;

typedef enum AttackApiID {
    ATTACK_API_ENEMY_DAMAGE_TARGET,
    ATTACK_API_PLAYER_DAMAGE_ENEMY,
    ATTACK_API_PARTNER_DAMAGE_ENEMY,
    ATTACK_API_ITEM_DAMAGE_ENEMY,
    ATTACK_API_ITEM_SPOOK_ENEMY,
    ATTACK_API_ITEM_AFFLICT_ENEMY,
    ATTACK_API_ITEM_CHECK_HIT,
} AttackApiID;

typedef enum HpChangeSource {
    HP_SOURCE_ENEMY_ATTACK,
    HP_SOURCE_PLAYER_ATTACK,
    HP_SOURCE_PARTNER_ATTACK,
    HP_SOURCE_ITEM,
    HP_SOURCE_DIRECT,
    HP_SOURCE_SCRIPT_SET,
    HP_SOURCE_SCRIPT_EVENT,
    HP_SOURCE_HEAL,
    HP_SOURCE_LEVEL_UP,
    HP_SOURCE_FIELD_HAZARD,
    HP_SOURCE_FIELD_HEART,
    HP_SOURCE_FULL_RESTORE,
    HP_SOURCE_HEART_BLOCK,
    HP_SOURCE_FIELD_ITEM,
} HpChangeSource;

typedef enum ContactHazard {
    CONTACT_HAZARD_SPIKE,
    CONTACT_HAZARD_SPIKE_TOP,
    CONTACT_HAZARD_EXPLODE,
    CONTACT_HAZARD_FIRE,
    CONTACT_HAZARD_SHOCK,
    CONTACT_HAZARD_COUNTER,
} ContactHazard;

typedef enum ContactCounter {
    CONTACT_COUNTER_NONE,
    CONTACT_COUNTER_SHOCK,
    CONTACT_COUNTER_GUARD,
} ContactCounter;

typedef enum GuardResult {
    GUARD_RESULT_NONE,
    GUARD_RESULT_GUARD,
    GUARD_RESULT_SUPERGUARD,
} GuardResult;

typedef enum DamagePopupKind {
    DAMAGE_POPUP_PRIMARY,
    DAMAGE_POPUP_NEXT,
} DamagePopupKind;

typedef enum ActorStatID {
    ACTOR_STAT_ATTACK_BOOST,
    ACTOR_STAT_DEFENSE_BOOST,
    ACTOR_STAT_SCALE,
    ACTOR_STAT_STATUS_FLAGS,
    ACTOR_STAT_GLOW,
    ACTOR_STAT_KO_TURNS,
    ACTOR_STAT_IDLE_PALETTE,
} ActorStatID;

typedef enum StatusPhase {
    STATUS_PHASE_PLAYER_TURN_DAMAGE,
    STATUS_PHASE_PLAYER_TURN,
    STATUS_PHASE_PARTNER_TURN,
    STATUS_PHASE_ENEMY_TURN,
    STATUS_PHASE_TURN_END,
    STATUS_PHASE_ACTION_END,
    STATUS_PHASE_PARTNER_TURN_END,
} StatusPhase;

typedef enum BuffsClearReason {
    BUFFS_CLEAR_SCRIPT,
    BUFFS_CLEAR_DISPEL,
    BUFFS_CLEAR_ALL_STATUS,
} BuffsClearReason;

typedef enum ActorBuffMask {
    ACTOR_BUFF_BOOSTS = 1,
    ACTOR_BUFF_STATIC = 2,
    ACTOR_BUFF_TRANSPARENT = 4,
} ActorBuffMask;

typedef enum StatusIconDrawID {
    STATUS_ICON_PERIL,
    STATUS_ICON_DANGER,
} StatusIconDrawID;

typedef enum TurnOrderDecision {
    TURN_ORDER_PLAYER_SKIPPED,
    TURN_ORDER_SKIP_PARTNER_TURN,
    TURN_ORDER_WHO_ACTS_FIRST,
    TURN_ORDER_PLAYER_IN_FRONT,
    TURN_ORDER_CAN_SWAP,
    TURN_ORDER_CAN_CHANGE_PARTNER,
    TURN_ORDER_FIRST_STRIKE,
    TURN_ORDER_FLEE_ENDS_TEAM_TURN,
} TurnOrderDecision;

typedef enum TurnSkipResult {
    TURN_SKIP_MARK_USED,
    TURN_SKIP_KEEP_TURN,
    TURN_SKIP_RESTART,
} TurnSkipResult;

typedef enum PerilState {
    PERIL_STATE_NONE,
    PERIL_STATE_DANGER,
    PERIL_STATE_PERIL,
} PerilState;

typedef enum PartnerChangePhase {
    PARTNER_CHANGE_LEAVE,
    PARTNER_CHANGE_ENTER,
} PartnerChangePhase;

typedef enum BattleInitStage {
    BATTLE_INIT_BEGIN,
    BATTLE_INIT_END,
    BATTLE_INIT_SECTION_LOADED,
} BattleInitStage;

typedef enum BattleScriptLoadKind {
    BATTLE_SCRIPT_LOAD_MOVE,
    BATTLE_SCRIPT_LOAD_ITEM,
    BATTLE_SCRIPT_LOAD_STAR_POWER,
} BattleScriptLoadKind;

typedef enum BattleCelebrationPhase {
    BATTLE_CELEBRATION_AWARD,
    BATTLE_CELEBRATION_JINGLE,
    BATTLE_CELEBRATION_WALK_OFF_BEGIN,
    BATTLE_CELEBRATION_WALK_OFF_STEP,
} BattleCelebrationPhase;

typedef struct BattleCelebration {
    int32_t starPoints;
    int32_t walkOffAnim;
    float playerStepX;
    float partnerStepX;
} BattleCelebration;

typedef enum BattleMenuId {
    BATTLE_MENU_WHEEL,
    BATTLE_MENU_STRATEGIES,
    BATTLE_MENU_MOVES,
    BATTLE_MENU_PARTNER_LIST,
    BATTLE_MENU_COUNT,
} BattleMenuId;

typedef enum MoveFPCostUse {
    MOVE_FP_ENABLE,
    MOVE_FP_DEDUCT,
} MoveFPCostUse;

typedef enum PopupMenuPhase {
    POPUP_MENU_OPENED,
    POPUP_MENU_LAID_OUT,
    POPUP_MENU_CLOSED,
} PopupMenuPhase;

typedef struct PopupMenuLayout {
    int32_t contentScissorWidth;
    int32_t partnerLevelX;
    int32_t partnerScissorWidth;
    int32_t arrowOffsetX;
} PopupMenuLayout;

typedef enum PopupMenuText {
    POPUP_TEXT_SELL_PROMPT_TITLE,
    POPUP_TEXT_ALREADY_HAVE_PARTNER,
} PopupMenuText;

typedef enum PauseMenuPhase {
    PAUSE_MENU_OPEN,
    PAUSE_MENU_CLOSE,
} PauseMenuPhase;

typedef enum StatusBarPhase {
    STATUS_BAR_PHASE_INIT,
    STATUS_BAR_PHASE_SYNC,
    STATUS_BAR_PHASE_DRAW,
} StatusBarPhase;

typedef enum PauseBadgeListReason {
    PAUSE_BADGE_LIST_OPEN,
    PAUSE_BADGE_LIST_REBUILD,
    PAUSE_BADGE_LIST_TAB_SWITCHED,
} PauseBadgeListReason;

typedef struct PauseBadgeList {
    int16_t* ids;
    int32_t count;
    int32_t capacity;
    int32_t tab;
} PauseBadgeList;

typedef struct PauseBadgesView {
    const int16_t* itemIds;
    int32_t itemIdsCount;
    const PauseItemPage* pages;
    int32_t pagesCount;
    const int32_t* iconIDs;
    int32_t iconIDsCount;
    const int32_t* currentPage;
    const int32_t* selectedIndex;
    const int32_t* level;
    const int32_t* currentTab;
    const int32_t* currentScrollPos;
    const int32_t* targetScrollPos;
    const int32_t* showNotEnoughBP;
} PauseBadgesView;

typedef struct PauseStatsView {
    const int32_t* iconIDs;
    int32_t iconIDsCount;
} PauseStatsView;

typedef struct ModPanelDraw {
    MenuPanel* panel;
    int32_t x;
    int32_t y;
    int32_t width;
    int32_t height;
    int32_t opacity;
    int32_t darkening;
} ModPanelDraw;

typedef struct StatLimits {
    int32_t levelCap;
    int32_t hpCap;
    int32_t fpCap;
    int32_t bpCap;
    int32_t levelUpHpFpCap;
    int32_t levelUpHpFpClamp;
} StatLimits;

#define STAT_LIMITS_VANILLA { 27, 75, 75, 30, 50, 75 }

typedef enum ItemSpawnSource {
    ITEM_SPAWN_SOURCE_ITEM_BLOCK,
    ITEM_SPAWN_SOURCE_ENEMY_DROP,
} ItemSpawnSource;

typedef enum PartnerAnimContext {
    PARTNER_ANIM_CONTEXT_WORLD_IDLE,
    PARTNER_ANIM_CONTEXT_BATTLE_MENU_THINK,
    PARTNER_ANIM_CONTEXT_BATTLE_MENU_CHOSEN,
} PartnerAnimContext;

typedef struct PlayerMovementConstraint {
    bool lockWalkZ;
} PlayerMovementConstraint;

DEFINE_EVENT(OnActorStat,
    Actor* actor;
    int32_t stat;
    int32_t* value;
);

DEFINE_EVENT(OnBuffsClear,
    Actor* actor;
    int32_t reason;
    int32_t* mask;
);

DEFINE_EVENT(OnInflictStatus,
    Actor* actor;
    int32_t status;
    int32_t* duration;
    int32_t* immune;
);

DEFINE_EVENT(OnStatusChance,
    Actor* actor;
    int32_t status;
    int32_t* chance;
);

DEFINE_EVENT(OnStatusTick,
    Actor* actor;
    int32_t phase;
);

DEFINE_EVENT(OnStatusIconDraw,
    int32_t iconID;
    int32_t icon;
    const Vec3f* anchor;
    int32_t* x;
    int32_t* y;
);

DEFINE_EVENT(OnTurnOrder,
    int32_t decision;
    int32_t* value;
);

DEFINE_EVENT(OnActorAnim,
    Actor* actor;
    ActorPart* part;
    int32_t statusKey;
    int32_t* anim;
);

DEFINE_EVENT(OnPerilState,
    Actor* actor;
    int32_t* peril;
);

DEFINE_EVENT(OnPartnerChange,
    int32_t phase;
    int32_t partnerID;
);

DEFINE_EVENT(OnStatusAfflictedNotice,
    Actor* player;
    Actor* partner;
    int32_t* status;
    int32_t* camPreset;
);

DEFINE_EVENT(OnBattleInit,
    int32_t stage;
);

DEFINE_EVENT(OnBattleMenusEnabled,
    int32_t* enabledMenus;
);

DEFINE_EVENT(OnBattleStateChanged,
    int32_t prev;
    int32_t next;
);

DEFINE_EVENT(OnBattleStateUpdate,
    int32_t state;
);

DEFINE_EVENT(OnBattleCelebration,
    int32_t phase;
    BattleCelebration* celebration;
);

DEFINE_EVENT(OnBattleScriptLoad,
    int32_t kind;
    int32_t id;
    EvtScript** script;
);

DEFINE_EVENT(OnBattlePartnerSelect,
    int32_t* partnerID;
);

DEFINE_EVENT(OnMoveFPCost,
    Actor* user;
    int32_t moveID;
    int32_t row;
    int32_t use;
    int32_t* cost;
);

DEFINE_EVENT(OnMoveCostDisplay,
    Actor* user;
    int32_t moveID;
    int32_t row;
    int32_t* cost;
    int32_t* discount;
    int32_t* discountColor;
);

DEFINE_EVENT(OnBattleBadgeMenuEntry,
    int32_t submenu;
    int32_t entryCount;
    int32_t* badgeID;
);

DEFINE_EVENT(OnBattleDefendBegin,
    Evt* script;
);

DEFINE_EVENT(OnBattleDefendEnd);

DEFINE_EVENT(OnBattleMenuOpen,
    int32_t who;
);

DEFINE_EVENT(OnBattleMainMenuInput);

DEFINE_EVENT(OnSwapRefused,
    int32_t* msgIndex;
    int32_t* msgArg;
);

DEFINE_EVENT(OnTargetName,
    int32_t actorID;
    int32_t* msgID;
);

DEFINE_EVENT(OnBattleMenuBuilt,
    int32_t menu;
    int32_t who;
    int32_t submenu;
    int32_t* count;
    int32_t* initialPos;
);

DEFINE_EVENT(OnBattleMenuSelect,
    int32_t menu;
    int32_t who;
    int32_t index;
);

DEFINE_EVENT(OnBattleMenuDrawEntry,
    int32_t menu;
    int32_t index;
    int32_t x;
    int32_t y;
    int32_t alpha;
);

DEFINE_EVENT(OnBattleMenuErrorText,
    int32_t menu;
    int32_t index;
    int32_t* msgID;
);

DEFINE_EVENT(OnBattleMenuCostStyle,
    int32_t index;
    int32_t* palette;
);

DEFINE_EVENT(OnBattleMenuCreated,
    int32_t menu;
);

DEFINE_EVENT(OnBattleMenuDestroyed,
    int32_t menu;
);

DEFINE_EVENT(OnBattlePopupMessage,
    int32_t index;
    int32_t* layout;
    int32_t* msgID;
);

DEFINE_EVENT(OnPopupMenu,
    int32_t phase;
    PopupMenu* menu;
);

DEFINE_EVENT(OnPopupMenuLayout,
    PopupMenu* menu;
    PopupMenuLayout* layout;
);

DEFINE_EVENT(OnPopupMenuDrawEntry,
    PopupMenu* menu;
    int32_t index;
    int32_t x;
    int32_t y;
);

DEFINE_EVENT(OnPopupMenuText,
    PopupMenu* menu;
    int32_t text;
    int32_t* msgID;
);

DEFINE_EVENT(OnPopupMenuChoose,
    PopupMenu* menu;
    int32_t index;
);

// Pause
DEFINE_EVENT(OnBadgeBPCost,
    int32_t badgeID;
    int32_t* cost;
);

DEFINE_EVENT(OnPauseMenuDrawElement,
    int32_t elementID;
);

DEFINE_EVENT(OnPauseMenu,
    int32_t phase;
    MenuPanel** panels;
    int32_t count;
);

DEFINE_EVENT(OnStatusBarPanel,
    int32_t phase;
    int32_t x;
    int32_t y;
);

DEFINE_EVENT(OnPauseBadgeList,
    int32_t reason;
    PauseBadgeList* list;
);

DEFINE_EVENT(OnPauseBadgeEquipped,
    int32_t listIndex;
    int32_t badgeID;
    int32_t* equipped;
);

DEFINE_EVENT(OnPauseBadgeTabButtons,
    int32_t* buttons;
);

DEFINE_EVENT(OnPauseBadgesView,
    const PauseBadgesView* view;
);

DEFINE_EVENT(OnPauseStatsView,
    const PauseStatsView* view;
);

DEFINE_EVENT(OnPauseLabelPos,
    int32_t label;
    int32_t* x;
    int32_t* y;
);

DEFINE_EVENT(OnPausePartnersOverlay,
    const ModPanelDraw* draw;
    int32_t partnerID;
);

DEFINE_EVENT(OnStatLimits,
    StatLimits* limits;
);

DEFINE_EVENT(OnMaxStatsRecalculated);

DEFINE_EVENT(OnSpriteComponentPalette,
    struct SpriteComponent** compList;
    int32_t compIndex;
    int32_t overridePalette;
    int32_t* palette;
);

DEFINE_EVENT(OnWindowStyle,
    int32_t styleID;
    struct DefaultWindowStyle** style;
);

DEFINE_EVENT(OnFileSlotHighlightStyle,
    int32_t slot;
    WindowStyleCustom** body;
    WindowStyleCustom** title;
);

DEFINE_EVENT(OnFileMenuModLabel,
    char* label;
    int32_t size;
);

DEFINE_EVENT(OnMessageLoad,
    uint32_t msgID;
    uint8_t** data;
);

DEFINE_EVENT(OnMessageSpeed,
    MessagePrintState* printer;
    int32_t* charsPerFrame;
    int32_t* skip;
);

DEFINE_EVENT(OnMessageOpen,
    MessagePrintState* printer;
);

DEFINE_EVENT(OnBgmSong,
    int32_t playerIndex;
    int32_t* songID;
);

DEFINE_EVENT(OnItemSpawnPick,
    int32_t source;
    Entity* entity;
    struct Enemy* enemy;
    int32_t* itemID;
);

DEFINE_EVENT(OnItemSpawned,
    int32_t source;
    Entity* entity;
    struct Enemy* enemy;
    int32_t itemID;
    int32_t itemEntityIndex;
);

DEFINE_EVENT(OnScriptResolve,
    EvtScript** script;
);

DEFINE_EVENT(OnPlayerMovementConstraint,
    PlayerMovementConstraint* constraint;
);

DEFINE_EVENT(OnPlayerLandAnim,
    int32_t* anim;
);

DEFINE_EVENT(OnPlayerIdleTick,
    int32_t* idleTimer;
    int32_t* anim;
);

DEFINE_EVENT(OnPlayerIdleAnim,
    int32_t* anim;
);

DEFINE_EVENT(OnPartnerAnim,
    int32_t context;
    int32_t partnerID;
    int32_t* anim;
);

DEFINE_EVENT(OnPlayerSpriteAnim,
    int32_t* anim;
);

DEFINE_EVENT(OnStatusBarUpdated);

DEFINE_EVENT(OnChangeMapInit);

DEFINE_EVENT(OnChangeMapStep,
    int32_t state;
);
