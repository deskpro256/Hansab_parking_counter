
/*============================[MESSAGE_FORMAT]========================

   Because the Arduino's C++ code Serial function has it setup real start/stop bits, parity checks and other necessary UART configurations, we use a simple messaging protocol
   that checks addresses, commands and the data to use with the commands. If the slave receives its address, it then checks everything else in the message, if not, it discards it and waits for its address.

  char msg [] = {
    STX,                // start of text
    recID,              // receiver address
    myID,               // transmitter address
    CMD,                // command
    DATAH,              // dataH
    DATAL,              // dataL
    ETX,                // end of text
  };

*/

