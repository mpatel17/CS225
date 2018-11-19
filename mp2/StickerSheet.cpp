#include "StickerSheet.h"



StickerSheet::StickerSheet(const Image & picture, unsigned m) {
  base = new Image();
  *base = picture;
  max = m;
  curr = 0;
  arrx = new int[m];
  arry = new int[m];
  pics = new Image*[m];

  for(unsigned i = 0; i < m; i++) {
    arrx[i] = 0;
    arry[i] = 0;
    pics[i] = NULL;
  }
}

StickerSheet::~StickerSheet() {
  destroy();
}

StickerSheet::StickerSheet(const StickerSheet & other) {
  copy(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet & other) {
  if(this != &other){
    this->destroy();
    this->copy(other);
  }
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned m) {
  Image** pics2 = new Image*[m];
  int* arrx2 = new int[m];
  int* arry2 = new int[m];
  if(m < curr) {
    for(unsigned i = 0; i < m; i++) {
      arrx2[i] = arrx[i];
      arry2[i] = arry[i];
      pics2[i] = pics[i];
    }
  }
  else {
    for(unsigned i = 0; i < curr; i++) {
      arrx2[i] = arrx[i];
      arry2[i] = arry[i];
      pics2[i] = pics[i];
    }
  }
  for(unsigned i = curr; i < m; i++) {
    arrx2[i] = 0;
    arry2[i] = 0;
    pics2[i] = NULL;
  }
  if(m < max) {
    for(unsigned i = m; i < max; i++)
      delete pics[i];
  }
  if(m < curr)
    curr = m;
  delete[] pics;
  pics = pics2;
  pics2 = NULL;
  delete[] arrx;
  arrx = arrx2;
  arrx2 = NULL;
  delete[] arry;
  arry = arry2;
  arry2 = NULL;
  max = m;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
  if(curr < max) {
    Image* ret = new Image();
    *ret = sticker;
    pics[curr] = ret;
    arrx[curr] = x;
    arry[curr] = y;
    curr++;
    //std::cout << "returned" << std::endl;
    return curr-1;
  }
  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if(index < curr) {
    if(pics[index] != NULL) {
      arrx[index] = x;
      arry[index] = y;
      return true;
    }
  }
  return false;
}

void StickerSheet::removeSticker(unsigned index) {
  delete pics[index];
  for(unsigned i = index; i < curr-1; i++) {
    arrx[i] = arrx[i+1];
    arry[i] = arry[i+1];
    pics[i] = pics[i+1];
  }
  arrx[curr-1] = 0;
  arry[curr-1] = 0;
  pics[curr-1] = NULL;
}

Image* StickerSheet::getSticker(unsigned index) const {
  if(index < max)
    return pics[index];
  return NULL;
}

void StickerSheet::copy(const StickerSheet & other) {
  base = new Image();
  base->resize(other.base->width(), other.base->height());
  *base = *(other.base);
  max = other.max;
  curr = other.curr;

  arrx = new int[max];
  arry = new int[max];
  pics = new Image*[max];

  for(unsigned i = 0; i < curr; i++) {
    arrx[i] = other.arrx[i];
    arry[i] = other.arry[i];
    pics[i] = new Image();
    *(pics[i]) = *(other.pics[i]);
  }

  for(unsigned i = curr; i < max; i++) {
    arrx[i] = 0;
    arry[i] = 0;
    pics[i] = NULL;
  }
}

void StickerSheet::destroy() {
  delete base;
  delete[] arrx;
  delete[] arry;
  for(unsigned i = 0; i < curr; i++)
    delete pics[i];
  delete[] pics;
}

Image StickerSheet::render() const {

  Image ret = Image();
  unsigned width = base->width();
  unsigned height = base->height();
  ret.resize(base->width(), base->height());

  for(unsigned x = 0; x < base->width(); x++) {
    for(unsigned y = 0; y < base->height(); y++) {
      ret.getPixel(x,y) = base->getPixel(x,y);
    }
  }

  for(unsigned i = 0; i < curr; i++) {
    if(pics[i] != NULL) {

      unsigned newx = arrx[i] + pics[i]->width();
      if(width < newx) {
        ret.resize(newx, height);
        width = newx;
      }
      unsigned newy = arry[i] + pics[i]->height();
      if(height < newy) {
        ret.resize(width, newy);
        height = newy;
      }

      for(unsigned x = arrx[i]; x < newx; x++) {
        for(unsigned y = arry[i]; y < newy; y++) {

          if(pics[i]->getPixel(x-arrx[i],y-arry[i]).a > 0) {
            ret.getPixel(x,y) = pics[i]->getPixel(x-arrx[i],y-arry[i]);
          }

        }
      }
    }
  }

  return ret;
}
