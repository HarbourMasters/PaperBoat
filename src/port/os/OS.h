#ifndef PORT_OS_H
#define PORT_OS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void OS_CreateThread(void* thread, int32_t id, void (*entry)(void*), void* arg, void* sp, int32_t pri);
void OS_StartThread(void* thread);
void OS_StopThread(void* thread);
void OS_SetThreadPri(void* thread, int32_t pri);

// osStartThread only launches entries enabled here.
void OS_EnableThreadEntry(void* entry);

void OS_RequestThreadExit(void);
int OS_ThreadShouldExit(void);
void OS_JoinDecompThreads(void);

void OS_SetQueueBlocking(void* mq, int enabled);

void OS_BeginShutdown(void);

void OS_StopViTicker(void);

void OS_ViNotifyPresent(void);

int OS_SiService(void);

int OS_ViBlackActive(void);

void port_auBackendGone(void);

uint32_t port_aiGetLength(void);
int32_t port_aiSetNextBuffer(void* buf, uint32_t size);

void port_auBgmLock(void);
void port_auBgmUnlock(void);

void port_auReleaseFence(void);
void port_auAcquireFence(void);

#ifdef __cplusplus
}

#include "libultraship/libultra/message.h"
#include "libultraship/libultra/sptask.h"

extern "C" {

typedef struct OS_BlockedWait {
    unsigned long tid; // SDL thread id
    OSMesgQueue* mq;
    int isSend; // 0 = recv, 1 = send/jam
} OS_BlockedWait;
int OS_MesgSnapshotBlockedWaits(OS_BlockedWait* out, int max);

void OS_SendEventMesg(OSEvent event);
void OS_JamEventMesg(OSEvent event);

OSTask* OS_SpTakePendingTask(void);
OSTask* OS_SpPeekPendingTask(void);

} // extern "C"
#endif

#endif
