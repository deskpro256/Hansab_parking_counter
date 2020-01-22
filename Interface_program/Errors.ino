
/*
  Error codes come in following a dash and device ID on which the error occoured on.
  Example:
  E1-12 = Device with ID 12 is not responding.

  E0 : No error
  E1 : Device not responding.
  E2 : Invalid count on a device. Either lower than 0 or higher than it's configured number. See configuration file for proper count.
  E3 : Reserved
*/

//===================================[GET_ERRORS]=======================================

void getErrors(char receiverID) {
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


//===================================[COUNT_ERROR_CHECK]=======================================

void checkForCountError() {
  //---------------------------
  if (currentFloorCount[0] < 0) {
    errorState = true;
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
    PORTD |= (1 << PD6); //error led on
  }
  else {
    PORTD &= ~(1 << PD6);//error led off
  }
}


//===================================[SEND_ERROR_REPORT]=======================================

void sendErrorReport() {    //sends the errorDevices[] array to configurator program
  int idGet = 0;
  char dev[2] = {'0', '0'};
  char code;
  char ErrorDeviceText1[] = "Error devices: \n";
  char ErrorDeviceText2[] = "ID | ErrorCode \n";
  delay(50);
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTD |= (1 << PD5);      // Enable COM Led
  Serial.write(ErrorDeviceText1, 16);
  delay(10);
  Serial.write(ErrorDeviceText2, 16);
  for (int i = 0; i <= 31; i += 2) {
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
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTD &= ~(1 << PD5);     // Disable COM Led
}

void addToErrorList(int id, char errCode) {
  //add to error list
  errorDevices[id * 2] = id;
  errorDevices[(id * 2) + 1] = errCode;
}
