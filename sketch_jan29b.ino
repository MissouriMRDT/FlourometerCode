#include <util/delay_basic.h>

/*
 * D11: Master
 * D10:ICG
 * D9:Shift
 */

#ifdef ARDUINO_AVR_DUE
//defines pins based on microcontroller hex values
#define SH 0x40
#define ICG 0x80
#define MCLK 0x10
#else
#define SH 0x02
#define ICG 0x04
#define MCLK 0x08
#endif

#define CLOCK PORTB
#define MIN_SIGNAL 10
//cuts signal noise (whether it be ADC or LDO when we build the final circiut)

uint16_t buffer[800]; //allocates memory needed for read
uint16_t avg = 0;
char cmdBuffer[16];
int cmdIndex;
int exposureTime = 20;

/*
 * Bitewise ops:
 * |=bitwise or
 * &=bitewise and
 * ~=bitewise inverse
 * found these aee very useful for clocks, used quite a bit throughout here
 * I still don't have an in depth understanding of why this works so well
 * for clock value assignments but arduinos website shows how to do it
 */

void setup() {

    uint16_t val;
    // Initialize the clocks.
    DDRB |= (SH | ICG | MCLK); // Set the clock lines to outputs
    CLOCK |= ICG; // Set the ICG HIGH.

    // Enable the serial port for io.
    Serial.begin(115200);

    // Setup timer2 to generate a 470kHz frequency
    //TCC... are waveform generators
    TCCR2A = +(0 << COM2A1) | (1 << COM2A0) | (1 << WGM21) | (0 << WGM20);
    TCCR2B = (0 << WGM22) | (1 << CS20);
    OCR2A = 20;
    TCNT2 = 1;

    // Set the ADC clock to sysclk/32
    ADCSRA &= ~((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
    ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
}

void readCCD(void) {
    int x;
    uint16_t result;

    CLOCK &= ~ICG;
    delayMicroseconds(36);
    CLOCK |= SH;
    delayMicroseconds(5);
    CLOCK &= ~SH;
    delayMicroseconds(15);
    CLOCK |= ICG;
    delayMicroseconds(1);
  

    for (x = 0; x < 800; x++) {
        CLOCK |= SH;


    /*
     * I copied some of this loop, I don't fully understand why it only itterates
     * 800 times and why A0 is subtracted from 1023, I believe these have to do with
     * the float value size (4 bytes) and the 3069 active elements (3 itterations
     * per tick * 1023)
     */
        if (x == 0) {
            result = (uint16_t)(1023 - analogRead(A0));
            if (result > MIN_SIGNAL) {
                avg = result - MIN_SIGNAL;
            } else {
                avg = result;
            }
        } else {
            result = (uint16_t)(1023 - analogRead(A0));
        }
        CLOCK &= ~SH;
        if (result < avg) {
            result = 0;
        } else {
            result -= avg;
        }
        buffer[x] = result;
        delayMicroseconds(20);
    }
}

void sendData(void) {
    int x;

    for (x = 0; x < 800; ++x) {
        Serial.println(buffer[x]);
        //sends data over the serial, can format to some other file here
    }
}

void loop() {
    while (Serial.available()) {
        cmdBuffer[cmdIndex++] = Serial.read();
        //reads in a character input from the serial to determine read action
    }
    if (cmdBuffer[0] == 's') {
        sendData();
    } else if (cmdBuffer[0] == 'e') {
        exposureTime = atoi((char *)&cmdBuffer[1]); //fast char to string conversion
        if (exposureTime > 1000) exposureTime = 1000;
        else if (exposureTime < 0) exposureTime = 0;
        Serial.println(exposureTime);
        //traps invalid exposure times to prevent sensor saturation
    }
    memset(cmdBuffer, 0 , sizeof(cmdBuffer)); //clears the serial buffer
    cmdIndex = 0;
    readCCD();
    delay(exposureTime);
}
