/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_

#include "Image.h"

namespace cs225{

class StickerSheet {

public:
  StickerSheet(const Image & picture, unsigned m);
  ~StickerSheet();
  StickerSheet(const StickerSheet & other);
  const StickerSheet& operator=(const StickerSheet & other);
  void changeMaxStickers(unsigned m);
  int addSticker(Image & sticker, unsigned x, unsigned y);
  bool translate(unsigned index, unsigned x, unsigned y);
  void removeSticker(unsigned index);
  Image* getSticker(unsigned index) const;
  Image render() const;
  void copy(const StickerSheet & other);
  void destroy();

  Image* base;
  unsigned max;
  int* arrx;
  int* arry;
  Image** pics;
  unsigned curr;

};

}

#endif
