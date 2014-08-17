/*

// Timer stuff (Oszillators)
 
#define TIMERS 5
struct timer {unsigned long takt; unsigned long lastMillis; unsigned long count; int delta; byte up; byte down;};
// Always set the following number right - If you set a timer,
// you have to set sensfull limits in the setup part
timer multiTimer[TIMERS];

int InitTimers() {
  for (int i = 0; i < TIMERS; i++) 
    multiTimer[i].delta = 1;
 
  // set range (up/down), speed (takt=ms between steps) and starting point of all oszillators
 
  multiTimer[0].takt=  31;     //x1
  multiTimer[0].up = CANVAS_WIDTH - 1;
  multiTimer[0].down = 0;
  multiTimer[0].count = 0;
 
  multiTimer[1].takt=  37;     //y1
  multiTimer[1].up = CANVAS_HEIGHT - 1;
  multiTimer[1].down = 0;
  multiTimer[1].count = 0;
 
  multiTimer[2].takt=  15;      //color
  multiTimer[2].up = 255;
  multiTimer[2].down = 0;
  multiTimer[2].count = 0;
 
  multiTimer[3].takt=  45;     //x2  
  multiTimer[3].up = CANVAS_WIDTH - 1;
  multiTimer[3].down = 0;
  multiTimer[3].count = 0;
 
  multiTimer[4].takt=  57;     //y2
  multiTimer[4].up = CANVAS_HEIGHT - 1;
  multiTimer[4].down = 0;
  multiTimer[4].count = 0;
  
  return 0;
}

// counts all variables with different speeds linear up and down
void UpdateTimers()
{
  static int t = InitTimers();
  
  unsigned long now=millis();
  for (int i=0; i < TIMERS; i++)
  {
    while (now-multiTimer[i].lastMillis >= multiTimer[i].takt)
    {
      multiTimer[i].lastMillis += multiTimer[i].takt;
      multiTimer[i].count = multiTimer[i].count + multiTimer[i].delta;
      if ((multiTimer[i].count == multiTimer[i].up) || (multiTimer[i].count == multiTimer[i].down))
      {
        multiTimer[i].delta = -multiTimer[i].delta;
      }
    }
  }
}

// fade the image buffer arround
// x, y: center   r: radius   dimm: fade down
void Spiral(int x,int y, int r, byte dimm) {  
  for(int d = r; d >= 0; d--) {
    for(int i = x-d; i <= x+d; i++) {
       canvas[i][y-d] = scale8(canvas[i+1][y-d] + canvas[i][y-d], dimm);
    }
    for(int i = y-d; i <= y+d; i++) {
       canvas[x+d][i] = scale8(canvas[x+d][i+1] + canvas[x+d][i], dimm);
    }
    for(int i = x+d; i >= x-d; i--) {
       canvas[i][y+d] = scale8(canvas[i-1][y+d] + canvas[i][y+d], dimm);
    }
    for(int i = y+d; i >= y-d; i--) {
       canvas[x-d][i] = scale8(canvas[x-d][i-1] + canvas[x-d][i], dimm);
    }
  }
}
 
void Funky() {
  static long int last = millis();
  
  // manage the Oszillators
  UpdateTimers();

  if (millis() > last + 500) { 
    // draw just a line defined by 5 oszillators
    Line(
      multiTimer[3].count,  // x1
      multiTimer[4].count,  // y1
      multiTimer[0].count,  // x2
      multiTimer[1].count,  // y2
      multiTimer[2].count); // color
      
    last = millis();
  }
 
  // manipulate the screen buffer
  // with fixed parameters (could be oszillators too)
  // center x, y, radius, scale color down
  // --> affects always a square with an odd length
  //Spiral(3,3,3,128);
  //Spiral(4,1,2,128);
 
  // increase the contrast
  DimAll(170);
}  

// Bresenham line
void Line(int x0, int y0, int x1, int y1, byte color)
{
  int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
  int err = dx+dy, e2;
  for(;;){  
    canvas[x0][y0] = color;

    if (x0==x1 && y0==y1) break;
    e2 = 2*err;
    if (e2 > dy) { err += dy; x0 += sx; }
    if (e2 < dx) { err += dx; y0 += sy; }
  }
}



void DimAll(uint8_t value)
{
  for(int col = 0; col < CANVAS_WIDTH; col++) {
    for( int row = 0; row < CANVAS_HEIGHT; row++) {
      canvas[col][row] = scale8(canvas[col][row], value);
    }
  }
}
*/

