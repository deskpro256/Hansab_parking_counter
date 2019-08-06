/*

   SLAVE DEVICE 7SEGMENT DISPLAY
   PROGRAM BY KARLIS REINIS ULMANIS
   ADDRESS = 35 / 0x23 / #
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
  {1, 1, 1, 0},   // -
  {1, 1, 1, 1}    // BLANK
};

int bcd[3] = {};
int a, b, c = 0;
int digit[3] = {};
char data[3] = {};

char buff [sizeBuff];        // RECEIVING BUFFER
char recMsg [sizeBuff];      // RECEIVED MESSAGE

bool newData = false;           //flag var to see if there is new data on the UART

char STX = '[';       //start bit of the message
char ETX = ']';       //end bit of the message

char myID = '#';    // my address

int i = 0;    //just a counter number for 'for loops'

volatile int count = 0;

//============================[NOP_DELAY]========================
//no-operation delay with a set value
void NOPdelay(unsigned int z) {
  for (unsigned int x = 0; x <= z; x++) {
    NOP;
  }
}

//============================[SETUP]========================

void setup() {

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
  Serial.begin(9600);   //starting UART with 9600 BAUD
}

//============================[RECEIVED_MY_ADDRESS]========================
//checks if the address byte has slaves or floors address
void isMyAddress() {
  //moves all the buff[] to a stored message value while also clearing the buffer
  for (int i = 0; i <= sizeBuff; i++) {
    recMsg[i] = buff[i];
    buff[i] = 0x00;
  }
  data[0] = recMsg[3];
  data[1] = recMsg[4];
  data[2] = recMsg[5];

  count = data[0] + data[1] + data[2];

}

//============================[READ_SERIAL_BUFFER]========================
void readSerial() {
  //reads the serial data,stores data in a 7 byte buffer
  Serial.readBytes(buff, sizeBuff);
  PORTD ^= (1 << PD3);
  isMyAddress();
}

//==============================[LOOP]========================

void loop() {
  // if there is a message coming in, turn on the comm LED, read the message in buffer,then turn off the LED
  if (Serial.available()) {
    readSerial();
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
    //NOPdelay(16000);
  }

}
