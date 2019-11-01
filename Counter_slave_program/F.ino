
//===============================[CONFIGURATION MODE]================================
//FTS MESSAGE:
/*  STX RXID TXID CMD TYPE FLOORID MAX MIN  */


void ReceiveConfig() {
  //reads the serial data,stores data in an 8 byte buffer
  char lookForSTX;
  while (lookForSTX != STX) {
    lookForSTX = Serial.read();
  }
  if (lookForSTX == STX) {
    Serial.readBytes(buff, sizeBuff);
    //------
    PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
    PORTD |= (1 << PD5);      // Enable COM Led
    delay(10);
    Serial.write(buff, sizeBuff);
    delay(10);
    PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
    PORTD &= ~(1 << PD5);     // Disable COM Led
    //------
    newData = true;
    isMyAddress();
  }
  else {
    newData = false;
    ReceiveConfig();
  }

  // if received my address
  if (recMsg[1] == myID) {
    newData = false;
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

    writeEEPROMSettings();
  }

}
