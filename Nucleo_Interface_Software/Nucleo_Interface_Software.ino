#include "Nucleo_Interface_Software.h"

void setup() {
  Serial.begin(115200);

  Serial1.begin(115200);
}

/* The firmware expects 12 bytes from the computer and will not do anything until 12 bytes have been received.
 * The format is:
 * byte[1-2]: The characters E and R. Defines where the firmware should start reading in its circular input-buffer.
 * byte[3-6]: The 4 bytes constituting the 32-bit int holding the SH-period
 * byte[7-10]: The 4 bytes constituting the 32-bit int holding the ICG-period
 * byte[11]: Continuous flag: 0 equals one acquisition, 1 equals continuous mode
 * byte[12]: The number of integrations to average
 */
void loop() {
  if (Serial.available() > 0) {
    if ((char)Serial.read() == 's')
    {
      rxtxOneReading();
      //Serial.print("txfull: ");
      /*for (int k = 0; k < 12; k++)
      {
        Serial.print(txfull[k], BIN);
        Serial.print(" ");
      }
      */
      for (int i = 0; i < sizeof(rxData16); i++)
        Serial.println(rxData16[i]);
    }
  }

}

void rxtxOneReading()
{
  // Transmit key 'ER'
  txfull[0] = 69;
  txfull[1] = 82;
  
  // Split 32-bit integers to be sent into 8-bit data
  txfull[2] = (SHperiod >> 24) & 0xff;
  txfull[3] = (SHperiod >> 16) & 0xff;
  txfull[4] = (SHperiod >> 8) & 0xff;
  txfull[5] = SHperiod & 0xff;
  txfull[6] = (ICGperiod >> 24) & 0xff;
  txfull[7] = (ICGperiod >> 16) & 0xff;
  txfull[8] = (ICGperiod >> 8) & 0xff;
  txfull[9] = ICGperiod & 0xff;
  
  //averages to perform
  txfull[10] = AVGn[0];
  txfull[11] = AVGn[1];

  Serial1.write(txfull, 96);

  for (int j = 0; j < 7388; j++)
  {
    uint8_t tmp = Serial1.read(); //analogRead(0);
    //Serial.println(tmp, BIN);
    rxData8[j] = tmp;
  }

  //Serial1.close();

  for (int i = 0; i < 3694; i++)
  {
    rxData16[i] = (rxData8[2*i+1] << 8) + rxData8[2*i];
  }
}
