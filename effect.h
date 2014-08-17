#ifndef Effect_h
#define Effect_h

#include "FastLED.h"

class Animation {
  protected:
    virtual void tick(unsigned long t) { }

  public:
    void clear();
    int width, height;
    CRGBPalette16 palette;
    unsigned long ticks;

    Animation(int width, int height) : width(width), height(height) {
    }
    
    virtual void start() {
      Serial.println("Default start");
    };
    virtual void loop(unsigned long t) {
      tick(ticks++);
    };

    virtual CRGB at(int x, int y) {
      Serial.println("Default ()");
    };

    void setPalette(CRGBPalette16 pal) {
      this->palette = pal;
    }
      
 };

class Effect : public Animation {
  protected:
    void clear();
    CRGB *leds;
  
  public:
    Effect(CRGB *leds, int width, int height) : Animation(width, height) {
    }

    CRGB at(int x, int y) {
      return leds[y * width + x];
    }
    
};

#endif

