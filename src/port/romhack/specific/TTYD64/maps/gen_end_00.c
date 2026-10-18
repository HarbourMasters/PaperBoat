#include "common.h"
#include "effects.h"
#include "entity.h"
#include "foliage.h"
#include "map.h"
#include "npc.h"
#include "script_api/map.h"
#include <string.h>
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/maps/maps.h"

extern CreditsEntry end_00_Credits_Jobs[];
extern EvtScript end_00_EVS_ShowCredits_Names;

API_CALLABLE(end_00_ShowCreditList);

extern u8 TTYD64_end_00_String_Task_Logo[];
extern u8 TTYD64_end_00_String_MRTNEWB[];
extern u8 TTYD64_end_00_String_messy[];
extern CreditsEntry TTYD64_end_00_CreditList_Titles[];
extern CreditsEntry TTYD64_end_00_CreditList_Names[];
extern u8 TTYD64_end_00_String_Task_Sprites_ItemsAndRecipes[];
extern u8 TTYD64_end_00_String_Task_Sprites_NewEnemies[];
extern u8 TTYD64_end_00_String_SpecialThanks[];
extern u8 TTYD64_end_00_String_EvelynHorstman[];
extern u8 TTYD64_end_00_String_Marceline[];
extern u8 TTYD64_end_00_String_Testers[];
extern u8 TTYD64_end_00_String_OrangeIsBorange[];
extern u8 TTYD64_end_00_String_Ja_and_Shade[];
extern u8 TTYD64_end_00_String_SwordBolt[];
extern u8 TTYD64_end_00_String_SquidJesus[];
extern u8 TTYD64_end_00_String_1upShyGuy[];
extern u8 TTYD64_end_00_String_Fatguy[];
extern u8 TTYD64_end_00_String_XModxGodX[];
extern u8 TTYD64_end_00_String_StevenBlue[];
extern u8 TTYD64_end_00_String_ShyGuyXXL[];
extern u8 TTYD64_end_00_String_pieordie1[];
extern u8 TTYD64_end_00_String_JasonParker[];
extern u8 TTYD64_end_00_String_Lunarman[];
extern u8 TTYD64_end_00_String_NomadNamrod[];
extern u8 TTYD64_end_00_String_Dreamkazoo[];
extern u8 TTYD64_end_00_String_Jdaster[];
extern u8 TTYD64_end_00_String_CrackerJack[];
extern u8 TTYD64_end_00_String_Zephiles[];
extern u8 TTYD64_end_00_String_Mania[];
extern u8 TTYD64_end_00_String_Rayne[];
extern u8 TTYD64_end_00_String_Awestin[];
extern u8 TTYD64_end_00_String_WhyCron[];
extern u8 TTYD64_end_00_String_ZeroZXL[];
extern u8 TTYD64_end_00_String_Reborn[];
extern u8 TTYD64_end_00_String_DiaFiend[];
extern u8 TTYD64_end_00_String_BossBuzz[];
extern u8 TTYD64_end_00_String_Link75[];
extern u8 TTYD64_end_00_String_Riviera[];
extern u8 TTYD64_end_00_String_Matoi[];
extern EvtScript TTYD64_end_00_Script_ShowNames;
extern u8 TTYD64_end_00_String_Drew[];
extern u8 TTYD64_end_00_String_Patrons[];
extern u8 TTYD64_end_00_String_ZoomZike[];
extern u8 TTYD64_end_00_String_Task_Dex[];
extern u8 TTYD64_end_00_String_Task_Sprites_Misc[];
extern u8 TTYD64_end_00_String_Task_Sprites_NewBadges[];
extern u8 TTYD64_end_00_String_TylerBravenst[];
extern u8 TTYD64_end_00_String_Typo[];
extern u8 TTYD64_end_00_String_AwakenedEmperor[];
extern u8 TTYD64_end_00_String_Kevin[];
extern u8 TTYD64_end_00_String_Decomp[];
extern u8 TTYD64_end_00_String_BlueWarrior[];
extern u8 TTYD64_end_00_String_Task_ExtraMusic[];
extern u8 TTYD64_end_00_String_Ponderman[];
extern u8 TTYD64_end_00_String_Tericonix[];
extern u8 TTYD64_end_00_String_Zioreturns[];
extern u8 TTYD64_end_00_String_BlackJack[];
extern u8 TTYD64_end_00_String_Task_BG[];
extern u8 TTYD64_end_00_String_Fraiseffddf4[];
extern u8 TTYD64_end_00_String_TwoPieRadian[];
extern u8 TTYD64_end_00_String_GeminiSaint_and_Alop[];
extern u8 TTYD64_end_00_String_Washudoll[];
extern u8 TTYD64_end_00_String_chefshadow94[];
extern u8 TTYD64_end_00_String_GaganAtwal[];
extern u8 TTYD64_end_00_String_TeamLuxk[];
extern u8 TTYD64_end_00_String_Starzee[];
extern u8 TTYD64_end_00_String_Mishy[];
extern u8 TTYD64_end_00_String_Moemura[];
extern u8 TTYD64_end_00_String_Samevi[];
extern u8 TTYD64_end_00_String_Task_MIDIs[];
extern u8 TTYD64_end_00_String_Brotenko[];
extern u8 TTYD64_end_00_String_Griscuit[];
extern u8 TTYD64_end_00_String_Bloop_and_ForrestRiedi[];
extern u8 TTYD64_end_00_String_Zarexel[];
extern u8 TTYD64_end_00_String_Kappy[];
extern u8 TTYD64_end_00_String_Task_Music[];

