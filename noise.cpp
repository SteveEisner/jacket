#include "canvas.h"

class Noise : public CanvasEffect {

  public:
    Noise() : CanvasEffect() { }
    
    void start() override {
      setPalette( Bands_p ); //CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Green )); 
    }
  
    void tick(unsigned long t) {
      for(int col = 0; col < width; col++) {
        for( int row = 0; row < height; row++) {
          uint8_t s = sin8(col * 3 + t);
          uint8_t c = cos8(row * 2 + t);
          
          pixel(col, row) = qadd8(s, c);
        }
      }
        
      rotate(rotation+2);    
    }
  
};


