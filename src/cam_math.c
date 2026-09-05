#include "common.h"
#include "camera.h"

s32 gCurrentCameraID = CAM_DEFAULT;

CameraControlSettings* test_ray_zone(f32 posX, f32 posY, f32 posZ, Collider** zone) {
    f32 hitX, hitY, hitZ, hitDepth, nX, nY, nZ;
    s32 zoneID;

    hitDepth = 32767.0f;
    zoneID = test_ray_zones(posX, posY, posZ, 0.0f, -1.0f, 0.0f, &hitX, &hitY, &hitZ, &hitDepth, &nX, &nY, &nZ);
    if (zoneID >= 0) {
        if (zone != nullptr) {
            *zone = &gZoneCollisionData.colliderList[zoneID];
        }
        return gZoneCollisionData.colliderList[zoneID].camSettings;
    } else {
        return nullptr;
    }
}

s32 calculate_segment_intersection(f32 A1x, f32 A1z, f32 A2x, f32 A2z, f32 B1x, f32 B1z, f32 B2x, f32 B2z, f32* interX, f32* interZ, f32* squared_dist) {
    f32 B1_side;
    f32 B2_side;
    f32 disc;

    f32 alpha;
    f32 Px;
    f32 Pz;

    f32 dx12 = A2x - A1x;
    f32 dz12 = A2z - A1z;
    f32 dx13 = B1x - A1x;
    f32 dz13 = B1z - A1z;
    f32 dx14 = B2x - A1x;
    f32 dz14 = B2z - A1z;
    f32 dx34 = B2x - B1x;
    f32 dz34 = B2z - B1z;

    // if distance between points on the line is 0
    if (dx12 == 0.0f && dz12 == 0.0f) {
        return false;
    }
    // if length of second segment is 0
    if (dx34 == 0.0f && dz34 == 0.0f) {
        return false;
    }

    disc = -dz12 * dx13 + dx12 * dz13;
    if (disc < 0.0f) {
        B1_side = -1.0f;
    } else if (disc > 0.0f) {
        B1_side = 1.0f;
    } else {
        B1_side = 0.0f;
    }

    disc = -dz12 * dx14 + dx12 * dz14;
    if (disc < 0.0f) {
        B2_side = -1.0f;
    } else if (disc > 0.0f) {
        B2_side = 1.0f;
    } else {
        B2_side = 0.0f;
    }

    // B1 and B2 are on the same side relative to the line: no intersection
    if (B1_side == B2_side) {
        return false;
    }

    if (fabsf(dx12) > fabsf(dx34)) {
        /*
        We represent intersection point P as P = B1 + alpha * (B2 - B1)
        and solve the equation (P - A1) x (A2 - A1) = 0, where 'x' is cross product, A1 and A2 are points on the line
        and B1 and B2 are the ends of the segment.
        So, (B1 - A1 + alpha * (B2 - B1)) x (A2 - A1) = 0,
        alpha = [-(B1 - A1) x (A2 - A1)] / [(B2 - B1) x (A2 - A1)]
        */
        // same as -(B1 - A1) x (A2 - A1)
        alpha = A1x * dz12 - A1z * dx12 + dx12 * B1z - dz12 * B1x;
        // divide by (B2 - B1) x (A2 - A1)
        alpha /= dz12 * dx34 - dx12 * dz34;
        /*
            Now we represent P as P = A1 + beta * (A2 - A1), and we are to find beta.
            B1 + alpha * (B2 - B1) = A1 + beta * (A2 - A1)
            beta * (A2 - A1) = B1 + alpha * (B2 - B1) - A1
            We use only 'x' part of this equation to find beta.

            Actually this step could be omitted and we calculate intersection directly as B1 + alpha * (B2 - B1).
            Don't know why it's done this way.
        */
        alpha = (B1x + dx34 * alpha - A1x) / dx12;
        Px = A1x + dx12 * alpha;
        Pz = A1z + dz12 * alpha;
    } else {
        /*
        We represent intersection point P as P = A1 + alpha * (A2 - A1)
        and solve the equation (B2 - B1) x (P - B1) = 0
        */
        // same as (B2 - B1) x (B1 - A1)
        alpha = B1z * dx34 + A1x * dz34 - B1z * dz34 - A1z * dx34;
        // divide by (B2 - B1) x (A2 - A1)
        alpha /= dz12 * dx34 - dx12 * dz34;
        // Now we represent P as P = B1 + beta * (B2 - B1) and find beta
        alpha = (A1x + dx12 * alpha - B1x) / dx34;
        Px = B1x + dx34 * alpha;
        Pz = B1z + dz34 * alpha;
    }
    // (P - A1) * (P - A2) > 0 when P is outside of segment A1-A2
    if ((Px - A1x) * (Px - A2x) + (Pz - A1z) * (Pz - A2z) > 0.0f) {
        return false;
    }

    *interX = Px;
    *interZ = Pz;
    // distance between P and B1
    *squared_dist = SQ(Px - B1x) + SQ(Pz - B1z);
    return true;
}

