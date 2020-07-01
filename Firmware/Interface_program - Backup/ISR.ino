//============================[ISR]==========================================================

ISR(INT1_vect) {
  if (PIND & (1 << PD3)) {
    //PORTC |= (1 << PC2);      // Enable CFG Led
    PORTC &= ~(1 << PC2);     // Enable CFG Led
    ConfigEnabled = true;
  }
  else {
    //PORTC &= ~(1 << PC2);     // Disable CFG Led
    PORTC |= (1 << PC2);      // Disable CFG Led
    ConfigEnabled = false;
  }
}
