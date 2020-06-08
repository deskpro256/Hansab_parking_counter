//SLAVE COUNT FLOORID[1]  COUNT 1  COUNT 2  COUNT 3  FLOORID[2]  COUNT 1  COUNT 2  COUNT 3  FLOORID[3]  COUNT 1  COUNT 2  COUNT 3  FLOORID[4]  COUNT 1  COUNT 2  COUNT 3

//===============================[CONFIGURATION MODE]================================
//FTS MESSAGE:
//  0    1    2    3     4        5      6      7       8      9      10      11     12     13     14     15     16    17
/*  STX RXID TXID CMD SLAVECNT  COUNT1 COUNT2 COUNT3  COUNT1 COUNT2 COUNT3  COUNT1 COUNT2 COUNT3  COUNT1 COUNT2 COUNT3 ETX */


void ReceiveConfig() {
  wdt_reset();
  //reads the serial data,stores data in an 17 byte buffer
  char lookForSTX;
  while (lookForSTX != STX) {
    wdt_reset();
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
  if (configBuff[0] == myID) {
    newData = false;
    //moves all the buff[] to a stored message value while also clearing the buffer
    for (int i = 0; i <= sizeConfigBuff; i++) {
      recConfig[i] = configBuff[i];
      configBuff[i] = 0x00;
    }

    slaveCount  = recConfig[3];                                                                           //Slave  count

    tempF1Count = ((recConfig[4]   - 48) * 100) + ((recConfig[5]   - 48) * 10) + (recConfig[6]   - 48);   //Floor1 count
    tempF2Count = ((recConfig[7]   - 48) * 100) + ((recConfig[8]   - 48) * 10) + (recConfig[9]   - 48);   //Floor2 count
    tempF3Count = ((recConfig[10]  - 48) * 100) + ((recConfig[11]  - 48) * 10) + (recConfig[12]  - 48);   //Floor3 count
    tempF4Count = ((recConfig[13]  - 48) * 100) + ((recConfig[14]  - 48) * 10) + (recConfig[15]  - 48);   //Floor4 count

    writeEEPROMSettings(recConfig[3],
                        recConfig[4], recConfig[5], recConfig[6],
                        recConfig[7], recConfig[8], recConfig[9],
                        recConfig[10], recConfig[11], recConfig[12],
                        recConfig[13], recConfig[14], recConfig[15]);
  }

}
