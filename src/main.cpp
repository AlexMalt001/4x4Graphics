//include Adafruit libraries for screen
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <TouchScreen.h>


//include my external files
#include "serialProcess.h" //manages serial setup and interface with reciever
#include "screen.h" //manages interface with screen
#include "load.h" //contains details on variables, etc


#define BLACK    0x0000
#define WHITE    0xFFFF

//config for screen - see Adafruit's documentation
#define TFT_CS 10//lines 18+19 set pins for screen
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC); //define a screen object
Adafruit_ILI9341 screenLoader::screen = tft; //tell the screen loader what screen to use

//TODO: CHANGE THESE TO NAMESPACES
//load in external objects
pins pins;
serialProcess io;
dataProcess data;
screenLoader loader;

void setup() {
  load::modeSet(); //set pin modes CURRENTLY REDUNDANT
  load::serialSetup(); //configure serial comms
  roundDial test(loader, "POT1", 0,0,30,250,0,1024,BLACK,BLACK,BLACK,BLACK);
  test.erase();
}

void loop() {
  //TODO: SERIAL SEND CLOCK
  //TODO: COMMAND HANDLER
  eraseManager::redraw(load::objectArray);
}
