#include <cmath>

#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

MyColorPicker::MyColorPicker(Point c, unsigned r) {
  center = c;
  radius = r;
}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  double h = 300;
  double dx = x - center.x;
  double dy = y - center.y;
  double dist = sqrt((dx * dx) + (dy * dy));

  double s = 1.0;
  double l = 0.5;
  double a = x/radius;
  return HSLAPixel(h, s, l, a);
}
