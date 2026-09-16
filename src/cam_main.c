#include "common.h"
#include "camera.h"
#include "nu/nusys.h"
#include "hud_element.h"
#include "dx/profiling.h"
#include "port/Engine.h"

void render_models(void);
void execute_render_tasks(void);
void render_item_entities(void);

f32 CamLengthScale;
s16 gCurrentCamID;
u16* nuGfxCfb_ptr;
Gfx* gMainGfxPos;
DisplayContext* gDisplayContext;
Camera gCameras[4];

void update_cameras(void) {
    s32 sx, sy, sz;
    s32 camID;

    for (camID = 0; camID < ARRAY_COUNT(gCameras); camID++) {
        Camera* cam = &gCameras[camID];

        if (cam->flags == 0 || cam->flags & CAMERA_FLAG_DISABLED) {
            continue;
        }

        gCurrentCamID = camID;

        switch (cam->updateMode) {
            default:
            case CAM_UPDATE_MINIMAL:
                update_camera_minimal(cam);
                break;
            case CAM_UPDATE_INTERP_POS:
                update_camera_interp_pos(cam);
                break;
            case CAM_UPDATE_FROM_ZONE:
                update_camera_zone_interp(cam);
                break;
            case CAM_UPDATE_NO_INTERP:
                update_camera_no_interp(cam);
                break;
            case CAM_UPDATE_UNUSED_RADIAL:
                update_camera_unused_radial(cam);
                break;
            case CAM_UPDATE_UNUSED_CONFINED:
                update_camera_unused_confined(cam);
                break;
            case CAM_UPDATE_UNUSED_LEADING:
                update_camera_unused_leading(cam);
                break;
        }

        guLookAtReflectF(cam->mtxViewPlayer, &gDisplayContext->lookAt, cam->lookAt_eye.x, cam->lookAt_eye.y, cam->lookAt_eye.z, cam->lookAt_obj.x, cam->lookAt_obj.y, cam->lookAt_obj.z, 0, 1.0f, 0);

        if (!(cam->flags & CAMERA_FLAG_ORTHO)) {
            if (cam->flags & CAMERA_FLAG_LEAD_PLAYER) {
                create_camera_leadplayer_matrix(cam);
            }

            guPerspectiveF(cam->mtxPerspective, &cam->perspNorm, cam->vfov, (f32) cam->viewportW / (f32) cam->viewportH, (f32) cam->nearClip, (f32) cam->farClip, 1.0f);

            if (cam->flags & CAMERA_FLAG_SHAKING) {
                guMtxCatF(cam->mtxViewShaking, cam->mtxPerspective, cam->mtxPerspective);
            }

            if (cam->flags & CAMERA_FLAG_LEAD_PLAYER) {
                guMtxCatF(cam->mtxViewLeading, cam->mtxPerspective, cam->mtxPerspective);
            }

            guMtxCatF(cam->mtxViewPlayer, cam->mtxPerspective, cam->mtxPerspective);
        } else {
            f32 w = cam->viewportW;
            f32 h = cam->viewportH;

            guOrthoF(cam->mtxPerspective, -w * 0.5, w * 0.5, -h * 0.5, h * 0.5, -1000.0f, 1000.0f, 1.0f);
        }

        get_screen_coords(CAM_DEFAULT, cam->targetPos.x, cam->targetPos.y, cam->targetPos.z, &sx, &sy, &sz);
        cam->targetScreenCoords.x = sx;
        cam->targetScreenCoords.y = sy;
        cam->targetScreenCoords.z = sz;
    }

    gCurrentCamID = CAM_DEFAULT;
}

// Widescreen: true if this camera draws content that reaches the true screen edges, so it
// spans the widened width rather than the centered 4:3 box.
static b32 cam_has_fullscreen_viewport(s32 camID) {
    return camID == CAM_DEFAULT || camID == CAM_BATTLE
           || gCameras[camID].viewportW >= SCREEN_WIDTH - 2 * SCREEN_INSET_X;
}

// Widescreen: true when the view is wider than 4:3 and so reaches past the 4:3 box.
static b32 cam_view_is_widened(void) {
    return OTRGetRectDimensionFromLeftEdge(0) < 0;
}

