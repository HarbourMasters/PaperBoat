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

void OS_EnableThreadEntry(void* entry);
void OS_RequestThreadExit(void);
int OS_ThreadShouldExit(void);
void OS_JoinDecompThreads(void);

void port_auWaitRetrace(short** outMsg);
void port_auStartTicker(void);
void port_auStopTicker(void);

void port_auBackendGone(void);

uint32_t port_aiGetLength(void);
int32_t port_aiSetNextBuffer(void* buf, uint32_t size);

void port_auBgmLock(void);
void port_auBgmUnlock(void);

void port_auReleaseFence(void);
void port_auAcquireFence(void);

#ifdef __cplusplus
}
#endif

#endif
