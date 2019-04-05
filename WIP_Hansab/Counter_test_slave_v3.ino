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

/*============================[MESSAGE_FORMAT]========================

   Because the Arduino's C++ code Serial function has it setup real start/stop bits, parity checks and other necessary UART configurations, we use a simple messaging protocol
   that checks addresses, commands and the data to use with the commands. If the slave receives its address, it then checks everything else in the message, if not, it discards it and waits for its address.

  char msg [] = {
    STX,                // start of text
    recID,              // receiver address
    myID,               // transmitter address
    CMD,                // command
    DATAH,              // dataH
    DATAL,              // dataL
    ETX,                // end of text
  };

*/

unsigned char buff [sizeBuff];        // RECEIVING BUFFER
unsigned char msg [sizeBuff];         // SENDING MESSAGE
unsigned char recMsg [sizeBuff];      // RECEIVED MESSAGE

bool newData = false;           //flag var to see if there is new data on the UART

unsigned char STX = 0x02;       //start bit of the message
unsigned char ETX = 0x03;       //end bit of the message

unsigned char myID = 0x00;    // my address
unsigned char floorID = 0x00; // my floor address
unsigned char recID = 0x00;   // MASTER address

/*  since this project is only for small lots, max count = 512 spots
    data is divided in 2 parts dataHigh and dataLow(1 byte each = 256)
    with the 2 bytes together we can get 512
    If the lot has 300 spots(data2INT), dataL = 256 and dataH = 44
*/
unsigned char DATAH = 0x00;
unsigned char DATAL = 0x00;
unsigned int dataH = 0;
unsigned int dataL = 0;
unsigned int data2INT = 0;


volatile int type = 0;
/*  type 1:  [↓↑]   single bidirectional entrance
    type 2: [↑][↓]  separate directional entrance and exit
    type 3:  [↑]    single entrance
    type 4:  [↓]    single exit
    type 5:  eco    eco(sigle loop action)
*/

//arrays to store values for detecting the direction of a vehicle
unsigned char AB1[2]; // L1[A] & L2[B]
unsigned char AB2[2]; // L3[A] & L4[B]

unsigned char CMD = 0x00;  //by default on startup,there hasn't been any messages, so the command byte is just null
/*what each command stands for
   set -> cmd to set the count number
   ask -> enquiry of the current state
   fts -> first time setup configuration
   cfg -> cmd for change configuraton
   dis -> cmd to display a number on the screen
   err -> cmd to set error flag on
      ASCII CHAR| DC1  ENQ   DC2    DC3   DC4   !
             CMD| set  ask   fts    cfg   dis  err */
byte CMDLUT[] = {0x11, 0x05, 0x12, 0x13, 0x14, 0x21}; // a look up table for every command
int ADRLUT[] = {ADR1, ADR2, ADR3, ADR4};              // a look up table for adress selecting pins

int i = 0;    //just a counter number for 'for loops'
int oldCount = 0;
int maxCount = 123;

volatile int count = 10;

//============================[RS485_SEND]========================

void RS485Send(byte CMD, byte DATAH, byte DATAL) {

  char msg [] = {
    STX,                // start of text
    recID,              // receiver address
    myID,               // transmitter address
    CMD,                // command
    DATAH,              // dataH
    DATAL,              // dataL
    ETX,                // end of text
  };

  NOPdelay(1000);           // give the master a moment to prepare to receive
  PORTD |= (1 << PD2);      // (RE_DE, HIGH) enable sending
  Serial.print(msg);
  NOPdelay(1000);
  PORTD &= ~(1 << PD2);     // (RE_DE, LOW) disable sending

}

//============================[NOP_DELAY]========================
//no-operation delay with a set value
void NOPdelay(unsigned int z) {
  for (unsigned int x = 0; x <= z; x++) {
    NOP;
  }
}

//============================[SETUP]========================

void setup() {
  Serial.begin(250000);   //starting UART with 250000 BAUD
  /*
    //PORT B
    DDRB |= 0B00000000;;

    //PORT C
    DDRC |= 0B00111000;;

    //PORT D
    DDRD |= 0B00000000;

    PORTD |= 0B00010110;

    PORTC &= ~(1 << PC3);
    /////////

  */

  //LEDS
  pinMode(2, OUTPUT);      // RE-DE
  pinMode(A3, OUTPUT);     // ERROR LED
  pinMode(A4, OUTPUT);     // LOOP ACTIVITY LED
  pinMode(A5, OUTPUT);     // COMM LED

  //TYPE 1
  pinMode(A0, INPUT_PULLUP);     // SENS IN&OUT
  pinMode(A1, INPUT_PULLUP);     // SENS IN&OUT
  pinMode(A2, INPUT_PULLUP);     // SENS IN&OUT
  pinMode(13, INPUT_PULLUP);     // SENS IN&OUT

  //TYPE 2
  //TYPE 4
  pinMode(5, INPUT_PULLUP);      // SENS OUT
  pinMode(6, INPUT_PULLUP);      // SENS OUT

  //TYPE 3
  pinMode(7, INPUT_PULLUP);      // SENS IN
  pinMode(8, INPUT_PULLUP);      // SENS IN

  //ADDRESS BITS
  pinMode(9, INPUT_PULLUP);      // ADR IN 1
  pinMode(10, INPUT_PULLUP);     // ADR IN 2
  pinMode(11, INPUT_PULLUP);     // ADR IN 3
  pinMode(12, INPUT_PULLUP);     // ADR IN 4

  digitalWrite(2, LOW);          //turning off the RS485 TX

  getMyAddress();                // reads its own address on power-up

}


