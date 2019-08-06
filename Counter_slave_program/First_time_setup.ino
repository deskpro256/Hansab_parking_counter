//FTS MESSAGE:
/*  STX RXID TXID CMD TYPE FLOORID MAX MIN ETX */

//===============================[IS THIS THE FIRST TIME CONFIGURING?]================================
void isFirstCfgTime() {
  if (EEPROM[0] = 1) {
    loop();
  }
  else {
    EEPROM[0] = 1;
    loop();
    //configurationMode();
  }
}

//===============================[CONFIGURATION MODE]================================
//FTS MESSAGE:
/*  STX RXID TXID CMD TYPE FLOORID MAX MIN ETX */

void configurationMode() {
  if (Serial.available()) {  //wait for config from PC software
    PORTC ^= (1 << PD5);
    Serial.readBytes(buff, sizeBuff); //reads the serial data,stores data in a 8 byte buffer
    //checks the buffer for the msg stx and etx bytes, if the buffer is still clear, there is no new data, return, if there is new data, continue on reading the message
    if (buff[0] == STX && buff[sizeBuff - 1] == ETX) {
      newData = true;
    }
    else {
      newData = false;
      configurationMode();
    }
    if (newData == true) {
      PORTC ^= (1 << PD5);
      if (recMsg[1] == myID) {
        //moves all the buff[] to a stored message value while also clearing the buffer
        for (int i = 0; i <= sizeBuff - 1; i++) {
          recMsg[i] = buff[i];
          buff[i] = 0x00;
        }
        CMD = recMsg[2];
        type = recMsg[3];
        floorID = recMsg[4];
        DATAH = recMsg[5];
        DATAL = recMsg[6];
        data2INT = DATAH + DATAL;
        
        getCMD(CMD, mesType, data2INT);
      }
    }
  }
}
