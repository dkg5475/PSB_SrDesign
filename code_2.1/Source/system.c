#include "../Header/system.h"
#include "samc21e18a.h"
#include "core_cm0plus.h"
#include <stdint.h>

static void osc48m_init(void) {
    
    uint32_t calibValue = (uint32_t)(((*(uint64_t*)0x00806020UL) >> 41) & 0x3fffffUL);
    OSCCTRL_REGS->OSCCTRL_CAL48M = calibValue;

    /* Selection of the Division Value */
    OSCCTRL_REGS->OSCCTRL_OSC48MDIV = (uint8_t)OSCCTRL_OSC48MDIV_DIV(0UL);

    //wait for sync
    while((OSCCTRL_REGS->OSCCTRL_OSC48MSYNCBUSY & OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV_Msk) == OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV_Msk);
    
    //wait for sync
    while((OSCCTRL_REGS->OSCCTRL_STATUS & OSCCTRL_STATUS_OSC48MRDY_Msk) != OSCCTRL_STATUS_OSC48MRDY_Msk);
    
    OSCCTRL_REGS->OSCCTRL_OSC48MCTRL |= OSCCTRL_OSC48MCTRL_ONDEMAND_Msk;
}


static void gclk0_init (void) {
    // Configure GCLK0 (Main clock) 
    // Set the division factor = 1UL 
    // Enable the GCLK0 Instance 
    GCLK_REGS->GCLK_GENCTRL[0] = GCLK_GENCTRL_DIV(0UL) |
            GCLK_GENCTRL_SRC_OSC48M  |
            GCLK_GENCTRL_GENEN_Msk;
    
    // Wait for the GCLK0 instance to be ready
    while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL0_Msk) == GCLK_SYNCBUSY_GENCTRL0_Msk);

}


/* 
static void gclk1_init (void) {
    // Configure GCLK1 for other uses 
    GCLK_REGS->GCLK_GENCTRL[1] = GCLK_GENCTRL_DIV(1UL) | 
            GCLK_GENCTRL_SRC_OSC48M  |
            GCLK_GENCTRL_GENEN_Msk;
    
    // Wait for the GCLK1 instance to be ready 
    while(!(GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL1_Msk));
}
*/


static void mclk_init (void) {
    
    // Enable APBx (Peripheral Bus) Clocks
    MCLK_REGS->MCLK_APBAMASK = MCLK_APBAMASK_MCLK_Msk |   // Main Clock
                           MCLK_APBAMASK_OSCCTRL_Msk | // Oscillator Control
                           MCLK_APBAMASK_GCLK_Msk |    // Generic Clock Controller
                           MCLK_APBAMASK_WDT_Msk |     // Watchdog Timer
                           MCLK_APBAMASK_SUPC_Msk |    // Supply Controller
                           MCLK_APBAMASK_PM_Msk |      // Power Manager 
                           MCLK_APBAMASK_RSTC_Msk;     // Reset Controller 

    MCLK_REGS->MCLK_APBBMASK = MCLK_APBBMASK_PORT_Msk;   // GPIO Ports
     
    MCLK_REGS->MCLK_APBCMASK = MCLK_APBCMASK_SERCOM0_Msk | // UART
                           MCLK_APBCMASK_SERCOM3_Msk | // SPI
                           MCLK_APBCMASK_SDADC_Msk |   // Sigma-Delta ADC
                           MCLK_APBCMASK_DAC_Msk |     // Digital-to-Analog Converter
                           MCLK_APBCMASK_TC3_Msk;      // Timer/Counter
    

}



