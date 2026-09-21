#include "TextureCache.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <string>

#include <SDL2/SDL.h>
#include <fast/Fast3dWindow.h>
#include <fast/interpreter.h>
#include <libultraship/bridge/consolevariablebridge.h>
#include <ship/Context.h>
#include <ship/resource/ResourceManager.h>
#include <ship/resource/archive/ArchiveManager.h>
#include <spdlog/spdlog.h>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <dxgi.h>
#include <wrl/client.h>
#pragma comment(lib, "dxgi.lib")
#endif

static uint64_t GuessVideoMemoryBytes() {
#ifdef _WIN32
    Microsoft::WRL::ComPtr<IDXGIFactory1> factory;
    if (SUCCEEDED(CreateDXGIFactory1(IID_PPV_ARGS(factory.GetAddressOf())))) {
        Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
        for (UINT i = 0; factory->EnumAdapters1(i, adapter.ReleaseAndGetAddressOf()) != DXGI_ERROR_NOT_FOUND; i++) {
            DXGI_ADAPTER_DESC1 desc {};
            if (SUCCEEDED(adapter->GetDesc1(&desc)) && !(desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
                && desc.DedicatedVideoMemory > 0)
            {
                return (uint64_t) desc.DedicatedVideoMemory;
            }
        }
    }
#endif
    return (uint64_t) (std::max) (SDL_GetSystemRAM(), 512) * 1024ull * 1024ull / 4;
}

constexpr uint64_t kMiB = 1024ull * 1024ull;
constexpr uint64_t kBaseBudget = 256 * kMiB;
constexpr size_t kMaxEntries = 16384;

uint64_t TextureCache_CeilingBytes() {
    const uint64_t raw = (std::max) (kBaseBudget, GuessVideoMemoryBytes() / 2);
    const uint64_t unit = raw >= 2048 * kMiB ? 1024 * kMiB : 256 * kMiB;
    return (std::max) (kBaseBudget, (raw + unit / 2) / unit * unit);
}

void TextureCache_Configure() {
    auto window = std::dynamic_pointer_cast<Fast::Fast3dWindow>(Ship::Context::GetRawInstance()->GetWindow());
    auto interpreter = window != nullptr ? window->GetInterpreterWeak().lock() : nullptr;
    if (interpreter == nullptr) {
        return;
    }
    uint64_t largest = 0;
    std::string largestName;
    auto archives = Ship::Context::GetRawInstance()->GetResourceManager()->GetArchiveManager()->GetArchives();
    for (const auto& archive : *archives) {
        const std::filesystem::path path = archive->GetPath();
        std::error_code ec;
        const uint64_t size = std::filesystem::is_directory(path, ec) ? 0 : std::filesystem::file_size(path, ec);
        if (!ec && size > largest) {
            largest = size;
            largestName = path.filename().generic_string();
        }
    }

    const uint64_t ceiling = TextureCache_CeilingBytes();
    // 0 = auto; 1..4 = that many quarters of the ceiling.
    const int32_t step = std::clamp(CVarGetInteger("gGraphics.TextureCache", 0), 0, 4);
    uint64_t budget = (std::min) ((std::max) (kBaseBudget, largest * 2), ceiling);
    if (step != 0) {
        budget = ceiling * (uint64_t) step / 4;
    }

    interpreter->SetTextureCacheMaxSize(kMaxEntries);
    interpreter->SetTextureCacheBudgetBytes((size_t) budget);
    SPDLOG_INFO(
        "Texture cache: {} MB ({}; largest archive {} at {} MB, ceiling {} MB)", budget / kMiB,
        step == 0 ? "auto" : "set", largestName, largest / kMiB, ceiling / kMiB
    );
}
