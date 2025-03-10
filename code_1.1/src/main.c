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
#include "duration.h"
#include "sensor.h"
#include "convert.h"
#include "fis.h"
#include "dac_10bit.h"

extern struct sdadc_t sdadc;
extern struct timer_t timer;
extern struct conversions_t conversions;
extern struct fuzzyVars_t fuzzyVars;
extern struct compute_gaussian_t compute_gaussian;
extern struct tempDev_gaussianLUT_t tempDev_gaussianLUT;
extern struct tempSlope_gaussianLUT_t tempSlope_gaussianLUT;
extern struct interpolation_t interpolation;
extern TempMembership_t TempMembership;
extern SlopeMembership_t SlopeMembership;
extern struct evaluate_t evaluate;
extern struct fuzzyOutputs_t fuzzyOutputs;

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize (NULL);
    SDADC_Init(); // Initialize SDADC
    DAC_Initialize(); //Initialize DAC
    
    while (true)
    {   
        /* Read from the SDADC over a given time interval */
        startTimer();
        clearBuffer();
        while(!isBufferFull()) {
            readSensor();
        }
        endTimer();
        calcElapsed();
        /* Convert the raw samples to voltage, and then to temperature */
        rawToVoltage(sdadc.rawSamples);
        voltageToTemp();
        /* Calculate the slope */
        calcSlope(timer.elapsedSeconds);
        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}



/*******************************************************************************
 End of File
*/

