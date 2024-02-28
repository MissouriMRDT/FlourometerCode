#include "Fluorometer_Software.h"


void setup() {
    // Serial Debugger
    Serial.begin(115200);
    // Serial.println("");
    analogWrite(33, 0);
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);

    // I/O
    // pinmode(LED_400, OUTPUT);
    // pinmode(LED_430, OUTPUT);
    // pinmode(LED_522, OUTPUT);
    // pinmode(LED_530, OUTPUT);
    
    // RoveComm
    //Serial.println("");
    //RoveComm.begin();
    //Serial.println("");
 
    // Hamamatsu
    MiniSpec.init();
};

void loop() {
  int16_t data[288];
  delay(2000);
  MiniSpec.read(data);
  Serial.println(data[1]);
};