#define IR_LINKS_PIN 5 //TODO pins aanpassen
#define IR_RECHTS_PIN 17
#define IR_VOOR_PIN 18
#define REED_PIN 0

typedef struct SensorData{
  bool links;
  bool rechts;
  bool voor;
  bool reed;
};

void sensorSetup(){
  pinMode(IR_LINKS_PIN, INPUT);
  pinMode(IR_RECHTS_PIN, INPUT);
  pinMode(IR_VOOR_PIN, INPUT);
  pinMode(REED_PIN, INPUT_PULLUP);
}

SensorData leesSensoren(){
  SensorData data;
  data.links = digitalRead(IR_LINKS_PIN);
  data.rechts = digitalRead(IR_RECHTS_PIN);
  data.voor = digitalRead(IR_VOOR_PIN);
  data.reed = !digitalRead(REED_PIN);
  return data;
}
