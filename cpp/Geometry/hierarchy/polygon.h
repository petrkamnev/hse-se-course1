#pragma once
#include <vector>

#include "shape.h"

class Polygon : public Shape {
 public:
  Polygon() = default;
  Polygon(const std::vector<Point>& other);

  int verticesCount();
  std::vector<Point> getVertices() const;
  bool isConvex();
  double perimeter();
  double area();
  bool operator==(const Shape& another);
  bool isCongruentTo(const Shape& another);
  bool isSimilarTo(const Shape& another);
  bool containsPoint(Point point);
  void rotate(Point center, double angle);
  void reflex(Point center);
  void reflex(Line axis);
  void scale(Point center, double coefficient);

 protected:
  std::vector<Point> vertices;
  Point __get__vector__(const Point& a, const Point& b);
  double __cross__prod__(const Point& a, const Point& b);
  double __dot__prod__(const Point& a, const Point& b);
  double __get__len__(const Point& a);
  double __get__angle__(const Point& a, const Point& b);
  Point __sum__(const Point& a, const Point& b);
  Point __prod__(const Point& a, double k);
};