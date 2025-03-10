/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <math.h>                       // Defines natural log (ln))
#include "definitions.h"                // SYS function prototypes
#include "duration.h"
#include "sensor.h"
#include "convert.h"
#include "fis.h"
#include "dac_10bit.h"



int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SDADC_Init(); // Init SDADC
    DAC_Initialize(); //Init DAC
    
    while ( true )
    {   
        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}



/*******************************************************************************
 End of File
*/

