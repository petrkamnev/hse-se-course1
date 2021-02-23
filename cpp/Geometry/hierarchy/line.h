#pragma once
#include "point.h"

class Line {
 public:
  Line(const Point& c, const Point& d);
  Line();

  bool operator==(const Line& other);
  bool operator!=(const Line& other);

  double get_a();
  double get_b();
  double get_c();

 protected:
  double a;
  double b;
  double c;
};