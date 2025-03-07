#include "definitions.h"
#include <stdint.h> 

/* Macros */
#define TIMER_FREQ 3000000U


/* Function prototypes */
void     startTimer                    (void);
void     endTimer                      (void);
float    calcElapsed                   (void);
void     TC3_Callback_InterruptHandler (TC_TIMER_STATUS status, uintptr_t context);

/* Global structures */
#ifndef DURATION_H
#define DURATION_H
    //!Define global structure timer variables
    struct timer_t
    {
        float elapsedSeconds;
        volatile uint16_t startTime;
        volatile uint16_t endTime;
        volatile uint16_t elapsedTime; 
    };
    
    
#endif
    
