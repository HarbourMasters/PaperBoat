#include "../TTYD64.h"
#include "nm.h"

void TTYD64_InstallNewMaps(void) {
    TTYD64_nm_InstallRegistry();
    TTYD64_nm_InstallGenerated();
}
