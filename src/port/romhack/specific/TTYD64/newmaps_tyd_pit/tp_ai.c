#include "common.h"
#include "effects.h"
#include "npc.h"
#include "tp.h"

#define NAMESPACE TTYD64_tp_kzn_03
// visual enemy
#include "common.h"
#include "npc.h"
#include "effects.h"

// hitbox enemy

void N(PiranhaPlantAI_00)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if (npc->duration > 0) {
        npc->duration--;
    } else {
        enemy->varTable[0] = 0;
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        script->functionTemp[1] = 0;
        script->functionTemp[0] = 1;
    }
}

void N(PiranhaPlantAI_01)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    EffectInstance* temp;

    if (basic_ai_check_player_dist(territory, enemy, aiSettings->alertRadius, aiSettings->alertOffsetDist, 0)) {
        ai_enemy_play_sound(npc, SOUND_BURROW_DIG, 0);
        fx_emote(EMOTE_EXCLAMATION, npc, 0, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 10, &temp);
        ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_MELEE_PRE];
        npc->duration = enemy->varTable[8];
        script->functionTemp[0] = 10;
    }
}

void N(PiranhaPlantAI_10)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    s32 phi_s7 = false;
    s32 phi_fp = false;
    f32 sp38;
    f32 yaw;
    f32 yaw2;
    f32 moveSpeed;
    f32 posRadius;
    s32 cond1;
    s32 cond2;
    f32 terSize;
    f32 sp20;
    f32 sp24;
    f32 sp28;
    f32 sp2C;
    f32 sp30;
    f32 sp34;

    npc->duration--;
    if (enemy->varTable[9] >= npc->duration) {
        enemy->flags |=
            (ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER
             | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER);
    }

    if (npc->duration == 0) {
        if (clamp_angle(gPlayerStatusPtr->spriteFacingAngle) < 180.0f) {
            yaw2 = clamp_angle(gCameras[gCurrentCameraID].curYaw - 90.0f);
        } else {
            yaw2 = clamp_angle(gCameras[gCurrentCameraID].curYaw + 90.0f);
        }

        yaw = clamp_angle(yaw2 + 180.0f);
        if (enemy->varTable[7] == 0) {
            moveSpeed = 32.0f;

            if (gPlayerStatusPtr->actionState != 0) {
                moveSpeed = 100.0f;
                if (gPlayerStatusPtr->actionState == 1) {
                    moveSpeed = 90.0f;
                }
            }
        } else {
            moveSpeed = 38.0f;

            if (gPlayerStatusPtr->actionState != 0) {
                moveSpeed = 90.0f;
                if (gPlayerStatusPtr->actionState == 1) {
                    moveSpeed = 75.0f;
                }
            }
        }

        npc->pos.x = gPlayerStatusPtr->pos.x;
        npc->pos.z = gPlayerStatusPtr->pos.z;
        add_vec2D_polar(&npc->pos.x, &npc->pos.z, npc->collisionDiameter, yaw);
        npc_move_heading(npc, moveSpeed + npc->collisionDiameter, yaw2);

        if (enemy->varTable[7] == 0) {
            if (npc->pos.x > 380.0) {
                npc->pos.x = 380.0f;
            }
            if (npc->pos.x < -380.0) {
                npc->pos.x = -380.0f;
            }
            if (npc->pos.z > 380.0) {
                npc->pos.z = 380.0f;
            }
            if (npc->pos.z < -380.0) {
                npc->pos.z = -380.0f;
            }

            sp38 = sqrtf(SQ(npc->pos.x) + SQ(npc->pos.z));
            yaw2 = atan2(0.0f, 0.0f, npc->pos.x, npc->pos.z);

            if (sp38 < 305.0) {
                npc->pos.x = 0.0f;
                npc->pos.z = 0.0f;
                add_vec2D_polar(&npc->pos.x, &npc->pos.z, 305.0f, yaw2);
            } else if (sp38 > 375.0) {
                npc->pos.x = 0.0f;
                npc->pos.z = 0.0f;
                add_vec2D_polar(&npc->pos.x, &npc->pos.z, 375.0f, yaw2);
            }
        } else {
            if (!(npc->flags & NPC_FLAG_IGNORE_WORLD_COLLISION)) {
                sp20 = gPlayerStatusPtr->pos.x;
                sp24 = gPlayerStatusPtr->pos.y + 18.0;
                sp28 = gPlayerStatusPtr->pos.z;
                if (npc_test_move_simple_with_slipping(
                        npc->collisionChannel, &sp20, &sp24, &sp28, moveSpeed, yaw2, npc->collisionHeight,
                        npc->collisionDiameter
                    ))
                {
                    sp20 = gPlayerStatusPtr->pos.x;
                    sp24 = gPlayerStatusPtr->pos.y + 45.0;
                    sp28 = gPlayerStatusPtr->pos.z;
                    cond1 = npc_test_move_simple_with_slipping(
                        npc->collisionChannel, &sp20, &sp24, &sp28, moveSpeed, yaw2, npc->collisionHeight,
                        npc->collisionDiameter
                    );
                    sp2C = npc->pos.x;
                    sp30 = npc->pos.y + 100.0;
                    sp34 = npc->pos.z;
                    sp38 = 200.0f;
                    cond2 = npc_raycast_down_sides(npc->collisionChannel, &sp2C, &sp30, &sp34, &sp38);
                    if (!cond1 && cond2 && sp38 > 80.0 && sp38 < 120.0 && npc->pos.y != sp30) {
                        phi_fp = true;
                    } else {
                        sp20 = gPlayerStatusPtr->pos.x;
                        sp24 = gPlayerStatusPtr->pos.y + 10.0;
                        sp28 = gPlayerStatusPtr->pos.z;
                        npc_test_move_simple_with_slipping(
                            npc->collisionChannel, &sp20, &sp24, &sp28, moveSpeed, yaw2, npc->collisionHeight,
                            npc->collisionDiameter
                        );
                        posRadius = dist2D(gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z, sp20, sp28);
                        npc->pos.x = gPlayerStatusPtr->pos.x;
                        npc->pos.z = gPlayerStatusPtr->pos.z;
                        add_vec2D_polar(&npc->pos.x, &npc->pos.z, npc->collisionDiameter, yaw);
                        npc_move_heading(npc, posRadius + npc->collisionDiameter, yaw2);
                        phi_s7 = true;
                    }
                }
            } else {
                sp20 = gPlayerStatusPtr->pos.x;
                sp24 = gPlayerStatusPtr->pos.y + 18.0;
                sp28 = gPlayerStatusPtr->pos.z;
                if (npc_test_move_simple_with_slipping(
                        npc->collisionChannel, &sp20, &sp24, &sp28, moveSpeed, yaw2, npc->collisionHeight,
                        npc->collisionDiameter
                    ))
                {
                    posRadius = dist2D(gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z, sp20, sp28);
                    npc->pos.x = gPlayerStatusPtr->pos.x;
                    npc->pos.z = gPlayerStatusPtr->pos.z;
                    add_vec2D_polar(&npc->pos.x, &npc->pos.z, npc->collisionDiameter, yaw);
                    npc_move_heading(npc, posRadius + npc->collisionDiameter, yaw2);
                }
            }
        }

        if (is_point_outside_territory(
                territory->shape, territory->pointX, territory->pointZ, npc->pos.x, npc->pos.z, territory->sizeX,
                territory->sizeZ
            ))
        {
            switch (territory->shape) {
                case SHAPE_CYLINDER:
                    sp38 = dist2D(npc->pos.x, npc->pos.z, territory->pointX, territory->pointZ);

                    if (territory->sizeX < sp38) {
                        terSize = atan2(territory->pointX, territory->pointZ, npc->pos.x, npc->pos.z);
                        npc->pos.x = territory->pointX;
                        npc->pos.z = territory->pointZ;
                        add_vec2D_polar(&npc->pos.x, &npc->pos.z, territory->sizeX, terSize);
                    }
                    break;
                case SHAPE_RECT:
                    terSize = territory->pointX + territory->sizeX;
                    if (npc->pos.x > terSize) {
                        npc->pos.x = terSize;
                    }

                    terSize = territory->pointX - territory->sizeX;
                    if (npc->pos.x < terSize) {
                        npc->pos.x = terSize;
                    }

                    terSize = territory->pointZ + territory->sizeZ;
                    if (npc->pos.z > terSize) {
                        npc->pos.z = terSize;
                    }

                    terSize = territory->pointZ - territory->sizeZ;
                    if (npc->pos.z < terSize) {
                        npc->pos.z = terSize;
                    }
                    break;
            }
        }

        if (!phi_s7 && (!(npc->flags & NPC_FLAG_FLYING) || phi_fp)) {
            sp20 = npc->pos.x;
            sp38 = 400.0f;
            sp28 = npc->pos.z;
            sp24 = npc->pos.y + 150.0;

            if (npc_raycast_down_sides(npc->collisionChannel, &sp20, &sp24, &sp28, &sp38) != 0) {
                npc->pos.y = sp24;
            }
        }

        npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
        ai_enemy_play_sound(npc, SOUND_BURROW_SURFACE, 0);
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_MELEE_HIT];
        npc->duration = enemy->varTable[10];
        script->functionTemp[0] = 11;
    }
}

