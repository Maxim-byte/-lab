#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include"shape.hpp"

namespace gromov
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t& position, double width, double height);

    void move(const point_t& position) noexcept override;

    void move(const double x, const double y) noexcept override;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    double getWidth() const noexcept;

    double getHeight() const noexcept;

    point_t getCentre() const noexcept override;

    void scale(const double coefficient) override;

    void rotate(double angle) noexcept override;

  private:
    point_t tops_[4];
  };
}

#endif
