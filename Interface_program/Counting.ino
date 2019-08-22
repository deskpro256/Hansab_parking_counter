//===================================[NUMBER_COUNTING]=======================================
void countNumbers() {
  totalCount = floorCount[0] + floorCount[1] + floorCount[2];
}

//===================================[GET_CHANGES]=======================================
void getChanges(int receiverID) {
  while (newData == false) {
    RS485Send(receiverID, messageType[0], CMDLUT[1], 0x00, 0x00, 0x00);
    //timerStart();
    tries++;
    RS485Receive();
  }
  if (tries > 2) {
    //add to error list
    errorDevices[receiverID - 1] = receiverID;
    errorDevices[receiverID] = errorCodes[1];
  }
  else {
    isMyAddress();
  }
}

//===================================[COMPARE_FLOOR_COUNT]================================
void compareFloor() {
  //
}

//===================================[SEND_DISPLAY_COUNT]================================
void sendDisplayCount() {
  //
}

//===================================[SEND_DISPLAY_COUNT_TO_USB]================================
void sendDisplayCountToUSB() {

  for (int i = 0; i <= 2; i++) {
    huns = (floorCount[i] / 100);
    tens = (floorCount[i] % 100) / 10;
    ones = (floorCount[i] % 10);
    char test[] = {'[', huns, tens, ones, ']'};
    delay(10);
    PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
    PORTD |= (1 << PD5);      // Enable COM Led
    Serial.println(test);
    delay(10);
    PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
    PORTD &= ~(1 << PD5);     // Disable COM Led
  }
}
