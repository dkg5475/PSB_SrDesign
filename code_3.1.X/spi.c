#include "spi.h"
#include "samc21e18a.h"


void spim_init (void) {
    // Disable the SPI before making any changes (enabled protected registers)
    SERCOM3_REGS->SPIM.SERCOM_CTRLA &= ~SERCOM_SPIM_CTRLA_ENABLE_Msk;
    
    // set character size, don't need receiver (write only slave device)
    SERCOM3_REGS->SPIM.SERCOM_CTRLB = SERCOM_SPIM_CTRLB_CHSIZE_8_BIT;
    
    // wait for sync after writing to CTRLB
    while((SERCOM3_REGS->SPIM.SERCOM_SYNCBUSY & SERCOM_SPIM_SYNCBUSY_CTRLB_Msk) == 0U); 
    
    // select the baud value 
    SERCOM3_REGS->SPIM.SERCOM_BAUD = (uint8_t)SERCOM_SPIM_BAUD_BAUD(SERCOM3_SPIM_BAUD_VALUE);
    
    SERCOM3_REGS->SPIM.SERCOM_INTENSET = SERCOM_SPIM_INTENSET_TXC_Msk | 
            SERCOM_SPIM_INTENSET_DRE_Msk;
    
    SERCOM3_REGS->SPIM.SERCOM_CTRLA = SERCOM_SPIM_CTRLA_MODE_SPI_MASTER | // set to master mode
            SERCOM_SPIM_CTRLA_DOPO_PAD0 | // set DOPO to PAD0 (PA16 SDIN)
            SERCOM_SPIM_CTRLA_CPOL(0x1UL) |  // clock is high when idle
            SERCOM_SPIM_CTRLA_CPHA(0x0UL) | // falling edge indicates the start of sampling, rising edge is change of states (on SYNC line))
            SERCOM_SPIM_CTRLA_DORD_MSB | // MSB is transmitted first
            SERCOM_SPIM_CTRLA_ENABLE_Msk | // enable the SPI master
            SERCOM_SPIM_CTRLA_RUNSTDBY_Msk; // run in standby mode
    
    // wait for sync after enabling
    while((SERCOM3_REGS->SPIM.SERCOM_SYNCBUSY & SERCOM_SPIM_SYNCBUSY_ENABLE_Msk) == 0U); 
}

void spim_tx_byte (uint8_t data) {
    // Wait for the data register empty (DRE) flag to be set (1))
    while((SERCOM3_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_DRE_Msk) == 0U);
    
    SERCOM3_REGS->SPIM.SERCOM_DATA = data;
    
    // wait for transmission to complete by checking the TXC flag (set when data is shifted out)
    while((SERCOM3_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_TXC_Msk) == 0U);
}
 
bool spim_busy (void) {
    return ((SERCOM3_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_TXC_Msk) == 0U)? true : false;
}

void spim_tx_24bit (uint32_t data) {
    spim_tx_byte((data >> 16) & 0xFF);
    spim_tx_byte((data >> 8) & 0xFF);
    spim_tx_byte(data & 0xFF);
}
