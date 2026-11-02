#include "common.h"
#include "hud_element.h"
#include "item_entity.h"
#include "port/romhack/specific/TTYD64/data.h"

static const ALIGN_ASSET(2) char TTYD64_ICON_2809790[] = "__OTR__icons/romhack/2809790";
static const ALIGN_ASSET(2) char TTYD64_ICON_2809990_pal[] = "__OTR__icons/romhack/2809990.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28099B0_pal[] = "__OTR__icons/romhack/28099B0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28090D0[] = "__OTR__icons/romhack/28090D0";
static const ALIGN_ASSET(2) char TTYD64_ICON_28092D0_pal[] = "__OTR__icons/romhack/28092D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28092F0_pal[] = "__OTR__icons/romhack/28092F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2808E90[] = "__OTR__icons/romhack/2808E90";
static const ALIGN_ASSET(2) char TTYD64_ICON_2809090_pal[] = "__OTR__icons/romhack/2809090.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28090B0_pal[] = "__OTR__icons/romhack/28090B0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805890[] = "__OTR__icons/romhack/2805890";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805A90_pal[] = "__OTR__icons/romhack/2805A90.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805AB0_pal[] = "__OTR__icons/romhack/2805AB0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2804F90[] = "__OTR__icons/romhack/2804F90";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805190_pal[] = "__OTR__icons/romhack/2805190.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28051B0_pal[] = "__OTR__icons/romhack/28051B0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2809C10[] = "__OTR__icons/romhack/2809C10";
static const ALIGN_ASSET(2) char TTYD64_ICON_2809E10_pal[] = "__OTR__icons/romhack/2809E10.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2809E30_pal[] = "__OTR__icons/romhack/2809E30.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807C90[] = "__OTR__icons/romhack/2807C90";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807E90_pal[] = "__OTR__icons/romhack/2807E90.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807EB0_pal[] = "__OTR__icons/romhack/2807EB0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807150[] = "__OTR__icons/romhack/2807150";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807350_pal[] = "__OTR__icons/romhack/2807350.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807370_pal[] = "__OTR__icons/romhack/2807370.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806190[] = "__OTR__icons/romhack/2806190";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806390_pal[] = "__OTR__icons/romhack/2806390.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28063B0_pal[] = "__OTR__icons/romhack/28063B0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806F10[] = "__OTR__icons/romhack/2806F10";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807110_pal[] = "__OTR__icons/romhack/2807110.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807130_pal[] = "__OTR__icons/romhack/2807130.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28075D0[] = "__OTR__icons/romhack/28075D0";
static const ALIGN_ASSET(2) char TTYD64_ICON_28077D0_pal[] = "__OTR__icons/romhack/28077D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28077F0_pal[] = "__OTR__icons/romhack/28077F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2809550[] = "__OTR__icons/romhack/2809550";
static const ALIGN_ASSET(2) char TTYD64_ICON_2809750_pal[] = "__OTR__icons/romhack/2809750.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2809770_pal[] = "__OTR__icons/romhack/2809770.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2809E50[] = "__OTR__icons/romhack/2809E50";
static const ALIGN_ASSET(2) char TTYD64_ICON_280A050_pal[] = "__OTR__icons/romhack/280A050.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280A070_pal[] = "__OTR__icons/romhack/280A070.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2808A10[] = "__OTR__icons/romhack/2808A10";
static const ALIGN_ASSET(2) char TTYD64_ICON_2808C10_pal[] = "__OTR__icons/romhack/2808C10.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2808C30_pal[] = "__OTR__icons/romhack/2808C30.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807ED0[] = "__OTR__icons/romhack/2807ED0";
static const ALIGN_ASSET(2) char TTYD64_ICON_28080D0_pal[] = "__OTR__icons/romhack/28080D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28080F0_pal[] = "__OTR__icons/romhack/28080F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28099D0[] = "__OTR__icons/romhack/28099D0";
static const ALIGN_ASSET(2) char TTYD64_ICON_2809BD0_pal[] = "__OTR__icons/romhack/2809BD0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2809BF0_pal[] = "__OTR__icons/romhack/2809BF0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806CD0[] = "__OTR__icons/romhack/2806CD0";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806ED0_pal[] = "__OTR__icons/romhack/2806ED0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806EF0_pal[] = "__OTR__icons/romhack/2806EF0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806610[] = "__OTR__icons/romhack/2806610";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806810_pal[] = "__OTR__icons/romhack/2806810.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806830_pal[] = "__OTR__icons/romhack/2806830.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2808C50[] = "__OTR__icons/romhack/2808C50";
static const ALIGN_ASSET(2) char TTYD64_ICON_2808E50_pal[] = "__OTR__icons/romhack/2808E50.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2808E70_pal[] = "__OTR__icons/romhack/2808E70.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2809310[] = "__OTR__icons/romhack/2809310";
static const ALIGN_ASSET(2) char TTYD64_ICON_2809510_pal[] = "__OTR__icons/romhack/2809510.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2809530_pal[] = "__OTR__icons/romhack/2809530.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28051D0[] = "__OTR__icons/romhack/28051D0";
static const ALIGN_ASSET(2) char TTYD64_ICON_28053D0_pal[] = "__OTR__icons/romhack/28053D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28053F0_pal[] = "__OTR__icons/romhack/28053F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805410[] = "__OTR__icons/romhack/2805410";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805610_pal[] = "__OTR__icons/romhack/2805610.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805630_pal[] = "__OTR__icons/romhack/2805630.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2808590[] = "__OTR__icons/romhack/2808590";
static const ALIGN_ASSET(2) char TTYD64_ICON_2808790_pal[] = "__OTR__icons/romhack/2808790.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28087B0_pal[] = "__OTR__icons/romhack/28087B0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805650[] = "__OTR__icons/romhack/2805650";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805850_pal[] = "__OTR__icons/romhack/2805850.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805870_pal[] = "__OTR__icons/romhack/2805870.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805AD0[] = "__OTR__icons/romhack/2805AD0";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805CD0_pal[] = "__OTR__icons/romhack/2805CD0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805CF0_pal[] = "__OTR__icons/romhack/2805CF0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807390[] = "__OTR__icons/romhack/2807390";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807590_pal[] = "__OTR__icons/romhack/2807590.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28075B0_pal[] = "__OTR__icons/romhack/28075B0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2808110[] = "__OTR__icons/romhack/2808110";
static const ALIGN_ASSET(2) char TTYD64_ICON_2808310_pal[] = "__OTR__icons/romhack/2808310.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2808330_pal[] = "__OTR__icons/romhack/2808330.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2808350[] = "__OTR__icons/romhack/2808350";
static const ALIGN_ASSET(2) char TTYD64_ICON_2808550_pal[] = "__OTR__icons/romhack/2808550.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2808570_pal[] = "__OTR__icons/romhack/2808570.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807810[] = "__OTR__icons/romhack/2807810";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807A10_pal[] = "__OTR__icons/romhack/2807A10.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807A30_pal[] = "__OTR__icons/romhack/2807A30.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807A50[] = "__OTR__icons/romhack/2807A50";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807C50_pal[] = "__OTR__icons/romhack/2807C50.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2807C70_pal[] = "__OTR__icons/romhack/2807C70.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28087D0[] = "__OTR__icons/romhack/28087D0";
static const ALIGN_ASSET(2) char TTYD64_ICON_28089D0_pal[] = "__OTR__icons/romhack/28089D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28089F0_pal[] = "__OTR__icons/romhack/28089F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280A090[] = "__OTR__icons/romhack/280A090";
static const ALIGN_ASSET(2) char TTYD64_ICON_280A290_pal[] = "__OTR__icons/romhack/280A290.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280A2B0_pal[] = "__OTR__icons/romhack/280A2B0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805D10[] = "__OTR__icons/romhack/2805D10";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805F10_pal[] = "__OTR__icons/romhack/2805F10.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805F30_pal[] = "__OTR__icons/romhack/2805F30.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2805F50[] = "__OTR__icons/romhack/2805F50";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806150_pal[] = "__OTR__icons/romhack/2806150.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806170_pal[] = "__OTR__icons/romhack/2806170.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28063D0[] = "__OTR__icons/romhack/28063D0";
static const ALIGN_ASSET(2) char TTYD64_ICON_28065D0_pal[] = "__OTR__icons/romhack/28065D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28065F0_pal[] = "__OTR__icons/romhack/28065F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806850[] = "__OTR__icons/romhack/2806850";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806A50_pal[] = "__OTR__icons/romhack/2806A50.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806A70_pal[] = "__OTR__icons/romhack/2806A70.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806A90[] = "__OTR__icons/romhack/2806A90";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806C90_pal[] = "__OTR__icons/romhack/2806C90.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2806CB0_pal[] = "__OTR__icons/romhack/2806CB0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280A2D0[] = "__OTR__icons/romhack/280A2D0";
static const ALIGN_ASSET(2) char TTYD64_ICON_280A4D0_pal[] = "__OTR__icons/romhack/280A4D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280A4F0_pal[] = "__OTR__icons/romhack/280A4F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280A510[] = "__OTR__icons/romhack/280A510";
static const ALIGN_ASSET(2) char TTYD64_ICON_280A710_pal[] = "__OTR__icons/romhack/280A710.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280A730_pal[] = "__OTR__icons/romhack/280A730.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280A750[] = "__OTR__icons/romhack/280A750";
static const ALIGN_ASSET(2) char TTYD64_ICON_280A950_pal[] = "__OTR__icons/romhack/280A950.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280A970_pal[] = "__OTR__icons/romhack/280A970.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280A990[] = "__OTR__icons/romhack/280A990";
static const ALIGN_ASSET(2) char TTYD64_ICON_280AB90_pal[] = "__OTR__icons/romhack/280AB90.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280ABB0_pal[] = "__OTR__icons/romhack/280ABB0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280ABD0[] = "__OTR__icons/romhack/280ABD0";
static const ALIGN_ASSET(2) char TTYD64_ICON_280ADD0_pal[] = "__OTR__icons/romhack/280ADD0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280ADF0_pal[] = "__OTR__icons/romhack/280ADF0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280AE10[] = "__OTR__icons/romhack/280AE10";
static const ALIGN_ASSET(2) char TTYD64_ICON_280B010_pal[] = "__OTR__icons/romhack/280B010.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280B030_pal[] = "__OTR__icons/romhack/280B030.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280B050[] = "__OTR__icons/romhack/280B050";
static const ALIGN_ASSET(2) char TTYD64_ICON_280B250_pal[] = "__OTR__icons/romhack/280B250.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280B270_pal[] = "__OTR__icons/romhack/280B270.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280B290[] = "__OTR__icons/romhack/280B290";
static const ALIGN_ASSET(2) char TTYD64_ICON_280B490_pal[] = "__OTR__icons/romhack/280B490.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280B4B0_pal[] = "__OTR__icons/romhack/280B4B0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280B4D0[] = "__OTR__icons/romhack/280B4D0";
static const ALIGN_ASSET(2) char TTYD64_ICON_280B6D0_pal[] = "__OTR__icons/romhack/280B6D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280B6F0_pal[] = "__OTR__icons/romhack/280B6F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280B710[] = "__OTR__icons/romhack/280B710";
static const ALIGN_ASSET(2) char TTYD64_ICON_280B910_pal[] = "__OTR__icons/romhack/280B910.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280B930_pal[] = "__OTR__icons/romhack/280B930.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280B950[] = "__OTR__icons/romhack/280B950";
static const ALIGN_ASSET(2) char TTYD64_ICON_280BB50_pal[] = "__OTR__icons/romhack/280BB50.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280BB70_pal[] = "__OTR__icons/romhack/280BB70.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280BB90[] = "__OTR__icons/romhack/280BB90";
static const ALIGN_ASSET(2) char TTYD64_ICON_280BD90_pal[] = "__OTR__icons/romhack/280BD90.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280BDB0_pal[] = "__OTR__icons/romhack/280BDB0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280BDD0[] = "__OTR__icons/romhack/280BDD0";
static const ALIGN_ASSET(2) char TTYD64_ICON_280BFD0_pal[] = "__OTR__icons/romhack/280BFD0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280BFF0_pal[] = "__OTR__icons/romhack/280BFF0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280C010[] = "__OTR__icons/romhack/280C010";
static const ALIGN_ASSET(2) char TTYD64_ICON_280C210_pal[] = "__OTR__icons/romhack/280C210.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280C230_pal[] = "__OTR__icons/romhack/280C230.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280C250[] = "__OTR__icons/romhack/280C250";
static const ALIGN_ASSET(2) char TTYD64_ICON_280C450_pal[] = "__OTR__icons/romhack/280C450.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280C470_pal[] = "__OTR__icons/romhack/280C470.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280C490[] = "__OTR__icons/romhack/280C490";
static const ALIGN_ASSET(2) char TTYD64_ICON_280C690_pal[] = "__OTR__icons/romhack/280C690.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280C6B0_pal[] = "__OTR__icons/romhack/280C6B0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280C6D0[] = "__OTR__icons/romhack/280C6D0";
static const ALIGN_ASSET(2) char TTYD64_ICON_280C8D0_pal[] = "__OTR__icons/romhack/280C8D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280C8F0_pal[] = "__OTR__icons/romhack/280C8F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280C910[] = "__OTR__icons/romhack/280C910";
static const ALIGN_ASSET(2) char TTYD64_ICON_280CB10_pal[] = "__OTR__icons/romhack/280CB10.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280CB30_pal[] = "__OTR__icons/romhack/280CB30.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280CB50[] = "__OTR__icons/romhack/280CB50";
static const ALIGN_ASSET(2) char TTYD64_ICON_280CD50_pal[] = "__OTR__icons/romhack/280CD50.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280CD70_pal[] = "__OTR__icons/romhack/280CD70.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280CD90[] = "__OTR__icons/romhack/280CD90";
static const ALIGN_ASSET(2) char TTYD64_ICON_280CF90_pal[] = "__OTR__icons/romhack/280CF90.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280CFB0_pal[] = "__OTR__icons/romhack/280CFB0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280CFD0[] = "__OTR__icons/romhack/280CFD0";
static const ALIGN_ASSET(2) char TTYD64_ICON_280D1D0_pal[] = "__OTR__icons/romhack/280D1D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280D1F0_pal[] = "__OTR__icons/romhack/280D1F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280D210[] = "__OTR__icons/romhack/280D210";
static const ALIGN_ASSET(2) char TTYD64_ICON_280D410_pal[] = "__OTR__icons/romhack/280D410.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280D430_pal[] = "__OTR__icons/romhack/280D430.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280D450[] = "__OTR__icons/romhack/280D450";
static const ALIGN_ASSET(2) char TTYD64_ICON_280D650_pal[] = "__OTR__icons/romhack/280D650.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280D670_pal[] = "__OTR__icons/romhack/280D670.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280D690[] = "__OTR__icons/romhack/280D690";
static const ALIGN_ASSET(2) char TTYD64_ICON_280D890_pal[] = "__OTR__icons/romhack/280D890.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280D8B0_pal[] = "__OTR__icons/romhack/280D8B0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280D8D0[] = "__OTR__icons/romhack/280D8D0";
static const ALIGN_ASSET(2) char TTYD64_ICON_280DAD0_pal[] = "__OTR__icons/romhack/280DAD0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280DAF0_pal[] = "__OTR__icons/romhack/280DAF0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280DB10[] = "__OTR__icons/romhack/280DB10";
static const ALIGN_ASSET(2) char TTYD64_ICON_280DD10_pal[] = "__OTR__icons/romhack/280DD10.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280DD30_pal[] = "__OTR__icons/romhack/280DD30.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280DD50[] = "__OTR__icons/romhack/280DD50";
static const ALIGN_ASSET(2) char TTYD64_ICON_280DF50_pal[] = "__OTR__icons/romhack/280DF50.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280DF70_pal[] = "__OTR__icons/romhack/280DF70.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280DF90[] = "__OTR__icons/romhack/280DF90";
static const ALIGN_ASSET(2) char TTYD64_ICON_280E190_pal[] = "__OTR__icons/romhack/280E190.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280E1B0_pal[] = "__OTR__icons/romhack/280E1B0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280E1D0[] = "__OTR__icons/romhack/280E1D0";
static const ALIGN_ASSET(2) char TTYD64_ICON_280E3D0_pal[] = "__OTR__icons/romhack/280E3D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280E3F0_pal[] = "__OTR__icons/romhack/280E3F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280E410[] = "__OTR__icons/romhack/280E410";
static const ALIGN_ASSET(2) char TTYD64_ICON_280E610_pal[] = "__OTR__icons/romhack/280E610.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280E630_pal[] = "__OTR__icons/romhack/280E630.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280E650[] = "__OTR__icons/romhack/280E650";
static const ALIGN_ASSET(2) char TTYD64_ICON_280E850_pal[] = "__OTR__icons/romhack/280E850.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280E870_pal[] = "__OTR__icons/romhack/280E870.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280E890[] = "__OTR__icons/romhack/280E890";
static const ALIGN_ASSET(2) char TTYD64_ICON_280EA90_pal[] = "__OTR__icons/romhack/280EA90.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280EAB0_pal[] = "__OTR__icons/romhack/280EAB0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280EAD0[] = "__OTR__icons/romhack/280EAD0";
static const ALIGN_ASSET(2) char TTYD64_ICON_280ECD0_pal[] = "__OTR__icons/romhack/280ECD0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280ECF0_pal[] = "__OTR__icons/romhack/280ECF0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280ED10[] = "__OTR__icons/romhack/280ED10";
static const ALIGN_ASSET(2) char TTYD64_ICON_280EF10_pal[] = "__OTR__icons/romhack/280EF10.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280EF30_pal[] = "__OTR__icons/romhack/280EF30.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280EF50[] = "__OTR__icons/romhack/280EF50";
static const ALIGN_ASSET(2) char TTYD64_ICON_280F150_pal[] = "__OTR__icons/romhack/280F150.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280F170_pal[] = "__OTR__icons/romhack/280F170.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280F190[] = "__OTR__icons/romhack/280F190";
static const ALIGN_ASSET(2) char TTYD64_ICON_280F390_pal[] = "__OTR__icons/romhack/280F390.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280F3B0_pal[] = "__OTR__icons/romhack/280F3B0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280F3D0[] = "__OTR__icons/romhack/280F3D0";
static const ALIGN_ASSET(2) char TTYD64_ICON_280F5D0_pal[] = "__OTR__icons/romhack/280F5D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280F5F0_pal[] = "__OTR__icons/romhack/280F5F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280F610[] = "__OTR__icons/romhack/280F610";
static const ALIGN_ASSET(2) char TTYD64_ICON_280F810_pal[] = "__OTR__icons/romhack/280F810.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280F830_pal[] = "__OTR__icons/romhack/280F830.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280F850[] = "__OTR__icons/romhack/280F850";
static const ALIGN_ASSET(2) char TTYD64_ICON_280FA50_pal[] = "__OTR__icons/romhack/280FA50.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280FA70_pal[] = "__OTR__icons/romhack/280FA70.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280FA90[] = "__OTR__icons/romhack/280FA90";
static const ALIGN_ASSET(2) char TTYD64_ICON_280FC90_pal[] = "__OTR__icons/romhack/280FC90.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280FCB0_pal[] = "__OTR__icons/romhack/280FCB0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280FCD0[] = "__OTR__icons/romhack/280FCD0";
static const ALIGN_ASSET(2) char TTYD64_ICON_280FED0_pal[] = "__OTR__icons/romhack/280FED0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280FEF0_pal[] = "__OTR__icons/romhack/280FEF0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_280FF10[] = "__OTR__icons/romhack/280FF10";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810110_pal[] = "__OTR__icons/romhack/2810110.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810130_pal[] = "__OTR__icons/romhack/2810130.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810150[] = "__OTR__icons/romhack/2810150";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810350_pal[] = "__OTR__icons/romhack/2810350.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810370_pal[] = "__OTR__icons/romhack/2810370.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810390[] = "__OTR__icons/romhack/2810390";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810590_pal[] = "__OTR__icons/romhack/2810590.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28105B0_pal[] = "__OTR__icons/romhack/28105B0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28105D0[] = "__OTR__icons/romhack/28105D0";
static const ALIGN_ASSET(2) char TTYD64_ICON_28107D0_pal[] = "__OTR__icons/romhack/28107D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28107F0_pal[] = "__OTR__icons/romhack/28107F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810810[] = "__OTR__icons/romhack/2810810";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810A10_pal[] = "__OTR__icons/romhack/2810A10.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810A30_pal[] = "__OTR__icons/romhack/2810A30.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810A50[] = "__OTR__icons/romhack/2810A50";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810C50_pal[] = "__OTR__icons/romhack/2810C50.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810C70_pal[] = "__OTR__icons/romhack/2810C70.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810C90[] = "__OTR__icons/romhack/2810C90";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810E90_pal[] = "__OTR__icons/romhack/2810E90.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810EB0_pal[] = "__OTR__icons/romhack/2810EB0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2810ED0[] = "__OTR__icons/romhack/2810ED0";
static const ALIGN_ASSET(2) char TTYD64_ICON_28110D0_pal[] = "__OTR__icons/romhack/28110D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28110F0_pal[] = "__OTR__icons/romhack/28110F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2811110[] = "__OTR__icons/romhack/2811110";
static const ALIGN_ASSET(2) char TTYD64_ICON_2811310_pal[] = "__OTR__icons/romhack/2811310.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2811330_pal[] = "__OTR__icons/romhack/2811330.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2811350[] = "__OTR__icons/romhack/2811350";
static const ALIGN_ASSET(2) char TTYD64_ICON_2811550_pal[] = "__OTR__icons/romhack/2811550.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2811570_pal[] = "__OTR__icons/romhack/2811570.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2811590[] = "__OTR__icons/romhack/2811590";
static const ALIGN_ASSET(2) char TTYD64_ICON_2811790_pal[] = "__OTR__icons/romhack/2811790.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28117B0_pal[] = "__OTR__icons/romhack/28117B0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28117D0[] = "__OTR__icons/romhack/28117D0";
static const ALIGN_ASSET(2) char TTYD64_ICON_28119D0_pal[] = "__OTR__icons/romhack/28119D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28119F0_pal[] = "__OTR__icons/romhack/28119F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2811A10[] = "__OTR__icons/romhack/2811A10";
static const ALIGN_ASSET(2) char TTYD64_ICON_2811C10_pal[] = "__OTR__icons/romhack/2811C10.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2811C30_pal[] = "__OTR__icons/romhack/2811C30.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2811C50[] = "__OTR__icons/romhack/2811C50";
static const ALIGN_ASSET(2) char TTYD64_ICON_2811E50_pal[] = "__OTR__icons/romhack/2811E50.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2811E70_pal[] = "__OTR__icons/romhack/2811E70.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2811E90[] = "__OTR__icons/romhack/2811E90";
static const ALIGN_ASSET(2) char TTYD64_ICON_2812090_pal[] = "__OTR__icons/romhack/2812090.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28120B0_pal[] = "__OTR__icons/romhack/28120B0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28120D0[] = "__OTR__icons/romhack/28120D0";
static const ALIGN_ASSET(2) char TTYD64_ICON_28122D0_pal[] = "__OTR__icons/romhack/28122D0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_28122F0_pal[] = "__OTR__icons/romhack/28122F0.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_2812310[] = "__OTR__icons/romhack/2812310";
static const ALIGN_ASSET(2) char TTYD64_ICON_2812510_pal[] = "__OTR__icons/romhack/2812510.pal";

