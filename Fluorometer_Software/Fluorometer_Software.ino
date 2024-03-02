#include "Fluorometer_Software.h"

void setup() {
    // Serial Debugger
    Serial.begin(115200);
    Serial.println("");

    miniSpec.init();
};

void loop() {
    int16_t video[288];
    miniSpec.read(video);
    for (int i = 0; i < 288; i++) {
       Serial.print(video[i]);
       Serial.print(",");
    }
    Serial.println("");
    delay(5000);
  
};