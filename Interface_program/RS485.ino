//===================================[RS485_SEND]=======================================

void RS485Send(char receiverID, char msgType, char command, char data1, char data2, char data3) {
  /*
    msg[0] = STX;
    msg[1] = receiverID;
    msg[2] = myID;
    msg[3] = msgType;
    msg[4] = command;
    msg[5] = data1;
    msg[6] = data2;
    msg[7] = data3;
    msg[8] = ETX;
  */
  /*
  msg[0] = STX;
  msg[1] = 'H';
  msg[2] = 'e';
  msg[3] = 'l';
  msg[4] = 'l';
  msg[5] = 'o';
  msg[6] = '!';
  msg[7] = '?';
  msg[8] = ETX;
  */
  char something[] = {STX, receiverID, myID, msgType, command, data1, data2, data3, ETX};
  delay(10);
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTD |= (1 << PD5);      // Enable COM Led
  Serial.println(something);
  delay(10);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTD &= ~(1 << PD5);     // Disable COM Led
}

//===================================[RS485_RECEIVE]=======================================

void RS485Receive() {
  //reads the serial data,stores data in a byte buffer
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
//checks if the address byte has its address

void isMyAddress() {
  if (recMsg[1] == myID) {
    //moves all the buff[] to a stored message value while also clearing the buffer
    for (int i = 0; i <= sizeBuff; i++) {
      recMsg[i] = buff[i];
      buff[i] = 0x00;
    }
    mesType = recMsg[3];
    CMD = recMsg[4];
    huns = recMsg[5];
    tens = recMsg[6];
    ones = recMsg[7];
    data2INT = (huns * 100) + (tens * 10) + ones;

    getCMD(CMD, mesType, data2INT);
  }
}

//===================================[GREETING]=======================================

void greeting() {
  delay(10);
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTD |= (1 << PD5);      // Enable COM Led
  Serial.println(connectedString);
  Serial.println(versionNum);
  delay(10);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTD &= ~(1 << PD5);     // Disable COM Led
}

//====================[test]====================

void testSend(char what) {
  delay(10);
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTD |= (1 << PD5);      // Enable COM Led
  Serial.println(what);
  delay(10);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTD &= ~(1 << PD5);     // Disable COM Led
}
