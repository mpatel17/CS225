#include "Image.h"

using namespace cs225;

void Image::lighten() {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel& pixel = this->getPixel(x,y);
      pixel.l += 0.1;
      if(pixel.l > 1.0) {
        pixel.l = 1.0;
      }
    }
  }
}

void Image::lighten(double amount) {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel& pixel = this->getPixel(x,y);
      pixel.l += amount;
      if(pixel.l > 1.0) {
        pixel.l = 1.0;
      }
    }
  }
}

void Image::darken() {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel& pixel = this->getPixel(x,y);
      pixel.l -= 0.1;
      if(pixel.l < 0) {
        pixel.l = 0;
      }
    }
  }
}

void Image::darken(double amount) {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel& pixel = this->getPixel(x,y);
      pixel.l -= amount;
      if(pixel.l < 0) {
        pixel.l = 0;
      }
    }
  }
}

void Image::saturate() {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel& pixel = this->getPixel(x,y);
      pixel.s += 0.1;
      if(pixel.s > 1.0) {
        pixel.s = 1.0;
      }
    }
  }
}

void Image::saturate(double amount) {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel& pixel = this->getPixel(x,y);
      pixel.s += amount;
      if(pixel.s > 1.0) {
        pixel.s = 1.0;
      }
    }
  }
}

void Image::desaturate() {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel& pixel = this->getPixel(x,y);
      pixel.s -= 0.1;
      if(pixel.s < 0) {
        pixel.s = 0;
      }
    }
  }
}

void Image::desaturate(double amount) {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel& pixel = this->getPixel(x,y);
      pixel.s -= amount;
      if(pixel.s < 0) {
        pixel.s = 0;
      }
    }
  }
}

void Image::grayscale() {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel& pixel = this->getPixel(x,y);
      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees) {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel& pixel = this->getPixel(x,y);
      pixel.h += degrees;
      while(pixel.h > 360)
        pixel.h -= 360;
      while(pixel.h < 0)
        pixel.h += 360;
    }
  }
}

void Image::illinify() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel& pixel = this->getPixel(x,y);

      if(pixel.h < 113.5 || pixel.h > 293.5) {
        pixel.h = 11;
      }
      else {
        pixel.h = 216;
      }
    }
  }
}

void Image::scale(double factor) {
  unsigned int w = (unsigned int)(factor*width());
  unsigned int h = (unsigned int)(factor*height());

  PNG* image2 = new PNG(w,h);

  for(unsigned x = 0; x < w; x++) {
    for(unsigned y = 0; y < h; y++) {
      HSLAPixel& pixel2 = image2->getPixel(x,y);
      pixel2 = this->getPixel((unsigned int)(x/factor), (unsigned int)(y/factor));
    }
  }

  this->resize(w,h);

  for(unsigned x = 0; x < w; x++) {
    for(unsigned y = 0; y < h; y++) {
      this->getPixel(x,y) = image2->getPixel(x,y);
    }
  }

  delete image2;
}

void Image::scale(unsigned w, unsigned h) {
  double factor = 1.0*w/this->width();
  h = (unsigned) (height()*factor);

  PNG* image2 = new PNG(w,h);

  for(unsigned x = 0; x < w; x++) {
    for(unsigned y = 0; y < h; y++) {
      HSLAPixel& pixel2 = image2->getPixel(x,y);
      pixel2 = this->getPixel((unsigned int)(x/factor), (unsigned int)(y/factor));
    }
  }

  this->resize(w,h);

  for(unsigned x = 0; x < w; x++) {
    for(unsigned y = 0; y < h; y++) {
      this->getPixel(x,y) = image2->getPixel(x,y);
    }
  }

  delete image2;
}