s32 calculate_line_segment_intersection(f32 A1x, f32 A1z, f32 A2x, f32 A2z, f32 B1x, f32 B1z, f32 B2x, f32 B2z, f32* interX, f32* interZ, f32* squared_dist) {
    f32 B1_side;
    f32 B2_side;
    f32 disc;

    f32 alpha;
    f32 Px;
    f32 Pz;

    f32 dx12 = A2x - A1x;
    f32 dz12 = A2z - A1z;
    f32 dx13 = B1x - A1x;
    f32 dz13 = B1z - A1z;
    f32 dx14 = B2x - A1x;
    f32 dz14 = B2z - A1z;
    f32 dx34 = B2x - B1x;
    f32 dz34 = B2z - B1z;

    if (dx12 == 0.0f && dz12 == 0.0f) {
        return false;
    }
    if (dx34 == 0.0f && dz34 == 0.0f) {
        return false;
    }

    disc = -dz12 * dx13 + dx12 * dz13;
    if (disc < 0.0f) {
        B1_side = -1.0f;
    } else if (disc > 0.0f) {
        B1_side = 1.0f;
    } else {
        B1_side = 0.0f;
    }

    disc = -dz12 * dx14 + dx12 * dz14;
    if (disc < 0.0f) {
        B2_side = -1.0f;
    } else if (disc > 0.0f) {
        B2_side = 1.0f;
    } else {
        B2_side = 0.0f;
    }

    if (B1_side == B2_side) {
        return false;
    }

    if (fabsf(dx12) > fabsf(dx34)) {
        alpha = A1x * dz12 - A1z * dx12 + dx12 * B1z - dz12 * B1x;
        alpha /= dz12 * dx34 - dx12 * dz34;
        alpha = (B1x + dx34 * alpha - A1x) / dx12;
        Px = A1x + dx12 * alpha;
        Pz = A1z + dz12 * alpha;
    } else {
        alpha = B1z * dx34 + A1x * dz34 - B1z * dz34 - A1z * dx34;
        alpha /= dz12 * dx34 - dx12 * dz34;
        alpha = (A1x + dx12 * alpha - B1x) / dx34;
        Px = B1x + dx34 * alpha;
        Pz = B1z + dz34 * alpha;
    }

    *interX = Px;
    *interZ = Pz;
    *squared_dist = SQ(Px - B1x) + SQ(Pz - B1z);
    return true;
}

s32 func_800328A4(CameraControlSettings* camSettings, f32 Px, f32 Pz) {
    f32 product1, product2;
    f32 dot1x, dot1z, dot2x, dot2z;

    if (camSettings == nullptr) {
        return 0;
    }
    if (camSettings->type != CAM_CONTROL_CONSTAIN_BETWEEN_POINTS) {
        return 0;
    }

    f32 Ax = camSettings->points.two.Ax;
    f32 Az = camSettings->points.two.Az;
    f32 Bx = camSettings->points.two.Bx;
    f32 Bz = camSettings->points.two.Bz;

    // dot product of AB and AP
    dot1x = (Bx - Ax) * (Px - Ax);
    dot1z = (Bz - Az) * (Pz - Az);
    product1 = dot1x + dot1z;

    // dot product of AB and BP
    dot2x = (Bx - Ax) * (Px - Bx);
    dot2z = (Bz - Az) * (Pz - Bz);
    product2 = dot2x + dot2z;

    if (product1 < 0 && product2 < 0) {
        return -1;
    }
    if (product1 > 0 && product2 > 0) {
        return 1;
    }
    return 0;
}

