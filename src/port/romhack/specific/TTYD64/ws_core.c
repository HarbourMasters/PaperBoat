#include "port/romhack/specific/TTYD64/ws_internal.h"
#include <math.h>
#include <string.h>

TTYD64_ws_SaveBlockRecord TTYD64_ws_SaveBlockRecords[WS_SB_RECORDS];

void TTYD64_ConvertAsciiToPM64String(u8* dest, const char* ascii) {
    u8* out = dest + 8;

    while (*ascii != 0) {
        if (*ascii == ' ') {
            *out = 0xF7;
        } else {
            *out = (u8) (*ascii - 0x20);
        }
        out++;
        ascii++;
    }
    *out = 0xFD;
}

s32 TTYD64_ws_RandomPick(s32 chest, s32 callerType, s32* outType) {
    const s32* table = TTYD64_ws_RandomItems;
    s32 count = 0x8B;
    s32 type = callerType;

    if ((u32) rand_int(100) < 30) {
        table = TTYD64_ws_RandomBadges;
        if (chest != 0) {
            type = 2;
        }
        count = 0x3C;
    }
    count = rand_int(count - 1);
    *outType = type;
    return table[count];
}

void TTYD64_ws_FlameBodyColor(u32 mode, s32* r, s32* g, s32* b) {
    switch (mode) {
        case 0:
            return;
        case 1:
            *r = 0x50;
            *g = 0x87;
            *b = 0x63;
            break;
        case 2:
            *r = 0x87;
            *g = 0x50;
            *b = 0x87;
            break;
        case 3:
            *r = 0xE0;
            *g = 0xE0;
            *b = 0xE0;
            break;
        case 4:
            *r = 0x35;
            *g = 0xE1;
            *b = 0xEE;
            break;
        default:
            *r = 0;
            *g = 0;
            *b = 0;
            break;
    }
}

void TTYD64_ws_FlameOutlineColor(u32 mode, s32* r, s32* g, s32* b) {
    switch (mode) {
        case 0:
            return;
        case 1:
            *r = 0x1D;
            *g = 0x41;
            *b = 0x3D;
            break;
        case 2:
            *r = 0x41;
            *g = 0x1D;
            *b = 0x40;
            break;
        case 3:
            *r = 0x76;
            *g = 0x76;
            *b = 0x76;
            break;
        case 4:
            *r = 0x26;
            *g = 0x77;
            *b = 0x7D;
            break;
        default:
            *r = 0xFF;
            *g = 0xFF;
            *b = 0xFF;
            break;
    }
}

f32 TTYD64_ws_RingBlastScale(f32 unk20) {
    f32 scale = 1.0f;

    if (unk20 > 5.0f) {
        scale = 1.0f - (unk20 - 5.0f);
        if (scale < 0.0f) {
            scale = 0.0f;
        }
    }
    return scale;
}

u8 TTYD64_ws_RingBlastByte(f32 scale, s32 color, b32 shiftedThreshold) {
    union {
        u32 bits;
        f32 f;
    } threshold;
    f32 value = scale * (f32) color;
    s32 out;

    threshold.bits = shiftedThreshold ? WS_RING_BLAST_BUG_THRESHOLD_BITS : 0x4F000000;
    if (threshold.f <= value) {
        out = (s32) (value - threshold.f) | (s32) 0x80000000;
    } else {
        out = (s32) value;
    }
    return (u8) out;
}

s32 TTYD64_ws_RingBlastSolve(f32 scale, u8 desired, s32 fallback) {
    s32 start;
    s32 span;
    s32 c;

    if (((u32) (scale * (f32) fallback) & 0xFF) == desired) {
        return fallback;
    }
    if (desired == 0) {
        return 0;
    }
    if (!(scale > 0.0f)) {
        return fallback;
    }
    start = (s32) ((f32) desired / scale) - 2;
    if (start < 0) {
        start = 0;
    }
    span = (s32) (1.0f / scale) + 6;
    for (c = start; c <= start + span; c++) {
        if (((u32) (scale * (f32) c) & 0xFF) == desired) {
            return c;
        }
    }
    return fallback;
}

void TTYD64_ws_RingBlastColors(u8 poisonDrive, s32 slot, f32 scale, s32* r, s32* g, s32* b) {
    const u8* row = &TTYD64_ws_FlameColors[poisonDrive != 0 ? 0xC : 0];
    s32 cr = row[slot * 4 + 0];
    s32 cg = row[slot * 4 + 1];
    s32 cb = row[slot * 4 + 2];

    *r = TTYD64_ws_RingBlastSolve(scale, TTYD64_ws_RingBlastByte(scale, cr, true), cr);
    if (slot == 2) {
        *g = TTYD64_ws_RingBlastSolve(scale, TTYD64_ws_RingBlastByte(scale, cg, true), cg);
    } else {
        *g = cg;
    }
    *b = cb;
}

