#include "port/api/message.h"

#include "port/ShipInit.hpp"
#include "port/api/StableIds.hpp"
#include "port/hooks/Events.h"
#ifdef ENABLE_SCRIPTING
#include "port/api/ModOwner.hpp"
#endif

#include <algorithm>
#include <cstring>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace {

constexpr uint8_t kEnd = 0xFD;
constexpr uint8_t kSpace = 0xF7;
constexpr uint8_t kNewLine = 0xF0;
constexpr uint8_t kUnknown = 0x1F; // '?'

// Characters past ASCII that the US font has.
const std::unordered_map<uint32_t, uint8_t> kExtraChars = {
    { 0x00C0, 0x60 }, { 0x00C1, 0x61 }, { 0x00C2, 0x62 }, { 0x00C4, 0x63 }, { 0x00C7, 0x64 }, { 0x00C8, 0x65 },
    { 0x00C9, 0x66 }, { 0x00CA, 0x67 }, { 0x00CB, 0x68 }, { 0x00CC, 0x69 }, { 0x00CD, 0x6A }, { 0x00CE, 0x6B },
    { 0x00CF, 0x6C }, { 0x00D1, 0x6D }, { 0x00D2, 0x6E }, { 0x00D3, 0x6F }, { 0x00D4, 0x70 }, { 0x00D6, 0x71 },
    { 0x00D9, 0x72 }, { 0x00DA, 0x73 }, { 0x00DB, 0x74 }, { 0x00DC, 0x75 }, { 0x00DF, 0x76 }, { 0x00E0, 0x77 },
    { 0x00E1, 0x78 }, { 0x00E2, 0x79 }, { 0x00E4, 0x7A }, { 0x00E7, 0x7B }, { 0x00E8, 0x7C }, { 0x00E9, 0x7D },
    { 0x00EA, 0x7E }, { 0x00EB, 0x7F }, { 0x00EC, 0x80 }, { 0x00ED, 0x81 }, { 0x00EE, 0x82 }, { 0x00EF, 0x83 },
    { 0x00F1, 0x84 }, { 0x00F2, 0x85 }, { 0x00F3, 0x86 }, { 0x00F4, 0x87 }, { 0x00F6, 0x88 }, { 0x00F9, 0x89 },
    { 0x00FA, 0x8A }, { 0x00FB, 0x8B }, { 0x00FC, 0x8C }, { 0x00A1, 0x8D }, { 0x00BF, 0x8E }, { 0x00AA, 0x8F },
    { 0x2665, 0x90 }, { 0x2605, 0x91 }, { 0x2191, 0x92 }, { 0x2193, 0x93 }, { 0x2190, 0x94 }, { 0x2192, 0x95 },
    { 0x25CB, 0x96 }, { 0x00D7, 0x97 }, { 0x201C, 0xA2 }, { 0x201D, 0xA3 }, { 0x2018, 0xA4 }, { 0x2019, 0xA5 },
    { 0x266A, 0x00 }, { 0x00B0, 0x5F }, { 0x00A5, 0x3C },
};

const std::unordered_map<std::string, std::vector<uint8_t>> kTags = {
    { "NEXT", { 0xFB } },   { "WAIT", { 0xF1 } },   { "A", { 0x98 } },       { "B", { 0x99 } },
    { "L", { 0x9A } },      { "R", { 0x9B } },      { "Z", { 0x9C } },       { "C-UP", { 0x9D } },
    { "C-DOWN", { 0x9E } }, { "C-LEFT", { 0x9F } }, { "C-RIGHT", { 0xA0 } }, { "START", { 0xA1 } },
    { "HEART", { 0x90 } },  { "STAR", { 0x91 } },   { "NOTE", { 0x00 } },
};

