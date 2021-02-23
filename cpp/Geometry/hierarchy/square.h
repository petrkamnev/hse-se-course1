#pragma once
#include "circle.h"
#include "rectangle.h"

class Square : public Rectangle {
  Square() = default;
  Square(const Point& p1, const Point& p2);
  Circle circumscribedCircle();
  Circle inscribedCircle();
};
