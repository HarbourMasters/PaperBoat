#include "common.h"
#include "effects.h"
#include "hud_element.h"
#include "message_ids.h"
#include "ld_addrs.h"
#include "model.h"
#include "battle/states/states.h"
#include "script_api/battle.h"
#include "entity.h"
#include "sprite/npc/BattleGoombario.h"
#include "sprite/npc/BattleKooper.h"
#include "sprite/npc/BattleBombette.h"
#include "sprite/npc/BattleParakarry.h"
#include "sprite/npc/Goompa.h"
#include "sprite/npc/BattleWatt.h"
#include "sprite/npc/BattleSushie.h"
#include "sprite/npc/BattleLakilester.h"
#include "sprite/npc/BattleBow.h"
#include "sprite/player.h"

extern HudScript HES_ProjectorBeam;
extern IconHudScriptPair gItemHudScripts[];

enum {
    // BTL_SUBSTATE_INIT                            = 0,
    BTL_SUBSTATE_LOAD_STAR_POINTS                   = 1,
    BTL_SUBSTATE_TALLY_STAR_POINTS                  = 2,
    BTL_SUBSTATE_POST_STAR_POINTS                   = 3,
    BTL_SUBSTATE_LEVEL_UP_LOAD                      = 4,
    BTL_SUBSTATE_LEVEL_UP_BEGIN                     = 5,
    BTL_SUBSTATE_LEVEL_UP_CREATE_HUD                = 6,
    BTL_SUBSTATE_LEVEL_UP_SHOW_HUD                  = 7,
    BTL_SUBSTATE_LEVEL_UP_CHOOSE                    = 8,
    BTL_SUBSTATE_LEVEL_UP_UPGRADE                   = 9,
    BTL_SUBSTATE_LEVEL_UP_FADE_OUT                  = 10,
    BTL_SUBSTATE_LEVEL_UP_DESTROY_HUD               = 11,
    BTL_SUBSTATE_LEVEL_UP_INVALID                   = 15,
    BTL_SUBSTATE_LEVEL_UP_INVALID_DELAY             = 16,
    BTL_SUBSTATE_SKIPPABLE_END_DELAY                = 20,
    BTL_SUBSTATE_WALK_AWAY                          = 21,
    BTL_SUBSTATE_DONE                               = 22,
};

// menu position index for level up screen
enum {
    MENU_HP  = 0,
    MENU_FP  = 1,
    MENU_BP  = 2,
};

// first index for LevelUpStatTextIDs
enum {
    LVL_UP_FP  = 0,
    LVL_UP_HP  = 1,
    LVL_UP_BP  = 2,
};

// second index for LevelUpStatTextIDs
enum {
    LVL_UP_TITLE        = 0,
    LVL_UP_CUR_TENS     = 1,
    LVL_UP_CUR_ONES     = 2,
    LVL_UP_ARROW        = 3,
    LVL_UP_NEXT_TENS    = 4,
    LVL_UP_NEXT_ONES    = 5,
    LVL_UP_BONUS        = 6,
};

BSS HudElemID LevelUpStatEmblemIDs[4];
BSS HudElemID LevelUpStatTextIDs[3][7];
BSS HudElemID LevelUpSpotlightID;
BSS HudElemID LevelUpSelectTextID;

BSS s32 CelebrateSubstateTime;
BSS s32 D_8029FB50;
BSS s32 EndBattleRewardStep;
BSS s32 CantLevelUpStat[3];
BSS s32 EndBattleRewardTotal;
BSS s32 EndBattleRewardIncrement;
BSS s32 pendingLevelUps;
BSS s32 EndBattleRewardsDone;
BSS Evt* LevelUpScriptPtr;
BSS s32 LevelUpScriptID;
BSS s32 CelebrateStateTime;
BSS s32 LevelUpSelectTextOffsetX;
BSS s32 LevelUpSelectTextVelX;

extern EntityModelScript EMS_starpoint_starpoint;
extern EntityModelScript EMS_starpoint_starpoints;
extern EntityModelScript EMS_starpoint_digit_0;
extern EntityModelScript EMS_starpoint_digit_1;
extern EntityModelScript EMS_starpoint_digit_2;
extern EntityModelScript EMS_starpoint_digit_3;
extern EntityModelScript EMS_starpoint_digit_4;
extern EntityModelScript EMS_starpoint_digit_5;
extern EntityModelScript EMS_starpoint_digit_6;
extern EntityModelScript EMS_starpoint_digit_7;
extern EntityModelScript EMS_starpoint_digit_8;
extern EntityModelScript EMS_starpoint_digit_9;
extern EntityModelScript EMS_starpoint_dummy;

extern EntityModelScript EMS_level_up;

extern HudScript HES_level_up_flower;
extern HudScript HES_level_up_leaves;
extern HudScript HES_level_up_heart;
extern HudScript HES_level_up_heart_copy;
extern HudScript HES_level_up_badge;

extern HudScript HES_level_up_FP;
extern HudScript HES_level_up_HP;
extern HudScript HES_level_up_BP;

extern HudScript HES_level_up_green_digit_0;
extern HudScript HES_level_up_green_digit_1;
extern HudScript HES_level_up_green_digit_2;
extern HudScript HES_level_up_green_digit_3;
extern HudScript HES_level_up_green_digit_4;
extern HudScript HES_level_up_green_digit_5;
extern HudScript HES_level_up_green_digit_6;
extern HudScript HES_level_up_green_digit_7;
extern HudScript HES_level_up_green_digit_8;
extern HudScript HES_level_up_green_digit_9;
extern HudScript HES_level_up_red_digit_0;
extern HudScript HES_level_up_red_digit_1;
extern HudScript HES_level_up_red_digit_2;
extern HudScript HES_level_up_red_digit_3;
extern HudScript HES_level_up_red_digit_4;
extern HudScript HES_level_up_red_digit_5;
extern HudScript HES_level_up_red_digit_6;
extern HudScript HES_level_up_red_digit_7;
extern HudScript HES_level_up_red_digit_8;
extern HudScript HES_level_up_red_digit_9;
extern HudScript HES_level_up_blue_digit_0;
extern HudScript HES_level_up_blue_digit_1;
extern HudScript HES_level_up_blue_digit_2;
extern HudScript HES_level_up_blue_digit_3;
extern HudScript HES_level_up_blue_digit_4;
extern HudScript HES_level_up_blue_digit_5;
extern HudScript HES_level_up_blue_digit_6;
extern HudScript HES_level_up_blue_digit_7;
extern HudScript HES_level_up_blue_digit_8;
extern HudScript HES_level_up_blue_digit_9;

extern HudScript HES_level_up_small_green_digit_0;
extern HudScript HES_level_up_small_green_digit_1;
extern HudScript HES_level_up_small_green_digit_2;
extern HudScript HES_level_up_small_green_digit_3;
extern HudScript HES_level_up_small_green_digit_4;
extern HudScript HES_level_up_small_green_digit_5;
extern HudScript HES_level_up_small_green_digit_6;
extern HudScript HES_level_up_small_green_digit_7;
extern HudScript HES_level_up_small_green_digit_8;
extern HudScript HES_level_up_small_green_digit_9;
extern HudScript HES_level_up_small_green_arrow;
extern HudScript HES_level_up_small_red_digit_0;
extern HudScript HES_level_up_small_red_digit_1;
extern HudScript HES_level_up_small_red_digit_2;
extern HudScript HES_level_up_small_red_digit_3;
extern HudScript HES_level_up_small_red_digit_4;
extern HudScript HES_level_up_small_red_digit_5;
extern HudScript HES_level_up_small_red_digit_6;
extern HudScript HES_level_up_small_red_digit_7;
extern HudScript HES_level_up_small_red_digit_8;
extern HudScript HES_level_up_small_red_digit_9;
extern HudScript HES_level_up_small_red_arrow;
extern HudScript HES_level_up_small_blue_digit_0;
extern HudScript HES_level_up_small_blue_digit_1;
extern HudScript HES_level_up_small_blue_digit_2;
extern HudScript HES_level_up_small_blue_digit_3;
extern HudScript HES_level_up_small_blue_digit_4;
extern HudScript HES_level_up_small_blue_digit_5;
extern HudScript HES_level_up_small_blue_digit_6;
extern HudScript HES_level_up_small_blue_digit_7;
extern HudScript HES_level_up_small_blue_digit_8;
extern HudScript HES_level_up_small_blue_digit_9;
extern HudScript HES_level_up_small_blue_arrow;

