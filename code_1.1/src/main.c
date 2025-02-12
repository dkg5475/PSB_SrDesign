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


#define SDADC_VREF                      (3.3f)
#define DAC_COUNT_INCREMENT             (31U)  // equivalent to 0.1V(0.1 / (3.3 / ((2^10) - 1)))
#define DAC_COUNT_MAX                   (1023U) // 0 to 1023 (10 bit DAC))
#define SDADC_RESULT_SIGNED_BIT_MSK     (~(0x01 << 15)) // bit mask for conversion

/*
 For the SAM C20/C21 microcontrollers, the Sigma-Delta ADC (SDADC) result register contains a 
 * 16-bit signed result, where:

 -Bit 15 (MSB) represents the sign bit (1 for negative, 0 for positive).
 -Bits [14:0] represent the ADC conversion result in two?s complement format.
 This macro is used to mask out the sign bit and extract only the magnitude of the ADC result.
 */


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

uint16_t sdadc_count; // for storing SDADC count
/* Initial value of DAC count which is midpoint = 1.65 V*/
uint16_t dac_count = 0x200;

// 
double input_voltage; 
double currentTemp; 
double prevTemp; 
double currentSlope; 


void switch_handler(uintptr_t context )
{
    /* Write next data sample */
    dac_count = dac_count + DAC_COUNT_INCREMENT;

    if (dac_count > DAC_COUNT_MAX)
            dac_count=0;

    DAC_DataWrite(dac_count);
}


int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    //SYSTICK_TimerStart();
    // EIC_CallbackRegister(EIC_PIN_3, switch_handler, (uintptr_t) NULL);
    DAC_DataWrite(dac_count);

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
	
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

