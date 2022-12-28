#include <iostream>
#include <memory>
#include <iomanip>
#include <functional>
#include "polygon.hpp"
#include "complexquad.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "base-types.hpp"
#include "base-operations.hpp"
#include "ioparse.hpp"
#include "iodataset.hpp"
#include "memoryShapes.hpp"
#include "traverse.hpp"

namespace ivl = ivlicheva;

namespace
{
  void scale(const ivl::point_t& scalePos, const double k, std::unique_ptr< ivl::Shape >& shape)
  {
    if (k <= 0)
    {
      throw std::logic_error("Bad scale coef");
    }
    ivl::point_t oldCenter = shape->getFrameRect().pos;
    shape->move(scalePos);
    double offsetX = shape->getFrameRect().pos.x - oldCenter.x;
    double offsetY = shape->getFrameRect().pos.y - oldCenter.y;
    shape->scale(k);
    shape->move(-offsetX * k, -offsetY * k);
  }
}

int main()
{
  using ushape_t = std::unique_ptr< ivl::Shape >;
  std::cout << std::fixed << std::setprecision(1);
  size_t size = 0;
  size_t capacity = 0;
  std::unique_ptr< ushape_t[] > shapes = std::make_unique< ushape_t[] >(capacity);
  bool isScaled = false;
  while (!std::cin.eof())
  {
    try
    {
      std::string str = "";
      std::getline(std::cin, str);
      if (str.size())
      {
        std::string name = ivl::getSubstring(str);
        if (name == "RECTANGLE")
        {
          ivl::point_t a = ivl::convertStringToPoint(str);
          ivl::point_t b = ivl::convertStringToPoint(str);
          ushape_t shape = std::make_unique< ivl::Rectangle >(a, b);
          shapes = ivl::push< ushape_t, ivl::GoldenRatio >(std::move(shapes), size, capacity, std::move(shape));
        }
        else if (name == "POLYGON")
        {
          size_t sizeP = 0;
          size_t capP = 0;
          std::unique_ptr< ivl::point_t[] > points = std::make_unique< ivl::point_t[] >(sizeP);
          while (!str.empty())
          {
            ivl::point_t newPoint = ivl::convertStringToPoint(str);
            points = ivl::push< ivl::point_t, ivl::GoldenRatio >(std::move(points), sizeP, capP, std::move(newPoint));
          }
          ushape_t shape = std::make_unique< ivl::Polygon >(std::move(points), sizeP);
          shapes = ivl::push< ushape_t, ivl::GoldenRatio >(std::move(shapes), size, capacity, std::move(shape));
        }
        else if (name == "COMPLEXQUAD")
        {
          ivl::point_t a = ivl::convertStringToPoint(str);
          ivl::point_t b = ivl::convertStringToPoint(str);
          ivl::point_t c = ivl::convertStringToPoint(str);
          ivl::point_t d = ivl::convertStringToPoint(str);
          ushape_t shape = std::make_unique< ivl::Complexquad >(a, b, c, d);
          shapes = ivl::push< ushape_t, ivl::GoldenRatio >(std::move(shapes), size, capacity, std::move(shape));
        }
        else if (name == "SCALE")
        {
          ivl::point_t scalePos = ivl::convertStringToPoint(str);
          double k = std::stod(str);
          ivl::outShapes(shapes, size, std::cout);
          ivl::traverse(shapes, size, std::bind(scale, scalePos, k, std::placeholders::_1));
          ivl::outShapes(shapes, size, std::cout);
          isScaled = true;
          break;
        }
        else
        {
          continue;
        }
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  if (size == 0 || !isScaled)
  {
    std::cerr << "Bad args\n";
    return 1;
  }
  return 0;
}
