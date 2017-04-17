
#include "Arduino.h"
#include "load.h"


void load :: modeSet() { //function to set pin modes

//currently redundant for graphics processor
}

void load :: serialSetup() { //initialise main serial connections
  Serial.begin(9600); //begin debug comms with computer
//  Serial1.begin(115200); //begin comms with main processor
}


