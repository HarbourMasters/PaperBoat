/**
 * Global Variable Initialization for PC Port
 *
 * BSS section globals are not automatically zero-initialized on the PC port,
 * which can cause crashes when garbage values are read (e.g., gPlayerData.curPartner = 70).
 * This file provides centralized initialization of all critical game globals.
 */

#include "common.h"
#include "entity.h"
#include "npc.h"
#include "model.h"
#include "overlay.h"
#include "effects.h"
#include "nu/nusys.h"

// External declarations for all globals that need initialization

// Player/Game State (from engine1_post_bss.c)
extern PartnerStatus gPartnerStatus;
extern s32 gSpinHistoryPosY[6];
extern s32 gSpinHistoryPosX[6];
extern s32 gSpinHistoryPosZ[6];
extern StatusBar gStatusBar;
extern PlayerStatus gPlayerStatus;
extern PlayerSpinState gPlayerSpinState;
extern PlayerData gPlayerData;
extern s16 gSpinHistoryPosAngle[5];

// Battle System (from battle_bss.c)
extern s32 gBattleState;
extern BattleStatus gBattleStatus;
extern s32 gLastDrawBattleState;
extern s32 gDefeatedBattleSubstate;
extern s32 gBattleSubState;
extern s32 gDefeatedBattleState;
extern s32 gCurrentBattleID;
extern s32 gCurrentStageID;

// World/Collision (from engine2_post_bss.c, main_post_bss.c)
extern CollisionStatus gCollisionStatus;
extern HiddenPanelsData gCurrentHiddenPanels;
extern CollisionData gCollisionData;
extern CollisionData gZoneCollisionData;
extern EncounterStatus gCurrentEncounter;

// Save Data (from main_post_bss.c)
extern SaveData gCurrentSaveFile;
extern SaveGlobals gSaveGlobals;

// UI/Graphics (from engine2_post_bss.c)
extern Window gWindows[64];
extern ScreenOverlay ScreenOverlays[2];
extern TextureHandle TextureHandles[128];
extern MusicControlData gMusicControlData[2];
extern DisplayContext D_80164000[2];

// Camera (from main_post_bss.c)
extern Camera gCameras[4];

// Game status (from main_loop.c)
extern GameStatus gGameStatus;

// Entity/Worker Lists
extern WorkerList gWorldWorkerList;
extern WorkerList gBattleWorkerList;
extern EntityModelList gWorldEntityModelList;
extern EntityModelList gBattleEntityModelList;
extern EntityList gWorldEntityList;
extern EntityList gBattleEntityList;
extern ShadowList gWorldShadowList;
extern ShadowList gBattleShadowList;

// Partner movement history (from partners.c)
extern PlayerPathElement gPlayerMoveHistory[40];
extern s32 gPlayerMoveHistoryIndex;

// Effect instances (from main_post_bss.c)
extern EffectInstance* gEffectInstances[96];

// Script system (from evt/script_list.c)
extern u32* gMapFlags;
extern Bytecode* gMapVars;
extern s32 gNumScripts;
extern ScriptList gWorldScriptList;
extern ScriptList gBattleScriptList;
extern ScriptList* gCurrentScriptListPtr;
extern s32 gScriptIndexList[MAX_SCRIPTS];
extern s32 gScriptIdList[MAX_SCRIPTS];
extern s32 gScriptListCount;

void init_game_globals(void) {
    // Initialize NuSystem graphics globals (nuGfxCfb, nuGfxCfb_ptr)
    // This is normally done by boot_main() -> nuGfxInit(), but the port doesn't call boot_main
    nuGfxInit();

    // Player state
    mem_clear(&gPlayerData, sizeof(gPlayerData));
    mem_clear(&gPlayerStatus, sizeof(gPlayerStatus));
    mem_clear(&gPartnerStatus, sizeof(gPartnerStatus));
    mem_clear(&gStatusBar, sizeof(gStatusBar));
    mem_clear(&gPlayerSpinState, sizeof(gPlayerSpinState));

    // Player physics/animation state
    mem_clear(gSpinHistoryPosX, sizeof(gSpinHistoryPosX));
    mem_clear(gSpinHistoryPosY, sizeof(gSpinHistoryPosY));
    mem_clear(gSpinHistoryPosZ, sizeof(gSpinHistoryPosZ));
    mem_clear(gSpinHistoryPosAngle, sizeof(gSpinHistoryPosAngle));

    // Partner movement history
    mem_clear(gPlayerMoveHistory, sizeof(gPlayerMoveHistory));
    gPlayerMoveHistoryIndex = 0;

    // Battle state
    mem_clear(&gBattleStatus, sizeof(gBattleStatus));
    gBattleState = 0;
    gBattleSubState = 0;
    gLastDrawBattleState = 0;
    gDefeatedBattleState = 0;
    gDefeatedBattleSubstate = 0;
    gCurrentBattleID = 0;
    gCurrentStageID = 0;

    // Collision data
    mem_clear(&gCollisionStatus, sizeof(gCollisionStatus));
    mem_clear(&gCollisionData, sizeof(gCollisionData));
    mem_clear(&gZoneCollisionData, sizeof(gZoneCollisionData));
    mem_clear(&gCurrentHiddenPanels, sizeof(gCurrentHiddenPanels));

    // Encounter
    mem_clear(&gCurrentEncounter, sizeof(gCurrentEncounter));

    // Save data
    mem_clear(&gCurrentSaveFile, sizeof(gCurrentSaveFile));
    mem_clear(&gSaveGlobals, sizeof(gSaveGlobals));

    // UI/Graphics
    mem_clear(gWindows, sizeof(gWindows));
    mem_clear(ScreenOverlays, sizeof(ScreenOverlays));
    mem_clear(TextureHandles, sizeof(TextureHandles));
    mem_clear(gMusicControlData, sizeof(gMusicControlData));
    mem_clear(D_80164000, sizeof(D_80164000));

    // Camera
    mem_clear(gCameras, sizeof(gCameras));

    // Game status (only partially initialized at definition)
    mem_clear(&gGameStatus, sizeof(gGameStatus));

    // Entity/Worker lists
    mem_clear(&gWorldWorkerList, sizeof(gWorldWorkerList));
    mem_clear(&gBattleWorkerList, sizeof(gBattleWorkerList));
    mem_clear(&gWorldEntityModelList, sizeof(gWorldEntityModelList));
    mem_clear(&gBattleEntityModelList, sizeof(gBattleEntityModelList));
    mem_clear(&gWorldEntityList, sizeof(gWorldEntityList));
    mem_clear(&gBattleEntityList, sizeof(gBattleEntityList));
    mem_clear(&gWorldShadowList, sizeof(gWorldShadowList));
    mem_clear(&gBattleShadowList, sizeof(gBattleShadowList));

    // Effect instances
    mem_clear(gEffectInstances, sizeof(gEffectInstances));

    // Script list (must be zeroed before clear_script_list() is called)
    gCurrentScriptListPtr = NULL;
    gMapFlags = NULL;
    gMapVars = NULL;
    gNumScripts = 0;
    gScriptListCount = 0;
    mem_clear(&gWorldScriptList, sizeof(gWorldScriptList));
    mem_clear(&gBattleScriptList, sizeof(gBattleScriptList));
    mem_clear(gScriptIndexList, sizeof(gScriptIndexList));
    mem_clear(gScriptIdList, sizeof(gScriptIdList));

}
