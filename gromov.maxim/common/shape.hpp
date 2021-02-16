#ifndef SHAPE_HPP
#define SHAPE_HPP

#include"base-types.hpp"

namespace gromov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const noexcept = 0;

    virtual rectangle_t getFrameRect() const noexcept = 0;

    virtual point_t getCentre() const noexcept = 0;

    virtual void move(const double x, const double y) = 0;

    virtual void move(const point_t& center) noexcept = 0;

    virtual void scale(const double coefficient) = 0;

    virtual void rotate(double angle) noexcept = 0;
    
  };
}

#endif
