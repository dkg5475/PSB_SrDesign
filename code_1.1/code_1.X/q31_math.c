#include "definitions.h"
#include <stdint.h> 
#include "q31_math.h"

//!MODULE: q31
//!
//!Provides multiply and divide functions in the Q31 format \n\n
//!
//!This module provides functions for Q31 fixed-point arithmetic \n\n
//!
//!The duration module defines the following functions:\n
//!    - Q31_MUL, which multiplies two int32_t numbers\n
//!    - Q31_DIV, which divides two int32_t numbers\n
//!    - double_to_Q31, which converts a double type value to Q31 format\n
//!    - Q31_to_double, which converts a Q31 type value to double\n
//!    - float_to_Q31, which converts a float type value to Q31\n
//!
//!    - Q31 is a signed 32-bit fixed-point format where:\n
//!       - 1 bit is for sign (MSB))\n
//!       - 31 bits are for fractional values\n
//!       - Since the sign bit is used, the range of numbers in Q31 is -1.0 <= x < 1.0\n
//!       - Numerically, this means -2^31 <= x <= 2^31\n
//!
//!    - Since Q31 uses integers, mathematical operations must be scaled properly to \n
//!      prevent overflow and maintain precision.\n\n
//! 
//!    - Multiplication in Q31 follows the form of result = ( (A * B) / 2^31) \n
//!    - Since multiplying two Q31 numbers produces a Q62 result (32-bit × 32-bit = 64-bit), \n
//!    - we must right shift by 31 to bring it back to Q31 format.\n
//!    - The function implementation for multiplication ensures that 0.5 * 0.5 = 0.25 (correct scaling) and 
//!    - 0.999 * 0.999 = 0.998, handling overflow\n\n
//!
//!    - Division in Q31 follows to form:  result = ( (A * 2^31) / B) \n
//!    - Since dividing two Q31 numbers results in a Q31 output, we must left shift by 31 before dividing. \n
//!    - function implementation for division ensures 0.5 / 2 = 0.25 (correct scaling) \n
//!    - and handles divide by zero safety.\n\n
//!
//!    - Conversion Between Q31 and Floating-Point \n
//!    - Since microcontrollers often work with floating-point numbers for ease of understanding,
//!    - conversion functions are useful.\n
//!    - Conversion from double to Q31 looks like result = (double * 2^31) \n
//!    - Conversion from Q31 to double looks like result = (Q31 * 2^-31) \n\n
//!    
//!    - Exponential Function in Q31
//!    - Since exponential functions (e^x) are non-linear, we approximate it using a Taylor Series. 
//!    - For embedded systems, we limit the terms to 6 to save computation time. 
//!
//!
//!
//!
//!@param None
//!@return None




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