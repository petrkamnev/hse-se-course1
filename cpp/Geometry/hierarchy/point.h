#pragma once
struct Point {
  double x;
  double y;

  Point() = default;
  Point(const double& x_, const double& y_);

  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;
};