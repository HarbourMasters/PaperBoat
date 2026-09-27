#include "SaveConverter.h"

#include <algorithm>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <utility>
#include <vector>

#include <spdlog/fmt/fmt.h>
#include <nlohmann/json.hpp>
#include <ship/Context.h>

#include "port/FilePicker.h"

#include "common.h"
#include "dx/config.h"
#include "dx/versioning.h"

extern "C" {
void ver_deserialize_vanilla_save(SaveData* save);
}

nlohmann::ordered_json ConvertSaveData_to_JSON(SaveData* saveData);
std::string CollapsedJSONArray(const nlohmann::ordered_json& jsonFile);

namespace fs = std::filesystem;

namespace SaveConverter {

namespace {

    constexpr char kMagic[] = "Mario Story 006";
    constexpr size_t kRegionStride = 0x4000; // one save per 16 KB region
    constexpr size_t kSaveRegions = 6;       // six physical saves, then two globals pages
    constexpr size_t kVanillaSize = 0x1380;  // sizeof(VanillaSaveData)

    struct SwapRun {
        size_t offset;
        size_t width;
        size_t count;
    };

    constexpr size_t kPlayer = 0x40;

    constexpr SwapRun kSwaps[] = {
        { 0x0030, 4, 4 },          // crc1, crc2, saveSlot, saveCount
        { kPlayer + 0x00C, 2, 1 }, // coins
        { kPlayer + 0x016, 2, 3 }, // partners[0].unk_02
        { kPlayer + 0x01E, 2, 3 },
        { kPlayer + 0x026, 2, 3 },
        { kPlayer + 0x02E, 2, 3 },
        { kPlayer + 0x036, 2, 3 },
        { kPlayer + 0x03E, 2, 3 },
        { kPlayer + 0x046, 2, 3 },
        { kPlayer + 0x04E, 2, 3 },
        { kPlayer + 0x056, 2, 3 },
        { kPlayer + 0x05E, 2, 3 },
        { kPlayer + 0x066, 2, 3 },
        { kPlayer + 0x06E, 2, 3 },   // ...partners[11].unk_02
        { kPlayer + 0x074, 2, 32 },  // keyItems
        { kPlayer + 0x0B4, 2, 128 }, // badges
        { kPlayer + 0x1B4, 2, 10 },  // invItems
        { kPlayer + 0x1C8, 2, 32 },  // storedItems
        { kPlayer + 0x208, 2, 64 },  // equippedBadges
        { kPlayer + 0x28C, 2, 1 },   // merleeTurnCount
        { kPlayer + 0x290, 2, 1 },   // starPower
        { kPlayer + 0x294, 2, 12 },  // actionCommandAttempts .. trainingsDone
        { kPlayer + 0x2AC, 4, 3 },   // walkingStepsTaken, runningStepsTaken, totalCoinsEarned
        { kPlayer + 0x2B8, 2, 1 },   // idleFrameCounter
        { kPlayer + 0x2BC, 4, 1 },   // frameCounter
        { kPlayer + 0x2C0, 2, 2 },   // quizzesAnswered, quizzesCorrect
        { kPlayer + 0x2C4, 4, 12 },  // partnerUnlockedTime
        { kPlayer + 0x2F4, 4, 12 },  // partnerUsedTime
        { kPlayer + 0x324, 4, 2 },   // tradeEventStartTime, droTreeHintTime
        { kPlayer + 0x32C, 2, 2 },   // starPiecesCollected, jumpGamePlays
        { kPlayer + 0x330, 4, 1 },   // jumpGameTotal
        { kPlayer + 0x334, 2, 2 },   // jumpGameRecord, smashGamePlays
        { kPlayer + 0x338, 4, 1 },   // smashGameTotal
        { kPlayer + 0x33C, 2, 1 },   // smashGameRecord
        { 0x0468, 2, 3 },            // areaID, mapID, entryID
        { 0x0470, 4, 720 },          // enemyDefeatFlags[60][12]
        { 0x0FB0, 4, 64 },           // globalFlags
        { 0x12B0, 4, 8 },            // areaFlags
        { 0x12E6, 2, 3 },            // savePos
        { 0x12EC, 4, 1 },            // summary.timePlayed
    };

    uint32_t ReadBE32(const uint8_t* p) {
        return ((uint32_t) p[0] << 24) | ((uint32_t) p[1] << 16) | ((uint32_t) p[2] << 8) | p[3];
    }

    void SwapWords(std::vector<uint8_t>& bytes) {
        for (size_t i = 0; i + 3 < bytes.size(); i += 4) {
            std::swap(bytes[i], bytes[i + 3]);
            std::swap(bytes[i + 1], bytes[i + 2]);
        }
    }

    size_t FindFlashBase(const std::vector<uint8_t>& bytes) {
        const size_t len = sizeof(kMagic) - 1;
        if (bytes.size() < kVanillaSize) {
            return std::string::npos;
        }
        for (size_t i = 0; i + kVanillaSize <= bytes.size(); i += 4) {
            if (std::memcmp(bytes.data() + i, kMagic, len) == 0) {
                return i;
            }
        }
        return std::string::npos;
    }

