#include "canvas.h"

class Solid : public Effect {
  protected:
    CRGB color;

  public:
    Solid(CRGB color) : color(color), Effect((CRGB*)0, 1,1) { }
    
    CRGB at(int x, int y) {
      return color;
    }
  
};


