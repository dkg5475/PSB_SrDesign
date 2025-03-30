#include "../Header/system.h"
#include "samc21e18a.h"
#include <stdint.h>

void osc32k_init (void) {
    /* Enable the 32.768 kHz oscillator */
    /* No additional configurations needed*/
    OSC32KCTRL_REGS->OSC32KCTRL_OSC32K |= OSC32KCTRL_OSC32K_ENABLE_Msk;
    
    /* Wait for the oscillator to be ready */
    while(!(OSC32KCTRL_REGS->OSC32KCTRL_STATUS & OSC32KCTRL_STATUS_OSC32KRDY_Msk ));
}

void gclk2_init (void) {
    /* Configure GCLK2 to be used within some peripherals */
    /* Set the division factor = 1UL */
    /* Set the source for the GCLK1 instance to be the 32.768 kHz oscillator */
    /* Enable the GCLK2 instance */
    GCLK_REGS->GCLK_GENCTRL[2] = GCLK_GENCTRL_DIV(1UL) | 
            GCLK_GENCTRL_SRC_OSC32K  |
            GCLK_GENCTRL_GENEN_Msk;
    
    /* Wait for the GCLK1 instance to be ready */
    while(!(GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL2_Msk));
}

void osc48m_init (void) {
    /* Use the factory calibration for the 48 MHz oscillator */
    int32_t calibValue = (uint32_t)(((*(uint64_t*)0x00806020UL) >> 19 ) & 0x3FFFFFUL);
    OSCCTRL_REGS->OSCCTRL_CAL48M = calibValue;
    
    /* Divide the clock by 1 (to achieve 48 MHz */
    OSCCTRL_REGS->OSCCTRL_OSC48MDIV |= OSCCTRL_OSC48MDIV_DIV_DIV1;
    
    /* Wait for the OSC48M to sync*/
    while(OSCCTRL_REGS->OSCCTRL_OSC48MSYNCBUSY & OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV_Msk);
    
    /* Wait for the OSC48M to be ready */
    while(OSCCTRL_REGS->OSCCTRL_OSC48MCTRL & OSCCTRL_STATUS_OSC48MRDY_Msk);
    
    /* Enable the 48 MHz oscillator */
    OSCCTRL_REGS->OSCCTRL_OSC48MCTRL |= OSCCTRL_OSC48MCTRL_ENABLE_Msk;
}

void gclk1_init (void) {
    /* Configure 48 MHz clock for the everything other than the CPU */
    /* Set the division factor = 1UL */
    /* Set the source for the GCLK1 instance to be the 48 MHz OSC */
    /* Enable the GCLK1 instance */
    GCLK_REGS->GCLK_GENCTRL[1] = GCLK_GENCTRL_DIV(1UL) | 
            GCLK_GENCTRL_SRC_OSC48M  |
            GCLK_GENCTRL_GENEN_Msk;
    
    /* Wait for the GCLK1 instance to be ready */
    while(!(GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL1_Msk));
}

void dpll_init (void) {
    /* Disable the DPLL via the CTRLA register before configuring */
    OSCCTRL_REGS->OSCCTRL_DPLLCTRLA = 0;
    
    /* Wait until the DPLL is fully disabled */
    while (OSCCTRL_REGS->OSCCTRL_DPLLSYNCBUSY & OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk);
    
    /* Set the reference for DPLL to be GCLK1 (OSC48M) */
    /* Set the DPLL to use the high damping filter */
    OSCCTRL_REGS->OSCCTRL_DPLLCTRLB |= OSCCTRL_DPLLCTRLB_REFCLK_GCLK | 
            OSCCTRL_DPLLCTRLB_FILTER_HDFILT;
    
    /* Set the multiplication factor */
    /* Since we are sourcing the 48 MHz oscillator, we need to multiply by 2 */
    /* A multiplication of 2 corresponds to an LDR of 1 and a fractional part of 0*/
    /* Prescaler value of 0 */
    OSCCTRL_REGS->OSCCTRL_DPLLRATIO |= OSCCTRL_DPLLRATIO_LDR(1UL) | 
            OSCCTRL_DPLLRATIO_LDRFRAC(0UL) |
            OSCCTRL_DPLLPRESC_PRESC(0UL);
    
    /* Re-enable the DPLL */
    OSCCTRL_REGS->OSCCTRL_DPLLCTRLA |= OSCCTRL_DPLLCTRLA_ENABLE_Msk;
    
    /* Wait for the DPLL to lock on*/
    while(!(OSCCTRL_REGS->OSCCTRL_DPLLSTATUS & OSCCTRL_DPLLSTATUS_LOCK_Msk));
    
    /* Wait for the DPLL clock to be ready */
    while(!(OSCCTRL_REGS->OSCCTRL_DPLLSTATUS & OSCCTRL_DPLLSTATUS_CLKRDY_Msk));
    
}

