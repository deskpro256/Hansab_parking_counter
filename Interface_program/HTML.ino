
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
  // Response header
  // send a standard http response header
  client.println("HTTP/1.0 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  // Response header
  
  client.println("<!DOCTYPE HTML>");
  client.println("<HTML><BODY>");
  //form added to send data from browser and view received data in serial monitor
  client.println("<h3>Change login</h3>");
  client.print("<FORM ACTION=http://");
  client.print(myIP);
  client.println(" METHOD=\"post\">");
  client.println("<label for = \"user\">Username:</label><br>");
  client.println("<input type=\"text\" id=\"user\" name=\"user\"><br>");
  client.println("<label for=\"pass\">Password:</label><br>");
  client.println("<input type=\"text\" id=\"pass\" name=\"pass\"><br>");
  client.println("<input type=\"submit\" value=\"Change\">");
  client.println("</FORM>");
  client.println("<BR>");
  client.println("</BODY></HTML>");
}
