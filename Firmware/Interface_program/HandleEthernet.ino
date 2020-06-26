
//=================[CHECK ETH LINK STATUS]=======================

void checkLinkStatus() {
  wdt_reset();
  if (Ethernet.linkStatus() == LinkON && EthSetup == true) {
    EthSetup = false;
    EthernetSetup();
  }
}

//=================[ETHERNET SETUP]=======================
void EthernetSetup() {
  wdt_reset();

  NetworkEEPROMRead();
  // if DHCP = 0, use manually entered settings
  if (DHCP == 0x00) {

    // start the Ethernet connection and the server:
    /*
      IPAddress newIP(IP[0], IP[1], IP[2], IP[3]);
      IPAddress newSN(SN[0], SN[1], SN[2], SN[3]);
      IPAddress newGW(GW[0], GW[1], GW[2], GW[3]);
    */
    Ethernet.init(10);  // PB2
    Ethernet.begin(MAC, IP, GW, GW, SN);
  }

  //if DHCP = 1, use DHCP address
  else {
    // start the Ethernet connection and the server:
    Ethernet.init(10);  // PB2
    Ethernet.begin(MAC);
    while (Ethernet.linkStatus() != LinkON) {}
    //EthSetup = true;
    //checkLinkStatus();

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
        // if you've gotten to the end of the line (received a newline character) and the line is blank, the http request has ended, so you can send a reply

        if (c == '\n' && currentLineIsBlank) {

          // Here is where the POST data is.
          /*
                    if (reading && c == ' ') reading = false;
                    if (c == '?') reading = true; //found the ?, begin reading the info

                    if (reading) {
                      //Serial.print(c);
                      if (c != '?') {
                        POSTData += c;
                      }

                    }
          */
          while (client.available())
          {
            Serial.write(client.read());
            //getPOSTData();
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

    getPOSTData(POSTData);
    // give the web browser time to receive the data
    delay(10);
    // close the connection:
    client.stop();
  }
}
