/*******************************************************************************
  SDADC PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_sdadc.c

  Summary
    SDADC PLIB Implementation File.

  Description
    This file defines the interface to the SDADC peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:
    None.

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
/* This section lists the other files that are included in this file.
*/

#include "device.h"
#include "interrupts.h"
#include "plib_sdadc.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

volatile static SDADC_CALLBACK_OBJECT SDADC_CallbackObj;
// *****************************************************************************
// *****************************************************************************
// Section: SDADC Implementation
// *****************************************************************************
// *****************************************************************************

/* Initialize SDADC module as per MHC configurations */
void SDADC_Initialize( void )
{
    /* Software Reset */
    SDADC_REGS->SDADC_CTRLA = (uint8_t)SDADC_CTRLA_SWRST_Msk;

    while((SDADC_REGS->SDADC_SYNCBUSY & SDADC_SYNCBUSY_SWRST_Msk) == SDADC_SYNCBUSY_SWRST_Msk)
    {
        /* Wait for synchronization */
    }

    /* Set prescaler, over sampling ratio and skip count */
    SDADC_REGS->SDADC_CTRLB = (uint16_t)(SDADC_CTRLB_PRESCALER_DIV4 | SDADC_CTRLB_OSR_OSR1024 | SDADC_CTRLB_SKPCNT(2UL));

    /* Configure reference voltage */
    SDADC_REGS->SDADC_REFCTRL = (uint8_t)SDADC_REFCTRL_REFSEL_AREFB;

    SDADC_REGS->SDADC_SEQCTRL = SDADC_SEQCTRL_SEQEN(1UL << 0U) | SDADC_SEQCTRL_SEQEN(1UL << 1U) | SDADC_SEQCTRL_SEQEN(1UL << 2U);

    /* Clear all interrupts */
    SDADC_REGS->SDADC_INTFLAG = (uint8_t)SDADC_INTFLAG_Msk;

    /* Enable interrupt */
    SDADC_REGS->SDADC_INTENSET = (uint8_t)(SDADC_INTENSET_RESRDY_Msk);
    SDADC_CallbackObj.callback = NULL;


    /* Configure Run in standby, On demand property */
    SDADC_REGS->SDADC_CTRLA |= (uint8_t)(SDADC_CTRLA_RUNSTDBY_Msk | SDADC_CTRLA_ONDEMAND_Msk);

    /* Enable SDADC */
    SDADC_REGS->SDADC_CTRLA |= (uint8_t)SDADC_CTRLA_ENABLE_Msk;

    while((SDADC_REGS->SDADC_SYNCBUSY) != 0U)
    {
        /* Wait for synchronization */
    }
}

void SDADC_Enable( void )
{
    SDADC_REGS->SDADC_CTRLA |= (uint8_t)SDADC_CTRLA_ENABLE_Msk;
    while((SDADC_REGS->SDADC_SYNCBUSY & SDADC_SYNCBUSY_ENABLE_Msk) == SDADC_SYNCBUSY_ENABLE_Msk)
    {
        /* Wait for synchronization */
    }
}

void SDADC_Disable( void )
{
    SDADC_REGS->SDADC_CTRLA &= (uint8_t)(~SDADC_CTRLA_ENABLE_Msk);
    while((SDADC_REGS->SDADC_SYNCBUSY & SDADC_SYNCBUSY_ENABLE_Msk) == SDADC_SYNCBUSY_ENABLE_Msk)
    {
        /* Wait for synchronization */
    }
}

 
void SDADC_ConversionStart( void )
{
    /* Start conversion */
    SDADC_REGS->SDADC_SWTRIG = (uint8_t)SDADC_SWTRIG_START_Msk;

    while((SDADC_REGS->SDADC_SYNCBUSY & SDADC_SYNCBUSY_SWTRIG_Msk) == SDADC_SYNCBUSY_SWTRIG_Msk)
    {
        /* Synchronization between SWTRIG start with the clock domain */
    }
}

int16_t SDADC_ConversionResultGet( void )
{
    /* right-shift by 8-bits to get signed 16-bit result */
    uint32_t result = SDADC_REGS->SDADC_RESULT >> 8U;
    return ((int16_t)result);
}

bool SDADC_ConversionSequenceIsFinished(void)
{
    bool seq_status = false;
    if ((SDADC_REGS->SDADC_SEQSTATUS & SDADC_SEQSTATUS_SEQBUSY_Msk) != SDADC_SEQSTATUS_SEQBUSY_Msk)
    {
        seq_status = true;
    }
    return seq_status;
}


void SDADC_CallbackRegister( SDADC_CALLBACK callback, uintptr_t context )
{
    SDADC_CallbackObj.callback = callback;

    SDADC_CallbackObj.context = context;
}


void __attribute__((used)) SDADC_InterruptHandler( void )
{
    SDADC_STATUS status;
    status = SDADC_REGS->SDADC_INTFLAG;
    /* Clear interrupt flags */
    SDADC_REGS->SDADC_INTFLAG = (uint8_t)SDADC_INTFLAG_Msk;

    if (SDADC_CallbackObj.callback != NULL)
    {
        uintptr_t context = SDADC_CallbackObj.context;
        SDADC_CallbackObj.callback(status, context);
    }

}


