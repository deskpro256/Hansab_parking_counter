//===================================[RS485_SEND]=======================================

void RS485Send(byte receiverID, byte command, byte datahigh, byte datalow) {

  char msg [] = {
    STX,                // start of text
    receiverID,         // receiver address
    myID,               // transmitter address
    command,            // command
    datahigh,           // dataH
    datalow,            // dataL
    ETX,                // end of text
  };

  NOPdelay(160000);         // give the receiver a moment to prepare to receive
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTD |= (1 << PD5);      // Enable COM Led
  Serial.print(msg);
  NOPdelay(160000);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTD &= ~(1 << PD5);     // Disable COM Led
}

//===================================[RS485_RECEIVE]=======================================

void RS485Receive() {
  //reads the serial data,stores data in a 8 byte buffer
  Serial.readBytes(buff, sizeBuff);
  //checks the buffer for the msg stx and etx bytes, if the buffer is still clear, there is no new data, return, if there is new data, continue on reading the message
  if (buff[0] == STX && buff[sizeBuff - 1] == ETX) {
    newData = true;
  }
  else {
    newData = false;
  }
}
void greeting(){  
  NOPdelay(160000);         // give the receiver a moment to prepare to receive
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTD |= (1 << PD5);      // Enable COM Led
  Serial.println(connectedString);
  Serial.println(versionNum);
  NOPdelay(160000);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTD &= ~(1 << PD5);     // Disable COM Led
    }
