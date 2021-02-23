#include "ellipse.h"

#include <cmath>

Point Ellipse::__get__vector__(const Point& a, const Point& b) const {
  return Point(b.x - a.x, b.y - a.y);
}

double Ellipse::__get__len__(const Point& a) const {
  return sqrt(pow(a.x, 2) + pow(a.y, 2));
}

Point Ellipse::__sum__(const Point& a, const Point& b) const {
  return Point(a.x + b.x, a.y + b.y);
}

Point Ellipse::__prod__(const Point& a, double k) const {
  return Point(a.x * k, a.y * k);
}

Ellipse::Ellipse(const Point& p1, const Point& p2, const double& sum_) {
  focuses_ = std::make_pair(p1, p2);
  if (focuses_.first.x > focuses_.second.x + 1e-9 ||
      (abs(focuses_.first.x - focuses_.second.x) < 1e-9 &&
       focuses_.first.y > focuses_.second.y + 1e-9)) {
    std::swap(focuses_.first, focuses_.second);
  }
  sum = sum_;
}

std::pair<Point, Point> Ellipse::focuses() { return focuses_; };

Point Ellipse::center() {
  return Point((focuses_.first.x + focuses_.second.x) / 2,
               (focuses_.first.y + focuses_.second.y) / 2);
}

double Ellipse::eccentricity() const {
  return __get__len__(__get__vector__(focuses_.first, focuses_.second)) / sum;
}

std::pair<Line, Line> Ellipse::directrices() {
  Point c = center();
  double len = (sum / 2) / eccentricity();
  Point tmp = __get__vector__(c, focuses_.first);
  tmp = __prod__(tmp, len / __get__len__(tmp));
  Point d = __sum__(c, tmp);
  Point e = __sum__(c, __prod__(tmp, -1));
  Line ln = Line(focuses_.first, focuses_.second);
  return std::make_pair(
      Line(c, Point(__sum__(c, Point(ln.get_a(), ln.get_b())))),
      Line(d, Point(__sum__(d, Point(ln.get_a(), ln.get_b())))));
}

bool Ellipse::operator==(const Shape& another) {
  const Ellipse* other = dynamic_cast<const Ellipse*>(&another);
  if (!other) {
    return 0;
  }
  return focuses_ == other->focuses_ && abs(sum - other->sum) < 1e-9;
}

bool Ellipse::isCongruentTo(const Shape& another) {
  const Ellipse* other = dynamic_cast<const Ellipse*>(&another);
  if (!other) {
    return 0;
  }
  return (__get__len__(__get__vector__(focuses_.first, focuses_.second)) -
          __get__len__(__get__vector__(other->focuses_.first,
                                       other->focuses_.second))) < 1e-9 &&
         abs(sum - other->sum) < 1e-9;
}
bool Ellipse::isSimilarTo(const Shape& another) {
  const Ellipse* other = dynamic_cast<const Ellipse*>(&another);
  if (!other) {
    return 0;
  }
  return abs(eccentricity() - other->eccentricity()) < 1e-9;
}
bool Ellipse::containsPoint(Point point) {
  return __get__len__(__get__vector__(point, focuses_.first)) +
             __get__len__(__get__vector__(point, focuses_.second)) <
         sum + 1e-9;
}
void Ellipse::rotate(Point center, double angle) {
  angle = angle / 180 * 3.1415926;
  std::vector<Point*> tmp = {&(focuses_.first), &(focuses_.second)};
  for (Point* t1 : tmp) {
    Point& t = *t1;
    Point p = __get__vector__(center, t);
    p = Point(p.x * cos(angle) - p.y * sin(angle),
              p.x * sin(angle) + p.y * cos(angle));
    t = __sum__(center, p);
  }
}
void Ellipse::reflex(Point center) { rotate(center, 3.1415926); }
void Ellipse::reflex(Line axis) {
  std::vector<Point*> tmp = {&(focuses_.first), &(focuses_.second)};
  for (Point* t1 : tmp) {
    Point& t = *t1;
    double l = 2 * ((axis.get_a() * t.x + axis.get_b() * t.y + axis.get_c()) /
                    sqrt(pow(axis.get_a(), 2) + pow(axis.get_b(), 2)));
    Point tmp = __prod__(Point(axis.get_a(), axis.get_b()),
                         -l / __get__len__(Point(axis.get_a(), axis.get_b())));
    t = __sum__(t, tmp);
  }
}

void Ellipse::scale(Point center, double coefficient) {
  std::vector<Point*> tmp = {&(focuses_.first), &(focuses_.second)};
  for (Point* t1 : tmp) {
    Point& t = *t1;
    Point tmp = __get__vector__(center, t);
    t = __sum__(center, __prod__(tmp, coefficient));
  }
}

double Ellipse::perimeter() {
  double a = sum / 2;
  double b = a * sqrt(1 - pow(eccentricity(), 2));
  return 4 * (3.1415926 * a * b + (a - b) * (a - b)) / (a + b);
}

double Ellipse::area() {
  double a = sum / 2;
  double b = a * sqrt(1 - pow(eccentricity(), 2));
  return 3.1415926 * a * b;
}