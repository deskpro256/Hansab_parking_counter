/* Interface device program for Hansab
  Written by Karlis Reinis Ulmanis
*/

#include <EEPROM.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <SPI.h>
#include <Ethernet.h>

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
#define sizeConfigBuff 19
#define sizeNWConfigBuff 18 //ethernet settings

/////////////////////////
int maxCount = 3996;
int floorMaxCount[4] = {0, 0, 0, 0};
int currentFloorCount[4] = {0, 0, 0, 0};
int tempF1Count = 0;
int tempF2Count = 0;
int tempF3Count = 0;
int tempF4Count = 0;
int activeFloors = 1;
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
int slaveCount = 16;
volatile bool ConfigEnabled = false;
int tries = 0;  // counts retries
byte currentAddress = 0;

char buff [sizeBuff];        // RECEIVING BUFFER
char recMsg [sizeBuff];      // RECEIVED MESSAGE
byte configBuff [sizeConfigBuff];   // RECEIVED CONFIG BUFFER
byte recConfig [sizeConfigBuff];    // RECEIVED CONFIG MESSAGE

//Network settings start
// nw setting buffers
byte NWConfigBuff [sizeNWConfigBuff];    // RECEIVED NW CONFIG CONFIG
byte NWConfig [sizeNWConfigBuff];    // RECEIVED NW CONFIG MESSAGE
// ip address stuff
byte IP[4] = {192, 168, 0, 177}; // IP Address
byte SN[4] = {255, 255, 255, 0}; // Gateway
byte GW[4] = {192, 168, 0, 1};   // Subnet
byte MAC[6] = {0xFA, 0x4C, 0x1D, 0xE4, 0xB5, 0x21};
// FA-4C-1D-E4-B5-21  mac address
byte DHCP; // dhcp
IPAddress ip(IP[0], IP[1], IP[2], IP[3]);
IPAddress gateway(GW[0], GW[1], GW[2], GW[3]);
IPAddress subnet(SN[0], SN[1], SN[2], SN[3]);
IPAddress dns(GW[0], GW[1], GW[2], GW[3]);// same as GW, so use that
IPAddress myIP;
IPAddress mySN;
IPAddress myGW;
EthernetClient client;
EthernetServer server(80); // web server on port 80
// auth stuff
char linebuf[80];
int charcount = 0;
boolean authentificated = false;
//auth : admin:Hansab123  /default user & pass
char auth[] = "YWRtaW46SGFuc2FiMTIz";

// strings to send to terminal
char DHCPSetting[] = "\n\rDHCP: ";
char IPSettings[] = "\n\rIP: ";
char SNSettings[] = "\n\rSN: ";
char GWSettings[] = "\n\rGW: ";
char MACSettings[] = "\n\rMAC: ";
char dhcpOn[] = "On";
char dhcpOff[] = "Off";
char colon = ':';

// Network settings end
//[=====================================]
// HTML Tags
char docTypeHTML[] = "<!DOCTYPE html>";
char htmlStart[] = "<html>";
char htmlEnd[] = "</html>";
char autoScaleMeta[] = "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
char headStart[] = "<head>";
char headEnd[] = "</head>";
char bodyStart[] = "<body>";
char bodyEnd[] = "</body>";
char styleStart[] = "<style>";
char styleEnd[] = "</style>";
char scriptStart[] = "<script>";
char scriptEnd[] = "</script>";
char centerStart[] = "<center>";
char centerEnd[] = "</center>";
char divStart[] = "<div>";
char divEnd[] = "</div>";
char formEnd[] = "</form>";

//HTML TAG END


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
  // uncomment next line for custom PCB's
  //PORTC &=  ~(1 << PC2) | ~(1 << PC3) | ~(1 << PC4); //disable ALL LED'S
  // test Perfboard device
  PORTC &=  ~(1 << PC1) | ~(1 << PC2) | ~(1 << PC3); //disable ALL LED'S
  delay(1000);
  // uncomment next line for custom PCB's
  //PORTC |= (1 << PC2) | (1 << PC3) | (1 << PC4);  //ENABLE ALL LED'S
  // test Perfboard device
  PORTC |= (1 << PC1) | (1 << PC2) | (1 << PC3);  //ENABLE ALL LED'S
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
  DDRC |= 0x0E;
  DDRD |= 0x10;

  PORTB |= 0B00000000;
  PORTC |= 0B00000000;
  PORTD |= 0B00011100;
  /*
    DDRB |= 0x00;
    DDRC |= 0x0C;
    DDRD |= 0xE4;

    PORTB |= 0B00000000;
    PORTC |= 0B00000000;
    PORTD |= 0B00001000;
  */
  //------[ISR SETUP]------
  EICRA = 0B00000100;
  EIMSK = 0B00000010;
  //-----------[WDT]--------
  sei();
  Serial.begin(9600);   //starting UART with 9600 BAUD
  // uncomment next line for custom PCB's
  //PORTC &=  ~(1 << PC2) | ~(1 << PC3) | ~(1 << PC4); //disable ALL LED'S
  // test Perfboard device
  PORTC |=  (1 << PC1) | (1 << PC2) | (1 << PC3); //disable ALL LED'S
  // read the settings saved in eeprom
  readEEPROMSettings();
  // ethernet settings
  EthernetSetup();
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
        //PORTC ^= (1 << PC2);
        PORTC ^= (1 << PC1);
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
  DHCPMaintain();
  handleEthernet();
}
