#include <cstdint>

#define CCD_IN 0
#define SH 2
#define ICG 3
#define CLK_IN 4
#define CLK_OUT 1

uint16_t ccd_buff[3648];

int i = 0;

void setup() {
  Serial.begin(9600);
  analogWriteResolution(6);
  analogWriteFrequency(CLK_OUT, 2000000);
  analogWrite(CLK_OUT, 32);
  pinMode(CLK_IN, INPUT);

  attachInterrupt(CLK_IN, ccd_isr, FALLING);
  cli();
}

void loop() {
  readCCD();
  
  for(int j = 0; j < 3648; j++)
    Serial.println(ccd_buff[j]);

  while(1);
}

void readCCD() {
  while (digitalRead(CLK_IN));
  
  digitalWrite(SH, LOW);
  digitalWrite(ICG, HIGH);
  delayMicroseconds(1);
  digitalWrite(SH, HIGH);
  delayMicroseconds(5);
  digitalWrite(ICG, LOW);

  i = 0;
  sei();
  delay(8);
  cli();
}

void ccd_isr() {
  if (i%4 == 1 && i > 4*32 && i < 4*(32+3648)) {
    ccd_buff[(i/4)-32] = analogRead(CCD_IN);
  }
  i++;
}
