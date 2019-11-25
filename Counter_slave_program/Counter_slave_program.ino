
/* Slave device program for Hansab
   Written by Karlis Reinis Ulmanis
                2019
*/

#include <EEPROM.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <SendOnlySoftwareSerial.h>


#define NOP __asm__ __volatile__ ("nop\n\t")  //NO OPERATION

//IN&OUT
#define L1 A2 //PC2
#define L2 A1 //PC1

#define L3 A0 //PC0
#define L4 13 //PB5

//OUT
#define L5 12 //PB4
#define L6 11 //PB3

//IN
#define L7 10 //PB2
#define L8 9  //PB1

//ADRESS SELECT
#define ADR1 8 //PB0
#define ADR2 7 //PD7
#define ADR3 6 //PD6
#define ADR4 5 //PD5

//number of bytes in buffer and message buff[sizeBuff] & msg[sizeBuff]
#define sizeBuff 8

//PD3 = SWTX
//PD4 = DDE
SendOnlySoftwareSerial Display(PD3); //PD3

int oldCount = 0;
volatile int maxCount = 999;
volatile int count = 666;
int displayCount = 0;
bool countChanged = false;

// Flags for redundancy to detect vehicles
volatile boolean L1_flag = false;
volatile boolean L2_flag = false;

volatile boolean L3_flag = false;
volatile boolean L4_flag = false;

volatile boolean L5_flag = false;
volatile boolean L6_flag = false;

volatile boolean L7_flag = false;
volatile boolean L8_flag = false;

//////////////////////////////////
char buff [sizeBuff];        // RECEIVING BUFFER
char recMsg [sizeBuff];      // RECEIVED MESSAGE

bool newData = false;           //flag var to see if there is new data on the UART

char msg [sizeBuff];
char messageType[] = {0x05, 0x06, 0x15}; //ENQ ACK NAK
char mesType = 0x00; // received message type /ENQ ACK NAK
byte STX = 0x5B;       // start bit of the message  0x5B
byte ETX = 0x5D;       // end bit of the message    0x5D
char lookForSTX;

char myID = 0xFF;    // my address
char floorID = 0xF1; // my floor address
char RXID = 0x1D;   // MASTER address
char id[] = {'0', '0'}; // for greeting show id

char ones = 0x00;
char tens = 0x00;
char huns = 0x00;

unsigned int changedCount = 0;

bool errorState = false;
int errorCount = 0;
char errorCodes[4] = {'0', '1', '2', '3'}; // E0 E1 E2 E3

volatile int type = 5;
/*  type 1:  [↓↑]   single bidirectional entrance
    type 2: [↑][↓]  separate directional entrance and exit
    type 3:  [↑]    single entrance
    type 4:  [↓]    single exit
    type 5:  eco    eco(sigle loop action)
*/

char CMD = 0x00;  //by default on startup,there hasn't been any messages, so the command byte is just null
char plusMinus[] = {0x2B, 0x2D, 0x3D}; // + / - / =
char inOut = 0x00;

int ADRLUT[] = {ADR1, ADR2, ADR3, ADR4};// a look up table for adress selecting pins

char CMDLUT[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B}; // a look up table for every command

char dispNum[] = {0x1B, 0x01, 0x00, 0x06, 0xA1, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};    // no write to eeprom & no reply
//char dispNum[] = {0x1B, 0x01, 0x00, 0x06, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};  //    write to eeprom & reply
char packetSum = 0x00;
char checkSum = 0x00;

const unsigned long debounceTimeMin = 50;
const unsigned long debounceTimeMax = 2000;
volatile bool contactPressed = false;
volatile unsigned long current_millis = 0;
volatile unsigned long last_millis = 0;



//============================[NOP_DELAY]========================
//no-operation delay with a set value
void NOPdelay(unsigned int z) {
  for (unsigned int x = 0; x <= z; x++) {
    NOP;
  }
}

//============================[DEBOUNCE]========================
void debounceISR() {
  current_millis = millis();
  if (current_millis - last_millis >= debounceTimeMin || current_millis - last_millis >= debounceTimeMax) {
    contactPressed = true;
  }
  last_millis = current_millis;
}
//============================[SETUP]========================

void setup() {
  //------[PIN COFING]-----
  //1 = OUTPUT // 0 = INPUT
  DDRB |= 0x00;
  DDRC |= 0B00111000;
  DDRD |= 0B00000100;

  PORTB |= 0B00111111;
  PORTC |= 0B00000111;
  PORTD |= 0B11100000;

  //------[ISR SETUP]------
  PCMSK0 = 0B000111110;
  PCMSK1 = 0B000000111;

  PCICR |= (1 << PCIE0);
  PCICR |= (1 << PCIE1);
  //------------------------
  sei(); //enable interrupts
  Serial.begin(9600);   //starting UART with 9600 BAUD
  Display.begin(9600);
  getMyID();  // reads its own address on power-up
  //isFirstCfgTime(); // check to see if this is the first time setting up cfg
  //drawDisplay(0x00,0x00,0x00);
  oldCount = count;
}

//==============================[LOOP]========================

void loop() {
  // if there is a message coming in, turn on the comm LED, read the message in buffer,then turn off the LED
  if (Serial.available() > 0) {
    lookForSTX = Serial.read();
    if (lookForSTX == STX) {
      PORTD ^= (1 << PD3);
      RS485Receive();
    }
  }
  errorCheck();
  countCheck();
}
