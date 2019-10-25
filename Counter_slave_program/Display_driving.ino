
//============================[DRAW_DISPLAY]========================
// When the master sends a message to the entire floor's slaves, the number to be dispayed gets sent to the display through the RS232 port
//RS232 DISPLAY DRIVER
// needs the "meandr" protocol

//============================[DRAW_DISPLAY]========================
void drawDisplay(int countNum) {

  checkSum = 0x00;
  packetSum = 0x00;
  huns = (countNum / 100);
  tens = (countNum % 100) / 10;
  ones = (countNum % 10);
  char nums[] = {huns + '0', tens + '0', ones + '0'};

  dispNum[7] = nums[2];
  dispNum[8] = nums[1];
  dispNum[9] = nums[0];
  
  //summing the bytes
  for (int i = 0; i <= 9; i++) {
    packetSum += dispNum[i];
  }
  //checksum = low byte of the inverse of the sum of header&inf packet
  checkSum = (packetSum ^ 0xFF) & 0xFF;
  dispNum[10] = checkSum;

  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTC |= (1 << PC5);      // Enable COM Led
  delay(10);
  Serial.write(dispNum, 11);
  delay(50);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTC &= ~(1 << PC5);     // Disable COM Led
}
