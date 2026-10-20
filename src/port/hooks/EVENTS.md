# PaperBoat Event Reference

The game fires events with `CALL_EVENT` and its cancellable variants, and mods and port code listen with
`REGISTER_LISTENER`. Events are declared in `src/port/hooks/list/EngineEvent.h` and `GameEvent.h`. They fire on the
game thread, except `EngineReady`, which fires on the main thread before the game thread starts.

**Order**: listeners run from `EVENT_PRIORITY_LOW` to `EVENT_PRIORITY_HIGH`, so a `HIGH` listener runs last and has
the final say over pointer fields. Among listeners of the same priority, the one registered last runs first, so a mod's
listener runs before the port's own.

**Cancellable events**: a listener sets `event->Cancelled = true`. What that does depends on how the game fires the
event, and is noted per event:
- _(cancellable)_: the game skips its own code for this event.
- _(cancellable, replaces)_: the game uses the listener's `result` instead of running its own code.
- _(cancellable, skips item)_: the game skips this element and goes on with the next.
- _(cancellable, returns)_: the game stops the function the event fires in.

**Pointer fields**: a field such as `int32_t* damage` lets listeners change the value the game goes on with. Write
`*ev->damage`, no need to cancel.

**Polled events**: events marked _(polled)_ compare the game with a snapshot once per frame while a file is in play
(from `OnSaveFileStart` until the next file load, outside the title demo). They fire on the frame after the change.

```c
#include "port/hooks/Events.h"

REGISTER_LISTENER(OnCoinsChanged, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
    OnCoinsChanged* ev = (OnCoinsChanged*) event;
    // read, change through pointer fields, or cancel
});
```

---

## Engine Events

### `EngineReady`
Fires once at startup, after every event is registered and every mod's `ModInit` has run, before the game starts.

---

### `GameFrameUpdate`
Fires at the start of every game frame, in every game mode.

---

### `WorkerUpdate`
```c
Worker* worker;
```
Fires before a worker updates. _(cancellable)_: the worker doesn't update this frame.

---

### `WorkerDraw`
```c
Worker* worker;
WorkerDrawMode mode; // WORKER_DRAW_MODE_SCENE, _FRONT_UI or _BACK_UI
```
Fires before a worker draws in the scene, the front UI or the back UI. _(cancellable)_: it isn't drawn.

---

### `ScriptRequestUpdate`
```c
Evt* script;
```
Fires when an EVT script is about to run this frame. _(cancellable)_: it doesn't run this frame.

---

### `ScriptFrameUpdate`
```c
Evt* script;
int32_t* status; // EVT_CMD_RESULT_* of the command
```
Fires before each EVT command a script runs. _(cancellable)_: the command isn't run, and `*status` is used as its
result.

---

### `MessageUpdate`
```c
MessagePrintState* message;
```
Fires before a message box updates. _(cancellable, skips item)_: it doesn't update this frame.

---

### `MessageDrawSetup`
```c
MessagePrintState* message;
```
Fires as a message box starts drawing. _(cancellable, skips item)_: it isn't drawn.

---

### `MessagePreDraw`
```c
MessagePrintState* message;
```
Fires before a message box's contents draw. _(cancellable, skips item)_: they aren't drawn.

---

### `MessagePostDraw`
```c
MessagePrintState* message;
```
Fires after a message box drew.

---

### `MessageTextFilterSet`
Fires when message drawing sets up its texture filtering, so port code can override it.

---

### `MessageLookup`
```c
int32_t msgID;
uint8_t* data; // set to encoded text to use it instead
```
Fires whenever the game reads the text of a message, for display, measuring or variables. Leaving `data` NULL keeps the
game's text. The message API (`src/port/api/message.h`) answers it for mod messages and overrides.

---

### `HudElementUpdate`
```c
HudElement* element;
int32_t* result;
```
Fires before a HUD element runs its script. _(cancellable, replaces)_: the update returns `*result`.

---

### `HudElementPreDraw`
```c
HudElement* element;
int16_t* texSizeX; int16_t* texSizeY;
int16_t* drawSizeX; int16_t* drawSizeY;
int16_t* offsetX; int16_t* offsetY;
int32_t* clamp; int32_t* dropShadow;
```
Fires before a HUD element draws, with its size and offsets. _(cancellable, returns)_: it isn't drawn.

---

