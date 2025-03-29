#include "../Header/uart.h"
#include "samc21e18a.h"
#include <string.h>
#include <stdio.h>

/* Macros to be used only in the source file */
#define F_CPU 48000000UL  // Adjust if your clock changes
#define BAUD_RATE 14400UL
/* Integer/Arithmetic baud value calculation */
#define BAUD_VALUE (65536 * (1 - (16.0 * BAUD_RATE) / F_CPU))

/* Initialization of global values */
volatile uint8_t rxBuffer[RX_BUFFER_SIZE];
volatile uint8_t rx_ptr = 0;
bool commandReady = false; 


void init_uart (void) {
    /* Disable USART instance before configurations are made*/
    SERCOM0_REGS->USART_INT.SERCOM_CTRLA &= ~SERCOM_USART_INT_CTRLA_ENABLE_Msk; 
    /* Software reset of USART settings */
    SERCOM0_REGS->USART_INT.SERCOM_CTRLA = SERCOM_USART_INT_CTRLA_SWRST_Msk; 
    /* Wait for the software reset to complete */
    while (SERCOM0_REGS->USART_INT.SERCOM_SYNCBUSY & SERCOM_USART_INT_SYNCBUSY_SWRST_Msk);
    
    /* Set the USART to run in async mode (CMODE) */
    /* Set the data order */
    /* Set the Immediate Buffer Overflow Notification (IBON) */
    /* Set the RX pin to be SERCOM0_PAD1 */
    /* TX: PAD[0] = TxD; PAD[2] = RTS; PAD[3] = CTS Position (RTS and CTS are disabled) */ 
    /* Set the sampling rate to be 16x the baud rate and to use arithmetic/integer baud rate generation (0UL) */
    /* Set the format of the data to be 8 bits, no parity, 1 stop bit */
    SERCOM0_REGS->USART_INT.SERCOM_CTRLA = SERCOM_USART_INT_CTRLA_CMODE(0UL) |
            SERCOM_USART_INT_CTRLA_DORD_Msk | 
            SERCOM_USART_INT_CTRLA_IBON_Msk | 
            SERCOM_USART_INT_CTRLA_RXPO_PAD1 |
            SERCOM_USART_INT_CTRLA_TXPO_PAD0 | 
            SERCOM_USART_INT_CTRLA_SAMPR_16X_ARITHMETIC |
            SERCOM_USART_INT_CTRLA_FORM_USART_FRAME_NO_PARITY;
    
    /* Set baud rate to be 14400 for a 48 MHz clock  */
    SERCOM0_REGS->USART_INT.SERCOM_BAUD = (uint16_t)SERCOM_USART_INT_BAUD_BAUD(65521UL);
    
    /* Set the data size to be 8 bits */
    /* Set number of stop bits to be 1 */
    /* Enable receiving (1 to enable) */
    /* Enable transmitting (1 to enable) */
    SERCOM0_REGS->USART_INT.SERCOM_CTRLB = SERCOM_USART_INT_CTRLB_CHSIZE_8_BIT | // 8 data bits
                                SERCOM_USART_INT_CTRLB_SBMODE_1_BIT | // 1 stop bit
                                SERCOM_USART_INT_CTRLB_RXEN(0x1UL)  |  
                                SERCOM_USART_INT_CTRLB_TXEN(0x1UL); 
    
    /* Wait for sync */
    while((SERCOM0_REGS->USART_INT.SERCOM_SYNCBUSY) != 0U);
    
    /* Enable the UART after the configurations */
    SERCOM0_REGS->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE_Msk;
    
    /* Enable Receive Complete interrupt */
    SERCOM0_REGS->USART_INT.SERCOM_INTENSET = (uint8_t)SERCOM_USART_INT_INTENSET_RXC_Msk;
    
    // Enable SERCOM0 IRQ in NVIC
    NVIC_EnableIRQ(SERCOM0_IRQn);
    
}

void show_boot_screen (void) {
   printf("\r\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
   printf("Penn State Behrend Embedded OCXO\r\n");
   printf("Sponsored by Kyocera AVX\r\n\r\n");
}

void tx_byte (uint8_t data) {
    /* Wait for the data register to empty before sending the byte */
    while(!(SERCOM0_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk));
    SERCOM0_REGS->USART_INT.SERCOM_DATA = data;
    
    /* Wait for the transmission to complete */
    while(!(SERCOM0_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_TXC_Msk));
    
    /* Clear the TXC flag */
    SERCOM0_REGS->USART_INT.SERCOM_INTFLAG = SERCOM_USART_INT_INTFLAG_TXC_Msk;
}

void sercom0_rx_handler (void) {
    
    if (SERCOM0_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_RXC_Msk) {
        // Check if there's room in the buffer to store the byte
        if (rx_ptr < RX_BUFFER_SIZE - 1) {  // Ensure there's space for the null terminator
            rxBuffer[rx_ptr] = SERCOM0_REGS->USART_INT.SERCOM_DATA;
            rx_ptr++;

            // Null terminate the buffer after receiving a byte
            rxBuffer[rx_ptr] = '\0';  // Null-terminate the string
        }
    }
        
    // Check if the ERROR interrupt flag is set (optional error handling)
    if (SERCOM0_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_ERROR_Msk) {
        // Handle the error
        for (int i = 0; i < RX_BUFFER_SIZE; i++) {
            rxBuffer[i] = 0;  // Clear the buffer
        }
        rx_ptr = 0;  // Reset the pointer
    }
    
}

cmd_id_t parseCommand (void) {
    if (strncmp(rxBuffer[rx_ptr], "!c") == 0) {
        return START;
    }
}