void N(PiranhaPlantAI_11)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (enemy->varTable[11] >= npc->duration) {
        enemy->flags &=
            ~(ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER
              | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER);
    }
    if (npc->duration == 0) {
        npc->curAnim = enemy->animList[10];
        npc->duration = 0;
        script->functionTemp[0] = 12;
    }
}

void N(PiranhaPlantAI_12)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    EffectInstance* temp;

    npc->duration++;
    if (npc->duration == enemy->varTable[13]) {
        npc->curAnim = enemy->animList[11];
    }
    if (npc->duration == 9) {
        enemy->varTable[0] = 3;
    }
    if (npc->duration >= enemy->varTable[12]) {
        enemy->varTable[0] = 4;
        npc->duration = 8;
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        fx_emote(EMOTE_FRUSTRATION, npc, 0, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 10, &temp);
        script->functionTemp[0] = 13;
    }
}

void N(PiranhaPlantAI_13)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration == 0) {
        npc->duration = enemy->varTable[15];
        script->functionTemp[0] = 14;
    }
}

void N(PiranhaPlantAI_LosePlayer)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    EffectInstance* retVal;

    npc->duration--;
    if (npc->duration == 0) {
        if (basic_ai_check_player_dist(territory, enemy, aiSettings->alertRadius, aiSettings->alertOffsetDist, 0) == 0)
        {
            fx_emote(EMOTE_QUESTION, npc, 0, npc->collisionHeight, 1, 2, -20, 15, &retVal);
        }
        npc->duration = 0;
        script->functionTemp[0] = 0;
    }
}

