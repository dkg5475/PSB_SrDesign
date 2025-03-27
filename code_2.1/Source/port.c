#include "../Header/port.h"
#include "samc21e18a.h"
#include <stdint.h>

/* All analog pins are set on peripheral function B (PORT_PMUX_PMUXE_B/PORT_PMUX_PMUXO_B) */
    /* All pins belong to GROUP[0] since there are no PA pins on the device*/
    /* Analog pins don't need direction to be set */
    /* Each PMUX[n] covers 2 pins:
     PMUX[0] -> PA00 and PA01
     PMUX[1] -> PA02 and PA03 
     PMUX[2] -> PA04 AND PA05
     PMUX[3] -> PA06 and PA07
     PMUX[4] -> PA08 and PA09
     PMUX[5] -> PA10 and PA11
     PMUX[6] -> PA12 and PA13
     PMUX[7] -> PA14 and PA15
     PMUX[8] -> PA16 and PA17
     PMUX[9] -> PA18 and PA19 
     ...
     PMUX[15] -> PA30 and PA31 */
    
    /* Each PMUX[n] is an 8 bit register split into two 4-bit fields */
    /* PMUXE: Even pin, lower 4-bits */
    /* PMUXO: Odd pin, upper 4-bits
     For example:-
     In PORT_PMUX[1] -> PMUXE controls PA02
     In PORT_PMUX[1] -> PMUXO controls PA03
    */

void pin_cfg(void) {
    
    /* Enable multiplexing on PA02 and disable digital inputs*/
    PORT_REGS->GROUP[0].PORT_PINCFG[2] = PORT_PINCFG_PMUXEN_Msk |
            ~PORT_PINCFG_INEN_Msk; 
    /* Peripheral function B for PMUX[1] */
    PORT_REGS->GROUP[0].PORT_PMUX[1] = PORT_PMUX_PMUXE_B; 

    /* Configure PA04 to be the reference for the SDADC */
    /* Enable peripheral multiplexing for PA04 */
    PORT_REGS->GROUP[0].PORT_PINCFG[4] = PORT_PINCFG_PMUXEN_Msk |
            ~PORT_PINCFG_INEN_Msk;
    /* // Select PMUX for PA04 (SDADC VREF) */
    PORT_REGS->GROUP[0].PORT_PMUX[2] = PORT_PMUX_PMUXE_B; 
    
    /* Configure PA05 and PA06 as analog pins (to read samples from) */
    /* Enable peripheral multiplexing for PA05 and PA06 and disable digital input */
    /* The disabling of digital inputs is done by writing to the corresponding PINCFG register 
     and inverted the enable mask */
    PORT_REGS->GROUP[0].PORT_PINCFG[5] = PORT_PINCFG_PMUXEN_Msk |
            ~PORT_PINCFG_INEN_Msk;
    PORT_REGS->GROUP[0].PORT_PINCFG[6] = PORT_PINCFG_PMUXEN_Msk |
            ~PORT_PINCFG_INEN_Msk; 
    
    /* Select PMUX B (Peripheral function B) for PA05 and PA06*/
    /* PMUX[2] PMUXO -> PA05 */
    /* PMUX[3] PMUXE -> PA06*/
    PORT_REGS->GROUP[0].PORT_PMUX[2] = PORT_PMUX_PMUXO_B |
            ~PORT_PINCFG_INEN_Msk;  
    PORT_REGS->GROUP[0].PORT_PMUX[3] = PORT_PMUX_PMUXE_B |
            ~PORT_PINCFG_INEN_Msk;  
    /* Set PA05 as input */
    PORT_REGS->GROUP[0].PORT_DIRCLR = (1 << 5); 
    /* Set pa 06 as input */
    PORT_REGS->GROUP[0].PORT_DIRCLR = (1 << 6); 
    
    /* Configure PA08 and PA09 for UART TX/RX */   
    /* Enable peripheral multiplexing for PA08, and PA09 */
    PORT_REGS->GROUP[0].PORT_PINCFG[8] = PORT_PINCFG_PMUXEN_Msk; 
    PORT_REGS->GROUP[0].PORT_PINCFG[9] = PORT_PINCFG_PMUXEN_Msk; 
    
    /* PMUX[4] PMUXE -> PA08 */
    /* PMUX[4] PMUXE -> PA09 */
    /* 0x3 refers to peripheral function 3*/
    /* Set PA08 (TX) and PA09 (RX) to peripheral function C */
    PORT_REGS->GROUP[0].PORT_PMUX[4] = PORT_PMUX_PMUXE_C |
    PORT_PMUX_PMUXO_C; 
    
    /* Set PA08 (UART TX) as output */
    PORT_REGS->GROUP[0].PORT_DIRSET = (1 << 8); 
    /* Set PA09 (UART RX) as input */
    PORT_REGS->GROUP[0].PORT_DIRCLR = (1 << 9);  
    
    
    
    /* Configure PA16 for SPI SDIN */
    /* Configure PA17 for SPI SYNC */
    /* Configure PA18 for SPI SCLK */
    /* Enable multiplexing for PA16, PA17, and PA18*/
    PORT_REGS->GROUP[0].PORT_PINCFG[16] = PORT_PINCFG_PMUXEN_Msk; 
    PORT_REGS->GROUP[0].PORT_PINCFG[17] = PORT_PINCFG_PMUXEN_Msk; 
    PORT_REGS->GROUP[0].PORT_PINCFG[18] = PORT_PINCFG_PMUXEN_Msk; 
    
    /* PMUX[8] PMUXE -> PA16 */
    /* PMUX[8] PMUXO -> PA17 */
    /* PMUX[9] PMUXE -> PA18 */
    
    /* PA16 and PA17 as SDIN and SYNC */
    PORT_REGS->GROUP[0].PORT_PMUX[8] = PORT_PMUX_PMUXE_D |   
    PORT_PMUX_PMUXO_D;  
    
    /* PA18 as SCLK */
    PORT_REGS->GROUP[0].PORT_PMUX[9] = PORT_PMUX_PMUXE_D;  
    
    /* Set each SPI signal as an output by writing 1 to PORT_DIRSET*/
    PORT_REGS->GROUP[0].PORT_DIRSET = (1 << 16); 
    PORT_REGS->GROUP[0].PORT_DIRSET = (1 << 17); 
    PORT_REGS->GROUP[0].PORT_DIRSET = (1 << 18); 
}