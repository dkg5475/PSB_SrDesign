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

static struct generateGauss_t generateGauss;

float generate_gaussian_lut(float x, float mean1, float sigma1, float mean2, float sigma2) {
    // Calculate the first Gaussian: e^(-((x - mean1)^2) / (2 * sigma1^2))
    float diff1 = x - mean1;
    float exponent1 = -((diff1 * diff1) / (2.0f * sigma1 * sigma1));
    float gauss1_val = expf(exponent1);

    // Calculate the second Gaussian: e^(-((x - mean2)^2) / (2 * sigma2^2))
    float diff2 = x - mean2;
    float exponent2 = -((diff2 * diff2) / (2.0f * sigma2 * sigma2));
    float gauss2_val = expf(exponent2);

    // Combine the two Gaussian values
    return gauss1_val + gauss2_val;
}


static struct gaussianLookup_t gaussianLookup;

float lookup_gaussian (float x) {
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

void initializeFIS(FIS_Parameters *fis, float T_set) {
    fis->coldLower = -40.0f;
    fis->coldUpper = T_set - 8.0f;
    fis->optimalLower = T_set - 0.02f;
    fis->optimalUpper = T_set + 0.02f;
    fis->hotLower = T_set + 8.0f;
    fis->hotUpper = 120.0f;
}

 struct evalFIS_t evalfis;
 

float evaluateFIS(float temp, float slope) {
    // Compute membership values for TempReadings using LUT
    evalfis.coldMF = lookup_gaussian(temp);    // Lookup Gaussian for Cold range
    evalfis.optimalMF = lookup_gaussian(temp); // Lookup Gaussian for Optimal range
    evalfis.hotMF = lookup_gaussian(temp);     // Lookup Gaussian for Hot range

    // Compute membership values for TempSlope using LUT
    evalfis.decreasingMF = lookup_gaussian(slope); // Lookup Gaussian for Decreasing slope
    evalfis.stableMF = lookup_gaussian(slope);     // Lookup Gaussian for Stable slope
    evalfis.increasingMF = lookup_gaussian(slope); // Lookup Gaussian for Increasing slope

    // Rule evaluation (Sugeno-style outputs)
    evalfis.powerAdjust = 0.0f;

    // Rule-based evaluation using membership values from LUT
    if (evalfis.coldMF && evalfis.decreasingMF) {
        evalfis.powerAdjust = 1.5f;   // VeryLargeIncrease
    }
    else if (evalfis.coldMF && evalfis.stableMF) {
        evalfis.powerAdjust = 0.75f;  // LargeIncrease
    }
    else if (evalfis.coldMF && evalfis.increasingMF) {
        evalfis.powerAdjust = -0.5f;  // SmallIncrease
    }
    else if (evalfis.optimalMF) {
        evalfis.powerAdjust = 0.0f;   // NoChange
    }
    else if (evalfis.hotMF && evalfis.decreasingMF) {
        evalfis.powerAdjust = 0.0f;   // NoChange
    }
    else if (evalfis.hotMF && evalfis.stableMF) {
        evalfis.powerAdjust = -0.75f; // SmallDecrease
    }
    else if (evalfis.hotMF && evalfis.increasingMF) {
        evalfis.powerAdjust = -1.5f;  // LargeDecrease
    }

    // Return the computed power adjustment (direct floating-point value)
    return evalfis.powerAdjust;
}









