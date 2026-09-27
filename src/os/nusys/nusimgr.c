#include "common.h"
#include "nu/nusys.h"
#include "port/DevTools/ThreadWatchdog.h"
#include "port/os/OS.h"

OSMesgQueue nuSiMesgQ;
static OSMesg nuSiMesgBuf[8];
static OSThread siMgrThread;
static u64 siMgrStack[NU_SI_STACK_SIZE/sizeof(u64)];
OSMesgQueue	nuSiMgrMesgQ;
NUCallBackList* nuSiCallBackList = nullptr;

static void nuSiMgrThread(void* arg);

#if !VERSION_JP && !VERSION_IQUE
u8 nuSiMgrInit(void) {
    u8 pattern;
    OSContStatus status[NU_CONT_MAXCONTROLLERS];
    u32 i;

    osCreateMesgQueue(&nuSiMesgQ, nuSiMesgBuf, ARRAY_COUNT(nuSiMesgBuf));
//  osSetEventMesg(OS_EVENT_SI, &nuSiMesgQ, nullptr);
    osSetEventMesg(OS_EVENT_SI, &nuSiMesgQ, OS_MESG_PTR(nullptr));
    osContInit(&nuSiMesgQ, &pattern, &status[0]);

    for (i = 0; i < ARRAY_COUNT(status); i++) {
//      if (((pattern >> i) & 1) && (status[i].errno == 0) && ((status[i].type & 0x1F07) != 5)) {
        if (((pattern >> i) & 1) && (status[i].err_no == 0) && ((status[i].type & 0x1F07) != 5)) {
            pattern &= ~(1 << i);
        }
    }

    OS_EnableThreadEntry((void*) nuSiMgrThread); // [port]
    osCreateThread(&siMgrThread, NU_SI_THREAD_ID, nuSiMgrThread, nullptr, (siMgrStack + NU_SI_STACK_SIZE/sizeof(u64)), NU_SI_THREAD_PRI);
    osStartThread(&siMgrThread);
    return pattern;
}

s32 nuSiSendMesg(NUScMsg mesg, void* dataPtr) {
    OSMesg rtnMesgBuf;
    OSMesgQueue rtnMesgQ;
    NUSiCommonMesg siCommonMesg;

    siCommonMesg.mesg = mesg;
    siCommonMesg.dataPtr = dataPtr;
    siCommonMesg.rtnMesgQ = &rtnMesgQ;

    osCreateMesgQueue(&rtnMesgQ, &rtnMesgBuf, 1);
    OS_SetQueueBlocking(&rtnMesgQ, 1); // [port]

//  osSendMesg(&nuSiMgrMesgQ, &siCommonMesg, OS_MESG_BLOCK);
    osSendMesg(&nuSiMgrMesgQ, OS_MESG_PTR(&siCommonMesg), OS_MESG_BLOCK);
    osRecvMesg(&rtnMesgQ, nullptr, OS_MESG_BLOCK);

    return siCommonMesg.error;
}

void nuSiMgrStop(void) {
    nuSiSendMesg(NU_SI_STOP_MGR_MSG, nullptr);
}

void nuSiMgrRestart(void) {
    osStartThread(&siMgrThread);
}
#endif