// clang-format off
u8 TTYD64_end_00_String_Task_Logo[] = {
    0xFF, 0x00, 0x04, 0x0B, 0x0E, 0x06, 0x0E, 0xFD
};

u8 TTYD64_end_00_String_MRTNEWB[] = {
    0xFF, 0x00, 0x03, 0x0C, 0x11, 0x13, 0xF7, 0x0D, 0x04, 0x16, 0x01, 0xFD
};

u8 TTYD64_end_00_String_messy[] = {
    0xFF, 0x00, 0x03, 0x0C, 0x04, 0x12, 0x12, 0x18, 0xFD
};

CreditsEntry TTYD64_end_00_CreditList_Titles[] = {
    { .msgID = 0, .posX = 0, .posY = 0, .palette = 0, .appearMode = 0, .appearTime = 0, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 0, .vanishMode = 0, .vanishTime = 0, .perCharDelayOut = 0, .next = 235, .flags = 0 },
    { .msgID = 0x2E0005, .posX = 160, .posY = 166, .palette = 0, .appearMode = 4, .appearTime = 40, .perCharDelayIn = 2, .holdMode = 0, .holdTime = 176, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 248, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 166, .palette = 0, .appearMode = 4, .appearTime = 40, .perCharDelayIn = 2, .holdMode = 0, .holdTime = 176, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 248, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 166, .palette = 0, .appearMode = 4, .appearTime = 40, .perCharDelayIn = 2, .holdMode = 0, .holdTime = 176, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 248, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 166, .palette = 0, .appearMode = 4, .appearTime = 40, .perCharDelayIn = 2, .holdMode = 0, .holdTime = 176, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 248, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 166, .palette = 0, .appearMode = 4, .appearTime = 40, .perCharDelayIn = 2, .holdMode = 0, .holdTime = 176, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 248, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 166, .palette = 0, .appearMode = 4, .appearTime = 40, .perCharDelayIn = 2, .holdMode = 0, .holdTime = 176, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 248, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 166, .palette = 0, .appearMode = 4, .appearTime = 40, .perCharDelayIn = 2, .holdMode = 0, .holdTime = 176, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 248, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 166, .palette = 0, .appearMode = 4, .appearTime = 40, .perCharDelayIn = 2, .holdMode = 0, .holdTime = 176, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 248, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 166, .palette = 0, .appearMode = 4, .appearTime = 40, .perCharDelayIn = 2, .holdMode = 0, .holdTime = 176, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 248, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 166, .palette = 0, .appearMode = 4, .appearTime = 40, .perCharDelayIn = 2, .holdMode = 0, .holdTime = 176, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 248, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 166, .palette = 0, .appearMode = 4, .appearTime = 40, .perCharDelayIn = 2, .holdMode = 0, .holdTime = 389, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 461, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 166, .palette = 0, .appearMode = 4, .appearTime = 40, .perCharDelayIn = 2, .holdMode = 0, .holdTime = 176, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 248, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 166, .palette = 0, .appearMode = 4, .appearTime = 40, .perCharDelayIn = 2, .holdMode = 0, .holdTime = 784, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 848, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 166, .palette = 0, .appearMode = 4, .appearTime = 40, .perCharDelayIn = 2, .holdMode = 0, .holdTime = 2021, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 2140, .flags = 1 },
    { .msgID = 0, .posX = 0, .posY = 0, .palette = 0, .appearMode = 4, .appearTime = 0, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 0, .vanishMode = 0, .vanishTime = 0, .perCharDelayOut = 0, .next = -1, .flags = 0 },
};

