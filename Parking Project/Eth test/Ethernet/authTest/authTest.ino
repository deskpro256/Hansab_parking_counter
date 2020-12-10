
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {0x4A, 0xCD, 0x14, 0xAE, 0x30, 0xEE};
IPAddress ip(192, 168, 0, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
//auth : admin:admin
char auth[] = "YWRtaW46YWRtaW4=";
void setup() {

  // start the Ethernet connection and the server:
  Ethernet.begin(mac);
  server.begin();
}


void SendOKpage(EthernetClient &client)
{
  // send a standard http response header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connnection: close");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  // add a meta refresh tag, so the browser pulls again every 5 seconds:
  client.println("<meta http-equiv=\"refresh\" content=\"5\">");
  // output the value of each analog input pin
  for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
    int sensorReading = analogRead(analogChannel);
    client.print("analog input ");
    client.print(analogChannel);
    client.print(" is ");
    client.print(sensorReading);
    client.println("<br />");
  }
  client.println("</html>");
}


void SendAuthentificationpage(EthernetClient &client)
{
  client.println("HTTP/1.1 401 Authorization Required");
  client.println("WWW-Authenticate: Basic realm=\"Secure Area\"");
  client.println("Content-Type: text/html");
  client.println("Connnection: close");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<HTML>  <HEAD>   <TITLE>Error</TITLE>");
  client.println(" </HEAD> <BODY><H1>401 Unauthorized.</H1></BODY> </HTML>");
}

char linebuf[80];
int charcount = 0;
boolean authentificated = false;

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    memset(linebuf, 0, sizeof(linebuf));
    charcount = 0;
    authentificated = false;
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
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
            Serial.write(client.read());
          }
          Serial.println();
          
          if (authentificated)
            SendOKpage(client);
          else
            SendAuthentificationpage(client);
          break;
        }
        if (c == '\n') {
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
