#include "common.h"
#include "assets/ui.h"

// msg UI assets loaded from OTR via assets/ui.h

#if VERSION_JP
BSS IMG_BIN MsgCharImgMenuLatin[0x798] ALIGNED(16);
BSS IMG_BIN MsgCharImgMenuKana[0x37F8] ALIGNED(16);
// in JP button icons uses this, which has smaller size to store the credits subtitle character set. What's going on here?
BSS IMG_BIN MsgCharImgSubtitle[0x460] ALIGNED(16);
BSS IMG_BIN MsgCharImgKana[0x5710] ALIGNED(16);
BSS PAL_BIN D_802F4560[80][8];
BSS IMG_BIN MsgCharImgLatin[0xBD0] ALIGNED(16);
// in JP kanji chars also uses this
BSS IMG_BIN MsgCharImgTitle[0x34F0] ALIGNED(16);
#else
BSS IMG_BIN MsgCharImgTitle[0xF60];
BSS IMG_BIN MsgCharImgNormal[0x5100];
BSS IMG_BIN MsgCharImgSubtitle[0xB88];
BSS PAL_BIN D_802F4560[80][8] ALIGNED(16);
#endif
