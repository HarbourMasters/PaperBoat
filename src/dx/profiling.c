// Stolen from HackerSM64

#include "profiling.h"
#include "dx/utils.h"
#include "game_modes.h"
#include "PR/os_internal_reg.h"

#if USE_PROFILER

#define RDP_CYCLE_CONV(x) ((10 * (x)) / 625) // 62.5 million cycles per frame

ProfileTimeData all_profiling_data[PROFILER_TIME_COUNT];

int profile_buffer_index = -1;
int rsp_buffer_indices[PROFILER_RSP_COUNT];
// Holds either the start time if the task is running, or the amount of time the task has run for so far if yielded
u32 rsp_pending_times[PROFILER_RSP_COUNT];
u32 prev_start;
u32 cur_start;
u32 prev_time;
u32 gfx_start;
u32 gfx_buffer_index;
u32 audio_start;
u32 audio_buffer_index;
u32 preempted_time;
u32 collision_time = 0;

#ifdef GFX_PROFILING
u32 gfx_subset_starts[GFX_SUBSET_SIZE];
u32 gfx_subset_tallies[GFX_SUBSET_SIZE];
#endif
#ifdef AUDIO_PROFILING
u32 audio_subset_starts[AUDIO_SUBSET_SIZE];
u32 audio_subset_tallies[AUDIO_SUBSET_SIZE];
#endif

static void buffer_update(ProfileTimeData* data, u32 new, int buffer_index) {
    u32 old = data->counts[buffer_index];
    data->total -= old;
    data->total += new;
    data->counts[buffer_index] = new;
}

void profiler_update(enum ProfilerTime which, u32 delta) {
    u32 cur_time = osGetCount();
    u32 diff;
    ProfileTimeData* cur_data = &all_profiling_data[which];

    diff = cur_time - prev_time - delta;

    u32 saved = __osDisableInt();
    u32 cur_preempted_time = preempted_time;
    preempted_time = 0;
    __osRestoreInt(saved);
    if (cur_preempted_time > 0) {
        diff -= cur_preempted_time;
        cur_start += cur_preempted_time;
    }

    buffer_update(cur_data, diff, profile_buffer_index);
    prev_time = cur_time;
}

void profiler_rsp_started(enum ProfilerRSPTime which) {
    rsp_pending_times[which] = osGetCount();
}

void profiler_rsp_completed(enum ProfilerRSPTime which) {
    ProfileTimeData* cur_data = &all_profiling_data[PROFILER_TIME_RSP_GFX + which];
    int cur_index = rsp_buffer_indices[which];
    u32 time = osGetCount() - rsp_pending_times[which];
    rsp_pending_times[which] = 0;

    buffer_update(cur_data, time, cur_index);
    cur_index++;
    if (cur_index >= PROFILING_BUFFER_SIZE) {
        cur_index = 0;
    }
    rsp_buffer_indices[which] = cur_index;
}

void profiler_rsp_resumed() {
    rsp_pending_times[PROFILER_RSP_GFX] = osGetCount() - rsp_pending_times[PROFILER_RSP_GFX];
}

// This ends up being the same math as resumed, so we just use resumed for both
// void profiler_rsp_yielded() {
//     rsp_pending_times[PROFILER_RSP_GFX] = osGetCount() - rsp_pending_times[PROFILER_RSP_GFX];
// }

void profiler_gfx_started() {
    gfx_start = osGetCount();

#ifdef GFX_PROFILING
    for (s32 i = 0; i < GFX_SUBSET_SIZE; i++) {
        gfx_subset_tallies[i] = 0;
    }

    gfx_subset_starts[PROFILER_TIME_SUB_GFX_UPDATE - PROFILER_TIME_SUB_GFX_START] = gfx_start;
#endif
}

void profiler_audio_started() {
    audio_start = osGetCount();

#ifdef AUDIO_PROFILING
    for (s32 i = 0; i < AUDIO_SUBSET_SIZE; i++) {
        audio_subset_tallies[i] = 0;
    }

    audio_subset_starts[PROFILER_TIME_SUB_AUDIO_UPDATE - PROFILER_TIME_SUB_AUDIO_START] = audio_start;
#endif
}