#define TTYD64_HES_ITEM(raster, palette) \
    { hs_SetVisible hs_SetTileSize(HUD_ELEMENT_SIZE_32x32) hs_Loop HUD_ELEMENT_OP_SetImage, \
      60, \
      (intptr_t) raster, \
      (intptr_t) palette, \
      0, \
      0, \
      hs_Restart hs_End }
#define TTYD64_IES_ITEM(raster, palette) \
    { ITEM_SCRIPT_OP_SetImage, 60, (intptr_t) raster, (intptr_t) palette, 0, 0, ITEM_SCRIPT_OP_Restart, \
      ITEM_SCRIPT_OP_End }

static HudScript TTYD64_HES_Item_0EE = TTYD64_HES_ITEM(TTYD64_ICON_2809790, TTYD64_ICON_2809990_pal);
static HudScript TTYD64_HES_Item_0EE_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2809790, TTYD64_ICON_28099B0_pal);
static ItemScript TTYD64_IES_Item_0EE = TTYD64_IES_ITEM(TTYD64_ICON_2809790, TTYD64_ICON_2809990_pal);
static HudScript TTYD64_HES_Item_12D = TTYD64_HES_ITEM(TTYD64_ICON_28090D0, TTYD64_ICON_28092D0_pal);
static HudScript TTYD64_HES_Item_12D_disabled = TTYD64_HES_ITEM(TTYD64_ICON_28090D0, TTYD64_ICON_28092F0_pal);
static ItemScript TTYD64_IES_Item_12D = TTYD64_IES_ITEM(TTYD64_ICON_28090D0, TTYD64_ICON_28092D0_pal);
static HudScript TTYD64_HES_Item_12E = TTYD64_HES_ITEM(TTYD64_ICON_2808E90, TTYD64_ICON_2809090_pal);
static HudScript TTYD64_HES_Item_12E_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2808E90, TTYD64_ICON_28090B0_pal);
static ItemScript TTYD64_IES_Item_12E = TTYD64_IES_ITEM(TTYD64_ICON_2808E90, TTYD64_ICON_2809090_pal);
static HudScript TTYD64_HES_Item_143 = TTYD64_HES_ITEM(TTYD64_ICON_2805890, TTYD64_ICON_2805A90_pal);
static HudScript TTYD64_HES_Item_143_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2805890, TTYD64_ICON_2805AB0_pal);
static ItemScript TTYD64_IES_Item_143 = TTYD64_IES_ITEM(TTYD64_ICON_2805890, TTYD64_ICON_2805A90_pal);
static HudScript TTYD64_HES_Item_16D = TTYD64_HES_ITEM(TTYD64_ICON_2804F90, TTYD64_ICON_2805190_pal);
static HudScript TTYD64_HES_Item_16D_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2804F90, TTYD64_ICON_28051B0_pal);
static ItemScript TTYD64_IES_Item_16D = TTYD64_IES_ITEM(TTYD64_ICON_2804F90, TTYD64_ICON_2805190_pal);
static HudScript TTYD64_HES_Item_16E = TTYD64_HES_ITEM(TTYD64_ICON_2809C10, TTYD64_ICON_2809E10_pal);
static HudScript TTYD64_HES_Item_16E_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2809C10, TTYD64_ICON_2809E30_pal);
static ItemScript TTYD64_IES_Item_16E = TTYD64_IES_ITEM(TTYD64_ICON_2809C10, TTYD64_ICON_2809E10_pal);
static HudScript TTYD64_HES_Item_16F = TTYD64_HES_ITEM(TTYD64_ICON_2807C90, TTYD64_ICON_2807E90_pal);
static HudScript TTYD64_HES_Item_16F_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2807C90, TTYD64_ICON_2807EB0_pal);
static ItemScript TTYD64_IES_Item_16F = TTYD64_IES_ITEM(TTYD64_ICON_2807C90, TTYD64_ICON_2807E90_pal);
static HudScript TTYD64_HES_Item_170 = TTYD64_HES_ITEM(TTYD64_ICON_2807150, TTYD64_ICON_2807350_pal);
static HudScript TTYD64_HES_Item_170_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2807150, TTYD64_ICON_2807370_pal);
static ItemScript TTYD64_IES_Item_170 = TTYD64_IES_ITEM(TTYD64_ICON_2807150, TTYD64_ICON_2807350_pal);
static HudScript TTYD64_HES_Item_171 = TTYD64_HES_ITEM(TTYD64_ICON_2806190, TTYD64_ICON_2806390_pal);
static HudScript TTYD64_HES_Item_171_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2806190, TTYD64_ICON_28063B0_pal);
static ItemScript TTYD64_IES_Item_171 = TTYD64_IES_ITEM(TTYD64_ICON_2806190, TTYD64_ICON_2806390_pal);
static HudScript TTYD64_HES_Item_172 = TTYD64_HES_ITEM(TTYD64_ICON_2806F10, TTYD64_ICON_2807110_pal);
static HudScript TTYD64_HES_Item_172_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2806F10, TTYD64_ICON_2807130_pal);
static ItemScript TTYD64_IES_Item_172 = TTYD64_IES_ITEM(TTYD64_ICON_2806F10, TTYD64_ICON_2807110_pal);
static HudScript TTYD64_HES_Item_173 = TTYD64_HES_ITEM(TTYD64_ICON_28075D0, TTYD64_ICON_28077D0_pal);
static HudScript TTYD64_HES_Item_173_disabled = TTYD64_HES_ITEM(TTYD64_ICON_28075D0, TTYD64_ICON_28077F0_pal);
static ItemScript TTYD64_IES_Item_173 = TTYD64_IES_ITEM(TTYD64_ICON_28075D0, TTYD64_ICON_28077D0_pal);
static HudScript TTYD64_HES_Item_174 = TTYD64_HES_ITEM(TTYD64_ICON_2809550, TTYD64_ICON_2809750_pal);
static HudScript TTYD64_HES_Item_174_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2809550, TTYD64_ICON_2809770_pal);
static ItemScript TTYD64_IES_Item_174 = TTYD64_IES_ITEM(TTYD64_ICON_2809550, TTYD64_ICON_2809750_pal);
static HudScript TTYD64_HES_Item_175 = TTYD64_HES_ITEM(TTYD64_ICON_2809E50, TTYD64_ICON_280A050_pal);
static HudScript TTYD64_HES_Item_175_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2809E50, TTYD64_ICON_280A070_pal);
static ItemScript TTYD64_IES_Item_175 = TTYD64_IES_ITEM(TTYD64_ICON_2809E50, TTYD64_ICON_280A050_pal);
static HudScript TTYD64_HES_Item_176 = TTYD64_HES_ITEM(TTYD64_ICON_2808A10, TTYD64_ICON_2808C10_pal);
static HudScript TTYD64_HES_Item_176_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2808A10, TTYD64_ICON_2808C30_pal);
static ItemScript TTYD64_IES_Item_176 = TTYD64_IES_ITEM(TTYD64_ICON_2808A10, TTYD64_ICON_2808C10_pal);
static HudScript TTYD64_HES_Item_177 = TTYD64_HES_ITEM(TTYD64_ICON_2807ED0, TTYD64_ICON_28080D0_pal);
static HudScript TTYD64_HES_Item_177_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2807ED0, TTYD64_ICON_28080F0_pal);
static ItemScript TTYD64_IES_Item_177 = TTYD64_IES_ITEM(TTYD64_ICON_2807ED0, TTYD64_ICON_28080D0_pal);
static HudScript TTYD64_HES_Item_178 = TTYD64_HES_ITEM(TTYD64_ICON_28099D0, TTYD64_ICON_2809BD0_pal);
static HudScript TTYD64_HES_Item_178_disabled = TTYD64_HES_ITEM(TTYD64_ICON_28099D0, TTYD64_ICON_2809BF0_pal);
static ItemScript TTYD64_IES_Item_178 = TTYD64_IES_ITEM(TTYD64_ICON_28099D0, TTYD64_ICON_2809BD0_pal);
static HudScript TTYD64_HES_Item_179 = TTYD64_HES_ITEM(TTYD64_ICON_2806CD0, TTYD64_ICON_2806ED0_pal);
static HudScript TTYD64_HES_Item_179_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2806CD0, TTYD64_ICON_2806EF0_pal);
static ItemScript TTYD64_IES_Item_179 = TTYD64_IES_ITEM(TTYD64_ICON_2806CD0, TTYD64_ICON_2806ED0_pal);
static HudScript TTYD64_HES_Item_17A = TTYD64_HES_ITEM(TTYD64_ICON_2806610, TTYD64_ICON_2806810_pal);
static HudScript TTYD64_HES_Item_17A_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2806610, TTYD64_ICON_2806830_pal);
static ItemScript TTYD64_IES_Item_17A = TTYD64_IES_ITEM(TTYD64_ICON_2806610, TTYD64_ICON_2806810_pal);
static HudScript TTYD64_HES_Item_17B = TTYD64_HES_ITEM(TTYD64_ICON_2808C50, TTYD64_ICON_2808E50_pal);
static HudScript TTYD64_HES_Item_17B_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2808C50, TTYD64_ICON_2808E70_pal);
static ItemScript TTYD64_IES_Item_17B = TTYD64_IES_ITEM(TTYD64_ICON_2808C50, TTYD64_ICON_2808E50_pal);
static HudScript TTYD64_HES_Item_17C = TTYD64_HES_ITEM(TTYD64_ICON_2809310, TTYD64_ICON_2809510_pal);
static HudScript TTYD64_HES_Item_17C_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2809310, TTYD64_ICON_2809530_pal);
static ItemScript TTYD64_IES_Item_17C = TTYD64_IES_ITEM(TTYD64_ICON_2809310, TTYD64_ICON_2809510_pal);
static HudScript TTYD64_HES_Item_17D = TTYD64_HES_ITEM(TTYD64_ICON_28051D0, TTYD64_ICON_28053D0_pal);
static HudScript TTYD64_HES_Item_17D_disabled = TTYD64_HES_ITEM(TTYD64_ICON_28051D0, TTYD64_ICON_28053F0_pal);
static ItemScript TTYD64_IES_Item_17D = TTYD64_IES_ITEM(TTYD64_ICON_28051D0, TTYD64_ICON_28053D0_pal);
static HudScript TTYD64_HES_Item_17E = TTYD64_HES_ITEM(TTYD64_ICON_2805410, TTYD64_ICON_2805610_pal);
static HudScript TTYD64_HES_Item_17E_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2805410, TTYD64_ICON_2805630_pal);
static ItemScript TTYD64_IES_Item_17E = TTYD64_IES_ITEM(TTYD64_ICON_2805410, TTYD64_ICON_2805610_pal);
static HudScript TTYD64_HES_Item_17F = TTYD64_HES_ITEM(TTYD64_ICON_2808590, TTYD64_ICON_2808790_pal);
static HudScript TTYD64_HES_Item_17F_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2808590, TTYD64_ICON_28087B0_pal);
static ItemScript TTYD64_IES_Item_17F = TTYD64_IES_ITEM(TTYD64_ICON_2808590, TTYD64_ICON_2808790_pal);
static HudScript TTYD64_HES_Item_180 = TTYD64_HES_ITEM(TTYD64_ICON_2805650, TTYD64_ICON_2805850_pal);
static HudScript TTYD64_HES_Item_180_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2805650, TTYD64_ICON_2805870_pal);
static ItemScript TTYD64_IES_Item_180 = TTYD64_IES_ITEM(TTYD64_ICON_2805650, TTYD64_ICON_2805850_pal);
static HudScript TTYD64_HES_Item_181 = TTYD64_HES_ITEM(TTYD64_ICON_2805AD0, TTYD64_ICON_2805CD0_pal);
static HudScript TTYD64_HES_Item_181_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2805AD0, TTYD64_ICON_2805CF0_pal);
static ItemScript TTYD64_IES_Item_181 = TTYD64_IES_ITEM(TTYD64_ICON_2805AD0, TTYD64_ICON_2805CD0_pal);
static HudScript TTYD64_HES_Item_182 = TTYD64_HES_ITEM(TTYD64_ICON_2807390, TTYD64_ICON_2807590_pal);
static HudScript TTYD64_HES_Item_182_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2807390, TTYD64_ICON_28075B0_pal);
static ItemScript TTYD64_IES_Item_182 = TTYD64_IES_ITEM(TTYD64_ICON_2807390, TTYD64_ICON_2807590_pal);
static HudScript TTYD64_HES_Item_183 = TTYD64_HES_ITEM(TTYD64_ICON_2808110, TTYD64_ICON_2808310_pal);
static HudScript TTYD64_HES_Item_183_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2808110, TTYD64_ICON_2808330_pal);
static ItemScript TTYD64_IES_Item_183 = TTYD64_IES_ITEM(TTYD64_ICON_2808110, TTYD64_ICON_2808310_pal);
static HudScript TTYD64_HES_Item_184 = TTYD64_HES_ITEM(TTYD64_ICON_2808350, TTYD64_ICON_2808550_pal);
static HudScript TTYD64_HES_Item_184_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2808350, TTYD64_ICON_2808570_pal);
static ItemScript TTYD64_IES_Item_184 = TTYD64_IES_ITEM(TTYD64_ICON_2808350, TTYD64_ICON_2808550_pal);
static HudScript TTYD64_HES_Item_185 = TTYD64_HES_ITEM(TTYD64_ICON_2807810, TTYD64_ICON_2807A10_pal);
static HudScript TTYD64_HES_Item_185_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2807810, TTYD64_ICON_2807A30_pal);
static ItemScript TTYD64_IES_Item_185 = TTYD64_IES_ITEM(TTYD64_ICON_2807810, TTYD64_ICON_2807A10_pal);
static HudScript TTYD64_HES_Item_186 = TTYD64_HES_ITEM(TTYD64_ICON_2807A50, TTYD64_ICON_2807C50_pal);
static HudScript TTYD64_HES_Item_186_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2807A50, TTYD64_ICON_2807C70_pal);
static ItemScript TTYD64_IES_Item_186 = TTYD64_IES_ITEM(TTYD64_ICON_2807A50, TTYD64_ICON_2807C50_pal);
static HudScript TTYD64_HES_Item_187 = TTYD64_HES_ITEM(TTYD64_ICON_28087D0, TTYD64_ICON_28089D0_pal);
static HudScript TTYD64_HES_Item_187_disabled = TTYD64_HES_ITEM(TTYD64_ICON_28087D0, TTYD64_ICON_28089F0_pal);
static ItemScript TTYD64_IES_Item_187 = TTYD64_IES_ITEM(TTYD64_ICON_28087D0, TTYD64_ICON_28089D0_pal);
static HudScript TTYD64_HES_Item_188 = TTYD64_HES_ITEM(TTYD64_ICON_280A090, TTYD64_ICON_280A290_pal);
static HudScript TTYD64_HES_Item_188_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280A090, TTYD64_ICON_280A2B0_pal);
static ItemScript TTYD64_IES_Item_188 = TTYD64_IES_ITEM(TTYD64_ICON_280A090, TTYD64_ICON_280A290_pal);
static HudScript TTYD64_HES_Item_189 = TTYD64_HES_ITEM(TTYD64_ICON_2805D10, TTYD64_ICON_2805F10_pal);
static HudScript TTYD64_HES_Item_189_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2805D10, TTYD64_ICON_2805F30_pal);
static ItemScript TTYD64_IES_Item_189 = TTYD64_IES_ITEM(TTYD64_ICON_2805D10, TTYD64_ICON_2805F10_pal);
static HudScript TTYD64_HES_Item_18A = TTYD64_HES_ITEM(TTYD64_ICON_2805F50, TTYD64_ICON_2806150_pal);
static HudScript TTYD64_HES_Item_18A_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2805F50, TTYD64_ICON_2806170_pal);
static ItemScript TTYD64_IES_Item_18A = TTYD64_IES_ITEM(TTYD64_ICON_2805F50, TTYD64_ICON_2806150_pal);
static HudScript TTYD64_HES_Item_18B = TTYD64_HES_ITEM(TTYD64_ICON_28063D0, TTYD64_ICON_28065D0_pal);
static HudScript TTYD64_HES_Item_18B_disabled = TTYD64_HES_ITEM(TTYD64_ICON_28063D0, TTYD64_ICON_28065F0_pal);
static ItemScript TTYD64_IES_Item_18B = TTYD64_IES_ITEM(TTYD64_ICON_28063D0, TTYD64_ICON_28065D0_pal);
static HudScript TTYD64_HES_Item_18C = TTYD64_HES_ITEM(TTYD64_ICON_2806850, TTYD64_ICON_2806A50_pal);
static HudScript TTYD64_HES_Item_18C_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2806850, TTYD64_ICON_2806A70_pal);
static ItemScript TTYD64_IES_Item_18C = TTYD64_IES_ITEM(TTYD64_ICON_2806850, TTYD64_ICON_2806A50_pal);
static HudScript TTYD64_HES_Item_18D = TTYD64_HES_ITEM(TTYD64_ICON_2806A90, TTYD64_ICON_2806C90_pal);
static HudScript TTYD64_HES_Item_18D_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2806A90, TTYD64_ICON_2806CB0_pal);
static ItemScript TTYD64_IES_Item_18D = TTYD64_IES_ITEM(TTYD64_ICON_2806A90, TTYD64_ICON_2806C90_pal);
static HudScript TTYD64_HES_Item_18E = TTYD64_HES_ITEM(TTYD64_ICON_280A2D0, TTYD64_ICON_280A4D0_pal);
static HudScript TTYD64_HES_Item_18E_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280A2D0, TTYD64_ICON_280A4F0_pal);
static ItemScript TTYD64_IES_Item_18E = TTYD64_IES_ITEM(TTYD64_ICON_280A2D0, TTYD64_ICON_280A4D0_pal);
static HudScript TTYD64_HES_Item_18F = TTYD64_HES_ITEM(TTYD64_ICON_280A510, TTYD64_ICON_280A710_pal);
static HudScript TTYD64_HES_Item_18F_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280A510, TTYD64_ICON_280A730_pal);
static ItemScript TTYD64_IES_Item_18F = TTYD64_IES_ITEM(TTYD64_ICON_280A510, TTYD64_ICON_280A710_pal);
static HudScript TTYD64_HES_Item_190 = TTYD64_HES_ITEM(TTYD64_ICON_280A750, TTYD64_ICON_280A950_pal);
static HudScript TTYD64_HES_Item_190_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280A750, TTYD64_ICON_280A970_pal);
static ItemScript TTYD64_IES_Item_190 = TTYD64_IES_ITEM(TTYD64_ICON_280A750, TTYD64_ICON_280A950_pal);
static HudScript TTYD64_HES_Item_191 = TTYD64_HES_ITEM(TTYD64_ICON_280A990, TTYD64_ICON_280AB90_pal);
static HudScript TTYD64_HES_Item_191_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280A990, TTYD64_ICON_280ABB0_pal);
static ItemScript TTYD64_IES_Item_191 = TTYD64_IES_ITEM(TTYD64_ICON_280A990, TTYD64_ICON_280AB90_pal);
static HudScript TTYD64_HES_Item_192 = TTYD64_HES_ITEM(TTYD64_ICON_280ABD0, TTYD64_ICON_280ADD0_pal);
static HudScript TTYD64_HES_Item_192_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280ABD0, TTYD64_ICON_280ADF0_pal);
static ItemScript TTYD64_IES_Item_192 = TTYD64_IES_ITEM(TTYD64_ICON_280ABD0, TTYD64_ICON_280ADD0_pal);
static HudScript TTYD64_HES_Item_193 = TTYD64_HES_ITEM(TTYD64_ICON_280AE10, TTYD64_ICON_280B010_pal);
static HudScript TTYD64_HES_Item_193_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280AE10, TTYD64_ICON_280B030_pal);
static ItemScript TTYD64_IES_Item_193 = TTYD64_IES_ITEM(TTYD64_ICON_280AE10, TTYD64_ICON_280B010_pal);
static HudScript TTYD64_HES_Item_194 = TTYD64_HES_ITEM(TTYD64_ICON_280B050, TTYD64_ICON_280B250_pal);
static HudScript TTYD64_HES_Item_194_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280B050, TTYD64_ICON_280B270_pal);
static ItemScript TTYD64_IES_Item_194 = TTYD64_IES_ITEM(TTYD64_ICON_280B050, TTYD64_ICON_280B250_pal);
static HudScript TTYD64_HES_Item_195 = TTYD64_HES_ITEM(TTYD64_ICON_280B290, TTYD64_ICON_280B490_pal);
static HudScript TTYD64_HES_Item_195_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280B290, TTYD64_ICON_280B4B0_pal);
static ItemScript TTYD64_IES_Item_195 = TTYD64_IES_ITEM(TTYD64_ICON_280B290, TTYD64_ICON_280B490_pal);
static HudScript TTYD64_HES_Item_196 = TTYD64_HES_ITEM(TTYD64_ICON_280B4D0, TTYD64_ICON_280B6D0_pal);
static HudScript TTYD64_HES_Item_196_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280B4D0, TTYD64_ICON_280B6F0_pal);
static ItemScript TTYD64_IES_Item_196 = TTYD64_IES_ITEM(TTYD64_ICON_280B4D0, TTYD64_ICON_280B6D0_pal);
static HudScript TTYD64_HES_Item_197 = TTYD64_HES_ITEM(TTYD64_ICON_280B710, TTYD64_ICON_280B910_pal);
static HudScript TTYD64_HES_Item_197_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280B710, TTYD64_ICON_280B930_pal);
static ItemScript TTYD64_IES_Item_197 = TTYD64_IES_ITEM(TTYD64_ICON_280B710, TTYD64_ICON_280B910_pal);
static HudScript TTYD64_HES_Item_198 = TTYD64_HES_ITEM(TTYD64_ICON_280B950, TTYD64_ICON_280BB50_pal);
static HudScript TTYD64_HES_Item_198_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280B950, TTYD64_ICON_280BB70_pal);
static ItemScript TTYD64_IES_Item_198 = TTYD64_IES_ITEM(TTYD64_ICON_280B950, TTYD64_ICON_280BB50_pal);
static HudScript TTYD64_HES_Item_199 = TTYD64_HES_ITEM(TTYD64_ICON_280BB90, TTYD64_ICON_280BD90_pal);
static HudScript TTYD64_HES_Item_199_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280BB90, TTYD64_ICON_280BDB0_pal);
static ItemScript TTYD64_IES_Item_199 = TTYD64_IES_ITEM(TTYD64_ICON_280BB90, TTYD64_ICON_280BD90_pal);
static HudScript TTYD64_HES_Item_19A = TTYD64_HES_ITEM(TTYD64_ICON_280BDD0, TTYD64_ICON_280BFD0_pal);
static HudScript TTYD64_HES_Item_19A_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280BDD0, TTYD64_ICON_280BFF0_pal);
static ItemScript TTYD64_IES_Item_19A = TTYD64_IES_ITEM(TTYD64_ICON_280BDD0, TTYD64_ICON_280BFD0_pal);
static HudScript TTYD64_HES_Item_19B = TTYD64_HES_ITEM(TTYD64_ICON_280C010, TTYD64_ICON_280C210_pal);
static HudScript TTYD64_HES_Item_19B_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280C010, TTYD64_ICON_280C230_pal);
static ItemScript TTYD64_IES_Item_19B = TTYD64_IES_ITEM(TTYD64_ICON_280C010, TTYD64_ICON_280C210_pal);
static HudScript TTYD64_HES_Item_19C = TTYD64_HES_ITEM(TTYD64_ICON_280C250, TTYD64_ICON_280C450_pal);
static HudScript TTYD64_HES_Item_19C_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280C250, TTYD64_ICON_280C470_pal);
static ItemScript TTYD64_IES_Item_19C = TTYD64_IES_ITEM(TTYD64_ICON_280C250, TTYD64_ICON_280C450_pal);
static HudScript TTYD64_HES_Item_19D = TTYD64_HES_ITEM(TTYD64_ICON_280C490, TTYD64_ICON_280C690_pal);
static HudScript TTYD64_HES_Item_19D_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280C490, TTYD64_ICON_280C6B0_pal);
static ItemScript TTYD64_IES_Item_19D = TTYD64_IES_ITEM(TTYD64_ICON_280C490, TTYD64_ICON_280C690_pal);
static HudScript TTYD64_HES_Item_19E = TTYD64_HES_ITEM(TTYD64_ICON_280C6D0, TTYD64_ICON_280C8D0_pal);
static HudScript TTYD64_HES_Item_19E_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280C6D0, TTYD64_ICON_280C8F0_pal);
static ItemScript TTYD64_IES_Item_19E = TTYD64_IES_ITEM(TTYD64_ICON_280C6D0, TTYD64_ICON_280C8D0_pal);
static HudScript TTYD64_HES_Item_19F = TTYD64_HES_ITEM(TTYD64_ICON_280C910, TTYD64_ICON_280CB10_pal);
static HudScript TTYD64_HES_Item_19F_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280C910, TTYD64_ICON_280CB30_pal);
static ItemScript TTYD64_IES_Item_19F = TTYD64_IES_ITEM(TTYD64_ICON_280C910, TTYD64_ICON_280CB10_pal);
static HudScript TTYD64_HES_Item_1A0 = TTYD64_HES_ITEM(TTYD64_ICON_280CB50, TTYD64_ICON_280CD50_pal);
static HudScript TTYD64_HES_Item_1A0_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280CB50, TTYD64_ICON_280CD70_pal);
static ItemScript TTYD64_IES_Item_1A0 = TTYD64_IES_ITEM(TTYD64_ICON_280CB50, TTYD64_ICON_280CD50_pal);
static HudScript TTYD64_HES_Item_1A1 = TTYD64_HES_ITEM(TTYD64_ICON_280CD90, TTYD64_ICON_280CF90_pal);
static HudScript TTYD64_HES_Item_1A1_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280CD90, TTYD64_ICON_280CFB0_pal);
static ItemScript TTYD64_IES_Item_1A1 = TTYD64_IES_ITEM(TTYD64_ICON_280CD90, TTYD64_ICON_280CF90_pal);
static HudScript TTYD64_HES_Item_1A2 = TTYD64_HES_ITEM(TTYD64_ICON_280CFD0, TTYD64_ICON_280D1D0_pal);
static HudScript TTYD64_HES_Item_1A2_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280CFD0, TTYD64_ICON_280D1F0_pal);
static ItemScript TTYD64_IES_Item_1A2 = TTYD64_IES_ITEM(TTYD64_ICON_280CFD0, TTYD64_ICON_280D1D0_pal);
static HudScript TTYD64_HES_Item_1A3 = TTYD64_HES_ITEM(TTYD64_ICON_280D210, TTYD64_ICON_280D410_pal);
static HudScript TTYD64_HES_Item_1A3_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280D210, TTYD64_ICON_280D430_pal);
static ItemScript TTYD64_IES_Item_1A3 = TTYD64_IES_ITEM(TTYD64_ICON_280D210, TTYD64_ICON_280D410_pal);
static HudScript TTYD64_HES_Item_1A4 = TTYD64_HES_ITEM(TTYD64_ICON_280D450, TTYD64_ICON_280D650_pal);
static HudScript TTYD64_HES_Item_1A4_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280D450, TTYD64_ICON_280D670_pal);
static ItemScript TTYD64_IES_Item_1A4 = TTYD64_IES_ITEM(TTYD64_ICON_280D450, TTYD64_ICON_280D650_pal);
static HudScript TTYD64_HES_Item_1A5 = TTYD64_HES_ITEM(TTYD64_ICON_280D690, TTYD64_ICON_280D890_pal);
static HudScript TTYD64_HES_Item_1A5_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280D690, TTYD64_ICON_280D8B0_pal);
static ItemScript TTYD64_IES_Item_1A5 = TTYD64_IES_ITEM(TTYD64_ICON_280D690, TTYD64_ICON_280D890_pal);
static HudScript TTYD64_HES_Item_1A6 = TTYD64_HES_ITEM(TTYD64_ICON_280D8D0, TTYD64_ICON_280DAD0_pal);
static HudScript TTYD64_HES_Item_1A6_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280D8D0, TTYD64_ICON_280DAF0_pal);
static ItemScript TTYD64_IES_Item_1A6 = TTYD64_IES_ITEM(TTYD64_ICON_280D8D0, TTYD64_ICON_280DAD0_pal);
static HudScript TTYD64_HES_Item_1A7 = TTYD64_HES_ITEM(TTYD64_ICON_280DB10, TTYD64_ICON_280DD10_pal);
static HudScript TTYD64_HES_Item_1A7_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280DB10, TTYD64_ICON_280DD30_pal);
static ItemScript TTYD64_IES_Item_1A7 = TTYD64_IES_ITEM(TTYD64_ICON_280DB10, TTYD64_ICON_280DD10_pal);
static HudScript TTYD64_HES_Item_1A8 = TTYD64_HES_ITEM(TTYD64_ICON_280DD50, TTYD64_ICON_280DF50_pal);
static HudScript TTYD64_HES_Item_1A8_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280DD50, TTYD64_ICON_280DF70_pal);
static ItemScript TTYD64_IES_Item_1A8 = TTYD64_IES_ITEM(TTYD64_ICON_280DD50, TTYD64_ICON_280DF50_pal);
static HudScript TTYD64_HES_Item_1A9 = TTYD64_HES_ITEM(TTYD64_ICON_280DF90, TTYD64_ICON_280E190_pal);
static HudScript TTYD64_HES_Item_1A9_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280DF90, TTYD64_ICON_280E1B0_pal);
static ItemScript TTYD64_IES_Item_1A9 = TTYD64_IES_ITEM(TTYD64_ICON_280DF90, TTYD64_ICON_280E190_pal);
static HudScript TTYD64_HES_Item_1AA = TTYD64_HES_ITEM(TTYD64_ICON_280E1D0, TTYD64_ICON_280E3D0_pal);
static HudScript TTYD64_HES_Item_1AA_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280E1D0, TTYD64_ICON_280E3F0_pal);
static ItemScript TTYD64_IES_Item_1AA = TTYD64_IES_ITEM(TTYD64_ICON_280E1D0, TTYD64_ICON_280E3D0_pal);
static HudScript TTYD64_HES_Item_1AB = TTYD64_HES_ITEM(TTYD64_ICON_280E410, TTYD64_ICON_280E610_pal);
static HudScript TTYD64_HES_Item_1AB_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280E410, TTYD64_ICON_280E630_pal);
static ItemScript TTYD64_IES_Item_1AB = TTYD64_IES_ITEM(TTYD64_ICON_280E410, TTYD64_ICON_280E610_pal);
static HudScript TTYD64_HES_Item_1AC = TTYD64_HES_ITEM(TTYD64_ICON_280E650, TTYD64_ICON_280E850_pal);
static HudScript TTYD64_HES_Item_1AC_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280E650, TTYD64_ICON_280E870_pal);
static ItemScript TTYD64_IES_Item_1AC = TTYD64_IES_ITEM(TTYD64_ICON_280E650, TTYD64_ICON_280E850_pal);
static HudScript TTYD64_HES_Item_1AD = TTYD64_HES_ITEM(TTYD64_ICON_280E890, TTYD64_ICON_280EA90_pal);
static HudScript TTYD64_HES_Item_1AD_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280E890, TTYD64_ICON_280EAB0_pal);
static ItemScript TTYD64_IES_Item_1AD = TTYD64_IES_ITEM(TTYD64_ICON_280E890, TTYD64_ICON_280EA90_pal);
static HudScript TTYD64_HES_Item_1AE = TTYD64_HES_ITEM(TTYD64_ICON_280EAD0, TTYD64_ICON_280ECD0_pal);
static HudScript TTYD64_HES_Item_1AE_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280EAD0, TTYD64_ICON_280ECF0_pal);
static ItemScript TTYD64_IES_Item_1AE = TTYD64_IES_ITEM(TTYD64_ICON_280EAD0, TTYD64_ICON_280ECD0_pal);
static HudScript TTYD64_HES_Item_1AF = TTYD64_HES_ITEM(TTYD64_ICON_280ED10, TTYD64_ICON_280EF10_pal);
static HudScript TTYD64_HES_Item_1AF_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280ED10, TTYD64_ICON_280EF30_pal);
static ItemScript TTYD64_IES_Item_1AF = TTYD64_IES_ITEM(TTYD64_ICON_280ED10, TTYD64_ICON_280EF10_pal);
static HudScript TTYD64_HES_Item_1B0 = TTYD64_HES_ITEM(TTYD64_ICON_280EF50, TTYD64_ICON_280F150_pal);
static HudScript TTYD64_HES_Item_1B0_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280EF50, TTYD64_ICON_280F170_pal);
static ItemScript TTYD64_IES_Item_1B0 = TTYD64_IES_ITEM(TTYD64_ICON_280EF50, TTYD64_ICON_280F150_pal);
static HudScript TTYD64_HES_Item_1B1 = TTYD64_HES_ITEM(TTYD64_ICON_280F190, TTYD64_ICON_280F390_pal);
static HudScript TTYD64_HES_Item_1B1_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280F190, TTYD64_ICON_280F3B0_pal);
static ItemScript TTYD64_IES_Item_1B1 = TTYD64_IES_ITEM(TTYD64_ICON_280F190, TTYD64_ICON_280F390_pal);
static HudScript TTYD64_HES_Item_1B2 = TTYD64_HES_ITEM(TTYD64_ICON_280F3D0, TTYD64_ICON_280F5D0_pal);
static HudScript TTYD64_HES_Item_1B2_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280F3D0, TTYD64_ICON_280F5F0_pal);
static ItemScript TTYD64_IES_Item_1B2 = TTYD64_IES_ITEM(TTYD64_ICON_280F3D0, TTYD64_ICON_280F5D0_pal);
static HudScript TTYD64_HES_Item_1B3 = TTYD64_HES_ITEM(TTYD64_ICON_280F610, TTYD64_ICON_280F810_pal);
static HudScript TTYD64_HES_Item_1B3_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280F610, TTYD64_ICON_280F830_pal);
static ItemScript TTYD64_IES_Item_1B3 = TTYD64_IES_ITEM(TTYD64_ICON_280F610, TTYD64_ICON_280F810_pal);
static HudScript TTYD64_HES_Item_1B4 = TTYD64_HES_ITEM(TTYD64_ICON_280F850, TTYD64_ICON_280FA50_pal);
static HudScript TTYD64_HES_Item_1B4_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280F850, TTYD64_ICON_280FA70_pal);
static ItemScript TTYD64_IES_Item_1B4 = TTYD64_IES_ITEM(TTYD64_ICON_280F850, TTYD64_ICON_280FA50_pal);
static HudScript TTYD64_HES_Item_1B5 = TTYD64_HES_ITEM(TTYD64_ICON_280FA90, TTYD64_ICON_280FC90_pal);
static HudScript TTYD64_HES_Item_1B5_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280FA90, TTYD64_ICON_280FCB0_pal);
static ItemScript TTYD64_IES_Item_1B5 = TTYD64_IES_ITEM(TTYD64_ICON_280FA90, TTYD64_ICON_280FC90_pal);
static HudScript TTYD64_HES_Item_1B6 = TTYD64_HES_ITEM(TTYD64_ICON_280FCD0, TTYD64_ICON_280FED0_pal);
static HudScript TTYD64_HES_Item_1B6_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280FCD0, TTYD64_ICON_280FEF0_pal);
static ItemScript TTYD64_IES_Item_1B6 = TTYD64_IES_ITEM(TTYD64_ICON_280FCD0, TTYD64_ICON_280FED0_pal);
static HudScript TTYD64_HES_Item_1B7 = TTYD64_HES_ITEM(TTYD64_ICON_280FF10, TTYD64_ICON_2810110_pal);
static HudScript TTYD64_HES_Item_1B7_disabled = TTYD64_HES_ITEM(TTYD64_ICON_280FF10, TTYD64_ICON_2810130_pal);
static ItemScript TTYD64_IES_Item_1B7 = TTYD64_IES_ITEM(TTYD64_ICON_280FF10, TTYD64_ICON_2810110_pal);
static HudScript TTYD64_HES_Item_1B8 = TTYD64_HES_ITEM(TTYD64_ICON_2810150, TTYD64_ICON_2810350_pal);
static HudScript TTYD64_HES_Item_1B8_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2810150, TTYD64_ICON_2810370_pal);
static ItemScript TTYD64_IES_Item_1B8 = TTYD64_IES_ITEM(TTYD64_ICON_2810150, TTYD64_ICON_2810350_pal);
static HudScript TTYD64_HES_Item_1B9 = TTYD64_HES_ITEM(TTYD64_ICON_2810390, TTYD64_ICON_2810590_pal);
static HudScript TTYD64_HES_Item_1B9_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2810390, TTYD64_ICON_28105B0_pal);
static ItemScript TTYD64_IES_Item_1B9 = TTYD64_IES_ITEM(TTYD64_ICON_2810390, TTYD64_ICON_2810590_pal);
static HudScript TTYD64_HES_Item_1BA = TTYD64_HES_ITEM(TTYD64_ICON_28105D0, TTYD64_ICON_28107D0_pal);
static HudScript TTYD64_HES_Item_1BA_disabled = TTYD64_HES_ITEM(TTYD64_ICON_28105D0, TTYD64_ICON_28107F0_pal);
static ItemScript TTYD64_IES_Item_1BA = TTYD64_IES_ITEM(TTYD64_ICON_28105D0, TTYD64_ICON_28107D0_pal);
static HudScript TTYD64_HES_Item_1BB = TTYD64_HES_ITEM(TTYD64_ICON_2810810, TTYD64_ICON_2810A10_pal);
static HudScript TTYD64_HES_Item_1BB_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2810810, TTYD64_ICON_2810A30_pal);
static ItemScript TTYD64_IES_Item_1BB = TTYD64_IES_ITEM(TTYD64_ICON_2810810, TTYD64_ICON_2810A10_pal);
static HudScript TTYD64_HES_Item_1BC = TTYD64_HES_ITEM(TTYD64_ICON_2810A50, TTYD64_ICON_2810C50_pal);
static HudScript TTYD64_HES_Item_1BC_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2810A50, TTYD64_ICON_2810C70_pal);
static ItemScript TTYD64_IES_Item_1BC = TTYD64_IES_ITEM(TTYD64_ICON_2810A50, TTYD64_ICON_2810C50_pal);
static HudScript TTYD64_HES_Item_1BD = TTYD64_HES_ITEM(TTYD64_ICON_2810C90, TTYD64_ICON_2810E90_pal);
static HudScript TTYD64_HES_Item_1BD_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2810C90, TTYD64_ICON_2810EB0_pal);
static ItemScript TTYD64_IES_Item_1BD = TTYD64_IES_ITEM(TTYD64_ICON_2810C90, TTYD64_ICON_2810E90_pal);
static HudScript TTYD64_HES_Item_1BE = TTYD64_HES_ITEM(TTYD64_ICON_2810ED0, TTYD64_ICON_28110D0_pal);
static HudScript TTYD64_HES_Item_1BE_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2810ED0, TTYD64_ICON_28110F0_pal);
static ItemScript TTYD64_IES_Item_1BE = TTYD64_IES_ITEM(TTYD64_ICON_2810ED0, TTYD64_ICON_28110D0_pal);
static HudScript TTYD64_HES_Item_1BF = TTYD64_HES_ITEM(TTYD64_ICON_2811110, TTYD64_ICON_2811310_pal);
static HudScript TTYD64_HES_Item_1BF_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2811110, TTYD64_ICON_2811330_pal);
static ItemScript TTYD64_IES_Item_1BF = TTYD64_IES_ITEM(TTYD64_ICON_2811110, TTYD64_ICON_2811310_pal);
static HudScript TTYD64_HES_Item_1C0 = TTYD64_HES_ITEM(TTYD64_ICON_2811350, TTYD64_ICON_2811550_pal);
static HudScript TTYD64_HES_Item_1C0_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2811350, TTYD64_ICON_2811570_pal);
static ItemScript TTYD64_IES_Item_1C0 = TTYD64_IES_ITEM(TTYD64_ICON_2811350, TTYD64_ICON_2811550_pal);
static HudScript TTYD64_HES_Item_1C1 = TTYD64_HES_ITEM(TTYD64_ICON_2811590, TTYD64_ICON_2811790_pal);
static HudScript TTYD64_HES_Item_1C1_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2811590, TTYD64_ICON_28117B0_pal);
static ItemScript TTYD64_IES_Item_1C1 = TTYD64_IES_ITEM(TTYD64_ICON_2811590, TTYD64_ICON_2811790_pal);
static HudScript TTYD64_HES_Item_1C2 = TTYD64_HES_ITEM(TTYD64_ICON_28117D0, TTYD64_ICON_28119D0_pal);
static HudScript TTYD64_HES_Item_1C2_disabled = TTYD64_HES_ITEM(TTYD64_ICON_28117D0, TTYD64_ICON_28119F0_pal);
static ItemScript TTYD64_IES_Item_1C2 = TTYD64_IES_ITEM(TTYD64_ICON_28117D0, TTYD64_ICON_28119D0_pal);
static HudScript TTYD64_HES_Item_1C3 = TTYD64_HES_ITEM(TTYD64_ICON_2811A10, TTYD64_ICON_2811C10_pal);
static HudScript TTYD64_HES_Item_1C3_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2811A10, TTYD64_ICON_2811C30_pal);
static ItemScript TTYD64_IES_Item_1C3 = TTYD64_IES_ITEM(TTYD64_ICON_2811A10, TTYD64_ICON_2811C10_pal);
static HudScript TTYD64_HES_Item_1C4 = TTYD64_HES_ITEM(TTYD64_ICON_2811C50, TTYD64_ICON_2811E50_pal);
static HudScript TTYD64_HES_Item_1C4_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2811C50, TTYD64_ICON_2811E70_pal);
static ItemScript TTYD64_IES_Item_1C4 = TTYD64_IES_ITEM(TTYD64_ICON_2811C50, TTYD64_ICON_2811E50_pal);
static HudScript TTYD64_HES_Item_1C5 = TTYD64_HES_ITEM(TTYD64_ICON_2811E90, TTYD64_ICON_2812090_pal);
static HudScript TTYD64_HES_Item_1C5_disabled = TTYD64_HES_ITEM(TTYD64_ICON_2811E90, TTYD64_ICON_28120B0_pal);
static ItemScript TTYD64_IES_Item_1C5 = TTYD64_IES_ITEM(TTYD64_ICON_2811E90, TTYD64_ICON_2812090_pal);
static HudScript TTYD64_HES_Item_1C6 = TTYD64_HES_ITEM(TTYD64_ICON_28120D0, TTYD64_ICON_28122D0_pal);
static HudScript TTYD64_HES_Item_1C6_disabled = TTYD64_HES_ITEM(TTYD64_ICON_28120D0, TTYD64_ICON_28122F0_pal);
static ItemScript TTYD64_IES_Item_1C6 = TTYD64_IES_ITEM(TTYD64_ICON_28120D0, TTYD64_ICON_28122D0_pal);
static HudScript TTYD64_HES_Item_1C7 = TTYD64_HES_ITEM(TTYD64_ICON_2812310, TTYD64_ICON_2812510_pal);
static ItemScript TTYD64_IES_Item_1C7 = TTYD64_IES_ITEM(TTYD64_ICON_2812310, TTYD64_ICON_2812510_pal);

