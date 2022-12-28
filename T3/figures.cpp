#include "figures.hpp"
#include <iostream>
#include <limits>
#include <iterator>
#include <algorithm>
#include "iostructs.hpp"

std::istream& ivlicheva::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point input;
  in >> DelimeterIO{'('} >> input.x >> DelimeterIO{';'} >> input.y >> DelimeterIO{')'};
  if (in)
  {
    point = input;
  }
  return in;
}

std::istream& ivlicheva::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t size = 0;
  in >> size;
  if (size < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  Polygon input;
  using istreamIter_t = std::istream_iterator< ivlicheva::Point >;
  std::copy_n(istreamIter_t(in), size, std::back_inserter(input.points));
  if (in)
  {
    polygon = input;
  }
  return in;
}

std::ostream& ivlicheva::operator<<(std::ostream& out, const Point& point)
{
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

std::ostream& ivlicheva::operator<<(std::ostream& out, const Polygon& polygon)
{
  std::copy(polygon.points.begin(), std::prev(polygon.points.end()), std::ostream_iterator< Point >(out, " "));
  out << *(--polygon.points.end());
  return out;
}
