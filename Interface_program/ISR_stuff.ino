//============================[ISR]==========================================================

ISR(INT1_vect) {
  if (PIND & (1 << PD3)) {
    PORTD |= (1 << PD7);      // Enable CFG Led
    configurationMode();
  }
  else {
    PORTD &= ~(1 << PD7);     // Disable CFG Led
  }
}
