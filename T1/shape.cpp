#include "shape.hpp"
#include <stdexcept>

void ivlicheva::Shape::scale(double k)
{
  if (k <= 0)
  {
    throw std::logic_error("Bad coef");
  }
  doScale(k);
}
