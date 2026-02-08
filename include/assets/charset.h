#pragma once

#include "alignment.h"

static const ALIGN_ASSET(2) char CHARSET_STANDARD[] = "__OTR__charset/charset_standard";
static const ALIGN_ASSET(2) char CHARSET_STANDARD_PAL[] = "__OTR__charset/charset_standard_palette";
static const ALIGN_ASSET(2) char CHARSET_TITLE[] = "__OTR__charset/charset_title";
static const ALIGN_ASSET(2) char CHARSET_SUBTITLE[] = "__OTR__charset/charset_subtitle";
static const ALIGN_ASSET(2) char CHARSET_SUBTITLE_PAL[] = "__OTR__charset/charset_subtitle_palette";
static const ALIGN_ASSET(2) char CHARSET_TITLE_PAL[] = "__OTR__charset/charset_title_palette";

// TODO: revisit these constants if we want to allow modding these assets
#define CHARSET_POSTCARD_WIDTH 150
#define CHARSET_POSTCARD_HEIGHT 105
#define CHARSET_PEACH_LETTER_WIDTH 150
#define CHARSET_PEACH_LETTER_HEIGHT 105
#define CHARSET_LETTER_CONTENT_WIDTH 70
#define CHARSET_LETTER_CONTENT_HEIGHT 95

// Peach letter
static const ALIGN_ASSET(2) char CHARSET_PEACH_LETTER[] = "__OTR__charset/charset_peach_letter";
static const ALIGN_ASSET(2) char CHARSET_PEACH_LETTER_PAL[] = "__OTR__charset/charset_peach_letter_palette";

// Postcard
static const ALIGN_ASSET(2) char CHARSET_POSTCARD[] = "__OTR__charset/charset_postcard";
static const ALIGN_ASSET(2) char CHARSET_POSTCARD_PAL[] = "__OTR__charset/charset_postcard_palette";

// Letter content 1-12
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_1[] = "__OTR__charset/charset_letter_content_1";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_1_PAL[] = "__OTR__charset/charset_letter_content_1_palette";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_2[] = "__OTR__charset/charset_letter_content_2";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_2_PAL[] = "__OTR__charset/charset_letter_content_2_palette";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_3[] = "__OTR__charset/charset_letter_content_3";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_3_PAL[] = "__OTR__charset/charset_letter_content_3_palette";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_4[] = "__OTR__charset/charset_letter_content_4";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_4_PAL[] = "__OTR__charset/charset_letter_content_4_palette";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_5[] = "__OTR__charset/charset_letter_content_5";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_5_PAL[] = "__OTR__charset/charset_letter_content_5_palette";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_6[] = "__OTR__charset/charset_letter_content_6";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_6_PAL[] = "__OTR__charset/charset_letter_content_6_palette";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_7[] = "__OTR__charset/charset_letter_content_7";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_7_PAL[] = "__OTR__charset/charset_letter_content_7_palette";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_8[] = "__OTR__charset/charset_letter_content_8";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_8_PAL[] = "__OTR__charset/charset_letter_content_8_palette";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_9[] = "__OTR__charset/charset_letter_content_9";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_9_PAL[] = "__OTR__charset/charset_letter_content_9_palette";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_10[] = "__OTR__charset/charset_letter_content_10";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_10_PAL[] = "__OTR__charset/charset_letter_content_10_palette";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_11[] = "__OTR__charset/charset_letter_content_11";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_11_PAL[] = "__OTR__charset/charset_letter_content_11_palette";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_12[] = "__OTR__charset/charset_letter_content_12";
static const ALIGN_ASSET(2) char CHARSET_LETTER_CONTENT_12_PAL[] = "__OTR__charset/charset_letter_content_12_palette";

// Lookup arrays for indexed access
static const char* const CHARSET_LETTER_CONTENT_IMGS[] = {
    CHARSET_LETTER_CONTENT_1,  CHARSET_LETTER_CONTENT_2,  CHARSET_LETTER_CONTENT_3,
    CHARSET_LETTER_CONTENT_4,  CHARSET_LETTER_CONTENT_5,  CHARSET_LETTER_CONTENT_6,
    CHARSET_LETTER_CONTENT_7,  CHARSET_LETTER_CONTENT_8,  CHARSET_LETTER_CONTENT_9,
    CHARSET_LETTER_CONTENT_10, CHARSET_LETTER_CONTENT_11, CHARSET_LETTER_CONTENT_12,
};
static const char* const CHARSET_LETTER_CONTENT_PALS[] = {
    CHARSET_LETTER_CONTENT_1_PAL,  CHARSET_LETTER_CONTENT_2_PAL,  CHARSET_LETTER_CONTENT_3_PAL,
    CHARSET_LETTER_CONTENT_4_PAL,  CHARSET_LETTER_CONTENT_5_PAL,  CHARSET_LETTER_CONTENT_6_PAL,
    CHARSET_LETTER_CONTENT_7_PAL,  CHARSET_LETTER_CONTENT_8_PAL,  CHARSET_LETTER_CONTENT_9_PAL,
    CHARSET_LETTER_CONTENT_10_PAL, CHARSET_LETTER_CONTENT_11_PAL, CHARSET_LETTER_CONTENT_12_PAL,
};