extern HudScript HES_level_up_select_one_to_upgrade;

s32 bFadeToBlackAmt = 255;

s32 D_80284154[] = {
    [PARTNER_NONE]          = 0,
    [PARTNER_GOOMBARIO]     = ANIM_BattleGoombario_Walk,
    [PARTNER_KOOPER]        = ANIM_BattleKooper_Walk,
    [PARTNER_BOMBETTE]      = ANIM_BattleBombette_Walk,
    [PARTNER_PARAKARRY]     = ANIM_BattleParakarry_Walk,
    [PARTNER_GOOMPA]        = ANIM_Goompa_Walk,
    [PARTNER_WATT]          = ANIM_BattleWatt_Walk,
    [PARTNER_SUSHIE]        = ANIM_BattleSushie_Walk,
    [PARTNER_LAKILESTER]    = ANIM_BattleLakilester_Walk,
    [PARTNER_BOW]           = ANIM_BattleBow_Walk,
    [PARTNER_GOOMBARIA]     = 0,
    [PARTNER_TWINK]         = 0,
};

EntityModelScript* starpoint_digit_scripts[] = {
    &EMS_starpoint_digit_0,
    &EMS_starpoint_digit_1,
    &EMS_starpoint_digit_2,
    &EMS_starpoint_digit_3,
    &EMS_starpoint_digit_4,
    &EMS_starpoint_digit_5,
    &EMS_starpoint_digit_6,
    &EMS_starpoint_digit_7,
    &EMS_starpoint_digit_8,
    &EMS_starpoint_digit_9,
};

EntityModelScript* starpoint_space_script = &EMS_starpoint_dummy;

HudScript* levelup_stat_scripts[3] = {
    &HES_level_up_FP,
    &HES_level_up_HP,
    &HES_level_up_BP,
};

HudScript* HES_LevelUpDigits[3][10] = {
    {
        &HES_level_up_green_digit_0,
        &HES_level_up_green_digit_1,
        &HES_level_up_green_digit_2,
        &HES_level_up_green_digit_3,
        &HES_level_up_green_digit_4,
        &HES_level_up_green_digit_5,
        &HES_level_up_green_digit_6,
        &HES_level_up_green_digit_7,
        &HES_level_up_green_digit_8,
        &HES_level_up_green_digit_9,
    },
    {
        &HES_level_up_red_digit_0,
        &HES_level_up_red_digit_1,
        &HES_level_up_red_digit_2,
        &HES_level_up_red_digit_3,
        &HES_level_up_red_digit_4,
        &HES_level_up_red_digit_5,
        &HES_level_up_red_digit_6,
        &HES_level_up_red_digit_7,
        &HES_level_up_red_digit_8,
        &HES_level_up_red_digit_9,
    },
    {
        &HES_level_up_blue_digit_0,
        &HES_level_up_blue_digit_1,
        &HES_level_up_blue_digit_2,
        &HES_level_up_blue_digit_3,
        &HES_level_up_blue_digit_4,
        &HES_level_up_blue_digit_5,
        &HES_level_up_blue_digit_6,
        &HES_level_up_blue_digit_7,
        &HES_level_up_blue_digit_8,
        &HES_level_up_blue_digit_9,
    },
};

HudScript* level_up_small_digit_scripts[3][10] = {
    {
        &HES_level_up_small_green_digit_0,
        &HES_level_up_small_green_digit_1,
        &HES_level_up_small_green_digit_2,
        &HES_level_up_small_green_digit_3,
        &HES_level_up_small_green_digit_4,
        &HES_level_up_small_green_digit_5,
        &HES_level_up_small_green_digit_6,
        &HES_level_up_small_green_digit_7,
        &HES_level_up_small_green_digit_8,
        &HES_level_up_small_green_digit_9,
    },
    {
        &HES_level_up_small_red_digit_0,
        &HES_level_up_small_red_digit_1,
        &HES_level_up_small_red_digit_2,
        &HES_level_up_small_red_digit_3,
        &HES_level_up_small_red_digit_4,
        &HES_level_up_small_red_digit_5,
        &HES_level_up_small_red_digit_6,
        &HES_level_up_small_red_digit_7,
        &HES_level_up_small_red_digit_8,
        &HES_level_up_small_red_digit_9,
    },
    {
        &HES_level_up_small_blue_digit_0,
        &HES_level_up_small_blue_digit_1,
        &HES_level_up_small_blue_digit_2,
        &HES_level_up_small_blue_digit_3,
        &HES_level_up_small_blue_digit_4,
        &HES_level_up_small_blue_digit_5,
        &HES_level_up_small_blue_digit_6,
        &HES_level_up_small_blue_digit_7,
        &HES_level_up_small_blue_digit_8,
        &HES_level_up_small_blue_digit_9,
    },
};

s32* virtual_entity_get_by_index(s32);

void draw_content_level_up_textbox(void* data, s32 posX, s32 posY);
void draw_content_cant_increase_popup(void* data, s32 posX, s32 posY);

API_CALLABLE(GetRemainingStarPointsReward) {
    script->varTable[0] = (s8)gBattleStatus.totalStarPoints;
    return ApiStatus_DONE2;
}

API_CALLABLE(GetStarPointDigitScripts) {
    s32 levelUp = false;

    script->varTable[10] = gBattleStatus.totalStarPoints / 100; // star points in hundreds (levels to gain)
    script->varTable[11] = (gBattleStatus.totalStarPoints % 100) / 10; // star points in tens
    script->varTable[12] = gBattleStatus.totalStarPoints % 10; // star points in ones

    if (script->varTable[10] > 0) {
        script->varTablePtr[10].p = starpoint_digit_scripts[script->varTable[10]];
        levelUp = true;
    } else {
        script->varTablePtr[10].p = starpoint_space_script;
    }

    if ((script->varTable[11] > 0) || levelUp) {
        script->varTablePtr[11].p = starpoint_digit_scripts[script->varTable[11]];
    } else {
        script->varTablePtr[11].p = starpoint_space_script;
    }

    script->varTablePtr[12].p = starpoint_digit_scripts[script->varTable[12]];
    return ApiStatus_DONE2;
}