void TTYD64_ws_FileBoxColors(s32 fileIndex, u32 out[4]) {
    switch (fileIndex) {
        case 0:
            out[0] = 0xFFFFFFFF;
            out[1] = 0xC7BFA9FF;
            out[2] = 0xFFD86CFF;
            out[3] = 0x92761AFF;
            break;
        case 1:
            out[0] = 0xFFFFFFFF;
            out[1] = 0xC7A9A9FF;
            out[2] = 0xFF6C6CFF;
            out[3] = 0x921A1AFF;
            break;
        case 2:
            out[0] = 0xFFFFFFFF;
            out[1] = 0xB0C7A9FF;
            out[2] = 0x6CFF71FF;
            out[3] = 0x1A921CFF;
            break;
        case 3:
            out[0] = 0xFFFFFFFF;
            out[1] = 0xACA9C7FF;
            out[2] = 0x806CFFFF;
            out[3] = 0x1A4292FF;
            break;
        default:
            out[0] = 0xFFFFFFFF;
            out[1] = 0xC8C8AAFF;
            out[2] = 0xFFEE6AFF;
            out[3] = 0x92641AFF;
            break;
    }
}

void TTYD64_ws_SaveBlockReset(void) {
    s32 i;
    s32 face;

    for (i = 0; i < WS_SB_RECORDS; i++) {
        TTYD64_ws_SaveBlockRecord* rec = &TTYD64_ws_SaveBlockRecords[i];

        rec->entityIndex = 0xFFFF;
        rec->active = 0;
        for (face = 0; face < WS_SB_FACES; face++) {
            TTYD64_ws_SaveBlockFrame* frames = rec->frames[face];

            memset(rec->colors[face], 0, WS_SB_COLOR_BYTES);
            memset(&frames[0], 0, sizeof(frames[0]));
            memset(&frames[1], 0, sizeof(frames[1]));
            memset(&frames[2], 0, sizeof(frames[2]));
            frames[3].frame = 0;
            frames[3].lastFrame = 0;
            frames[3].r = 0.0f;
        }
    }
}

static f32 sb_delta(u32 from, u32 to, u16 lastFrame) {
    f32 delta = 0.0f;

    if (from != to) {
        b32 rising = from < to;
        s32 diff = rising ? (s32) (to - from) : (s32) (from - to);

        delta = (f32) diff / (f32) lastFrame;
        if (!rising) {
            delta = delta * -1.0f;
        }
    }
    return delta;
}

static u8 sb_round(f32 value) {
    return (u8) (s32) lrintf(value);
}

void TTYD64_ws_SaveBlockAnimate(s32 listIndex, TTYD64_ws_SaveBlockColorSetter set) {
    TTYD64_ws_SaveBlockRecord* rec = NULL;
    s32 face;
    s32 v;
    s32 c;
    s32 i;

    for (i = 0; i < WS_SB_RECORDS; i++) {
        if (TTYD64_ws_SaveBlockRecords[i].entityIndex == (u32) listIndex) {
            rec = &TTYD64_ws_SaveBlockRecords[i];
            break;
        }
    }
    if (rec == NULL) {
        for (i = 0; i < WS_SB_RECORDS; i++) {
            if (TTYD64_ws_SaveBlockRecords[i].active == 0) {
                rec = &TTYD64_ws_SaveBlockRecords[i];
                rec->entityIndex = (u16) listIndex;
                rec->active = 1;
                break;
            }
        }
    }
    if (rec == NULL) {
        return;
    }

    if (rec->colors[0][0] == 0) {
        for (face = 0; face < WS_SB_FACES; face++) {
            for (v = 0; v < WS_SB_VERTS; v++) {
                u32 word;

                do {
                    c = rand_int(7);
                } while (c == 0);
                rec->colors[face][v] = c;
                word = TTYD64_ws_SaveBlockColorData[c];
                rec->frames[face][0].r = (f32) (s32) ((word >> 24) & 0xFF);
                rec->frames[face][0].g = (f32) (s32) ((word >> 16) & 0xFF);
                rec->frames[face][0].b = (f32) (s32) ((word >> 8) & 0xFF);
            }
        }
        for (face = 0; face < WS_SB_FACES; face++) {
            for (v = 0; v < WS_SB_VERTS; v++) {
                set(face, v, TTYD64_ws_SaveBlockColorData[rec->colors[face][v]], false);
            }
        }
    }

    for (face = 0; face < WS_SB_FACES; face++) {
        v = 0;
        while (v < WS_SB_VERTS) {
            u8* col = &rec->colors[face][v];
            TTYD64_ws_SaveBlockFrame* fr = &rec->frames[face][v];
            u32 from;
            u32 to;
            u32 nextFrame;

            if (fr->frame == fr->lastFrame) {
                memset(fr, 0, sizeof(*fr));
                col[0] = col[9];
                do {
                    c = rand_int(7);
                } while (c == 0 || c == col[0]);
                col[9] = c;
                fr->lastFrame = rand_int(10) + 10;
                from = TTYD64_ws_SaveBlockColorData[col[0]];
                to = TTYD64_ws_SaveBlockColorData[col[9]];
                fr->r = (f32) (s32) ((from >> 24) & 0xFF);
                fr->dr = sb_delta((from >> 24) & 0xFF, (to >> 24) & 0xFF, fr->lastFrame);
                fr->g = (f32) (s32) ((from >> 16) & 0xFF);
                fr->dg = sb_delta((from >> 16) & 0xFF, (to >> 16) & 0xFF, fr->lastFrame);
                fr->b = (f32) (s32) ((from >> 8) & 0xFF);
                fr->db = sb_delta((from >> 8) & 0xFF, (to >> 8) & 0xFF, fr->lastFrame);
                continue;
            }

            fr->r = fr->r + fr->dr;
            fr->g = fr->g + fr->dg;
            fr->b = fr->b + fr->db;
            set(face, v, ((u32) sb_round(fr->r) << 24) | ((u32) sb_round(fr->g) << 16) | ((u32) sb_round(fr->b) << 8),
                true);
            nextFrame = (u32) fr->frame + 1;
            fr->frame = (u16) nextFrame;
            if (nextFrame == fr->lastFrame) {
                set(face, v, TTYD64_ws_SaveBlockColorData[col[9]], false);
            }
            v++;
        }
    }
}