//============================[GET_MY_ADDRESS]========================
// reads the DIP switches and translates that to an address for RS485 communication protocol
void getMyAddress() {
  int adrINT;     //varialble to store slave's address as an int
  int DIP[4];     //array to store the SW1 DIP switch states
  //reading the states of SW1
  for (i = 3; i >= 0 ; i--) {
    digitalRead(ADRLUT[i]);
    if (ADRLUT[i] == HIGH) {
      DIP[i] = 1;
    }
    else {
      DIP[i] = 0;
    }

  }
  //takes the values of DIP and adds it up in a 4 bit "byte",then turns it into an integer
  adrINT = (DIP[0] * 8) + (DIP[1] * 4) + (DIP[2] * 2) + (DIP[3] * 1);
  //adrINT to HEX
  myID = adrINT - '0';
}

//==================================[SET]========================
void setCount(int val) {
  count = val;
}

//============================[CONFIG]========================
void cfgCMD(int val) {
  type = val;
  EEPROM[0] = type;
}


//============================[GET_DATA_VAL]========================
// translates the received byte data to an integer to later use for displaying the number on a screen
void getData() {

  DATAH = recMsg[4];
  DATAL = recMsg[5];

  dataH = DATAH;
  dataL = DATAL;

  data2INT = dataH + dataL;
  getCMD();
}

//============================[GET_CMD_NAME]========================
// gets the command byte from the message and
void getCMD() {
  //set  ask   fts    cfg   dis  err
  if (CMD == CMDLUT[0]) { // set num on display

  }

  if (CMD == CMDLUT[1]) { //ask

  }

  if (CMD == CMDLUT[2]) { //fts

  }

  if (CMD == CMDLUT[3]) { //cfg

  }

  if (CMD == CMDLUT[4]) { //dis

  }

  if (CMD == CMDLUT[5]) { //err

  }

}

//============================[RECEIVED_MY_ADDRESS]========================
//checks if the address byte has slaves or floors address
void isMyAddress() {
  if (recMsg[1] == myID || recMsg[1] == floorID) {
    //moves all the buff[] to a stored message value while also clearing the buffer
    for (int i = 0; i <= sizeBuff; i++) {
      recMsg[i] = buff[i];
      buff[i] = 0x00;
    }
  }
}

//============================[READ_SERIAL_BUFFER]========================
void readSerial() {
  //reads the serial data,stores data in a 7 byte buffer
  Serial.readBytes(buff, sizeBuff);
  //checks the buffer for the msg stx and etx bytes, if the buffer is still clear, there is no new data, return, if there is new data, continue on reading the message
  if (buff[0] == STX && buff[sizeBuff - 1] == ETX) {
    newData = true;
    return;
  }
  else {
    newData = false;
    return;
  }
}


//AB1[2]; // L1[A] & L2[B]
//AB2[2]; // L3[A] & L4[B]
//============================[CHECK_LOOPS]========================<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//from ISR to this in order to correctly know the vehicles direction
void checkLoops() {

  if (type == 1) {
    // L1, L2, L3, L4

  }

  if (type == 2) {
    //L5-L8

  }

  if (type == 3) {
    //L7, L8, L11, L12

  }

  if (type == 4) {
    //L5, L6, L9 L10

  }

}

//==============================[LOOP]========================

void loop() {

  oldCount = count;

  // if there is a message coming in, turn on the comm LED, read the message in buffer,then turn off the LED
  if (Serial.available()) {
    PORTC |= (1 << PC5);
    readSerial();
    PORTC &= ~(1 << PC5);
  }
  // if there is new data in the message buffer, check it for the slaves address, if true, then continues with the message translation, else continue on
  if (newData) {
    isMyAddress();
  }
  checkLoops();
  // error state check. If the count is not within the margins set by min/max turn on the error LED, master ticks the error in a log file
  if (count < 1 || count > maxCount) {
    PORTC |= (1 << PC3);
    //+send error report func
  }
  else {
    PORTC &= ~(1 << PC3);
  }
}

//============================[DRAW_DISPLAY]========================
// When the master sends a message to the entire floor's slaves, the number to be dispayed gets sent to the display through the RS232 port
//RS232 DISPLAY DRIVER
// needs the "meandr" protocol from Hansab guys

void drawDisplay(int PLACEHOLDER) {
  //stuff here
}
