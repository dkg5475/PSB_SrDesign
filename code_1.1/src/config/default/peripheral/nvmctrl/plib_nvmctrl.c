/*******************************************************************************
  Non-Volatile Memory Controller(NVMCTRL) PLIB.

  Company:
    Microchip Technology Inc.

  File Name:
    plib_nvmctrl.c

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <string.h>
#include "interrupts.h"
#include "plib_nvmctrl.h"


// *****************************************************************************
// *****************************************************************************
// Section: NVMCTRL Implementation
// *****************************************************************************
// *****************************************************************************


void NVMCTRL_Initialize(void)
{
    NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_READMODE_NO_MISS_PENALTY | NVMCTRL_CTRLB_SLEEPPRM_WAKEONACCESS | NVMCTRL_CTRLB_RWS(2UL) | NVMCTRL_CTRLB_MANW_Msk;
}

void NVMCTRL_CacheInvalidate(void)
{
    NVMCTRL_REGS->NVMCTRL_CTRLA = (uint16_t)(NVMCTRL_CTRLA_CMD_INVALL | NVMCTRL_CTRLA_CMDEX_KEY);
}
bool NVMCTRL_RWWEEPROM_Read( uint32_t *data, uint32_t length, const uint32_t address )
{
    uint32_t *paddress = (uint32_t*)address;
    (void)memcpy(data, paddress, length);
    return true;
}

bool NVMCTRL_RWWEEPROM_PageWrite ( uint32_t *data, const uint32_t address )
{
    uint32_t i;
    uint32_t * paddress = (uint32_t *)address;

    /* Writing 32-bit words in the given address */
    for ( i = 0U; i < (NVMCTRL_RWWEEPROM_PAGESIZE/4U); i++)
    {
        *paddress = *(data + i);
        paddress++;
    }

     /* Set address and command */
    NVMCTRL_REGS->NVMCTRL_ADDR = address >> 1U;

    NVMCTRL_REGS->NVMCTRL_CTRLA = (uint16_t)(NVMCTRL_CTRLA_CMD_RWWEEWP | NVMCTRL_CTRLA_CMDEX_KEY);

    return true;
}

bool NVMCTRL_RWWEEPROM_RowErase( uint32_t address )
{
     /* Set address and command */
    NVMCTRL_REGS->NVMCTRL_ADDR = address >> 1U;

    NVMCTRL_REGS->NVMCTRL_CTRLA = (uint16_t)(NVMCTRL_CTRLA_CMD_RWWEEER | NVMCTRL_CTRLA_CMDEX_KEY);

    return true;
}
bool NVMCTRL_Read( uint32_t *data, uint32_t length, const uint32_t address )
{
    uint32_t *paddress = (uint32_t*)address;
    (void)memcpy(data, paddress, length);
    return true;
}

bool NVMCTRL_PageBufferWrite( uint32_t *data, const uint32_t address)
{
    uint32_t i;
    uint32_t * paddress = (uint32_t *)address;

    /* writing 32-bit data into the given address */
    for (i = 0U; i < (NVMCTRL_FLASH_PAGESIZE/4U); i++)
    {
        *paddress = *(data + i);
        paddress++;
    }

    return true;
}

bool NVMCTRL_PageBufferCommit( const uint32_t address)
{
    uint16_t command = NVMCTRL_CTRLA_CMD_WP_Val;

    /* Set address and command */
    NVMCTRL_REGS->NVMCTRL_ADDR = address >> 1U;

    if (address >= NVMCTRL_RWWEEPROM_START_ADDRESS)
    {
        command = NVMCTRL_CTRLA_CMD_RWWEEWP;
    }

    NVMCTRL_REGS->NVMCTRL_CTRLA = (uint16_t)(command | NVMCTRL_CTRLA_CMDEX_KEY);


    return true;
}

bool NVMCTRL_PageWrite( uint32_t *data, const uint32_t address )
{
    uint32_t i;
    uint32_t * paddress = (uint32_t *)address;

    /* writing 32-bit data into the given address */
    for (i = 0U; i < (NVMCTRL_FLASH_PAGESIZE/4U); i++)
    {
        *paddress = *(data + i);
        paddress++;
    }

    /* Set address and command */
    /* Shift right by 1 bit to ensure word alignment */
    NVMCTRL_REGS->NVMCTRL_ADDR = address >> 1U;

    // Trigger the page write command to NVMCTRL register
    // CMDEX_KEY confirms that the write operation command is valid 
    NVMCTRL_REGS->NVMCTRL_CTRLA = (uint16_t)(NVMCTRL_CTRLA_CMD_WP_Val | NVMCTRL_CTRLA_CMDEX_KEY);

    return true;
}

