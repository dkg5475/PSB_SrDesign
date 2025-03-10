#ifndef DAC_10BIT_H
#define DAC_10BIT_H

#include "definitions.h"
#include <stdint.h> 

/* Function prototypes (wrapper functions) */
uint16_t defuzzify_10bit (float x);


/* Global Structures */ 
    //!Define global structure for callback handler
    struct defuzzify_t {
        float Vout;
        uint16_t DAC_val;
    };
    
#endif
    

