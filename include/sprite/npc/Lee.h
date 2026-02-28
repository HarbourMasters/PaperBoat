#ifndef _NPC_SPRITE_LEE_H_
#define _NPC_SPRITE_LEE_H_

#include "types.h"

#define SPR_Lee 0xA4

#define SPR_IMG_Lee_Idle1 0x0
#define SPR_IMG_Lee_Idle2 0x1
#define SPR_IMG_Lee_Idle3 0x2
#define SPR_IMG_Lee_Idle4 0x3
#define SPR_IMG_Lee_Step1 0x4
#define SPR_IMG_Lee_Step2 0x5
#define SPR_IMG_Lee_Step3 0x6
#define SPR_IMG_Lee_Talk 0x7
#define SPR_IMG_Lee_Defeated1 0x8
#define SPR_IMG_Lee_Defeated2 0x9
#define SPR_IMG_Lee_RaiseArms1 0xA
#define SPR_IMG_Lee_RaiseArms2 0xB
#define SPR_IMG_Lee_RaiseArms3 0xC
#define SPR_IMG_Lee_Midair1 0xD
#define SPR_IMG_Lee_Midair2 0xE
#define SPR_IMG_Lee_RaisedArmsTalk 0xF
#define SPR_IMG_Lee_Crouch 0x10
#define SPR_IMG_Lee_Hurt1 0x11
#define SPR_IMG_Lee_Hurt2 0x12
#define SPR_IMG_Lee_Burned 0x13
#define SPR_IMG_Lee_Sleep1 0x14
#define SPR_IMG_Lee_Sleep2 0x15
#define SPR_IMG_Lee_Sleep3 0x16
#define SPR_IMG_Lee_Dizzy1 0x17
#define SPR_IMG_Lee_Dizzy2 0x18
#define SPR_IMG_Lee_Dizzy3 0x19
#define SPR_IMG_Lee_Dizzy4 0x1A

#define SPR_PAL_Lee 0x0
#define SPR_PAL_Lee_Poisoned 0x1
#define SPR_PAL_Lee_Dizzy 0x2
#define SPR_PAL_Lee_Shocked 0x3
#define SPR_PAL_Lee_Burnt 0x4

#define ANIM_Lee_Still 0xA40000
#define ANIM_Lee_MidairStill 0xA40001
#define ANIM_Lee_Idle 0xA40002
#define ANIM_Lee_Walk 0xA40003
#define ANIM_Lee_Run 0xA40004
#define ANIM_Lee_RaiseArms 0xA40005
#define ANIM_Lee_Talk 0xA40006
#define ANIM_Lee_RaisedArmsTalk 0xA40007
#define ANIM_Lee_Crouch 0xA40008
#define ANIM_Lee_Midair 0xA40009
#define ANIM_Lee_Land 0xA4000A
#define ANIM_Lee_Hurt 0xA4000B
#define ANIM_Lee_Defeated 0xA4000C
#define ANIM_Lee_Burned 0xA4000D
#define ANIM_Lee_Sleep 0xA4000E
#define ANIM_Lee_Dizzy 0xA4000F

#define ANIM_Lee_Poisoned_Still 0xA40100
#define ANIM_Lee_Poisoned_MidairStill 0xA40101
#define ANIM_Lee_Poisoned_Idle 0xA40102
#define ANIM_Lee_Poisoned_Walk 0xA40103
#define ANIM_Lee_Poisoned_Run 0xA40104
#define ANIM_Lee_Poisoned_RaiseArms 0xA40105
#define ANIM_Lee_Poisoned_Talk 0xA40106
#define ANIM_Lee_Poisoned_RaisedArmsTalk 0xA40107
#define ANIM_Lee_Poisoned_Crouch 0xA40108
#define ANIM_Lee_Poisoned_Midair 0xA40109
#define ANIM_Lee_Poisoned_Land 0xA4010A
#define ANIM_Lee_Poisoned_Hurt 0xA4010B
#define ANIM_Lee_Poisoned_Defeated 0xA4010C
#define ANIM_Lee_Poisoned_Burned 0xA4010D
#define ANIM_Lee_Poisoned_Sleep 0xA4010E
#define ANIM_Lee_Poisoned_Dizzy 0xA4010F

#define ANIM_Lee_Dizzy_Still 0xA40200
#define ANIM_Lee_Dizzy_MidairStill 0xA40201
#define ANIM_Lee_Dizzy_Idle 0xA40202
#define ANIM_Lee_Dizzy_Walk 0xA40203
#define ANIM_Lee_Dizzy_Run 0xA40204
#define ANIM_Lee_Dizzy_RaiseArms 0xA40205
#define ANIM_Lee_Dizzy_Talk 0xA40206
#define ANIM_Lee_Dizzy_RaisedArmsTalk 0xA40207
#define ANIM_Lee_Dizzy_Crouch 0xA40208
#define ANIM_Lee_Dizzy_Midair 0xA40209
#define ANIM_Lee_Dizzy_Land 0xA4020A
#define ANIM_Lee_Dizzy_Hurt 0xA4020B
#define ANIM_Lee_Dizzy_Defeated 0xA4020C
#define ANIM_Lee_Dizzy_Burned 0xA4020D
#define ANIM_Lee_Dizzy_Sleep 0xA4020E
#define ANIM_Lee_Dizzy_Dizzy 0xA4020F

#define ANIM_Lee_Shocked_Still 0xA40300
#define ANIM_Lee_Shocked_MidairStill 0xA40301
#define ANIM_Lee_Shocked_Idle 0xA40302
#define ANIM_Lee_Shocked_Walk 0xA40303
#define ANIM_Lee_Shocked_Run 0xA40304
#define ANIM_Lee_Shocked_RaiseArms 0xA40305
#define ANIM_Lee_Shocked_Talk 0xA40306
#define ANIM_Lee_Shocked_RaisedArmsTalk 0xA40307
#define ANIM_Lee_Shocked_Crouch 0xA40308
#define ANIM_Lee_Shocked_Midair 0xA40309
#define ANIM_Lee_Shocked_Land 0xA4030A
#define ANIM_Lee_Shocked_Hurt 0xA4030B
#define ANIM_Lee_Shocked_Defeated 0xA4030C
#define ANIM_Lee_Shocked_Burned 0xA4030D
#define ANIM_Lee_Shocked_Sleep 0xA4030E
#define ANIM_Lee_Shocked_Dizzy 0xA4030F

#define ANIM_Lee_Burnt_Still 0xA40400
#define ANIM_Lee_Burnt_MidairStill 0xA40401
#define ANIM_Lee_Burnt_Idle 0xA40402
#define ANIM_Lee_Burnt_Walk 0xA40403
#define ANIM_Lee_Burnt_Run 0xA40404
#define ANIM_Lee_Burnt_RaiseArms 0xA40405
#define ANIM_Lee_Burnt_Talk 0xA40406
#define ANIM_Lee_Burnt_RaisedArmsTalk 0xA40407
#define ANIM_Lee_Burnt_Crouch 0xA40408
#define ANIM_Lee_Burnt_Midair 0xA40409
#define ANIM_Lee_Burnt_Land 0xA4040A
#define ANIM_Lee_Burnt_Hurt 0xA4040B
#define ANIM_Lee_Burnt_Defeated 0xA4040C
#define ANIM_Lee_Burnt_Burned 0xA4040D
#define ANIM_Lee_Burnt_Sleep 0xA4040E
#define ANIM_Lee_Burnt_Dizzy 0xA4040F

#endif
