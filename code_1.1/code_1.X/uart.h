#ifndef UART_H
#define UART_H

#include "definitions.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 50

typedef struct {
    uint8_t txBuffer[BUFFER_SIZE];
    uint8_t rxBuffer[BUFFER_SIZE];
    volatile uint32_t nBytesRead;
    uint32_t nBytesAvailable;
    volatile bool txThresholdEventReceived;
    volatile bool rxThresholdEventReceived;
    bool calibrationActiveFlag;
    
}uart_t;

typedef enum {
    START,
    SETPOINT,
    END,
    INVALID
}cmd_id_t;

typedef struct {
    cmd_id_t id;
    char payload[BUFFER_SIZE];
}Command_t;

typedef struct {
    const char *start_msg;
    const char *setpt_msg;
    const char *end_msg;
    const char *tx_ideal_msg;
    const char *rx_ideal_msg;
    const char *invalid_msg;
}commandMessages_t;

extern Command_t receivedCommand;
extern volatile bool commandReady;
extern commandMessages_t cmdMessages;

void      show_boot_screen      (void);
void      usartReadEventHandler (SERCOM_USART_EVENT event, uintptr_t context);
void      usartWriteEventHandler(SERCOM_USART_EVENT event, uintptr_t context);
void      usartRegisterHandlers (void);
cmd_id_t  parseCommand          (const char *input);
void      handleCommand         (Command_t *cmd);

#endif 