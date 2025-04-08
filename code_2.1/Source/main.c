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
#include "../Header/dac.h"
#include "../Header/fis.h"

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
    dac_init();
    tc3_init();
    
    //Enable interrupts
    nvic_int_enable();
    
    // Initial temperature setpoint 
    initFuzzyVars(97.00f);
    
    // LUTs for slope
    generate_gaussianLUT_slope(slopeLUTs.decMF, STD_DEV_SLOPE, SLOPE_LOWER_LIMIT, STD_DEV_SLOPE, DEC_C2);
    generate_gaussianLUT_slope(slopeLUTs.stableMF, STD_DEV_SLOPE, STABLE_C1, STD_DEV_SLOPE, STABLE_C2);
    generate_gaussianLUT_slope(slopeLUTs.incMF, STD_DEV_SLOPE, INC_C1, STD_DEV_SLOPE, SLOPE_UPPER_LIMIT);
    
    // LUTs for temperature deviation 
    generate_gaussianLUT_dev(devLUTs.coldMF, STD_DEV_COLD_HOT, TEMP_LOWER_LIMIT, STD_DEV_COLD_HOT, COLD_C2);
    generate_gaussianLUT_dev(devLUTs.optimalMF, STD_DEV_OPTIMAL, OPTIMAL_C1, STD_DEV_OPTIMAL, OPTIMAL_C2);
    generate_gaussianLUT_dev(devLUTs.hotMF, STD_DEV_COLD_HOT, HOT_C1, STD_DEV_COLD_HOT, TEMP_UPPER_LIMIT);
    
    const char* msg = "Reached the while loop\n\n\n\r";
    printf("%s", msg);
    
    uint16_t start = 0;
    uint16_t end = 0;
    float elapsed = 0;
    int counter = 1;
    float output = 0;
    uint16_t dac_out = 0;
    
    dac_write((uint16_t)0x246); // heat the crystal to its max to begin (~0.6V)
    
    while(1) {
        //printf("Counter iteration %d:\n\n\r", counter);
        start = 0;
        end = 0;
        tc3_start(); // start the timer
        start = tc3_counter_get(); // get timer value after start
        sdadc_start();
        while (!bufferFullFlag);
        sdadc_stop(); // end sampling
        end = tc3_counter_get(); // get the timer value before end
        tc3_end(); // end timer
        elapsed = calc_elapsed(start, end); // calculate the time that has elapsed
        
        raw_to_voltage(); // convert to voltage
        find_average(); // find the average of the samples
        get_temp_inputs(); // convert the first, last, and average of the samples to temp
        calc_slope(elapsed); // calculate the slope

        printf("Average of the samples is %.8f\n\n\r", inputs.samples_average);
        printf("First temperature sample: %.8f\n\n\r", inputs.first_sample);
        printf("Last temperature sample: %.8f\n\n\r", inputs.last_sample);
        printf("Elapsed time is %.8f \n\n\r", elapsed);
        printf("Slope value is %.8f\n\n\r", inputs.temp_slope);
        
        tempMembership.cold = interpolate_LUT(inputs.samples_average, devLUTs.coldMF, LUT_SIZE_DEV, TEMP_LOWER_LIMIT, TEMP_UPPER_LIMIT);
        tempMembership.optimal = interpolate_LUT(inputs.samples_average, devLUTs.optimalMF, LUT_SIZE_DEV, TEMP_LOWER_LIMIT, TEMP_UPPER_LIMIT);
        tempMembership.hot = interpolate_LUT(inputs.samples_average, devLUTs.hotMF, LUT_SIZE_DEV, TEMP_LOWER_LIMIT, TEMP_UPPER_LIMIT);
        
        // Find the degree of membership for each membership functions for the slope
        slopeMembership.dec = interpolate_LUT(inputs.temp_slope, slopeLUTs.decMF, LUT_SIZE_SLOPE, SLOPE_LOWER_LIMIT, SLOPE_UPPER_LIMIT);
        slopeMembership.stable = interpolate_LUT(inputs.temp_slope, slopeLUTs.stableMF, LUT_SIZE_SLOPE, SLOPE_LOWER_LIMIT, SLOPE_UPPER_LIMIT);
        slopeMembership.inc = interpolate_LUT(inputs.temp_slope, slopeLUTs.incMF, LUT_SIZE_SLOPE, SLOPE_LOWER_LIMIT, SLOPE_UPPER_LIMIT);
        
        // Evaluate the output of the controller
        output = evaluate_ruleset(tempMembership, slopeMembership);
        
        printf("The degree of membership of cold is %.8f\n\n\r", tempMembership.cold);
        printf("The degree of membership of optimal is %.8f\n\n\r", tempMembership.optimal);
        printf("The degree of membership of hot is %.8f\n\n\r", tempMembership.hot);
        
        printf("The degree of membership of decreasing is %.8f\n\n\r", slopeMembership.dec);
        printf("The degree of membership of stable is %.8f\n\n\r", slopeMembership.stable);
        printf("The degree of membership of increasing is %.8f\n\n\r", slopeMembership.inc);
        
        printf("Evaluated rule-set output is %.8f\n\n\r\r", output);
        
        // Defuzzify the output
        dac_out = defuzzify(output);
        
        dac_write(dac_out);
        // dac_write((uint16_t)246); // for testing
        
        //systick_delay_ms(5000);
        counter++;
    }
    
    
    return (EXIT_SUCCESS);
}

