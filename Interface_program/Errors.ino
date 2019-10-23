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
    RS485Send(receiverID, messageType[0], CMDLUT[0], 'E', 'R', 'R');
    delay(100);
    tries++;
    if (Serial.available() > 8) {
      RS485Receive();
    }
  //replied = false;
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

//===================================[SEND_ERROR_REPORT]=======================================

void sendErrorReport() {    //sends the errorDevices[] array to configurator program

  delay(10);
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTD |= (1 << PD5);      // Enable COM Led
  Serial.println(errorDevices);
  delay(10);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTD &= ~(1 << PD5);     // Disable COM Led
}

void addToErrorList(char id, char errCode) {
  //add to error list
  errorDevices[id] = id;
  errorDevices[id + 1] = errCode;
}
