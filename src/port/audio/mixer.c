#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <macros.h>

#include "mixer.h"



#ifndef __clang__
#pragma GCC optimize("unroll-loops")
#endif

#if defined(__SSE2__) || defined(__aarch64__)
#define SSE2_AVAILABLE
#else
#pragma message("Warning: SSE2 support is not available. Code will not compile")
#endif

#if defined(__SSE2__)
#include <emmintrin.h>
#elif defined(__aarch64__)
#include "sse2neon.h"
#endif

#ifdef SSE2_AVAILABLE
typedef struct {
    __m128i lo, hi;
} m256i;

static m256i m256i_mul_epi16(__m128i a, __m128i b) {
    m256i res;
    res.lo = _mm_mullo_epi16(a, b);
    res.hi = _mm_mulhi_epi16(a, b);

    m256i ret;
    ret.lo = _mm_unpacklo_epi16(res.lo, res.hi);
    ret.hi = _mm_unpackhi_epi16(res.lo, res.hi);
    return ret;
}

static m256i m256i_add_m256i_epi32(m256i a, m256i b) {
    m256i res;
    res.lo = _mm_add_epi32(a.lo, b.lo);
    res.hi = _mm_add_epi32(a.hi, b.hi);
    return res;
}

static m256i m256i_add_m128i_epi32(m256i a, __m128i b) {
    m256i res;
    res.lo = _mm_add_epi32(a.lo, b);
    res.hi = _mm_add_epi32(a.hi, b);
    return res;
}

static m256i m256i_srai(m256i a, int b) {
    m256i res;
    res.lo = _mm_srai_epi32(a.lo, b);
    res.hi = _mm_srai_epi32(a.hi, b);
    return res;
}

static __m128i m256i_clamp_to_m128i(m256i a) {
    return _mm_packs_epi32(a.lo, a.hi);
}
#endif

#define ROUND_UP_32(v) (((v) + 31) & ~31)
#define ROUND_UP_16(v) (((v) + 15) & ~15)
#define ROUND_DOWN_16(v) ((v) & ~0xf)

#define DMEM_BUF_SIZE (0xAA0) // N_AL_AUX_R_OUT + 2*AUDIO_SAMPLES
#define BUF_U8(a) (rspa.buf + (a))
#define BUF_S16(a) (int16_t*) BUF_U8(a)

// DMEM addresses used by n_* macros (from audio.h)
#define N_AL_DECODER_IN         0
#define N_AL_RESAMPLER_OUT      0
#define N_AL_TEMP_0             0
#define N_AL_DECODER_OUT        0x170
#define N_AL_TEMP_1             0x170
#define N_AL_TEMP_2             0x2E0
#define N_AL_MAIN_L_OUT         0x4E0
#define N_AL_MAIN_R_OUT         0x650
#define N_AL_AUX_L_OUT          0x7C0
#define N_AL_AUX_R_OUT          0x930

// Audio samples per frame (from audio.h)
#define AUDIO_SAMPLES           0xB8

// ============================================================================
// RSP Audio State
// ============================================================================

static struct {
    ADPCM_STATE* adpcm_loop_state;

    int16_t adpcm_table[8][2][8];

    // n_abi state for envelope mixer
    struct {
        // Set by n_aSetVolume with A_RATE
        uint16_t ltgt;    // left target volume
        uint16_t lratm;   // left rate M
        uint16_t lratl;   // left rate L

        // Set by n_aSetVolume with A_VOL | A_LEFT
        uint16_t cvolL;   // current left volume
        uint16_t dryamt;  // dry mix amount
        uint16_t wetamt;  // wet mix amount

        // Set by n_aSetVolume with A_VOL | A_RIGHT
        uint16_t rtgt;    // right target volume
        uint16_t rratm;   // right rate M
        uint16_t rratl;   // right rate L
    } env;

    uint8_t buf[DMEM_BUF_SIZE];
} rspa;

