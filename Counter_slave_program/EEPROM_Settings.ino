
//============================[EEPROM_WRITE]========================
void writeEEPROMSettings(byte _type, byte _floorID, byte _count1, byte _count2, byte _count3) {

  EEPROM.write(0, _type);
  EEPROM.write(1, _floorID);
  EEPROM.write(2, _count1);
  EEPROM.write(3, _count2);
  EEPROM.write(4, _count3);
  SW_Reset();
}

//============================[EEPROM_WRITE]========================
void readEEPROMSettings() {

  type = EEPROM[0];
  floorID = EEPROM[1];
  maxCount = ((EEPROM[2] - 48) * 100) + ((EEPROM[3] - 48) * 10) + (EEPROM[4] - 48); //count123
  count = maxCount;
}