CreditsEntry TTYD64_end_00_CreditList_Names[] = {
    { .msgID = 0, .posX = 0, .posY = 0, .palette = 0, .appearMode = 0, .appearTime = 0, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 0, .vanishMode = 0, .vanishTime = 0, .perCharDelayOut = 0, .next = 275, .flags = 0 },
    { .msgID = 0x2E0006, .posX = 160, .posY = 195, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 320, .flags = 1 },
    { .msgID = 0x2E0006, .posX = 160, .posY = 195, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 63, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 214, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 195, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 104, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 238, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 195, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 104, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 222, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 195, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 195, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 245, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 238, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 195, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 152, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 238, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 195, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 152, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 272, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 195, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 238, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 195, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 256, .flags = 1 },
    { .msgID = 0, .posX = 74, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 243, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 74, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 243, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 206, .flags = 1 },
    { .msgID = 0, .posX = 74, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 243, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 254, .flags = 1 },
    { .msgID = 0, .posX = 74, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 243, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 74, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 160, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 238, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 206, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 206, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 206, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 238, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 206, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 206, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 206, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 206, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 206, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 206, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 206, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 206, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 206, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 186, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 99, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 0, .flags = 1 },
    { .msgID = 0, .posX = 211, .posY = 205, .palette = 1, .appearMode = 0, .appearTime = 40, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 136, .vanishMode = 0, .vanishTime = 30, .perCharDelayOut = 0, .next = 206, .flags = 1 },
    { .msgID = 0, .posX = 0, .posY = 0, .palette = 0, .appearMode = 4, .appearTime = 0, .perCharDelayIn = 0, .holdMode = 0, .holdTime = 0, .vanishMode = 0, .vanishTime = 0, .perCharDelayOut = 0, .next = -1, .flags = 0 },
};

u8 TTYD64_end_00_String_Task_Sprites_ItemsAndRecipes[] = {
    0xFF, 0x00, 0x04, 0x13, 0x13, 0x18, 0x03, 0xF7, 0x08, 0x13, 0x04, 0x0C,
    0x12, 0xF7, 0x00, 0x0D, 0x03, 0xF7, 0x11, 0x04, 0x02, 0x08, 0x0F, 0x04,
    0x12, 0xF7, 0x12, 0x0F, 0x11, 0x08, 0x13, 0x04, 0x12, 0xFD
};

u8 TTYD64_end_00_String_Task_Sprites_NewEnemies[] = {
    0xFF, 0x00, 0x04, 0x0D, 0x04, 0x16, 0xF7, 0x04, 0x0D, 0x04, 0x0C, 0x08,
    0x04, 0x12, 0xF7, 0x12, 0x0F, 0x11, 0x08, 0x13, 0x04, 0x12, 0xFD
};

u8 TTYD64_end_00_String_SpecialThanks[] = {
    0xFF, 0x00, 0x04, 0x12, 0x0F, 0x04, 0x02, 0x08, 0x00, 0x0B, 0xF7, 0x13,
    0x07, 0x00, 0x0D, 0x0A, 0x12, 0xF7, 0x13, 0x0E, 0xFD
};

u8 TTYD64_end_00_String_EvelynHorstman[] = {
    0xFF, 0x00, 0x03, 0x04, 0x15, 0x04, 0x0B, 0x18, 0x0D, 0xF7, 0x07, 0x0E,
    0x11, 0x12, 0x13, 0x0C, 0x00, 0x0D, 0xFD
};

u8 TTYD64_end_00_String_Marceline[] = {
    0xFF, 0x00, 0x03, 0x0C, 0x00, 0x11, 0x02, 0x04, 0x0B, 0x08, 0x0D, 0x04,
    0xF7, 0x01, 0x04, 0x0B, 0x0B, 0xFD
};

u8 TTYD64_end_00_String_Testers[] = {
    0xFF, 0x00, 0x04, 0x00, 0x0B, 0x0F, 0x07, 0x00, 0xF7, 0x13, 0x04, 0x12,
    0x13, 0x04, 0x11, 0x12, 0xFD
};

u8 TTYD64_end_00_String_OrangeIsBorange[] = {
    0xFF, 0x00, 0x03, 0x0E, 0x11, 0x00, 0x0D, 0x06, 0x04, 0x08, 0x12, 0x01,
    0x0E, 0x11, 0x00, 0x0D, 0x06, 0x04, 0xFD
};

u8 TTYD64_end_00_String_Ja_and_Shade[] = {
    0xFF, 0x00, 0x03, 0x09, 0x00, 0x13, 0x07, 0x04, 0x0F, 0x0B, 0x00, 0x18,
    0x04, 0x11, 0xFD
};

u8 TTYD64_end_00_String_SwordBolt[] = {
    0xFF, 0x00, 0x03, 0x12, 0x16, 0x0E, 0x11, 0x03, 0x01, 0x0E, 0x0B, 0x13,
    0xFD
};

