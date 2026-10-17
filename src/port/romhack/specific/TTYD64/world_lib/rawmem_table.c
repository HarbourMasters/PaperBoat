#include "common.h"
#include "effects.h"
#include "overlay.h"
#include "model.h"
#include "entity.h"
#include "battle/action_cmd.h"
#include "dx/versioning.h"
#include "port/Engine.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_rawmem.h"
#include "../include/ttyd64_symbols.h"
#include "world_lib.h"

extern s32 BattleStatusUpdateDelay;
extern MessagePrintState* gCurrentPrintContext;

// clang-format off
b32 TTYD64_WorldLib_FieldRef(s32 field, void* ptr, TTYD64FieldRef* r) {
    r->lvSize = 0;
    switch (field) {
        case TTYD64_F_ACTOR_428_2U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 2;
            r->sign = SG_ZERO;
            r->addr = &(((Actor*) ptr)->targetActorID);
            r->lvSize = sizeof(((Actor*) ptr)->targetActorID);
            return true;
        case TTYD64_F_GCURRENTSAVEFILE_123A_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gCurrentSaveFile.globalBytes[394]);
            r->lvSize = sizeof(gCurrentSaveFile.globalBytes[394]);
            return true;
        case TTYD64_F_STATCHANGEFXDATA_20_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((StatChangeFXData*) ptr)->arrowValue);
            r->lvSize = sizeof(((StatChangeFXData*) ptr)->arrowValue);
            return true;
        case TTYD64_F_GPLAYERDATA_5_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gPlayerData.curFP);
            r->lvSize = sizeof(gPlayerData.curFP);
            return true;
        case TTYD64_F_GBATTLESTATUS_180_2U:
            r->n64Size = 2;
            r->sign = SG_ZERO;
            r->addr = &(gBattleStatus.lastAttackDamage);
            r->lvSize = sizeof(gBattleStatus.lastAttackDamage);
            return true;
        case TTYD64_F_GITEMTABLE_12BB_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gItemTable[149].potencyA);
            r->lvSize = sizeof(gItemTable[149].potencyA);
            return true;
        case TTYD64_F_GBATTLESTATUS_PLAYERACTOR_210_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gBattleStatus.playerActor->debuff);
            r->lvSize = sizeof(gBattleStatus.playerActor->debuff);
            return true;
        case TTYD64_F_GACTIONCOMMANDSTATUS_60_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gActionCommandStatus.wrongButtonPressed);
            r->lvSize = sizeof(gActionCommandStatus.wrongButtonPressed);
            return true;
        case TTYD64_F_STATCHANGEFXDATA_1C_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((StatChangeFXData*) ptr)->arrowType);
            r->lvSize = sizeof(((StatChangeFXData*) ptr)->arrowType);
            return true;
        case TTYD64_F_GPLAYERDATA_0_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gPlayerData.bootsLevel);
            r->lvSize = sizeof(gPlayerData.bootsLevel);
            return true;
        case TTYD64_F_GPLAYERDATA_1_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gPlayerData.hammerLevel);
            r->lvSize = sizeof(gPlayerData.hammerLevel);
            return true;
        case TTYD64_F_GBATTLESTATUS_81_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gBattleStatus.actionQuality);
            r->lvSize = sizeof(gBattleStatus.actionQuality);
            return true;
        case TTYD64_F_ACTOR_425_1U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(((Actor*) ptr)->selectedTargetIndex);
            r->lvSize = sizeof(((Actor*) ptr)->selectedTargetIndex);
            return true;
        case TTYD64_F_GPLAYERDATA_1D_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gPlayerData.partners[1].level);
            r->lvSize = sizeof(gPlayerData.partners[1].level);
            return true;
        case TTYD64_F_ITEMDATA_0_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((ItemData*) ptr)->nameMsg);
            r->lvSize = sizeof(((ItemData*) ptr)->nameMsg);
            return true;
        case TTYD64_F_EFFECTINSTANCE_C_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((EffectInstance*) ptr)->data.any);
            r->lvSize = sizeof(((EffectInstance*) ptr)->data.any);
            return true;
        case TTYD64_F_WATERBLOCKFXDATA_10_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((WaterBlockFXData*) ptr)->timeLeft);
            r->lvSize = sizeof(((WaterBlockFXData*) ptr)->timeLeft);
            return true;
        case TTYD64_F_PARTNERDATA_1_1U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(((PartnerData*) ptr)->level);
            r->lvSize = sizeof(((PartnerData*) ptr)->level);
            return true;
        case TTYD64_F_GPLAYERDATA_12_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gPlayerData.curPartner);
            r->lvSize = sizeof(gPlayerData.curPartner);
            return true;
        case TTYD64_F_GBATTLESTATUS_17A_2U:
            r->n64Size = 2;
            r->sign = SG_ZERO;
            r->addr = &(gBattleStatus.moveArgument);
            r->lvSize = sizeof(gBattleStatus.moveArgument);
            return true;
        case TTYD64_F_GBATTLESTATUS_17C_2U:
            r->n64Size = 2;
            r->sign = SG_ZERO;
            r->addr = &(gBattleStatus.selectedMoveID);
            r->lvSize = sizeof(gBattleStatus.selectedMoveID);
            return true;
        case TTYD64_F_GPLAYERDATA_2_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gPlayerData.curHP);
            r->lvSize = sizeof(gPlayerData.curHP);
            return true;
        case TTYD64_F_RECOVERFXDATA_40_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((RecoverFXData*) ptr)->unk_40);
            r->lvSize = sizeof(((RecoverFXData*) ptr)->unk_40);
            return true;
        case TTYD64_F_RECOVERFXDATA_2C_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((RecoverFXData*) ptr)->timeLeft);
            r->lvSize = sizeof(((RecoverFXData*) ptr)->timeLeft);
            return true;
        case TTYD64_F_RECOVERFXDATA_5C_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((RecoverFXData*) ptr)[1].vel.y);
            r->lvSize = sizeof(((RecoverFXData*) ptr)[1].vel.y);
            return true;
        case TTYD64_F_RECOVERFXDATA_70_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((RecoverFXData*) ptr)[1].alpha);
            r->lvSize = sizeof(((RecoverFXData*) ptr)[1].alpha);
            return true;
        case TTYD64_F_RECOVERFXDATA_4_4F:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_FLOAT;
            r->addr = &(((RecoverFXData*) ptr)->pos.x);
            r->lvSize = sizeof(((RecoverFXData*) ptr)->pos.x);
            return true;
        case TTYD64_F_GPLAYERDATA_3_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gPlayerData.curMaxHP);
            r->lvSize = sizeof(gPlayerData.curMaxHP);
            return true;
        case TTYD64_F_GPLAYERDATA_6_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gPlayerData.curMaxFP);
            r->lvSize = sizeof(gPlayerData.curMaxFP);
            return true;
        case TTYD64_F_PARTNERDATA_6_1U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(TTYD64_PartnerHPRecord((PartnerData*) ptr - gPlayerData.partners)->max);
            r->lvSize = sizeof(TTYD64_PartnerHPRecords[0].max);
            return true;
        case TTYD64_F_PARTNERDATA_5_1U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(TTYD64_PartnerHPRecord((PartnerData*) ptr - gPlayerData.partners)->hp);
            r->lvSize = sizeof(TTYD64_PartnerHPRecords[0].hp);
            return true;
        case TTYD64_F_EFFECT_DATA_20_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((StatChangeFXData*) ptr)->arrowValue);
            r->lvSize = sizeof(((StatChangeFXData*) ptr)->arrowValue);
            return true;
        case TTYD64_F_EFFECT_DATA_1C_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((StatChangeFXData*) ptr)->arrowType);
            r->lvSize = sizeof(((StatChangeFXData*) ptr)->arrowType);
            return true;
        case TTYD64_F_TTYD64_DEBUFFSCOUNTERS_FXPOINTERS_0_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = ptr;
            r->lvSize = sizeof(((TTYD64CounterUI*) NULL)->fx);
            return true;
        case TTYD64_F_TTYD64_DEBUFFSCOUNTERS_DATA_0_1U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = ptr;
            r->lvSize = sizeof(((TTYD64CounterUI*) NULL)->counterType);
            return true;
        case TTYD64_F_EFFECT_DATA_40_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((RecoverFXData*) ptr)->unk_40);
            r->lvSize = sizeof(((RecoverFXData*) ptr)->unk_40);
            return true;
        case TTYD64_F_GBATTLESTATUS_8B_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gBattleStatus.hustleTurns);
            r->lvSize = sizeof(gBattleStatus.hustleTurns);
            return true;
        case TTYD64_F_ENTITY_40_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((Entity*) ptr)->dataBuf.any);
            r->lvSize = sizeof(((Entity*) ptr)->dataBuf.any);
            return true;
        case TTYD64_F_GBATTLESTATUS_PLAYERACTOR_138_4U:
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(gBattleStatus.playerActor->homePos.x);
            r->lvSize = sizeof(gBattleStatus.playerActor->homePos.x);
            return true;
        case TTYD64_F_GBATTLESTATUS_PLAYERACTOR_140_4U:
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(gBattleStatus.playerActor->homePos.z);
            r->lvSize = sizeof(gBattleStatus.playerActor->homePos.z);
            return true;
        case TTYD64_F_GPARTNERSTATUS_0_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gPartnerStatus.partnerActionState);
            r->lvSize = sizeof(gPartnerStatus.partnerActionState);
            return true;
        case TTYD64_F_GPLAYERDATA_18_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &TTYD64_ShineSprites;
            r->lvSize = sizeof(TTYD64_ShineSprites);
            return true;
        case TTYD64_F_EXTRAACTORDATA_EVERYONE_E_1U:
            if (TTYD64_ActorRec(ACTOR_PLAYER) == NULL) {
                return false;
            }
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(TTYD64_ActorRec(ACTOR_PLAYER)->defendStack);
            r->lvSize = sizeof(TTYD64_ActorRec(ACTOR_PLAYER)->defendStack);
            return true;
        case TTYD64_F_ACTOR_192_2U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 2;
            r->sign = SG_ZERO;
            r->addr = &(((Actor*) ptr)->actorID);
            r->lvSize = sizeof(((Actor*) ptr)->actorID);
            return true;
        case TTYD64_F_GPLAYERDATA_28E_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gPlayerData.maxStarPower);
            r->lvSize = sizeof(gPlayerData.maxStarPower);
            return true;
        case TTYD64_F_GPLAYERDATA_290_2U:
            r->n64Size = 2;
            r->sign = SG_ZERO;
            r->addr = &(gPlayerData.starPower);
            r->lvSize = sizeof(gPlayerData.starPower);
            return true;
        case TTYD64_F_GBATTLESTATUS_198_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gBattleStatus.powerBounceCounter);
            r->lvSize = sizeof(gBattleStatus.powerBounceCounter);
            return true;
        case TTYD64_F_SUPERGUARD_BYTEFLAG_0_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(TTYD64_Guard.superguarded);
            r->lvSize = sizeof(TTYD64_Guard.superguarded);
            return true;
        case TTYD64_F_BATTLESTATUSUPDATEDELAY_0_4U:
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(BattleStatusUpdateDelay);
            r->lvSize = sizeof(BattleStatusUpdateDelay);
            return true;
        case TTYD64_F_GBATTLESTATUS_1A8_2U:
            r->n64Size = 2;
            r->sign = SG_ZERO;
            r->addr = &(gBattleStatus.attackerActorID);
            r->lvSize = sizeof(gBattleStatus.attackerActorID);
            return true;
        case TTYD64_F_GMESSAGEPRINTERS_4F8_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(msg_get_printer_by_index(0)[0].windowState);
            r->lvSize = sizeof(msg_get_printer_by_index(0)[0].windowState);
            return true;
        case TTYD64_F_GPLAYERSTATUS_14_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gPlayerStatus.enableCollisionOverlapsCheck);
            r->lvSize = sizeof(gPlayerStatus.enableCollisionOverlapsCheck);
            return true;
        case TTYD64_F_GPLAYERSTATUS_15_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gPlayerStatus.inputDisabledCount);
            r->lvSize = sizeof(gPlayerStatus.inputDisabledCount);
            return true;
        case TTYD64_F_GPLAYERSTATUS_A8_4U:
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(gPlayerStatus.spriteFacingAngle);
            r->lvSize = sizeof(gPlayerStatus.spriteFacingAngle);
            return true;
        case TTYD64_F_ENEMY_D0_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((Enemy*) ptr)->territory);
            r->lvSize = sizeof(((Enemy*) ptr)->territory);
            return true;
        case TTYD64_F_ENTITY_48_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((Entity*) ptr)->pos.x);
            r->lvSize = sizeof(((Entity*) ptr)->pos.x);
            return true;
        case TTYD64_F_ENTITY_4C_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((Entity*) ptr)->pos.y);
            r->lvSize = sizeof(((Entity*) ptr)->pos.y);
            return true;
        case TTYD64_F_ENTITY_50_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((Entity*) ptr)->pos.z);
            r->lvSize = sizeof(((Entity*) ptr)->pos.z);
            return true;
        case TTYD64_F_ENTITY_48_4F:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_FLOAT;
            r->addr = &(((Entity*) ptr)->pos.x);
            r->lvSize = sizeof(((Entity*) ptr)->pos.x);
            return true;
        case TTYD64_F_ENTITY_4C_4F:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_FLOAT;
            r->addr = &(((Entity*) ptr)->pos.y);
            r->lvSize = sizeof(((Entity*) ptr)->pos.y);
            return true;
        case TTYD64_F_ENTITY_50_4F:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_FLOAT;
            r->addr = &(((Entity*) ptr)->pos.z);
            r->lvSize = sizeof(((Entity*) ptr)->pos.z);
            return true;
        case TTYD64_F_GCOLLISIONSTATUS_2_2U:
            r->n64Size = 2;
            r->sign = SG_ZERO;
            r->addr = &(gCollisionStatus.curFloor);
            r->lvSize = sizeof(gCollisionStatus.curFloor);
            return true;
        case TTYD64_F_GGAMESTATUS_7E_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gGameStatus.peachFlags);
            r->lvSize = sizeof(gGameStatus.peachFlags);
            return true;
        case TTYD64_F_GCOLLISIONSTATUS_8_2U:
            r->n64Size = 2;
            r->sign = SG_ZERO;
            r->addr = &(gCollisionStatus.curCeiling);
            r->lvSize = sizeof(gCollisionStatus.curCeiling);
            return true;
        case TTYD64_F_GPLAYERDATA_A_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gPlayerData.hasActionCommands);
            r->lvSize = sizeof(gPlayerData.hasActionCommands);
            return true;
        case TTYD64_F_GGAMESTATUS_10_4U:
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(gGameStatus.pressedButtons[0]);
            r->lvSize = sizeof(gGameStatus.pressedButtons[0]);
            return true;
        case TTYD64_F_GCURRENTPRINTCONTEXT_0_4U:
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(gCurrentPrintContext);
            r->lvSize = sizeof(gCurrentPrintContext);
            return true;
        case TTYD64_F_MESSAGEPRINTSTATE_4_2U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 2;
            r->sign = SG_ZERO;
            r->addr = &(gCurrentPrintContext->printBufferPos);
            r->lvSize = sizeof(gCurrentPrintContext->printBufferPos);
            return true;
        case TTYD64_F_MESSAGEPRINTSTATE_460_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(gCurrentPrintContext->curLinePos);
            r->lvSize = sizeof(gCurrentPrintContext->curLinePos);
            return true;
        case TTYD64_F_MESSAGEPRINTSTATE_466_2U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 2;
            r->sign = SG_ZERO;
            r->addr = &(gCurrentPrintContext->nextLinePos);
            r->lvSize = sizeof(gCurrentPrintContext->nextLinePos);
            return true;
        case TTYD64_F_MESSAGEPRINTSTATE_486_1U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gCurrentPrintContext->curLine);
            r->lvSize = sizeof(gCurrentPrintContext->curLine);
            return true;
        case TTYD64_F_GGAMESTATUS_7D_1U:
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(gGameStatus.keepUsingPartnerOnMapChange);
            r->lvSize = sizeof(gGameStatus.keepUsingPartnerOnMapChange);
            return true;
        case TTYD64_F_GPLAYERSTATUS_54_4U:
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(gPlayerStatus.curSpeed);
            r->lvSize = sizeof(gPlayerStatus.curSpeed);
            return true;
        case TTYD64_F_GPLAYERSTATUS_A8_4F:
            r->n64Size = 4;
            r->sign = SG_FLOAT;
            r->addr = &(gPlayerStatus.spriteFacingAngle);
            r->lvSize = sizeof(gPlayerStatus.spriteFacingAngle);
            return true;
        case TTYD64_F_ITEMDATA_1A_1U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(((ItemData*) ptr)->moveID);
            r->lvSize = sizeof(((ItemData*) ptr)->moveID);
            return true;
        case TTYD64_F_MOVEDATA_12_1U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 1;
            r->sign = SG_ZERO;
            r->addr = &(((MoveData*) ptr)->costBP);
            r->lvSize = sizeof(((MoveData*) ptr)->costBP);
            return true;
        case TTYD64_F_SIMPLESPRINGDATA_0_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((SimpleSpringData*) ptr)->launchVel);
            r->lvSize = sizeof(((SimpleSpringData*) ptr)->launchVel);
            return true;
        case TTYD64_F_ENTITY_0_4U:
            if (ptr == NULL) {
                return false;
            }
            r->n64Size = 4;
            r->sign = SG_ZERO;
            r->addr = &(((Entity*) ptr)->flags);
            r->lvSize = sizeof(((Entity*) ptr)->flags);
            return true;
        default:
            return false;
    }
}

// clang-format on
