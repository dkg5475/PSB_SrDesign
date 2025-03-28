#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

/* Macros*/
#define UART_BUFFER_SIZE 64  

/* Global data structures */
extern volatile uint8_t rx_buffer[UART_BUFFER_SIZE];
extern volatile uint8_t tx_buffer[UART_BUFFER_SIZE];

/* For tracking head element and tail element in each buffer*/
/* Head tracks the front of the buffer (first element) */
/* Tail tracks the end of the buffer (last element) */
extern volatile uint8_t rx_head;
extern volatile uint8_t rx_tail;
extern volatile uint8_t tx_head;
extern volatile uint8_t tx_tail;

/* Flag to be set when new command is received and ready to be processed */
extern volatile bool commandReady;
/* Verbose mode flag */
extern bool verboseModeActive;

/* Command IDs */
typedef enum {
    START,
    SETPOINT,
    END,
    INVALID
}cmd_id_t;

/* Struct to be used in command processing */
typedef struct {
    cmd_id_t id;
    char commandBuffer[UART_BUFFER_SIZE];
    char payload[UART_BUFFER_SIZE];
}Command_t;


/* Function prototypes */
void uart_init               (void);
void uart_enable             (void);
void uart_disable            (void);
void uart_write              (uint8_t data);
void uart_read               (void);
void sercom0_read_handler    (void);
void sercom0_write_handler   (void);
void show_boot_screen        (void);
void transfer_data           (void);
cmd_id_t parseCommand        (const char *input);
void handleCommand           (Command_t *cmd);

#endif