/*

   SLAVE DEVICE 7SEGMENT DISPLAY
   PROGRAM BY KARLIS REINIS ULMANIS
   ADRESS = 16; 0x0F
*/
#include <EEPROM.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define NOP __asm__ __volatile__ ("nop\n\t")  //NO OPERATION



//number of bytes in buffer and message buff[sizeBuff] & msg[sizeBuff]
#define sizeBuff 7


// 7 SEGMENT SETUP
int state[3][3] {
  {0, 0, 1},
  {0, 1, 0},
  {1, 0, 0}
};

int numbers[16][4] = {
  {0, 0, 0, 0},   // 0
  {0, 0, 0, 1},   // 1
  {0, 0, 1, 0},   // 2
  {0, 0, 1, 1},   // 3
  {0, 1, 0, 0},   // 4
  {0, 1, 0, 1},   // 5
  {0, 1, 1, 0},   // 6
  {0, 1, 1, 1},   // 7
  {1, 0, 0, 0},   // 8
  {1, 0, 0, 1},   // 9
  {1, 1, 0, 1},   // L
  {1, 1, 1, 0},   // H
  {1, 1, 1, 1},   // P
  {1, 1, 0, 1},   // A
  {1, 1, 1, 0},    // -
  {1, 1, 1, 1}    // BLANK
};

int bcd[3] = {};
int a, b, c = 0;
int digit[3] = {};


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

char buff [sizeBuff];        // RECEIVING BUFFER
char msg [sizeBuff];         // SENDING MESSAGE
char recMsg [sizeBuff];      // RECEIVED MESSAGE

bool newData = false;           //flag var to see if there is new data on the UART

char STX = '[';       //start bit of the message
char ETX = ']';       //end bit of the message

char myID = 'B';    // my address
char floorID = 'F'; // my floor address
char recID = 'A';   // MASTER address

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


volatile int type = 0;
/*  type 1:  [↓↑]   single bidirectional entrance
    type 2: [↑][↓]  separate directional entrance and exit
    type 3:  [↑]    single entrance
    type 4:  [↓]    single exit
    type 5:  eco    eco(sigle loop action)
*/

//arrays to store values for detecting the direction of a vehicle
char AB1[2]; // L1[A] & L2[B]
char AB2[2]; // L3[A] & L4[B]

//char CMD = 0x00;  //by default on startup,there hasn't been any messages, so the command byte is just null
char CMD = '0';  //by default on startup,there hasn't been any messages, so the command byte is just null
/*what each command stands for
   set -> cmd to set the count number
   ask -> enquiry of the current state
   fts -> first time setup configuration
   cfg -> cmd for change configuraton
   dis -> cmd to display a number on the screen
   err -> cmd to set error flag on
      ASCII CHAR| DC1  ENQ   DC2    DC3   DC4   !
             CMD| set  ask   fts    cfg   dis  err */
//char CMDLUT[] = {0x11, 0x05, 0x12, 0x13, 0x14, 0x21}; // a look up table for every command
char CMDLUT[] = {'Q', 'W', 'E', 'R', 'T', 'Y'}; // a look up table for every command


//int ADRLUT[] = {ADR1, ADR2, ADR3, ADR4};              // a look up table for adress selecting pins

int i = 0;    //just a counter number for 'for loops'
int oldCount = 0;
int maxCount = 123;

volatile int count = 123;

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
  Serial.begin(9600);   //starting UART with 115200 BAUD

  pinMode(3, OUTPUT); //led

  pinMode(4, OUTPUT); //001		COM_3
  pinMode(10, OUTPUT); //010	COM_2
  pinMode(9, OUTPUT); //100		COM_1

  pinMode(5, OUTPUT);    // A 5
  pinMode(6, OUTPUT);    // D 4
  pinMode(7, OUTPUT);    // B 3
  pinMode(8, OUTPUT);    // C 2

  pinMode(2, OUTPUT);      // RE-DE
  digitalWrite(2, LOW);          //turning off the RS485 TX
  digitalWrite(3, LOW);          //turning off the led

  getMyID();                // reads its own address on power-up

}


//============================[GET_MY_ADDRESS]========================
// reads the DIP switches and translates that to an address for RS485 communication protocol
void getMyID() {
  myID = 0x0F;
}

//============================[GET_CMD_NAME]========================
// gets the command byte from the message and
void getCMD() {
  
  if (CMD == CMDLUT[0]) {
    // set count
  }

  if (CMD == CMDLUT[1]) { //ask
    //reply with count
  }

  if (CMD == CMDLUT[2]) { //fts
    //gets type data
  }

  if (CMD == CMDLUT[3]) { //cfg
    //any changes after  fts
  }

  if (CMD == CMDLUT[4]) { //dis
    //set num on display
  }

  if (CMD == CMDLUT[5]) { //err
    //error state enable
    count = data2INT;
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
    CMD = recMsg[3];
    DATAH = recMsg[4];
    DATAL = recMsg[5];

    dataH = DATAH;
    dataL = DATAL;

    data2INT = dataH + dataL;
    getCMD();
  }
}

//============================[READ_SERIAL_BUFFER]========================
void readSerial() {
  //reads the serial data,stores data in a 7 byte buffer
  Serial.readBytes(buff, sizeBuff);
  //checks the buffer for the msg stx and etx bytes, if the buffer is still clear, there is no new data, return, if there is new data, continue on reading the message
  if (buff[0] == STX && buff[sizeBuff - 1] == ETX) {
    count = count - 1;
    newData = true;
    return;
  }
  else {
    count = count + 1;
    newData = false;
    return;
  }
}

//==============================[LOOP]========================

void loop() {
  // if there is a message coming in, turn on the comm LED, read the message in buffer,then turn off the LED
  if (Serial.available()) {
    PORTD |= (1 << PD3);
    readSerial();
    PORTD &= ~(1 << PD3);
  }
  // if there is new data in the message buffer, check it for the slaves address, if true, then continues with the message translation, else continue on
  if (newData) {
    isMyAddress();
  }
  i = 0;
  while (i <= 2) {

    a = count / 100;        //simti
    b = (count % 100) / 10; //desmiti
    c = count % 10;         //vieni

    digit[0] = a;
    digit[1] = b;
    digit[2] = c;

    bcd[0] = numbers[digit[i]][0];
    bcd[1] = numbers[digit[i]][1];
    bcd[2] = numbers[digit[i]][2];
    bcd[3] = numbers[digit[i]][3];

    digitalWrite(4, state[i][2]);
    digitalWrite(10, state[i][1]);
    digitalWrite(9, state[i][0]);

    digitalWrite(6 , bcd[0]);
    digitalWrite(8 , bcd[1]);
    digitalWrite(7 , bcd[2]);
    digitalWrite(5 , bcd[3]);
    i++;
    NOPdelay(16000);
  }

}
