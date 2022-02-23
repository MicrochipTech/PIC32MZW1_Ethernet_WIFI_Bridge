/*******************************************************************************
  System Definitions

  File Name:
    definitions.h

  Summary:
    project system definitions.

  Description:
    This file contains the system-wide prototypes and definitions for a project.

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

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "crypto/crypto.h"
#include "system/time/sys_time.h"
#include "peripheral/coretimer/plib_coretimer.h"
#include "system/int/sys_int.h"
#include "system/reset/sys_reset.h"
#include "osal/osal.h"
#include "system/debug/sys_debug.h"
#include "driver/miim/drv_miim.h"
#include "net_pres/pres/net_pres.h"
#include "net_pres/pres/net_pres_encryptionproviderapi.h"
#include "net_pres/pres/net_pres_transportapi.h"
#include "net_pres/pres/net_pres_socketapi.h"
#include "driver/usart/drv_usart.h"
#include "driver/ba414e/drv_ba414e.h"
#include "usb/usb_chapter_9.h"
#include "usb/usb_device.h"
#include "driver/ethmac/drv_ethmac.h"
#include "peripheral/nvm/plib_nvm.h"
#include "usb/usb_device_cdc.h"
#include "usb/usb_cdc.h"
#include "peripheral/uart/plib_uart1.h"
#include "peripheral/uart/plib_uart2.h"
#include "driver/usb/usbfs/drv_usbfs.h"
#include "library/tcpip/tcpip.h"
#include "system/sys_time_h2_adapter.h"
#include "system/sys_random_h2_adapter.h"
#include "system/command/sys_command.h"
#include "peripheral/clk/plib_clk.h"
#include "peripheral/gpio/plib_gpio.h"
#include "peripheral/evic/plib_evic.h"
#include "wolfssl/wolfcrypt/port/pic32/crypt_wolfcryptcb.h"
#include "driver/wifi/pic32mzw1/include/wdrv_pic32mzw_api.h"
#include "system/wifi/sys_wifi.h"
#include "system/console/sys_console.h"
#include "system/console/src/sys_console_uart_definitions.h"
#include "system/console/src/sys_console_usb_cdc_definitions.h"
#include "FreeRTOS.h"
#include "task.h"
#include "monitor.h"
#include "app.h"
#include "uart_bridge.h"



// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

/* CPU clock frequency */
#define CPU_CLOCK_FREQUENCY 200000000

// *****************************************************************************
// *****************************************************************************
// Section: System Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* System Initialization Function

  Function:
    void SYS_Initialize( void *data )

  Summary:
    Function that initializes all modules in the system.

  Description:
    This function initializes all modules in the system, including any drivers,
    services, middleware, and applications.

  Precondition:
    None.

  Parameters:
    data            - Pointer to the data structure containing any data
                      necessary to initialize the module. This pointer may
                      be null if no data is required and default initialization
                      is to be used.

  Returns:
    None.

  Example:
    <code>
    SYS_Initialize ( NULL );

    while ( true )
    {
        SYS_Tasks ( );
    }
    </code>

  Remarks:
    This function will only be called once, after system reset.
*/

void SYS_Initialize( void *data );

// *****************************************************************************
/* System Tasks Function

Function:
    void SYS_Tasks ( void );

Summary:
    Function that performs all polled system tasks.

Description:
    This function performs all polled system tasks by calling the state machine
    "tasks" functions for all polled modules in the system, including drivers,
    services, middleware and applications.

Precondition:
    The SYS_Initialize function must have been called and completed.

Parameters:
    None.

Returns:
    None.

Example:
    <code>
    SYS_Initialize ( NULL );

    while ( true )
    {
        SYS_Tasks ( );
    }
    </code>

Remarks:
    If the module is interrupt driven, the system will call this routine from
    an interrupt context.
*/

void SYS_Tasks ( void );

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* System Objects

Summary:
    Structure holding the system's object handles

Description:
    This structure contains the object handles for all objects in the
    MPLAB Harmony project's system configuration.

Remarks:
    These handles are returned from the "Initialize" functions for each module
    and must be passed into the "Tasks" function for each module.
*/

typedef struct
{
    SYS_MODULE_OBJ  sysTime;
    SYS_MODULE_OBJ  sysConsole0;


    SYS_MODULE_OBJ  drvMiim;
    SYS_MODULE_OBJ  drvUsart0;
    SYS_MODULE_OBJ  netPres;


    SYS_MODULE_OBJ  ba414e;

	SYS_MODULE_OBJ  usbDevObject0;

	SYS_MODULE_OBJ  drvUSBFSObject;


    SYS_MODULE_OBJ  tcpip;
    SYS_MODULE_OBJ  sysConsole1;

    SYS_MODULE_OBJ  sysDebug;

    SYS_MODULE_OBJ  drvWifiPIC32MZW1;
    SYS_MODULE_OBJ  syswifi;

} SYSTEM_OBJECTS;

// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************

extern const USB_DEVICE_INIT usbDevInitData; 



extern SYSTEM_OBJECTS sysObj;

    typedef struct {        
        char msg[4096];
        uint32_t magic;
    } EXCEPT_MSG;

    #define MAGIC_CODE 0x47114711


//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* DEFINITIONS_H */
/*******************************************************************************
 End of File
*/
