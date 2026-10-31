#include "port/romhack/specific/TTYD64/TTYD64.h"
#include "port/romhack/specific/TTYD64/world/newmaps.h"

void TTYD64_InstallNewMaps(void) {
    TTYD64_nm_InstallRegistry();
    TTYD64_nm_InstallGenerated();
}
