#ifndef CCD_SOFTWARE_H
#define CCD_SOFTWARE_H

#include <RoveComm.h>

#include <cstdint>

// RoveComm
EthernetServer TCPServer(RC_ROVECOMM_ETHERNET_TCP_PORT);
RoveCommEthernet RoveComm;

// Fluorometer Pins
#define CCD_IN A10
#define SH 2
#define ICG 3
#define MASTER_CLK 1
#define CLK_IN 4
#define DATA_CLK 5
#define DATA_CLK_IN 8

// LED Pins
#define CONTROL_LED_265 27
#define CONTROL_LED_275 38
#define CONTROL_LED_280 39
#define CONTROL_LED_310 40
#define CONTROL_LED_365 41

// CCD
#define CCD_SIZE 215
uint16_t ccd_buff[CCD_SIZE];


#endif