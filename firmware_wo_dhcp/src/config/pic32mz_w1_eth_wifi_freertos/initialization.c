/*******************************************************************************
  System Initialization File

  File Name:
    initialization.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits,
    and allocates any necessary global system resources,
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
#include "configuration.h"
#include "definitions.h"
#include "device.h"



// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************




/*** FBCFG0 ***/
#pragma config BUHSWEN =    OFF
#pragma config PCSCMODE =    DUAL
#pragma config BOOTISA =    MIPS32



/*** DEVCFG0 ***/
#pragma config TDOEN =      ON
#pragma config TROEN =     OFF
#pragma config JTAGEN =     OFF
#pragma config FCPRI =      LRSA
#pragma config DMAPRI =    LRSA
#pragma config EXLPRI =    LRSA
#pragma config USBSSEN =     OFF
#pragma config PMULOCK =     OFF
#pragma config PGLOCK =      OFF
#pragma config PMDLOCK =   OFF
#pragma config IOLOCK =  OFF
#pragma config CFGLOCK =   OFF
#pragma config OC_ACLK =  OCMP_TMR2_TMR3
#pragma config IC_ACLK =  ICAP_TMR2_TMR3
#pragma config CANFDDIV =  0
#pragma config PCM =  SFR
#pragma config UPLLHWMD =  OFF
#pragma config SPLLHWMD =   OFF
#pragma config BTPLLHWMD =        OFF
#pragma config ETHPLLHWMD =        OFF
#pragma config FECCCON =         OFF
#pragma config ETHTPSF =         RPSF
#pragma config EPGMCLK =         FRC


/*** DEVCFG1 ***/
#pragma config DEBUG =         EMUC
#pragma config ICESEL =         ICS_PGx2
#pragma config TRCEN =         ON
#pragma config FMIIEN =         OFF
#pragma config ETHEXEREF =         OFF
#pragma config CLASSBDIS =         DISABLE
#pragma config USBIDIO =         ON
#pragma config VBUSIO =         ON
#pragma config HSSPIEN =         OFF
#pragma config SMCLR =      MCLR_NORM
#pragma config USBDMTRIM =      0
#pragma config USBDPTRIM =      0
#pragma config HSUARTEN =    ON
#pragma config WDTPSS =    PSS1



/*** DEVCFG2 ***/
#pragma config DMTINTV =    WIN_63_64
#pragma config POSCMOD =    HS
#pragma config WDTRMCS =    LPRC
#pragma config SOSCSEL =    CRYSTAL
#pragma config WAKE2SPD =    ON
#pragma config CKSWEN =    ON
#pragma config FSCMEN =    ON
#pragma config WDTPS =    PS1
#pragma config WDTSPGM =    STOP
#pragma config WINDIS =    NORMAL
#pragma config WDTEN =    OFF
#pragma config WDTWINSZ =    WINSZ_25
#pragma config DMTCNT =    DMT31
#pragma config DMTEN =    OFF



/*** DEVCFG4 ***/
#pragma config SOSCCFG =    0
#pragma config VBZPBOREN =    ON
#pragma config DSZPBOREN =    ON
#pragma config DSWDTPS =    DSPS1
#pragma config DSWDTOSC =    LPRC
#pragma config DSWDTEN =    OFF
#pragma config DSEN =    OFF
#pragma config SOSCEN =    OFF


/*** FCPN0 ***/
#pragma config CP =    OFF




// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
/* Forward declaration of MAC initialization data */
const TCPIP_MODULE_MAC_PIC32INT_CONFIG tcpipMACPIC32INTInitData;


/* Forward declaration of MIIM initialization data */
static const DRV_MIIM_INIT drvMiimInitData;


/* Forward declaration of PHY initialization data */
const DRV_ETHPHY_INIT tcpipPhyInitData_LAN8740;

static CRYPT_RNG_CTX wdrvRngCtx;
static const WDRV_PIC32MZW_SYS_INIT wdrvPIC32MZW1InitData = {
    .pCryptRngCtx  = &wdrvRngCtx,
    .pRegDomName   = "GEN",
    .powerSaveMode = WDRV_PIC32MZW_POWERSAVE_RUN_MODE,
    .powerSavePICCorrelation = WDRV_PIC32MZW_POWERSAVE_PIC_ASYNC_MODE
};



// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************
/* Structure to hold the object handles for the modules in the system. */
SYSTEM_OBJECTS sysObj;

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************


static const DRV_BA414E_INIT_DATA ba414eInitData = 
{
};
  
 

