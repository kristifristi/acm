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

// Replace with your network credentials
const char* ssid     = "tesla iot";
const char* password = "fsL6HgjN";

int START_OF_STOP = 1;
// Create an instance of the server
WiFiServer server(80);

void startLoop2() {
  START_OF_STOP == 1;
  // Code to start loop2
  }

void stopLoop2() {
  START_OF_STOP == 0;
  // Code to stop loop2
}

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

  // Match the request
  if (request.indexOf("/LOOP2/START") != -1) {
    startLoop2();
  } else if (request.indexOf("/LOOP2/STOP") != -1) {
    stopLoop2();
  }

int irSensorValue = -1;
int irRightSensorValue = analogRead(IR_RECHTS_PIN);
int irLeftSensorValue = analogRead(IR_LINKS_PIN);
int irFrontSensorValue = analogRead(IR_VOOR_PIN);
int reedValue = analogRead(REED_PIN);

  // Create a string with the sensor value
  String sensorValueStr0 = "IR Sensor value: " + String(irSensorValue);
    client.println();
  String sensorValueStr1 = "Right IR Sensor value: " + String(irRightSensorValue);
    client.println();

  String sensorValueStr2 = "Left IR Sensor value: " + String(irLeftSensorValue);
  String sensorValueStr3 = "Front IR Sensor value: " + String(irFrontSensorValue);
  String sensorValueStr4 = "Reed Sensor value: " + String(reedValue);

  // Send the response to the client
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println("Refresh: 5");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<a href=\"/LOOP2/START\">Start Loop2</a><br>");
  client.println("<a href=\"/LOOP2/STOP\">Stop Loop2</a><br>");
  client.println(sensorValueStr0);
  client.println(sensorValueStr1);
  client.println(sensorValueStr2);
  client.println(sensorValueStr3);
  client.println(sensorValueStr4);

  client.println("</html>");

  delay(1);
}
