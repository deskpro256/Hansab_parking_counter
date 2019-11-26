//===================================[NUMBER_COUNTING]=======================================
void countNumbers() {

  floorCount[0] = tempF1Count;
  floorCount[1] = tempF2Count;
  floorCount[2] = tempF3Count;
  floorCount[3] = tempF4Count;

  totalCount = floorCount[0] + floorCount[1] + floorCount[2] + floorCount[3];
}

//===================================[GET_CHANGES]=======================================
void getChanges(int receiverID) {
  RS485Send(receiverID, messageType[0], CMDLUT[1], 'C', 'N', 'G');
  tries++;
  if (Serial.available() > 0) {
    lookForSTX = Serial.read();
    if (lookForSTX == STX) {
      PORTD ^= (1 << PD3);
      RS485Receive();
    }
  }
  replied = false;
  if (tries > 1) {
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
void compareFloor(char _floorID, char sign, char _count) {

  PORTD ^= (1 << PD6);

  tempF1Count = floorCount[0];
  tempF2Count = floorCount[1];
  tempF3Count = floorCount[2];
  tempF4Count = floorCount[3];

  if (_floorID == floorNaddresses[0]) {
    if (sign == '-') {
      countChanged = true;
      tempF1Count -= _count;
      //floorCount[0] -= _count;
    }
    else {
      tempF1Count += _count;
      //floorCount[0] += _count;
      countChanged = true;
    }
  }
  else if (_floorID == floorNaddresses[1]) {
    if (sign == '-') {
      tempF2Count -= _count;
      countChanged = true;
    }
    else {
      tempF2Count += _count;
      countChanged = true;
    }
  }
  else if (_floorID == floorNaddresses[2]) {
    if (sign == '-') {
      tempF3Count -= _count;
      countChanged = true;
    }
    else {
      tempF3Count += _count;
      countChanged = true;
    }
  }
  else if (_floorID == floorNaddresses[4]) {
    if (sign == '-') {
      tempF4Count -= _count;
      countChanged = true;
    }
    else {
      tempF4Count += _count;
      countChanged = true;
    }
  }
}

//===================================[SEND_DISPLAY_COUNT]================================
void sendDisplayCount() {

  for (int i = 0; i <= activeFloors - 1; i++) {
    huns = (floorCount[i] / 100);
    tens = (floorCount[i] % 100) / 10;
    ones = (floorCount[i] % 10);
    char FloorNumbers[] = {huns + '0', tens + '0', ones + '0'};
    RS485Send(floorNaddresses[i], messageType[0], CMDLUT[2], FloorNumbers[0], FloorNumbers[1], FloorNumbers[2]);
    delay(50);
  }
}


//===================================[SEND_DISPLAY_COUNT]================================
void sendDisplayCountToUSB(char _floorNum) {
  int i = 0;
  if (_floorNum == 0xF1) {
    i = 0;
  }
  else if (_floorNum == 0xF2) {
    i = 1;
  }
  else if (_floorNum == 0xF3) {
    i = 2;
  }
  else if (_floorNum == 0xF4) {
    i = 3;
  }

  huns = (floorCount[i] / 100);
  tens = (floorCount[i] % 100) / 10;
  ones = (floorCount[i] % 10);
  char FloorNumbersInt[] = {STX, PCID, myID , _floorNum, CMDLUT[6], huns + '0', tens + '0', ones + '0'};

  delay(10);
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTD |= (1 << PD5);      // Enable COM Led
  Serial.write(FloorNumbersInt, 8);
  delay(10);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTD &= ~(1 << PD5);     // Disable COM Led

}
