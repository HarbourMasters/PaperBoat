#include "ultra64.h"
#include <string.h>

// Format: https://wiki.cloudmodding.com/oot/Yay0
void decode_yay0(void* src, void* dst) {
    u8* srcBytes = (u8*)src;
    u8* dstBytes = (u8*)dst;
    const u32 YAY0_MAX_DECOMP_SIZE = 0x40000;

    u32 magic = (srcBytes[0] << 24) | (srcBytes[1] << 16) | (srcBytes[2] << 8) | srcBytes[3];
    u32 decompSize = (srcBytes[4] << 24) | (srcBytes[5] << 16) | (srcBytes[6] << 8) | srcBytes[7];

    u32 linkTableOffset = (srcBytes[8] << 24) | (srcBytes[9] << 16) | (srcBytes[10] << 8) | srcBytes[11];
    u32 chunkOffset = (srcBytes[12] << 24) | (srcBytes[13] << 16) | (srcBytes[14] << 8) | srcBytes[15];

    if (magic != 0x59617930) {
        // Not a valid file
        memcpy(dst, src, decompSize);
        return;
    }

    // Clamp to a sane maximum to avoid overrunning fixed buffers (e.g. gMapShapeData)
    if (decompSize > YAY0_MAX_DECOMP_SIZE) {
        decompSize = YAY0_MAX_DECOMP_SIZE;
    }

    u8* linkTable = srcBytes + linkTableOffset;
    u8* chunkData = srcBytes + chunkOffset;
    u32 codeOffset = 16; // Start after header
    u32 dstPos = 0;
    u32 linkPos = 0;
    u32 chunkPos = 0;

    while (dstPos < decompSize) {
        // Read code byte (bit field)
        u8 code = srcBytes[codeOffset++];

        for (int i = 0; i < 8 && dstPos < decompSize; i++) {
            if (code & 0x80) {
                // Bit is 1: copy one byte directly from chunk data
                dstBytes[dstPos++] = chunkData[chunkPos++];
            } else {
                // Bit is 0: copy from link table (RLE)
                u8 byte1 = linkTable[linkPos++];
                u8 byte2 = linkTable[linkPos++];

                u32 dist = ((byte1 & 0x0F) << 8) | byte2;
                u32 count = (byte1 >> 4);

                if (count == 0) {
                    count = chunkData[chunkPos++] + 0x12;
                } else {
                    count += 2;
                }

                // Copy from earlier in the output
                u32 srcPos = dstPos - (dist + 1);
                for (u32 j = 0; j < count && dstPos < decompSize; j++) {
                    dstBytes[dstPos++] = dstBytes[srcPos++];
                }
            }

            code <<= 1;
        }
    }
}