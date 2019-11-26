//===================================[RS485_SEND]=======================================

void RS485Send(char receiverID, char msgType, char command, char data1, char data2, char data3) {

  msg[0] = STX;
  msg[1] = receiverID;
  msg[2] = myID;
  msg[3] = msgType;
  msg[4] = command;
  msg[5] = data1;
  msg[6] = data2;
  msg[7] = data3;

  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTD |= (1 << PD5);      // Enable COM Led
  delay(10);
  Serial.write(msg, sizeBuff);
  delay(10);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTD &= ~(1 << PD5);     // Disable COM Led
}

//===================================[RS485_RECEIVE]=======================================

void RS485Receive() {
  //reads the serial data,stores data in an 8 byte buffer
  if (lookForSTX == STX) {
    lookForSTX = 0x00;
    Serial.readBytes(buff, sizeBuff - 1);
    newData = true;
    isMyAddress();
  }
  else {
    newData = false;
  }
}


//============================[RECEIVED_MY_ADDRESS]========================
//checks if the address byte has its address

void isMyAddress() {

  if (buff[0] == myID || buff[0] == 0xF1 || buff[0] == 0xF2 || buff[0] == 0xF3 || buff[0] == 0xF4) {
    newData = false;
    replied = true;
    //moves all the buff[] to a stored message value while also clearing the buffer
    for (int i = 0; i <= sizeBuff - 1; i++) {
      recMsg[i] = buff[i];
      buff[i] = 0x00;
    }
    if (recMsg[0] != myID) {
      mesType = recMsg[0];
    }
    else {
      mesType = recMsg[2];
    }
    CMD = recMsg[3];
    huns = recMsg[4];
    tens = recMsg[5];
    ones = recMsg[6];
    getCMD(CMD, mesType, ones, tens, huns);
  }
}
