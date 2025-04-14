#ifndef FIS_H
#define	FIS_H

#include <stdint.h> 
#include <math.h>

/* Macros */
#define LUT_SIZE_DEV   512U
#define LUT_SIZE_SLOPE 512U

// Temperature bounds
#define TEMP_LOWER_LIMIT   -40.0f
#define TEMP_UPPER_LIMIT    120.0f


// Standard deviation values used repeatedly
#define STD_DEV_COLD_HOT               2.5f
#define STD_DEV_OPTIMAL                1.0f

// Center values used repeatedly
#define DEC_C2             -0.35f
#define STABLE_C1          -0.03f
#define STABLE_C2          -0.03f
#define INC_C1              0.35f

// Voltage adjustments used in rule-firing function
#define LARGE_INCREASE       0.475f
#define SMALL_INCREASE       0.2375f
#define NO_CHANGE            0.000f
#define SMALL_DECREASE      -0.2375f
#define LARGE_DECREASE      -0.475f

// Some important global values that change 
extern volatile float T_set;
extern volatile float COLD_C2;
extern volatile float OPTIMAL_C1;
extern volatile float OPTIMAL_C2;
extern volatile float HOT_C1;

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
void     initFuzzyVars              (float T_set);
float    compute_gaussian_value     (float x, float sigma1, float c1, float sigma2, float c2);
void     generate_gaussianLUT_dev   (float *lut, float sigma1, float c1, float sigma2, float c2);
void     generate_gaussianLUT_slope (float *lut, float sigma1, float c1, float sigma2, float c2);
float    interpolate_LUT            (float x, float *lut, int16_t lut_size, float x_min, float x_max);
float    evaluate_ruleset           (fis_tempMembership_t tempMF);
uint16_t defuzzify                  (float x);
uint16_t defuzzify_16               (float x);


#endif	/* FIS_H */

