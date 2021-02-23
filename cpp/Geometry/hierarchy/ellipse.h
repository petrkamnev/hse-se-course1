#pragma once

#include <utility>

#include "shape.h"

class Ellipse : Shape {
 public:
  Ellipse() = default;
  Ellipse(const Point& p1, const Point& p2, const double& sum_);

  std::pair<Point, Point> focuses();
  std::pair<Line, Line> directrices();
  double eccentricity() const;
  Point center();
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
  Point __get__vector__(const Point& a, const Point& b) const;
  double __get__len__(const Point& a) const;
  Point __sum__(const Point& a, const Point& b) const;
  Point __prod__(const Point& a, double k) const;
  std::pair<Point, Point> focuses_;
  double sum;
};