static int16_t resample_table[64][4] = {
    { 0x0c39, 0x66ad, 0x0d46, 0xffdf }, { 0x0b39, 0x6696, 0x0e5f, 0xffd8 }, { 0x0a44, 0x6669, 0x0f83, 0xffd0 },
    { 0x095a, 0x6626, 0x10b4, 0xffc8 }, { 0x087d, 0x65cd, 0x11f0, 0xffbf }, { 0x07ab, 0x655e, 0x1338, 0xffb6 },
    { 0x06e4, 0x64d9, 0x148c, 0xffac }, { 0x0628, 0x643f, 0x15eb, 0xffa1 }, { 0x0577, 0x638f, 0x1756, 0xff96 },
    { 0x04d1, 0x62cb, 0x18cb, 0xff8a }, { 0x0435, 0x61f3, 0x1a4c, 0xff7e }, { 0x03a4, 0x6106, 0x1bd7, 0xff71 },
    { 0x031c, 0x6007, 0x1d6c, 0xff64 }, { 0x029f, 0x5ef5, 0x1f0b, 0xff56 }, { 0x022a, 0x5dd0, 0x20b3, 0xff48 },
    { 0x01be, 0x5c9a, 0x2264, 0xff3a }, { 0x015b, 0x5b53, 0x241e, 0xff2c }, { 0x0101, 0x59fc, 0x25e0, 0xff1e },
    { 0x00ae, 0x5896, 0x27a9, 0xff10 }, { 0x0063, 0x5720, 0x297a, 0xff02 }, { 0x001f, 0x559d, 0x2b50, 0xfef4 },
    { 0xffe2, 0x540d, 0x2d2c, 0xfee8 }, { 0xffac, 0x5270, 0x2f0d, 0xfedb }, { 0xff7c, 0x50c7, 0x30f3, 0xfed0 },
    { 0xff53, 0x4f14, 0x32dc, 0xfec6 }, { 0xff2e, 0x4d57, 0x34c8, 0xfebd }, { 0xff0f, 0x4b91, 0x36b6, 0xfeb6 },
    { 0xfef5, 0x49c2, 0x38a5, 0xfeb0 }, { 0xfedf, 0x47ed, 0x3a95, 0xfeac }, { 0xfece, 0x4611, 0x3c85, 0xfeab },
    { 0xfec0, 0x4430, 0x3e74, 0xfeac }, { 0xfeb6, 0x424a, 0x4060, 0xfeaf }, { 0xfeaf, 0x4060, 0x424a, 0xfeb6 },
    { 0xfeac, 0x3e74, 0x4430, 0xfec0 }, { 0xfeab, 0x3c85, 0x4611, 0xfece }, { 0xfeac, 0x3a95, 0x47ed, 0xfedf },
    { 0xfeb0, 0x38a5, 0x49c2, 0xfef5 }, { 0xfeb6, 0x36b6, 0x4b91, 0xff0f }, { 0xfebd, 0x34c8, 0x4d57, 0xff2e },
    { 0xfec6, 0x32dc, 0x4f14, 0xff53 }, { 0xfed0, 0x30f3, 0x50c7, 0xff7c }, { 0xfedb, 0x2f0d, 0x5270, 0xffac },
    { 0xfee8, 0x2d2c, 0x540d, 0xffe2 }, { 0xfef4, 0x2b50, 0x559d, 0x001f }, { 0xff02, 0x297a, 0x5720, 0x0063 },
    { 0xff10, 0x27a9, 0x5896, 0x00ae }, { 0xff1e, 0x25e0, 0x59fc, 0x0101 }, { 0xff2c, 0x241e, 0x5b53, 0x015b },
    { 0xff3a, 0x2264, 0x5c9a, 0x01be }, { 0xff48, 0x20b3, 0x5dd0, 0x022a }, { 0xff56, 0x1f0b, 0x5ef5, 0x029f },
    { 0xff64, 0x1d6c, 0x6007, 0x031c }, { 0xff71, 0x1bd7, 0x6106, 0x03a4 }, { 0xff7e, 0x1a4c, 0x61f3, 0x0435 },
    { 0xff8a, 0x18cb, 0x62cb, 0x04d1 }, { 0xff96, 0x1756, 0x638f, 0x0577 }, { 0xffa1, 0x15eb, 0x643f, 0x0628 },
    { 0xffac, 0x148c, 0x64d9, 0x06e4 }, { 0xffb6, 0x1338, 0x655e, 0x07ab }, { 0xffbf, 0x11f0, 0x65cd, 0x087d },
    { 0xffc8, 0x10b4, 0x6626, 0x095a }, { 0xffd0, 0x0f83, 0x6669, 0x0a44 }, { 0xffd8, 0x0e5f, 0x6696, 0x0b39 },
    { 0xffdf, 0x0d46, 0x66ad, 0x0c39 }
};

