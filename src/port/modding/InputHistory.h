#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct Evt;

#define MOD_INPUT_HISTORY_FRAMES 64

typedef enum ModInputMatch {
    MOD_INPUT_MATCH_ANY,
    MOD_INPUT_MATCH_ONLY,
    MOD_INPUT_MATCH_BYTE_EXACT,
} ModInputMatch;

typedef void (*ModInputFrameFn)(uint32_t frame, uint32_t held, uint32_t pressed);

uint32_t Mod_InputFrame(void);
uint32_t Mod_InputPressedAt(uint32_t frame);
uint32_t Mod_InputHeldAt(uint32_t frame);
bool Mod_InputMatches(uint32_t pressed, uint32_t mask, int32_t match);
bool Mod_InputPressedSince(uint32_t frame, uint32_t mask, int32_t match);
bool Mod_InputPressedWithin(uint32_t frames, uint32_t mask, int32_t match);
int32_t Mod_InputFirstPress(uint32_t since, uint32_t mask, int32_t match);
void Mod_RegisterInputFrameListener(const char* owner, ModInputFrameFn fn);

int32_t Mod_EvtInputMarkFrame(struct Evt* script, bool isInitialCall);
int32_t Mod_EvtInputPressedSince(struct Evt* script, bool isInitialCall);
int32_t Mod_EvtInputPressedWithin(struct Evt* script, bool isInitialCall);

#ifdef __cplusplus
}
#endif
