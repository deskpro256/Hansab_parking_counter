
//============================[ISR]================================================================================,,,,,,,,
//isr for pins L4-L8
//PB1   L4
//PB2   L5
//PB3   L6
//PB4   L7
//PB5   L8
ISR(PCINT0_vect) {
  cli();
  //L4
  if (!(PINB & (1 << PB1))) {
    L4_flag = true;
    sei();
    checkLoops();
  }
  //L5
  if (!(PINB & (1 << PB2))) {
    L5_flag = true;
    sei();
    checkLoops();
  }
  //L6
  if (!(PINB & (1 << PB3))) {
    L6_flag = true;
    sei();
    checkLoops();
  }
  //L7
  if (!(PINB & (1 << PB4))) {
    L7_flag = true;
    sei();
    checkLoops();
  }
  //L8
  if (!(PINB & (1 << PB5))) {
    L8_flag = true;
    sei();
    checkLoops();
  }
}
//['A','B'] >> carIn
//['B','A'] >> carOut
//isr for pins L1-L3
//PC0
//PC1
//PC2
ISR(PCINT1_vect) {
  cli();
  //L1
  if (!(PINC & (1 << PC2))) {
    L1_flag = true;
    sei();
    checkLoops();
  }

  //L2
  if (!(PINC & (1 << PC1))) {
    L2_flag = true;
    sei();
    checkLoops();
  }

  //L3
  if (!(PINC & (1 << PC0))) {
    L3_flag = true;
    sei();
    checkLoops();
  }
}

