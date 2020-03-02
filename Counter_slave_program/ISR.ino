
//============================[ISR]================================================================================
//isr for pins L4-L8
//PB1   L4
//PB2   L5
//PB3   L6
//PB4   L7
//PB5   L8

//isr for pins L1-L3


ISR(PCINT1_vect) {
  debounceISR();
  if (contactPressed) {

    //L1
    if (!(PINC & (1 << PC2))) {
      L1_flag = true;
    }
    //L2
    if (!(PINC & (1 << PC1))) {
      L2_flag = true;
    }
    //L3
    if (!(PINC & (1 << PC0))) {
      L3_flag = true;
    }

    checkLoops();
  }
}

ISR(PCINT0_vect) {
  debounceISR();
  if (contactPressed) {

    //L4
    if (!(PINB & (1 << PB5))) {
      L4_flag = true;
    }
    //L5
    if (!(PINB & (1 << PB4))) {
      L5_flag = true;
    }
    //L6
    if (!(PINB & (1 << PB3))) {
      L6_flag = true;
    }
    //L7
    if (!(PINB & (1 << PB2))) {
      L7_flag = true;
    }
    //L8
    if (!(PINB & (1 << PB1))) {
      L8_flag = true;
    }

    checkLoops();
  }
}
