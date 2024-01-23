#include "motor.h"
#include "sensor.h"
#include "test.h"

const int linkerbochten[] = {3,7,8,12};
const int aantalLinks = 4;

int kennisInc(int i, bool even){
  static unsigned long laatst = millis();
  if(millis() - laatst > 100){
    i += i%2 == !even;
    laatst = millis();
  }
  return i;
}

void setup() {
    motorSetup();
    sensorSetup();
    Serial.begin(921600);
}

void loop() {
  // testMotor();
  //testTime();
  static unsigned long laatstV = millis();
  static unsigned long laatstL = millis();
  static unsigned long laatstR = millis();
  static int zijkantKennis = 1;
  static int bochtenteller = 0;
  static int laatstebocht = 0;
  static bool linkerbocht = false;
  static bool grotebocht = false;
  SensorData omgeving = leesSensoren();
  static unsigned long printTijd = millis();
  if((millis() - printTijd) > 1000){
    Serial.println("bocht: " + String(bochtenteller));
    //Serial.println("Tijd: " + String(millis() - laatstL));
    Serial.println("kennis: " + String(zijkantKennis));
    Serial.println("groot" + String(grotebocht));
    printTijd = millis();
  }
  if(bochtenteller != laatstebocht){
    for(int i = 0; i < aantalLinks;++i){
      linkerbocht = false;
      if(bochtenteller == linkerbochten[i]){
        linkerbocht = true;
      }
    }
    grotebocht = bochtenteller == 1;
  }
  if(omgeving.voor){
    motorControl(-1,-1);
    if((millis() - laatstV) > 1000){
      ++bochtenteller;
    }
    laatstV = millis();
    zijkantKennis = 0;
  } else if(omgeving.links){
    zijkantKennis = kennisInc(zijkantKennis,true);
    motorControl(1,0);
    laatstL = millis();
  } else if(omgeving.rechts){
    zijkantKennis = kennisInc(zijkantKennis,true);
    motorControl(0,1);
    laatstR = millis();
  } else if(zijkantKennis == 0){   
    linkerbocht ? motorControl(0,1) : motorControl(1,0);
  } else if(grotebocht && zijkantKennis > 5){
    while(!leesSensoren().links || millis() - laatstL < 500){
      if(millis()%250 < 100){
        motorControl(1,1);
      } else {
        motorControl(0,1);
      }
    }
    grotebocht = false;
  } else {
    zijkantKennis = kennisInc(zijkantKennis,false);
    motorControl(1,1);

  }
}



