#ifndef SENSOR_H
#define SENSOR_H

/* Macros */
#define SAMPLE_COUNT 64

/* Included libraries*/
#include "definitions.h"
#include <stdint.h> 

/* Function prototypes */
void SDADC_Init                   (void); 
void SDADC_ResultReadyHandler     (SDADC_STATUS status, uintptr_t context);
bool isBufferFull                 (void);
void clearBuffer                  (void);
int16_t* readSensor               (void);

/* Global Structures */
    //!Define global structure for callback handler
    struct sdadc_t {
        int16_t rawSamples[SAMPLE_COUNT];
        volatile int16_t  adcResult;
        volatile uint16_t counter;
        bool              bufferFullFlag;
    };
#endif
    

