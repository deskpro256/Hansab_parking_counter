
//===================================[RS485_RECEIVE]=======================================

void RS485Receive() {
  //reads the serial data,stores data in an 8 byte buffer
  if (lookForSTX == STX) {
    lookForSTX = 0x00;
    Serial.readBytes(buff, sizeBuff - 1);
    newData = true;
    PORTD ^= (1 << PD3);
    isMyAddress();
  }
  else {
    newData = false;
  }

}
// char dispNum[] = {0x1B, 0x01, 0x00, 0x06, 0xA1, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};    // no write to eeprom & no reply
//============================[RECEIVED_MY_ADDRESS]========================
//checks if the address byte has own or floor address
void isMyAddress() {
  if (buff[0] == myID) {
    newData = false;
    //moves all the buff[] to a stored message value while also clearing the buffer
    for (int i = 0; i <= sizeBuff - 1; i++) {
      recMsg[i] = buff[i];
      buff[i] = 0x00;
    }
    huns = recMsg[8] - '0';
    tens = recMsg[7] - '0';
    ones = recMsg[6] - '0';

    count = (huns * 100) + (tens * 10) + (ones);
  }
}