static inline int16_t clamp16(int32_t v) {
    if (v < -0x8000) {
        return -0x8000;
    } else if (v > 0x7fff) {
        return 0x7fff;
    }
    return (int16_t) v;
}

// ============================================================================
// Standard ABI Implementations
// ============================================================================

void aClearBufferImpl(uint16_t addr, int nbytes) {
    nbytes = ROUND_UP_16(nbytes);
    memset(BUF_U8(addr), 0, nbytes);
}

void aLoadADPCMImpl(int num_entries_times_16, const int16_t* book_source_addr) {
    memcpy(rspa.adpcm_table, book_source_addr, num_entries_times_16);
}

void aDMEMMoveImpl(uint16_t in_addr, uint16_t out_addr, int nbytes) {
    nbytes = ROUND_UP_16(nbytes);
    memmove(BUF_U8(out_addr), BUF_U8(in_addr), nbytes);
}

void aSetLoopImpl(ADPCM_STATE* adpcm_loop_state) {
    rspa.adpcm_loop_state = adpcm_loop_state;
}

#ifdef SSE2_AVAILABLE
static const __attribute__((aligned(16))) int32_t x4000[4] = {
    0x4000,
    0x4000,
    0x4000,
    0x4000,
};
#endif

#ifndef SSE2_AVAILABLE

void aMixImpl(uint16_t count, int16_t gain, uint16_t in_addr, uint16_t out_addr) {
    int nbytes = count == 0 ? AUDIO_SAMPLES * sizeof(int16_t) : ROUND_UP_32(ROUND_DOWN_16(count << 4));
    int nsamples = nbytes / sizeof(int16_t);
    int16_t* in = BUF_S16(in_addr);
    int16_t* out = BUF_S16(out_addr);
    int32_t sample;

    if (gain == -0x8000) {
        for (int i = 0; i < nsamples; i++) {
            sample = *out - *in++;
            *out++ = clamp16(sample);
        }
        return;
    }

    for (int i = 0; i < nsamples; i++) {
        sample = ((*out * 0x7fff + *in++ * gain) + 0x4000) >> 15;
        *out++ = clamp16(sample);
    }
}

#else

static const __attribute__((aligned(16))) int16_t x7fff[8] = {
    0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
};

void aMixImpl(uint16_t count, int16_t gain, uint16_t in_addr, uint16_t out_addr) {
    int nbytes = count == 0 ? AUDIO_SAMPLES * sizeof(int16_t) : ROUND_UP_32(ROUND_DOWN_16(count << 4));
    int16_t* in = BUF_S16(in_addr);
    int16_t* out = BUF_S16(out_addr);

    if (gain == -0x8000) {
        while (nbytes >= 16) {
            __m128i outVec = _mm_loadu_si128((__m128i*) out);
            __m128i inVec = _mm_loadu_si128((__m128i*) in);
            __m128i subsVec = _mm_subs_epi16(outVec, inVec);
            _mm_storeu_si128((__m128i*) out, subsVec);
            nbytes -= 8 * sizeof(int16_t);
            in += 8;
            out += 8;
        }
        return;
    }

    __m128i x7fffVec = _mm_load_si128((__m128i*) x7fff);
    __m128i x4000Vec = _mm_load_si128((__m128i*) x4000);
    __m128i gainVec = _mm_set1_epi16(gain);

    while (nbytes >= 16) {
        __m128i outVec = _mm_loadu_si128((__m128i*) out);
        __m128i inVec = _mm_loadu_si128((__m128i*) in);
        m256i outx7fff = m256i_mul_epi16(outVec, x7fffVec);
        m256i inxGain = m256i_mul_epi16(inVec, gainVec);
        in += 8;

        m256i addVec = m256i_add_m256i_epi32(outx7fff, inxGain);
        addVec = m256i_add_m128i_epi32(addVec, x4000Vec);
        m256i shiftedVec = m256i_srai(addVec, 15);
        outVec = m256i_clamp_to_m128i(shiftedVec);
        _mm_storeu_si128((__m128i*) out, outVec);
        out += 8;

        nbytes -= 8 * sizeof(int16_t);
    }
}

