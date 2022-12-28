#include "polygon.hpp"
#include <memory>
#include <stdexcept>
#include <cmath>
#include "base-types.hpp"
#include "base-operations.hpp"

ivlicheva::Polygon::Polygon(std::unique_ptr< point_t[] >&& points, size_t n):
  points_(std::move(points)),
  n_(n)
{
  if (n < 3)
  {
    throw std::logic_error("Not enough points");
  }
  bool isNotEqual = false;
  for (size_t i = 0; i < n - 1 && !isNotEqual; ++i)
  {
    for (size_t j = i + 1; j < n && !isNotEqual; ++j)
    {
      isNotEqual = points_[i] == points_[j];
    }
  }
  if (isNotEqual)
  {
    throw std::logic_error("Some points are equal");
  }
}

double ivlicheva::Polygon::getArea() const
{
  double area = 0;
  size_t j = n_ - 1;
  for (size_t i = 0; i < n_; ++i)
  {
    area += (points_[i].x + points_[j].x) * (points_[j].y - points_[i].y);
    j = i;
  }
  return std::abs(area / 2.0);
}

ivlicheva::rectangle_t ivlicheva::Polygon::getFrameRect() const
{
  point_t leftBottom = points_[0];
  point_t rightTop = points_[0];
  for (size_t i = 1; i < n_; ++i)
  {
    point_t p = points_[i];
    if (p.x < leftBottom.x)
    {
      leftBottom.x = p.x;
    }
    if (p.y < leftBottom.y)
    {
      leftBottom.y = p.y;
    }
    if (p.x > rightTop.x)
    {
      rightTop.x = p.x;
    }
    if (p.y > rightTop.y)
    {
      rightTop.y = p.y;
    }
  }
  return createRectangle(leftBottom, rightTop);
}

void ivlicheva::Polygon::move(const point_t& newPos)
{
  point_t pos = getCenterPos();
  double offsetX = newPos.x - pos.x;
  double offsetY = newPos.y - pos.y;
  for (size_t i = 0; i < n_; ++i)
  {
    points_[i].x += offsetX;
    points_[i].y += offsetY;
  }
}

void ivlicheva::Polygon::move(double offsetX, double offsetY)
{
  for (size_t i = 0; i < n_; ++i)
  {
    points_[i].x += offsetX;
    points_[i].y += offsetY;
  }
}

void ivlicheva::Polygon::doScale(double k)
{
  point_t pos = getCenterPos();
  for (size_t i = 0; i < n_; ++i)
  {
    points_[i] = scalePoint(points_[i], pos, k);
  }
}

ivlicheva::point_t ivlicheva::Polygon::getCenterPos() const
{
  point_t pos{0, 0};
  for (size_t i = 0; i < n_; ++i)
  {
    pos.x += points_[i].x;
    pos.y += points_[i].y;
  }
  pos.x /= n_;
  pos.y /= n_;
  return pos;
}