API_CALLABLE(AwaitBattleRewardsDone) {
    if (EndBattleRewardsDone) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

API_CALLABLE(InitStarPointModelFlags) {
    EntityModel* model;

    model = get_entity_model(*virtual_entity_get_by_index(script->varTable[6]));
    model->flags &= ~MODEL_FLAGS_MASK_FFF0 ;
    model->flags |= MODEL_FLAG_TRANSFORM_GROUP_MEMBER;
    model = get_entity_model(*virtual_entity_get_by_index(script->varTable[7]));
    model->flags &= ~MODEL_FLAGS_MASK_FFF0 ;
    model->flags |= MODEL_FLAG_TRANSFORM_GROUP_MEMBER;
    model = get_entity_model(*virtual_entity_get_by_index(script->varTable[8]));
    model->flags &= ~MODEL_FLAGS_MASK_FFF0 ;
    model->flags |= MODEL_FLAG_TRANSFORM_GROUP_MEMBER;
    model = get_entity_model(*virtual_entity_get_by_index(script->varTable[9]));
    model->flags &= ~MODEL_FLAGS_MASK_FFF0 ;
    model->flags |= MODEL_FLAG_TRANSFORM_GROUP_MEMBER;

    return ApiStatus_DONE2;
}

API_CALLABLE(InitLevelUpModelFlags) {
    EntityModel* model = get_entity_model(*virtual_entity_get_by_index(script->varTable[9]));
    model->flags &= ~MODEL_FLAGS_MASK_FFF0;
    model->flags |= MODEL_FLAG_TRANSFORM_GROUP_MEMBER;

    return ApiStatus_DONE2;
}

API_CALLABLE(MakeLevelUpConfetti) {
    fx_confetti(3, 0.0f, 100.0f, 0.0f, 1.0f, 120);
    return ApiStatus_DONE2;
}

EvtScript EVS_ShowStarpoints = {
    Set(LVarF, 0)
    Call(GetRemainingStarPointsReward)
    IfEq(LVar0, 0)
        Return
    EndIf
    IfLt(LVar0, 2)
        Call(CreateVirtualEntity, LVar6, Ref(EMS_starpoint_starpoint))
        Call(SetVirtualEntityPosition, LVar6, -278, 68, 70)
        Call(SetVirtualEntityScale, LVar6, Float(0.5), Float(0.5), Float(0.5))
    Else
#if VERSION_JP
        Call(CreateVirtualEntity, LVar6, Ref(EMS_starpoint_starpoint))
#else
        Call(CreateVirtualEntity, LVar6, Ref(EMS_starpoint_starpoints))
#endif
        Call(SetVirtualEntityPosition, LVar6, -278, 68, 70)
        Call(SetVirtualEntityScale, LVar6, Float(0.5), Float(0.5), Float(0.5))
        Set(LFlag0, true)
    EndIf
    Switch(LVar0)
        CaseGt(99)
            Set(LVarF, 3)
        CaseGt(9)
            Set(LVarF, 2)
        CaseDefault
            Set(LVarF, 1)
    EndSwitch
    Call(GetStarPointDigitScripts)
    Call(CreateVirtualEntity, LVar7, LVarA)
    Call(SetVirtualEntityPosition, LVar7, -353, 68, 70)
    Call(SetVirtualEntityScale, LVar7, Float(0.5), Float(0.5), Float(0.5))
    Call(CreateVirtualEntity, LVar8, LVarB)
    Call(SetVirtualEntityPosition, LVar8, -338, 68, 70)
    Call(SetVirtualEntityScale, LVar8, Float(0.5), Float(0.5), Float(0.5))
    Call(CreateVirtualEntity, LVar9, LVarC)
    Call(SetVirtualEntityPosition, LVar9, -323, 68, 70)
    Call(SetVirtualEntityScale, LVar9, Float(0.5), Float(0.5), Float(0.5))
    Call(InitStarPointModelFlags)
    Switch(LVarF)
        CaseEq(3)
            Set(LVar0, -197)
        CaseEq(2)
            Set(LVar0, -204)
        CaseEq(1)
            Set(LVar0, -211)
    EndSwitch
    Loop(10)
        Add(LVar0, 20)
        Set(LVar1, LVar0)
        Add(LVar1, -78)
        Call(SetVirtualEntityPosition, LVar6, LVar1, 68, 70)
        Set(LVar1, LVar0)
#if VERSION_JP
        Add(LVar1, -154)
#else
        Add(LVar1, -146)
#endif
        Call(SetVirtualEntityPosition, LVar7, LVar1, 68, 70)
        Set(LVar1, LVar0)
#if VERSION_JP
        Add(LVar1, -139)
#else
        Add(LVar1, -131)
#endif
        Call(SetVirtualEntityPosition, LVar8, LVar1, 68, 70)
        Set(LVar1, LVar0)
#if VERSION_JP
        Add(LVar1, -124)
#else
        Add(LVar1, -116)
#endif
        Call(SetVirtualEntityPosition, LVar9, LVar1, 68, 70)
        Wait(1)
    EndLoop
    Call(AwaitBattleRewardsDone)
    Switch(LVarF)
        CaseEq(3)
            Set(LVar0, 3)
        CaseEq(2)
            Set(LVar0, -4)
        CaseEq(1)
            Set(LVar0, -11)
    EndSwitch
    Loop(10)
        Add(LVar0, 20)
        Set(LVar1, LVar0)
        Add(LVar1, -78)
        Call(SetVirtualEntityPosition, LVar6, LVar1, 68, 70)
        Set(LVar1, LVar0)
        Add(LVar1, -154)
        Call(SetVirtualEntityPosition, LVar7, LVar1, 68, 70)
        Set(LVar1, LVar0)
        Add(LVar1, -139)
        Call(SetVirtualEntityPosition, LVar8, LVar1, 68, 70)
        Set(LVar1, LVar0)
        Add(LVar1, -124)
        Call(SetVirtualEntityPosition, LVar9, LVar1, 68, 70)
        Wait(1)
    EndLoop
    Call(DeleteVirtualEntity, LVar6)
    Call(DeleteVirtualEntity, LVar7)
    Call(DeleteVirtualEntity, LVar8)
    Call(DeleteVirtualEntity, LVar9)
    Return
    End
};

EvtScript EVS_ShowLevelUp = {
    Call(CreateVirtualEntity, LVar9, Ref(EMS_level_up))
    Call(SetVirtualEntityPosition, LVar9, 0, 210, 70)
    Call(InitLevelUpModelFlags)
    ChildThread
        Wait(4)
        Call(MakeLevelUpConfetti)
    EndChildThread
    Thread
        Wait(8)
        Call(ShakeCam, 1, 0, 5, Float(3.0))
        Call(ShakeCam, 1, 0, 3, Float(2.25))
        Call(ShakeCam, 1, 0, 4, Float(1.2))
        Call(ShakeCam, 1, 0, 6, Float(0.45))
        Call(ShakeCam, 1, 0, 8, Float(0.15))
    EndThread
    Thread
        Set(LVar0, 210)
        Loop(10)
            Sub(LVar0, 10)
            Call(SetVirtualEntityPosition, LVar9, 0, LVar0, 70)
            Wait(1)
        EndLoop
    EndThread
    Wait(8)
    Return
    End
};

void btl_state_update_celebration(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    s8 currentSubmenu;
    s32 newSubmenu;
    HudElemID hid;
    s32 x, y, z;
    s32 width;
    s32 itemHudElemID;

    Evt* script;

    s32 tensDigit;
    s32 onesDigit;

    s32 deltaSP;
    s32 prevSP;

    s32 i;
    s32 j;


    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            if (battleStatus->pendingStarPoints <= 0) {
                player->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
                BattleCelebration celebration = { battleStatus->totalStarPoints, ANIM_MarioB1_AdjustCap, 4.0f, 4.0f };
                {
                    CALL_EVENT(OnBattleCelebration, BATTLE_CELEBRATION_AWARD, &celebration);
                    if (celebration.starPoints > 127) {
                        celebration.starPoints = 127;
                    } else if (celebration.starPoints < 0) {
                        celebration.starPoints = 0;
                    }
                    battleStatus->totalStarPoints = celebration.starPoints;
                }
                EndBattleRewardTotal = battleStatus->totalStarPoints * 100;
                pendingLevelUps = 0;
                D_8029FB50 = 0;
                bFadeToBlackAmt = 0;
                LevelUpSelectTextOffsetX = 0;
                LevelUpSelectTextVelX = 0;
                {
                    CALL_CANCELLABLE_EVENT(OnBattleCelebration, BATTLE_CELEBRATION_JINGLE, &celebration) {
                        sfx_play_sound(SOUND_JINGLE_WON_BATTLE);
                    }
                }

                prevSP = playerData->starPoints + battleStatus->totalStarPoints;
                if (prevSP > 99) {
                    bgm_set_song(0, SONG_LEVEL_UP, 0, 250, 8);
                } else {
                    bgm_set_song(0, SONG_BATTLE_END, 0, 250, 8);
                }

                CelebrateStateTime = 0;
                btl_cam_use_preset(BTL_CAM_VICTORY);
                EndBattleRewardStep = 0;
                CelebrateSubstateTime = 1;
                gBattleSubState = BTL_SUBSTATE_LOAD_STAR_POINTS;
                gBattleStatus.flags2 |= BS_FLAGS2_AWARDING_STAR_POINTS;
            }
            break;
        case BTL_SUBSTATE_LOAD_STAR_POINTS:
            if (CelebrateSubstateTime != 0) {
                CelebrateSubstateTime--;
            } else if (btl_cam_is_moving_done()) {
                DMA_COPY_SEGMENT(starpoint);
                script = start_script(&EVS_ShowStarpoints, EVT_PRIORITY_A, 0);
                EndBattleRewardsDone = false;
                // divide reward into 20 increments
                EndBattleRewardStep = 20;
                EndBattleRewardIncrement = EndBattleRewardTotal / EndBattleRewardStep;
                player->takeTurnScript = script;
                CelebrateSubstateTime = 1;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
                gBattleSubState = BTL_SUBSTATE_TALLY_STAR_POINTS;
            }
            break;
        case BTL_SUBSTATE_TALLY_STAR_POINTS:
            if (CelebrateSubstateTime == 0) {
                if (battleStatus->totalStarPoints != 0) {
                    // determine the remaining star point reward after this step and give the difference to the player
                    EndBattleRewardTotal -= EndBattleRewardIncrement;
                    prevSP = battleStatus->totalStarPoints;
                    battleStatus->totalStarPoints = EndBattleRewardTotal / 100;
                    deltaSP = prevSP - battleStatus->totalStarPoints;
                    if (deltaSP > 0) {
                        sfx_play_sound(SOUND_STAR_POINT_PICKUP);
                    }

                    playerData->starPoints += deltaSP;
                    bFadeToBlackAmt++; // ??
                    if (EndBattleRewardStep == 0 && battleStatus->totalStarPoints != 0) {
                        playerData->starPoints++;
                    }
                }
                StatLimits spLimits = STAT_LIMITS_VANILLA;
                CALL_EVENT(OnStatLimits, &spLimits);
                if (playerData->level >= spLimits.levelCap) {
                    playerData->starPoints = 0;
                }
                if (playerData->starPoints >= 100) {
                    pendingLevelUps = 1;
                    playerData->starPoints -= 100;
                }
                if (playerData->level + pendingLevelUps == spLimits.levelCap) {
                    playerData->starPoints = 0;
                }
                if (battleStatus->totalStarPoints == 0) {
                    if (EndBattleRewardStep == 0) {
                        EndBattleRewardsDone = true;
                        player->flags &= ~(ACTOR_FLAG_USING_IDLE_ANIM | ACTOR_FLAG_SHOW_STATUS_ICONS);
                        if (partner != nullptr) {
                            partner->flags &= ~(ACTOR_FLAG_USING_IDLE_ANIM | ACTOR_FLAG_SHOW_STATUS_ICONS);
                        }
                        battleStatus->battlePhase = PHASE_CELEBRATE;
                        script = start_script(&EVS_Mario_HandlePhase, EVT_PRIORITY_A, 0);
                        player->takeTurnScript = script;
                        player->takeTurnScriptID = script->id;
                        script->owner1.actorID = ACTOR_PLAYER;
                        if (partner != nullptr) {
                            script = start_script(partner->takeTurnSource, EVT_PRIORITY_A, 0);
                            partner->takeTurnScript = script;
                            partner->takeTurnScriptID = script->id;
                            script->owner1.actorID = ACTOR_PARTNER;
                        }
                        CelebrateSubstateTime = 40;
                        gBattleSubState = BTL_SUBSTATE_POST_STAR_POINTS;
                    } else {
                        EndBattleRewardStep--;
                    }
                }
            } else {
                CelebrateSubstateTime--;
            }
            break;
        case BTL_SUBSTATE_POST_STAR_POINTS:
            if (CelebrateSubstateTime == 0) {
                if (pendingLevelUps == 0) {
                    gBattleSubState = BTL_SUBSTATE_SKIPPABLE_END_DELAY;
                } else {
                    gBattleSubState = BTL_SUBSTATE_LEVEL_UP_LOAD;
                }
                break;
            }
            CelebrateSubstateTime--;
            break;
        case BTL_SUBSTATE_LEVEL_UP_LOAD:
            if (CelebrateStateTime >= 99) {
                playerData->level++;
                btl_cam_use_preset(BTL_CAM_DEFAULT);
                btl_cam_move(5);
                DMA_COPY_SEGMENT(level_up);
                sfx_play_sound(SOUND_LOOP_CHEERING);
                CelebrateStateTime = 0;
                gBattleSubState = BTL_SUBSTATE_LEVEL_UP_BEGIN;
            }
            break;
        case BTL_SUBSTATE_LEVEL_UP_BEGIN:
            LevelUpScriptPtr = start_script(&EVS_ShowLevelUp, EVT_PRIORITY_A, 0);
            LevelUpScriptID = LevelUpScriptPtr->id;
            CelebrateSubstateTime = 25;
            gBattleSubState = BTL_SUBSTATE_LEVEL_UP_CREATE_HUD;
            mdl_set_all_tint_type(ENV_TINT_SHROUD);
            *gBackgroundTintModePtr = ENV_TINT_SHROUD;
            mdl_set_shroud_tint_params(0, 0, 0, 0);
            break;
        case BTL_SUBSTATE_LEVEL_UP_CREATE_HUD:
            if (CelebrateSubstateTime == 18) {
                {
                    s32 delta = playerData->curMaxHP - playerData->curHP;
                    CALL_CANCELLABLE_EVENT(OnActorHpChange, player, HP_SOURCE_LEVEL_UP, &delta) {
                        playerData->curHP += delta;
                    }
                }
                playerData->curFP = playerData->curMaxFP;
                x = player->curPos.x + 0.0f;
                y = player->curPos.y + 35.0f;
                z = player->curPos.z;
                fx_recover(0, x, y, z, playerData->curHP);
                x = player->curPos.x + 20.0f;
                y = player->curPos.y + 25.0f;
                z = player->curPos.z;
                fx_recover(1, x, y, z, playerData->curFP);
                playerData->starPower = playerData->maxStarPower * SP_PER_BAR;
            }

            if (CelebrateSubstateTime != 0) {
                CelebrateSubstateTime--;
                if (CelebrateSubstateTime < 10) {
                    mdl_set_shroud_tint_params(0, 0, 0, ((10 - CelebrateSubstateTime) * 16) & 0xF0);
                }
            } else {
                hid = hud_element_create(&HES_level_up_heart);
                LevelUpStatEmblemIDs[0] = hid;
                hud_element_set_render_pos(hid, 310, 140);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);

                hid = hud_element_create(&HES_level_up_flower);
                LevelUpStatEmblemIDs[1] = hid;
                hud_element_set_render_pos(hid, 158, 340);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);

                hid = hud_element_create(&HES_level_up_leaves);
                LevelUpStatEmblemIDs[3] = hid;
                hud_element_set_render_pos(hid, 158, 340);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);

                hid = hud_element_create(&HES_level_up_badge);
                LevelUpStatEmblemIDs[2] = hid;
                hud_element_set_render_pos(hid, 6, 140);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);

                hid = hud_element_create(levelup_stat_scripts[0]);
                LevelUpStatTextIDs[LVL_UP_FP][LVL_UP_TITLE] = hid;
                hud_element_set_render_pos(hid, 160, 317);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);

                for (i = 1; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_FP]); i++) {
                    hid = hud_element_create(HES_LevelUpDigits[LVL_UP_FP][0]);
                    LevelUpStatTextIDs[LVL_UP_FP][i] = hid;
                    hud_element_set_render_pos(hid, 160, 317);
                    hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER | HUD_ELEMENT_FLAG_DISABLED);
                }

                hid = hud_element_create(levelup_stat_scripts[1]);
                LevelUpStatTextIDs[LVL_UP_HP][LVL_UP_TITLE] = hid;
                hud_element_set_render_pos(hid, 312, 117);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);

                for (i = 1; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_HP]); i++) {
                    hid = hud_element_create(HES_LevelUpDigits[LVL_UP_HP][0]);
                    LevelUpStatTextIDs[LVL_UP_HP][i] = hid;
                    hud_element_set_render_pos(hid, 312, 117);
                    hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER | HUD_ELEMENT_FLAG_DISABLED);
                }

                hid = hud_element_create(levelup_stat_scripts[2]);
                LevelUpStatTextIDs[LVL_UP_BP][LVL_UP_TITLE] = hid;
                hud_element_set_render_pos(hid, 8, 117);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);

                for (i = 1; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_BP]); i++) {
                    hid = hud_element_create(HES_LevelUpDigits[LVL_UP_BP][0]);
                    LevelUpStatTextIDs[LVL_UP_BP][i] = hid;
                    hud_element_set_render_pos(hid, 8, 117);
                    hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER | HUD_ELEMENT_FLAG_DISABLED);
                }

                CantLevelUpStat[MENU_HP] = false;
                CantLevelUpStat[MENU_FP] = false;
                CantLevelUpStat[MENU_BP] = false;

                StatLimits menuLimits = STAT_LIMITS_VANILLA;
                CALL_EVENT(OnStatLimits, &menuLimits);
                if (playerData->hardMaxFP != menuLimits.levelUpHpFpCap) {
                    // current FP
                    tensDigit = playerData->curMaxFP / 10;
                    onesDigit = playerData->curMaxFP % 10;
                    hid = LevelUpStatTextIDs[LVL_UP_FP][LVL_UP_CUR_TENS];
                    hud_element_set_script(hid, level_up_small_digit_scripts[LVL_UP_FP][tensDigit]);
                    if (tensDigit != 0) {
                        hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    }
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x - 14, y + 46);

                    hid = LevelUpStatTextIDs[LVL_UP_FP][LVL_UP_CUR_ONES];
                    hud_element_set_script(hid, level_up_small_digit_scripts[LVL_UP_FP][onesDigit]);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x - 8, y + 46);

                    hid = LevelUpStatTextIDs[LVL_UP_FP][LVL_UP_ARROW];
                    hud_element_set_script(hid, &HES_level_up_small_green_arrow);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x - 3, y + 46);

                    // upgraded FP
                    s32 nextFP = playerData->curMaxFP + 5;
                    if (nextFP > 99) {
                        nextFP = 99;
                    }
                    tensDigit = nextFP / 10;
                    onesDigit = nextFP % 10;
                    hid = LevelUpStatTextIDs[LVL_UP_FP][LVL_UP_NEXT_TENS];
                    hud_element_set_script(hid, HES_LevelUpDigits[LVL_UP_FP][tensDigit]);
                    if (tensDigit != 0) {
                        hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    }
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x + 3, y + 46);

                    hid = LevelUpStatTextIDs[LVL_UP_FP][LVL_UP_NEXT_ONES];
                    hud_element_set_script(hid, HES_LevelUpDigits[LVL_UP_FP][onesDigit]);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x + 10, y + 46);
                } else {
                    // upgraded FP only
                    hid = LevelUpStatTextIDs[LVL_UP_FP][LVL_UP_NEXT_TENS];
                    tensDigit = playerData->curMaxFP / 10;
                    onesDigit = playerData->curMaxFP % 10;
                    hud_element_set_script(hid, HES_LevelUpDigits[LVL_UP_FP][tensDigit]);
                    if (tensDigit != 0) {
                        hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    }
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x - 6, y + 46);

                    hid = LevelUpStatTextIDs[LVL_UP_FP][LVL_UP_NEXT_ONES];
                    hud_element_set_script(hid, HES_LevelUpDigits[LVL_UP_FP][onesDigit]);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x + 2, y + 46);
                    CantLevelUpStat[MENU_FP] = true;
                }

                if (is_ability_active(ABILITY_FP_PLUS)) {
                    hid = LevelUpStatTextIDs[LVL_UP_FP][LVL_UP_BONUS];
                    itemHudElemID = gItemTable[ITEM_FP_PLUS_A].hudElemID;
                    hud_element_set_script(hid, gItemHudScripts[itemHudElemID].enabled);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    hud_element_set_scale(hid, 0.5f);
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x + 17, y + 46);
                }

                if (playerData->hardMaxHP != menuLimits.levelUpHpFpCap) {
                    // current HP
                    tensDigit = playerData->curMaxHP / 10;
                    onesDigit = playerData->curMaxHP % 10;

                    hid = LevelUpStatTextIDs[LVL_UP_HP][LVL_UP_CUR_TENS];
                    hud_element_set_script(hid, level_up_small_digit_scripts[LVL_UP_HP][tensDigit]);
                    if (tensDigit != 0) {
                        hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    }
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x - 14, y + 46);

                    hid = LevelUpStatTextIDs[LVL_UP_HP][LVL_UP_CUR_ONES];
                    hud_element_set_script(hid, level_up_small_digit_scripts[LVL_UP_HP][onesDigit]);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x - 8, y + 46);

                    hid = LevelUpStatTextIDs[LVL_UP_HP][LVL_UP_ARROW];
                    hud_element_set_script(hid, &HES_level_up_small_red_arrow);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x - 3, y + 46);

                    s32 nextHP = playerData->curMaxHP + 5;
                    if (nextHP > 99) {
                        nextHP = 99;
                    }
                    tensDigit = nextHP / 10;
                    onesDigit = nextHP % 10;

                    hid = LevelUpStatTextIDs[LVL_UP_HP][LVL_UP_NEXT_TENS];
                    hud_element_set_script(hid, HES_LevelUpDigits[LVL_UP_HP][tensDigit]);
                    if (tensDigit != 0) {
                        hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    }
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x + 3, y + 46);

                    hid = LevelUpStatTextIDs[LVL_UP_HP][LVL_UP_NEXT_ONES];
                    hud_element_set_script(hid, HES_LevelUpDigits[LVL_UP_HP][onesDigit]);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x + 10, y + 46);
                } else {
                    tensDigit = playerData->curMaxHP / 10;
                    onesDigit = playerData->curMaxHP % 10;

                    hid = LevelUpStatTextIDs[LVL_UP_HP][LVL_UP_NEXT_TENS];
                    hud_element_set_script(hid, HES_LevelUpDigits[LVL_UP_HP][tensDigit]);
                    if (tensDigit != 0) {
                        hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    }
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x - 6, y + 46);

                    hid = LevelUpStatTextIDs[LVL_UP_HP][LVL_UP_NEXT_ONES];
                    hud_element_set_script(hid, HES_LevelUpDigits[LVL_UP_HP][onesDigit]);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x + 2, y + 46);
                    CantLevelUpStat[MENU_HP] = true;
                }

                if (is_ability_active(ABILITY_HP_PLUS)) {
                    hid = LevelUpStatTextIDs[LVL_UP_HP][LVL_UP_BONUS];
                    itemHudElemID = gItemTable[ITEM_HP_PLUS_A].hudElemID;
                    hud_element_set_script(hid, gItemHudScripts[itemHudElemID].enabled);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    hud_element_set_scale(hid, 0.5f);
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x + 17, y + 46);
                }

                if (playerData->maxBP != menuLimits.bpCap) {
                    tensDigit = playerData->maxBP / 10;
                    onesDigit = playerData->maxBP % 10;

                    hid = LevelUpStatTextIDs[LVL_UP_BP][LVL_UP_CUR_TENS];
                    hud_element_set_script(hid, level_up_small_digit_scripts[LVL_UP_BP][tensDigit]);
                    if (tensDigit != 0) {
                        hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    }
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x - 14, y + 46);

                    hid = LevelUpStatTextIDs[LVL_UP_BP][LVL_UP_CUR_ONES];
                    hud_element_set_script(hid, level_up_small_digit_scripts[LVL_UP_BP][onesDigit]);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x - 8, y + 46);

                    hid = LevelUpStatTextIDs[LVL_UP_BP][LVL_UP_ARROW];
                    hud_element_set_script(hid, &HES_level_up_small_blue_arrow);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x - 3, y + 46);

                    tensDigit = (playerData->maxBP + 3) / 10;
                    onesDigit = (playerData->maxBP + 3) % 10;

                    hid = LevelUpStatTextIDs[LVL_UP_BP][LVL_UP_NEXT_TENS];
                    hud_element_set_script(hid, HES_LevelUpDigits[LVL_UP_BP][tensDigit]);
                    if (tensDigit != 0) {
                        hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    }
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x + 3, y + 46);

                    hid = LevelUpStatTextIDs[LVL_UP_BP][LVL_UP_NEXT_ONES];
                    hud_element_set_script(hid, HES_LevelUpDigits[LVL_UP_BP][onesDigit]);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x + 10, y + 46);
                } else {
                    s32 cappedValue = menuLimits.bpCap;
                    if (cappedValue > 99) {
                        cappedValue = 99;
                    }
                    hid = LevelUpStatTextIDs[LVL_UP_BP][LVL_UP_NEXT_TENS];
                    hud_element_set_script(hid, HES_LevelUpDigits[LVL_UP_BP][cappedValue / 10]);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x - 6, y + 46);

                    hid = LevelUpStatTextIDs[LVL_UP_BP][LVL_UP_NEXT_ONES];
                    hud_element_set_script(hid, HES_LevelUpDigits[LVL_UP_BP][cappedValue % 10]);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    hud_element_get_render_pos(hid, &x, &y);
                    hud_element_set_render_pos(hid, x + 2, y + 46);
                    CantLevelUpStat[MENU_BP] = true;
                }

                LevelUpSpotlightID = hid = hud_element_create(&HES_ProjectorBeam);
                hud_element_create_transform_B(hid);
                hud_element_set_render_pos(hid, 156, 13);
                hud_element_set_tint(hid, 255, 255, 255);
                hud_element_set_transform_rotation_pivot(hid, 0, -35);
                hud_element_set_transform_rotation(hid, 0.0f, 0.0f, 180.0f);
                hud_element_set_transform_scale(hid, 1.0f, 1.5f, 1.0f);
                hud_element_set_alpha(hid, 200);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX | HUD_ELEMENT_FLAG_MANUAL_RENDER);

                LevelUpSelectTextID = hid = hud_element_create(&HES_level_up_select_one_to_upgrade);
                hud_element_set_render_pos(hid, 0, 0);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);
                battleStatus->curSubmenu = MENU_FP;

                CelebrateSubstateTime = 10;
                gBattleSubState = BTL_SUBSTATE_LEVEL_UP_SHOW_HUD;
            }
            break;
        case BTL_SUBSTATE_LEVEL_UP_SHOW_HUD:
            hid = LevelUpStatEmblemIDs[0];
            hud_element_get_render_pos(hid, &x, &y);
            x -= 20;
            hud_element_set_render_pos(hid, x, y);

            for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_HP]); i++) {
                hid = LevelUpStatTextIDs[LVL_UP_HP][i];
                hud_element_get_render_pos(hid, &x, &y);
                x -= 20;
                hud_element_set_render_pos(hid, x, y);
            }

            hid = LevelUpStatEmblemIDs[1];
            hud_element_get_render_pos(hid, &x, &y);
            y -= 20;
            hud_element_set_render_pos(hid, x, y);

            hid = LevelUpStatEmblemIDs[3];
            hud_element_get_render_pos(hid, &x, &y);
            y -= 20;
            hud_element_set_render_pos(hid, x, y);

            for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_FP]); i++) {
                hid = LevelUpStatTextIDs[LVL_UP_FP][i];
                hud_element_get_render_pos(hid, &x, &y);
                y -= 20;
                hud_element_set_render_pos(hid, x, y);
            }

            hid = LevelUpStatEmblemIDs[2];
            hud_element_get_render_pos(hid, &x, &y);
            x += 20;
            hud_element_set_render_pos(hid, x, y);

            for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_BP]); i++) {
                hid = LevelUpStatTextIDs[LVL_UP_BP][i];
                hud_element_get_render_pos(hid, &x, &y);
                x += 20;
                hud_element_set_render_pos(hid, x, y);
            }

            CelebrateSubstateTime--;
            if (CelebrateSubstateTime == 0) {
                hud_element_set_tint(hid, 128, 128, 128);
#if VERSION_JP
                x = 32;
                y = 186;
                set_window_properties(WIN_BTL_DESC_BOX, 32, 186, 242, 32, WINDOW_PRIORITY_20, draw_content_level_up_textbox, nullptr, -1);
#else
                x = 20;
                y = 186;
                set_window_properties(WIN_BTL_DESC_BOX, 20, 186, 280, 32, WINDOW_PRIORITY_20, draw_content_level_up_textbox, nullptr, -1);
#endif
                set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
                gBattleSubState = BTL_SUBSTATE_LEVEL_UP_CHOOSE;
            }
            break;
        case BTL_SUBSTATE_LEVEL_UP_CHOOSE:
            if (battleStatus->curButtonsPressed & BUTTON_A) {
                if (!CantLevelUpStat[battleStatus->curSubmenu]) {
                    sfx_play_sound(SOUND_MENU_NEXT);
                    sfx_play_sound(SOUND_LRAW_CHEERING | SOUND_ID_TRIGGER_CHANGE_SOUND);
                    gBattleSubState = BTL_SUBSTATE_LEVEL_UP_UPGRADE;
                } else {
                    sfx_play_sound(SOUND_MENU_ERROR);
                    gBattleSubState = BTL_SUBSTATE_LEVEL_UP_INVALID;
                }
                break;
            }

            newSubmenu = currentSubmenu = battleStatus->curSubmenu;
            if (battleStatus->curButtonsHeld & BUTTON_STICK_LEFT) {
                newSubmenu--;
            }
            if (battleStatus->curButtonsHeld & BUTTON_STICK_RIGHT) {
                newSubmenu++;
            }
            if (newSubmenu < 0) {
                newSubmenu = 0;
            }
            if (newSubmenu > 2) {
                newSubmenu = 2;
            }
            if (newSubmenu != currentSubmenu) {
                sfx_play_sound(SOUND_MENU_CHANGE_SELECTION);
                battleStatus->curSubmenu = newSubmenu;
            }

            CelebrateStateTime++;
            if (CelebrateStateTime > 100) {
                fx_confetti(3, 0.0f, 100.0f, 0.0f, 1.0f, 120);
                CelebrateStateTime = 0;
            }
            break;
        case BTL_SUBSTATE_LEVEL_UP_UPGRADE:
            hud_element_free(LevelUpSpotlightID);
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);

            StatLimits upgradeLimits = STAT_LIMITS_VANILLA;
            CALL_EVENT(OnStatLimits, &upgradeLimits);
            switch (battleStatus->curSubmenu) {
                case 0:
                    playerData->hardMaxHP += 5;
                    playerData->curMaxHP += 5;
                    playerData->curHP += 5;
                    if (playerData->curMaxHP > upgradeLimits.levelUpHpFpClamp) {
                        playerData->curMaxHP = upgradeLimits.levelUpHpFpClamp;
                    }
                    if (playerData->curHP > playerData->curMaxHP) {
                        playerData->curHP = playerData->curMaxHP;
                    }
                    player->maxHP = playerData->curMaxHP;
                    player->curHP = playerData->curHP;
                    break;
                case 1:
                    playerData->hardMaxFP += 5;
                    playerData->curMaxFP += 5;
                    playerData->curFP += 5;
                    if (playerData->curMaxFP > upgradeLimits.levelUpHpFpClamp) {
                        playerData->curMaxFP = upgradeLimits.levelUpHpFpClamp;
                    }
                    if (playerData->curFP > playerData->curMaxFP) {
                        playerData->curFP = playerData->curMaxFP;
                    }
                    break;
                case 2:
                    playerData->maxBP += 3;
                    if (playerData->maxBP > upgradeLimits.bpCap) {
                        playerData->maxBP = upgradeLimits.bpCap;
                    }
                    break;
            }

            set_actor_anim(0, 0, ANIM_MarioB1_AdjustCap);

            if (partner != nullptr) {
                script = start_script(partner->takeTurnSource, EVT_PRIORITY_A, 0);
                partner->takeTurnScript = script;
                partner->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PARTNER;
            }
            if (!(gBattleStatus.flags2 & BS_FLAGS2_DONT_STOP_MUSIC)) {
                bgm_set_song(0, -1, 0, 2000, 8);
            }
            bFadeToBlackAmt = 0;
            gBattleSubState = BTL_SUBSTATE_LEVEL_UP_FADE_OUT;
            break;
        case BTL_SUBSTATE_LEVEL_UP_FADE_OUT:
            if ((gGameStatusPtr->frameCounter % 2) != 0) {
                switch (battleStatus->curSubmenu) {
                    case MENU_HP:
                        hud_element_set_flags(LevelUpStatEmblemIDs[0], HUD_ELEMENT_FLAG_DISABLED);
                        break;
                    case MENU_FP:
                        hud_element_set_flags(LevelUpStatEmblemIDs[1], HUD_ELEMENT_FLAG_DISABLED);
                        hud_element_set_flags(LevelUpStatEmblemIDs[3], HUD_ELEMENT_FLAG_DISABLED);
                        break;
                    case MENU_BP:
                        hud_element_set_flags(LevelUpStatEmblemIDs[2], HUD_ELEMENT_FLAG_DISABLED);
                        break;
                }
            } else {
                switch (battleStatus->curSubmenu) {
                    case MENU_HP:
                        hud_element_clear_flags(LevelUpStatEmblemIDs[0], HUD_ELEMENT_FLAG_DISABLED);
                        break;
                    case MENU_FP:
                        hud_element_clear_flags(LevelUpStatEmblemIDs[1], HUD_ELEMENT_FLAG_DISABLED);
                        hud_element_clear_flags(LevelUpStatEmblemIDs[3], HUD_ELEMENT_FLAG_DISABLED);
                        break;
                    case MENU_BP:
                        hud_element_clear_flags(LevelUpStatEmblemIDs[2], HUD_ELEMENT_FLAG_DISABLED);
                        break;
                }
            }
            if (bFadeToBlackAmt == 255) {
                gBattleSubState = BTL_SUBSTATE_LEVEL_UP_DESTROY_HUD;
                break;
            }
            bFadeToBlackAmt += 10;
            if (bFadeToBlackAmt > 255) {
                bFadeToBlackAmt = 255;
            }
            break;
        case BTL_SUBSTATE_LEVEL_UP_DESTROY_HUD:
            hud_element_free(LevelUpStatEmblemIDs[0]);
            hud_element_free(LevelUpStatEmblemIDs[1]);
            hud_element_free(LevelUpStatEmblemIDs[3]);
            hud_element_free(LevelUpStatEmblemIDs[2]);

            for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs); i++) {
                for (j = 0; j < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_FP]); j++) {
                    hud_element_free(LevelUpStatTextIDs[i][j]);
                }
            }

            hud_element_free(LevelUpSelectTextID);
            mdl_set_shroud_tint_params(0, 0, 0, 0);
            btl_set_state(BATTLE_STATE_END_BATTLE);
            gBattleSubState = BTL_SUBSTATE_END_BATTLE_EXEC_STAGE_SCRIPT;
            break;
        case BTL_SUBSTATE_LEVEL_UP_INVALID:
            width = get_msg_width(MSG_Menus_CantIncrease, 0) + 31;
            x = 160 - (width / 2);
            y = 80;
            set_window_properties(WIN_BTL_POPUP, x, y, width, 28, WINDOW_PRIORITY_10, draw_content_cant_increase_popup, nullptr, -1);
            set_window_update(WIN_BTL_POPUP, WINDOW_UPDATE_SHOW);
            CelebrateSubstateTime = 60;
            gBattleSubState = BTL_SUBSTATE_LEVEL_UP_INVALID_DELAY;
            break;
        case BTL_SUBSTATE_LEVEL_UP_INVALID_DELAY:
            if (gGameStatusPtr->pressedButtons[0] & (BUTTON_A | BUTTON_B)) {
                CelebrateSubstateTime = 0;
            }
            if (CelebrateSubstateTime != 0) {
                CelebrateSubstateTime--;
                break;
            }
            set_window_update(WIN_BTL_POPUP, WINDOW_UPDATE_HIDE);
            gBattleSubState = BTL_SUBSTATE_LEVEL_UP_CHOOSE;
            break;
        case BTL_SUBSTATE_SKIPPABLE_END_DELAY:
            if (battleStatus->curButtonsPressed & (BUTTON_A | BUTTON_B)) {
                CelebrateStateTime = 99;
#if VERSION_JP
                sfx_play_sound(SOUND_MENU_NEXT);
#endif
            }
            if (CelebrateStateTime >= 99) {
                if (!(gBattleStatus.flags2 & BS_FLAGS2_DONT_STOP_MUSIC)) {
                    bgm_set_song(0, -1, 0, 1500, 8);
                }
                bFadeToBlackAmt = 0;
                btl_cam_set_params(true, 270, 100, 8, 0, 0x2400, 100);
                BattleCelebration walkOff = { battleStatus->totalStarPoints, ANIM_MarioB1_AdjustCap, 4.0f, 4.0f };
                CALL_EVENT(OnBattleCelebration, BATTLE_CELEBRATION_WALK_OFF_BEGIN, &walkOff);
                set_actor_anim(0, 0, walkOff.walkOffAnim);
                if (partner != nullptr) {
                    set_actor_anim(ACTOR_PARTNER, 0, D_80284154[playerData->curPartner]);
                }
                CelebrateSubstateTime = 6;
                gBattleSubState = BTL_SUBSTATE_WALK_AWAY;
                break;
            }
            break;
        case BTL_SUBSTATE_WALK_AWAY:
            if (CelebrateSubstateTime != 0) {
                CelebrateSubstateTime--;
                if (CelebrateSubstateTime == 0) {
                    set_actor_anim(0, 0, ANIM_Mario1_Walk);
                }
            } else {
                player->yaw = 0.0f;
                if (partner != nullptr) {
                    partner->yaw = 0.0f;
                }

                BattleCelebration walkStep = { battleStatus->totalStarPoints, ANIM_MarioB1_AdjustCap, 4.0f, 4.0f };
                CALL_EVENT(OnBattleCelebration, BATTLE_CELEBRATION_WALK_OFF_STEP, &walkStep);
                player->curPos.x += walkStep.playerStepX;
                if (partner != nullptr) {
                    partner->curPos.x += walkStep.partnerStepX;
                }
            }
            if (bFadeToBlackAmt == 255) {
                gBattleSubState = BTL_SUBSTATE_DONE;
                break;
            }
            bFadeToBlackAmt += 20;
            if (bFadeToBlackAmt > 255) {
                bFadeToBlackAmt = 255;
            }
            break;
        case BTL_SUBSTATE_DONE:
            if (does_script_exist(player->takeTurnScriptID)) {
                kill_script_by_ID(player->takeTurnScriptID);
            }
            if (partner != nullptr && does_script_exist(partner->takeTurnScriptID)) {
                kill_script_by_ID(partner->takeTurnScriptID);
            }
            btl_set_state(BATTLE_STATE_END_BATTLE);
            gBattleSubState = BTL_SUBSTATE_END_BATTLE_EXEC_STAGE_SCRIPT;
            break;
    }
    CelebrateStateTime++;
}

