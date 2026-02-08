#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "libultraship/libultra/abi.h"

// ============================================================================
// Standard ABI macro overrides (non-n_* versions)
// ============================================================================

#undef aSegment
#undef aClearBuffer
#undef aDMEMMove
#undef aMix
#undef aSetLoop
#undef aLoadADPCM

// ============================================================================
// n_abi.h macro overrides
// ============================================================================

#undef n_aADPCMdec
#undef n_aPoleFilter
#undef n_aEnvMixer
#undef n_aInterleave
#undef n_aLoadBuffer
#undef n_aResample
#undef n_aSaveBuffer
#undef n_aSetVolume
#undef n_aLoadADPCM

// ============================================================================
// Standard ABI implementation declarations
// ============================================================================

void aClearBufferImpl(uint16_t addr, int nbytes);
void aLoadADPCMImpl(int num_entries_times_16, const int16_t* book_source_addr);
void aDMEMMoveImpl(uint16_t in_addr, uint16_t out_addr, int nbytes);
void aSetLoopImpl(ADPCM_STATE* adpcm_loop_state);
void aMixImpl(uint16_t count, int16_t gain, uint16_t in_addr, uint16_t out_addr);

// ============================================================================
// n_abi implementation declarations
// ============================================================================

// n_aADPCMdec(pkt, s, f, c, a, d)
// s = state pointer (ADPCM_STATE), f = flags, c = count (samples * 2), a = align offset, d = dmem output addr
void n_aADPCMdecImpl(void* state, uint8_t flags, uint16_t count, uint8_t align, uint16_t dmem_out);

// n_aPoleFilter(pkt, f, g, t, s)
// f = flags (first = A_INIT), g = gain, t = dmem buffer (shifted), s = state pointer
void n_aPoleFilterImpl(uint8_t flags, uint16_t gain, uint8_t dmem_shift, void* state);

// n_aEnvMixer(pkt, f, t, s)
// f = flags (A_INIT or A_CONTINUE), t = initial right volume (when A_INIT), s = state pointer
void n_aEnvMixerImpl(uint8_t flags, uint16_t init_vol_r, void* state);

// n_aInterleave(pkt)
// No parameters - uses preset DMEM addresses
void n_aInterleaveImpl(void);

// n_aLoadBuffer(pkt, c, d, s)
// c = count in bytes, d = dmem dest, s = dram source
void n_aLoadBufferImpl(uint16_t count, uint16_t dmem, void* dram);

// n_aResample(pkt, s, f, p, i, o)
// s = state pointer, f = flags (first = true), p = pitch, i = dmem in offset, o = dmem out offset (0-3)
void n_aResampleImpl(void* state, uint8_t flags, uint16_t pitch, uint16_t in_offset, uint8_t out_offset);

// n_aSaveBuffer(pkt, c, d, s)
// c = count in bytes, d = dmem source, s = dram dest
void n_aSaveBufferImpl(uint16_t count, uint16_t dmem, void* dram);

// n_aSetVolume(pkt, f, v, t, r)
// f = flags: A_RATE, A_VOL|A_LEFT, A_VOL|A_RIGHT
// Parameters vary based on flags:
//   A_RATE:        v = left target, t = left rate M, r = left rate L
//   A_VOL|A_LEFT:  v = left volume, t = dry amount, r = wet amount
//   A_VOL|A_RIGHT: v = right target, t = right rate M, r = right rate L
void n_aSetVolumeImpl(uint8_t flags, uint16_t vol, uint16_t target, uint16_t rate);

// n_aLoadADPCM(pkt, c, d)
// c = count in bytes, d = ADPCM codebook data pointer
void n_aLoadADPCMImpl(uint16_t count, void* data);

// ============================================================================
// Standard ABI macro redirects
// ============================================================================

#define aSegment(pkt, s, b) \
    do {                    \
    } while (0)
#define aClearBuffer(pkt, d, c) aClearBufferImpl(d, c)
#define aLoadADPCM(pkt, c, d) aLoadADPCMImpl(c, d)
#define aDMEMMove(pkt, i, o, c) aDMEMMoveImpl(i, o, c)
#define aSetLoop(pkt, a) aSetLoopImpl(a)
#define aMix(pkt, c, g, i, o) aMixImpl(c, g, i, o)

// ============================================================================
// n_abi macro redirects (ignore pkt parameter, call Impl functions)
// ============================================================================

#define n_aADPCMdec(pkt, s, f, c, a, d) n_aADPCMdecImpl((void*)(s), f, c, a, d)
#define n_aPoleFilter(pkt, f, g, t, s) n_aPoleFilterImpl(f, g, t, (void*)(s))
#define n_aEnvMixer(pkt, f, t, s) n_aEnvMixerImpl(f, t, (void*)(s))
#define n_aInterleave(pkt) n_aInterleaveImpl()
#define n_aLoadBuffer(pkt, c, d, s) n_aLoadBufferImpl(c, d, (void*)(s))
#define n_aResample(pkt, s, f, p, i, o) n_aResampleImpl((void*)(s), f, p, i, o)
#define n_aSaveBuffer(pkt, c, d, s) n_aSaveBufferImpl(c, d, (void*)(s))
#define n_aSetVolume(pkt, f, v, t, r) n_aSetVolumeImpl(f, v, t, r)
#define n_aLoadADPCM(pkt, c, d) n_aLoadADPCMImpl(c, (void*)(d))
