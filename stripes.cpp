#include "canvas.h"

class Stripes : public CanvasEffect {

  public:
    Stripes() : CanvasEffect() { }
    
    void start() override {
      setPalette( CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Green )); 
    }
  
    void tick(unsigned long t) {
      Serial.println (t);

      for(int col = 0; col < width; col++) {
        for( int row = 0; row < height; row++) {
          pixel(col, row) = (col % 3) * 127; // ? 0 : 255;
        }
      }
    }
  
};


