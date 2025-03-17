#ifndef DURATION_H
#define DURATION_H

#include "definitions.h"
#include <stdint.h> 

/* Macros */
#define TIMER_FREQ 3000000U

/* Function prototypes */
void     startTimer                    (void);
void     endTimer                      (void);
void     calcElapsed                   (void);
// void     TC3_Callback_InterruptHandler (TC_TIMER_STATUS status, uintptr_t context);

/* Global structures */
    //!Define global structure timer variables
    typedef struct
    {
        float elapsedSeconds;
        volatile uint16_t startTime;
        volatile uint16_t endTime;
        volatile uint16_t elapsedTime; 
    }duration_timer_t;
    
    extern duration_timer_t timer;
#endif
    
