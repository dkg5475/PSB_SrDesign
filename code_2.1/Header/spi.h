#ifndef SPI_H
#define	SPI_H

#include <stdbool.h>
#include <stdint.h>

#define SERCOM3_Frequency               (48000000UL)// clk freq for the baud calculation
#define SERCOM3_SPIM_BAUD_VALUE         (23UL) // baud register value

//[23:16] device commands for the external DAC80501MDQFT 
#define DEVID       0x01U
#define SYNC        0x02U
#define CONFIG      0x03U
#define GAIN        0x04U
#define TRIGGER     0x05U
#define STATUS      0x07U
#define DATA        0x08U





// spim denotes master device operations (from microcontroller to external DAC)
void spim_init      (void);
bool spim_busy      (void);
void spim_tx_byte   (uint8_t data);
void spis_sync      (void);

#endif	/* SPI_H */

