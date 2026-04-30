#include "common.h"
#include "gbi_custom.h"
#include "port/patches/Patches.h"

// Patch static Gfx[] arrays declared in source code having G_VTX assets
void port_patch_dl(Gfx* dl) {
    if (dl == NULL) {
        return;
    }
    gbi_resolve_vtx_in_static_dl(dl);
}
