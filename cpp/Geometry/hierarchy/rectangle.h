#pragma once
#include "polygon.h"

class Rectangle : public Polygon {
 public:
  Rectangle() = default;
  Rectangle(const Point& p1, const Point& p2, const double& d);
  const Point& center();
  std::pair<Line, Line> diagonals();
};