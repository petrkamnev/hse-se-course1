#include "rectangle.h"

#include <algorithm>

Rectangle::Rectangle(const Point& p1, const Point& p2, const double& d) {
  double x1 = std::min(p1.x, p2.x);
  double x2 = std::max(p1.x, p2.x);
  double y1 = std::min(p1.y, p2.y);
  double y2 = std::max(p1.y, p2.y);
  vertices = {Point(x2, y1), Point(x2, y2), Point(x1, y2), Point(x1, y1)};
}

const Point& Rectangle::center() {
  return __sum__(__prod__(vertices[0], 1 / 2), __prod__(vertices[2], 1 / 2));
}

std::pair<Line, Line> Rectangle::diagonals() {
  return std::make_pair(Line(vertices[0], vertices[2]),
                        Line(vertices[1], vertices[3]));
}