#include "definitions.h"
#include <stdint.h> 
#include "q31_math.h"

/* Macros */
#define LUT_SIZE 256

/* Global structures */
#ifndef FIS_H
#define FIS_H

    typedef struct {
        float coldLower, coldUpper;
        float optimalLower, optimalUpper;
        float hotLower, hotUpper;
    }FIS_Parameters;
    
    struct generateGauss_t {
        float diff1;
        float exponent1;
        float gauss1_val;
        
        float diff2;
        float exponent2;
        float gauss2_val;
        
        float x;
        
    };
    
    struct gaussianLookup_t {
        int16_t index;
        float gauss1_value;
        float gauss2_value;
        float gaussian_lut[LUT_SIZE];
    };
    
    struct evalFIS_t {
        float coldMF;
        float optimalMF;
        float hotMF;
        
        float decreasingMF;
        float stableMF;
        float increasingMF;
        
        float powerAdjust;
       
    };
    
#endif
    
/* Function prototypes*/
float generate_gaussian_lut (float mean1, float sigma1, float mean2, float sigma2);
float lookup_gaussian       (float x);
void  initializeFIS         (FIS_Parameters *fis, float T_set);
float evaluateFIS           (float temp_q31, float slope_q31);
    

