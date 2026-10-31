#include "ScriptOverrides.h"

#include <iterator>
#include <unordered_map>

#include <spdlog/spdlog.h>

#include "ModInternal.h"
#include "port/ShipInit.hpp"
#include "port/hooks/Events.h"

static int32_t sScriptReplacementCount = 0;

static std::unordered_map<const void*, Mod::OwnerStack<void*>>& ScriptReplacements() {
    static std::unordered_map<const void*, Mod::OwnerStack<void*>> sReplacements;
    return sReplacements;
}

extern "C" void Mod_ReplaceScript(const char* owner, const void* original, const void* replacement) {
    if (original == nullptr || replacement == nullptr || original == replacement) {
        return;
    }
    const std::string name = Mod::OwnerName(owner);
    auto& replacements = ScriptReplacements();
    if (const std::string* previous = replacements[original].Push(name, const_cast<void*>(replacement))) {
        SPDLOG_WARN("Mod: {} replaces script {} already replaced by {}", name, original, *previous);
    }
    sScriptReplacementCount = (int32_t) replacements.size();
}

static void OnScriptResolveReplace(IEvent* event) {
    if (sScriptReplacementCount == 0) {
        return;
    }
    auto* ev = (OnScriptResolve*) event;
    auto& replacements = ScriptReplacements();
    auto it = replacements.find(*ev->script);
    if (it != replacements.end()) {
        *ev->script = (EvtScript*) it->second.Top();
    }
}

static void ListenScriptOverrides() {
    REGISTER_LISTENER(OnScriptResolve, EVENT_PRIORITY_NORMAL, OnScriptResolveReplace);
}

static RegisterShipInitFunc sScriptOverridesInit(ListenScriptOverrides);

void Mod::UnregisterScriptOverrides(const std::string& owner) {
    auto& replacements = ScriptReplacements();
    for (auto it = replacements.begin(); it != replacements.end();) {
        it->second.Remove(owner);
        it = it->second.Empty() ? replacements.erase(it) : std::next(it);
    }
    sScriptReplacementCount = (int32_t) replacements.size();
}