#include "common.h"
#include "npc.h"

API_CALLABLE(N(PiranhaPlantAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    EnemyDetectVolume territory;
    EnemyDetectVolume* territoryPtr = &territory;
    MobileAISettings* npcAISettings = (MobileAISettings*) evt_get_variable(script, *args++);

    territory.skipPlayerDetectChance = 0;
    territory.shape = enemy->territory->wander.detectShape;
    territory.pointX = enemy->territory->wander.detectPos.x;
    territory.pointZ = enemy->territory->wander.detectPos.z;
    territory.sizeX = enemy->territory->wander.detectSize.x;
    territory.sizeZ = enemy->territory->wander.detectSize.z;
    territory.halfHeight = 200.0f;
    territory.detectFlags = 0;

    if (isInitialCall || (enemy->aiFlags & AI_FLAG_SUSPEND)) {
        script->AI_TEMP_STATE = AI_STATE_PIRANHA_PLANT_00;
        npc->duration = 0;
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];

        enemy->AI_VAR_ATTACK_STATE = MELEE_HITBOX_STATE_NONE;
        if (enemy->aiFlags & AI_FLAG_SUSPEND) {
            script->AI_TEMP_STATE = AI_STATE_SUSPEND;
            script->functionTemp[1] = AI_STATE_PIRANHA_PLANT_00;
            enemy->aiFlags &= ~AI_FLAG_SUSPEND;
        }
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_PIRANHA_PLANT_00:
            N(PiranhaPlantAI_00)(script, npcAISettings, territoryPtr);
        case AI_STATE_PIRANHA_PLANT_01:
            N(PiranhaPlantAI_01)(script, npcAISettings, territoryPtr);
            break;
        case AI_STATE_PIRANHA_PLANT_10:
            N(PiranhaPlantAI_10)(script, npcAISettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_PIRANHA_PLANT_11) {
                break;
            }
        case AI_STATE_PIRANHA_PLANT_11:
            N(PiranhaPlantAI_11)(script, npcAISettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_PIRANHA_PLANT_12) {
                break;
            }
        case AI_STATE_PIRANHA_PLANT_12:
            N(PiranhaPlantAI_12)(script, npcAISettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_PIRANHA_PLANT_13) {
                break;
            }
        case AI_STATE_PIRANHA_PLANT_13:
            N(PiranhaPlantAI_13)(script, npcAISettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_LOSE_PLAYER) {
                break;
            }
        case AI_STATE_LOSE_PLAYER:
            N(PiranhaPlantAI_LosePlayer)(script, npcAISettings, territoryPtr);
            break;
        case AI_STATE_SUSPEND:
            basic_ai_suspend(script);
            break;
    }
    return ApiStatus_BLOCK;
}
#undef NAMESPACE

