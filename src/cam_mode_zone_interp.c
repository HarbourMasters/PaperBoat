#include "common.h"

BSS CameraRig CurrentCamRig;
BSS f32 D_800A08DC;
BSS f32 D_800A08E0;
BSS f32 D_800A08E4;
BSS f32 D_800A08E8;
BSS f32 D_800A08EC;

CameraControlSettings* test_ray_zone_aabb(f32 x, f32 y, f32 z) {
    f32 hitX, hitY, hitZ;
    f32 hitDepth = 32767.0f;
    f32 nx, ny, nz;
    s32 zoneID = test_ray_zones(x, y, z, 0.0f, -1.0f, 0.0f, &hitX, &hitY, &hitZ, &hitDepth, &nx, &ny, &nz);

    if (zoneID <= NO_COLLIDER) {
        return nullptr;
    }

    return gZoneCollisionData.colliderList[zoneID].camSettings;
}

enum CameraSettingsPtrType {
    CAMERA_SETTINGS_PTR_MINUS_2     = -2,
    CAMERA_SETTINGS_PTR_MINUS_1     = -1,
    CAMERA_SETTINGS_PTR_NULL        = 0,
};

void apply_fixed_orientation(CameraControlSettings* controller, CameraRig* configuration, f32 x, f32 y, f32 z)
{
    f32 Ax = controller->points.two.Ax;
    f32 Az = controller->points.two.Az;
    f32 Bx = controller->points.two.Bx;
    f32 Bz = controller->points.two.Bz;

    f32 ABx = (Bx - Ax);
    f32 ABz = (Bz - Az);

    if (controller->flag) {
        f32 perpdot = ABx * (z - Bz) - ABz * (x - Bx);
        f32 dist2 = SQ(ABx) + SQ(ABz);

        // only move camera along the line perpendicular to AB passing through B
        configuration->targetPos.x = Bx - ABz * (perpdot / dist2);
        configuration->targetPos.y = y;
        configuration->targetPos.z = Bz + ABx * (perpdot / dist2);
    } else {
        configuration->targetPos.x = x;
        configuration->targetPos.y = y;
        configuration->targetPos.z = z;
    }
}

