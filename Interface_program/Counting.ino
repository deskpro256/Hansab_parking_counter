//===================================[NUMBER_COUNTING]=======================================
void countNumbers() {

  floorCount[0] = tempF1Count;
  floorCount[1] = tempF2Count;
  floorCount[2] = tempF3Count;
  floorCount[3] = tempF4Count;

}

//===================================[GET_CHANGES]=======================================

void getChanges(char receiverID) {
  replied = false;
  RS485Send(receiverID, messageType[0], CMDLUT[1], 'C', 'N', 'G');
  tries++;
  delay(50);
  if (Serial.available() > 0) {
    lookForSTX = Serial.read();
    if (lookForSTX == STX) {
      PORTD ^= (1 << PD3);
      RS485Receive();
    }
  }
  if (replied == false) {
    if (tries < 2) {
      getChanges(receiverID); // try again
    }
    else {
      PORTD |= (1 << PD6);      // Enable ERR Led
      //add to error list
      addToErrorList(receiverID, errorCodes[1]);
      tries = 0;
      replied = false;
    }
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

  for (int i = 0; i <= 3; i++) {
    byte byteHuns = (floorCount[i] / 100) + 0x30;
    byte byteTens = ((floorCount[i] % 100) / 10) + 0x30;
    byte byteOnes = (floorCount[i] % 10) + 0x30;
    delay(20);
    RS485Send(floorNaddresses[i], messageType[0], CMDLUT[2], byteHuns, byteTens, byteOnes);
    delay(20);
  }
}


//===================================[SEND_DISPLAY_COUNT]================================
void sendDisplayCountToUSB(byte _floorNum) {
  /*
    tempF1Count = floorCount[0];
    tempF2Count = floorCount[1];
    tempF3Count = floorCount[2];
    tempF4Count = floorCount[3];
  */

  if (_floorNum == 0xF1) {
    huns = (tempF1Count / 100);
    tens = (tempF1Count % 100) / 10;
    ones = (tempF1Count % 10);
  }
  else if (_floorNum == 0xF2) {
    huns = (tempF2Count / 100);
    tens = (tempF2Count % 100) / 10;
    ones = (tempF2Count % 10);
  }
  else if (_floorNum == 0xF3) {
    huns = (tempF3Count / 100);
    tens = (tempF3Count % 100) / 10;
    ones = (tempF3Count % 10);
  }
  else if (_floorNum == 0xF4) {
    huns = (tempF4Count / 100);
    tens = (tempF4Count % 100) / 10;
    ones = (tempF4Count % 10);
  }

  RS485Send(PCID, _floorNum, CMDLUT[6], huns + '0', tens + '0', ones + '0');

}
