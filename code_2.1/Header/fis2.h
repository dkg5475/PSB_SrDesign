#ifndef FIS2_H
#define	FIS2_H

#include <stdint.h> 
#include <math.h>

/* Macros */
#define LUT_SIZE_DEV2   512U

// Temperature bounds
#define TEMP_LOWER_LIMIT2   -40.0f
#define TEMP_UPPER_LIMIT2    120.0f

// Standard deviation values used repeatedly
#define STD_DEV_VCOLD_VHOT2      2.5f
#define STD_DEV_COLD_HOT2        2.0f
#define STD_DEV_OPTIMAL2         1.0f

// Voltage adjustments used in rule-firing function
#define LARGE_INCREASE2              0.900f
#define SMALL_INCREASE2              0.450f
#define NO_CHANGE2                   0.000f
#define SMALL_DECREASE2             -0.450f
#define LARGE_DECREASE2             -0.900f

// Some important global values that change 
extern volatile float T_set2;

extern volatile float VERY_COLD_C22;

extern volatile float COLD_C12;
extern volatile float COLD_C22;

extern volatile float OPTIMAL_C12;
extern volatile float OPTIMAL_C22;

extern volatile float HOT_C12;
extern volatile float HOT_C22;

extern volatile float VERY_HOT_C12;


/* Structs to hold the degrees of membership from inputs*/
typedef struct {
    float very_cold;
    float cold;
    float optimal; 
    float hot;
    float very_hot;
}fis_tempMembership2_t;

extern fis_tempMembership2_t tempMembership2;

typedef struct {
    float veryColdMF[LUT_SIZE_DEV2];
    float coldMF[LUT_SIZE_DEV2];
    float optimalMF[LUT_SIZE_DEV2];
    float hotMF[LUT_SIZE_DEV2];
    float veryHotMF[LUT_SIZE_DEV2];
}fis_devLUTs2_t;

extern fis_devLUTs2_t devLUTs2;




/* Function Prototypes */
void     initFuzzyVars2              (float T_set);
float    compute_gaussian_value2     (float x, float sigma1, float c1, float sigma2, float c2);
void     generate_gaussianLUT_dev2   (float *lut, float sigma1, float c1, float sigma2, float c2);
float    interpolate_LUT2            (float x, float *lut, int16_t lut_size, float x_min, float x_max);
float    evaluate_ruleset2           (fis_tempMembership2_t tempMF);
uint16_t defuzzify2                  (float x);
uint16_t defuzzify_16                (float x);


#endif	/* FIS2_H */

