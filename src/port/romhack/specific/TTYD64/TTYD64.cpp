#include <cstring>
#include <iterator>
#include <memory>

#include "port/romhack/RomhackPort.h"
#include "TTYD64.h"
#include "include/ttyd64_api.h"
#include "include/ttyd64_drop_tables.h"
#include "include/ttyd64_flags.h"
#include "include/ttyd64_items.h"
#include "include/ttyd64_rawmem.h"
#include "include/ttyd64_symbols.h"
#include "port/hooks/Events.h"
#include "port/modding/ModSaveData.h"

#include "dx/versioning.h"

namespace {

void RegisterSaveData() {
    Mod_RegisterSaveData(
        "TTYD64", "partnerHP",
        { []() {
             nlohmann::json partners = nlohmann::json::array();
             for (const TTYD64PartnerHPRecord& record : TTYD64_PartnerHPRecords) {
                 partners.push_back({ { "displayed", record.displayed }, { "hp", record.hp }, { "max", record.max } });
             }
             return partners;
         },
          [](const nlohmann::json& partners) {
              for (size_t i = 0; i < std::size(TTYD64_PartnerHPRecords); i++) {
                  const nlohmann::json record = i < partners.size() ? partners[i] : nlohmann::json::object();
                  TTYD64_PartnerHPRecords[i].displayed = record.value("displayed", 0);
                  TTYD64_PartnerHPRecords[i].hp = record.value("hp", 0);
                  TTYD64_PartnerHPRecords[i].max = record.value("max", 0);
              }
          },
          []() { std::memset(TTYD64_PartnerHPRecords, 0, sizeof(TTYD64_PartnerHPRecords)); } }
    );
    Mod_RegisterSaveData(
        "TTYD64", "shineSprites",
        { []() { return nlohmann::json(TTYD64_ShineSprites); },
          [](const nlohmann::json& value) { TTYD64_ShineSprites = value.get<u8>(); },
          []() { TTYD64_ShineSprites = 0; } }
    );
    Mod_RegisterSaveData(
        "TTYD64", "fortressKeys",
        { []() { return nlohmann::json(TTYD64_FortressKeys); },
          [](const nlohmann::json& value) { TTYD64_FortressKeys = value.get<s32>(); },
          []() { TTYD64_FortressKeys = 0; } }
    );
}

} // namespace

class TTYD64Port final : public Romhack::Port {
public:
    void ApplyDataTables() override {
        TTYD64_ApplyDataTables();
    }

    void Init() override {
        RegisterSaveData();
        TTYD64_InstallActorRecords();
        TTYD64_InstallDataTables();
        TTYD64_InstallWorldLib();
        TTYD64_InstallBattleCore();
        TTYD64_InstallEnemyItems();
        TTYD64_InstallBadgesStrats();
        TTYD64_InstallPartnerHP();
        TTYD64_InstallBattleItemsUI();
        TTYD64_InstallHudPause();
        TTYD64_InstallWorldSystems();
        TTYD64_InstallPlayerOverlays();
        TTYD64_InstallBattlesA();
        TTYD64_InstallBattlesB();
        TTYD64_InstallBattlesNew();
        TTYD64_InstallNewMaps();
        TTYD64_InstallNewMapsTydPit();
        TTYD64_InstallMaps();
    }
};

std::unique_ptr<Romhack::Port> CreateTTYD64Port() {
    return std::make_unique<TTYD64Port>();
}
