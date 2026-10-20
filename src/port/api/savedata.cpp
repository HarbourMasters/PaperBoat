#ifdef ENABLE_SCRIPTING

#include "port/api/savedata.h"

#include "port/save/SaveMods.h"

#include <algorithm>
#include <cstring>
#include <string>

using nlohmann::json;

namespace {

constexpr char kHex[] = "0123456789abcdef";

const json* Find(const char* key) {
    if (key == nullptr) {
        return nullptr;
    }
    const json& data = SaveMods::Data();
    auto it = data.find(key);
    return it != data.end() ? &*it : nullptr;
}

void Set(const char* key, json value) {
    if (key != nullptr) {
        SaveMods::Data()[key] = std::move(value);
    }
}

int HexDigit(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return -1;
}

} // namespace

extern "C" int C_SaveDataHas(const char* key) {
    return Find(key) != nullptr;
}

extern "C" void C_SaveDataRemove(const char* key) {
    if (key != nullptr) {
        SaveMods::Data().erase(key);
    }
}

extern "C" int32_t C_SaveDataGetInt(const char* key, int32_t defaultValue) {
    const json* value = Find(key);
    return value != nullptr && value->is_number() ? value->get<int32_t>() : defaultValue;
}

extern "C" void C_SaveDataSetInt(const char* key, int32_t value) {
    Set(key, value);
}

extern "C" float C_SaveDataGetFloat(const char* key, float defaultValue) {
    const json* value = Find(key);
    return value != nullptr && value->is_number() ? value->get<float>() : defaultValue;
}

extern "C" void C_SaveDataSetFloat(const char* key, float value) {
    Set(key, value);
}

extern "C" const char* C_SaveDataGetString(const char* key, const char* defaultValue) {
    const json* value = Find(key);
    return value != nullptr && value->is_string() ? value->get_ref<const std::string&>().c_str() : defaultValue;
}

extern "C" void C_SaveDataSetString(const char* key, const char* value) {
    Set(key, value != nullptr ? value : "");
}

// Bytes are kept as a hex string.
extern "C" uint32_t C_SaveDataGetBytes(const char* key, void* out, uint32_t capacity) {
    const json* value = Find(key);
    if (value == nullptr || !value->is_string()) {
        return 0;
    }
    const std::string& hex = value->get_ref<const std::string&>();
    if (hex.size() % 2 != 0) {
        return 0;
    }
    const uint32_t size = (uint32_t) (hex.size() / 2);
    uint8_t* bytes = (uint8_t*) out;
    for (uint32_t i = 0; bytes != nullptr && i < std::min(size, capacity); i++) {
        const int high = HexDigit(hex[i * 2]);
        const int low = HexDigit(hex[i * 2 + 1]);
        if (high < 0 || low < 0) {
            return 0;
        }
        bytes[i] = (uint8_t) (high << 4 | low);
    }
    return size;
}

extern "C" void C_SaveDataSetBytes(const char* key, const void* data, uint32_t size) {
    if (key == nullptr || (data == nullptr && size > 0)) {
        return;
    }
    const uint8_t* bytes = (const uint8_t*) data;
    std::string hex;
    hex.reserve(size * 2);
    for (uint32_t i = 0; i < size; i++) {
        hex += kHex[bytes[i] >> 4];
        hex += kHex[bytes[i] & 0xF];
    }
    Set(key, std::move(hex));
}

#endif
