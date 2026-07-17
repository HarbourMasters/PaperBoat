#include "SaveManager.h"
#include "SaveTypes.h"
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <libultraship/bridge/consolevariablebridge.h>
#include "port/ShipUtils.h"
#include <fstream>
#include <filesystem>
#include <regex>

extern "C" {
#include "dx/versioning.h"

extern SaveData gCurrentSaveFile;
}

using nlohmann::json;
using nlohmann::ordered_json;
namespace fs = std::filesystem;

std::string CollapsedJSONArray(const nlohmann::ordered_json& jsonFile) {
    std::string source = jsonFile.dump(4);
    std::string result;
    result.reserve(source.length());

    bool isCollapsed = false;

    for (size_t i = 0; i < source.length(); ++i) {
        char c = source[i];

        if (c == '[') {
            size_t next = source.find_first_not_of(" \n\r\t", i + 1);
            if (next != std::string::npos && (isdigit(source[next]) || source[next] == '-' || source[next] == ']')) {
                isCollapsed = true;
                result += c;
                continue;
            }
        }

        if (isCollapsed) {
            if (isspace(c)) {
                continue;
            }

            if (c == ']') {
                isCollapsed = false;
                result += c;
            }
            else if (c == ',') {
                result += ", ";
            }
            else {
                result += c;
            }
        }
        else {
            result += c;
        }
    }

    return result;
}

