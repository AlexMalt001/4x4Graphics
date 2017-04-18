#include <Adafruit_ILI9341.h>

#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include <TouchScreen.h>

#include "Arduino.h"

#include "screen.h"
#include "load.h"


void dataOutput::setValue(float newValue) {
  value = newValue;
  recalculateValueViz();
}

void dataOutput::setMaxValue(float newMaxValue) {
  maxValue = newMaxValue;
  recalculateValueViz();
} 

void dataOutput::setLabel(String newLabel) {
  label = newLabel;
}

void dataOutput::setMinValue(float newMinValue) {
  minValue = newMinValue;
  recalculateValueViz();
}


void eraseManager::redraw(screenObjectArray & array) {
  for (int i=0; i <= array.length; i++) {
    screenObject &obj  = *(array.first + i);
    obj.redraw();
  }
}

void eraseManager::erase(screenObjectArray & array) {
  for (int i=0; i <= array.length; i++) {
    screenObject &obj  = *(array.first + i);
    obj.erase();
  }
}


void eraseManager::screenObjectArray::addObject(screenObject * ptr) {
  length++;
  first = realloc(first, length);
  *(first+length) = *ptr;
}


screenLoader :: screenLoader (uint16_t background) {
  backgroundColour = background;
}

screenLoader :: screenLoader(const screenLoader& _loader) {
  backgroundColour = _loader.backgroundColour;
}

screenLoader::screenLoader() {

}

inverseQuartCircle :: inverseQuartCircle (int _x, int _y, int _radius, unsigned int _colour, bool _top, bool _left, const screenLoader& _loader) {
  x=_x;
  y=_y;
  radius = _radius;
  colour = _colour;
  top = _top;
  left = _left;
  loader = _loader;
}

void linearMeter::erase() {
  //TODO: ADD ERASE FUNCTION FOR LINEAR METER
}

void roundDial::erase() {
  loader.screen.fillRect(xPos, yPos, 2*radius, 2*radius, loader.backgroundColour);
}

void linearMeter::redraw() {
  //TODO: ADD REDRAW CODE
}

void roundDial::redraw() {
  if (value == oldValue) {
    return;
  }
  erase();
  draw();
}


roundDial :: roundDial (screenLoader _loader, String _label, int _xPos, int _yPos, int _scale,
                              float _value, float _minValue, float _maxValue, uint16_t _colour, uint16_t _accent, uint16_t _lineColour, uint16_t _textColour){
  loader = _loader;
  xPos = _xPos;
  yPos = _yPos;
  scale = _scale;
  value = _value;
  maxValue = _maxValue;
  minValue = _minValue;
  colour = _colour;
  accent = _accent;
  lineColour = _lineColour;
  label = _label;
  textColour = _textColour;
  load::objectArray.addObject(this);
  recalculateVars();
  findValueRadians();
}

void roundDial::recalculateVars() { //defines how scale affects dimensions of dial
  radius = scale;
  innerRadius = radius-3*(radius/8);
}

void roundDial::setAccent(uint16_t _accent) {
  accent = _accent;
}

void roundDial::setLineColour(uint16_t _lineColour) {
  lineColour = _lineColour;
}

