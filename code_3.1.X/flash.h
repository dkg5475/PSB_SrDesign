#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* Macros */
#define NVMCTRL_FLASH_START_ADDRESS        (0x00000000U)
#define NVMCTRL_FLASH_PAGESIZE             (64U)
#define NVMCTRL_FLASH_ROWSIZE              (256U)

#define NVMCTRL_USERROW_START_ADDRESS     (0x00804000U)
#define NVMCTRL_USERROW_SIZE              (0x100U)
#define NVMCTRL_USERROW_PAGESIZE          (64U)

#define NVMCTRL_ERROR_NONE 0x0U
#define NVMCTRL_ERROR_PROG 0x4U
#define NVMCTRL_ERROR_LOCK 0x8U
#define NVMCTRL_ERROR_NVM 0x10U

typedef uint16_t NVMCTRL_ERROR;

/* Function prototypes*/
void nvm_init               (void);
bool nvm_read               (uint32_t *data, uint32_t length, const uint32_t address);
bool nvm_page_write         (uint32_t *data, const uint32_t address);
bool nvm_row_erase          (uint32_t address);
bool nvm_user_row_erase     (uint32_t address);
void nvm_set_security_bit   (void);
bool nvm_is_busy            (void);
NVMCTRL_ERROR nvm_error_get (void);
void nvm_region_lock        (uint32_t address);
void nvm_region_unlock      (uint32_t address);



#endif