#include "Fluorometer_Software.h"

void setup() {
    // Serial Debugger
    Serial.begin(115200);
    Serial.println("");

    RoveComm.begin(RC_FLUOROMETERBOARD_FIRSTOCTET, RC_FLUOROMETERBOARD_SECONDOCTET, RC_FLUOROMETERBOARD_THIRDOCTET, RC_FLUOROMETERBOARD_FOURTHOCTET, &TCPServer);

    miniSpec.init();
}

void loop() {

  rovecomm_packet packet = RoveComm.read();
  switch (packet.data_id) {
    case (RC_FLUOROMETERBOARD_REQUESTREADING_DATA_ID): {
      uint8_t video[288];
      miniSpec.read(video);
      RoveComm.write(RC_FLUOROMETERBOARD_READING_DATA_ID, RC_FLUOROMETERBOARD_READING_DATA_COUNT, video);
    }
  }
    
  
}