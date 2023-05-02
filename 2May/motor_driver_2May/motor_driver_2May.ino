#include "PWM.cpp"
#include "RotaryEncoder.h"

PWM* motor;
  const int ledPin = 13;
  const int buttonPin = 4;
  const int emStop = 5;

void setup() {
  motor = new PWM(9, 10);
  initRotaryEncoder(2, 3);
  Serial.begin(9600);
  motor->setDutyCycle((int) (30));
  pinMode(ledPin,OUTPUT); // Set the LED Pin as an output
  pinMode(buttonPin,INPUT_PULLUP); // Set the Tilt Switch as an input
  pinMode(emStop, INPUT_PULLUP);
}

float rpmsmooth = 0;
//float goalRPM = 0;
float goalRPM = 100;

float P = 0.02211;
float D = -0.000000000;
float dutyCycle = 0;

int i = 0;
void loop() {
  int digitalVal = digitalRead(buttonPin); // Take a reading
  int emVal = digitalRead(emStop);

// Simulate the approaching of train to a station upon button press
  if(HIGH == digitalVal)
  {
    digitalWrite(ledPin,LOW); //Turn the LED off
    goalRPM = 50;
  }
  else
  {
    digitalWrite(ledPin,HIGH);//Turn the LED on
    goalRPM = 100;
  }

  if (HIGH == emVal)
  {
    goalRPM = 0;
  }
  
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
  /*
  delay(5);
  i++;
  if (i%400 == 0) {
   // goalRPM = -50;
}
  if (i == 100){
    goalRPM = 20;
  }
  if (i == 200){
    goalRPM = 50;
  }
  if (i == 500){
    goalRPM = 100;
  }
  */
}
