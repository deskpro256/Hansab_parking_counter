//===================================[NUMBER_COUNTING]=======================================
void countNumbers() {
  totalCount = floorCount[0] + floorCount[1] + floorCount[2];
}

//===================================[GET_CHANGES]=======================================
void getChanges(int receiverID) {
  RS485Send(receiverID, messageType[0], CMDLUT[1], 'C', 'N', 'G');
  tries++;
  if (Serial.available() > 8) {
    RS485Receive();
  }
  replied = false;
  if (tries > 2) {
    PORTD |= (1 << PD6);      // Enable ERR Led
    //add to error list
    addToErrorList(receiverID, errorCodes[1]);
    tries = 0;
  }
  else {
    tries = 0;
  }
  PORTD &= ~(1 << PD6);     // Disable ERR Led
}

//===================================[COMPARE_FLOOR_COUNT]================================
void compareFloor() {
  //
}

//===================================[SEND_DISPLAY_COUNT]================================
void sendDisplayCount() {

}

//===================================[SEND_DISPLAY_COUNT_TO_USB]================================
void sendDisplayCountToUSB() {

  for (int i = 0; i <= 2; i++) {
    huns = (floorCount[i] / 100);
    tens = (floorCount[i] % 100) / 10;
    ones = (floorCount[i] % 10);
    char test[] = {huns + '0', tens + '0', ones + '0'};

    delay(10);
    PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
    PORTD |= (1 << PD5);      // Enable COM Led
    Serial.write(test, 3);
    Serial.println();
    delay(10);
    PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
    PORTD &= ~(1 << PD5);     // Disable COM Led
  }
}

//===================================[SEND_DISPLAY_COUNT_TO_USB]================================
void sendToDisplay() {
  checkSum = 0x00;
  packetSum = 0x00;
  huns = (floorCount[0] / 100);
  tens = (floorCount[0] % 100) / 10;
  ones = (floorCount[0] % 10);
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
  //checkSum = 0xa3;
  dispNum[10] = checkSum;


  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTD |= (1 << PD5);      // Enable COM Led
  delay(10);
  Serial.write(dispNum, 11);
  delay(100);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTD &= ~(1 << PD5);     // Disable COM Led
}
