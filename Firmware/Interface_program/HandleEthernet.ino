
//=================[CHECK ETH LINK STATUS]=======================

void checkLinkStatus() {
  PORTD |= (1 << PD4);      // (RE_DE, HIGH) enable sending
  //PORTC |= (1 << PC2);      // Enable COM Led
  //perf test device
  PORTC |= (1 << PC1);      // Enable COM Led
  delay(50);
  if (Ethernet.linkStatus() == LinkON) {
    Serial.println(F("\n\rLink status: On"));
  }
  else if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println(F("\n\rLink status: Off"));
  }
  delay(100);
  PORTD &= ~(1 << PD4);     // (RE_DE, LOW) disable sending
  //PORTC &= ~(1 << PC2);     // Disable COM Led
  //perf test device
  PORTC &= ~(1 << PC1);     // Disable COM Led
}


//=================[DHCP MAINTAIN]=======================
void DHCPMaintain() {
  // if DHCP is on, need to maintain the connection
  if (DHCP == 0x01) {
    // send the connection status to terminal

    PORTD |= (1 << PD4);      // (RE_DE, HIGH) enable sending
    //PORTC |= (1 << PC2);      // Enable COM Led
    //perf test device
    PORTC |= (1 << PC1);      // Enable COM Led
    delay(50);

    switch (Ethernet.maintain()) {
      case 0:
        //Serial.println(F("\n\rDHCP: Nothing happened"));
        break;
      case 1:
        Serial.println(F("\n\rDHCP: Renew failed"));
        break;
      case 2:
        Serial.println(F("\n\rDHCP: Renew success"));
        break;
      case 3:
        Serial.println(F("\n\rDHCP: Rebind fail"));
        break;
      case 4:
        Serial.println(F("\n\rDHCP: Rebind success"));
        break;
      default:
        Serial.println(F("\n\rDHCP: Unexpected number"));
        break;
    }
    //checkLinkStatus();

    delay(50);
    PORTD &= ~(1 << PD4);     // (RE_DE, LOW) disable sending
    //PORTC &= ~(1 << PC2);     // Disable COM Led
    //perf test device
    PORTC &= ~(1 << PC1);     // Disable COM Led
  }
}

//=================[ETHERNET SETUP]=======================
void EthernetSetup() {
  wdt_reset();

  NetworkRead();
  // if DHCP = 0, use manually entered settings
  if (DHCP == 0x00) {

    // start the Ethernet connection and the server:
    IPAddress newIP(IP[0], IP[1], IP[2], IP[3]);
    IPAddress newSN(SN[0], SN[1], SN[2], SN[3]);
    IPAddress newGW(GW[0], GW[1], GW[2], GW[3]);
    Ethernet.init(10);  // PB2
    Ethernet.begin(MAC, newIP, newGW, newGW, newSN);
    /*
        myIP = Ethernet.localIP();
        mySN = Ethernet.subnetMask();
        myGW = Ethernet.gatewayIP();
    */
  }

  //if DHCP = 1, use DHCP address
  else {
    // start the Ethernet connection and the server:
    Ethernet.init(10);  // PB2
    Ethernet.begin(MAC);
    /*
      myIP = Ethernet.localIP();
      mySN = Ethernet.subnetMask();
      myGW = Ethernet.gatewayIP();
    */
  }

  server.begin();
  //checkLinkStatus();
  sendNWSettings();
}



//=================[HANDLE ETHERNET STUFF]=======================
void handleEthernet() {

  wdt_reset();

  // listen for incoming clients
  client = server.available();
  if (client) {
    memset(linebuf, 0, sizeof(linebuf));
    charcount = 0;
    authentificated = false;
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      wdt_reset();
      if (client.available()) {
        char c = client.read();
        linebuf[charcount] = c;
        if (charcount < sizeof(linebuf) - 1) charcount++;
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {

          // Here is where the POST data is.
          while (client.available())
          {
            //getPOSTData();
            Serial.write(client.read());
          }
          Serial.println();

          if (authentificated) {
            SendMainPage(client);
          }
          else {
            SendLogin(client);
          }
          break;
        }
        if (c == '\n') {
          wdt_reset();
          // you're starting a new line
          currentLineIsBlank = true;
          if (strstr(linebuf, "Authorization: Basic") > 0 && strstr(linebuf, auth) > 0)
            authentificated = true;
          memset(linebuf, 0, sizeof(linebuf));
          charcount = 0;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}
