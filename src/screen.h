#ifndef screen_h
#define screen_h

//include Adafruit libraries for screen
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <TouchScreen.h>


class screenUtils { //base class for drawables that are not final readouts (ie masks)
  public:
    virtual void draw(); //function to draw the drawable
};

class screenLoader { //data about screen
//TODO: MAKE THIS SUCK LESS
  public:
    static Adafruit_ILI9341 screen;
    screenLoader(uint16_t background); 
    screenLoader(const screenLoader&);
    screenLoader();
    uint16_t backgroundColour;
};

class inverseQuartCircle : public screenUtils { //draws squares of size radiusXradius with a circle cut out
  //inverseQuartCircle = IQC henceforth
  public:
    void draw(); //function to draw the IQC
    inverseQuartCircle(int _x, int _y, int _radius, unsigned int _colour, bool _top, bool _left, const screenLoader& _loader); //constructor
  private:
    bool left; //these two bools control where the origin of the circle cutout is (ie top left corner)
    bool top;
    int radius; //radius of circle
    int x; //x position of circle
    int y; //y position of circle
    uint16_t colour; //colour of IQC
    //TODO: MAKE THIS (\|/) a reference/pointer
    screenLoader loader; //private (reference) to 'global' screen data class instance)
};

class dataOutput {
  public:
    void setValue(float value);
    void setMaxValue(float value);
    void setMinValue(float value);
    void setLabel(String label);
  protected:
    virtual void recalculateValueViz() = 0;
    String label;
    float value;
    float oldValue;
    float maxValue;
    float minValue;

};

class screenObject { //tools extended by all on-screen objects
  public:
    virtual void erase() = 0; //erase object
    virtual void redraw() = 0; //erase and redraw object (for most objects, only if value has changed)
    void setScale(int scale); //set scale of object
    void setXPos(int xPos);//set x position of object
    void setYPos(int yPos); //set y position of object
    void setColour(uint16_t colour); //set colour of object
  protected:
    screenLoader loader;
    virtual void scaleAdjust() = 0;
    screenObject *getSelfReference(); //get a screenObject* from an instance of a derived class
    int scale; //scale of object
    int xPos; //x position of object
    int yPos; //y position of object
    uint16_t colour; //colour of object
};
 
 //TODO: Fully integrate screenObject into this
class roundDial : public screenObject, public dataOutput{ //a semi-round dial filled from lower-limit to value
  public:
    void redraw();// redraw object
    void erase(); //erase object
    void setOutlineColour(uint16_t colour); //set colour of object's outline
    void draw(); //draw object with current parameters
    void setAccent(uint16_t colour); //set secondary colour
    void setLineColour(uint16_t colour); //set colour of lines
    // \|/ construct with given parameters
    roundDial(screenLoader loader, String label, int _xPos, int _yPos, int _scale, float value, float minValue, float maxValue, uint16_t colour, uint16_t accent, uint16_t lineColour, uint16_t textColour);

  private:
    void recalculateValueViz(); //interface with dataOutput base class
    void scaleAdjust() {} //not necessary for this dial - null function
    uint16_t lineColour; //colour of lines in object
    uint16_t accent; //secondary colour of object
    void findValueRadians(); //find the number of radians which the value occupies
    const int maxDegrees = 225; //max number of degrees of the dial (has no effect)
    const float maxRadians = 1.25; //max number of radians of the dial
    float valueRadians; //number of radians currently occupied by the value
    void recalculateVars(); //recalculate scale and radiuses
    int radius; //outer radius of dial derived from scale
    int innerRadius; //inner radius of dial derived from scale
    uint16_t textColour; //colour of label
};

class linearMeter : public screenObject { //a straight meter, filled from the left

  //TODO:FINISH LINEAR METER

  public:
    void redraw(); //redraw object
    void erase(); //erase object
  private:
    int ratio; //ratio of length to width (x length : 1 width) * scale
    int oldValue; //value from previous draw for selective redraw
    String label; //label (name) of the dial
    float value; //current value (with original mapping)
    uint16_t lineColour; //colour of lines in object
    uint16_t accent; //secondary colour of object
    float minValue; //min value of the dial
    float maxValue; //max value of the dial
};

namespace eraseManager { //code to manage automatic erase and redraw of all objects

  class screenObjectArray { //maintains an array of *POINTERS TO* some screenObject objects
    public:
      screenObject * first; //ptr to first item in array
      int length; //length of array
      void addObject(screenObject* ptr); //add a new object to the array
  };

  void redraw(screenObjectArray & array); //redraw all objects (normally only if value has changed)
  
  void erase(screenObjectArray & array); //erase all objects in array from screen

}




#endif
