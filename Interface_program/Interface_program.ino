/* Interface device program for Hansab
    Written by Karlis Reinis Ulmanis
                2019
    type 1:  [↓↑]   single bidirectional entrance
    type 2: [↑][↓]  separate directional entrance and exit
    type 3:  [↑]    single entrance
    type 4:  [↓]    single exit
    type 5:  eco    eco(sigle loop action)
*/

#include <EEPROM.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define NOP __asm__ __volatile__ ("nop\n\t")  //NO OPERATION

//============================[NOP_DELAY]========================
//no-operation delay with a set value
void NOPdelay(unsigned int z) {
  for (unsigned int x = 0; x <= z; x++) {
    NOP;
  }
}

//============================[VARIABLES]========================

char connectedString[] = "Hansab Interface device connected!";
char versionNum[] = "Version Number: v1.00";

//number of bytes in buffer and message buff[sizeBuff] & msg[sizeBuff]
#define sizeBuff 9

////Slave data array/////
char slaveData[16][4] {};
/////////////////////////
int floorCount[3] = {123, 456, 789};
int totalCount = 0;
int maxCount = 512;
char errorDevices[32] = {}; //devices with errors. ID, ERROR, ID, ERROR ...
char errorCodes[4] = {'0', '1', '2', '3'}; // E0 E1 E2 E3
char addresses[15] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
char floorDevices[15] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; //floor num according to address
int slaveCount = 15;
bool batteryUsed = false;
bool externalPower = false;
int timeout = 1000; // 1 sec
int tries = 0;  // counts retries
char currentAddress = 0;

char buff [sizeBuff];        // RECEIVING BUFFER
char recMsg [sizeBuff];      // RECEIVED MESSAGE

bool newData = false;           //flag var to see if there is new data on the UART
char msg [9];
char messageType[] = {0x05, 0x06, 0x21}; //ENQ ACK NAK
char mesType = 0x00; // received message type / ACK NAK
char STX = 0x02;       // start bit of the message  0x5B
char ETX = 0x03;       // end bit of the message    0x5D

char CMD = '0';  // by default on startup,there hasn't been any messages, so the command byte is just null
char CMDLUT[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08}; // a look up table for every command

char myID = 0x00;    // my address
char floorID = '0'; // floor address
char RXID = '0';   // receivers address

char ones = 0x00;
char tens = 0x00;
char huns = 0x00;
unsigned int data2INT = 0;

int foo = 0;
//============================[SETUP]========================

void setup() {
  //------[PIN COFING]-----
  //1 = OUTPUT // 0 = INPUT
  DDRB |= 0x00;
  DDRC |= 0x0C;
  DDRD |= 0xE4;

  PORTB |= 0B00000000;
  PORTC |= 0B00000000;
  PORTD |= 0B00001000;

  //------[ISR SETUP]------
  EICRA = 0B00000100;
  EIMSK = 0B00000010;
  sei();
  Serial.begin(115200);   //starting UART with 115200 BAUD
  greeting();
  //countNumbers();
  //isFirstCfgTime(); // check to see if this is the first time setting up cfg
}

//==============================[LOOP]========================

void loop() {
  foo = 1;
  delay(10);
  while (foo <= slaveCount) {
    currentAddress = addresses[foo];
    testSend(currentAddress);
    delay(10);
    RS485Send(currentAddress, messageType[0], CMDLUT[1], '1', '2', '3');
    /*
      getErrors(currentAddress);
      delay(10);
      getChanges(currentAddress);
    */
    foo++;
  }
  delay(10);
  compareFloor();
  delay(10);
  sendDisplayCount();
  delay(10);
  sendDisplayCountToUSB();
  delay(10);
  powerSource();
  delay(1000);
}
