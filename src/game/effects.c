#include "common.h"
#include "effects.h"
#include "ld_addrs.h"
#include "port/Engine.h"

typedef s8 TlbEntry[0x1000];
typedef TlbEntry TlbMappablePage[15];

#define EFFECT_GLOBALS_TLB_IDX 0x10

BSS EffectSharedData gEffectSharedData[15];
EffectInstance* gEffectInstances[96];

extern TlbMappablePage gEffectDataBuffer;
extern Addr gEffectGlobals;

#define FX_ENTRY(name, gfx_name) { \
    .entryPoint = name##_main, \
    .dmaStart = effect_##name##_ROM_START, \
    .dmaEnd = effect_##name##_ROM_END, \
    .dmaDest = effect_##name##_VRAM, \
    .graphicsDmaStart = gfx_name##_ROM_START, \
    .graphicsDmaEnd = gfx_name##_ROM_END, \
}

#include "effects/effect_table.c"

s32 D_8007FEB8[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 5, 3, 4, 13, 60, 0, 512, 0, 0, 3, 0 };

/// Used for unbound function points in effect structs.
void stub_effect_delegate(EffectInstance* effect) {
}

void set_effect_pos_offset(EffectInstance* effect, f32 x, f32 y, f32 z) {
    s32* data = effect->data.any;

    ((f32*)data)[1] = x;
    ((f32*)data)[2] = y;
    ((f32*)data)[3] = z;
}

void clear_effect_data(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffectSharedData); i++) {
        gEffectSharedData[i].flags = 0;
    }

    for (i = 0; i < ARRAY_COUNT(gEffectInstances); i++) {
        gEffectInstances[i] = nullptr;
    }

    osUnmapTLBAll();
    osMapTLB(EFFECT_GLOBALS_TLB_IDX, OS_PM_4K, effect_globals_VRAM, (s32)&gEffectGlobals & 0xFFFFFF, -1, -1);
    DMA_COPY_SEGMENT(effect_globals);
}

void func_80059D48(void) {
}