void get_cam_frame_x(s32 camID, s32* left, s32* right) {
    Camera* camera = &gCameras[camID];
    s32 startX = 0;
    s32 endX = SCREEN_WIDTH;

    if (!cam_view_is_widened()) {
        startX = camera->viewportStartX;
        endX = camera->viewportStartX + abs(camera->viewportW);
    }

    *left = OTRGetRectDimensionFromLeftEdge(startX);
    *right = OTRGetRectDimensionFromRightEdge(SCREEN_WIDTH - endX);
}

// The world and battle cameras are drawn inside a black margin, but only at 4:3 or narrower:
// a wider view has no margin to draw.
static b32 cam_is_framed(s32 camID) {
    return (camID == CAM_DEFAULT || camID == CAM_BATTLE) && !cam_view_is_widened();
}

void get_cam_scissor_x(s32 camID, s32* left, s32* right) {
    Camera* camera = &gCameras[camID];

    if (cam_is_framed(camID)) {
        get_cam_frame_x(camID, left, right);
        *left = OTRGetScissorCoordX(*left);
        *right = OTRGetScissorCoordX(*right);
    } else if (cam_has_fullscreen_viewport(camID)) {
        *left = 0;
        *right = SCREEN_WIDTH;
    } else {
        *left = OTRGetScissorCoordX(camera->viewportStartX);
        *right = OTRGetScissorCoordX(camera->viewportStartX + camera->viewportW);
    }
}

// Widescreen: fit each camera's viewport to the screen.
static void cam_widescreen_fit_viewport(s32 camID, Camera* camera) {
    s32 left;
    s32 right;
    s32 centerX;
    f32 zoom;
    f32 centerY;

    if (cam_is_framed(camID)) {
        get_cam_scissor_x(camID, &left, &right);
        zoom = (f32) (right - left) / abs(camera->viewportW);
        centerY = SCREEN_HEIGHT / 2 + (camera->viewportStartY + camera->viewportH / 2 - SCREEN_HEIGHT / 2) * zoom;

        camera->vp.vp.vscale[0] = 2.0f * (right - left);
        camera->vp.vp.vscale[1] = 2.0f * camera->viewportH * zoom;
        camera->vp.vp.vtrans[0] = 4 * (left + (right - left) / 2);
        camera->vp.vp.vtrans[1] = 4.0f * centerY;
        camera->vpAlt.vp.vscale[0] = camera->vp.vp.vscale[0];
        camera->vpAlt.vp.vscale[1] = camera->vp.vp.vscale[1];
        camera->vpAlt.vp.vtrans[0] = gGameStatusPtr->altViewportOffset.x + camera->vp.vp.vtrans[0];
        camera->vpAlt.vp.vtrans[1] = gGameStatusPtr->altViewportOffset.y + camera->vp.vp.vtrans[1];
        return;
    }

    if (camID == CAM_DEFAULT || camID == CAM_BATTLE) {
        camera->vp.vp.vscale[0] = 2.0f * SCREEN_WIDTH;
        camera->vp.vp.vtrans[0] = 4 * (SCREEN_WIDTH / 2);
        camera->vpAlt.vp.vscale[0] = camera->vp.vp.vscale[0];
        camera->vpAlt.vp.vtrans[0] = gGameStatusPtr->altViewportOffset.x + camera->vp.vp.vtrans[0];
        return;
    }

    if (cam_has_fullscreen_viewport(camID)) {
        return;
    }

    // A sub-viewport camera's 3D render stays inside the 4:3 box, aligned with the 2D window
    // frame drawn around it.
    centerX = OTRGetScissorCoordX(camera->viewportStartX + (camera->viewportW / 2));
    camera->vp.vp.vtrans[0] = 4 * centerX;
    camera->vpAlt.vp.vtrans[0] = gGameStatusPtr->altViewportOffset.x + 4 * centerX;
}