#define NAMESPACE TTYD64_tp_flo_13
// spiny AI

#include "common.h"
#include "npc.h"
#include "effects.h"
#include "sprite/npc/Spiny.h"

// prerequisites
#include "world/common/enemy/ai/TackleAI.inc.c"

API_CALLABLE(N(BlueSpinyAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    EnemyDetectVolume territory;
    EnemyDetectVolume* territoryPtr = &territory;
    MobileAISettings* aiSettings = (MobileAISettings*) evt_get_variable(script, *args);
    u32 x, y, z;
    f32 x2, y2, z2, w2;
    Npc* npc2;

    territory.skipPlayerDetectChance = 0;
    territory.shape = enemy->territory->wander.detectShape;
    territory.pointX = enemy->territory->wander.detectPos.x;
    territory.pointZ = enemy->territory->wander.detectPos.z;
    territory.sizeX = enemy->territory->wander.detectSize.x;
    territory.sizeZ = enemy->territory->wander.detectSize.z;
    territory.halfHeight = 65.0f;
    territory.detectFlags = 0;

    if (isInitialCall) {
        enemy->varTable[6] = npc->collisionHeight;
        enemy->aiFlags |= AI_FLAG_SKIP_EMOTE_AFTER_FLEE;
    }

    if (isInitialCall || (enemy->varTable[10] == 100)) {
        script->AI_TEMP_STATE = 100;
        npc->duration = 0;
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->flags &= ~NPC_FLAG_JUMPING;
        enemy->flags |= ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN;
        npc->flags &= ~NPC_FLAG_GRAVITY;
        npc->flags |= NPC_FLAG_FLYING;
        enemy->varTable[10] = 0;
        enemy->varTable[11] = -1;
        npc->pos.x = NPC_DISPOSE_POS_X;
        npc->pos.y = NPC_DISPOSE_POS_Y;
        npc->pos.z = NPC_DISPOSE_POS_Z;
    }

    if (enemy->aiFlags & AI_FLAG_SUSPEND) {
        npc->duration = 0;
        npc->collisionHeight = enemy->varTable[6];
        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
        if (npc->flags & NPC_FLAG_JUMPING) {
            npc->curAnim = 0x004A0118;
            npc->moveSpeed = 0.0f;
            npc->jumpVel = 0.0f;
            npc->jumpScale = 1.0f;
            script->AI_TEMP_STATE = 102;
        } else {
            EffectInstance* emoteTemp;
            fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 0x28, &emoteTemp);
            npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
            script->functionTemp[1] = 0;
            script->AI_TEMP_STATE = 200;
        }
    }
    get_screen_coords(CAM_DEFAULT, npc->pos.x, npc->pos.y, npc->pos.z, &x, &y, &z);
    if (script->AI_TEMP_STATE < 100 && x + 50 >= 421) {
        script->AI_TEMP_STATE = 110;
    }

    switch (script->AI_TEMP_STATE) {
        case 0:
            basic_ai_wander_init(script, aiSettings, territoryPtr);
            npc->collisionHeight = enemy->varTable[6];
            if (enemy->varTable[13] != 0) {
                if (npc->pos.y <= 0.0) {
                    npc->flags &= ~NPC_FLAG_GRAVITY;
                    npc->flags |= NPC_FLAG_FLYING;
                } else {
                    npc->flags |= NPC_FLAG_GRAVITY;
                    npc->flags &= ~NPC_FLAG_FLYING;
                }
            }
            basic_ai_wander(script, aiSettings, territoryPtr);
            break;
        case 1:
            basic_ai_wander(script, aiSettings, territoryPtr);
            break;
        case 2:
            basic_ai_loiter_init(script, aiSettings, territoryPtr);
        case 3:
            basic_ai_loiter(script, aiSettings, territoryPtr);
            break;
        case 12:
            N(set_script_owner_npc_anim)(script, aiSettings, territoryPtr);
        case 13:
            N(UnkDistFunc)(script, aiSettings, territoryPtr);
            npc->collisionHeight = enemy->varTable[6];
            break;
        case 14:
            N(UnkNpcAIFunc12)(script, aiSettings, territoryPtr);
            break;
        case 15:
            N(set_script_owner_npc_col_height)(script, aiSettings, territoryPtr);
            break;
        case 100:
            if (enemy->varTable[10] != 2) {
                break;
            }
            npc2 = get_npc_unsafe(get_enemy(enemy->varTable[11])->npcID);
            if (npc2->yaw < 180.0) {
                npc->pos.x = npc2->pos.x + 12.0;
            } else {
                npc->pos.x = npc2->pos.x - 12.0;
            }
            npc->pos.y = npc2->pos.y + 25.0;
            npc->pos.z = npc2->pos.z + 1.0;
            npc->rot.y = 0.0f;
            npc->flags |= NPC_FLAG_FLYING;
            npc->flags &= ~NPC_FLAG_INVISIBLE;
            npc->flags &= ~NPC_FLAG_GRAVITY;
            npc->renderYaw = 0.0f;
            npc->curAnim = 0x004A0118;
            script->AI_TEMP_STATE = 101;
        case 101:
            if (enemy->varTable[10] != 3) {
                break;
            }
            enemy->varTable[10] = 4;
            npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
            npc->moveSpeed = 2.5f;
            npc->jumpVel = 8.0f;
            npc->jumpScale = 0.8f;
            npc->flags |= NPC_FLAG_JUMPING;
            script->AI_TEMP_STATE = 102;
        case 102:
            if (npc->moveSpeed > 0.0) {
                x2 = npc->pos.x;
                y2 = npc->pos.y;
                z2 = npc->pos.z;
                if (npc_test_move_simple_with_slipping(
                        npc->collisionChannel, &x2, &y2, &z2, npc->moveSpeed, npc->yaw, npc->collisionHeight,
                        npc->collisionDiameter
                    )
                    == 0)
                {
                    npc_move_heading(npc, npc->moveSpeed, npc->yaw);
                } else {
                    npc->moveSpeed = 0.0f;
                }
            }
            if (npc->jumpVel < 0.0) {
                x2 = npc->pos.x;
                y2 = npc->pos.y + 13.0;
                z2 = npc->pos.z;
                w2 = fabsf(npc->jumpVel) + 16.0;
                if ((npc_raycast_down_sides(npc->collisionChannel, &x2, &y2, &z2, &w2) != 0)
                    && (w2 <= (fabsf(npc->jumpVel) + 13.0)))
                {
                    npc->pos.y = y2;
                    enemy->territory->wander.centerPos.x = npc->pos.x;
                    enemy->territory->wander.centerPos.y = npc->pos.y;
                    enemy->territory->wander.centerPos.z = npc->pos.z;
                    enemy->territory->wander.detectPos.x = npc->pos.x;
                    enemy->territory->wander.detectPos.y = npc->pos.y;
                    enemy->territory->wander.detectPos.z = npc->pos.z;
                    enemy->varTable[10] = 5;
                    if (enemy->varTable[13] != 0) {
                        if (npc->pos.y <= 0.0) {
                            npc->flags &= ~NPC_FLAG_GRAVITY;
                            npc->flags |= NPC_FLAG_FLYING;
                        } else {
                            npc->flags |= NPC_FLAG_GRAVITY;
                            npc->flags &= ~NPC_FLAG_FLYING;
                        }
                    } else if (!enemy->territory->wander.isFlying) {
                        npc->flags |= NPC_FLAG_GRAVITY;
                        npc->flags &= ~NPC_FLAG_FLYING;
                    } else {
                        npc->flags &= ~NPC_FLAG_GRAVITY;
                        npc->flags |= NPC_FLAG_FLYING;
                    }
                    npc->flags |= NPC_FLAG_IGNORE_CAMERA_FOR_YAW;
                    npc->flags &= ~NPC_FLAG_JUMPING;
                    npc->jumpVel = 0.0f;
                    npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
                    npc->curAnim = 0x004A011A;
                    npc->duration = 3;
                    script->AI_TEMP_STATE = 103;
                    break;
                }
            }
            npc->pos.y += npc->jumpVel;
            npc->jumpVel -= npc->jumpScale;
            break;
        case 103:
            npc->duration--;
            if (npc->duration <= 0) {
                npc->flags &= ~NPC_FLAG_IGNORE_CAMERA_FOR_YAW;
                npc->curAnim = 0x004A0101;
                script->AI_TEMP_STATE = 0;
            }
            break;
        case 110:
            npc->duration = 30;
            npc->pos.x = NPC_DISPOSE_POS_X;
            npc->pos.y = NPC_DISPOSE_POS_Y;
            npc->pos.z = NPC_DISPOSE_POS_Z;
            npc->flags |= NPC_FLAG_FLYING | NPC_FLAG_INVISIBLE;
            npc->flags &= ~NPC_FLAG_GRAVITY;
            script->AI_TEMP_STATE = 111;
        case 111:
            npc->duration--;
            if (npc->duration <= 0) {
                enemy->varTable[10] = 0;
                script->AI_TEMP_STATE = 100;
            }
            break;
        case 200:
            basic_ai_suspend(script);
            break;
    }
    return ApiStatus_BLOCK;
}
#undef NAMESPACE

