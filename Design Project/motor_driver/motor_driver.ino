#include "PWM.cpp"
#include "RotaryEncoder.h"
#include "TrainRide.h"
#define BRAKE 7
PWM* motor;

  
  const int OrangeButton = 4;
  const int OrangeLEDg = 12;
  const int OrangeLEDr = 13;
  
  const int YellowButton = 6;
  const int YellowLEDg = 8;
  const int YellowLEDr = 7;
  
  const int GreenButton = 0;
  const int GreenLEDg = 0;
  const int GreenLEDr = 0; 
  

  const int emStop = 5;
  const int BrakeLED = 11;

  int currentLine = 0;
  int nextLine = 0;
  
  
void setup() {
  
  motor = new PWM(9, 10);
  initRotaryEncoder(2, 3);
  Serial.begin(9600);
  motor->setDutyCycle((int) (30));

  pinMode(YellowButton,INPUT);
  pinMode(OrangeButton,INPUT);
  pinMode(YellowLEDr,OUTPUT);
  pinMode(YellowLEDg,OUTPUT);
  pinMode(OrangeLEDr,OUTPUT);
  pinMode(OrangeLEDg,OUTPUT);
  pinMode(BrakeLED,OUTPUT);
  pinMode(emStop, INPUT);
}

float rpmsmooth = 0;
float goalRPM = 0;

float P = 0.02211;
float D = -0.000000000;
float dutyCycle = 0;

int i = 0;
void loop() {


  bool ob = digitalRead(OrangeButton);
  bool yb = digitalRead(YellowButton);
  bool em = digitalRead(emStop);

//  Serial.print(ob);
//  Serial.print(" | ");
//  Serial.print(yb);
//  Serial.print(" | ");
//  Serial.println(em);

  //read button presses to select the next line. Hold the button down for a bit!
  if (em){
    Serial.println("EMERGENCY STOP!");
    currentLine = BRAKE;
    i = 0;
    nextLine = BRAKE; 
  }else if(ob && !yb){
    //Serial.println("ORANGE IS ON");
    nextLine = 3;                   //T3 service
    digitalWrite(YellowLEDr, LOW);
    digitalWrite(OrangeLEDr, HIGH); //Light up the red LED to show the next route
  } else if (yb && !ob){
    //Serial.println("yellow IS ON");
    nextLine = 1;                   //T1 service
    digitalWrite(YellowLEDr, HIGH);
    digitalWrite(OrangeLEDr, LOW);
  } else if (ob && yb) {
    Serial.println("CASE 100!!");
    nextLine = 100;
    i = -1;
  } 
  
  

  if(i==0){
    currentLine = nextLine;
    nextLine = 0;
    digitalWrite(OrangeLEDr, LOW);
    digitalWrite(YellowLEDr, LOW);
  }  


  
  switch (currentLine) {
    case 0: 
      goalRPM = 0;
      i = -1; //This will increment to 0
    break;
    case 1: 
      digitalWrite(OrangeLEDg, LOW);
      digitalWrite(YellowLEDg, HIGH); //set light of previous route to dim
      digitalWrite(YellowLEDr, LOW); 
      routeT1(&goalRPM, &i);
    break;
    
    case 3: 
      digitalWrite(YellowLEDg, LOW);
      digitalWrite(OrangeLEDg, HIGH); //set light of previous route to dim
      digitalWrite(OrangeLEDr, LOW); 
      routeT3(&goalRPM, &i); 
    break;

    case BRAKE: 
      digitalWrite(OrangeLEDg, LOW);
      digitalWrite(OrangeLEDr, LOW);
      digitalWrite(YellowLEDg, LOW); //set light of previous route to dim
      digitalWrite(YellowLEDr, LOW); 
      goalRPM = 0;
      digitalWrite(BrakeLED,i < 50);
      i = -1;
    break;

    //test value, not being used
    case 100: 
      Serial.println("here");
      digitalWrite(OrangeLEDg, LOW);
      digitalWrite(OrangeLEDr, LOW);
      goalRPM = 100;
      if (i > 1000) i = -1;
    break;
  }


  // Motor control sequence
  MotorState ss = getMotorState();
  float p = (goalRPM - ss.rpm) * P ;//+ ss.ra * D;
  dutyCycle += p;
  motor->setDutyCycle((int) 50 - dutyCycle);
     
  Serial.print(ss.rpm);
  Serial.print(", ");
  Serial.print(ss.ra * 0.001);
  Serial.print(", ");
  Serial.print(dutyCycle);
  Serial.print(", ");
  Serial.print(goalRPM);
  Serial.println("");
  
  delay(10);
  i++;
}
