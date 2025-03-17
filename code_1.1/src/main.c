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
// Custom header and source files are placed in code_1.X
#include "../code_1.X/duration.h"                
#include "../code_1.X/sensor.h"
#include "../code_1.X/convert.h"
#include "../code_1.X/fis.h"
#include "../code_1.X/dac_10bit.h"

int main (void)
{
    /* Initialize all modules */
    SYS_Initialize (NULL);
     
    SDADC_Init(); // Initialize SDADC
    DAC_Initialize(); //Initialize DAC
    
    while (true)
    {   
        
    }
    
    
    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}



/*******************************************************************************
 End of File
*/

