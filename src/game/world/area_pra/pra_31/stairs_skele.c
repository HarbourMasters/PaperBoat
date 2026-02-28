#include "pra_31.h"
#include "assets/world.h"

// All 34 stairs skeleton DLs and stairs VTX extracted to OTR via world_pra_31.yml
// DL symbols (pra_31_unk_01_gfx through pra_31_unk_34_gfx) defined in assets/world.h

s32 N(post_gfx_pad)[] = { 0, 0, 0, 0 };

StaticAnimatorNode N(D_80245A90_D847F0) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_29_gfx,
};

StaticAnimatorNode N(D_80245ABC_D8481C) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(D_80245A90_D847F0),
};

StaticAnimatorNode N(D_80245AE8_D84848) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_28_gfx,
};

StaticAnimatorNode N(D_80245B14_D84874) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(D_80245AE8_D84848),
    .sibling = &N(D_80245ABC_D8481C),
};

StaticAnimatorNode N(D_80245B40_D848A0) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_27_gfx,
};

StaticAnimatorNode N(D_80245B6C_D848CC) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(D_80245B40_D848A0),
    .sibling = &N(D_80245B14_D84874),
};

StaticAnimatorNode N(D_80245B98_D848F8) = {
    .pos = { 500.0f, 50.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(89.99725f) },
    .child = &N(D_80245B6C_D848CC),
};

StaticAnimatorNode N(D_80245BC4_D84924) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_25_gfx,
};

StaticAnimatorNode N(D_80245BF0_D84950) = {
    .pos = { 420.0f, 50.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(D_80245BC4_D84924),
    .sibling = &N(D_80245B98_D848F8),
};

StaticAnimatorNode N(D_80245C1C_D8497C) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_21_gfx,
};

StaticAnimatorNode N(D_80245C48_D849A8) = {
    .pos = { 410.0f, 40.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-180.0f) },
    .child = &N(D_80245C1C_D8497C),
    .sibling = &N(D_80245BF0_D84950),
};

StaticAnimatorNode N(D_80245C74_D849D4) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_19_gfx,
};

StaticAnimatorNode N(D_80245CA0_D84A00) = {
    .pos = { 400.0f, 40.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(D_80245C74_D849D4),
    .sibling = &N(D_80245C48_D849A8),
};

StaticAnimatorNode N(D_80245CCC_D84A2C) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_15_gfx,
};

StaticAnimatorNode N(D_80245CF8_D84A58) = {
    .pos = { 390.0f, 30.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-180.0f) },
    .child = &N(D_80245CCC_D84A2C),
    .sibling = &N(D_80245CA0_D84A00),
};

StaticAnimatorNode N(D_80245D24_D84A84) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_13_gfx,
};

StaticAnimatorNode N(D_80245D50_D84AB0) = {
    .pos = { 380.0f, 30.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(D_80245D24_D84A84),
    .sibling = &N(D_80245CF8_D84A58),
};

StaticAnimatorNode N(D_80245D7C_D84ADC) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_11_gfx,
};

StaticAnimatorNode N(D_80245DA8_D84B08) = {
    .pos = { 380.0f, 20.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(89.99725f) },
    .child = &N(D_80245D7C_D84ADC),
    .sibling = &N(D_80245D50_D84AB0),
};

StaticAnimatorNode N(D_80245DD4_D84B34) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_09_gfx,
};

StaticAnimatorNode N(D_80245E00_D84B60) = {
    .pos = { 370.0f, 20.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-180.0f) },
    .child = &N(D_80245DD4_D84B34),
    .sibling = &N(D_80245DA8_D84B08),
};

StaticAnimatorNode N(D_80245E2C_D84B8C) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_07_gfx,
};

StaticAnimatorNode N(D_80245E58_D84BB8) = {
    .pos = { 360.0f, 20.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(D_80245E2C_D84B8C),
    .sibling = &N(D_80245E00_D84B60),
};

StaticAnimatorNode N(D_80245E84_D84BE4) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_05_gfx,
};

StaticAnimatorNode N(D_80245EB0_D84C10) = {
    .pos = { 360.0f, 10.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(89.99725f) },
    .child = &N(D_80245E84_D84BE4),
    .sibling = &N(D_80245E58_D84BB8),
};

StaticAnimatorNode N(D_80245EDC_D84C3C) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_03_gfx,
};

StaticAnimatorNode N(D_80245F08_D84C68) = {
    .pos = { 350.0f, 10.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-180.0f) },
    .child = &N(D_80245EDC_D84C3C),
    .sibling = &N(D_80245EB0_D84C10),
};

StaticAnimatorNode N(D_80245F34_D84C94) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_01_gfx,
};

StaticAnimatorNode N(D_80245F60_D84CC0) = {
    .pos = { 340.0f, 10.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(D_80245F34_D84C94),
    .sibling = &N(D_80245F08_D84C68),
};

StaticAnimatorNode N(D_80245F8C_D84CEC) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_17_gfx,
};

StaticAnimatorNode N(D_80245FB8_D84D18) = {
    .pos = { 400.0f, 30.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(89.99725f) },
    .child = &N(D_80245F8C_D84CEC),
    .sibling = &N(D_80245F60_D84CC0),
};

StaticAnimatorNode N(D_80245FE4_D84D44) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = (void*) pra_31_unk_23_gfx,
};

StaticAnimatorNode N(D_80246010_D84D70) = {
    .pos = { 420.0f, 40.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(89.99725f) },
    .child = &N(D_80245FE4_D84D44),
    .sibling = &N(D_80245FB8_D84D18),
};

StaticAnimatorNode N(D_8024603C_D84D9C) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(D_80246010_D84D70),
};

StaticAnimatorNode N(D_80246068_D84DC8) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(D_8024603C_D84D9C),
};

StaticAnimatorNode* N(AS_Stairs_Skeleton)[] = {
    &N(D_80246068_D84DC8), &N(D_8024603C_D84D9C),
    &N(D_80246010_D84D70), &N(D_80245FE4_D84D44),
    &N(D_80245FB8_D84D18), &N(D_80245F8C_D84CEC),
    &N(D_80245F60_D84CC0), &N(D_80245F34_D84C94),
    &N(D_80245F08_D84C68), &N(D_80245EDC_D84C3C),
    &N(D_80245EB0_D84C10), &N(D_80245E84_D84BE4),
    &N(D_80245E58_D84BB8), &N(D_80245E2C_D84B8C),
    &N(D_80245E00_D84B60), &N(D_80245DD4_D84B34),
    &N(D_80245DA8_D84B08), &N(D_80245D7C_D84ADC),
    &N(D_80245D50_D84AB0), &N(D_80245D24_D84A84),
    &N(D_80245CF8_D84A58), &N(D_80245CCC_D84A2C),
    &N(D_80245CA0_D84A00), &N(D_80245C74_D849D4),
    &N(D_80245C48_D849A8), &N(D_80245C1C_D8497C),
    &N(D_80245BF0_D84950), &N(D_80245BC4_D84924),
    &N(D_80245B98_D848F8), &N(D_80245B6C_D848CC),
    &N(D_80245B40_D848A0), &N(D_80245B14_D84874),
    &N(D_80245AE8_D84848), &N(D_80245ABC_D8481C),
    &N(D_80245A90_D847F0), nullptr
};