void update_camera_from_controller(
    Camera* camera,
    CameraRig* prevRig, CameraControlSettings** prevSettingsPtr,
    CameraRig* newRig, CameraControlSettings** curSettingsPtr,
    f32 x1, f32 y1, f32 z1,
    f32 x2, f32 y2, f32 z2,
    f32* interpAlpha, b32 changingMap, b32 changingZone)
{
    CameraControlSettings* prevSettings;
    CameraControlSettings* curSettings;
    CameraRig* curRig;
    f32 dx, dz;
    f32 x, y, z;

    curRig = prevRig;
    curSettings = *prevSettingsPtr;
    x = x1;
    y = y1;
    z = z1;

    if ((s32)curSettings != CAMERA_SETTINGS_PTR_MINUS_2 && (s32)curSettings != CAMERA_SETTINGS_PTR_MINUS_1) {
        if (curSettings == CAMERA_SETTINGS_PTR_NULL) {
            curRig->targetPos.x = x;
            curRig->targetPos.y = y;
            curRig->targetPos.z = z;
        } else {
            switch (curSettings->type) {
                case CAM_CONTROL_FOLLOW_PLAYER:
                    curRig->targetPos.x = x;
                    curRig->targetPos.y = y;
                    curRig->targetPos.z = z;
                    break;
                case CAM_CONTROL_FIXED_POS_AND_ORIENTATION:
                    break;
                case CAM_CONTROL_FIXED_ORIENTATION:
                    if (curSettings->flag) {
                        f32 Ax = curSettings->points.two.Ax;
                        f32 Az = curSettings->points.two.Az;
                        f32 Bx = curSettings->points.two.Bx;
                        f32 Bz = curSettings->points.two.Bz;

                        f32 ABx = (Bx - Ax);
                        f32 ABz = (Bz - Az);

                        f32 perpdot = ABx * (z - Bz) - ABz * (x - Bx);
                        f32 dist2 = SQ(ABx) + SQ(ABz);

                        // only move camera along the line perpendicular to AB passing through B
                        curRig->targetPos.x = Bx - ABz * (perpdot / dist2);
                        curRig->targetPos.y = y;
                        curRig->targetPos.z = Bz + ABx * (perpdot / dist2);
                    } else {
                        curRig->targetPos.x = x;
                        curRig->targetPos.y = y;
                        curRig->targetPos.z = z;
                    }
                    break;
                case CAM_CONTROL_CONSTAIN_BETWEEN_POINTS:
                    {
                        f32 Ax = curSettings->points.two.Ax;
                        f32 Az = curSettings->points.two.Az;
                        f32 Bx = curSettings->points.two.Bx;
                        f32 Bz = curSettings->points.two.Bz;

                        f32 ABx = Bx - Ax;
                        f32 ABz = Bz - Az;

                        // project point onto line
                        f32 t = (ABx * (x - Ax) + ABz * (z - Az)) / (SQ(ABx) + SQ(ABz));
                        f32 Px = Ax + t * ABx;
                        f32 Pz = Az + t * ABz;

                        // vector giving orthogonal part (i.e., x = orthoX + Px)
                        f32 orthoX = x - Px;
                        f32 orthoZ = z - Pz;

                        // clamp to end points
                        if (t < 0.0f) {
                            Px = Ax;
                            Pz = Az;
                        } else if (t > 1.0f) {
                            Px = Bx;
                            Pz = Bz;
                        }
                        if (!curSettings->flag) {
                            Px += orthoX;
                            Pz += orthoZ;
                        }

                        curRig->targetPos.x = Px;
                        curRig->targetPos.y = y;
                        curRig->targetPos.z = Pz;
                    }
                    break;
                case CAM_CONTROL_LOOK_AT_POINT:
                    if (curSettings->flag) {
                        f32 Ax = curSettings->points.two.Ax;
                        f32 Az = curSettings->points.two.Az;
                        f32 Bx = curSettings->points.two.Bx;
                        f32 Bz = curSettings->points.two.Bz;

                        f32 ABx = Bx - Ax;
                        f32 ABz = Bz - Az;
                        f32 camRadius = sqrtf(SQ(ABx) + SQ(ABz));

                        // find radius of a circle containing the sample point centered on point A
                        f32 dx = x - Ax;
                        f32 dz = z - Az;
                        f32 curRadius = sqrtf(SQ(dx) + SQ(dz));

                        if (curRadius != 0.0f) {
                            // rescale the radius to equal the length of segment AB
                            curRig->targetPos.x = Ax + dx * (camRadius / curRadius);
                            curRig->targetPos.y = y;
                            curRig->targetPos.z = Az + dz * (camRadius / curRadius);
                        }
                    } else {
                        curRig->targetPos.x = x;
                        curRig->targetPos.y = y;
                        curRig->targetPos.z = z;
                    }
                    break;
                case CAM_CONTROL_CONSTRAIN_TO_LINE:
                case CAM_CONTROL_LOOK_AT_POINT_CONSTAIN_TO_LINE:
                    *prevSettingsPtr = (CameraControlSettings*) CAMERA_SETTINGS_PTR_MINUS_1;
                    break;
            }
        }
    }

    curRig = newRig;
    curSettings = *curSettingsPtr;
    x = x2;
    y = y2;
    z = z2;

    if (curSettings == nullptr) {
        curRig->targetPos.x = x;
        curRig->targetPos.y = y;
        curRig->targetPos.z = z;
    } else {
        switch (curSettings->type) {
            case CAM_CONTROL_FOLLOW_PLAYER:
                curRig->targetPos.x = x;
                curRig->targetPos.y = y;
                curRig->targetPos.z = z;
                break;
            case CAM_CONTROL_FIXED_POS_AND_ORIENTATION:
                {
                    f32 Ax = curSettings->points.two.Ax;
                    f32 Az = curSettings->points.two.Az;
                    f32 Bx = curSettings->points.two.Bx;
                    f32 By = curSettings->points.two.By;
                    f32 Bz = curSettings->points.two.Bz;

                    f32 ABx = Bx - Ax;
                    f32 ABz = Bz - Az;

                    curRig->boomLength = fabsf(curSettings->boomLength);
                    curRig->boomYaw = atan2(0.0f, 0.0f, ABx, ABz);
                    curRig->boomPitch = curSettings->boomPitch;
                    curRig->viewPitch = curSettings->viewPitch;
                    curRig->targetPos.x = Bx;
                    curRig->targetPos.y = By;
                    curRig->targetPos.z = Bz;
                    *prevSettingsPtr = (CameraControlSettings*) CAMERA_SETTINGS_PTR_MINUS_2;
                }
                break;
            case CAM_CONTROL_FIXED_ORIENTATION:
                dx = curSettings->points.two.Bx - curSettings->points.two.Ax;
                dz = curSettings->points.two.Bz - curSettings->points.two.Az;
                curRig->boomLength = fabsf(curSettings->boomLength);
                curRig->boomYaw = atan2(0.0f, 0.0f, dx, dz);
                curRig->boomPitch = curSettings->boomPitch;
                curRig->viewPitch = curSettings->viewPitch;

                if (curSettings->flag) {
                    f32 Ax = curSettings->points.two.Ax;
                    f32 Az = curSettings->points.two.Az;
                    f32 Bx = curSettings->points.two.Bx;
                    f32 Bz = curSettings->points.two.Bz;

                    f32 ABx = Bx - Ax;
                    f32 ABz = Bz - Az;

                    f32 perpdot = ABx * (z - Bz) - ABz * (x - Bx);
                    f32 dist2 = SQ(ABx) + SQ(ABz);

                    // only move camera along the line perpendicular to AB passing through B
                    curRig->targetPos.x = Bx - ABz * (perpdot / dist2);
                    curRig->targetPos.y = y;
                    curRig->targetPos.z = Bz + ABx * (perpdot / dist2);
                } else {
                    curRig->targetPos.x = x;
                    curRig->targetPos.y = y;
                    curRig->targetPos.z = z;
                }

                if (changingZone) {
                    if (*interpAlpha != 1.0f) {
                        prevSettings = *prevSettingsPtr;
                        if (((s32)prevSettings != CAMERA_SETTINGS_PTR_MINUS_2
                                && (s32)prevSettings != CAMERA_SETTINGS_PTR_MINUS_1
                                && (s32)prevSettings != CAMERA_SETTINGS_PTR_NULL)
                            && prevSettings->type == curSettings->type
                            && prevSettings->boomLength == curSettings->boomLength
                            && prevSettings->boomPitch == curSettings->boomPitch
                            && prevSettings->viewPitch == curSettings->viewPitch
                            && prevSettings->flag != curSettings->flag
                        ) {
                            *interpAlpha = 1.0f;
                        }
                    }
                }
                break;
            case CAM_CONTROL_CONSTAIN_BETWEEN_POINTS:
                {
                    f32 Ax = curSettings->points.two.Ax;
                    f32 Az = curSettings->points.two.Az;
                    f32 Bx = curSettings->points.two.Bx;
                    f32 Bz = curSettings->points.two.Bz;

                    f32 ABx = Bx - Ax;
                    f32 ABz = Bz - Az;

                    curRig->boomLength = fabsf(curSettings->boomLength);
                    curRig->boomYaw = atan2(0.0f, 0.0f, ABz, -ABx);
                    curRig->boomPitch = curSettings->boomPitch;
                    curRig->viewPitch = curSettings->viewPitch;

                    // project point onto line
                    f32 t = (ABx * (x - Ax) + ABz * (z - Az)) / (SQ(ABx) + SQ(ABz));
                    f32 Px = Ax + t * ABx;
			        f32 Pz = Az + t * ABz;

                    // vector giving orthogonal part (i.e., x = orthoX + Px)
                    f32 orthoX = x - Px;
                    f32 orthoZ = z - Pz;

                    // clamp to end points
                    if (t < 0.0f) {
                        Px = Ax;
                        Pz = Az;
                    } else if (t > 1.0f) {
                        Px = Bx;
                        Pz = Bz;
                    }
                    if (!curSettings->flag) {
                        Px += orthoX;
                        Pz += orthoZ;
                    }

                    curRig->targetPos.x = Px;
                    curRig->targetPos.y = y;
                    curRig->targetPos.z = Pz;

                    if (changingZone) {
                        if (*interpAlpha != 1.0f) {
                            prevSettings = *prevSettingsPtr;
                            if (((s32)prevSettings != CAMERA_SETTINGS_PTR_MINUS_2
                                    && (s32)prevSettings != CAMERA_SETTINGS_PTR_MINUS_1
                                    && (s32)prevSettings != CAMERA_SETTINGS_PTR_NULL)
                                && (prevSettings->type == curSettings->type)
                                && (prevSettings->boomLength == curSettings->boomLength)
                                && (prevSettings->boomPitch == curSettings->boomPitch)
                                && (prevSettings->viewPitch == curSettings->viewPitch)
                                && (prevSettings->flag != curSettings->flag)
                            ) {
                                *interpAlpha = 1.0f;
                            }
                        }
                    }
                }
                break;
            case CAM_CONTROL_LOOK_AT_POINT:
                {
                    f32 Ax = curSettings->points.two.Ax;
                    f32 Az = curSettings->points.two.Az;
                    f32 Bx = curSettings->points.two.Bx;
                    f32 Bz = curSettings->points.two.Bz;

                    f32 ABx = Bx - Ax;
                    f32 ABz = Bz - Az;
                    f32 camRadius = sqrtf(SQ(ABx) + SQ(ABz));
                    f32 curRadius, dx, dz;

                    if (curSettings->boomLength < 0.0f) {
                        // negative boom length means look *away* from point
                        dx = x - Ax;
                        dz = z - Az;
                        curRig->boomLength = -curSettings->boomLength;
                    } else {
                        dx = Ax - x;
                        dz = Az - z;
                        curRig->boomLength = curSettings->boomLength;
                    }
                    curRig->boomYaw = atan2(0.0f, 0.0f, dx, dz);
                    curRig->boomPitch = curSettings->boomPitch;
                    curRig->viewPitch = curSettings->viewPitch;

                    if (curSettings->flag) {
                        // find radius of a circle containing the sample point centered on point A
                        dx = x - Ax;
                        dz = z - Az;
                        curRadius = sqrtf(SQ(dx) + SQ(dz));

                        if (curRadius != 0.0f) {
                            // rescale the radius to equal the length of segment AB
                            curRig->targetPos.x = Ax + dx * (camRadius / curRadius);
                            curRig->targetPos.y = y;
                            curRig->targetPos.z = Az + dz * (camRadius / curRadius);
                        }
                    } else {
                        curRig->targetPos.x = x;
                        curRig->targetPos.y = y;
                        curRig->targetPos.z = z;
                    }

                    if (changingZone) {
                        if (*interpAlpha != 1.0f) {
                            prevSettings = *prevSettingsPtr;
                            if (((s32)prevSettings != CAMERA_SETTINGS_PTR_MINUS_2
                                    && (s32)prevSettings != CAMERA_SETTINGS_PTR_MINUS_1
                                    && (s32)prevSettings != CAMERA_SETTINGS_PTR_NULL)
                                && (prevSettings->type == curSettings->type)
                                && (prevSettings->boomLength == curSettings->boomLength)
                                && (prevSettings->boomPitch == curSettings->boomPitch)
                                && (prevSettings->viewPitch == curSettings->viewPitch)
                                && (prevSettings->flag != curSettings->flag)
                                && (prevSettings->points.two.Ax == curSettings->points.two.Ax)
                                && (prevSettings->points.two.Az == curSettings->points.two.Az)
                            ) {
                                *interpAlpha = 1.0f;
                            }
                        }
                    }
                }
                break;
            case CAM_CONTROL_CONSTRAIN_TO_LINE:
                {
                    const f32 Ax = curSettings->points.three.Ax;
                    const f32 Az = curSettings->points.three.Az;
                    const f32 Bx = curSettings->points.three.Bx;
                    const f32 Bz = curSettings->points.three.Bz;
                    const f32 Cx = curSettings->points.three.Cx;
                    const f32 Cz = curSettings->points.three.Cz;

                    if (!curSettings->flag) {
                        f32 Tx, Tz;
                        f32 BAx, BAz;
                        f32 BCx, BCz;

                        if (Ax == Bx && Az == Bz) {
                            BAx = Bx - Cx;
                            BAz = Bz - Cz;
                        } else {
                            BAx = Bx - Ax;
                            BAz = Bz - Az;
                        }

                        BCx = Bx - Cx;
                        BCz = Bz - Cz;

                        // move the target from the sample point along the direction perpendicular
                        // to BA until it meets line BC
                        if (BCx == 0.0f) {
                            f32 Q = BAz + BCx * BAx / BCz;
                            f32 V = (x - Bx) + (Bz - z) * BCx / BCz;

                            Tx = x - BAz * V / Q;
                            Tz = z + BAx * V / Q;
                        } else {
                            f32 Q = -BAx - BAz * BCz / BCx;
                            f32 V = (z - Bz) + (Bx - x) * BCz / BCx;

                            Tx = x - BAz * V / Q;
                            Tz = z + BAx * V / Q;
                        }

                        curRig->targetPos.x = Tx;
                        curRig->targetPos.y = y;
                        curRig->targetPos.z = Tz;

                        if (changingMap) {
                            dx = Bx - Ax;
                            dz = Bz - Az;
                            curRig->boomLength = fabsf(curSettings->boomLength);
                            curRig->boomYaw = atan2(0.0f, 0.0f, dx, dz);
                            curRig->boomPitch = curSettings->boomPitch;
                            curRig->viewPitch = curSettings->viewPitch;
                        }
                    } else {
                        if (changingMap) {
                            dx = Bx - Ax;
                            dz = Bz - Az;
                            curRig->boomLength = fabsf(curSettings->boomLength);
                            curRig->boomYaw = atan2(0.0f, 0.0f, dx, dz);
                            curRig->boomPitch = curSettings->boomPitch;
                            curRig->viewPitch = curSettings->viewPitch;
                            curRig->targetPos.x = Bx;
                            curRig->targetPos.z = Bz;
                        } else if (changingZone) {
                            curRig->targetPos.x = prevRig->targetPos.x;
                            curRig->targetPos.z = prevRig->targetPos.z;
                        }

                        // y always tracks the sample point, even while x and z stay fixed
                        curRig->targetPos.y = y;
                    }
                    *prevSettingsPtr = (CameraControlSettings*) CAMERA_SETTINGS_PTR_MINUS_1;
                }
                break;
            case CAM_CONTROL_LOOK_AT_POINT_CONSTAIN_TO_LINE:
                {
                    // camera position is projected onto a line defined by BC, while the yaw faces point A
                    f32 Ax = curSettings->points.three.Ax;
                    f32 Az = curSettings->points.three.Az;
                    f32 Bx = curSettings->points.three.Bx;
                    f32 Bz = curSettings->points.three.Bz;
                    f32 Cx = curSettings->points.three.Cx;
                    f32 Cz = curSettings->points.three.Cz;

                    if (!curSettings->flag) {
                        f32 CBx = Bx - Cx;
                        f32 CBz = Bz - Cz;
                        f32 dist2 = SQ(CBx) + SQ(CBz);
                        dist2 = (CBx * (x - Cx) + CBz * (z - Cz)) / dist2;
                        f32 Px = Cx + dist2 * CBx;
                        f32 Pz = Cz + dist2 * CBz;

                        curRig->targetPos.x = Px;
                        curRig->targetPos.y = y;
                        curRig->targetPos.z = Pz;

                        if (curSettings->boomLength < 0.0f) {
                            dx = Px - Ax;
                            dz = Pz - Az;
                            curRig->boomLength = -curSettings->boomLength;
                        } else {
                            dx = Ax - Px;
                            dz = Az - Pz;
                            curRig->boomLength = curSettings->boomLength;
                        }
                        curRig->boomYaw = atan2(0.0f, 0.0f, dx, dz);
                        curRig->boomPitch = curSettings->boomPitch;
                        curRig->viewPitch = curSettings->viewPitch;
                    } else {
                        if (changingMap) {
                            if (curSettings->boomLength < 0.0f) {
                                dx = Bx - Ax;
                                dz = Bz - Az;
                                curRig->boomLength = -curSettings->boomLength;
                            } else {
                                dx = Ax - Bx;
                                dz = Az - Bz;
                                curRig->boomLength = curSettings->boomLength;
                            }
                            curRig->boomYaw = atan2(0.0f, 0.0f, dx, dz);
                            curRig->boomPitch = curSettings->boomPitch;
                            curRig->viewPitch = curSettings->viewPitch;
                            curRig->targetPos.x = Bx;
                            curRig->targetPos.z = Bz;
                        } else if (changingZone) {
                            curRig->targetPos.x = Bx;
                            curRig->targetPos.z = Bz;
                        }

                        // y always tracks the sample point, even while x and z stay fixed
                        curRig->targetPos.y = y;
                    }
                    *prevSettingsPtr = (CameraControlSettings*) CAMERA_SETTINGS_PTR_MINUS_1;
                }
                break;
        }

        if (changingZone
            && ((curSettings->type == CAM_CONTROL_LOOK_AT_POINT_CONSTAIN_TO_LINE) || (prevRig->boomYaw != newRig->boomYaw))
            && (fabsf(prevRig->boomYaw - newRig->boomYaw) < 3.0f)
            && (fabsf(prevRig->boomLength - newRig->boomLength) < 10.0f)
            && (fabsf(prevRig->boomPitch - newRig->boomPitch) < 1.0f)
            && (fabsf(prevRig->viewPitch - newRig->viewPitch) < 1.0f)
            && (fabsf(prevRig->targetPos.x - newRig->targetPos.x) < 10.0f)
            && (fabsf(prevRig->targetPos.y - newRig->targetPos.y) < 10.0f)
            && (fabsf(prevRig->targetPos.z - newRig->targetPos.z) < 10.0f)
        ) {
            *interpAlpha = 1.0f;
        }
    }

    if (*prevSettingsPtr == (CameraControlSettings*) CAMERA_SETTINGS_PTR_MINUS_1) {
        if (changingZone) {
            D_800A08E4 = prevRig->targetPos.x - newRig->targetPos.x;
            D_800A08E8 = prevRig->targetPos.y - newRig->targetPos.y;
            D_800A08EC = prevRig->targetPos.z - newRig->targetPos.z;
        }
        prevRig->targetPos.x = newRig->targetPos.x + D_800A08E4;
        prevRig->targetPos.y = newRig->targetPos.y + D_800A08E8;
        prevRig->targetPos.z = newRig->targetPos.z + D_800A08EC;
    }
}

