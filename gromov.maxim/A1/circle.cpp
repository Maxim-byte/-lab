#include "circle.hpp"
#include <cmath>
#include <stdexcept>

Circle::Circle(double radius, const point_t& position):
  radius_(radius),
  position_(position)
{
  if(radius <= 0)
  {
    throw std::invalid_argument("Radius must be positive");
  }
}

void Circle::move(const point_t& position)
{
  position_ = position;
}

void Circle::move(const double x,const double y)
{
  position_ = {position_.x + x,position_.y + y};
}

double Circle::getArea() const
{
  return (radius_ * radius_ * M_PI);
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ 2 * radius_, 2 * radius_,position_};
}

double Circle::getRadius() const
{
  return radius_;
}

point_t Circle::getCentre() const
{
  return position_;
}
