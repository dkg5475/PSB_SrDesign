#include "definitions.h"
#include "convert.h"
#include <math.h>
#include <stdint.h>
#include "dac_10bit.h"

//!MODULE: dac_10bit
//!
//!Used to defuzzify the output from FIS and write to the internal 10-bit DAC (14 bits with dithering) \n\n
//!
//!This module is used as a wrapper around DAC function calls and defuzzification \n\n
//!
//!The duration module defines the following functions:\n
//!    
//!@param None
//!@return None


/* Converts the output of the FIS to a DAC output */
/* Maps fuzzy output to voltage range (2V at min heating, 0V at max heating) */
/* Convert voltage to 14-bit DAC value (0-16383 for 0-2V range) */
/* Voltage is set to 0 to 1023 for 10-bit DAC range*/

uint16_t defuzzify_10bit (float x) {
    float Vout = 0;
    float DAC_val = 0;
    
    // Ensure x is within expected range (-1.5 to 1.5)
    if (x > 1.5) {
        x = 1.5;
    }
    if (x < -1.5) {
        x = -1.5;
    }
    
    Vout = 1.0 - (x / 1.5);

    DAC_val = (uint16_t)((Vout / 2.0) * 1023);
    
    return DAC_val;
}




