#pragma once

#include <spdlog/spdlog.h>

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Gives each content id a number in [first, last] for the session. Save files store the numbers of the ids they use
// under the key and are renumbered when they load, so the numbers only need to agree within a session.
class StableIds {
public:
    StableIds(const char* key, int first, int last)
        : mKey(key)
        , mFirst(first)
        , mLast(last) {
        All().push_back(this);
    }

    // Number of a registered id. owner is the mod registering it.
    int Register(const std::string& id, const std::string& owner) {
        const int number = Get(id);
        if (number < 0) {
            return -1;
        }
        mActive.insert(number);
        if (!owner.empty()) {
            mIds[id].owner = owner;
        }
        return number;
    }

    void Unregister(int number) {
        mActive.erase(number);
    }

    bool IsActive(int number) const {
        return mActive.contains(number);
    }

    // Number of the id, giving it a free one the first time, preferred when that one is free. -1 when the range is
    // full.
    int Get(const std::string& id, int preferred = -1, const std::string& owner = {}) {
        if (auto it = mIds.find(id); it != mIds.end()) {
            return it->second.number;
        }
        int number = preferred >= mFirst && preferred <= mLast && !mById.contains(preferred) ? preferred : -1;
        for (int candidate = mFirst; number < 0 && candidate <= mLast; candidate++) {
            if (!mById.contains(candidate)) {
                number = candidate;
            }
        }
        if (number < 0) {
            SPDLOG_ERROR("{}: no numbers left for {}", mKey, id);
            return -1;
        }
        mIds[id] = { number, owner };
        mById[number] = id;
        return number;
    }

    // Id given the number, or nullptr.
    const std::string* IdOf(int number) {
        auto it = mById.find(number);
        return it != mById.end() ? &it->second : nullptr;
    }

    // Mod that last registered the id, empty when unknown.
    std::string Owner(const std::string& id) {
        auto it = mIds.find(id);
        return it != mIds.end() ? it->second.owner : std::string();
    }

    const std::string& Key() const {
        return mKey;
    }

    static std::vector<StableIds*>& All() {
        static std::vector<StableIds*> all;
        return all;
    }

    static StableIds* ForKey(const std::string& key) {
        for (StableIds* ids : All()) {
            if (ids->mKey == key) {
                return ids;
            }
        }
        return nullptr;
    }

private:
    struct Entry {
        int number = -1;
        std::string owner;
    };

    std::string mKey;
    int mFirst;
    int mLast;
    std::unordered_map<std::string, Entry> mIds;
    std::unordered_map<int, std::string> mById;
    std::unordered_set<int> mActive;
};
