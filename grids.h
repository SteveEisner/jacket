#ifndef Grids_h
#define Grids_h

#include "FastLED.h"

// base GridMap class.  Allows from mapping from an X x Y grid of
// T values to an MX x MY grid of T values (where
// MX and MY are greater than X and Y respectively), using linear
// interpolation to fill in the gaps.  Optionally allows for rotating
// around the center point.  Subclasses should provide an implementation
// for the interpolate method, appropriate to the type of data being mapped
template<int X, int Y, int MX, int MY, class T> class AbstractGridMap {
  int revcosval,revsinval;
  uint8_t angle;

  inline void rtpt_rev(int & x, int & y) {
    if(angle) {
      int _x = x - MX/2;
      int _y = y - MX/2;
      x = (_x * revcosval) - (_y * revsinval);
      y = (_x * revsinval) + (_y * revcosval);
      x /= 256;
      y /= 256;
      x += (MX/2);
      y += (MX/2);
    }
  }

public:
  T m_Data[X][Y];

public:
  AbstractGridMap() { 
    rotate(0); 
  }

  void rotate(uint8_t rotate) {
    Serial.print("Angle ");
    Serial.println(rotate);
    angle=rotate;
    revcosval = 2 * ((int)cos8(256-angle)-128);
    revsinval = 2 * ((int)sin8(256-angle)-128);
  }

  T* operator[](int x) { 
    return m_Data[x]; 
  }
  T& pixel(int x, int y) {
    return m_Data[x][y];
  }

  virtual T interpolate(int bx, int by, int fx, int fy) = 0;

  T operator()(int x, int y) {
    // reverse rotate x/y
    rtpt_rev(x,y);

    // compute inner grid point
    int bx = (x * (X-1))/MX;
    int by = (y * (Y-1))/MY;

    // get the delta between the inner grid point and the requested location
    int dx = x - ((bx) * MX) / (X-1);
    int dy = y - ((by) * MY) / (Y-1);

    // convert the delta into a 0-255 frac8 value
    uint8_t fx = (dx*256) / MX;
    uint8_t fy = (dy*256) / MX;

    return interpolate(bx,by,fx,fy);
  }
};

template<int X, int Y, int MX, int MY> class CRGBGridMap : 
public AbstractGridMap<X,Y,MX,MY,CRGB> {
public:
  CRGBGridMap() { 
    this->rotate(0); 
  }

  virtual CRGB interpolate(int bx, int by, int fx, int fy) {
    CRGB x1(this->m_Data[bx][by].lerp8(this->m_Data[bx+1][by],fx));
    CRGB x2(this->m_Data[bx][by+1].lerp8(this->m_Data[bx+1][by+1],fx));
    return x1.lerp8(x2,fy);
  }
};

template<int X, int Y, int MX, int MY> class GridMap : 
public AbstractGridMap<X,Y,MX,MY,uint16_t> {
public:
  GridMap() { 
    memset(this->m_Data,0,sizeof(uint16_t)*X*Y); 
  }

  virtual uint16_t interpolate(int bx, int by, int fx, int fy) {
    uint16_t x1 = lerp16by8(this->m_Data[bx][by],this->m_Data[bx+1][by],fx);
    uint16_t x2 = lerp16by8(this->m_Data[bx][by+1], this->m_Data[bx+1][by+1],fx);

    return lerp16by8(x1,x2,fy);
  }
};


template<int X, int Y, int MX, int MY> class PaletteGridMap : 
public AbstractGridMap<X,Y,MX,MY,uint8_t> {
public:
  PaletteGridMap() { 
    memset(this->m_Data,0,sizeof(uint8_t)*X*Y); 
  }

  virtual uint8_t interpolate(int bx, int by, int fx, int fy) {
    uint8_t x1 = lerp8by8(this->m_Data[bx][by],this->m_Data[bx+1][by],fx);
    uint8_t x2 = lerp8by8(this->m_Data[bx][by+1], this->m_Data[bx+1][by+1],fx);

    return lerp8by8(x1,x2,fy);
  }
};

#endif
