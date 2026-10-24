#include "Messages.h"

#include <cstdio>
#include <map>
#include <utility>
#include <vector>

#include "ModInternal.h"
#include "port/Engine.h"
#include "port/ShipInit.hpp"
#include "port/hooks/Events.h"

struct InlineMessage {
    std::string owner;
    const uint8_t* bytes;
};

static std::vector<InlineMessage>& InlineMessages() {
    static std::vector<InlineMessage> sMessages;
    return sMessages;
}

static std::map<std::pair<std::string, const uint8_t*>, size_t>& InlineMessageIndex() {
    static std::map<std::pair<std::string, const uint8_t*>, size_t> sIndex;
    return sIndex;
}

static int32_t InlineMessageId(size_t index) {
    return (MOD_INLINE_MSG_SECTION << 16) | (int32_t) index;
}

extern "C" int32_t Mod_RegisterInlineMessage(const char* owner, const uint8_t* bytes) {
    const std::string name = Mod::OwnerName(owner);
    auto& messages = InlineMessages();
    auto& index = InlineMessageIndex();
    const auto key = std::make_pair(name, bytes);
    const auto it = index.find(key);

    if (it != index.end()) {
        return InlineMessageId(it->second);
    }
    messages.push_back({ name, bytes });
    index[key] = messages.size() - 1;
    return InlineMessageId(messages.size() - 1);
}

static void* LoadModMessage(uint32_t msgID) {
    if ((msgID >> 16) == MOD_INLINE_MSG_SECTION) {
        auto& messages = InlineMessages();
        const uint32_t index = msgID & 0xFFFF;
        return index < messages.size() ? (void*) messages[index].bytes : nullptr;
    }
    char path[64];
    snprintf(path, sizeof(path), "__OTR__messages/MSG_mod_%02X_%04X", msgID >> 16, msgID & 0xFFFF);
    return GameEngine_GetDataExact(path);
}

static void OnMessageLoadServe(IEvent* event) {
    auto* ev = (OnMessageLoad*) event;

    if (*ev->data == nullptr) {
        *ev->data = (uint8_t*) LoadModMessage(ev->msgID);
    }
}

static void OnMessageLoadWarn(IEvent* event) {
    static bool sWarnedMissingMsg = false;
    auto* ev = (OnMessageLoad*) event;

    if (*ev->data == nullptr && !sWarnedMissingMsg) {
        sWarnedMissingMsg = true;
        GameEngine_LogWarn("Message 0x%08X not found, falling back to message 0/0", ev->msgID);
    }
}

static void ListenMessages() {
    REGISTER_LISTENER(OnMessageLoad, EVENT_PRIORITY_NORMAL, OnMessageLoadServe);
    REGISTER_LISTENER(OnMessageLoad, EVENT_PRIORITY_HIGH, OnMessageLoadWarn);
}

static RegisterShipInitFunc sMessagesInit(ListenMessages);

void Mod::UnregisterMessages(const std::string& owner) {
    auto& index = InlineMessageIndex();

    for (InlineMessage& message : InlineMessages()) {
        if (message.owner == owner) {
            index.erase(std::make_pair(message.owner, message.bytes));
            message.owner.clear();
            message.bytes = nullptr;
        }
    }
}
