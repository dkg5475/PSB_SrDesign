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
#include <xc.h>

int main(void) {
    clocks_init();
    pin_init();
    
    //uint8_t msg[10] = "Hello\n\r";
    //uint8_t character1 = 'H';
    // uint8_t character2 = 'E';
    
    while(1) {
    }
    
    return (EXIT_SUCCESS);
}