u8 TTYD64_end_00_String_SquidJesus[] = {
    0xFF, 0x00, 0x03, 0x12, 0x10, 0x14, 0x08, 0x03, 0x09, 0x04, 0x12, 0x14,
    0x12, 0xFD
};

u8 TTYD64_end_00_String_1upShyGuy[] = {
    0xFF, 0x00, 0x03, 0x1E, 0x14, 0x0F, 0x12, 0x07, 0x18, 0x06, 0x14, 0x18,
    0xFD
};

u8 TTYD64_end_00_String_Fatguy[] = {
    0xFF, 0x00, 0x03, 0x05, 0x00, 0x13, 0x06, 0x14, 0x18, 0x24, 0x1D, 0x20,
    0xFD
};

u8 TTYD64_end_00_String_XModxGodX[] = {
    0xFF, 0x00, 0x03, 0x17, 0x0C, 0x0E, 0x03, 0x17, 0x06, 0x0E, 0x03, 0x17,
    0xFD
};

u8 TTYD64_end_00_String_StevenBlue[] = {
    0xFF, 0x00, 0x03, 0x12, 0x13, 0x04, 0x15, 0x04, 0x0D, 0x01, 0x0B, 0x14,
    0x04, 0xFD
};

u8 TTYD64_end_00_String_ShyGuyXXL[] = {
    0xFF, 0x00, 0x03, 0x12, 0x07, 0x18, 0x06, 0x14, 0x18, 0x17, 0x17, 0x0B,
    0xFD
};

u8 TTYD64_end_00_String_pieordie1[] = {
    0xFF, 0x00, 0x03, 0x0F, 0x08, 0x04, 0x0E, 0x11, 0x03, 0x08, 0x04, 0x1E,
    0xFD
};

u8 TTYD64_end_00_String_JasonParker[] = {
    0xFF, 0x00, 0x03, 0x09, 0x00, 0x12, 0x0E, 0x0D, 0xF7, 0x0F, 0x00, 0x11,
    0x0A, 0x04, 0x11, 0xFD
};

u8 TTYD64_end_00_String_Lunarman[] = {
    0xFF, 0x00, 0x03, 0x0B, 0x14, 0x0D, 0x00, 0x11, 0x0C, 0x00, 0x0D, 0x1B,
    0x04, 0x17, 0x04, 0xFD
};

u8 TTYD64_end_00_String_NomadNamrod[] = {
    0xFF, 0x00, 0x03, 0x0D, 0x0E, 0x0C, 0x00, 0x03, 0xF7, 0x0D, 0x00, 0x0C,
    0x11, 0x0E, 0x03, 0xFD
};

u8 TTYD64_end_00_String_Dreamkazoo[] = {
    0xFF, 0x00, 0x03, 0x03, 0x11, 0x04, 0x00, 0x0C, 0x0A, 0x00, 0x19, 0x0E,
    0x0E, 0xFD
};

u8 TTYD64_end_00_String_Jdaster[] = {
    0xFF, 0x00, 0x03, 0x09, 0x03, 0x00, 0x12, 0x13, 0x04, 0x11, 0x23, 0x21,
    0xFD
};

u8 TTYD64_end_00_String_CrackerJack[] = {
    0xFF, 0x00, 0x03, 0x02, 0x11, 0x00, 0x02, 0x0A, 0x04, 0x11, 0xF7, 0x09,
    0x00, 0x02, 0x0A, 0xFD
};

u8 TTYD64_end_00_String_Zephiles[] = {
    0xFF, 0x00, 0x03, 0x19, 0x04, 0x0F, 0x07, 0x08, 0x0B, 0x04, 0x12, 0xFD
};

u8 TTYD64_end_00_String_Mania[] = {
    0xFF, 0x00, 0x03, 0x0C, 0x00, 0x0D, 0x08, 0x00, 0xFD
};

u8 TTYD64_end_00_String_Rayne[] = {
    0xFF, 0x00, 0x03, 0x11, 0x00, 0x18, 0x0D, 0x04, 0xFD
};

u8 TTYD64_end_00_String_Awestin[] = {
    0xFF, 0x00, 0x03, 0x00, 0x16, 0x04, 0x12, 0x13, 0x08, 0x0D, 0xFD
};

u8 TTYD64_end_00_String_WhyCron[] = {
    0xFF, 0x00, 0x03, 0x16, 0x07, 0x18, 0x02, 0x11, 0x0E, 0x0D, 0xFD
};

u8 TTYD64_end_00_String_ZeroZXL[] = {
    0xFF, 0x00, 0x03, 0x19, 0x04, 0x11, 0x0E, 0x19, 0x17, 0x0B, 0xFD
};

