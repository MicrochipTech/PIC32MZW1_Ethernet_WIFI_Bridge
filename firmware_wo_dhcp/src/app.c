/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "system/net/sys_net.h"
//#include "definitions.h"
#include "tcpip_manager_control.h"
//#include "tcpip/src/link_list.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

SYS_MODULE_OBJ g_tcpServHandle = SYS_MODULE_OBJ_INVALID;
SYS_NET_Config g_tcpServCfg;

#define RECV_BUFFER_LEN		1400
uint8_t recv_buffer[RECV_BUFFER_LEN + 1];

void TcpServCallback(uint32_t event, void *data, void* cookie)
{
    switch(event)
    {
        case SYS_NET_EVNT_CONNECTED:
        {
            SYS_CONSOLE_PRINT("TcpServCallback(): Status UP\r\n");
            while(SYS_NET_SendMsg(g_tcpServHandle, (uint8_t*)"hello", 5) <= 0);
            break;
        }

        case SYS_NET_EVNT_DISCONNECTED:
        {
            SYS_CONSOLE_PRINT("TcpServCallback(): Status DOWN\r\n");
            break;
        }

        case SYS_NET_EVNT_RCVD_DATA:
        {
			int32_t cumm_len = 0;
            int32_t len = RECV_BUFFER_LEN;
            while(len == RECV_BUFFER_LEN)
            {
                len = SYS_NET_RecvMsg(g_tcpServHandle, recv_buffer, RECV_BUFFER_LEN);
                if(len>0)
                {
                    if(cumm_len == 0)
                    {
                            uint8_t buffer[33];
                            int32_t tmp_len = (len > 32)? 32 : len;

                            memcpy(buffer, recv_buffer, tmp_len);
                            buffer[tmp_len] = '\0';
                            SYS_CONSOLE_PRINT("TcpServCallback(): Data Rcvd = %s\r\n", buffer);
                    }
                    cumm_len += len;
                    SYS_NET_SendMsg(g_tcpServHandle, recv_buffer, len);
                }
            }
            SYS_CONSOLE_PRINT("TcpServCallback(): Total Data Rcvd = %d Bytes\r\n", cumm_len);
            
            break;
        }
        
        case SYS_NET_EVNT_LL_INTF_DOWN:
        {
            /* 
            ** User needs to take a decision if they want to close the socket or
            ** wait for the Lower layer to come up
             */
            SYS_CONSOLE_PRINT("TcpServCallback(): Lower Layer Down\r\n");
            break;
        }
        
        case SYS_NET_EVNT_LL_INTF_UP:
        {
            /* 
            ** The lower layer was down and now it has come up again. 
            ** The socket was in connected state all this while
             */
            SYS_CONSOLE_PRINT("TcpServCallback(): Lower Layer Up\r\n");
            break;
        }                
        
        case SYS_NET_EVNT_SERVER_AWAITING_CONNECTION:
        {
            /* 
            ** The server is awaiting connection from the client
             */
            SYS_CONSOLE_PRINT("TcpServCallback(): Server Awaiting Connection\r\n");
            break;
        }                
    }
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/
void SYS_WIFI_TCPIP_DHCP_EventHandler
(
    TCPIP_NET_HANDLE hNet, 
    TCPIP_DHCP_EVENT_TYPE evType,
    const void* param
) 
{
    IPV4_ADDR ipAddr;
    IPV4_ADDR gateWayAddr;
    IPV4_ADDR subMask;
    TCPIP_NET_HANDLE    netHdl;

    switch (evType) 
    {
        case DHCP_EVENT_BOUND:
        {

            /* TCP/IP Stack BOUND event indicates
               PIC32MZW1 has received the IP address from connected HOMEAP */
            ipAddr.Val = TCPIP_STACK_NetAddress(hNet);
            subMask.Val = TCPIP_STACK_NetMask(hNet);
            
            if (ipAddr.Val) 
            {
                gateWayAddr.Val = TCPIP_STACK_NetAddressGateway(hNet);
                SYS_CONSOLE_PRINT("IP address obtained = %d.%d.%d.%d \r\n",
                        ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);
                SYS_CONSOLE_PRINT("Gateway IP address = %d.%d.%d.%d \r\n",
                        gateWayAddr.v[0], gateWayAddr.v[1], gateWayAddr.v[2], gateWayAddr.v[3]);
                
                
                /* set the IP address of the Wi-Fi interface for WIFI stations to communicate with WFI32*/
                netHdl = TCPIP_STACK_NetHandleGet("PIC32MZW1");
                TCPIP_STACK_NetAddressSet(netHdl, &ipAddr, 
                                   &subMask, true);

            }
            break;
        }

        case DHCP_EVENT_CONN_ESTABLISHED:
        {
            break;
        }

        case DHCP_EVENT_CONN_LOST:
        {

            
            break;
        }

        default:
        {
            break;
        }
    }
}
// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    SYS_CONSOLE_MESSAGE("APP_Initialize\n");

    g_tcpServHandle = SYS_NET_Open(NULL, TcpServCallback, 0); 
    if(g_tcpServHandle != SYS_MODULE_OBJ_INVALID)
        SYS_CONSOLE_PRINT("TCP Service Initialized Successfully\r\n");

    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    TCPIP_NET_HANDLE    netHdl;
    
    SYS_CMD_READY_TO_READ();
    SYS_NET_Task(g_tcpServHandle);

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;


            if (appInitialized)
            {

                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            /* ETH network handle*/
            netHdl = TCPIP_STACK_NetHandleGet("PIC32MZWINT");
            if ((true == TCPIP_DHCP_Enable(netHdl)) && 
                    (TCPIP_STACK_ADDRESS_SERVICE_DHCPC == TCPIP_STACK_AddressServiceSelect(_TCPIPStackHandleToNet(netHdl), TCPIP_NETWORK_CONFIG_DHCP_CLIENT_ON))) 
                {
                    //ethDhcpHdl= TCPIP_DHCP_HandlerRegister (netHdl, SYS_WIFI_TCPIP_DHCP_EventHandler, NULL);
                    TCPIP_DHCP_HandlerRegister (netHdl, SYS_WIFI_TCPIP_DHCP_EventHandler, NULL);
                    appData.state = APP_STATE_IDLE_TASKS;
            }

            break;
        }

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }

}


/*******************************************************************************
 End of File
 */
