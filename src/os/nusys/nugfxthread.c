#include "common.h"
#include "nu/nusys.h"
#include "port/os/OS.h"

void gfxThread(void*);

NUGfxFunc nuGfxFunc = nullptr;
NUGfxPreNMIFunc nuGfxPreNMIFunc = nullptr;
OSMesgQueue	nuGfxMesgQ;
static OSMesg nuGfxMesgBuf[NU_GFX_MESGS];
static char GfxStack[NU_GFX_STACK_SIZE];

OSThread D_800B1B90;

void nuGfxThreadStart(void) {
    osCreateThread(&D_800B1B90, 4, gfxThread, nullptr, &GfxStack[NU_GFX_STACK_SIZE], NU_GFX_THREAD_PRI);
    osStartThread(&D_800B1B90);
}

void gfxThread(void* data) {
    NUScClient gfxClient;
    NUScMsg* mesgType;

    osCreateMesgQueue(&nuGfxMesgQ, nuGfxMesgBuf, NU_GFX_MESGS);
    nuScAddClient(&gfxClient, &nuGfxMesgQ, NU_SC_RETRACE_MSG | NU_SC_PRENMI_MSG);

    while (true) {
        osRecvMesg(&nuGfxMesgQ, (OSMesg*) &mesgType, OS_MESG_BLOCK);
        if (OS_ThreadShouldExit()) { // [port]
            return;
        }

        switch (*mesgType) {
            case NU_SC_RETRACE_MSG:
                if (nuGfxFunc != nullptr) {
                    (*nuGfxFunc)(nuGfxTaskSpool);
                }
                break;
            case NU_SC_PRENMI_MSG:
                if (nuGfxPreNMIFunc != nullptr) {
                    (*nuGfxPreNMIFunc)();
                }
                break;
        }
    }
}