void interp_camera_y_position(Camera* camera, f32 targetY) {
    if (camera->moveFlags & CAMERA_MOVE_IGNORE_PLAYER_Y) {
        camera->yinterpAlpha = 0.0f;
    } else if (camera->yinterpGoal != targetY) {
        camera->yinterpGoal = targetY;
        camera->yinterpAlpha = 0.0f;
    }

    // always follow player moving down with no interp
    if (targetY < camera->yinterpGoal && targetY <= camera->yinterpCur) {
        camera->yinterpGoal = targetY;
        camera->yinterpAlpha = 1.0f;
    }

    camera->yinterpAlpha += (1.01f - camera->yinterpAlpha) / camera->yinterpRate;

    if (camera->yinterpAlpha > 1.0f) {
        camera->yinterpAlpha = 1.0f;
    }

    if (camera->moveFlags & CAMERA_MOVE_ACCEL_INTERP_Y) {
        camera->yinterpAlpha += 0.3f;
        if (camera->yinterpAlpha >= 1.0f) {
            camera->yinterpAlpha = 1.0f;
        }
    }

    if (!(camera->moveFlags & CAMERA_MOVE_NO_INTERP_Y)) {
        camera->yinterpCur += (camera->yinterpGoal - camera->yinterpCur) * camera->yinterpAlpha;
    }
}

