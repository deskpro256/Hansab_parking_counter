
//NETWORK SETTINGS:
//   0   1    2    3      4   5   6   7     8   9  10  11    12  13  14   15  16
/*  STX RXID TXID CMD    IP1 IP2 IP3 IP4   GW1 GW2 GW3 GW4   SN1 SN2 SN3 SN4  ETX */
void ReceiveNWConfig() {
  wdt_reset();
  //reads the serial data,stores data in an 17 byte buffer
  char lookForSTX;
  while (lookForSTX != STX) {
    wdt_reset();
    lookForSTX = Serial.read();
  }
  if (lookForSTX == STX) {
    Serial.readBytes(NWConfigBuff, sizeNWConfigBuff - 1);
    newData = true;
  }
  else {
    newData = false;
    ReceiveNWConfig();
  }

  // if received my address
  if (NWConfigBuff[0] == myID) {
    newData = false;
    //moves all the buff[] to a stored message value while also clearing the buffer
    for (int i = 0; i <= sizeNWConfigBuff; i++) {
      NWConfig[i] = NWConfigBuff[i];
      NWConfigBuff[i] = 0x00;
    }

    IP[0]  = NWConfig[3];
    IP[1]  = NWConfig[4];
    IP[2]  = NWConfig[5];
    IP[3]  = NWConfig[6];

    GW[0]  = NWConfig[7];
    GW[1]  = NWConfig[8];
    GW[2]  = NWConfig[9];
    GW[3]  = NWConfig[10];

    SN[0]  = NWConfig[11];
    SN[1]  = NWConfig[12];
    SN[2]  = NWConfig[13];
    SN[3]  = NWConfig[14];


    NetworkWrite(NWConfig[3], NWConfig[4], NWConfig[5], NWConfig[6],
                 NWConfig[7], NWConfig[8], NWConfig[9], NWConfig[10],
                NWConfig[11], NWConfig[12], NWConfig[13], NWConfig[14]);
  }

}