### `HudElementPostDraw`
```c
HudElement* element;
int16_t texSizeX; int16_t texSizeY;
int16_t drawSizeX; int16_t drawSizeY;
int16_t offsetX; int16_t offsetY;
int32_t clamp; int32_t dropShadow;
```
Fires after a HUD element drew.

---

### `SpriteComponentPreDraw`
```c
uint32_t* imgfxFlags; // IMGFX_FLAG_* used for the component
```
Fires before a sprite component draws.

---

### `SpriteShadingPreDraw`
Fires before a shaded sprite's palette is set up.

---

### `MusicControlPreUpdate`
```c
MusicControlData* musicControl;
```
Fires before a music player updates. _(cancellable, skips item)_: it doesn't update this frame.

---

### `MusicControlPostUpdate`
```c
MusicControlData* musicControl;
```
Fires after a music player updated.

---

### `MusicControlSetSong`
```c
MusicControlData* music;
int32_t* songID;
int32_t* variation;
int32_t* fadeOutTime;
int16_t* volume;
int32_t* result;
```
Fires when the game asks for a song. Change the song through the pointers. _(cancellable, replaces)_: the request
returns `*result` without playing anything.

---

### `AmbientSoundPreUpdate`
```c
AmbientSoundSettings* settings;
```
Fires before ambient sound updates. _(cancellable, returns)_: it doesn't update this frame.

---

### `AmbientSoundPostUpdate`
```c
AmbientSoundSettings* settings;
```
Fires after ambient sound updated.

---

### `AmbientSoundPlay`
```c
AmbientSoundSettings* settings;
int32_t* soundID;
int32_t* fadeTime;
int32_t* result;
```
Fires when the game starts an ambient sound. _(cancellable, replaces)_: it returns `*result` without playing.

---

### `BackgroundPreDraw`
```c
int32_t bgRenderState; // BACKGROUND_RENDER_STATE_*
```
Fires before the paused-game background draws. _(cancellable, returns)_: it isn't drawn.

---

### `CameraPerspective`
```c
s32 camID;
Camera* camera;
f32* aspect;
```
Fires as a camera's projection is built. Change `*aspect` for a different aspect ratio.

---

### `CameraFitViewport`
```c
s32 camID;
Camera* camera;
```
Fires as a camera renders, to fit its viewport to the window.

---

### `CameraSetViewport`
```c
s32 camID;
s16* x; s16* y; s16* width; s16* height;
```
Fires when the game sets a camera's viewport. Change it through the pointers.

---

### `BattleMenuDrawReel`
```c
s32 hid; // HUD element of the menu icon
s32 x;
s32 y;
```
Fires as the battle menu draws each icon of its reel.

---

## Game Events

### `OnSaveFileLoad`
```c
int32_t saveSlot;
```
Fires when the game loads a save slot, for the file menu's previews as well as for play. _(cancellable)_: the game
doesn't read flash; the port reads its JSON saves this way.

---

### `OnPostSaveFileLoad`
Fires after the port read a save slot from disk.

---

### `OnSaveFileStart`
```c
int32_t saveSlot;
```
Fires when the player starts playing the loaded file, right after its data was unpacked into the game. Mod save data
(`src/port/api/savedata.h`) is ready.

---

### `OnSaveFileCreate`
```c
int32_t saveSlot;
```
Fires when the file menu creates a new file, before it is first written.

---

### `OnSaveFileSave`
```c
void* saveData; // SaveData being written
```
Fires when the game saves. _(cancellable)_: the game doesn't write flash; the port writes its JSON saves this way.

---

### `OnSaveFileErase`
```c
int32_t saveSlot;
```
Fires when the file menu erases a file. _(cancellable)_: the game doesn't erase flash.

---

### `OnSaveGlobalsSave`
```c
void* saveGlobals;
```
Fires when the game saves the settings shared by all files. _(cancellable)_: it doesn't write flash.

---

### `OnSaveGlobalsLoad`
```c
void* saveGlobals;
```
Fires when the game loads the settings shared by all files. _(cancellable)_: it doesn't read flash.

---

### `OnMapLoad`
```c
const char* mapName;
```
Fires as a map starts loading, before its assets and scripts.

---

### `OnMapReady`
```c
const char* mapName;
```
Fires once a map has loaded and its main script started. A good time to start a mod's scripts with
`C_StartScript`.

