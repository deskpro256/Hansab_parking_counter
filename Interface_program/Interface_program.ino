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

//number of bytes in buffer and message buff[sizeBuff] & msg[sizeBuff]
#define sizeBuff 8

////Slave data array/////
//char slaveData[16][4] {}; //GOES IN EEPROM
/////////////////////////
int floorCount[4] = {123, 456, 789, 696};
int activeFloors = 1;
char floorNaddresses[4] = {0xF1, 0xF2, 0xF3, 0xF4};
int tempF1Count = 0;
int tempF2Count = 0;
int tempF3Count = 0;
int tempF4Count = 0;
bool countChanged = false;
int totalCount = 0;
int maxCount = 512;
char errorDevices[32] = {}; //devices with errors. ID, ERROR, ID, ERROR ...
char errorCodes[4] = {'0', '1', '2', '3'}; // E0 E1 E2 E3
byte addresses[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
byte floorDevices[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; //floor num according to address
int slaveCount = 15;
volatile bool ConfigEnabled = false;
int tries = 0;  // counts retries
byte currentAddress = 0;

byte buff [sizeBuff];        // RECEIVING BUFFER
byte recMsg [sizeBuff];      // RECEIVED MESSAGE

bool newData = false;           // flag var to see if there is new data on the UART
bool replied = false;           // flag to see if slave has replied

byte msg [sizeBuff];
byte messageType[] = {0x05, 0x06, 0x15}; //ENQ ACK NAK
byte mesType = 0x00; // received message type / ACK NAK
byte STX = 0x5B;       // start bit of the message  0x5B
byte ETX = 0x5D;       // end bit of the message    0x5D
char lookForSTX;

byte CMD = '0';  // by default on startup,there hasn't been any messages, so the command byte is just null
byte CMDLUT[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B}; // a look up table for every command

byte myID = 0x1D;    // my address
byte PCID = 0x1C;    // my address
byte floorID = 0x00; // floor address
byte RXID = 0x00;   // receivers address

byte ones = 0x00;
byte tens = 0x00;
byte huns = 0x00;
int foo = 0;//just a general slave counter iterator var


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
  //Serial.begin(9600);   //starting UART with 115200 BAUD
  Serial.begin(9600);   //starting UART with 9600 BAUD
  //isFirstCfgTime(); // check to see if this is the first time setting up cfg
  tempF1Count = floorCount[0];
  tempF2Count = floorCount[1];
  tempF3Count = floorCount[2];
  tempF4Count = floorCount[3];
}

//==============================[LOOP]========================

void loop() {
  if (ConfigEnabled) {
    if (Serial.available() > 0) {
      lookForSTX = Serial.read();
      if (lookForSTX == STX) {
        PORTD ^= (1 << PD3);
        RS485Receive();
      }
    }
  }
  else {
    foo = 0;
    slaveCount = 1;
    while (foo <= slaveCount) {
      currentAddress = addresses[foo];
      delay(100);
      getErrors(currentAddress);
      delay(100);
      getChanges(currentAddress);
      delay(100);
      foo++;
    }
    countNumbers();
    if (countChanged) {
      sendDisplayCount();
      countChanged = false;
    }

    //CheckPowerSource();
    delay(1000);
  }
}
