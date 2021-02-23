#include "circle.h"

Circle::Circle(const Point& p, const double& radius) {
  Ellipse(p, p, radius * 2);
}
double Circle::radius() { return sum / 2; }