void render_frame(s32 isSecondPass) {
    s32 firstCamID;
    s32 lastCamID;
    s32 camID;

    if (!isSecondPass) {
        gCurrentCamID = CAM_DEFAULT;
        mdl_update_transform_matrices();
    }

    // first pass:  loop uses camIDs from CAM_DEFAULT to CAM_HUD - 1
    // second pass: loop only uses CAM_HUD
    if (isSecondPass) {
        firstCamID = CAM_HUD;
        lastCamID = ARRAY_COUNT(gCameras);
    } else {
        firstCamID = CAM_DEFAULT;
        lastCamID = CAM_HUD;
    }

    for (camID = firstCamID; camID < lastCamID; camID++) {
        Camera* camera = &gCameras[camID];

        if (camera->flags == 0 || (camera->flags & (CAMERA_FLAG_NO_DRAW | CAMERA_FLAG_DISABLED))) {
            continue;
        }

        gCurrentCamID = camID;
        FrameInterpolation_RecordOpenChild("camera_render", TAG_CAMERA(camID, camera));

        cam_widescreen_fit_viewport(camID, camera);

        if (camera->fpDoPreRender != nullptr) {
            camera->fpDoPreRender(camera);
        } else {
            s32 ulx;
            s32 uly;
            s32 lrx;
            s32 lry;

            gSPViewport(gMainGfxPos++, &camera->vp);
            gSPClearGeometryMode(gMainGfxPos++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                    G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
            gSPTexture(gMainGfxPos++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
            gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
            gDPPipelineMode(gMainGfxPos++, G_PM_NPRIMITIVE);

            get_cam_scissor_x(camID, &ulx, &lrx);
            uly = camera->viewportStartY;
            lry = uly + camera->viewportH;

            if (ulx < 0) {
                ulx = 0;
            }
            if (uly < 0) {
                uly = 0;
            }
            if (lrx < 1) {
                lrx = 1;
            }
            if (lry < 1) {
                lry = 1;
            }

            if (ulx > SCREEN_WIDTH - 1) {
                ulx = SCREEN_WIDTH - 1;
            }
            if (uly > SCREEN_HEIGHT - 1) {
                uly = SCREEN_HEIGHT - 1;
            }
            if (lrx > SCREEN_WIDTH) {
                lrx = SCREEN_WIDTH;
            }
            if (lry > SCREEN_HEIGHT) {
                lry = SCREEN_HEIGHT;
            }

            gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, ulx, uly, lrx, lry);
            gDPSetTextureLOD(gMainGfxPos++, G_TL_TILE);
            gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
            gDPSetTextureDetail(gMainGfxPos++, G_TD_CLAMP);
            gDPSetTexturePersp(gMainGfxPos++, G_TP_PERSP);
            gDPSetTextureFilter(gMainGfxPos++, G_TF_BILERP);
            gDPSetTextureConvert(gMainGfxPos++, G_TC_FILT);
            gDPSetCombineMode(gMainGfxPos++, G_CC_SHADE, G_CC_SHADE);
            gDPSetCombineKey(gMainGfxPos++, G_CK_NONE);
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
            gDPSetRenderMode(gMainGfxPos++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
            gDPSetColorDither(gMainGfxPos++, G_CD_DISABLE);
            gSPClipRatio(gMainGfxPos++, FRUSTRATIO_2);
            gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH,
                                osVirtualToPhysical(nuGfxCfb_ptr));
            gDPPipeSync(gMainGfxPos++);

            if (!(camera->flags & CAMERA_FLAG_ORTHO)) {
                gSPPerspNormalize(gMainGfxPos++, camera->perspNorm);
            }

            FrameInterpolation_RecordOpenChild("camera_persp", 0);
            guMtxF2L(camera->mtxPerspective, &gDisplayContext->camPerspMatrix[gCurrentCamID]);
            FrameInterpolation_RecordCloseChild();
            gSPMatrix(gMainGfxPos++, &gDisplayContext->camPerspMatrix[gCurrentCamID], G_MTX_NOPUSH | G_MTX_LOAD |
                        G_MTX_PROJECTION);
        }

        camera->mtxBillboard = &gDisplayContext->matrixStack[gMatrixListPos++];
        FrameInterpolation_RecordOpenChild("camera_billboard", 0);
        guRotate(camera->mtxBillboard, -camera->curBoomYaw, 0.0f, 1.0f, 0.0f);
        FrameInterpolation_RecordCloseChild();

        camera->vpAlt.vp.vtrans[0] = camera->vp.vp.vtrans[0] + gGameStatusPtr->altViewportOffset.x;
        camera->vpAlt.vp.vtrans[1] = camera->vp.vp.vtrans[1] + gGameStatusPtr->altViewportOffset.y;

        if (!(camera->flags & CAMERA_FLAG_ORTHO)) {
            if (gCurrentCamID != CAM_HUD) {
                if (!(camera->flags & CAMERA_FLAG_RENDER_ENTITIES)) {
                    GFX_PROFILER_START(PROFILER_TIME_SUB_GFX_ENTITIES);
                    render_entities();
                    GFX_PROFILER_COMPLETE(PROFILER_TIME_SUB_GFX_ENTITIES);
                }
                if (!(camera->flags & CAMERA_FLAG_RENDER_MODELS)) {
                    GFX_PROFILER_START(PROFILER_TIME_SUB_GFX_MODELS);
                    #if DX_DEBUG_MENU
                    if (!dx_debug_should_hide_models()) {
                        render_models();
                    }
                    #else
                    render_models();
                    #endif
                    GFX_PROFILER_COMPLETE(PROFILER_TIME_SUB_GFX_MODELS);
                }
                GFX_PROFILER_START(PROFILER_TIME_SUB_GFX_PLAYER);
                render_player();
                GFX_PROFILER_SWITCH(PROFILER_TIME_SUB_GFX_PLAYER, PROFILER_TIME_SUB_GFX_NPCS);
                render_npcs();
                GFX_PROFILER_SWITCH(PROFILER_TIME_SUB_GFX_NPCS, PROFILER_TIME_SUB_GFX_WORKERS);
                render_workers_scene();
                GFX_PROFILER_SWITCH(PROFILER_TIME_SUB_GFX_WORKERS, PROFILER_TIME_SUB_GFX_EFFECTS);
                render_effects_scene();
                GFX_PROFILER_SWITCH(PROFILER_TIME_SUB_GFX_EFFECTS, PROFILER_TIME_SUB_GFX_RENDER_TASKS);
                execute_render_tasks();
                #if DX_DEBUG_MENU
                dx_debug_draw_collision();
                #endif
                GFX_PROFILER_SWITCH(PROFILER_TIME_SUB_GFX_RENDER_TASKS, PROFILER_TIME_SUB_GFX_HUD_ELEMENTS);
                FrameInterpolation_RecordOpenChild("cam_hud_elements", 0);
                render_transformed_hud_elements();
                FrameInterpolation_RecordCloseChild();
            } else {
                guOrthoF(camera->mtxPerspective, 0.0f, SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f, -1000.0f, 1000.0f, 1.0f);
                FrameInterpolation_RecordOpenChild("camera_persp_hud", 0);
                guMtxF2L(camera->mtxPerspective, &gDisplayContext->camPerspMatrix[gCurrentCamID]);
                FrameInterpolation_RecordCloseChild();
                gSPMatrix(gMainGfxPos++, &gDisplayContext->camPerspMatrix[gCurrentCamID], G_MTX_NOPUSH |
                            G_MTX_LOAD | G_MTX_PROJECTION);
                FrameInterpolation_RecordOpenChild("cam_hud_elements", 0);
                render_transformed_hud_elements();
                FrameInterpolation_RecordCloseChild();
                FrameInterpolation_RecordOpenChild("cam_item_entities", 0);
                render_item_entities();
                FrameInterpolation_RecordCloseChild();
            }
        } else {
            render_workers_scene();
            execute_render_tasks();
        }

        if (camera->fpDoPostRender != nullptr) {
            camera->fpDoPostRender(camera);
        }

        gDPPipeSync(gMainGfxPos++);
        gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH,
                            osVirtualToPhysical(nuGfxCfb_ptr));
        gDPPipeSync(gMainGfxPos++);

        FrameInterpolation_RecordCloseChild();
    }
}

