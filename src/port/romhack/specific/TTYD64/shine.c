#include "port/romhack/specific/TTYD64/hp_internal.h"
#include "port/modding/Messages.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"

API_CALLABLE(TTYD64_hp_Function_ShineBlock_HideContent) {
    Bytecode* args = script->ptrReadPos;

    entity_upgrade_block_hide_content(evt_get_variable(script, *args++));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_hp_ModifyGlobalOverrideFlags_NukeSomeFlags) {
    gOverrideFlags &= ~0x40;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetShineBoxAnim) {
    Bytecode* args = script->ptrReadPos;

    evt_set_variable(script, *args++, TTYD64_ShineBox.state);
    evt_set_variable(script, *args++, TTYD64_ShineBox.offset);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetShineBoxOffset) {
    TTYD64_ShineBox.offset = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetShineCounterVisible) {
    TTYD64_ShineBox.visible = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

// clang-format off
EvtScript TTYD64_Script_ShineBlock = {
    Set(LVar7, LVar0)
    Set(LVar8, LVar1)
    Call(GetValueByRef, LVar8, LVar1)
    IfEq(LVar1, true)
        Return
    EndIf
    Call(IsStartingConversation, LVar0)
    IfEq(LVar0, true)
        Return
    EndIf
    Call(TTYD64_ReadField, TTYD64_F_GPARTNERSTATUS_0_1U, LVar0)
    IfEq(LVar0, 1)
        Return
    EndIf
    SetGroup(0)
    SuspendGroup(2)
    Call(ModifyGlobalOverrideFlags, true, 0x00200000)
    Call(DisablePlayerInput, true)
    Call(DisablePartnerAI, 0)
    Call(SetTimeFreezeMode, 2)
    Call(TTYD64_hp_Function_ShineBlock_HideContent, LVar7)
    Call(ShowGotItem, 0x28, true, 0)
    Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_18_1U, LVar0)
    IfNe(LVar0, 0xFF)
        Add(LVar0, 1)
    EndIf
    Call(TTYD64_WriteField, TTYD64_F_GPLAYERDATA_18_1U, LVar0)
    Call(SetTimeFreezeMode, 0)
    Call(SetValueByRef, LVar8, true)
    Call(DisablePlayerInput, false)
    Call(EnablePartnerAI)
    Call(ModifyGlobalOverrideFlags, false, 0x00200000)
    Call(TTYD64_hp_ModifyGlobalOverrideFlags_NukeSomeFlags)
    ResumeGroup(2)
    Return
    End
};

EvtScript TTYD64_hp_Script_HandleSpeed = {
    Call(TTYD64_GetShineBoxAnim, LVar0, LVar1)
    Switch(LVar0)
        CaseEq(0)
            IfLt(LVar1, 8)
                Add(LVar1, 1)
                Call(TTYD64_SetShineBoxOffset, LVar1)
                Wait(3)
            EndIf
        CaseEq(1)
        CaseEq(2)
            IfGt(LVar1, 0)
                Sub(LVar1, 1)
                Call(TTYD64_SetShineBoxOffset, LVar1)
                Wait(3)
            EndIf
    EndSwitch
    Return
    End
};
// clang-format on

static const u8 sString_CurrentShines[] = {
    0xFF, 0x24, 0xFF, 0x05, 0x0A, 0x58, 0xF7, 0xFF, 0x28, 0x00, 0xFF, 0x25, 0xFD
};
static const u8 sString_ShineIcon[] = { 0xFF, 0x17, 0x00, 0x28, 0xFD };

static s32 sIconPosY;
static s32 sTextPosY;
static s32 sBoxSizeX;
static s32 sIconOpacity;
static s32 sTextOpacity;
static s32 sStringCurrentShinesID;
static s32 sStringShineIconID;

void TTYD64_Draw_ShinesCounter(void) {
    u32 state;
    u32 offset;

    if (!TTYD64_ShineBox.visible) {
        return;
    }
    state = TTYD64_ShineBox.state;
    if (state == 1) {
        goto offsets_end;
    }
    start_script(&TTYD64_hp_Script_HandleSpeed, 1, 0);
    offset = TTYD64_ShineBox.offset;
    switch (offset) {
        case 0:
            if (TTYD64_ShineBox.state == 2) {
                TTYD64_ShineBox.visible = false;
                TTYD64_ShineBox.state = 0;
            }
            sBoxSizeX = 0;
            goto load_box;
        case 1:
        case 2:
        case 3:
        case 4:
            sBoxSizeX = 8 * offset;
            goto load_box;
        case 5:
            sIconPosY = 0;
            sTextPosY = 0;
            sIconOpacity = 0;
            sTextOpacity = 0;
            sBoxSizeX = 8 * offset;
            goto load_box;
        case 6:
            sIconPosY = 144;
            sTextPosY = 154;
            sIconOpacity = 0x55;
            sTextOpacity = 0x54;
            sBoxSizeX = 8 * offset;
            goto load_box;
        case 7:
            sIconPosY = 146;
            sTextPosY = 156;
            sIconOpacity = 0xAA;
            sBoxSizeX = 70;
            goto load_box;
    }

offsets_end:
    sIconPosY = 148;
    sTextPosY = 158;
    sIconOpacity = 0xFF;
    sTextOpacity = 0xFE;
    TTYD64_ShineBox.state = 1;

load_box:
    TTYD64_DrawBox(0x20, 0x98, sBoxSizeX, 0x1A, 3, 0xFF);
    set_message_int_var(TTYD64_ShineSprites, 0);
    draw_msg(sStringCurrentShinesID, 65, sTextPosY, sTextOpacity, -1, 0);
    draw_msg(sStringShineIconID, 0x20, sIconPosY, sIconOpacity, -1, 0);
}

void TTYD64_hp_InstallShine(void) {
    sStringCurrentShinesID = Mod_RegisterInlineMessage("TTYD64", sString_CurrentShines);
    sStringShineIconID = Mod_RegisterInlineMessage("TTYD64", sString_ShineIcon);
}
