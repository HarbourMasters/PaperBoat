#pragma once

#include "Abilities.h"
#include "ActorExt.h"
#include "BattleMenus.h"
#include "BattleOverrides.h"
#include "DataTables.h"
#include "EvtBuffers.h"
#include "InputHistory.h"
#include "Inventory.h"
#include "MapRegistry.h"
#include "MapTextures.h"
#include "Messages.h"
#include "ModSaveData.h"
#include "Panels.h"
#include "Popups.h"
#include "ScriptOverrides.h"
#include "VertexColors.h"
#include "WindowStyles.h"

#ifdef __cplusplus
extern "C" {
#endif

void Mod_UnregisterOwner(const char* owner);

#ifdef __cplusplus
}
#endif
