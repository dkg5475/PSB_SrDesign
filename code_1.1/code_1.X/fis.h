#ifndef FIS_H
#define FIS_H

#include "definitions.h"
#include <stdint.h> 

/* Macros */
#define LUT_SIZE_DEV   256
#define LUT_SIZE_SLOPE 201

/* Global structures */

/* Constants used repeatedly in calculations */
struct fuzzyConstants_t {

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
};

extern struct fuzzyConstants_t fuzzyConstants;

struct fuzzyVars_t {
    float T_set; 
    
    float coldMF_c2;
    
    float optimalMF_c1;
    float optimalMF_c2;
    
    float hotMF_c1;
};

extern struct fuzzyVars_t fuzzyVars;

/* Struct for intermediate values used in gauss2mf function*/
struct compute_gaussian_t {
    float diff1;
    float exp1;
    float gauss1_value;
    
    float diff2;
    float exp2; 
    float gauss2_value;
    
    float result;
};

extern struct compute_gaussian_t compute_gaussian;

/* Intermediate values to be used for tempDev Gaussian LUT function */
struct tempDev_gaussianLUT_t {
    float step_size;
    float x;
};

extern struct tempDev_gaussianLUT_t tempDev_gaussianLUT;

/* Intermediate values to be used for tempSlope Gaussian LUT function */
struct tempSlope_gaussianLUT_t {
    float step_size;
    float x;
};

extern struct tempSlope_gaussianLUT_t tempSlope_gaussianLUT;

/* Intermediate values to be used for LUT interpolation */
struct interpolation_t {
    float step_size;
    int index;
    
    float x_i;   // lower bound of LUT
    float x_ip1; // upper bound of LUT
    float y_i;   // LUT value at lower index
    float y_ip1; // LUT value at upper index
};

extern struct interpolation_t interpolation;

/* Structs to hold the degrees of membership from inputs*/
typedef struct {
    float cold;
    float optimal; 
    float hot;
}tempMembership_t;

extern tempMembership_t tempMembership;

typedef struct {
    float dec;
    float stable;
    float inc;
}slopeMembership_t;

extern slopeMembership_t slopeMembership;

struct evaluate_t {
    float rule_strengths[7];
    float rule_outputs[7];
    
    float numerator;
    float denominator;
};

extern struct evaluate_t evaluate;

struct fuzzyOutputs_t {
    const float VERY_LARGE_INCREASE;
    const float LARGE_INCREASE;
    const float SMALL_INCREASE;
    const float NO_CHANGE;
    const float SMALL_DECREASE;
    const float LARGE_DECREASE;
};

extern struct fuzzyOutputs_t fuzzyOutputs;

struct devLUTs_t {
    float coldMF[LUT_SIZE_DEV];
    float optimalMF[LUT_SIZE_DEV];
    float hotMF[LUT_SIZE_DEV];
};

extern struct devLUTs_t devLUTs;

struct slopeLUTs_t {
    float decMF[LUT_SIZE_SLOPE];
    float stableMF[LUT_SIZE_SLOPE];
    float incMF[LUT_SIZE_SLOPE];
};

extern struct slopeLUTs_t slopeLUTs;

/* Function Prototypes */
void  initFuzzyVars              (float T_set);
float compute_gaussian_value     (float x, float sigma1, float c1, float sigma2, float c2);
void  generate_gaussianLUT_dev   (float *lut, float sigma1, float c1, float sigma2, float c2);
void  generate_gaussianLUT_slope (float *lut, float sigma1, float c1, float sigma2, float c2);
float interpolate_LUT            (float x, float *lut, int16_t lut_size, float x_min, float x_max);
float evaluate_ruleset           (tempMembership_t tempMF, slopeMembership_t slopeMF);

    
#endif
