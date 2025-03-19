#include "uart.h"
#include "definitions.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

uart_t uart = {
  .txBuffer = {0},
  .rxBuffer = {0},
  .nBytesRead = 0,
  .nBytesAvailable = 0,
  .txThresholdEventReceived = false,
  .rxThresholdEventReceived = false,
  .calibrationActiveFlag = false
};



void show_boot_screen (void) {
   printf("\r\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
   printf("Penn State Behrend Embedded OCXO\r\n");
   printf("Sponsored by Kyocera AVX\r\n\r\n");
}

/* Triggered when event threshold is reached (10 bytes) */
void usartReadEventHandler (SERCOM_USART_EVENT event, uintptr_t context) {
    if (event == SERCOM_USART_EVENT_READ_THRESHOLD_REACHED) {
        uart.nBytesRead = SERCOM0_USART_ReadCountGet();
        
        uart.nBytesRead += SERCOM0_USART_Read((uint8_t*)&uart.rxBuffer[uart.nBytesRead], uart.nBytesAvailable);
    }
    
    if (uart.rxBuffer[uart.nBytesRead - 1] == '\n' || uart.rxBuffer[uart.nBytesRead - 1] == '\r') {
        uart.rxBuffer[uart.nBytesRead - 1] = '\0'; // null terminate the last character (replace the \r or \n)
        uart.nBytesRead = 0; // reset bytes read counter
        commandReady = true; // command is ready to parse
    }
}

/* Triggered when the TX buffer is empty */
void usartWriteEventHandler (SERCOM_USART_EVENT event, uintptr_t context) {
    uart.txThresholdEventReceived = true;
}

/* Register both event handlers */
void usartRegisterHandlers (void) {
    SERCOM0_USART_WriteCallbackRegister(usartWriteEventHandler, (uintptr_t) NULL);
    // Set the read threshold so that the event handler runs when there are at least 2 bytes in the buffer
    SERCOM0_USART_ReadThresholdSet(2);
    SERCOM0_USART_ReadCallbackRegister(usartReadEventHandler, (uintptr_t) NULL);
}

Command_t receivedCommand;
volatile bool commandReady;

commandMessages_t cmdMessages = {
    .start_msg      = "Entering Calibration mode...\r\n",  // Initialization of start_msg
    .setpt_msg      = "Received new setpoint...\r\n",     // Initialization of setpt_msg
    .end_msg        = "Ending Calibration Mode...\r\n",   // Initialization of end_msg
    .invalid_msg    = "Invalid Command\r\n"             // Initialization of invalid_msg
};


cmd_id_t parseCommand (const char *input) {
    if (strncmp(input, "!c", 2) == 0) {
        return START;
    }
    else if (strncmp(input, "!s", 2) == 0) {
        if (strlen(input) > 3) {
            strncpy(receivedCommand.payload, input + 3, BUFFER_SIZE - 1);
            return SETPOINT;
        }
        /* If the "!s" command doesn't have a valid setpoint attached, it's invalid */
        return INVALID;
    }
    else if (strncmp(input, "!e", 2) == 0) {
        return END;
    }
    
    return INVALID;
}

void handleCommand (Command_t *cmd) {
    switch (cmd->id) {
        case START:
            SERCOM0_USART_Write((uint8_t*)cmdMessages.start_msg, strlen(cmdMessages.start_msg));
            uart.calibrationActiveFlag = true;
            break;
        
        case SETPOINT:
            SERCOM0_USART_Write((uint8_t*)cmdMessages.setpt_msg, strlen(cmdMessages.setpt_msg));
            break;
        
        case END:
            SERCOM0_USART_Write((uint8_t*)cmdMessages.end_msg, strlen(cmdMessages.end_msg));
            uart.calibrationActiveFlag = false;
            break;
            
        default:
            SERCOM0_USART_Write((uint8_t*)cmdMessages.end_msg, strlen(cmdMessages.end_msg));
    }
}

