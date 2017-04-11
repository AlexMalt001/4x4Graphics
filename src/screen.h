#ifndef screen_h
#define screen_h

//include Adafruit libraries for screen
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <TouchScreen.h>


class screenUtils {

};

class screenLoader { //data about screen
  public:
    static Adafruit_ILI9341 screen;
    screenLoader(uint16_t background);
    screenLoader(const screenLoader&);
    screenLoader();
    uint16_t backgroundColour;
};

class inverseQuartCircle : public screenUtils {
  public:
    void draw();
    inverseQuartCircle(int _x, int _y, int _radius, unsigned int _colour, bool _top, bool _left, const screenLoader& _loader);
  private:
    bool left;
    bool top;
    int radius;
    int x;
    int y;
    uint16_t colour;
    screenLoader loader;
};



class screenObject { //tools extended by all on-screen objects
  public:
    virtual void erase();
    virtual void redraw();
    void setScale(int in);
    void setXPos(int in);
    void setYPos(int in);
    void setColour(uint16_t colour);
  protected:
    screenObject *getSelfReference();
    int scale;
    int xPos;
    int yPos;
    uint16_t colour;
};

class roundDial : public screenObject{ //a semi-round dial filled from lower-limit to value
  public:
    void redraw();
    void erase();
    void setOutlineColour(uint16_t colour);
    void setScale(int in);
    void draw();
    void setLabel(String in);
    void setValue(float value);
    void setMaxValue(float maxValue);
    void setMinValue(float minValue);
    void setAccent(uint16_t colour);
    void setLineColour(uint16_t colour);
    roundDial(screenLoader loader, String label, int _xPos, int _yPos, int _scale, float value, float minValue, float maxValue, uint16_t colour, uint16_t accent, uint16_t lineColour, uint16_t textColour);

  private:
    int oldValue;
    uint16_t lineColour;
    uint16_t accent;
    float minValue;
    float maxValue;
    void findValueRadians();
    int maxDegrees = 225;
    float maxRadians = 1.25;
    float valueRadians;
    void recalculateVars();
    screenLoader loader;
    String label;
    float value;
    int radius;
    int innerRadius;
    uint16_t textColour;
};

class linearMeter : public screenObject {

  //TODO:FINISH LINEAR METER

  public:
    void redraw();
    void erase();
  private:
    int oldValue;
    String label;
    float value;
    uint16_t lineColour;
    uint16_t accent;
    float minValue;
    float maxValue;
};

namespace eraseManager {

  class screenObjectArray {
    public:
      screenObject * first;
      int length;
      void addObject(screenObject* ptr);
  };

  void redraw(screenObjectArray & array);
  
  void erase(screenObjectArray & array);

}




#endif
