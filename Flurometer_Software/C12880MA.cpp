#include "C12880MA.h"

void init() {
    pinmode(LED_WHITE, INPUT);
    pinmode(VIDEO, OUTPUT);
    pinmode(EOS, OUTPUT);
    pinmode(TRG, OUTPUT);
    pinmode(START, INPUT);
    pinmode(CLK, INPUT);
    analogReadAveraging(1);
    analogReadRes(8);
};

void read() {
    
};