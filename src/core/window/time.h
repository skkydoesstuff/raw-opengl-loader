#pragma once

typedef struct {
  double delta_time;
  double total_time;

  long long frequency;
  long long previous_counter;
} Time;

void time_create(Time* time);
void time_update(Time* time);