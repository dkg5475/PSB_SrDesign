#include "../Header/flash.h"
#include "samc21e18a.h"

void nvm_init (void) {
    // Initialize NVM controller with no miss penalty, low power mode with wake on access, 2 read wait states, and manual writes
    NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_READMODE_NO_MISS_PENALTY | 
            NVMCTRL_CTRLB_SLEEPPRM_WAKEONACCESS | 
            NVMCTRL_CTRLB_RWS(2UL) | 
            NVMCTRL_CTRLB_MANW_Msk;
}

bool nvm_read (uint32_t *data, uint32_t length, const uint32_t address) {
    uint32_t *paddress = (uint32_t*)address;
    (void)memcpy(data, paddress, length); // copy the given length from the starting address into the passed buffer (data))
    return true;
}

bool nvm_page_write (uint32_t *data, const uint32_t address) {
    uint32_t i;
    uint32_t * paddress = (uint32_t *)address;

    /* writing 32-bit data into the given address */
    for (i = 0U; i < (NVMCTRL_FLASH_PAGESIZE/4U); i++)
    {
        *paddress = *(data + i);
        paddress++;
    }

     /* Set address and command */
    // Shift right by 1 bit (dividing by 2) to ensure word alignment) 
    NVMCTRL_REGS->NVMCTRL_ADDR = address >> 1U;
    
    /* Trigger the write command and write the CMDEX key value to the CTRLA register for validity */
    NVMCTRL_REGS->NVMCTRL_CTRLA = (uint16_t)(NVMCTRL_CTRLA_CMD_WP | NVMCTRL_CTRLA_CMDEX_KEY);

    return true;
}

bool nvm_row_erase (uint32_t address) {
    /* Set address and command */
    NVMCTRL_REGS->NVMCTRL_ADDR = address >> 1U;

    /* Write the erase row CMD and validate using the key */
    NVMCTRL_REGS->NVMCTRL_CTRLA = (uint16_t)(NVMCTRL_CTRLA_CMD_ER | NVMCTRL_CTRLA_CMDEX_KEY);

    return true;
}

bool nvm_user_row_erase (uint32_t address) {
    bool rowerase = false;
    // Check if the address is within the user row address bounds
    if ((address >= NVMCTRL_USERROW_START_ADDRESS) && (address <= (NVMCTRL_USERROW_START_ADDRESS + NVMCTRL_USERROW_SIZE)))
    {
        /* Set address and command */
        NVMCTRL_REGS->NVMCTRL_ADDR = address >> 1U;

        NVMCTRL_REGS->NVMCTRL_CTRLA = NVMCTRL_CTRLA_CMD_EAR | NVMCTRL_CTRLA_CMDEX_KEY;


        rowerase = true;
    }

    return rowerase;
}

void nvm_set_security_bit (void) {
    // Set the security bit and validate the operation using the cmdex key
    NVMCTRL_REGS->NVMCTRL_CTRLA = (uint16_t)(NVMCTRL_CTRLA_CMD_SSB | NVMCTRL_CTRLA_CMDEX_KEY);
}

bool nvm_is_busy (void) {
    // Check the ready mask
    return ((NVMCTRL_REGS->NVMCTRL_INTFLAG & NVMCTRL_INTFLAG_READY_Msk)!= NVMCTRL_INTFLAG_READY_Msk);
}

NVMCTRL_ERROR nvm_error_get (void) {
    uint16_t nvm_error;

    /* Get the error bits set */
    nvm_error = (NVMCTRL_REGS->NVMCTRL_STATUS & (NVMCTRL_STATUS_NVME_Msk | NVMCTRL_STATUS_LOCKE_Msk | NVMCTRL_STATUS_PROGE_Msk));

    /* Clear the error bits in both STATUS and INTFLAG register */
    NVMCTRL_REGS->NVMCTRL_STATUS |= nvm_error;

    // Re-enable error interrupts   
    NVMCTRL_REGS->NVMCTRL_INTFLAG = NVMCTRL_INTFLAG_ERROR_Msk;

    return ((NVMCTRL_ERROR) nvm_error);
}

void nvm_region_lock (uint32_t address) {
    
    /* Set address and command */
    /* Shift right by 1 bit to ensure word alignment*/
    NVMCTRL_REGS->NVMCTRL_ADDR = address >> 1U;

    // Lock the region by writing to the CTRLA register and using the key to validate
    NVMCTRL_REGS->NVMCTRL_CTRLA = (uint16_t)(NVMCTRL_CTRLA_CMD_LR | NVMCTRL_CTRLA_CMDEX_KEY);
}

void nvm_region_unlock (uint32_t address) {
    /* Set address and command */
    NVMCTRL_REGS->NVMCTRL_ADDR = address >> 1U;

    // Unlock the region by writing to the CTRLA register and using the key to validate
    NVMCTRL_REGS->NVMCTRL_CTRLA = (uint16_t)(NVMCTRL_CTRLA_CMD_UR | NVMCTRL_CTRLA_CMDEX_KEY);
}