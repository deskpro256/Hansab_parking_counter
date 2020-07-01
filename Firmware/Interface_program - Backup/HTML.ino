
void SendLogin(EthernetClient &client)
{
  wdt_reset();
  client.println("HTTP/1.1 401 Authorization Required");
  client.println("WWW-Authenticate: Basic realm=\"Secure Area\"");
  client.println("Content-Type: text/html");
  client.println("Connnection: close");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<HTML>  <HEAD>   <TITLE>Error</TITLE>");
  client.println(" </HEAD> <BODY><H1>401 Unauthorized.</H1></BODY> </HTML>");
}


//=================[MAIN HTML PAGE]=======================

void SendMainPage(EthernetClient &client) {
  wdt_reset();
  // Response header
  // send a standard http response header
  client.println("HTTP/1.0 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  // Response header

  // web page

  client.println(docTypeHTML);
  client.println(htmlStart);
  client.println(headStart);
  client.println(autoScaleMeta);
  client.println(styleStart);
  client.println(F("body{background-color: #171f61; font-family: Arial;}"));
  client.println(F(".tab {overflow: hidden; border: 1px solid #ccc; background-color: #f1f1f1; width: 513px;}"));
  client.println(F(".tab button { background-color: inherit;  float: left;  border: none;  outline: none;  cursor: pointer;  padding: 14px 16px; transition: 0.3s; font-size: 17px;}"));
  client.println(F(".tab button:hover { background-color: #ddd;}"));
  client.println(F(".tab button.active { background-color: #ccc;}"));
  client.println(F(".tabcontent { width: 490px; border-color: black; background-color: #f2f2f2; display: none; padding: 6px 12px; -webkit-animation: fadeEffect 1s; animation: fadeEffect 1s;}"));
  client.println(F("@-webkit-keyframes fadeEffect { from {opacity: 0;} to {opacity: 1;}}"));
  client.println(F("@keyframes fadeEffect { from {opacity: 0;} to {opacity: 1;}}"));
  client.println(F(".def{width: 505px; border-color: black; background-color: #f2f2f2; padding: 5px;}"));
  client.println(styleEnd);
  client.println(F("<title>Parking configurator</title>"));
  client.println(headEnd);
  client.println(bodyStart);
  client.println(centerStart);
  client.println(F("<div class = \"def\">"));
  client.println(F("<img src=\"https://www.hansab.lv/sites/all/themes/hansab/imgs/hansab-logo.svg\">"));
  client.println(F("<h3>Parking solutions</h3>"));
  client.println(divEnd);
  client.println(F("<div class=\"tab\">"));
  client.println(F("<button class=\"tablinks\" onclick=\"openTab(event, 'Current')\" id=\"defaultOpen\">Current</button>"));
  client.println(F("<button class=\"tablinks\" onclick=\"openTab(event, 'Configuration')\">Configuration</button>"));
  client.println(F("<button class=\"tablinks\" onclick=\"openTab(event, 'Network')\">Network</button>"));
  client.println(divEnd);
  client.println(F("<div id=\"Current\" class=\"tabcontent\">"));

  client.print(F("<form action=\"http://"));
  client.print(Ethernet.localIP());
  client.println("\" method=\"post\">");

  client.println(F("<h3>Current statistics</h3>"));

  if (activeFloors == 0x01) {

    client.println(F("<label for=\"Zone 1\">Zone 1 Count:</label>"));
    client.print(F("<input type=\"number\" id=\"zone\" name=\"zone1\" value = \""));
    client.print(currentFloorCount[0]);
    client.println(F("\" min=\"0\" max=\"999\"><br>"));
  }

  if (activeFloors == 0x02) {
    client.println(F("<label for=\"Zone 1\">Zone 1 Count:</label>"));
    client.print(F("<input type=\"number\" id=\"zone\" name=\"zone1\" value = \""));
    client.print(currentFloorCount[0]);
    client.println(F("\" min=\"0\" max=\"999\"><br>"));

    client.println(F("<label for=\"Zone 2\">Zone 2 Count:</label>"));
    client.print(F("<input type=\"number\" id=\"zone\" name=\"zone2\" value = \""));
    client.print(currentFloorCount[1]);
    client.println(F("\" min=\"0\" max=\"999\"><br>"));
  }

  if (activeFloors == 0x03) {

    client.println(F("<label for=\"Zone 1\">Zone 1 Count:</label>"));
    client.print(F("<input type=\"number\" id=\"zone\" name=\"zone1\" value = \""));
    client.print(currentFloorCount[0]);
    client.println(F("\" min=\"0\" max=\"999\"><br>"));

    client.println(F("<label for=\"Zone 2\">Zone 2 Count:</label>"));
    client.print(F("<input type=\"number\" id=\"zone\" name=\"zone2\" value = \""));
    client.print(currentFloorCount[1]);
    client.println(F("\" min=\"0\" max=\"999\"><br>"));

    client.println(F("<label for=\"Zone 3\">Zone 3 Count:</label>"));
    client.print(F("<input type=\"number\" id=\"zone\" name=\"zone3\" value = \""));
    client.print(currentFloorCount[2]);
    client.println(F("\" min=\"0\" max=\"999\"><br>"));
  }

  if (activeFloors == 0x04) {
    client.println(F("<label for=\"Zone 1\">Zone 1 Count:</label>"));
    client.print(F("<input type=\"number\" id=\"zone\" name=\"zone1\" value = \""));
    client.print(currentFloorCount[0]);
    client.println(F("\" min=\"0\" max=\"999\"><br>"));

    client.println(F("<label for=\"Zone 2\">Zone 2 Count:</label>"));
    client.print(F("<input type=\"number\" id=\"zone\" name=\"zone2\" value = \""));
    client.print(currentFloorCount[1]);
    client.println(F("\" min=\"0\" max=\"999\"><br>"));

    client.println(F("<label for=\"Zone 3\">Zone 3 Count:</label>"));
    client.print(F("<input type=\"number\" id=\"zone\" name=\"zone3\" value = \""));
    client.print(currentFloorCount[2]);
    client.println(F("\" min=\"0\" max=\"999\"><br>"));

    client.println(F("<label for=\"Zone 4\">Zone 4 Count:</label>"));
    client.print(F("<input type=\"number\" id=\"zone\" name=\"zone4\" value = \""));
    client.print(currentFloorCount[3]);
    client.println(F("\" min=\"0\" max=\"999\"><br>"));
  }

  client.println(F("<br><br><input type=\"submit\" value=\"Change\">"));

  client.println(formEnd);
  client.println(divEnd);

  client.println(F("<div id=\"Configuration\" class=\"tabcontent\">"));
  client.println(F("<h3>Configuration info</h3>"));

  client.println(F("Active zones: "));
  client.print(activeFloors);
  client.println(F("<br>"));


  if (activeFloors == 0x01) {
    client.print(F("Zone 1 max count: "));
    client.print(floorMaxCount[0]);
    client.println(F("<br>"));
  }

  if (activeFloors == 0x02) {
    client.print(F("Zone 1 max count: "));
    client.print(floorMaxCount[0]);
    client.println(F("<br>"));

    client.print(F("Zone 2 max count: "));
    client.print(floorMaxCount[1]);
    client.println(F("<br>"));
  }

  if (activeFloors == 0x03) {
    client.print(F("Zone 1 max count: "));
    client.print(floorMaxCount[0]);
    client.println(F("<br>"));

    client.print(F("Zone 2 max count: "));
    client.print(floorMaxCount[1]);
    client.println(F("<br>"));

    client.print(F("Zone 3 max count: "));
    client.print(floorMaxCount[2]);
    client.println(F("<br>"));
  }

  if (activeFloors == 0x04) {
    client.print(F("Zone 1 max count: "));
    client.print(floorMaxCount[0]);
    client.println(F("<br>"));

    client.print(F("Zone 2 max count: "));
    client.print(floorMaxCount[1]);
    client.println(F("<br>"));

    client.print(F("Zone 3 max count: "));
    client.print(floorMaxCount[2]);
    client.println(F("<br>"));

    client.print(F("Zone 4 max count: "));
    client.print(floorMaxCount[3]);
    client.println(F("<br>"));
  }


  client.print(F("Node count: "));
  client.print(slaveCount);
  client.println(F("<br><br>"));

  client.print(F("<form action=\"http://"));
  client.print(Ethernet.localIP());
  client.println("\" method=\"post\">");
  client.println(F("<input type=\"submit\" value=\"Restart\" onclick=\"Restart()\">"));
  client.println(formEnd);

  client.println(divEnd);

  client.println(F("<div id=\"Network\" class=\"tabcontent\">"));
  client.println(F("<h3>Network</h3>"));
  client.println(F("<h4>Current settings:</h4>"));

  client.print(F("DHCP: "));
  if (DHCP == 0x01) {
    client.print(F("ON"));
  }
  else {
    client.print(F("OFF"));
  }
  client.println(F("<br>"));


  client.print(F("IP Address: "));
  client.print(Ethernet.localIP());
  client.println(F("<br>"));

  client.print(F("Subnet: "));
  client.print(Ethernet.subnetMask());
  client.println(F("<br>"));

  client.print(F("Gateway: "));
  client.print(Ethernet.gatewayIP());
  client.println(F("<br>"));

  client.print(F("MAC Address: "));
  client.print(MAC[0], HEX);
  client.print(colon);
  client.print(MAC[1], HEX);
  client.print(colon);
  client.print(MAC[2], HEX);
  client.print(colon);
  client.print(MAC[3], HEX);
  client.print(colon);
  client.print(MAC[4], HEX);
  client.print(colon);
  client.println(MAC[5], HEX);
  client.println(F("<br>"));

  client.println(divEnd);

  client.println(scriptStart);
  client.println(F("function Restart(){alert(\"The device is restarting!\");}"));
  client.println(F("function openTab(evt, tabName) {"));
  client.println(F("var i, tabcontent, tablinks;"));
  client.println(F("tabcontent = document.getElementsByClassName(\"tabcontent\");"));
  client.println(F("for (i = 0; i < tabcontent.length; i++) {tabcontent[i].style.display = \"none\";}"));
  client.println(F("tablinks = document.getElementsByClassName(\"tablinks\");"));
  client.println(F("for (i = 0; i < tablinks.length; i++) {tablinks[i].className = tablinks[i].className.replace(\" active\", \"\");}"));
  client.println(F("document.getElementById(tabName).style.display = \"block\";"));
  client.println(F("evt.currentTarget.className += \" active\";}"));
  client.println(F("document.getElementById(\"defaultOpen\").click();"));
  client.println(scriptEnd);
  client.println(F("<br><br>"));

  client.print(F("<form action=\"http://"));
  client.print(Ethernet.localIP());
  client.println(F("\" method=\"post\">"));
  client.println(F("<input type=\"submit\" value=\"Exit\" onclick=\"Exit()\">"));

  client.println(formEnd);
  client.println(centerEnd);
  client.println(bodyEnd);
  client.println(htmlEnd);
  // web page end
  wdt_reset();
}