// Reads the code point at text[pos] and moves pos past it. Invalid bytes read as themselves.
uint32_t NextCodePoint(const std::string& text, size_t& pos) {
    const uint8_t first = (uint8_t) text[pos++];
    int extra = first >= 0xF0 ? 3 : first >= 0xE0 ? 2 : first >= 0xC0 ? 1 : 0;
    uint32_t code = extra == 3 ? first & 0x07 : extra == 2 ? first & 0x0F : extra == 1 ? first & 0x1F : first;
    for (; extra > 0 && pos < text.size() && ((uint8_t) text[pos] & 0xC0) == 0x80; extra--) {
        code = code << 6 | ((uint8_t) text[pos++] & 0x3F);
    }
    return code;
}

// Encodes a tag's contents, e.g. "PAUSE 30", or returns false when it isn't one.
bool EncodeTag(const std::string& tag, std::vector<uint8_t>& out) {
    const size_t space = tag.find(' ');
    const std::string name = tag.substr(0, space);
    const std::string args = space == std::string::npos ? "" : tag.substr(space + 1);
    if (auto it = kTags.find(name); it != kTags.end()) {
        out.insert(out.end(), it->second.begin(), it->second.end());
        return true;
    }
    std::vector<unsigned long> values;
    for (size_t pos = 0; pos < args.size();) {
        char* end = nullptr;
        const int base = name == "RAW" ? 16 : 10;
        values.push_back(strtoul(args.c_str() + pos, &end, base));
        if (end == args.c_str() + pos) {
            return false;
        }
        pos = end - args.c_str();
        while (pos < args.size() && args[pos] == ' ') {
            pos++;
        }
    }
    if (name == "PAUSE" && values.size() == 1) {
        out.insert(out.end(), { 0xF2, (uint8_t) values[0] });
    } else if (name == "COLOR" && values.size() == 1) {
        out.insert(out.end(), { 0xFF, 0x05, (uint8_t) values[0] });
    } else if (name == "STYLE" && values.size() == 1) {
        out.insert(out.end(), { 0xFC, (uint8_t) values[0] });
    } else if (name == "RAW" && !values.empty()) {
        for (unsigned long value : values) {
            out.push_back((uint8_t) value);
        }
    } else {
        return false;
    }
    return true;
}

std::vector<uint8_t> Encode(const std::string& text) {
    std::vector<uint8_t> out;
    for (size_t pos = 0; pos < text.size();) {
        if (text.compare(pos, 2, "<<") == 0) {
            const size_t close = text.find(">>", pos + 2);
            if (close != std::string::npos && EncodeTag(text.substr(pos + 2, close - pos - 2), out)) {
                pos = close + 2;
                continue;
            }
        }
        const uint32_t code = NextCodePoint(text, pos);
        if (code == ' ') {
            out.push_back(kSpace);
        } else if (code == '\n') {
            out.push_back(kNewLine);
        } else if (code > 0x20 && code < 0x7F) {
            out.push_back((uint8_t) (code - 0x20));
        } else if (auto it = kExtraChars.find(code); it != kExtraChars.end()) {
            out.push_back(it->second);
        } else if (code != '\r') {
            out.push_back(kUnknown);
        }
    }
    out.push_back(kEnd);
    return out;
}

using Text = std::unique_ptr<std::vector<uint8_t>>;

struct CustomMessage {
    bool used = false;
    std::string owner;
    Text text;
};

struct Override {
    std::string owner;
    Text text;
};

std::unordered_map<int32_t, CustomMessage> sMessages;
std::unordered_map<int32_t, std::vector<Override>> sOverrides;
// Text the game may still be reading, e.g. a message box opened before the mod reloaded. Kept until shutdown.
std::vector<Text> sRetired;
StableIds sNumbers("messages", C_MSG_FIRST, C_MSG_LAST);

std::string CurrentOwner() {
#ifdef ENABLE_SCRIPTING
    return ModOwner::Current();
#else
    return {};
#endif
}

void Retire(Text text) {
    if (text != nullptr) {
        sRetired.push_back(std::move(text));
    }
}

