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
    
    // Set the read-wait-states to 3 at immediately after startup
    NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_RWS(3UL); 

    // Initialization of clock, pins, and peripherals
    pin_init();
    system_init();
    systick_init();
    uart_init();
    nvm_init();
    nvic_init();
    sdadc_init();
    tc3_init();
    
    const char* msg = "Reached the while loop!\n\n\n\r";
    uint16_t start = 0;
    uint16_t end = 0;
    float elapsed = 0;
    printf("%s", msg);
    
    while(1) {
        tc3_start();
        start = tc3_counter_get();
        systick_delay_ms(1000);
        end = tc3_counter_get();
        tc3_end();
        printf("Start is %u, end is %u\n\n\n\r", start, end);
        elapsed = calc_elapsed(start, end);
        printf("Timer ran for %.8f\n\n\n\r", elapsed);
    }
    
    
    return (EXIT_SUCCESS);
}

