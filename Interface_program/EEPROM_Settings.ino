
//     0         1      2      3          4      5      6           7     8       9         10     11     12
//SLAVECNT     COUNT1 COUNT2 COUNT3     COUNT1 COUNT2 COUNT3     COUNT1 COUNT2 COUNT3     COUNT1 COUNT2 COUNT3
//============================[EEPROM_WRITE]========================
void writeEEPROMSettings( byte _slaveCount,
                          byte _Floor1Byte1, byte _Floor1Byte2, byte _Floor1Byte3,
                          byte _Floor2Byte1, byte _Floor2Byte2, byte _Floor2Byte3,
                          byte _Floor3Byte1, byte _Floor3Byte2, byte _Floor3Byte3,
                          byte _Floor4Byte1, byte _Floor4Byte2, byte _Floor4Byte3) {

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

  EEPROM.write(13, 0x69); // preset byte to look for
}

//============================[EEPROM_WRITE]========================
void readEEPROMSettings() {
  wdt_reset();
  //if the controller hasn't been configured yet, put some default values in. 1 slave, 123 spaces in each floor
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

    EEPROM.write(13, 0x69); // preset byte to look for
  }
  else {
    wdt_reset();
    //slaveCount  = EEPROM[0];                                                                //Slave  count
    slaveCount  = EEPROM.read(0);
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
  }

}
