#include "complexquad.hpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include "base-types.hpp"
#include "base-operations.hpp"

namespace
{
  double getTriangleArea(const ivlicheva::point_t& a, const ivlicheva::point_t& b, const ivlicheva::point_t& c)
  {
    double side1 = ivlicheva::getLength(a, b);
    double side2 = ivlicheva::getLength(a, c);
    double side3 = ivlicheva::getLength(b, c);
    double p = (side1 + side2 + side3) / 2;
    return std::sqrt(p * (p - side1) * (p - side2) * (p - side3));
  }
}

ivlicheva::Complexquad::Complexquad(const point_t& a, const point_t& b, const point_t& c, const point_t& d):
  a_(a),
  b_(b),
  c_(c),
  d_(d)
{
  bool isEqual = a == b || a == c || a == d || b == c || b == d || c == d;
  point_t intersectPos = getCenterPos();
  bool isPos = intersectPos == a || intersectPos == b || intersectPos == c || intersectPos == d;
  if (isEqual || isPos || !isIntersect(a, b, c, d))
  {
    throw std::logic_error("Bad values");
  }
}

double ivlicheva::Complexquad::getArea() const
{
  point_t pos = getCenterPos();
  return getTriangleArea(a_, pos, d_) + getTriangleArea(c_, b_, pos);
}

ivlicheva::rectangle_t ivlicheva::Complexquad::getFrameRect() const
{
  point_t leftBottom{std::min({a_.x, b_.x, c_.x, d_.x}), std::min({a_.y, b_.y, c_.y, d_.y})};
  point_t rightTop{std::max({a_.x, b_.x, c_.x, d_.x}), std::max({a_.y, b_.y, c_.y, d_.y})};
  return createRectangle(leftBottom, rightTop);
}

void ivlicheva::Complexquad::move(const point_t& newPos)
{
  point_t pos = getCenterPos();
  double offsetX = newPos.x - pos.x;
  double offsetY = newPos.y - pos.y;
  a_.x += offsetX;
  a_.y += offsetY;
  b_.x += offsetX;
  b_.y += offsetY;
  c_.x += offsetX;
  c_.y += offsetY;
  d_.x += offsetX;
  d_.y += offsetY;
}

void ivlicheva::Complexquad::move(double offsetX, double offsetY)
{
  a_.x += offsetX;
  a_.y += offsetY;
  b_.x += offsetX;
  b_.y += offsetY;
  c_.x += offsetX;
  c_.y += offsetY;
  d_.x += offsetX;
  d_.y += offsetY;
}

void ivlicheva::Complexquad::doScale(double k)
{
  point_t pos = getCenterPos();
  a_ = scalePoint(a_, pos, k);
  b_ = scalePoint(b_, pos, k);
  c_ = scalePoint(c_, pos, k);
  d_ = scalePoint(d_, pos, k);
}

ivlicheva::point_t ivlicheva::Complexquad::getCenterPos() const
{
  point_t pos;
  double n = 0;
  if (b_.y - a_.y != 0)
  {
    double q = (b_.x - a_.x) / (a_.y - b_.y);
    double sn = (c_.x - d_.x) + (c_.y - d_.y) * q;
    double fn = (c_.x - a_.x) + (c_.y - a_.y) * q;
    n = fn / sn;
  }
  else
  {
    n = (c_.y - a_.y) / (c_.y - d_.y);
  }
  pos.x = c_.x + (d_.x - c_.x) * n;
  pos.y = c_.y + (d_.y - c_.y) * n;
  return pos;
}
