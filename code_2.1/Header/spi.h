#ifndef SPI_H
#define	SPI_H

// SERCOM3 clk freq value for the baud calculation 
#define SERCOM3_Frequency      (48000000UL)

// SERCOM3 SPI baud value for 1000000 Hz baud rate 
#define SERCOM3_SPIM_BAUD_VALUE         (23UL)

void spi_init(void);

#endif	/* SPI_H */

