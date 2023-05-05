#include "MIMXRT1062.h"

#ifndef _FSL_XBARA_H_
#define _FSL_XBARA_H_

// Macros for the entire XBARA_SELx register.
#define XBARA_SELx(base, output) (((volatile uint16_t *)(&((base)->SEL0)))[(uint32_t)(output) / 2UL])

/* Set the XBARA_SELx_SELx field to a new value. */
#define XBARA_WR_SELx_SELx(base, input, output) XBARA_SetSignalsConnection((base), (input), (output))

// ***********************************************************
//                           PROTOTYPES
// ***********************************************************
void XBARA_SetSignalsConnection(XBARA_Type *base, xbar_input_signal_t input, xbar_output_signal_t output);

void XBARA_Init(XBARA_Type *base);

#endif /* _FSL_XBARA_H */