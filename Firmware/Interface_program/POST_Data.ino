// here the HTTP POST data gets parsed
/*
  https://web.archive.org/web/20170504071329/https://www.instructables.com/id/Arduino-Ethernet-Shield-Tutorial/
*/

//===================================[GET_POST_DATA]=======================================
// post data looks like:
// zone1=100&zone2=200&zone3=300&zone4=400

void getPOSTData(String str) {
  
  int startIndex = str.indexOf("zone1");
  int endIndex = str.indexOf("zone2");  
  String zone1 = str.substring(startIndex + 2, endIndex - 1);
  char tempRed[4];
  redStr.toCharArray(tempRed, sizeof(tempRed));
  redVal = atoi(tempRed);
  
  startIndex = str.indexOf("zone2");
  endIndex = str.indexOf("zone3");
  String greenStr = str.substring(startIndex + 2, endIndex -1);
  char tempGreen[4];
  greenStr.toCharArray(tempGreen, sizeof(tempGreen));
  greenVal = atoi(tempGreen);
  
  startIndex = str.indexOf("zone3");
  endIndex = str.indexOf("zone4");
  String blueStr = str.substring(startIndex + 2, endIndex -1);
  char tempBlue[4];
  blueStr.toCharArray(tempBlue, sizeof(tempBlue));
  blueVal = atoi(tempBlue);
  
  Serial.println(redStr + " " + greenStr + " " + blueStr);
  
}



//===================================[EXIT]=======================================
void logout() {
  authentificated = false;
}





//===================================[CURRENT DATA]=======================================
void updateCurrentData(unsigned int f1 = 1, unsigned int f2 = 0, unsigned int f3 = 0, unsigned int f4 = 0) {

  currentFloorCount[0] = f1;
  currentFloorCount[1] = f2;
  currentFloorCount[2] = f3;
  currentFloorCount[3] = f4;
}






//===================================[RESTART]=======================================
// RESTART

//SW_Reset();
