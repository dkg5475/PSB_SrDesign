#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define TIMER_FREQ 3000000U

/* Function prototypes*/
void tc3_init            (void);
void tc3_start           (void);
void tc3_end             (void);
uint16_t tc3_get_counter (void);
float calc_elapsed        (uint16_t start, uint16_t end);


// Global structures
typedef struct
{
    float elapsedSeconds;
    uint16_t startTime;
    uint16_t endTime;
    uint16_t elapsedTime; 
}duration_timer_t;
    
extern duration_timer_t timer;

#endif