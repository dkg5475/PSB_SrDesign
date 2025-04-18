#ifndef CAL_TEMP_H
#define CAL_TEMP_H

#include "analog.h"
#include <math.h>

// Global variables
extern float voltage_samples[SAMPLE_COUNT];

// Function prototypes
float myLn                    (float x);
void  raw_to_voltage          (void);
void  find_average            (void);
float voltage_to_temp         (float sample);
void  get_temp_inputs         (void);
void calc_slope               (float t);

// Global struct for constants used in calculations 
typedef struct {
    const float SUPPLY_VOLTAGE;  
    const float SDADC_VREF;
    const float R13;             
    const float SH_A; // steinhart-hart coeff 'A'
    const float SH_B; // steinhart-hart coeff 'B'
    const float SH_C; // steinhart-hart coeff 'C'
    const float kelvinConst;       
} cal_temp_constants_t;
    
extern cal_temp_constants_t constants;

typedef struct {
    float samples_average;
    float first_sample;
    float last_sample;
    float temp_slope;
}inputs_t;

extern inputs_t inputs;

#endif