bool NVMCTRL_RowErase( uint32_t address )
{
    /* Set address and command */
    NVMCTRL_REGS->NVMCTRL_ADDR = address >> 1U;

    NVMCTRL_REGS->NVMCTRL_CTRLA = (uint16_t)(NVMCTRL_CTRLA_CMD_ER_Val | NVMCTRL_CTRLA_CMDEX_KEY);

    return true;
}

bool NVMCTRL_USER_ROW_PageWrite( uint32_t *data, const uint32_t address )
{
    uint32_t i;
    uint32_t * paddress = (uint32_t *)address;
    bool pagewrite_val = false;

    if ((address >= NVMCTRL_USERROW_START_ADDRESS) && (address <= ((NVMCTRL_USERROW_START_ADDRESS + NVMCTRL_USERROW_SIZE) - NVMCTRL_USERROW_PAGESIZE)))
    {
        /* writing 32-bit data into the given address */
        for (i = 0U; i < (NVMCTRL_USERROW_PAGESIZE/4U); i++)
        {
            *paddress = data[i];
                      paddress++;
        }

        /* Set address and command */
        NVMCTRL_REGS->NVMCTRL_ADDR = address >> 1U;

        NVMCTRL_REGS->NVMCTRL_CTRLA = NVMCTRL_CTRLA_CMD_WAP_Val | NVMCTRL_CTRLA_CMDEX_KEY;


        pagewrite_val = true;
    }

    return pagewrite_val;
}

bool NVMCTRL_USER_ROW_RowErase( uint32_t address )
{
    bool rowerase = false;
    if ((address >= NVMCTRL_USERROW_START_ADDRESS) && (address <= (NVMCTRL_USERROW_START_ADDRESS + NVMCTRL_USERROW_SIZE)))
    {
        /* Set address and command */
        NVMCTRL_REGS->NVMCTRL_ADDR = address >> 1U;

        NVMCTRL_REGS->NVMCTRL_CTRLA = NVMCTRL_CTRLA_CMD_EAR_Val | NVMCTRL_CTRLA_CMDEX_KEY;


        rowerase = true;
    }

    return rowerase;
}

NVMCTRL_ERROR NVMCTRL_ErrorGet( void )
{
    uint16_t nvm_error;

    /* Get the error bits set */
    nvm_error = (NVMCTRL_REGS->NVMCTRL_STATUS & (NVMCTRL_STATUS_NVME_Msk | NVMCTRL_STATUS_LOCKE_Msk | NVMCTRL_STATUS_PROGE_Msk));

    /* Clear the error bits in both STATUS and INTFLAG register */
    NVMCTRL_REGS->NVMCTRL_STATUS |= nvm_error;

    NVMCTRL_REGS->NVMCTRL_INTFLAG = NVMCTRL_INTFLAG_ERROR_Msk;

    return ((NVMCTRL_ERROR) nvm_error);
}

bool NVMCTRL_IsBusy(void)
{
    return ((NVMCTRL_REGS->NVMCTRL_INTFLAG & NVMCTRL_INTFLAG_READY_Msk)!= NVMCTRL_INTFLAG_READY_Msk);
}

void NVMCTRL_RegionLock(uint32_t address)
{
    /* Set address and command */
    NVMCTRL_REGS->NVMCTRL_ADDR = address >> 1U;

    NVMCTRL_REGS->NVMCTRL_CTRLA = (uint16_t)(NVMCTRL_CTRLA_CMD_LR_Val | NVMCTRL_CTRLA_CMDEX_KEY);
}

void NVMCTRL_RegionUnlock(uint32_t address)
{
    /* Set address and command */
    NVMCTRL_REGS->NVMCTRL_ADDR = address >> 1U;

    NVMCTRL_REGS->NVMCTRL_CTRLA = (uint16_t)(NVMCTRL_CTRLA_CMD_UR_Val | NVMCTRL_CTRLA_CMDEX_KEY);
}

void NVMCTRL_SecurityBitSet(void)
{
    NVMCTRL_REGS->NVMCTRL_CTRLA = (uint16_t)(NVMCTRL_CTRLA_CMD_SSB_Val | NVMCTRL_CTRLA_CMDEX_KEY);
}
