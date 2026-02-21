#include "Merlar.h"

API_CALLABLE(N(AddMerlarHoverMotion)) {
    Npc* npc;

    if (isInitialCall) {
        script->functionTempF[1].f = 0.0f;
        script->functionTempPtr[2] = get_npc_safe(script->owner2.npcID);
    }
    npc = script->functionTempPtr[2];
    npc->verticalRenderOffset = sin_deg(script->functionTempF[1].f) * 5.0f;
    script->functionTempF[1].f = clamp_angle(script->functionTempF[1].f + 4.5f);
    return ApiStatus_BLOCK;
}

EvtScript N(EVS_NpcAuxAI_Merlar) = {
    Return
    End
};

NpcSettings N(NpcSettings_Merlar) = {
    .height = 60,
    .radius = 60,
    .level = ACTOR_LEVEL_NONE,
    .otherAI = &N(EVS_NpcAuxAI_Merlar),
};

EvtScript N(EVS_NpcAux_Merlar) = {
    Return
    End
};

EvtScript N(EVS_NpcIdle_Merlar) = {
    Call(N(AddMerlarHoverMotion))
    Return
    End
};
