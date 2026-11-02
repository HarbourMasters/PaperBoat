#include "common.h"
#include "inventory.h"
#include "pause/pause_common.h"
#include "hud_element.h"
#include "world/partners.h"

extern PopupMenu gItemChoicePopupMenu;

API_CALLABLE(ShowKeyChoicePopup) {
    PlayerData* playerData = &gPlayerData;
    PopupMenu* menu = &gItemChoicePopupMenu;
    Trigger* trigger = script->owner2.trigger;
    s32 numEntries;
    s32 i;

    if (isInitialCall) {
        script->functionTemp[0] = 0;
    }

    switch (script->functionTemp[0]) {
        case 0:
            disable_player_input();
            disable_player_static_collisions();
            partner_disable_input();
            close_status_bar();
            numEntries = 0;

            gOverrideFlags |= GLOBAL_OVERRIDES_40;

            for (i = 0; i < ARRAY_COUNT(playerData->keyItems); i++) {
                s16 invItem = playerData->keyItems[i];

                if (invItem != ITEM_NONE) {
                    s32 found = false;
                    s32* itemIt = trigger->itemList;

                    while (*itemIt > 0) {
                        if (invItem == *itemIt) {
                            found = true;
                            break;
                        }
                        itemIt++;
                    }

                    if (found) {
                        ItemData* item = &gItemTable[playerData->keyItems[i]];

                        menu->ptrIcon[numEntries] = gItemHudScripts[item->hudElemID].enabled;
                        menu->userIndex[numEntries] = i;
                        menu->enabled[numEntries] = true;
                        menu->nameMsg[numEntries] = item->nameMsg;
                        menu->descMsg[numEntries] = item->shortDescMsg;
                        numEntries++;
                    }
                }
            }

            if (numEntries == 0) {
                script->varTable[0] = 0;
                return ApiStatus_DONE1;
            }
            menu->popupType = POPUP_MENU_USEKEY;
            menu->numEntries = numEntries;
            menu->initialPos = 0;
            create_standard_popup_menu(menu);
            script->functionTemp[1] = 0;
            script->functionTemp[0] = 1;
            break;
        case 1:
            if (script->functionTemp[1] == 0) {
                script->functionTemp[2] = menu->result;
                if (script->functionTemp[2] == 0) {
                    break;
                }
                hide_popup_menu();
            }

            script->functionTemp[1]++;
            if (script->functionTemp[1] >= 15) {
                destroy_popup_menu();

                if (script->functionTemp[2] == 0xFF) {
                    script->varTable[0] = -1;
                } else {
                    s32 invIndex = menu->userIndex[script->functionTemp[2] - 1];
                    script->varTable[1] = invIndex;
                    script->varTable[0] = playerData->keyItems[invIndex];
                }
                return ApiStatus_DONE1;
            }
            break;
    }
    return ApiStatus_BLOCK;
}

API_CALLABLE(ShowConsumableChoicePopup) {
    PlayerData* playerData = &gPlayerData;
    PopupMenu* menu = &gItemChoicePopupMenu;
    Trigger* trigger = script->owner2.trigger;
    s32 capacity;
    s32 numEntries;
    s32 i;

    if (isInitialCall) {
        script->functionTemp[0] = 0;
    }

    switch (script->functionTemp[0]) {
        case 0:
            disable_player_input();
            disable_player_static_collisions();
            partner_disable_input();
            close_status_bar();
            numEntries = 0;

            gOverrideFlags |= GLOBAL_OVERRIDES_40;

            capacity = get_consumables_capacity();
            for (i = 0; i < capacity; i++) {
                s16 invItem = playerData->invItems[i];

                if (invItem != ITEM_NONE) {
                    s32 found = false;
                    s32* itemIt = trigger->itemList;

                    while (*itemIt > 0) {
                        if (invItem == *itemIt) {
                            found = true;
                            break;
                        }
                        itemIt++;
                    }
                    CALL_EVENT(OnConsumableChoiceMatch, invItem, trigger->itemList, &found);

                    if (found && numEntries < ARRAY_COUNT(menu->ptrIcon)) {
                        ItemData* item = &gItemTable[playerData->invItems[i]];

                        menu->ptrIcon[numEntries] = gItemHudScripts[item->hudElemID].enabled;
                        menu->userIndex[numEntries] = i;
                        menu->enabled[numEntries] = true;
                        menu->nameMsg[numEntries] = item->nameMsg;
                        menu->descMsg[numEntries] = item->shortDescMsg;
                        numEntries++;
                    }
                }
            }

            if (numEntries == 0) {
                script->varTable[0] = 0;
                return ApiStatus_DONE1;
            }
            menu->popupType = POPUP_MENU_USEKEY;
            menu->numEntries = numEntries;
            menu->initialPos = 0;
            create_standard_popup_menu(menu);
            script->functionTemp[1] = 0;
            script->functionTemp[0] = 1;
            break;
        case 1:
            if (script->functionTemp[1] == 0) {
                script->functionTemp[2] = menu->result;
                if (script->functionTemp[2] == 0) {
                    break;
                }
                hide_popup_menu();
            }

            script->functionTemp[1]++;
            if (script->functionTemp[1] >= 15) {
                destroy_popup_menu();

                if (script->functionTemp[2] == 0xFF) {
                    script->varTable[0] = -1;
                } else {
                    s32 invIdx = menu->userIndex[script->functionTemp[2] - 1];
                    script->varTable[1] = invIdx;
                    script->varTable[0] = playerData->invItems[invIdx];
                }
                return ApiStatus_DONE1;
            }
            break;
    }
    return ApiStatus_BLOCK;
}

