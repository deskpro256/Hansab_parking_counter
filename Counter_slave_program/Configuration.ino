//TYPE[1-5]  FLOORID[1-4]  COUNT Data 1  COUNT Data 2  COUNT Data 3


//===============================[CONFIGURATION MODE]================================
//FTS MESSAGE:
/*  STX RXID TXID CMD TYPE FLOORID COUNT1 COUNT2 COUNT3 ETX*/

void ReceiveConfig() {
  //reads the serial data,stores data in an 10 byte buffer
  lookForSTX;
  while (lookForSTX != STX) {
    lookForSTX = Serial.read();
  }
  if (lookForSTX == STX) {
    Serial.readBytes(configBuff, sizeConfigBuff - 1);
    newData = true;
  }
  else {
    newData = false;
    ReceiveConfig();
  }

  // if received my address
  if (recMsg[1] == myID) {
    newData = false;
    //moves all the buff[] to a stored message value while also clearing the buffer
    for (int i = 0; i <= sizeConfigBuff; i++) {
      recMsg[i] = configBuff[i];
      configBuff[i] = 0x00;
    }
    type = recConfig[3]; //type
    floorID = recConfig[4]; //floorid
    maxCount = ((recConfig[5] - 48) * 100) + ((recConfig[6] - 48) * 10) + (recConfig[7] - 48); //count123
    count = maxCount;

    writeEEPROMSettings(recConfig[3], recConfig[4], recConfig[5], recConfig[6], recConfig[7]);
  }

}
