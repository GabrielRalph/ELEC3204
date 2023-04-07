unsigned long time;

class EWMA{
  private:
    float value;
    float lambda;
    bool init;

  public:
    EWMA(float l){
      init = false;
      lambda = 1/l;
    }

    void updateValue(float v) {
      if (!init) {
        value = v;
        init = true;
      }

      float dv = lambda * (v - value);
      value += dv;
      return dv;
    }

    void setLambda(float l){
      lambda = l;
    }

    float getValue(){
      return value;
    }
};

class RotaryEncoder {
  private:
    int pinA;
    int pinB;
    int state;
    time lastTime;
    EWMA velocity;
    int position;         // I
    float acceleration;   // D

    float getTimeDelta(){
      time now = micros();
      float dt = 0.000001 * ((float)(now - lastTime)); // seconds
      if (lastTime > now) dt = 0.000001 * ((float)(now));
      lastTime = now;
      return dt;
    }

    void interruptHandler() {
      float dt = getTimeDelta();
      int a = digitalRead(pinA);
      int b = digitalRead(pinB);
      int newState = (a << 1) | b;
      float di = 0;
      if ((state == 0 && newState == 1) ||
          (state == 1 && newState == 3) ||
          (state == 3 && newState == 2) ||
          (state == 2 && newState == 0)) {
        di = -1;
      } else if ((state == 0 && newState == 2) ||
                 (state == 2 && newState == 3) ||
                 (state == 3 && newState == 1) ||
                 (state == 1 && newState == 0)) {
        di = 1;
      }

      position += di;
      acceleration = velocity.updateValue(di/dt)/dt;

      state = newState;
    }

  public:
    RotaryEncoder(int _pinA, int _pinB) {
      pinA = _pinA;
      pinB = _pinB;
      state = 0;
      position = 0;
      velocity =  0;
      acceleration = 0;
      lastTime = 0;
      velocity = new EWMA(1/4);
      pinMode(pinA, INPUT);
      pinMode(pinB, INPUT);
      attachInterrupt(digitalPinToInterrupt(pinA), this->interruptHandler, CHANGE);
      attachInterrupt(digitalPinToInterrupt(pinB), this->interruptHandler, CHANGE);
    }

    // position in increments
    int getPosition() {
      return position;
    }

    // inc / s
    float getSpeed() {
      return 1/dt;
    }

    // inc / s / s
    float getAccel(){
      return a;
    }

};
