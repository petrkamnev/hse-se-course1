#include "line.h"

#include <cmath>

Line::Line() {
  a = 1;
  b = 1;
  c = 1;
}

Line::Line(const Point& d, const Point& e) {
  double a = e.y - d.y;
  b = d.x - e.x;
  double c = -a * d.x - b * d.y;
  if (abs(a) >= 1e-9) {
    a /= a;
    b /= a;
    c /= a;
  } else if (abs(b) >= 1e-9) {
    b /= b;
    c /= b;
  } else if (abs(c) >= 1e-9) {
    c /= c;
  }
}

bool Line::operator==(const Line& other) {
  return (abs(a - other.a) < 1e-9) && (abs(b - other.b) < 1e-9) &&
         (abs(c - other.c) < 1e-9);
}

bool Line::operator!=(const Line& other) { return !(*this == other); }

double Line::get_a() { return a; }

double Line::get_b() { return b; }

double Line::get_c() { return c; }