#include "../Header/uart.h"
#include "samc21e18a.h"
#include <string.h>
#include <stdio.h>

/* Macros to be used only in the source file */
#define F_CPU 48000000UL  // Adjust if your clock changes
#define BAUD_RATE 14400UL
#define BAUD_VALUE (F_CPU / (16 * BAUD_RATE)) // 16x oversampling
/* Get current position in the buffer */
#define BUFFER_COUNT ((rx_head >= rx_tail) ? (rx_head - rx_tail) : (UART_BUFFER_SIZE - rx_tail + rx_head))

/* Initialization of rx and tx buffers*/
volatile uint8_t rx_buffer[UART_BUFFER_SIZE] = {0};
volatile uint8_t tx_buffer[UART_BUFFER_SIZE] = {0};

/* Initialization of head and tail variables for each buffer */
volatile uint8_t rx_head = 0;
volatile uint8_t rx_tail = 0;
volatile uint8_t tx_head = 0;
volatile uint8_t tx_tail = 0;

/* Initialization of flags */
volatile bool commandReady = false;
bool verboseModeActive = false;

/* Initialization of global structs */
Command_t receivedCommand;

void uart_init(void) {
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
    /* Set the TX pin to be SERCOM0_PAD0 */
    /* Set the sampling rate to be 8x the baud rate (1UL) */
    /* Set the format of the data to be 8 bits, no parity, 1 stop bit */
    SERCOM0_REGS->USART_INT.SERCOM_CTRLA = SERCOM_USART_INT_CTRLA_CMODE(0UL) |
            SERCOM_USART_INT_CTRLA_DORD_Msk | 
            SERCOM_USART_INT_CTRLA_IBON_Msk | 
            SERCOM_USART_INT_CTRLA_RXPO_PAD1 |
            SERCOM_USART_INT_CTRLA_TXPO_PAD0 | 
            SERCOM_USART_INT_CTRLA_SAMPR(1UL) |
            SERCOM_USART_INT_CTRLA_FORM(0x0UL);
    
    /* Set baud rate to be 14400 for a 48 MHz clock  */
    SERCOM0_REGS->USART_INT.SERCOM_BAUD = (uint16_t)SERCOM_USART_INT_BAUD_BAUD(BAUD_VALUE);
    
    /* Set the data size to be 8 bits */
    /* Set number of stop bits to be 1 */
    /* Enable receiving */
    /* Enable transmitting */
    SERCOM0_REGS->USART_INT.SERCOM_CTRLB = SERCOM_USART_INT_CTRLB_CHSIZE_8_BIT | // 8 data bits
                                SERCOM_USART_INT_CTRLB_SBMODE_1_BIT | // 1 stop bit
                                SERCOM_USART_INT_CTRLB_RXEN_Msk     |  
                                SERCOM_USART_INT_CTRLB_TXEN_Msk; 
    
    /* Wait for sync */
    while((SERCOM0_REGS->USART_INT.SERCOM_SYNCBUSY) != 0U);
    
    /* Enable the UART after the configurations */
    SERCOM0_REGS->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE_Msk;
    
    /* Enable error interrupt */
    SERCOM0_REGS->USART_INT.SERCOM_INTENSET = (uint8_t)SERCOM_USART_INT_INTENSET_ERROR_Msk;

    /* Enable Receive Complete interrupt */
    SERCOM0_REGS->USART_INT.SERCOM_INTENSET = (uint8_t)SERCOM_USART_INT_INTENSET_RXC_Msk;
    
    /* Enable Transmit Complete Interrupt */
    SERCOM0_REGS->USART_INT.SERCOM_INTENSET = (uint8_t)SERCOM_USART_INT_INTENSET_TXC_Msk;
    
    // Enable SERCOM0 IRQ in NVIC
    NVIC_EnableIRQ(SERCOM0_IRQn);
    
}

void uart_enable (void) {
    /* If the SERCOM0 USART isn't enabled, enable it */
    if (!(SERCOM0_REGS->USART_INT.SERCOM_CTRLA & SERCOM_USART_INT_CTRLA_ENABLE_Msk))
    {
        /* Wait for any ongoing sync before modifying CTRLA */
        while (SERCOM0_REGS->USART_INT.SERCOM_SYNCBUSY & SERCOM_USART_INT_SYNCBUSY_Msk);
        
        /* Enable SERCOM0 USART */
        SERCOM0_REGS->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE_Msk;

        /* Wait for sync */
        while((SERCOM0_REGS->USART_INT.SERCOM_SYNCBUSY) != 0U);
    }
}

