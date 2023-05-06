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


// Variables
uint16_t ccd_buff[3648];
int ccd_buff_index = 0;

#endif