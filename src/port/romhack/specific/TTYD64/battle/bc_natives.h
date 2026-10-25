#pragma once

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

API_CALLABLE(TTYD64_bc_PlayTextPopup);

extern EvtScript TTYD64_Script_MakeEffect;
extern EvtScript TTYD64_bc_EVS_Enemy_ShockHit;
extern EvtScript TTYD64_bc_EVS_Player_HandleEvent;
extern EvtScript TTYD64_DoShockHit;
extern EvtScript TTYD64_UpdateHealthBarPos;
extern EvtScript TTYD64_HandleEvent_Player;
extern EvtScript TTYD64_Script_Ponder_GoBackToHome;
extern EvtScript TTYD64_Script_Ponder_Stylish;

#ifdef __cplusplus
}
#endif
