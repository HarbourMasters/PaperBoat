#include "InputHistory.h"

#include <algorithm>
#include <array>
#include <string>
#include <vector>

#include "ModInternal.h"
#include "port/ShipInit.hpp"
#include "port/hooks/Events.h"

#include "common.h"

namespace {

struct InputRecord {
    uint32_t frame;
    uint32_t held;
    uint32_t pressed;
};

struct FrameListener {
    std::string owner;
    ModInputFrameFn fn;
};

std::array<InputRecord, MOD_INPUT_HISTORY_FRAMES> sRecords;
uint32_t sFrame;

std::vector<FrameListener>& Listeners() {
    static std::vector<FrameListener> sListeners;
    return sListeners;
}

const InputRecord* RecordAt(uint32_t frame) {
    if (frame == 0 || frame > sFrame || sFrame - frame >= MOD_INPUT_HISTORY_FRAMES) {
        return nullptr;
    }
    return &sRecords[frame % MOD_INPUT_HISTORY_FRAMES];
}

uint32_t OldestFrame() {
    return sFrame >= MOD_INPUT_HISTORY_FRAMES ? sFrame - MOD_INPUT_HISTORY_FRAMES + 1 : 1;
}

uint32_t ByteMask(uint32_t mask) {
    uint32_t bytes = 0;
    for (int32_t shift = 0; shift < 32; shift += 8) {
        if (mask & (0xFFu << shift)) {
            bytes |= 0xFFu << shift;
        }
    }
    return bytes;
}

int32_t FirstPressAfter(uint32_t since, uint32_t mask, int32_t match) {
    uint32_t first = std::max<uint32_t>(since + 1, OldestFrame());
    for (uint32_t frame = first; frame <= sFrame; frame++) {
        if (Mod_InputMatches(RecordAt(frame)->pressed, mask, match)) {
            return static_cast<int32_t>(frame);
        }
    }
    return -1;
}

void RecordFrame(IEvent*) {
    const uint32_t held = gGameStatusPtr->curButtons[0];
    const uint32_t pressed = gGameStatusPtr->pressedButtons[0];

    sFrame++;
    sRecords[sFrame % MOD_INPUT_HISTORY_FRAMES] = { sFrame, held, pressed };
    for (const FrameListener& listener : Listeners()) {
        listener.fn(sFrame, held, pressed);
    }
}

void Listen() {
    REGISTER_LISTENER(GameFrameUpdate, EVENT_PRIORITY_LOW, RecordFrame);
}

RegisterShipInitFunc sInputHistoryInit(Listen);

} // namespace

extern "C" uint32_t Mod_InputFrame(void) {
    return sFrame;
}

extern "C" uint32_t Mod_InputPressedAt(uint32_t frame) {
    const InputRecord* record = RecordAt(frame);
    return record != nullptr ? record->pressed : 0;
}

extern "C" uint32_t Mod_InputHeldAt(uint32_t frame) {
    const InputRecord* record = RecordAt(frame);
    return record != nullptr ? record->held : 0;
}

extern "C" bool Mod_InputMatches(uint32_t pressed, uint32_t mask, int32_t match) {
    if (mask == 0) {
        return false;
    }
    switch (match) {
        case MOD_INPUT_MATCH_ONLY:
            return (pressed & mask) != 0 && (pressed & ~mask) == 0;
        case MOD_INPUT_MATCH_BYTE_EXACT:
            return (pressed & ByteMask(mask)) == mask;
        default:
            return (pressed & mask) != 0;
    }
}

extern "C" bool Mod_InputPressedSince(uint32_t frame, uint32_t mask, int32_t match) {
    return FirstPressAfter(frame, mask, match) >= 0;
}

extern "C" bool Mod_InputPressedWithin(uint32_t frames, uint32_t mask, int32_t match) {
    if (frames == 0) {
        return false;
    }
    return FirstPressAfter(sFrame >= frames ? sFrame - frames : 0, mask, match) >= 0;
}

extern "C" int32_t Mod_InputFirstPress(uint32_t since, uint32_t mask, int32_t match) {
    return FirstPressAfter(since, mask, match);
}

extern "C" void Mod_RegisterInputFrameListener(const char* owner, ModInputFrameFn fn) {
    if (fn != nullptr) {
        Listeners().push_back({ Mod::OwnerName(owner), fn });
    }
}

void Mod::UnregisterInputFrameListeners(const std::string& owner) {
    auto& listeners = Listeners();
    listeners.erase(
        std::remove_if(
            listeners.begin(), listeners.end(), [&](const FrameListener& listener) { return listener.owner == owner; }
        ),
        listeners.end()
    );
}

extern "C" API_CALLABLE(Mod_EvtInputMarkFrame) {
    evt_set_variable(script, *script->ptrReadPos, static_cast<s32>(sFrame));
    return ApiStatus_DONE2;
}

extern "C" API_CALLABLE(Mod_EvtInputPressedSince) {
    Bytecode* args = script->ptrReadPos;
    const uint32_t frame = evt_get_variable(script, *args++);
    const uint32_t mask = evt_get_variable(script, *args++);
    const int32_t match = evt_get_variable(script, *args++);

    evt_set_variable(script, *args++, Mod_InputPressedSince(frame, mask, match));
    return ApiStatus_DONE2;
}

extern "C" API_CALLABLE(Mod_EvtInputPressedWithin) {
    Bytecode* args = script->ptrReadPos;
    const uint32_t frames = evt_get_variable(script, *args++);
    const uint32_t mask = evt_get_variable(script, *args++);
    const int32_t match = evt_get_variable(script, *args++);

    evt_set_variable(script, *args++, Mod_InputPressedWithin(frames, mask, match));
    return ApiStatus_DONE2;
}
