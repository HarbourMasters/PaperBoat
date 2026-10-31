#include "status_icons.h"
#include "port/patches/Patches.h"

extern "C" void port_remove_status_icon_now(s32 iconID, s32 slot) {
    HudStatusIcon* icon = &D_800A0F44[iconID];
    HudComplexStatusIcon* status;

    switch (slot) {
        case STATUS_ICON_SLOT_DEBUFF:
            remove_status_debuff(iconID);
            status = &icon->status1;
            break;
        case STATUS_ICON_SLOT_STATIC:
            remove_status_static(iconID);
            status = &icon->status2;
            break;
        case STATUS_ICON_SLOT_TRANSPARENT:
            remove_status_transparent(iconID);
            status = &icon->status3;
            break;
        default:
            return;
    }
    if (status->removingTask != STATUS_ICON_TASK_NONE) {
        hud_element_free(status->removingElementHID);
        status->removing = 0;
        status->removingTask = STATUS_ICON_TASK_NONE;
    }
}
