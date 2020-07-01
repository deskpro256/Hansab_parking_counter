// here the HTTP POST data gets parsed
/*
  https://web.archive.org/web/20170504071329/https://www.instructables.com/id/Arduino-Ethernet-Shield-Tutorial/
*/

//===================================[GET_POST_DATA]=======================================
// post data looks like:
// zone1=100&zone2=200&zone3=300&zone4=400

void getPOSTData(String str) {
  /*
  int Zone1Val = 0;
  int Zone2Val = 0;
  int Zone3Val = 0;
  int Zone4Val = 0;
  //see what the POST data contains and then send off to it's function

  if (str.substring(0) == "exit") {
    authentificated = false;
  }
  else if (str.substring(0) == "restart") {
    SW_Reset();
  }
  else if (str.startsWith("zone1")) {
    if (activeFloors == 0x01) {
      // zone1=100
      Zone1Val = 100;
    }
    else if (activeFloors == 0x02) {
      // zone1=100&zone2=200
      Zone1Val = 100;
      Zone2Val = 200;
    }
    else if (activeFloors == 0x03) {
      // zone1=100&zone2=200&zone3=300
      Zone1Val = 100;
      Zone2Val = 200;
      Zone3Val = 300;
    }
    else if (activeFloors == 0x04) {
      // zone1=100&zone2=200&zone3=300&zone4=400
      Zone1Val = 100;
      Zone2Val = 200;
      Zone3Val = 300;
      Zone4Val = 400;
    }

    PORTD |= (1 << PD4);      // (RE_DE, HIGH) enable sending
    //PORTC |= (1 << PC2);      // Enable COM Led
    //perf test device
    PORTC |= (1 << PC1);      // Enable COM Led
    delay(50);
    Serial.println(str);
    delay(50);
    PORTD &= ~(1 << PD4);     // (RE_DE, LOW) disable sending
    //PORTC &= ~(1 << PC2);     // Disable COM Led
    //perf test device
    PORTC &= ~(1 << PC1);     // Disable COM Led

    currentFloorCount[0] = Zone1Val;
    currentFloorCount[1] = Zone2Val;
    currentFloorCount[2] = Zone3Val;
    currentFloorCount[3] = Zone4Val;
  }
  */
}
