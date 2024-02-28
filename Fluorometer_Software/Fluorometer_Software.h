#ifndef FLUOROMETER_SOFTWARE_H
#define FLUOROMETER_SOFTWARE_H

#include "PinAssignments.h"
#include <stdint.h>
#include "RoveComm.h"
#include "C12880MA.h"

C12880MA MiniSpec(CLK, TRG, START, EOS, VIDEO, LED_WHITE);
// EthernetServer TCPServer(RC_ROVECOMM_ETHERNET_TCP_PORT);
// RoveCommEthernet RoveComm;

#endif /* FLUOROMETER_SOFTWARE_H */