/*** ETH MAC Initialization Data ***/
const TCPIP_MODULE_MAC_PIC32INT_CONFIG tcpipMACPIC32INTInitData =
{ 
    .nTxDescriptors         = TCPIP_EMAC_TX_DESCRIPTORS,
    .rxBuffSize             = TCPIP_EMAC_RX_BUFF_SIZE,
    .nRxDescriptors         = TCPIP_EMAC_RX_DESCRIPTORS,
    .nRxDedicatedBuffers    = TCPIP_EMAC_RX_DEDICATED_BUFFERS,
    .nRxInitBuffers         = TCPIP_EMAC_RX_INIT_BUFFERS,
    .rxLowThreshold         = TCPIP_EMAC_RX_LOW_THRESHOLD,
    .rxLowFill              = TCPIP_EMAC_RX_LOW_FILL,
    .linkInitDelay          = TCPIP_INTMAC_PHY_LINK_INIT_DELAY,
    .ethFlags               = TCPIP_EMAC_ETH_OPEN_FLAGS,
    .ethModuleId            = TCPIP_INTMAC_MODULE_ID,
    .pPhyBase               = &DRV_ETHPHY_OBJECT_BASE_Default,
    .pPhyInit               = &tcpipPhyInitData_LAN8740,
};




// <editor-fold defaultstate="collapsed" desc="TCP/IP Stack Initialization Data">
// *****************************************************************************
// *****************************************************************************
// Section: TCPIP Data
// *****************************************************************************
// *****************************************************************************
/*** ARP Service Initialization Data ***/
const TCPIP_ARP_MODULE_CONFIG tcpipARPInitData =
{ 
    .cacheEntries       = TCPIP_ARP_CACHE_ENTRIES,     
    .deleteOld          = TCPIP_ARP_CACHE_DELETE_OLD,    
    .entrySolvedTmo     = TCPIP_ARP_CACHE_SOLVED_ENTRY_TMO, 
    .entryPendingTmo    = TCPIP_ARP_CACHE_PENDING_ENTRY_TMO, 
    .entryRetryTmo      = TCPIP_ARP_CACHE_PENDING_RETRY_TMO, 
    .permQuota          = TCPIP_ARP_CACHE_PERMANENT_QUOTA, 
    .purgeThres         = TCPIP_ARP_CACHE_PURGE_THRESHOLD, 
    .purgeQuanta        = TCPIP_ARP_CACHE_PURGE_QUANTA, 
    .retries            = TCPIP_ARP_CACHE_ENTRY_RETRIES, 
    .gratProbeCount     = TCPIP_ARP_GRATUITOUS_PROBE_COUNT,
};


/*** UDP Sockets Initialization Data ***/
const TCPIP_UDP_MODULE_CONFIG tcpipUDPInitData =
{
    .nSockets       = TCPIP_UDP_MAX_SOCKETS,
    .sktTxBuffSize  = TCPIP_UDP_SOCKET_DEFAULT_TX_SIZE, 
};

/*** TCP Sockets Initialization Data ***/
const TCPIP_TCP_MODULE_CONFIG tcpipTCPInitData =
{
    .nSockets       = TCPIP_TCP_MAX_SOCKETS,
    .sktTxBuffSize  = TCPIP_TCP_SOCKET_DEFAULT_TX_SIZE, 
    .sktRxBuffSize  = TCPIP_TCP_SOCKET_DEFAULT_RX_SIZE,
};








/*** ICMP Server Initialization Data ***/
const TCPIP_ICMP_MODULE_CONFIG tcpipICMPInitData = 
{
    0
};















/*** IPv4 Initialization Data ***/


const TCPIP_IPV4_MODULE_CONFIG  tcpipIPv4InitData = 
{
    .arpEntries = TCPIP_IPV4_ARP_SLOTS, 
};


TCPIP_MAC_BRIDGE_ENTRY_BIN tcpipMacbridgeTable[2] = 
{
	{0},
	{1},
};

