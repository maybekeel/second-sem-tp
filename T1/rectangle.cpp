#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>
#include "base-types.hpp"
#include "base-operations.hpp"

ivlicheva::Rectangle::Rectangle(rectangle_t rectangle):
  rectangle_(rectangle)
{
  if (rectangle.width <= 0 || rectangle.height <= 0)
  {
    throw std::logic_error("Incorrect length");
  }
}

ivlicheva::Rectangle::Rectangle(const point_t& leftBottom, const point_t& rightTop)
{
  if (rightTop.x <= leftBottom.x || rightTop.y <= leftBottom.y)
  {
    throw std::logic_error("Incorrect points");
  }
  rectangle_ = createRectangle(leftBottom, rightTop);
}

double ivlicheva::Rectangle::getArea() const
{
  return rectangle_.width * rectangle_.height;
}

ivlicheva::rectangle_t ivlicheva::Rectangle::getFrameRect() const
{
  return rectangle_;
}

void ivlicheva::Rectangle::move(const point_t& newPos)
{
  rectangle_.pos = newPos;
}

void ivlicheva::Rectangle::move(double offsetX, double offsetY)
{
  rectangle_.pos.x += offsetX;
  rectangle_.pos.y += offsetY;
}

void ivlicheva::Rectangle::doScale(double k)
{
  rectangle_.width *= k;
  rectangle_.height *= k;
}
