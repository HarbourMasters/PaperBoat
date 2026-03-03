#ifndef _EVT_MSG_API_H_
#define _EVT_MSG_API_H_

#include "script_api/macros.h"

#define SpeakToPlayer(...) \
    EVT_CMD(EVT_OP_CALL, evt_SpeakToPlayer, ##__VA_ARGS__),
API_CALLABLE(evt_SpeakToPlayer);

#define EndSpeech(...) \
    EVT_CMD(EVT_OP_CALL, evt_EndSpeech, ##__VA_ARGS__),
API_CALLABLE(evt_EndSpeech);

#define ContinueSpeech(...) \
    EVT_CMD(EVT_OP_CALL, evt_ContinueSpeech, ##__VA_ARGS__),
API_CALLABLE(evt_ContinueSpeech);

#define SpeakToNpc(...) \
    EVT_CMD(EVT_OP_CALL, evt_SpeakToNpc, ##__VA_ARGS__),
API_CALLABLE(evt_SpeakToNpc);

#endif
