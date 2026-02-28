#pragma once

#include <stdint.h>
#include <stddef.h>

// Forward declarations for C code
#ifdef __cplusplus
extern "C" {
#endif

void* ResourceGetDataByName(const char* name);
void* ResourceGetDataByCrc(uint64_t crc);
const char* ResourceGetNameByCrc(uint64_t crc);
size_t ResourceGetSizeByName(const char* name);
uint16_t ResourceGetTexWidthByName(const char* name);
uint16_t ResourceGetTexHeightByName(const char* name);
uint8_t GameEngine_OTRSigCheck(const char* data);

#ifdef __cplusplus
}
#endif

#define LOAD_ASSET(path) (path == NULL ? NULL : (GameEngine_OTRSigCheck((const char*) path) ? ResourceGetDataByName((const char*) path) : path))
#define LOAD_ASSET_RAW(path) ResourceGetDataByName((const char*) path)
#define LOAD_ASSET_TEX_WIDTH(path) (GameEngine_OTRSigCheck((const char*) path) ? ResourceGetTexWidthByName((const char*) path) : 0)
#define LOAD_ASSET_TEX_HEIGHT(path) (GameEngine_OTRSigCheck((const char*) path) ? ResourceGetTexHeightByName((const char*) path) : 0)

#ifdef __cplusplus
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <SDL2/SDL.h>
#include <fast/interpreter.h>
#include <libultraship.h>

#ifndef IDYES
#define IDYES 6
#endif
#ifndef IDNO
#define IDNO 7
#endif

class GameEngine {
  public:
    static GameEngine* Instance;

    std::shared_ptr<Ship::Context> context;

    GameEngine();
    void StartFrame() const;
    static bool GenAssetFile(bool exitOnFail = true);
    static void Create();
    static void HandleAudioThread();
    static void StartAudioFrame();
    static void EndAudioFrame();
    static void AudioInit();
    static void AudioExit();
    static void RunCommands(Gfx* Commands, const std::vector<std::unordered_map<Mtx*, MtxF>>& mtx_replacements);
    static void Destroy();
	static uint32_t GetInterpolationFPS();
	static uint32_t GetInterpolationFrameCount();
    static void ProcessGfxCommands(Gfx* commands);

    static int ShowYesNoBox(const char* title, const char* box);
    static void ShowMessage(const char* title, const char* message, SDL_MessageBoxFlags type = SDL_MESSAGEBOX_ERROR);

  private:
    mutable bool mPrevAltAssets = false;

    static struct {
        std::thread thread;
        std::mutex mutex;
        std::condition_variable cv_to_thread;
        std::condition_variable cv_from_thread;
        bool running = false;
        bool processing = false;
    } mAudio;
};

Fast::Interpreter* GameEngine_GetInterpreter();
#define memallocn(type, n) (type*) GameEngine_Malloc(sizeof(type) * n)
#define memalloc(type) memallocn(type, 1)

extern "C" {
#else
#include <stdint.h>
#define memalloc(size) GameEngine_Malloc(size)
#endif

void* GameEngine_Malloc(size_t size);
void GameEngine_ProcessGfxCommands(Gfx* commands);
void GameEngine_LogInfo(const char* fmt, ...);
void GameEngine_LogStackTrace(const char* label);

// Controller input - reads all 4 pads from libultraship ControlDeck
void GameEngine_ReadController(OSContPad* pads);

// C-callable context tracking for display list debugging
void GameEngine_SetDisplayListContext(const char* context);
const char* GameEngine_GetDisplayListContext(void);

// Texture debug tracking - maps memory addresses to source asset paths
void GameEngine_RegisterTextureDebugInfo(const void* addr, const char* assetPath, int rasterIdx);
const char* GameEngine_LookupTextureSource(const void* addr);

// Invalidate GPU texture cache entry for a specific RAM address.
// Call when player raster cache overwrites a buffer with new image data,
// since the Fast3D interpreter caches textures by pointer address.
void GameEngine_InvalidateTextureCache(const void* addr);

// Save file path - returns path to "pm64.sav" in app directory
// Buffer must be at least 512 bytes. Returns 0 on success, -1 on failure.
int GameEngine_GetSaveFilePath(char* buf, int bufSize);

// Clear the GPU depth buffer (replaces N64 gDPSetColorImage-to-ZBuffer hack)
void GameEngine_ClearDepthBuffer(void);

// CVar access for game C code
int GameEngine_CVarGetInteger(const char* name, int defaultValue);

#ifdef __cplusplus
}
#endif