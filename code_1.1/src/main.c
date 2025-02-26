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
#include "definitions.h"                // SYS function prototypes


#define SDADC_VREF                      (2.0f)
#define DAC_COUNT_INCREMENT             (132U)  // equivalent to 0.1V increment
// (0.1 / (2.0 / ((2^16) - 1)))
#define DAC_COUNT_MAX                   (65535U) // 0 to 65535 (16 bit DAC))
#define SDADC_RESULT_SIGNED_BIT_MSK     (~(0x01 << 15)) // bit mask for conversion

/*
 For the SAM C20/C21 microcontrollers, the Sigma-Delta ADC (SDADC) result register contains a 
 * 16-bit signed result, where:

 -Bit 15 (MSB) represents the sign bit (1 for negative, 0 for positive).
 -Bits [14:0] represent the ADC conversion result in two?s complement format.
 This macro is used to mask out the sign bit and extract only the magnitude of the ADC result.
 */

void readSensor (void); // for reading and storing conversion results


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

// variables that will be fuzzified
typedef struct { 
    double tempPoints[64];
    double slope; 
}fuzzyInputs;

float input_voltage;
int16_t sdadc_count; // for storing SDADC count


int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    while ( true )
    {
	
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

void readSensor (void) {
    /* Start ADC Conversion*/
        SDADC_ConversionStart();
        
        for (int i = 0; i < sizeof(fuzzyInputs->tempPoints); i++) {
            while(!SDADC_ConversionResultIsReady()) {
                // wait for result
            } 
            
            sdadc_count = (int16_t)SDADC_ConversionResultGet();
            input_voltage = (float)sdadc_count * SDADC_VREF / 32767;
            
        
        }
        /* Wait till SDADC conversion result is available */
        
        
        
        
        
}


/*******************************************************************************
 End of File
*/

