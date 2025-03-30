#include "../Header/cal_temp.h"
#include "samc21e18a.h"
#include "../Header/analog.h"
#include <stdint.h>
#include "../Header/timer.h"

// Wrapper function around natural log function from math.h
// Might replace later
float myLn (float x) {
    return logf(x);
}

void raw_to_voltage (void) {
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        voltage_samples[i] = (float)((sample_buffer[i] * constants.SDADC_VREF) / INT16_MAX); // INT16_MAX is 2^16
    }
    inputs.first_sample = voltage_samples[0];
    inputs.last_sample = voltage_samples[SAMPLE_COUNT - 1];
}

void find_average (void) {
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        inputs.samples_average += voltage_samples[i];
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
    float rTherm = ((voltageOut * constants.R18) / (constants.SUPPLY_VOLTAGE - voltageOut));
    
    /* Calculates the temperature using the beta equation */
    /* T = B / [ln(R_T / R_25) + (B/T_25)], where temperature is in Kelvin */
    float tempK = (constants.B_VALUE) / ( ( myLn(rTherm) / constants.R_25 ) + (constants.B_VALUE / constants.T_25) );
    /* Convert the current data sample to Celsius */
    float tempC = tempK - constants.kelvinConst;
    /* Store the final result */
    float result = tempC;
    
    return result;
}

void get_inputs (void) {
    voltage_to_temp(inputs.samples_average);
    voltage_to_temp(inputs.first_sample);
    voltage_to_temp(inputs.last_sample);
}
