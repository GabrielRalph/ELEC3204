#include "PWM.cpp"
#include "RotaryEncoder.h"

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
  boolean Brake = false;
  const int BrakeLED = 11;

  int currentLine = 3;
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

/*
    Serial.print(currentLine);
    Serial.print(", ");
    Serial.print(nextLine);
    Serial.print(", ");
    Serial.print(goalRPM);
    Serial.print(", ");
    Serial.print(i);
    Serial.println("");
*/

 /* 
  int emVal = digitalRead(emStop);


  //emergency stop
   // if (digitalRead(emStop) == HIGH)
    if (LOW == emVal)
  {
    Serial.println("EMERGENCY STOP!");
    Brake = true;
    goalRPM = 0;
    currentLine = 0;
    nextLine = 0;
   
  }*/


//read button presses to select the next line. Hold the button down for a bit!

  if(digitalRead(OrangeButton)== HIGH)
  {
    //Serial.println("ORANGE IS ON");
    nextLine = 3;                   //T3 service
    digitalWrite(YellowLEDr, LOW);
    digitalWrite(OrangeLEDr, HIGH); //Light up the red LED to show the next route
  }
   if(digitalRead(YellowButton)== HIGH)
  {
    //Serial.println("yellow IS ON");
    nextLine = 1;                   //T1 service
    digitalWrite(YellowLEDr, HIGH);
    digitalWrite(OrangeLEDr, LOW);
  }
  /*
   if(digitalRead(GreenButton)== HIGH)
  {
    nextLine = 8;                   //T8 service
    digitalWrite(GreenLEDr, HIGH);
  }
*/

  

  if(i==0)
  {
    currentLine = nextLine;
    nextLine = 0;
    
    if (currentLine == 3)
    {
      digitalWrite(OrangeLEDg, HIGH);
      digitalWrite(OrangeLEDr, LOW);
      digitalWrite(YellowLEDg, LOW); //set light of previous route to dim
    }  
    if (currentLine == 1)
    {
      digitalWrite(YellowLEDg, HIGH);
      digitalWrite(YellowLEDr, LOW);
      digitalWrite(OrangeLEDg, LOW); //set light of previous route to dim
    }  
    if (currentLine == 0)//Just wait here
    {
      goalRPM = 0;
      i = -1; //This will increment to 0
    }
  }
/*
  if (i == 6000)
  {
    i = -1;
  }*/
    
  
  //Hard coded routes
  if (Brake == true)
  {
    goalRPM = 0;
    currentLine = 0;
    
    if((i%100)==0){
      digitalWrite(BrakeLED,HIGH);
    }
    if((i%100)==50){
      digitalWrite(BrakeLED,LOW);
    }
  }
  
  
  
  if (currentLine == 3)
  {
  
  //This route only goes forwards, so keep RPM above 0 here
    if (goalRPM >= 100)
    {
      goalRPM = 100;
    }
    if (goalRPM <= 0)
    {
      goalRPM = 0;
    }
  
   //The route 
    if (((i%5) == 0)&&(i<500)){
      goalRPM +=1;
  
    }
    if (i==100)
    {
      Serial.println("This is your T3 City Circle service stopping at: St James, Circular Quay, Wynyard and Central");
    }
     if (((i%5) == 0)&&(i>=600)&&(i<1100))
     {
      goalRPM -=1;
    }
    if (i==700)
    {
     Serial.println("Next stop: St.James");
    }
    if (i == 1100)
    {
      
     Serial.println("Please mind the gap");
    }
  
  
    
    if (((i%5) == 0)&&(i>=1300)&&(i<1800))
    {
      goalRPM +=1;
    }
    if (((i%5) == 0)&&(i>=1900)&&(i<2400))
    {
      goalRPM -=1;
    }
    if (i==2000){
      Serial.println("Next stop: Circular Quay");
    }
    if (i== 2400)
    {
      Serial.println("Please mind the gap");
    }
  
  
    if (((i%5) == 0)&&(i>=2500)&&(i<3000))
    {
      goalRPM +=1;
    }
    if (((i%5) == 0)&&(i>=3100)&&(i<3600))
    {
      goalRPM -=1;
    }
    if (i==3200){
      Serial.println("Next stop: Wynyard");
    }
    if (i== 3600)
    {
      Serial.println("Please mind the gap");
    }
  
  
  
    if (((i%5) == 0)&&(i>=3800)&&(i<4300))
    {
      goalRPM +=1;
    }
    if (((i%5) == 0)&&(i>=4400)&&(i<4900))
    {
      goalRPM -=1;
    }
    if (i==4500){
      Serial.println("Next stop: Central");
    }
    if (i== 4900)
    {
      Serial.println("Please mind the gap");
    }
    if (i==5200)
    {
      i=-1;
    }
    
  }


  if (currentLine == 1)
  {
      //This route goes forwards and backwards
    if (goalRPM >= 100)
    {
      goalRPM = 100;
    }
    if (goalRPM <= -100)
    {
      goalRPM = -100;
    }
  
   //The route 
    if (((i%5) == 0)&&(i<500)){
      goalRPM +=1;
  
    }
    if (i==100)
    {
      Serial.println("This is your T1 Western service stopping at: Redfern and Parramatta");
    }
     if (((i%5) == 0)&&(i>=600)&&(i<1100))
     {
      goalRPM -=1;
    }
    if (i==700)
    {
     Serial.println("Next stop: Redfern");
    }
    if (i == 1100)
    {
      
     Serial.println("Please mind the gap");
    }
  
  
    
    if (((i%5) == 0)&&(i>=1300)&&(i<1800))
    {
      goalRPM +=1;
    }
    if (((i%5) == 0)&&(i>=2000)&&(i<2500))
    {
      goalRPM -=1;
    }
    if (i==2100){
      Serial.println("Next stop: Parramatta");
    }
    if (i== 2500)
    {
      Serial.println("Please mind the gap");
    }
  
  
    if (((i%5) == 0)&&(i>=2800)&&(i<3300))
    {
      goalRPM -=1;
    }
    if (i==2900)
    {
      Serial.println("This is your T1 North shore service stopping at: Redfern and Central");
    }
    if (((i%5) == 0)&&(i>=3400)&&(i<3900))
    {
      goalRPM +=1;
    }
    if (i==3500){
      Serial.println("Next stop: Redfern");
    }
    if (i== 3900)
    {
      Serial.println("Please mind the gap");
    }
  
  
  
    if (((i%5) == 0)&&(i>=4100)&&(i<4600))
    {
      goalRPM -=1;
    }
    if (((i%5) == 0)&&(i>=4800)&&(i<5300))
    {
      goalRPM +=1;
    }
    if (i==4900){
      Serial.println("Next stop: Central");
    }
    if (i== 5300)
    {
      Serial.println("Please mind the gap");
    }
    if (i==5300)
    {
      i=-1;
    }
    
  }
  
  //test value, not being used
  if (currentLine == 100)
  {
    goalRPM = 100;
  }


  MotorState ss = getMotorState();

  float p = (goalRPM - ss.rpm) * P ;//+ ss.ra * D;
//  float d = -ss.ra / 1000000000;
  dutyCycle += p;
  motor->setDutyCycle((int) 50 - dutyCycle);
    
 
  
  delay(10);
  i++;

  
}