#define NAMESPACE TTYD64_tp_iwa_01
#include "common.h"
#include "npc.h"
#include "sprite/npc/MontyMole.h"

// prerequisites

// ensure state handlers conform to expected signature
static AIStateHandler N(MontyMoleAI_Init);
static AIStateHandler N(MontyMoleAI_Wander);
static AIStateHandler N(MontyMoleAI_PreSurface);
static AIStateHandler N(MontyMoleAI_Surface);
static AIStateHandler N(MontyMoleAI_DrawRock);
static AIStateHandler N(MontyMoleAI_ThrowRock);
static AIStateHandler N(MontyMoleAI_PreBurrow);
static AIStateHandler N(MontyMoleAI_Burrow);

enum AiStateMontyMole {
    AI_STATE_MOLE_INIT = 0,         // choose random heading and duration for next state
    AI_STATE_MOLE_WANDER = 1,       // wander around 'underground'
    AI_STATE_MOLE_PRE_SURFACE = 12, // delay before emerging from underground
    AI_STATE_MOLE_SURFACE = 13,     // emerge from underground
    AI_STATE_MOLE_DRAW_ROCK = 14,   // pull out a rock, can either attack or cancel
    AI_STATE_MOLE_THROW_ROCK = 15,  // throw the rock
    AI_STATE_MOLE_UNUSED = 16,
    AI_STATE_MOLE_PRE_BURROW = 20, // delay before burrowing back underground
    AI_STATE_MOLE_BURROW = 21,     // burrow underground
};

