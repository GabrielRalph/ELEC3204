#include "PWM.cpp"
#define pinA 2
#define pinB 3

typedef unsigned long time;

PWM* m1;

volatile int pos = 0;
float velocity = 0;
time lastTime = 0;
volatile int state = 0;

void setup() {
  m1 = &PWM(10, 9);
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinA), interruptHandler, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), interruptHandler, CHANGE);

  m1->setDutyCycle((int) (80));
}

float getTimeDelta(){
  time now = millis();
  float dt = 0.001 * ((float)(now - lastTime)); // seconds
  if (lastTime > now) dt = 0.001 * ((float)(now));
  lastTime = now;
  return dt;
}


void interruptHandler() {
  int a = digitalRead(pinA);
  int b = digitalRead(pinB);
  int newState = (a << 1) | b;
  int di = 0;
  if ((state == 0 && newState == 1) ||
      (state == 1 && newState == 3) ||
      (state == 3 && newState == 2) ||
      (state == 2 && newState == 0)) {
//    di = -1;
    pos++;
  } else if ((state == 0 && newState == 2) ||
             (state == 2 && newState == 3) ||
             (state == 3 && newState == 1) ||
             (state == 1 && newState == 0)) {
//    di = 1;
    pos--;
  }
  state = newState;
}



int count = 0;
int p0 = pos;
float vel = 0;
int smooth = 3;
int dt = 1;

float goalVel = 100;
float duty = 80;

void loop() {
  if (!(count%smooth)) {
    int p1 = pos;
    float dt = getTimeDelta();
    vel = ((float) (p1 - p0)) / dt;
    vel /= 48;
    vel /= 74.83;
    vel *= 60;
    p0 = pos;
  }
  delay(dt);

  float error = goalVel - vel;

  float p = error * 0.08;
//  Serial.print(count);
//  Serial.print(", 1000, ");
  Serial.print(vel);
  Serial.print(", ");
  Serial.println(error);
  count ++;

  if (abs(error) > 1) {
    duty += p;
    m1->setDutyCycle((int) (duty));
  }

  if (count > 200) {
    goalVel = 50;
  }
  
}