u8 TTYD64_end_00_String_Reborn[] = {
    0xFF, 0x00, 0x03, 0x11, 0x04, 0x01, 0x0E, 0x11, 0x0D, 0xFD
};

u8 TTYD64_end_00_String_DiaFiend[] = {
    0xFF, 0x00, 0x03, 0x03, 0x08, 0x00, 0x05, 0x08, 0x04, 0x0D, 0x03, 0xFD
};

u8 TTYD64_end_00_String_BossBuzz[] = {
    0xFF, 0x00, 0x03, 0x01, 0x0E, 0x12, 0x12, 0x01, 0x14, 0x19, 0x19, 0xFD
};

u8 TTYD64_end_00_String_Link75[] = {
    0xFF, 0x00, 0x03, 0x0B, 0x08, 0x0D, 0x0A, 0xF7, 0x24, 0x22, 0xFD
};

u8 TTYD64_end_00_String_Riviera[] = {
    0xFF, 0x00, 0x03, 0x11, 0x08, 0x15, 0x08, 0x04, 0x11, 0x00, 0xFD
};

u8 TTYD64_end_00_String_Matoi[] = {
    0xFF, 0x00, 0x03, 0x0C, 0x00, 0x13, 0x0E, 0x08, 0xFD
};

EvtScript TTYD64_end_00_Script_ShowNames = {
    Call(end_00_ShowCreditList, (Bytecode) TTYD64_end_00_CreditList_Names)
    Return
    End
};

u8 TTYD64_end_00_String_Drew[] = {
    0xFF, 0x00, 0x03, 0x03, 0x11, 0x04, 0x16, 0xFD
};

u8 TTYD64_end_00_String_Patrons[] = {
    0xFF, 0x00, 0x04, 0x0F, 0x00, 0x13, 0x11, 0x0E, 0x0D, 0x12, 0xFD
};

u8 TTYD64_end_00_String_ZoomZike[] = {
    0xFF, 0x00, 0x03, 0x19, 0x0E, 0x0E, 0x0C, 0x19, 0x08, 0x0A, 0x04, 0xFD
};

u8 TTYD64_end_00_String_Task_Dex[] = {
    0xFF, 0x00, 0x04, 0x03, 0x04, 0x12, 0x08, 0x06, 0x0D, 0x1C, 0xF7, 0x0C,
    0x0E, 0x03, 0x04, 0x0B, 0x08, 0x0D, 0x06, 0x1C, 0xF7, 0x0F, 0x11, 0x0E,
    0x06, 0x11, 0x00, 0x0C, 0x08, 0x0D, 0x06, 0x1C, 0xF7, 0x12, 0x0F, 0x11,
    0x08, 0x13, 0x04, 0x12, 0xF7, 0x00, 0x0D, 0x08, 0x0C, 0x00, 0x13, 0x08,
    0x0E, 0x0D, 0x12, 0xFD
};

u8 TTYD64_end_00_String_Task_Sprites_Misc[] = {
    0xFF, 0x00, 0x04, 0x0C, 0x08, 0x12, 0x02, 0x04, 0x0B, 0x0B, 0x00, 0x0D,
    0x04, 0x0E, 0x14, 0x12, 0xF7, 0x0D, 0x04, 0x16, 0xF7, 0x12, 0x0F, 0x11,
    0x08, 0x13, 0x04, 0x12, 0xFD
};

u8 TTYD64_end_00_String_Task_Sprites_NewBadges[] = {
    0xFF, 0x00, 0x04, 0x13, 0x13, 0x18, 0x03, 0xF7, 0x01, 0x00, 0x03, 0x06,
    0x04, 0x12, 0xF7, 0x12, 0x0F, 0x11, 0x08, 0x13, 0x04, 0x12, 0xFD
};

u8 TTYD64_end_00_String_TylerBravenst[] = {
    0xFF, 0x00, 0x03, 0x13, 0x18, 0x0B, 0x04, 0x11, 0xF7, 0x01, 0x11, 0x00,
    0x15, 0x04, 0x0D, 0x12, 0x13, 0xFD
};

u8 TTYD64_end_00_String_Typo[] = {
    0xFF, 0x00, 0x03, 0x13, 0x18, 0x0F, 0x0E, 0xF7, 0x1A, 0x13, 0x18, 0x0F,
    0x0E, 0x06, 0x11, 0x00, 0x05, 0x17, 0x1A, 0xFD
};

u8 TTYD64_end_00_String_AwakenedEmperor[] = {
    0xFF, 0x00, 0x03, 0x00, 0x16, 0x00, 0x0A, 0x04, 0x0D, 0x04, 0x03, 0xF7,
    0x04, 0x0C, 0x0F, 0x04, 0x11, 0x0E, 0x11, 0xFD
};