SaveData* ConvertJSON_to_SaveData(nlohmann::json jsonSaveFile) {
    SaveData* saveData = new SaveData();

    strncpy(saveData->magicString, jsonSaveFile["magicString"].get_ref<const std::string&>().c_str(), sizeof(saveData->magicString) - 1);
    strncpy(saveData->modName, jsonSaveFile["modName"].get_ref<const std::string&>().c_str(), sizeof(saveData->modName) - 1);
    saveData->majorVersion = jsonSaveFile["majorVersion"];
    saveData->minorVersion = jsonSaveFile["minorVersion"];
    saveData->patchVersion = jsonSaveFile["patchVersion"];

    saveData->reserved = jsonSaveFile["reserved"].get<int>();
    saveData->crc1 = jsonSaveFile["crc1"];
    saveData->crc2 = jsonSaveFile["crc2"];

    saveData->saveSlot = jsonSaveFile["saveSlot"];
    saveData->saveCount = jsonSaveFile["saveCount"];

    ordered_json jsonPlayer = jsonSaveFile["player"];
    saveData->player.bootsLevel = jsonPlayer["bootsLevel"];
    saveData->player.hammerLevel = jsonPlayer["hammerLevel"];
    saveData->player.curHP = jsonPlayer["curHP"];
    saveData->player.curMaxHP = jsonPlayer["curMaxHP"];
    saveData->player.hardrMaxHP = jsonPlayer["hardMaxHP"];
    saveData->player.curFP = jsonPlayer["curFP"];
    saveData->player.curMaxFP = jsonPlayer["curMaxFP"];
    saveData->player.hardMaxFP = jsonPlayer["hardMaxFP"];
    saveData->player.maxBP = jsonPlayer["maxBP"];
    saveData->player.level = jsonPlayer["level"];
    saveData->player.hasActionCommands = jsonPlayer["hasActionCommands"];
    saveData->player.coins = jsonPlayer["coins"];
    saveData->player.starPieces = jsonPlayer["starPieces"];
    saveData->player.starPoints = jsonPlayer["starPoints"];
    saveData->player.curPartner = jsonPlayer["curPartner"];

    ordered_json jsonPartners = jsonPlayer["partners"];
    for (int p = 0; p < MAX_PARTNERS; p++) {
        saveData->player.partners[p].enabled = jsonPartners[p]["enabled"];
        saveData->player.partners[p].level = jsonPartners[p]["level"];

        // TODO: Check if these are ever not Zero and remove.
        for (int pu = 0; pu < 3; pu++) {
            saveData->player.partners[p].unk_02[pu] = jsonPartners[p]["unk_02"][pu];
        }
    }

    ordered_json jsonKeyItems = jsonPlayer["keyItems"];
    for (int ki = 0; ki < MAX_KEYITEMS; ki++) {
        saveData->player.keyItems[ki] = jsonKeyItems[ki];
    }

    ordered_json jsonBadges = jsonPlayer["badges"];
    for (int b = 0; b < MAX_BADGES; b++) {
        saveData->player.badges[b] = jsonBadges[b];
    }

    ordered_json jsonInvItems = jsonPlayer["invItems"];
    for (int ii = 0; ii < MAX_INVITEMS; ii++) {
        saveData->player.invItems[ii] = jsonInvItems[ii];
    }

    ordered_json jsonStoredItems = jsonPlayer["storedItems"];
    for (int si = 0; si < MAX_STOREDITEMS; si++) {
        saveData->player.storedItems[si] = jsonStoredItems[si];
    }

    ordered_json jsonEquippedBadges = jsonPlayer["equippedBadges"];
    for (int eb = 0; eb < MAX_EQUIPPEDBADGES; eb++) {
        saveData->player.equippedBadges[eb] = jsonEquippedBadges[eb];
    }

    saveData->player.merleeSpellType = jsonPlayer["merleeSpellType"];
    saveData->player.merleeCastsLeft = jsonPlayer["merleeCastsLeft"];
    saveData->player.merleeTurnCount = jsonPlayer["merleeTurnCount"];
    saveData->player.maxStarPower = jsonPlayer["maxStarPower"];
    saveData->player.starPower = jsonPlayer["starPower"];
    saveData->player.starBeamLevel = jsonPlayer["starBeamLevel"];
    saveData->player.actionCommandAttempts = jsonPlayer["actionCommandAttempts"];
    saveData->player.actionCommandSuccesses = jsonPlayer["actionCommandSuccesses"];
    saveData->player.hitsTaken = jsonPlayer["hitsTaken"];
    saveData->player.hitsBlocked = jsonPlayer["hitsBlocked"];
    saveData->player.playerFirstStrikes = jsonPlayer["playerFirstStrikes"];
    saveData->player.enemyFirstStrikes = jsonPlayer["enemyFirstStrikes"];
    saveData->player.powerBounces = jsonPlayer["powerBounces"];
    saveData->player.battlesCount = jsonPlayer["battlesCount"];
    saveData->player.battlesWon = jsonPlayer["battlesWon"];
    saveData->player.fleeAttempts = jsonPlayer["fleeAttempts"];
    saveData->player.battlesFled = jsonPlayer["battlesFled"];
    saveData->player.trainingsDone = jsonPlayer["trainingsDone"];
    saveData->player.walkingStepsTaken = jsonPlayer["walkingStepsTaken"];
    saveData->player.runningStepsTaken = jsonPlayer["runningStepsTaken"];
    saveData->player.totalCoinsEarned = jsonPlayer["totalCoinsEarned"];
    saveData->player.idleFrameCounter = jsonPlayer["idleFrameCounter"];
    saveData->player.frameCounter = jsonPlayer["frameCounter"];
    saveData->player.quizzesAnswered = jsonPlayer["quizzesAnswered"];
    saveData->player.quizzesCorrect = jsonPlayer["quizzesCorrect"];

    ordered_json jsonPartnerUnlockTime = jsonPlayer["partnerUnlockedTime"];
    for (int pt = 0; pt < MAX_PARTNERUNLOCKTIME; pt++) {
        saveData->player.partnerUnlockedTime[pt] = jsonPartnerUnlockTime[pt];
    }

    ordered_json jsonPartnerUsedTime = jsonPlayer["partnerUsedTime"];
    for (int put = 0; put < MAX_PARTNERUSEDTIME; put++) {
        saveData->player.partnerUnlockedTime[put] = jsonPartnerUsedTime[put];
    }

    saveData->player.tradeEventStartTime = jsonPlayer["tradeEventStartTime"];
    saveData->player.droTreeHintTime = jsonPlayer["droTreeHintTime"];
    saveData->player.starPiecesCollected = jsonPlayer["starPiecesCollected"];
    saveData->player.jumpGamePlays = jsonPlayer["jumpGamePlays"];
    saveData->player.jumpGameTotal = jsonPlayer["jumpGameTotal"];
    saveData->player.jumpGameRecord = jsonPlayer["jumpGameRecord"];
    saveData->player.smashGamePlays = jsonPlayer["smashGamePlays"];
    saveData->player.smashGameTotal = jsonPlayer["smashGameTotal"];
    saveData->player.smashGameRecord = jsonPlayer["smashGameRecord"];

    saveData->areaID = jsonSaveFile["areaID"];
    saveData->mapID = jsonSaveFile["mapID"];
    saveData->entryID = jsonSaveFile["entryID"];

    saveData->unk_46E[0] = jsonSaveFile["unk_46E"][0];
    saveData->unk_46E[1] = jsonSaveFile["unk_46E"][1];

    ordered_json jsonEnemyDefeatFlags = jsonSaveFile["enemyDefeatFlags"];
    for (int en = 0; en < MAX_ENEMYDEFEATFLAGINDEX; en++) {
        ordered_json jsonEnemyData = jsonEnemyDefeatFlags[en];
        for (int ed = 0; ed < MAX_ENEMYDEFEATFLAGDATA; ed++) {
            saveData->enemyDefeatFlags[en][ed] = jsonEnemyData[ed];
        }
    }

    ordered_json jsonGlobalFlags = jsonSaveFile["globalFlags"];
    for (int gf = 0; gf < MAX_GLOBALFLAGS; gf++) {
        saveData->globalFlags[gf] = jsonGlobalFlags[gf];
    }

    ordered_json jsonGlobalBytes = jsonSaveFile["globalBytes"];
    for (int gb = 0; gb < MAX_GLOBALBYTES; gb++) {
        saveData->globalBytes[gb] = jsonGlobalBytes[gb];
    }

    ordered_json jsonAreaFlags = jsonSaveFile["areaFlags"];
    for (int af = 0; af < MAX_AREAFLAGS; af++) {
        saveData->areaFlags[af] = jsonAreaFlags[af];
    }

    ordered_json jsonAreaBytes = jsonSaveFile["areaBytes"];
    for (int ab = 0; ab < MAX_AREABYTES; ab++) {
        saveData->areaBytes[ab] = jsonAreaBytes[ab];
    }

    saveData->debugEnemyContact = jsonSaveFile["debugEnemyContact"];
    saveData->debugUnused1 = jsonSaveFile["debugUnused1"];
    saveData->debugUnused2 = jsonSaveFile["debugUnused2"];

    saveData->musicEnabled = jsonSaveFile["musicEnabled"];

    saveData->unk_12E4[0] = jsonSaveFile["unk_12E4"][0];
    saveData->unk_12E4[1] = jsonSaveFile["unk_12E4"][1];

    Vec3s position = { jsonSaveFile["savePos"][0], jsonSaveFile["savePos"][1], jsonSaveFile["savePos"][2] };
    saveData->savePos = position;

    ordered_json jsonSummary = jsonSaveFile["summary"];
    saveData->summary.timePlayed = jsonSummary["timePlayed"];
    saveData->summary.spiritsRescued = jsonSummary["spiritsRescued"];
    saveData->summary.unused_05[0] = jsonSummary["unused_05"][0];
    saveData->summary.level = jsonSummary["level"];

    for (int fn = 0; fn < MAX_FILENAME; fn++) {
        int val = 0;
        if (jsonSummary["filename"][fn] < 0) {
            val = jsonSummary["filename"][fn].get<int>() + 256;
        } else {
            val = jsonSummary["filename"][fn];
        }
        saveData->summary.filename[fn] = static_cast<char>(static_cast<unsigned char>(val));
    }

    ordered_json jsonUnused_0F = jsonSummary["unused_0F"];
    for (int uf = 0; uf < MAX_UNUSED0F; uf++) {
        saveData->summary.unused_0F[uf] = jsonUnused_0F[uf];
    }

    ordered_json jsonUnk1304 = jsonSaveFile["unk_1304"];
    for (int un = 0; un < MAX_UNK1304; un++) {
        saveData->unk_1304[un] = jsonUnk1304[un];
    }

    return saveData;
}

