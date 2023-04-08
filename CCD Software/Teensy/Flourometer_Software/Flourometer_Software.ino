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

  attachInterrupt(digitalPinToInterrupt(CLK_IN), ccd_isr, FALLING);
  cli();

  //      --Disable GPT1--
  GPT1_CR &= (0<<0);

  //      --Disable GPT interrupts: Clear interrupt register (IR)--
  GPT1_IR &= 0b000000;
  
  //      --Configure Output Mode to disconnected for all channels--
  // Bits 28-26: Output compare disabled for channel 3
  // Bits 25-23: Output compare disabled for channel 2
  // Bits 22-20: Output compare disabled for channel 1
  GPT1_CR &= (0b000<<26) | (0b000<<23) | (0b000<<20);
  
  //      --Disable Input Capture Modes-- CR[IMn]=0
  // Bits 19-18: Input Capture mode disabled for channel 2
  // Bits 17-16: Input Capture mode disabled for channel 1
  GPT1_CR &= (0b00<<18) | (0b00<<16);

  //      --Set clock source to desired value-- CR[CLKSRC]
  GPT1_CR |= (0b010<<6);

  //      --Assert GPT Software Reset CR[SWR]=1--
  GPT1_CR |= (1<<15);

  //      --Configure Prescaler--
  // Reserved bits
  GPT1_PR &= (0b0000000000000000<<16);
  // Bits 15-12: Prescaler divide value for the oscillator clock. Set to divide by 1, but we don't use so won't do anything.
  GPT1_PR &= (0b0000<<12);
  // Bits 11-0: Prescaler divide by 4096.
  GPT1_PR |= (0b111111111111<<0);

  // Bit 15:     Software reset disabled
  // Bits 14-11: Reserved, should write 0s
  // Bit 10:     Disable the Oscillator Clock Input
  // Bit 9:      Set timer to restart mode.
  // Bits 8-6:   Set clock source to high frequency reference clock.
  // Bit 5:      Operation during stop mode enabled.
  // Bit 4:      Operation during doze mode enabled.
  // Bit 3:      Operation during wait mode enabled.
  // Bit 2:      Operation during debug mode enabled.
  // Bit 1:      ENMOD bit. Selectes value of the main counter and prescalre counter when GPT is enabled again. Resets counting from 0 in this setting.
  // Bit 0:      GPT enable. Leaves GPT disabled for now.
  GPT1_CR |= (0<<15) | (0b0000<<11) | (0<<10) | (0<<9) | (0b010<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1) | (0<<0);
  
  //      --Clear the flags in the GPT status register (SR) by writing 1s to them--
  GPT1_SR |= 0b111111;

  //      --Enable GPT1--
  GPT1_CR |= (1<<0);

  //      --Enable GPT1 interrupts--
  GPT1_IR &= 0b000000;
  
}


void loop() {
  //readCCD();
  Serial.println(GPT1_CNT);
  /*
  for(int j = 0; j < 3648; j++)
    Serial.println(ccd_buff[j]);

  while(1);
  */
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
