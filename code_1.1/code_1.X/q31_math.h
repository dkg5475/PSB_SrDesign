#include "definitions.h"
#include <stdint.h> 

/* Macros for Q31 multiplication and division*/
#define Q31_SCALE (2147483648)  // 2^31 for fixed-point scaling

/* Function prototypes*/
inline int32_t Q31_mul (int32_t a, int32_t b);
inline int32_t Q31_div (int32_t a, int32_t b);
int32_t double_to_Q31  (double value, double min_range, double max_range);
double  Q31_to_double  (int32_t q31_value, double min_range, double max_range);
int32_t float_to_Q31   (float x);
int32_t Q31_exp        (int32_t x);

/* Global structures */
#ifndef Q31_MATH_H
#define Q31_MATH_H

    struct intermediate_t
    {
        double scale_factor;
        int32_t result; 
        int32_t term; 
        int32_t x_n;
    };
    
#endif

/* Inline functions defined here to avoid linker issues */
    
inline int32_t Q31_mul(int32_t a, int32_t b) {
    return (int32_t)(((int64_t)a * b) >> 31);
}

inline int32_t Q31_div(int32_t a, int32_t b) {
    if (b == 0) { // handle divide by 0 overflow
        return (a >= 0) ? INT32_MAX : INT32_MIN;
    }
    return (int32_t)(((int64_t)a << 31) / b);
}
/* *****************************************************************************
 End of File
 */

