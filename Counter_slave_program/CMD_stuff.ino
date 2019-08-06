
//char CMDLUT[] = {
// 0x01 - getErrors
// 0x02 - getChanges
// 0x03 - sendDisplayCount
// 0x04 - clearErrors
// 0x05 - firstTimeSetup
// 0x06 -
// 0x07 -
// 0x08 -
// 0x09 -
// };     a look up table for every command

//char messageType[] = {
//                      0x05 - ENQ
//                      0x06 - ACK
//                      0x21 - NAK
//};                     a look up table for every messageType

//============================[GET_CMD_NAME]========================
// gets the command byte from the message and executes the corresponding func
void getCMD(char cmd, char msgType, int data) {

  if (cmd == CMDLUT[0]) {  // getError
    sendErrorReport(errorCount);
  }
  if (cmd == CMDLUT[1]) {  //getChanges
    if (changedCount = true) {
      unsigned int changedCount = oldCount - count;
      RS485Send(RXID, messageType[1], CMDLUT[1], inOut, changedCount);
    }
    else {
      RS485Send(RXID, messageType[1], CMDLUT[1], 0x00, 0x00);
    }
  }
  if (cmd == CMDLUT[2]) {

  }
  if (cmd == CMDLUT[3]) {

  }
  if (cmd == CMDLUT[4]) {

  }
  if (cmd == CMDLUT[5]) {

  }
  if (cmd == CMDLUT[6]) {

  }
  if (cmd == CMDLUT[7]) {

  }
  if (cmd == CMDLUT[8]) {

  }
}
