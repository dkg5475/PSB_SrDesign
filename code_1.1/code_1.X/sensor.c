#include "definitions.h"
#include "sensor.h"

//!MODULE: sensor
//!
//!Functions used for the reading samples from the SDADC \n\n
//!
//!This module is used as a wrapper around SDADC function calls to read and store voltage samples\n\n
//!
//!The duration module defines the following functions:\n
//!    - Defines the result ready handler, the initialization function \n
//!    - Also defines a function for retrieving the raw SDADC samples
//!@param None
//!@return None

struct sdadc_t sdadc = {
    .rawSamples[SAMPLE_COUNT] = {0},
    .adcResult = 0,
};

/* Note that the parameters are unused but are included since the SDADC driver requires them */
void SDADC_ResultReadyHandler (SDADC_STATUS status, uintptr_t context) {   
    if (!sdadc.bufferFullFlag) {
        sdadc.adcResult = SDADC_ConversionResultGet();
        sdadc.rawSamples[sdadc.counter++] = sdadc.adcResult;
    }
    
    if (sdadc.counter >= SAMPLE_COUNT) {
        sdadc.bufferFullFlag = true;
    }
}

void SDADC_Init(void) {
    sdadc.counter = 0;
    sdadc.bufferFullFlag = false; 
    SDADC_Enable();
    SDADC_CallbackRegister(SDADC_ResultReadyHandler, (uintptr_t)NULL);
}   

bool isBufferFull(void) {
    return sdadc.bufferFullFlag;
}

void clearBuffer(void) {
    sdadc.counter = 0;
    sdadc.bufferFullFlag = false;
}

void readSensor (void) {
    
    if (sdadc.bufferFullFlag) {
        clearBuffer();
    }
    
    SDADC_ConversionStart();
}


