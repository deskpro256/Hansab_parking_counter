

#include <avr/io.h>
//number of bytes in buffer and message buff[sizeBuff] & msg[sizeBuff]
#define sizeBuff 11

#define NOP __asm__ __volatile__ ("nop\n\t")  //NO OPERATION
//============================[NOP_DELAY]========================
//no-operation delay with a set value
void NOPdelay(unsigned int z) {
  for (unsigned int x = 0; x <= z; x++) {
    NOP;
  }
}
int state[3][3] {
  {0, 0, 1},
  {0, 1, 0},
  {1, 0, 0}
};

int numbers[10][4] = {
  {0, 0, 0, 0},   // 0
  {0, 0, 0, 1},   // 1
  {0, 0, 1, 0},   // 2
  {0, 0, 1, 1},   // 3
  {0, 1, 0, 0},   // 4
  {0, 1, 0, 1},   // 5
  {0, 1, 1, 0},   // 6
  {0, 1, 1, 1},   // 7
  {1, 0, 0, 0},   // 8
  {1, 0, 0, 1}    // 9
};

int bcd[3] = {};
int a, b, c, i = 0;
int digit[3] = {};
int minCount = 0;
int maxCount = 999;
int count = 123;

//////////////////////////////////
char buff [sizeBuff];        // RECEIVING BUFFER
char recMsg [sizeBuff];      // RECEIVED MESSAGE
char lookForSTX;
bool newData = false;           //flag var to see if there is new data on the UART

byte STX = 0x1B;       // start bit of the message  0x5B

char myID = 0x01;    // my address

int ones;
int tens;
int huns;

//============================[SETUP]========================

void setup() {

  pinMode(3, OUTPUT); //led

  pinMode(4, OUTPUT); //001    COM_3
  pinMode(10, OUTPUT); //010  COM_2
  pinMode(9, OUTPUT); //100   COM_1

  pinMode(5, OUTPUT);    // A 5
  pinMode(6, OUTPUT);    // D 4
  pinMode(7, OUTPUT);    // B 3
  pinMode(8, OUTPUT);    // C 2

  pinMode(2, OUTPUT);      // RE-DE
  digitalWrite(2, LOW);          //turning off the RS485 TX
  digitalWrite(3, LOW);          //turning off the led
  Serial.begin(9600);   //starting UART with 9600 BAUD
}


//==============================[LOOP]========================

void loop() {
  
  if (count <= 0) {
    count = 0;
  }

  if (Serial.available() > 0) {
    lookForSTX = Serial.read();
    if (lookForSTX == STX) {
      PORTD ^= (1 << PD3);
      RS485Receive();
    }
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
