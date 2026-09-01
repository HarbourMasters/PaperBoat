#include "states.h"
#include "model.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/patches/Patches.h"
#include "port/shape_loader.h"

extern ShapeFile gMapShapeData;
extern StageListRow* gCurrentStagePtr;
extern s32 bActorsIgnoreDuringCount[];

extern EvtScript EVS_OnBattleInit;
extern EvtScript EVS_Mario_OnActorCreate;
extern EvtScript EVS_Peach_OnActorCreate;
extern EvtScript EVS_MarioEnterStage;
extern EvtScript EVS_PeachEnterStage;

enum {
    // BTL_SUBSTATE_INIT                    = 0,
    BTL_SUBSTATE_CREATE_ENEMIES             = 1,
    BTL_SUBSTATE_CHECK_FIRST_STRIKE         = 4,
    BTL_SUBSTATE_FADE_IN                    = 7,
    BTL_SUBSTATE_DONE                       = 8,
};

BSS s32 BattleEnemiesCreated;

void load_stage_assets(Stage* stage) {
    ModelNode* rootModel;

    {
        char shapeAssetPath[64];
        snprintf(shapeAssetPath, sizeof(shapeAssetPath), "__OTR__shapes/%s", stage->shape);
        u8* shapeData = (u8*)ResourceGetDataByName(shapeAssetPath);
        size_t shapeSize = ResourceGetSizeByName(shapeAssetPath);
        Shape_LoadFromRawData(&gMapShapeData, shapeData, shapeSize, stage->shape);
    }

    rootModel = gMapShapeData.header.root;
    if (rootModel != nullptr) {
        load_data_for_models(rootModel, stage->texture);
    }
    load_battle_hit_asset(stage->hit);

    if (stage->bg != nullptr) {
        port_load_map_bg(stage->bg);
        set_background(&gBackgroundImage);
    }
}

