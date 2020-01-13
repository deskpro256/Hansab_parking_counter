
//char CMDLUT[] = {
// 0x01 - getErrors
// 0x02 - getChanges
// 0x03 - sendDisplayCount
// 0x04 - clearErrors
// 0x05 - firstTimeSetup
// 0x06 - ping/pong
// 0x07 - sendDisplayCountToUSB
// 0x08 - sendErrorReport
// 0x09 - restart
// 0x0A -
// };     a look up table for every command

//char messageType[] = {
//                      0x05 - ENQ
//                      0x06 - ACK
//                      0x21 - NAK
//};                     a look up table for every messageType

//============================[GET_CMD_NAME]========================
// gets the command byte from the message and executes the corresponding func
void getCMD(char cmd, char msgType, char _ones, char _tens, char _hundreds) {
  //--------------------------------------
  if (cmd == CMDLUT[0]) {  // getError
    if (msgType == messageType[1]) { //if error
      addToErrorList(currentAddress, errorCodes[2]);
    }
  }
  //--------------------------------------
  if (cmd == CMDLUT[1]) {   //getChanges
    // floor sign count
    // ones
    //hundreds = + or -, tens = count diff,ones = floorNum
    if (msgType == messageType[1]) { //if changes
      compareFloor(_ones, _hundreds, _tens);
    }
  }
  //--------------------------------------
  if (cmd == CMDLUT[2]) { // 0x03 - sendDisplayCount
    //msgType == floorNaddresses[]
    if (msgType == floorNaddresses[0]) {
      tempF1Count =  ((_hundreds - '0') * 100) + ((_tens - '0') * 10) + (_ones - '0');
    }
    else if (msgType == floorNaddresses[1]) {
      tempF2Count =  ((_hundreds - '0') * 100) + ((_tens - '0') * 10) + (_ones - '0');
    }
    else if (msgType == floorNaddresses[2]) {
      tempF3Count =  ((_hundreds - '0') * 100) + ((_tens - '0') * 10) + (_ones - '0');
    }
    else if (msgType == floorNaddresses[3]) {
      tempF4Count =  ((_hundreds - '0') * 100) + ((_tens - '0') * 10) + (_ones - '0');
    }
    countChanged = true;
    currentFloorCount[0] = tempF1Count;
    currentFloorCount[1] = tempF2Count;
    currentFloorCount[2] = tempF3Count;
    currentFloorCount[3] = tempF4Count;
  }
  //--------------------------------------
  if (cmd == CMDLUT[3]) { // 0x04 - clearErrors
    for (int e = 0; e <= 32; e++) {
      errorDevices[e] = 0x00;
    }
  }
  //--------------------------------------
  if (cmd == CMDLUT[4]) { // 0x05 - firstTimeSetup
    ReceiveConfig();
    SW_Reset();
  }
  //--------------------------------------
  if (cmd == CMDLUT[5]) { // 0x06 - ping/pong
    RS485Send(0x1C, messageType[1], 'P', 'O', 'N', 'G');
  }
  //--------------------------------------
  if (cmd == CMDLUT[6]) { // 0x07 - sendDisplayCountToUSB
    sendDisplayCountToUSB(msgType);
  }
  //--------------------------------------
  if (cmd == CMDLUT[7]) { // 0x08 - sendErrorReport
    sendErrorReport();
  }
  //--------------------------------------
  if (cmd == CMDLUT[8]) { // 0x09 -  restart
    SW_Reset();
  }
  //--------------------------------------
  if (cmd == CMDLUT[9]) { // 0x0A -
    //reserved
  }
  //--------------------------------------
}
