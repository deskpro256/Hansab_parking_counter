//============================[GET_MY_ADDRESS]========================
// reads the DIP switches and translates that to an address for RS485 communication protocol
void getMyID() {
  int adrINT;     //varialble to store slave's address as an int
  int DIP[4];     //array to store the SW1 DIP switch states
  //reading the states of SW1
  for (int i = 0; i <= 3 ; i++) {
    if (digitalRead(ADRLUT[i]) == HIGH) {
      DIP[i] = 1;
    }
    else {
      DIP[i] = 0;
    }
  }
  //takes the values of DIP and adds it up in a 4 bit "byte",then turns it into an integer
  adrINT = (DIP[0] * 8) + (DIP[1] * 4) + (DIP[2] * 2) + (DIP[3] * 1);
  //adrINT to ascii
  myID = adrINT;

  // optional ID for greeting()
  if (myID <= 0x09) {
    id [1] = myID + '0';
  } else if (myID == 0x0A) {
    id [0] = '1';
    id [1] = '0';
  } else if (myID == 0x0B) {
    id [0] = '1';
    id [1] = '1';
  } else if (myID == 0x0C) {
    id [0] = '1';
    id [1] = '2';
  } else if (myID == 0x0D) {
    id [0] = '1';
    id [1] = '3';
  } else if (myID == 0x0E) {
    id [0] = '1';
    id [1] = '4';
  } else if (myID == 0x0F) {
    id [0] = '1';
    id [1] = '5';
  }

}
