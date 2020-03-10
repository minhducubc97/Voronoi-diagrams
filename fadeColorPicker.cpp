#include "fadeColorPicker.h"
#include <math.h>

fadeColorPicker::fadeColorPicker(double fade) { fadeFactor = fade; }

HSLAPixel fadeColorPicker::operator()(point p) {
  double dist =
      sqrt(pow((double)(p.x - p.c.x), 2) + pow((double)(p.y - p.c.y), 2));
  HSLAPixel ret;
  ret.h = p.c.color.h;
  ret.s = p.c.color.s;
  ret.l = p.c.color.l * pow(fadeFactor, dist);
  return ret;
}
