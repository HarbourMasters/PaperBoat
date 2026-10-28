#include "states.h"
#include "battle/battle.h"
#include "battle/battle_menu.h"
#include "hud_element.h"

enum {
    // BTL_SUBSTATE_INIT            = 0,
    BTL_SUBSTATE_CHOOSE             = 1,
    BTL_SUBSTATE_DONE               = 2,
    BTL_SUBSTATE_CANCEL             = 10,
};

void btl_state_update_select_target(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* actor;
    s32 targetListLength;
    s32 selectedTargetIndex;
    HudElemID hid;
    s8* targetIndexList;
    SelectableTarget* target;
    s32 i;

    if (!(gBattleStatus.flags1 & BS_FLAGS1_PARTNER_ACTING)) {
        actor = battleStatus->playerActor;
    } else {
        actor = battleStatus->partnerActor;
    }
    targetListLength = actor->targetListLength;
    selectedTargetIndex = actor->selectedTargetIndex;

    actor->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
    targetIndexList = actor->targetIndexList;
    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            BattleMenu_TargetPointerAlpha = 255;
            BattleMenu_TargetNameOffsetX = -100;
            gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;

            // prepare the action command tip for the selected move
            if (!is_ability_active(ABILITY_BERSERKER) || (gBattleStatus.flags1 & BS_FLAGS1_PARTNER_ACTING)) {
                if (battleStatus->selectedMoveID != MOVE_NONE) {
                    s8 actionTip = gMoveTable[battleStatus->selectedMoveID].actionTip;

                    if (actionTip >= 0) {
                        btl_show_battle_message(BTL_MSG_ACTION_TIP_PRESS_BEFORE_LANDING + actionTip, 60);
                    }
                }
            }

            // create the target list
            create_current_pos_target_list(actor);
            targetListLength = actor->targetListLength;
            if (battleStatus->curTargetListFlags & TARGET_FLAG_SELECT_ONE) {
                targetIndexList = actor->targetIndexList;
                for (i = 0; i < targetListLength; i++) {
                    target = &actor->targetData[targetIndexList[i]];
                    if (get_actor_part(get_actor(target->actorID), target->partID)->flags & ACTOR_PART_FLAG_DEFAULT_TARGET) {
                        actor->selectedTargetIndex = i;
                        break;
                    }
                }
            }

            // when TARGET_FLAG_OVERRIDE is set, skip selecting a target and begin executing the move
            if (battleStatus->curTargetListFlags & TARGET_FLAG_OVERRIDE) {
                if (!(gBattleStatus.flags1 & BS_FLAGS1_PARTNER_ACTING)) {
                    gBattleSubState = battleStatus->acceptTargetMenuSubstate;
                    if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                        btl_state_update_player_menu();
                    } else {
                        btl_state_update_player_menu();
                    }
                    btl_set_state(BATTLE_STATE_PLAYER_MOVE);
                } else {
                    gBattleSubState = battleStatus->acceptTargetMenuSubstate;
                    if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                        btl_state_update_twink_menu();
                    } else {
                        btl_state_update_partner_menu();
                    }
                    btl_set_state(BATTLE_STATE_PARTNER_MOVE);
                }
                break;
            }

            // if the target list is empty, skip selecting a target and begin executing the move
            if (targetListLength == 0) {
                if (!(gBattleStatus.flags1 & BS_FLAGS1_PARTNER_ACTING)) {
                    gBattleSubState = battleStatus->acceptTargetMenuSubstate;
                    if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                        btl_state_update_player_menu();
                    } else {
                        btl_state_update_player_menu();
                    }
                    btl_set_state(BATTLE_STATE_PLAYER_MOVE);
                } else {
                    gBattleSubState = battleStatus->acceptTargetMenuSubstate;
                    if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                        btl_state_update_twink_menu();
                    } else {
                        btl_state_update_partner_menu();
                    }
                    btl_set_state(BATTLE_STATE_PARTNER_MOVE);
                }
                break;
            }

            // create the HUD elements for the target pointers
            for (i = 0; i < targetListLength; i++) {
                hid = hud_element_create(&HES_HandPointDownLoop);
                BattleMenu_TargetHudElems[i] = hid;
                hud_element_set_render_depth(hid, 0);
                hud_element_set_render_pos(hid, 0, -100);
            }
            gBattleSubState = BTL_SUBSTATE_CHOOSE;
            break;
        case BTL_SUBSTATE_CHOOSE:
            // animate the target name sliding into view
            if (BattleMenu_TargetNameOffsetX < 0) {
                BattleMenu_TargetNameOffsetX += 20;
                if (BattleMenu_TargetNameOffsetX > 0) {
                    BattleMenu_TargetNameOffsetX = 0;
                }
            }

            if (battleStatus->curButtonsPressed & BUTTON_B) {
                sfx_play_sound(SOUND_MENU_BACK);
                gBattleSubState = BTL_SUBSTATE_CANCEL;
                break;
            }

            if (battleStatus->curButtonsPressed & BUTTON_A) {
                sfx_play_sound(SOUND_MENU_NEXT);
                BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
                BattleMenu_SwapDelay = 4;
                gBattleSubState = BTL_SUBSTATE_DONE;
                break;
            }

            gBattleStatus.flags1 |= BS_FLAGS1_MENU_OPEN;
            if (battleStatus->curButtonsDown & (BUTTON_Z | BUTTON_R)) {
                gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;
                break;
            }

            if (battleStatus->curTargetListFlags & TARGET_FLAG_SELECT_ONE) {
                s32 oldSelectedTargetIndex = selectedTargetIndex;

                if (battleStatus->curButtonsHeld & BUTTON_STICK_LEFT) {
                    selectedTargetIndex--;
                }
                if (battleStatus->curButtonsHeld & BUTTON_STICK_RIGHT) {
                    selectedTargetIndex++;
                }
                if (selectedTargetIndex < 0) {
                    selectedTargetIndex = targetListLength - 1;
                }
                if (selectedTargetIndex >= targetListLength) {
                    selectedTargetIndex = 0;
                }
                if (selectedTargetIndex != oldSelectedTargetIndex) {
                    s32 actorFlags;

                    target = &actor->targetData[targetIndexList[selectedTargetIndex]];
                    actorFlags = get_actor(target->actorID)->flags;
                    hid = BattleMenu_TargetHudElems[0];

                    if (actorFlags & ACTOR_FLAG_UPSIDE_DOWN) {
                        hud_element_set_script(hid, &HES_HandPointLeftLoop);
                    } else {
                        hud_element_set_script(hid, &HES_HandPointDownLoop);
                    }
                    sfx_play_sound(SOUND_MENU_CHANGE_SELECTION);
                }
                actor->selectedTargetIndex = selectedTargetIndex;
            }
            break;
        case BTL_SUBSTATE_DONE:
            gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;
            target = &actor->targetData[targetIndexList[actor->selectedTargetIndex]];
            actor->targetActorID = target->actorID;
            actor->targetPartID = target->partID;

            // free the HUD elements for the target pointers
            for (i = 0; i < targetListLength; i++) {
                hud_element_free(BattleMenu_TargetHudElems[i]);
            }

            // begin executing the move
            if (!(gBattleStatus.flags1 & BS_FLAGS1_PARTNER_ACTING)) {
                gBattleSubState = battleStatus->acceptTargetMenuSubstate;
                if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                    btl_state_update_peach_menu();
                } else {
                    btl_state_update_player_menu();
                }
                btl_set_state(BATTLE_STATE_PLAYER_MOVE);
            } else {
                gBattleSubState = battleStatus->acceptTargetMenuSubstate;
                if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                    btl_state_update_twink_menu();
                } else {
                    btl_state_update_partner_menu();
                }
                btl_set_state(BATTLE_STATE_PARTNER_MOVE);
            }
            break;
        case BTL_SUBSTATE_CANCEL:
            // free the HUD elements for the target pointers
            for (i = 0; i < targetListLength; i++) {
                hud_element_free(BattleMenu_TargetHudElems[i]);
            }

            gBattleStatus.flags1 |= BS_FLAGS1_10000 | BS_FLAGS1_MENU_OPEN;
            actor->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;

            if (battleStatus->itemUsesLeft != 0) {
                btl_set_state(BATTLE_STATE_PLAYER_MENU);
                gBattleSubState = battleStatus->cancelTargetMenuSubstate;
                if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                    btl_state_update_peach_menu();
                } else {
                    btl_state_update_player_menu();
                }
            } else if (!(gBattleStatus.flags1 & BS_FLAGS1_PARTNER_ACTING)) {
                btl_set_state(BATTLE_STATE_PLAYER_MENU);
                gBattleSubState = battleStatus->cancelTargetMenuSubstate;
                if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                    btl_state_update_peach_menu();
                } else {
                    btl_state_update_player_menu();
                }
            } else {
                btl_set_state(BATTLE_STATE_PARTNER_MENU);
                gBattleSubState = battleStatus->cancelTargetMenuSubstate;
                if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                    btl_state_update_twink_menu();
                } else {
                    btl_state_update_partner_menu();
                }
            }
            break;
    }
}

