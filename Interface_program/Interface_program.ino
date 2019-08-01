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

String connectedString = "Hansab Interface device connected!";
String versionNum = "Version Number: v1.00";

//number of bytes in buffer and message buff[sizeBuff] & msg[sizeBuff]
#define sizeBuff 8


int floorCount[3] = {0, 0, 0};
int totalCount = 0;
int maxCount = 512;
char errorDevices[32] = {}; //devices with errors. ID, ERROR, ID, ERROR ...
char errorCodes[4] = {'0', '1', '2', '3'}; // E0 E1 E2 E3
char addresses[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
char usedAddresses[15];
char floorDevices[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //floor num according to address
int slaveCount = 0;
bool batteryUsed = false;
bool externalPower = false;
int timeout = 1000; // 1 sec
int tries = 0;  // counts retries
int currentAddress = 0;


char buff [sizeBuff];        // RECEIVING BUFFER
char recMsg [sizeBuff];      // RECEIVED MESSAGE

bool newData = false;           //flag var to see if there is new data on the UART

char STX = '[';       //start bit of the message
char ETX = ']';       //end bit of the message

char CMD = '0';  //by default on startup,there hasn't been any messages, so the command byte is just null

char myID = 0;    // my address
char floorID = '0'; // floor address
char RXID = '0';   // receivers address

/*  since this project is only for small lots, max count = 512 spots
    data is divided in 2 parts dataHigh and dataLow(1 byte each = 256)
    with the 2 bytes together we can get 512
    If the lot has 300 spots(data2INT), dataL = 256 and dataH = 44
*/
char DATAH = 0x00;
char DATAL = 0x00;
unsigned int dataH = 0;
unsigned int dataL = 0;
unsigned int data2INT = 0;

//============================[VARIABLES]========================


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

  Serial.begin(9600);   //starting UART with 9600 BAUD
}

//==============================[LOOP]========================

void loop() {
  for (int i = 0; i < sizeof(slaveCount-1); i++) {
    getErrors(i);
    getChanges(i);
  }
    compareFloor();
    sendDisplayCount();
    powerSource();
}
