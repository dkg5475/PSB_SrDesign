#include "definitions.h"
#include "convert.h"
#include <math.h>
#include <stdint.h>
#include "dac_10bit.h"

//!MODULE: convert
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

struct defuzzify_t defuzzify;

void defuzzify_10bit (float x) {
    // Ensure x is within expected range (-1.5 to 1.5)
    if (x > 1.5) {
        x = 1.5;
    }
    if (x < -1.5) {
        x = -1.5;
    }
    
    defuzzify.Vout = 1.0 - (x / 1.5);

    defuzzify.DAC_val = (uint16_t)((defuzzify.Vout / 2.0) * 16383);

}




