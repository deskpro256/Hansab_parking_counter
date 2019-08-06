//===================================[NUMBER_COUNTING]=======================================
void countNumbers() {
  totalCount = floorCount[0] + floorCount[1] + floorCount[2];
}

//===================================[GET_CHANGES]=======================================
void getChanges(int receiverID) {
  while (newData == false && tries <= 2) {
    RS485Send(receiverID, messageType[0], CMDLUT[1], 0x00, 0x00);
    //timerStart();
    tries++;
    RS485Receive();
  }
  if (tries > 2) {
    //add to error list
    errorDevices[receiverID - 1] = receiverID;
    errorDevices[receiverID] = errorCodes[1];
  }
  else {
    isMyAddress();
  }
}

//===================================[COMPARE_FLOOR_COUNT]================================
void compareFloor() {
  //
}

//===================================[SEND_DISPLAY_COUNT]================================
void sendDisplayCount() {
  //
}
