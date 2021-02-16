#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace  gromov
{
  class Circle : public Shape
  {
  public:
    Circle(double radius, const point_t& position);

    void move(const point_t& position) noexcept override;

    void move(const double x, const double y) noexcept override;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    double getRadius() const noexcept;

    point_t getCentre() const noexcept override;

    void scale(const double coefficient) override;

    void rotate(double angle) noexcept override;
    
  private:
    double radius_;
    point_t position_;
  };
}

#endif
