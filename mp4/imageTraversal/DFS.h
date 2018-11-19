/**
 * @file DFS.h
 */

#ifndef DFS_H
#define DFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <stack>
#include <vector>
#include <algorithm>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  bool isLegal(const Point & neighbor);
  bool isVisited(const Point & point);
  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

  ~DFS();

private:
	/** @todo [Part 1] */
	/** add private members here*/

  PNG pic;
  Point first;
  double tol;
  stack<Point> s;
  int** visited;

};

#endif