#endif

// ============================================================================
// n_abi Implementations
// ============================================================================

// n_aLoadBuffer: Load from DRAM to DMEM
void n_aLoadBufferImpl(uint16_t count, uint16_t dmem, void* dram) {
    if (dram == NULL) {
        return;
    }
    int actual = ROUND_DOWN_16(count);
    memcpy(BUF_U8(dmem), dram, actual);
}

// n_aSaveBuffer: Save from DMEM to DRAM
void n_aSaveBufferImpl(uint16_t count, uint16_t dmem, void* dram) {
    if (dram == NULL) {
        return;
    }
    int actual = ROUND_DOWN_16(count);
    memcpy(dram, BUF_U8(dmem), actual);
}

// n_aLoadADPCM: Load ADPCM codebook
void n_aLoadADPCMImpl(uint16_t count, void* data) {
    if (data == NULL) {
        return;
    }
    memcpy(rspa.adpcm_table, data, count);
}

// n_aSetVolume: Store volume/rate state for envelope mixer
// Flags determine what parameters are being set:
//   A_RATE:        Store rate values (left target, left rate M, left rate L)
//   A_VOL|A_LEFT:  Store left volume, dry amount, wet amount
//   A_VOL|A_RIGHT: Store right target, right rate M, right rate L
void n_aSetVolumeImpl(uint8_t flags, uint16_t vol, uint16_t target, uint16_t rate) {
    if (flags == A_RATE) {
        // A_RATE: v = left target, t = left rate M, r = left rate L
        rspa.env.ltgt = vol;
        rspa.env.lratm = target;
        rspa.env.lratl = rate;
    } else if ((flags & (A_VOL | A_LEFT)) == (A_VOL | A_LEFT)) {
        // A_VOL | A_LEFT: v = current left volume, t = dry amount, r = wet amount
        rspa.env.cvolL = vol;
        rspa.env.dryamt = target;
        rspa.env.wetamt = rate;
    } else if ((flags & A_VOL) == A_VOL) {
        // A_VOL | A_RIGHT (A_RIGHT = 0): v = right target, t = right rate M, r = right rate L
        rspa.env.rtgt = vol;
        rspa.env.rratm = target;
        rspa.env.rratl = rate;
    }
}

