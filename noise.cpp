#include "canvas.h"

class Noise : public CanvasEffect {

  public:
    Noise() : CanvasEffect() { }
    
    void start() override {
      setPalette( CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Green )); 
    }
  
    void tick(unsigned long t) {
      for(int col = 0; col < width; col++) {
        for( int row = 0; row < height; row++) {
          uint8_t s = sin8(col * 3 + t/20);
          uint8_t c = cos8(row * 2 + t/20);
          
          pixel(col, row) = qadd8(s, c);
        }
      }
    }
  
};


