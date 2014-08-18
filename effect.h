#ifndef Effect_h
#define Effect_h

#include "FastLED.h"
#include "grids.h"
#include "palettes.h"

class Animation {
  protected:
    virtual void tick(unsigned long t) { }
    unsigned long ticks;
    CRGBPalette16 palette;
    virtual CRGB atPixel(int x, int y) { }

  public:
    void clear();
    int width, height;

    Animation(int width, int height) : width(width), height(height) {
    }
    
    virtual void start() { };
    virtual void loop(unsigned long t) {
      tick(ticks++);
    };

    CRGB at(int x, int y) { 
      // Use an X position of -99 to turn on LEDs (makes it easy to identify single pixels)
      // Other out-of-bounds values will return black
      if (x == -99)
        return CRGB::White;
      else if (x < 0 || x >= 255)
        return CRGB::Black;
      else if (y < 0 || y > 255)
        return CRGB::Black;

      // OK, delegate to 
      return atPixel(x,y);        
    };

    void setPalette(CRGBPalette16 pal) {
      this->palette = pal;
    }
      
 };


// Effect that directly drives a strand of LEDs
class LEDEffect : public Animation {
  protected:
    void clear();
    CRGB *leds;
  
    CRGB atPixel(int x, int y) {
      if (x < 0 || x >= width)
        return CRGB::Black;
      if (y < 0 || y >= width)
        return CRGB::Black;
      return leds[y * width + x];
    }

  public:
    LEDEffect(CRGB *leds, int width, int height = 1) : leds(leds), Animation(width, height) {
    }

};



#define CANVAS_WIDTH 25
#define CANVAS_HEIGHT 25

// Effect that drives a virtual matrix of palette values
class PaletteEffect : public Animation {

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

    CRGB atPixel(int x, int y) {
      uint8_t color = canvas( x , y );
      
      return ColorFromPalette( this->palette, color);
    }
  
  public:
    PaletteEffect() : Animation(CANVAS_WIDTH, CANVAS_HEIGHT) {}
    
};

#endif

