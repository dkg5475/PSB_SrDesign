/* 
 * File:   main.c
 * Author: Danfi
 *
 * Created on March 26, 2025, 7:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "samc21e18a.h"
#include "CMSIS/Core/../Core/../Core/Include/core_cm0plus.h"

void system_init(void) {
    /* Enable OSC32K to run at 32.768 kHz */
    /* No additional configurations needed*/
    OSC32KCTRL_REGS->OSC32KCTRL_OSC32K |= OSC32KCTRL_OSC32K_ENABLE_Msk;
    
    /* Wait for the oscillator to be ready */
    while(!(OSC32KCTRL_REGS->OSC32KCTRL_STATUS & OSC32KCTRL_STATUS_OSC32KRDY_Msk ));
    
    /* Configure 48 MHz clock for the everything other than the CPU */
    /* Set the division factor = 1UL */
    /* Set the source for the GCLK1 instance to be the 48 MHz OSC */
    /* Enable the GCLK1 instance */
    GCLK_REGS->GCLK_GENCTRL[1] = GCLK_GENCTRL_DIV(1UL) | 
            GCLK_GENCTRL_SRC_OSC48M  |
            GCLK_GENCTRL_GENEN_Msk;
    
    /* Wait for the GCLK1 instance to be ready*/
    while(!(GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL1_Msk));
    
    /* Disable the DPLL via the CTRLA register before configuring */
    OSCCTRL_REGS->OSCCTRL_DPLLCTRLA = 0;
    
    /* Wait for sync */
    while(!(OSCCTRL_REGS->OSCCTRL_DPLLSYNCBUSY & OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk));
    
    /* Set the reference for DPLL to be GCLK1 (OSC48M) */
    OSCCTRL_REGS->OSCCTRL_DPLLCTRLB = OSCCTRL_DPLLCTRLB_REFCLK_GCLK;
    
    /* Set the multiplication factor */
    /* Since we are sourcing the 48 MHz oscillator, we need to multiply by 2 */
    /* A multiplication of 2 corresponds to an LDR of 1 and a fractional part of 0*/
    OSCCTRL_REGS->OSCCTRL_DPLLRATIO = OSCCTRL_DPLLRATIO_LDR(1) | OSCCTRL_DPLLRATIO_LDRFRAC(0);
    
    /* Re-enable the DPLL */
    OSCCTRL_REGS->OSCCTRL_DPLLCTRLA = OSCCTRL_DPLLCTRLA_ENABLE_Msk;
    
    /* Wait for the DPLL to lock on*/
    while(!(OSCCTRL_REGS->OSCCTRL_DPLLSTATUS & OSCCTRL_DPLLSTATUS_LOCK_Msk));
    
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

void usart0_initialize(void) {
    /* Enable SERCOM0 clock (assuming SERCOM0 is for UART) */
    /* GCLK1 is set to 48 MHz */
    /* CHEN Msk enables the channel */
    GCLK_REGS->GCLK_PCHCTRL[SERCOM0_GCLK_ID_CORE] = GCLK_PCHCTRL_GEN_GCLK1 | GCLK_PCHCTRL_CHEN_Msk;
    
    /* Enable APB Clock for SERCOM0 */
    MCLK_REGS->MCLK_APBCMASK |= MCLK_APBCMASK_SERCOM0_Msk;
    
    /* Configure PA08 and PA09 for UART TX/RX */
    PORT_REGS->GROUP[0].PORT_PINCFG[8] = PORT_PINCFG_PMUXEN_Msk; // Enable peripheral multiplexing for PA08
    PORT_REGS->GROUP[0].PORT_PINCFG[9] = PORT_PINCFG_PMUXEN_Msk;  // Enable peripheral multiplexing for PA09
    
    PORT_REGS->GROUP[0].PORT_PMUX[4] |= PORT_PMUX_PMUXE(0); // Set PA08 (TX) to SERCOM0 UART TX (MUX 0)
    PORT_REGS->GROUP[0].PORT_PMUX[4] |= PORT_PMUX_PMUXO(0);  // Set PA09 (RX) to SERCOM0 UART RX (MUX 0)
    
    /* Set the USART to run in async mode */
    /* Set the data order */
    /* Set the Immediate Buffer Overflow Notification (IBON) */
    /* Set the RX pin to be SERCOM0_PAD1 */
    /* Set the TX pin to be SERCOM0_PAD0 */
    /* Set the sampling rate to be 8x the baud rate (1UL) */
    /* Set the format of the data to be 8 bits, no parity, 1 stop bit */
    SERCOM0_REGS->USART_INT.SERCOM_CTRLA = SERCOM_USART_INT_CTRLA_CMODE(0UL) |
            SERCOM_USART_INT_CTRLA_DORD_Msk | 
            SERCOM_USART_INT_CTRLA_IBON_Msk | 
            SERCOM_USART_INT_CTRLA_RXPO_PAD1 |
            SERCOM_USART_INT_CTRLA_TXPO_PAD0 | 
            SERCOM_USART_INT_CTRLA_SAMPR(1UL) |
            SERCOM_USART_INT_CTRLA_FORM(0x0UL);
    
    /* Set baud rate to be 14400 for a 48 MHz clock  */
    SERCOM0_REGS->USART_INT.SERCOM_BAUD = (uint16_t)SERCOM_USART_INT_BAUD_BAUD(33330UL);
    
    /* Set the data size to be 8 bits */
    /* Set number of stop bits to be 1 */
    /* Enable receiving */
    /* Enable transmitting */
    SERCOM0_REGS->USART_INT.SERCOM_CTRLB = SERCOM_USART_INT_CTRLB_CHSIZE_8_BIT | // 8 data bits
                                SERCOM_USART_INT_CTRLB_SBMODE_1_BIT | // 1 stop bit
                                SERCOM_USART_INT_CTRLB_RXEN_Msk     |  
                                SERCOM_USART_INT_CTRLB_TXEN_Msk; 
    
    /* Enable the UART after the configurations */
    SERCOM0_REGS->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE_Msk;
    
    /* Wait for sync */
    while((SERCOM0_REGS->USART_INT.SERCOM_SYNCBUSY) != 0U);
    
    /* Enable error interrupt */
    SERCOM0_REGS->USART_INT.SERCOM_INTENSET = (uint8_t)SERCOM_USART_INT_INTENSET_ERROR_Msk;

    /* Enable Receive Complete interrupt */
    SERCOM0_REGS->USART_INT.SERCOM_INTENSET = (uint8_t)SERCOM_USART_INT_INTENSET_RXC_Msk;
    
    /* Enable Transmit Complete Interrupt */
    SERCOM0_REGS->USART_INT.SERCOM_INTENSET = (uint8_t)SERCOM_USART_INT_INTENSET_TXC_Msk;
    
    
            
}

int main(void) {
    
    system_init();
    usart0_initialize();
    
    while(1) {
        
    }
    
    return (EXIT_SUCCESS);
}

