#include "definitions.h"
#include "convert.h"
#include <math.h>
#include <stdint.h>

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



convert_conversions_t conversions = {
    .SUPPLY_VOLTAGE = 3.0f,
    .SDADC_VREF     = 3.0f,
    .R18 = 4990.0f,
    .B_VALUE = 4300.0f,
    .R_25 = 100000.0f,
    .T_25 = 298.15f,
    .kelvinConst = 273.15f,
            
    .voltageOut = 0,
    .rTherm = 0,
    .tempK = 0,
    .tempC = 0,
    
    .voltageSamples = {0},
    
    .samplesAverage_voltage = 0,
    .firstSample_voltage = 0,
    .lastSample_voltage = 0,
    
    .result = 0,
            
    .samplesAverage = 0,
    .firstSample = 0, 
    .lastSample = 0, 
    .tempSlope = 0
    
};

float myLn (float x) {
    return (logf(x));
}

void rawToVoltage (int16_t *rawSampleBuffer) {
    // Convert the raw samples into voltage  
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        conversions.voltageSamples[i] = (float)((rawSampleBuffer[i] * conversions.SDADC_VREF) / INT16_MAX);
    }
    
    // Store the first and last element of the buffer (for later use)
    conversions.firstSample_voltage = conversions.voltageSamples[0];
    conversions.lastSample_voltage = conversions.voltageSamples[SAMPLE_COUNT - 1];
}

void findAverage (void) {
    // Sum up the voltage samples
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        conversions.samplesAverage_voltage += conversions.voltageSamples[i];
    }
    
    // Divide by the sample count
    conversions.samplesAverage_voltage = conversions.samplesAverage_voltage / SAMPLE_COUNT;
}

float voltageToTemp (float voltageSample) {
    /* Calculates passed data point (Voltage Divider Equation */
    /* R_T = (Vout - R18) / (Vin - Vout) */
    /* R_T = rTherm */
    /* Vout = current element of voltageSamples */
    /* Vin = supply voltage of voltage divider (3.0V) */
        
    // Convert the the passed data sample to temperature
    conversions.voltageOut = voltageSample; 
    conversions.rTherm = ( (conversions.voltageOut * conversions.R18) / (conversions.SUPPLY_VOLTAGE - conversions.voltageOut));
    /* Calculates the temperature using the beta equation */
    /* T = B / [ln(R_T / R_25) + (B/T_25)], where temperature is in Kelvin */
    conversions.tempK = (conversions.B_VALUE) / ( ( myLn(conversions.rTherm) / conversions.R_25 ) + (conversions.B_VALUE / conversions.T_25) );
    /* Convert the current data sample to Celsius */
    conversions.tempC = conversions.tempK - conversions.kelvinConst;
    /* Store the final result */
    conversions.result = conversions.tempC;
    
    return conversions.result;
}

float calcSlope (float t) {
    conversions.tempSlope = (conversions.firstSample - conversions.lastSample) / t;
    
    return conversions.tempSlope;
}





