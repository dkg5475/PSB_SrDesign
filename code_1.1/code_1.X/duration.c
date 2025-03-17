    #include "duration.h"

    //!MODULE: duration
    //!
    //!TC3 Wrapper functions used for the temperature slope calculations \n\n
    //!
    //!This module is used as a wrapper around TC3 function calls to calculate the time spent over an interval\n\n
    //!
    //!The duration module defines the following functions:\n
    //!    - Defines the startTimer, endTimer, and calcElapsed functions\n
    //!    - Also defines a callback interrupt handler for when the timer ends
    //!
    //!@param None
    //!@return None

duration_timer_t timer = {
    .elapsedSeconds = 0,
    .startTime = 0,
    .endTime = 0,
    .elapsedTime = 0
};

void startTimer (void) {
    /* Start the timer and get its value */
    TC3_TimerStart();
    timer.startTime = TC3_Timer16bitCounterGet(); 
}

void endTimer (void) {
    /* Get the value of the timer right before it ends*/
    timer.endTime = TC3_Timer16bitCounterGet();
    TC3_TimerStop();
}

void calcElapsed (void) {
    if (timer.endTime >= timer.startTime) {
        timer.elapsedTime = timer.endTime - timer.startTime;
    }
    else { /* To handle overflow */
        timer.elapsedTime = (float)((65535 - timer.startTime) + timer.endTime + 1 );
    }
    timer.elapsedSeconds = timer.elapsedTime / TIMER_FREQ;
}



