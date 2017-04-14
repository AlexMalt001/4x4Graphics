
#include "Arduino.h"
#include "load.h"

//TODO: REMOVE FROM GRAPHICS
//TODO: MAKE CONSTANT
//pin settings
int throttle = A0; //pin set for INPUT from throttle pot
int steer = A1; //pin set for INPUT from steer pot 
int thTrim = A3; //pin set for INPUT of throttle trim setting from throttle trim pot
int stTrim = A4; //pin set for INPUT of steering trim setting from steering trim pot
//int stDR = A8;

int thSwitch = 22; //pin to read from 'th' switch
int stSwitch = 23; //pin to read from 'st' switch

int ledR = 24; //pin for red LED
int ledG = 25; //pin for green LED

void load :: modeSet() { //function to set pin modes
  //set control input pin modes
  pinMode(throttle, INPUT); 
  pinMode(steer, INPUT);
  pinMode(thTrim, INPUT);
  pinMode(stTrim, INPUT);
//  pinMode(stDR, INPUT);

  //set invert switch pin modes
  pinMode(thSwitch, INPUT);
  pinMode(stSwitch, INPUT);

  //set data LED pin modes
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  
}

void load :: serialSetup() { //initialise main serial connections
  Serial.begin(9600); //begin debug comms with computer
//  Serial1.begin(115200); //begin comms with main processor
}


