#include <stdint.h>

#include <RoveComm.h>

// Data the teensy sends to the nucleo
uint32_t SHperiod = 20;
uint32_t ICGperiod = 100000;
uint8_t AVGn [2] = { 0, 1 };
uint32_t MCLK = 200000;


// Data arrays for received bytes
uint8_t rxData8[7388];
uint16_t rxData16[3694];

// Arrays for data to transmit
uint8_t txsh[4];
uint8_t txicg[4];
uint8_t txfull[12];
