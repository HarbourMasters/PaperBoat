// GBI Middleware - Intercepts GBI macro calls to handle OTR path resolution
// This allows static display lists (like curtains.c) to use OTR paths for vertices and textures

#include "Engine.h"
#include <libultraship.h>

// G_SETTIMG_OTR_FILEPATH opcode for OTR texture paths (from libultraship gbi.h)
#define G_SETTIMG_OTR_FILEPATH 0x25

extern "C" void gSPVertexOTR(Gfx* pkt, uintptr_t v, int n, int v0) {
    if (GameEngine_OTRSigCheck((const char*)v)) {
        const char* path = (const char*)v;
        void* data = ResourceGetDataByName(path);
        v = (uintptr_t)data;
    }
    __gSPVertex(pkt, v, n, v0);
}

extern "C" void gDPSetTextureImageOTR(Gfx* pkt, int fmt, int siz, int width, uintptr_t img) {
    if (GameEngine_OTRSigCheck((const char*)img)) {
        // Use G_SETTIMG_OTR_FILEPATH opcode for OTR paths
        const char* path = (const char*)img;
        gSetImage(pkt, G_SETTIMG_OTR_FILEPATH, fmt, siz, width, img);
    } else {
        // Regular texture - use normal G_SETTIMG
        gSetImage(pkt, G_SETTIMG, fmt, siz, width, img);
    }
}