void TTYD64_ws_FFWDPrinterAcquired(TTYD64FFWDState* ffwd) {
    if (ffwd->suppressed != 0) {
        ffwd->printerOpen = 0;
    } else {
        ffwd->printerOpen = 1;
    }
}

static b32 ws_ffwd_active(const TTYD64FFWDState* ffwd) {
    return ffwd->enabled != 0 && ffwd->suppressed == 0;
}

void TTYD64_ws_FFWDSpeed(const TTYD64FFWDState* ffwd, s32* charsPerFrame, s32* skip) {
    if (ws_ffwd_active(ffwd)) {
        *charsPerFrame = 0x32;
        *skip = true;
    }
}

void TTYD64_ws_FFWDReset(TTYD64FFWDState* ffwd) {
    ffwd->enabled = 0;
    ffwd->printerOpen = 0;
    ffwd->suppressed = 0;
}

void TTYD64_ws_FFWDInputEnabled(TTYD64FFWDState* ffwd, s32 keepFFWD) {
    ffwd->printerOpen = 0;
    if (!keepFFWD) {
        TTYD64_ws_FFWDReset(ffwd);
    }
}

void TTYD64_ws_FFWDBattleStateSet(TTYD64FFWDState* ffwd, s32 keepFFWD) {
    if (!keepFFWD) {
        TTYD64_ws_FFWDReset(ffwd);
    }
    ffwd->printerOpen = 0;
}

s32 TTYD64_ws_FFWDFrame(TTYD64FFWDState* ffwd, u32 pressedButtons) {
    s32 style;

    if (ffwd->suppressed != 0 || ffwd->printerOpen == 0) {
        return -1;
    }
    style = ffwd->enabled != 0 ? 2 : 0;
    if (pressedButtons & BUTTON_START) {
        ffwd->enabled = ffwd->enabled == 0 ? 1 : 0;
    }
    return style;
}

b32 TTYD64_ws_BowBattlePartner(s32 battleState, s32 mode, s32 partner) {
    if (battleState == 0x1D) {
        return false;
    }
    if (mode != 1) {
        return false;
    }
    if (partner == 5 || partner == 0xB) {
        return false;
    }
    return true;
}

s32 TTYD64_ws_BowAfterBattlePartner(s32 mode, s32 curPartner, s32 lastPartner) {
    if (mode != 1) {
        return curPartner;
    }
    if (curPartner == 5 || curPartner == 0xB) {
        return curPartner;
    }
    return lastPartner;
}

s32 TTYD64_ws_FileBoxIndex(u8 menuState, u8 copyFromIdx, u8 selected) {
    if (menuState == 4) {
        return copyFromIdx;
    }
    return selected;
}

b32 TTYD64_ws_ConsumableChoiceMatch(const s32* itemList) {
    return itemList[0] > 0;
}
