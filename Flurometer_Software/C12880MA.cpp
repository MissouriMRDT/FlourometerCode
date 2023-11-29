#include "C12880MA.h"
#include <stdint.h>

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

C12880MA::C12880MA(uint8_t m_CLK_pin, uint8_t m_TRG_pin, uint8_t m_START_pin, uint8_t m_EOS_pin, uint8_t m_VIDEO_pin, uint8_t m_LED_WHITE_pin) {
    m_CLK_pin = CLK_pin;
    m_TRG_pin = TRG_pin;
    m_START_pin = START_pin;
    m_EOS_pin = EOS_pin;
    m_VIDEO_pin = VIDEO_pin;
    m_LED_WHITE_pin = LED_WHITE_pin;
};
