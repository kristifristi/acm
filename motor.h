#define MOTOR_L_VOORUIT 21 
#define MOTOR_L_ACHTERUIT 19
#define MOTOR_R_VOORUIT 4
#define MOTOR_R_ACHTERUIT 16

int truncateInt(int x, int limit){
  int sign = (x < 0) ? -1 : 1;
  x = (abs(x) > limit) ? limit * sign : x;
}

void motorSetup(){
  pinMode(MOTOR_L_VOORUIT, OUTPUT);
  pinMode(MOTOR_L_ACHTERUIT, OUTPUT);
  pinMode(MOTOR_R_VOORUIT, OUTPUT);
  pinMode(MOTOR_R_ACHTERUIT, OUTPUT);
}

void motorControl(int links, int rechts){
  switch(links){
    case 1:
      digitalWrite(MOTOR_L_VOORUIT, HIGH);
      digitalWrite(MOTOR_L_ACHTERUIT, LOW);
      break;
    case -1:
      digitalWrite(MOTOR_L_VOORUIT, LOW);
      digitalWrite(MOTOR_L_ACHTERUIT, HIGH);
      break;
    default:
      digitalWrite(MOTOR_L_VOORUIT, LOW);
      digitalWrite(MOTOR_L_ACHTERUIT, LOW);
  }
  switch(rechts){
    case 1:
      digitalWrite(MOTOR_R_VOORUIT, HIGH);
      digitalWrite(MOTOR_R_ACHTERUIT, LOW);
      break;
    case -1:
      digitalWrite(MOTOR_R_VOORUIT, LOW);
      digitalWrite(MOTOR_R_ACHTERUIT, HIGH);
      break;
    default:
      digitalWrite(MOTOR_R_VOORUIT, LOW);
      digitalWrite(MOTOR_R_ACHTERUIT, LOW);
  }

}

void motorControlA(int L, int R){
  L = truncateInt(L, 255);
  if(L < 0){
    L *= -1;
    digitalWrite(MOTOR_L_VOORUIT, LOW);
    analogWrite(MOTOR_L_ACHTERUIT, L);
  } else {
    digitalWrite(MOTOR_L_ACHTERUIT, LOW);
    analogWrite(MOTOR_L_VOORUIT, L);
  }
  R = truncateInt(R, 255);
  if(R < 0){
    R *= -1;
    digitalWrite(MOTOR_R_VOORUIT, LOW);
    analogWrite(MOTOR_R_ACHTERUIT, R);
  } else {
    digitalWrite(MOTOR_R_ACHTERUIT, LOW);
    analogWrite(MOTOR_R_VOORUIT, R);
  }
}
