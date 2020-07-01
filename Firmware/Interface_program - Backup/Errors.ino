
/*
  Error codes come in following a dash and device ID on which the error occoured on.
  Example:
  E1-12 = Device with ID 12 is not responding.

  E0 : No error
  E1 : Device not responding.
  E2 : Invalid count on a device. Either lower than 0 or higher than it's configured number. See configuration file for proper count.
  E3 : Reserved
*/

/*
   Currently unused as the system takes care of false count on troubled devices
  //===================================[GET_ERRORS]=======================================

  void getErrors(char receiverID) {
  wdt_reset();
  replied = false;
  RS485Send(receiverID, messageType[0], CMDLUT[0], 'E', 'R', 'R');
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
      getErrors(receiverID); // try again
    }
    else {
      //add to error list
      addToErrorList(receiverID, errorCodes[1]);
      tries = 0;
      replied = false;
    }
  }
  }
*/

//===================================[COUNT_ERROR_CHECK]=======================================

void checkForCountError() {
  wdt_reset();
  //---------------------------
  if (currentFloorCount[0] < 0) {
    errorState = true;
    isF1Negative = true;
    currentFloorCount[0] = 0;
  }
  else if (currentFloorCount[0] > floorMaxCount[0]) {
    errorState = true;
    currentFloorCount[0] = floorMaxCount[0];
  }
  else {
    errorState = false;
  }
  //---------------------------
  if (currentFloorCount[1] < 0) {
    errorState = true;
    isF2Negative = true;
    currentFloorCount[1] = 0;
  }
  else if (currentFloorCount[1] > floorMaxCount[1]) {
    errorState = true;
    currentFloorCount[1] = floorMaxCount[1];
  }
  else {
    errorState = false;
  }
  //---------------------------
  if (currentFloorCount[2] < 0) {
    errorState = true;
    isF3Negative = true;
    currentFloorCount[2] = 0;
  }
  else if (currentFloorCount[2] > floorMaxCount[2]) {
    errorState = true;
    currentFloorCount[2] = floorMaxCount[2];
  }
  else {
    errorState = false;
  }
  //---------------------------
  if (currentFloorCount[3] < 0) {
    errorState = true;
    isF4Negative = true;
    currentFloorCount[3] = 0;
  }
  else if (currentFloorCount[3] > floorMaxCount[3]) {
    errorState = true;
    currentFloorCount[3] = floorMaxCount[3];
  }
  else {
    errorState = false;
  }
  //---------------------------
  if (errorState) {
    //PORTC |= (1 << PC3); //error led on
    PORTC &= ~(1 << PC3);//error led on
  }
  else {
    //PORTC &= ~(1 << PC3);//error led off
    PORTC |= (1 << PC3); //error led off
  }
}


//===================================[SEND_ERROR_REPORT]=======================================

void sendErrorReport() {    //sends the errorDevices[] array to configurator program
  wdt_reset();
  int idGet = 0; // Device ID got from error device list to add to the string if the ID is 9 and lower, have 0 in fron, if larger then add a 1 in front.
  char dev[2] = {'0', '0'};  //device ID 00 - 0F
  char code; // error code to add
  char ErrorDeviceText1[] = "Error devices: \n"; //string to send to the software
  char ErrorDeviceText2[] = "ID | ErrorCode \n"; //string to send to the software
  delay(50);
  PORTD |= (1 << PD4);      // (RE_DE, HIGH) enable sending
  //PORTC |= (1 << PC2);      // Enable COM Led
  //perf test device
  PORTC |= (1 << PC1);      // Enable COM Led
  Serial.write(ErrorDeviceText1, 16);
  delay(10);
  Serial.write(ErrorDeviceText2, 16);
  //for (int i = 0; i <= 31; i += 2) {
  for (int i = 0; i <= (slaveCount * 2) - 1; i += 2) {
    idGet = errorDevices[i];
    if (idGet < 10) {
      dev[0] = '0';
      dev[1] = errorDevices[i] + 48;
    }
    else {
      dev[0] = '1';
      dev[1] = errorDevices[i] + 38;
    }
    code = errorDevices[i + 1];

    Serial.write(dev[0]);
    Serial.write(dev[1]);
    Serial.write(" - E");
    Serial.write(code);
    Serial.write("\n");
    delay(10);
  }
  delay(1000);
  wdt_reset();
  PORTD &= ~(1 << PD4);     // (RE_DE, LOW) disable sending
  //PORTC &= ~(1 << PC2);     // Disable COM Led
  //perf test device
  PORTC &= ~(1 << PC1);     // Disable COM Led
}

void addToErrorList(int id, char errCode) {
  wdt_reset();
  //add to error list
  errorDevices[id * 2] = id;
  errorDevices[(id * 2) + 1] = errCode;
}