// n_aEnvMixer: Envelope mixer using stored volume/rate state
// Uses fixed DMEM addresses:
//   Input: N_AL_RESAMPLER_OUT (0)
//   Output: N_AL_MAIN_L_OUT, N_AL_MAIN_R_OUT, N_AL_AUX_L_OUT, N_AL_AUX_R_OUT
void n_aEnvMixerImpl(uint8_t flags, uint16_t init_vol_r, void* state) {
    // The n_abi envelope mixer processes AUDIO_SAMPLES samples from the resampler output
    // and mixes them into the main L/R and aux L/R output buffers

    int16_t* in = BUF_S16(N_AL_RESAMPLER_OUT);
    int16_t* mainL = BUF_S16(N_AL_MAIN_L_OUT);
    int16_t* mainR = BUF_S16(N_AL_MAIN_R_OUT);
    int16_t* auxL = BUF_S16(N_AL_AUX_L_OUT);
    int16_t* auxR = BUF_S16(N_AL_AUX_R_OUT);

    // State is ENVMIX_STATE (40 shorts)
    // State layout (from N64 RSP):
    // [0-15]: cvolL, cvolR, ltgt, rtgt, lratm, lratl, rratm, rratl, etc.
    int16_t* envState = (int16_t*)state;

    int32_t cvolL, cvolR;
    int32_t ltgt, rtgt;
    int32_t lratm, lratl, rratm, rratl;
    int32_t dryamt, wetamt;

    if (flags & A_INIT) {
        // Initialize from n_aSetVolume calls and init_vol_r parameter
        cvolL = rspa.env.cvolL;
        cvolR = init_vol_r;  // Passed as parameter
        ltgt = rspa.env.ltgt;
        rtgt = rspa.env.rtgt;
        lratm = rspa.env.lratm;
        lratl = rspa.env.lratl;
        rratm = rspa.env.rratm;
        rratl = rspa.env.rratl;
        dryamt = rspa.env.dryamt;
        wetamt = rspa.env.wetamt;
    } else {
        // Load from saved state
        if (envState != NULL) {
            cvolL = envState[0];
            cvolR = envState[1];
            ltgt = envState[2];
            rtgt = envState[3];
            lratm = envState[4];
            lratl = envState[5];
            rratm = envState[6];
            rratl = envState[7];
            dryamt = envState[8];
            wetamt = envState[9];
        } else {
            return;
        }
    }

    // Process AUDIO_SAMPLES samples in groups of 8 (matching N64 RSP behavior)
    // Rate is 16.16 fixed-point, applied once per 8 samples
    int32_t lrate = (lratm << 16) | (uint16_t)lratl;
    int32_t rrate = (rratm << 16) | (uint16_t)rratl;
    int32_t cvolL_acc = cvolL << 16;
    int32_t cvolR_acc = cvolR << 16;

    for (int i = 0; i < AUDIO_SAMPLES; i++) {
        int32_t sample = in[i];

        // Apply left volume (VMUDM: signed sample × unsigned vol → middle word = >> 16)
        int32_t sampleL = (sample * cvolL) >> 16;
        // Accumulate into dry/wet (VMULF-like: signed × signed → >> 15)
        mainL[i] = clamp16(mainL[i] + ((sampleL * dryamt) >> 15));
        auxL[i] = clamp16(auxL[i] + ((sampleL * wetamt) >> 15));

        // Apply right volume (VMUDM: >> 16)
        int32_t sampleR = (sample * cvolR) >> 16;
        mainR[i] = clamp16(mainR[i] + ((sampleR * dryamt) >> 15));
        auxR[i] = clamp16(auxR[i] + ((sampleR * wetamt) >> 15));

        // Update volumes every 8 samples
        if ((i & 7) == 7) {
            if (cvolL != ltgt) {
                cvolL_acc += lrate;
                cvolL = cvolL_acc >> 16;
                if ((lrate > 0 && cvolL > ltgt) || (lrate < 0 && cvolL < ltgt)) {
                    cvolL = ltgt;
                    cvolL_acc = cvolL << 16;
                }
            }
            if (cvolR != rtgt) {
                cvolR_acc += rrate;
                cvolR = cvolR_acc >> 16;
                if ((rrate > 0 && cvolR > rtgt) || (rrate < 0 && cvolR < rtgt)) {
                    cvolR = rtgt;
                    cvolR_acc = cvolR << 16;
                }
            }
        }
    }

    // Save state
    if (envState != NULL) {
        envState[0] = (int16_t)cvolL;
        envState[1] = (int16_t)cvolR;
        envState[2] = (int16_t)ltgt;
        envState[3] = (int16_t)rtgt;
        envState[4] = (int16_t)lratm;
        envState[5] = (int16_t)lratl;
        envState[6] = (int16_t)rratm;
        envState[7] = (int16_t)rratl;
        envState[8] = (int16_t)dryamt;
        envState[9] = (int16_t)wetamt;
    }
}

