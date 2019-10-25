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
#define sizeBuff 9

////Slave data array/////
char slaveData[16][4] {};
/////////////////////////
int floorCount[4] = {123, 456, 789, 696};
int totalCount = 0;
int maxCount = 512;
char errorDevices[32] = {}; //devices with errors. ID, ERROR, ID, ERROR ...
char errorCodes[4] = {'0', '1', '2', '3'}; // E0 E1 E2 E3
byte addresses[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
byte floorDevices[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; //floor num according to address
int slaveCount = 15;
volatile bool ConfigEnabled = false;
bool batteryUsed = false;
bool externalPower = false;
int timeout = 1000; // 1 sec
int tries = 0;  // counts retries
byte currentAddress = 0;

byte buff [sizeBuff];        // RECEIVING BUFFER
byte recMsg [sizeBuff];      // RECEIVED MESSAGE

bool newData = false;           // flag var to see if there is new data on the UART
bool replied = false;           // flag to see if slave has replied

byte msg [9] = {'0', '0', '0', '0', '0', '0', '0', '0', '0'};
byte messageType[] = {0x05, 0x06, 0x15}; //ENQ ACK NAK
byte mesType = 0x00; // received message type / ACK NAK
byte STX = 0x5B;       // start bit of the message  0x5B
byte ETX = 0x5D;       // end bit of the message    0x5D

byte CMD = '0';  // by default on startup,there hasn't been any messages, so the command byte is just null
byte CMDLUT[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B}; // a look up table for every command

byte myID = 0x1D;    // my address
byte floorID = '0'; // floor address
byte RXID = '1';   // receivers address

byte ones = 0x00;
byte tens = 0x00;
byte huns = 0x00;
unsigned int data2INT = 0;
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
  Serial.begin(9600, SERIAL_8N2);   //starting UART with 9600 BAUD
  //isFirstCfgTime(); // check to see if this is the first time setting up cfg
}

//==============================[LOOP]========================

void loop() {
  if (ConfigEnabled) {
    //CheckPowerSource();
    if (Serial.available() > 8) {
      PORTC ^= (1 << PC5);
      RS485Receive();
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
      compareFloor();
      sendDisplayCount();
      //CheckPowerSource();
      delay(1000);
  }
}
