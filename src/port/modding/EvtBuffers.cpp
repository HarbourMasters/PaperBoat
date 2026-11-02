#include "EvtBuffers.h"

#include <algorithm>
#include <vector>

#include <spdlog/spdlog.h>

#include "ModInternal.h"

#include "common.h"

static int32_t sWideEvtBufferCount = 0;

struct WideEvtBuffer {
    std::string owner;
    uintptr_t begin;
    uintptr_t end;
};

static std::vector<WideEvtBuffer>& WideEvtBuffers() {
    static std::vector<WideEvtBuffer> sBuffers;
    return sBuffers;
}

extern "C" void Mod_RegisterWideEvtBuffer(const char* owner, const intptr_t* buf, size_t count) {
    if (buf == nullptr || count == 0) {
        return;
    }
    const std::string name = Mod::OwnerName(owner);
    const uintptr_t begin = (uintptr_t) buf;
    const uintptr_t end = (uintptr_t) (buf + count);
    auto& buffers = WideEvtBuffers();
    for (const WideEvtBuffer& range : buffers) {
        if (range.owner != name && begin < range.end && range.begin < end) {
            SPDLOG_WARN("Mod: {} registers a wide EVT buffer overlapping one of {}", name, range.owner);
        }
    }
    buffers.push_back({ name, begin, end });
    sWideEvtBufferCount = (int32_t) buffers.size();
}

static bool IsWideEvtBuffer(const void* ptr) {
    if (sWideEvtBufferCount == 0) {
        return false;
    }
    uintptr_t addr = (uintptr_t) ptr;
    for (const auto& range : WideEvtBuffers()) {
        if (addr >= range.begin && addr < range.end) {
            return true;
        }
    }
    return false;
}

extern "C" Bytecode evt_buffer_next(Evt* script) {
    if (IsWideEvtBuffer(script->buffer)) {
        Bytecode* wide = (Bytecode*) script->buffer;
        script->buffer = (s32*) (wide + 1);
        return *wide;
    }
    return *script->buffer++;
}

extern "C" Bytecode evt_buffer_at(Evt* script, s32 index) {
    if (IsWideEvtBuffer(script->buffer)) {
        return ((Bytecode*) script->buffer)[index];
    }
    return script->buffer[index];
}

void Mod::UnregisterEvtBuffers(const std::string& owner) {
    auto& buffers = WideEvtBuffers();
    buffers.erase(
        std::remove_if(
            buffers.begin(), buffers.end(), [&](const WideEvtBuffer& range) { return range.owner == owner; }
        ),
        buffers.end()
    );
    sWideEvtBufferCount = (int32_t) buffers.size();
}
