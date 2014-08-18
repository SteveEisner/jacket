#include "canvas.h"

class Descent : public CanvasEffect {
  protected:
    int vertical = false;
    
  public:
    Descent(int vertical) : vertical(vertical), CanvasEffect() { }
  
    void start() {
      setPalette( RainbowColors_p ); 
    }
  
    void tick(unsigned long t) {
      uint8_t xx;
    
      for(int col = 0; col < width; col++) {
        for( int row = 0; row < height; row++) {
          if (vertical)
            xx = (uint8_t)(row * 3 * 256 / width);
          else
            xx = (uint8_t)(col * 3 * 256 / height);
          pixel(col, row) = xx + t * 4;
        }
      }
    }

};