void create_cameras(void) {
    CameraInitData camData;
    CameraInitData* camDataPtr = &camData;
    s32 i;

    CamLengthScale = 1.0f;

    for (i = 0; i < ARRAY_COUNT(gCameras); i++) {
        gCameras[i].flags = 0;
    }

    camDataPtr->flags = CAMERA_FLAG_DISABLED;
    camDataPtr->updateMode = CAM_UPDATE_MINIMAL;
    camDataPtr->viewWidth = 160;
    camDataPtr->viewHeight = 120;
    camDataPtr->viewStartX = 0;
    camDataPtr->viewStartY = 0;
    camDataPtr->nearClip = 8;
    camDataPtr->farClip = 16384;
    camDataPtr->vfov = 50;
    initialize_next_camera(camDataPtr);

    camDataPtr->flags = CAMERA_FLAG_DISABLED;
    camDataPtr->updateMode = CAM_UPDATE_MINIMAL;
    camDataPtr->viewWidth = 160;
    camDataPtr->viewHeight = 120;
    camDataPtr->viewStartX = 160;
    camDataPtr->viewStartY = 0;
    camDataPtr->nearClip = 8;
    camDataPtr->farClip = 16384;
    camDataPtr->vfov = 50;
    initialize_next_camera(camDataPtr);

    camDataPtr->flags = CAMERA_FLAG_DISABLED;
    camDataPtr->updateMode = CAM_UPDATE_MINIMAL;
    camDataPtr->viewWidth = 160;
    camDataPtr->viewHeight = 120;
    camDataPtr->viewStartX = 0;
    camDataPtr->viewStartY = 120;
    camDataPtr->nearClip = 8;
    camDataPtr->farClip = 16384;
    camDataPtr->vfov = 50;
    initialize_next_camera(camDataPtr);

    camDataPtr->flags = CAMERA_FLAG_DISABLED;
    camDataPtr->updateMode = CAM_UPDATE_MINIMAL;
    camDataPtr->viewWidth = 160;
    camDataPtr->viewHeight = 120;
    camDataPtr->viewStartX = 160;
    camDataPtr->viewStartY = 120;
    camDataPtr->nearClip = 8;
    camDataPtr->farClip = 16384;
    camDataPtr->vfov = 50;
    initialize_next_camera(camDataPtr);
}

