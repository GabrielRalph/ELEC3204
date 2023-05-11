#include "PWM.cpp"
#include "RotaryEncoder.h"

PWM* motor;

void setup() {
  motor = new PWM(9, 10);
  initRotaryEncoder(2, 3);
  Serial.begin(9600);
  motor->setDutyCycle((int) (30));
}

float rpmsmooth = 0;
float goalRPM = 100;

float P = 0.02211;
float D = -0.000000000;
float dutyCycle = 0;

int i = 0;
void loop() {
  MotorState ss = getMotorState();
//
  float p = (goalRPM - ss.rpm) * P ;//+ ss.ra * D;
//  float d = -ss.ra / 1000000000;
  dutyCycle += p;
  motor->setDutyCycle((int) 50 - dutyCycle);

  
  if (i < 600){
    Serial.print(millis());
    Serial.print(", ");
    Serial.print(ss.rpm);
    Serial.print(", ");
    Serial.print(ss.ra * 0.001);
    Serial.print(", ");
    Serial.print(dutyCycle);
    Serial.print(", ");
    Serial.print(goalRPM);
    Serial.println("");
  }
  

  delay(5);
  i++;
//  if (i%400 == 0) {
//    goalRPM = -50;
//  }
}
