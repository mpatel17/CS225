#include <iterator>
#include <cmath>
#include <list>
#include <stack>
#include <vector>
#include <algorithm>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  pic = png;
  first = start;
//cout<<first<<endl;
  tol = tolerance;
//cout<<tol<<endl;
  s.push(first);
//cout<<s.top()<<endl;
  int** arr = new int*[png.width()];
  for(unsigned i = 0; i < png.width(); i++){
    arr[i] = new int[png.height()];
    for(unsigned j = 0; j < png.height(); j++)
      arr[i][j] = 0;
  }
  visited = arr;
//cout<<first<<endl;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
//cout<<first<<endl;
//cout<<tol<<endl;
  return ImageTraversal::Iterator(this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

bool DFS::isLegal(const Point & neighbor) {
  if(neighbor.x >= pic.width() || neighbor.y >= pic.height())
    return false;

  if(isVisited(neighbor))
    return false;

  if(calculateDelta(pic.getPixel(first.x, first.y), pic.getPixel(neighbor.x, neighbor.y)) > tol)
    return false;

  return true;
}

bool DFS::isVisited(const Point & point) {
  if(visited[point.x][point.y])
    return true;
  return false;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */

  //right neighbor
  if(isLegal(Point(point.x + 1, point.y)))
    s.push(Point(point.x + 1, point.y));

  //bottom neighbor
  if(isLegal(Point(point.x, point.y + 1)))
    s.push(Point(point.x, point.y + 1));

  //left neighbor
  if(isLegal(Point(point.x - 1, point.y)))
    s.push(Point(point.x - 1, point.y));

  //top neighbor
  if(isLegal(Point(point.x, point.y - 1)))
    s.push(Point(point.x, point.y - 1));

}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point ret;
  ret = s.top();
  s.pop();
  visited[ret.x][ret.y] = 1;

  while(!s.empty() && visited[s.top().x][s.top().y])
    s.pop();

  return ret;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return s.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  if(s.empty())
    return true;
  return false;
}

DFS::~DFS() {
  for(unsigned i = 0; i < pic.width(); i++)
    delete[] visited[i];
  delete[] visited;
}
