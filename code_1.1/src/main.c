/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <math.h>                       // Defines natural log (ln))
#include "definitions.h"                // SYS function prototypes
// Custom header and source files are placed in code_1.X
#include "../code_1.X/duration.h"                
#include "../code_1.X/sensor.h"
#include "../code_1.X/convert.h"
#include "../code_1.X/fis.h"
#include "../code_1.X/dac_10bit.h"
#include "../code_1.x/uart.h"

int main (void)
{
    /* Initialize all modules */
    SYS_Initialize (NULL);
    
    show_boot_screen();
     
    float T_set_initial = 97.00f;
    float T_set_received = 0.0f;
    // float T_set_ideal = 0.0f;
    float rule_output = 0.0f;
    uint16_t dac_data = 0;
    
    SDADC_InitVariables(); // Initialize SDADC and some internal struct members
    
    
    // Set the read threshold so that the event handler runs when there are at least 2 bytes in the buffer
    SERCOM0_USART_ReadThresholdSet(2);
    
    // Register UART Read/Write Interrupt Handlers
    SERCOM0_USART_WriteCallbackRegister(usartWriteEventHandler, (uintptr_t) NULL);
    SERCOM0_USART_ReadCallbackRegister(usartReadEventHandler, (uintptr_t) NULL);
    
    initFuzzyVars(T_set_initial);
    
    // Create look-up tables (LUTs) for slope membership functions
    generate_gaussianLUT_slope(slopeLUTs.decMF, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.MIN_SLOPE_LIMIT, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.DEC_CENTER_2);
    generate_gaussianLUT_slope(slopeLUTs.stableMF, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.STABLE_CENTER_1, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.STABLE_CENTER_2);
    generate_gaussianLUT_slope(slopeLUTs.incMF, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.INC_CENTER_1, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.MAX_SLOPE_LIMIT);
    
    while (true)
    {   
        tempUpdateFlag = false;
        
        if (commandReady) {
            commandReady = false; // reset the flag
            
            receivedCommand.id = parseCommand((const char*)rxBuffer);
            
            handleCommand(&receivedCommand);
            
            if (receivedCommand.id == SETPOINT) {
                T_set_received = atof(receivedCommand.payload);
                printf("New received setpoint is %.3f\r\n", T_set_received);
            }
        } 
        // Create LUTs for temperature difference membership functions
        generate_gaussianLUT_dev(devLUTs.coldMF, fuzzyConstants.SIGMA_COLD_HOT, fuzzyConstants.TEMP_DEV_LOWER_LIMIT, fuzzyConstants.SIGMA_COLD_HOT, fuzzyVars.coldMF_c2);
        generate_gaussianLUT_dev(devLUTs.optimalMF, fuzzyConstants.SIGMA_OPTIMAL, fuzzyVars.optimalMF_c1, fuzzyConstants.SIGMA_OPTIMAL, fuzzyVars.optimalMF_c2);
        generate_gaussianLUT_dev(devLUTs.hotMF, fuzzyConstants.SIGMA_COLD_HOT, fuzzyVars.hotMF_c1, fuzzyConstants.SIGMA_COLD_HOT, fuzzyConstants.TEMP_DEV_UPPER_LIMIT);
        
        // Enable receiving data
        SERCOM0_USART_Read((uint8_t*)rxBuffer, RX_BUFFER_SIZE);
        
        
        startTimer();
        while(!sdadc.bufferFullFlag) {
            readSensor();
        }
        endTimer();
        calcElapsed();
        
        rawToVoltage(sdadc.rawSamples);
        findAverage();
        
        conversions.samplesAverage = voltageToTemp(conversions.samplesAverage_voltage);
        conversions.firstSample = voltageToTemp(conversions.firstSample_voltage);
        conversions.lastSample = voltageToTemp(conversions.lastSample_voltage);
        
        calcSlope(timer.elapsedSeconds);
        
        if (verboseActiveFlag && !tempUpdateFlag) {
            tempUpdateFlag = true; //user has just been updated
            sendCurrentTemp(conversions.samplesAverage);
        }
        
        // Find the degree of membership for membership functions for the individual average temperature reading
        tempMembership.cold = interpolate_LUT(conversions.samplesAverage, devLUTs.coldMF, LUT_SIZE_DEV, fuzzyConstants.TEMP_DEV_LOWER_LIMIT, fuzzyConstants.TEMP_DEV_UPPER_LIMIT);
        tempMembership.optimal = interpolate_LUT(conversions.samplesAverage, devLUTs.optimalMF, LUT_SIZE_DEV, fuzzyConstants.TEMP_DEV_LOWER_LIMIT, fuzzyConstants.TEMP_DEV_UPPER_LIMIT);
        tempMembership.hot = interpolate_LUT(conversions.samplesAverage, devLUTs.hotMF, LUT_SIZE_DEV, fuzzyConstants.TEMP_DEV_LOWER_LIMIT, fuzzyConstants.TEMP_DEV_UPPER_LIMIT);
        
        // Find the degree of membership for each membership functions for the slope
        slopeMembership.dec = interpolate_LUT(conversions.tempSlope, slopeLUTs.decMF, LUT_SIZE_SLOPE, fuzzyConstants.MIN_SLOPE_LIMIT, fuzzyConstants.MAX_SLOPE_LIMIT);
        slopeMembership.stable = interpolate_LUT(conversions.tempSlope, slopeLUTs.stableMF, LUT_SIZE_SLOPE, fuzzyConstants.MIN_SLOPE_LIMIT, fuzzyConstants.MAX_SLOPE_LIMIT);
        slopeMembership.inc = interpolate_LUT(conversions.tempSlope, slopeLUTs.incMF, LUT_SIZE_SLOPE, fuzzyConstants.MIN_SLOPE_LIMIT, fuzzyConstants.MAX_SLOPE_LIMIT);
        
        rule_output = evaluate_ruleset(tempMembership, slopeMembership);
        
        dac_data = defuzzify_10bit(rule_output);
        
        // Use DAC_DataWrite to write to internal DAC
        DAC_DataWrite(dac_data);
        
    }
    
    
    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}



/*******************************************************************************
 End of File
*/

