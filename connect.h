/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA2 encryption. For insecure
 WEP or WPA, change the Wifi.begin() call and use Wifi.setMinSecurity() accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32 
31.01.2017 by Jan Hendrik Berlin
 
 */
#include <WiFi.h>
#include <string>

// Replace with your network credentials
const char* ssid     = "tesla iot";
const char* password = "fsL6HgjN";

// Create an instance of the server
WiFiServer server(80);


void setupfn() {
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}


void loopfn() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  client.flush();
  Serial.println(request);
  Serial.println(String(START_OF_STOP));
  // Match the request
  if (request.indexOf("START") != -1) {
    START_OF_STOP = 1;
  }
  if (request.indexOf("STOP") != -1) {
    START_OF_STOP = 0;
  }
  if (request.indexOf("RESET") != -1) {
    bochtenteller = 0;
  }
  if (request.indexOf("SET") != -1) {
    String str = request.substring(request.indexOf("/SET")+ 5,request.indexOf("HTTP")-1);
    Serial.println("\"" + str + "\"");
    bochtenteller = str.toInt();
  }


  // Create a string with the sensor value
  client.println();
  client.println();
  String sensorValueStr1 =  "Laatse detectie rechts: " + String(millis() - laatstR) + "<br>";

  String sensorValueStr2 = "Laatste detectie links: " + String(millis() - laatstL) + "<br>";
  String sensorValueStr3 = "Laatste detectie voor: " + String(millis() - laatstV) +"<br>";
  String sensorValueStr4 = "Laatste bocht: " + String(bochtenteller) + "<br>";
  String sensorValueStr5 = "ZijkantKennis: " + String(zijkantKennis) + "<br>";

  // Send the response to the client
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println("Refresh: 1");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<a href=\"/START\">Start</a><br>");
  client.println("<a href=\"/STOP\">Stop</a><br>");
  client.println("<a href=\"/RESET\">reset</a><br>");
  client.println("<p>" + sensorValueStr1);
  client.println(sensorValueStr2);
  client.println(sensorValueStr3);
  client.println(sensorValueStr4);
  client.println(sensorValueStr5 + "</p>");
  client.println("</html>");

  delay(1000);
}
