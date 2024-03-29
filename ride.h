/*
project 2: acm
Kristiaan Cramer
1069459
hogeschool rotterdam
2024
*/
const int linkerbochten[] = {3,8,9,13};
const int aantalLinks = 4;

unsigned long laatstV = millis();
unsigned long laatstL = millis();
unsigned long laatstR = millis();
unsigned long laatstM = millis();
int zijkantKennis = 1;
int bochtenteller = 0;

int kennisInc(int i, bool even){
  static unsigned long laatst = millis();
  if(millis() - laatst > 100){
    i += i%2 == !even;
    laatst = millis();
  }
  return i;
}

void drive (void* pvParameters){
  // Serial.print("hellow world");
  while(1){
    if(!START_OF_STOP){
      motorControl(0,0);
      long unsigned t = millis();
      while(!START_OF_STOP){
        if(millis() - t > 1000){
          // Serial.println("Man Im DEAD " + String(START_OF_STOP));
          t = millis();
        }
        if(START_OF_STOP){
          zijkantKennis = 1;
          break;
        }
      }
    }
    static int laatstebocht = 0;
    static bool linkerbocht = false;
    static bool grotebocht = false;
    SensorData omgeving = leesSensoren();
    static unsigned long printTijd = millis();
    if(omgeving.reed){ START_OF_STOP = 0; }
    if(bochtenteller != laatstebocht){
      linkerbocht = false;
      for(int i = 0; i < aantalLinks;++i){
        if(bochtenteller == linkerbochten[i]){
          linkerbocht = true;
        }
      }
      grotebocht = bochtenteller == 3;
    }
    if(omgeving.voor){
      motorControl(-1,-1);
      if((millis() - laatstV) > 1000){
        ++bochtenteller;
      }
      zijkantKennis = 0;
      laatstV = millis();
    } else if(omgeving.links){
      zijkantKennis = kennisInc(zijkantKennis,true);
      motorControl(1,0);
      laatstL = millis();
    } else if(omgeving.rechts){
      zijkantKennis = kennisInc(zijkantKennis,true);
      motorControl(0,1);
      laatstR = millis();
    } else if(zijkantKennis == 0){
      if(millis() - laatstV > 100){
        motorControl(1,1);
      } else {
        linkerbocht ? motorControl(0,1) : motorControl(1,0);
      }
    } else if(grotebocht && zijkantKennis > 1){
      while(!leesSensoren().links || millis() - laatstL < 500){
        if(millis()%250 < 175){
          motorControl(1,1);
        } else {
          motorControl(0,1);
        }
        if(leesSensoren().voor) { break;}
      }
      grotebocht = false;
    } else {
      zijkantKennis = kennisInc(zijkantKennis,false);
      if(bochtenteller == 4 && millis()%250 < 40){
        motorControl(1,0);
      } else {
        motorControl(1,1);
      }
    }
    if(bochtenteller > 15){
      START_OF_STOP = 0;
    }
  }
}