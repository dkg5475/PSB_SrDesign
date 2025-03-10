#include "definitions.h"
#include "convert.h"
#include <math.h>
#include "fis.h"

//!MODULE: fis
//!
//!Functions used for the Fuzzy Inference System FIS \n\n
//!
//!This module is used to calculate the gaussian lookup-tables (LUTs) and achieve an output based on the ruleset \n\n
//!
//!The duration module defines the following functions:\n
//!    - 
//!@param None
//!@return None

struct fuzzyConstants_t fuzzyConstants = {
    .LUT_SIZE_DEV          =  256,
    .LUT_SIZE_SLOPE        =  201,
    
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

struct fuzzyOutputs_t fuzzyOutputs = {
    .VERY_LARGE_INCREASE = -1.5f,
    .LARGE_INCREASE      = -0.75f,
    .SMALL_INCREASE      = -0.5f,
    .NO_CHANGE           = 0.0f,
    .SMALL_DECREASE      = 0.75f,
    .LARGE_DECREASE      = 1.5f
};

static struct compute_gaussian_t compute_gaussian;

float compute_gaussian_value (float x, float sigma1, float c1, float sigma2, float c2) {
    if (x <= c1) {
        compute_gaussian.diff1 = x - c1;
        compute_gaussian.exp1 = -(compute_gaussian.diff1 * compute_gaussian.diff1) / (2.0f * (sigma1 * sigma1));
        compute_gaussian.gauss1_value = expf(compute_gaussian.exp1);
    }
    else {
        compute_gaussian.gauss1_value = 1;
    }
    
    if (x <= c2) {
        compute_gaussian.diff2 = x - c2;
        compute_gaussian.exp2 = -(compute_gaussian.diff2 * compute_gaussian.diff2) / (2.0f * (sigma2 * sigma2));
        compute_gaussian.gauss2_value = expf(compute_gaussian.exp2);
    }
    else {
        compute_gaussian.gauss2_value = 1;
    }
    
    compute_gaussian.result = (compute_gaussian.gauss1_value * compute_gaussian.gauss2_value);
    
    return compute_gaussian.result;
}

static struct tempDev_gaussianLUT_t tempDev_gaussianLUT;

void generate_gaussianLUT_dev (float *lut, float sigma1, float c1, float sigma2, float c2) {
    tempDev_gaussianLUT.step_size = (fuzzyConstants.TEMP_DEV_UPPER_LIMIT - fuzzyConstants.TEMP_DEV_LOWER_LIMIT) / (fuzzyConstants.LUT_SIZE_DEV - 1);
    
    for (int i = 0; i < fuzzyConstants.LUT_SIZE_DEV; i++) {
        tempDev_gaussianLUT.x = fuzzyConstants.TEMP_DEV_LOWER_LIMIT + (i * tempDev_gaussianLUT.step_size);
        lut[i] = compute_gaussian_value(tempDev_gaussianLUT.x, sigma1, c1, sigma2, c2);
    }
}

static struct tempSlope_gaussianLUT_t tempSlope_gaussianLUT;

void generate_gaussianLUT_slope (float *lut, float sigma1, float c1, float sigma2, float c2) {
    tempSlope_gaussianLUT.step_size = (fuzzyConstants.MAX_SLOPE_LIMIT - fuzzyConstants.MIN_SLOPE_LIMIT) / (fuzzyConstants.LUT_SIZE_SLOPE - 1);
    
    for (int i = 0; i < fuzzyConstants.LUT_SIZE_SLOPE; i++) {
        tempSlope_gaussianLUT.x = fuzzyConstants.MIN_SLOPE_LIMIT + (i * tempSlope_gaussianLUT.step_size);
        lut[i] = compute_gaussian_value(tempSlope_gaussianLUT.x, sigma1, c1, sigma2, c2);
    }
}

/* Linear interpolation function */
/* If x is the input value for which we need an interpolated LUT value, and it falls between */
/* two LUT indices x_i and x_i+1 (x_ip1 in the code), then the corresponding output y can be */
/* approximated as y = y_i + ( (x - x_i) * (y_ip1 - y_i) ) / (x_ip1 - x_i) */

static struct interpolation_t interpolation;

float interpolate_LUT (float x, float *lut, int16_t lut_size, float x_min, float x_max) {
    interpolation.step_size = (x_max - x_min) / (lut_size - 1);
    interpolation.index = (int)((x - x_min) / interpolation.step_size);
    
    if (interpolation.index < 0) {
        return lut[0];
    }
    
    if (interpolation.index >= (lut_size - 1)) {
        return lut[lut_size - 1];
    }
    
    interpolation.x_i = x_min + (interpolation.index * interpolation.step_size);
    interpolation.x_ip1 = x_min + ((interpolation.index + 1) * interpolation.step_size);
    
    interpolation.y_i = lut[interpolation.index];
    interpolation.y_ip1 = lut[interpolation.index + 1];
    
    return interpolation.y_i + ((x - interpolation.x_i) * (interpolation.y_ip1 - interpolation.y_i)) / (interpolation.x_ip1 - interpolation.x_i);
}

TempMembership_t  TempMembership;
SlopeMembership_t SlopeMembership;
struct evaluate_t evaluate;

/* Fuzzy logic rule for Type-2 Sugeno are evaluted using Fuzzy AND operator, or the minimum of two values */
/* Output = Sum(Rule Strength * Rule Output) / Sum(Rule Strength) */
float evaluate_ruleset (TempMembership_t tempMF, SlopeMembership_t slopeMF) {
    evaluate.rule_strengths[0] = fmin(tempMF.cold, slopeMF.dec);
    evaluate.rule_outputs[0] = fuzzyOutputs.VERY_LARGE_INCREASE;
    
    evaluate.rule_strengths[1] = fmin(tempMF.cold, slopeMF.stable);
    evaluate.rule_outputs[1] = fuzzyOutputs.LARGE_DECREASE;
    
    evaluate.rule_strengths[2] = fmin(tempMF.cold, slopeMF.inc);
    evaluate.rule_outputs[2] = fuzzyOutputs.SMALL_INCREASE;
    
    evaluate.rule_strengths[3] = tempMF.optimal;
    evaluate.rule_outputs[3] = fuzzyOutputs.NO_CHANGE;
    
    evaluate.rule_strengths[4] = fmin(tempMF.hot, slopeMF.dec);
    evaluate.rule_outputs[4] = fuzzyOutputs.NO_CHANGE;
    
    evaluate.rule_strengths[5] = fmin(tempMF.hot, slopeMF.stable);
    evaluate.rule_outputs[5] = fuzzyOutputs.SMALL_DECREASE;
    
    evaluate.rule_strengths[6] = fmin(tempMF.hot, slopeMF.inc);
    evaluate.rule_outputs[6] = fuzzyOutputs.LARGE_DECREASE;
    
    evaluate.numerator = 0;
    evaluate.denominator = 0;
    
    // Sugeno Weighted Sum
    for (int i = 0; i < 7; i++) {
        evaluate.numerator += evaluate.rule_strengths[i] * evaluate.rule_outputs[i];
        evaluate.denominator += evaluate.rule_strengths[i];
    }
    
    if (evaluate.denominator == 0) { // Division by 0 error
        return 0; 
    }
    
    return (evaluate.numerator / evaluate.denominator);
}