void update_effects(void) {
    if (!(gOverrideFlags & (GLOBAL_OVERRIDES_800 | GLOBAL_OVERRIDES_400))) {
        EffectSharedData* sharedData;
        s32 i;

        // reset free delay for each EffectSharedData touched in previous update
        for (i = 0, sharedData = gEffectSharedData; i < ARRAY_COUNT(gEffectSharedData); i++, sharedData++) {
            if (sharedData->flags & FX_SHARED_DATA_LOADED) {
                if (!(sharedData->flags & FX_SHARED_DATA_CAN_FREE)) {
                    sharedData->flags |= FX_SHARED_DATA_CAN_FREE;
                    sharedData->freeDelay = 3;
                }
            }
        }

        // update each EffectInstances
        for (i = 0; i < ARRAY_COUNT(gEffectInstances); i++) {
            EffectInstance* effectInstance = gEffectInstances[i];

            if (effectInstance != nullptr && (effectInstance->flags & FX_INSTANCE_FLAG_ENABLED)) {
                effectInstance->shared->flags &= ~FX_SHARED_DATA_CAN_FREE;

                EffectSharedData* sd = effectInstance->shared;
                void (*updateFunc)(EffectInstance*) = sd->update;
                if (updateFunc == NULL || (uintptr_t)updateFunc < 0x100000000ULL) {
                    GameEngine_LogInfo("Bad update ptr %p for effect %d (inst %d, shared=%p)",
                        updateFunc, effectInstance->effectID, i, sd);
                    GameEngine_LogInfo("  shared: flags=0x%x idx=%d cnt=%d delay=%d update=%p scene=%p ui=%p gfx=%p",
                        sd->flags, sd->effectIndex, sd->instanceCounter, sd->freeDelay,
                        sd->update, sd->renderScene, sd->renderUI, sd->graphics);
                    // Dump raw bytes of the shared data to see corruption pattern
                    u8* raw = (u8*)sd;
                    GameEngine_LogInfo("  raw[0..47]: %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x "
                        "%02x%02x%02x%02x%02x%02x%02x%02x %02x%02x%02x%02x%02x%02x%02x%02x "
                        "%02x%02x%02x%02x%02x%02x%02x%02x %02x%02x%02x%02x%02x%02x%02x%02x",
                        raw[0],raw[1],raw[2],raw[3], raw[4],raw[5],raw[6],raw[7],
                        raw[8],raw[9],raw[10],raw[11], raw[12],raw[13],raw[14],raw[15],
                        raw[16],raw[17],raw[18],raw[19],raw[20],raw[21],raw[22],raw[23],
                        raw[24],raw[25],raw[26],raw[27],raw[28],raw[29],raw[30],raw[31],
                        raw[32],raw[33],raw[34],raw[35],raw[36],raw[37],raw[38],raw[39],
                        raw[40],raw[41],raw[42],raw[43],raw[44],raw[45],raw[46],raw[47]);
                    continue;
                }

                if (gGameStatusPtr->context != CONTEXT_WORLD) {
                    if (effectInstance->flags & FX_INSTANCE_FLAG_BATTLE) {
                        updateFunc(effectInstance);
                        effectInstance->flags |= FX_INSTANCE_FLAG_HAS_UPDATED;
                    }
                } else {
                    if (!(effectInstance->flags & FX_INSTANCE_FLAG_BATTLE)) {
                        updateFunc(effectInstance);
                        effectInstance->flags |= FX_INSTANCE_FLAG_HAS_UPDATED;
                    }
                }
            }
        }

        // free any EffectSharedData which haven't been used recently
        for (i = 0, sharedData = gEffectSharedData; i < ARRAY_COUNT(gEffectSharedData); i++, sharedData++) {
            if (sharedData->flags & FX_SHARED_DATA_LOADED) {
                if (sharedData->flags & FX_SHARED_DATA_CAN_FREE) {
                    if (sharedData->freeDelay != 0) {
                        sharedData->freeDelay--;
                    } else {
                        // On port, graphics is always NULL or (void*)1 sentinel.
                        // Never heap-allocated, so never free.
                        sharedData->graphics = nullptr;
                        sharedData->flags = 0;
                        osUnmapTLB(i);
                    }
                }
            }
        }
    }
}

void render_effects_scene(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffectInstances); i++) {
        EffectInstance* effectInstance = gEffectInstances[i];

        if (effectInstance != nullptr) {
            FrameInterpolation_RecordOpenChild("effect_render", TAG_EFFECT(i, effectInstance));
            if (effectInstance->flags & FX_INSTANCE_FLAG_ENABLED) {
                if (effectInstance->flags & FX_INSTANCE_FLAG_HAS_UPDATED) {
                    void (*sceneFunc)(EffectInstance*) = effectInstance->shared->renderScene;
                    if (sceneFunc == NULL || (uintptr_t)sceneFunc < 0x100000000ULL) {
                        continue;
                    }
                    if (gGameStatusPtr->context != CONTEXT_WORLD) {
                        if (effectInstance->flags & FX_INSTANCE_FLAG_BATTLE) {
                            sceneFunc(effectInstance);
                        }
                    } else {
                        if (!(effectInstance->flags & FX_INSTANCE_FLAG_BATTLE)) {
                            sceneFunc(effectInstance);
                        }
                    }
                }
            }
            FrameInterpolation_RecordCloseChild();
        }
    }
}

