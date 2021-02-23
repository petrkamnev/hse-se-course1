#include "square.h"

Square::Square(const Point& p1, const Point& p2) { Rectangle(p1, p2, 1); }

Circle Square::circumscribedCircle() {
  return Circle(center(),
                __get__len__(__get__vector__(vertices[0], vertices[2])));
}

Circle Square::inscribedCircle() {
  return Circle(center(),
                __get__len__(__get__vector__(vertices[0], vertices[1])));
}