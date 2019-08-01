/*
  Error codes come in following a dash and device ID on which the error occoured on.
  Example:
  E1-12 = Device with ID 12 is not responding.

  E0 : No error
  E1 : Device not responding.
  E2 : Invalid count on a device. Either lower than 0 or higher than it's configured number. See configuration file for proper count.
  E3 : Reserved
*/
//void RS485Send(byte receiverID, byte command, byte datahigh, byte datalow) {

void getErrors(int receiverID) {
  RS485Send(, , , );
  //start timeout timer
  tries++;
  while (newData == false) {
    RS485Receive();
  }
}

void sendErrorReport() {      //sends the errorDevices[] array to configurator program
  NOPdelay(160000);         // give the receiver a moment to prepare to receive
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTD |= (1 << PD5);      // Enable COM Led
  Serial.print(errorDevices);
  NOPdelay(160000);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTD &= ~(1 << PD5);     // Disable COM Led
}
