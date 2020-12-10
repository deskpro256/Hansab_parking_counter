//===================================[RS485_SEND]=======================================

void RS485Send(char receiverID, char msgType, char command, char data1, char data2, char data3) {
  wdt_reset();

  msg[0] = STX;
  msg[1] = receiverID;
  msg[2] = myID;
  msg[3] = msgType;
  msg[4] = command;
  msg[5] = data1;
  msg[6] = data2;
  msg[7] = data3;
  msg[8] = ETX;

  PORTD |= (1 << PD4);      // (RE_DE, HIGH) enable sending
  //PORTC |= (1 << PC2);      // Enable COM Led
  //perf test device
  PORTC |= (1 << PC1);      // Enable COM Led
  delay(50);
  Serial.write(msg, sizeBuff);
  delay(50);
  PORTD &= ~(1 << PD4);     // (RE_DE, LOW) disable sending
  //PORTC &= ~(1 << PC2);     // Disable COM Led
  //perf test device
  PORTC &= ~(1 << PC1);     // Disable COM Led
}

//===================================[RS485_RECEIVE]=======================================

void RS485Receive() {
  wdt_reset();
  //reads the serial data,stores data in an 9 byte buffer
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
  wdt_reset();

  if ((buff[0] == myID || buff[0] == floorNaddresses[0] || buff[0] == floorNaddresses[1] || buff[0] == floorNaddresses[2] || buff[0] == floorNaddresses[3]) && buff[7] == ETX) {

    newData = false;
    replied = true;
    //moves all the buff[] to a stored message value while also clearing the buffer
    for (int i = 0; i <= sizeBuff; i++) {
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