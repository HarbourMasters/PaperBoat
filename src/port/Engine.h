#pragma once

#include <stdint.h>
#include <stddef.h>
#include "build.h"

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
// Vanilla bytes regardless of alt assets; for data the CPU reads or copies.
void* GameEngine_GetDataExact(const char* name);
size_t GameEngine_GetSizeExact(const char* name);
uint16_t GameEngine_GetTexWidthExact(const char* name);
uint16_t GameEngine_GetTexHeightExact(const char* name);

// --- Widescreen helpers ---
float GameEngine_GetAspectRatio(void);
float OTRGetDimensionFromLeftEdge(float v);
float OTRGetDimensionFromRightEdge(float v);
float OTRGetDimensionFromLeftEdgeForcedAspect(float v, float aspectRatio);
float OTRGetDimensionFromRightEdgeForcedAspect(float v, float aspectRatio);
int16_t OTRGetRectDimensionFromLeftEdge(float v);
int16_t OTRGetRectDimensionFromRightEdge(float v);
int16_t OTRGetRectDimensionFromLeftEdgeForcedAspect(float v, float aspectRatio);
int16_t OTRGetRectDimensionFromRightEdgeForcedAspect(float v, float aspectRatio);
int16_t OTRGetScissorCoordX(float v);
uint32_t OTRGetGameRenderWidth(void);
uint32_t OTRGetGameRenderHeight(void);

#ifdef __cplusplus
}
#endif

#define LOAD_ASSET(path) (path == NULL ? NULL : (GameEngine_OTRSigCheck((const char*) path) ? GameEngine_GetDataExact((const char*) path) : path))
#define LOAD_ASSET_RAW(path) GameEngine_GetDataExact((const char*) path)
#define LOAD_ASSET_GFX(path) (path)
#define LOAD_ASSET_TEX_WIDTH(path) (GameEngine_OTRSigCheck((const char*) path) ? GameEngine_GetTexWidthExact((const char*) path) : 0)
#define LOAD_ASSET_TEX_HEIGHT(path) (GameEngine_OTRSigCheck((const char*) path) ? GameEngine_GetTexHeightExact((const char*) path) : 0)

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

extern Ship::Context* gShipContext;

class GameEngine {
  public:
    static GameEngine* Instance;

    ImFont *fontStandard;
    ImFont *fontStandardLarger;
    ImFont *fontStandardLargest;
    ImFont *fontMono;
    ImFont *fontMonoLarger;
    ImFont *fontMonoLargest;

    Ship::Context* context;

    GameEngine();
    void StartFrame() const;
    void RenderGuiFrame() const;
    void PollControllers() const;
    static void DrainRenderService();
    static void ShutdownRenderService();
    static bool GenAssetFile(bool exitOnFail = true);
    static void Create(int argc, char* argv[]);
    static void AudioInit();
    static void AudioExit();
    void FinishInit();
    void RunExtract(int argc, char* argv[]);
    static bool sRelaunchRequested;
    static bool CanRelaunch();
    static void RequestRelaunch() {
        sRelaunchRequested = true;
    }
    static void RelaunchIfRequested(int argc, char* argv[]);

    static void RunCommands(Gfx* Commands, const std::vector<std::unordered_map<Mtx*, MtxF>>& mtx_replacements);
    static void Destroy();
    static uint32_t GetInterpolationFPS();
    static uint32_t GetInterpolationFrameCount();
    static void ProcessGfxCommands(Gfx* commands);

    static int ShowYesNoBox(const char* title, const char* box);
    static void ShowMessage(const char* title, const char* message, SDL_MessageBoxFlags type = SDL_MESSAGEBOX_ERROR);
    static ImFont *CreateFontWithSize(float size, std::string fontPath);
    static void ScaleImGui();

  private:
    mutable bool mPrevAltAssets = false;
    mutable bool mPrevDPadAsLeftStick = false;
    mutable bool mPrevAutoMipmaps = true;

    static struct {
        bool running = false;
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
#ifdef __cplusplus
void GameEngine_ProcessGfxCommands(Gfx* commands);
#else
// In C translation units the N64 typedefs may not be visible yet, so declare
// with void* and let callers cast.  The actual definition in Engine.cpp uses
// the real types.
void GameEngine_ProcessGfxCommands(void* commands);
#endif
void GameEngine_LogInfo(const char* fmt, ...);
void GameEngine_LogStackTrace(const char* label);

// Controller input - reads all 4 pads from libultraship ControlDeck
#ifdef __cplusplus
void GameEngine_ReadController(OSContPad* pads);
#else
void GameEngine_ReadController(void* pads);
#endif

// Invalidate GPU texture cache entry for a specific RAM address.
// Call when player raster cache overwrites a buffer with new image data,
// since the Fast3D interpreter caches textures by pointer address.
void GameEngine_InvalidateTextureCache(const void* addr);
void GameEngine_PrefetchTextures(const char* group);
void gfx_texture_cache_clear(void);

void port_nuGfxOnSubmit(void* task);
void port_runOnRenderThread(void (*fn)(void*), void* arg);

#ifdef __cplusplus
}
#endif
