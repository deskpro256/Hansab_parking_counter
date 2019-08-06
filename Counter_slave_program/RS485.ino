//============================[RS485_SEND]========================

void RS485Send(byte receiverID, byte msgType, byte command, byte datahigh, byte datalow) {

  char msg [] = {
    STX,                // start of text
    receiverID,         // receiver address
    myID,               // transmitter address
    msgType,            // ENQ - ACK - NAK
    command,            // command
    datahigh,           // dataH
    datalow,            // dataL
    ETX,                // end of text
  };

  delay(100);
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTC |= (1 << PC5);      // Enable COM Led
  Serial.print(msg);
  delay(100);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTC &= ~(1 << PC5);     // Disable COM Led
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
//============================[RECEIVED_MY_ADDRESS]========================
//checks if the address byte has own or floor address
void isMyAddress() {
  if (recMsg[1] == myID || recMsg[1] == floorID) {
    //moves all the buff[] to a stored message value while also clearing the buffer
    for (int i = 0; i <= sizeBuff; i++) {
      recMsg[i] = buff[i];
      buff[i] = 0x00;
    }
    mesType = recMsg[3];
    CMD = recMsg[4];
    DATAH = recMsg[5];
    DATAL = recMsg[6];
    data2INT = DATAH + DATAL;
    
    getCMD(CMD, mesType, data2INT);
  }
}
