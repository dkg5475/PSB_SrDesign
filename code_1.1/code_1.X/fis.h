#ifndef FIS_H
#define FIS_H

#include "definitions.h"
#include <stdint.h> 

/* Macros */
#define LUT_SIZE_DEV   256
#define LUT_SIZE_SLOPE 201

/* Global structures */

/* Constants used repeatedly in calculations */
typedef struct {

    const float TEMP_DEV_LOWER_LIMIT;
    const float TEMP_DEV_UPPER_LIMIT;
    const float MIN_SLOPE_LIMIT;
    const float MAX_SLOPE_LIMIT;

    const float SIGMA_COLD_HOT;
    const float SIGMA_OPTIMAL;
    const float SIGMA_SLOPE;

    const float DEC_CENTER_2;
    const float STABLE_CENTER_1;
    const float STABLE_CENTER_2;
    const float INC_CENTER_1;
}fis_fuzzyConstants_t;

extern fis_fuzzyConstants_t fuzzyConstants;

typedef struct {
    float T_set; 
    
    float coldMF_c2;
    
    float optimalMF_c1;
    float optimalMF_c2;
    
    float hotMF_c1;
}fis_fuzzyVars_t;

extern fis_fuzzyVars_t fuzzyVars;

/* Struct for intermediate values used in gauss2mf function*/
typedef struct {
    float diff1;
    float exp1;
    float gauss1_value;
    
    float diff2;
    float exp2; 
    float gauss2_value;
    
    float result;
}fis_compute_gaussian_t;

extern fis_compute_gaussian_t compute_gaussian;

/* Intermediate values to be used for tempDev Gaussian LUT function */
typedef struct {
    float step_size;
    float x;
}fis_tempDev_gaussianLUT_t;

extern fis_tempDev_gaussianLUT_t tempDev_gaussianLUT;

/* Intermediate values to be used for tempSlope Gaussian LUT function */
typedef struct {
    float step_size;
    float x;
}fis_tempSlope_gaussianLUT_t;

extern fis_tempSlope_gaussianLUT_t tempSlope_gaussianLUT;

/* Intermediate values to be used for LUT interpolation */
typedef struct {
    float step_size;
    int index;
    
    float x_i;   // lower bound of LUT
    float x_ip1; // upper bound of LUT
    float y_i;   // LUT value at lower index
    float y_ip1; // LUT value at upper index
}fis_interpolation_t;

extern fis_interpolation_t interpolation;

/* Structs to hold the degrees of membership from inputs*/
typedef struct {
    float cold;
    float optimal; 
    float hot;
}fis_tempMembership_t;

extern fis_tempMembership_t tempMembership;

typedef struct {
    float dec;
    float stable;
    float inc;
}fis_slopeMembership_t;

extern fis_slopeMembership_t slopeMembership;

typedef struct {
    float rule_strengths[7];
    float rule_outputs[7];
    
    float numerator;
    float denominator;
}fis_evaluate_t;

extern fis_evaluate_t evaluate;

typedef struct {
    const float VERY_LARGE_INCREASE;
    const float LARGE_INCREASE;
    const float SMALL_INCREASE;
    const float NO_CHANGE;
    const float SMALL_DECREASE;
    const float LARGE_DECREASE;
}fis_fuzzyOutputs_t;

extern fis_fuzzyOutputs_t fuzzyOutputs;

typedef struct {
    float coldMF[LUT_SIZE_DEV];
    float optimalMF[LUT_SIZE_DEV];
    float hotMF[LUT_SIZE_DEV];
}fis_devLUTs_t;

extern fis_devLUTs_t devLUTs;

typedef struct {
    float decMF[LUT_SIZE_SLOPE];
    float stableMF[LUT_SIZE_SLOPE];
    float incMF[LUT_SIZE_SLOPE];
}fis_slopeLUTs_t;

extern fis_slopeLUTs_t slopeLUTs;

/* Function Prototypes */
void  initFuzzyVars              (float T_set);
float compute_gaussian_value     (float x, float sigma1, float c1, float sigma2, float c2);
void  generate_gaussianLUT_dev   (float *lut, float sigma1, float c1, float sigma2, float c2);
void  generate_gaussianLUT_slope (float *lut, float sigma1, float c1, float sigma2, float c2);
float interpolate_LUT            (float x, float *lut, int16_t lut_size, float x_min, float x_max);
float evaluate_ruleset           (fis_tempMembership_t tempMF, fis_slopeMembership_t slopeMF);

    
#endif
