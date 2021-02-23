#pragma once
#include "ellipse.h"

class Circle : public Ellipse {
 public:
  Circle() = default;
  Circle(const Point& p, const double& radius);
  double radius();
};