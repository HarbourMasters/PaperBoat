#pragma once

#include "port/hooks/impl/EventSystem.h"
#include "common_structs.h"
#include "hud_element.h"
#include "audio/public.h"
#include <stdarg.h>

typedef enum VBehaviorID {
    VB_DUMMY
} VBehaviorID;

typedef enum WorkerDrawMode {
    WORKER_DRAW_MODE_SCENE,
    WORKER_DRAW_MODE_FRONT_UI,
    WORKER_DRAW_MODE_BACK_UI,
} WorkerDrawMode;

DEFINE_EVENT(GameFrameUpdate);

DEFINE_EVENT(WorkerUpdate,
    Worker* worker;
);

DEFINE_EVENT(WorkerDraw,
    Worker* worker;
    WorkerDrawMode mode;
);

DEFINE_EVENT(TriggerUpdate,
    Trigger* trigger;
);

DEFINE_EVENT(TriggerActivate,
    Trigger* trigger;
);

DEFINE_EVENT(ScriptRequestUpdate,
    Evt* script;
);

DEFINE_EVENT(ScriptFrameUpdate,
    Evt* script;
    int32_t* status;
);

DEFINE_EVENT(MessageUpdate,
    MessagePrintState* message;
);

DEFINE_EVENT(MessageDrawSetup,
    MessagePrintState* message;
);

DEFINE_EVENT(MessagePreDraw,
    MessagePrintState* message;
);

DEFINE_EVENT(MessagePostDraw,
    MessagePrintState* message;
);

DEFINE_EVENT(HudElementUpdate,
    HudElement* element;
    int32_t* result;
);

DEFINE_EVENT(HudElementPreDraw,
    HudElement* element;
    int16_t* texSizeX;
    int16_t* texSizeY;
    int16_t* drawSizeX;
    int16_t* drawSizeY;
    int16_t* offsetX;
    int16_t* offsetY;
    int32_t* clamp;
    int32_t* dropShadow;
);

DEFINE_EVENT(HudElementPostDraw,
    HudElement* element;
    int16_t texSizeX;
    int16_t texSizeY;
    int16_t drawSizeX;
    int16_t drawSizeY;
    int16_t offsetX;
    int16_t offsetY;
    int32_t clamp;
    int32_t dropShadow;
);

DEFINE_EVENT(EntityPreUpdate,
    Entity* entity;
);

DEFINE_EVENT(EntityPostUpdate,
    Entity* entity;
);

DEFINE_EVENT(EntityPreDraw,
    Entity* entity;
);

DEFINE_EVENT(EntityPostDraw,
    Entity* entity;
);

DEFINE_EVENT(ShadowPreUpdate,
    Shadow* shadow;
);

DEFINE_EVENT(ShadowPostUpdate,
    Shadow* shadow;
);

DEFINE_EVENT(ShadowPreDraw,
    Shadow* shadow;
);

DEFINE_EVENT(ShadowPostDraw,
    Shadow* shadow;
);

DEFINE_EVENT(MusicControlPreUpdate,
    MusicControlData* musicControl;
);

DEFINE_EVENT(MusicControlPostUpdate,
    MusicControlData* musicControl;
);

DEFINE_EVENT(MusicControlSetSong,
    MusicControlData* music;
    int32_t* songID;
    int32_t* variation;
    int32_t* fadeOutTime;
    int16_t* volume;
    int32_t* result;
);

DEFINE_EVENT(AmbientSoundPreUpdate,
    AmbientSoundSettings* settings;
);

DEFINE_EVENT(AmbientSoundPostUpdate,
    AmbientSoundSettings* settings;
);

DEFINE_EVENT(AmbientSoundPlay,
    AmbientSoundSettings* settings;
    int32_t* soundID;
    int32_t* fadeTime;
    int32_t* result;
);

DEFINE_EVENT(WindowUpdate,
    Window* window;
);

DEFINE_EVENT(WindowRootPreDraw);
DEFINE_EVENT(WindowRootPostDraw);

DEFINE_EVENT(WindowPreDraw,
    Window* window;
    int32_t* childWindowID;
);

DEFINE_EVENT(WindowPostDraw,
    Window* window;
    int32_t childWindowID;
);

DEFINE_EVENT(TheaterPreDraw);
DEFINE_EVENT(TheaterPostDraw);

DEFINE_EVENT(CurtainsPreDraw);
DEFINE_EVENT(CurtainsPostDraw);

DEFINE_EVENT(BackgroundPreDraw,
    int32_t bgRenderState;
);

DEFINE_EVENT(VanillaBehavior,
    VBehaviorID id;
    bool* should;
    va_list args;
);