// n_aInterleave: Interleave L/R channels using fixed DMEM addresses
// Input: N_AL_MAIN_L_OUT, N_AL_MAIN_R_OUT
// Output: DMEM address 0
void n_aInterleaveImpl(void) {
    int16_t* left = BUF_S16(N_AL_MAIN_L_OUT);
    int16_t* right = BUF_S16(N_AL_MAIN_R_OUT);
    int16_t* out = BUF_S16(0);  // Output to DMEM 0

    for (int i = 0; i < AUDIO_SAMPLES; i++) {
        *out++ = *left++;
        *out++ = *right++;
    }
}

// n_aResample: Resample audio with state
// Parameters from n_abi.h bit packing:
//   s = state pointer
//   f = flags (2 bits: bit 0 = clear, bit 1 = first/init)
//   p = pitch (16 bits)
//   i = dmem in offset (12 bits, but shifted >> 8 to get actual offset)
//   o = dmem out offset (2 bits)
void n_aResampleImpl(void* state, uint8_t flags, uint16_t pitch, uint16_t in_offset, uint8_t out_offset) {
    // State is RESAMPLE_STATE (16 shorts)
    int16_t* rsState = (int16_t*)state;
    int16_t tmp[32];

    // in_offset is the raw DMEM address (callers pass addresses like 0x170 directly)
    uint16_t in_addr = in_offset;
    uint16_t out_addr = N_AL_RESAMPLER_OUT + (out_offset << 8);

    int16_t* in_initial = BUF_S16(in_addr);
    int16_t* in = in_initial;
    int16_t* out = BUF_S16(out_addr);

    // Number of output samples = AUDIO_SAMPLES
    int nbytes = AUDIO_SAMPLES * sizeof(int16_t);
    uint32_t pitch_accumulator;

    bool first = (flags & 1) != 0;

    if (first) {
        memset(tmp, 0, 5 * sizeof(int16_t));
    } else if (rsState != NULL) {
        memcpy(tmp, rsState, 16 * sizeof(int16_t));
    }

    // Handle continuation from previous frame
    if (!first && rsState != NULL) {
        memcpy(in - 8, tmp + 8, 8 * sizeof(int16_t));
        in -= tmp[5] / sizeof(int16_t);
    }

    in -= 4;
    pitch_accumulator = (uint16_t)tmp[4];
    memcpy(in, tmp, 4 * sizeof(int16_t));

    // Resample loop
    do {
        for (int i = 0; i < 8; i++) {
            int16_t* tbl = resample_table[pitch_accumulator * 64 >> 16];
            int32_t sample = ((in[0] * tbl[0] + 0x4000) >> 15) +
                            ((in[1] * tbl[1] + 0x4000) >> 15) +
                            ((in[2] * tbl[2] + 0x4000) >> 15) +
                            ((in[3] * tbl[3] + 0x4000) >> 15);
            *out++ = clamp16(sample);

            pitch_accumulator += (pitch << 1);
            in += pitch_accumulator >> 16;
            pitch_accumulator %= 0x10000;
        }
        nbytes -= 8 * sizeof(int16_t);
    } while (nbytes > 0);

    // Save state
    if (rsState != NULL) {
        rsState[4] = (int16_t)pitch_accumulator;
        memcpy(rsState, in, 4 * sizeof(int16_t));
        int i = (in - in_initial + 4) & 7;
        in -= i;
        if (i != 0) {
            i = -8 - i;
        }
        rsState[5] = i;
        memcpy(rsState + 8, in, 8 * sizeof(int16_t));
    }
}