API_CALLABLE(RemoveItemAt) {
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);

    gPlayerData.invItems[index] = ITEM_NONE;
    sort_consumables();
    return ApiStatus_DONE2;
}

API_CALLABLE(RemoveKeyItemAt) {
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);

    gPlayerData.keyItems[index] = ITEM_NONE;
    return ApiStatus_DONE2;
}

API_CALLABLE(CloseChoicePopup) {
    enable_player_input();
    enable_player_static_collisions();
    partner_enable_input();
    gOverrideFlags &= ~GLOBAL_OVERRIDES_40;
    return ApiStatus_DONE2;
}

API_CALLABLE(AddItem) {
    Bytecode* args = script->ptrReadPos;
    s32 itemID = evt_get_variable(script, *args++);
    Bytecode outVar = *args++;

    s32 addedIdx = add_item(itemID);

    evt_set_variable(script, outVar, addedIdx);
    return ApiStatus_DONE2;
}

API_CALLABLE(RemoveItem) {
    Bytecode* args = script->ptrReadPos;
    s32 itemID = evt_get_variable(script, *args++);
    Bytecode outVar = *args++;

    s32 removedIdx = remove_item(itemID);

    evt_set_variable(script, outVar, removedIdx);
    return ApiStatus_DONE2;
}

API_CALLABLE(FindItem) {
    Bytecode* args = script->ptrReadPos;
    s32 itemID = evt_get_variable(script, *args++);
    Bytecode outVar = *args++;

    s32 foundIdx = find_item(itemID);

    evt_set_variable(script, outVar, foundIdx);
    return ApiStatus_DONE2;
}

API_CALLABLE(CountItem) {
    Bytecode* args = script->ptrReadPos;
    s32 itemID = evt_get_variable(script, *args++);
    Bytecode outVar = *args++;

    b32 count = count_item(itemID);

    evt_set_variable(script, outVar, count);
    return ApiStatus_DONE2;
}

API_CALLABLE(HasItem) {
    Bytecode* args = script->ptrReadPos;
    s32 itemID = evt_get_variable(script, *args++);
    Bytecode outVar = *args++;

    b32 hasItem = has_item(itemID);

    evt_set_variable(script, outVar, hasItem);
    return ApiStatus_DONE2;
}

API_CALLABLE(MakeItemEntity) {
    Bytecode* args = script->ptrReadPos;
    s32 itemID = evt_get_variable(script, *args++);
    s32 x = evt_get_variable(script, *args++);
    s32 y = evt_get_variable(script, *args++);
    s32 z = evt_get_variable(script, *args++);
    s32 itemSpawnMode = evt_get_variable(script, *args++);
    s32 pickupVar = evt_get_variable_index(script, *args++);

    script->varTable[0] = make_item_entity_nodelay(itemID, x, y, z, itemSpawnMode, pickupVar);
    return ApiStatus_DONE2;
}

API_CALLABLE(DropItemEntity) {
    Bytecode* args = script->ptrReadPos;
    s32 itemID = evt_get_variable(script, *args++);
    s32 x = evt_get_variable(script, *args++);
    s32 y = evt_get_variable(script, *args++);
    s32 z = evt_get_variable(script, *args++);
    s32 itemSpawnMode = evt_get_variable(script, *args++);
    s32 pickupVar = evt_get_variable(script, *args++);

    script->varTable[0] = make_item_entity_nodelay(itemID, x, y, z, itemSpawnMode, pickupVar);
    return ApiStatus_DONE2;
}

