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
#include <dxgi1_4.h>
#include <wrl/client.h>
#pragma comment(lib, "dxgi.lib")
#endif

struct VideoMemoryEstimate {
    uint64_t bytes;
    bool measured;
};

static VideoMemoryEstimate QueryVideoMemory() {
#ifdef _WIN32
    Microsoft::WRL::ComPtr<IDXGIFactory1> factory;
    if (SUCCEEDED(CreateDXGIFactory1(IID_PPV_ARGS(factory.GetAddressOf())))) {
        Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
        for (UINT i = 0; factory->EnumAdapters1(i, adapter.ReleaseAndGetAddressOf()) != DXGI_ERROR_NOT_FOUND; i++) {
            DXGI_ADAPTER_DESC1 desc {};
            if (FAILED(adapter->GetDesc1(&desc)) || (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
                || desc.DedicatedVideoMemory == 0)
            {
                continue;
            }
            static bool reported = false;
            Microsoft::WRL::ComPtr<IDXGIAdapter3> adapter3;
            DXGI_QUERY_VIDEO_MEMORY_INFO info {};
            if (!reported && SUCCEEDED(adapter.As(&adapter3))
                && SUCCEEDED(adapter3->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &info)))
            {
                reported = true;
                SPDLOG_INFO("Video memory: {} MB", (uint64_t) desc.DedicatedVideoMemory / (1024ull * 1024ull));
            }
            return { (uint64_t) desc.DedicatedVideoMemory, true };
        }
    }
#endif
    return { (uint64_t) (std::max) (SDL_GetSystemRAM(), 512) * 1024ull * 1024ull / 4, false };
}

constexpr uint64_t kMiB = 1024ull * 1024ull;
constexpr uint64_t kBaseBudget = 256 * kMiB;
constexpr size_t kMaxEntries = 16384;

uint64_t TextureCache_CeilingBytes() {
    const VideoMemoryEstimate vram = QueryVideoMemory();
    const uint64_t usable = vram.measured ? vram.bytes : vram.bytes / 2;
    const uint64_t raw = (std::max) (kBaseBudget, usable);
    const uint64_t unit = raw >= 2048 * kMiB ? 1024 * kMiB : 256 * kMiB;
    return (std::max) (kBaseBudget, (raw + unit / 2) / unit * unit);
}

uint64_t TextureCache_AutoBytes() {
    return (std::max) (kBaseBudget, TextureCache_CeilingBytes() * 5 / 8);
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
    const int32_t step = std::clamp(CVarGetInteger("gGraphics.TextureCache", 0), 0, 4);
    uint64_t budget = TextureCache_AutoBytes();
    if (step != 0) {
        budget = ceiling * (uint64_t) step / 4;
    }
    interpreter->SetTextureCacheMaxSize(kMaxEntries);
    interpreter->SetTextureCacheBudgetBytes((size_t) budget);
}