void update_camera_lead_amount(Camera* camera, f32 candidateLeadAmount) {
    s32 ignoreStickInput = camera->flags & CAMERA_FLAG_SUPRESS_LEADING;
    f32 stickX;
    f32 deltaLeadAmount;

    if (camera->curSettings != nullptr && camera->curSettings->type == CAM_CONTROL_FIXED_POS_AND_ORIENTATION) {
        ignoreStickInput = true;
    }

    if (ignoreStickInput) {
        stickX = 0.0f;
        camera->increasingLeadInterp = true;
        camera->leadInterpAlpha = 1.0f;
        camera->targetLeadAmount = 0.0f;
    } else {
        if (gPlayerStatusPtr->animFlags & PA_FLAG_RIDING_PARTNER) {
            stickX = gPartnerStatus.stickX;
        } else {
            stickX = gPlayerStatusPtr->stickAxis[0];
        }
        if (stickX > 0.0f) {
            stickX = 50.0f;
        }
        if (stickX < 0.0f) {
            stickX = -50.0f;
        }
    }

    if (stickX != 0.0f) {
        if (stickX < 0.0f) {
            if (camera->accumulatedStickLead > 0.0f) {
                // reversing direction
                camera->accumulatedStickLead = stickX;
            } else {
                camera->accumulatedStickLead += stickX;
            }
            if (camera->accumulatedStickLead <= -300.0f) {
                // max accumulation
                camera->increasingLeadInterp = true;
                if (camera->targetLeadAmount > 0.0f) {
                    camera->leadInterpAlpha = 0.0f;
                }
                camera->targetLeadAmount = -candidateLeadAmount;
                camera->accumulatedStickLead = -300.0f;
            }
        } else {
            if (camera->accumulatedStickLead < 0.0f) {
                // reversing direction
                camera->accumulatedStickLead = stickX;
            } else {
                camera->accumulatedStickLead += stickX;
            }
            if (camera->accumulatedStickLead >= 300.0f) {
                // max accumulation
                camera->increasingLeadInterp = true;
                if (camera->targetLeadAmount < 0.0f) {
                    camera->leadInterpAlpha = 0.0f;
                }
                camera->targetLeadAmount = candidateLeadAmount;
                camera->accumulatedStickLead = 300.0f;
            }
        }
    }

    if (camera->increasingLeadInterp) {
        camera->leadInterpAlpha += 0.01f;
        if (camera->leadInterpAlpha > 1.0f) {
            camera->leadInterpAlpha = 1.0f;
        }
    }

    // determine ratio to interp leadAmount by
    if (camera->targetLeadAmount - camera->leadAmount == 0.0f) {
        camera->leadInterpAlpha = 0.0f;
        camera->increasingLeadInterp = false;
    }

    deltaLeadAmount = (camera->targetLeadAmount - camera->leadAmount) * camera->leadInterpAlpha;
    if (camera->targetLeadAmount - camera->leadAmount > 0.0f) {
        // snap small changes
        if (camera->targetLeadAmount - camera->leadAmount < 0.1) {
            deltaLeadAmount = camera->targetLeadAmount - camera->leadAmount;
        }
        // clamp large changes to 3.0
        if (deltaLeadAmount > 3.0f) {
            deltaLeadAmount = 3.0f;
        }
    } else {
        // snap small changes
        if (camera->targetLeadAmount - camera->leadAmount > -0.1) {
            deltaLeadAmount = camera->targetLeadAmount - camera->leadAmount;
        }
        // clamp large changes to -3.0
        if (deltaLeadAmount < -3.0f) {
            deltaLeadAmount = -3.0f;
        }
    }

    if (stickX != 0.0f || ignoreStickInput) {
        camera->leadAmount += deltaLeadAmount;
    } else {
        camera->leadInterpAlpha = 0.0f;
    }
}

