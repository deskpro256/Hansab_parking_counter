//PC0  A1 - EXTERNAL ANALOG PIN
//PC1  A2 - BATTERY ANALOG PIN
//PC2  G1 - EXTERNAL GATE
//PC3  G2 - BATTERY GATE

//============================[POWER_SOURCE]==========================================================
void CheckPowerSource() {
  // check if external power is connected
  int temp = 0;
  PORTC |= (1 << PC2);
  delay(10);
  temp = analogRead(PC0);
  PORTC &= ~(1 << PC2);
  if (temp > 10) {
    //send external
    temp = 0;
    sendSource('E');
  }
  PORTC |= (1 << PC3);
  delay(10);
  temp = analogRead(PC1);
  PORTC &= ~(1 << PC3);
  if (temp > 10) {
    //send battery
    temp = 0;
    sendSource('B');
  }
}
void CheckVoltages() {
  int ExtV = 0;
  int BattV = 0;

  PORTC |= (1 << PC2);
  delay(10);
  ExtV = analogRead(PC0);
  PORTC &= ~(1 << PC2);

  PORTC |= (1 << PC3);
  delay(10);
  BattV = analogRead(PC1);
  PORTC &= ~(1 << PC3);
}

//send voltage
void sendVoltage(int val) {
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTC |= (1 << PC5);      // Enable COM Led
  delay(10);
  Serial.println(val);
  delay(10);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTC &= ~(1 << PC5);     // Disable COM Led
}

void sendSource(char c) {
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  PORTC |= (1 << PC5);      // Enable COM Led
  delay(10);
  Serial.println(c);
  delay(10);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending
  PORTC &= ~(1 << PC5);     // Disable COM Led
}
