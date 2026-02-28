#include "animation_script.h"
#include "assets/world.h"

StaticAnimatorNode N(D_80248AA0_971C60) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .vertexStartOffset = 0x02EE,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248ACC_971C8C) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .sibling = &N(D_80248AA0_971C60),
    .vertexStartOffset = 0x02BC,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248AF8_971CB8) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .sibling = &N(D_80248ACC_971C8C),
    .vertexStartOffset = 0x028A,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248B24_971CE4) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .sibling = &N(D_80248AF8_971CB8),
    .vertexStartOffset = 0x0258,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248B50_971D10) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .sibling = &N(D_80248B24_971CE4),
    .vertexStartOffset = 0x0226,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248B7C_971D3C) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .sibling = &N(D_80248B50_971D10),
    .vertexStartOffset = 0x01F4,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248BA8_971D68) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .sibling = &N(D_80248B7C_971D3C),
    .vertexStartOffset = 0x01C2,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248BD4_971D94) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .sibling = &N(D_80248BA8_971D68),
    .vertexStartOffset = 0x0190,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248C00_971DC0) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .sibling = &N(D_80248BD4_971D94),
    .vertexStartOffset = 0x015E,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248C2C_971DEC) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .sibling = &N(D_80248C00_971DC0),
    .vertexStartOffset = 0x012C,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248C58_971E18) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .sibling = &N(D_80248C2C_971DEC),
    .vertexStartOffset = 0x00FA,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248C84_971E44) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .sibling = &N(D_80248C58_971E18),
    .vertexStartOffset = 0x00C8,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248CB0_971E70) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .sibling = &N(D_80248C84_971E44),
    .vertexStartOffset = 0x0096,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248CDC_971E9C) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .sibling = &N(D_80248CB0_971E70),
    .vertexStartOffset = 0x0064,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248D08_971EC8) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .sibling = &N(D_80248CDC_971E9C),
    .vertexStartOffset = 0x0032,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248D34_971EF4) = {
    .displayList = (void*) toad_house_blanket_gfx,
    .sibling = &N(D_80248D08_971EC8),
    .vertexStartOffset = 0,
    .vtxList = (Vtx*) toad_house_blanket_vtx,
};

StaticAnimatorNode N(D_80248D60_971F20) = {
    .child = &N(D_80248D34_971EF4),
    .vertexStartOffset = -1,
};

StaticAnimatorNode* N(D_80248D8C_971F4C)[] = {
    &N(D_80248D60_971F20), &N(D_80248D34_971EF4), &N(D_80248D08_971EC8), &N(D_80248CDC_971E9C),
    &N(D_80248CB0_971E70), &N(D_80248C84_971E44), &N(D_80248C58_971E18), &N(D_80248C2C_971DEC),
    &N(D_80248C00_971DC0), &N(D_80248BD4_971D94), &N(D_80248BA8_971D68), &N(D_80248B7C_971D3C),
    &N(D_80248B50_971D10), &N(D_80248B24_971CE4), &N(D_80248AF8_971CB8), &N(D_80248ACC_971C8C),
    &N(D_80248AA0_971C60), nullptr
};

// blanket vtx, gfx, and texture extracted to OTR via world_mac_01.yml
// toad_house_blanket_vtx, toad_house_blanket_gfx, toad_house_blanket_img defined in assets/world.h

AnimScript N(ANS_ToadHouseBlanket) = {
        as_DisableMirroring
        as_SetRotation(1, 0.0, 0.0, 0.0)
        as_SetPos(1, 0, 0, 0)
        as_SetScale(1, 1.0, 1.0, 1.0)
        as_SetRotation(2, 0.0, 0.0, 0.0)
        as_SetPos(2, 0, 0, 0)
        as_SetScale(2, 1.0, 1.0, 1.0)
        as_SetRotation(3, 0.0, 0.0, 0.0)
        as_SetPos(3, 0, 0, 0)
        as_SetScale(3, 1.0, 1.0, 1.0)
        as_SetRotation(4, 0.0, 0.0, 0.0)
        as_SetPos(4, 0, 0, 0)
        as_SetScale(4, 1.0, 1.0, 1.0)
        as_SetRotation(5, 0.0, 0.0, 0.0)
        as_SetPos(5, 0, 0, 0)
        as_SetScale(5, 1.0, 1.0, 1.0)
        as_SetRotation(6, 0.0, 0.0, 0.0)
        as_SetPos(6, 0, 0, 0)
        as_SetScale(6, 1.0, 1.0, 1.0)
        as_SetRotation(7, 0.0, 0.0, 0.0)
        as_SetPos(7, 0, 0, 0)
        as_SetScale(7, 1.0, 1.0, 1.0)
        as_SetRotation(8, 0.0, 0.0, 0.0)
        as_SetPos(8, 0, 0, 0)
        as_SetScale(8, 1.0, 1.0, 1.0)
        as_SetRotation(9, 0.0, 0.0, 0.0)
        as_SetPos(9, 0, 0, 0)
        as_SetScale(9, 1.0, 1.0, 1.0)
        as_SetRotation(10, 0.0, 0.0, 0.0)
        as_SetPos(10, 0, 0, 0)
        as_SetScale(10, 1.0, 1.0, 1.0)
        as_SetRotation(11, 0.0, 0.0, 0.0)
        as_SetPos(11, 0, 0, 0)
        as_SetScale(11, 1.0, 1.0, 1.0)
        as_SetRotation(12, 0.0, 0.0, 0.0)
        as_SetPos(12, 0, 0, 0)
        as_SetScale(12, 1.0, 1.0, 1.0)
        as_SetRotation(13, 0.0, 0.0, 0.0)
        as_SetPos(13, 0, 0, 0)
        as_SetScale(13, 1.0, 1.0, 1.0)
        as_SetRotation(14, 0.0, 0.0, 0.0)
        as_SetPos(14, 0, 0, 0)
        as_SetScale(14, 1.0, 1.0, 1.0)
        as_SetRotation(15, 0.0, 0.0, 0.0)
        as_SetPos(15, 0, 0, 0)
        as_SetScale(15, 1.0, 1.0, 1.0)
        as_SetRotation(16, 0.0, 0.0, 0.0)
        as_SetPos(16, 0, 0, 0)
        as_SetScale(16, 1.0, 1.0, 1.0)
        as_SetRotation(17, 0.0, 0.0, 0.0)
        as_SetPos(17, 0, 0, 0)
        as_SetScale(17, 1.0, 1.0, 1.0)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
        as_Wait(1)
    as_Restart
    as_End
};
