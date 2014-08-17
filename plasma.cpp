#include "canvas.h"

class Plasma : public CanvasEffect {

  public:
    Plasma() : CanvasEffect() { }
  
    void start() {
      setPalette( CloudColors_p ); 
    }
  
    void tick(unsigned long t) {
      unsigned long frame = t;
  
      for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
          int16_t v = 0;
          uint16_t wibble = sin8(frame);
  
          v += sin16(x * wibble * 8 + frame);
          v += cos16(y * (128 - wibble) * 4 + frame);
          v += sin16(y * x * cos8(-frame) / 2);
  
          pixel(x,y) = (v >> 8) + 127;
        }
      }
  
      rotate(rotation++);    
    }

};

