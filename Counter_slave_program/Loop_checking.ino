
//AB1[2]; // L1[A] & L2[B]
//AB2[2]; // L3[A] & L4[B]
//============================[CHECK_LOOPS]========================<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//from ISR to this in order to correctly know the vehicles direction
/*  type 1:  [↓↑]   single bidirectional entrance
    type 2: [↑][↓]  separate directional entrance and exit
    type 3:  [↑]    single entrance
    type 4:  [↓]    single exit
    type 5:  eco    eco(sigle loop action)
*/
void checkLoops() {
    PORTC ^= (1 << PC4);  
  if (type == 1) {
    // L1, L2
    if (AB1 == "AB") {
      //carIN
      count --;
      L1_flag = false;
      L2_flag = false;
    }
    else if (AB1 == "BA") {
      //carOUT
      count ++;
      L1_flag = false;
      L2_flag = false;
    }
    if (AB1[0] != 'B') {
      AB1[0] = 'A';
    }
    else {
      AB1[1] = 'A';
    }

    // L3, L4
    if (AB2 == "AB") {
      //carIN
      count --;
      L3_flag = false;
      L4_flag = false;
    }
    else if (AB2 == "BA") {
      //carOUT
      count ++;
      L3_flag = false;
      L4_flag = false;
    }
    if (AB2[0] != 'B') {
      AB2[0] = 'A';
    }
    else {
      AB2[1] = 'A';
    }
  }

  if (type == 2) {
    //L5, L6
    if (L5_flag == true && L6_flag == true) {
      //carOUT
      count ++;
      L5_flag = false;
      L6_flag = false;
    }

    //L7, L8
    if (L7_flag == true && L8_flag == true) {
      //carIN
      count --;
      L7_flag = false;
      L8_flag = false;
    }
  }

  if (type == 3) {
    //L7, L8
    if (L7_flag == true && L8_flag == true) {
      //carIN
      count --;
      L7_flag = false;
      L8_flag = false;
    }
  }

  if (type == 4) {
    //L5, L6
    if (L5_flag == true && L6_flag == true) {
      //carOUT
      count ++;
      L5_flag = false;
      L6_flag = false;
    }
  }
  if (type == 5) {
    //L5, L6, L7, L8
    if (L5_flag == true) {
      //carOUT
      count ++;
      L5_flag = false;
    }
    if (L6_flag == true) {
      //carOUT
      count ++;
      L6_flag = false;
    }
    if (L7_flag == true) {
      //carOUT
      count --;
      L7_flag = false;
    }
    if (L8_flag == true) {
      //carOUT
      count --;
      L8_flag = false;
    }
  }
    PORTC &= ~(1 << PC4);
  sei(); //enable interrupts
}
