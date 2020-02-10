
//============================[CHECK_LOOPS]========================<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//from ISR to this in order to correctly know the vehicles direction
/*  type 1:  [↓↑]   single bidirectional entrance
    type 2: [↑][↓]  separate directional entrance and exit
    type 3:  [↑]    single entrance
    type 4:  [↓]    single exit
    type 5:  eco    eco(sigle loop action) only in/ only out
*/
void checkLoops() {
  wdt_reset();
  //oldCount = count;
  contactPressed = false;
  PORTC ^= (1 << PC4);
  if (type == 1) {
    // L1, L2
    if (L1_flag == true) {
      //carIN
      count--;
      L1_flag = false;
    }
    else if (L2_flag == true) {
      //carOUT
      count++;
      L2_flag = false;
    }

    // L3, L4
    if (L3_flag == true) {
      //carIN
      count--;
      L3_flag = false;
    }
    else if (L4_flag == true) {
      //carOUT
      count++;
      L4_flag = false;
    }
  }


  else if (type == 2) {
    //L5, L6
    if (L5_flag == true && L6_flag == true) {
      //carOUT
      count++;
      L5_flag = false;
      L6_flag = false;
    }

    //L7, L8
    if (L7_flag == true && L8_flag == true) {
      //carIN
      count--;
      L7_flag = false;
      L8_flag = false;
    }
  }
  // in
  else if (type == 3) {
    //L7, L8
    if (L7_flag == true && L8_flag == true) {
      //carIN
      count--;
      L7_flag = false;
      L8_flag = false;
    }
  }
  // out
  else if (type == 4) {
    //L5, L6
    if (L5_flag == true && L6_flag == true) {
      //carOUT
      count++;
      L5_flag = false;
      L6_flag = false;
    }
  }
  //eco / single loop action
  else if (type == 5) {
    //L5, L6, L7, L8
    if (L5_flag == true) {
      //carOUT
      count++;
      L5_flag = false;
    }
    if (L6_flag == true) {
      //carOUT
      count++;
      L6_flag = false;
    }
    if (L7_flag == true) {
      //carIN
      count--;
      L7_flag = false;
    }
    if (L8_flag == true) {
      //carIN
      count--;
      L8_flag = false;
    }
  }
}
