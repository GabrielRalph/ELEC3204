#include "arduino.h" 

void routeT3(float* _goalRPM, int *_i){
  float goalRPM = *_goalRPM;
  int i = *_i;
  
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

    *_i = i;
    *_goalRPM = goalRPM;
}

void routeT1(float* _goalRPM, int *_i){
  float goalRPM = *_goalRPM;
  int i = *_i;
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

  *_i = i;
  *_goalRPM = goalRPM;
}
