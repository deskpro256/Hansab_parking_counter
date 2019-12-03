
//============================[EEPROM_WRITE]========================
void writeEEPROMSettings(byte _type, byte _floorID, byte _count1, byte _count2, byte _count3) {

  EEPROM[0] = _type;
  EEPROM[1] = _floorID;
  EEPROM[2] = _count1;
  EEPROM[3] = _count2;
  EEPROM[4] = _count3;
  SW_Reset();
}

//============================[EEPROM_WRITE]========================
void readEEPROMSettings() {

  type = EEPROM[0];
  floorID = EEPROM[1];
  maxCount = ((EEPROM[2] - 48) * 100) + ((EEPROM[3] - 48) * 10) + (EEPROM[4] - 48); //count123
  count = maxCount;
}

void fakeEEPROM() {
  
  EEPROM[0] = 5; //type
  
  EEPROM[1] = 0xF1; //floor
  
  EEPROM[2] = 0x32; //cnt1
  EEPROM[3] = 0x33; //cnt2
  EEPROM[4] = 0x34; //cnt3
}
