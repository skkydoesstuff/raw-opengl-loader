#include "core/window/time.h"

#include <windows.h>

void time_create(Time* time) {
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;

    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);

    time->frequency = freq.QuadPart;
    time->previous_counter = counter.QuadPart;

    time->delta_time = 0.0;
    time->total_time = 0.0;
}

void time_update(Time* time) {
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);

    time->delta_time =
        (double)(counter.QuadPart - time->previous_counter) /
        (double)time->frequency;

    time->total_time += time->delta_time;
    time->previous_counter = counter.QuadPart;
}