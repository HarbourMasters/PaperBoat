
/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1994, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

/**************************************************************************
 *
 *  $Revision: 1.10 $
 *  $Date: 1997/02/11 08:37:33 $
 *  $Source: /hosts/gate3/exdisk2/cvs/N64OS/Master/cvsmdev2/PR/include/ultra64.h,v $
 *
 **************************************************************************/

#ifndef _ULTRA64_H_
#define _ULTRA64_H_

// Use libultraship headers for the port
#include <libultraship/libultra/types.h>
#include <libultraship/libultra/gu.h>
#include <libultraship/libultra/gbi.h>
#include <libultraship/libultra/mbi.h>
#include <libultraship/libultra/sptask.h>
#include <libultraship/libultra/os.h>
#include <libultraship/libultra/vi.h>
#include <libultraship/libultra/pi.h>
#include <libultraship/libultra/thread.h>
#include <libultraship/libultra/message.h>
#include <libultraship/libultra/time.h>
#include <libultraship/libultra/controller.h>
#include <libultraship/libultra/pfs.h>
#include <libultraship/libultra/exception.h>
#include <libultraship/libultra/interrupt.h>
#include <libultraship/libultra/rcp.h>
#include <libultraship/libultra/r4300.h>
#include <libultraship/libultra/convert.h>

// Additional PM64-specific OS headers
#include <PR/os_tlb.h>

// Additional constants needed by PM64
#ifndef SP_UCODE_DATA_SIZE
#define SP_UCODE_DATA_SIZE 2048
#endif

// Additional PI functions and video modes not in libultraship
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
extern s32 osEPiReadIo(OSPiHandle *, u32, u32 *);
extern s32 osEPiWriteIo(OSPiHandle *, u32, u32);
extern u32 osMemSize; // Memory size global variable

// 64-bit safe: returns full pointer value, not truncated to 32-bit
uintptr_t osVirtualToPhysical(void* addr);

// Video system globals and modes
extern s32 osTvType; // 0 = PAL, 1 = NTSC, 2 = MPAL
extern OSViMode osViModeNtscLan1;
extern OSViMode osViModeMpalLan1;

#ifdef __cplusplus
}
#endif

#endif
