#ifndef ANALOG_H
#define ANALOG_H

#include <stdint.h>
#include <stdbool.h>

#define SAMPLE_COUNT 128

// Global variables 
extern volatile int16_t sample_buffer[SAMPLE_COUNT];  // Buffer to store samples
extern volatile uint8_t sample_index;  // Index for buffer
extern volatile bool bufferFullFlag;

// Function prototypes
void     sdadc_init         (void);
void     sdadc_start        (void);
void     sdadc_stop         (void);
void     SDADC_Handler      (void);
void     sdadc_flush        (void);



#endif