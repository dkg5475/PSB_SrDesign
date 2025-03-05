#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

/*
#define LUT_SIZE 256      // Number of LUT entries
#define X_MIN -40.0f      // Minimum x value (e.g., temperature)
#define X_MAX 120.0f      // Maximum x value

#define COLD_LOWER_LIMIT  -40.0f
#define HOT_UPPER_LIMIT    120.0f
#define MIN_SLOPE_LIMIT   -1.0f
#define MAX_SLOPE_LIMIT    1.0f

#define SIGMA_COLD         2.5f
#define SIGMA_OPTIMAL      1.0f
#define SIGMA_HOT          2.5f

#define SIGMA_SLOPE        0.2f
*/

const int16_t  LUT_SIZE_1         =  256;
const int16_t  LUT_SIZE_2         =  64;
const int16_t  LUT_SIZE_3         =  32;
const float   X_MIN              = -40.0f;
const float   X_MAX              =  120.0f;

const float COLD_LOWER_LIMIT   = -40.0f;
const float HOT_UPPER_LIMIT    =  120.0f;
const float MIN_SLOPE_LIMIT    = -1.0f;
const float MAX_SLOPE_LIMIT    =  1.0f;

const float SIGMA_COLD_HOT     =  2.5f;
const float SIGMA_OPTIMAl      =  1.0f;
const float SIGMA_SLOPE        =  0.2f;

const float DEC_CENTER_2        = -0.35f;
const float STABLE_CENTER_1     = -0.03f;
const float STABLE_CENTER_2     =  0.03f;
const float INCREASING_CENTER_1 =  0.35f;




// Helper function: computes the combined Gaussian value for a given x
float compute_gaussian_value(float x, float sigma1, float c1, float sigma2, float c2) {
    float diff1; 
    float exp1;
    float gauss1_value = 0.0f;

    float diff2;
    float exp2;
    float gauss2_value = 0.0f;

    float result;

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
    
    result = gauss1_value * gauss2_value;

    return (result);

}

// Function to generate a Gaussian LUT and return it as a dynamically allocated array (FOR TEMP DEV)
void generate_gaussian_LUT(float *lut_arr, int16_t lut_size, float sigma1, float c1, float sigma2, float c2) {
    float step_size = (X_MAX - X_MIN) / (lut_size - 1);
    
    for (int i = 0; i < lut_size; i++) {
        float x = X_MIN + (i * step_size); // compute the x value for this index in the LUT
        lut_arr[i] = compute_gaussian_value(x, sigma1, c1, sigma2, c2);
    }
   
}

void generate_gaussian_LUT_S(float *lut_arr, int16_t lut_size, float sigma1, float c1, float sigma2, float c2) {
    float step_size = 2.0f / (lut_size - 1);
    
    for (int i = 0; i < lut_size; i++) {
        float x = MIN_SLOPE_LIMIT + (i * step_size); // compute the x value for this index in the LUT
        lut_arr[i] = compute_gaussian_value(x, sigma1, c1, sigma2, c2);
    }
   
}

// Function to print the LUT values for debugging

void print_LUT(float* lut, int16_t lut_size) {
    for (int i = 0; i < lut_size; i++) {
        printf("LUT[%d] = %f\n", i, lut[i]);
    }
}


int main() {

    
    float T_set = 97.00f;

    /* Cold MF values */

    float coldMF_c2 = T_set - 8.0f;

    /* Optimal MF values */

    float optimalMF_c1 = T_set - 0.02f;
    float optimalMF_c2 = T_set + 0.02f;

    /* Hot MF values */

    float hotMF_c1 = T_set + 8.0f;

    /*
    float x = 0;
    float res = compute_gaussian_value(x, SIGMA_SLOPE, MIN_SLOPE_LIMIT, SIGMA_SLOPE, DEC_CENTER_2);
    printf("result is %f\n", res);
    */
    
    /*
    printf("START OF DEC_MF\n");
    float decMF[LUT_SIZE_1];
    generate_gaussian_LUT_S(decMF, LUT_SIZE_1, MIN_SLOPE_LIMIT, SIGMA_SLOPE, DEC_CENTER_2, SIGMA_SLOPE);
    print_LUT(decMF, LUT_SIZE_1);
    printf("\n\n\n");
    */
    
    /*
    printf("START OF STABLE_MF\n");
    float stableMF[LUT_SIZE_1];
    generate_gaussian_LUT_S(stableMF, LUT_SIZE_1, STABLE_CENTER_1, SIGMA_SLOPE, STABLE_CENTER_2, SIGMA_SLOPE);
    print_LUT(stableMF, LUT_SIZE_1);
    printf("\n\n\n");
    */
    
    
    printf("START OF INC_MF\n");
    float incMF[LUT_SIZE_1];
    generate_gaussian_LUT_S(incMF, LUT_SIZE_1, INCREASING_CENTER_1, SIGMA_SLOPE, MAX_SLOPE_LIMIT, SIGMA_SLOPE);
    print_LUT(incMF, LUT_SIZE_1);
    printf("\n\n\n");
    
    
    /*
    printf("START OF COLDMF\n");
    float coldMF[LUT_SIZE];
    generate_gaussian_LUT(coldMF, coldMF_s1, coldMF_c1, coldMF_s2, coldMF_c2);
    print_LUT(coldMF);
    printf("\n\n\n");
    
    printf("START OF OPTIMALMF\n");
    float optimalMF[LUT_SIZE];
    generate_gaussian_LUT(optimalMF, optimalMF_s1, optimalMF_c1, optimalMF_s2, optimalMF_c2);
    print_LUT(optimalMF);
    printf("\n\n\n");
    
    printf("START OF HOTMF\n");
    float hotMF[LUT_SIZE];
    generate_gaussian_LUT(hotMF, hotMF_s1, hotMF_c1, hotMF_s2, hotMF_c2);
    print_LUT(hotMF);
    printf("\n\n\n");
    */

    
}