const TTYD64_ItemIcon TTYD64_ItemIcons[] = {
    { 0x0EE, &TTYD64_HES_Item_0EE, &TTYD64_HES_Item_0EE_disabled, &TTYD64_IES_Item_0EE, TTYD64_ICON_2809790,
      TTYD64_ICON_2809990_pal },
    { 0x12D, &TTYD64_HES_Item_12D, &TTYD64_HES_Item_12D_disabled, &TTYD64_IES_Item_12D, TTYD64_ICON_28090D0,
      TTYD64_ICON_28092D0_pal },
    { 0x12E, &TTYD64_HES_Item_12E, &TTYD64_HES_Item_12E_disabled, &TTYD64_IES_Item_12E, TTYD64_ICON_2808E90,
      TTYD64_ICON_2809090_pal },
    { 0x143, &TTYD64_HES_Item_143, &TTYD64_HES_Item_143_disabled, &TTYD64_IES_Item_143, TTYD64_ICON_2805890,
      TTYD64_ICON_2805A90_pal },
    { 0x16D, &TTYD64_HES_Item_16D, &TTYD64_HES_Item_16D_disabled, &TTYD64_IES_Item_16D, TTYD64_ICON_2804F90,
      TTYD64_ICON_2805190_pal },
    { 0x16E, &TTYD64_HES_Item_16E, &TTYD64_HES_Item_16E_disabled, &TTYD64_IES_Item_16E, TTYD64_ICON_2809C10,
      TTYD64_ICON_2809E10_pal },
    { 0x16F, &TTYD64_HES_Item_16F, &TTYD64_HES_Item_16F_disabled, &TTYD64_IES_Item_16F, TTYD64_ICON_2807C90,
      TTYD64_ICON_2807E90_pal },
    { 0x170, &TTYD64_HES_Item_170, &TTYD64_HES_Item_170_disabled, &TTYD64_IES_Item_170, TTYD64_ICON_2807150,
      TTYD64_ICON_2807350_pal },
    { 0x171, &TTYD64_HES_Item_171, &TTYD64_HES_Item_171_disabled, &TTYD64_IES_Item_171, TTYD64_ICON_2806190,
      TTYD64_ICON_2806390_pal },
    { 0x172, &TTYD64_HES_Item_172, &TTYD64_HES_Item_172_disabled, &TTYD64_IES_Item_172, TTYD64_ICON_2806F10,
      TTYD64_ICON_2807110_pal },
    { 0x173, &TTYD64_HES_Item_173, &TTYD64_HES_Item_173_disabled, &TTYD64_IES_Item_173, TTYD64_ICON_28075D0,
      TTYD64_ICON_28077D0_pal },
    { 0x174, &TTYD64_HES_Item_174, &TTYD64_HES_Item_174_disabled, &TTYD64_IES_Item_174, TTYD64_ICON_2809550,
      TTYD64_ICON_2809750_pal },
    { 0x175, &TTYD64_HES_Item_175, &TTYD64_HES_Item_175_disabled, &TTYD64_IES_Item_175, TTYD64_ICON_2809E50,
      TTYD64_ICON_280A050_pal },
    { 0x176, &TTYD64_HES_Item_176, &TTYD64_HES_Item_176_disabled, &TTYD64_IES_Item_176, TTYD64_ICON_2808A10,
      TTYD64_ICON_2808C10_pal },
    { 0x177, &TTYD64_HES_Item_177, &TTYD64_HES_Item_177_disabled, &TTYD64_IES_Item_177, TTYD64_ICON_2807ED0,
      TTYD64_ICON_28080D0_pal },
    { 0x178, &TTYD64_HES_Item_178, &TTYD64_HES_Item_178_disabled, &TTYD64_IES_Item_178, TTYD64_ICON_28099D0,
      TTYD64_ICON_2809BD0_pal },
    { 0x179, &TTYD64_HES_Item_179, &TTYD64_HES_Item_179_disabled, &TTYD64_IES_Item_179, TTYD64_ICON_2806CD0,
      TTYD64_ICON_2806ED0_pal },
    { 0x17A, &TTYD64_HES_Item_17A, &TTYD64_HES_Item_17A_disabled, &TTYD64_IES_Item_17A, TTYD64_ICON_2806610,
      TTYD64_ICON_2806810_pal },
    { 0x17B, &TTYD64_HES_Item_17B, &TTYD64_HES_Item_17B_disabled, &TTYD64_IES_Item_17B, TTYD64_ICON_2808C50,
      TTYD64_ICON_2808E50_pal },
    { 0x17C, &TTYD64_HES_Item_17C, &TTYD64_HES_Item_17C_disabled, &TTYD64_IES_Item_17C, TTYD64_ICON_2809310,
      TTYD64_ICON_2809510_pal },
    { 0x17D, &TTYD64_HES_Item_17D, &TTYD64_HES_Item_17D_disabled, &TTYD64_IES_Item_17D, TTYD64_ICON_28051D0,
      TTYD64_ICON_28053D0_pal },
    { 0x17E, &TTYD64_HES_Item_17E, &TTYD64_HES_Item_17E_disabled, &TTYD64_IES_Item_17E, TTYD64_ICON_2805410,
      TTYD64_ICON_2805610_pal },
    { 0x17F, &TTYD64_HES_Item_17F, &TTYD64_HES_Item_17F_disabled, &TTYD64_IES_Item_17F, TTYD64_ICON_2808590,
      TTYD64_ICON_2808790_pal },
    { 0x180, &TTYD64_HES_Item_180, &TTYD64_HES_Item_180_disabled, &TTYD64_IES_Item_180, TTYD64_ICON_2805650,
      TTYD64_ICON_2805850_pal },
    { 0x181, &TTYD64_HES_Item_181, &TTYD64_HES_Item_181_disabled, &TTYD64_IES_Item_181, TTYD64_ICON_2805AD0,
      TTYD64_ICON_2805CD0_pal },
    { 0x182, &TTYD64_HES_Item_182, &TTYD64_HES_Item_182_disabled, &TTYD64_IES_Item_182, TTYD64_ICON_2807390,
      TTYD64_ICON_2807590_pal },
    { 0x183, &TTYD64_HES_Item_183, &TTYD64_HES_Item_183_disabled, &TTYD64_IES_Item_183, TTYD64_ICON_2808110,
      TTYD64_ICON_2808310_pal },
    { 0x184, &TTYD64_HES_Item_184, &TTYD64_HES_Item_184_disabled, &TTYD64_IES_Item_184, TTYD64_ICON_2808350,
      TTYD64_ICON_2808550_pal },
    { 0x185, &TTYD64_HES_Item_185, &TTYD64_HES_Item_185_disabled, &TTYD64_IES_Item_185, TTYD64_ICON_2807810,
      TTYD64_ICON_2807A10_pal },
    { 0x186, &TTYD64_HES_Item_186, &TTYD64_HES_Item_186_disabled, &TTYD64_IES_Item_186, TTYD64_ICON_2807A50,
      TTYD64_ICON_2807C50_pal },
    { 0x187, &TTYD64_HES_Item_187, &TTYD64_HES_Item_187_disabled, &TTYD64_IES_Item_187, TTYD64_ICON_28087D0,
      TTYD64_ICON_28089D0_pal },
    { 0x188, &TTYD64_HES_Item_188, &TTYD64_HES_Item_188_disabled, &TTYD64_IES_Item_188, TTYD64_ICON_280A090,
      TTYD64_ICON_280A290_pal },
    { 0x189, &TTYD64_HES_Item_189, &TTYD64_HES_Item_189_disabled, &TTYD64_IES_Item_189, TTYD64_ICON_2805D10,
      TTYD64_ICON_2805F10_pal },
    { 0x18A, &TTYD64_HES_Item_18A, &TTYD64_HES_Item_18A_disabled, &TTYD64_IES_Item_18A, TTYD64_ICON_2805F50,
      TTYD64_ICON_2806150_pal },
    { 0x18B, &TTYD64_HES_Item_18B, &TTYD64_HES_Item_18B_disabled, &TTYD64_IES_Item_18B, TTYD64_ICON_28063D0,
      TTYD64_ICON_28065D0_pal },
    { 0x18C, &TTYD64_HES_Item_18C, &TTYD64_HES_Item_18C_disabled, &TTYD64_IES_Item_18C, TTYD64_ICON_2806850,
      TTYD64_ICON_2806A50_pal },
    { 0x18D, &TTYD64_HES_Item_18D, &TTYD64_HES_Item_18D_disabled, &TTYD64_IES_Item_18D, TTYD64_ICON_2806A90,
      TTYD64_ICON_2806C90_pal },
    { 0x18E, &TTYD64_HES_Item_18E, &TTYD64_HES_Item_18E_disabled, &TTYD64_IES_Item_18E, TTYD64_ICON_280A2D0,
      TTYD64_ICON_280A4D0_pal },
    { 0x18F, &TTYD64_HES_Item_18F, &TTYD64_HES_Item_18F_disabled, &TTYD64_IES_Item_18F, TTYD64_ICON_280A510,
      TTYD64_ICON_280A710_pal },
    { 0x190, &TTYD64_HES_Item_190, &TTYD64_HES_Item_190_disabled, &TTYD64_IES_Item_190, TTYD64_ICON_280A750,
      TTYD64_ICON_280A950_pal },
    { 0x191, &TTYD64_HES_Item_191, &TTYD64_HES_Item_191_disabled, &TTYD64_IES_Item_191, TTYD64_ICON_280A990,
      TTYD64_ICON_280AB90_pal },
    { 0x192, &TTYD64_HES_Item_192, &TTYD64_HES_Item_192_disabled, &TTYD64_IES_Item_192, TTYD64_ICON_280ABD0,
      TTYD64_ICON_280ADD0_pal },
    { 0x193, &TTYD64_HES_Item_193, &TTYD64_HES_Item_193_disabled, &TTYD64_IES_Item_193, TTYD64_ICON_280AE10,
      TTYD64_ICON_280B010_pal },
    { 0x194, &TTYD64_HES_Item_194, &TTYD64_HES_Item_194_disabled, &TTYD64_IES_Item_194, TTYD64_ICON_280B050,
      TTYD64_ICON_280B250_pal },
    { 0x195, &TTYD64_HES_Item_195, &TTYD64_HES_Item_195_disabled, &TTYD64_IES_Item_195, TTYD64_ICON_280B290,
      TTYD64_ICON_280B490_pal },
    { 0x196, &TTYD64_HES_Item_196, &TTYD64_HES_Item_196_disabled, &TTYD64_IES_Item_196, TTYD64_ICON_280B4D0,
      TTYD64_ICON_280B6D0_pal },
    { 0x197, &TTYD64_HES_Item_197, &TTYD64_HES_Item_197_disabled, &TTYD64_IES_Item_197, TTYD64_ICON_280B710,
      TTYD64_ICON_280B910_pal },
    { 0x198, &TTYD64_HES_Item_198, &TTYD64_HES_Item_198_disabled, &TTYD64_IES_Item_198, TTYD64_ICON_280B950,
      TTYD64_ICON_280BB50_pal },
    { 0x199, &TTYD64_HES_Item_199, &TTYD64_HES_Item_199_disabled, &TTYD64_IES_Item_199, TTYD64_ICON_280BB90,
      TTYD64_ICON_280BD90_pal },
    { 0x19A, &TTYD64_HES_Item_19A, &TTYD64_HES_Item_19A_disabled, &TTYD64_IES_Item_19A, TTYD64_ICON_280BDD0,
      TTYD64_ICON_280BFD0_pal },
    { 0x19B, &TTYD64_HES_Item_19B, &TTYD64_HES_Item_19B_disabled, &TTYD64_IES_Item_19B, TTYD64_ICON_280C010,
      TTYD64_ICON_280C210_pal },
    { 0x19C, &TTYD64_HES_Item_19C, &TTYD64_HES_Item_19C_disabled, &TTYD64_IES_Item_19C, TTYD64_ICON_280C250,
      TTYD64_ICON_280C450_pal },
    { 0x19D, &TTYD64_HES_Item_19D, &TTYD64_HES_Item_19D_disabled, &TTYD64_IES_Item_19D, TTYD64_ICON_280C490,
      TTYD64_ICON_280C690_pal },
    { 0x19E, &TTYD64_HES_Item_19E, &TTYD64_HES_Item_19E_disabled, &TTYD64_IES_Item_19E, TTYD64_ICON_280C6D0,
      TTYD64_ICON_280C8D0_pal },
    { 0x19F, &TTYD64_HES_Item_19F, &TTYD64_HES_Item_19F_disabled, &TTYD64_IES_Item_19F, TTYD64_ICON_280C910,
      TTYD64_ICON_280CB10_pal },
    { 0x1A0, &TTYD64_HES_Item_1A0, &TTYD64_HES_Item_1A0_disabled, &TTYD64_IES_Item_1A0, TTYD64_ICON_280CB50,
      TTYD64_ICON_280CD50_pal },
    { 0x1A1, &TTYD64_HES_Item_1A1, &TTYD64_HES_Item_1A1_disabled, &TTYD64_IES_Item_1A1, TTYD64_ICON_280CD90,
      TTYD64_ICON_280CF90_pal },
    { 0x1A2, &TTYD64_HES_Item_1A2, &TTYD64_HES_Item_1A2_disabled, &TTYD64_IES_Item_1A2, TTYD64_ICON_280CFD0,
      TTYD64_ICON_280D1D0_pal },
    { 0x1A3, &TTYD64_HES_Item_1A3, &TTYD64_HES_Item_1A3_disabled, &TTYD64_IES_Item_1A3, TTYD64_ICON_280D210,
      TTYD64_ICON_280D410_pal },
    { 0x1A4, &TTYD64_HES_Item_1A4, &TTYD64_HES_Item_1A4_disabled, &TTYD64_IES_Item_1A4, TTYD64_ICON_280D450,
      TTYD64_ICON_280D650_pal },
    { 0x1A5, &TTYD64_HES_Item_1A5, &TTYD64_HES_Item_1A5_disabled, &TTYD64_IES_Item_1A5, TTYD64_ICON_280D690,
      TTYD64_ICON_280D890_pal },
    { 0x1A6, &TTYD64_HES_Item_1A6, &TTYD64_HES_Item_1A6_disabled, &TTYD64_IES_Item_1A6, TTYD64_ICON_280D8D0,
      TTYD64_ICON_280DAD0_pal },
    { 0x1A7, &TTYD64_HES_Item_1A7, &TTYD64_HES_Item_1A7_disabled, &TTYD64_IES_Item_1A7, TTYD64_ICON_280DB10,
      TTYD64_ICON_280DD10_pal },
    { 0x1A8, &TTYD64_HES_Item_1A8, &TTYD64_HES_Item_1A8_disabled, &TTYD64_IES_Item_1A8, TTYD64_ICON_280DD50,
      TTYD64_ICON_280DF50_pal },
    { 0x1A9, &TTYD64_HES_Item_1A9, &TTYD64_HES_Item_1A9_disabled, &TTYD64_IES_Item_1A9, TTYD64_ICON_280DF90,
      TTYD64_ICON_280E190_pal },
    { 0x1AA, &TTYD64_HES_Item_1AA, &TTYD64_HES_Item_1AA_disabled, &TTYD64_IES_Item_1AA, TTYD64_ICON_280E1D0,
      TTYD64_ICON_280E3D0_pal },
    { 0x1AB, &TTYD64_HES_Item_1AB, &TTYD64_HES_Item_1AB_disabled, &TTYD64_IES_Item_1AB, TTYD64_ICON_280E410,
      TTYD64_ICON_280E610_pal },
    { 0x1AC, &TTYD64_HES_Item_1AC, &TTYD64_HES_Item_1AC_disabled, &TTYD64_IES_Item_1AC, TTYD64_ICON_280E650,
      TTYD64_ICON_280E850_pal },
    { 0x1AD, &TTYD64_HES_Item_1AD, &TTYD64_HES_Item_1AD_disabled, &TTYD64_IES_Item_1AD, TTYD64_ICON_280E890,
      TTYD64_ICON_280EA90_pal },
    { 0x1AE, &TTYD64_HES_Item_1AE, &TTYD64_HES_Item_1AE_disabled, &TTYD64_IES_Item_1AE, TTYD64_ICON_280EAD0,
      TTYD64_ICON_280ECD0_pal },
    { 0x1AF, &TTYD64_HES_Item_1AF, &TTYD64_HES_Item_1AF_disabled, &TTYD64_IES_Item_1AF, TTYD64_ICON_280ED10,
      TTYD64_ICON_280EF10_pal },
    { 0x1B0, &TTYD64_HES_Item_1B0, &TTYD64_HES_Item_1B0_disabled, &TTYD64_IES_Item_1B0, TTYD64_ICON_280EF50,
      TTYD64_ICON_280F150_pal },
    { 0x1B1, &TTYD64_HES_Item_1B1, &TTYD64_HES_Item_1B1_disabled, &TTYD64_IES_Item_1B1, TTYD64_ICON_280F190,
      TTYD64_ICON_280F390_pal },
    { 0x1B2, &TTYD64_HES_Item_1B2, &TTYD64_HES_Item_1B2_disabled, &TTYD64_IES_Item_1B2, TTYD64_ICON_280F3D0,
      TTYD64_ICON_280F5D0_pal },
    { 0x1B3, &TTYD64_HES_Item_1B3, &TTYD64_HES_Item_1B3_disabled, &TTYD64_IES_Item_1B3, TTYD64_ICON_280F610,
      TTYD64_ICON_280F810_pal },
    { 0x1B4, &TTYD64_HES_Item_1B4, &TTYD64_HES_Item_1B4_disabled, &TTYD64_IES_Item_1B4, TTYD64_ICON_280F850,
      TTYD64_ICON_280FA50_pal },
    { 0x1B5, &TTYD64_HES_Item_1B5, &TTYD64_HES_Item_1B5_disabled, &TTYD64_IES_Item_1B5, TTYD64_ICON_280FA90,
      TTYD64_ICON_280FC90_pal },
    { 0x1B6, &TTYD64_HES_Item_1B6, &TTYD64_HES_Item_1B6_disabled, &TTYD64_IES_Item_1B6, TTYD64_ICON_280FCD0,
      TTYD64_ICON_280FED0_pal },
    { 0x1B7, &TTYD64_HES_Item_1B7, &TTYD64_HES_Item_1B7_disabled, &TTYD64_IES_Item_1B7, TTYD64_ICON_280FF10,
      TTYD64_ICON_2810110_pal },
    { 0x1B8, &TTYD64_HES_Item_1B8, &TTYD64_HES_Item_1B8_disabled, &TTYD64_IES_Item_1B8, TTYD64_ICON_2810150,
      TTYD64_ICON_2810350_pal },
    { 0x1B9, &TTYD64_HES_Item_1B9, &TTYD64_HES_Item_1B9_disabled, &TTYD64_IES_Item_1B9, TTYD64_ICON_2810390,
      TTYD64_ICON_2810590_pal },
    { 0x1BA, &TTYD64_HES_Item_1BA, &TTYD64_HES_Item_1BA_disabled, &TTYD64_IES_Item_1BA, TTYD64_ICON_28105D0,
      TTYD64_ICON_28107D0_pal },
    { 0x1BB, &TTYD64_HES_Item_1BB, &TTYD64_HES_Item_1BB_disabled, &TTYD64_IES_Item_1BB, TTYD64_ICON_2810810,
      TTYD64_ICON_2810A10_pal },
    { 0x1BC, &TTYD64_HES_Item_1BC, &TTYD64_HES_Item_1BC_disabled, &TTYD64_IES_Item_1BC, TTYD64_ICON_2810A50,
      TTYD64_ICON_2810C50_pal },
    { 0x1BD, &TTYD64_HES_Item_1BD, &TTYD64_HES_Item_1BD_disabled, &TTYD64_IES_Item_1BD, TTYD64_ICON_2810C90,
      TTYD64_ICON_2810E90_pal },
    { 0x1BE, &TTYD64_HES_Item_1BE, &TTYD64_HES_Item_1BE_disabled, &TTYD64_IES_Item_1BE, TTYD64_ICON_2810ED0,
      TTYD64_ICON_28110D0_pal },
    { 0x1BF, &TTYD64_HES_Item_1BF, &TTYD64_HES_Item_1BF_disabled, &TTYD64_IES_Item_1BF, TTYD64_ICON_2811110,
      TTYD64_ICON_2811310_pal },
    { 0x1C0, &TTYD64_HES_Item_1C0, &TTYD64_HES_Item_1C0_disabled, &TTYD64_IES_Item_1C0, TTYD64_ICON_2811350,
      TTYD64_ICON_2811550_pal },
    { 0x1C1, &TTYD64_HES_Item_1C1, &TTYD64_HES_Item_1C1_disabled, &TTYD64_IES_Item_1C1, TTYD64_ICON_2811590,
      TTYD64_ICON_2811790_pal },
    { 0x1C2, &TTYD64_HES_Item_1C2, &TTYD64_HES_Item_1C2_disabled, &TTYD64_IES_Item_1C2, TTYD64_ICON_28117D0,
      TTYD64_ICON_28119D0_pal },
    { 0x1C3, &TTYD64_HES_Item_1C3, &TTYD64_HES_Item_1C3_disabled, &TTYD64_IES_Item_1C3, TTYD64_ICON_2811A10,
      TTYD64_ICON_2811C10_pal },
    { 0x1C4, &TTYD64_HES_Item_1C4, &TTYD64_HES_Item_1C4_disabled, &TTYD64_IES_Item_1C4, TTYD64_ICON_2811C50,
      TTYD64_ICON_2811E50_pal },
    { 0x1C5, &TTYD64_HES_Item_1C5, &TTYD64_HES_Item_1C5_disabled, &TTYD64_IES_Item_1C5, TTYD64_ICON_2811E90,
      TTYD64_ICON_2812090_pal },
    { 0x1C6, &TTYD64_HES_Item_1C6, &TTYD64_HES_Item_1C6_disabled, &TTYD64_IES_Item_1C6, TTYD64_ICON_28120D0,
      TTYD64_ICON_28122D0_pal },
    { 0x1C7, &TTYD64_HES_Item_1C7, &TTYD64_HES_Item_1C7, &TTYD64_IES_Item_1C7, TTYD64_ICON_2812310,
      TTYD64_ICON_2812510_pal },
};

