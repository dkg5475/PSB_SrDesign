#include "../Header/system.h"
#include "samc21e18a.h"
#include <stdint.h>

void osc48m_init(void) {
    /* Disable the 48 MHz oscillator before configuring */
    OSCCTRL_REGS->OSCCTRL_OSC48MCTRL &= ~OSCCTRL_OSC48MCTRL_ENABLE_Msk;

    /* Use the factory calibration for the 48 MHz oscillator */
    uint32_t calibValue = (uint32_t)(((*(uint64_t*)0x00806020UL) >> 19) & 0x3FFFFF);
    OSCCTRL_REGS->OSCCTRL_CAL48M = calibValue;

    /* Set the oscillator divider to 1 (48 MHz output) */
    OSCCTRL_REGS->OSCCTRL_OSC48MDIV = OSCCTRL_OSC48MDIV_DIV_DIV1;

    /* Wait for the divider to synchronize */
    while (OSCCTRL_REGS->OSCCTRL_OSC48MSYNCBUSY & OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV_Msk);

    /* Enable the 48 MHz oscillator */
    OSCCTRL_REGS->OSCCTRL_OSC48MCTRL |= OSCCTRL_OSC48MCTRL_ENABLE_Msk;

    /* Wait for the OSC48M to be ready */
    while (!(OSCCTRL_REGS->OSCCTRL_STATUS & OSCCTRL_STATUS_OSC48MRDY_Msk));
}


void gclk0_init (void) {
    /* Configure GCLK0 (Main clock) */
    /* Set the division factor = 1UL */
    /* Enable the GCLK0 Instance */
    GCLK_REGS->GCLK_GENCTRL[0] = GCLK_GENCTRL_DIV(1UL) |
            GCLK_GENCTRL_SRC_OSC48M  |
            GCLK_GENCTRL_GENEN_Msk;
    
    /* Wait for the GCLK0 instance to be ready*/
    while(!(GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL0_Msk));
 
    /* Wait for the CPU to run from GCLK0 */
    while(!((GCLK_REGS->GCLK_GENCTRL[0] & GCLK_GENCTRL_SRC_Msk) == GCLK_GENCTRL_SRC_DPLL96M_Val));
}

void gclk1_init (void) {
    /* Configure GCLK1 for other uses */
    GCLK_REGS->GCLK_GENCTRL[1] = GCLK_GENCTRL_DIV(1UL) | 
            GCLK_GENCTRL_SRC_OSC48M  |
            GCLK_GENCTRL_GENEN_Msk;
    
    /* Wait for the GCLK1 instance to be ready */
    while(!(GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL1_Msk));
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
    /* GCLK0 is set to 48 MHz */
    /* CHEN Msk enables the channel */
    
    /* Set SERCOM0 to run off GCLK0 */
    GCLK_REGS->GCLK_PCHCTRL[SERCOM0_GCLK_ID_CORE] = GCLK_PCHCTRL_GEN_GCLK0 | GCLK_PCHCTRL_CHEN_Msk;
    /* Set SERCOM3 to run off GCLK0 */
    GCLK_REGS->GCLK_PCHCTRL[SERCOM3_GCLK_ID_CORE] = GCLK_PCHCTRL_GEN_GCLK0 | GCLK_PCHCTRL_CHEN_Msk;
    /* Set SDADC to run off GCLK0 */
    GCLK_REGS->GCLK_PCHCTRL[SDADC_GCLK_ID] = GCLK_PCHCTRL_GEN_GCLK0 | GCLK_PCHCTRL_CHEN_Msk;
    /* Set DAC to run off GCLK0 */
    GCLK_REGS->GCLK_PCHCTRL[DAC_GCLK_ID] = GCLK_PCHCTRL_GEN_GCLK0 | GCLK_PCHCTRL_CHEN_Msk;
    /* Set the TC3 instance to run off GCLK0 */
    GCLK_REGS->GCLK_PCHCTRL[TC3_GCLK_ID] = GCLK_PCHCTRL_GEN_GCLK0 | GCLK_PCHCTRL_CHEN_Msk;
}

void clocks_init (void) {
    osc48m_init();
    gclk0_init();
    gclk1_init();
    mclk_init();
    peripheral_clk_init();
}