---

### `OnPlayerSpeedUpdate`
```c
float* walkSpeed;
float* runSpeed;
```
Fires every frame as the player's movement speeds are set.

---

### `OnHiddenBlockAlphaChange`
```c
int32_t* alpha;
```
Fires while a hidden block fades, with the alpha it is drawn with.

---

### `OnCoinDrop`
```c
int32_t* count;
```
Fires when the coins a won battle drops are counted, after badges and Merlee, before they are capped at 20.

---

### `OnStarPointDrop`
```c
int32_t* count;
```
Fires when a battle awards star points, with how many.

---

### `OnPlayerDamageReceived`
```c
int32_t* damage;
```
Fires when the player takes damage in battle, with the damage dealt.

---

### `OnEnemyAttackDamage`
```c
Actor* attacker;
int32_t* damage;
```
Fires when an enemy's attack works out its damage.

---

### `OnPartnerAttackDamage`
```c
Actor* partner;
Actor* target;
int32_t* damage;
```
Fires when a partner's attack works out its damage against an enemy.

---

### `OnActorDefenseCheck`
```c
Actor* target;
int32_t* defenseTable;
int32_t elementFlags; // DAMAGE_TYPE_* of the attack
int32_t* defense;
```
Fires when the game reads an actor's defense against an attack.

---

### `OnActorBlueprintLoad`
```c
struct ActorBlueprint** blueprint;
```
Fires as a battle creates an actor from its blueprint. Point `*blueprint` at another to change the actor.

---

### `OnActorCreated`
```c
Actor* actor;
```
Fires after a battle created an actor.

---

### `OnBattleEffectsRemoved`
Fires when the game removes every effect as a battle ends.

---

### `OnPlayerFPChange`
```c
int32_t fpCost;
```
Fires when a move takes FP in battle. _(cancellable)_: no FP is taken.

---

### `OnPlayerSPChange`
```c
int32_t spCost;
```
Fires when a star power takes star energy. _(cancellable)_: none is taken.

---

### `OnPlayerBPCostCheck`
Fires when the pause menu checks whether a badge fits in the player's BP. _(cancellable)_: the badge is equipped
without the check.

---

### `OnBlockWindowCheck`
```c
int32_t* blockWindow;
int32_t* mashWindow;
```
Fires when a block action command sets its timing windows, in frames.

---

### `OnActionCommandDifficulty`
```c
int32_t* difficultyLevel;
```
Fires when an action command works out its difficulty.

---

### `OnPowerBounceChance`
```c
int32_t* hitChance;  // percent
int32_t targetChance; // the target's own power bounce chance
```
Fires as Power Bounce or Goombario's Multibonk works out the chance of another bounce.

---

### `OnCoinsChanged`
```c
int32_t before;
int32_t after;
```
Fires when the player's coins changed. _(polled)_

---

### `OnStarPointsChanged`
```c
int32_t before;
int32_t after;
```
Fires when the player's star points changed. _(polled)_

---

### `OnStarPiecesChanged`
```c
int32_t before;
int32_t after;
```
Fires when the player's star pieces changed. _(polled)_

---

### `OnHPChanged`
```c
int32_t before;
int32_t after;
```
Fires when the player's HP changed. _(polled)_

---

### `OnFPChanged`
```c
int32_t before;
int32_t after;
```
Fires when the player's FP changed. _(polled)_

---

### `OnItemCountChanged`
```c
int16_t item;
int32_t before;
int32_t after;
```
Fires when how many of an item the player has changed, counting the inventory, stored items, key items and badges.
Moving an item to storage changes nothing. _(polled)_

---

## Declared, not fired yet

These are declared and registered, but nothing fires them yet. Listening to them is harmless.

`TriggerUpdate`, `TriggerActivate`, `EntityPreUpdate`, `EntityPostUpdate`, `EntityPreDraw`, `EntityPostDraw`,
`ShadowPreUpdate`, `ShadowPostUpdate`, `ShadowPreDraw`, `ShadowPostDraw`, `WindowUpdate`, `WindowRootPreDraw`,
`WindowRootPostDraw`, `WindowPreDraw`, `WindowPostDraw`, `TheaterPreDraw`, `TheaterPostDraw`, `CurtainsPreDraw`,
`CurtainsPostDraw`, `VanillaBehavior`.
