#include "C12880MA.h"
#include <stdint.h>
#include "Arduino.h"

const uint8_t pin_to_channel[] = {
  // pg 482
  7,        // 0/A0  AD_B1_02
  8,        // 1/A1  AD_B1_03
  12,       // 2/A2  AD_B1_07
  11,       // 3/A3  AD_B1_06
  6,        // 4/A4  AD_B1_01
  5,        // 5/A5  AD_B1_00
  15,       // 6/A6  AD_B1_10
  0,        // 7/A7  AD_B1_11
  13,       // 8/A8  AD_B1_08
  14,       // 9/A9  AD_B1_09
  1,        // 24/A10 AD_B0_12
  2,        // 25/A11 AD_B0_13
  128 + 3,  // 26/A12 AD_B1_14 - only on ADC2, 3
  128 + 4,  // 27/A13 AD_B1_15 - only on ADC2, 4
  7,        // 14/A0  AD_B1_02
  8,        // 15/A1  AD_B1_03
  12,       // 16/A2  AD_B1_07
  11,       // 17/A3  AD_B1_06
  6,        // 18/A4  AD_B1_01
  5,        // 19/A5  AD_B1_00
  15,       // 20/A6  AD_B1_10
  0,        // 21/A7  AD_B1_11
  13,       // 22/A8  AD_B1_08
  14,       // 23/A9  AD_B1_09
  1,        // 24/A10 AD_B0_12
  2,        // 25/A11 AD_B0_13
  128 + 3,  // 26/A12 AD_B1_14 - only on ADC2, 3
  128 + 4,  // 27/A13 AD_B1_15 - only on ADC2, 4
#ifdef ARDUINO_TEENSY41
  255,      // 28
  255,      // 29
  255,      // 30
  255,      // 31
  255,      // 32
  255,      // 33
  255,      // 34
  255,      // 35
  255,      // 36
  255,      // 37
  128 + 1,  // 38/A14 AD_B1_12 - only on ADC2, 1
  128 + 2,  // 39/A15 AD_B1_13 - only on ADC2, 2
  9,        // 40/A16 AD_B1_04
  10,       // 41/A17 AD_B1_05
#endif
};  // links to array in Teensy analog.c library


// Begins a reading from ADC
void startSample(uint8_t pin) {
  // validate pin and determine corresponding ADC channel
  if (pin > sizeof(pin_to_channel)) return;
  uint8_t ch = pin_to_channel[pin];
  if (ch == 255) return;

  // Start ADC reading
  if (!(ch & 0x80)) {
    ADC1_HC0 = ch;
  } else {
    ADC2_HC0 = ch & 0x7f;
  }
}

int16_t readSample(uint8_t pin) {
  // validate pin and determine corresponding ADC channel
  if (pin > sizeof(pin_to_channel)) return 0;
  uint8_t ch = pin_to_channel[pin];
  if (ch == 255) return 0;

  // Read ADC
  if (!(ch & 0x80)) {
    return (ADC1_HS & ADC_HS_COCO0) ? ADC1_R0 : -1;
  } else {
    return (ADC2_HS & ADC_HS_COCO0) ? ADC2_R0 : -1;
  }
}

void C12880MA::init() {
  // I/O
  pinMode(m_LED_WHITE_pin, OUTPUT);
  pinMode(m_VIDEO_pin, INPUT);
  pinMode(m_EOS_pin, INPUT);
  pinMode(m_TRG_pin, INPUT);
  pinMode(m_START_pin, OUTPUT);
  pinMode(m_CLK_pin, OUTPUT);

  // Video ADC Configuraiton
  analogReadAveraging(1);
  analogReadRes(8);
};

C12880MA::C12880MA(uint8_t CLK_pin, uint8_t TRG_pin, uint8_t START_pin, uint8_t EOS_pin, uint8_t VIDEO_pin, uint8_t LED_WHITE_pin) {
  m_CLK_pin = CLK_pin;
  m_TRG_pin = TRG_pin;
  m_START_pin = START_pin;
  m_EOS_pin = EOS_pin;
  m_VIDEO_pin = VIDEO_pin;
  m_LED_WHITE_pin = LED_WHITE_pin;
};

uint32_t startHighPulses = 6;
void C12880MA::read(uint8_t video[288]) {
  digitalWrite(m_CLK_pin, HIGH);
  delayMicroseconds(2);
  digitalWrite(m_CLK_pin, LOW);
  digitalWrite(m_START_pin, HIGH);

  for (uint32_t i = 0; i < startHighPulses; i++) {
    delayMicroseconds(2);
    digitalWrite(m_CLK_pin, HIGH);
    delayMicroseconds(2);
    digitalWrite(m_CLK_pin, LOW);
  }
  digitalWrite(m_START_pin, LOW);
  delayMicroseconds(2);

  for (int i = 0; i < 88; i++) {
    digitalWrite(m_CLK_pin, HIGH);
    delayMicroseconds(2);
    digitalWrite(m_CLK_pin, LOW);
    delayMicroseconds(2);
  }
  for (int i = 0; i < 288; i++) {
    startSample(m_VIDEO_pin);
    digitalWrite(m_CLK_pin, HIGH);
    delayMicroseconds(2);
    digitalWrite(m_CLK_pin, LOW);
    delayMicroseconds(2);
    video[i] = readSample(m_VIDEO_pin);
  }
}

void C12880MA::setIntegrationTime(uint32_t time_us) {
  if (time_us < 54 * 4) {
    time_us = 54 * 4;
  }
  time_us /= 4;
  time_us -= 48;
  startHighPulses = time_us;
}
