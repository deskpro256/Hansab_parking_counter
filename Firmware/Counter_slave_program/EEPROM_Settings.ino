
//============================[EEPROM_WRITE]========================
void writeEEPROMSettings(byte _type, byte _floorID, byte _count1, byte _count2, byte _count3) {
  wdt_reset();

  EEPROM.write(0, _type);
  EEPROM.write(1, _floorID);
  EEPROM.write(2, _count1);
  EEPROM.write(3, _count2);
  EEPROM.write(4, _count3);

  EEPROM.write(5, 0x69);
}

//============================[EEPROM_WRITE]========================
void readEEPROMSettings() {
  if (EEPROM.read(5) != 0x69) {
    //dafault values if the controller hasn't been configured. type 1, floor F1, 123 count
    EEPROM.write(0, 0x01);
    EEPROM.write(1, 0xF1);
    EEPROM.write(2, 0x31);
    EEPROM.write(3, 0x32);
    EEPROM.write(4, 0x33);

    EEPROM.write(5, 0x69);
  }
  else {
    wdt_reset();
    type = EEPROM[0];
    floorID = EEPROM[1];
    maxCount = ((EEPROM[2] - 48) * 100) + ((EEPROM[3] - 48) * 10) + (EEPROM[4] - 48); //count123
    count = maxCount;
    oldCount = count;
  }
}
