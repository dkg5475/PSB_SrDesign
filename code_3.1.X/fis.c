#include "fis.h"
#include <math.h>

// Values that vary based off the current setpoint
// Actual data gets written to these in the initFuzzyVars function
volatile float T_set      = 0;
volatile float COLD_C2    = 0;
volatile float OPTIMAL_C1 = 0;
volatile float OPTIMAL_C2 = 0;
volatile float HOT_C1     = 0;


fis_tempMembership_t tempMembership = {
    .cold = 0,
    .optimal = 0,
    .hot = 0
};

fis_slopeMembership_t slopeMembership = {
    .dec = 0,
    .stable = 0,
    .inc = 0
};

// Initialization of LUTs to be used during the algorithm

fis_devLUTs_t devLUTs = {
    .coldMF = {0},
    .optimalMF = {0},
    .hotMF = {0} 
};

fis_slopeLUTs_t slopeLUTs = {
    .decMF = {0},     
    .stableMF = {0},
    .incMF = {0}
};

// Initialization of variable values to be used later on 
void initFuzzyVars (float setpt) {   
    T_set = setpt;
    COLD_C2 = T_set - 8.0f;
    OPTIMAL_C1 = T_set - 0.02f;
    OPTIMAL_C2 = T_set + 0.02f;
    HOT_C1 = T_set + 8.0f;
}

float compute_gaussian_value (float x, float sigma1, float c1, float sigma2, float c2) {
    float diff1 = 0;
    float exp1 = 0;
    float gauss1_value = 0;
    
    float diff2 = 0;
    float exp2 = 0;
    float gauss2_value = 0;
    
    float result = 0;
    
    if (x <= c1) {
        diff1 = x - c1;
        exp1 = -(diff1 * diff1) / (2.0f * (sigma1 * sigma1));
        gauss1_value = expf(exp1);
    }
    else {
        gauss1_value = 1;
    }
    
    if (x <= c2) {
        gauss2_value = 1;
    }
    else {
        diff2 = x - c2;
        exp2 = -(diff2 * diff2) / (2.0f * (sigma2 * sigma2));
        gauss2_value = expf(exp2);
    }
    
    result = (gauss1_value * gauss2_value);
    
    return result;
}

void generate_gaussianLUT_dev (float *lut, float sigma1, float c1, float sigma2, float c2) {
    float step_size = 0;
    float x = 0;
    
    step_size = (TEMP_UPPER_LIMIT - TEMP_LOWER_LIMIT) / (LUT_SIZE_DEV - 1);
    
    for (int i = 0; i < LUT_SIZE_DEV; i++) {
        x = TEMP_LOWER_LIMIT + (i * step_size);
        lut[i] = compute_gaussian_value(x, sigma1, c1, sigma2, c2);
    }
}


/* Linear interpolation function */
/* If x is the input value for which we need an interpolated LUT value, and it falls between */
/* two LUT indices x_i and x_i+1 (x_ip1 in the code), then the corresponding output y can be */
/* approximated as y = y_i + ( (x - x_i) * (y_ip1 - y_i) ) / (x_ip1 - x_i) */

float interpolate_LUT (float x, float *lut, int16_t lut_size, float x_min, float x_max) {
    float step_size = 0;
    int index = 0;
    
    float x_i = 0;   // lower bound of LUT
    float x_ip1 = 0; // upper bound of LUT
    float y_i = 0;   // LUT value at lower index
    float y_ip1 = 0; // LUT value at upper index
    
    
    step_size = (x_max - x_min) / (lut_size - 1);
    index = (int)((x - x_min) / step_size);
    
    if (index < 0) {
        return lut[0];
    }
    
    if (index >= (lut_size - 1)) {
        return lut[lut_size - 1];
    }
    
    x_i = x_min + (index * step_size);
    x_ip1 = x_min + ((index + 1) * step_size);
    
    y_i = lut[index];
    y_ip1 = lut[index + 1];
    
    return y_i + ((x - x_i) * (y_ip1 - y_i)) / (x_ip1 - x_i);
};

/* Fuzzy logic rule for Type-2 Sugeno are evaluted using Fuzzy AND operator, or the minimum of two values */
/* Output = Sum(Rule Strength * Rule Output) / Sum(Rule Strength) */
float evaluate_ruleset (fis_tempMembership_t tempMF) {
    float rule_strengths[3] = {0};
    float rule_outputs[3] = {0};
    
    float numerator = 0;
    float denominator = 0;
    
    
    rule_strengths[0] = tempMF.cold;
    rule_outputs[0] = LARGE_INCREASE;
    
    rule_strengths[1] = tempMF.optimal;
    rule_outputs[1] = NO_CHANGE;
   
    rule_strengths[2] = tempMF.hot;
    rule_outputs[2] = LARGE_DECREASE;
    
    // Sugeno Weighted Sum
    for (int i = 0; i < 3; i++) {
        numerator += rule_strengths[i] * rule_outputs[i];
        denominator += rule_strengths[i];
    }
    
    if (denominator == 0) { // Division by 0 error
        return 0; 
    }
    
    return (numerator / denominator);
}

uint16_t defuzzify(float x) {
    // Clamp x to [-0.95, 0.95]
    if (x > 2.5) {
        x = 2.5;
    } 
    
    if (x < 0.6) {
        x = 0.6;
    }

    /* 
    // Scale to 10-bit DAC value [0, 1023]
    uint16_t dac_val = (uint16_t)(roundf((x * 1023.0f) / 2.5f));
    if (dac_val < 246) {
        dac_val = 246;
    }
    if (dac_val > 1023) {
        dac_val = 1023;
    }
    */
    
    // Scale to 14-bit DAC value [0, 16383]
    uint16_t dac_val = (uint16_t)(roundf((x * 16383.0f) / 2.5f));
    if (dac_val < 3932) {
        dac_val = 3932;
    }
    if (dac_val > 16383) {
        dac_val = 16383;
    }
    
    return dac_val;
}


