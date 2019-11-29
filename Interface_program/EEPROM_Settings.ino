
//     0         1      2      3          4      5      6           7     8       9         10     11     12
//SLAVECNT     COUNT1 COUNT2 COUNT3     COUNT1 COUNT2 COUNT3     COUNT1 COUNT2 COUNT3     COUNT1 COUNT2 COUNT3
//============================[EEPROM_WRITE]========================
void writeEEPROMSettings( byte _slaveCount,
                          byte _Floor1Byte1, byte _Floor1Byte2, byte _Floor1Byte3,
                          byte _Floor2Byte1, byte _Floor2Byte2, byte _Floor2Byte3,
                          byte _Floor3Byte1, byte _Floor3Byte2, byte _Floor3Byte3,
                          byte _Floor4Byte1, byte _Floor4Byte2, byte _Floor4Byte3) {

  EEPROM[0] = _slaveCount;
  //floor 1
  EEPROM[1] = _Floor1Byte1;
  EEPROM[2] = _Floor1Byte2;
  EEPROM[3] = _Floor1Byte3;
  //floor 2
  EEPROM[4] = _Floor2Byte1;
  EEPROM[5] = _Floor2Byte2;
  EEPROM[6] = _Floor2Byte3;
  //floor 3
  EEPROM[7] = _Floor3Byte1;
  EEPROM[8] = _Floor3Byte2;
  EEPROM[9] = _Floor3Byte3;
  //floor 4
  EEPROM[10] = _Floor4Byte1;
  EEPROM[11] = _Floor4Byte2;
  EEPROM[12] = _Floor4Byte3;

}

//============================[EEPROM_WRITE]========================
void readEEPROMSettings() {

  slaveCount  = EEPROM[0];                                                                //Slave  count
  tempF1Count = ((EEPROM[1]  - 48) * 100) + ((EEPROM[2]  - 48) * 10) + (EEPROM[3]  - 48); //Floor1 count
  tempF2Count = ((EEPROM[4]  - 48) * 100) + ((EEPROM[5]  - 48) * 10) + (EEPROM[6]  - 48); //Floor2 count
  tempF3Count = ((EEPROM[7]  - 48) * 100) + ((EEPROM[8]  - 48) * 10) + (EEPROM[9]  - 48); //Floor3 count
  tempF4Count = ((EEPROM[10] - 48) * 100) + ((EEPROM[11] - 48) * 10) + (EEPROM[12] - 48); //Floor4 count

  floorCount[0] = tempF1Count;
  floorCount[1] = tempF2Count;
  floorCount[2] = tempF3Count;
  floorCount[3] = tempF4Count;
}

void fakeEEPROM() {
  EEPROM[0] = 1;
  //floor 1
  EEPROM[1] = 0x31;
  EEPROM[2] = 0x32;
  EEPROM[3] = 0x33;
  //floor 2
  EEPROM[4] = 0x34;
  EEPROM[5] = 0x35;
  EEPROM[6] = 0x36;
  //floor 3
  EEPROM[7] = 0x37;
  EEPROM[8] = 0x38;
  EEPROM[9] = 0x39;
  //floor 4
  EEPROM[10] = 0x31;
  EEPROM[11] = 0x31;
  EEPROM[12] = 0x31;

}
