#include "rectangle.hpp"
#include <stdexcept>
#include <string>
#include <cmath>
#include <algorithm>
#include "detail.hpp"

namespace gromov
{
  Rectangle::Rectangle(const point_t& position, double width, double height):
    tops_{{position.x - width / 2, position.y + height / 2},
      {position.x + width / 2, position.y + height / 2},
      {position.x - width / 2, position.y - height / 2},
      {position.x + width / 2, position.y - height / 2}}
  {
    if(width <= 0 || height <= 0)
    {
      throw std::invalid_argument(std::string("Height and Width must be positive,height = "
          + std::to_string(height) + " ,width = "
          + std::to_string(width)));
    }
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    double maxX = std::max({tops_[2].x, tops_[3].x, tops_[0].x, tops_[1].x}),
      minX = std::min({tops_[2].x, tops_[3].x, tops_[0].x, tops_[1].x}),
      maxY = std::max({tops_[2].y, tops_[3].y, tops_[0].y, tops_[1].y}),
      minY = std::min({tops_[2].y, tops_[3].y, tops_[0].y , tops_[1].y});
    return {maxX - minX, maxY - minY, {(maxX + minX) / 2, (maxY + minY) / 2}};
  }

  void Rectangle::move(const point_t& position) noexcept
  {
    move(position.x - getCentre().x ,position.y - getCentre().y);
  }

  void Rectangle::move(const double x, const double y) noexcept
  {
    for(point_t & top : tops_)
    {
      top.x += x;
      top.y += y;
    }
  }

  double Rectangle::getArea() const noexcept
  {
    return getWidth() * getHeight();
  }

  double Rectangle::getWidth() const noexcept
  {
    return detail::getDistance(tops_[0], tops_[1]);
  }

  double Rectangle::getHeight() const noexcept
  {
    return  detail::getDistance(tops_[0], tops_[2]);
  }

  point_t Rectangle::getCentre() const noexcept
  {
    return {(tops_[1].x + tops_[2].x) / 2, (tops_[1].y + tops_[2].y) / 2};
  }

  void Rectangle::scale(const double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument(std::string("Coefficient must be positive = "
          + std::to_string(coefficient)));
    }
    const point_t center = getCentre();
    for(point_t & top : tops_)
    {
      top.x = center.x + (top.x - center.x) * coefficient;
      top.y = center.y + (top.y - center.y) * coefficient;
    }
  }

  void Rectangle::rotate(double angle) noexcept
  {
    angle = (angle * M_PI) / 180;
    const double sin = std::sin(angle), cos = std::cos(angle);
    const point_t center = getCentre();
    for(point_t & top : tops_)
    {
      const double oldX = top.x;
      top.x = center.x + (top.x - center.x) * cos - (top.y - center.y) * sin;
      top.y = center.y + (oldX - center.x) * sin + (top.y - center.y) * cos;
    }
  }

}
