#include "port/ShipInit.hpp"
#include "port/hooks/Events.h"

#include "common.h"
#include "game_modes.h"

#include <map>

namespace {

struct Snapshot {
    int coins = 0;
    int starPoints = 0;
    int starPieces = 0;
    int hp = 0;
    int fp = 0;
    std::map<s16, int> items;
};

Snapshot sLast;
bool sActive = false;

Snapshot Take() {
    const PlayerData& player = gPlayerData;
    Snapshot snapshot;
    snapshot.coins = player.coins;
    snapshot.starPoints = player.starPoints;
    snapshot.starPieces = player.starPieces;
    snapshot.hp = player.curHP;
    snapshot.fp = player.curFP;
    const auto add = [&](const s16* list, size_t count) {
        for (size_t i = 0; i < count; i++) {
            if (list[i] != ITEM_NONE) {
                snapshot.items[list[i]]++;
            }
        }
    };
    add(player.invItems, ARRAY_COUNT(player.invItems));
    add(player.keyItems, ARRAY_COUNT(player.keyItems));
    add(player.badges, ARRAY_COUNT(player.badges));
    add(player.storedItems, ARRAY_COUNT(player.storedItems));
    return snapshot;
}

bool InPlay() {
    if (!sActive || gGameStatusPtr->demoState != DEMO_STATE_NONE) {
        return false;
    }
    switch (get_game_mode()) {
        case GAME_MODE_WORLD:
        case GAME_MODE_CHANGE_MAP:
        case GAME_MODE_BATTLE:
        case GAME_MODE_END_BATTLE:
        case GAME_MODE_PAUSE:
        case GAME_MODE_UNPAUSE:
        case GAME_MODE_GAME_OVER:
            return true;
        default:
            return false;
    }
}

void Compare() {
    Snapshot now = Take();
    if (!InPlay()) {
        sLast = std::move(now);
        return;
    }
    const Snapshot before = std::move(sLast);
    sLast = now;

    if (now.coins != before.coins) {
        CALL_EVENT(OnCoinsChanged, before.coins, now.coins);
    }
    if (now.starPoints != before.starPoints) {
        CALL_EVENT(OnStarPointsChanged, before.starPoints, now.starPoints);
    }
    if (now.starPieces != before.starPieces) {
        CALL_EVENT(OnStarPiecesChanged, before.starPieces, now.starPieces);
    }
    if (now.hp != before.hp) {
        CALL_EVENT(OnHPChanged, before.hp, now.hp);
    }
    if (now.fp != before.fp) {
        CALL_EVENT(OnFPChanged, before.fp, now.fp);
    }
    for (const auto& [item, count] : now.items) {
        auto it = before.items.find(item);
        const int previous = it != before.items.end() ? it->second : 0;
        if (count != previous) {
            CALL_EVENT(OnItemCountChanged, item, previous, count);
        }
    }
    for (const auto& [item, count] : before.items) {
        if (!now.items.contains(item)) {
            CALL_EVENT(OnItemCountChanged, item, count, 0);
        }
    }
}

void InitEventWatch() {
    REGISTER_LISTENER(GameFrameUpdate, EVENT_PRIORITY_NORMAL, [](IEvent* event) { Compare(); });
    REGISTER_LISTENER(OnSaveFileLoad, EVENT_PRIORITY_NORMAL, [](IEvent* event) { sActive = false; });
    REGISTER_LISTENER(OnSaveFileStart, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        sActive = true;
        sLast = Take();
    });
}

RegisterShipInitFunc sInitEventWatch(InitEventWatch);

} // namespace
