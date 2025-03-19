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

int main (void)
{
    /* Initialize all modules */
    SYS_Initialize (NULL);
     
    SDADC_InitVariables(); // Initialize SDADC and some internal struct members
    
    float T_set_initial = 97.00f;
    initFuzzyVars(T_set_initial);
    
    // Create look-up tables (LUTs) for slope membership functions
    generate_gaussianLUT_slope(slopeLUTs.decMF, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.MIN_SLOPE_LIMIT, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.DEC_CENTER_2);
    generate_gaussianLUT_slope(slopeLUTs.stableMF, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.STABLE_CENTER_1, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.STABLE_CENTER_2);
    generate_gaussianLUT_slope(slopeLUTs.incMF, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.INC_CENTER_1, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.MAX_SLOPE_LIMIT);
    
    while (true)
    {   
        // Create LUTs for temperature difference membership functions
        
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
        
        
    }
    
    
    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}



/*******************************************************************************
 End of File
*/

