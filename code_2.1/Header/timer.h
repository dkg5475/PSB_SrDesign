#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define TIMER_FREQ 3000000U // timer runs at 3 MHz

/* Function prototypes*/
void tc3_init                 (void);
void tc3_start                (void);
void tc3_end                  (void);
uint16_t tc3_counter_get      (void);
float calc_elapsed            (uint16_t start, uint16_t end);


// Global structures

#endif