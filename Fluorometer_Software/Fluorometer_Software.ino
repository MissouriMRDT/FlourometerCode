#include "Fluorometer_Software.h"

void setup() {
    // Serial Debugger
    Serial.begin(115200);

    Serial.println("Reflectance setup...");
    RoveComm.begin(RC_REFLECTANCESPECTROMETERBOARD_FIRSTOCTET, RC_REFLECTANCESPECTROMETERBOARD_SECONDOCTET, RC_REFLECTANCESPECTROMETERBOARD_THIRDOCTET, RC_REFLECTANCESPECTROMETERBOARD_FOURTHOCTET, &TCPServer);
    Serial.println("Complete");

    miniSpec.init();
}

void loop() {

  rovecomm_packet packet = RoveComm.read();
  switch (packet.data_id) {
    case (RC_REFLECTANCESPECTROMETERBOARD_REQUESTREADING_DATA_ID): {
      uint32_t data = ((uint32_t*) packet.data)[0];
      miniSpec.setIntegrationTime(data);

      uint8_t video[288];
      miniSpec.read(video);
      RoveComm.write(RC_REFLECTANCESPECTROMETERBOARD_READING_DATA_ID, RC_REFLECTANCESPECTROMETERBOARD_READING_DATA_COUNT, video);
    }
  }
    
  
}