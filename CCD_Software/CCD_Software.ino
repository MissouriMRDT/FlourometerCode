#include "CCD_Software.h"


void setup()
{
    Serial.begin(9600);

    // Configure LED pins
    pinMode(CONTROL_LED_265, OUTPUT);
    pinMode(CONTROL_LED_275, OUTPUT);
    pinMode(CONTROL_LED_280, OUTPUT);
    pinMode(CONTROL_LED_310, OUTPUT);
    pinMode(CONTROL_LED_365, OUTPUT);

    // Configure input pins
    pinMode(CCD_IN, INPUT);
    pinMode(ICG, INPUT);

    Serial.println("RoveComm Initializing...");
    RoveComm.begin(RC_SCIENCESENSORSBOARD_FIRSTOCTET, RC_SCIENCESENSORSBOARD_SECONDOCTET, RC_SCIENCESENSORSBOARD_THIRDOCTET, RC_SCIENCESENSORSBOARD_FOURTHOCTET, &TCPServer);
    Serial.println("Complete");
}



void loop()
{
    rovecomm_packet packet = RoveComm.read();
    switch (packet.data_id)
    {

        // Turn on/off LEDs
        case RC_SCIENCESENSORSBOARD_FLUOROMETERLEDS_DATA_ID:
        {
            uint8_t data = ((uint8_t *) packet.data)[0];

            digitalWrite(CONTROL_LED_265, data & (1 << 0));
            digitalWrite(CONTROL_LED_275, data & (1 << 1));
            digitalWrite(CONTROL_LED_280, data & (1 << 2));
            digitalWrite(CONTROL_LED_310, data & (1 << 3));
            digitalWrite(CONTROL_LED_365, data & (1 << 4));

            break;
        }

        // Read and transmit CCD buffer
        case RC_SCIENCESENSORSBOARD_REQFLUOROMETER_DATA_ID:
        {
            uint8_t data = ((uint8_t *) packet.data)[0];

            Serial.println("Reading...");
            while (digitalRead(ICG) == LOW);
            while (digitalRead(ICG) == HIGH);

            uint32_t startTime = micros();
            for (int i = 0; i < CCD_SIZE; i++) {
                ccd_buff[i] = analogRead(CCD_IN);
            }
            Serial.println((micros() - startTime));

            RoveComm.write(RC_SCIENCESENSORSBOARD_FLUOROMETERDATA_DATA_ID, RC_SCIENCESENSORSBOARD_FLUOROMETERDATA_DATA_COUNT, ccd_buff);

            break;
        }

    }
    
}
