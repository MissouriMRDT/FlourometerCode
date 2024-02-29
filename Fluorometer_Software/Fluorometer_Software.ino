#include "C12880MA.h"
#include "Fluorometer_Software.h"

uint16_t data[288];
C12880_Class spec(TRG, START, CLK, VIDEO);

void setup() {
Serial.begin(115200);
spec.begin();
}

void loop() {
spec.read_into(data);

}
