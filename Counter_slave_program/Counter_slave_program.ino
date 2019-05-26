/*

   SLAVE DEVICE
   PROGRAM BY KARLIS REINIS ULMANIS

*/
#include <EEPROM.h>
#include <avr/io.h>
#include <avr/interrupt.h>

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
#define sizeBuff 7

int i = 0;    //just a counter number for 'for loops'

int oldCount = 0;
int maxCount = 100;
volatile int count = 98;

// Flags for redundancy detecting vehicles
boolean L1_flag = false;
boolean L2_flag = false;

boolean L3_flag = false;
boolean L4_flag = false;

boolean L5_flag = false;
boolean L6_flag = false;

boolean L7_flag = false;
boolean L8_flag = false;

//////////////////////////////////
char buff [sizeBuff];        // RECEIVING BUFFER
char msg [sizeBuff];         // SENDING MESSAGE
char recMsg [sizeBuff];      // RECEIVED MESSAGE

bool newData = false;           //flag var to see if there is new data on the UART
/*
  char STX = 0x02;       //start bit of the message
  char ETX = 0x03;       //end bit of the message

  char myID = 0x00;    // my address
  char floorID = 0x00; // my floor address
  char recID = 0x0F;   // MASTER address
*/
char STX = '[';       //start bit of the message
char ETX = ']';       //end bit of the message

char myID = 'A';    // my address
char floorID = 'F'; // my floor address
char recID = 'B';   // MASTER address

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


volatile int type = 2;
/*  type 1:  [↓↑]   single bidirectional entrance
    type 2: [↑][↓]  separate directional entrance and exit
    type 3:  [↑]    single entrance
    type 4:  [↓]    single exit
    type 5:  eco    eco(sigle loop action)
*/

//arrays to store values for detecting the direction of a vehicle
//['A','B'] >> carIn
//['B','A'] >> carOut
char AB1[2] = {'0', '0'}; // L1[A] & L2[B]
char AB2[2] = {'0', '0'}; // L3[A] & L4[B]

//char CMD = 0x00;  //by default on startup,there hasn't been any messages, so the command byte is just null
char CMD = '0';  //by default on startup,there hasn't been any messages, so the command byte is just null

int ADRLUT[] = {ADR1, ADR2, ADR3, ADR4};              // a look up table for adress selecting pins

//char CMDLUT[] = {0x11, 0x05, 0x12, 0x13, 0x14, 0x21}; // a look up table for every command
char CMDLUT[] = {'Q', 'W', 'E', 'R', 'T', 'Y'}; // a look up table for every command


//============================[NOP_DELAY]========================
//no-operation delay with a set value
void NOPdelay(unsigned int z) {
  for (unsigned int x = 0; x <= z; x++) {
    NOP;
  }
}


//============================[SETUP]========================

void setup() {
  //------[PIN COFING]-----
  //1 = OUTPUT // 0 = INPUT
  DDRB |= 0x00;
  DDRC |= 0B00111000;
  DDRD |= 0B00000100;

  PORTB |= 0B00111110;
  PORTC |= 0B00000111;
  PORTD |= 0B00000000;

  //------[ISR SETUP]------

  PCMSK0 = 0B000111110;
  PCMSK1 = 0B000000111;

  PCICR |= (1 << PCIE0);
  PCICR |= (1 << PCIE1);
  sei();

  Serial.begin(9600);   //starting UART with xxxx BAUD

  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending

  getMyID();                // reads its own address on power-up
}



//==============================[LOOP]========================

void loop() {

  oldCount = count;

  // if there is a message coming in, turn on the comm LED, read the message in buffer,then turn off the LED
  if (Serial.available()) {
    PORTC ^= (1 << PC5);
    readSerial();
  }
  // if there is new data in the message buffer, check it for the slaves address, if true, then continues with the message translation, else continue on
  if (newData) {
    PORTC ^= (1 << PC5);
    isMyAddress();
  }
  // error state check. If the count is not within the margins set by min/max turn on the error LED, master ticks the error in a log file
  if (count < 1 || count > maxCount) {
    PORTC |= (1 << PC3);
    //+send error report func
  }
  else {
    PORTC &= ~(1 << PC3);
  }
}

