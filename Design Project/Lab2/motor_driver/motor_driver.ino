#include "PWM.cpp"

PWM* m1;

void setup() {
  m1 = &PWM(10, 9);
  // put your setup code here, to run once:

}

float theta = 0;
void loop() {
  float dc = 0.1 + 0.9 * 0.5 * (cos(theta) + 1);
  m1->setDutyCycle((int) (dc * 100));
  delay(20);
  theta += 0.01;
}
