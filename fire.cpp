#include "canvas.h"

// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100 
#define COOLING  200

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 20

class Fire : public CanvasEffect {

  public:
    Fire() : CanvasEffect() { }

    void start() {
      setPalette( CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Orange ) ); 
    }
  
    void tick(unsigned long t) {
      // Step 1.  Cool down every cell a little
      for(int col = 0; col < width; col++) {
        for( int i = 0; i < height; i++) {
          pixel(col, i) = qsub8( pixel(col,i),  random8(0, ((COOLING * 10) / height) + 2));
        }
  
        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for( int k = height - 3; k > 2; k--) {
          pixel(col, k) = (pixel(col, k-1) + pixel(col, k-2) + pixel(col, k-2) ) / 3;
        }
        pixel(col, 2) = (pixel(col, 1) + pixel(col, 0) ) / 2;
        pixel(col, 1) = pixel(col, 0);
  
        // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
        if( random8() < SPARKING ) {
          canvas[col][0] = qadd8( canvas[col][0], random8(64,255) );
        }
  
        // Step 4. Some fire spreads side to side along the bottom
        canvas[col][0] = qadd8( canvas[col][0], qadd8(canvas[(col + width - 1) % width][0], canvas[(col + 1) % width][0]) / 10);
      }
    }
    

};


