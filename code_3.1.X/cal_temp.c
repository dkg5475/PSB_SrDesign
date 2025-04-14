#include "cal_temp.h"
#include "samc21e18a.h"
#include "analog.h"
#include <stdint.h>
#include <stdio.h>
#include "timer.h"
#include <math.h>

#define SDADC_RESULT_SIGNED_BIT_MSK     (~(0x01 << 15))

cal_temp_constants_t constants = {
    .SUPPLY_VOLTAGE = 3.0f,
    .SDADC_VREF = 3.0f,
    .R13 = 4250.0f,
    .SH_A = 0.00087264,
    .SH_B = 0.00020796,
    .SH_C = 5.2284e-8f,
    .kelvinConst = 273.15f
};

inputs_t inputs = {
    .first_sample = 0,
    .last_sample = 0,
    .samples_average = 0,
    .temp_slope = 0
};

float voltage_samples[SAMPLE_COUNT];

// Wrapper function around natural log function from math.h
// Might replace later
float myLn (float x) {
    return logf(x);
}

void raw_to_voltage (void) {
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        voltage_samples[i] = (float)((sample_buffer[i] * constants.SDADC_VREF) / 32767.0f); // 32767 is 2^16
    }
    
    inputs.first_sample = fabs(voltage_samples[0]);
    inputs.last_sample = fabs(voltage_samples[SAMPLE_COUNT - 1]);
}

void find_average (void) {
    inputs.samples_average = 0;
    
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        inputs.samples_average += fabs(voltage_samples[i]);
    }
    inputs.samples_average /= SAMPLE_COUNT;
}


/* Calculates passed data point (Voltage Divider Equation */
    /* R_T = (Vout - R18) / (Vin - Vout) */
    /* R_T = rTherm */
    /* Vout = current element of voltageSamples */
    /* Vin = supply voltage of voltage divider (3.0V) */

float voltage_to_temp (float sample) {
    float voltageOut = sample; 
    float rTherm = ((voltageOut * constants.R13) / (constants.SUPPLY_VOLTAGE - voltageOut));
    
    /* Calculates the temperature using the beta equation */
    /* T = B / [ln(R_T / R_25) + (B/T_25)], where temperature is in Kelvin */
    float temp_B = myLn(rTherm) * constants.SH_B;
    float temp_C = powf((myLn(rTherm)), 3) * constants.SH_C;
    
    float sum = constants.SH_A + temp_B + temp_C;
    float result_kelvin = 1 / sum;
    /* Convert the current data sample to Celsius */
    float result_celsius = result_kelvin - constants.kelvinConst;
    
    return result_celsius;
}

void get_temp_inputs (void) {
    inputs.samples_average = voltage_to_temp(inputs.samples_average);
    inputs.first_sample = voltage_to_temp(inputs.first_sample);
    inputs.last_sample = voltage_to_temp(inputs.last_sample);
}

void calc_slope (float t) {
    inputs.temp_slope = (inputs.last_sample - inputs.first_sample) / t;
}

