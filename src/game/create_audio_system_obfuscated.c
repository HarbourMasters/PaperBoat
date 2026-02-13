#include "common.h"

// N64 anti-tamper code removed — ROM hash verification doesn't work on the port.
void create_audio_system(void);
void create_audio_system_obfuscated(void) {
    create_audio_system();
}