// determine the largest parameter difference between prevRig and nextRig
f32 get_maximum_interp_delta(Camera* camera) {
    f32 maxDelta;
    f32 curDelta;
    f32 deltaX, deltaY, deltaZ;

    curDelta = fabsf(camera->prevRig.boomYaw - camera->nextRig.boomYaw);
    if (curDelta > 180.0f) {
        curDelta = 360.0f - curDelta;
    }
    maxDelta = curDelta;

    curDelta = fabsf(camera->prevRig.boomPitch - camera->nextRig.boomPitch);
    if (curDelta > 180.0f) {
        curDelta = 360.0f - curDelta;
    }
    if (maxDelta < curDelta) {
        maxDelta = curDelta;
    }

    curDelta = fabsf(camera->prevRig.viewPitch - camera->nextRig.viewPitch);
    if (curDelta > 180.0f) {
        curDelta = 360.0f - curDelta;
    }
    if (maxDelta < curDelta) {
        maxDelta = curDelta;
    }

    curDelta = fabsf(camera->prevRig.boomLength - camera->nextRig.boomLength);
    if (maxDelta < curDelta) {
        maxDelta = curDelta;
    }

    deltaX = camera->prevRig.targetPos.x - camera->nextRig.targetPos.x;
    deltaY = camera->prevRig.targetPos.y - camera->nextRig.targetPos.y;
    deltaZ = camera->prevRig.targetPos.z - camera->nextRig.targetPos.z;
    curDelta = SQ(deltaX) + SQ(deltaY) + SQ(deltaZ);
    if (curDelta != 0.0f) {
        // reduce this delta to avoid over-weighting changes in target pos
        curDelta = sqrtf(curDelta) * 0.2;
    }
    if (maxDelta < curDelta) {
        maxDelta = curDelta;
    }

    // clamp maxDelta to the interval [20.0, 90.0]
    if (maxDelta > 90.0f) {
        maxDelta = 90.0f;
    }
    if (maxDelta < 20.0f) {
        maxDelta = 20.0f;
    }

    return maxDelta;
}

