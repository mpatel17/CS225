#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "mp1.h"
#include <string>
#include <math.h>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  PNG png;
  png.readFromFile(inputFile);

  unsigned width = png.width();
  unsigned height = png.height();

  PNG result = PNG(width, height);

  for(unsigned x = 0; x < width; x++) {
    for(unsigned y = 0; y < height; y++) {
      HSLAPixel *pixelOut = result.getPixel(width - x - 1, height - y - 1);
      HSLAPixel *pixelIn = png.getPixel(x, y);
      *pixelOut = *pixelIn;
    }
  }

  result.writeToFile(outputFile);

}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);

  for(unsigned x = 0; x < width; x++) {
    for(unsigned y = 0; y < height; y++) {
      HSLAPixel* pixel = png.getPixel(x, y);
      pixel->s = 1;
      pixel->l = .5;
      pixel->a = 1;

      double dist = sqrt((x*x) + (y*y));
      double center = height*sqrt(2) / 2;
      pixel->h = -0.63*fabs(dist - center) + 360;

    }
  }

  return png;
}
