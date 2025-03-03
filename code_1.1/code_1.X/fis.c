#include "definitions.h"
#include "convert.h"
#include "q31_math.h"

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

static struct generateGauss_t generateGauss;

int32_t generate_gaussian_lut (int32_t mean1, int32_t sigma1, int32_t mean2, int32_t sigma2) {
    // Calculate the first Gaussian: e^(-((x - mean1)^2) / (2 * sigma1^2))
    generateGauss.diff1 = generateGauss.x - mean1;
    generateGauss.exponent1 = -Q31_div(Q31_mul(generateGauss.diff1, generateGauss.diff1), (2 * Q31_mul(sigma1, sigma1)));
    generateGauss.gauss1_val = Q31_exp(generateGauss.exponent1);

    // Calculate the second Gaussian: e^(-((x - mean2)^2) / (2 * sigma2^2))
    generateGauss.diff2 = generateGauss.x - mean2;
    generateGauss.exponent2 = -Q31_div(Q31_mul(generateGauss.diff2, generateGauss.diff2), (2 * Q31_mul(sigma2, sigma2)));
    generateGauss.gauss2_val = Q31_exp(generateGauss.exponent2);

    // Combine the two Gaussian values
    return generateGauss.gauss1_val + generateGauss.gauss2_val;
}

static struct gaussianLookup_t gaussianLookup;

int32_t lookup_gaussian (int32_t x) {
    // Normalize the input value to an index in the LUT
    gaussianLookup.index = (x + (LUT_SIZE / 2)) * 10;  // Scale input to the LUT index range
    gaussianLookup.index = (gaussianLookup.index < 0) ? 0 : (gaussianLookup.index >= LUT_SIZE) ? LUT_SIZE - 1 : gaussianLookup.index;  // Ensure index is within bounds

    // Retrieve precomputed Gaussian values for both Gaussian functions from the LUT
    gaussianLookup.gauss1_value = gaussianLookup.gaussian_lut[gaussianLookup.index];  // Corresponds to the first Gaussian
    gaussianLookup.gauss2_value = gaussianLookup.gaussian_lut[gaussianLookup.index];  // Corresponds to the second Gaussian

    // Combine the two Gaussian values for gauss2mf
    return gaussianLookup.gauss1_value + gaussianLookup.gauss2_value;
}

FIS_Parameters fis; 

void initializeFIS (FIS_Parameters *fis, double T_set) {
    fis->coldLower = double_to_Q31(-40.0, -40.0, 120.0);
    fis->coldUpper = double_to_Q31(T_set - 8, -40.0, 120.0);
    fis->optimalLower = double_to_Q31(T_set - 0.02, -40.0, 120.0);
    fis->optimalUpper = double_to_Q31(T_set + 0.02, -40.0, 120.0);
    fis->hotLower = double_to_Q31(T_set + 8, -40.0, 120.0);
    fis->hotUpper = double_to_Q31(120.0, -40.0, 120.0);
}

 struct evalFIS_t evalfis;
 

int32_t evaluateFIS(int32_t temp_q31, int32_t slope_q31) {
    // Compute membership values for TempReadings using LUT
    evalfis.coldMF = lookup_gaussian(temp_q31); // Lookup Gaussian for Cold range
    evalfis.optimalMF = lookup_gaussian(temp_q31); // Lookup Gaussian for Optimal range
    evalfis.hotMF = lookup_gaussian(temp_q31); // Lookup Gaussian for Hot range

    // Compute membership values for TempSlope using LUT
    evalfis.decreasingMF = lookup_gaussian(slope_q31); // Lookup Gaussian for Decreasing slope
    evalfis.stableMF = lookup_gaussian(slope_q31);    // Lookup Gaussian for Stable slope
    evalfis.increasingMF = lookup_gaussian(slope_q31); // Lookup Gaussian for Increasing slope

    // Rule evaluation (Sugeno-style outputs)
    evalfis.powerAdjust_q31 = 0;

    // Rule-based evaluation using membership values from LUT
    if (evalfis.coldMF && evalfis.decreasingMF) {
        evalfis.powerAdjust_q31 = double_to_Q31(1.5, 0, 2);   // VeryLargeIncrease
    }
    else if (evalfis.coldMF && evalfis.stableMF) {
        evalfis.powerAdjust_q31 = double_to_Q31(0.75, 0, 2); // LargeIncrease
    }
    else if (evalfis.coldMF && evalfis.increasingMF) {
        evalfis.powerAdjust_q31 = double_to_Q31(-0.5, 0, 2); // SmallIncrease
    }
    else if (evalfis.optimalMF) {
        evalfis.powerAdjust_q31 = double_to_Q31(0.0, 0, 2);           // NoChange
    }
    else if (evalfis.hotMF && evalfis.decreasingMF) {
        evalfis.powerAdjust_q31 = double_to_Q31(0.0, 0, 2); // NoChange
    }
    else if (evalfis.hotMF && evalfis.stableMF) {
        evalfis.powerAdjust_q31 = double_to_Q31(-0.75, 0, 2);  // SmallDecrease
    }
    else if (evalfis.hotMF && evalfis.increasingMF) {
        evalfis.powerAdjust_q31 = double_to_Q31(-1.5, 0, 2); // LargeDecrease
    }

    // Return the computed power adjustment (scaled for DAC input)
    return evalfis.powerAdjust_q31;
}








