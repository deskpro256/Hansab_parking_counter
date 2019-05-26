
//============================[RECEIVED_MY_ADDRESS]========================
//checks if the address byte has slaves or floors address
void isMyAddress() {
  if (recMsg[1] == myID || recMsg[1] == floorID) {
    //moves all the buff[] to a stored message value while also clearing the buffer
    for (int i = 0; i <= sizeBuff; i++) {
      recMsg[i] = buff[i];
      buff[i] = 0x00;
    }
    CMD = recMsg[3];
    DATAH = recMsg[4];
    DATAL = recMsg[5];

    dataH = DATAH;
    dataL = DATAL;

    data2INT = dataH + dataL;
    getCMD();
  }
}

//============================[READ_SERIAL_BUFFER]========================
void readSerial() {
  //reads the serial data,stores data in a 7 byte buffer
  Serial.readBytes(buff, sizeBuff);
  //checks the buffer for the msg stx and etx bytes, if the buffer is still clear, there is no new data, return, if there is new data, continue on reading the message
  if (buff[0] == STX && buff[sizeBuff - 1] == ETX) {
    newData = true;
  }
  else {
    newData = false;
  }
}

