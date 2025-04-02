#include "../Header/system.h"
#include "../Header/analog.h"
#include "samc21e18a.h"
#include <stdint.h>
#include <stdbool.h>

#define SAMPLE_COUNT 64

volatile uint16_t sample_buffer[SAMPLE_COUNT] = {0};  // Buffer to store samples
volatile uint8_t sample_index = 0;  // Index for buffer
volatile bool bufferFullFlag = false;

void sdadc_init (void) {
    /* Reset the SDADC */
    SDADC_REGS->SDADC_CTRLA = (uint8_t)SDADC_CTRLA_SWRST_Msk;
    
    /* Wait for sync */
    while((SDADC_REGS->SDADC_SYNCBUSY & SDADC_SYNCBUSY_SWRST_Msk) == SDADC_SYNCBUSY_SWRST_Msk);
    
    /* Set prescaler (minimum 2) so SDADC clock is 24 MHz (runs off GCLK1 which is 48 MHz) */
    SDADC_REGS->SDADC_CTRLB = (uint16_t)(SDADC_CTRLB_PRESCALER_DIV2 | SDADC_CTRLB_OSR_OSR1024 | SDADC_CTRLB_SKPCNT(2UL));
    
    /* Configure reference voltage */
    SDADC_REGS->SDADC_REFCTRL = (uint8_t)SDADC_REFCTRL_REFSEL_AREFB;
    
    /* Configure sequence control register */
    /* Set PA05 as AIN[0] and PA06 as AIN[1] */
    SDADC_REGS->SDADC_SEQCTRL = SDADC_SEQCTRL_SEQEN(1UL << 0U) | 
            SDADC_SEQCTRL_SEQEN(1UL << 1U);
    
     /* Clear all interrupts */
    SDADC_REGS->SDADC_INTFLAG = (uint8_t)SDADC_INTFLAG_Msk;

    /* Enable the SDADC result ready interrupt */
    SDADC_REGS->SDADC_INTENSET = (uint8_t)(SDADC_INTENSET_RESRDY_Msk);
    
    /* Configure Run in standby, On demand property */
    SDADC_REGS->SDADC_CTRLA |= (uint8_t)(SDADC_CTRLA_RUNSTDBY_Msk | SDADC_CTRLA_ONDEMAND_Msk);

    /* Enable SDADC */
    SDADC_REGS->SDADC_CTRLA |= (uint8_t)SDADC_CTRLA_ENABLE_Msk;

    /* Wait for sync */
    while((SDADC_REGS->SDADC_SYNCBUSY) != 0U);
}

void sdadc_start (void) {
    /* Start conversion */
    SDADC_REGS->SDADC_SWTRIG = (uint8_t)SDADC_SWTRIG_START_Msk;

    /* Wait for synchronization between SWTRIG start with the clock domain */
    while((SDADC_REGS->SDADC_SYNCBUSY & SDADC_SYNCBUSY_SWTRIG_Msk) == SDADC_SYNCBUSY_SWTRIG_Msk);
}

void sdadc_stop (void) {
   // Disable the SDADC
   SDADC_REGS->SDADC_CTRLA &= (uint8_t)(~SDADC_CTRLA_ENABLE_Msk);
   // Wait for sync
   while((SDADC_REGS->SDADC_SYNCBUSY & SDADC_SYNCBUSY_ENABLE_Msk) == SDADC_SYNCBUSY_ENABLE_Msk);
}

void SDADC_Handler (void) {
    // Check if the interrupt is triggered by the Result Ready event
    if (SDADC_REGS->SDADC_INTFLAG & SDADC_INTFLAG_RESRDY_Msk) {
        // Store result in buffer 
        sample_buffer[sample_index] = SDADC_REGS->SDADC_RESULT;
        sample_index = (sample_index + 1) % SAMPLE_COUNT;
        
        // If buffer is full, signal that the average is ready
        if (sample_index >= SAMPLE_COUNT) {
            sample_index = 0;   // Reset index for next batch
            bufferFullFlag = true;  // buffer is full and sampling is done
        }

        // Clear the interrupt flag
        SDADC_REGS->SDADC_INTFLAG = SDADC_INTFLAG_RESRDY_Msk;
    }
}