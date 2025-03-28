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

int main(void) {
    clocks_init();
    pin_init();
    uart_init();
    
    uint8_t msg[10] = "Hello\n\r";
    
    while(1) {
        printf("%s\n\r", msg);
    }
    
    return (EXIT_SUCCESS);
}