void render_effects_UI(void) {
    s32 cond = true;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffectInstances); i++) {
        EffectInstance* effectInstance = gEffectInstances[i];

        if (effectInstance != nullptr) {
            if (effectInstance->flags & FX_INSTANCE_FLAG_ENABLED) {
                if (effectInstance->flags & FX_INSTANCE_FLAG_HAS_UPDATED) {
                    void (*renderUI)(EffectInstance* effect);

                    if (gGameStatusPtr->context != CONTEXT_WORLD && !(effectInstance->flags & FX_INSTANCE_FLAG_BATTLE)) {
                        continue;
                    }

                    if (gGameStatusPtr->context == CONTEXT_WORLD && effectInstance->flags & FX_INSTANCE_FLAG_BATTLE) {
                        continue;
                    }

                    renderUI = effectInstance->shared->renderUI;
                    if (renderUI != NULL && renderUI != stub_effect_delegate) {
                        FrameInterpolation_RecordOpenChild("effect_renderUI", TAG_EFFECT(i, effectInstance));
                        if (cond) {
                            Camera* camera = &gCameras[gCurrentCameraID];

                            gDPPipeSync(gMainGfxPos++);
                            gSPViewport(gMainGfxPos++, &camera->vp);
                            gSPClearGeometryMode(gMainGfxPos++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG |
                                                G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                                                G_SHADING_SMOOTH | G_CLIPPING | 0x40F9FA);
                            gSPSetGeometryMode(gMainGfxPos++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
                            gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE,
                                              camera->viewportStartX,
                                              camera->viewportStartY,
                                              camera->viewportStartX + camera->viewportW,
                                              camera->viewportStartY + camera->viewportH);
                            gSPClipRatio(gMainGfxPos++, FRUSTRATIO_2);

                            cond = false;
                            if (!(camera->flags & CAMERA_FLAG_ORTHO)) {
                                gSPPerspNormalize(gMainGfxPos++, camera->perspNorm);
                                gSPMatrix(gMainGfxPos++, &gDisplayContext->camPerspMatrix[gCurrentCameraID],
                                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
                            }
                        }

                        renderUI(effectInstance);
                        FrameInterpolation_RecordCloseChild();
                    }
                }
            }
        }
    }
}

EffectInstance* create_effect_instance(EffectBlueprint* effectBp) {
    EffectInstance* newEffectInst;
    EffectSharedData* sharedData;
    s32 i;

    // Search for an unused instance
    for (i = 0; i < ARRAY_COUNT(gEffectInstances); i++) {
        if (gEffectInstances[i] == nullptr) {
            break;
        }
    }

    ASSERT(i < ARRAY_COUNT(gEffectInstances));

    // Allocate space for the new instance
    gEffectInstances[i] = newEffectInst = general_heap_malloc(sizeof(*newEffectInst));
    ASSERT(newEffectInst != nullptr);

    sharedData = &gEffectSharedData[0];
    newEffectInst->effectID = effectBp->effectID;
    newEffectInst->flags = FX_INSTANCE_FLAG_ENABLED;

    // Look for a loaded effect of the proper index
    for (i = 0; i < ARRAY_COUNT(gEffectSharedData); i++) {
        if ((sharedData->flags & FX_SHARED_DATA_LOADED) && (sharedData->effectIndex == effectBp->effectID)) {
            break;
        }
        sharedData++;
    }

    // On N64, the TLB miss handler transparently loaded effect overlays on first access.
    // On the port all code is statically linked, so we lazy-load here instead.
    if (i >= ARRAY_COUNT(gEffectSharedData)) {
        load_effect(effectBp->effectID);
        sharedData = &gEffectSharedData[0];
        for (i = 0; i < ARRAY_COUNT(gEffectSharedData); i++) {
            if ((sharedData->flags & FX_SHARED_DATA_LOADED) && (sharedData->effectIndex == effectBp->effectID)) {
                break;
            }
            sharedData++;
        }
    }

    ASSERT(i < ARRAY_COUNT(gEffectSharedData));

    // If this is the first new instance of the effect, initialize the function pointers
    if (sharedData->instanceCounter == 0) {
        sharedData->update = effectBp->update;
        if (sharedData->update == nullptr) {
            sharedData->renderScene = stub_effect_delegate;
        }

        sharedData->renderScene = effectBp->renderScene;
        /// @bug? null check for renderUI instead of renderWorld
        if (sharedData->renderUI == nullptr) {
            sharedData->renderUI = stub_effect_delegate;
        }

        sharedData->renderUI = effectBp->renderUI;
        if (sharedData->renderUI == nullptr) {
            sharedData->renderUI = stub_effect_delegate;
        }
    }

    sharedData->instanceCounter++;
    newEffectInst->shared = sharedData;

    if (effectBp->init != nullptr) {
        effectBp->init(newEffectInst);
    }

    if (gGameStatusPtr->context != CONTEXT_WORLD) {
        newEffectInst->flags |= FX_INSTANCE_FLAG_BATTLE;
    }
    return newEffectInst;
}

