#ifndef load_h
#define load_h

#include "Arduino.h"
#include "screen.h"



namespace load {
    void modeSet();
    void serialSetup();
    eraseManager::screenObjectArray objectArray;
}

class pins {
  public:

  const int throttle = A0;
  const int steer = A1;
  const int thTrim = A3;
  const int stTrim = A4;
  const int stDR = A7;

  const int thSwitch = 22;
  const int stSwitch = 23;

  const int ledR = 24;
  const int ledG = 25;
};

#endif
