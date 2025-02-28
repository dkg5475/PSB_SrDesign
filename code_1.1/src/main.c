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


/* Primary functions used for Fuzzy Logic Algorithm */
void readSensor            (void); 
void convertSamples        (void);
void calcSlope             (void); 
void fuzzifyInputs         (double tempReading, double slope); 
void defuzzify             (double fuzzOut);
void send_16_bit_dac_output(unsigned int dac_data);


/* Constants used in conversion from voltage to temperature */
const double SUPPLY_VOLTAGE = 3.0;           // Supply voltage (in voltage divider)
const double R18            = 4990.0;        // Known resistor value in voltage divider
const double B_VALUE        = 4300.0;        // Beta-value used for temp conversion 
const double R_25           = 100000.0;      // Resistance of thermistor at room temp (25 deg C)
const double T_25           = 298.15;        // 25 deg C => 298.15K (need to use Kelvin in conversion formula)

/* Also used in voltage to temp conversion, but are not fixed */
double voltageOut; // Vout for calculating R_2 (thermistor resistance)
double rTherm;     // thermistor resistance 
double point;      // individual temperature data points

/* Variables to be used in Fuzzy Logic Algorithm */
double tempPoints[64]; // Buffer for converted temperature points
double tempSlope;      // Slope value for one iteration of the algorithm 

/* For storing the raw hexadecimal output string of the SDADC*/
int16_t sdadc_count; 


#define SDADC_VREF                      (2.0f)
#define DAC_COUNT_INCREMENT             (132U)  // equivalent to 0.1V increment
// (0.1 / (2.0 / ((2^16) - 1)))
#define DAC_COUNT_MAX                   (65535U) // 0 to 65535 (16 bit DAC))
#define SDADC_RESULT_SIGNED_BIT_MSK     (~(0x01 << 15)) // bit mask for conversion

/*
 For the SAM C20/C21 microcontrollers, the Sigma-Delta ADC (SDADC) result register contains a 
 * 16-bit signed result, where:

 -Bit 15 (MSB) represents the sign bit (1 for negative, 0 for positive).
 -Bits [14:0] represent the ADC conversion result in 2's complement format.
 This macro is used to mask out the sign bit and extract only the magnitude of the ADC result.
 */


int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    /* Register callback function for TC3 period interrupt */
    TC3_TimerCallbackRegister(TC3_Callback_InterruptHandler, (uintptr_t)NULL);
    
    while ( true )
    {   
        SYSTICK_DelayMs(50);
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

void readSensor (void) {
    
    /* Start Timer */
    
    
    /* Start ADC Conversion*/
        SDADC_ConversionStart();
        
        for (int i = 0; i < sizeof(tempPoints); i++) {
            while(!SDADC_ConversionResultIsReady()) {
                // wait for result
            } 
            
            /* Get the initial output from SDADC */
            sdadc_count = (int16_t)SDADC_ConversionResultGet(); 
            
            /* Convert the initial output to voltage */
            voltageOut = (double)sdadc_count * SDADC_VREF / 32767; 
            
            /* Get the resistance of the thermistor from the measured voltage */
            rTherm = (voltageOut * R18) / (SUPPLY_VOLTAGE - voltageOut); 
            
            /* Calculate the temperature based off previous measurements */
            point = B_VALUE / ( log(rTherm / R_25) + (B_VALUE / T_25) );
            
            /* Add the temp point to the buffer */
            tempPoints[i] = point; 
        
        }
        /* Wait till SDADC conversion result is available */
   
}


void startTimer(void) {
    
    TC3_TimerStart();
    
    /* Set startTime to the value in TC3 */
    startTime = TC3_Timer16bitCounterGet();
    
}

void stopTimer(void) {
    /* Set endTime to the value in TC3 */
    endTime = TC3_Timer16bitCounterGet(); 
    TC3_TimerStop();
    
    if (endTime >= startTime) /* Calculate elapsedTime regularly */ 
    {
        elapsedTime = endTime - startTime; 
    }
    else /* Overflow condition */
    {
        elapsedTime = (65535 - startTime) + endTime + 1; 
    }
    
    
}

/*******************************************************************************
 End of File
*/

