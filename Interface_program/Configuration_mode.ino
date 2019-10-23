//FTS MESSAGE:
/*  STX RXID TXID CMD TYPE FLOORID MAX MIN ETX */

//===============================[CONFIGURATION MODE]================================

void configurationMode() {
  if (Serial.available() > 8) { //wait for config from PC software
    PORTC ^= (1 << PD5);
    Serial.readBytes(buff, sizeBuff); //reads the serial data,stores data in a 9 byte buffer
    //checks the buffer for the msg stx and etx bytes, if the buffer is still clear, there is no new data, return, if there is new data, continue on reading the message
    if (buff[0] == STX && buff[sizeBuff - 1] == ETX) {
      newData = true;
    }
    else {
      newData = false;
      configurationMode();
    }
    // if there is new data, start parsing it
    if (newData == true) {
      PORTC ^= (1 << PD5);
      // if received own address
      if (recMsg[1] == myID) {
        //moves all the buff[] to a stored message value while also clearing the buffer
        for (int i = 0; i <= sizeBuff - 1; i++) {
          recMsg[i] = buff[i];
          buff[i] = 0x00;
        }
        firstTimeSetup();
      }
      // else if received PING - reply with PONG
      else if (recMsg[4] == CMDLUT[5]) {
        RS485Send(0x99, messageType[1], CMDLUT[5], 'P', 'N', 'G');
      }

      // else if received slaves address. Store their data somewhere
      else {
        //moves all the buff[] to a stored message value while also clearing the buffer
        for (int i = 0; i <= sizeBuff - 1; i++) {
          recMsg[i] = buff[i];
          buff[i] = 0x00;
        }
        storeSlaveData();
      }
    }
  }
}

//============================[IS THIS THE FIRST TIME CONFIGURING?]===================================

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
