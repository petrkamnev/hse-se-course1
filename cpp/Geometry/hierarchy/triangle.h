#pragma once
#include "circle.h"
#include "polygon.h"

class Triangle : public Polygon {
 public:
  Triangle() = default;
  Triangle(const Point& a, const Point& b, const Point& c);
  Circle circumscribedCircle();
  Circle inscribedCircle();
};