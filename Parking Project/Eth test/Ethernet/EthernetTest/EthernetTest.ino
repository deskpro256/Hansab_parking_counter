
#include <SPI.h>
#include <Ethernet.h>

/*
  Ethernet.begin(mac);
  Ethernet.begin(mac, ip);
  Ethernet.begin(mac, ip, dns);
  Ethernet.begin(mac, ip, dns, gateway);
  Ethernet.begin(mac, ip, dns, gateway, subnet);
*/

//Network stuff
// The IP address will be dependent on your local network:
byte ipAddr[] = {192, 168, 0, 177};
int port = 80;
byte sn[] = {255, 255, 255, 255};
byte gw[] = {192, 168, 0, 1};

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {0x4A, 0xCD, 0x14, 0xAE, 0x30, 0xEA};
IPAddress ip(ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);
IPAddress gateway(gw[0], gw[1], gw[2], gw[3]);
IPAddress subnet(sn[0], sn[1], sn[2], sn[3]);
IPAddress dns(gw[0], gw[1], gw[2], gw[3]);// same as GW, so use that

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup()
{
  //PC0 - ETHRST
  DDRC |= (1 << PC1) | (1 << PC2) | (1 << PC3);
  PORTC &= ~(1 << PC1) | ~(1 << PC2) | ~(1 << PC3);


  Serial.begin(9600);

  // set SPI SS pins on w5100 and SD
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  // start the Ethernet connection and the server:
  Ethernet.init(10);  // PB2
  Ethernet.begin(mac);
  delay(2000);
  server.begin();

  Serial.println("setup finished");
  // print your local IP address:
  Serial.print("My IP address: ");
  Serial.println(ip);
  //Serial.println(ip);
}
void loop()
{
  PORTC ^= (1 << PC1) | (1 << PC2) | (1 << PC3);
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      while (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {

          // Here is where the POST data is.
          while (client.available())
          {
            Serial.write(client.read());
          }
          Serial.println();

          //send standard response header
          sendResponseHeader();

          //sends the HTML
          SendMainPage();
          client.stop();
        }
        else if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    Serial.println("Disconnected");
  }
}
