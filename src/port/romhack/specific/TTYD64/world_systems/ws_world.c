#include "ws_internal.h"
#include "entity.h"
#include "effects.h"
#include "filemenu.h"
#include "game_modes.h"
#include "script_api/macros.h"
#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/modding/Messages.h"
#include "../TTYD64.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_flags.h"
#include "../include/ttyd64_rawmem.h"
#include "../include/ttyd64_symbols.h"

#define WS_GAME_MODE       TTYD64_ModByte(TTYD64_MB_GameMode)
#define WS_MODE_BOW        1
#define WS_MODE_RANDOMIZED 2
#define WS_MSG_MENUS_BUY   0x1D01AD

API_CALLABLE(DisablePlayerInput);
API_CALLABLE(AddItem);
API_CALLABLE(ShowGotItem);
API_CALLABLE(SetTimeFreezeMode);

extern EvtScript TTYD64_kmr_33_Script_OpenChest;
extern EvtScript TTYD64_tik_05_Script_OpenChest;
extern EvtScript TTYD64_dro_03_Script_OpenChest;
extern EvtScript TTYD64_kpa_135_Script_OpenChest;
extern EvtScript TTYD64_tyd_00_Script_OpenChest;
extern MenuPanel filemenu_main_menuBP;

static s32 sMsgFFWD;
static s32 sMsgPage;

typedef struct TTYD64EffectTints {
    u8 poisonDrive;
    u32 fireBreath;
} TTYD64EffectTints;

static TTYD64EffectTints sEffectTints;

API_CALLABLE(TTYD64_SetPoisonDrive) {
    sEffectTints.poisonDrive = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetFireBreathTint) {
    sEffectTints.fireBreath = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

typedef struct TTYD64WorldModes {
    b32 underwaterFollowsMover;
    b32 shopBuyPopup;
    u8 verticalMovementLocked;
    u8 eightBitSwitchPressed;
} TTYD64WorldModes;

static TTYD64WorldModes sWorldModes;

API_CALLABLE(TTYD64_SetUnderwaterFollowsMover) {
    sWorldModes.underwaterFollowsMover = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetShopBuyPopup) {
    sWorldModes.shopBuyPopup = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetVerticalMovementLocked) {
    sWorldModes.verticalMovementLocked = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Set8BitSwitchPressed) {
    sWorldModes.eightBitSwitchPressed = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_ResetFFWD) {
    TTYD64_ws_FFWDReset(&TTYD64_FFWD);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetFFWDSuppressed) {
    TTYD64_FFWD.suppressed = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

static s32 ws_mode(void) {
    return evt_get_variable(NULL, WS_GAME_MODE);
}

static void ws_ffwd_frame(void) {
    s32 style = TTYD64_ws_FFWDFrame(&TTYD64_FFWD, gGameStatusPtr->pressedButtons[0]);

    if (style >= 0) {
        draw_msg(sMsgFFWD, 0xF2, 0xC8, 0xFF, 0, style);
    }
}

static void ws_draw_shop_current_page(void) {
    Evt* script;

    if (TTYD64_ReadBE(TTYD64_Data_Shop_ExtraData, sizeof(void*), 4) == 0) {
        return;
    }
    TTYD64_DrawBox(0x1D, 0x7D, 0x5D, 0x1D, 0, 0xFF);
    memcpy(&script, TTYD64_Data_Shop_ExtraData, sizeof(script));
    set_message_int_var((s32) script->varTable[10] + 1, 0);
    set_message_int_var((s32) script->varTable[11] + 1, 1);
    draw_msg(sMsgPage, 0x27, 0x83, 0xFF, 0, 0);
}

void TTYD64_HudDriverFrame(void) {
    ws_ffwd_frame();
    TTYD64_Function_kmr31_DrawDescriptionBox();
    ws_draw_shop_current_page();
    TTYD64_Draw_ShinesCounter();
    TTYD64_Function_UpdateMinigames();
}

void TTYD64_Function_Mode_Random_GetEnemyItem(s32* itemID) {
    s32 type;

    if (ws_mode() != WS_MODE_RANDOMIZED) {
        return;
    }
    *itemID = TTYD64_ws_RandomPick(0, 0, &type);
}

static EvtScript* const sRandomizableChestScripts[] = {
    &TTYD64_kmr_33_Script_OpenChest,  &TTYD64_tik_05_Script_OpenChest, &TTYD64_dro_03_Script_OpenChest,
    &TTYD64_kpa_135_Script_OpenChest, &TTYD64_tyd_00_Script_OpenChest,
};

static b32 ws_is_randomizable_chest_script(EvtScript* script) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sRandomizableChestScripts); i++) {
        if (sRandomizableChestScripts[i] == script) {
            return true;
        }
    }
    return false;
}

