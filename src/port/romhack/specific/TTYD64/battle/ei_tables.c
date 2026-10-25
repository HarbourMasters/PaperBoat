#include "port/romhack/specific/TTYD64/battle/enemy_items_internal.h"

// clang-format off
const TTYD64DropEntry TTYD64_ItemDropTable_Goomba[] = {
    { 0x8D, 10, 10 },
    { 0x89, 0, 5 },
    { 0x80, 10, 10 },
    { 0x8F, 5, 5 },
    { 0x19C, 5, 5 },
    { 0x112, 2, 1 },
    { 0x17E, 2, 1 },
    { 0x121, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Paragoomba[] = {
    { 0x8A, 5, 5 },
    { 0xA4, 0, 5 },
    { 0x80, 10, 10 },
    { 0x8F, 5, 5 },
    { 0x1A2, 5, 5 },
    { 0x112, 2, 1 },
    { 0x17E, 2, 1 },
    { 0xE1, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_SpikedGoomba[] = {
    { 0x8A, 5, 5 },
    { 0xA4, 0, 5 },
    { 0x80, 10, 10 },
    { 0x8F, 5, 5 },
    { 0x1A1, 5, 5 },
    { 0x112, 2, 1 },
    { 0x17E, 2, 1 },
    { 0x12E, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Ember[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x80, 0, 15 },
    { 0x1A1, 5, 5 },
    { 0x9A, 10, 10 },
    { 0x177, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Magikoopa[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x83, 10, 10 },
    { 0x92, 20, 20 },
    { 0x96, 0, 10 },
    { 0x18D, 2, 2 },
    { 0x129, 0, 2 },
    { 0x143, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_KoopaTroopa[] = {
    { 0x8A, 5, 5 },
    { 0xA4, 0, 5 },
    { 0x90, 20, 20 },
    { 0x18E, 10, 10 },
    { 0x8F, 5, 5 },
    { 0xFF, 2, 1 },
    { 0x184, 2, 1 },
    { 0x140, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Paratroopa[] = {
    { 0x8A, 5, 5 },
    { 0xA4, 0, 5 },
    { 0x90, 20, 20 },
    { 0x18E, 10, 10 },
    { 0x1A2, 5, 5 },
    { 0x10D, 2, 1 },
    { 0x18B, 2, 1 },
    { 0x140, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Fuzzy[] = {
    { 0x8A, 5, 5 },
    { 0xA4, 0, 5 },
    { 0x80, 5, 5 },
    { 0x8F, 5, 5 },
    { 0x199, 10, 10 },
    { 0xEB, 0, 1 },
    { 0x17A, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Bobomb[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x19A, 5, 5 },
    { 0x9A, 20, 20 },
    { 0x19F, 0, 10 },
    { 0xE7, 0, 2 },
    { 0x172, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_BillBlaster[] = {
    { 0x8A, 0, 5 },
    { 0xA4, 0, 5 },
    { 0xFD, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Cleft[] = {
    { 0x8A, 5, 5 },
    { 0xA4, 0, 5 },
    { 0x190, 10, 10 },
    { 0x19C, 5, 5 },
    { 0x1A1, 5, 5 },
    { 0xE8, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_MontyMole[] = {
    { 0x8A, 0, 5 },
    { 0xA4, 0, 10 },
    { 0xF8, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Pokey[] = {
    { 0x8A, 5, 5 },
    { 0xA8, 5, 16 },
    { 0xA4, 0, 5 },
    { 0x84, 10, 10 },
    { 0x1A2, 5, 5 },
    { 0x19C, 5, 5 },
    { 0xEB, 0, 2 },
    { 0x16E, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Bandit[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x8F, 10, 10 },
    { 0x98, 0, 15 },
    { 0xF1, 2, 1 },
    { 0x17F, 2, 1 },
    { 0x104, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_PokeyMummy[] = {
    { 0x95, 5, 5 },
    { 0x89, 0, 15 },
    { 0x190, 5, 5 },
    { 0x199, 5, 5 },
    { 0x19D, 5, 5 },
    { 0xF8, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Swooper[] = {
    { 0x1A3, 0, 10 },
    { 0x195, 0, 5 },
    { 0x199, 15, 15 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_BuzzyBeetle[] = {
    { 0x1A3, 10, 10 },
    { 0x195, 0, 10 },
    { 0x190, 5, 5 },
    { 0x1A1, 5, 5 },
    { 0x19C, 5, 5 },
    { 0x121, 0, 2 },
    { 0x124, 0, 2 },
    { 0x12F, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_ForestFuzzy[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x92, 5, 5 },
    { 0x97, 5, 5 },
    { 0x17A, 0, 2 },
    { 0x180, 0, 1 },
    { 0x130, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_PiranhaPlant[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x9A, 5, 5 },
    { 0x12E, 0, 2 },
    { 0x179, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Bzzap[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x82, 15, 10 },
    { 0x1A2, 5, 5 },
    { 0x19D, 5, 5 },
    { 0x17A, 0, 2 },
    { 0x178, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_HyperGoomba[] = {
    { 0x95, 5, 5 },
    { 0x89, 0, 5 },
    { 0x81, 5, 5 },
    { 0x97, 20, 20 },
    { 0x111, 2, 1 },
    { 0x182, 2, 1 },
    { 0x16D, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_HyperParagoomba[] = {
    { 0x95, 5, 5 },
    { 0x89, 0, 5 },
    { 0x97, 10, 20 },
    { 0x9A, 10, 10 },
    { 0x111, 2, 1 },
    { 0x182, 2, 1 },
    { 0x16D, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_HyperCleft[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x190, 15, 10 },
    { 0x19C, 5, 5 },
    { 0x97, 5, 5 },
    { 0x16D, 0, 2 },
    { 0x17D, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Clubba[] = {
    { 0x1A3, 10, 10 },
    { 0x195, 0, 10 },
    { 0x190, 5, 5 },
    { 0x1A1, 5, 5 },
    { 0x97, 5, 5 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_ShyGuy[] = {
    { 0x8C, 10, 10 },
    { 0xA3, 0, 10 },
    { 0x84, 10, 10 },
    { 0x19F, 0, 15 },
    { 0x98, 0, 10 },
    { 0x140, 0, 2 },
    { 0x105, 0, 1 },
    { 0x18A, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_SkyGuy[] = {
    { 0x1A3, 10, 10 },
    { 0x195, 0, 10 },
    { 0x190, 5, 5 },
    { 0x1A1, 5, 5 },
    { 0x19C, 5, 5 },
    { 0x121, 0, 2 },
    { 0x124, 0, 2 },
    { 0x12F, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_MediGuy[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x83, 10, 10 },
    { 0x92, 5, 20 },
    { 0x96, 0, 10 },
    { 0x18D, 2, 2 },
    { 0x129, 0, 2 },
    { 0x143, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_GrooveGuy[] = {
    { 0x1A3, 10, 10 },
    { 0x195, 0, 10 },
    { 0x80, 10, 10 },
    { 0x1A2, 10, 10 },
    { 0x19C, 10, 10 },
    { 0x129, 0, 1 },
    { 0x143, 0, 1 },
    { 0xEB, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_SpyGuy[] = {
    { 0x1A3, 10, 10 },
    { 0x195, 0, 10 },
    { 0x190, 5, 5 },
    { 0x1A1, 5, 5 },
    { 0x97, 5, 5 },
    { 0x121, 0, 2 },
    { 0x124, 0, 2 },
    { 0x12F, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_PyroGuy[] = {
    { 0x1A3, 0, 10 },
    { 0x195, 0, 5 },
    { 0x80, 15, 15 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_HammerBros[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x82, 15, 10 },
    { 0x19C, 20, 20 },
    { 0x1A1, 5, 5 },
    { 0xF9, 2, 2 },
    { 0x185, 2, 2 },
    { 0x107, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Koopatrol[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x82, 20, 20 },
    { 0x18E, 5, 5 },
    { 0x97, 10, 10 },
    { 0x112, 2, 2 },
    { 0x17E, 2, 2 },
    { 0x177, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_SpearGuy[] = {
    { 0x8C, 0, 5 },
    { 0xA3, 0, 5 },
    { 0x80, 0, 5 },
    { 0x92, 0, 5 },
    { 0x9A, 0, 5 },
    { 0x130, 0, 2 },
    { 0x180, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_JungleFuzzy[] = {
    { 0x1A3, 5, 5 },
    { 0x195, 0, 5 },
    { 0x8F, 15, 15 },
    { 0x1A2, 5, 5 },
    { 0x182, 2, 1 },
    { 0x16E, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_SpikeTop[] = {
    { 0x1A3, 10, 10 },
    { 0x195, 0, 10 },
    { 0x190, 5, 5 },
    { 0x1A1, 5, 5 },
    { 0x97, 5, 5 },
    { 0x121, 0, 2 },
    { 0x124, 0, 2 },
    { 0x12F, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_HurtPlant[] = {
    { 0x8C, 0, 5 },
    { 0xA3, 0, 10 },
    { 0x105, 0, 1 },
    { 0x18A, 0, 1 },
    { 0x16F, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_MBush[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x92, 5, 5 },
    { 0x97, 5, 5 },
    { 0x17A, 0, 2 },
    { 0x180, 0, 1 },
    { 0x130, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_PutridPiranha[] = {
    { 0x8C, 0, 5 },
    { 0xA3, 0, 10 },
    { 0xF8, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_LavaBubble[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x80, 0, 15 },
    { 0x1A1, 5, 5 },
    { 0x199, 10, 10 },
    { 0x177, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Lakitu[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x82, 10, 10 },
    { 0x9A, 5, 5 },
    { 0x8B, 10, 10 },
    { 0x129, 0, 2 },
    { 0x143, 0, 2 },
    { 0x178, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Spiny[] = {
    { 0x1A3, 10, 10 },
    { 0x195, 0, 10 },
    { 0x190, 5, 5 },
    { 0x1A1, 5, 5 },
    { 0x19C, 5, 5 },
    { 0x121, 0, 2 },
    { 0x124, 0, 2 },
    { 0x12F, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_RuffPuff[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x82, 15, 10 },
    { 0x1A2, 5, 5 },
    { 0x19D, 5, 5 },
    { 0x17A, 0, 2 },
    { 0x178, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_CrazeeDayzee[] = {
    { 0x8C, 10, 10 },
    { 0xA3, 0, 10 },
    { 0x84, 10, 10 },
    { 0x19F, 0, 15 },
    { 0x98, 0, 10 },
    { 0x140, 0, 2 },
    { 0x105, 0, 1 },
    { 0x18A, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_AmazyDayzee[] = {
    { 0x8E, 10, 10 },
    { 0xA2, 0, 10 },
    { 0x83, 10, 10 },
    { 0x19F, 0, 15 },
    { 0x96, 0, 10 },
    { 0x140, 0, 2 },
    { 0x105, 0, 2 },
    { 0x18A, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_DarkKoopa[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x19A, 10, 10 },
    { 0x18E, 10, 10 },
    { 0x19D, 20, 20 },
    { 0xFF, 2, 1 },
    { 0x185, 2, 1 },
    { 0x11A, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_DarkParatroopa[] = {
    { 0x8C, 10, 10 },
    { 0xA3, 0, 5 },
    { 0x80, 20, 20 },
    { 0x9A, 10, 10 },
    { 0xE7, 2, 2 },
    { 0x18D, 2, 2 },
    { 0xE1, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Gloomba[] = {
    { 0x8C, 10, 10 },
    { 0xA3, 0, 5 },
    { 0x80, 20, 20 },
    { 0x1A2, 5, 5 },
    { 0x8B, 10, 10 },
    { 0xE7, 2, 2 },
    { 0x18D, 2, 2 },
    { 0x121, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_SpikedGloomba[] = {
    { 0x8C, 10, 10 },
    { 0xA3, 0, 5 },
    { 0x80, 20, 20 },
    { 0x9A, 5, 5 },
    { 0x199, 10, 10 },
    { 0xE7, 2, 2 },
    { 0x18D, 2, 2 },
    { 0x12E, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Paragloomba[] = {
    { 0x8C, 10, 10 },
    { 0xA3, 0, 5 },
    { 0x80, 20, 20 },
    { 0x1A2, 10, 10 },
    { 0xE7, 2, 2 },
    { 0x18D, 2, 2 },
    { 0xE1, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Swoopula[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x19A, 5, 5 },
    { 0x97, 5, 5 },
    { 0x9A, 15, 15 },
    { 0xE1, 0, 2 },
    { 0x107, 0, 2 },
    { 0x18C, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Duplighost[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x19A, 15, 10 },
    { 0x1A2, 5, 5 },
    { 0x12E, 0, 2 },
    { 0x179, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Gulpit[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x190, 10, 15 },
    { 0x19C, 5, 5 },
    { 0x92, 5, 5 },
    { 0xE8, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_FrostPiranha[] = {
    { 0x8C, 0, 5 },
    { 0xA3, 0, 10 },
    { 0x179, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_WhiteClubba[] = {
    { 0x8C, 10, 10 },
    { 0xA3, 0, 10 },
    { 0x82, 20, 20 },
    { 0x92, 10, 10 },
    { 0x97, 10, 10 },
    { 0x113, 2, 1 },
    { 0x187, 2, 1 },
    { 0x11A, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_BonyBeetle[] = {
    { 0x95, 10, 10 },
    { 0xA3, 0, 10 },
    { 0x82, 10, 10 },
    { 0x92, 10, 10 },
    { 0x97, 5, 5 },
    { 0xE2, 1, 1 },
    { 0x183, 1, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_DryBones[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x19A, 5, 5 },
    { 0x9A, 20, 20 },
    { 0x19F, 0, 10 },
    { 0xE7, 0, 2 },
    { 0x172, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_BombshellBlaster[] = {
    { 0x8C, 0, 5 },
    { 0xA3, 0, 5 },
    { 0xFD, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_StoneChomp[] = {
    { 0x8C, 0, 10 },
    { 0xA3, 0, 10 },
    { 0x1A1, 10, 10 },
    { 0xFB, 2, 1 },
    { 0x181, 2, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_BadgeBandit[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x19A, 5, 5 },
    { 0x8F, 10, 10 },
    { 0x98, 0, 15 },
    { 0xF1, 2, 2 },
    { 0x17F, 2, 2 },
    { 0x104, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_DarkLakitu[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x82, 20, 20 },
    { 0x1A2, 5, 5 },
    { 0x8B, 10, 10 },
    { 0x129, 0, 2 },
    { 0x143, 0, 2 },
    { 0x178, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_SkyBlueSpiny[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x82, 15, 10 },
    { 0x9A, 5, 5 },
    { 0x1A1, 5, 5 },
    { 0x179, 0, 2 },
    { 0x170, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_DarkHammerBros[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x82, 15, 10 },
    { 0x19C, 20, 20 },
    { 0x1A1, 5, 5 },
    { 0xF9, 2, 2 },
    { 0x185, 2, 2 },
    { 0x107, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_DarkMontyMole[] = {
    { 0x8A, 0, 5 },
    { 0xA4, 0, 10 },
    { 0xF8, 0, 1 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_DarkMagikoopa[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x83, 20, 10 },
    { 0x92, 20, 20 },
    { 0x96, 0, 10 },
    { 0x18D, 2, 2 },
    { 0x129, 0, 2 },
    { 0x143, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_PoisonPuff[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x82, 15, 10 },
    { 0x1A2, 5, 5 },
    { 0x1A1, 5, 5 },
    { 0x179, 0, 2 },
    { 0x170, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_DarkEmber[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x80, 10, 15 },
    { 0x1A1, 5, 5 },
    { 0x9A, 10, 10 },
    { 0x177, 0, 2 },
};
const TTYD64DropEntry TTYD64_ItemDropTable_Swampire[] = {
    { 0x8C, 5, 5 },
    { 0xA3, 0, 5 },
    { 0x19A, 5, 5 },
    { 0x97, 5, 5 },
    { 0x1A2, 15, 15 },
    { 0xE1, 0, 2 },
    { 0x107, 0, 2 },
    { 0x114, 0, 1 },
};

static const struct {
    const TTYD64DropEntry* entries;
    s32 count;
} sDropTables[TTYD64_DROP_COUNT] = {
    { NULL, 0 },
    { TTYD64_ItemDropTable_Goomba, ARRAY_COUNT(TTYD64_ItemDropTable_Goomba) },
    { TTYD64_ItemDropTable_Paragoomba, ARRAY_COUNT(TTYD64_ItemDropTable_Paragoomba) },
    { TTYD64_ItemDropTable_SpikedGoomba, ARRAY_COUNT(TTYD64_ItemDropTable_SpikedGoomba) },
    { TTYD64_ItemDropTable_Ember, ARRAY_COUNT(TTYD64_ItemDropTable_Ember) },
    { TTYD64_ItemDropTable_Magikoopa, ARRAY_COUNT(TTYD64_ItemDropTable_Magikoopa) },
    { TTYD64_ItemDropTable_KoopaTroopa, ARRAY_COUNT(TTYD64_ItemDropTable_KoopaTroopa) },
    { TTYD64_ItemDropTable_Paratroopa, ARRAY_COUNT(TTYD64_ItemDropTable_Paratroopa) },
    { TTYD64_ItemDropTable_Fuzzy, ARRAY_COUNT(TTYD64_ItemDropTable_Fuzzy) },
    { TTYD64_ItemDropTable_Bobomb, ARRAY_COUNT(TTYD64_ItemDropTable_Bobomb) },
    { TTYD64_ItemDropTable_BillBlaster, ARRAY_COUNT(TTYD64_ItemDropTable_BillBlaster) },
    { TTYD64_ItemDropTable_Cleft, ARRAY_COUNT(TTYD64_ItemDropTable_Cleft) },
    { TTYD64_ItemDropTable_MontyMole, ARRAY_COUNT(TTYD64_ItemDropTable_MontyMole) },
    { TTYD64_ItemDropTable_Pokey, ARRAY_COUNT(TTYD64_ItemDropTable_Pokey) },
    { TTYD64_ItemDropTable_Bandit, ARRAY_COUNT(TTYD64_ItemDropTable_Bandit) },
    { TTYD64_ItemDropTable_PokeyMummy, ARRAY_COUNT(TTYD64_ItemDropTable_PokeyMummy) },
    { TTYD64_ItemDropTable_Swooper, ARRAY_COUNT(TTYD64_ItemDropTable_Swooper) },
    { TTYD64_ItemDropTable_BuzzyBeetle, ARRAY_COUNT(TTYD64_ItemDropTable_BuzzyBeetle) },
    { TTYD64_ItemDropTable_ForestFuzzy, ARRAY_COUNT(TTYD64_ItemDropTable_ForestFuzzy) },
    { TTYD64_ItemDropTable_PiranhaPlant, ARRAY_COUNT(TTYD64_ItemDropTable_PiranhaPlant) },
    { TTYD64_ItemDropTable_Bzzap, ARRAY_COUNT(TTYD64_ItemDropTable_Bzzap) },
    { TTYD64_ItemDropTable_HyperGoomba, ARRAY_COUNT(TTYD64_ItemDropTable_HyperGoomba) },
    { TTYD64_ItemDropTable_HyperParagoomba, ARRAY_COUNT(TTYD64_ItemDropTable_HyperParagoomba) },
    { TTYD64_ItemDropTable_HyperCleft, ARRAY_COUNT(TTYD64_ItemDropTable_HyperCleft) },
    { TTYD64_ItemDropTable_Clubba, ARRAY_COUNT(TTYD64_ItemDropTable_Clubba) },
    { TTYD64_ItemDropTable_ShyGuy, ARRAY_COUNT(TTYD64_ItemDropTable_ShyGuy) },
    { TTYD64_ItemDropTable_SkyGuy, ARRAY_COUNT(TTYD64_ItemDropTable_SkyGuy) },
    { TTYD64_ItemDropTable_MediGuy, ARRAY_COUNT(TTYD64_ItemDropTable_MediGuy) },
    { TTYD64_ItemDropTable_GrooveGuy, ARRAY_COUNT(TTYD64_ItemDropTable_GrooveGuy) },
    { TTYD64_ItemDropTable_SpyGuy, ARRAY_COUNT(TTYD64_ItemDropTable_SpyGuy) },
    { TTYD64_ItemDropTable_PyroGuy, ARRAY_COUNT(TTYD64_ItemDropTable_PyroGuy) },
    { TTYD64_ItemDropTable_HammerBros, ARRAY_COUNT(TTYD64_ItemDropTable_HammerBros) },
    { TTYD64_ItemDropTable_Koopatrol, ARRAY_COUNT(TTYD64_ItemDropTable_Koopatrol) },
    { TTYD64_ItemDropTable_SpearGuy, ARRAY_COUNT(TTYD64_ItemDropTable_SpearGuy) },
    { TTYD64_ItemDropTable_JungleFuzzy, ARRAY_COUNT(TTYD64_ItemDropTable_JungleFuzzy) },
    { TTYD64_ItemDropTable_SpikeTop, ARRAY_COUNT(TTYD64_ItemDropTable_SpikeTop) },
    { TTYD64_ItemDropTable_HurtPlant, ARRAY_COUNT(TTYD64_ItemDropTable_HurtPlant) },
    { TTYD64_ItemDropTable_MBush, ARRAY_COUNT(TTYD64_ItemDropTable_MBush) },
    { TTYD64_ItemDropTable_PutridPiranha, ARRAY_COUNT(TTYD64_ItemDropTable_PutridPiranha) },
    { TTYD64_ItemDropTable_LavaBubble, ARRAY_COUNT(TTYD64_ItemDropTable_LavaBubble) },
    { TTYD64_ItemDropTable_Lakitu, ARRAY_COUNT(TTYD64_ItemDropTable_Lakitu) },
    { TTYD64_ItemDropTable_Spiny, ARRAY_COUNT(TTYD64_ItemDropTable_Spiny) },
    { TTYD64_ItemDropTable_RuffPuff, ARRAY_COUNT(TTYD64_ItemDropTable_RuffPuff) },
    { TTYD64_ItemDropTable_CrazeeDayzee, ARRAY_COUNT(TTYD64_ItemDropTable_CrazeeDayzee) },
    { TTYD64_ItemDropTable_AmazyDayzee, ARRAY_COUNT(TTYD64_ItemDropTable_AmazyDayzee) },
    { TTYD64_ItemDropTable_DarkKoopa, ARRAY_COUNT(TTYD64_ItemDropTable_DarkKoopa) },
    { TTYD64_ItemDropTable_DarkParatroopa, ARRAY_COUNT(TTYD64_ItemDropTable_DarkParatroopa) },
    { TTYD64_ItemDropTable_Gloomba, ARRAY_COUNT(TTYD64_ItemDropTable_Gloomba) },
    { TTYD64_ItemDropTable_SpikedGloomba, ARRAY_COUNT(TTYD64_ItemDropTable_SpikedGloomba) },
    { TTYD64_ItemDropTable_Paragloomba, ARRAY_COUNT(TTYD64_ItemDropTable_Paragloomba) },
    { TTYD64_ItemDropTable_Swoopula, ARRAY_COUNT(TTYD64_ItemDropTable_Swoopula) },
    { TTYD64_ItemDropTable_Duplighost, ARRAY_COUNT(TTYD64_ItemDropTable_Duplighost) },
    { TTYD64_ItemDropTable_Gulpit, ARRAY_COUNT(TTYD64_ItemDropTable_Gulpit) },
    { TTYD64_ItemDropTable_FrostPiranha, ARRAY_COUNT(TTYD64_ItemDropTable_FrostPiranha) },
    { TTYD64_ItemDropTable_WhiteClubba, ARRAY_COUNT(TTYD64_ItemDropTable_WhiteClubba) },
    { TTYD64_ItemDropTable_BonyBeetle, ARRAY_COUNT(TTYD64_ItemDropTable_BonyBeetle) },
    { TTYD64_ItemDropTable_DryBones, ARRAY_COUNT(TTYD64_ItemDropTable_DryBones) },
    { TTYD64_ItemDropTable_BombshellBlaster, ARRAY_COUNT(TTYD64_ItemDropTable_BombshellBlaster) },
    { TTYD64_ItemDropTable_StoneChomp, ARRAY_COUNT(TTYD64_ItemDropTable_StoneChomp) },
    { TTYD64_ItemDropTable_BadgeBandit, ARRAY_COUNT(TTYD64_ItemDropTable_BadgeBandit) },
    { TTYD64_ItemDropTable_DarkLakitu, ARRAY_COUNT(TTYD64_ItemDropTable_DarkLakitu) },
    { TTYD64_ItemDropTable_SkyBlueSpiny, ARRAY_COUNT(TTYD64_ItemDropTable_SkyBlueSpiny) },
    { TTYD64_ItemDropTable_DarkHammerBros, ARRAY_COUNT(TTYD64_ItemDropTable_DarkHammerBros) },
    { TTYD64_ItemDropTable_DarkMontyMole, ARRAY_COUNT(TTYD64_ItemDropTable_DarkMontyMole) },
    { TTYD64_ItemDropTable_DarkMagikoopa, ARRAY_COUNT(TTYD64_ItemDropTable_DarkMagikoopa) },
    { TTYD64_ItemDropTable_PoisonPuff, ARRAY_COUNT(TTYD64_ItemDropTable_PoisonPuff) },
    { TTYD64_ItemDropTable_DarkEmber, ARRAY_COUNT(TTYD64_ItemDropTable_DarkEmber) },
    { TTYD64_ItemDropTable_Swampire, ARRAY_COUNT(TTYD64_ItemDropTable_Swampire) },
};

const s32 TTYD64_ItemHog_ItemTable[10] = {
    0x8D, 0x8D, 0x8D, 0x8A, 0xA4, 0x80, 0x98, 0x90, 0x8B, 0x89,
};
// clang-format on

const TTYD64DropEntry* TTYD64_GetDropTable(s32 dropTable, s32* count) {
    if (dropTable <= TTYD64_DROP_NONE || dropTable >= TTYD64_DROP_COUNT) {
        *count = 0;
        return NULL;
    }
    *count = sDropTables[dropTable].count;
    return sDropTables[dropTable].entries;
}
