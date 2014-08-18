#include "effect.h"

class Solid : public LEDEffect {
  protected:
    CRGB color;

    CRGB atPixel(int x, int y) {
      return color;
    }

  public:
    Solid(CRGB color) : color(color), LEDEffect((CRGB*)0, 1,1) { }
    
  
};


