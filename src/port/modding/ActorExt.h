#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int32_t Mod_RegisterActorExt(const char* owner, int32_t size);
void* Mod_ActorExt(int32_t handle, int32_t actorID);
void* Mod_PartnerExt(int32_t handle, int32_t partnerID);

#ifdef __cplusplus
}
#endif