void InitMessageApi() {
    REGISTER_LISTENER(MessageLookup, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        auto* lookup = reinterpret_cast<MessageLookup*>(event);
        if (lookup->msgID >= C_MSG_FIRST && lookup->msgID <= C_MSG_LAST) {
            auto it = sMessages.find(lookup->msgID);
            if (it != sMessages.end() && it->second.used) {
                lookup->data = it->second.text->data();
            }
        } else if (!sOverrides.empty()) {
            auto it = sOverrides.find(lookup->msgID);
            if (it != sOverrides.end() && !it->second.empty()) {
                lookup->data = it->second.back().text->data();
            }
        }
    });
#ifdef ENABLE_SCRIPTING
    ModOwner::AddReleaser([](const std::string& mod) {
        for (auto& [msgID, message] : sMessages) {
            if (message.used && message.owner == mod) {
                C_UnregisterMessage(msgID);
            }
        }
        for (auto it = sOverrides.begin(); it != sOverrides.end();) {
            std::erase_if(it->second, [&](Override& entry) {
                if (entry.owner != mod) {
                    return false;
                }
                Retire(std::move(entry.text));
                return true;
            });
            it = it->second.empty() ? sOverrides.erase(it) : std::next(it);
        }
    });
#endif
}

// After PortEnhancements registers the event IDs, as every ShipInit function runs.
RegisterShipInitFunc sInitMessageApi(InitMessageApi);

} // namespace

extern "C" int32_t C_RegisterMessage(const char* id, const char* text) {
    if (id == nullptr || id[0] == '\0') {
        return 0;
    }
    const std::string owner = CurrentOwner();
    const int number = sNumbers.Register(id, owner);
    if (number < 0) {
        return 0;
    }
    CustomMessage& message = sMessages[number];
    Retire(std::move(message.text));
    message.used = true;
    message.owner = owner;
    message.text = std::make_unique<std::vector<uint8_t>>(Encode(text != nullptr ? text : ""));
    return number;
}

extern "C" void C_UnregisterMessage(int32_t msgID) {
    auto it = sMessages.find(msgID);
    if (it == sMessages.end() || !it->second.used) {
        return;
    }
    it->second.used = false;
    Retire(std::move(it->second.text));
    sNumbers.Unregister(msgID);
}

extern "C" int32_t C_FindMessage(const char* id) {
    if (id == nullptr) {
        return 0;
    }
    const int number = sNumbers.Find(id);
    auto it = sMessages.find(number);
    return it != sMessages.end() && it->second.used ? number : 0;
}

extern "C" int C_OverrideMessage(int32_t msgID, const char* text) {
    if (msgID <= 0 || (msgID >= C_MSG_FIRST && msgID <= C_MSG_LAST) || msgID > 0x00FFFFFF) {
        return 0;
    }
    C_RemoveMessageOverride(msgID);
    sOverrides[msgID].push_back(
        { CurrentOwner(), std::make_unique<std::vector<uint8_t>>(Encode(text != nullptr ? text : "")) }
    );
    return 1;
}

extern "C" void C_RemoveMessageOverride(int32_t msgID) {
    auto it = sOverrides.find(msgID);
    if (it == sOverrides.end()) {
        return;
    }
    const std::string owner = CurrentOwner();
    std::erase_if(it->second, [&](Override& entry) {
        if (entry.owner != owner) {
            return false;
        }
        Retire(std::move(entry.text));
        return true;
    });
    if (it->second.empty()) {
        sOverrides.erase(it);
    }
}

extern "C" uint32_t C_EncodeText(const char* text, uint8_t* out, uint32_t capacity) {
    const std::vector<uint8_t> encoded = Encode(text != nullptr ? text : "");
    if (out != nullptr) {
        memcpy(out, encoded.data(), std::min<size_t>(encoded.size(), capacity));
    }
    return (uint32_t) encoded.size();
}
