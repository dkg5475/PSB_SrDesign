#ifndef UART_H
#define UART_H

#include "definitions.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RX_BUFFER_SIZE 10
#define TX_BUFFER_SIZE 40

// global variables used
extern uint8_t txBuffer[40];
extern uint8_t rxBuffer[10];
extern volatile uint32_t nBytesRead;
extern uint32_t nBytesAvailable;
extern volatile bool txThresholdEventReceived;
extern volatile bool rxThresholdEventReceived;
extern bool verboseActiveFlag;
extern volatile float new_setpoint;
extern bool tempUpdateFlag;

typedef enum {
    START,
    SETPOINT,
    END,
    INVALID
}cmd_id_t;

typedef struct {
    cmd_id_t id;
    char payload[RX_BUFFER_SIZE];
}Command_t;

typedef struct {
    const char *start_msg;
    const char *setpt_msg;
    const char *end_msg;
    const char *current_temp_msg;
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
void      sendCurrentTemp       (float temp);

#endif 