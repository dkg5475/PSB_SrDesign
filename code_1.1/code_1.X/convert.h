#ifndef CONVERT_H
#define CONVERT_H

#include "definitions.h"
#include <stdint.h> 

/* Macros */
#define SAMPLE_COUNT 64
// #define SDADC_VREF   3.0

/* Function prototypes*/
float  myLn                (float x); 
void   rawToVoltage        (int16_t *rawSampleBuffer);
void   findAverage         (void);
float  voltageToTemp       (float voltageSample);
float  calcSlope           (float t);
/* Adding myLn as a wrapper in case we decide to add a custom approximation */


/* Global structures */
    //!Define global structure for variables needed
    typedef struct {
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
        
        float voltageSamples[SAMPLE_COUNT];
        
        float samplesAverage_voltage;
        float firstSample_voltage;
        float lastSample_voltage;
        
        float result;
        
        float samplesAverage; // for holding the average of the samples in the buffer 
        float firstSample;  // first sample in the buffer
        float lastSample; // last sample in the buffer
        float tempSlope;
        
    }convert_conversions_t;
    
    extern convert_conversions_t conversions;

#endif
    

