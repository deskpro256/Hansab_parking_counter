
//============================[DRAW_DISPLAY]========================
// When the master sends a message to the entire floor's slaves
// the number to be dispayed gets sent to the display through the RS485 port
// RS485 DISPLAY DRIVER

//============================[DRAW_DISPLAY]========================
void drawDisplay(char onesN, char tensN, char hundredsN) {
  wdt_reset();

  checkSum = 0x00;
  packetSum = 0x00;

  dispNum[7] = onesN;
  dispNum[8] = tensN;
  dispNum[9] = hundredsN;

  //summing the bytes
  for (int i = 0; i <= 9; i++) {
    packetSum += dispNum[i];
  }
  //checksum = low byte of the inverse of the sum of header&inf packet
  checkSum = (packetSum ^ 0xFF) & 0xFF;
  dispNum[10] = checkSum;

  //PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTD |= (1 << PD4);      // (RE_DE, HIGH) enable sending
  PORTC |= (1 << PC5);      // Enable COM Led
  delay(50);
  Display.write(dispNum, 11);
  delay(50);
  //PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTD &= ~(1 << PD4);     // (RE_DE, LOW) disable sending
  PORTC &= ~(1 << PC5);     // Disable COM Led
}
