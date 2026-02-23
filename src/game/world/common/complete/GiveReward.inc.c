#ifndef _COMMON_GIVE_REWARD_H_
#define _COMMON_GIVE_REWARD_H_

#include "common.h"

static s32 N(varStashStorage)[16];
static s32 N(varStashActive) = false;

// TODO extracted from world/common/todo/StashVars to reduce warnings (for now)
API_CALLABLE(N(StashVars)) {
    s32 i;

    if (!N(varStashActive)) {
        for (i = 0; i < ARRAY_COUNT(script->varTable); i++) {
            N(varStashStorage)[i] = script->varTable[i];
        }
        N(varStashActive) = true;
    } else {
        for (i = 0; i < ARRAY_COUNT(script->varTable); i++) {
            script->varTable[i] = N(varStashStorage)[i];
        }
        N(varStashActive) = false;
    }

    return ApiStatus_DONE2;
}

#include "world/common/todo/GetItemName.inc.c"

EvtScript N(GiveItemReward) = {
    Call(ShowGotItem, LVar0, ITEM_TYPE_KEY, 0)
    Return
    Return
    End
};

EvtScript N(GiveCoinReward) = {
    Call(ShowGotItem, LVar0, ITEM_TYPE_KEY, ITEM_PICKUP_FLAG_1_COIN)
    Return
    Return
    End
};

#define EVT_GIVE_KEY_REWARD(itemID) \
    Set(LVar0, itemID) \
    Set(LVar1, ITEM_TYPE_KEY) \
    ExecWait(N(GiveItemReward)) \
    Call(AddKeyItem, itemID)

#define EVT_GIVE_BADGE_REWARD(itemID) \
    Set(LVar0, itemID) \
    Set(LVar1, ITEM_TYPE_BADGE) \
    ExecWait(N(GiveItemReward)) \
    Call(AddBadge, itemID, LVar0)

#define EVT_GIVE_BADGE_REWARD_ALT(itemID, outIdx) \
    Set(LVar0, itemID) \
    Set(LVar1, ITEM_TYPE_BADGE) \
    ExecWait(N(GiveItemReward)) \
    Call(AddBadge, LVar0, outIdx)

#define EVT_GIVE_CONSUMABLE_REWARD(itemID) \
    Set(LVar0, itemID) \
    Set(LVar1, ITEM_TYPE_CONSUMABLE) \
    ExecWait(N(GiveItemReward)) \
    Call(AddItem, LVar0, LVar1)

#define EVT_GIVE_CONSUMABLE_REWARD_ALT(itemID) \
    Set(LVar0, itemID) \
    Set(LVar1, ITEM_TYPE_CONSUMABLE) \
    ExecWait(N(GiveItemReward)) \
    Call(AddItem, itemID, LVar0)

#define EVT_GIVE_STAR_PIECE() \
    Set(LVar0, ITEM_STAR_PIECE) \
    Set(LVar1, ITEM_TYPE_STAR_PIECE) \
    ExecWait(N(GiveItemReward)) \
    Call(AddStarPieces, 1)

#define EVT_GIVE_COIN() \
    Set(LVar0, ITEM_COIN) \
    Set(LVar1, 0) \
    ExecWait(N(GiveCoinReward)) \
    Call(AddCoin, 1)

#endif
