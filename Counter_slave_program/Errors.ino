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
//send error with errcount
  }
  else {
//reply with no error
  }
}