u8 TTYD64_end_00_String_Kevin[] = {
    0xFF, 0x00, 0x03, 0x0A, 0x04, 0x15, 0x08, 0x0D, 0xF7, 0x00, 0x11, 0x13,
    0x07, 0x14, 0x11, 0xF7, 0x0B, 0x12, 0xFD
};

u8 TTYD64_end_00_String_Decomp[] = {
    0xFF, 0x00, 0x03, 0x03, 0x04, 0x02, 0x0E, 0x0C, 0x0F, 0xF7, 0x13, 0x04,
    0x00, 0x0C, 0xFD
};

u8 TTYD64_end_00_String_BlueWarrior[] = {
    0xFF, 0x00, 0x03, 0x01, 0x0B, 0x14, 0x04, 0xF7, 0x16, 0x00, 0x11, 0x11,
    0x08, 0x0E, 0x11, 0xFD
};

u8 TTYD64_end_00_String_Task_ExtraMusic[] = {
    0xFF, 0x00, 0x04, 0x04, 0x17, 0x13, 0x11, 0x00, 0xF7, 0x0C, 0x14, 0x12,
    0x08, 0x02, 0xFD
};

u8 TTYD64_end_00_String_Ponderman[] = {
    0xFF, 0x00, 0x03, 0x0F, 0x0E, 0x0D, 0x03, 0x04, 0x11, 0x0C, 0x00, 0x0D,
    0xFD
};

u8 TTYD64_end_00_String_Tericonix[] = {
    0xFF, 0x00, 0x03, 0x13, 0x04, 0x11, 0x08, 0x02, 0x0E, 0x0D, 0x08, 0x17,
    0xFD
};

u8 TTYD64_end_00_String_Zioreturns[] = {
    0xFF, 0x00, 0x03, 0x19, 0x08, 0x0E, 0x11, 0x04, 0x13, 0x14, 0x11, 0x0D,
    0x12, 0xFD
};

u8 TTYD64_end_00_String_BlackJack[] = {
    0xFF, 0x00, 0x03, 0x01, 0x0B, 0x00, 0x02, 0x0A, 0x09, 0x00, 0x02, 0x0A,
    0xFD
};

u8 TTYD64_end_00_String_Task_BG[] = {
    0xFF, 0x00, 0x04, 0x13, 0x08, 0x13, 0x0B, 0x04, 0xF7, 0x12, 0x02, 0x11,
    0x04, 0x04, 0x0D, 0xFD
};

u8 TTYD64_end_00_String_Fraiseffddf4[] = {
    0xFF, 0x00, 0x03, 0x05, 0x11, 0x00, 0x08, 0x12, 0x04, 0x05, 0x05, 0x03,
    0x03, 0x05, 0x21, 0xFD
};

u8 TTYD64_end_00_String_TwoPieRadian[] = {
    0xFF, 0x00, 0x03, 0x13, 0x16, 0x0E, 0x0F, 0x08, 0x04, 0x11, 0x00, 0x03,
    0x08, 0x00, 0x0D, 0xFD
};

u8 TTYD64_end_00_String_GeminiSaint_and_Alop[] = {
    0xFF, 0x00, 0x03, 0x06, 0x04, 0x0C, 0x08, 0x0D, 0x08, 0xF7, 0x12, 0x00,
    0x08, 0x0D, 0x13, 0xFD
};

u8 TTYD64_end_00_String_Washudoll[] = {
    0xFF, 0x00, 0x03, 0x16, 0x00, 0x12, 0x07, 0x14, 0x03, 0x0E, 0x0B, 0x0B,
    0xFD
};

u8 TTYD64_end_00_String_chefshadow94[] = {
    0xFF, 0x00, 0x03, 0x02, 0x07, 0x04, 0x05, 0x12, 0x07, 0x00, 0x03, 0x0E,
    0x16, 0x26, 0x21, 0xFD
};

u8 TTYD64_end_00_String_GaganAtwal[] = {
    0xFF, 0x00, 0x03, 0x06, 0x00, 0x06, 0x00, 0x0D, 0xF7, 0x00, 0x13, 0x16,
    0x00, 0x0B, 0xFD
};

u8 TTYD64_end_00_String_TeamLuxk[] = {
    0xFF, 0x00, 0x03, 0x13, 0x04, 0x00, 0x0C, 0xF7, 0x0B, 0x14, 0x17, 0x0A,
    0xFD
};

u8 TTYD64_end_00_String_Starzee[] = {
    0xFF, 0x00, 0x03, 0x12, 0x13, 0x00, 0x11, 0x19, 0x04, 0x04, 0xFD
};

u8 TTYD64_end_00_String_Mishy[] = {
    0xFF, 0x00, 0x03, 0x0C, 0x08, 0x12, 0x07, 0x18, 0xFD
};