void roundDial::draw() { //draws an on screen object of type roundDial on screen

  if(value == oldValue) {//does not redraw if value is the same
    return;
  }

  oldValue = value;
  loader.screen.fillCircle(xPos+radius, yPos+radius, radius-1, accent); //fills 'accent circle'


  if(valueRadians < maxRadians/5) { //first of 3 triangles that cut out the readout bar
    float topangle = HALF_PI-(valueRadians*PI);
    int ypoint0 = (radius/sin(topangle))*sin(valueRadians*PI);
    loader.screen.fillTriangle(xPos,yPos+radius,xPos,(yPos+radius)-ypoint0,xPos+radius,yPos+radius,colour);
    //Serial.println("y point: " + String(ypoint0) + " top angle: " + String(topangle/PI));
    inverseQuartCircle topLeft(xPos,yPos,radius,loader.backgroundColour,true,true,loader);
    topLeft.draw();
  }else {

    loader.screen.fillTriangle(xPos,yPos+radius,xPos,yPos,xPos+radius,yPos+radius,colour);

    if(valueRadians < 3*(maxRadians/5)) {
      int thirdsidelength = sqrt(2*(pow(radius,2)));
      //Serial.println(thirdsidelength);
      float bottomangle = (valueRadians-(maxRadians/5))*PI;
      float thirdangle = (PI-bottomangle)-(HALF_PI/2);
      int xpoint3 = (thirdsidelength/sin(thirdangle))*sin(bottomangle);
      loader.screen.fillTriangle(xPos+radius,yPos+radius,xPos,yPos,xPos+xpoint3,yPos,colour);
      inverseQuartCircle topLeft(xPos,yPos,radius,loader.backgroundColour,true,true,loader);
      topLeft.draw();
      if(valueRadians > 2*(maxRadians/5)) {
        inverseQuartCircle topRight(xPos+radius,yPos,radius ,loader.backgroundColour,true,false,loader);
        topRight.draw();
      }
    } else { //also fulfils conditions for third triangle
      loader.screen.fillTriangle(xPos+radius,yPos+radius,xPos,yPos,xPos+(2*radius),yPos, colour);
      inverseQuartCircle topLeft(xPos,yPos,radius,loader.backgroundColour,true,true,loader);
      topLeft.draw();

      int firstsidelength = sqrt(2*(pow(radius,2)));
      float sideangle = (valueRadians-(3*(maxRadians/5)))*PI;
      float thirdangle = (PI-sideangle)-(HALF_PI/2);
      int ypoint3 = (firstsidelength/sin(thirdangle))*sin(sideangle);;
      loader.screen.fillTriangle(xPos+radius,yPos+radius,xPos+(2*radius),yPos,xPos+(2*radius),yPos+ypoint3,colour);

      inverseQuartCircle topRight(xPos+radius,yPos,radius ,loader.backgroundColour,true,false,loader);
      topRight.draw();

      if(valueRadians > 4*(maxRadians/5)) {
        inverseQuartCircle bottomRight(xPos+radius,yPos+radius,radius,loader.backgroundColour,false,false,loader);
        bottomRight.draw();
      }
  }
  }

  loader.screen.fillCircle(xPos+radius, yPos+radius, innerRadius, loader.backgroundColour);//'remove' inside of dial (fill with background)

  //outlines
  loader.screen.drawCircle(xPos+radius, yPos+radius, innerRadius,lineColour);
  loader.screen.drawCircle(xPos+radius, yPos+radius, radius-1,lineColour);

  //remove wierd anomaly at bottom
  loader.screen.drawFastHLine(xPos, yPos+(2*radius), 2*radius, loader.backgroundColour);

  //cut out bottom
  loader.screen.fillRect(xPos,yPos+radius,radius,radius,loader.backgroundColour);
  loader.screen.fillTriangle(xPos+radius, yPos+(radius*2), xPos+radius, yPos+radius, xPos+(2*radius), yPos+(2*radius), loader.backgroundColour);

  //outlines
  //make fastHLine
  loader.screen.drawLine(xPos, yPos+radius, xPos+(radius-innerRadius), yPos+radius, lineColour);
  int innerxyOffset = sqrt((pow(innerRadius,2))/2);
  int outerxyOffset = sqrt((pow(radius,2))/2);
  loader.screen.drawLine(xPos+radius+innerxyOffset, yPos+radius+innerxyOffset, xPos+radius+outerxyOffset, yPos+radius+outerxyOffset, lineColour);

  //value label
  loader.screen.setCursor(xPos+2, yPos+radius+4);
  loader.screen.setTextColor(lineColour); //TODO: ADD CUSTOMISABLE TEXT COLOUR
  int textSize = (radius-innerRadius)/7; //i liked this size
  loader.screen.setTextSize(textSize);
  loader.screen.print(round(value)); //TODO: ADD OPTION FOR PERCENTAGE?
  loader.screen.drawRect(xPos, yPos+radius+2, 6+(String(round(maxValue))).length()*(5*textSize)+String(round(value)).length(),2+(textSize*8), lineColour);

  //name label
  loader.screen.setCursor(xPos + ((6+(String(round(maxValue))).length()*(5*textSize)+String(round(value)).length())/2), yPos+radius+6+(textSize*8)); //placing it just below value label
  loader.screen.setTextSize(textSize/2);
  loader.screen.print(label);
  int xposoffset =  6+(String(round(maxValue))).length()*(5*textSize)+String(round(value)).length();
  loader.screen.drawRect((xPos + (xposoffset/2))-2, yPos+radius+5+(textSize*8), ((6+(String(round(maxValue))).length()*(5*textSize)+String(round(value)).length())/2)+1, (textSize)*5, lineColour);
}

void roundDial::recalculateValueViz() {
  findValueRadians();
}

void roundDial::findValueRadians() { //finds number of degrees for the value
  valueRadians = (value/maxValue)*maxRadians;
}

void screenObject::setXPos(int in) { //sets scale of an object
  xPos = in;
}

void screenObject::setYPos(int in) { //sets scale of an object
  yPos = in;
}


void screenObject::setColour(uint16_t in) { //sets scale of an object
  colour = in;
}

void screenObject::setScale(int in) { //sets scale of an object
  scale = in;
  scaleAdjust();
}

void inverseQuartCircle :: draw() {
  int radiusSquared = pow(radius, 2);
  if(left) { //checks if drawing vertical or horizontal
    if(!top) {

      int currentx = x+radius;
      int i = 0;

      while (x<=currentx) {
        int lowerposy = sqrt(radiusSquared-pow(i,2));
        loader.screen.drawFastVLine(currentx, y+lowerposy, radius-lowerposy, colour);
        currentx = currentx-1;
        i=i+1;
      }

    } else {

      int currentx = x+radius;
      int i =0;

      while (x<=currentx) {
        int lowerposy = sqrt(radiusSquared-pow(i,2));
        int len = (radius-lowerposy);
        loader.screen.drawFastVLine(currentx,y,len,colour);
        i=i+1;
        currentx = currentx-1;
      }
    }

  }else {
    if(top) {
      int maxX = x+radius;
      int i = 0;
      int currentx=x;
      while (currentx<=maxX) {

        int lowerposy = sqrt(radiusSquared-pow(i,2));
        loader.screen.drawFastVLine(currentx,y,radius-lowerposy,colour);
        currentx++;
        i++;
      }
    }else {

      int maxX = x+radius;
      int i = 0;
      int currentx = x;
      while (currentx<=maxX) {
        int lowerposy = sqrt(radiusSquared-pow(i,2));
        loader.screen.drawFastVLine(currentx,y+lowerposy,radius-lowerposy,colour);
        currentx++;
        i++;
      }
    }
  }
}
