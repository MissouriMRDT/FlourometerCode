#include "xbara.h"

typedef union
{
    uint8_t _u8[2];
    uint16_t _u16;
} xbara_u8_u16_t;

void XBARA_SetSignalsConnection(XBARA_Type *base, xbar_input_signal_t input, xbar_output_signal_t output)
{
    xbara_u8_u16_t regVal;
    uint8_t byteInReg;
    uint8_t outputIndex = (uint8_t)output;

    byteInReg = outputIndex % 2U;

    regVal._u16 = XBARA_SELx(base, outputIndex);

    regVal._u8[byteInReg] = (uint8_t)input;

    XBARA_SELx(base, outputIndex) = regVal._u16;
}

void XBARA_Init(XBARA_Type *base)
{
#if !(defined())
    CLOCK_EnableClock(s_xbaraClock[XBARA_GetInstance(base)]);
}