void uart_disable (void) {
    /* If the SERCOM0 is enabled, disable it */
    if ((SERCOM0_REGS->USART_INT.SERCOM_CTRLA & SERCOM_USART_INT_CTRLA_ENABLE_Msk) != 0U)
    {
        /* Wait for any ongoing sync before modifying CTRLA */
        while (SERCOM0_REGS->USART_INT.SERCOM_SYNCBUSY & SERCOM_USART_INT_SYNCBUSY_Msk);
        
        /* Disable the USART*/
        SERCOM0_REGS->USART_INT.SERCOM_CTRLA &= ~SERCOM_USART_INT_CTRLA_ENABLE_Msk;

        /* Wait for sync */
        while((SERCOM0_REGS->USART_INT.SERCOM_SYNCBUSY) != 0U);
    }
}

void uart_write(uint8_t data) {
    uint8_t next_head = (tx_head + 1) % UART_BUFFER_SIZE;  

    /* Check if buffer is full (next_head == tx_tail means full) */
    if (next_head == tx_tail) {
        return;  // Drop the byte or handle buffer full case
    }
    
    /* Store byte in buffer */
    tx_buffer[tx_head] = data;  
    /* Move head forward */
    tx_head = next_head;       

    // Enable Data Register Empty (DRE) interrupt to start transmission
    SERCOM0_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_DRE_Msk;
}

void sercom0_read_handler (void) {
    uint8_t data = 0;

    /* RX Interrupt Handling, triggers when 2 bytes are received */
    if (SERCOM0_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_RXC_Msk) {
        data = SERCOM0_REGS->USART_INT.SERCOM_DATA;

        /* Calculate next head position */
        uint8_t next_head = (rx_head + 1) % UART_BUFFER_SIZE;
        
        /* Check if buffer is full before writing */
        if (next_head == rx_tail) {
            // Buffer is full, discard oldest byte
            rx_tail = (rx_tail + 1) % UART_BUFFER_SIZE;
        }

        /* Store data in ring buffer */
        rx_buffer[rx_head] = data;
        rx_head = (rx_head + 1) % UART_BUFFER_SIZE;

        /* Safely check last character received */
        uint8_t last_index = (rx_head == 0) ? (UART_BUFFER_SIZE - 1) : (rx_head - 1);
        if (rx_buffer[last_index] == '\n' || rx_buffer[last_index] == '\r') {
            commandReady = true;
        }
    }
}

void sercom0_write_handler(void) {
    /* Check if Data Register Empty interrupt is triggered */
    
    if (SERCOM0_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk) {
        /* If buffer is not empty, send next byte */
        if (tx_head != tx_tail) {
            SERCOM0_REGS->USART_INT.SERCOM_DATA = tx_buffer[tx_tail]; 
            /* Move tail forward */
            tx_tail = (tx_tail + 1) % UART_BUFFER_SIZE; 
        } else {
            /* Buffer empty, disable DRE interrupt */
            SERCOM0_REGS->USART_INT.SERCOM_INTENCLR = SERCOM_USART_INT_INTENCLR_DRE_Msk;
        }
    }
}

int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        uart_write(ptr[i]); // Send each char via UART
    }
    return len;
}

void show_boot_screen (void) {
    printf("\r\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("Penn State Behrend Embedded OCXO\r\n");
    printf("Sponsored by Kyocera AVX\r\n\r\n");
}

void transfer_data (void) {
    uint8_t i = 0;
    while (rx_tail != rx_head && i < UART_BUFFER_SIZE - 1) {
        receivedCommand.commandBuffer[i] = rx_buffer[rx_tail];
        rx_tail = (rx_tail + 1) % UART_BUFFER_SIZE;
        i++;
    }
    receivedCommand.commandBuffer[i] = '\0'; // Null-terminate the command
}

cmd_id_t parseCommand (const char *input) {
    
    /* Checking for a NULL argument to avoid crashing from strcmp and strlen*/
    if(input == NULL) {
        return INVALID; 
    }
    
    if (strncmp(input, "!c", 2) == 0) {
        return START;
    }
    else if (strncmp(input, "!s", 2) == 0) {
        if (strlen(input) > 2) { // Make sure there is some kind of number after "!s"
            strncpy(receivedCommand.payload, input + 3, UART_BUFFER_SIZE - 1);
            receivedCommand.payload[UART_BUFFER_SIZE - 1] = '\0'; // Ensure null termination
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
            printf("Entering Verbose Mode...\r\n");
            verboseModeActive = true;
            break;
            
        case SETPOINT:
            printf("Received new setpoint...\r\n");
            break;
            
        case END:
            printf("Ending Verbose Mode...\r\n");
            break;
            
        default:  
            printf("Invalid Command!!!\r\n");
            break;
    }
}