u8 TTYD64_end_00_String_Moemura[] = {
    0xFF, 0x00, 0x03, 0x0C, 0x0E, 0x04, 0x0C, 0x14, 0x11, 0x00, 0xFD
};

u8 TTYD64_end_00_String_Samevi[] = {
    0xFF, 0x00, 0x03, 0x12, 0x00, 0x0C, 0x04, 0x15, 0x08, 0xFD
};

u8 TTYD64_end_00_String_Task_MIDIs[] = {
    0xFF, 0x00, 0x04, 0x0C, 0x08, 0x03, 0x08, 0x12, 0xFD
};

u8 TTYD64_end_00_String_Brotenko[] = {
    0xFF, 0x00, 0x03, 0x01, 0x11, 0x0E, 0x13, 0x04, 0x0D, 0x0A, 0x0E, 0xFD
};

u8 TTYD64_end_00_String_Griscuit[] = {
    0xFF, 0x00, 0x03, 0x06, 0x11, 0x08, 0x12, 0x02, 0x14, 0x08, 0x13, 0xFD
};

u8 TTYD64_end_00_String_Bloop_and_ForrestRiedi[] = {
    0xFF, 0x00, 0x03, 0x01, 0x0B, 0x0E, 0x0E, 0x0F, 0xFD
};

u8 TTYD64_end_00_String_Zarexel[] = {
    0xFF, 0x00, 0x03, 0x19, 0x00, 0x11, 0x04, 0x17, 0x04, 0x0B, 0xFD
};

u8 TTYD64_end_00_String_Kappy[] = {
    0xFF, 0x00, 0x03, 0x0A, 0x00, 0x0F, 0x0F, 0x18, 0xFD
};

u8 TTYD64_end_00_String_Task_Music[] = {
    0xFF, 0x00, 0x04, 0x0C, 0x14, 0x12, 0x08, 0x02, 0xFD
};
// clang-format on

