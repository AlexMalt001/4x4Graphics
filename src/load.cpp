
#include "Arduino.h"
#include "load.h"

int throttle = A0;
int steer = A1;
int thTrim = A3;
int stTrim = A4;
//int stDR = A8;

int thSwitch = 22;
int stSwitch = 23;

int ledR = 24;
int ledG = 25;

void load :: modeSet() {
  pinMode(throttle, INPUT);
  pinMode(steer, INPUT);
  pinMode(thTrim, INPUT);
  pinMode(stTrim, INPUT);
//  pinMode(stDR, INPUT);

  pinMode(thSwitch, INPUT);
  pinMode(stSwitch, INPUT);

  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  
}

void load :: serialSetup() {
  Serial.begin(9600);
//  Serial1.begin(115200);
}