void btl_state_draw_select_target(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    s32 msgID;
    s32 targetListLength;
    s32 currentPartner;
    s32 actorID;
    SelectableTarget* target;
    Actor* choosingActor;
    Actor* enemyActor;
    s32 id;
    s32 i;
    s32 nameWidth;
    s32 xOffset, yOffset;
    f32 targetX, targetY, targetZ;
    s32 screenX, screenY, screenZ;
    s32 selectedTargetIndex;
    s8* targetIndexList;

    if (!(gBattleStatus.flags1 & BS_FLAGS1_PARTNER_ACTING)) {
        choosingActor = battleStatus->playerActor;
    } else {
        choosingActor = battleStatus->partnerActor;
    }

    targetListLength = choosingActor->targetListLength;
    target = choosingActor->targetData;
    selectedTargetIndex = choosingActor->selectedTargetIndex;
    targetIndexList = choosingActor->targetIndexList;

    if (targetListLength == 0) {
        return;
    }

    // draw target pointers
    if (battleStatus->curTargetListFlags & TARGET_FLAG_SELECT_ONE) {
        target = &choosingActor->targetData[targetIndexList[selectedTargetIndex]];
        enemyActor = get_actor(target->actorID);
        id = BattleMenu_TargetHudElems[0];
        targetX = target->truePos.x;
        targetY = target->truePos.y;
        targetZ = target->truePos.z;

        // select target pointer style based on target actor orientation
        if (enemyActor->flags & ACTOR_FLAG_UPSIDE_DOWN) {
            xOffset = 16;
            yOffset = 2;
            if (hud_element_get_script(id) != &HES_HandPointLeftLoop) {
                hud_element_set_script(id, &HES_HandPointLeftLoop);
            }
        } else {
            xOffset = 5;
            yOffset = -11;
            if (hud_element_get_script(id) != &HES_HandPointDownLoop) {
                hud_element_set_script(id, &HES_HandPointDownLoop);
            }
        }

        get_screen_coords(CAM_BATTLE, targetX, targetY, targetZ, &screenX, &screenY, &screenZ);
        hud_element_set_render_pos(id, screenX + xOffset, screenY + yOffset);
        hud_element_set_alpha(id, BattleMenu_TargetPointerAlpha);
    } else {
        for (i = 0; i < targetListLength; i++) {
            target = &choosingActor->targetData[targetIndexList[i]];
            enemyActor = get_actor(target->actorID);
            id = BattleMenu_TargetHudElems[i];
            targetX = target->truePos.x;
            targetY = target->truePos.y;
            targetZ = target->truePos.z;

            // select target pointer style based on target actor orientation
            if (enemyActor->flags & ACTOR_FLAG_UPSIDE_DOWN) {
                xOffset = 16;
                yOffset = 2;
                if (hud_element_get_script(id) != &HES_HandPointLeftLoop) {
                    hud_element_set_script(id, &HES_HandPointLeftLoop);
                }
            } else {
                xOffset = 5;
                yOffset = -11;
                if (hud_element_get_script(id) != &HES_HandPointDownLoop) {
                    hud_element_set_script(id, &HES_HandPointDownLoop);
                }
            }

            get_screen_coords(CAM_BATTLE, targetX, targetY, targetZ, &screenX, &screenY, &screenZ);
            hud_element_set_render_pos(id, screenX + xOffset, screenY + yOffset);
            hud_element_set_alpha(id, BattleMenu_TargetPointerAlpha);
        }
    }

    currentPartner = gPlayerData.curPartner;
    screenX = 52;
    screenY = 64;
    if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
        currentPartner = PARTNER_TWINK;
    }

    // get target name width
    if ((battleStatus->curTargetListFlags & TARGET_FLAG_SELECT_ONE) || targetListLength == 1) {
        actorID = target->actorID;
        if (actorID == ACTOR_PLAYER) {
            nameWidth = get_msg_width(MSG_Menus_Battle_TargetMario, 0) + 10;
        } else if (actorID == ACTOR_PARTNER) {
            nameWidth = get_msg_width(PartnerNameMessages[currentPartner], 0) + 10;
        } else {
            target = &choosingActor->targetData[targetIndexList[selectedTargetIndex]];
            enemyActor = get_actor(target->actorID);
            msgID = get_actor_part(enemyActor, target->partID)->staticData->overrideNameMsg;
            if (msgID == MSG_NONE) {
                msgID = bActorNames[enemyActor->actorType];
            }
            nameWidth = get_msg_width(msgID, 0) + 10;
        }
    } else {
        target = &choosingActor->targetData[targetIndexList[selectedTargetIndex]];
        actorID = target->actorID;
        if (actorID == ACTOR_PLAYER) {
            msgID = MSG_Menus_Battle_TargetMario;
            CALL_EVENT(OnTargetName, actorID, &msgID);
            nameWidth = get_msg_width(msgID, 0) + 10;
        } else if (actorID == ACTOR_PARTNER) {
            msgID = PartnerNameMessages[currentPartner];
            CALL_EVENT(OnTargetName, actorID, &msgID);
            nameWidth = get_msg_width(msgID, 0) + 10;
        } else {
            nameWidth = get_msg_width(MSG_Menus_Battle_TargetAllEnemies, 0) + 10;
        }
    }

    // draw target name box
    draw_box(0, WINDOW_STYLE_4, screenX + BattleMenu_TargetNameOffsetX, screenY, 0, nameWidth, 20, 255, 0,
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f, nullptr, nullptr, nullptr, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr);

    // draw target name text
    screenX += 4;
    screenY += 2;
    if ((battleStatus->curTargetListFlags & TARGET_FLAG_SELECT_ONE) || targetListLength == 1) {
        actorID = target->actorID;
        if (actorID == ACTOR_PLAYER) {
            draw_msg(MSG_Menus_Battle_TargetMario, screenX + BattleMenu_TargetNameOffsetX, screenY, 255, MSG_PAL_36, 0);
        } else if (actorID == ACTOR_PARTNER) {
            draw_msg(PartnerNameMessages[currentPartner], screenX + BattleMenu_TargetNameOffsetX, screenY, 255, MSG_PAL_36, 0);
        } else {
            target = &choosingActor->targetData[targetIndexList[selectedTargetIndex]];
            enemyActor = get_actor(target->actorID);
            msgID = get_actor_part(enemyActor, target->partID)->staticData->overrideNameMsg;
            if (msgID == MSG_NONE) {
                msgID = bActorNames[enemyActor->actorType];
            }
            draw_msg(msgID, screenX + BattleMenu_TargetNameOffsetX, screenY, 255, MSG_PAL_36, 0);
        }
    } else {
        target = &choosingActor->targetData[targetIndexList[selectedTargetIndex]];
        actorID = target->actorID;
        if (actorID == ACTOR_PLAYER) {
            msgID = MSG_Menus_Battle_TargetMario;
            CALL_EVENT(OnTargetName, actorID, &msgID);
            draw_msg(msgID, screenX + BattleMenu_TargetNameOffsetX, screenY, 255, MSG_PAL_36, 0);
        } else if (actorID == ACTOR_PARTNER) {
            msgID = PartnerNameMessages[currentPartner];
            CALL_EVENT(OnTargetName, actorID, &msgID);
            draw_msg(msgID, screenX + BattleMenu_TargetNameOffsetX, screenY, 255, MSG_PAL_36, 0);
        } else {
            draw_msg(MSG_Menus_Battle_TargetAllEnemies, screenX + BattleMenu_TargetNameOffsetX, screenY, 255, MSG_PAL_36, 0);
        }
    }
}
