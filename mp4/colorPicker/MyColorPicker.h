#ifndef MyColorPicker_H
#define MyColorPicker_H

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  MyColorPicker(Point center, unsigned radius);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  Point center;
  unsigned radius;

};

#endif
