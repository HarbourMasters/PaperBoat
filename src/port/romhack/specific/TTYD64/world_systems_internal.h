#pragma once

#include "common.h"
#include "port/modding/VertexColors.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"

#ifdef __cplusplus
extern "C" {
#endif

#define WS_RANDOM_ITEMS_WORDS            139
#define WS_RANDOM_BADGES_WORDS           60
#define WS_SB_RECORDS                    2
#define WS_SB_FACES                      6
#define WS_SB_VERTS                      9
#define WS_SB_REFS                       2
#define WS_SB_COLOR_BYTES                18
#define WS_RING_BLAST_BUG_THRESHOLD_BITS 0x40097050

typedef struct TTYD64_ws_SaveBlockFrame {
    u16 frame;
    u16 lastFrame;
    f32 r;
    f32 dr;
    f32 g;
    f32 dg;
    f32 b;
    f32 db;
} TTYD64_ws_SaveBlockFrame;

typedef struct TTYD64_ws_SaveBlockRecord {
    u8 colors[WS_SB_FACES][WS_SB_COLOR_BYTES];
    TTYD64_ws_SaveBlockFrame frames[WS_SB_FACES][WS_SB_VERTS];
    u16 entityIndex;
    u16 active;
} TTYD64_ws_SaveBlockRecord;

typedef void (*TTYD64_ws_SaveBlockColorSetter)(s32 face, s32 vert, u32 rgba, b32 keepAlpha);

extern const s32 TTYD64_ws_RandomItems[WS_RANDOM_ITEMS_WORDS];
extern const s32 TTYD64_ws_RandomBadges[WS_RANDOM_BADGES_WORDS];
extern const u32 TTYD64_ws_SaveBlockColorData[8];
extern const ModVertexRef TTYD64_ws_SaveBlockFaceVerts[WS_SB_FACES][WS_SB_VERTS][WS_SB_REFS];
extern const u8 TTYD64_ws_FlameColors[24];
extern const u8 TTYD64_ws_String_FFWD[];
extern const u8 TTYD64_ws_String_Page[];

extern TTYD64_ws_SaveBlockRecord TTYD64_ws_SaveBlockRecords[WS_SB_RECORDS];

s32 TTYD64_ws_RandomPick(s32 chest, s32 callerType, s32* outType);
void TTYD64_ws_FlameBodyColor(u32 mode, s32* r, s32* g, s32* b);
void TTYD64_ws_FlameOutlineColor(u32 mode, s32* r, s32* g, s32* b);
f32 TTYD64_ws_RingBlastScale(f32 unk20);
u8 TTYD64_ws_RingBlastByte(f32 scale, s32 color, b32 shiftedThreshold);
s32 TTYD64_ws_RingBlastSolve(f32 scale, u8 desired, s32 fallback);
void TTYD64_ws_RingBlastColors(u8 poisonDrive, s32 slot, f32 scale, s32* r, s32* g, s32* b);
void TTYD64_ws_FileBoxColors(s32 fileIndex, u32 out[4]);
void TTYD64_ws_FFWDPrinterAcquired(TTYD64FFWDState* ffwd);
void TTYD64_ws_FFWDSpeed(const TTYD64FFWDState* ffwd, s32* charsPerFrame, s32* skip);
void TTYD64_ws_FFWDReset(TTYD64FFWDState* ffwd);
void TTYD64_ws_FFWDInputEnabled(TTYD64FFWDState* ffwd, s32 keepFFWD);
void TTYD64_ws_FFWDBattleStateSet(TTYD64FFWDState* ffwd, s32 keepFFWD);
s32 TTYD64_ws_FFWDFrame(TTYD64FFWDState* ffwd, u32 pressedButtons);
b32 TTYD64_ws_BowBattlePartner(s32 battleState, s32 mode, s32 partner);
s32 TTYD64_ws_BowAfterBattlePartner(s32 mode, s32 curPartner, s32 lastPartner);
s32 TTYD64_ws_FileBoxIndex(u8 menuState, u8 copyFromIdx, u8 selected);
b32 TTYD64_ws_ConsumableChoiceMatch(const s32* itemList);
void TTYD64_ws_SaveBlockReset(void);
void TTYD64_ws_SaveBlockAnimate(s32 listIndex, TTYD64_ws_SaveBlockColorSetter set);

#ifdef __cplusplus
}
#endif
