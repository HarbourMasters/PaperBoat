#include "port/Engine.h"
#include "port/ui/cvar_prefixes.h"

#include <cstdio>
#include <cstring>

extern "C" {
#include "common.h"
#include "port/patches/Patches.h"
}

// Messages for the non-English PAL languages ship in their own o2r, extracted
// from a PAL ROM into messages_de/, messages_fr/ and messages_es/. English
// stays in messages/, from the base pm64.o2r.

extern "C" {

#define MSG_PATH_PREFIX "__OTR__messages"

static const char* sLangSuffix[] = {
    [LANGUAGE_EN] = "",
    [LANGUAGE_DE] = "_de",
    [LANGUAGE_FR] = "_fr",
    [LANGUAGE_ES] = "_es",
};

s32 port_msg_language(void) {
    s32 language = CVarGetInteger(CVAR_SETTING("Language"), LANGUAGE_EN);

    if (language < 0 || language >= (s32) ARRAY_COUNT(sLangSuffix)) {
        return LANGUAGE_EN;
    }
    return language;
}

u8* port_msg_localized_asset(const char* basePath) {
    static char path[128];
    s32 language;
    const char* name;
    u8* data;

    if (basePath == NULL) {
        return NULL;
    }

    language = port_msg_language();
    if (language == LANGUAGE_EN) {
        return (u8*) LOAD_ASSET_RAW(basePath);
    }

    if (strncmp(basePath, MSG_PATH_PREFIX "/", sizeof(MSG_PATH_PREFIX)) != 0) {
        return (u8*) LOAD_ASSET_RAW(basePath);
    }
    name = basePath + sizeof(MSG_PATH_PREFIX); // past the '/'

    snprintf(path, sizeof(path), MSG_PATH_PREFIX "%s/%s", sLangSuffix[language], name);

    // Fall back to English whenever the translated message is absent
    data = (u8*) LOAD_ASSET_RAW(path);
    if (data == NULL) {
        data = (u8*) LOAD_ASSET_RAW(basePath);
    }
    return data;
}
}
