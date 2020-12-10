
#include <Ethernet.h>

int switchPin = 22;
int switchVariable;
int dhcpActive;

byte mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip[4] = {192, 168, 2, 187};
byte subnet[4] = {255, 255, 255, 0};
byte dns[4];
byte gateway[4];


void setup() {

  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);

  dnsGateway();

  if (digitalRead(switchPin) == HIGH) {
    switchVariable = 0;
  } else {
    switchVariable = 1;
  }
  switcher(switchVariable);

  Serial.println();
  Serial.println("Switcher exited");
  Serial.println("---------------------------------------");
  Serial.println();
}



void loop() {

  if (dhcpActive == 0) {
    dchpMaintain();
    Serial.println("---------------------------------------");
    Serial.println("Running DHCP Maintain");
    Serial.println("---------------------------------------");
  }
}




void switcher (int switchVariable) {
  switch (switchVariable) {
    case 0:
      Serial.println("---------------------------------------");
      Serial.println("Ethernet initializing with DHCP");
      Ethernet.begin(mac);
      Serial.println("Ethernet successfully initialized with DHCP");
      Serial.print("IP address = ");
      Serial.println(Ethernet.localIP());
      Serial.print("Subnet Mask = ");
      Serial.println(Ethernet.subnetMask());

      dhcpActive = 0;
      delay(1000);
      break;

    case 1:
      Serial.println("---------------------------------------");
      Serial.println("Ethernet initializing with static IP");
      Ethernet.begin(mac, ip, dns, gateway, subnet);
      Serial.println("Ethernet successfully initialized with static IP");
      Serial.print("IP address = ");
      Serial.println(Ethernet.localIP());
      Serial.print("Subnet Mask = ");
      Serial.println(Ethernet.subnetMask());


      dhcpActive = 1;
      delay(1000);
      break;

  }
}


int dchpMaintain () {
  Ethernet.maintain();
  Serial.println("Running DHCP Maintain");
  delay(1000);
  //return(Ethernet.maintain);
}

void dnsGateway () {
  dns[0] = ip[0];
  dns[1] = ip[1];
  dns[2] = ip[2];
  dns[3] = 1;

  gateway[0] = ip[0];
  gateway[1] = ip[1];
  gateway[2] = ip[2];
  gateway[3] = 1;
}