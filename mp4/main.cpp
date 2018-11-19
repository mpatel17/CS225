
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]

  PNG png;
  png.readFromFile("smiley.png");

  Point center = Point(png.width()/2, png.height()/2);
  FloodFilledImage image(png);
  DFS dfs(png, center, 0.5);
  BFS bfs(png, center, 0.5);
  MyColorPicker purple(center, png.width()/2);
  image.addFloodFill(dfs, purple);
  image.addFloodFill(bfs, purple);

  Animation animation = image.animate(1000);

  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.


  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");



  return 0;
}