API_CALLABLE(TTYD64_ws_SetOpenedChestFlag) {
    s32 entityIndex = (u8) gPlayerStatus.interactingWithID;
    Entity* chest;

    if (entityIndex == 255) {
        return ApiStatus_DONE2;
    }
    chest = get_entity_by_index(entityIndex);
    if (chest != NULL && chest->dataBuf.chest->gameFlagIndex != 0xFFFF) {
        set_global_flag(chest->dataBuf.chest->gameFlagIndex);
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_ws_GetRandomChestItem) {
    Bytecode* args = script->ptrReadPos;
    s32 type;
    s32 itemID = TTYD64_ws_RandomPick(1, 0, &type);

    evt_set_variable(script, args[0], itemID);
    evt_set_variable(script, args[1], type);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_ws_AddKeyItem) {
    Bytecode* args = script->ptrReadPos;
    PlayerData* playerData = &gPlayerData;
    s32 itemID = evt_get_variable(script, args[0]);
    s32 i;

    if (itemID == ITEM_KOOPA_FORTRESS_KEY) {
        TTYD64_FortressKeys++;
        return ApiStatus_DONE2;
    }
    for (i = 0; i < ARRAY_COUNT(playerData->keyItems); i++) {
        if (playerData->keyItems[i] == ITEM_NONE) {
            break;
        }
    }
    if (i < ARRAY_COUNT(playerData->keyItems)) {
        playerData->keyItems[i] = itemID;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_ws_AddBadge) {
    Bytecode* args = script->ptrReadPos;
    s32 badgeID = evt_get_variable(script, args[0]);

    evt_set_variable(script, args[1], add_item(badgeID));
    return ApiStatus_DONE2;
}

// clang-format off
EvtScript TTYD64_ws_Script_ShowGotItem = {
    SetGroup(0)
    Call(SetTimeFreezeMode, 2)
    Wait(40)
    Call(ShowGotItem, LVar0, false, 0)
    Call(SetTimeFreezeMode, 0)
    Return
    Return
    End
};

EvtScript TTYD64_ws_Script_GiveItem = {
    Call(DisablePlayerInput, true)
    Set(LVar0, LVarA)
    IfNe(LVarA, 0)
        ExecWait(TTYD64_ws_Script_ShowGotItem)
    EndIf
    Switch(LVarB)
        CaseEq(0)
            Call(AddItem, LVarA, LVar0)
        CaseEq(1)
            Call(TTYD64_ws_AddKeyItem, LVarA)
        CaseEq(2)
            Call(TTYD64_ws_AddBadge, LVarA, LVar0)
    EndSwitch
    Wait(15)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript TTYD64_ws_Script_OpenRandomChest = {
    Call(TTYD64_ws_SetOpenedChestFlag)
    Call(TTYD64_ws_GetRandomChestItem, LVar0, LVar1)
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    ExecWait(TTYD64_ws_Script_GiveItem)
    Return
    End
};
// clang-format on

static void ws_sb_set_color(s32 face, s32 vert, u32 rgba, b32 keepAlpha) {
    s32 i;

    for (i = 0; i < WS_SB_REFS; i++) {
        ModVertexRef ref = TTYD64_ws_SaveBlockFaceVerts[face][vert][i];

        if (ref.vtxAsset == NULL) {
            continue;
        }
        if (keepAlpha) {
            Mod_SetVertexColorRGB(ref, rgba >> 24, rgba >> 16, rgba >> 8);
        } else {
            Mod_SetVertexColor(ref, rgba >> 24, rgba >> 16, rgba >> 8, rgba);
        }
    }
}

static void ws_on_entity_pre_draw(IEvent* event) {
    EntityPreDraw* ev = (EntityPreDraw*) event;

    if (ev->entity->blueprint == &Entity_SavePoint) {
        TTYD64_ws_SaveBlockAnimate(ev->entity->listIndex, ws_sb_set_color);
    }
}

static void ws_on_status_bar_updated(IEvent* event) {
    TTYD64_HudDriverFrame();
}

static void ws_on_message_open(IEvent* event) {
    TTYD64_ws_FFWDPrinterAcquired(&TTYD64_FFWD);
}

static void ws_on_message_speed(IEvent* event) {
    OnMessageSpeed* ev = (OnMessageSpeed*) event;

    TTYD64_ws_FFWDSpeed(&TTYD64_FFWD, ev->charsPerFrame, ev->skip);
}

static void ws_on_title_screen_init(IEvent* event) {
    TTYD64_ws_FFWDReset(&TTYD64_FFWD);
}

static void ws_on_player_input_enabled(IEvent* event) {
    TTYD64_ws_FFWDInputEnabled(&TTYD64_FFWD, evt_get_variable(NULL, TTYD64_ModFlag(TTYD64_MF_Flag_Settings_FFWD)));
}

static void ws_on_battle_state_changed(IEvent* event) {
    OnBattleStateChanged* ev = (OnBattleStateChanged*) event;

    TTYD64_UpdateNewStatuses_Visibility(TTYD64_RequestedBattleState(ev->next));
    if (ev->prev == BATTLE_STATE_START) {
        TTYD64_enemy_item_table_data_update_actorMostInFront();
    }
    TTYD64_ws_FFWDBattleStateSet(&TTYD64_FFWD, evt_get_variable(NULL, TTYD64_ModFlag(TTYD64_MF_Flag_Settings_FFWD)));
}

static void ws_on_action_command_load(IEvent* event) {
    TTYD64_FFWD.printerOpen = 0;
}

static void ws_on_effect_color(IEvent* event) {
    OnEffectColor* ev = (OnEffectColor*) event;

    switch (ev->effectID) {
        case EFFECT_FIRE_BREATH:
            if (ev->slot == 0) {
                TTYD64_ws_FlameBodyColor(sEffectTints.fireBreath, &ev->color->r, &ev->color->g, &ev->color->b);
            } else {
                TTYD64_ws_FlameOutlineColor(sEffectTints.fireBreath, &ev->color->r, &ev->color->g, &ev->color->b);
            }
            break;
        case EFFECT_RING_BLAST:
            TTYD64_ws_RingBlastColors(
                sEffectTints.poisonDrive, ev->slot, TTYD64_ws_RingBlastScale(ev->effect->data.ringBlast->unk_20),
                &ev->color->r, &ev->color->g, &ev->color->b
            );
            break;
        case EFFECT_UNDERWATER:
            if (sWorldModes.underwaterFollowsMover) {
                ev->color->a = 0x100;
            }
            break;
    }
}

static b32 ws_randomizes_block(Entity* block) {
    return ws_mode() == WS_MODE_RANDOMIZED && block->dataBuf.block->item != ITEM_COIN;
}

static void ws_on_item_spawn_pick(IEvent* event) {
    OnItemSpawnPick* ev = (OnItemSpawnPick*) event;
    s32 type;

    if (ev->source != ITEM_SPAWN_SOURCE_ITEM_BLOCK || !ws_randomizes_block(ev->entity)) {
        return;
    }
    *ev->itemID = TTYD64_ws_RandomPick(0, 0, &type);
}

static void ws_on_item_spawned(IEvent* event) {
    OnItemSpawned* ev = (OnItemSpawned*) event;
    BlockData* data;

    if (ev->source != ITEM_SPAWN_SOURCE_ITEM_BLOCK || !ws_randomizes_block(ev->entity)) {
        return;
    }
    data = ev->entity->dataBuf.block;
    if (data->gameFlagIndex != 0xFFFF) {
        set_global_flag(data->gameFlagIndex);
    }
}

static void ws_on_entity_created(IEvent* event) {
    OnEntityCreated* ev = (OnEntityCreated*) event;
    Entity* entity = ev->entity;

    if (entity->blueprint == &Entity_SavePoint) {
        TTYD64_ws_SaveBlockReset();
    }
}

static void ws_on_chest_opening(IEvent* event) {
    OnChestOpening* ev = (OnChestOpening*) event;

    if (evt_get_variable(NULL, TTYD64_ModFlag(TTYD64_MF_Flag_LockInputs_GiantChest))) {
        disable_player_input();
    }
    if (ws_mode() == WS_MODE_RANDOMIZED && ev->chest->blueprint == &Entity_Chest
        && ws_is_randomizable_chest_script(*ev->script))
    {
        *ev->script = &TTYD64_ws_Script_OpenRandomChest;
    }
}

static void ws_on_player_movement_constraint(IEvent* event) {
    OnPlayerMovementConstraint* ev = (OnPlayerMovementConstraint*) event;

    if (sWorldModes.verticalMovementLocked != 0) {
        ev->constraint->lockWalkZ = true;
    }
}

static void ws_on_player_land_anim(IEvent* event) {
    if (sWorldModes.eightBitSwitchPressed != 0) {
        event->Cancelled = true;
    }
}

static void ws_on_battle_partner_select(IEvent* event) {
    OnBattlePartnerSelect* ev = (OnBattlePartnerSelect*) event;

    if (TTYD64_ws_BowBattlePartner(gBattleState, ws_mode(), *ev->partnerID)) {
        evt_set_variable(NULL, TTYD64_ModByte(TTYD64_MB_BowMode_LastPartner), *ev->partnerID);
        *ev->partnerID = PARTNER_BOW;
    }
}

static void ws_on_battle_cleanup(IEvent* event) {
    if (ws_mode() != WS_MODE_BOW) {
        return;
    }
    gPlayerData.curPartner = TTYD64_ws_BowAfterBattlePartner(
        WS_MODE_BOW, gPlayerData.curPartner, evt_get_variable(NULL, TTYD64_ModByte(TTYD64_MB_BowMode_LastPartner))
    );
}

static void ws_on_battle_darkness_check(IEvent* event) {
    OnBattleDarknessCheck* ev = (OnBattleDarknessCheck*) event;

    if (ws_mode() == WS_MODE_BOW) {
        *ev->darknessMode = 0;
    }
}

static WindowStyleCustom sFileSlotBodyStyles[5];
static WindowStyleCustom sFileSlotTitleStyles[5];

static void ws_set_style_colors(WindowStyleCustom* style, u32 color1, u32 color2) {
    style->color1.r = color1 >> 24;
    style->color1.g = color1 >> 16;
    style->color1.b = color1 >> 8;
    style->color1.a = color1;
    style->color2.r = color2 >> 24;
    style->color2.g = color2 >> 16;
    style->color2.b = color2 >> 8;
    style->color2.a = color2;
}

static void ws_init_file_slot_styles(void) {
    u32 colors[4];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sFileSlotBodyStyles); i++) {
        sFileSlotBodyStyles[i] = filemenu_windowStyles[16];
        sFileSlotTitleStyles[i] = filemenu_windowStyles[18];
        TTYD64_ws_FileBoxColors(i, colors);
        ws_set_style_colors(&sFileSlotBodyStyles[i], colors[0], colors[1]);
        ws_set_style_colors(&sFileSlotTitleStyles[i], colors[2], colors[3]);
    }
}

static void ws_on_file_slot_highlight_style(IEvent* event) {
    OnFileSlotHighlightStyle* ev = (OnFileSlotHighlightStyle*) event;
    s32 fileIndex;

    if ((u8) gGameStatusPtr->context != 0) {
        return;
    }
    fileIndex =
        TTYD64_ws_FileBoxIndex(filemenu_main_menuBP.state, filemenu_CopyFromFileIdx, filemenu_main_menuBP.selected);
    if ((u32) fileIndex >= ARRAY_COUNT(sFileSlotBodyStyles)) {
        fileIndex = ARRAY_COUNT(sFileSlotBodyStyles) - 1;
    }
    *ev->body = &sFileSlotBodyStyles[fileIndex];
    *ev->title = &sFileSlotTitleStyles[fileIndex];
}

static void ws_on_popup_menu_text(IEvent* event) {
    OnPopupMenuText* ev = (OnPopupMenuText*) event;

    if (ev->text != POPUP_TEXT_SELL_PROMPT_TITLE) {
        return;
    }
    if (sWorldModes.shopBuyPopup) {
        *ev->msgID = WS_MSG_MENUS_BUY;
    }
}

static void ws_on_consumable_choice_match(IEvent* event) {
    OnConsumableChoiceMatch* ev = (OnConsumableChoiceMatch*) event;

    *ev->found = TTYD64_ws_ConsumableChoiceMatch(ev->itemList);
}

static void ws_on_boot_logos(IEvent* event) {
    OnBootLogos* ev = (OnBootLogos*) event;

    *ev->firstState = LOGOS_STATE_IS_HOLD_1;
}

static void ws_on_intro_story_skip(IEvent* event) {
    OnIntroStorySkip* ev = (OnIntroStorySkip*) event;

    *ev->skip = true;
}

static void ws_on_title_screen_timeout(IEvent* event) {
    event->Cancelled = true;
}

void TTYD64_InstallWorldSystemsListeners(void) {
    sMsgFFWD = Mod_RegisterInlineMessage("TTYD64", TTYD64_ws_String_FFWD);
    sMsgPage = Mod_RegisterInlineMessage("TTYD64", TTYD64_ws_String_Page);
    ws_init_file_slot_styles();

    REGISTER_LISTENER(OnStatusBarUpdated, EVENT_PRIORITY_NORMAL, ws_on_status_bar_updated);
    REGISTER_LISTENER(OnMessageOpen, EVENT_PRIORITY_NORMAL, ws_on_message_open);
    REGISTER_LISTENER(OnMessageSpeed, EVENT_PRIORITY_NORMAL, ws_on_message_speed);
    REGISTER_LISTENER(OnTitleScreenInit, EVENT_PRIORITY_NORMAL, ws_on_title_screen_init);
    REGISTER_LISTENER(OnPlayerInputEnabled, EVENT_PRIORITY_NORMAL, ws_on_player_input_enabled);
    REGISTER_LISTENER(OnBattleStateChanged, EVENT_PRIORITY_NORMAL, ws_on_battle_state_changed);
    REGISTER_LISTENER(OnActionCommandLoad, EVENT_PRIORITY_NORMAL, ws_on_action_command_load);
    REGISTER_LISTENER(OnEffectColor, EVENT_PRIORITY_NORMAL, ws_on_effect_color);
    REGISTER_LISTENER(OnItemSpawnPick, EVENT_PRIORITY_NORMAL, ws_on_item_spawn_pick);
    REGISTER_LISTENER(OnItemSpawned, EVENT_PRIORITY_NORMAL, ws_on_item_spawned);
    REGISTER_LISTENER(OnEntityCreated, EVENT_PRIORITY_NORMAL, ws_on_entity_created);
    REGISTER_LISTENER(EntityPreDraw, EVENT_PRIORITY_NORMAL, ws_on_entity_pre_draw);
    REGISTER_LISTENER(OnChestOpening, EVENT_PRIORITY_NORMAL, ws_on_chest_opening);
    REGISTER_LISTENER(OnPlayerMovementConstraint, EVENT_PRIORITY_NORMAL, ws_on_player_movement_constraint);
    REGISTER_LISTENER(OnPlayerLandAnim, EVENT_PRIORITY_NORMAL, ws_on_player_land_anim);
    REGISTER_LISTENER(OnBattlePartnerSelect, EVENT_PRIORITY_NORMAL, ws_on_battle_partner_select);
    REGISTER_LISTENER(OnBattleCleanup, EVENT_PRIORITY_NORMAL, ws_on_battle_cleanup);
    REGISTER_LISTENER(OnBattleDarknessCheck, EVENT_PRIORITY_NORMAL, ws_on_battle_darkness_check);
    REGISTER_LISTENER(OnFileSlotHighlightStyle, EVENT_PRIORITY_NORMAL, ws_on_file_slot_highlight_style);
    REGISTER_LISTENER(OnPopupMenuText, EVENT_PRIORITY_NORMAL, ws_on_popup_menu_text);
    REGISTER_LISTENER(OnConsumableChoiceMatch, EVENT_PRIORITY_NORMAL, ws_on_consumable_choice_match);
    REGISTER_LISTENER(OnBootLogos, EVENT_PRIORITY_NORMAL, ws_on_boot_logos);
    REGISTER_LISTENER(OnIntroStorySkip, EVENT_PRIORITY_NORMAL, ws_on_intro_story_skip);
    REGISTER_LISTENER(OnTitleScreenTimeout, EVENT_PRIORITY_NORMAL, ws_on_title_screen_timeout);
}