#ifdef PUPPYPRINT_DEBUG

void profiler_collision_reset() {
    collision_time = 0;
}

void profiler_collision_update(u32 time) {
    collision_time += osGetCount() - time;
}

void profiler_collision_completed() {
    ProfileTimeData* cur_data = &all_profiling_data[PROFILER_TIME_COLLISION];
    buffer_update(cur_data, collision_time, profile_buffer_index);
}

#endif

u32 profiler_get_delta(enum ProfilerDeltaTime which) {
    if (which == PROFILER_DELTA_COLLISION) {
        return collision_time;
    } else {
        return 0;
    }
}

void profiler_gfx_completed() {
    ProfileTimeData* cur_data = &all_profiling_data[PROFILER_TIME_GFX];
    u32 time = osGetCount();
    u32 cur_index = gfx_buffer_index;

    preempted_time = time - gfx_start;
    buffer_update(cur_data, time - gfx_start, cur_index);

#ifdef GFX_PROFILING
    gfx_subset_tallies[PROFILER_TIME_SUB_GFX_UPDATE - PROFILER_TIME_SUB_GFX_START] += time - gfx_subset_starts[PROFILER_TIME_SUB_GFX_UPDATE - PROFILER_TIME_SUB_GFX_START];

    for (s32 i = 0; i < GFX_SUBSET_SIZE; i++) {
        cur_data = &all_profiling_data[i + PROFILER_TIME_SUB_GFX_START];
        buffer_update(cur_data, gfx_subset_tallies[i], cur_index);
    }
#endif

    cur_index++;
    if (cur_index >= PROFILING_BUFFER_SIZE) {
        cur_index = 0;
    }

    gfx_buffer_index = cur_index;
}


void profiler_audio_completed() {
    ProfileTimeData* cur_data = &all_profiling_data[PROFILER_TIME_AUDIO];
    u32 time = osGetCount();
    u32 cur_index = audio_buffer_index;

    preempted_time = time - audio_start;
    buffer_update(cur_data, time - audio_start, cur_index);

#ifdef AUDIO_PROFILING
    audio_subset_tallies[PROFILER_TIME_SUB_AUDIO_UPDATE - PROFILER_TIME_SUB_AUDIO_START] += time - audio_subset_starts[PROFILER_TIME_SUB_AUDIO_UPDATE - PROFILER_TIME_SUB_AUDIO_START];

    for (s32 i = 0; i < AUDIO_SUBSET_SIZE; i++) {
        cur_data = &all_profiling_data[i + PROFILER_TIME_SUB_AUDIO_START];
        buffer_update(cur_data, audio_subset_tallies[i], cur_index);
    }
#endif

    cur_index++;
    if (cur_index >= PROFILING_BUFFER_SIZE) {
        cur_index = 0;
    }

    audio_buffer_index = cur_index;
}

static void update_fps_timer() {
    u32 diff = cur_start - prev_start;

    buffer_update(&all_profiling_data[PROFILER_TIME_FPS], diff, profile_buffer_index);
    prev_start = cur_start;
}

static void update_total_timer() {
    u32 saved = __osDisableInt();
    u32 cur_preempted_time = preempted_time;
    preempted_time = 0;
    __osRestoreInt(saved);

    prev_time = cur_start + cur_preempted_time;
    profiler_update(PROFILER_TIME_TOTAL, PROFILER_TIME_PUPPYPRINT1 + PROFILER_DELTA_PUPPYPRINT2);
}

#ifdef PUPPYPRINT_DEBUG
extern u8 sPPDebugPage;
extern u8 fDebug;
#endif

static void update_rdp_timers() {
    u32 tmem = IO_READ(DPC_TMEM_REG);
    u32 cmd =  IO_READ(DPC_BUFBUSY_REG);
    u32 pipe = IO_READ(DPC_PIPEBUSY_REG);

    if (gGameStatus.frameCounter > 5) {
        IO_WRITE(DPC_STATUS_REG, (DPC_CLR_CLOCK_CTR | DPC_CLR_CMD_CTR | DPC_CLR_PIPE_CTR | DPC_CLR_TMEM_CTR));
    }

    buffer_update(&all_profiling_data[PROFILER_TIME_TMEM], tmem, profile_buffer_index);
    buffer_update(&all_profiling_data[PROFILER_TIME_CMD], cmd, profile_buffer_index);
    buffer_update(&all_profiling_data[PROFILER_TIME_PIPE], pipe, profile_buffer_index);
}

