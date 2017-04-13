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



class screenObject { //tools extended by all on-screen objects
  public:
    virtual void erase(); //erase object
    virtual void redraw(); //erase and redraw object (for most objects, only if value has changed)
    void setScale(int in); //set scale of object
    void setXPos(int in);//set x position of object
    void setYPos(int in); //set y position of object
    void setColour(uint16_t colour); //set colour of object
  protected:
    screenObject *getSelfReference(); //get a screenObject* from an instance of a derived class
    int scale; //scale of object
    int xPos; //x position of object
    int yPos; //y position of object
    uint16_t colour; //colour of object
};

class roundDial : public screenObject{ //a semi-round dial filled from lower-limit to value
  public:
    void redraw();// redraw object
    void erase(); //erase object
    void setOutlineColour(uint16_t colour); //set colour of object's outline
    void setScale(int in); //set object's scale
    void draw(); //draw object with current parameters
    void setLabel(String in); //set string label of object
    void setValue(float value); //set value to display on object
    void setMaxValue(float maxValue); //set max value of the dial
    void setMinValue(float minValue); //set min value of the dial
    void setAccent(uint16_t colour); //set secondary colour
    void setLineColour(uint16_t colour); //set colour of lines
    // \|/ construct with given parameters
    roundDial(screenLoader loader, String label, int _xPos, int _yPos, int _scale, float value, float minValue, float maxValue, uint16_t colour, uint16_t accent, uint16_t lineColour, uint16_t textColour);

  private:
    int oldValue; //value from previous draw for selective redraw
    uint16_t lineColour; //colour of lines in object
    uint16_t accent; //secondary colour of object
    float minValue; //min value of the dial
    float maxValue; //max value of the dial
    void findValueRadians(); //find the number of radians which the value occupies
    const int maxDegrees = 225; //max number of radians of the dial
    const float maxRadians = 1.25;
    float valueRadians; //number of radians currently occupied by the value
    void recalculateVars(); //recalculate scale and radiuses
    // \|/ TODO: MAKE THIS A REFERENCE/POINTER in the global object class
    screenLoader loader; //private reference to 'global' loader object 
    String label; //label (name) of the dial
    float value; //current value (with original mapping)
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
    int oldValue; //value from previous draw for selective redraw
    String label; //label (name) of the dial
    float value;  //current value (with original mapping)
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
