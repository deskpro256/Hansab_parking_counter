
//NETWORK SETTINGS:
//   0   1    2    3      4     5   6   7   8     9  10  11  12     13  14  15  16   17
/*  STX RXID TXID CMD   DHCP   IP1 IP2 IP3 IP4   GW1 GW2 GW3 GW4   SN1 SN2 SN3 SN4   ETX */
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
    DHCP   = NWConfig[3];

    NetworkEEPROMWrite(NWConfig[3],
                       NWConfig[4], NWConfig[5], NWConfig[6], NWConfig[7],
                       NWConfig[8], NWConfig[9], NWConfig[10], NWConfig[11],
                       NWConfig[12], NWConfig[13], NWConfig[14], NWConfig[15]);

    // restart chip with new ethernet settings
    SW_Reset();
  }

}

//===================================[SEND NETWORK SETTINGS]=======================================
void sendNWSettings() {
  // convert bytes to numbers

  wdt_reset();

  DHCP = EEPROM[14];
  NetworkEEPROMRead();
  /*
    myIP = Ethernet.localIP();
    mySN = Ethernet.subnetMask();
    myGW = Ethernet.gatewayIP();
  */
  wdt_reset();

  PORTD |= (1 << PD4);      // (RE_DE, HIGH) enable sending
  //PORTC |= (1 << PC2);      // Enable COM Led
  //perf test device
  PORTC |= (1 << PC1);      // Enable COM Led
  delay(50);

  Serial.write(DHCPSetting, 8);
  if (DHCP == 0x01) {
    Serial.write(dhcpOn, 2);
  }
  else {
    Serial.write(dhcpOff, 3);
  }

  Serial.write(IPSettings, 6);
  Serial.print(IP[0]);
  Serial.print('.');
  Serial.print(IP[1]);
  Serial.print('.');
  Serial.print(IP[2]);
  Serial.print('.');
  Serial.print(IP[3]);
  //Serial.print(Ethernet.localIP());

  Serial.write(SNSettings, 6);
  Serial.print(SN[0]);
  Serial.print('.');
  Serial.print(SN[1]);
  Serial.print('.');
  Serial.print(SN[2]);
  Serial.print('.');
  Serial.print(SN[3]);
  //Serial.print(Ethernet.subnetMask());

  Serial.write(GWSettings, 6);
  Serial.print(GW[0]);
  Serial.print('.');
  Serial.print(GW[1]);
  Serial.print('.');
  Serial.print(GW[2]);
  Serial.print('.');
  Serial.print(GW[3]);
  //Serial.print(Ethernet.gatewayIP());

  Serial.write(MACSettings, 7);
  Serial.print(MAC[0], HEX);
  Serial.print(colon);
  Serial.print(MAC[1], HEX);
  Serial.print(colon);
  Serial.print(MAC[2], HEX);
  Serial.print(colon);
  Serial.print(MAC[3], HEX);
  Serial.print(colon);
  Serial.print(MAC[4], HEX);
  Serial.print(colon);
  Serial.println(MAC[5], HEX);

  delay(1000);
  wdt_reset();
  PORTD &= ~(1 << PD4);     // (RE_DE, LOW) disable sending
  //PORTC &= ~(1 << PC2);     // Disable COM Led
  //perf test device
  PORTC &= ~(1 << PC1);     // Disable COM Led
}


//===================================[RECEIVE MAC SETTINGS]=======================================
//                                                [   int    pc  maccmd MAC1  MAC2  MAC3  MAC4  MAC5  MAC6   ]  11 BYTES
void ReceiveMAC() {

  wdt_reset();
  //reads the serial data,stores data in an 17 byte buffer
  char lookForSTX;
  while (lookForSTX != STX) {
    wdt_reset();
    lookForSTX = Serial.read();
  }
  if (lookForSTX == STX) {
    Serial.readBytes(MACBuff, sizeMACConfigBuff - 1);
    newData = true;
  }
  else {
    newData = false;
    ReceiveMAC();
  }

  // if received my address
  if (MACBuff[0] == myID) {
    newData = false;
    //moves all the buff[] to a stored message value while also clearing the buffer
    for (int i = 0; i <= sizeMACConfigBuff; i++) {
      MACConfig[i] = MACBuff[i];
      MACBuff[i] = 0x00;
    }
    //DHCP   = MACConfig[3];

    MACEEPROMWrite(MACConfig[3],MACConfig[4], MACConfig[5], MACConfig[6], MACConfig[7],MACConfig[8]);

    // restart chip with new ethernet settings
    SW_Reset();
  }
}