ordered_json ConvertSaveData_to_JSON(SaveData* saveData) {
    ordered_json jsonSave = ordered_json::object();

    jsonSave["magicString"] = saveData->magicString;
    jsonSave["modName"] = saveData->modName;
    jsonSave["majorVersion"] = saveData->majorVersion;
    jsonSave["minorVersion"] = saveData->minorVersion;
    jsonSave["patchVersion"] = saveData->patchVersion;

    jsonSave["reserved"] = saveData->reserved;
    jsonSave["crc1"] = saveData->crc1;
    jsonSave["crc2"] = saveData->crc2;

    jsonSave["saveSlot"] = saveData->saveSlot;
    jsonSave["saveCount"] = saveData->saveCount;

    // PlayerData player
    ordered_json jsonPlayerData = ordered_json::object();
    jsonPlayerData["bootsLevel"] = saveData->player.bootsLevel;
    jsonPlayerData["hammerLevel"] = saveData->player.hammerLevel;
    jsonPlayerData["curHP"] = saveData->player.curHP;
    jsonPlayerData["curMaxHP"] = saveData->player.curMaxHP;
    jsonPlayerData["hardMaxHP"] = saveData->player.hardMaxHP;
    jsonPlayerData["curFP"] = saveData->player.curFP;
    jsonPlayerData["curMaxFP"] = saveData->player.curMaxFP;
    jsonPlayerData["hardMaxFP"] = saveData->player.hardMaxFP;
    jsonPlayerData["maxBP"] = saveData->player.maxBP;
    jsonPlayerData["level"] = saveData->player.level;
    jsonPlayerData["hasActionCommands"] = saveData->player.hasActionCommands;
    jsonPlayerData["coins"] = saveData->player.coins;
    jsonPlayerData["starPieces"] = saveData->player.starPieces;
    jsonPlayerData["starPoints"] = saveData->player.starPoints;
    jsonPlayerData["curPartner"] = saveData->player.curPartner;

    ordered_json jsonPartners = ordered_json::array();
    for (int p = 0; p < MAX_PARTNERS; p++) {
        ordered_json partnerEntry = ordered_json::object();
        partnerEntry["enabled"] = saveData->player.partners[p].enabled;
        partnerEntry["level"] = saveData->player.partners[p].level;

        // TODO: Check if this is ever not Zero and remove it from save file.
        ordered_json partnerUnk_02 = ordered_json::array();
        for (int pu = 0; pu < 3; pu++) {
            partnerUnk_02.push_back(saveData->player.partners[p].unk_02[pu]);
        }
        partnerEntry["unk_02"] = partnerUnk_02;

        jsonPartners.push_back(partnerEntry);
    }
    jsonPlayerData["partners"] = jsonPartners;

    ordered_json jsonKeyItems = ordered_json::array();
    for (int ki = 0; ki < MAX_KEYITEMS; ki++) {
        jsonKeyItems.push_back(saveData->player.keyItems[ki]);
    }
    jsonPlayerData["keyItems"] = jsonKeyItems;

    ordered_json jsonBadges = ordered_json::array();
    for (int b = 0; b < MAX_BADGES; b++) {
        jsonBadges.push_back(saveData->player.badges[b]);
    }
    jsonPlayerData["badges"] = jsonBadges;

    ordered_json jsonInvItems = ordered_json::array();
    for (int ii = 0; ii < MAX_INVITEMS; ii++) {
        jsonInvItems.push_back(saveData->player.invItems[ii]);
    }
    jsonPlayerData["invItems"] = jsonInvItems;

    ordered_json jsonStoredItems = ordered_json::array();
    for (int si = 0; si < MAX_STOREDITEMS; si++) {
        jsonStoredItems.push_back(saveData->player.storedItems[si]);
    }
    jsonPlayerData["storedItems"] = jsonStoredItems;

    ordered_json jsonEquippedBadges = ordered_json::array();
    for (int eb = 0; eb < MAX_EQUIPPEDBADGES; eb++) {
        jsonEquippedBadges.push_back(saveData->player.equippedBadges[eb]);
    }
    jsonPlayerData["equippedBadges"] = jsonEquippedBadges;

    jsonPlayerData["merleeSpellType"] = saveData->player.merleeSpellType;
    jsonPlayerData["merleeCastsLeft"] = saveData->player.merleeCastsLeft;
    jsonPlayerData["merleeTurnCount"] = saveData->player.merleeTurnCount;
    jsonPlayerData["maxStarPower"] = saveData->player.maxStarPower;
    jsonPlayerData["starPower"] = saveData->player.starPower;
    jsonPlayerData["starBeamLevel"] = saveData->player.starBeamLevel;
    jsonPlayerData["actionCommandAttempts"] = saveData->player.actionCommandAttempts;
    jsonPlayerData["actionCommandSuccesses"] = saveData->player.actionCommandSuccesses;
    jsonPlayerData["hitsTaken"] = saveData->player.hitsTaken;
    jsonPlayerData["hitsBlocked"] = saveData->player.hitsBlocked;
    jsonPlayerData["playerFirstStrikes"] = saveData->player.playerFirstStrikes;
    jsonPlayerData["enemyFirstStrikes"] = saveData->player.enemyFirstStrikes;
    jsonPlayerData["powerBounces"] = saveData->player.powerBounces;
    jsonPlayerData["battlesCount"] = saveData->player.battlesCount;
    jsonPlayerData["battlesWon"] = saveData->player.battlesWon;
    jsonPlayerData["fleeAttempts"] = saveData->player.fleeAttempts;
    jsonPlayerData["battlesFled"] = saveData->player.battlesFled;
    jsonPlayerData["trainingsDone"] = saveData->player.trainingsDone;
    jsonPlayerData["walkingStepsTaken"] = saveData->player.walkingStepsTaken;
    jsonPlayerData["runningStepsTaken"] = saveData->player.runningStepsTaken;
    jsonPlayerData["totalCoinsEarned"] = saveData->player.totalCoinsEarned;
    jsonPlayerData["idleFrameCounter"] = saveData->player.idleFrameCounter;
    jsonPlayerData["frameCounter"] = saveData->player.frameCounter;
    jsonPlayerData["quizzesAnswered"] = saveData->player.quizzesAnswered;
    jsonPlayerData["quizzesCorrect"] = saveData->player.quizzesCorrect;

    ordered_json jsonPartnerUnlockTime = ordered_json::array();
    for (int pt = 0; pt < MAX_PARTNERUNLOCKTIME; pt++) {
        jsonPartnerUnlockTime.push_back(saveData->player.partnerUnlockedTime[pt]);
    }
    jsonPlayerData["partnerUnlockedTime"] = jsonPartnerUnlockTime;

    ordered_json jsonPartnerUsedTime = ordered_json::array();
    for (int put = 0; put < MAX_PARTNERUSEDTIME; put++) {
        jsonPartnerUsedTime.push_back(saveData->player.partnerUsedTime[put]);
    }
    jsonPlayerData["partnerUsedTime"] = jsonPartnerUsedTime;

    jsonPlayerData["tradeEventStartTime"] = saveData->player.tradeEventStartTime;
    jsonPlayerData["droTreeHintTime"] = saveData->player.droTreeHintTime;
    jsonPlayerData["starPiecesCollected"] = saveData->player.starPiecesCollected;
    jsonPlayerData["jumpGamePlays"] = saveData->player.jumpGamePlays;
    jsonPlayerData["jumpGameTotal"] = saveData->player.jumpGameTotal;
    jsonPlayerData["jumpGameRecord"] = saveData->player.jumpGameRecord;
    jsonPlayerData["smashGamePlays"] = saveData->player.smashGamePlays;
    jsonPlayerData["smashGameTotal"] = saveData->player.smashGameTotal;
    jsonPlayerData["smashGameRecord"] = saveData->player.smashGameRecord;

    jsonSave["player"] = jsonPlayerData;

    jsonSave["areaID"] = saveData->areaID;
    jsonSave["mapID"] = saveData->mapID;
    jsonSave["entryID"] = saveData->entryID;

    jsonSave["unk_46E"] = saveData->unk_46E;

    ordered_json jsonEnemyDefeatFlags = ordered_json::array();
    for (int en = 0; en < MAX_ENEMYDEFEATFLAGINDEX; en++) {
        ordered_json jsonEnemyData = ordered_json::array();
        for (int ed = 0; ed < MAX_ENEMYDEFEATFLAGDATA; ed++) {
            jsonEnemyData.push_back(saveData->enemyDefeatFlags[en][ed]);
        }
        jsonEnemyDefeatFlags.push_back(jsonEnemyData);
    }
    jsonSave["enemyDefeatFlags"] = jsonEnemyDefeatFlags;

    ordered_json jsonGlobalFlags = ordered_json::array();
    for (int gf = 0; gf < MAX_GLOBALFLAGS; gf++) {
        jsonGlobalFlags.push_back(saveData->globalFlags[gf]);
    }
    jsonSave["globalFlags"] = jsonGlobalFlags;

    ordered_json jsonGlobalBytes = ordered_json::array();
    for (int gb = 0; gb < MAX_GLOBALBYTES; gb++) {
        jsonGlobalBytes.push_back(saveData->globalBytes[gb]);
    }
    jsonSave["globalBytes"] = jsonGlobalBytes;

    ordered_json jsonAreaFlags = ordered_json::array();
    for (int af = 0; af < MAX_AREAFLAGS; af++) {
        jsonAreaFlags.push_back(saveData->areaFlags[af]);
    }
    jsonSave["areaFlags"] = jsonAreaFlags;

    ordered_json jsonAreaBytes = ordered_json::array();
    for (int ab = 0; ab < MAX_AREABYTES; ab++) {
        jsonAreaBytes.push_back(saveData->areaBytes[ab]);
    }
    jsonSave["areaBytes"] = jsonAreaBytes;

    jsonSave["debugEnemyContact"] = saveData->debugEnemyContact;
    jsonSave["debugUnused1"] = saveData->debugUnused1;
    jsonSave["debugUnused2"] = saveData->debugUnused2;

    jsonSave["musicEnabled"] = saveData->musicEnabled;

    jsonSave["unk_12E4"] = saveData->unk_12E4;

    ordered_json jsonPos = ordered_json::array();
    jsonPos.push_back(saveData->savePos.x);
    jsonPos.push_back(saveData->savePos.y);
    jsonPos.push_back(saveData->savePos.z);

    jsonSave["savePos"] = jsonPos;

    ordered_json jsonSaveFileSummary = ordered_json::object();
    jsonSaveFileSummary["timePlayed"] = saveData->summary.timePlayed;
    jsonSaveFileSummary["spiritsRescued"] = saveData->summary.spiritsRescued;
    jsonSaveFileSummary["unused_05"] = saveData->summary.unused_05;
    jsonSaveFileSummary["level"] = saveData->summary.level;

    ordered_json jsonFileName = ordered_json::array();
    for (int fn = 0; fn < MAX_FILENAME; fn++) {
        jsonFileName.push_back(saveData->summary.filename[fn]);
    }
    jsonSaveFileSummary["filename"] = jsonFileName;

    jsonSaveFileSummary["unused_0F"] = saveData->summary.unused_0F;

    jsonSave["summary"] = jsonSaveFileSummary;

    jsonSave["unk_1304"] = saveData->unk_1304;

    return jsonSave;
}