Camera* initialize_next_camera(CameraInitData* initData) {
    Camera* camera;
    s32 camID;

    for (camID = 0; camID < ARRAY_COUNT(gCameras); camID++) {
        camera = &gCameras[camID];

        if (camera->flags == 0) {
            break;
        }
    }

    ASSERT(camID < ARRAY_COUNT(gCameras));

    camera->flags = initData->flags | CAMERA_FLAG_INITIALIZED | CAMERA_FLAG_LEAD_PLAYER;
    camera->moveFlags = 0;
    camera->lookAt_eye.x = 0;
    camera->lookAt_eye.y = 0;
    camera->lookAt_eye.z = 0;
    camera->lookAt_obj.x = 0;
    camera->lookAt_obj.y = 0;
    camera->lookAt_obj.z = -100.0f;
    camera->curYaw = 0.0f;
    camera->curBoomLength = 0;
    camera->targetOffsetY = 0;
    camera->curBoomYaw = 0.0f;
    camera->targetBoomYaw = 0.0f;
    camera->needsInit = true;
    camera->updateMode = initData->updateMode;
    camera->nearClip = initData->nearClip;
    camera->farClip = initData->farClip;
    camera->vfov = initData->vfov;
    camera->params.world.zoomPercent = 100;
    set_cam_viewport(camID, initData->viewStartX, initData->viewStartY, initData->viewWidth, initData->viewHeight);
    camera->bgColor[0] = 0;
    camera->bgColor[1] = 0;
    camera->bgColor[2] = 0;
    camera->lookAt_obj_target.x = 0;
    camera->lookAt_obj_target.y = 0;
    camera->lookAt_obj_target.z = 0;
    camera->targetPos.x = 0;
    camera->targetPos.y = 0;
    camera->targetPos.z = 0;
    camera->fpDoPreRender = nullptr;
    camera->fpDoPostRender = nullptr;
    camera->leadAmount = 0.0f;
    camera->targetLeadAmount = 0.0f;
    camera->leadInterpAlpha = 0.0f;
    camera->accumulatedStickLead = 0.0f;
    camera->increasingLeadInterp = false;
    camera->prevLeadPosX = 0.0f;
    camera->prevLeadPosZ = 0.0f;
    camera->leadConstrainDir = 0;
    camera->needsInitialConstrainDir = true;
    camera->prevLeadSettings = nullptr;
    camera->panActive = false;
    camera->useOverrideSettings = false;
    camera->leadAmtScale = 0.2f;
    camera->moveSpeed = 1.0f;
    return camera;
}

