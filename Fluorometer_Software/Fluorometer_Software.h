#ifndef FLUOROMETER_SOFTWARE_H
#define FLUOROMETER_SOFTWARE_H

#include "PinAssignments.h"
#include <stdint.h>
//#include "RoveComm.h"
#include "c12880.h"

C12880_Class MiniSpec(TRG, START, CLK, VIDEO);
// EthernetServer TCPServer(RC_ROVECOMM_ETHERNET_TCP_PORT);
// RoveCommEthernet RoveComm;

#endif /* FLUOROMETER_SOFTWARE_H */