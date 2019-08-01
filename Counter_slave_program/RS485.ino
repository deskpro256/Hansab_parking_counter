//============================[RS485_SEND]========================

void RS485Send(byte receiverID, byte command, byte datahigh, byte datalow) {

  char msg [] = {
    STX,                // start of text
    receiverID,         // receiver address
    myID,               // transmitter address
    command,            // command
    datahigh,           // dataH
    datalow,            // dataL
    ETX,                // end of text
  };

  NOPdelay(160000);         // give the receiver a moment to prepare to receive
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTD |= (1 << PC5);      // Enable COM Led
  Serial.print(msg);
  NOPdelay(160000);         
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTD &= ~(1 << PC5);     // Disable COM Led
}
