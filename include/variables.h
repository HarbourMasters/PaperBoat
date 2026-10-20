#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "ultra64.h"
#include "common_structs.h"
#include "types.h"
#include "macros.h"
#include "enums.h"

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

extern_s PlayerStatus* gPlayerStatusPtr;
extern_s CollisionStatus gCollisionStatus;
extern_s GameStatus gGameStatus;
extern_s GameStatus* gGameStatusPtr;
extern u32 gRandSeed;

extern_s ItemData* gItemTable;
extern_s MoveData* gMoveTable;
extern const s32 gItemTableVanillaCount;
extern const s32 gMoveTableVanillaCount;
extern intptr_t** gItemEntityScripts;
extern const s32 gItemEntityScriptsVanillaCount;
extern intptr_t* gItemIconRasterOffsets;
extern intptr_t* gItemIconPaletteOffsets;
extern const s32 gItemIconRasterOffsetsVanillaCount;

extern s32 gBattleState;
extern_s BattleStatus gBattleStatus;
extern s32 gLastDrawBattleState;
extern s32 gDefeatedBattleSubstate;
extern s32 gBattleSubState;
extern s32 gDefeatedBattleState;
extern s32 gCurrentBattleID;
extern s32 gCurrentStageID;
extern struct Battle* gOverrideBattlePtr;

extern_s Camera gCameras[4];
extern_s s32 gCurrentCameraID;

extern CollisionData gCollisionData;

extern u8* gBackgroundTintModePtr;
extern s32 gEntityHideMode;

extern HiddenPanelsData gCurrentHiddenPanels;

extern BackgroundHeader gBackgroundImage;

extern CollisionData gZoneCollisionData;

// Animation related

extern PartnerAnimations gPartnerAnimations[12];

extern SpriteShadingProfile* gSpriteShadingProfile;

extern Window gWindows[64];

extern s32 gEncounterState;
extern s32 gOverrideFlags;

extern WindowStyle gWindowStyles[];

extern u16 gCurrentDoorSounds;
extern u16 gCurrentRoomDoorSounds;

extern UNK_FUN_PTR(TalkNotificationCallback);
extern UNK_FUN_PTR(InteractNotificationCallback);
extern UNK_FUN_PTR(ISpyNotificationCallback);
extern UNK_FUN_PTR(PulseStoneNotificationCallback);

extern Entity* TweesterTouchingPartner;
extern Entity* TweesterTouchingPlayer;

extern s32 PrevPlayerDirection;
extern s32 PeachDisguiseNpcIndex;
extern s32 PlayerRunStateTime;
extern s32 PrevPlayerCamRelativeYaw;
extern s32 D_800F7B44;
extern f32 PlayerNormalYaw;
extern f32 PlayerNormalPitch;
extern s32 NpcHitQueryColliderID;
extern Vec3s StandardActorHomePositions[];

extern s32 gEncounterSubState;
extern s32 gTimeFreezeMode;
extern b32 EncounterStateChanged;

extern u8 IntroMessageIdx;
extern s32 PartnerIDFromMenuIndex[12]; // partner IDs

// Scripts
extern EvtScript EVS_NpcDefeat;
extern EvtScript ShakeCam1;
extern EvtScript ShakeCamX;

extern_s MusicControlData gMusicControlData[2];

// gfx
extern DisplayContext* gDisplayContext;
extern Gfx* gMainGfxPos;
extern u16 gMatrixListPos;
extern s32 gCurrentDisplayContextIndex;
extern DisplayContext D_80164000[2]; // port: double-buffered display contexts

extern s16 gCurrentCamID;

extern s32 PartnerWishAnims[][5];

// On port, heap_battleHead is u8[BATTLE_HEAP_SIZE] — _heap_create needs backing memory
extern u8 heap_battleHead[BATTLE_HEAP_SIZE];

extern u32 bMarioIdleAnims[];
extern s32 bMarioDefendAnims[];
extern s32 bPeachIdleAnims[];

extern_s PartnerStatus gPartnerStatus;
extern StatusBar gStatusBar;
extern_s PlayerStatus gPlayerStatus;
extern PlayerSpinState gPlayerSpinState;
extern_s PlayerData gPlayerData;

#if VERSION_PAL
extern s32 gCurrentLanguage;
#else
#define gCurrentLanguage 0
#endif

#ifdef _LANGUAGE_C_PLUS_PLUS
} // extern "C"
#endif

#endif
