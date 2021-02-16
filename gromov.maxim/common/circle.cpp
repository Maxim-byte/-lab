#include "circle.hpp"
#include <cmath>
#include <stdexcept>
#include <string>

namespace gromov
{
  Circle::Circle(double radius, const point_t& position):
    radius_(radius),
    position_(position)
  {
    if(radius <= 0)
    {
      throw std::invalid_argument(std::string("Radius must be positive,radius = " + std::to_string(radius_)));
    }
  }

  void Circle::move(const point_t& position) noexcept
  {
    position_ = position;
  }

  void Circle::move(const double x, const double y) noexcept
  {
    position_.x += x;
    position_.y += y;
  }

  double Circle::getArea() const noexcept
  {
    return (radius_ * radius_ * M_PI);
  }

  rectangle_t Circle::getFrameRect() const noexcept
  {
    return rectangle_t{2 * radius_, 2 * radius_, position_};
  }

  double Circle::getRadius() const noexcept
  {
    return radius_;
  }

  point_t Circle::getCentre() const noexcept
  {
    return position_;
  }

  void Circle::scale(const double coefficient)
  {
    if(coefficient <= 0)
    {
      throw std::invalid_argument(std::string("Coefficient must be positive,coefficient = " + std::to_string(coefficient)));
    }
    radius_ *= coefficient;
  }

  void Circle::rotate(const double) noexcept
  {}
}