void btl_draw_upgrade_windows(s32 phase) {
    BattleStatus* battleStatus = &gBattleStatus;
    s32 x;
    s32 y;
    s32 d1;
    s32 d2;
    s32 d3;

    switch (phase) {
        case 0: // before choice
            d1 = 100;
            d2 = 100;
            d3 = 100;
            break;
        case 1: // choosing
            switch (battleStatus->curSubmenu) {
                case MENU_HP:
                    d1 = 0;
                    d2 = 100;
                    d3 = 100;
                    break;
                case MENU_FP:
                    d1 = 100;
                    d2 = 0;
                    d3 = 100;
                    break;
                default:
                    d1 = 100;
                    d2 = 100;
                    d3 = 0;
                    break;
            }
            break;
        default: // after choice
            d1 = 100;
            d2 = 100;
            d3 = 100;
            break;
    }

    hud_element_get_render_pos(LevelUpStatEmblemIDs[0], &x, &y);
    draw_box(0, WINDOW_STYLE_15, x - 22, y - 22, 0, 44, 44, 255, d1, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, nullptr, nullptr, nullptr,
             SCREEN_WIDTH, SCREEN_HEIGHT, nullptr);
    hud_element_get_render_pos(LevelUpStatEmblemIDs[3], &x, &y);
    draw_box(0, WINDOW_STYLE_15, x - 22, y - 22, 0, 44, 44, 255, d2, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, nullptr, nullptr, nullptr,
             SCREEN_WIDTH, SCREEN_HEIGHT, nullptr);
    hud_element_get_render_pos(LevelUpStatEmblemIDs[2], &x, &y);
    draw_box(0, WINDOW_STYLE_15, x - 22, y - 22, 0, 44, 44, 255, d3, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, nullptr, nullptr, nullptr,
             SCREEN_WIDTH, SCREEN_HEIGHT, nullptr);
}

