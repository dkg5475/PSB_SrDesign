#include "../Header/fis2.h"

// Values that vary based off the current setpoint
// Actual data gets written to these in the initFuzzyVars function
volatile float T_set2 = 0;

volatile float VERY_COLD_C22 = 0;

volatile float COLD_C12 = 0;
volatile float COLD_C22 = 0;

volatile float OPTIMAL_C12 = 0;
volatile float OPTIMAL_C22 = 0;

volatile float HOT_C12 = 0;
volatile float HOT_C22 = 0;

volatile float VERY_HOT_C12 = 0;


fis_tempMembership2_t tempMembership2 = {
    .very_cold = 0,
    .cold = 0,
    .optimal = 0,
    .hot = 0,
    .very_hot = 0
};


// Initialization of LUTs to be used during the algorithm

fis_devLUTs2_t devLUTs2 = {
    .veryColdMF = {0},
    .coldMF = {0},
    .optimalMF = {0},
    .hotMF = {0},
    .veryHotMF = {0}
};


// Initialization of variable values to be used later on 
void initFuzzyVars2 (float setpt) {   
    T_set2 = setpt;
    
    //VERY_COLD_C22 = T_set2 - 8.0f;
    
    //COLD_C12 = T_set2 - 8.0f;
    //COLD_C22 = T_set2 - 1.0f;
    
    //OPTIMAL_C12 = T_set2 - 0.02f;
    //OPTIMAL_C22 = T_set2 + 0.02f;
    
    //HOT_C12 = T_set2 + 1.0f;
    //HOT_C22 = T_set2 + 8.0f;
    
    //VERY_HOT_C12 = T_set2 + 8.0f;
    
    T_set2 = setpt;
    COLD_C22 = T_set2 - 8.0f;
    OPTIMAL_C12 = T_set2 - 0.02f;
    OPTIMAL_C22 = T_set2 + 0.02f;
    HOT_C12 = T_set2 + 8.0f;
}

float compute_gaussian_value2 (float x, float sigma1, float c1, float sigma2, float c2) {
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

void generate_gaussianLUT_dev2 (float *lut, float sigma1, float c1, float sigma2, float c2) {
    float step_size = 0;
    float x = 0;
    
    step_size = (TEMP_UPPER_LIMIT2 - TEMP_LOWER_LIMIT2) / (LUT_SIZE_DEV2 - 1);
    
    for (int i = 0; i < LUT_SIZE_DEV2; i++) {
        x = TEMP_LOWER_LIMIT2 + (i * step_size);
        lut[i] = compute_gaussian_value2(x, sigma1, c1, sigma2, c2);
    }
}

/* Linear interpolation function */
/* If x is the input value for which we need an interpolated LUT value, and it falls between */
/* two LUT indices x_i and x_i+1 (x_ip1 in the code), then the corresponding output y can be */
/* approximated as y = y_i + ( (x - x_i) * (y_ip1 - y_i) ) / (x_ip1 - x_i) */

float interpolate_LUT2 (float x, float *lut, int16_t lut_size, float x_min, float x_max) {
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
float evaluate_ruleset2(fis_tempMembership2_t tempMF) {
    float rule_strengths[2] = {0};
    float rule_outputs[2] = {0};

    float numerator = 0;
    float denominator = 0;

    // Apply rules for each temperature region
    //rule_strengths[0] = tempMF.very_cold;
    //rule_outputs[0] = LARGE_INCREASE2;

    //rule_strengths[1] = tempMF.cold;
    //rule_outputs[1] = SMALL_INCREASE2;

    //rule_strengths[2] = tempMF.optimal;
    //rule_outputs[2] = NO_CHANGE2;

    //rule_strengths[3] = tempMF.hot;
    //rule_outputs[3] = SMALL_DECREASE2;

    //rule_strengths[4] = tempMF.very_hot;
    //rule_outputs[4] = LARGE_DECREASE2;
    
    rule_strengths[0] = tempMF.cold;
    rule_outputs[0] = LARGE_INCREASE2;

    rule_strengths[0] = tempMF.optimal;
    rule_outputs[0] = NO_CHANGE2;

    rule_strengths[0] = tempMF.hot;
    rule_outputs[0] = LARGE_DECREASE2;

    // Sugeno Weighted Sum
    for (int i = 0; i < 3; i++) {
        numerator += rule_strengths[i] * rule_outputs[i];
        denominator += rule_strengths[i];
    }

    // Avoid division by zero
    if (denominator == 0) {
        return 0;
    }

    return (numerator / denominator);
}


uint16_t defuzzify2(float x) {
    // Clamp x to [-0.7, 0.7]
    if (x > LARGE_INCREASE2) {
        x = LARGE_INCREASE2;
    } else if (x < LARGE_DECREASE2) {
        x = LARGE_DECREASE2;
    }

    // Normalize x to [0.0, 1.0] from [-0.95, 0.95]
    float normalized = (x - LARGE_DECREASE2) / (LARGE_INCREASE2 - LARGE_DECREASE2);  // (x + 0.95) / 1.9

    // Scale to 10-bit DAC value [0, 1023]
    uint16_t dac_val = (uint16_t)roundf(normalized * 1023.0f);

    return dac_val;
}