void gclk0_init (void) {
    /* Configure GCLK0 (Main clock) */
    /* Set the division factor = 1UL */
    /* Set the source for GCLK0 as the 96 MHz DPLL*/
    /* Enable the GCLK0 Instance */
    GCLK_REGS->GCLK_GENCTRL[0] = GCLK_GENCTRL_DIV(1UL) |
            GCLK_GENCTRL_SRC_DPLL96M  |
            GCLK_GENCTRL_GENEN_Msk;
    
    /* Wait for the GCLK0 instance to be ready*/
    while(!(GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL0_Msk));
 
    /* Wait for the CPU to run from GCLK0 */
    while(!((GCLK_REGS->GCLK_GENCTRL[0] & GCLK_GENCTRL_SRC_Msk) == GCLK_GENCTRL_SRC_DPLL96M_Val));
}

void mclk_init (void) {
    /* Configure the APBC Clock (peripheral bus clock) */
    /* Configure for SERCOM0 (UART) and SERCOM3 (SPI) */
    /* Configure for SDADC and DAC */
    /* Configure for the TC3 module*/
    MCLK_REGS->MCLK_APBCMASK |= MCLK_APBCMASK_SERCOM0_Msk |
            MCLK_APBCMASK_SERCOM3_Msk |
            MCLK_APBCMASK_SDADC_Msk |
            MCLK_APBCMASK_DAC_Msk |
            MCLK_APBCMASK_TC3_Msk;            
}

void peripheral_clk_init (void) {
    /* Enable SERCOM0 clock, where SERCOM0 corresponds to the USART instance  */
    /* Enable SERCOM3 clock, where SERCOM3 corresponds to the SPI instance */
    /* GCLK1 is set to 48 MHz */
    /* CHEN Msk enables the channel */
    
    /* Set SERCOM0 to run off GCLK1 */
    GCLK_REGS->GCLK_PCHCTRL[SERCOM0_GCLK_ID_CORE] = GCLK_PCHCTRL_GEN_GCLK1 | GCLK_PCHCTRL_CHEN_Msk;
    /* Set SERCOM3 to run off GCLK1 */
    GCLK_REGS->GCLK_PCHCTRL[SERCOM3_GCLK_ID_CORE] = GCLK_PCHCTRL_GEN_GCLK1 | GCLK_PCHCTRL_CHEN_Msk;
    /* Set SDADC to run off GCLK1 */
    GCLK_REGS->GCLK_PCHCTRL[SDADC_GCLK_ID] = GCLK_PCHCTRL_GEN_GCLK1 | GCLK_PCHCTRL_CHEN_Msk;
    /* Set DAC to run off GCLK1 */
    GCLK_REGS->GCLK_PCHCTRL[DAC_GCLK_ID] = GCLK_PCHCTRL_GEN_GCLK1 | GCLK_PCHCTRL_CHEN_Msk;
}

void clocks_init (void) {
    // osc32k_init();
    // gclk2_init();
    osc48m_init();
    gclk1_init();
    dpll_init();
    gclk0_init();
    mclk_init();
    peripheral_clk_init();
}



