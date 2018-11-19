#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include <vector>
#include <algorithm>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  pic = png;
  first = start;
  tol = tolerance;
  q.push(first);
  int** arr = new int*[png.width()];
  for(unsigned i = 0; i < png.width(); i++){
    arr[i] = new int[png.height()];
    for(unsigned j = 0; j < png.height(); j++)
      arr[i][j] = 0;
  }
  visited = arr;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

bool BFS::isLegal(const Point & neighbor) {
  if(neighbor.x >= pic.width() || neighbor.y >= pic.height())
    return false;

  if(isVisited(neighbor))
    return false;

  if(calculateDelta(pic.getPixel(first.x, first.y), pic.getPixel(neighbor.x, neighbor.y)) > tol)
    return false;

  return true;
}

bool BFS::isVisited(const Point & point) {
  if(visited[point.x][point.y])
    return true;
  return false;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  if(isLegal(Point(point.x + 1, point.y)))
    q.push(Point(point.x + 1, point.y));

  //bottom neighbor
  if(isLegal(Point(point.x, point.y + 1)))
    q.push(Point(point.x, point.y + 1));

  //left neighbor
  if(isLegal(Point(point.x - 1, point.y)))
    q.push(Point(point.x - 1, point.y));

  //top neighbor
  if(isLegal(Point(point.x, point.y - 1)))
    q.push(Point(point.x, point.y - 1));
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point ret = q.front();
  q.pop();
  visited[ret.x][ret.y] = 1;

  while(!q.empty() && visited[q.front().x][q.front().y])
  q.pop();

  return ret;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return q.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  if(q.empty())
    return true;

  return false;
}

BFS::~BFS() {
  for(unsigned i = 0; i < pic.width(); i++)
    delete[] visited[i];
  delete[] visited;
}
