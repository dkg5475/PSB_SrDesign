#include "../Header/uart.h"
#include "samc21e18a.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Macros to be used only in the source file */
#define F_CPU 48000000UL  // Adjust if your clock changes
#define BAUD_RATE 14400UL
/* Integer/Arithmetic baud value calculation */
#define BAUD_VALUE ((uint16_t)(65536 * (1.0 - (16.0 * BAUD_RATE / F_CPU))))
/* Fraction baud calculation, sampling is 16x so S = 16  */

#define S 16
#define BAUD_VALUE_INT (uint16_t)(F_CPU / (S * BAUD_RATE))
#define BAUD_VALUE_FRAC (uint8_t)(((F_CPU / (float)(S * BAUD_RATE)) - baud_int) * 8)

/* Initialization of global values */
static uint8_t rxBuffer[RX_BUFFER_SIZE];
static uint8_t rx_ptr;
Command_t receivedCommand; 
volatile bool commandReady = false; 
bool verboseActiveFlag = false;

// override printf functiont to work with uart
/* 
int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        tx_byte(ptr[i]);  // Send each character via USART
    }
    return len;  // Return the number of bytes written
}
 * */
 
void _mon_putc(char c) {
    tx_byte((uint8_t)c);
}


void uart_init (void) {
    
    
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
    
    /* Set the USART to run in async mode (CMODE) */
    /* Set the data order (set to be LSB is transmitted first) */
    /* Set the Immediate Buffer Overflow Notification (IBON) */
    /* Set the RX pin to be SERCOM0_PAD1 */
    /* TX: PAD[0] = TxD; PAD[2] = RTS; PAD[3] = CTS Position (RTS and CTS are disabled) */ 
    /* Set the sampling rate to be 16x the baud rate and to use fractional baud rate generation (1UL) */
    /* Set the format of the data to be 8 bits, no parity, 1 stop bit */
    SERCOM0_REGS->USART_INT.SERCOM_CTRLA = SERCOM_USART_INT_CTRLA_CMODE_ASYNC |
            SERCOM_USART_INT_CTRLA_DORD_Msk | 
            SERCOM_USART_INT_CTRLA_IBON_Msk | 
            SERCOM_USART_INT_CTRLA_RXPO_PAD1 |
            SERCOM_USART_INT_CTRLA_TXPO_PAD2 | 
            SERCOM_USART_INT_CTRLA_SAMPR(1UL) |
            SERCOM_USART_INT_CTRLA_FORM_USART_FRAME_NO_PARITY |
            SERCOM_USART_INT_CTRLA_RUNSTDBY_Msk |
            SERCOM_USART_INT_CTRLA_MODE_USART_INT_CLK;
            
    
    /* Set baud rate to be 14400 for a 48 MHz clock  */
    SERCOM0_REGS->USART_INT.SERCOM_BAUD = (uint16_t)SERCOM_USART_INT_BAUD_BAUD(16592UL);
    
    /* Enable the UART after the configurations */
    SERCOM0_REGS->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE_Msk;
    
    /* Enable Receive Complete interrupt */
    SERCOM0_REGS->USART_INT.SERCOM_INTENSET = (uint8_t)SERCOM_USART_INT_INTENSET_RXC_Msk;
    
    // Enable TX Complete Interrupt
    SERCOM0_REGS->USART_INT.SERCOM_INTENSET = (uint8_t)SERCOM_USART_INT_INTENSET_TXC_Msk;
    
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

void SERCOM0_Handler(void) {
    if (SERCOM0_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_RXC_Msk) {
        uint8_t received_byte = SERCOM0_REGS->USART_INT.SERCOM_DATA;
        
        // Check if ESC (0x1B) key is pressed
        if (received_byte == 0x1B) {
            printf("Escape requested, please try again!\r\n");
            rx_ptr = 0;  // reset the buffer pointer
            memset(rxBuffer, 0, RX_BUFFER_SIZE);  // clear the buffer
            return;  
        }
        
        // Ensure buffer does not overflow
        if (rx_ptr < RX_BUFFER_SIZE - 1) {
            rxBuffer[rx_ptr] = received_byte;
            rx_ptr++;

            // If newline is received, assume it's a complete command
            if (received_byte == '\n') {
                rxBuffer[rx_ptr] = '\0';  // Null-terminate the string
                commandReady = true;      // Flag the command for processing
                rx_ptr = 0;               // Reset buffer pointer for the next command
            }
        } else {
            // Buffer Overflow Handling
            rx_ptr = 0; 
            rxBuffer[rx_ptr] = '\0';
            printf("Error: RX buffer overflow!\r\n");
        }
    }

    // Check for errors
    if (SERCOM0_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_ERROR_Msk) {
        memset(rxBuffer, 0, RX_BUFFER_SIZE);  // Clear the buffer
        rx_ptr = 0;
        printf("Escape requested, please try again!\r\n");

        // Clear the error flag to prevent repeated error handling
        SERCOM0_REGS->USART_INT.SERCOM_INTFLAG = SERCOM_USART_INT_INTFLAG_ERROR_Msk;
    }
}

cmd_id_t parseCommand (void) {
    char* buffer = ((char*)rxBuffer);
    
    if (strncmp(buffer, "!c", 2) == 0) {
        return START;
    }
    else if(strncmp(buffer, "!s", 2) == 0) {
        if (strlen(buffer) > 3) {  // Ensure a payload exists
            
            // Find the start of the number (after "!s ")
            char *payload_start = buffer + 3;  // Skip "!s "
            
            // Trim leading spaces
            while (*payload_start == ' ') {
                payload_start++;
            }

            // Find the first '\r' or '\n' and replace with '\0'
            char *end = payload_start;
            while (*end != '\0' && *end != '\r' && *end != '\n') {
                end++;
            }
            *end = '\0';  // Null-terminate at the newline
            
            // Convert the extracted string to float and check for errors
            char *endptr;
            float value = strtof(payload_start, &endptr);

            // check for invalid options after !s, like "!s abc\n\n\n\r"
            if (endptr == payload_start || (!isspace(*endptr) && *endptr != '\0')) {
                printf("Invalid number received: %s\r\n", payload_start);
                return INVALID;  // Return invalid command if no valid float is found
            }

            receivedCommand.setpoint = value;
            return SETPOINT;
        }
        else { // no valid setpoint found
            return INVALID;
        }
    }
    else if (strncmp(buffer, "!e", 2) == 0) { // end verbose mode detection
        return END;
    }
    else if (strncmp(buffer, "!h", 2) == 0) {
        return HELP;
    }
    else { // any other input is invalid 
        return INVALID;
    }
    return INVALID;
}

void handleCommand (Command_t *cmd) {
    switch (cmd->id) {
        case START:
            printf("Entering Verbose Mode...\r\n");
            verboseActiveFlag = true;
            printf("Verbose Mode has been entered!\r\n");
            break;
        
        case SETPOINT:
            printf("Received new setpoint...\r\n");
            break;
        
        case END:
            printf("Ending Verbose Mode...\r\n");
            verboseActiveFlag = false;
            printf("Verbose Mode has been ended!\r\n");
            break;
            
        case HELP:
            printf("\r\n\n\n");
            printf("********************************************************************************************\r\n");
            printf("                                       COMMANDS MENU\r\n");
            printf("********************************************************************************************\r\n\n");
            printf("Command  Action\r\n");
            printf("  !c     Begin or end verbose mode \r\n");
            printf("  !s     Send a new setpoint during verbose mode\r\n");
            printf("  !e     End verbose mode\r\n");
            printf("  !h     Show commands menu \r\n");
            
        default:
            printf("Invalid command, please try again!\r\n");
    }
}