void TTYD64_InstallMap_end_00(void) {
    memcpy(&end_00_Credits_Jobs, &TTYD64_end_00_CreditList_Titles, sizeof(TTYD64_end_00_CreditList_Titles));
    Mod_ReplaceScript("TTYD64", &end_00_EVS_ShowCredits_Names, &TTYD64_end_00_Script_ShowNames);
    end_00_Credits_Jobs[2].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Task_Dex);
    end_00_Credits_Jobs[3].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Task_Sprites_NewBadges);
    end_00_Credits_Jobs[4].msgID =
        Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Task_Sprites_ItemsAndRecipes);
    end_00_Credits_Jobs[5].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Task_Sprites_Misc);
    end_00_Credits_Jobs[6].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Task_Sprites_NewEnemies);
    end_00_Credits_Jobs[7].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Task_BG);
    end_00_Credits_Jobs[8].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Task_Logo);
    end_00_Credits_Jobs[9].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Task_Music);
    end_00_Credits_Jobs[10].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Task_ExtraMusic);
    end_00_Credits_Jobs[11].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Task_MIDIs);
    end_00_Credits_Jobs[12].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_SpecialThanks);
    end_00_Credits_Jobs[13].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Testers);
    end_00_Credits_Jobs[14].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Patrons);
    TTYD64_end_00_CreditList_Names[3].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_BossBuzz);
    TTYD64_end_00_CreditList_Names[4].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Typo);
    TTYD64_end_00_CreditList_Names[5].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_BossBuzz);
    TTYD64_end_00_CreditList_Names[6].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Brotenko);
    TTYD64_end_00_CreditList_Names[7].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Fraiseffddf4);
    TTYD64_end_00_CreditList_Names[8].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Starzee);
    TTYD64_end_00_CreditList_Names[9].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Riviera);
    TTYD64_end_00_CreditList_Names[10].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_ShyGuyXXL);
    TTYD64_end_00_CreditList_Names[11].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_BossBuzz);
    TTYD64_end_00_CreditList_Names[12].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Kevin);
    TTYD64_end_00_CreditList_Names[13].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_StevenBlue);
    TTYD64_end_00_CreditList_Names[14].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_BlackJack);
    TTYD64_end_00_CreditList_Names[15].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Mania);
    TTYD64_end_00_CreditList_Names[16].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_BlueWarrior);
    TTYD64_end_00_CreditList_Names[17].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_SwordBolt);
    TTYD64_end_00_CreditList_Names[18].msgID =
        Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_GeminiSaint_and_Alop);
    TTYD64_end_00_CreditList_Names[19].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_pieordie1);
    TTYD64_end_00_CreditList_Names[20].msgID =
        Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Bloop_and_ForrestRiedi);
    TTYD64_end_00_CreditList_Names[21].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Washudoll);
    TTYD64_end_00_CreditList_Names[22].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Link75);
    TTYD64_end_00_CreditList_Names[23].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_StevenBlue);
    TTYD64_end_00_CreditList_Names[24].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Decomp);
    TTYD64_end_00_CreditList_Names[25].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Jdaster);
    TTYD64_end_00_CreditList_Names[26].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Ja_and_Shade);
    TTYD64_end_00_CreditList_Names[27].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Zephiles);
    TTYD64_end_00_CreditList_Names[28].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_ZoomZike);
    TTYD64_end_00_CreditList_Names[29].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Reborn);
    TTYD64_end_00_CreditList_Names[30].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Ponderman);
    TTYD64_end_00_CreditList_Names[31].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_GaganAtwal);
    TTYD64_end_00_CreditList_Names[32].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_CrackerJack);
    TTYD64_end_00_CreditList_Names[33].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_TwoPieRadian);
    TTYD64_end_00_CreditList_Names[34].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_TylerBravenst);
    TTYD64_end_00_CreditList_Names[35].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Jdaster);
    TTYD64_end_00_CreditList_Names[36].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_EvelynHorstman);
    TTYD64_end_00_CreditList_Names[37].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_DiaFiend);
    TTYD64_end_00_CreditList_Names[38].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Mishy);
    TTYD64_end_00_CreditList_Names[39].msgID =
        Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_OrangeIsBorange);
    TTYD64_end_00_CreditList_Names[40].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_MRTNEWB);
    TTYD64_end_00_CreditList_Names[41].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Zarexel);
    TTYD64_end_00_CreditList_Names[42].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_TeamLuxk);
    TTYD64_end_00_CreditList_Names[43].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_1upShyGuy);
    TTYD64_end_00_CreditList_Names[44].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_CrackerJack);
    TTYD64_end_00_CreditList_Names[45].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_TwoPieRadian);
    TTYD64_end_00_CreditList_Names[46].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_TylerBravenst);
    TTYD64_end_00_CreditList_Names[47].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Jdaster);
    TTYD64_end_00_CreditList_Names[48].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_EvelynHorstman);
    TTYD64_end_00_CreditList_Names[49].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_DiaFiend);
    TTYD64_end_00_CreditList_Names[50].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Mishy);
    TTYD64_end_00_CreditList_Names[51].msgID =
        Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_OrangeIsBorange);
    TTYD64_end_00_CreditList_Names[52].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_MRTNEWB);
    TTYD64_end_00_CreditList_Names[53].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Zarexel);
    TTYD64_end_00_CreditList_Names[54].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_TeamLuxk);
    TTYD64_end_00_CreditList_Names[55].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_1upShyGuy);
    TTYD64_end_00_CreditList_Names[56].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Samevi);
    TTYD64_end_00_CreditList_Names[57].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_XModxGodX);
    TTYD64_end_00_CreditList_Names[58].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Drew);
    TTYD64_end_00_CreditList_Names[59].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_ZeroZXL);
    TTYD64_end_00_CreditList_Names[60].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Zioreturns);
    TTYD64_end_00_CreditList_Names[61].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_JasonParker);
    TTYD64_end_00_CreditList_Names[62].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_SquidJesus);
    TTYD64_end_00_CreditList_Names[63].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_chefshadow94);
    TTYD64_end_00_CreditList_Names[64].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Tericonix);
    TTYD64_end_00_CreditList_Names[65].msgID =
        Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_AwakenedEmperor);
    TTYD64_end_00_CreditList_Names[66].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_NomadNamrod);
    TTYD64_end_00_CreditList_Names[67].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Matoi);
    TTYD64_end_00_CreditList_Names[68].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_WhyCron);
    TTYD64_end_00_CreditList_Names[69].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Ponderman);
    TTYD64_end_00_CreditList_Names[70].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Awestin);
    TTYD64_end_00_CreditList_Names[71].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Reborn);
    TTYD64_end_00_CreditList_Names[72].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Dreamkazoo);
    TTYD64_end_00_CreditList_Names[73].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Rayne);
    TTYD64_end_00_CreditList_Names[74].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Moemura);
    TTYD64_end_00_CreditList_Names[75].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Lunarman);
    TTYD64_end_00_CreditList_Names[76].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Marceline);
    TTYD64_end_00_CreditList_Names[77].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Kappy);
    TTYD64_end_00_CreditList_Names[78].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Fatguy);
    TTYD64_end_00_CreditList_Names[79].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_Griscuit);
    TTYD64_end_00_CreditList_Names[80].msgID = Mod_RegisterInlineMessage("TTYD64", TTYD64_end_00_String_messy);
}