/*** TCPIP MAC Bridge Initialization Data ***/
const TCPIP_MAC_BRIDGE_CONFIG  tcpipBridgeInitData = 
{
	.purgeTimeout = TCPIP_MAC_BRIDGE_ENTRY_TIMEOUT,
    .transitDelay = TCPIP_MAC_BRIDGE_MAX_TRANSIT_DELAY,
	.fdbEntries = TCPIP_MAC_BRIDGE_FDB_TABLE_ENTRIES,
    .pktPoolSize = TCPIP_MAC_BRIDGE_PACKET_POOL_SIZE,
    .pktSize = TCPIP_MAC_BRIDGE_PACKET_SIZE,
    .dcptPoolSize = TCPIP_MAC_BRIDGE_DCPT_POOL_SIZE,
    .pktReplenish = TCPIP_MAC_BRIDGE_PACKET_POOL_REPLENISH,
    .dcptReplenish = TCPIP_MAC_BRIDGE_DCPT_POOL_REPLENISH,
    .bridgeFlags = TCPIP_MC_BRIDGE_INIT_FLAGS,
    .bridgeTableSize = 2,
    .bridgeTable = (const TCPIP_MAC_BRIDGE_ENTRY*)tcpipMacbridgeTable,
    // advanced
	.bridgePermTableSize = 0,
    .bridgePermTable = 0,

};



TCPIP_STACK_HEAP_EXTERNAL_CONFIG tcpipHeapConfig =
{
    .heapType = TCPIP_STACK_HEAP_TYPE_EXTERNAL_HEAP,
    .heapFlags = TCPIP_STACK_HEAP_USE_FLAGS,
    .heapUsage = TCPIP_STACK_HEAP_USAGE_CONFIG,
    .malloc_fnc = TCPIP_STACK_MALLOC_FUNC,
    .calloc_fnc = TCPIP_STACK_CALLOC_FUNC,
    .free_fnc = TCPIP_STACK_FREE_FUNC,
};


const TCPIP_NETWORK_CONFIG __attribute__((unused))  TCPIP_HOSTS_CONFIGURATION[] =
{
    /*** Network Configuration Index 0 ***/
    {
        .interface = TCPIP_NETWORK_DEFAULT_INTERFACE_NAME_IDX0,
        .hostName = TCPIP_NETWORK_DEFAULT_HOST_NAME_IDX0,
        .macAddr = TCPIP_NETWORK_DEFAULT_MAC_ADDR_IDX0,
        .ipAddr = TCPIP_NETWORK_DEFAULT_IP_ADDRESS_IDX0,
        .ipMask = TCPIP_NETWORK_DEFAULT_IP_MASK_IDX0,
        .gateway = TCPIP_NETWORK_DEFAULT_GATEWAY_IDX0,
        .priDNS = TCPIP_NETWORK_DEFAULT_DNS_IDX0,
        .secondDNS = TCPIP_NETWORK_DEFAULT_SECOND_DNS_IDX0,
        .powerMode = TCPIP_NETWORK_DEFAULT_POWER_MODE_IDX0,
        .startFlags = TCPIP_NETWORK_DEFAULT_INTERFACE_FLAGS_IDX0,
        .pMacObject = &TCPIP_NETWORK_DEFAULT_MAC_DRIVER_IDX0,
    },
    /*** Network Configuration Index 1 ***/
    {
        .interface = TCPIP_NETWORK_DEFAULT_INTERFACE_NAME_IDX1,
        .hostName = TCPIP_NETWORK_DEFAULT_HOST_NAME_IDX1,
        .macAddr = TCPIP_NETWORK_DEFAULT_MAC_ADDR_IDX1,
        .ipAddr = TCPIP_NETWORK_DEFAULT_IP_ADDRESS_IDX1,
        .ipMask = TCPIP_NETWORK_DEFAULT_IP_MASK_IDX1,
        .gateway = TCPIP_NETWORK_DEFAULT_GATEWAY_IDX1,
        .priDNS = TCPIP_NETWORK_DEFAULT_DNS_IDX1,
        .secondDNS = TCPIP_NETWORK_DEFAULT_SECOND_DNS_IDX1,
        .powerMode = TCPIP_NETWORK_DEFAULT_POWER_MODE_IDX1,
        .startFlags = TCPIP_NETWORK_DEFAULT_INTERFACE_FLAGS_IDX1,
        .pMacObject = &TCPIP_NETWORK_DEFAULT_MAC_DRIVER_IDX1,
    },
};

const size_t TCPIP_HOSTS_CONFIGURATION_SIZE = sizeof (TCPIP_HOSTS_CONFIGURATION) / sizeof (*TCPIP_HOSTS_CONFIGURATION);

