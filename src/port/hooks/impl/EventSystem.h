#pragma once

#include <ship/events/EventTypes.h>
#include <libultraship/bridge/eventsbridge.h>

// Backwards-compatible alias for dx
typedef EventPriority PortEventPriority;

#define CALL_CANCELLABLE_EVENT_INV(eventType, ...) \
    eventType eventType##_ = { {false}, __VA_ARGS__ }; \
    EventSystemCallEvent(eventType##ID, &eventType##_, __FILE__, __LINE__, FILE_AND_LINE); \
    if (eventType##_.Event.Cancelled)

#define CALL_CANCELLABLE_CONTINUE_EVENT(eventType, ...) \
    eventType eventType##_ = { {false}, __VA_ARGS__ }; \
    EventSystemCallEvent(eventType##ID, &eventType##_, __FILE__, __LINE__, FILE_AND_LINE); \
    if (eventType##_.Event.Cancelled) { \
        continue; \
    }

#define REGISTER_VB_SHOULD(flag, body)                                              \
    REGISTER_LISTENER(VanillaBehavior, EVENT_PRIORITY_NORMAL, [](IEvent* event) {   \
        VanillaBehavior* ev = (VanillaBehavior*)event;                              \
        va_list args;                                                               \
        va_start(args, ev->args);                                                   \
        body;                                                                       \
        va_end(args);                                                               \
    });

#define COND_VB_SHOULD(id, condition, body)           \
    {                                                 \
        static ListenerID hookId = 0;                 \
        UNREGISTER_LISTENER(VanillaBehavior, hookId); \
        hookId = 0;                                   \
        if (condition) {                              \
            hookId = REGISTER_VB_SHOULD(id, body);    \
        }                                             \
    }
