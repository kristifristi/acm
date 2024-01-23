
void testSensor(){
  SensorData omgeving = leesSensoren();
  Serial.print(omgeving.links ? "L" : " ");
  Serial.print(omgeving.voor ? "V" : " ");
  Serial.println(omgeving.rechts ? "R" : " ");
}

void testMotor() {
  delay(1000);
  motorControl(1, 0);
  Serial.println("+L");
  delay(1000);
  motorControl(-1, 0);
  Serial.println("-L");
  delay(1000);
  motorControl(0, 1);
  Serial.println("+R");
  delay(1000);
  motorControl(0, -1);
  Serial.println("-R");
  delay(1000);
  motorControl(-1, -1);
  Serial.println("-L,-R");
  delay(1000);
  motorControl(1, 1);
  Serial.println("+L,+R");
  delay(1000);
  motorControl(1, -1);
  Serial.println("+L,-R");
  delay(1000);
  motorControl(-1, 1);
  Serial.println("-L,+R");
  delay(1000);
  motorControl(0, 0);
  Serial.println("0L,0R");
}

void testTime(){
  delay(1000);
  Serial.println("test");
  Serial.println(millis());
}