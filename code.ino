#include "global.h"
#include "motor.h"
#include "sensor.h"
#include "test.h"
#include "ride.h"
#include "connect.h"



bool ride = false;





void setup() {
  motorSetup();
  sensorSetup();
  Serial.begin(921600);
  xTaskCreatePinnedToCore (
      drive,     // Function to implement the task
      "drive",   // Name of the task
      1000,      // Stack size in bytes
      NULL,      // Task input parameter
      0,         // Priority of the task
      NULL,      // Task handle.
      0          // Core where the task should run
    );
  setupfn();
}

void loop() {
  loopfn();
}





