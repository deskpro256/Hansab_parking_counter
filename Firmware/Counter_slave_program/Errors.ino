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
  wdt_reset();
  if (errorState) {
    byte byteHuns = (errcount / 100) + 0x30;
    byte byteTens = ((errcount % 100) / 10) + 0x30;
    byte byteOnes = (errcount % 10) + 0x30;
    RS485Send(RXID, messageType[1], CMDLUT[0], byteHuns, byteTens, byteOnes);
  }
  //send error with errcount
  else {
    RS485Send(RXID, messageType[2], CMDLUT[0], 0x78 , 0x78, 0x78);
    //reply with no error
  }
}
//============================[ERROR_CHECK]========================

void errorCheck() {
  wdt_reset();
  // error state check. If the count is not within the margins set by min/max turn on the error LED, master ticks the error in a log file
  if (count < 0 || count > maxCount) {
    PORTC |= (1 << PC3); //error led on
    //errorState = true;
    //errorCount = count;
    //count = 0;
  }
  else {
    PORTC &= ~(1 << PC3);//error led off
  }
}

//============================[CLEAR_ERRORS]========================
void clearErrors() {
  wdt_reset();
  errorState = false;
}