#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

/* Macros*/
#define RX_BUFFER_SIZE 50

/* Global data structures */
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

extern volatile uint8_t rxBuffer[RX_BUFFER_SIZE];
extern volatile uint8_t rx_ptr; // to track the current index in the buffer 
extern Command_t receivedCommand; 
extern bool commandReady;

/* Function prototypes */
void init_uart               (void);
void show_boot_screen        (void);
void tx_byte                 (void);
void sercom0_rx_handler      (void);
cmd_id_t parseCommand        (void);


#endif