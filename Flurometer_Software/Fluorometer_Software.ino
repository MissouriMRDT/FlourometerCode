#include "Fluorometer_Software.h"
#include "C12880MA.h"
#include "RoveComm.h"
#include "RoveCommManifest.h"

void setup() {
    // Serial Debugger
    Serial.begin(115200);
    Serial.println("");

    // I/O
    pinmode(LED_400, OUTPUT);
    pinmode(LED_430, OUTPUT);
    pinmode(LED_522, OUTPUT);
    pinmode(LED_530, OUTPUT);
    
    // RoveComm
    Serial.println("");
    RoveComm.begin();
    Serial.println("");

    // Hamamatsu
    C12880MA();
};

void loop() {
    
};