#ifndef COMPLEXQUAD_H
#define COMPLEXQUAD_H

#include "shape.hpp"
#include "base-types.hpp"

namespace ivlicheva
{
  class Complexquad: public Shape
  {
    public:
      Complexquad() = delete;
      Complexquad(const Complexquad&) = default;
      Complexquad(const point_t&, const point_t&, const point_t&, const point_t&);
      ~Complexquad() = default;

      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(const point_t&) override;
      void move(double, double) override;
      void doScale(double) override;

    private:
      point_t a_, b_, c_, d_;
      point_t getCenterPos() const;
  };
}

#endif
