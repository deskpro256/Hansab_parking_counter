/*
  Error codes come in following a dash and device ID on which the error occoured on.
  Example:
  E1-12 = Device with ID 12 is not responding.

  E0 : No error
  E1 : Device not responding.
  E2 : Invalid count on a device. Either lower than 0 or higher than it's configured number. See configuration file for proper count.
  E3 : Reserved
*/
//============================[SEND_ERROR_REPORT]========================

void sendErrorReport(int errcount) {      //sends the error report to master
  if (errorState == true) {
    if (errcount <= 255) {
      eH = 0x00;
      eL = errcount;
    }
    else if (errcount > 255) {
      eH = errcount - 255;
      eL = 255;
    }
    RS485Send(RXID, messageType[1], CMDLUT[0], eH , eL);
  }
  //send error with errcount
  else {
    RS485Send(RXID, messageType[2], CMDLUT[0], 0x00, 0x00);
    //reply with no error
  }
}
//============================[ERROR_CHECK]========================

void errorCheck() {
  // error state check. If the count is not within the margins set by min/max turn on the error LED, master ticks the error in a log file
  if (count < 0 || count > maxCount) {
    PORTC |= (1 << PC3);
    errorState = true;
    errorCount = count;
  }
  else {
    PORTC &= ~(1 << PC3);
  }
}

//============================[CLEAR_ERRORS]========================
void clearErrors() {
  errorState = false;
}
