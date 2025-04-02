#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

/* Macros*/
#define RX_BUFFER_SIZE 20

/* Global data structures */
typedef enum {
    HELP,
    START,
    SETPOINT,
    END,
    INVALID
}cmd_id_t;

typedef struct {
    cmd_id_t id;
    char payload[RX_BUFFER_SIZE];
    float setpoint;
}Command_t;

/* Function prototypes */
void uart_init               (void);
void show_boot_screen        (void);
void tx_byte                 (uint8_t data);
void sercom0_rx_handler      (void);
cmd_id_t parseCommand        (void);
void handleCommand           (Command_t *cmd);


#endif