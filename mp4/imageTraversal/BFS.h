/**
 * @file BFS.h
 */

#ifndef BFS_H
#define BFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include <vector>
#include <algorithm>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  bool isLegal(const Point & neighbor);
  bool isVisited(const Point & point);
  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

  ~BFS();

private:
  /** @todo [Part 1] */
  /** add private members here*/

  PNG pic;
  Point first;
  double tol;
  queue<Point> q;
  int** visited;

};

#endif
