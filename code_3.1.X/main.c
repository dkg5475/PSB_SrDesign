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
#include "system.h"
#include "port.h"
#include "uart.h"
#include "analog.h"
#include "flash.h"
#include "cal_temp.h"
#include "timer.h"
#include "systick.h"
#include "dac.h"
#include "fis.h"

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
    initFuzzyVars(98.00f);

    // LUTs for temperature deviation 
    generate_gaussianLUT_dev(devLUTs.coldMF, STD_DEV_COLD_HOT, TEMP_LOWER_LIMIT, STD_DEV_COLD_HOT, COLD_C2);
    generate_gaussianLUT_dev(devLUTs.optimalMF, STD_DEV_OPTIMAL, OPTIMAL_C1, STD_DEV_OPTIMAL, OPTIMAL_C2);
    generate_gaussianLUT_dev(devLUTs.hotMF, STD_DEV_COLD_HOT, HOT_C1, STD_DEV_COLD_HOT, TEMP_UPPER_LIMIT);
  
    
    //int counter = 1;
    
    float prev_state = 0;
    float current_state = 0;
    float next_state = 0;
    
    uint16_t dac_out = 246;
    prev_state = 0.601173f;
    
    //float voltage_dac = 0;
    
    dac_write(dac_out);
    
    
    while(1) {
        //printf("Counter iteration %d:\n\n\r", counter);
        sdadc_start();
        while (!bufferFullFlag);
        sdadc_stop(); // end sampling
        
        
        raw_to_voltage(); // convert to voltage
        find_average(); // find the average of the samples
        //printf("Thermistor Voltage (V) = %.8f\n\n\r", inputs.samples_average);
        get_temp_inputs(); // convert the first, last, and average of the samples to temp
        //calc_slope(elapsed); // calculate the slope
        //inputs.temp_slope = (inputs.samples_average - prev_temp)/elapsed;
        //prev_temp = inputs.samples_average;
        //printf("First Sample = %.8f\n\n\r", inputs.first_sample);
        //printf("Last Sample = %.8f\n\n\r", inputs.last_sample);
        //printf("Time elapsed = %.8f\n\n\r", elapsed);
        //printf("Slope = %.8f\n\n\r", inputs.temp_slope);
        
        
        //printf("Temperature (C) = %.8f\n\n\r", inputs.samples_average);
        //printf("First temperature sample: %.8f\n\n\r", inputs.first_sample);
        //printf("Last temperature sample: %.8f\n\n\r", inputs.last_sample);
        //printf("Elapsed time is %.8f \n\n\r", elapsed);
        //printf("Slope (C/ms) = %.8f\n\n\r", inputs.temp_slope);
        
        
        tempMembership.cold = interpolate_LUT(inputs.samples_average, devLUTs.coldMF, LUT_SIZE_DEV, TEMP_LOWER_LIMIT, TEMP_UPPER_LIMIT);
        tempMembership.optimal = interpolate_LUT(inputs.samples_average, devLUTs.optimalMF, LUT_SIZE_DEV, TEMP_LOWER_LIMIT, TEMP_UPPER_LIMIT);
        tempMembership.hot = interpolate_LUT(inputs.samples_average, devLUTs.hotMF, LUT_SIZE_DEV, TEMP_LOWER_LIMIT, TEMP_UPPER_LIMIT);

        
        // Evaluate the output of the controller
        current_state = evaluate_ruleset(tempMembership);

        //printf("\n\r\r");
        //printf("The degree of membership of cold is %.8f\n\n\r", tempMembership.cold);
        //printf("The degree of membership of optimal is %.8f\n\n\r", tempMembership.optimal);
        //printf("The degree of membership of hot is %.8f\n\n\r", tempMembership.hot);
        
        //printf("The degree of membership of decreasing is %.8f\n\n\r", slopeMembership.dec);
        //printf("The degree of membership of stable is %.8f\n\n\r", slopeMembership.stable);
        //printf("The degree of membership of increasing is %.8f\n\n\r", slopeMembership.inc);
       
        //printf("\n\r\r");

        next_state = prev_state - current_state;
        
        if (next_state < 0.6) {
            next_state = 0.6;
        }
        
        if (next_state > 2.5) {
            next_state = 2.5;
        }
        
        //printf("Prev  %.8f\n\n\r\r", prev_state);
        //printf("Computed Voltage Adjustment = %.8f\n\n\r", current_state);
        //printf("DAC Output Voltage = %.8f\n\n\r", next_state);

        // Defuzzify the output
        dac_out = defuzzify(next_state);
        
        // write to dac
        dac_write(dac_out);
        //printf("DAC Output = %u\n\r\r", dac_out);
        
        prev_state = next_state;
        
        printf("%.8f %.8f %u \n\r", inputs.samples_average, next_state, dac_out);
        
        /*
        counter++;
        if (counter == 1) {
            printf("%.8f %.8f %u \n\r", inputs.samples_average, next_state, dac_out);
            counter = 1;
        }
        */
        //systick_delay_ms(10);
        //printf("---------------------------------\n\r");
    }
    
    
    return (EXIT_SUCCESS);
}

