#include "polygon.h"

#include <cmath>

Polygon::Polygon(const std::vector<Point>& other) { vertices = other; }

int Polygon::verticesCount() { return vertices.size(); }

std::vector<Point> Polygon::getVertices() const { return vertices; }

Point Polygon::__get__vector__(const Point& a, const Point& b) {
  return Point(b.x - a.x, b.y - a.y);
}

double Polygon::__cross__prod__(const Point& a, const Point& b) {
  return a.x * b.y - a.y * b.x;
}

double Polygon::__dot__prod__(const Point& a, const Point& b) {
  return a.x * b.x + a.y * b.y;
}

Point Polygon::__sum__(const Point& a, const Point& b) {
  return Point(a.x + b.x, a.y + b.y);
}

Point Polygon::__prod__(const Point& a, double k) {
  return Point(a.x * k, a.y * k);
}

double Polygon::__get__angle__(const Point& a, const Point& b) {
  return atan2(__cross__prod__(a, b), __dot__prod__(a, b));
}

double Polygon::__get__len__(const Point& a) {
  return sqrt(pow(a.x, 2) + pow(a.y, 2));
}

bool Polygon::isConvex() {
  vertices.push_back(vertices[0]);
  vertices.push_back(vertices[1]);
  bool ans = 1;
  double cur = 0;
  for (int i = 0; i < vertices.size() - 2; i++) {
    double tmp = __cross__prod__(__get__vector__(vertices[i], vertices[i + 1]),
                                 __get__vector__(vertices[i], vertices[i + 2]));
    if ((tmp > 1e-9 && cur < -1e-9) || (tmp < -1e-9 && cur > 1e-9)) {
      ans = 0;
      break;
    }
    cur = tmp;
  }
  vertices.pop_back();
  vertices.pop_back();
  return ans;
}

double Polygon::perimeter() {
  vertices.push_back(vertices[0]);
  double ans = 0;
  for (int i = 0; i < vertices.size() - 1; i++) {
    ans += __get__len__(__get__vector__(vertices[i], vertices[i + 1]));
  }
  vertices.pop_back();
  return ans;
}

double Polygon::area() {
  double ans = 0;
  for (int i = 1; i < (int)vertices.size() - 1; i++) {
    ans += __cross__prod__(__get__vector__(vertices[0], vertices[i]),
                           __get__vector__(vertices[0], vertices[i + 1])) /
           2;
  }
  return abs(ans);
}

bool Polygon::operator==(const Shape& another) {
  const Polygon* other = dynamic_cast<const Polygon*>(&another);
  if (!other) {
    return 0;
  }
  std::vector<Point> vertices = other->getVertices();
  if (vertices.size() != vertices.size()) {
    return 0;
  }
  for (int i = 0; i < vertices.size(); i++) {
    if (vertices[i] != vertices[i]) {
      return 0;
    }
  }
  return 1;
}

bool Polygon::isCongruentTo(const Shape& another) {
  const Polygon* other = dynamic_cast<const Polygon*>(&another);
  if (!other) {
    return 0;
  }
  std::vector<Point> v1 = vertices;
  std::vector<Point> v2 = other->getVertices();
  if (v1.size() != v2.size()) {
    return 0;
  }
  v1.push_back(v1[0]);
  v2.push_back(v2[0]);
  for (int i = 0; i < v1.size() - 2; i++) {
    Point v11 = __get__vector__(v1[i], v1[i + 1]);
    Point v12 = __get__vector__(v1[i + 1], v1[i + 2]);
    Point v21 = __get__vector__(v2[i], v2[i + 1]);
    Point v22 = __get__vector__(v2[i + 1], v2[i + 2]);
    if (abs(__get__len__(v11) - __get__len__(v21)) > 1e-9 ||
        abs(__get__angle__(v11, v12) - __get__angle__(v21, v22)) > 1e-9) {
      return 0;
    }
  }
  return 1;
}

bool Polygon::isSimilarTo(const Shape& another) {
  const Polygon* other = dynamic_cast<const Polygon*>(&another);
  if (!other) {
    return 0;
  }
  std::vector<Point> v1 = vertices;
  std::vector<Point> v2 = other->getVertices();
  if (v1.size() != v2.size()) {
    return 0;
  }
  v1.push_back(v1[0]);
  v2.push_back(v2[0]);
  for (int i = 0; i < v1.size() - 2; i++) {
    Point v11 = __get__vector__(v1[i], v1[i + 1]);
    Point v12 = __get__vector__(v1[i + 1], v1[i + 2]);
    Point v21 = __get__vector__(v2[i], v2[i + 1]);
    Point v22 = __get__vector__(v2[i + 1], v2[i + 2]);
    if (abs(__get__len__(v12) / __get__len__(v11) -
            __get__len__(v22) / __get__len__(v21)) > 1e-9 ||
        abs(__get__angle__(v11, v12) - __get__angle__(v21, v22)) > 1e-9) {
      return 0;
    }
  }
  return 1;
}

bool Polygon::containsPoint(Point point) {
  vertices.push_back(vertices[0]);
  double sum = 0;
  for (int i = 0; i < vertices.size() - 1; i++) {
    if (point == vertices[i] ||
        abs(__cross__prod__(__get__vector__(point, vertices[i]),
                            __get__vector__(point, vertices[i + 1]))) < 1e-9 &&
            __dot__prod__(__get__vector__(point, vertices[i]),
                          __get__vector__(point, vertices[i + 1])) < -1e-9) {
      return 1;
    }
    sum += __get__angle__(__get__vector__(point, vertices[i]),
                          __get__vector__(point, vertices[i + 1]));
  }
  vertices.pop_back();
  return abs(sum) >= 1e-9;
}

void Polygon::rotate(Point center, double angle) {
  angle = angle / 180 * 3.1415926;
  for (int i = 0; i < vertices.size(); i++) {
    Point p = __get__vector__(center, vertices[i]);
    p = Point(p.x * cos(angle) - p.y * sin(angle),
              p.x * sin(angle) + p.y * cos(angle));
    vertices[i] = __sum__(center, p);
  }
}

void Polygon::reflex(Point center) { rotate(center, 3.1415926); }

void Polygon::reflex(Line axis) {
  for (int i = 0; i < vertices.size(); i++) {
    double l = 2 * ((axis.get_a() * vertices[i].x +
                     axis.get_b() * vertices[i].y + axis.get_c()) /
                    sqrt(pow(axis.get_a(), 2) + pow(axis.get_b(), 2)));
    Point tmp = __prod__(Point(axis.get_a(), axis.get_b()),
                         -l / __get__len__(Point(axis.get_a(), axis.get_b())));
    vertices[i] = __sum__(vertices[i], tmp);
  }
}

void Polygon::scale(Point center, double coefficient) {
  for (int i = 0; i < vertices.size(); i++) {
    Point tmp = __get__vector__(center, vertices[i]);
    vertices[i] = __sum__(center, __prod__(tmp, coefficient));
  }
}