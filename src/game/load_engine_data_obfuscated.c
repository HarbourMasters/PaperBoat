#include "common.h"

// N64 anti-tamper code removed — ROM hash verification doesn't work on the port.
void load_engine_data(void);
void load_engine_data_obfuscated(void) {
    load_engine_data();
}