const s32 TTYD64_ItemIconCount = ARRAY_COUNT(TTYD64_ItemIcons);

static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_Gift[] = "__OTR__icons/key/Gift";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_Gift_pal[] = "__OTR__icons/key/Gift.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakeDone[] = "__OTR__icons/key/CakeDone";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakeDone_pal[] = "__OTR__icons/key/CakeDone.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakeBare[] = "__OTR__icons/key/CakeBare";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakeBare_pal[] = "__OTR__icons/key/CakeBare.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakePan[] = "__OTR__icons/key/CakePan";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakePan_pal[] = "__OTR__icons/key/CakePan.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakeBatter[] = "__OTR__icons/key/CakeBatter";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakeBatter_pal[] = "__OTR__icons/key/CakeBatter.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakeBowl[] = "__OTR__icons/key/CakeBowl";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakeBowl_pal[] = "__OTR__icons/key/CakeBowl.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakeMixed[] = "__OTR__icons/key/CakeMixed";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakeMixed_pal[] = "__OTR__icons/key/CakeMixed.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakeWithIcing[] = "__OTR__icons/key/CakeWithIcing";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakeWithIcing_pal[] = "__OTR__icons/key/CakeWithIcing.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakeWithBerries[] = "__OTR__icons/key/CakeWithBerries";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_key_CakeWithBerries_pal[] = "__OTR__icons/key/CakeWithBerries.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_menu_hammer_1[] = "__OTR__icons/menu/hammer_1";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_menu_hammer_1_pal[] = "__OTR__icons/menu/hammer_1.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_menu_hammer_2[] = "__OTR__icons/menu/hammer_2";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_menu_hammer_2_pal[] = "__OTR__icons/menu/hammer_2.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_menu_hammer_3[] = "__OTR__icons/menu/hammer_3";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_menu_hammer_3_pal[] = "__OTR__icons/menu/hammer_3.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_menu_boots_1[] = "__OTR__icons/menu/boots_1";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_menu_boots_1_pal[] = "__OTR__icons/menu/boots_1.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_menu_boots_2[] = "__OTR__icons/menu/boots_2";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_menu_boots_2_pal[] = "__OTR__icons/menu/boots_2.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_menu_boots_3[] = "__OTR__icons/menu/boots_3";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_menu_boots_3_pal[] = "__OTR__icons/menu/boots_3.pal";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_menu_items[] = "__OTR__icons/menu/items";
static const ALIGN_ASSET(2) char TTYD64_ICON_icons_menu_items_pal[] = "__OTR__icons/menu/items.pal";

