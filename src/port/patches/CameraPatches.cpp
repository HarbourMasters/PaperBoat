#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

extern "C" {
extern Camera gCameras[4];
extern GameStatus* gGameStatusPtr;
}

static s32 cam_abs(s32 v) {
    return v < 0 ? -v : v;
}

static bool cam_view_is_widened(void) {
    return OTRGetRectDimensionFromLeftEdge(0) < 0;
}

static bool cam_has_fullscreen_viewport(s32 camID) {
    return camID == CAM_DEFAULT || camID == CAM_BATTLE ||
           gCameras[camID].viewportW >= SCREEN_WIDTH - 2 * SCREEN_INSET_X;
}

static bool cam_is_framed(s32 camID) {
    return (camID == CAM_DEFAULT || camID == CAM_BATTLE) && !cam_view_is_widened();
}

extern "C" void get_cam_frame_x(s32 camID, s32* left, s32* right) {
    Camera* camera = &gCameras[camID];
    s32 startX = 0;
    s32 endX = SCREEN_WIDTH;

    if (!cam_view_is_widened()) {
        startX = camera->viewportStartX;
        endX = camera->viewportStartX + cam_abs(camera->viewportW);
    }

    *left = OTRGetRectDimensionFromLeftEdge(startX);
    *right = OTRGetRectDimensionFromRightEdge(SCREEN_WIDTH - endX);
}

extern "C" void get_cam_scissor_x(s32 camID, s32* left, s32* right) {
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

static void cam_fit_viewport(s32 camID, Camera* camera) {
    s32 left;
    s32 right;
    s32 centerX;
    f32 zoom;
    f32 centerY;

    if (cam_is_framed(camID)) {
        get_cam_scissor_x(camID, &left, &right);
        zoom = (f32) (right - left) / cam_abs(camera->viewportW);
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

    centerX = OTRGetScissorCoordX(camera->viewportStartX + (camera->viewportW / 2));
    camera->vp.vp.vtrans[0] = 4 * centerX;
    camera->vpAlt.vp.vtrans[0] = gGameStatusPtr->altViewportOffset.x + 4 * centerX;
}

static f32 cam_get_display_aspect(s32 camID, Camera* camera) {
    f32 nativeW = cam_abs(camera->viewportW);

    if (cam_view_is_widened() && (camID == CAM_DEFAULT || camID == CAM_BATTLE)) {
        nativeW = SCREEN_WIDTH;
    }

    return nativeW / (f32) camera->viewportH;
}

static void RegisterCameraPatches_Init() {
    REGISTER_LISTENER(CameraFitViewport, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        auto* ev = (CameraFitViewport*) event;
        cam_fit_viewport(ev->camID, ev->camera);
    });

    REGISTER_LISTENER(CameraPerspective, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        auto* ev = (CameraPerspective*) event;

        if (ev->camera->viewportH != 0) {
            *ev->aspect = cam_get_display_aspect(ev->camID, ev->camera);
        }
    });
}

static RegisterShipInitFunc cameraPatchesInitFunc(RegisterCameraPatches_Init);