void set_camera_from_rig(Camera* camera, CameraRig* rig) {
    camera->curBoomLength = CurrentCamRig.boomLength;
    camera->curBoomYaw = CurrentCamRig.boomYaw + D_800A08E0;;
    camera->curYaw = camera->curBoomYaw;
    camera->targetOffsetY = 0.0f;

    f32 sinBoomYaw = sin_deg(camera->curBoomYaw);
    f32 cosBoomYaw = cos_deg(camera->curBoomYaw);
    f32 cosBoomPitch = cos_deg(CurrentCamRig.boomPitch + D_800A08DC);
    f32 sinBoomPitch = sin_deg(CurrentCamRig.boomPitch + D_800A08DC);

    if (!(camera->moveFlags & CAMERA_MOVE_NO_INTERP_Y)) {
        camera->lookAt_eye.y = CurrentCamRig.targetPos.y + (CurrentCamRig.boomLength * sinBoomPitch);
    }

    camera->lookAt_eye.x = CurrentCamRig.targetPos.x - (sinBoomYaw * CurrentCamRig.boomLength * cosBoomPitch);
    camera->lookAt_eye.z = CurrentCamRig.targetPos.z + (cosBoomYaw * CurrentCamRig.boomLength * cosBoomPitch);
    f32 cosViewPitch = cos_deg(CurrentCamRig.viewPitch);
    f32 sinViewPitch = sin_deg(CurrentCamRig.viewPitch);

    f32 dx = CurrentCamRig.targetPos.x - camera->lookAt_eye.x;
    f32 dy = CurrentCamRig.targetPos.y - camera->lookAt_eye.y;
    f32 dz = CurrentCamRig.targetPos.z - camera->lookAt_eye.z;
    f32 dr = SQ(dx) + SQ(dz);
    if (dr != 0.0f) {
        dr = sqrtf(dr);
    }
    if (!(camera->moveFlags & CAMERA_MOVE_NO_INTERP_Y)) {
        camera->lookAt_obj.y = camera->lookAt_eye.y + (dy * cosViewPitch) - (dr * sinViewPitch);
    }
    f32 projectedRadius = (dy * sinViewPitch) + (dr * cosViewPitch);
    camera->lookAt_obj.x = camera->lookAt_eye.x + (sinBoomYaw * projectedRadius);
    camera->lookAt_obj.z = camera->lookAt_eye.z - (cosBoomYaw * projectedRadius);

    camera->lookAt_yaw = -CurrentCamRig.boomYaw;
    camera->lookAt_pitch = -CurrentCamRig.boomPitch - CurrentCamRig.viewPitch;

    camera->lookAt_obj_target.x = camera->lookAt_obj.x;
    camera->lookAt_obj_target.y = camera->lookAt_obj.y;
    camera->lookAt_obj_target.z = camera->lookAt_obj.z;
}

