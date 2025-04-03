/* 
 * File:   main.c
 * Author: Danfi
 *
 * Created on March 26, 2025, 7:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "samc21e18a.h"
#include "core_cm0plus.h"
#include "../Header/system.h"
#include "../Header/port.h"
#include "../Header/uart.h"
#include "../Header/analog.h"
#include "../Header/flash.h"
#include "../Header/cal_temp.h"
#include "../Header/timer.h"
#include "../Header/systick.h"

int main (void) {
    // Clearing of PAC write protection for DSU and chip erase function
    //PAC_REGS->PAC_WRCTRL = PAC_WRCTRL_PERID(33) | PAC_WRCTRL_KEY_CLR;
    //chip_erase();
    
    NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_RWS(3UL); 

    
    // Initialization of clock, pins, and peripherals
    pin_init();
    system_init();
    //systick_init();
    //uart_init();
    //nvm_init();

    //uint8_t character2 = 'E';
 
    while(1) {
        
    }
    
    
    return (EXIT_SUCCESS);
}

