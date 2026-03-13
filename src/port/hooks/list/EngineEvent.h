#pragma once

#include "port/hooks/impl/EventSystem.h"
#include <stdarg.h>

DEFINE_EVENT(GameFrameUpdate);

typedef enum VBehaviorID {
    VB_DUMMY
} VBehaviorID;

DEFINE_EVENT(VanillaBehavior,
    VBehaviorID id;
    bool* should;
    va_list args;
);