const TTYD64_ItemIconOffsets TTYD64_ItemIconTail[] = {
    { 0x15D, TTYD64_ICON_icons_key_Gift, TTYD64_ICON_icons_key_Gift_pal },
    { 0x15E, TTYD64_ICON_icons_key_CakeDone, TTYD64_ICON_icons_key_CakeDone_pal },
    { 0x15F, TTYD64_ICON_icons_key_CakeBare, TTYD64_ICON_icons_key_CakeBare_pal },
    { 0x160, TTYD64_ICON_icons_key_CakePan, TTYD64_ICON_icons_key_CakePan_pal },
    { 0x161, TTYD64_ICON_icons_key_CakeBatter, TTYD64_ICON_icons_key_CakeBatter_pal },
    { 0x162, TTYD64_ICON_icons_key_CakeBowl, TTYD64_ICON_icons_key_CakeBowl_pal },
    { 0x163, TTYD64_ICON_icons_key_CakeMixed, TTYD64_ICON_icons_key_CakeMixed_pal },
    { 0x164, TTYD64_ICON_icons_key_CakeWithIcing, TTYD64_ICON_icons_key_CakeWithIcing_pal },
    { 0x165, TTYD64_ICON_icons_key_CakeWithBerries, TTYD64_ICON_icons_key_CakeWithBerries_pal },
    { 0x166, TTYD64_ICON_icons_menu_hammer_1, TTYD64_ICON_icons_menu_hammer_1_pal },
    { 0x167, TTYD64_ICON_icons_menu_hammer_2, TTYD64_ICON_icons_menu_hammer_2_pal },
    { 0x168, TTYD64_ICON_icons_menu_hammer_3, TTYD64_ICON_icons_menu_hammer_3_pal },
    { 0x169, TTYD64_ICON_icons_menu_boots_1, TTYD64_ICON_icons_menu_boots_1_pal },
    { 0x16A, TTYD64_ICON_icons_menu_boots_2, TTYD64_ICON_icons_menu_boots_2_pal },
    { 0x16B, TTYD64_ICON_icons_menu_boots_3, TTYD64_ICON_icons_menu_boots_3_pal },
    { 0x16C, TTYD64_ICON_icons_menu_items, TTYD64_ICON_icons_menu_items_pal },
};

const s32 TTYD64_ItemIconTailCount = ARRAY_COUNT(TTYD64_ItemIconTail);
