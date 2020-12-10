
//===================================[GET_CHANGES]=======================================

void getChanges(char receiverID) {
  wdt_reset();
  replied = false;
  RS485Send(receiverID, messageType[0], CMDLUT[1], 'C', 'N', 'G');
  tries++;
  delay(50);
  if (Serial.available() > 0) {
    lookForSTX = Serial.read();
    if (lookForSTX == STX) {
      RS485Receive();
    }
  }
  if (replied == false) {
    if (tries < 2) {
      getChanges(receiverID); // try again
    }
    else {
      //add to error list
      addToErrorList(receiverID, errorCodes[1]);
      tries = 0;
      replied = false;
    }
  }
}

//===================================[COMPARE_FLOOR_COUNT]================================
void compareFloor(char _floorID, char sign, char _count) {
  wdt_reset();

  tempF1Count = currentFloorCount[0];
  tempF2Count = currentFloorCount[1];
  tempF3Count = currentFloorCount[2];
  tempF4Count = currentFloorCount[3];

  if (_floorID == floorNaddresses[0]) {
    if (sign == '-') {
      countChanged = true;
      tempF1Count -= _count;
    }
    else {
      if (isF1Negative == true) {
        isF1Negative = false;
      }
      else {
        tempF1Count += _count;
        countChanged = true;
      }
    }
  }
  else if (_floorID == floorNaddresses[1]) {
    if (sign == '-') {
      tempF2Count -= _count;
      countChanged = true;
    }
    else {
      if (isF2Negative == true) {
        isF2Negative = false;
      }
      else {
        tempF2Count += _count;
        countChanged = true;
      }
    }
  }
  else if (_floorID == floorNaddresses[2]) {
    if (sign == '-') {
      tempF3Count -= _count;
      countChanged = true;
    }
    else {
      if (isF3Negative == true) {
        isF3Negative = false;
      }
      else {
        tempF3Count += _count;
        countChanged = true;
      }
    }
  }
  else if (_floorID == floorNaddresses[3]) {
    if (sign == '-') {
      tempF4Count -= _count;
      countChanged = true;
    }
    else {
      if (isF4Negative == true) {
        isF4Negative = false;
      }
      else {
        tempF4Count += _count;
        countChanged = true;
      }
    }
  }
  currentFloorCount[0] = tempF1Count;
  currentFloorCount[1] = tempF2Count;
  currentFloorCount[2] = tempF3Count;
  currentFloorCount[3] = tempF4Count;

  sendDisplayCount();
}

//===================================[SEND_DISPLAY_COUNT]================================
void sendDisplayCount() {
  wdt_reset();

  for (int i = 0; i <= 3; i++) {
    byte byteHuns = (currentFloorCount[i] / 100) + 0x30;
    byte byteTens = ((currentFloorCount[i] % 100) / 10) + 0x30;
    byte byteOnes = (currentFloorCount[i] % 10) + 0x30;
    delay(20);
    RS485Send(floorNaddresses[i], messageType[0], CMDLUT[2], byteHuns, byteTens, byteOnes);
    delay(20);
  }
}


//===================================[SEND_DISPLAY_COUNT]================================
void sendDisplayCountToUSB(byte _floorNum) {
  wdt_reset();

  tempF1Count = currentFloorCount[0];
  tempF2Count = currentFloorCount[1];
  tempF3Count = currentFloorCount[2];
  tempF4Count = currentFloorCount[3];

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
