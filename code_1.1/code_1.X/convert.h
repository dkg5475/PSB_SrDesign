#include "definitions.h"
#include <stdint.h> 

/* Macros */
#define SAMPLE_COUNT 64
#define SDADC_VREF   2.0

/* Function prototypes*/
double  myLn                (double x); 
void    rawToVoltage        (int16_t *samples);
void    voltageToTemp       (void);
double  calcSlope           (double);
double* getTempSamples      (void);
/* Adding myLn as a wrapper in case we decide to add a custom approximation */


/* Global structures */
#ifndef CONVERT_H
#define CONVERT_H
    //!Define global structure for variables needed
    struct conversions_t {
        const double SUPPLY_VOLTAGE;  
        const double R18;             
        const double B_VALUE;         
        const double R_25;            
        const double T_25;      
        const double kelvinConst;

        double voltageOut; // Vout for calculating R_2 (thermistor resistance)
        double rTherm;     // thermistor resistance 
        double tempK;      // individual temperature data points in Kelvin
        double tempC;      // individual temperature data points in Celsius 
        
        double voltageSamples[SAMPLE_COUNT]; 
        double tempSamples[SAMPLE_COUNT];
        
        double firstSample;  // first sample in the buffer
        double lastSample; // last sample in the buffer
        double tempSlope;
    };

    
#endif
    

