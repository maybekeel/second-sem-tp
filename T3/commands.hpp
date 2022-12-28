#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <string>
#include <iosfwd>
#include "figures.hpp"

namespace ivlicheva
{
  struct Commands
  {
    public:
      Commands(const std::vector< Polygon >&, std::istream&, std::ostream&);
      bool getArea();
      bool getMax();
      bool getMin();
      bool getCount();
      bool getRects();
      bool getRightShapes();

    private:
      std::vector< Polygon > polygons_;
      std::istream& in_;
      std::ostream& out_;
      double doGetArea(const Polygon&) const;
      double getAreaOdd() const;
      double getAreaEven() const;
      double getAreaMean() const;
      double getAreaCount(const size_t&) const;
      double getMaxArea() const;
      size_t getMaxVertexes() const;
      double getMinArea() const;
      size_t getMinVertexes() const;
      size_t getCountOdd() const;
      size_t getCountEven() const;
      size_t getCountNumOfVertexes(const size_t&) const;
      bool isRect(const Polygon&) const;
      size_t doGetRects() const;
      bool isRightShape(const Polygon&) const;
      size_t doGetRightShapes() const;
  };
}

#endif
