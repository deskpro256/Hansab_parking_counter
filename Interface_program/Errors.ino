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
  while (newData == false && tries < 2) {
    RS485Send(receiverID, messageType[0], CMDLUT[0], 0x00, 0x00, 0x00);
    //timerStart();
    tries++;
    RS485Receive();
  }
  if (tries > 2) {
    //add to error list
    PORTD |= (1 << PD6);      // Enable ERR Led
    addToErrorList(receiverID, errorCodes[1]);
  }
  else {
    tries = 0;
    isMyAddress();
  }
  PORTD &= ~(1 << PD6);     // Disable ERR Led
  tries = 0;
}

//===================================[SEND_ERROR_REPORT]=======================================

void sendErrorReport() {    //sends the errorDevices[] array to configurator program
  delay(100);
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTD |= (1 << PD5);      // Enable COM Led
  Serial.write(errorDevices);
  delay(100);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTD &= ~(1 << PD5);     // Disable COM Led
}

void addToErrorList(char id, char errCode) {
  //add to error list
  errorDevices[id - 1] = id;
  errorDevices[id] = errCode;
}