void btl_state_update_normal_start(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    Battle* battle;
    Stage* stage;
    Actor* actor;
    Evt* script;
    s32 enemyNotDone;
    s32 type;
    s32 i;
    s32 j;

    s32* types;

    battle = gCurrentBattlePtr;
    if (gOverrideBattlePtr != nullptr) {
        battle = gOverrideBattlePtr;
    }

    if (gCurrentStagePtr == nullptr) {
        stage = battle->stage;
    } else {
        stage = gCurrentStagePtr->stage;
    }

    battleStatus->curStage = stage;
    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            #if DX_DEBUG_MENU
            dx_debug_set_battle_info(gCurrentBattleID << 16 | (gCurrentStageID & 0xFFFF), stage->shape);
            #endif

            BattleEnemiesCreated = battle->formationSize;
            set_screen_overlay_params_back(OVERLAY_NONE, -1.0f);

            load_stage_assets(stage);

            if (gGameStatusPtr->demoBattleFlags & DEMO_BTL_FLAG_ENABLED) {
                set_curtain_scale_goal(1.0f);
            }

            battleStatus->controlScript = nullptr;
            battleStatus->camMovementScript = nullptr;
            battleStatus->unk_90 = 0;
            battleStatus->preUpdateCallback = nullptr;
            battleStatus->initBattleCallback = nullptr;
            battleStatus->curSubmenu = 0;
            battleStatus->lastSelectedAbility = 0;
            battleStatus->curPartnerSubmenu = 0;
            battleStatus->lastPartnerPowerSelection = 0;
            battleStatus->totalStarPoints = 0;
            battleStatus->pendingStarPoints = 0;
            battleStatus->incrementStarPointDelay = 0;
            battleStatus->damageTaken = 0;
            battleStatus->nextMerleeSpellType = MERLEE_SPELL_NONE;
            battleStatus->actionCommandMode = AC_MODE_NOT_LEARNED;
            gCameras[CAM_DEFAULT].flags |= CAMERA_FLAG_DISABLED;
            gCameras[CAM_BATTLE].flags |= CAMERA_FLAG_DISABLED;
            gCameras[CAM_TATTLE].flags |= CAMERA_FLAG_DISABLED;
            if (gPlayerData.hasActionCommands) {
                battleStatus->actionCommandMode = AC_MODE_LEARNED;
            }
            battleStatus->actionQuality = 0;
            battleStatus->maxActionQuality = 0;
            battleStatus->enabledMenusFlags = -1;
            battleStatus->enabledStarPowersFlags = -1;
            battleStatus->itemUsesLeft = 0;
            battleStatus->hammerCharge = 0;
            battleStatus->jumpCharge = 0;
            battleStatus->unk_98 = 0;
            battleStatus->hpDrainCount = 0;
            gBattleStatus.flags2 |= BS_FLAGS2_CAN_FLEE;
            if (currentEncounter->forbidFleeing) {
                gBattleStatus.flags2 &= ~BS_FLAGS2_CAN_FLEE;
            }
            battleStatus->endBattleFadeOutRate = 10;
            battleStatus->waitForState = BATTLE_STATE_NONE;
            battleStatus->hammerLossTurns = -1;
            battleStatus->jumpLossTurns = -1;
            battleStatus->itemLossTurns = -1;
            battleStatus->outtaSightActive = 0;
            battleStatus->waterBlockTurnsLeft = 0;
            battleStatus->waterBlockAmount = 0;
            battleStatus->waterBlockEffect = nullptr;
            battleStatus->cloudNineTurnsLeft = 0;
            battleStatus->cloudNineDodgeChance = 0;
            battleStatus->cloudNineEffect = nullptr;
            battleStatus->reflectFlags = 0;
            battleStatus->turboChargeTurnsLeft = 0;
            battleStatus->turboChargeAmount = 0;
            battleStatus->stateFreezeCount = 0;
            battleStatus->merleeAttackBoost = 0;
            battleStatus->merleeDefenseBoost = 0;
            battleStatus->darknessMode = BTL_DARKNESS_STATE_NONE;
            battleStatus->unk_433 = -1;
            battleStatus->hustleTurns = 0;
            battleStatus->nextActorOrdinal = 0;
            battleStatus->cancelTurnMode = 0;
            gBattleStatus.flags2 &= ~BS_FLAGS2_PLAYER_TURN_USED;
            gBattleStatus.flags2 &= ~BS_FLAGS2_PARTNER_TURN_USED;
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;
            gBattleStatus.flags2 &= ~BS_FLAGS2_STORED_TURBO_CHARGE_TURN;
            gBattleStatus.flags2 &= ~BS_FLAGS2_DOING_JUMP_TUTORIAL;

            for (i = 0; i < ARRAY_COUNT(battleStatus->varTable); i++) {
                battleStatus->varTable[i] = 0;
            }

            BattleScreenFadeAmt = 255;
            battleStatus->inputBitmask = 0xFFFFF & ~(BUTTON_START | 0xC0);
            battleStatus->buffEffect = fx_partner_buff(0, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            setup_status_bar_for_battle();
            gCurrentCameraID = CAM_BATTLE;
            script = start_script(&EVS_OnBattleInit, EVT_PRIORITY_A, 0);
            battleStatus->camMovementScript = script;
            battleStatus->camMovementScriptID = script->id;
            gBattleSubState = BTL_SUBSTATE_CREATE_ENEMIES;
            break;
        case BTL_SUBSTATE_CREATE_ENEMIES:
            // wait for camera initialization to finish
            if (does_script_exist(battleStatus->camMovementScriptID)) {
                break;
            }

            if (stage->preBattle != nullptr) {
                script = start_script(stage->preBattle, EVT_PRIORITY_A, 0);
                battleStatus->controlScript = script;
                battleStatus->controlScriptID = script->id;
            }

            gStatusBar.hidden = false;
            gBattleStatus.flags1 |= BS_FLAGS1_ACTORS_VISIBLE;

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                battleStatus->enemyActors[i] = nullptr;
            }
            battleStatus->initialEnemyCount = 0;

            for (i = 0; i < BattleEnemiesCreated; i++) {
                create_actor(&(*battle->formation)[i]);
                types = bActorsIgnoreDuringCount;
                actor = battleStatus->enemyActors[i];

                while (true) {
                    type = *types;
                    if (type == -1) {
                        battleStatus->initialEnemyCount++;
                        break;
                    } else if (actor->actorType == type) {
                        break;
                    }
                    types++;
                }

                actor->instigatorValue = 0;
                if (i == 0) {
                    actor->instigatorValue = currentEncounter->instigatorValue;
                    if (currentEncounter->dizzyAttack.status == STATUS_KEY_DIZZY) {
                        inflict_status_set_duration(actor, STATUS_KEY_DIZZY, STATUS_TURN_MOD_DIZZY, currentEncounter->dizzyAttack.duration);
                    }
                }
            }

            if (stage->stageEnemyCount != 0) {
                if (stage->stageEnemyChance == 0 || (stage->stageEnemyChance > 0 && (rand_int(stage->stageEnemyChance) == 0))) {
                    BattleEnemiesCreated += stage->stageEnemyCount;
                    for (j = 0; i < BattleEnemiesCreated; i++, j++) {
                        create_actor(&(*stage->stageFormation)[j]);
                        actor = battleStatus->enemyActors[i];
                        actor->instigatorValue = 0;
                        if (i == 0) {
                            actor->instigatorValue = 0;
                            if (currentEncounter->dizzyAttack.status == STATUS_KEY_DIZZY) {
                                inflict_status_set_duration(actor, STATUS_KEY_DIZZY, STATUS_TURN_MOD_DIZZY, currentEncounter->dizzyAttack.duration);
                            }
                        }

                    }
                }
            }

            load_player_actor();
            actor = battleStatus->playerActor;
            if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                script = start_script(&EVS_Peach_OnActorCreate, EVT_PRIORITY_A, 0);
            } else {
                script = start_script(&EVS_Mario_OnActorCreate, EVT_PRIORITY_A, 0);
            }
            actor->takeTurnScript = script;
            actor->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PLAYER;
            load_partner_actor();
            gBattleSubState = BTL_SUBSTATE_CHECK_FIRST_STRIKE;
            break;
        case BTL_SUBSTATE_CHECK_FIRST_STRIKE:
            enemyNotDone = false;
            for (i = 0; i < BattleEnemiesCreated; i++) {
                actor = battleStatus->enemyActors[i];
                if (does_script_exist(actor->takeTurnScriptID)) {
                    enemyNotDone = true;
                    break;
                } else {
                    actor->takeTurnScript = nullptr;
                }
            }
            if (enemyNotDone) {
                break;
            }

            actor = battleStatus->playerActor;
            if (does_script_exist(actor->takeTurnScriptID)) {
                break;
            }
            actor->takeTurnScript = nullptr;

            actor = battleStatus->partnerActor;
            if (actor != nullptr) {
                if (does_script_exist(actor->takeTurnScriptID)) {
                    break;
                }
                actor->takeTurnScript = nullptr;
            }

            if (battle->onBattleStart != nullptr) {
                script = start_script(battle->onBattleStart, EVT_PRIORITY_A, 0);
                battleStatus->controlScript = script;
                battleStatus->controlScriptID = script->id;
            }
            if (battleStatus->darknessMode > BTL_DARKNESS_STATE_NONE) {
                set_screen_overlay_color(SCREEN_LAYER_BACK, 0, 0, 0);
                set_screen_overlay_params_back(OVERLAY_SCREEN_COLOR, 215.0f);
            }
            if (is_ability_active(ABILITY_CHILL_OUT) && currentEncounter->firstStrikeType == FIRST_STRIKE_ENEMY) {
                currentEncounter->firstStrikeType = FIRST_STRIKE_NONE;
            }

            switch (currentEncounter->firstStrikeType) {
                case FIRST_STRIKE_PLAYER:
                    btl_set_state(BATTLE_STATE_FIRST_STRIKE);
                    break;
                case FIRST_STRIKE_ENEMY:
                    btl_set_state(BATTLE_STATE_ENEMY_FIRST_STRIKE);
                    break;
                default:
                    if (!(gGameStatusPtr->demoBattleFlags & DEMO_BTL_FLAG_ENABLED)) {
                        actor = battleStatus->playerActor;
                        if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                            script = start_script(&EVS_PeachEnterStage, EVT_PRIORITY_A, 0);
                        } else {
                            script = start_script(&EVS_MarioEnterStage, EVT_PRIORITY_A, 0);
                        }
                        actor->takeTurnScript = script;
                        actor->takeTurnScriptID = script->id;
                        script->owner1.actorID = ACTOR_PLAYER;
                    }

                    if (currentEncounter->curEnemy != nullptr
                        && currentEncounter->curEnemy->encountered == ENCOUNTER_TRIGGER_SPIN
                        && is_ability_active(ABILITY_DIZZY_ATTACK)
                    ) {
                        actor = battleStatus->enemyActors[0];
                        script = start_script(&EVS_ApplyDizzyAttack, EVT_PRIORITY_A, 0);
                        actor->takeTurnScript = script;
                        actor->takeTurnScriptID = script->id;
                        script->owner1.enemyID = ACTOR_ENEMY0;
                    }

                    BattleScreenFadeAmt = 305;
                    BattleSubstateDelay = 0;
                    gBattleSubState = BTL_SUBSTATE_FADE_IN;
                    break;
            }
            break;
        case BTL_SUBSTATE_FADE_IN:
            if (BattleScreenFadeAmt == 0) {
                gBattleSubState = BTL_SUBSTATE_DONE;
                break;
            }

            BattleSubstateDelay++;
            if (BattleSubstateDelay == 15) {
                btl_cam_use_preset(BTL_CAM_DEFAULT);
            }

            if (!(gGameStatusPtr->demoBattleFlags & DEMO_BTL_FLAG_ENABLED)) {
                BattleScreenFadeAmt -= 10;
            } else {
                BattleScreenFadeAmt -= 50;
            }

            if (BattleScreenFadeAmt < 0) {
                BattleScreenFadeAmt = 0;
            }
            break;
        case BTL_SUBSTATE_DONE:
            if (battleStatus->stateFreezeCount == 0) {
                set_screen_overlay_params_front(OVERLAY_NONE, -1.0f);
                btl_set_state(BATTLE_STATE_BEGIN_TURN);
            }
            break;
    }
}

void btl_state_draw_normal_start(void) {
    set_screen_overlay_color(SCREEN_LAYER_FRONT, 0, 0, 0);

    if (BattleScreenFadeAmt > 255) {
        set_screen_overlay_params_front(OVERLAY_SCREEN_COLOR, 255.0f);
    } else {
        set_screen_overlay_params_front(OVERLAY_SCREEN_COLOR, BattleScreenFadeAmt);
    }
}
