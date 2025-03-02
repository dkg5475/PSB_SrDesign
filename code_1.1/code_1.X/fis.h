#include "definitions.h"
#include <stdint.h> 
#include "q31_math.h"

/* Macros */
#define LUT_SIZE 256

/* Global structures */
#ifndef FIS_H
#define FIS_H

    typedef struct {
        int32_t coldLower, coldUpper;
        int32_t optimalLower, optimalUpper;
        int32_t hotLower, hotUpper;
    }FIS_Parameters;
    
    struct generateGauss_t {
        int32_t diff1;
        int32_t exponent1;
        int32_t gauss1_val;
        
        int32_t diff2;
        int32_t exponent2;
        int32_t gauss2_val;
        
        int32_t x;
        
    };
    
    struct gaussianLookup_t {
        int16_t index;
        int32_t gauss1_value;
        int32_t gauss2_value;
        int32_t gaussian_lut[LUT_SIZE];
    };
    
    struct evalFIS_t {
        int32_t coldMF;
        int32_t optimalMF;
        int32_t hotMF;
        
        int32_t decreasingMF;
        int32_t stableMF;
        int32_t increasingMF;
        
        int32_t powerAdjust_q31;
       
    };
    
#endif
    
/* Function prototypes*/
int32_t generate_gaussian_lut (int32_t mean1, int32_t sigma1, int32_t mean2, int32_t sigma2);
int32_t lookup_gaussian       (int32_t x);
void    initializeFIS         (FIS_Parameters *fis, double T_set);
int32_t evaluateFIS           (int32_t temp_q31, int32_t slope_q31);
    