float profiler_get_fps() {
    return (1000000.0f * PROFILING_BUFFER_SIZE) / (OS_CYCLES_TO_USEC(all_profiling_data[PROFILER_TIME_FPS].total));
}

u32 profiler_get_cpu_cycles() {
    u32 cpu_normal_time = all_profiling_data[PROFILER_TIME_TOTAL].total / PROFILING_BUFFER_SIZE;
    u32 cpu_audio_time = all_profiling_data[PROFILER_TIME_AUDIO].total / PROFILING_BUFFER_SIZE;
    return cpu_normal_time + cpu_audio_time * 2;
}

u32 profiler_get_rsp_cycles() {
    u32 rsp_graphics_time = all_profiling_data[PROFILER_TIME_RSP_GFX].total / PROFILING_BUFFER_SIZE;
    u32 rsp_audio_time = all_profiling_data[PROFILER_TIME_RSP_AUDIO].total / PROFILING_BUFFER_SIZE;
    return rsp_graphics_time + rsp_audio_time;
}

u32 profiler_get_rdp_cycles() {
    u32 rdp_pipe_cycles = all_profiling_data[PROFILER_TIME_PIPE].total;
    u32 rdp_tmem_cycles = all_profiling_data[PROFILER_TIME_TMEM].total;
    u32 rdp_cmd_cycles = all_profiling_data[PROFILER_TIME_CMD].total;

    u32 rdp_max_cycles = MAX(MAX(rdp_pipe_cycles, rdp_tmem_cycles), rdp_cmd_cycles);

    return rdp_max_cycles / PROFILING_BUFFER_SIZE;
}

u32 profiler_get_cpu_microseconds() {
    u32 cpu_normal_time = OS_CYCLES_TO_USEC(all_profiling_data[PROFILER_TIME_TOTAL].total / PROFILING_BUFFER_SIZE);
    u32 cpu_audio_time = OS_CYCLES_TO_USEC(all_profiling_data[PROFILER_TIME_AUDIO].total / PROFILING_BUFFER_SIZE);
    return cpu_normal_time + cpu_audio_time * 2;
}

u32 profiler_get_rsp_microseconds() {
    u32 rsp_graphics_time = OS_CYCLES_TO_USEC(all_profiling_data[PROFILER_TIME_RSP_GFX].total / PROFILING_BUFFER_SIZE);
    u32 rsp_audio_time = OS_CYCLES_TO_USEC(all_profiling_data[PROFILER_TIME_RSP_AUDIO].total / PROFILING_BUFFER_SIZE);
    return rsp_graphics_time + rsp_audio_time;
}

u32 profiler_get_rdp_microseconds() {
    u32 rdp_pipe_cycles = all_profiling_data[PROFILER_TIME_PIPE].total;
    u32 rdp_tmem_cycles = all_profiling_data[PROFILER_TIME_TMEM].total;
    u32 rdp_cmd_cycles = all_profiling_data[PROFILER_TIME_CMD].total;

    u32 rdp_max_cycles = MAX(MAX(rdp_pipe_cycles, rdp_tmem_cycles), rdp_cmd_cycles);

    return RDP_CYCLE_CONV(rdp_max_cycles / PROFILING_BUFFER_SIZE);
}

