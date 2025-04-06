#include "../Header/fis.h"

fis_fuzzyConstants_t fuzzyConstants = {
    .TEMP_DEV_LOWER_LIMIT  = -40.0f,
    .TEMP_DEV_UPPER_LIMIT  =  120.0f,
    .MIN_SLOPE_LIMIT       = -1.0f,
    .MAX_SLOPE_LIMIT       =  1.0f,
            
    .SIGMA_COLD_HOT        =  2.5f,
    .SIGMA_OPTIMAL         =  1.0f,
    .SIGMA_SLOPE           =  0.2f,
            
    .DEC_CENTER_2          =  -0.35f,
    .STABLE_CENTER_1       =  -0.03f,
    .STABLE_CENTER_2       =   0.03f,
    .INC_CENTER_1          =   0.35f
};

fis_fuzzyOutputs_t fuzzyOutputs = {
    .VERY_LARGE_INCREASE = -1.5f,
    .LARGE_INCREASE      = -0.75f,
    .SMALL_INCREASE      = -0.5f,
    .NO_CHANGE           = 0.0f,
    .SMALL_DECREASE      = 0.75f,
    .LARGE_DECREASE      = 1.5f
};

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

fis_fuzzyVars_t fuzzyVars; // explicit init done in function call 

/* Cannot initialize a struct with non-constant values, so this function will do so*/
void initFuzzyVars (float T_set) {
    fuzzyVars.T_set = T_set;
    fuzzyVars.coldMF_c2 = T_set - 8.0f;
    fuzzyVars.optimalMF_c1 = T_set - 0.02f;
    fuzzyVars.optimalMF_c2 = T_set + 0.02f;
    fuzzyVars.hotMF_c1 = T_set + 8.0f;
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
        diff2 = x - c2;
        exp2 = -(diff2 * diff2) / (2.0f * (sigma2 * sigma2));
        gauss2_value = expf(exp2);
    }
    else {
        gauss2_value = 1;
    }
    
    result = (gauss1_value * gauss2_value);
    
    return result;
}

void generate_gaussianLUT_dev (float *lut, float sigma1, float c1, float sigma2, float c2) {
    float step_size = 0;
    float x = 0;
    
    step_size = (fuzzyConstants.TEMP_DEV_UPPER_LIMIT - fuzzyConstants.TEMP_DEV_LOWER_LIMIT) / (LUT_SIZE_DEV - 1);
    
    for (int i = 0; i < LUT_SIZE_DEV; i++) {
        x = fuzzyConstants.TEMP_DEV_LOWER_LIMIT + (i * step_size);
        lut[i] = compute_gaussian_value(x, sigma1, c1, sigma2, c2);
    }
}

void generate_gaussianLUT_slope (float *lut, float sigma1, float c1, float sigma2, float c2) {
    float step_size = 0;
    float x = 0;
    
    step_size = (fuzzyConstants.MAX_SLOPE_LIMIT - fuzzyConstants.MIN_SLOPE_LIMIT) / (LUT_SIZE_SLOPE - 1);
    
    for (int i = 0; i < LUT_SIZE_SLOPE; i++) {
        x = fuzzyConstants.MIN_SLOPE_LIMIT + (i * step_size);
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
float evaluate_ruleset (fis_tempMembership_t tempMF, fis_slopeMembership_t slopeMF) {
    float rule_strengths[7] = {0};
    float rule_outputs[7] = {0};
    
    float numerator = 0;
    float denominator = 0;
    
    
    rule_strengths[0] = fmin(tempMF.cold, slopeMF.dec);
    rule_outputs[0] = fuzzyOutputs.VERY_LARGE_INCREASE;
    
    rule_strengths[1] = fmin(tempMF.cold, slopeMF.stable);
    rule_outputs[1] = fuzzyOutputs.LARGE_DECREASE;
    
    rule_strengths[2] = fmin(tempMF.cold, slopeMF.inc);
    rule_outputs[2] = fuzzyOutputs.SMALL_INCREASE;
    
    rule_strengths[3] = tempMF.optimal;
    rule_outputs[3] = fuzzyOutputs.NO_CHANGE;
    
    rule_strengths[4] = fmin(tempMF.hot, slopeMF.dec);
    rule_outputs[4] = fuzzyOutputs.NO_CHANGE;
    
    rule_strengths[5] = fmin(tempMF.hot, slopeMF.stable);
    rule_outputs[5] = fuzzyOutputs.SMALL_DECREASE;
    
    rule_strengths[6] = fmin(tempMF.hot, slopeMF.inc);
    rule_outputs[6] = fuzzyOutputs.LARGE_DECREASE;
    
    // Sugeno Weighted Sum
    for (int i = 0; i < 7; i++) {
        numerator += rule_strengths[i] * rule_outputs[i];
        denominator += rule_strengths[i];
    }
    
    if (denominator == 0) { // Division by 0 error
        return 0; 
    }
    
    return (numerator / denominator);
}

uint16_t defuzzify (float x) {
    float Vout = 0;
    float DAC_val = 0;
    
    // Ensure x is within expected range (-1.5 to 1.5)
    if (x > 1.5) {
        x = 1.5;
    }
    if (x < -1.5) {
        x = -1.5;
    }
    
    Vout = 1.0 - (x / 1.5);

    DAC_val = (uint16_t)((Vout / 2.5) * 1023);
    
    return DAC_val;
}
