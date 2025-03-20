#include "uart.h"
#include "definitions.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

uint8_t txBuffer[TX_BUFFER_SIZE] = {0};
uint8_t rxBuffer[RX_BUFFER_SIZE] = {0};
volatile uint32_t nBytesRead = 0;
uint32_t nBytesAvailable = 0;
volatile bool txThresholdEventReceived = false;
volatile bool rxThresholdEventReceived = false;
bool verboseActiveFlag = false;
volatile float new_setpoint = 0;
bool tempUpdateFlag = false;


Command_t receivedCommand;
volatile bool commandReady;

void show_boot_screen (void) {
   printf("\r\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
   printf("Penn State Behrend Embedded OCXO\r\n");
   printf("Sponsored by Kyocera AVX\r\n\r\n");
}

/* Triggered when event threshold is reached (2 bytes) */
void usartReadEventHandler (SERCOM_USART_EVENT event, uintptr_t context) {
    if (event == SERCOM_USART_EVENT_READ_THRESHOLD_REACHED) {
        nBytesAvailable = SERCOM0_USART_ReadCountGet();
        
        nBytesRead += SERCOM0_USART_Read((uint8_t*)&rxBuffer[nBytesRead], nBytesAvailable);
    }
    
    if (rxBuffer[nBytesRead - 1] == '\n' || rxBuffer[nBytesRead - 1] == '\r') {
        rxBuffer[nBytesRead - 1] = '\0'; // null terminate the last character (replace the \r or \n)
        nBytesRead = 0; // reset bytes read counter
        commandReady = true; // command is ready to parse
    }
}

/* Triggered when the TX buffer is empty */
void usartWriteEventHandler (SERCOM_USART_EVENT event, uintptr_t context) {
    txThresholdEventReceived = true;
}

commandMessages_t cmdMessages = {
    .start_msg        = "Entering Calibration mode...\r\n",  // Initialization of start_msg
    .setpt_msg        = "Received new setpoint...\r\n",     // Initialization of setpt_msg
    .end_msg          = "Ending Calibration Mode...\r\n",   // Initialization of end_msg
    .invalid_msg      = "Invalid Command\r\n"             // Initialization of invalid_msg
};


cmd_id_t parseCommand (const char *input) {
    if (strncmp(input, "!c", 2) == 0) {
        return START;
    }
    else if (strncmp(input, "!s", 2) == 0) {
        if (strlen(input) > 3) {
            strncpy(receivedCommand.payload, input + 3, RX_BUFFER_SIZE - 1);
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
            printf(cmdMessages.start_msg);
            verboseActiveFlag = true;
            break;
        
        case SETPOINT:
            printf(cmdMessages.setpt_msg);
            break;
        
        case END:
            printf(cmdMessages.end_msg);
            verboseActiveFlag = false;
            break;
            
        default:
            printf(cmdMessages.invalid_msg);
    }
}

void sendCurrentTemp(float temp) {
    printf("Current temperature is approximately %.3f\r\n", temp);
}

int _write (int file, char *ptr, int len) {
    SERCOM0_USART_Write((void*)ptr, len);
    return len;
}
