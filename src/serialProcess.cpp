
#include "Arduino.h"
#include "serialProcess.h"

void serialProcess :: sendVars(int th, int st) {
//  Serial1.println(st + "," + th);
}

int dataProcess :: processVars(int input, int upper, int lower, int deadzone, int upperPWM, int lowerPWM) {
  int range = upper - lower;
  int half = (((upper - lower)/2) + lower);
  int upperDZ = half + deadzone;
  int lowerDZ = half - deadzone;

  //if(upperDZ > input > lowerDZ) {
  //  input = half;
  //}
  int presult = input - lower;
  int presult2 = (presult*100) / (range);
  Serial.println(presult2);
  int result = (presult*(upperPWM-lowerPWM))+lowerPWM;
  return result;
}





