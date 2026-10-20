#ifdef USE_NETWORKING
#include "port/net/PlayerIdentity.h"
#include <ship/Context.h>

#include <ship/config/Config.h>
#include <ship/utils/StringHelper.h>

#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>
#include <monocypher-ed25519.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <atomic>
#include <cstring>
#include <mutex>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/file.h>
#endif

namespace PlayerIdentity {

static std::mutex sMtx;
static std::atomic<bool> sInitialized { false };
static uint8_t sPublicKey[32];
static uint8_t sSecretKey[64];

static bool FillRandom(uint8_t* buf, size_t size) {
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context drbg;
    mbedtls_entropy_init(&entropy);
    mbedtls_ctr_drbg_init(&drbg);

    const char* pers = "paperboat_player_identity";
    const bool ok =
        mbedtls_ctr_drbg_seed(
            &drbg, mbedtls_entropy_func, &entropy, reinterpret_cast<const unsigned char*>(pers), std::strlen(pers)
        ) == 0
        && mbedtls_ctr_drbg_random(&drbg, buf, size) == 0;

    mbedtls_ctr_drbg_free(&drbg);
    mbedtls_entropy_free(&entropy);
    return ok;
}

static bool HoldSavedKey() {
    const std::string path = Ship::Context::GetPathRelativeToAppDirectory("satella.lock");
#ifdef _WIN32
    const HANDLE file = CreateFileA(path.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS,
                                    FILE_ATTRIBUTE_NORMAL, nullptr);
    return file != INVALID_HANDLE_VALUE || GetLastError() != ERROR_SHARING_VIOLATION;
#else
    const int fd = open(path.c_str(), O_RDWR | O_CREAT | O_CLOEXEC, 0644);
    return fd < 0 || flock(fd, LOCK_EX | LOCK_NB) == 0;
#endif
}

static void EnsureInitialized() {
    if (sInitialized.load(std::memory_order_acquire)) {
        return;
    }

    std::lock_guard<std::mutex> lock(sMtx);
    if (sInitialized.load(std::memory_order_relaxed)) {
        return;
    }

    auto config = Ship::Context::GetRawInstance()->GetConfig();
    if (config == nullptr) {
        return;
    }

    uint8_t seed[32] = {};
    const auto stored = StringHelper::HexToBytes(config->GetString("Satella.PlayerSeed"));
    if (!HoldSavedKey()) {
        if (!FillRandom(seed, sizeof(seed))) {
            return;
        }
        SPDLOG_WARN("Satella: another copy of the game in this folder has the player key; this one plays with a key "
                    "of its own until it closes");
    } else if (stored.size() == sizeof(seed)) {
        std::copy(stored.begin(), stored.end(), seed);
    } else {
        if (!FillRandom(seed, sizeof(seed))) {
            return;
        }
        config->SetString("Satella.PlayerSeed", StringHelper::BytesToHex({ seed, seed + sizeof(seed) }));
        config->Save();
    }

    crypto_ed25519_key_pair(sSecretKey, sPublicKey, seed);
    crypto_wipe(seed, sizeof(seed));
    sInitialized.store(true, std::memory_order_release);
}

std::vector<uint8_t> GetPublicKey() {
    EnsureInitialized();
    if (!sInitialized.load(std::memory_order_relaxed)) {
        return {};
    }
    return { sPublicKey, sPublicKey + sizeof(sPublicKey) };
}

std::vector<uint8_t> Sign(const uint8_t* data, size_t size) {
    EnsureInitialized();
    if (!sInitialized.load(std::memory_order_relaxed)) {
        return {};
    }
    std::vector<uint8_t> sig(64);
    crypto_ed25519_sign(sig.data(), sSecretKey, data, size);
    return sig;
}

} // namespace PlayerIdentity
#endif
