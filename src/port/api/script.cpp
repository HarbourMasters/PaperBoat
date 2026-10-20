#ifdef ENABLE_SCRIPTING

#include "port/api/script.h"

#include "port/ShipInit.hpp"
#include "port/api/ModOwner.hpp"

#include "common.h"

#include <algorithm>
#include <string>
#include <vector>

namespace {

struct StartedScript {
    int32_t id;
    const void* source;
    std::string owner;
};

std::vector<StartedScript> sScripts;

// The script with this ID, if it is still the one that was started. IDs can be reused once a script ends.
Evt* Running(const StartedScript& started) {
    if (!does_script_exist(started.id)) {
        return nullptr;
    }
    Evt* script = get_script_by_id(started.id);
    return script != nullptr && script->ptrFirstLine == (Bytecode*) started.source ? script : nullptr;
}

void Forget(const std::string& owner, int32_t id) {
    std::erase_if(sScripts, [&](const StartedScript& started) {
        return (id < 0 || started.id == id) && started.owner == owner;
    });
}

void InitScriptApi() {
    ModOwner::AddReleaser([](const std::string& mod) {
        for (const StartedScript& started : sScripts) {
            if (started.owner != mod) {
                continue;
            }
            if (Evt* script = Running(started)) {
                kill_script(script);
            }
        }
        Forget(mod, -1);
    });
}

RegisterShipInitFunc sInitScriptApi(InitScriptApi);

} // namespace

extern "C" int32_t C_StartScript(const void* source, int32_t priority, int32_t flags) {
    if (source == nullptr) {
        return -1;
    }
    std::erase_if(sScripts, [](const StartedScript& started) { return Running(started) == nullptr; });
    Evt* script = start_script((EvtScript*) source, priority, flags);
    if (script == nullptr) {
        return -1;
    }
    sScripts.push_back({ script->id, source, ModOwner::Current() });
    return script->id;
}

extern "C" void C_StopScript(int32_t scriptID) {
    const std::string owner = ModOwner::Current();
    for (const StartedScript& started : sScripts) {
        if (started.id == scriptID && started.owner == owner) {
            if (Evt* script = Running(started)) {
                kill_script(script);
            }
        }
    }
    Forget(owner, scriptID);
}

extern "C" int C_IsScriptRunning(int32_t scriptID) {
    for (const StartedScript& started : sScripts) {
        if (started.id == scriptID) {
            return Running(started) != nullptr;
        }
    }
    return 0;
}

extern "C" intptr_t C_ScriptGetVar(void* script, intptr_t var) {
    return evt_get_variable((Evt*) script, var);
}

extern "C" void C_ScriptSetVar(void* script, intptr_t var, intptr_t value) {
    evt_set_variable((Evt*) script, var, value);
}

extern "C" float C_ScriptGetFloat(void* script, intptr_t var) {
    return evt_get_float_variable((Evt*) script, var);
}

extern "C" void C_ScriptSetFloat(void* script, intptr_t var, float value) {
    evt_set_float_variable((Evt*) script, var, value);
}

#endif
