#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const point_t& position, double width, double height):
  width_(width),
  height_(height),
  position_{ position.x,position.y }
{
  if(width <= 0 || height <=0)
  {
    throw std::invalid_argument("Height and Width must be positive");
  }
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{height_,width_,position_};
}

void Rectangle::move(const point_t& position)
{
  position_ = position;
}

void Rectangle::move(const double x, const double y)
{
  position_ = {x + position_.x,y + position_.y};
}

double Rectangle::getArea() const
{
  return(height_ * width_);
}

double Rectangle::getWidth() const
{
  return width_;
}

double Rectangle::getHeight() const
{
  return height_;
}

point_t Rectangle::getPosition() const
{
  return position_;
}