void btl_state_draw_celebration(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    s32 rotZ;
    s32 id;
    s32 i;
    s32 j;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_LEVEL_UP_SHOW_HUD:
            btl_draw_upgrade_windows(0);
            id = LevelUpStatEmblemIDs[0];
            hud_element_set_tint(id, 128, 128, 128);
            hud_element_draw_clipped(id);
            id = LevelUpStatEmblemIDs[3];
            hud_element_set_tint(id, 128, 128, 128);
            hud_element_draw_clipped(id);
            id = LevelUpStatEmblemIDs[1];
            hud_element_set_tint(id, 128, 128, 128);
            hud_element_draw_clipped(id);
            id = LevelUpStatEmblemIDs[2];
            hud_element_set_tint(id, 128, 128, 128);
            hud_element_draw_clipped(id);

            for (j = 0; j < ARRAY_COUNT(LevelUpStatTextIDs); j++) {
                for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_FP]); i++) {
                    id = LevelUpStatTextIDs[j][i];

                    hud_element_set_tint(id, 128, 128, 128);
                    hud_element_draw_clipped(id);
                }
            }
            break;
        case BTL_SUBSTATE_LEVEL_UP_CHOOSE:
        case BTL_SUBSTATE_LEVEL_UP_INVALID:
        case BTL_SUBSTATE_LEVEL_UP_INVALID_DELAY:
            switch (battleStatus->curSubmenu) {
                case MENU_HP:
                    rotZ = 152;
                    hud_element_set_tint(LevelUpStatEmblemIDs[0], 255, 255, 255);
                    hud_element_set_tint(LevelUpStatEmblemIDs[3], 128, 128, 128);
                    hud_element_set_tint(LevelUpStatEmblemIDs[1], 128, 128, 128);
                    hud_element_set_tint(LevelUpStatEmblemIDs[2], 128, 128, 128);

                    for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_FP]); i++) {
                        id = LevelUpStatTextIDs[LVL_UP_FP][i];

                        hud_element_set_tint(id, 128, 128, 128);
                    }

                    for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_HP]); i++) {
                        id = LevelUpStatTextIDs[LVL_UP_HP][i];

                        hud_element_set_tint(id, 255, 255, 255);
                    }

                    for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_BP]); i++) {
                        id = LevelUpStatTextIDs[LVL_UP_BP][i];

                        hud_element_set_tint(id, 128, 128, 128);
                    }

                    id = LevelUpStatEmblemIDs[0];
                    if (hud_element_get_script(id) != &HES_level_up_heart_copy) {
                        hud_element_set_script(id, &HES_level_up_heart_copy);
                    }
                    id = LevelUpStatEmblemIDs[3];
                    if (hud_element_get_script(id) != &HES_level_up_leaves) {
                        hud_element_set_script(id, &HES_level_up_leaves);
                    }
                    id = LevelUpStatEmblemIDs[1];
                    if (hud_element_get_script(id) != &HES_level_up_flower) {
                        hud_element_set_script(id, &HES_level_up_flower);
                    }
                    id = LevelUpStatEmblemIDs[2];
                    if (hud_element_get_script(id) != &HES_level_up_badge) {
                        hud_element_set_script(id, &HES_level_up_badge);
                    }
                    break;
                case MENU_FP:
                    rotZ = 180;
                    hud_element_set_tint(LevelUpStatEmblemIDs[0], 128, 128, 128);
                    hud_element_set_tint(LevelUpStatEmblemIDs[3], 255, 255, 255);
                    hud_element_set_tint(LevelUpStatEmblemIDs[1], 255, 255, 255);
                    hud_element_set_tint(LevelUpStatEmblemIDs[2], 128, 128, 128);

                    for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_FP]); i++) {
                        id = LevelUpStatTextIDs[LVL_UP_FP][i];

                        hud_element_set_tint(id, 255, 255, 255);
                    }

                    for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_HP]); i++) {
                        id = LevelUpStatTextIDs[LVL_UP_HP][i];

                        hud_element_set_tint(id, 128, 128, 128);
                    }

                    for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_BP]); i++) {
                        id = LevelUpStatTextIDs[LVL_UP_BP][i];

                        hud_element_set_tint(id, 128, 128, 128);
                    }
                    break;
                case MENU_BP:
                default:
                    rotZ = 208;
                    hud_element_set_tint(LevelUpStatEmblemIDs[0], 128, 128, 128);
                    hud_element_set_tint(LevelUpStatEmblemIDs[3], 128, 128, 128);
                    hud_element_set_tint(LevelUpStatEmblemIDs[1], 128, 128, 128);
                    hud_element_set_tint(LevelUpStatEmblemIDs[2], 255, 255, 255);

                    for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_FP]); i++) {
                        id = LevelUpStatTextIDs[LVL_UP_FP][i];

                        hud_element_set_tint(id, 128, 128, 128);
                    }

                    for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_HP]); i++) {
                        id = LevelUpStatTextIDs[LVL_UP_HP][i];

                        hud_element_set_tint(id, 128, 128, 128);
                    }

                    for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_BP]); i++) {
                        id = LevelUpStatTextIDs[LVL_UP_BP][i];

                        hud_element_set_tint(id, 255, 255, 255);
                    }
                    break;
            }

            btl_draw_upgrade_windows(1);
            hud_element_draw_clipped(LevelUpStatEmblemIDs[0]);
            hud_element_draw_clipped(LevelUpStatEmblemIDs[3]);
            hud_element_draw_clipped(LevelUpStatEmblemIDs[1]);
            hud_element_draw_clipped(LevelUpStatEmblemIDs[2]);

            for (j = 0; j < ARRAY_COUNT(LevelUpStatTextIDs); j++) {
                for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_FP]); i++) {
                    hud_element_draw_clipped(LevelUpStatTextIDs[j][i]);
                }
            }

            hud_element_draw_complex_hud_first(-1);
            id = LevelUpSpotlightID;
            hud_element_set_transform_rotation(id, 0.0f, 0.0f, rotZ);
            hud_element_draw_complex_hud_next(id);
            break;
        case BTL_SUBSTATE_LEVEL_UP_UPGRADE:
        case BTL_SUBSTATE_LEVEL_UP_FADE_OUT:
            btl_draw_upgrade_windows(1);
            hud_element_draw_clipped(LevelUpStatEmblemIDs[0]);
            hud_element_draw_clipped(LevelUpStatEmblemIDs[3]);
            hud_element_draw_clipped(LevelUpStatEmblemIDs[1]);
            hud_element_draw_clipped(LevelUpStatEmblemIDs[2]);

            for (j = 0; j < ARRAY_COUNT(LevelUpStatTextIDs); j++) {
                for (i = 0; i < ARRAY_COUNT(LevelUpStatTextIDs[LVL_UP_FP]); i++) {
                    hud_element_draw_clipped(LevelUpStatTextIDs[j][i]);
                }
            }

            set_screen_overlay_params_front(OVERLAY_SCREEN_COLOR, bFadeToBlackAmt);
            break;
        case BTL_SUBSTATE_LEVEL_UP_DESTROY_HUD:
            set_screen_overlay_params_front(OVERLAY_SCREEN_COLOR, bFadeToBlackAmt);
            break;
        case BTL_SUBSTATE_WALK_AWAY:
            if (bFadeToBlackAmt != 0) {
                set_screen_overlay_params_front(OVERLAY_SCREEN_COLOR, bFadeToBlackAmt);
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_LEVEL_UP_SHOW_HUD:
        case BTL_SUBSTATE_LEVEL_UP_CHOOSE:
        case BTL_SUBSTATE_LEVEL_UP_UPGRADE:
            LevelUpSelectTextVelX += 2;
            LevelUpSelectTextOffsetX += LevelUpSelectTextVelX;
            if (LevelUpSelectTextOffsetX > 200) {
                LevelUpSelectTextOffsetX = 200;
                LevelUpSelectTextVelX = -LevelUpSelectTextVelX / 3; // rebounding
            }
            id = LevelUpSelectTextID;
            hud_element_set_render_pos(id, LevelUpSelectTextOffsetX - 43, 176);
            hud_element_draw_clipped(id);
            break;
        case BTL_SUBSTATE_LEVEL_UP_FADE_OUT:
            LevelUpSelectTextVelX += 4;
            LevelUpSelectTextOffsetX += LevelUpSelectTextVelX;
            if (LevelUpSelectTextOffsetX > 500) {
                LevelUpSelectTextOffsetX = 500;
            }
            id = LevelUpSelectTextID;
            hud_element_set_render_pos(id, LevelUpSelectTextOffsetX - 43, 176);
            hud_element_draw_clipped(id);
            break;
    }
}

