#include "../Header/timer.h"
#include <stdint.h>
#include "samc21e18a.h"

void tc3_init (void) {
    // software reset of TC
    TC3_REGS->COUNT16.TC_CTRLA = TC_CTRLA_SWRST_Msk;
    
    // wait for sync afte software reset
    while((TC3_REGS->COUNT16.TC_SYNCBUSY & TC_SYNCBUSY_SWRST_Msk) == TC_SYNCBUSY_SWRST_Msk);
    
    // counter resolution of 16 bits and clock division of 16 (3 MHz clock)
    TC3_REGS->COUNT16.TC_CTRLA = TC_CTRLA_MODE_COUNT16 | 
            TC_CTRLA_PRESCALER_DIV16;
    
    // clear all interrupt flags 
    TC3_REGS->COUNT16.TC_INTFLAG = (uint8_t)TC_INTFLAG_Msk;
    
    // Wait for sync 
    while((TC3_REGS->COUNT16.TC_SYNCBUSY) != 0U);
}

void tc3_start (void) {
    // Enable the TC3 module
    TC3_REGS->COUNT16.TC_CTRLA |= TC_CTRLA_ENABLE_Msk;
    
    // Wait for sync after enabling the TC
    while((TC3_REGS->COUNT16.TC_SYNCBUSY & TC_SYNCBUSY_ENABLE_Msk) == TC_SYNCBUSY_ENABLE_Msk);
}

void tc3_end (void) {
    // Disable the TC3 module
    TC3_REGS->COUNT16.TC_CTRLA &= ~TC_CTRLA_ENABLE_Msk;
    
    // Wait for sync after disabling
    while((TC3_REGS->COUNT16.TC_SYNCBUSY & TC_SYNCBUSY_ENABLE_Msk) == TC_SYNCBUSY_ENABLE_Msk);
}

uint16_t tc3_counter_get (void) {
    // Write command to force COUNT register read synchronization 
    TC3_REGS->COUNT16.TC_CTRLBSET |= (uint8_t)TC_CTRLBSET_CMD_READSYNC;
    
    /* Wait for sync */
    while((TC3_REGS->COUNT16.TC_SYNCBUSY & TC_SYNCBUSY_CTRLB_Msk) == TC_SYNCBUSY_CTRLB_Msk); 

    // Wait for CMD to equal 0
    while((TC3_REGS->COUNT16.TC_CTRLBSET & TC_CTRLBSET_CMD_Msk) != 0U);

    /* Read the current counter value */
    return (uint16_t)TC3_REGS->COUNT16.TC_COUNT;
}

float calc_elapsed (uint16_t start, uint16_t end){
    uint16_t elapsedTime;
    
    if (end >= start) {
        elapsedTime = end - start;
    }
    else { // To handle overflow 
        elapsedTime = (uint16_t)((65535 - start) + end + 1 );
    }
    
    float elapsedSeconds = (float)(elapsedTime) / (float)(TIMER_FREQ);
    float elapsedMs = elapsedSeconds * 1000;
    
    return elapsedMs;

}