void apply_constraints_to_lead_amount(Camera* camera) {
    CameraControlSettings* settings;
    Collider* zone;
    f32 leadAmount;
    s32 s2;

    // check settings directly under the target position
    settings = test_ray_zone(camera->targetPos.x, camera->targetPos.y + 10.0f, camera->targetPos.z, nullptr);

    leadAmount = camera->leadAmount;
    s2 = 0;

    if (settings != nullptr) {
        if (settings->type == CAM_CONTROL_CONSTRAIN_TO_LINE
            || settings->type == CAM_CONTROL_LOOK_AT_POINT_CONSTAIN_TO_LINE
            || (s2 = func_800328A4(settings, camera->targetPos.x, camera->targetPos.z)) != 0
        ) {
            if (camera->needsInitialConstrainDir) {
                f32 X, Y, Z, W;

                guPerspectiveF(camera->mtxPerspective, &camera->perspNorm, camera->vfov,
                    (f32)camera->viewportW / (f32)camera->viewportH, camera->nearClip, camera->farClip, 1.0f);
                guMtxCatF(camera->mtxViewPlayer, camera->mtxPerspective, camera->mtxPerspective);
                transform_point(camera->mtxPerspective, camera->targetPos.x, camera->targetPos.y, camera->targetPos.z,
                    1.0f, &X, &Y, &Z, &W);
                if (W == 0.0f) {
                    W = 1.0f;
                }
                W = 1.0f / W;
                X *= W;
                camera->leadConstrainDir = (X > 0.0f) ? 1 : (X < 0.0f) ? -1 : 0;
                camera->needsInitialConstrainDir = false;
            } else {
                CameraControlSettings* leadSettings = camera->prevLeadSettings;

                if (leadSettings == nullptr
                    || !(leadSettings->type == CAM_CONTROL_CONSTRAIN_TO_LINE
                        || leadSettings->type == CAM_CONTROL_LOOK_AT_POINT_CONSTAIN_TO_LINE
                        || func_800328A4(settings, camera->prevLeadPosX, camera->prevLeadPosZ) != 0)
                ) {
                    if (leadSettings != nullptr && s2 != 0) {
                        camera->leadConstrainDir = s2;
                    } else {
                        f32 dx = camera->prevLeadPosX - camera->targetPos.x;
                        f32 dz = camera->prevLeadPosZ - camera->targetPos.z;
                        f32 cosYaw = cos_deg(camera->curYaw);
                        f32 sinYaw = sin_deg(camera->curYaw);
                        f32 product = dx * cosYaw + dz * sinYaw;
                        camera->leadConstrainDir = (product > 0) ? -1 : (product < 0) ? 1 : 0;
                    }
                }
            }

            if ((leadAmount > 0.0f && camera->leadConstrainDir > 0) || (leadAmount < 0.0f && camera->leadConstrainDir < 0)) {
                camera->leadInterpAlpha = 0.0f;
                camera->leadAmount = 0.0f;
            }
            camera->prevLeadSettings = settings;
            camera->prevLeadPosX = camera->targetPos.x;
            camera->prevLeadPosZ = camera->targetPos.z;
            return;
        }
    }

    camera->leadConstrainDir = 0;
    camera->prevLeadSettings = settings;
    camera->prevLeadPosX = camera->targetPos.x;
    camera->prevLeadPosZ = camera->targetPos.z;

    // find settings under (target + lead) position
    f32 yaw = DEG_TO_RAD(camera->curBoomYaw);
    f32 newPosX = camera->targetPos.x + leadAmount * cos_rad(yaw);
    f32 newPosZ = camera->targetPos.z + leadAmount * sin_rad(yaw);
    f32 newPosY = camera->targetPos.y + 10.0f;

    settings = test_ray_zone(newPosX, newPosY, newPosZ, &zone);
    if (settings == nullptr) {
        return;
    }

    if (settings->type == CAM_CONTROL_CONSTRAIN_TO_LINE
        || settings->type == CAM_CONTROL_LOOK_AT_POINT_CONSTAIN_TO_LINE
        || func_800328A4(camera->prevLeadSettings, newPosX, newPosZ) != 0
    ) {
        f32 intX, intZ, intDistSq;
        f32 minDistSq = SQ(1000.0f);
        b32 constrainToZoneTriangles = true;

        // clamp lead amount to the points when using CAM_CONTROL_CONSTAIN_BETWEEN_POINTS
        if (camera->prevLeadSettings != nullptr && camera->prevLeadSettings->type == CAM_CONTROL_CONSTAIN_BETWEEN_POINTS) {
            settings = camera->prevLeadSettings;
            constrainToZoneTriangles = false;

            f32 ABx = settings->points.two.Bx - settings->points.two.Ax;
            f32 ABz = settings->points.two.Bz - settings->points.two.Az;

            if (calculate_line_segment_intersection(settings->points.two.Ax, settings->points.two.Az,
                    settings->points.two.Ax - ABz, settings->points.two.Az + ABx,
                    camera->targetPos.x, camera->targetPos.z, newPosX, newPosZ, &intX, &intZ, &intDistSq)
                && intDistSq < minDistSq
            ) {
                minDistSq = intDistSq;
            }
            if (calculate_line_segment_intersection(settings->points.two.Bx, settings->points.two.Bz,
                    settings->points.two.Bx - ABz, settings->points.two.Bz + ABx,
                    camera->targetPos.x, camera->targetPos.z, newPosX, newPosZ, &intX, &intZ, &intDistSq)
                && intDistSq < minDistSq
            ) {
                minDistSq = intDistSq;
            }
        }

        if (constrainToZoneTriangles) {
            for (s32 i = 0; i < zone->numTriangles; i++) {
                if (calculate_segment_intersection(zone->triangleTable[i].v1->x, zone->triangleTable[i].v1->z,
                        zone->triangleTable[i].v2->x, zone->triangleTable[i].v2->z,
                        camera->targetPos.x, camera->targetPos.z, newPosX, newPosZ, &intX, &intZ, &intDistSq)
                    && intDistSq < minDistSq
                ) {
                    minDistSq = intDistSq;
                }
                if (calculate_segment_intersection(zone->triangleTable[i].v2->x, zone->triangleTable[i].v2->z,
                        zone->triangleTable[i].v3->x, zone->triangleTable[i].v3->z,
                        camera->targetPos.x, camera->targetPos.z, newPosX, newPosZ, &intX, &intZ, &intDistSq)
                    && intDistSq < minDistSq
                ) {
                    minDistSq = intDistSq;
                }
                if (calculate_segment_intersection(zone->triangleTable[i].v3->x, zone->triangleTable[i].v3->z,
                        zone->triangleTable[i].v1->x, zone->triangleTable[i].v1->z,
                        camera->targetPos.x, camera->targetPos.z, newPosX, newPosZ, &intX, &intZ, &intDistSq)
                    && intDistSq < minDistSq
                ) {
                    minDistSq = intDistSq;
                }
            }
        }

        if (minDistSq == SQ(1000.0f) || minDistSq == 0.0f) {
            camera->leadAmount = 0.0f;
        } else {
            camera->leadAmount = (camera->leadAmount > 0.0f) ? sqrtf(minDistSq) : -sqrtf(minDistSq);
        }
        camera->leadInterpAlpha = 0.0f;
    }
}

void create_camera_leadplayer_matrix(Camera* camera) {
    f32 dx = camera->lookAt_eye.x - camera->lookAt_obj.x;
    f32 dy = camera->lookAt_eye.y - camera->lookAt_obj.y;
    f32 dz = camera->lookAt_eye.z - camera->lookAt_obj.z;
    f32 dist = sqrtf(SQ(dx) + SQ(dy) + SQ(dz));
    f32 theta = ((camera->vfov * 0.5f) / 180.0f) * PI;
    f32 distTanTheta = dist * (sin_rad(theta) / cos_rad(theta));
    f32 hfov = distTanTheta * camera->viewportW / camera->viewportH;

    update_camera_lead_amount(camera, hfov * camera->leadAmtScale);
    apply_constraints_to_lead_amount(camera);
    guTranslateF(camera->mtxViewLeading, -camera->leadAmount, 0.0f, 0.0f);
}
