#include "../Header/spi.h"
#include "samc21e18a.h"
#include <stdint.h>

void spi_init (void) {
    // Disable the SPI before making any changes (enabled protected registers)
    SERCOM3_REGS->SPIM.SERCOM_CTRLA &= ~SERCOM_SPIM_CTRLA_ENABLE_Msk;
    
    // set character size and enable the receiver
    SERCOM3_REGS->SPIM.SERCOM_CTRLB = SERCOM_SPIM_CTRLB_CHSIZE_8_BIT | 
            SERCOM_SPIM_CTRLB_RXEN_Msk;
    
    while((SERCOM3_REGS->SPIM.SERCOM_SYNCBUSY) != 0U); // wait for sync
    
    // select the baud value 
    SERCOM3_REGS->SPIM.SERCOM_BAUD = (uint8_t)SERCOM_SPIM_BAUD_BAUD(SERCOM3_SPIM_BAUD_VALUE);
    
    SERCOM3_REGS->SPIM.SERCOM_CTRLA = SERCOM_SPIM_CTRLA_MODE_SPI_MASTER | // set to master mode
            SERCOM_SPIM_CTRLA_DOPO_PAD0 | // set DOPO and DIPO to PAD0 (half duplex)
            SERCOM_SPIM_CTRLA_DIPO_PAD0 | 
            SERCOM_SPIM_CTRLA_CPOL_IDLE_LOW |  // clock is low when idle
            SERCOM_SPIM_CTRLA_CPHA_LEADING_EDGE | // leading edge is rising, sample, trailing edge falling, change
            SERCOM_SPIM_CTRLA_DORD_MSB | // MSB is transmitted first
            SERCOM_SPIM_CTRLA_ENABLE_Msk | // enable the SPI master
            SERCOM_SPIM_CTRLA_RUNSTDBY_Msk; // run in standby mode
    
    
}