void nuSiMgrThread(void* arg) {
    NUScClient siClient;
    OSMesg siMgrMesgBuf[NU_SI_MESG_MAX];
    NUSiCommonMesg* siMesg;
    NUCallBackList** siCallBackListPtr;
    s32 temp;
    u16 majorNo;
    u16 minorNo;

    osCreateMesgQueue(&nuSiMgrMesgQ, siMgrMesgBuf, NU_SI_MESG_MAX);
    OS_SetQueueBlocking(&nuSiMgrMesgQ, 1); // [port]
    nuScAddClient(&siClient, &nuSiMgrMesgQ, NU_SC_RETRACE_MSG);

    while (true) {
        osRecvMesg(&nuSiMgrMesgQ, (OSMesg*) &siMesg, OS_MESG_BLOCK);
        if (OS_ThreadShouldExit()) { // [port]
            return;
        }
        ThreadWatchdog_Beat(WATCHDOG_SI_MANAGER); // [port]

        siCallBackListPtr = &nuSiCallBackList;

        switch (siMesg->mesg) {
            case NU_SC_RETRACE_MSG:
                while (*siCallBackListPtr) {
                    if ((*siCallBackListPtr)->func[0]){
                        temp = (*((*siCallBackListPtr)->func[0]))(siMesg);
                    }
                    if (temp != 0) {
                        break;
                    }
                    siCallBackListPtr = &(*siCallBackListPtr)->next;
                }
                break;
            case NU_SI_STOP_MGR_MSG:
//              osSendMesg(siMesg->rtnMesgQ, nullptr, OS_MESG_BLOCK);
                osSendMesg(siMesg->rtnMesgQ, OS_MESG_PTR(nullptr), OS_MESG_BLOCK);
                nuScResetClientMesgType(&siClient, 0);
                osStopThread(nullptr);
                nuScResetClientMesgType(&siClient, NU_SC_RETRACE_MSG);
                break;
            default:
                majorNo = siMesg->mesg & NU_SI_MSG_MAJOR_NO_MASK;
                minorNo = siMesg->mesg & NU_SI_MSG_MINOR_NO_MASK;

                while (*siCallBackListPtr) {
                    if ((*siCallBackListPtr)->majorNo == majorNo) {
                        if ((*siCallBackListPtr)->funcNum > minorNo) {
                            siMesg->error = (*((*siCallBackListPtr)->func[minorNo]))(siMesg);
                        }
                        if (siMesg->rtnMesgQ != nullptr) {
//                          osSendMesg(siMesg->rtnMesgQ, nullptr, OS_MESG_BLOCK);
                            osSendMesg(siMesg->rtnMesgQ, OS_MESG_PTR(nullptr), OS_MESG_BLOCK);
                        }
                        break;
                    }
                    siCallBackListPtr = &(*siCallBackListPtr)->next;
                }
                break;
        }
    }
}

#if VERSION_JP || VERSION_IQUE
u8 nuSiMgrInit(void) {
    u8 pattern;
    OSContStatus status[NU_CONT_MAXCONTROLLERS];

    osCreateMesgQueue(&nuSiMesgQ, nuSiMesgBuf, ARRAY_COUNT(nuSiMesgBuf));
    osSetEventMesg(OS_EVENT_SI, &nuSiMesgQ, nullptr);
    osContInit(&nuSiMesgQ, &pattern, &status[0]);

    osCreateThread(&siMgrThread, NU_SI_THREAD_ID, nuSiMgrThread, nullptr, (siMgrStack + NU_SI_STACK_SIZE/sizeof(u64)), NU_SI_THREAD_PRI);
    osStartThread(&siMgrThread);
    return pattern;
}

s32 nuSiSendMesg(NUScMsg mesg, void* dataPtr) {
    OSMesg rtnMesgBuf;
    OSMesgQueue rtnMesgQ;
    NUSiCommonMesg siCommonMesg;

    siCommonMesg.mesg = mesg;
    siCommonMesg.dataPtr = dataPtr;
    siCommonMesg.rtnMesgQ = &rtnMesgQ;

    osCreateMesgQueue(&rtnMesgQ, &rtnMesgBuf, 1);

    osSendMesg(&nuSiMgrMesgQ, &siCommonMesg, OS_MESG_BLOCK);
    osRecvMesg(&rtnMesgQ, nullptr, OS_MESG_BLOCK);

    return siCommonMesg.error;
}

void nuSiMgrStop(void) {
    OSMesg rtnMesgBuf;
    OSMesgQueue rtnMesgQ;
    NUSiCommonMesg siCommonMesg;

    siCommonMesg.mesg = 0x7F00;
    siCommonMesg.dataPtr = nullptr;
    siCommonMesg.rtnMesgQ = &rtnMesgQ;

    osCreateMesgQueue(&rtnMesgQ, &rtnMesgBuf, 1);

    osSendMesg(&nuSiMgrMesgQ, &siCommonMesg, OS_MESG_BLOCK);
    osRecvMesg(&rtnMesgQ, nullptr, OS_MESG_BLOCK);
}

void nuSiMgrRestart(void) {
    osStartThread(&siMgrThread);
}
#endif
