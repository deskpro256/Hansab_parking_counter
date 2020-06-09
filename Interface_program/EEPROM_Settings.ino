
//     0         1      2      3          4      5      6           7     8       9         10     11     12
//SLAVECNT     COUNT1 COUNT2 COUNT3     COUNT1 COUNT2 COUNT3     COUNT1 COUNT2 COUNT3     COUNT1 COUNT2 COUNT3
//============================[EEPROM_WRITE]========================
void writeEEPROMSettings( byte _slaveCount,
                          byte _Floor1Byte1, byte _Floor1Byte2, byte _Floor1Byte3,
                          byte _Floor2Byte1, byte _Floor2Byte2, byte _Floor2Byte3,
                          byte _Floor3Byte1, byte _Floor3Byte2, byte _Floor3Byte3,
                          byte _Floor4Byte1, byte _Floor4Byte2, byte _Floor4Byte3,
                          byte actFloors) {

  //DEVICE SETTINGS

  wdt_reset();
  EEPROM.write(0, _slaveCount);
  //floor 1
  EEPROM.write(1, _Floor1Byte1);
  EEPROM.write(2, _Floor1Byte2);
  EEPROM.write(3, _Floor1Byte3);
  //floor 2
  EEPROM.write(4, _Floor2Byte1);
  EEPROM.write(5, _Floor2Byte2);
  EEPROM.write(6, _Floor2Byte3);
  //floor 3
  EEPROM.write(7, _Floor3Byte1);
  EEPROM.write(8, _Floor3Byte2);
  EEPROM.write(9, _Floor3Byte3);
  //floor 4
  EEPROM.write(10, _Floor4Byte1);
  EEPROM.write(11, _Floor4Byte2);
  EEPROM.write(12, _Floor4Byte3);
  
  EEPROM.write(28, actFloors);
  
  EEPROM.write(13, 0x69); // add the preset byte for further boot cycles

}

//============================[EEPROM_WRITE]========================
void readEEPROMSettings() {
  wdt_reset();
  //if the controller hasn't been configured yet, put some default IP values in.
  if (EEPROM.read(13) != 0x69) {
    EEPROM.write(0, 0x01);
    //floor 1
    EEPROM.write(1, 0x31);
    EEPROM.write(2, 0x32);
    EEPROM.write(3, 0x33);
    //floor 2
    EEPROM.write(4, 0x31);
    EEPROM.write(5, 0x32);
    EEPROM.write(6, 0x33);
    //floor 3
    EEPROM.write(7, 0x31);
    EEPROM.write(8, 0x32);
    EEPROM.write(9, 0x33);
    //floor 4
    EEPROM.write(10, 0x31);
    EEPROM.write(11, 0x32);
    EEPROM.write(12, 0x33);
    //active floor count
    EEPROM.write(28, 0x01);

    EEPROM.write(13, 0x69); // add the preset byte for further boot cycles
    readEEPROMSettings(); // now read the newly set values

  }
  // read the saved settings
  else {
    wdt_reset();
    slaveCount  = EEPROM[0];                                                                //Slave  count
    tempF1Count = ((EEPROM[1]  - 48) * 100) + ((EEPROM[2]  - 48) * 10) + (EEPROM[3]  - 48); //Floor1 count
    tempF2Count = ((EEPROM[4]  - 48) * 100) + ((EEPROM[5]  - 48) * 10) + (EEPROM[6]  - 48); //Floor2 count
    tempF3Count = ((EEPROM[7]  - 48) * 100) + ((EEPROM[8]  - 48) * 10) + (EEPROM[9]  - 48); //Floor3 count
    tempF4Count = ((EEPROM[10] - 48) * 100) + ((EEPROM[11] - 48) * 10) + (EEPROM[12] - 48); //Floor4 count
    //get maximum count for each floor
    floorMaxCount[0] = tempF1Count;
    floorMaxCount[1] = tempF2Count;
    floorMaxCount[2] = tempF3Count;
    floorMaxCount[3] = tempF4Count;
    //also set that count as current count
    currentFloorCount[0] = tempF1Count;
    currentFloorCount[1] = tempF2Count;
    currentFloorCount[2] = tempF3Count;
    currentFloorCount[3] = tempF4Count;
    //get active floor count
    activeFloors = EEPROM[28];
  }

}


