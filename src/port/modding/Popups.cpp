#include "Popups.h"

#include <iterator>
#include <map>
#include <string>

#include <spdlog/spdlog.h>

#include "ModInternal.h"
#include "port/ShipInit.hpp"
#include "port/hooks/Events.h"

#include "common.h"

namespace {

struct BattlePopup {
    std::string owner;
    int32_t msgID;
    int32_t layoutLike;
};

std::map<int32_t, BattlePopup>& BattlePopups() {
    static std::map<int32_t, BattlePopup> sPopups;
    return sPopups;
}

void OnBattlePopupMessageListener(IEvent* event) {
    auto* ev = (OnBattlePopupMessage*) event;
    const auto& popups = BattlePopups();
    const auto it = popups.find(ev->index);

    if (it == popups.end()) {
        return;
    }
    *ev->layout = it->second.layoutLike;
    *ev->msgID = it->second.msgID;
}

void Listen() {
    REGISTER_LISTENER(OnBattlePopupMessage, EVENT_PRIORITY_NORMAL, OnBattlePopupMessageListener);
}

RegisterShipInitFunc sPopupsInit(Listen);

} // namespace

extern "C" int32_t Mod_RegisterBattlePopupAt(const char* owner, int32_t index, int32_t msgID, int32_t layoutLike) {
    const std::string name = Mod::OwnerName(owner);
    auto& popups = BattlePopups();

    if (index < 0 || index > MOD_BATTLE_POPUP_LAST) {
        SPDLOG_ERROR("Mod: {} registered battle popup {:#x}, out of range", name, index);
        return -1;
    }
    const auto it = popups.find(index);
    if (it != popups.end() && it->second.owner != name) {
        SPDLOG_ERROR("Mod: {} registered battle popup {:#x}, already owned by {}", name, index, it->second.owner);
        return -1;
    }
    popups[index] = { name, msgID, layoutLike };
    return index;
}

extern "C" int32_t Mod_RegisterBattlePopup(const char* owner, int32_t msgID, int32_t layoutLike) {
    const auto& popups = BattlePopups();

    for (int32_t index = MOD_BATTLE_POPUP_FIRST; index <= MOD_BATTLE_POPUP_LAST; index++) {
        if (popups.find(index) == popups.end()) {
            return Mod_RegisterBattlePopupAt(owner, index, msgID, layoutLike);
        }
    }
    SPDLOG_ERROR("Mod: {} registered a battle popup, but none is free", Mod::OwnerName(owner));
    return -1;
}

void Mod::UnregisterPopups(const std::string& owner) {
    auto& popups = BattlePopups();

    for (auto it = popups.begin(); it != popups.end();) {
        it = it->second.owner == owner ? popups.erase(it) : std::next(it);
    }
}
