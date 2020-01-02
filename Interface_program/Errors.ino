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
      PORTD |= (1 << PD6);      // Enable ERR Led
      //add to error list
      addToErrorList(receiverID, errorCodes[1]);
      tries = 0;
      replied = false;
    }
  }

  PORTD &= ~(1 << PD6);     // Disable ERR Led
}

//===================================[SEND_ERROR_REPORT]=======================================

void sendErrorReport() {    //sends the errorDevices[] array to configurator program
  char ErrorDeviceText[] = "Error devices: \n";
  delay(50);
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTD |= (1 << PD5);      // Enable COM Led
  Serial.write(ErrorDeviceText, 16);
  Serial.write(errorDevices, 32);
  delay(1000);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTD &= ~(1 << PD5);     // Disable COM Led
}

void addToErrorList(int id, char errCode) {
  //add to error list
  errorDevices[id] = id;
  errorDevices[id + 1] = errCode;
}
