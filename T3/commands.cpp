#include "commands.hpp"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <functional>
#include "StreamGuard.hpp"

namespace
{
  bool isNumber(std::string str)
  {
    bool isNumber = true;
    for (size_t i = 0; i < str.size() && isNumber; i++)
    {
      isNumber = isNumber && std::isdigit(str.at(i));
    }
    return isNumber;
  }
  double getLength(const ivlicheva::Point& a, const ivlicheva::Point& b)
  {
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
  }
  bool isRight(const ivlicheva::Point& a, const ivlicheva::Point& b, const ivlicheva::Point& c)
  {
    double straight1 = getLength(a, b);
    double straight2 = getLength(b, c);
    double unionStraight = getLength(a, c);
    return std::sqrt(std::pow(straight1, 2) + std::pow(straight2, 2)) == unionStraight;
  }
  struct Points
  {
    public:
      Points(const ivlicheva::Point& point1, const ivlicheva::Point& point2):
        point1_(point1),
        point2_(point2)
      {}

      bool operator()(const ivlicheva::Point& point)
      {
        bool isRightAngle = isRight(point1_, point2_, point);
        point1_ = point2_;
        point2_ = point;
        return isRightAngle;
      }

    private:
      ivlicheva::Point point1_;
      ivlicheva::Point point2_;
  };
}

ivlicheva::Commands::Commands(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out):
  polygons_(vector),
  in_(in),
  out_(out)
{}

bool ivlicheva::Commands::getArea()
{
  std::string parameter = "";
  in_ >> parameter;
  StreamGuard guard(out_);
  out_ << std::fixed << std::setprecision(1);
  try
  {
    if (isNumber(parameter))
    {
      size_t count = std::stoul(parameter);
      out_ << getAreaCount(count) << '\n';
    }
    else if (parameter == "ODD")
    {
      out_ << getAreaOdd() << '\n';
    }
    else if (parameter == "EVEN")
    {
      out_ << getAreaEven() << '\n';
    }
    else if (parameter == "MEAN")
    {
      out_ << getAreaMean() << '\n';
    }
    else
    {
      return false;
    }
  }
  catch (const std::exception&)
  {
    return false;
  }
  return true;
}

bool ivlicheva::Commands::getMax()
{
  std::string parameter = "";
  in_ >> parameter;
  try
  {
    if (parameter == "AREA")
    {
      StreamGuard guard(out_);
      out_ << std::fixed << std::setprecision(1);
      out_ << getMaxArea() << '\n';
    }
    else if (parameter == "VERTEXES")
    {
      out_ << getMaxVertexes() << '\n';
    }
    else
    {
      return false;
    }
  }
  catch (const std::exception&)
  {
    return false;
  }
  return true;
}

bool ivlicheva::Commands::getMin()
{
  std::string parameter = "";
  in_ >> parameter;
  try
  {
    if (parameter == "AREA")
    {
      StreamGuard guard(out_);
      out_ << std::fixed << std::setprecision(1);
      out_ << getMinArea() << '\n';
    }
    else if (parameter == "VERTEXES")
    {
      out_ << getMinVertexes() << '\n';
    }
    else
    {
      return false;
    }
  }
  catch (const std::exception&)
  {
    return false;
  }
  return true;
}

bool ivlicheva::Commands::getCount()
{
  std::string parameter = "";
  in_ >> parameter;
  if (isNumber(parameter))
  {
    try
    {
      size_t count = std::stoul(parameter);
      out_ << getCountNumOfVertexes(count) << '\n';
    }
    catch (const std::exception&)
    {
      return false;
    }
  }
  else if (parameter == "ODD")
  {
    out_ << getCountOdd() << '\n';
  }
  else if (parameter == "EVEN")
  {
    out_ << getCountEven() << '\n';
  }
  else
  {
    return false;
  }
  return true;
}

bool ivlicheva::Commands::getRects()
{
  out_ << doGetRects() << '\n';
  return true;
}

bool ivlicheva::Commands::getRightShapes()
{
  out_ << doGetRightShapes() << '\n';
  return true;
}

double ivlicheva::Commands::doGetArea(const Polygon& polygon) const
{
  size_t size = polygon.points.size();
  Point pointPrev = polygon.points[size - 1];
  double area = std::accumulate(polygon.points.begin(), polygon.points.end(), 0,
   [&pointPrev](double area, const Point& point)
   {
     area += (point.x + pointPrev.x) * (pointPrev.y - point.y);
     pointPrev = point;
     return area;
   });
  return std::abs(area / 2.0);
}

