#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.hpp"
#include "base-types.hpp"

namespace ivlicheva
{
  class Rectangle: public Shape
  {
    public:
      Rectangle() = delete;
      Rectangle(const Rectangle&) = default;
      Rectangle(rectangle_t);
      Rectangle(const point_t&, const point_t&);
      ~Rectangle() = default;

      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(const point_t&) override;
      void move(double, double) override;
      void doScale(double) override;

    private:
      rectangle_t rectangle_;
  };
}

#endif
