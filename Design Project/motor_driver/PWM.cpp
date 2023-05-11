#include "arduino.h"
class PWM {
  public:
    int PWMA;
    int PWMB;
    
    PWM(int a, int b) {
      PWMA = a;
      PWMB = b;
      
      pinMode(PWMA, OUTPUT);          // output PWMA to Q1
      pinMode(PWMB, OUTPUT);          // output PWMB to Q2
  
      analogWrite(PWMA, 0);          // let PWMA=0
      analogWrite(PWMB, 0);          // let PWMB=0
    
      TCCR1A = 0; // clear Timer1 control register TCCR1A & B
      TCCR1B = 0;
      TCNT1 = 0; // clear Timer1 counter register
    
      TCCR1B |= _BV(CS11); //set prescaler=8 by lettin the bit value of CS11=1 in register TCCR1B, so the clock frequency=16MHz/8=2MHz
      ICR1 = 100;//  phase correct PWM. PWM frequency determined by counting up 0-100 and counting down 100-0 in the input compare register (ICR1), so freq=200*0.5us=10kHz
    }

    void setDutyCycle(int dc){
      int temp = (int)dc;
      temp = constrain(temp,1,99);
    
      OCR1A = temp; //duty of PWM for pin9 is from output compare register A 
      TCCR1A |= _BV(COM1A1) | _BV(COM1A0); //set output to low level
    
      OCR1B = temp;//duty of PWM for pin10 is from output compare register B
      TCCR1A |= _BV(COM1B1); //set output to high level
    
      TCCR1B |= _BV(WGM13); //
      TCCR1A |= _BV(WGM11); //Set ICR1 phas correct mode
    }
};

