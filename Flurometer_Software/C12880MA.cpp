#include "C12880MA.h"
#include <stdint.h>
#include "Arduino.h"

extern uint8_t pin_to_channel[]; // links to array in Teensy analog.c library

// Begins a reading from ADC
void startSample(uint8_t pin) {
    // validate pin and determine corresponding ADC channel
    if (pin > sizeof(pin_to_channel)) return;
    uint8_t ch = pin_to_channel[pin];
    if (ch == 255) return;

    // Start ADC reading
    if(!(ch & 0x80)) {
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
    if(!(ch & 0x80)) {
		return (ADC1_HS & ADC_HS_COCO0)? ADC1_R0 : -1;
	} else {
		return (ADC2_HS & ADC_HS_COCO0)? ADC2_R0 : -1;
	}
}

void C12880MA::init() {
    // I/O
    pinmode(LED_WHITE, INPUT);
    pinmode(VIDEO, OUTPUT);
    pinmode(EOS, OUTPUT);
    pinmode(TRG, OUTPUT);
    pinmode(START, INPUT);
    pinmode(CLK, INPUT);
    pinmode(pin, OUTPUT);

    // Video ADC Configuraiton
    analogReadAveraging(1);
    analogReadRes(8);

    // Clock Initialization 
    analogWriteResolution(m_CLK_pin, 280000);
    analogWrite(m_CLK_pin, 127);

};

C12880MA::C12880MA(uint8_t m_CLK_pin, uint8_t m_TRG_pin, uint8_t m_START_pin, uint8_t m_EOS_pin, uint8_t m_VIDEO_pin, uint8_t m_LED_WHITE_pin) {
    m_CLK_pin = CLK_pin;
    m_TRG_pin = TRG_pin;
    m_START_pin = START_pin;
    m_EOS_pin = EOS_pin;
    m_VIDEO_pin = VIDEO_pin;
    m_LED_WHITE_pin = LED_WHITE_pin;

};

// Interrupt service routine for rising edge of TRG pin
static C12880MA *active_C12880MA;
void TRG_isr() {
    // if m_TRG_index between start and stop indices, store result of readSample() into video array
    if ((active_C12880MA->m_TRG_index > 89) && (active_C12880MA->m_TRG_index < 288)) {
        video[active_C12880MA->m_TRG_index] = readSample(active_C12880MA->m_VIDEO_pin);
    }

    active_C12880MA->m_TRG_index++; // count pulses
    
    // if m_TRG_index between start and stop indices, start a new reading by calling startSample()
    if ((active_C12880MA->m_TRG_index > 89) && (active_C12880MA->m_TRG_index < 288)) {
        startSample(active_C12880MA->m_VIDEO_pin);
    }
}

void C12880MA::read(int16_t video[288]) {
    while (digitalRead(m_CLK_pin));
    digitalWrite(m_START_pin, HIGH)
    delayMicroseconds(21.4); // Start pulse high period is 6/f
    while (digitalread(m_CLK_pin));
    digitalWrite(m_START_pin, LOW) = 0;

    m_TRG_index = 0;
    m_video = video; // save pointer to array so ISR can access it
    active_C12880MA = this;
    attachInterrupt(digitalPinToInterrupt(m_TRG_pin), TRG_isr, RISING);
    while (!digitalRead(m_EOS_pin)); // wait for end of signal
    detachInterrupt(digitalPinToInterrupt(m_TRG_pin));
}
