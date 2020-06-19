
//============================[CHECK_LOOPS]========================

/* Types
    Type 1: [↑][↓]  separate directional entrance and exit
      L1 - L4 = OUT (L1&&L2)|(L3&&L4)
      L5 - L8 = IN  (L5&&L6)|(L7&&L8)
    Type 2:  eco   sigle loop action
      L1 - L4 = OUT (L1)(L2)(L3)(L4)
      L5 - L8 = IN  (L5)(L6)(L7)(L8)
    Type 3: [↓↑]   single bidirectional entrance
      L1 - L4 = IN/OUT (L1::L2)(L3::L4)
      L5 - L8 = IN/OUT (L5::L6)(L7::L8)
*/

void checkLoops() {

  wdt_reset();
  PORTC ^= (1 << PC4);

  //====================================================================================
  /*
    Type 1: [↑][↓]  separate directional entrance and exit
      L1 - L4 = OUT (L1&&L2)|(L3&&L4)
      L5 - L8 = IN  (L5&&L6)|(L7&&L8)
  */
  if (type == 1) {
    //==========================OUT==============================
    //L1 && L2
    if (!(PINC & (1 << PC2)) && !(PINC & (1 << PC1))) {
      //carOUT
      count++;
    }
    //L3 && L4
    if (!(PINC & (1 << PC0)) && !(PINB & (1 << PB5))) {
      //carOUT
      count++;
    }
    //==========================IN==============================
    //L5 && L6
    if (!(PINB & (1 << PB4)) && !(PINB & (1 << PB3))) {
      //carIN
      count--;
    }
    //L7 && L8
    if (!(PINB & (1 << PB2)) && !(PINB & (1 << PB1))) {
      //carIN
      count--;
    }

  }

  //====================================================================================
  /*
    Type 2:  eco   eco(sigle loop action)
      L1 - L4 = OUT (L1)(L2)(L3)(L4)
      L5 - L8 = IN  (L5)(L6)(L7)(L8)
  */
  else if (type == 2) {
    //==========OUT==============
    //L1
    if (!(PINC & (1 << PC2))) {
      //carOUT
      count++;
    }
    //L2
    if (!(PINC & (1 << PC1))) {
      //carOUT
      count++;
    }
    //L3
    if (!(PINC & (1 << PC0))) {
      //carOUT
      count++;
    }
    //L4
    if (!(PINB & (1 << PB5))) {
      //carOUT
      count++;
    }

    //==========IN=============
    //L5
    if (!(PINB & (1 << PB4))) {
      //carIN
      count--;
    }
    //L6
    if (!(PINB & (1 << PB3))) {
      //carIN
      count--;
    }
    //L7
    if (!(PINB & (1 << PB2))) {
      //carIN
      count--;
    }
    //L8
    if (!(PINB & (1 << PB1))) {
      //carIN
      count--;
    }
  }

  //====================================================================================
  /*
    Type 3: [↓↑]   single bidirectional entrance
      L1 - L4 = IN/OUT (L1::L2)(L3::L4)
      L5 - L8 = IN/OUT (L5::L6)(L7::L8)
  */
  else if (type == 3) {
    //L1
    if (!(PINC & (1 << PC2))) {
      //carIN
      count--;
    }
    //L2
    if (!(PINC & (1 << PC1))) {
      //carOUT
      count++;
    }
    //L3
    if (!(PINC & (1 << PC0))) {
      //carIN
      count--;
    }
    //L4
    if (!(PINB & (1 << PB5))) {
      //carOUT
      count++;
    }
    //L5
    if (!(PINB & (1 << PB4))) {
      //carIN
      count--;
    }
    //L6
    if (!(PINB & (1 << PB3))) {
      //carOUT
      count++;
    }
    //L7
    if (!(PINB & (1 << PB2))) {
      //carIN
      count--;
    }
    //L8
    if (!(PINB & (1 << PB1))) {
      //carOUT
      count++;
    }
  }


}//checkloops
