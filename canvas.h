#ifndef Canvas_h
#define Canvas_h

#include "effect.h"
#include "grids.h"
#include "palettes.h"

#define CANVAS_WIDTH 25
#define CANVAS_HEIGHT 25

class CanvasEffect : public Animation {

  protected:
    PaletteGridMap<CANVAS_WIDTH, CANVAS_HEIGHT, 255, 255> canvas;
    uint8_t rotation = 0;

    // Set a pixel
    uint8_t& pixel(int x, int y) {
      return canvas.pixel(x,y);
    }
  
    void rotate(uint8_t rot) {
      rotation = rot;
      canvas.rotate(rotation);
    }
  
  public:
    CanvasEffect() : Animation(CANVAS_WIDTH, CANVAS_HEIGHT) {}

    CRGB at(int x, int y) {
      // Use an X position of -99 to turn on LEDs (makes it easy to identify single pixels)
      // Other out-of-bounds values will return black
      if (x == -99)
        return CRGB::White;
      else if (x < 0 || x >= 255)
        return CRGB::Black;
      else if (y < 0 || y > 255)
        return CRGB::Black;
        
      uint8_t color = canvas( x , y );
      
      return ColorFromPalette( this->palette, color);
    }
    
};

#endif