const TCPIP_STACK_MODULE_CONFIG TCPIP_STACK_MODULE_CONFIG_TBL [] =
{
    {TCPIP_MODULE_IPV4,             &tcpipIPv4InitData},

    {TCPIP_MODULE_ICMP,             0},                             // TCPIP_MODULE_ICMP

    {TCPIP_MODULE_ARP,              &tcpipARPInitData},             // TCPIP_MODULE_ARP
    {TCPIP_MODULE_UDP,              &tcpipUDPInitData},             // TCPIP_MODULE_UDP
    {TCPIP_MODULE_TCP,              &tcpipTCPInitData},             // TCPIP_MODULE_TCP

    { TCPIP_MODULE_MANAGER,         &tcpipHeapConfig },             // TCPIP_MODULE_MANAGER

// MAC modules
    {TCPIP_MODULE_MAC_PIC32INT,     &tcpipMACPIC32INTInitData},     // TCPIP_MODULE_MAC_PIC32INT

    {TCPIP_MODULE_MAC_BRIDGE,       &tcpipBridgeInitData},      // TCPIP_MODULE_MAC_BRIDGE 
};

const size_t TCPIP_STACK_MODULE_CONFIG_TBL_SIZE = sizeof (TCPIP_STACK_MODULE_CONFIG_TBL) / sizeof (*TCPIP_STACK_MODULE_CONFIG_TBL);
/*********************************************************************
 * Function:        SYS_MODULE_OBJ TCPIP_STACK_Init()
 *
 * PreCondition:    None
 *
 * Input:
 *
 * Output:          valid system module object if Stack and its componets are initialized
 *                  SYS_MODULE_OBJ_INVALID otherwise
 *
 * Overview:        The function starts the initialization of the stack.
 *                  If an error occurs, the SYS_ERROR() is called
 *                  and the function de-initialize itself and will return false.
 *
 * Side Effects:    None
 *
 * Note:            This function must be called before any of the
 *                  stack or its component routines are used.
 *
 ********************************************************************/


SYS_MODULE_OBJ TCPIP_STACK_Init(void)
{
    TCPIP_STACK_INIT    tcpipInit;

    tcpipInit.pNetConf = TCPIP_HOSTS_CONFIGURATION;
    tcpipInit.nNets = TCPIP_HOSTS_CONFIGURATION_SIZE;
    tcpipInit.pModConfig = TCPIP_STACK_MODULE_CONFIG_TBL;
    tcpipInit.nModules = TCPIP_STACK_MODULE_CONFIG_TBL_SIZE;
    tcpipInit.initCback = 0;

    return TCPIP_STACK_Initialize(0, &tcpipInit.moduleInit);
}
// </editor-fold>

/* MIIM Driver Configuration */
static const DRV_MIIM_INIT drvMiimInitData =
{
	.ethphyId = DRV_MIIM_ETH_MODULE_ID,
};


    
    

/*** ETH PHY Initialization Data ***/
const DRV_ETHPHY_INIT tcpipPhyInitData_LAN8740 =
{    
    .ethphyId               = TCPIP_INTMAC_MODULE_ID,
    .phyAddress             = TCPIP_INTMAC_PHY_ADDRESS,
    .phyFlags               = TCPIP_INTMAC_PHY_CONFIG_FLAGS,
    .pPhyObject             = &DRV_ETHPHY_OBJECT_LAN8740,
    .resetFunction          = 0,
    .pMiimObject            = &DRV_MIIM_OBJECT_BASE_Default,
    .pMiimInit              = &drvMiimInitData,
    .miimIndex              = DRV_MIIM_DRIVER_INDEX,
};



// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="SYS_TIME Initialization Data">

const SYS_TIME_PLIB_INTERFACE sysTimePlibAPI = {
    .timerCallbackSet = (SYS_TIME_PLIB_CALLBACK_REGISTER)CORETIMER_CallbackSet,
    .timerStart = (SYS_TIME_PLIB_START)CORETIMER_Start,
    .timerStop = (SYS_TIME_PLIB_STOP)CORETIMER_Stop ,
    .timerFrequencyGet = (SYS_TIME_PLIB_FREQUENCY_GET)CORETIMER_FrequencyGet,
    .timerPeriodSet = (SYS_TIME_PLIB_PERIOD_SET)NULL,
    .timerCompareSet = (SYS_TIME_PLIB_COMPARE_SET)CORETIMER_CompareSet,
    .timerCounterGet = (SYS_TIME_PLIB_COUNTER_GET)CORETIMER_CounterGet,
};

const SYS_TIME_INIT sysTimeInitData =
{
    .timePlib = &sysTimePlibAPI,
    .hwTimerIntNum = 0,
};

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYS_CONSOLE Instance 0 Initialization Data">


/* Declared in console device implementation (sys_console_uart.c) */
extern const SYS_CONSOLE_DEV_DESC sysConsoleUARTDevDesc;