API_CALLABLE(DropResizableItemEntity) {
    Bytecode* args = script->ptrReadPos;
    s32 itemID = evt_get_variable(script, *args++);
    s32 x = evt_get_variable(script, *args++);
    s32 y = evt_get_variable(script, *args++);
    s32 z = evt_get_variable(script, *args++);
    s32 itemSpawnMode = evt_get_variable(script, *args++);
    s32 pickupVar = evt_get_variable_index(script, *args++);

    script->varTable[0] = make_item_entity_nodelay(itemID, x, y, z, itemSpawnMode, pickupVar);
    set_item_entity_flags(script->varTable[0], ITEM_ENTITY_RESIZABLE);
    return ApiStatus_DONE2;
}

API_CALLABLE(RemoveItemEntity) {
    Bytecode* args = script->ptrReadPos;
    s32 itemEntityIndex = evt_get_variable(script, *args++);

    remove_item_entity_by_index(itemEntityIndex);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetItemPos) {
    Bytecode* args = script->ptrReadPos;
    ItemEntity* ptrItemEntity;
    s32 itemEntityIndex;
    s32 x, y, z;

    itemEntityIndex = evt_get_variable(script, *args++);
    x = evt_get_variable(script, *args++);
    y = evt_get_variable(script, *args++);
    z = evt_get_variable(script, *args++);

    ptrItemEntity = (ItemEntity*) get_item_entity(itemEntityIndex);
    ptrItemEntity->pos.x = x;
    ptrItemEntity->pos.y = y;
    ptrItemEntity->pos.z = z;
    return ApiStatus_DONE2;
}

API_CALLABLE(SetItemFlags) {
    Bytecode* args = script->ptrReadPos;
    s32 itemEntityIndex = evt_get_variable(script, *args++);
    s32 flagBits = *args++;
    s32 mode = evt_get_variable(script, *args++);
    ItemEntity* itemEntity = get_item_entity(itemEntityIndex);

    if (mode != 0) {
        itemEntity->flags |= flagBits;
    } else {
        itemEntity->flags &= ~flagBits;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(SetItemAlpha) {
    Bytecode* args = script->ptrReadPos;
    s32 itemEntityIndex = evt_get_variable(script, *args++);
    s32 alpha = evt_get_variable(script, *args++);
    ItemEntity* itemEntity = get_item_entity(itemEntityIndex);

    itemEntity->alpha = alpha;
    return ApiStatus_DONE2;
}

API_CALLABLE(AddCoin) {
    script->varTable[0] = add_coins(evt_get_variable(script, *script->ptrReadPos));
    return ApiStatus_DONE2;
}

API_CALLABLE(AddStarPoints) {
    script->varTable[0] = add_star_points(evt_get_variable(script, *script->ptrReadPos));
    return ApiStatus_DONE2;
}

API_CALLABLE(AddStarPieces) {
    script->varTable[0] = add_star_pieces(evt_get_variable(script, *script->ptrReadPos));
    return ApiStatus_DONE2;
}

API_CALLABLE(GetItemPower) {
    Bytecode* args = script->ptrReadPos;
    s32 itemIdx = evt_get_variable(script, *args++);
    Bytecode out1 = *args++;
    Bytecode out2 = *args++;

    evt_set_variable(script, out1, (&gItemTable[itemIdx])->potencyA);
    evt_set_variable(script, out2, (&gItemTable[itemIdx])->potencyB);
    return ApiStatus_DONE2;
}

API_CALLABLE(ShowGotItem) {
    Bytecode* args = script->ptrReadPos;
    s32 itemID, unkCond, pickupMsgFlags;

    if (isInitialCall) {
        script->functionTemp[0] = false;
    }

    if (script->functionTemp[0]) {
        if (get_item_entity(script->functionTemp[1]) == nullptr) {
            return ApiStatus_DONE2;
         }
    } else {
        itemID = evt_get_variable(script, *args++);
        unkCond = evt_get_variable(script, *args++);
        pickupMsgFlags = *args++;
        script->functionTemp[1] = make_item_entity_at_player(itemID, unkCond, pickupMsgFlags);
        script->functionTemp[0] = true;
    }
    return ApiStatus_BLOCK;
}
