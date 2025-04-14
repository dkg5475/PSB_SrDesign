#include "dac.h"
#include "samc21e18a.h"

#define DAC_DATA_MSB_MASK                    (0x03FFFU)

void dac_init (void) {
    // software reset of dac (also disables the device))
    DAC_REGS->DAC_CTRLA = DAC_CTRLA_SWRST_Msk;
    
    // Wait for software reset to finish 
    while((DAC_REGS->DAC_SYNCBUSY & DAC_SYNCBUSY_SWRST_Msk) == DAC_SYNCBUSY_SWRST_Msk);
    
    // set reference voltage and enable external output bit (EOEN)
    DAC_REGS->DAC_CTRLB = (uint8_t)(DAC_CTRLB_REFSEL_VREFP |  
            DAC_CTRLB_EOEN_Msk | DAC_CTRLB_DITHER(1) | DAC_CTRLB_LEFTADJ(0));
    
    // If using dithering, we start conversion event input
    DAC_REGS->DAC_EVCTRL = DAC_EVCTRL_STARTEI_Msk;
    
    //Initialize the data register
    DAC_REGS->DAC_DATA = 0U;
    
    // Wait for sync
    while((DAC_REGS->DAC_SYNCBUSY & DAC_SYNCBUSY_ENABLE_Msk) == DAC_SYNCBUSY_ENABLE_Msk);
    
    // Enable DAC 
    DAC_REGS->DAC_CTRLA =(uint8_t)(DAC_CTRLA_ENABLE_Msk | DAC_CTRLA_RUNSTDBY_Msk);	
    
    // Wait for sync
    while((DAC_REGS->DAC_SYNCBUSY & DAC_SYNCBUSY_ENABLE_Msk) == DAC_SYNCBUSY_ENABLE_Msk);
            
}

void dac_write (uint16_t data) {
    // Write to the data register [9:0]
    uint16_t dac_data = data;
    
    DAC_REGS->DAC_DATA = (uint16_t)(DAC_DATA_MSB_MASK & DAC_DATA_DATA((uint32_t)dac_data));
    
    // wait for sync 
    while((DAC_REGS->DAC_SYNCBUSY & DAC_SYNCBUSY_DATA_Msk) == DAC_SYNCBUSY_DATA_Msk);
}

bool dac_isReady (void) {
    return ((DAC_REGS->DAC_STATUS & DAC_STATUS_READY_Msk) == DAC_STATUS_READY_Msk);
}
