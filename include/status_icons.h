#ifndef _STATUS_ICONS_H_
#define _STATUS_ICONS_H_

#include "common.h"
#include "hud_element.h"

enum StatusIconFlag {
    STATUS_ICON_FLAG_USED             = 0x001,
    STATUS_ICON_FLAG_BATTLE           = 0x002,
    STATUS_ICON_FLAG_DEBUFF           = 0x004,
    STATUS_ICON_FLAG_STATIC           = 0x008,
    STATUS_ICON_FLAG_TRANSPARENT      = 0x010,
    STATUS_ICON_FLAG_STATUS_CHILL_OUT = 0x020,
    STATUS_ICON_FLAG_BOOST_JUMP       = 0x040,
    STATUS_ICON_FLAG_BOOST_HAMMER     = 0x080,
    STATUS_ICON_FLAG_BOOST_PARTNER    = 0x100,
    STATUS_ICON_FLAG_SURPRISE         = 0x200,
    STATUS_ICON_FLAG_PERIL            = 0x400,
    STATUS_ICON_FLAG_DANGER           = 0x800,
};

enum StatusIconTask {
    STATUS_ICON_TASK_NONE = 0,
    STATUS_ICON_TASK_LOAD = 1,
    STATUS_ICON_TASK_DRAW = 2,
};

typedef struct HudComplexStatusIcon {
    /* 0x0 */ s8 active;
    /* 0x1 */ s8 removing;
    /* 0x2 */ s8 activeTask;
    /* 0x3 */ s8 removingTask;
    /* 0x4 */ s8 unk_04;
    /* 0x5 */ s8 frameCounter;
    /* 0x8 */ HudElemID activeElementHID;
    /* 0xC */ HudElemID removingElementHID;
} HudComplexStatusIcon; // size = 0x10

typedef struct HudSimpleStatusIcon {
    /* 0x0 */ s8 active;
    /* 0x1 */ s8 removing;
    /* 0x4 */ s32 activeElementID;
} HudSimpleStatusIcon; // size = 0x8

typedef struct HudStatusIcon {
    /* 0x00 */ s32 flags;
    /* 0x04 */ Vec3f worldPos;
    /* 0x10 */ s32 status1Radius;
    /* 0x14 */ s32 status1OffsetY;
    /* 0x18 */ s32 status2Radius;
    /* 0x1C */ s32 status2OffsetY;
    /* 0x20 */ s32 status3Radius;
    /* 0x24 */ s32 status3OffsetY;
    /* 0x28 */ s32 status4Radius;
    /* 0x2C */ s32 status4OffsetY;
    /* 0x30 */ s32 offsetY;
    /* 0x34 */ s32 offsetX;
    /* 0x38 */ HudComplexStatusIcon status1;
    /* 0x48 */ HudComplexStatusIcon status2;
    /* 0x58 */ HudComplexStatusIcon status3;
    /* 0x68 */ HudComplexStatusIcon status4;
    /* 0x78 */ HudSimpleStatusIcon boostJump;
    /* 0x80 */ s32 prevIndexBoostJump;
    /* 0x84 */ HudSimpleStatusIcon boostHammer;
    /* 0x8C */ s32 prevIndexBoostHammer;
    /* 0x90 */ HudSimpleStatusIcon boostPartner;
    /* 0x98 */ HudSimpleStatusIcon surprise;
    /* 0xA0 */ HudSimpleStatusIcon peril;
    /* 0xA8 */ HudSimpleStatusIcon danger;
} HudStatusIcon; // size = 0xB0

#ifdef __cplusplus
extern "C" {
#endif

extern HudStatusIcon* D_800A0F44;

#ifdef __cplusplus
}
#endif

#endif
