//============================[RS485_SEND]========================

void RS485Send(byte CMD, byte DATAH, byte DATAL) {

  char msg [] = {
    STX,                // start of text
    recID,              // receiver address
    myID,               // transmitter address
    CMD,                // command
    DATAH,              // dataH
    DATAL,              // dataL
    ETX,                // end of text
  };

  NOPdelay(1000);           // give the master a moment to prepare to receive
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  Serial.print(msg);
  NOPdelay(1000);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending

}

