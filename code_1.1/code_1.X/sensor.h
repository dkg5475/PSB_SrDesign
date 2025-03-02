#include "definitions.h"
#include <stdint.h> 

/* Macros */
#define SAMPLE_COUNT 64

/* Function prototypes */
void SDADC_Init                   (void); 
void SDADC_ResultReadyHandler     (SDADC_STATUS status, uintptr_t context);
int16_t* readSensor               (void);

/* Global Structures */
#ifndef SENSOR_H
#define SENSOR_H
    //!Define global structure for callback handler
    struct sdadc_t {
        int16_t rawSamples[SAMPLE_COUNT];
        volatile int16_t adcResult;
        volatile uint16_t counter;
    };
    
    
#endif
    

