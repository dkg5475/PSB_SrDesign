#ifndef CONVERT_H
#define CONVERT_H

#include "definitions.h"
#include <stdint.h> 

/* Macros */
#define SAMPLE_COUNT 64
// #define SDADC_VREF   3.0

/* Function prototypes*/
float  myLn                (double x); 
void   findAverage         (int16_t *sampleBuffer);
void   rawToVoltage        (void);
float  voltageToTemp       (float sample);
void   getTempPoints       (void);
float  calcSlope           (float t);
/* Adding myLn as a wrapper in case we decide to add a custom approximation */


/* Global structures */
    //!Define global structure for variables needed
    struct conversions_t {
        const float SUPPLY_VOLTAGE;  
        const float SDADC_VREF;
        const float R18;             
        const float B_VALUE;         
        const float R_25;            
        const float T_25;      
        const float kelvinConst;

        float voltageOut; // Vout for calculating R_2 (thermistor resistance)
        float rTherm;     // thermistor resistance 
        float tempK;      // individual temperature data points in Kelvin
        float tempC;      // individual temperature data points in Celsius 
        
        int16_t samplesAverage_raw; // for storing the average of the samples before conversions
        int16_t firstSample_raw; // first and last sample gathered before conversion
        int16_t lastSample_raw;
        
        float samplesAverage_voltage; // for storing average of the samples after converting to voltage
        float firstSample_voltage; // first and last samples as voltage
        float lastSample_voltage;
        
        float samplesAverage_temp;  // required variables as temperature
        float firstSample_temp;
        float lastSample_temp;
        float tempSlope;
        
    };

#endif
    

