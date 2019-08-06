//FTS MESSAGE:
//  STX | RXID | SLAVE COUNT | FLOOR COUNT | F1 CNT | F2 CNT | F3 CNT | ETX
//   [    0x00        5             1          100       0        0      ]

void firstTimeSetup() {

  slaveCount = recMsg[2];
  floorCount[0] = recMsg[4];
  floorCount[1] = recMsg[5];
  floorCount[2] = recMsg[6];
  countNumbers();
  configurationMode();
}
