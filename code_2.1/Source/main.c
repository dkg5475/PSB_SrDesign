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
#include "../Header/system.h"
#include "../Header/port.h"
#include "../Header/uart.h"
#include "../Header/analog.h"
#include "../Header/cal_temp.h"
#include "../Header/timer.h"

int main(void) {
    // Initialization of clock, pins, and peripherals
    clocks_init();
    pin_init();
    sdadc_init();
    tc3_init();
    
    
    
    //uint8_t msg[10] = "Hello\n\r";
    //uint8_t character1 = 'H';
    // uint8_t character2 = 'E';
    
    while(1) {
    }
    
    return (EXIT_SUCCESS);
}

