/*******************************************************************************
  Timer System Service Implementation.

  Company:
    Microchip Technology Inc.

  File Name:
    sys_time.c

  Summary:
    Source code for the timer system service implementation.

  Description:
    This file contains the source code for the timer system service
    implementation.
*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <string.h>
#include "system/time/sys_time.h"
#include "configuration.h"
#include "sys_time_local.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************

static SYS_TIME_COUNTER_OBJ gSystemCounterObj;

static SYS_TIME_TIMER_OBJ timers[SYS_TIME_MAX_TIMERS];

/* This a global token counter used to generate unique timer handles */
static uint16_t gSysTimeTokenCount = 1;

// *****************************************************************************
// *****************************************************************************
// Section: Local Functions
// *****************************************************************************
// *****************************************************************************

static inline uint16_t SYS_TIME_UPDATE_TOKEN(uint16_t token)
{
    token++;
    if (token >= SYS_TIME_HANDLE_TOKEN_MAX)
    {
        token = 1;
    }

    return token;
}

static inline uint32_t  SYS_TIME_MAKE_HANDLE(uint16_t token, uint16_t index)
{
    return ((uint32_t)(token) << 16 | (uint32_t)(index));
}

static bool SYS_TIME_ResourceLock(void)
{
    /* We will allow requests to be added from the interrupt
       context of the timer system service. But we must make
       sure that if we are inside interrupt, then we should
       not modify the mutex. */
    if (gSystemCounterObj.interruptNestingCount == 0U)
    {
        /* Acquire mutex only if not in interrupt context.
         * Additionally, disable the interrupt to prevent it from modifying the
         * shared resources asynchronously */

        if(OSAL_MUTEX_Lock(&gSystemCounterObj.timerMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_SUCCESS)
        {
            gSystemCounterObj.hwTimerIntStatus = gSystemCounterObj.timePlib->timerInterruptDisable();
            return true;
        }
        else
        {
            /* If everything is good, this part of code is not executed in an
             * RTOS environment */
            return false;
        }
    }
    /* There should not be a situation where it is not safe to update the shared
     * resources from the interrupt context. This is because, the interrupt is
     * disabled by the thread after acquiring the mutex and enabled only after
     * the update to the shared resource is complete. */
    return true;
}

static void SYS_TIME_ResourceUnlock(void)
{
    gSystemCounterObj.timePlib->timerInterruptRestore(gSystemCounterObj.hwTimerIntStatus);

    if(gSystemCounterObj.interruptNestingCount == 0U)
    {
        /* Mutex is never acquired from the interrupt context and hence should
         * never be released if in interrupt context.
         */
        (void) OSAL_MUTEX_Unlock(&gSystemCounterObj.timerMutex);
    }
}

static SYS_TIME_TIMER_OBJ* SYS_TIME_GetTimerObject(SYS_TIME_HANDLE handle)
{
    SYS_TIME_TIMER_OBJ* timerObj = (SYS_TIME_TIMER_OBJ*)NULL;

    if ((handle != SYS_TIME_HANDLE_INVALID) && (handle != 0U))
    {
        /* Make sure the index is within the bounds */
        if ((handle & SYS_TIME_INDEX_MASK) < (uint32_t)SYS_TIME_MAX_TIMERS)
        {
            /* The timer index is the contained in the lower 16 bits of the buffer
             * handle */
            timerObj = &timers[handle & SYS_TIME_INDEX_MASK];

            /* Make sure the timer handle is still active */
            if ((timerObj->tmrHandle == handle) && (timerObj->inUse == true))
            {
                return timerObj;
            }
        }
    }
    return NULL;
}

static void SYS_TIME_RemoveFromList(SYS_TIME_TIMER_OBJ* delTimer)
{
    SYS_TIME_COUNTER_OBJ* counter = (SYS_TIME_COUNTER_OBJ *)&gSystemCounterObj;
    SYS_TIME_TIMER_OBJ* tmr = counter->tmrActive;
    SYS_TIME_TIMER_OBJ* prevTmr = NULL;

    tmr = counter->tmrActive;

    /* Find the timer to be deleted from the linked list */
    while ((tmr != NULL) && (tmr != delTimer))
    {
        prevTmr = tmr;
        tmr = tmr->tmrNext;
    }

    /* Could not find the timer in the list? return */
    if (tmr == NULL)
    {
        return;
    }

    /* Add the deleted timer pending time to the next timer in the list */
    if (delTimer->tmrNext != NULL)
    {
        /* Use a non-volatile intermediate to prevent dual volatile access in single statement */
        uint32_t relativeTimePending = delTimer->relativeTimePending;
        delTimer->tmrNext->relativeTimePending += relativeTimePending;
    }

    /* If the deleted timer was at the head of the list */
    if (prevTmr == NULL)
    {
        counter->tmrActive = counter->tmrActive->tmrNext;
    }
    else
    {
        /* If the deleted timer was not the head of the list */
        prevTmr->tmrNext = delTimer->tmrNext;
    }

    delTimer->tmrNext = NULL;
}

static void SYS_TIME_AddToList(SYS_TIME_TIMER_OBJ* newTimer)
{
    uint64_t total_time = 0;
    SYS_TIME_COUNTER_OBJ* counter = (SYS_TIME_COUNTER_OBJ* )&gSystemCounterObj;
    SYS_TIME_TIMER_OBJ* tmr = counter->tmrActive;
    SYS_TIME_TIMER_OBJ* prevTmr = NULL;
    uint32_t newTimerTime;

    if (newTimer == NULL)
    {
        return;
    }

    newTimerTime = newTimer->relativeTimePending;

    if (tmr == NULL)
    {
        /* Add the new timer to the top of the list */
        newTimer->relativeTimePending = newTimerTime;
        counter->tmrActive = newTimer;
    }
    else
    {
        /* Find appropriate location to insert the new timer */
        while (tmr != NULL)
        {
            if ((total_time + tmr->relativeTimePending) > newTimerTime)
            {
                break;
            }
            total_time += tmr->relativeTimePending;
            prevTmr = tmr;
            tmr = tmr->tmrNext;
        }

        /* The new timer must be inserted to the head of the list */
        if (prevTmr == NULL)
        {
            /* head = newTimer*/
            counter->tmrActive = newTimer;
            /* head->next = previous head */
            newTimer->tmrNext = tmr;
        }
        else
        {
            newTimer->tmrNext = prevTmr->tmrNext;
            prevTmr->tmrNext = newTimer;
        }

        /* Update the relative times */
        newTimer->relativeTimePending = newTimerTime - (uint32_t)total_time;
        if (newTimer->tmrNext != NULL)
        {
            /* Subtract the new timers time from the next timer in the list */
            /* Use a non-volatile intermediate to prevent dual volatile access in single statement */
            newTimerTime = newTimer->relativeTimePending;
            newTimer->tmrNext->relativeTimePending -= newTimerTime;
        }
    }
}

static uint32_t SYS_TIME_GetTotalElapsedCount(SYS_TIME_TIMER_OBJ* tmr)
{
    SYS_TIME_COUNTER_OBJ* counterObj = (SYS_TIME_COUNTER_OBJ* )&gSystemCounterObj;
    SYS_TIME_TIMER_OBJ* tmrActive = counterObj->tmrActive;
    uint32_t pendingCount = 0;
    uint32_t elapsedCount = 0;

    if (tmr->active == false)
    {
        elapsedCount = 0;
    }
    else
    {
        /* Add time from all timers in the front */
        while ((tmrActive != NULL) && (tmrActive != tmr))
        {
            pendingCount += tmrActive->relativeTimePending;
            tmrActive = tmrActive->tmrNext;
        }

        /* Add the pending time of the requested timer */
        pendingCount += tmrActive->relativeTimePending;

        if (tmrActive->requestedTime >= pendingCount)
        {
            elapsedCount = tmrActive->requestedTime - pendingCount;
        }
        else
        {
            elapsedCount = 0;
        }
    }

    return elapsedCount;
}

static void SYS_TIME_ClientNotify(void)
{
    SYS_TIME_COUNTER_OBJ* counterObj = (SYS_TIME_COUNTER_OBJ* )&gSystemCounterObj;
    SYS_TIME_TIMER_OBJ* tmrActive = counterObj->tmrActive;

    while (tmrActive != NULL)
    {
        if(tmrActive->relativeTimePending == 0U)
        {
            tmrActive->tmrElapsedFlag = true;
            tmrActive->tmrElapsed = true;

            if ((tmrActive->type == SYS_TIME_SINGLE) && (tmrActive->callback != NULL))
            {
                /* Destroy single shot timer for which the callback is registered */
                (void) SYS_TIME_TimerDestroy(tmrActive->tmrHandle);
            }
            else
            {
                /* For periodic timers and delay timers, just remove from the list */
                /* Removing from list does not clear active flag */
                SYS_TIME_RemoveFromList(tmrActive);
                if (tmrActive->type == SYS_TIME_SINGLE)
                {
                    /* Delay timers become inactive after expiry. */
                    tmrActive->active = false;
                }
            }
            if(tmrActive->callback != NULL)
            {
                tmrActive->callback(tmrActive->context);
            }
            /* Get the timer at the top of the list */
            tmrActive = counterObj->tmrActive;
        }
        else
        {
            break;
        }
    }
}

static void SYS_TIME_UpdateTime(void)
{
    uint8_t i;
    SYS_TIME_COUNTER_OBJ* counterObj = (SYS_TIME_COUNTER_OBJ* )&gSystemCounterObj;
    SYS_TIME_TIMER_OBJ* tmr = NULL;

    /* Decrement the counter of the timer at the head of the list */
    tmr = counterObj->tmrActive;

    if ((tmr != NULL) && (tmr->relativeTimePending > 0U))
    {
        tmr->relativeTimePending--;
    }

    /* Update the list and notify the clients */
    SYS_TIME_ClientNotify();

    /* Add the removed timers back into the linked list if the timer type is periodic. */
    for ( i = 0U; i < (uint32_t)SYS_TIME_MAX_TIMERS; i++)
    {
        /* tmrElapsed is cleared anytime a timer is stopped, started, reloaded
         * or destroyed. tmrElapsedFlag is cleared when the application reads
         * the status by calling the SYS_TIME_TimerPeriodHasExpired API.
         */
        if (timers[i].tmrElapsed == true)
        {
            timers[i].tmrElapsed = false;

            if (timers[i].type == SYS_TIME_PERIODIC)
            {
                /* Reload the relative pending time with the requested time */
                timers[i].relativeTimePending = timers[i].requestedTime;
                SYS_TIME_AddToList(&timers[i]);
            }
        }
    }
}

static void SYS_TIME_PLIBCallback(uint32_t status, uintptr_t context)
{
    SYS_TIME_COUNTER_OBJ* counterObj = (SYS_TIME_COUNTER_OBJ *)&gSystemCounterObj;
    SYS_TIME_TIMER_OBJ* tmrActive = counterObj->tmrActive;

    counterObj->swCounter64++;

    if (tmrActive != NULL)
    {
        counterObj->interruptNestingCount++;

        SYS_TIME_UpdateTime();

        counterObj->interruptNestingCount--;
    }

}

static SYS_TIME_HANDLE SYS_TIME_TimerObjectCreate(
    uint32_t count,
    uint32_t period,
    SYS_TIME_CALLBACK callBack,
    uintptr_t context,
    SYS_TIME_CALLBACK_TYPE type
)
{
    SYS_TIME_HANDLE tmrHandle = SYS_TIME_HANDLE_INVALID;
    SYS_TIME_TIMER_OBJ *tmr;
    uint32_t tmrObjIndex = 0;

    if (SYS_TIME_ResourceLock() == false)
    {
        return tmrHandle;
    }
    if((gSystemCounterObj.status == SYS_STATUS_READY) && (period > 0U) && (period >= count))
    {
        tmr = timers;
        while(tmr < &timers[SYS_TIME_MAX_TIMERS])
        {
            if(tmr->inUse == false)
            {
                tmr->inUse = true;
                tmr->active = false;
                tmr->tmrElapsedFlag = false;
                tmr->tmrElapsed = false;
                tmr->type = type;
                tmr->requestedTime = period;
                tmr->callback = callBack;
                tmr->context = context;
                tmr->relativeTimePending = period - count;

                /* Assign a handle to this request. The timer handle must be unique. */
                tmr->tmrHandle = (SYS_TIME_HANDLE) SYS_TIME_MAKE_HANDLE(gSysTimeTokenCount, (uint16_t)tmrObjIndex);

                /* Update the token number. */
                gSysTimeTokenCount = SYS_TIME_UPDATE_TOKEN(gSysTimeTokenCount);

                tmrHandle = tmr->tmrHandle;
                break;
            }
            tmr++;
            tmrObjIndex++;
        }
    }

    SYS_TIME_ResourceUnlock();
    return tmrHandle;
}

/* MISRA C-2012 Rule 11.3 deviated:1 Deviation record ID -  H3_MISRAC_2012_R_11_3_DR_1 */
static void SYS_TIME_CounterInit(const SYS_MODULE_INIT* init)
{
    SYS_TIME_COUNTER_OBJ* counterObj = (SYS_TIME_COUNTER_OBJ *)&gSystemCounterObj;
    const SYS_TIME_INIT* initData = (const SYS_TIME_INIT *)init;

    counterObj->timePlib = initData->timePlib;
    counterObj->hwTimerTickFreq = (float)SYS_TIME_TICK_FREQ_IN_HZ;
    counterObj->hwTimerIntNum = initData->hwTimerIntNum;

    counterObj->swCounter64 = 0;
    counterObj->tmrActive = NULL;
    counterObj->interruptNestingCount = 0;

    counterObj->timePlib->timerCallbackSet(SYS_TIME_PLIBCallback, 0);
    counterObj->timePlib->timerStart();
}

/* MISRAC 2012 deviation block end */

// *****************************************************************************
// *****************************************************************************
// Section: System Interface Functions
// *****************************************************************************
// *****************************************************************************
SYS_MODULE_OBJ SYS_TIME_Initialize( const SYS_MODULE_INDEX index, const SYS_MODULE_INIT * const init )
{
    if(init == NULL || index != (uint32_t)SYS_TIME_INDEX_0)
    {
        return SYS_MODULE_OBJ_INVALID;
    }
    /* Create mutex to guard from multiple contesting threads */
    if(OSAL_MUTEX_Create(&gSystemCounterObj.timerMutex) != OSAL_RESULT_SUCCESS)
    {
        return SYS_MODULE_OBJ_INVALID;
    }

    SYS_TIME_CounterInit((const SYS_MODULE_INIT *)init);
    (void) memset(timers, 0, sizeof(timers));

    gSystemCounterObj.status = SYS_STATUS_READY;

    return (SYS_MODULE_OBJ)&gSystemCounterObj;
}

void SYS_TIME_Deinitialize ( SYS_MODULE_OBJ object )
{
    SYS_TIME_COUNTER_OBJ * counterObj = (SYS_TIME_COUNTER_OBJ *)&gSystemCounterObj;

    if(counterObj != (SYS_TIME_COUNTER_OBJ *)object)
    {
        return;
    }

    counterObj->timePlib->timerStop();

    (void) memset(&timers, 0, sizeof(timers));
    (void) memset(&gSystemCounterObj, 0, sizeof(gSystemCounterObj));

    counterObj->status = SYS_STATUS_UNINITIALIZED;

    return;
}

SYS_STATUS SYS_TIME_Status ( SYS_MODULE_OBJ object )
{
    SYS_TIME_COUNTER_OBJ * counterObj = (SYS_TIME_COUNTER_OBJ *)&gSystemCounterObj;
    SYS_STATUS status = SYS_STATUS_UNINITIALIZED;

    if(counterObj == (SYS_TIME_COUNTER_OBJ *)object)
    {
        status = counterObj->status;
    }

    return status;
}

// *****************************************************************************
// *****************************************************************************
// Section:  SYS TIME 32-bit Counter and Conversion Functions
// *****************************************************************************
// *****************************************************************************
uint32_t SYS_TIME_FrequencyGet ( void )
{
    return (uint32_t)gSystemCounterObj.hwTimerTickFreq;
}

uint64_t SYS_TIME_Counter64Get ( void )
{
    SYS_TIME_COUNTER_OBJ * counterObj = (SYS_TIME_COUNTER_OBJ *)&gSystemCounterObj;
    uint64_t counter64 = 0;
    bool interruptState;

	interruptState = SYS_INT_Disable();

    counter64 = counterObj->swCounter64;

    SYS_INT_Restore(interruptState);

    return counter64;
}

uint32_t SYS_TIME_CounterGet ( void )
{
    uint32_t counter32;

    counter32 = (uint32_t)SYS_TIME_Counter64Get();

    return counter32;
}

void SYS_TIME_CounterSet ( uint32_t count )
{
    bool interruptState;

	interruptState = SYS_INT_Disable();

    gSystemCounterObj.swCounter64 = count;

    SYS_INT_Restore(interruptState);
}

/* MISRA C-2012 Rule 10.8 deviated:2 Deviation record ID -  H3_MISRAC_2012_R_10_8_DR_1 */

uint32_t  SYS_TIME_CountToUS ( uint32_t count )
{
    return (uint32_t) (((uint64_t)count * 1000000u) / gSystemCounterObj.hwTimerTickFreq);
}

uint32_t  SYS_TIME_CountToMS ( uint32_t count )
{
    return (uint32_t) (((uint64_t)count * 1000u) / gSystemCounterObj.hwTimerTickFreq);
}

/* MISRA C-2012 Rule 10.1 deviated:2 Deviation record ID -  H3_MISRAC_2012_R_10_1_DR_1 */

/* MISRAC 2012 deviation block end */

uint32_t SYS_TIME_USToCount ( uint32_t us )
{
    float count = ((us * gSystemCounterObj.hwTimerTickFreq) / 1000000);

    return (uint32_t) ((uint32_t)count + ((count - (uint32_t)count) > 0));
}

uint32_t SYS_TIME_MSToCount ( uint32_t ms )
{
    float count = ((ms * gSystemCounterObj.hwTimerTickFreq) / 1000);

    return (uint32_t) ((uint32_t)count + ((count - (uint32_t)count) > 0));
}
/* MISRAC 2012 deviation block end */

// *****************************************************************************
// *****************************************************************************
// Section:  SYS TIME 32-bit Software Timers
// *****************************************************************************
// *****************************************************************************
SYS_TIME_HANDLE SYS_TIME_TimerCreate(
    uint32_t count,
    uint32_t period,
    SYS_TIME_CALLBACK callBack,
    uintptr_t context,
    SYS_TIME_CALLBACK_TYPE type
)
{
    /* Single shot timers must register a callback. This check must be performed
     * here itself as SYS_TIME_TimerObjectCreate are called by delay APIs as well
     * which are single shot timers with callBack set to NULL. */
    if ((type == SYS_TIME_SINGLE) && (callBack == NULL))
    {
        return SYS_TIME_HANDLE_INVALID;
    }

    return SYS_TIME_TimerObjectCreate(count, period, callBack, context, type);
}

SYS_TIME_RESULT SYS_TIME_TimerReload(
    SYS_TIME_HANDLE handle,
    uint32_t count,
    uint32_t period,
    SYS_TIME_CALLBACK callBack,
    uintptr_t context,
    SYS_TIME_CALLBACK_TYPE type
)
{
    SYS_TIME_TIMER_OBJ *tmr = NULL;
    SYS_TIME_RESULT result = SYS_TIME_ERROR;

    if (SYS_TIME_ResourceLock() == false)
    {
        return result;
    }

    /* Single shot timers must register a callback. */
    if ((type == SYS_TIME_SINGLE) && (callBack == NULL))
    {
        SYS_TIME_ResourceUnlock();
        return result;
    }

    tmr = SYS_TIME_GetTimerObject(handle);

    if((tmr != NULL) && (period > 0U) && (period >= count))
    {
        /* Temporarily remove the timer from the list. Update and then add it back */
        SYS_TIME_RemoveFromList(tmr);
        tmr->tmrElapsedFlag = false;
        tmr->tmrElapsed = false;
        tmr->type = type;
        tmr->requestedTime = period;
        tmr->relativeTimePending = period - count;
        tmr->callback = callBack;
        tmr->context = context;
        SYS_TIME_AddToList(tmr);
        tmr->active = true;
        result = SYS_TIME_SUCCESS;
    }

    SYS_TIME_ResourceUnlock();
    return result;
}

SYS_TIME_RESULT SYS_TIME_TimerDestroy(SYS_TIME_HANDLE handle)
{
    SYS_TIME_TIMER_OBJ *tmr = NULL;
    SYS_TIME_RESULT result = SYS_TIME_ERROR;

    if (SYS_TIME_ResourceLock() == false)
    {
        return result;
    }

    tmr = SYS_TIME_GetTimerObject(handle);

    if(tmr != NULL)
    {
        if(tmr->active == true)
        {
            SYS_TIME_RemoveFromList(tmr);
            tmr->active = false;
        }
        tmr->tmrElapsedFlag = false;
        tmr->tmrElapsed = false;
        tmr->inUse = false;
        result = SYS_TIME_SUCCESS;
    }

    SYS_TIME_ResourceUnlock();
    return result;
}

SYS_TIME_RESULT SYS_TIME_TimerStart(SYS_TIME_HANDLE handle)
{
    SYS_TIME_TIMER_OBJ *tmr = NULL;
    SYS_TIME_RESULT result = SYS_TIME_ERROR;

    if (SYS_TIME_ResourceLock() == false)
    {
        return result;
    }

    tmr = SYS_TIME_GetTimerObject(handle);

    if(tmr != NULL)
    {
        if (tmr->active == false)
        {
            /* Single shot timers can be started back from the single shot timer's
             * callback where relativeTimePending is 0. For this reason, if the
             * relativeTimePending is 0, it is reloaded with the requested time.
             */
            if (tmr->relativeTimePending == 0U)
            {
                tmr->relativeTimePending = tmr->requestedTime;
            }

            SYS_TIME_AddToList(tmr);

            tmr->tmrElapsedFlag = false;
            tmr->tmrElapsed = false;
            tmr->active = true;
        }
        result = SYS_TIME_SUCCESS;
    }

    SYS_TIME_ResourceUnlock();
    return result;
}

SYS_TIME_RESULT SYS_TIME_TimerStop(SYS_TIME_HANDLE handle)
{
    SYS_TIME_TIMER_OBJ *tmr = NULL;
    SYS_TIME_RESULT result = SYS_TIME_ERROR;

    if (SYS_TIME_ResourceLock() == false)
    {
        return result;
    }

    tmr = SYS_TIME_GetTimerObject(handle);

    if(tmr != NULL)
    {
        if (tmr->active == true)
        {
            SYS_TIME_RemoveFromList(tmr);
            tmr->tmrElapsedFlag = false;
            tmr->tmrElapsed = false;
            tmr->active = false;
            /* Make sure the timer is started fresh, when next time the timer start API is called */
            tmr->relativeTimePending = tmr->requestedTime;
        }
        result = SYS_TIME_SUCCESS;
    }

    SYS_TIME_ResourceUnlock();
    return result;
}

SYS_TIME_RESULT SYS_TIME_TimerCounterGet(SYS_TIME_HANDLE handle, uint32_t* count)
{
    SYS_TIME_TIMER_OBJ* tmr = NULL;
    SYS_TIME_RESULT result = SYS_TIME_ERROR;

    if (SYS_TIME_ResourceLock() == false)
    {
        return result;
    }

    if (count != NULL)
    {
        tmr = SYS_TIME_GetTimerObject(handle);
        if(tmr != NULL)
        {
            *count = SYS_TIME_GetTotalElapsedCount(tmr);
            result = SYS_TIME_SUCCESS;
        }
    }

    SYS_TIME_ResourceUnlock();
    return result;
}

bool SYS_TIME_TimerPeriodHasExpired(SYS_TIME_HANDLE handle)
{
    SYS_TIME_TIMER_OBJ* tmr = NULL;
    bool status = false;

    if (SYS_TIME_ResourceLock() == false)
    {
        return status;
    }

    tmr = SYS_TIME_GetTimerObject(handle);

    if(tmr != NULL)
    {
        status = tmr->tmrElapsedFlag;
        /* After the application reads the status, clear it. */
        tmr->tmrElapsedFlag = false;
    }

    SYS_TIME_ResourceUnlock();
    return status;
}


// *****************************************************************************
// *****************************************************************************
// Section:  SYS TIME Delay Interface Functions
// *****************************************************************************
// *****************************************************************************
SYS_TIME_RESULT SYS_TIME_DelayUS ( uint32_t us, SYS_TIME_HANDLE* handle )
{
    SYS_TIME_RESULT result = SYS_TIME_ERROR;

    if ((handle == NULL) || (us == 0U))
    {
        return result;
    }

    *handle = SYS_TIME_TimerObjectCreate(0, SYS_TIME_USToCount(us), NULL, 0, SYS_TIME_SINGLE);
    if(*handle != SYS_TIME_HANDLE_INVALID)
    {
       (void) SYS_TIME_TimerStart(*handle);
        result = SYS_TIME_SUCCESS;
    }

    return result;
}

SYS_TIME_RESULT SYS_TIME_DelayMS ( uint32_t ms, SYS_TIME_HANDLE* handle )
{
    SYS_TIME_RESULT result = SYS_TIME_ERROR;

    if ((handle == NULL) || (ms == 0U))
    {
        return result;
    }

    *handle = SYS_TIME_TimerObjectCreate(0, SYS_TIME_MSToCount(ms), NULL, 0, SYS_TIME_SINGLE);
    if(*handle != SYS_TIME_HANDLE_INVALID)
    {
        (void) SYS_TIME_TimerStart(*handle);
        result = SYS_TIME_SUCCESS;
    }

    return result;
}

bool SYS_TIME_DelayIsComplete ( SYS_TIME_HANDLE handle )
{
    bool status = false;

    if(true == SYS_TIME_TimerPeriodHasExpired(handle))
    {
       (void) SYS_TIME_TimerDestroy(handle);
        status = true;
    }

    return status;
}


// *****************************************************************************
// *****************************************************************************
// Section:  SYS TIME Callback Interface Functions
// *****************************************************************************
// *****************************************************************************
SYS_TIME_HANDLE SYS_TIME_CallbackRegisterUS ( SYS_TIME_CALLBACK callback, uintptr_t context, uint32_t us, SYS_TIME_CALLBACK_TYPE type )
{
    SYS_TIME_HANDLE handle = SYS_TIME_HANDLE_INVALID;

    /* Single shot timers must register a callback. */
    if ((type == SYS_TIME_SINGLE) && (callback == NULL))
    {
        return handle;
    }

    if (us != 0U)
    {
        handle = SYS_TIME_TimerObjectCreate(0, SYS_TIME_USToCount(us), callback, context, type);
        if(handle != SYS_TIME_HANDLE_INVALID)
        {
            (void) SYS_TIME_TimerStart(handle);
        }
    }

    return handle;
}

SYS_TIME_HANDLE SYS_TIME_CallbackRegisterMS ( SYS_TIME_CALLBACK callback, uintptr_t context, uint32_t ms, SYS_TIME_CALLBACK_TYPE type )
{
    SYS_TIME_HANDLE handle = SYS_TIME_HANDLE_INVALID;

    /* Single shot timers must register a callback. */
    if ((type == SYS_TIME_SINGLE) && (callback == NULL))
    {
        return handle;
    }

    if (ms != 0U)
    {
        handle = SYS_TIME_TimerObjectCreate(0, SYS_TIME_MSToCount(ms), callback, context, type);
        if(handle != SYS_TIME_HANDLE_INVALID)
        {
            (void) SYS_TIME_TimerStart(handle);
        }
    }

    return handle;
}
