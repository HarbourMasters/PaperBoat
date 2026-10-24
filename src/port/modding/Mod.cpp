#include "Mod.h"

#include <spdlog/spdlog.h>

#include "ModInternal.h"

extern "C" void Mod_UnregisterOwner(const char* owner) {
    const std::string name = Mod::OwnerName(owner);
    Mod::UnregisterScriptOverrides(name);
    Mod::UnregisterBattleOverrides(name);
    Mod::UnregisterMessages(name);
    Mod::UnregisterMaps(name);
    Mod::UnregisterEvtBuffers(name);
    Mod::UnregisterMapTextures(name);
    Mod::UnregisterAbilities(name);
    Mod::UnregisterSaveData(name);
    Mod::UnregisterActorExt(name);
    Mod::UnregisterBattleMenus(name);
    Mod::UnregisterPopups(name);
    Mod::UnregisterWindowStyles(name);
    Mod::UnregisterPanels(name);
    Mod::UnregisterItemCapacity(name);
    Mod::UnregisterSaveImports(name);
    Mod::UnregisterInputFrameListeners(name);
    SPDLOG_INFO("Mod: unregistered everything {} registered", name);
}
