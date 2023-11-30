#ifndef C12880MA_H
#define C12880MA_H

#include "PinAssignments.h"

#define C12880MA_DATA_START_INDEX 89
#define C12880MA_DATA_LENGTH 288
#define C12880MA_DATA_STOP_INDEX (C12880MA_DATA_START_INDEX, C12880MA_DATA_LENGTH)


class C12880MA {
friend void TRG_isr();
private:
uint8_t CLK_pin;
uint8_t TRG_pin;
uint8_t m_TRG_index;
uint8_t START_pin;
uint8_t EOS_pin;
uint8_t VIDEO_pin;
uint8_t LED_WHITE_pin;
int16_t *m_video;


public:

C12880MA(uint8_t m_CLK_pin, uint8_t m_TRG_pin, uint8_t m_START_pin, uint8_t m_EOS_pin, uint8_t m_VIDEO_pin, uint8_t m_LED_WHITE_pin);

void init();

void read(int16_t video[288]);
};
#endif /* C12880MA_H */