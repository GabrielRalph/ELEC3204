#include "arduino.h" 
#define MILIS_TO_MINUTES 60000

 typedef unsigned long time;
 typedef struct MotorState {
  float r;   // revolutions
  float rpm; // revolutions per minute
  float ra; // rotary acceleration
  float dt; // last difference in time
 } motorState;
 
 int pinA = 2;
 int pinB = 3;
 int CPR = 48;
 float GEAR_RATIO = 74.83;
 float lambda = 0.93;
 
 volatile long pos = 0;
 volatile byte state = 0;

 void interruptHandler() {
  int a = digitalRead(pinA);
  int b = digitalRead(pinB);
  int newState = (a << 1) | b;
  int di = 0;
  if ((state == 0 && newState == 1) ||
      (state == 1 && newState == 3) ||
      (state == 3 && newState == 2) ||
      (state == 2 && newState == 0)) {
    pos--;
  } else if ((state == 0 && newState == 2) ||
             (state == 2 && newState == 3) ||
             (state == 3 && newState == 1) ||
             (state == 1 && newState == 0)) {
    pos++;
  }
  state = newState;
}

void initRotaryEncoder(int a, int b){
  pinA = a;
  pinB = b;
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinA), interruptHandler, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), interruptHandler, CHANGE);
}





time lastTime = 0;
MotorState lastS = {0, 0, 0};
MotorState getMotorState(){
  time now = millis();
  // difference in time (in the unit of minutes)
  float dt = ((float) now - lastTime)/MILIS_TO_MINUTES;
  if (lastTime > now) dt = ((float)(now))/MILIS_TO_MINUTES;
  lastTime = now;

  float r = ((float) pos)/(CPR * GEAR_RATIO);
  float rpm = lastS.rpm * lambda + (r - lastS.r)/dt * (1 - lambda);
  if (isnan(rpm)) rpm = 0;
  
  float ra = (rpm - lastS.rpm)/dt;

  lastS = {r, rpm, ra, 60*dt};
  return lastS;
}



