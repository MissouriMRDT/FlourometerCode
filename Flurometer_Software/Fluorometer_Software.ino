#include "Fluorometer_Software.h"
#include "C12880MA.h"
#include "RoveComm.h"

void setup() {
    // Serial Debugger
    Serial.begin(115200);
    Serial.println("");

    // I/O
    // TODO: Call pinmode for LED pins
    
    // RoveComm
    Serial.println("");
    RoveComm.begin();
    Serial.println("");

    // Hamamatsu
    C12880MA();
};

void loop() {
    
};