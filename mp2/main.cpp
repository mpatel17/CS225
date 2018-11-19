#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image base;
  base.readFromFile("david.png");
  Image sticker1;
  sticker1.readFromFile("credit.png");
  Image sticker2;
  sticker2.readFromFile("glasses.png");
  sticker2.scale(200, 4);
  Image sticker3;
  sticker3.readFromFile("shorts.png");
  sticker3.scale(472, 2);

  StickerSheet sheet(base, 3);

  sheet.addSticker(sticker1, 0, base.height()-40);
  sheet.addSticker(sticker2, 485, 90);
  sheet.addSticker(sticker3, 360, 852);

  Image ret = sheet.render();
  ret.writeToFile("myImage.png");

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