void SaveManager_Init() {
    REGISTER_LISTENER(OnSaveFileSave, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnSaveFileSave* ev = (OnSaveFileSave*)event;
        event->Cancelled = true;

        SaveData* saveData = (SaveData*)ev->saveData;
        ordered_json jsonSaveFile = ConvertSaveData_to_JSON(saveData);

        if (!jsonSaveFile.empty()) {
            std::string fileName = fmt::format("file{}.json", saveData->saveSlot);
            std::string filePath = Ship::Context::GetPathRelativeToAppDirectory("saves/", "pm64");

            if (!fs::exists(filePath)) {
                fs::create_directories(filePath);
            }

            filePath += fileName;
            std::string collapsedString = CollapsedJSONArray(jsonSaveFile);

            std::ofstream outputFile(filePath);
            if (outputFile.is_open()) {
                outputFile << collapsedString;
                outputFile.close();
            }
        }
    })

    REGISTER_LISTENER(OnSaveFileLoad, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnSaveFileLoad* ev = (OnSaveFileLoad*)event;
        SaveData* currentSave = (SaveData*)ev->currentSaveFile;
        event->Cancelled = true;
        
        std::string fileName = fmt::format("file{}.json", ev->saveSlot);
        std::string filePath = Ship::Context::GetPathRelativeToAppDirectory("saves/" + fileName, "pm64");
        
        if (fs::exists(filePath)) {
            std::ifstream inputFile(filePath);
            json jsonSave;
            inputFile >> jsonSave;
        
            gCurrentSaveFile = *ConvertJSON_to_SaveData(jsonSave);
        } else {
            SaveData* newSaveData = new SaveData();
            gCurrentSaveFile = *newSaveData;
        }
    })

    REGISTER_LISTENER(OnSaveFileErase, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnSaveFileErase* ev = (OnSaveFileErase*)event;
        event->Cancelled = true;

        std::string fileName = fmt::format("file{}.json", ev->saveSlot);
        std::string filePath = Ship::Context::GetPathRelativeToAppDirectory("saves/" + fileName, "pm64");

        if (fs::exists(filePath)) {
            fs::remove(filePath);
        }
    })
}