#define INTANGIBLE_MONTY_MOLE_NPC_FLAGS \
    ENEMY_FLAG_SKIP_BATTLE \
    | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_IGNORE_PARTNER \
        | ENEMY_FLAG_CANT_INTERACT

static s32 N(MontyMoleAI_CanAttack)(Evt* script, EnemyDetectVolume* territory, f32 radius, f32 arg3) {
    Camera* cam;
    Enemy* enemy;
    Npc* npc;
    f32 angle;
    s32 retVal;

    enemy = script->owner1.enemy;
    npc = get_npc_unsafe(enemy->npcID);
    cam = &gCameras[gCurrentCamID];
    retVal = basic_ai_check_player_dist(territory, enemy, radius * 1.1, arg3, 0) != 0;
    // check npc facing angle for sight of player
    angle = 270.0f;
    if (clamp_angle(get_clamped_angle_diff(cam->curYaw, npc->yaw)) < 180.0) {
        angle = 90.0f;
    }
    if (fabsf(get_clamped_angle_diff(
            angle, atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z)
        ))
        > 60.0)
    {
        retVal = false;
    }
    // check for overlap with player
    if (get_xz_dist_to_player(npc->pos.x, npc->pos.z) < gPlayerStatusPtr->colliderDiameter + npc->collisionDiameter) {
        retVal = false;
    }
    // check player elevation difference
    if (fabsf(npc->pos.y - gPlayerStatusPtr->pos.y) >= 40.0f) {
        retVal = false;
    }
    // check for bow hiding
    if (gPartnerStatus.actingPartner == PARTNER_BOW) {
        retVal = false;
    }
    return retVal;
}

