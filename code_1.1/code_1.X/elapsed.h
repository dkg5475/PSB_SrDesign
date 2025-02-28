#include "definitions.h"
#include <stdint.h> 


/* ************************************************************************** */
/* Wrapper function prototypes
/* ************************************************************************** */
void startTimer                    (void);
void endTimer                      (void);
void TC3_Callback_InterruptHandler (TC_TIMER_STATUS status, uintptr_t context);

/* ************************************************************************** */
/* Define global structures
/* ************************************************************************** */
#ifndef ELAPSED_H
#define ELAPSED_H
    //!Define global structure for PID parameters
    struct timer_t
    {
        volatile uint16_t startTime;
        volatile uint16_t endTime;
        volatile uint16_t elapsedTime; 
    };
    
    extern struct timer_t timer;
#endif
    
/* *****************************************************************************
 End of File
 */
