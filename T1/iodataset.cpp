#include "iodataset.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <functional>
#include <string>
#include "shape.hpp"
#include "rectangle.hpp"
#include "base-types.hpp"
#include "ioparse.hpp"
#include "base-operations.hpp"
#include "traverse.hpp"

namespace
{
  void outShape(std::unique_ptr< ivlicheva::Shape >& shape, std::ostream& stream)
  {
    stream << ' ' << shape->getFrameRect();
  }

  struct sumShapesArea
  {
    sumShapesArea():
      area(0.f)
    {}

    void operator()(std::unique_ptr< ivlicheva::Shape >& shape)
    {
      area += shape->getArea();
    }

    double getArea() const
    {
      return area;
    }

  private:
    double area;
  };
}

void ivlicheva::outShapes(shapesArray_t& shapes, size_t size, std::ostream& stream)
{
  sumShapesArea functor;
  functor = traverse(shapes, size, functor);
  stream << functor.getArea();
  traverse(shapes, size, std::bind(outShape, std::placeholders::_1, std::ref(stream)));
  stream << '\n';
}

double ivlicheva::calculateShapesArea(const shapesArray_t& shapes, size_t size)
{
  double area = 0;
  for (size_t i = 0; i < size; ++i)
  {
    area += shapes[i]->getArea();
  }
  return area;
}