void remove_effect(EffectInstance* effectInstance) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffectInstances); i++) {
        if (gEffectInstances[i] == effectInstance) {
            break;
        }
    }

    ASSERT(i < ARRAY_COUNT(gEffectInstances));

    if (effectInstance->data.any == nullptr) {
        general_heap_free(effectInstance);
        gEffectInstances[i] = nullptr;
    } else {
        general_heap_free(effectInstance->data.any);
        general_heap_free(effectInstance);
        gEffectInstances[i] = nullptr;
    }
}

void remove_all_effects(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffectInstances); i++) {
        EffectInstance* effect = gEffectInstances[i];

        if (effect != nullptr && effect->flags & FX_INSTANCE_FLAG_BATTLE) {
            if (effect->data.any != nullptr) {
                general_heap_free(effect->data.any);
            }
            general_heap_free(effect);
            gEffectInstances[i] = nullptr;
        }
    }
}

s32 load_effect(s32 effectIndex) {
    EffectTableEntry* effectEntry = &gEffectTable[effectIndex];
    EffectSharedData* sharedData;
    s32 i;

    // Look for a loaded effect matching the desired index
    for (i = 0, sharedData = &gEffectSharedData[0]; i < ARRAY_COUNT(gEffectSharedData); i++) {
        if (sharedData->flags & FX_SHARED_DATA_LOADED && sharedData->effectIndex == effectIndex) {
            break;
        }
        sharedData++;
    }

    // If an effect was found within the table, initialize it and return
    if (i < ARRAY_COUNT(gEffectSharedData)) {
        sharedData->effectIndex = effectIndex;
        sharedData->instanceCounter = 0;
        sharedData->flags = FX_SHARED_DATA_LOADED;
        return 1;
    }

    // If a loaded effect wasn't found, look for the first empty space
    for (i = 0, sharedData = &gEffectSharedData[0]; i < ARRAY_COUNT(gEffectSharedData); i++) {
        if (!(sharedData->flags & FX_SHARED_DATA_LOADED)) {
            break;
        }
        sharedData++;
    }

    // If no empty space was found, panic
    ASSERT(i < ARRAY_COUNT(gEffectSharedData));

    // Map space for the effect
    osMapTLB(i, OS_PM_4K, effectEntry->dmaDest, (s32)(gEffectDataBuffer[i]) & 0xFFFFFF, -1, -1);

    // Copy the effect into the newly mapped space which
    // in the port is already included in the effects' c files
    // dma_copy(effectEntry->dmaStart, effectEntry->dmaEnd, effectEntry->dmaDest);

    // Effect graphics are loaded on-demand via OTR asset system.
    // Set a sentinel so code knows graphics are available but not heap-allocated.
    if (effectEntry->graphicsDmaStart != nullptr) {
        sharedData->graphics = (void*)1;  // sentinel: DLs loaded via OTR
    }

    // Initialize the newly loaded effect data
    sharedData->effectIndex = effectIndex;
    sharedData->instanceCounter = 0;
    sharedData->flags = FX_SHARED_DATA_LOADED;
    return 1;
}