//============================[NETWORK_WRITE]=======================
void NetworkWrite(byte dhcp,
                  byte IP_Byte1, byte IP_Byte2, byte IP_Byte3, byte IP_Byte4,
                  byte SN_Byte1, byte SN_Byte2, byte SN_Byte3, byte SN_Byte4,
                  byte GW_Byte1, byte GW_Byte2, byte GW_Byte3, byte GW_Byte4) {
  wdt_reset();

  // dhcp on/off
  EEPROM.write(14, dhcp);

  // IP ADDRESS
  EEPROM.write(15, IP_Byte1);
  EEPROM.write(16, IP_Byte2);
  EEPROM.write(17, IP_Byte3);
  EEPROM.write(18, IP_Byte4);

  // SUBNET
  EEPROM.write(19, SN_Byte1);
  EEPROM.write(20, SN_Byte2);
  EEPROM.write(21, SN_Byte3);
  EEPROM.write(22, SN_Byte4);

  // GATEWAY
  EEPROM.write(23, GW_Byte1);
  EEPROM.write(24, GW_Byte2);
  EEPROM.write(25, GW_Byte3);
  EEPROM.write(26, GW_Byte4);


  EEPROM.write(27, 0x69); // add the preset byte for further boot cycles

  if (dhcp == 0x00) {

    IPAddress ip(IP_Byte1, IP_Byte2, IP_Byte3, IP_Byte4);
    Ethernet.setLocalIP(ip);  // change the IP address

    IPAddress subnet(SN_Byte1, SN_Byte2, SN_Byte3, SN_Byte4);
    Ethernet.setLocalIP(subnet);  // change the SN address

    IPAddress gateway(GW_Byte1, GW_Byte2, GW_Byte3, GW_Byte4);
    Ethernet.setLocalIP(gateway);  // change the IP address

    IPAddress dns(GW_Byte1, GW_Byte2, GW_Byte3, GW_Byte4);
    Ethernet.setLocalIP(dns);  // change the DNS address

  }
  
  myIP = Ethernet.localIP();
  mySN = Ethernet.subnetMask();
  myGW = Ethernet.gatewayIP();
  DHCP = EEPROM[14];
  // restart ethernet chip with new ethernet settings
  //EthernetSetup();
}
//============================[NETWORK_READ]========================
void NetworkRead() {
  wdt_reset();
  //if the controller hasn't been configured yet, put some default IP values in.
  if (EEPROM.read(27) != 0x69) {

    // DHCP on/off
    EEPROM.write(14, 0x01); //dhcp off, default IP address

    // IP ADDRESS
    EEPROM.write(15, 192); //0xC01
    EEPROM.write(16, 168); //0xA8
    EEPROM.write(17, 0);   //0x00
    EEPROM.write(18, 177); //0xB1

    // GATEWAY
    EEPROM.write(19, 255); //0xFF
    EEPROM.write(20, 255); //0xFF
    EEPROM.write(21, 255); //0xFF
    EEPROM.write(22, 0);   //0xC0

    // SUBNET
    EEPROM.write(23, 192); //0xC0
    EEPROM.write(24, 168); //0xA8
    EEPROM.write(25, 0);   //0x00
    EEPROM.write(26, 1);   //0x01

    EEPROM.write(27, 0x69); // add the preset byte for further boot cycles
    NetworkRead(); // now read the newly set values

  }
  // get the saved settings
  else {
    wdt_reset();

    DHCP   = EEPROM[14];

    IP[0]  = EEPROM[15];
    IP[1]  = EEPROM[16];
    IP[2]  = EEPROM[17];
    GW[3]  = EEPROM[18];

    GW[0]  = EEPROM[19];
    GW[1]  = EEPROM[20];
    GW[2]  = EEPROM[21];
    SN[3]  = EEPROM[22];

    SN[0]  = EEPROM[23];
    SN[1]  = EEPROM[24];
    SN[2]  = EEPROM[25];
    SN[3]  = EEPROM[26];

  }

}
