#ifndef POLYGON_H
#define POLYGON_H

#include <memory>
#include "shape.hpp"
#include "base-types.hpp"

namespace ivlicheva
{
  class Polygon: public Shape
  {
    public:
      Polygon() = delete;
      Polygon(const Polygon&) = default;
      Polygon(std::unique_ptr< point_t[] >&&, size_t);
      ~Polygon() = default;

      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(const point_t&) override;
      void move(double, double) override;
      void doScale(double) override;

    private:
      std::unique_ptr< point_t[] > points_;
      size_t n_;
      point_t getCenterPos() const;
  };
}

#endif
