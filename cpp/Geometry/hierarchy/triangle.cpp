#include "triangle.h"

Triangle::Triangle(const Point& a, const Point& b, const Point& c) {
  vertices = {a, b, c};
}

Circle Triangle::inscribedCircle() {
  Point A = vertices[0];
  Point B = vertices[1];
  Point C = vertices[2];
  double L1 = __get__len__(__get__vector__(A, B));
  double L2 = __get__len__(__get__vector__(B, C));
  double L3 = __get__len__(__get__vector__(C, A));
  double y0 = (L2 * A.y + L3 * B.y + L1 * C.y) / (L2 + L3 + L1);
  double x0 = (L2 * A.x + L3 * B.x + L1 * C.x) / (L2 + L3 + L1);
  double R =
      (B.x * A.y + A.x * y0 - A.y * x0 - B.x * y0 - B.y * A.x + B.y * x0) /
      sqrt(pow((A.x - B.x), 2) + pow((A.y - B.y), 2));
  return Circle(Point(x0, y0), R);
}

Circle Triangle::circumscribedCircle() {
  Point A = vertices[0];
  Point B = vertices[1];
  Point C = vertices[2];
  double L1 = __get__len__(__get__vector__(A, B));
  double L2 = __get__len__(__get__vector__(B, C));
  double L3 = __get__len__(__get__vector__(C, A));
  double x0 = -1 / 2 *
              ((A.y * (B.x * B.x + B.y * B.y - C.x * C.x - C.y * C.y) +
                B.y * (C.x * C.x + C.y * C.y - A.x * A.x - A.y * A.y) +
                C.y * (A.x * A.x + A.y * A.y - B.x * B.x - B.y * B.y)) /
               (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)));
  double y0 = 1 / 2 *
              ((A.x * (B.x * B.x + B.y * B.y - C.x * C.x - C.y * C.y) +
                B.x * (C.x * C.x + C.y * C.y - A.x * A.x - A.y * A.y) +
                C.x * (A.x * A.x + A.y * A.y - B.x * B.x - B.y * B.y)) /
               (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)));
  double R = __get__len__(__get__vector__(A, Point(x0, y0)));
  return Circle(Point(x0, y0), R);
}