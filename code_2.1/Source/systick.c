#include "../Header/systick.h"
#include "samc21e18a.h"
#include "core_cm0plus.h"

volatile uint32_t counter = 0;

void systick_init (void) {
    SysTick->CTRL = 0U; // disable systick before writing to its registers
    
    SysTick->LOAD = 0xBB7F; // interrupts every 1 ms
    SysTick->VAL = 0; // reset the counter current value register
    
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | // set the clk source as the cpu clk
            SysTick_CTRL_TICKINT_Msk | // counting down to 0 pends the handler
            SysTick_CTRL_ENABLE_Msk; // enable systick after configuring
    
}

void SysTick_Handler (void) {
    if (counter > 0) {
        counter--;
    }
}

void systick_delay_ms (uint32_t ms) {
    counter = ms;
    while (counter > 0); // wait for the counter to decrement
}