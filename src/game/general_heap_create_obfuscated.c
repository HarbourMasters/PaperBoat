#include "common.h"

// N64 anti-tamper code removed — ROM hash verification doesn't work on the port.
// The original computed general_heap_create's address from ROM hashes and only called
// it if the address was in KSEG0 (0x8XXXXXXX). On the port, just call it directly.
void general_heap_create_obfuscated(void) {
    general_heap_create();
}
