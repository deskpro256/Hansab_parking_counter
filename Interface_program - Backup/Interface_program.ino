/* Interface device program for Hansab
  Written by Karlis Reinis Ulmanis

  2019
  type 1 :  [↓↑]   single bidirectional entrance
  type 2 : [↑][↓]  separate directional entrance and exit
  type 3 :  [↑]    single entrance
  type 4 :  [↓]    single exit
  type 5 :  eco    eco(sigle loop action)
*/

#include <EEPROM.h>
#include <avr/io.h>
#include <avr/wdt.h>
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
#define sizeConfigBuff 18 // 30 w/ ethernet settings

////Slave data array/////
//char slaveData[16][4] {}; //GOES IN EEPROM
/////////////////////////
int maxCount = 3996;
int floorMaxCount[4] = {0, 0, 0, 0};
int currentFloorCount[4] = {0, 0, 0, 0};
int tempF1Count = 0;
int tempF2Count = 0;
int tempF3Count = 0;
int tempF4Count = 0;
int activeFloors = 4;
char floorNaddresses[4] = {0xF1, 0xF2, 0xF3, 0xF4};
bool countChanged = false;
bool errorState = false;

bool countF1Changed = false;
bool countF2Changed = false;
bool countF3Changed = false;
bool countF4Changed = false;

bool isF1Negative = false;
bool isF2Negative = false;
bool isF3Negative = false;
bool isF4Negative = false;

//char errorDevices[32] = {}; //devices with errors. ID, ERROR, ID, ERROR ...
char errorDevices[32] = {0x00, 0x30, 0x01, 0x30, 0x02, 0x30, 0x03, 0x30,
                         0x04, 0x30, 0x05, 0x30, 0x06, 0x30, 0x07, 0x30,
                         0x08, 0x30, 0x09, 0x30, 0x0A, 0x30, 0x0B, 0x30,
                         0x0C, 0x30, 0x0D, 0x30, 0x0E, 0x30, 0x0F, 0x30
                        };
//devices with errors. ID, ERROR, ID, ERROR ...
char errorCodes[4] = {'0', '1', '2', '3'}; // E0 E1 E2 E3
byte addresses[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
int slaveCount = 15;
volatile bool ConfigEnabled = false;
int tries = 0;  // counts retries
byte currentAddress = 0;

char buff [sizeBuff];        // RECEIVING BUFFER
char recMsg [sizeBuff];      // RECEIVED MESSAGE
byte configBuff [sizeConfigBuff];   // RECEIVED MESSAGE
byte recConfig [sizeConfigBuff];    // RECEIVED CONFIG MESSAGE

bool newData = false;           // flag var to see if there is new data on the UART
bool replied = false;           // flag to see if slave has replied

byte msg [sizeBuff];
byte messageType[] = {0x05, 0x06, 0x15}; //ENQ ACK NAK
byte mesType = 0x00; // received message type / ACK NAK
byte STX = 0x5B;       // start bit of the message  0x5B
byte ETX = 0x5D;       // end bit of the message    0x5D
char lookForSTX = 0x00;

byte CMD = 0x00;  // by default on startup,there hasn't been any messages, so the command byte is just null
byte CMDLUT[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B}; // a look up table for every command

byte myID = 0x1D;    // my address
byte PCID = 0x1C;    // my address
byte floorID = 0x00; // floor address
byte RXID = 0x00;   // receivers address

byte ones = 0x00;
byte tens = 0x00;
byte huns = 0x00;
int foo = 0;//just a general slave counter iterator var

//watchdog stuff

//============================[SOFTWARE_RESET]========================
void SW_Reset() {
  PORTD &=  ~(1 << PD5) | ~(1 << PD6) | ~(1 << PD7); //disable ALL LED'S
  delay(1000);
  PORTD |= (1 << PD5) | (1 << PD6) | (1 << PD7);  //ENABLE ALL LED'S
  wdt_enable(WDTO_2S);
  while (1) {} //wait for it to reset
}

//============================[SETUP]========================

void setup() {
  /* Clear WDRF in MCUSR */
  MCUSR &= ~(1 << WDRF);
  /* Write logical one to WDCE and WDE */
  /* Keep old prescaler setting to prevent unintentional time-out
  */
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  wdt_disable();
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
  //-----------[WDT]--------
  sei();
  Serial.begin(9600);   //starting UART with 9600 BAUD

  PORTD &=  ~(1 << PD5) | ~(1 << PD6) | ~(1 << PD7); //disable ALL LED'S
  readEEPROMSettings();
  // update the displays with current count
  for (int i = 0; i <= 3; i++) {
  sendDisplayCount(i);
  }
}

//==============================[LOOP]========================

void loop() {
  wdt_reset();
  if (ConfigEnabled) {
    wdt_reset();
    if (Serial.available() > 0) {
      lookForSTX = Serial.read();
      if (lookForSTX == STX) {
        PORTD ^= (1 << PD5);
        RS485Receive();
      }
    }
  }
  else {
    wdt_reset();
    foo = 0;
    while (foo <= slaveCount - 1) {
      wdt_reset();
      //getErrors(foo);
      getChanges(foo);
      foo++;
    }
    checkForCountError();
    UpdateCount();
  }
}