    bool RegionIsValid(const uint8_t* region) {
        if (std::memcmp(region, kMagic, sizeof(kMagic) - 1) != 0) {
            return false;
        }
        const uint32_t crc1 = ReadBE32(region + 0x30);
        const uint32_t crc2 = ReadBE32(region + 0x34);
        if (crc1 != ~crc2) {
            return false;
        }
        uint32_t sum = 0;
        for (size_t i = 0; i < kVanillaSize; i += 4) {
            sum += ReadBE32(region + i);
        }
        return sum == crc1;
    }

    void SwapFields(uint8_t* save) {
        for (const SwapRun& run : kSwaps) {
            for (size_t i = 0; i < run.count; i++) {
                uint8_t* p = save + run.offset + i * run.width;
                std::reverse(p, p + run.width);
            }
        }
    }

    bool WriteSave(SaveData* saveData, int slotIndex) {
        const nlohmann::ordered_json json = ConvertSaveData_to_JSON(saveData);
        if (json.empty()) {
            return false;
        }
        const std::string dir = Ship::Context::GetPathRelativeToAppDirectory("saves/", "pm64");
        std::error_code ec;
        if (!fs::exists(dir)) {
            fs::create_directories(dir, ec);
        }
        std::ofstream out(dir + fmt::format("file{}.json", slotIndex));
        if (!out.is_open()) {
            return false;
        }
        out << CollapsedJSONArray(json);
        return out.good();
    }

} // namespace

Result ImportFromFlash(const std::string& srcPath, int srcSlot, int destSlot) {
    Result res;

    std::ifstream in(srcPath, std::ios::binary);
    if (!in) {
        res.message = "Couldn't open the selected file.";
        return res;
    }
    std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    size_t base = FindFlashBase(bytes);
    if (base == std::string::npos) {
        SwapWords(bytes);
        base = FindFlashBase(bytes);
    }
    if (base == std::string::npos) {
        res.message = "That doesn't look like a Paper Mario save file.";
        return res;
    }

    const uint8_t* newest[kSlotCount] = {};
    int32_t newestCount[kSlotCount] = {};
    for (size_t r = 0; r < kSaveRegions; r++) {
        const size_t off = base + r * kRegionStride;
        if (off + kVanillaSize > bytes.size()) {
            break;
        }
        const uint8_t* region = bytes.data() + off;
        if (!RegionIsValid(region)) {
            continue;
        }
        const int32_t slot = (int32_t) ReadBE32(region + 0x38);
        const int32_t count = (int32_t) ReadBE32(region + 0x3C);
        if (slot < 0 || slot >= kSlotCount) {
            continue;
        }
        if (newest[slot] == nullptr || count > newestCount[slot]) {
            newest[slot] = region;
            newestCount[slot] = count;
        }
    }

    std::vector<std::pair<int, int>> wanted;
    if (srcSlot == kSlotAll) {
        for (int i = 0; i < kSlotCount; i++) {
            wanted.emplace_back(i, i);
        }
    } else if (srcSlot >= 1 && srcSlot <= kSlotCount && destSlot >= 1 && destSlot <= kSlotCount) {
        wanted.emplace_back(srcSlot - 1, destSlot - 1);
    } else {
        res.message = "That isn't a slot this game has.";
        return res;
    }

    s32 savedDefeatFlags[60][12];
    std::memcpy(savedDefeatFlags, gCurrentEncounter.defeatFlags, sizeof(savedDefeatFlags));

    std::vector<int> failed;
    for (auto [from, to] : wanted) {
        if (newest[from] == nullptr) {
            continue;
        }
        std::vector<uint8_t> buffer((std::max) (sizeof(SaveData), kVanillaSize), 0);
        std::memcpy(buffer.data(), newest[from], kVanillaSize);
        SwapFields(buffer.data());

        SaveData* saveData = (SaveData*) buffer.data();
        ver_deserialize_vanilla_save(saveData);
        saveData->saveSlot = to;
        strcpy(saveData->modName, DX_MOD_NAME);
        saveData->majorVersion = DX_MOD_VER_MAJOR;
        saveData->minorVersion = DX_MOD_VER_MINOR;
        saveData->patchVersion = DX_MOD_VER_PATCH;

        if (WriteSave(saveData, to)) {
            res.slotsImported++;
        } else {
            failed.push_back(to + 1);
        }
    }

    std::memcpy(gCurrentEncounter.defeatFlags, savedDefeatFlags, sizeof(gCurrentEncounter.defeatFlags));

    if (!failed.empty()) {
        res.message = fmt::format("Couldn't write slot {}.", failed[0]);
        return res;
    }
    if (res.slotsImported == 0) {
        res.message = srcSlot == kSlotAll ? "That file has no save slots in it."
                                          : fmt::format("That file has nothing in slot {}.", srcSlot);
        return res;
    }

    res.ok = true;
    res.message = res.slotsImported == 1
        ? "Save file imported. Restart Paperboat to see it."
        : fmt::format("Imported {} slots. Restart Paperboat to see them.", res.slotsImported);
    return res;
}

void PickAndImport(int srcSlot, int destSlot, std::function<void(Result)> onComplete) {
    Ship::FileBrowserRequest req;
    req.Title = "Select a save to import";
    req.Filters = { { "All Files", { "*" } } };
    Paperboat::PickFile(std::move(req), [srcSlot, destSlot, onComplete](std::optional<fs::path> path) {
        if (!path) {
            if (onComplete) {
                onComplete({});
            }
            return;
        }
        Result r = ImportFromFlash(path->string(), srcSlot, destSlot);
        if (onComplete) {
            onComplete(r);
        }
    });
}

} // namespace SaveConverter