// n_aADPCMdec: ADPCM decode with n_abi parameters
// Parameters from n_abi.h bit packing:
//   s = state pointer
//   f = flags (4 bits)
//   c = count (12 bits, samples * 2)
//   a = align (4 bits)
//   d = dmem output address (12 bits)
void n_aADPCMdecImpl(void* state, uint8_t flags, uint16_t count, uint8_t align, uint16_t dmem_out) {
    ADPCM_STATE* adpcmState = (ADPCM_STATE*)state;

    // Input is at N_AL_DECODER_IN with alignment offset
    uint8_t* in = BUF_U8(N_AL_DECODER_IN + align);
    int16_t* out = BUF_S16(dmem_out);

    // count is samples * 2 (bytes of output)
    int nsamples = count >> 1;
    int nbytes = ROUND_UP_32(nsamples * sizeof(int16_t));

    // Initialize output based on flags
    if (flags & A_INIT) {
        memset(out, 0, 16 * sizeof(int16_t));
    } else if (flags & A_LOOP) {
        memcpy(out, rspa.adpcm_loop_state, 16 * sizeof(int16_t));
    } else if (adpcmState != NULL) {
        memcpy(out, adpcmState, 16 * sizeof(int16_t));
    }
    out += 16;

    // ADPCM decode loop
    while (nbytes > 0) {
        int shift = *in >> 4;
        int table_index = *in++ & 0xf;
        int16_t(*tbl)[8] = rspa.adpcm_table[table_index];

        for (int i = 0; i < 2; i++) {
            int16_t ins[8];
            int16_t prev1 = out[-1];
            int16_t prev2 = out[-2];

            if (flags & A_ADPCM_SHORT) {
                // 2-bit samples
                for (int j = 0; j < 2; j++) {
                    ins[j * 4] = (((*in >> 6) << 30) >> 30) << shift;
                    ins[j * 4 + 1] = ((((*in >> 4) & 0x3) << 30) >> 30) << shift;
                    ins[j * 4 + 2] = ((((*in >> 2) & 0x3) << 30) >> 30) << shift;
                    ins[j * 4 + 3] = (((*in++ & 0x3) << 30) >> 30) << shift;
                }
            } else {
                // 4-bit samples
                for (int j = 0; j < 4; j++) {
                    ins[j * 2] = (((*in >> 4) << 28) >> 28) << shift;
                    ins[j * 2 + 1] = (((*in++ & 0xf) << 28) >> 28) << shift;
                }
            }

            for (int j = 0; j < 8; j++) {
                int32_t acc = tbl[0][j] * prev2 + tbl[1][j] * prev1 + (ins[j] << 11);
                for (int k = 0; k < j; k++) {
                    acc += tbl[1][((j - k) - 1)] * ins[k];
                }
                acc >>= 11;
                *out++ = clamp16(acc);
            }
        }
        nbytes -= 16 * sizeof(int16_t);
    }

    // Save state
    if (adpcmState != NULL) {
        memcpy(adpcmState, out - 16, 16 * sizeof(int16_t));
    }

}

// n_aPoleFilter: Pole filter (lowpass)
// Parameters from n_abi.h:
//   f = flags (first = A_INIT)
//   g = gain (16 bits)
//   t = dmem buffer address (shifted)
//   s = state pointer (POLEF_STATE = 4 shorts)
void n_aPoleFilterImpl(uint8_t flags, uint16_t gain, uint8_t dmem_shift, void* state) {
    // dmem_shift is the buffer address >> 8
    uint16_t dmem_addr = dmem_shift << 8;
    int16_t* buf = BUF_S16(dmem_addr);
    POLEF_STATE* filterState = (POLEF_STATE*)state;

    // Single-pole IIR lowpass: y[n] = (gain * x[n] + coef[8] * y[n-1]) >> 14
    // gain = fgain (SCALE - timeConstant), coef[8] = timeConstant
    // SCALE = 16384 = 2^14, so gain + coef[8] = SCALE (unity DC gain)
    int16_t* coef = (int16_t*)rspa.adpcm_table;

    int32_t prev;
    if (flags & A_INIT) {
        prev = 0;
    } else if (filterState != NULL) {
        prev = (*filterState)[0];
    } else {
        prev = 0;
    }

    int32_t g = (int32_t)(int16_t)gain;
    int32_t fc = (int32_t)coef[8];

    for (int i = 0; i < AUDIO_SAMPLES; i++) {
        int32_t x = buf[i];
        int32_t y = (g * x + fc * prev) >> 14;
        y = clamp16(y);
        buf[i] = (int16_t)y;
        prev = y;
    }

    // Save state
    if (filterState != NULL) {
        (*filterState)[0] = (int16_t)prev;
    }
}
