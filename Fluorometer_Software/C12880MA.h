#ifndef C12880MA_H
#define C12880MA_H

#include <stdint.h>


class C12880MA {

private:
    uint8_t m_CLK_pin;
    uint8_t m_TRG_pin;
    uint8_t m_TRG_index;
    uint8_t m_START_pin;
    uint8_t m_EOS_pin;
    uint8_t m_VIDEO_pin;
    uint8_t m_LED_WHITE_pin;

public:
    C12880MA(uint8_t CLK_pin, uint8_t TRG_pin, uint8_t START_pin, uint8_t EOS_pin, uint8_t VIDEO_pin, uint8_t LED_WHITE_pin);

    void init();

    void read(uint8_t video[288]);

    void setIntegrationTime(uint32_t time_us);
};
#endif /* C12880MA_H */