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

// These structures are declared in each individual header file, 
// but for some reason the linker cannot load them.
// As a temporary work around, they are declared here

extern struct sdadc_t sdadc;

extern struct timer_t timer;

extern struct conversions_t conversions;

extern struct fuzzyConstants_t fuzzyConstants;
extern struct fuzzyVars_t fuzzyVars;
extern struct compute_gaussian_t compute_gaussian;
extern struct tempDev_gaussianLUT_t tempDev_gaussianLUT;
extern struct tempSlope_gaussianLUT_t tempSlope_gaussianLUT;
extern struct interpolation_t interpolation;
extern tempMembership_t tempMembership;
extern slopeMembership_t slopeMembership;
extern struct evaluate_t evaluate;
extern struct fuzzyOutputs_t fuzzyOutputs;
extern struct devLUTs_t devLUTs;
extern struct slopeLUTs_t slopeLUTs;

extern struct defuzzify_t defuzzify;



int main (void)
{
    /* Initialize all modules */
    SYS_Initialize (NULL);
     
    SDADC_Init(); // Initialize SDADC
    DAC_Initialize(); //Initialize DAC
    
    // Initialize certain changing variables used in the fuzzy logic controller 
    initFuzzyVars(97.00f);
    
    /* Initialize the LUTs for slope since they do not change based on the setpoint*/
    generate_gaussianLUT_slope(slopeLUTs.decMF, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.MIN_SLOPE_LIMIT, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.DEC_CENTER_2);
    generate_gaussianLUT_slope(slopeLUTs.stableMF, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.STABLE_CENTER_1, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.STABLE_CENTER_2);
    generate_gaussianLUT_slope(slopeLUTs.incMF, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.INC_CENTER_1, fuzzyConstants.SIGMA_SLOPE, fuzzyConstants.MAX_SLOPE_LIMIT);
    
    while (true)
    {   
        // Since the LUTs for tempDev is dynamic, the first step is to compute the LUTs
        // based on the starting setpoint (97.00f))
        generate_gaussianLUT_dev(devLUTs.coldMF, fuzzyConstants.SIGMA_COLD_HOT, fuzzyConstants.TEMP_DEV_LOWER_LIMIT, fuzzyConstants.SIGMA_COLD_HOT, fuzzyVars.coldMF_c2);
        generate_gaussianLUT_dev(devLUTs.optimalMF, fuzzyConstants.SIGMA_OPTIMAL, fuzzyVars.optimalMF_c1, fuzzyConstants.SIGMA_OPTIMAL, fuzzyVars.optimalMF_c2);
        generate_gaussianLUT_dev(devLUTs.hotMF, fuzzyConstants.SIGMA_COLD_HOT, fuzzyVars.hotMF_c1, fuzzyConstants.SIGMA_COLD_HOT, fuzzyConstants.TEMP_DEV_UPPER_LIMIT);
        
        // Read from the SDADC over a given time interval 
        clearBuffer();
        startTimer();
        while(!isBufferFull()) {
            readSensor();
        }
        endTimer();
        calcElapsed();
        // Convert the raw samples to voltage, and then to temperature 
        rawToVoltage(sdadc.rawSamples);
        voltageToTemp();
        // For debugging at runtime 
        /*
        for (int i = 0; i < 64; i++) {
            printf(" sample %d is %.4f\n", i, conversions.tempSamples[i]);
        }
         * */
        // Calculate the slope 
        calcSlope(timer.elapsedSeconds);
        
        // Interpolate the slope value and the last tempDev value 
        // Store the result of each into the membership struct members
        tempMembership.cold = interpolate_LUT(conversions.lastSample, devLUTs.coldMF, LUT_SIZE_SLOPE, fuzzyConstants.TEMP_DEV_LOWER_LIMIT, fuzzyConstants.TEMP_DEV_UPPER_LIMIT);
        tempMembership.optimal = interpolate_LUT(conversions.lastSample, devLUTs.optimalMF, LUT_SIZE_SLOPE, fuzzyConstants.TEMP_DEV_LOWER_LIMIT, fuzzyConstants.TEMP_DEV_UPPER_LIMIT);
        tempMembership.hot = interpolate_LUT(conversions.lastSample, devLUTs.hotMF, LUT_SIZE_SLOPE, fuzzyConstants.TEMP_DEV_LOWER_LIMIT, fuzzyConstants.TEMP_DEV_UPPER_LIMIT);
        
        slopeMembership.dec = interpolate_LUT(conversions.tempSlope, slopeLUTs.decMF, LUT_SIZE_DEV, fuzzyConstants.MIN_SLOPE_LIMIT, fuzzyConstants.MAX_SLOPE_LIMIT);
        slopeMembership.stable = interpolate_LUT(conversions.tempSlope, slopeLUTs.stableMF, LUT_SIZE_DEV, fuzzyConstants.MIN_SLOPE_LIMIT, fuzzyConstants.MAX_SLOPE_LIMIT);
        slopeMembership.inc = interpolate_LUT(conversions.tempSlope, slopeLUTs.incMF, LUT_SIZE_DEV, fuzzyConstants.MIN_SLOPE_LIMIT, fuzzyConstants.MAX_SLOPE_LIMIT);
    
        //Pass the degrees of membership previously calculated to the evaluate function
        float temp = 0;
        temp = evaluate_ruleset(tempMembership, slopeMembership);
        defuzzify_10bit(temp);
        DAC_DataWrite(defuzzify.DAC_val);
    }
    
    
    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}



/*******************************************************************************
 End of File
*/