static void N(MontyMoleAI_Init)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = (aiSettings->moveTime / 2) + rand_int((aiSettings->moveTime / 2) + 1);
    npc->yaw = clamp_angle((npc->yaw + rand_int(60)) - 30.0f);
    if (enemy->territory->wander.moveSpeedOverride < 0) {
        npc->moveSpeed = aiSettings->moveSpeed;
    } else {
        npc->moveSpeed = enemy->territory->wander.moveSpeedOverride / 32767.0;
    }
    enemy->flags |= INTANGIBLE_MONTY_MOLE_NPC_FLAGS;
    npc->flags |= NPC_FLAG_INVISIBLE;
    script->functionTemp[1] = 0;
    script->AI_TEMP_STATE = AI_STATE_MOLE_WANDER;
}

static void N(MontyMoleAI_Wander)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Npc dummyNpc;
    f32 hitDepth;

    if (is_point_outside_territory(
            enemy->territory->wander.wanderShape, enemy->territory->wander.centerPos.x,
            enemy->territory->wander.centerPos.z, npc->pos.x, npc->pos.z, enemy->territory->wander.wanderSize.x,
            enemy->territory->wander.wanderSize.z
        ))
    {
        npc->yaw =
            atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z);
    }
    dummyNpc.pos.x = npc->pos.x;
    dummyNpc.pos.y = npc->pos.y + 1.0f;
    dummyNpc.pos.z = npc->pos.z;
    npc_move_heading(&dummyNpc, npc->moveSpeed + npc->collisionDiameter, npc->yaw);
    hitDepth = 1000.0f;
    if (npc_raycast_down_sides(0, &dummyNpc.pos.x, &dummyNpc.pos.y, &dummyNpc.pos.z, &hitDepth) && (hitDepth < 5.0f)) {
        npc_move_heading(npc, npc->moveSpeed, npc->yaw);
    }
    if (npc->flags & NPC_FLAG_COLLDING_FORWARD_WITH_WORLD) {
        script->AI_TEMP_STATE = AI_STATE_MOLE_INIT;
    }
    if (aiSettings->playerSearchInterval >= 0) {
        if (script->functionTemp[1] <= 0) {
            script->functionTemp[1] = aiSettings->playerSearchInterval;
            if (N(MontyMoleAI_CanAttack)(script, territory, aiSettings->alertRadius, aiSettings->alertOffsetDist)) {
                npc->duration = 0;
                script->AI_TEMP_STATE = AI_STATE_MOLE_PRE_SURFACE;
                return;
            }
        }
        script->functionTemp[1]--;
    }
    if (!(npc->flags & (NPC_FLAG_FLYING | NPC_FLAG_GROUNDED))) {
        npc->homePos.x = npc->pos.x;
        npc->homePos.z = npc->pos.z;
    }
    npc->duration--;
    if (npc->duration == 0) {
        script->AI_TEMP_STATE = AI_STATE_MOLE_INIT;
    }
}

static void N(MontyMoleAI_PreSurface)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->flags &= ~NPC_FLAG_INVISIBLE;
    ai_enemy_play_sound(npc, SOUND_BURROW_SURFACE, 0);
    npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
    npc->curAnim = 0x002F0210; // emerge from ground
    npc->duration = 10;
    script->AI_TEMP_STATE = AI_STATE_MOLE_SURFACE;
}

static void N(MontyMoleAI_Surface)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration == 2) {
        enemy->flags &= ~(INTANGIBLE_MONTY_MOLE_NPC_FLAGS);
    }
    if (npc->duration <= 0) {
        npc->curAnim = 0x002F0218; // get and throw rock
        npc->duration = 10;
        script->AI_TEMP_STATE = AI_STATE_MOLE_DRAW_ROCK;
    }
}

static void N(MontyMoleAI_DrawRock)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    EffectInstance* emoteOut;

    npc->duration--;
    if ((npc->duration) <= 0) {
        if (!N(MontyMoleAI_CanAttack)(script, territory, aiSettings->alertRadius * 1.1, aiSettings->alertOffsetDist)) {
            fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 0x20F, &emoteOut);
            npc->curAnim = 0x002F0201; // cancel attack
            npc->duration = 30;
            script->AI_TEMP_STATE = AI_STATE_MOLE_PRE_BURROW;
        } else {
            npc->curAnim = 0x002F021B; // throw rock
            npc->duration = 15;
            script->AI_TEMP_STATE = AI_STATE_MOLE_THROW_ROCK;
        }
    }
}

