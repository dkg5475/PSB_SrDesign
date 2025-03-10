#include "definitions.h"
#include "convert.h"
#include <math.h>

//!MODULE: convert
//!
//!Functions used in converting from the raw SDADC readings to voltage, and then to temperature \n\n
//!
//!This module is used as a wrapper around SDADC function calls to read and store voltage samples\n\n
//!
//!The duration module defines the following functions:\n
//!    - myLn, which is a wrapper around the math.h implementation for the natural log function \n
//!    - rawToVoltage, which converts the raw SDADC samples to voltage
//!    - voltageToTemp, which converts the voltage samples to temperature (in Celsius)
//!    - calcSlope, which is a function to be used to calculate the temperature slope over the sampling interval
//!    - getTempSamples, which returns the buffer that holds the temperature data points
//!@param None
//!@return None

/* Static ensures that the struct declared here is private */
/* This means that in order to retrieve the value of a member, a get function must be implemented */

struct conversions_t conversions = {
    .SUPPLY_VOLTAGE = 3.0f,
    .SDADC_VREF     = 3.0f,
    .R18 = 4990.0f,
    .B_VALUE = 4300.0f,
    .R_25 = 100000.0f,
    .T_25 = 298.15f,
    .kelvinConst = 273.15f
};

float myLn (double x) {
    return (float)(log(x));
}


void rawToVoltage (int16_t *samples) {
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        conversions.voltageSamples[i] = (float)((samples[i] * conversions.SDADC_VREF) / 32768);
    }
}

void voltageToTemp (void) {
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        /* Calculates rTherm for each data point (Voltage Divider Equation */
        /* R_T = (Vout - R18) / (Vin - Vout) */
        /* R_T = rTherm */
        /* Vout = current element of voltageSamples */
        /* Vin = supply voltage of voltage divider (3.0V) */
        
        conversions.voltageOut = conversions.voltageSamples[i]; 
        conversions.rTherm = ( (conversions.voltageOut * conversions.R18) / (conversions.SUPPLY_VOLTAGE - conversions.voltageOut));
        
        /*Calculates the temperature using the beta equation */
        /* T = B / [ln(R_T / R_25) + (B/T_25)], where temperature is in Kelvin */
        conversions.tempK = (conversions.B_VALUE) / ( ( myLn(conversions.rTherm) / conversions.R_25 ) + (conversions.B_VALUE / conversions.T_25) );
        
        /* Convert the current data sample to Celsius */
        conversions.tempC = conversions.tempK - conversions.kelvinConst;
        
        /* Store the data sample in the tempSamples buffer */
        conversions.tempSamples[i] = conversions.tempC;
        
    }
}

float calcSlope (float t) {
    conversions.firstSample = conversions.tempSamples[0];
    conversions.lastSample = conversions.tempSamples[SAMPLE_COUNT - 1];
    conversions.tempSlope = (conversions.firstSample - conversions.lastSample) / t;
    
    return conversions.tempSlope;
}

float* getTempSamples (void) {
    return conversions.tempSamples;
}




