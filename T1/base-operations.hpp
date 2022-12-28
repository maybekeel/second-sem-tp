#ifndef BASE_OPERATIONS_HPP
#define BASE_OPERATIONS_HPP

#include <iosfwd>
#include "base-types.hpp"

namespace ivlicheva
{
  bool operator==(const point_t&, const point_t&);
  std::ostream& operator<<(std::ostream&, const point_t&);
  std::ostream& operator<<(std::ostream&, const rectangle_t&);
  rectangle_t createRectangle(const point_t&, const point_t&);
  bool isIntersect(const point_t&, const point_t&, const point_t&, const point_t&);
  double getLength(const point_t&, const point_t&);
  point_t scalePoint(const point_t&, const point_t&, double);
}

#endif
