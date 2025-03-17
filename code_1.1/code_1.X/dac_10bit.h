#ifndef DAC_10BIT_H
#define DAC_10BIT_H

#include "definitions.h"
#include <stdint.h> 

/* Function prototypes (wrapper functions) */
void defuzzify_10bit (float x);
/* Global Structures */ 
    //!Define global structure for callback handler
    typedef struct {
        float Vout;
        uint16_t DAC_val;
    }dac_10bit_defuzzify_t;
    
    extern dac_10bit_defuzzify_t defuzzify;
    
#endif
    

