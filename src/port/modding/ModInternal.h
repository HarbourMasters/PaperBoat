#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace Mod {

inline std::string OwnerName(const char* owner) {
    return owner != nullptr && owner[0] != '\0' ? owner : "unknown";
}

template <typename T> class OwnerStack {
public:
    struct Entry {
        std::string owner;
        T value;
    };

    const std::string* Push(const std::string& owner, const T& value) {
        const std::string* previous = nullptr;
        if (!mEntries.empty() && mEntries.back().owner != owner) {
            mConflictOwner = mEntries.back().owner;
            previous = &mConflictOwner;
        }
        Remove(owner);
        mEntries.push_back({ owner, value });
        return previous;
    }

    bool Remove(const std::string& owner) {
        const auto end =
            std::remove_if(mEntries.begin(), mEntries.end(), [&](const Entry& e) { return e.owner == owner; });
        const bool removed = end != mEntries.end();
        mEntries.erase(end, mEntries.end());
        return removed;
    }

    bool Empty() const {
        return mEntries.empty();
    }

    const T& Top() const {
        return mEntries.back().value;
    }

private:
    std::vector<Entry> mEntries;
    std::string mConflictOwner;
};

void ListenServices();
void ListenAbilities();
void ListenActorExt();
void ListenBattleMenus();
void ListenBattleOverrides();
void ListenMapResetData();

void UnregisterScriptOverrides(const std::string& owner);
void UnregisterBattleOverrides(const std::string& owner);
void UnregisterMessages(const std::string& owner);
void UnregisterMaps(const std::string& owner);
void UnregisterEvtBuffers(const std::string& owner);
void UnregisterMapTextures(const std::string& owner);
void UnregisterItems(const std::string& owner);
void UnregisterAbilities(const std::string& owner);
void UnregisterSaveData(const std::string& owner);
void UnregisterActorExt(const std::string& owner);
void UnregisterBattleMenus(const std::string& owner);
void UnregisterPopups(const std::string& owner);
void UnregisterWindowStyles(const std::string& owner);
void UnregisterPanels(const std::string& owner);
void UnregisterItemCapacity(const std::string& owner);
void UnregisterInputFrameListeners(const std::string& owner);

} // namespace Mod
