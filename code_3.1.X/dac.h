#ifndef DAC_H
#define DAC_H

#include <stdbool.h>
#include <stdint.h>

void dac_init       (void);
void dac_write      (uint16_t data);
bool dac_isReady    (void);


#endif