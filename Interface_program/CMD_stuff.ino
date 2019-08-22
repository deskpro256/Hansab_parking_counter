
//char CMDLUT[] = {
// 0x01 - getErrors
// 0x02 - getChanges
// 0x03 - sendDisplayCount
// 0x04 - clearErrors
// 0x05 - firstTimeSetup
// 0x06 - ping/pong
// 0x07 -
// 0x08 -
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
    if (msgType == messageType[1]) { //if error
      addToErrorList(currentAddress, errorCodes[2]);
    }
  }
  if (cmd == CMDLUT[1]) {   //getChanges
    if (msgType == messageType[1]) { //if changes
      
    //-----------------------here            
    }
  }
  if (cmd == CMDLUT[2]) { // 0x03 - sendDisplayCount

  }
  if (cmd == CMDLUT[3]) { // 0x04 - clearErrors

  }
  if (cmd == CMDLUT[4]) { // 0x05 - firstTimeSetup

  }
  if (cmd == CMDLUT[5]) { // 0x06 - ping/pong
      RS485Send(0x99, messageType[1], CMDLUT[5], 0x00, 0x00, 0x00);
  }
  if (cmd == CMDLUT[6]) { // 0x07 - sendDisplayCountToUSB
  }
  
  if (cmd == CMDLUT[7]) {

  }
  if (cmd == CMDLUT[8]) {

  }
}
