/*******************************************************************************
  Non-Volatile Memory Controller(NVMCTRL) PLIB.

  Company:
    Microchip Technology Inc.

  File Name:
    plib_nvmctrl.h

  Summary:
    Interface definition of NVMCTRL Plib.

  Description:
    This file defines the interface for the NVMCTRL Plib.
    It allows user to Program, Erase and lock the on-chip Non Volatile Flash
    Memory.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef PLIB_NVMCTRL_H
#define PLIB_NVMCTRL_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "device.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C++ Compatibility
 extern "C" {
#endif

// DOM-IGNORE-END
// *****************************************************************************
// *****************************************************************************
// Section: Preprocessor macros
// *****************************************************************************
// *****************************************************************************

#define NVMCTRL_FLASH_START_ADDRESS        (0x00000000U)
#define NVMCTRL_FLASH_PAGESIZE             (64U)
#define NVMCTRL_FLASH_ROWSIZE              (256U)

#define NVMCTRL_EMULATED_EEPROM_START_ADDRESS  (0x40000U)
#define NVMCTRL_EMULATED_EEPROM_PAGESIZE       (64U)
#define NVMCTRL_EMULATED_EEPROM_SIZE           (0U)

#define NVMCTRL_RWWEEPROM_START_ADDRESS    (0x00400000U)
#define NVMCTRL_RWWEEPROM_SIZE             (0x2000U)
#define NVMCTRL_RWWEEPROM_PAGESIZE         (64U)
#define NVMCTRL_RWWEEPROM_ROWSIZE          (256U)

#define NVMCTRL_USERROW_START_ADDRESS     (0x00804000U)
#define NVMCTRL_USERROW_SIZE              (0x100U)
#define NVMCTRL_USERROW_PAGESIZE          (64U)

#define NVMCTRL_ERROR_NONE 0x0U
#define NVMCTRL_ERROR_PROG 0x4U
#define NVMCTRL_ERROR_LOCK 0x8U
#define NVMCTRL_ERROR_NVM 0x10U

typedef uint16_t NVMCTRL_ERROR;


void NVMCTRL_Initialize(void);

bool NVMCTRL_Read( uint32_t *data, uint32_t length, const uint32_t address );

bool NVMCTRL_PageWrite( uint32_t *data, const uint32_t address );


bool NVMCTRL_PageBufferWrite( uint32_t *data, const uint32_t address);

bool NVMCTRL_PageBufferCommit( const uint32_t address);


bool NVMCTRL_RowErase( uint32_t address );

bool NVMCTRL_RWWEEPROM_Read( uint32_t *data, uint32_t length, const uint32_t address );

bool NVMCTRL_RWWEEPROM_PageWrite ( uint32_t *data, const uint32_t address );

bool NVMCTRL_RWWEEPROM_RowErase ( uint32_t address );

NVMCTRL_ERROR NVMCTRL_ErrorGet( void );

bool NVMCTRL_IsBusy( void );

void NVMCTRL_RegionLock (uint32_t address);

void NVMCTRL_RegionUnlock (uint32_t address);

void NVMCTRL_SecurityBitSet(void);


bool NVMCTRL_USER_ROW_PageWrite( uint32_t *data, const uint32_t address );

bool NVMCTRL_USER_ROW_RowErase( uint32_t address );

void NVMCTRL_CacheInvalidate ( void );

// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C++ Compatibility
}
#endif
// DOM-IGNORE-END
#endif // PLIB_NVMCTRL_H