const SYS_CONSOLE_UART_PLIB_INTERFACE sysConsole0UARTPlibAPI =
{
    .read = (SYS_CONSOLE_UART_PLIB_READ)UART1_Read,
	.readCountGet = (SYS_CONSOLE_UART_PLIB_READ_COUNT_GET)UART1_ReadCountGet,
	.readFreeBufferCountGet = (SYS_CONSOLE_UART_PLIB_READ_FREE_BUFFFER_COUNT_GET)UART1_ReadFreeBufferCountGet,
    .write = (SYS_CONSOLE_UART_PLIB_WRITE)UART1_Write,
	.writeCountGet = (SYS_CONSOLE_UART_PLIB_WRITE_COUNT_GET)UART1_WriteCountGet,
	.writeFreeBufferCountGet = (SYS_CONSOLE_UART_PLIB_WRITE_FREE_BUFFER_COUNT_GET)UART1_WriteFreeBufferCountGet,
};

const SYS_CONSOLE_UART_INIT_DATA sysConsole0UARTInitData =
{
    .uartPLIB = &sysConsole0UARTPlibAPI,    
};

const SYS_CONSOLE_INIT sysConsole0Init =
{
    .deviceInitData = (const void*)&sysConsole0UARTInitData,
    .consDevDesc = &sysConsoleUARTDevDesc,
    .deviceIndex = 0,
};



// </editor-fold>


const SYS_CMD_INIT sysCmdInit =
{
    .moduleInit = {0},
    .consoleCmdIOParam = SYS_CMD_SINGLE_CHARACTER_READ_CONSOLE_IO_PARAM,
	.consoleIndex = 0,
};


const SYS_DEBUG_INIT debugInit =
{
    .moduleInit = {0},
    .errorLevel = SYS_DEBUG_GLOBAL_ERROR_LEVEL,
    .consoleIndex = 0,
};





// *****************************************************************************
// *****************************************************************************
// Section: Local initialization functions
// *****************************************************************************
// *****************************************************************************



/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
 */

void SYS_Initialize ( void* data )
{

    /* Start out with interrupts disabled before configuring any modules */
    __builtin_disable_interrupts();

  
    PMU_Initialize();
	CLK_Initialize();

    /* Configure Wait States */
    PRECONbits.PFMWS = 5;



	GPIO_Initialize();

    NVM_Initialize();

    CORETIMER_Initialize();
	UART1_Initialize();



    /* Initialize the MIIM Driver */
    sysObj.drvMiim = DRV_MIIM_Initialize( DRV_MIIM_INDEX_0, (const SYS_MODULE_INIT *) &drvMiimInitData );

    /* Initialize the PIC32MZW1 Driver */
    CRYPT_RNG_Initialize(&wdrvRngCtx);
    sysObj.drvWifiPIC32MZW1 = WDRV_PIC32MZW_Initialize(WDRV_PIC32MZW_SYS_IDX_0, (SYS_MODULE_INIT*)&wdrvPIC32MZW1InitData);


    sysObj.sysTime = SYS_TIME_Initialize(SYS_TIME_INDEX_0, (SYS_MODULE_INIT *)&sysTimeInitData);
    sysObj.sysConsole0 = SYS_CONSOLE_Initialize(SYS_CONSOLE_INDEX_0, (SYS_MODULE_INIT *)&sysConsole0Init);

    SYS_CMD_Initialize((SYS_MODULE_INIT*)&sysCmdInit);

    sysObj.sysDebug = SYS_DEBUG_Initialize(SYS_DEBUG_INDEX_0, (SYS_MODULE_INIT*)&debugInit);


    /* WiFi Service Initialization */
    sysObj.syswifi = SYS_WIFI_Initialize(NULL,NULL,NULL);
    SYS_ASSERT(sysObj.syswifi  != SYS_MODULE_OBJ_INVALID, "SYS_WIFI_Initialize Failed" );


    sysObj.ba414e = DRV_BA414E_Initialize(0, (SYS_MODULE_INIT*)&ba414eInitData);


/* TCPIP Stack Initialization */
sysObj.tcpip = TCPIP_STACK_Init();
SYS_ASSERT(sysObj.tcpip != SYS_MODULE_OBJ_INVALID, "TCPIP_STACK_Init Failed" );


    CRYPT_WCCB_Initialize();

    APP_Initialize();


    EVIC_Initialize();

	/* Enable global interrupts */
    __builtin_enable_interrupts();


}


/*******************************************************************************
 End of File
*/
