#include "base-operations.hpp"
#include <cmath>
#include <iostream>
#include "base-types.hpp"

namespace
{
  using pnt_t = ivlicheva::point_t;
  double getArea(const pnt_t& a, const pnt_t& b, const pnt_t& c)
  {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
  }

  bool isIntersect(double a, double b, double c, double d)
  {
    if (a > b)
    {
      std::swap(a, b);
    }
    if (c > d)
    {
      std::swap(c, d);
    }
    return std::max(a,c) <= std::min(b,d);
  }
}

bool ivlicheva::operator==(const point_t& a, const point_t& b)
{
  return a.x == b.x && a.y == b.y;
}

std::ostream& ivlicheva::operator<<(std::ostream& stream, const point_t& point)
{
  stream << point.x << ' ' << point.y;
  return stream;
}

std::ostream& ivlicheva::operator<<(std::ostream& stream, const rectangle_t& rectangle)
{
  point_t leftBottom{rectangle.pos.x - rectangle.width / 2, rectangle.pos.y - rectangle.height / 2};
  point_t rightTop{rectangle.pos.x + rectangle.width / 2, rectangle.pos.y + rectangle.height / 2};
  stream << leftBottom << ' ' << rightTop;
  return stream;
}

ivlicheva::rectangle_t ivlicheva::createRectangle(const point_t& a, const point_t& b)
{
  rectangle_t rectangle;
  rectangle.width = std::abs(a.x - b.x);
  rectangle.height = std::abs(a.y - b.y);
  rectangle.pos.x = ((a.x + b.x) / 2);
  rectangle.pos.y = ((a.y + b.y) / 2);
  return rectangle;
}

bool ivlicheva::isIntersect(const point_t& a, const point_t& b, const point_t& c, const point_t& d)
{
  bool intersect = ::isIntersect(a.x, b.x, c.x, d.x) && ::isIntersect(a.y, b.y, c.y, d.y);
  return intersect && getArea(a, b, c) * getArea(a, b, d) <= 0 && getArea(c, d, a) * getArea(c, d, b) <= 0;
}

double ivlicheva::getLength(const point_t& a, const point_t& b)
{
  return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

ivlicheva::point_t ivlicheva::scalePoint(const point_t& pos, const point_t& center, double k)
{
  return point_t{center.x + k * (pos.x - center.x), center.y + k * (pos.y - center.y)};
}
