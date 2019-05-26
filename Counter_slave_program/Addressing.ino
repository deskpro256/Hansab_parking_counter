

//============================[GET_MY_ADDRESS]========================
// reads the DIP switches and translates that to an address for RS485 communication protocol
void getMyID() {
  int adrINT;     //varialble to store slave's address as an int
  int DIP[4];     //array to store the SW1 DIP switch states
  //reading the states of SW1
  for (i = 3; i >= 0 ; i--) {
    digitalRead(ADRLUT[i]);
    if (ADRLUT[i] == HIGH) {
      DIP[i] = 1;
    }
    else {
      DIP[i] = 0;
    }

  }
  //takes the values of DIP and adds it up in a 4 bit "byte",then turns it into an integer
  adrINT = (DIP[0] * 8) + (DIP[1] * 4) + (DIP[2] * 2) + (DIP[3] * 1);
  //adrINT to HEX
  myID = adrINT - '0';
}
