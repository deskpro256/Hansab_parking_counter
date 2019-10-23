
//char CMDLUT[] = {
// 0x01 - getErrors
// 0x02 - getChanges
// 0x03 - sendDisplayCount
// 0x04 - clearErrors
// 0x05 - firstTimeSetup
// 0x06 - ping/pong
// 0x07 - sendDisplayCountToUSB
// 0x08 - sendErrorReport
// 0x09 - request power data
// 0x0A -
// };     a look up table for every command

//char messageType[] = {
//                      0x05 - ENQ
//                      0x06 - ACK
//                      0x21 - NAK
//};                     a look up table for every messageType

//============================[GET_CMD_NAME]========================
// gets the command byte from the message and executes the corresponding func
void getCMD(char cmd, char msgType, int data) {

  if (cmd == CMDLUT[0]) {  // 0x01 - getErrors
    if (errorState) {
      sendErrorReport(errorCount);
    } else {
      RS485Send(0x1D, messageType[1], CMDLUT[0], 'N', 'E', 'r');
    }
  }
  if (cmd == CMDLUT[1]) {  // 0x02 - getChanges
    if (changedCount = true) {
      unsigned int changedCount = oldCount - count;
      RS485Send(RXID, messageType[1], CMDLUT[1], inOut, changedCount, 0x00);
    }
    else {
      RS485Send(RXID, messageType[2], CMDLUT[1], 0x00, 0x00, 0x00);
    }
  }
  if (cmd == CMDLUT[2]) { // 0x03 - sendDisplayCount
      drawDisplay(data);
  }
  if (cmd == CMDLUT[3]) { // 0x04 - clearErrors

  }
  if (cmd == CMDLUT[4]) { // 0x05 - firstTimeSetup

  }
  if (cmd == CMDLUT[5]) { // 0x06 - ping/pong
    RS485Send(0x1C, messageType[1], 'P', 'O', 'N', 'G');
  }
  if (cmd == CMDLUT[6]) { // 0x07 - request count from pc
    //do nothing
  }
  if (cmd == CMDLUT[7]) { // 0x08 - sendErrorReport
    //do nothing
  }
  if (cmd == CMDLUT[8]) { // 0x09 - request power data
    //do nothing
  }
  if (cmd == CMDLUT[9]) { // 0x0A -

  }
}