void set_cam_viewport(s16 id, s16 x, s16 y, s16 width, s16 height) {
    Camera* camera = &gCameras[id];

    camera->viewportW = width;
    camera->viewportH = height;
    camera->viewportStartX = x;
    camera->viewportStartY = y;

    camera->vp.vp.vscale[0] = 2.0f * camera->viewportW;
    camera->vp.vp.vscale[1] = 2.0f * camera->viewportH;
    camera->vp.vp.vscale[2] = 0x1FF;
    camera->vp.vp.vscale[3] = 0;

    camera->vp.vp.vtrans[0] = 4 * (s16) ((u16) camera->viewportStartX + (camera->viewportW / 2));
    camera->vp.vp.vtrans[1] = (s16) ((u16) camera->viewportStartY + (camera->viewportH / 2));
    camera->vp.vp.vtrans[1] = 4 * camera->vp.vp.vtrans[1];
    camera->vp.vp.vtrans[2] = 0x1FF;
    camera->vp.vp.vtrans[3] = 0;

    camera->vpAlt.vp.vscale[0] = 2.0f * camera->viewportW;
    camera->vpAlt.vp.vscale[1] = 2.0f * camera->viewportH;
    camera->vpAlt.vp.vscale[2] = 0x1FF;
    camera->vpAlt.vp.vscale[3] = 0;

    camera->vpAlt.vp.vtrans[0] = gGameStatusPtr->altViewportOffset.x + 4 * (s16) ((u16) camera->viewportStartX + (camera->viewportW / 2));
    camera->vpAlt.vp.vtrans[1] = gGameStatusPtr->altViewportOffset.y + 4 * (s16) ((u16) camera->viewportStartY + (camera->viewportH / 2));
    camera->vpAlt.vp.vtrans[2] = 0x200;
    camera->vpAlt.vp.vtrans[3] = 0;
}

void get_cam_viewport(s32 camID, u16* x, u16* y, u16* width, u16* height) {
    *width = gCameras[camID].viewportW;
    *height = gCameras[camID].viewportH;
    *x = gCameras[camID].viewportStartX;
    *y = gCameras[camID].viewportStartY;
}

void get_screen_coords(s32 camID, f32 x, f32 y, f32 z, s32* screenX, s32* screenY, s32* screenZ) {
    Camera* camera = &gCameras[camID];
    f32 tW;
    f32 tZ;
    f32 tY;
    f32 tX;

    transform_point(camera->mtxPerspective, x, y, z, 1.0f, &tX, &tY, &tZ, &tW);

    *screenZ = tZ + 5000.0f;
    if (*screenZ < 0) {
        *screenZ = 0;
    } else if (*screenZ > 10000) {
        *screenZ = 10000;
    }

    if (tW < 0.01 && tW > -0.01) {
        *screenX = 0;
        *screenY = 0;
        *screenZ = 0;
    } else {
        *screenX = camera->viewportStartX + (s32) ((1.0f + tX / tW) * camera->viewportW * 0.5f);
        *screenY = camera->viewportStartY + (s32) ((1.0f - tY / tW) * camera->viewportH * 0.5f);
    }
}

b32 is_outside_cam_viewport_bounds(s32 camID, s32 x, s32 y) {
    s32 startX = gCameras[camID].viewportStartX;
    s32 startY = gCameras[camID].viewportStartY;
    s32 endX = startX + gCameras[camID].viewportW;
    s32 endY = startY + gCameras[camID].viewportH;

    if (x < startX) {
        return true;
    } else if (x > endX) {
        return true;
    } else if (y < startY) {
        return true;
    } else if (y > endY) {
        return true;
    } else {
        return false;
    }
}

void get_cam_viewport_bounds(s32 camID, s32* x, s32* y, s32* width, s32* height) {
    *x = gCameras[camID].viewportStartX;
    *y = gCameras[camID].viewportStartY;
    *width = gCameras[camID].viewportStartX + gCameras[camID].viewportW;
    *height = gCameras[camID].viewportStartY + gCameras[camID].viewportH;
}
