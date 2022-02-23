WFI32 Example of Bridging the Ethernet and the WIFI Interface

Application Use Case is to enable Ethernet and WLAN (SoftAP) at the same time while the Harmony TCP Stack and its application like DHCP Server is accessible from both interfaces. 
And a UART1 (115200) to TCP Server (Port 47111) Bridge is part of this example.  

The Layer-2-Bridge example is based on H3 example app „wifi_eth_dual_interface“from the standard Wireless_wifi Repository.

The bridge is based on the standard bridge feature of the TCP Manager driver. 
 
Changelog
---------
1.	Debug Console on USB CDC
2.	Both interfaces eth0/wlan0 added to bridge
3.	FreeRTOS Heap management is used only
4.	wlan0 is set to SoftAP “DEMO_AP_SOFTAP” and password “password”
5.	DHCP server active on both interfaces
6.	Telnet Server active (user=”admin” password=”password”)
7.	Harmony TCP stack accessible from both interfaces at 192.168.1.1
8.	UART1 (115200) is bridged to TCP Server on Port 47111 as raw socket
9.	extended Exception Handler added with detailed CPU Register dump after next Reset
10.	VT100 Terminal Controll added for status display once per second
11.	Console commands added for FreeRTOS Heap Usage and Memory Hex Dump
12.	The following two commands where added
	o	“heap” Shows the FreeRTOS Heap state (Free Bytes, Failed Mallocs, etc)
	o	“dump <address> <count>” dumps <count> bytes memory from <address> 


SoftAP Setup
------------
WFI32E Curiosity Board + LAN8720 PHY Daughter Board
UART1 (115200) (GPIO Header) for Transparent UART data stream
USBCDC (J204) to power the board and retrieve debug messages

Station Setup
-------------
WFI32E Curiosity Board + LAN8720 PHY Daughter Board
UART1 (115200) (GPIO Header) for debug messages
USBCDC (J204) to power the board and enable Transparent UART data stream

Project manifest
----------------
project: wifi_eth_dual_interface_ap
creation_date: 2022-02-18T19:44:54.685+01:00[Europe/Paris]    # ISO 8601 format: https://www.w3.org/TR/NOTE-datetime
operating_system: Windows 10
mhc_mode: IDE            # [IDE|Standalone|Headless]
mhc_version: v3.8.2
mplabx_version: v6.00        # if MPLAB X plugin only
plugin_version: v3.6.4        # if MPLAB X plugin only
compiler: XC32 (3.01)

modules:
    - {name: "core", version: "v3.10.0"}
    - {name: "csp", version: "v3.10.0"}
    - {name: "wireless_wifi", version: "v3.6.1"}
    - {name: "usb", version: "v3.8.1"}
    - {name: "dev_packs", version: "v3.10.0"}
    - {name: "wireless_system_pic32mzw1_wfi32e01", version: "v3.6.1"}
    - {name: "wolfssl", version: "v4.7.0"}
    - {name: "net", version: "v3.7.4"}
    - {name: "crypto", version: "v3.7.5"}
    - {name: "CMSIS-FreeRTOS", version: "v10.3.1"}


