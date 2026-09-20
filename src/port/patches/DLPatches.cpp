#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

#include "common.h"
#include "common_structs.h"
#include "gbi_custom.h"
#include "port/patches/Patches.h"

extern "C" {

// Patch static Gfx[] arrays declared in source code having G_VTX assets
void port_patch_dl(Gfx* dl) {
    if (dl == NULL) {
        return;
    }
    gbi_resolve_vtx_in_static_dl(dl);
}

// Walks a NULL-terminated StaticAnimatorNode* array and patches every node's
// displayList. Use from scenes that relied on DMA_COPY_SEGMENT to make vertex
// data appear at fixed RAM addresses.
void port_patch_animator_tree(StaticAnimatorNode** tree) {
    if (tree == NULL) {
        return;
    }
    for (s32 i = 0; tree[i] != NULL; i++) {
        Gfx* dl = (Gfx*) tree[i]->displayList;
        if (dl != NULL) {
            port_patch_dl(dl);
        }
    }
}

}
