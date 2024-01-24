/*
project 2: acm
Kristiaan Cramer
1069459
hogeschool rotterdam
2024
*/
#include "global.h"
#include "motor.h"
#include "sensor.h"
#include "test.h"
#include "ride.h"
#include "connect.h"

void setup() {
  motorSetup();
  sensorSetup();
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(921600);
  // xTaskCreatePinnedToCore (
  //     drive,     // Function to implement the task
  //     "drive",   // Name of the task
  //     1000,      // Stack size in bytes
  //     NULL,      // Task input parameter
  //     0,         // Priority of the task
  //     NULL,      // Task handle.
  //     0          // Core where the task should run
  //   );
  // setupfn();
}

void loop() {
  static int blink = 0;
  blink = !blink;
  digitalWrite(LED_BUILTIN, blink);
  // loopfn();
  Serial.print(String(millis()) + ": ");
  testSensor();
  delay(1000);
}





