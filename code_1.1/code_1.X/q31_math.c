#include "definitions.h"
#include <stdint.h> 
#include "q31_math.h"

//!MODULE: q31
//!
//!Provides multiply and divide functions in the Q31 format \n\n
//!
//!This module is used as a wrapper around SDADC function calls to read and store voltage samples\n\n
//!
//!The duration module defines the following functions:\n
//!    - Q31_MUL, which multiplies two int32_t numbers
//!    - Q31_DIV, which divides two int32_t numbers
//!@param None
//!@return None

/* Inline suggests that the compiler expands the function in place, avoiding function call overhead */

static struct intermediate_t intermediate;

int32_t double_to_Q31 (double value, double min_range, double max_range) {
    intermediate.scale_factor = Q31_SCALE / (max_range - min_range);
    return (int32_t)(value * intermediate.scale_factor);
}

double Q31_to_double(int32_t q31_value, double min_range, double max_range) {
    intermediate.scale_factor = (max_range - min_range) / Q31_SCALE;
    return q31_value * intermediate.scale_factor;
}

int32_t float_to_Q31 (float x) {
    return ((int32_t)((x) * Q31_SCALE));
}

/* Approximate exponential function e^x in Q31 using a 6-term Taylor series*/
int32_t Q31_exp(int32_t x) {
    if (x < -Q31_SCALE) return 0; // e^(-inf) ? 0
    if (x > Q31_SCALE) return Q31_SCALE; // e^(inf) ? 1 (max Q31)
    
    intermediate.result = Q31_SCALE;
    intermediate.term = Q31_SCALE;
    intermediate.x_n = Q31_SCALE;
    
    for (int i = 1; i <= 6; i++) {
        intermediate.x_n = Q31_mul(intermediate.x_n, x);
        intermediate.term = Q31_div(intermediate.x_n, float_to_Q31(i));
        intermediate.result += intermediate.term;
    }
    
    return intermediate.result;
}