double ivlicheva::Commands::getAreaOdd() const
{
  return std::accumulate(polygons_.begin(), polygons_.end(), 0,
   [&](double area, const Polygon& polygon)
   {
     if (polygon.points.size() % 2 != 0)
     {
       return area + doGetArea(polygon);
     }
     return area;
   });
}

double ivlicheva::Commands::getAreaEven() const
{
  return std::accumulate(polygons_.begin(), polygons_.end(), 0,
   [&](double area, const Polygon& polygon)
   {
     if (polygon.points.size() % 2 == 0)
     {
       return area + doGetArea(polygon);
     }
     return area;
   });
}

double ivlicheva::Commands::getAreaMean() const
{
  if (!polygons_.size())
  {
    throw std::logic_error("Error");
  }
  double area = getAreaOdd() + getAreaEven();
  return area / polygons_.size();
}

double ivlicheva::Commands::getAreaCount(const size_t& n) const
{
  if (n < 3)
  {
    throw std::logic_error("Error");
  }
  return std::accumulate(polygons_.begin(), polygons_.end(), 0,
   [&](double area, const Polygon& polygon)
   {
     if (polygon.points.size() == n)
     {
       return area + doGetArea(polygon);
     }
     return area;
   });
}

double ivlicheva::Commands::getMaxArea() const
{
  if (polygons_.empty())
  {
    throw std::logic_error("Error");
  }
  Polygon polygonMax = *std::max_element(polygons_.begin(), polygons_.end(),
   [&](const Polygon& first, const Polygon& second)
   {
     return doGetArea(first) < doGetArea(second);
   });
  return doGetArea(polygonMax);
}

size_t ivlicheva::Commands::getMaxVertexes() const
{
  if (polygons_.empty())
  {
    throw std::logic_error("Error");
  }
  Polygon polygonMax = *std::max_element(polygons_.begin(), polygons_.end(),
   [](const Polygon& first, const Polygon& second)
   {
     return first.points.size() < second.points.size();
   });
  return polygonMax.points.size();
}

double ivlicheva::Commands::getMinArea() const
{
  if (polygons_.empty())
  {
    throw std::logic_error("Error");
  }
  Polygon polygonMin = *std::min_element(polygons_.begin(), polygons_.end(),
   [&](const Polygon& first, const Polygon& second)
   {
     return doGetArea(first) < doGetArea(second);
   });
  return doGetArea(polygonMin);
}

size_t ivlicheva::Commands::getMinVertexes() const
{
  if (polygons_.empty())
  {
    throw std::logic_error("Error");
  }
  Polygon polygonMin = *std::min_element(polygons_.begin(), polygons_.end(),
   [](const Polygon& first, const Polygon& second)
   {
     return first.points.size() < second.points.size();
   });
  return polygonMin.points.size();
}

size_t ivlicheva::Commands::getCountOdd() const
{
  return std::count_if(polygons_.begin(), polygons_.end(),
   [](const Polygon& polygon)
   {
     return polygon.points.size() % 2;
   });
}

size_t ivlicheva::Commands::getCountEven() const
{
  return std::count_if(polygons_.begin(), polygons_.end(),
   [](const Polygon& polygon)
   {
     return !(polygon.points.size() % 2);
   });
}

size_t ivlicheva::Commands::getCountNumOfVertexes(const size_t& n) const
{
  if (n < 3)
  {
    throw std::logic_error("Error");
  }
  return std::count_if(polygons_.begin(), polygons_.end(),
   [&n](const Polygon& polygon)
   {
     return polygon.points.size() == n;
   });
}

bool ivlicheva::Commands::isRect(const Polygon& polygon) const
{
  if (polygon.points.size() != 4)
  {
    return false;
  }
  bool isRightAngle1 = isRight(polygon.points[0], polygon.points[1], polygon.points[2]);
  bool isRightAngle2 = isRight(polygon.points[0], polygon.points[3], polygon.points[2]);
  return isRightAngle1 && isRightAngle2;
}

size_t ivlicheva::Commands::doGetRects() const
{
  return std::count_if(polygons_.begin(), polygons_.end(), std::bind(&Commands::isRect, this, std::placeholders::_1));
}

bool ivlicheva::Commands::isRightShape(const Polygon& polygon) const
{
  size_t size = polygon.points.size();
  Points functor(polygon.points[size - 2], polygon.points[size - 1]);
  return std::count_if(polygon.points.begin(), polygon.points.end(), functor);
}

size_t ivlicheva::Commands::doGetRightShapes() const
{
  return std::count_if(polygons_.begin(), polygons_.end(), std::bind(&Commands::isRightShape, this, std::placeholders::_1));
}
