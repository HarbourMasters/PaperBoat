#include "ShipUtils.h"
#include <libultraship/libultraship.h>

constexpr f32 fourByThree = 4.0f / 3.0f;

extern "C" bool Ship_IsCStringEmpty(const char* str) {
    return str == NULL || str[0] == '\0';
}

char seedString[MAX_SEED_STRING_SIZE];
u32 finalSeed = 0;

extern uint32_t Ship_Hash(std::string str) {
    // FNV-1a
    const size_t len = str.size();
    uint32_t hval = 0x811c9dc5;
    for (size_t pos = 0; pos < len; pos++) {
        hval ^= (uint32_t)str[pos];
        hval *= 0x01000193;
    }
    return hval;
}

// Build vertex coordinates for a quad command
// In order of top left, top right, bottom left, then bottom right
// Supports flipping the texture horizontally
extern "C" void Ship_CreateQuadVertexGroup(Vtx* vtxList, s32 xStart, s32 yStart, s32 width, s32 height, u8 flippedH) {
    vtxList[0].v.ob[0] = xStart;
    vtxList[0].v.ob[1] = yStart;
    vtxList[0].v.tc[0] = (flippedH ? width : 0) << 5;
    vtxList[0].v.tc[1] = 0 << 5;

    vtxList[1].v.ob[0] = xStart + width;
    vtxList[1].v.ob[1] = yStart;
    vtxList[1].v.tc[0] = (flippedH ? width * 2 : width) << 5;
    vtxList[1].v.tc[1] = 0 << 5;

    vtxList[2].v.ob[0] = xStart;
    vtxList[2].v.ob[1] = yStart + height;
    vtxList[2].v.tc[0] = (flippedH ? width : 0) << 5;
    vtxList[2].v.tc[1] = height << 5;

    vtxList[3].v.ob[0] = xStart + width;
    vtxList[3].v.ob[1] = yStart + height;
    vtxList[3].v.tc[0] = (flippedH ? width * 2 : width) << 5;
    vtxList[3].v.tc[1] = height << 5;
}

void LoadGuiTextures() {
    // @port: Load gui textures here
}