// implements CAM_UPDATE_FROM_ZONE
// this camera samples camera zones below its targetPos and derives control parameters from their settings,
// interpolating its control parameters when changing zones. these control parameters determine the camera
// position and orientation just like other camera modes.
// note that this code does NOT directly reference the player position in any manner, it is only concerned
// with the camera's targetPos, which must be assigned elsewhere.
// this is the camera used during world gameplay
//
// control parameters:
// zoomPercent -- boom length is adjusted by this factor, with 100 being no change, 50 being half distance, etc
void update_camera_zone_interp(Camera* camera) {
    CameraControlSettings* curSettings;
    CameraControlSettings* nextSettings;
    f32 targetX;
    f32 targetY;
    f32 targetZ;
    f32 maxDelta;
    b32 allParamsMatch;
    s32 changingZone;

    targetX = camera->targetPos.x;
    targetY = camera->targetPos.y;
    targetZ = camera->targetPos.z;
    changingZone = false;

    if (camera->needsReinit) {
        camera->curSettings = nullptr;
        camera->prevSettings = nullptr;
        camera->linearInterp = 0.0f;
        camera->yinterpAlpha = 1.0f;
        camera->yinterpGoal = 0.0f;
        camera->yinterpCur = targetY;

        camera->interpEasingParameter = 0.0f;
        camera->interpAlpha = 1.0f;
        camera->linearInterpRate = 1.0f;

        camera->prevTargetPos.x = 0.0f;
        camera->prevTargetPos.y = 0.0f;
        camera->prevTargetPos.z = 0.0f;
        camera->prevUseOverride = false;
        camera->prevPrevUseOverride = false;
        D_800A08DC = 0.0f;
        D_800A08E0 = 0.0f;
    }

    // determine current y-position
    interp_camera_y_position(camera, targetY);

    if (camera->panActive
        || camera->prevTargetPos.x != targetX
        || camera->prevTargetPos.y != targetY
        || camera->prevTargetPos.z != targetZ
        || camera->needsReinit
    ) {
        if (camera->useOverrideSettings) {
            nextSettings = &camera->overrideSettings;
        } else {
            nextSettings = test_ray_zone_aabb(targetX, targetY + 10.0f, targetZ);
        }

        allParamsMatch = false;
        curSettings = camera->curSettings;
        if (nextSettings != nullptr
            && curSettings != nullptr
            && nextSettings->type == curSettings->type
            && nextSettings->flag == curSettings->flag
            && nextSettings->boomLength == curSettings->boomLength
            && nextSettings->boomPitch == curSettings->boomPitch
            && nextSettings->viewPitch == curSettings->viewPitch
        ) {
            switch (nextSettings->type) {
                case CAM_CONTROL_FIXED_ORIENTATION:
                    if (nextSettings->points.two.Ax == curSettings->points.two.Ax
                        && nextSettings->points.two.Az == curSettings->points.two.Az
                        && nextSettings->points.two.Bx == curSettings->points.two.Bx
                        && nextSettings->points.two.Bz == curSettings->points.two.Bz
                    ) {
                        allParamsMatch = true;
                    }
                    break;
                case CAM_CONTROL_LOOK_AT_POINT:
                    if (nextSettings->flag) {
                        if (nextSettings->points.two.Ax == curSettings->points.two.Ax
                            && nextSettings->points.two.Az == curSettings->points.two.Az
                            && nextSettings->points.two.Bx == curSettings->points.two.Bx
                            && nextSettings->points.two.Bz == curSettings->points.two.Bz
                        ) {
                            allParamsMatch = true;
                        }
                    } else {
                        if (nextSettings->points.two.Ax == curSettings->points.two.Ax
                            && nextSettings->points.two.Az == curSettings->points.two.Az
                        ) {
                            allParamsMatch = true;
                        }
                    }
                    break;
                default:
                    if (nextSettings->points.two.Ax == curSettings->points.two.Ax
                        && nextSettings->points.two.Az == curSettings->points.two.Az
                        && nextSettings->points.two.Ay == curSettings->points.two.Ay
                        && nextSettings->points.two.By == curSettings->points.two.By
                        && nextSettings->points.two.Bx == curSettings->points.two.Bx
                        && nextSettings->points.two.Bz == curSettings->points.two.Bz
                    ) {
                        allParamsMatch = true;
                    }
                    break;
            }
        }

        if (camera->panActive || (nextSettings != curSettings && !allParamsMatch)) {
            if (camera->interpAlpha == 1.0f) {
                camera->prevSettings = camera->curSettings;
            } else {
                camera->prevSettings = (CameraControlSettings*) CAMERA_SETTINGS_PTR_MINUS_1;
            }
            camera->panActive = false;
            changingZone = true;
            camera->prevRig = CurrentCamRig;
            camera->curSettings = nextSettings;

            camera->interpAlpha = 0.0f;
            camera->linearInterp = 0.0f;
            camera->linearInterpRate = camera->moveSpeed;

            camera->prevPrevUseOverride = camera->prevUseOverride;
            camera->prevUseOverride = camera->useOverrideSettings;

            camera->prevPrevMovePos.x = camera->prevMovePos.x;
            camera->prevPrevMovePos.y = camera->prevMovePos.y;
            camera->prevPrevMovePos.z = camera->prevMovePos.z;

            camera->prevMovePos.x = camera->movePos.x;
            camera->prevMovePos.y = camera->movePos.y;
            camera->prevMovePos.z = camera->movePos.z;
        }
    }

    camera->prevTargetPos.x = targetX;
    camera->prevTargetPos.y = targetY;
    camera->prevTargetPos.z = targetZ;

    f32 posX;
    f32 posY;
    f32 posZ;
    f32 tX;
    f32 tY;
    f32 tZ;

    if (camera->prevPrevUseOverride) {
        posX = camera->prevPrevMovePos.x;
        posY = camera->prevPrevMovePos.y;
        posZ = camera->prevPrevMovePos.z;
    } else {
        posX = targetX;
        posY = camera->yinterpCur;
        posZ = targetZ;
    }

    if (camera->prevUseOverride) {
        tX = camera->prevMovePos.x;
        tY = camera->prevMovePos.y;
        tZ = camera->prevMovePos.z;
        camera->yinterpCur = tY;
    } else {
        tX = targetX;
        tY = camera->yinterpCur;
        tZ = targetZ;
    }

    update_camera_from_controller(camera,
        &camera->prevRig, &camera->prevSettings, &camera->nextRig, &camera->curSettings,
        posX, posY, posZ, tX, tY, tZ,
        &camera->interpAlpha, camera->needsReinit, changingZone);

    if (camera->needsReinit) {
        camera->prevRig = camera->nextRig;
        camera->needsReinit = false;
        camera->interpAlpha = 1.0f;
    }

    if (camera->prevRig.boomYaw - camera->nextRig.boomYaw > 180.0f) {
        camera->prevRig.boomYaw -= 360.0f;
    }
    if (camera->prevRig.boomYaw - camera->nextRig.boomYaw < -180.0f) {
        camera->prevRig.boomYaw += 360.0f;
    }

    maxDelta = get_maximum_interp_delta(camera);

    camera->linearInterp += (1.0f / maxDelta) * camera->linearInterpRate;
    if (camera->linearInterp > 1.0f) {
        camera->linearInterp = 1.0f;
    }

    if (camera->interpAlpha < 1.0f) {
        // this phi parameter controls whether the easing will be cosine in/out or quadratic out
        // when phi = 0, this expression reduces to cos(PI_D * alpha) and the easing is cosine in and out
        // when phi = 1, gamma 'blows up' as the denominator goes to zero, so this value is not valid.
        // however, as phi approaches 1, the formula for interpAlpha approaches 1 - SQ(1 - alpha)
        // intermediate values smoothly produce intermediate easing functions
        // in practice, only 0 and 0.5 are ever used, and 0.5 is extremely rare
        f32 phi = camera->interpEasingParameter;
        f32 plusCos = (1.0f + cos_rad(PI_D * phi)) * 0.5f;
        f32 minusCos = (1.0f - cos_rad(PI_D * phi)) * 0.5f;
        f32 alpha = camera->linearInterp;
        f32 beta = cos_rad(PI_D * (alpha * (1.0f - phi) + phi));
        f32 gamma = (beta + minusCos) / plusCos;
        // the range of gamma is [1,-1] so we must remap it to [0,1] before assigning interpAlpha
        camera->interpAlpha = (1.0f - gamma) * 0.5001;
    }

    if (camera->interpAlpha >= 1.0f) {
        camera->interpAlpha = 1.0f;
        camera->linearInterp = 0.0f;
    }

    // interpolate rig parameters between prevRig and nextRig, storing them in CurrentCamRig

    #define CAM_INTERP(field) CurrentCamRig.field = \
        (camera->prevRig.field  * (1.0f - camera->interpAlpha)) + (camera->nextRig.field  * camera->interpAlpha)

    CAM_INTERP(boomYaw);
    CAM_INTERP(boomLength);
    CAM_INTERP(boomPitch);
    CAM_INTERP(viewPitch);
    CAM_INTERP(targetPos.x);
    CAM_INTERP(targetPos.y);
    CAM_INTERP(targetPos.z);

    #undef CAM_INTERP

    CurrentCamRig.boomLength *= (camera->params.world.zoomPercent / 100.0f);

    // calculate camera position and orientation based on CurrentCamRig
    set_camera_from_rig(camera, &CurrentCamRig);
}