void profiler_print_times() {
    u32 microseconds[PROFILER_TIME_COUNT];
    char text_buffer_labels[196];
    char text_buffer_time[196];

    update_fps_timer();
    update_total_timer();
    update_rdp_timers();

#ifndef PUPPYPRINT_DEBUG
    static u8 show_profiler = 0;
    if ((gPlayerStatus.pressedButtons & (L_TRIG | U_JPAD)) && (gPlayerStatus.curButtons & L_TRIG) && (gPlayerStatus.curButtons & U_JPAD)) {
        show_profiler ^= 1;
    }
#endif

#ifdef PUPPYPRINT_DEBUG
    if (fDebug && sPPDebugPage == PUPPYPRINT_PAGE_PROFILER) {
#else
    if (show_profiler) {
#endif
        for (int i = 0; i < PROFILER_TIME_COUNT; i++) {
            if (i < PROFILER_TIME_TMEM) {
                microseconds[i] = OS_CYCLES_TO_USEC(all_profiling_data[i].total / PROFILING_BUFFER_SIZE);
            } else {
                microseconds[i] = RDP_CYCLE_CONV(all_profiling_data[i].total / PROFILING_BUFFER_SIZE);
            }
        }

        // audio time is removed from the main thread profiling, so add it back here
        u32 total_cpu = microseconds[PROFILER_TIME_TOTAL] + microseconds[PROFILER_TIME_AUDIO] * 2;
#ifndef GFX_PROFILING
        u32 total_rsp = microseconds[PROFILER_TIME_RSP_GFX] + microseconds[PROFILER_TIME_RSP_AUDIO] * 2;
        u32 max_rdp  = MAX(MAX(microseconds[PROFILER_TIME_TMEM], microseconds[PROFILER_TIME_CMD]), microseconds[PROFILER_TIME_PIPE]);
#endif

        s32 text_buffer_labels_len = sprintf(
            text_buffer_labels,
            "    " // space for prepend
            "FPS: %5.2f\n"
            "CPU\t\t%lu (%lu%%)\n"
            " Input\n"
            " Workers\n"
            " Triggers\n"
            " EVT\n"
            " Messages\n"
            " HUD elements\n"
            " Entities\n"
            " Gfx\n"
            " Audio\n",
            1000000.0f / microseconds[PROFILER_TIME_FPS],
            total_cpu, total_cpu / 333
        );
        s32 text_buffer_time_len = sprintf(
            text_buffer_time,
            "    " // space for prepend
            "\n"
            "\n"
            "%lu\n"
            "%lu\n"
            "%lu\n"
            "%lu\n"
            "%lu\n"
            "%lu\n"
            "%lu\n"
            "%lu\n"
            "%lu\n",
            microseconds[PROFILER_TIME_CONTROLLERS],
            microseconds[PROFILER_TIME_WORKERS],
            microseconds[PROFILER_TIME_TRIGGERS],
            microseconds[PROFILER_TIME_EVT],
            microseconds[PROFILER_TIME_MESSAGES],
            microseconds[PROFILER_TIME_HUD_ELEMENTS],
            microseconds[PROFILER_TIME_ENTITIES],
            microseconds[PROFILER_TIME_GFX],
            microseconds[PROFILER_TIME_AUDIO] * 2 // audio is 60Hz, so double the average
        );

        switch (get_game_mode()) {
            case GAME_MODE_WORLD:
                sprintf(&text_buffer_labels[text_buffer_labels_len],
                    " Encounters\n"
                    " NPCs\n"
                    " Player\n"
                    " Item entities\n"
                    " Effects\n"
                    " Cameras\n"
                );
                sprintf(&text_buffer_time[text_buffer_time_len],
                    "%lu\n"
                    "%lu\n"
                    "%lu\n"
                    "%lu\n"
                    "%lu\n"
                    "%lu\n",
                    microseconds[PROFILE_TIME_WORLD_ENCOUNTERS],
                    microseconds[PROFILE_TIME_WORLD_NPCS],
                    microseconds[PROFILE_TIME_WORLD_PLAYER],
                    microseconds[PROFILE_TIME_WORLD_ITEM_ENTITIES],
                    microseconds[PROFILE_TIME_WORLD_EFFECTS],
                    microseconds[PROFILE_TIME_WORLD_CAMERAS]
                );
                break;
            default:
                sprintf(&text_buffer_labels[text_buffer_labels_len],
                    " Game mode step\n"
                );
                sprintf(&text_buffer_time[text_buffer_time_len],
                    "%lu\n",
                    microseconds[PROFILER_TIME_STEP_GAME_MODE]
                );
                break;
        }

        dx_string_to_msg((u8*)&text_buffer_labels, (u8*)&text_buffer_labels);
        dx_string_to_msg((u8*)&text_buffer_time, (u8*)&text_buffer_time);
        text_buffer_labels[0] = text_buffer_time[0] = MSG_CHAR_READ_FUNCTION;
        text_buffer_labels[1] = text_buffer_time[1] = MSG_READ_FUNC_SIZE;
        text_buffer_labels[2] = text_buffer_time[2] = 14;
        text_buffer_labels[3] = text_buffer_time[3] = 14;
        draw_msg((intptr_t)&text_buffer_labels, 3, 0, 255, 0, 0);
        draw_msg((intptr_t)&text_buffer_time, 110, 0, 255, 0, 0);

#ifdef GFX_PROFILING
        s32 time_offset = 100;
        sprintf(
            text_buffer_labels,
            "    " // space for prepend
            "\n"
            "Gfx breakdown\n"
            " Entities\n"
            " Models\n"
            " Player\n"
            " Workers\n"
            " NPCs\n"
            " Effects\n"
            " Render tasks\n"
            " Hud elements\n"
            " Back UI\n"
            " Front UI\n"
        );
        sprintf(
            text_buffer_time,
            "    " // space for prepend
            "\n"
            "\n"
            "%lu\n"
            "%lu\n"
            "%lu\n"
            "%lu\n"
            "%lu\n"
            "%lu\n"
            "%lu\n"
            "%lu\n"
            "%lu\n"
            "%lu\n",
            microseconds[PROFILER_TIME_SUB_GFX_ENTITIES],
            microseconds[PROFILER_TIME_SUB_GFX_MODELS],
            microseconds[PROFILER_TIME_SUB_GFX_PLAYER],
            microseconds[PROFILER_TIME_SUB_GFX_WORKERS],
            microseconds[PROFILER_TIME_SUB_GFX_NPCS],
            microseconds[PROFILER_TIME_SUB_GFX_EFFECTS],
            microseconds[PROFILER_TIME_SUB_GFX_RENDER_TASKS],
            microseconds[PROFILER_TIME_SUB_GFX_HUD_ELEMENTS],
            microseconds[PROFILER_TIME_SUB_GFX_BACK_UI],
            microseconds[PROFILER_TIME_SUB_GFX_FRONT_UI]
        );
#else
        s32 time_offset = 50;
        sprintf(text_buffer_labels,
            "    " // space for prepend
            "\n"
            "RDP\t\t\t%lu (%lu%%)\n"
            " Tmem\n"
            " Cmd\n"
            " Pipe\n"
            "\n"
            "RSP\t\t%lu (%lu%%)\n"
            " Gfx\n"
            " Audio\n",
            max_rdp, max_rdp / 333,
            total_rsp, total_rsp / 333
        );
        sprintf(text_buffer_time,
            "    " // space for prepend
            "\n"
            "\n"
            "%lu\n"
            "%lu\n"
            "%lu\n"
            "\n"
            "\n"
            "%lu\n"
            "%lu\n",
            microseconds[PROFILER_TIME_TMEM],
            microseconds[PROFILER_TIME_CMD],
            microseconds[PROFILER_TIME_PIPE],
            microseconds[PROFILER_TIME_RSP_GFX],
            microseconds[PROFILER_TIME_RSP_AUDIO] * 2
        );
#endif
        dx_string_to_msg((u8*)&text_buffer_labels, (u8*)&text_buffer_labels);
        dx_string_to_msg((u8*)&text_buffer_time, (u8*)&text_buffer_time);
        text_buffer_labels[0] = text_buffer_time[0] = MSG_CHAR_READ_FUNCTION;
        text_buffer_labels[1] = text_buffer_time[1] = MSG_READ_FUNC_SIZE;
        text_buffer_labels[2] = text_buffer_time[2] = 14;
        text_buffer_labels[3] = text_buffer_time[3] = 14;
        draw_msg((intptr_t)&text_buffer_labels, SCREEN_WIDTH/2, 0, 255, 0, 0);
        draw_msg((intptr_t)&text_buffer_time, SCREEN_WIDTH/2 + time_offset, 0, 255, 0, 0);
    }
}

void profiler_frame_setup() {
    profile_buffer_index++;
    preempted_time = 0;

    if (profile_buffer_index >= PROFILING_BUFFER_SIZE) {
        profile_buffer_index = 0;
    }

    prev_time = cur_start = osGetCount();
}

#endif
