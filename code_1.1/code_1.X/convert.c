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



struct conversions_t conversions = {
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
    
    .samplesAverage_raw = 0,
    .firstSample_raw = 0,
    .lastSample_raw = 0,
    
    .samplesAverage_voltage = 0,
    .firstSample_voltage = 0,
    .lastSample_voltage = 0,
            
    .samplesAverage_temp = 0,
    .firstSample_temp = 0,
    .lastSample_temp = 0,
    .tempSlope = 0
    
};

float myLn (double x) {
    return (float)(log(x));
}

void findAverage (int16_t *sampleBuffer) {
    
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        conversions.samplesAverage_raw += sampleBuffer[i];
    }
    
    conversions.samplesAverage_raw /= SAMPLE_COUNT;
    
    //Store the first and last value (for slope calculation)
    conversions.firstSample_raw = sampleBuffer[0];
    conversions.lastSample_raw = sampleBuffer[SAMPLE_COUNT - 1];
}

void rawToVoltage (void) {
    
    //Convert the average of the samples to voltage
    conversions.samplesAverage_voltage = (float)((conversions.samplesAverage_raw * conversions.SDADC_VREF) / INT16_MAX);
    
    //Convert the first and last value of the samples to voltage (for the slope calculation)
    conversions.firstSample_voltage = (float)((conversions.firstSample_raw * conversions.SDADC_VREF) / INT16_MAX);
    conversions.lastSample_voltage = (float)((conversions.lastSample_raw * conversions.SDADC_VREF) / INT16_MAX);
}

float voltageToTemp (float voltage_sample) {
    // Accepts a sample as voltage, and returns it in temperature
    /* Calculates passed data point using the voltage divider equation */
    /* R_T = (Vout - R18) / (Vin - Vout) */
    /* R_T = rTherm */
    /* Vout = current element of voltageSamples */
    /* Vin = supply voltage of voltage divider (3.0V) */
        
    // Convert the average of the samples to temperature
    conversions.voltageOut = voltage_sample;
    conversions.rTherm = ( (conversions.voltageOut * conversions.R18) / (conversions.SUPPLY_VOLTAGE - conversions.voltageOut));
    /* Calculates the temperature using the beta equation */
    /* T = B / [ln(R_T / R_25) + (B/T_25)], where temperature is in Kelvin */
    conversions.tempK = (conversions.B_VALUE) / ( ( myLn(conversions.rTherm) / conversions.R_25 ) + (conversions.B_VALUE / conversions.T_25) );
    /* Convert the current data sample to Celsius */
    conversions.tempC = conversions.tempK - conversions.kelvinConst;
    /* Final result is the temp in Celsius */
    return conversions.tempC;
}

void getTempPoints (void) {
    conversions.firstSample_temp = voltageToTemp(conversions.firstSample_voltage);
    conversions.lastSample_temp = voltageToTemp(conversions.lastSample_voltage);
    conversions.samplesAverage_temp = voltageToTemp(conversions.samplesAverage_voltage);
}

float calcSlope (float t) {
    conversions.tempSlope = (conversions.firstSample_temp - conversions.lastSample_temp) / t;
    return conversions.tempSlope;
}