void draw_content_level_up_textbox(void* data, s32 posX, s32 posY) {
    BattleStatus* battleStatus = &gBattleStatus;
    s32 xOffset;
    s32 msgID;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_LEVEL_UP_CHOOSE:
        case BTL_SUBSTATE_LEVEL_UP_INVALID:
        case BTL_SUBSTATE_LEVEL_UP_INVALID_DELAY:
            switch (battleStatus->curSubmenu) {
                case MENU_HP:
                    if (!CantLevelUpStat[MENU_HP]) {
                        msgID = MSG_Menus_LevelUp_HP;
                    } else {
                        msgID = MSG_Menus_LevelUp_MaxedHP;
                    }
                    xOffset = 9;
                    break;
                case MENU_FP:
                    if (!CantLevelUpStat[MENU_FP]) {
                        msgID = MSG_Menus_LevelUp_FP;
                    } else {
                        msgID = MSG_Menus_LevelUp_MaxedFP;
                    }
                    xOffset = 9;
                    break;
                default:
                    if (!CantLevelUpStat[MENU_BP]) {
                        msgID = MSG_Menus_LevelUp_BP;
                    } else {
                        msgID = MSG_Menus_LevelUp_MaxedBP;
                    }
                    xOffset = 9;
                    break;
            }
            draw_msg(msgID, posX + xOffset + 17, posY, 255, MSG_PAL_STANDARD, 0);
            break;
    }
}

void draw_content_cant_increase_popup(void* data, s32 posX, s32 posY) {
    draw_msg(MSG_Menus_CantIncrease, posX + 11, posY + 6, 255, MSG_PAL_0F, 0);
}