static void peripheral_clk_init (void) {
    // Enable SERCOM0 clock, where SERCOM0 corresponds to the USART instance  
    // Enable SERCOM3 clock, where SERCOM3 corresponds to the SPI instance 
    // GCLK0 is set to 48 MHz 
    // CHEN Msk enables the channel 
    
    // Set SERCOM0 to run off GCLK0 
    GCLK_REGS->GCLK_PCHCTRL[SERCOM0_GCLK_ID_CORE] = GCLK_PCHCTRL_GEN(0x0UL) | GCLK_PCHCTRL_CHEN_Msk;
    // Wait for sync
    while ((GCLK_REGS->GCLK_PCHCTRL[SERCOM0_GCLK_ID_CORE] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk);
    
    
    // Set SERCOM3 to run off GCLK0 
    GCLK_REGS->GCLK_PCHCTRL[SERCOM3_GCLK_ID_CORE] = GCLK_PCHCTRL_GEN_GCLK0 | GCLK_PCHCTRL_CHEN_Msk;
    //Wait for sync
    while ((GCLK_REGS->GCLK_PCHCTRL[SERCOM3_GCLK_ID_CORE] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk);
    
    // Set SDADC to run off GCLK0 
    GCLK_REGS->GCLK_PCHCTRL[SDADC_GCLK_ID] = GCLK_PCHCTRL_GEN_GCLK0 | GCLK_PCHCTRL_CHEN_Msk;
    // Wait for sync
    while ((GCLK_REGS->GCLK_PCHCTRL[SDADC_GCLK_ID] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk);
    
    // Set DAC to run off GCLK0 
    GCLK_REGS->GCLK_PCHCTRL[DAC_GCLK_ID] = GCLK_PCHCTRL_GEN_GCLK0 | GCLK_PCHCTRL_CHEN_Msk;
    //Wait for sync
    while ((GCLK_REGS->GCLK_PCHCTRL[DAC_GCLK_ID] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk);
    
    // Set the TC3 instance to run off GCLK0 
    GCLK_REGS->GCLK_PCHCTRL[TC3_GCLK_ID] = GCLK_PCHCTRL_GEN_GCLK0 | GCLK_PCHCTRL_CHEN_Msk;
    //wait for sync
    while ((GCLK_REGS->GCLK_PCHCTRL[TC3_GCLK_ID] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk);
    
}


void system_init (void) {
    osc48m_init();
    gclk0_init();
    mclk_init();
    peripheral_clk_init();
}

void nvic_init (void) {
    // Enable NVIC Controller 
    __DMB();
    __enable_irq();
            
    NVIC_SetPriority(SERCOM0_IRQn, 0);
    NVIC_EnableIRQ(SERCOM0_IRQn);
    
    NVIC_SetPriority(SDADC_IRQn, 1);
    NVIC_EnableIRQ(SDADC_IRQn);
}

void nvic_int_disable (void) {
    __disable_irq();
    __DMB();
}

void nvic_int_enable (void) {
    __DMB();
    __enable_irq();
}

void supc_init (void) {
    USER_FUSES_REGS->FUSES_USER_WORD_0 = FUSES_USER_WORD_0_NVMCTRL_BOOTPROT_SIZE_16384BYTES; // protect the first 16KB of flash (startup file size))
    /* 
    USER_FUSES_REGS->FUSES_USER_WORD_0 = FUSES_USER_WORD_0_BODVDD_DIS_DISABLED; //disable the BOD on startup before configuration
    USER_FUSES_REGS->FUSES_USER_WORD_0 = FUSES_USER_WORD_0_BODVDDUSERLEVEL(0x3F); // Fuse setting for BODVDD threshold
    */
     
    SUPC_REGS->SUPC_BODVDD &= ~(SUPC_BODVDD_ENABLE_Msk); // disable the BODVDD during configuration
    while (!(SUPC_REGS->SUPC_STATUS & SUPC_STATUS_BVDDSRDY_Msk)); // wait for register sync 
    
    SUPC_REGS->SUPC_BODVDD = SUPC_BODVDD_LEVEL(0x15) | // set the threshold for the BODVDD to 2.7V
                             SUPC_BODVDD_ACTION_NONE | // BODVDD will do nothing for now
                             SUPC_BODVDD_HYST_Msk | //enable hysteresis to deal with noise
                             SUPC_BODVDD_ENABLE(0x1);  // enable BODVDD (via SUPC register) 
    
    while (!(SUPC_REGS->SUPC_STATUS & SUPC_STATUS_BVDDSRDY_Msk)); // wait for register sync 
    
    WDT_REGS->WDT_CTRLA &= ~(WDT_CTRLA_ENABLE_Msk); // Disable during configurations
    while (!(WDT_REGS->WDT_SYNCBUSY & WDT_SYNCBUSY_ENABLE_Msk)); // Wait for register sync
    
    WDT_REGS->WDT_CTRLA =  WDT_CTRLA_ALWAYSON_Msk | //WDT is always on
            WDT_CTRLA_WEN_Msk | // Enable WDT window
            WDT_CTRLA_ALWAYSON(0x0); // can be disabled via enable bit
    
    while(!(WDT_REGS->WDT_SYNCBUSY & WDT_SYNCBUSY_WEN_Msk)); // Wait for window enable sync 
    
    WDT_REGS->WDT_CONFIG = WDT_CONFIG_PER_CYC4096 | // timeout period of 4096 cycles
            WDT_CONFIG_WINDOW_CYC4096; // watchdog closed window period of 4096
    
    WDT_REGS->WDT_EWCTRL = WDT_EWCTRL_EWOFFSET_CYC2048; // cycles after warning is triggered before reset 
    
    WDT_REGS->WDT_CTRLA |= WDT_CTRLA_ENABLE_Msk; // enable 
    
    while(!(WDT_REGS->WDT_SYNCBUSY & WDT_SYNCBUSY_ENABLE_Msk)); // Wait for enable bit sync 
}

void chip_erase (void) {
    DSU_REGS->DSU_CTRL = DSU_CTRL_CE_Msk;
    while(!(DSU_REGS->DSU_STATUSA & DSU_STATUSA_DONE_Msk)); // this while loop runs while the DSU operation is not completed 
    // when a DSU operation is finished, a 1 is written to the STATUSA Register
    
}


