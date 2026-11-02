#include "common.h"

BSS s32 N(FlowerGuard_ItemChoiceList)[ITEM_TABLE_CAPACITY + 1];

API_CALLABLE(N(FlowerGuard_SetItemEntityPosition)) {
    Bytecode* args = script->ptrReadPos;
    s32 itemIdx = evt_get_variable(script, *args++);
    s32 x = evt_get_variable(script, *args++);
    s32 y = evt_get_variable(script, *args++);
    s32 z = evt_get_variable(script, *args++);
    ItemEntity* item = get_item_entity(itemIdx);

    item->pos.x = x;
    item->pos.y = y;
    item->pos.z = z;

    return ApiStatus_DONE2;
}

API_CALLABLE(N(FlowerGuard_JudgeItemTastiness)) {
    s32 itemId = evt_get_variable(script, *script->ptrReadPos);
    ItemData* item = &gItemTable[itemId];

    if (itemId == ITEM_YUMMY_MEAL) {
        script->varTable[9] = 2;
    } else if (item->typeFlags & ITEM_TYPE_FLAG_FOOD_OR_DRINK) {
        script->varTable[9] = 1;
    } else {
        script->varTable[9] = 0;
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(N(FlowerGuard_MakeItemList)) {
    s32 pos = 0;
    s32 itemID;

    for (itemID = 0; itemID < gItemCount; itemID++) {
        if (item_is_consumable(itemID)) {
            N(FlowerGuard_ItemChoiceList)[pos++] = itemID;
        }
    }
    N(FlowerGuard_ItemChoiceList)[pos] = ITEM_NONE;

    return ApiStatus_DONE2;
}