static void N(MontyMoleAI_ThrowRock)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* moleEnemy;
    Enemy* rockEnemy;
    Npc* moleNpc;

    moleEnemy = script->owner1.enemy;
    moleNpc = get_npc_unsafe(moleEnemy->npcID);
    moleNpc->duration--;
    if (moleNpc->duration == 13) {
        rockEnemy = get_enemy(moleEnemy->npcID + 1);
        rockEnemy->varTable[4] = moleEnemy->npcID;
        rockEnemy->varTable[0] = 1;
    }
    if (moleNpc->duration < 8) {
        if (dist2D(moleNpc->pos.x, moleNpc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z) > 100.0) {
            moleNpc->curAnim = 0x002F0215; // clap
        }
    }
    if (moleNpc->duration <= 0) {
        if (moleNpc->curAnim != 0x002F0215) {
            moleNpc->curAnim = 0x002F0201;
        }
        moleNpc->duration = 15;
        script->AI_TEMP_STATE = AI_STATE_MOLE_PRE_BURROW;
    }
}

static void N(MontyMoleAI_PreBurrow)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        ai_enemy_play_sound(npc, SOUND_BURROW_DIG, 0);
        npc->duration = 11;
        npc->curAnim = 0x002F0211; // retreat into ground
        script->AI_TEMP_STATE = AI_STATE_MOLE_BURROW;
    }
}

static void N(MontyMoleAI_Burrow)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration == 3) {
        enemy->flags |= INTANGIBLE_MONTY_MOLE_NPC_FLAGS;
    }
    if (npc->duration <= 0) {
        npc->flags |= NPC_FLAG_INVISIBLE;
        script->AI_TEMP_STATE = AI_STATE_MOLE_INIT;
    }
}

API_CALLABLE(N(MontyMoleAI_Main)) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    EnemyDetectVolume territory;
    EnemyDetectVolume* territoryPtr = &territory;
    MobileAISettings* aiSettings = (MobileAISettings*) evt_get_variable(script, *args++);

    territory.skipPlayerDetectChance = 0;
    territory.shape = enemy->territory->wander.detectShape;
    territory.pointX = enemy->territory->wander.detectPos.x;
    territory.pointZ = enemy->territory->wander.detectPos.z;
    territory.sizeX = enemy->territory->wander.detectSize.x;
    territory.sizeZ = enemy->territory->wander.detectSize.z;
    territory.halfHeight = 65.0f;
    territory.detectFlags = 0;

    if (isInitialCall) {
        script->AI_TEMP_STATE = AI_STATE_MOLE_INIT;
        npc->duration = 0;
        npc->flags &= ~NPC_FLAG_JUMPING;
        enemy->aiFlags |= (AI_FLAG_SKIP_EMOTE_AFTER_FLEE | AI_FLAG_SKIP_IDLE_ANIM_AFTER_FLEE);
    }

    if (enemy->aiFlags & AI_FLAG_SUSPEND) {
        if (enemy->aiSuspendTime != 0) {
            return ApiStatus_BLOCK;
        }
        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_MOLE_INIT:
            N(MontyMoleAI_Init)(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_STATE_MOLE_WANDER:
            N(MontyMoleAI_Wander)(script, aiSettings, territoryPtr);
            return ApiStatus_BLOCK;
        case AI_STATE_MOLE_PRE_SURFACE:
            N(MontyMoleAI_PreSurface)(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_STATE_MOLE_SURFACE:
            N(MontyMoleAI_Surface)(script, aiSettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_MOLE_DRAW_ROCK) {
                return ApiStatus_BLOCK;
            } // else fallthrough
        case AI_STATE_MOLE_DRAW_ROCK:
            N(MontyMoleAI_DrawRock)(script, aiSettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_MOLE_THROW_ROCK) {
                return ApiStatus_BLOCK;
            } // else fallthrough
        case AI_STATE_MOLE_THROW_ROCK:
            N(MontyMoleAI_ThrowRock)(script, aiSettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_MOLE_UNUSED) {
                return ApiStatus_BLOCK;
            } // else fallthrough
        case AI_STATE_MOLE_PRE_BURROW:
            N(MontyMoleAI_PreBurrow)(script, aiSettings, territoryPtr);
            return ApiStatus_BLOCK;
        case AI_STATE_MOLE_BURROW:
            N(MontyMoleAI_Burrow)(script, aiSettings, territoryPtr);
            return ApiStatus_BLOCK;
    }
    return ApiStatus_BLOCK;
}
#undef NAMESPACE
