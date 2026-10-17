#include "bc_internal.h"

void TTYD64_InstallBattleCore(void) {
    TTYD64_InstallBattleCoreActorData();
    TTYD64_InstallBattleCoreNewStatuses();
    TTYD64_InstallBattleCoreStatusEffects();
    TTYD64_InstallBattleCorePositions();
    TTYD64_InstallBattleCoreSuperguard();
    TTYD64_InstallBattleCoreStylish();
}
