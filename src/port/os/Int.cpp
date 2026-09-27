#include <mutex>

extern "C" {
#include "libultraship/libultra/types.h"
#include "libultraship/libultra/exception.h"
}

namespace {
std::recursive_mutex sIntLock;
thread_local int sMaskDepth = 0;
} // namespace

extern "C" OSIntMask osSetIntMask(OSIntMask mask) {
    if (mask == OS_IM_NONE) {
        sIntLock.lock();
        sMaskDepth++;
    } else if (sMaskDepth > 0) {
        sMaskDepth--;
        sIntLock.unlock();
    }
    return 0;
}
