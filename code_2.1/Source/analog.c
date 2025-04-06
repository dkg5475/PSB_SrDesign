#include "../Header/system.h"
#include "../Header/analog.h"
#include "samc21e18a.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define SAMPLE_COUNT 64


volatile int16_t sample_buffer[SAMPLE_COUNT] = {0};  // Buffer to store samples
volatile uint8_t sample_index = 0;  // Index for buffer
volatile bool bufferFullFlag = false;

void sdadc_flush (void) {
    // Flush the SDADC pipeline
    SDADC_REGS->SDADC_SWTRIG = SDADC_SWTRIG_FLUSH_Msk;
    
    // Wait for synchronization between SWTRIG start with the clock domain 
    while((SDADC_REGS->SDADC_SYNCBUSY & SDADC_SYNCBUSY_SWTRIG_Msk) == SDADC_SYNCBUSY_SWTRIG_Msk);
}

void sdadc_init (void) {
    // software reset of sdadc before configurations (this also disables it))
    SDADC_REGS->SDADC_CTRLA = (uint8_t)SDADC_CTRLA_SWRST_Msk;
    
    // wait for the software reset to finish
    while((SDADC_REGS->SDADC_SYNCBUSY & SDADC_SYNCBUSY_SWRST_Msk) == SDADC_SYNCBUSY_SWRST_Msk);
    
    SDADC_REGS->SDADC_CTRLB = (uint16_t)(SDADC_CTRLB_PRESCALER_DIV4 | //set the prescaler to 2 (24 MHz))
            SDADC_CTRLB_OSR_OSR1024 |  // oversampling ratio of 1024 (best quality)
            SDADC_CTRLB_SKPCNT(2UL)); // ensure results are valid only after 2 conversions
    
    //use external reference on PA04
    SDADC_REGS->SDADC_REFCTRL = (uint8_t)(SDADC_REFCTRL_REFSEL_AREFB | SDADC_REFCTRL_ONREFBUF_Msk);
    
    // Select AIN0 
    SDADC_REGS->SDADC_INPUTCTRL = SDADC_INPUTCTRL_MUXSEL_AIN0; 
    
    SDADC_REGS->SDADC_SEQCTRL = SDADC_SEQCTRL_SEQEN(0UL); // disable sequencing
    
    // enable chopper at sdadc input
    SDADC_REGS->SDADC_ANACTRL = SDADC_ANACTRL_ONCHOP_Msk;
    
    // clear the window monitor, overrun, and result ready interrupts by writing a 1 to all bits
    SDADC_REGS->SDADC_INTFLAG = (uint8_t)SDADC_INTFLAG_Msk; 

    // enable the SDADC result ready interrupt 
    //SDADC_REGS->SDADC_INTENSET = (uint8_t)(SDADC_INTENSET_RESRDY_Msk);
    
    // Enable Free-Run Mode
    SDADC_REGS->SDADC_CTRLC = SDADC_CTRLC_FREERUN_Msk;
    
    // configure run in standby mode, On demand property 
    SDADC_REGS->SDADC_CTRLA |= (uint8_t)(SDADC_CTRLA_RUNSTDBY_Msk | SDADC_CTRLA_ONDEMAND_Msk);

    // enable sdadc after configurations
    SDADC_REGS->SDADC_CTRLA |= (uint8_t)SDADC_CTRLA_ENABLE_Msk;

    // wait for sync after enabling 
    while((SDADC_REGS->SDADC_SYNCBUSY) != 0U);
}

void sdadc_start (void) {
    sample_index = 0;
    bufferFullFlag = false;
    
    // Enable the SDADC
    SDADC_REGS->SDADC_CTRLA |= (uint8_t)(SDADC_CTRLA_ENABLE_Msk);
    
    // wait for sync after enabling 
    while((SDADC_REGS->SDADC_SYNCBUSY) != 0U);
     
    // Start conversion (if in freerun this needs to be done once)
    SDADC_REGS->SDADC_SWTRIG = (uint8_t)SDADC_SWTRIG_START_Msk;

    // Wait for synchronization between SWTRIG start with the clock domain 
    while((SDADC_REGS->SDADC_SYNCBUSY & SDADC_SYNCBUSY_SWTRIG_Msk) == SDADC_SYNCBUSY_SWTRIG_Msk);
    
    // enable result ready and overrun interrupt
    SDADC_REGS->SDADC_INTENSET = (uint8_t)(SDADC_INTENSET_RESRDY_Msk);
    SDADC_REGS->SDADC_INTENSET = (uint8_t)(SDADC_INTENSET_OVERRUN_Msk);
    
}

void sdadc_stop (void) {   
    sdadc_flush();
    
    // Disable the SDADC
   SDADC_REGS->SDADC_CTRLA &= (uint8_t)(~SDADC_CTRLA_ENABLE_Msk);
   
   // Wait for sync
   while((SDADC_REGS->SDADC_SYNCBUSY & SDADC_SYNCBUSY_ENABLE_Msk) == SDADC_SYNCBUSY_ENABLE_Msk);
}

void SDADC_Handler (void) {
    int32_t result = 0;
    
    if (SDADC_REGS->SDADC_INTFLAG & SDADC_INTFLAG_OVERRUN_Msk) {
        // Clear the interrupt flag
        SDADC_REGS->SDADC_INTFLAG = SDADC_INTFLAG_OVERRUN_Msk;
        sdadc_flush();
        return;
    }
    
    // Check if the interrupt is triggered by the Result Ready event
    if (SDADC_REGS->SDADC_INTFLAG & SDADC_INTFLAG_RESRDY_Msk) {
        // Clear the interrupt flag
        SDADC_REGS->SDADC_INTFLAG = SDADC_INTFLAG_RESRDY_Msk;
                
        // Store result in buffer 
        result = SDADC_REGS->SDADC_RESULT >> 8U;
        sample_buffer[sample_index] = (int16_t)result;
        sample_index++;
        
         // If buffer is full, signal that the average is ready
        if (sample_index == SAMPLE_COUNT) {
            sample_index = 0;   // Reset index for next batch
            bufferFullFlag = true;  // buffer is full and sampling is done
            
            SDADC_REGS->SDADC_INTENCLR = SDADC_INTENCLR_RESRDY_Msk;
        }
        
    }
}